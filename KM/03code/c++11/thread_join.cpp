#include <iostream>
#include <thread>
#include <algorithm>
#include <unistd.h>
using  namespace std;


class ThreadRAII {
    std::thread &m_thread;
    public:
    ThreadRAII(std::thread &threadObj) : m_thread(threadObj) {}
    ~ThreadRAII() {
        // 假如 joinable 则调用 detach
        if (m_thread.joinable()) {
            m_thread.detach();
        }
    }
};

void thread_function() {
    for (int i = 0; i < 10000; i++) {
        std::cout << "thread_function executing" << std::endl;
    }
}

class WorkerThread {
public:
    void operator()() {
        sleep(1);
		std::cout << "Worker Thread " << std::this_thread::get_id() << "is Executing" << std::endl;
		
    }    
};
//g++ -std=c++11 -pthread  thread_join.cpp 
int main(void) {
    std::vector<std::thread> threadList;
    for (int i = 0; i < 10; i++) {
		std::thread threadObj(WorkerThread()));
        threadList.push_back(threadObj);
    }
    
	// 等待所有的工作线程结束，即对每一个 std::thread 对象调用 join() 函数
	std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
    // 下面这条语句是最后打印的
    std::cout << "Exiting from Main Thread join" << std::endl;
    
    return 0;
}