#include <iostream>

using namespace std;

//标准的做法，在函数内将不会更改的值用常量引用来代替
void argument(float f)
{
	const float& ff = f;
	cout<<"const float &ff = "<<ff<<endl;
}

int main()
{
	float f1 = 2.2;
	argument(f1);
}
