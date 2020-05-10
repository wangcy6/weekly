#include <iostream>

using namespace std;

int main()
{

	int a[10];
	int* b = a;


	cout<<"sizeof a[10]"<<sizeof(a)<<endl;
	cout<<"sizeof b"<<sizeof(b)<<endl;
	cout<<"sizeof b"<<sizeof(*b)<<endl;
}
