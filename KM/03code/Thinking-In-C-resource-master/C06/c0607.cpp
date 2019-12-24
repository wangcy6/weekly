#include <iostream>

using namespace std;

int main()
{
	double dArray[10] = {1.1};

	cout<<"sizeof dArray[10] = "<<sizeof(dArray)/sizeof(double)<<endl;

	for(int i = 0; i < sizeof(dArray) / sizeof(double); i++)
	{
		cout<<"dArray["<<i<<"] = "<<dArray[i]<<endl;
	}

	double dArray1[] = {1.1, 1.2, 1.3, 1.4, 1.6};
	for(int i = 0; i < sizeof(dArray1) / sizeof(*dArray1); i++)
	{
		cout<<"dArray1["<<i<<"] = "<<dArray1[i]<<endl;
	}

}
