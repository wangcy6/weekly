#include "dns_client.h"
#define DNSIP    "10.112.179.21"
#define DNSPORT   9821


#include "cJSON.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>



#define ERROR_SUCCESS  0
#define ERROR_SOCKET_CREATE                 1000
#define ERROR_SOCKET_SETREUSE               1001
#define ERROR_SOCKET_BIND                   1002
#define ERROR_SOCKET_LISTEN                 1003
#define ERROR_SOCKET_CLOSED                 1004
#define ERROR_SOCKET_GET_PEER_NAME          1005
#define ERROR_SOCKET_GET_PEER_IP            1006
#define ERROR_SOCKET_READ                   1007
#define ERROR_SOCKET_READ_FULLY             1008
#define ERROR_SOCKET_WRITE                  1009
#define ERROR_SOCKET_WAIT                   1010
#define ERROR_SOCKET_TIMEOUT                1011
#define ERROR_SOCKET_CONNECT                1012
#define ERROR_ST_SET_EPOLL                  1013
#define ERROR_ST_INITIALIZE                 1014
#define ERROR_ST_OPEN_SOCKET                1015
#define ERROR_ST_CREATE_LISTEN_THREAD       1016
#define ERROR_ST_CREATE_CYCLE_THREAD        1017
#define ERROR_ST_CONNECT                    1018
#define ERROR_SYSTEM_PACKET_INVALID         1019
#define ERROR_SYSTEM_CLIENT_INVALID         1020
#define ERROR_SYSTEM_ASSERT_FAILED          1021
#define ERROR_READER_BUFFER_OVERFLOW        1022
#define ERROR_SYSTEM_CONFIG_INVALID         1023
#define ERROR_SYSTEM_CONFIG_DIRECTIVE       1024
#define ERROR_SYSTEM_CONFIG_BLOCK_START     1025
#define ERROR_SYSTEM_CONFIG_BLOCK_END       1026
#define ERROR_SYSTEM_CONFIG_EOF             1027
#define ERROR_SYSTEM_STREAM_BUSY            1028
#define ERROR_SYSTEM_IP_INVALID             1029
#define ERROR_SYSTEM_FORWARD_LOOP           1030
#define ERROR_SYSTEM_WAITPID                1031
#define ERROR_SYSTEM_BANDWIDTH_KEY          1032
#define ERROR_SYSTEM_BANDWIDTH_DENIED       1033
#define ERROR_SYSTEM_PID_ACQUIRE            1034
#define ERROR_SYSTEM_PID_ALREADY_RUNNING    1035
#define ERROR_SYSTEM_PID_LOCK               1036
#define ERROR_SYSTEM_PID_TRUNCATE_FILE      1037
#define ERROR_SYSTEM_PID_WRITE_FILE         1038
#define ERROR_SYSTEM_PID_GET_FILE_INFO      1039
#define ERROR_SYSTEM_PID_SET_FILE_INFO      1040
#define ERROR_SYSTEM_FILE_ALREADY_OPENED    1041
#define ERROR_SYSTEM_FILE_OPENE             1042
#define ERROR_SYSTEM_FILE_CLOSE             1043
#define ERROR_SYSTEM_FILE_READ              1044
#define ERROR_SYSTEM_FILE_WRITE             1045
#define ERROR_SYSTEM_FILE_EOF               1046
#define ERROR_SYSTEM_FILE_RENAME            1047
#define ERROR_SYSTEM_CREATE_PIPE            1048
#define ERROR_SYSTEM_FILE_SEEK              1049
#define ERROR_SYSTEM_IO_INVALID             1050
#define ERROR_ST_EXCEED_THREADS             1051
#define ERROR_SYSTEM_SECURITY               1052
#define ERROR_SYSTEM_SECURITY_DENY          1053
#define ERROR_SYSTEM_SECURITY_ALLOW         1054
#define ERROR_SYSTEM_TIME                   1055
#define ERROR_SYSTEM_DIR_EXISTS             1056
#define ERROR_SYSTEM_CREATE_DIR             1057
#define ERROR_SYSTEM_KILL                   1058



#define  JSON_CONFFER             "confer"
#define  JSON_CONFERINFO          "info"
#define  JSON_CONFPUBSER           "pubser"
#define  JSON_SGREAMID                "streamid"
#define  JSON_REDISAPPNAME             "appname"
#define  NISMSGTYPELENG       1
#define  NISMSGLENGTH		  4
#define  NISMSGHEADSIZE     (NISMSGTYPELENG+NISMSGLENGTH)


#define  MSGTYPE_HEART            0x01
#define  MSGTYPE_CONFFERINFO      0x02
#define  MSGTYPE_STREAMINFO       0x03
#define  MSYTYPE_NOTIFYCONSTATE   0x04
#define  SC_INVOKE_MSG            0x07
#define  SC_INVOKE_STORAGE_MSG    0x08

void swap(void* pData, int32 size) {
	static int32 s_nDummy = 1;

	if (*(int8*)(&s_nDummy) != 0) {
		int8* pch = (int8*)pData;

		//		RTP_ASSERT(size > 0);

		for (int32 i = 0; i < (size >> 1); i++) {
			int8 chTemp;
			chTemp = pch[i];
			pch[i] = pch[size - 1 - i];
			pch[size - 1 - i] = chTemp;
		}
	}
}


void *thread_fun_trans(void *arg);
void *thread_fun(void *arg)
{
	cTestClient *pthis = (cTestClient *)arg;
	if (NULL == pthis)
	{
		return NULL;
	}

	char  m_chHead[NISMSGHEADSIZE];
	

	char *msg = pthis->set_msg_confinfo();
	int _senddatalen = strlen(msg);
	swap(&_senddatalen, sizeof(_senddatalen));

	byte _byte = MSGTYPE_CONFFERINFO;
	memcpy(m_chHead, &_byte, sizeof(byte));	//TYPE
	memcpy(m_chHead + NISMSGTYPELENG, &_senddatalen, sizeof(int));//len

	iovec iovs[2];
	iovs[0].iov_base = m_chHead;
	iovs[0].iov_len = (int)NISMSGHEADSIZE;
	iovs[1].iov_base = msg;
	iovs[1].iov_len = strlen(msg);
	ssize_t _nb_write = st_writev(pthis->m_stfd, iovs, 2, 0);

	free(msg);

    /**
	while (true)
	{
		char  m_chHead[NISMSGHEADSIZE];
		byte _byte = MSGTYPE_HEART;
		int _senddatalen = 0;
		memcpy(m_chHead, &_byte, sizeof(byte));	//TYPE
		memcpy(m_chHead + NISMSGTYPELENG, &_senddatalen, sizeof(int));//len

		int _nb_write = st_write(pthis->m_stfd, m_chHead, NISMSGHEADSIZE, 0);



		st_sleep(30);

	}
    **/


}

void *thread_fun_recv(void *arg)
{
	cTestClient *pthis = (cTestClient *)arg;
	if (NULL == pthis)
	{
		return NULL;
	}

	while (true)
	{
		char _chReadBUf[1024];
		int nb_read = st_read(pthis->m_stfd, _chReadBUf, 1024, ST_UTIME_NO_TIMEOUT);
	}

}

void cTestClient::join_confer(string stConferId, string stStreamId)
{
    //cout<<"join_confer" <<stConferId <<stStreamId<<endl;
	m_strConfId = stConferId;
	m_strStreamId = stStreamId;


	int ret = ERROR_SUCCESS;

	sockaddr_in addr;

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		ret = ERROR_SOCKET_CREATE;
		printf("create socket error. ret=%d", ret);
		return ;
	}

	
	m_stfd = st_netfd_open_socket(sock);
	if (m_stfd == NULL){
		ret = ERROR_ST_OPEN_SOCKET;
		printf("st_netfd_open_socket failed. ret=%d", ret);
		return ;
	}

	// connect to server.

	addr.sin_family = AF_INET;
	addr.sin_port = htons(DNSPORT);
	addr.sin_addr.s_addr = inet_addr(DNSIP);

	if (st_connect(m_stfd, (const struct sockaddr*)&addr, sizeof(sockaddr_in), ST_UTIME_NO_TIMEOUT) == -1)
	{
		ret = ERROR_ST_CONNECT;
		printf("connect to server error. ret=%d",  ret);
		return;
	}

	st_thread_create(thread_fun, this, 0, 0);
	//st_thread_create(thread_fun_recv, this, 0, 0);
}


void cTestClient::msg_trans()
{
	int ret = ERROR_SUCCESS;
	sockaddr_in addr;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		ret = ERROR_SOCKET_CREATE;
		printf("create socket error. ret=%d", ret);
		return ;
	}

	
	m_stfd = st_netfd_open_socket(sock);
	if (m_stfd == NULL){
		ret = ERROR_ST_OPEN_SOCKET;
		printf("st_netfd_open_socket failed. ret=%d", ret);
		return ;
	}

	// connect to server.

	addr.sin_family = AF_INET;
	addr.sin_port = htons(DNSPORT);
	addr.sin_addr.s_addr = inet_addr(DNSIP);

	if (st_connect(m_stfd, (const struct sockaddr*)&addr, sizeof(sockaddr_in), ST_UTIME_NO_TIMEOUT) == -1)
	{
		ret = ERROR_ST_CONNECT;
		printf("connect to server error. ret=%d",  ret);
		return;
	}

	st_thread_create(thread_fun_trans, this, 0, 0);
    //st_thread_create(thread_fun_recv, this, 0, 0);
}

char * cTestClient::set_msg_confinfo()
{


	cJSON *root, *confinfo, *dir1;
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, JSON_CONFFER, m_strConfId.c_str());
	cJSON_AddStringToObject(root, JSON_SGREAMID, m_strStreamId.c_str());
	cJSON_AddStringToObject(root, JSON_REDISAPPNAME, "meiban");

	char *out = cJSON_Print(root);
	printf("%s \n", out);
	cJSON_Delete(root);
	return out;
}


void *thread_fun_trans(void *arg)
{
	cTestClient *pthis = (cTestClient *)arg;
	if (NULL == pthis)
	{
		return NULL;
	}

	char  m_chHead[NISMSGHEADSIZE];
	

	char *msg = pthis->set_msg_confinfo();
	int _senddatalen = strlen(msg);
	swap(&_senddatalen, sizeof(_senddatalen));

	byte _byte = SC_INVOKE_STORAGE_MSG;
	memcpy(m_chHead, &_byte, sizeof(byte));	//TYPE
	memcpy(m_chHead + NISMSGTYPELENG, &_senddatalen, sizeof(int));//len

	iovec iovs[2];
	iovs[0].iov_base = m_chHead;
	iovs[0].iov_len = (int)NISMSGHEADSIZE;
	iovs[1].iov_base = msg;
	iovs[1].iov_len = strlen(msg);
	ssize_t _nb_write = st_writev(pthis->m_stfd, iovs, 2, 0);

	free(msg);
   
    //重要测试如果消息内容为空 程序做异常处理
    /**
	while (true)
	{
		char  m_chHead[NISMSGHEADSIZE];
		byte _byte = SC_INVOKE_STORAGE_MSG;
		int _senddatalen = 0;
		memcpy(m_chHead, &_byte, sizeof(byte));	//TYPE
		memcpy(m_chHead + NISMSGTYPELENG, &_senddatalen, sizeof(int));//len

		int _nb_write = st_write(pthis->m_stfd, m_chHead, NISMSGHEADSIZE, 0);


		st_sleep(30);

	}**/
	
}
