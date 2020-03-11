#include "../require.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class FName2 :public ifstream{
	string fileName;
	bool named;
	public:
	FName2():
		named(false)
	{}

	FName2(const string& fname):
	ifstream(fname.c_str()), fileName(fname)
	{
		assure(*this, fileName);
		named = true;
	}
	
	string name() const
	{
		return fileName;
	}

	void name(const string& newName)
	{
		if(named)
			return;
		fileName = newName;
		named = true;
	}
};

int main()
{
	FName2 file("FName2.cpp");
	assure(file, "FName2.cpp");
	cout<<file.name()<<endl;
	string s;
	getline(file, s);
	file.seekg(-200, ios::end);
	file.close();

}
