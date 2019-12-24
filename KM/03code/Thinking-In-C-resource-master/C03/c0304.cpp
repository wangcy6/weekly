#include <iostream>

using namespace std;


int main()
{
char cInput;

while(1)
{
cout<<"----------MAIN MENU---------"<<endl;
cout<<"<-- L ----- left -->"<<endl;
cout<<"<-- R ----- right-->"<<endl;
cout<<"<-- Q ----- quit -->"<<endl;
cin>>cInput;
if(cInput == 'q')
{
cout<<"Quit."<<endl;
break;
}
switch(cInput)
{
case 'l':
	cout<<"<-- Left Menu -->"<<endl;
	cout<<"Select a or b"<<endl;
	cin>>cInput;	
	switch(cInput)
	{
		case 'a':
		cout<<"You chose a."<<endl;
		continue;
		break;
		case 'b':
		cout<<"You chose b."<<endl;
		continue;
		break;
		default:
		cout<<"You didn~t chose a or b."<<endl;
		continue;
		break;
	}	
	break;
case 'r':
	cout<<"<-- Right Menu -->"<<endl;
	cout<<"Select c or d"<<endl;
	cin>>cInput;	
	switch(cInput)
	{
		case 'c':
		cout<<"You chose c."<<endl;
		continue;
		break;
		case 'd':
		cout<<"You chose d."<<endl;
		continue;
		break;
		default:
		cout<<"You didn~t chose c or d."<<endl;
		continue;
		break;
	}
	break;
default:
	cout<<"You must chose l or r or q;"<<endl;
break;
}

}


cout<<"Quit Menu..."<<endl;
return 0;
}
