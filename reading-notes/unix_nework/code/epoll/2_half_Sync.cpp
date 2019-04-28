#include <pthread.h>	// for pthread.
#include <semaphore.h>	// for sem.
#include <queue>		// for queue.
#include <vector>		// for vector.
#include <string.h>		// for memset.
 
// for file operation.
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
// for print log.
#include <iostream>
 
using namespace std;
 
// 队列层
class TaskQueue
{
	public:
		/*
		 * 定义item。
		 */
		typedef struct _taskItem
		{
			int start_offset;
			int size;
			void *buffer;
			sem_t *sem;
		} TaskItem;
	public:
		TaskQueue()
		{
			pthread_mutex_init(&m_mutex, NULL);
		}
		~TaskQueue()
		{
			pthread_mutex_destroy(&m_mutex);
		}
 
		/*
		 * 添加任务。
		 */
		void append(TaskItem &item)
		{
			pthread_mutex_lock(&m_mutex);
			m_items.push(item);
			pthread_mutex_unlock(&m_mutex);
		}
 
		/*
		 * 抛出一个任务；
		 */
		bool pop(TaskItem &item)
		{
			pthread_mutex_lock(&m_mutex);
			if(m_items.empty())
			{
				pthread_mutex_unlock(&m_mutex);
				return false;
			}
			item.start_offset = m_items.front().start_offset;
			item.size = m_items.front().size;
			item.buffer = m_items.front().buffer;
			item.sem = m_items.front().sem;
			m_items.pop();
			pthread_mutex_unlock(&m_mutex);
 
			return true;
		}
 
		/*
		 * 获取item的size；
		 */
		int getSize()
		{
			int size = 0;
			pthread_mutex_lock(&m_mutex);
			size  = m_items.size();
			pthread_mutex_unlock(&m_mutex);
			return m_items.size();
		}
 
	private:
		queue<TaskItem> m_items;	// 任务队列。
		pthread_mutex_t m_mutex;	// 任务队列的互斥量。
};
 
// 异步任务层
class AioProcessor
{
	public:
		AioProcessor(int fd, TaskQueue *queue)
		{
			m_fd = fd;
			m_queue = queue;
			m_isStartup = false;
		}
		~AioProcessor()
		{
			shutdwon();
		}
 
		void startup(int thread_count)
		{
			if(!m_isStartup)
			{
				/*
		 		 * 启动指定数目的线程。
		 		 */
				m_isStartup = true;
				for(int i=0; i<thread_count; ++i)
				{
					pthread_t tid;
					pthread_create(&tid, NULL, process, this);
					m_tids.push_back(tid);
				}
			}
		}
		void shutdwon()
		{
			if(m_isStartup)
			{
				/*
				 * 结束启动的线程。
				 */
				m_isStartup = false;
				vector<pthread_t>::iterator iter = m_tids.begin();
				for(; iter<m_tids.end(); ++iter)
				{
					pthread_join(*iter, NULL);
				}
			}
		}
 
	private:
		static void *process(void *param)
		{
			AioProcessor *processor = (AioProcessor *)param;
 
			/*
			 * 处理读文件请求，读取完毕发送完毕信号。
			 */
			TaskQueue::TaskItem item_to_be_process;
			while(processor->m_isStartup)
			{
				if(processor->m_queue->pop(item_to_be_process))
				{
					pread(processor->m_fd, item_to_be_process.buffer, item_to_be_process.size, item_to_be_process.start_offset);
					sem_post(item_to_be_process.sem);
				}
				else
				{
					usleep(1000);
				}
			}
 
			/*
			 * 线程结束。
			 */
			return NULL;
		}
	private:
		int m_fd;					// 文件句柄
		TaskQueue *m_queue;			// 任务队列
		vector<pthread_t> m_tids;	// 线程Id
		bool m_isStartup;			// true:已启动；false:未启动。
};
 
// 应用层
class Reader
{
	public:
		Reader(int fd)
			: m_fd(fd), m_queue(), m_processor(new AioProcessor(m_fd, &m_queue))
		{
			/*
			 * 启动processor。
			 */
			m_processor->startup(2);
		}
 
		~Reader()
		{
			/*
			 * 停止processor，并释放相关资源。
			 */
			m_processor->shutdwon();
			delete m_processor;
		}
		void read(const int start_offset, int size, void *buffer)
		{
			/*
			 * 构造一个item。
			 */
			sem_t sem;
			sem_init(&sem, 0, 0);
			TaskQueue::TaskItem item;
			item.start_offset = start_offset;
			item.size = size;
			item.buffer = buffer;
			item.sem = &sem;
 
			/*
			 * 将上面的item加入到任务队列中。
			 */
			m_queue.append(item);
 
			/*
			 * 等待读文件操作完成。
			 */
			sem_wait(&sem);
			sem_destroy(&sem);
 
			/*
			 * 读文件操作完成。
			 */
			return;
 
		}
	private:
		int 			m_fd;			// 文件句柄.
		TaskQueue		m_queue;		// 任务队列.
		AioProcessor*	m_processor;	// 任务处理器.
};
 
// 测试样例。
int main()
{
	int fd = open("./a.file", O_RDONLY);
	Reader reader(fd);
 
	int size = 10;
	char *buf = new char[size + 1];
	memset(buf, '\0', size+1);
	for(int i=0; i<10; i++)
	{
		reader.read(i*size, size, buf);
		cout<<buf<<endl;
	}
 
	close(fd);
	return 0;
}
