#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
//argv[0]为程序名
//for(int i = 0 ; i < argc; i++)
//	cout<<argv[i]<<endl;
for(int i = 1; i < argc; i++)
	cout<<atoi(argv[i])<<endl;
for(int i = 1; i < argc; i++)
	cout<<atol(argv[i])<<endl;
for(int i = 1; i < argc; i++)
	cout<<atof(argv[i])<<endl;


return 0;
}
