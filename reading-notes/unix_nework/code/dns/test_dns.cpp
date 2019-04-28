
#include "dns_client.h"

#define  TESTMAXNUM 1000
int main(int argc, char** argv)
{


	if (st_set_eventsys(ST_EVENTSYS_ALT) == -1)
	{

		printf("st_set_eventsys use %s failed.\n", st_get_eventsys_name());
		return 1;
	}


	if (st_init() != 0)
	{
		printf("st_init failed.\n");
		return 1;
	}

	int _index = 0;
	for (; _index < TESTMAXNUM; _index++)
	{
		for (size_t i = 0; i < 1000; i++)
		{
			cTestClient *_test=new cTestClient;
			char _chConfer[25], _chstream[25];
			char str[25];
			 
			sprintf(_chConfer, "%d", _index);
			sprintf(_chstream, "%d", i);
			_test->join_confer(_chConfer, _chstream);
			_test->msg_trans();
			st_usleep(10);
		}
 
	
	}


	while (true)
	{
		//	printf("this is main loop \n");
		st_sleep(1);

	}


	return 1;
}
