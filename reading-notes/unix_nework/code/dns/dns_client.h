#ifndef DNSCLIENTH
#define DNSCLIENTH

#include <string.h>
#include <string>
using namespace std;

#include "st.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef int32
#define  int32 int 
#endif

typedef unsigned char byte;

#if !defined(int8)
typedef char int8;
#endif

class cTestClient
{
public:

	void join_confer(string stConferId,string stStreamId);
	void msg_trans();//测试消息透传
	char * set_msg_confinfo();
	string m_strConfId;
	string m_strStreamId;
	st_netfd_t m_stfd;
protected:
private:
};

#endif
