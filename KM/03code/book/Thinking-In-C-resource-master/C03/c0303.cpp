#include <fstream>
#include <string>
#include <iostream>


using namespace std;
int main()
{
string input;
cout<<"Please input a word:";
while(cin >> input)
{
int Type = 0;
cout<<"Input size: "<<input.size()<<endl;
cout<<"Input length: "<<input.length()<<endl;

	if(input.length())
	{
		if(input[0] <= 'z' && input[0] >= 'a')
			Type = 2;
		if(input[0] <= 'Z' && input[0] >= 'A')
			Type = 1;
		if(input[0] == 'q')
			Type = 4;
	}



	switch (Type)
	{
	case 0:
		cout<<"Please input a word:"<<endl;
		break;
	case 1:
		cout<<"A~Z."<<endl;
		break;
	case 2: 
		cout<<"a~z."<<endl;
		break;

	case 3: cout<<"Funing words."<<endl;
		break;

	case 4:
		cout<<"Quit!"<<endl;
		break;
	default:
		break;
	}

	if(input[0] == 'q')
	break;
}
	return 0;
}


