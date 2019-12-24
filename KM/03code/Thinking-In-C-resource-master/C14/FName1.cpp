#include <iostream>
#include "../require.h"
#include <fstream>
#include <string>

using namespace std;

class FName1{
	ifstream file;
	string fileName;
	bool named;
	public:
	FName1(): named(false){}
	FName1(const string& fname):
		fileName(fname), file(fname.c_str())
	{
		assure(file, fileName);
		named = true;
	}

	string name() const {return fileName;}

	void name(const string& newName)
	{
		if(named)
			return;
		fileName = newName;
		named = true;
	}

	operator ifstream&()
	{
		return file;
	}
};
int main()
{
	FName1 file("FName1.cpp");
	cout<<file.name()<<endl;
	//Error:close() not a member;
	//file.close;
	return 0;
}
