#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Text{
	string m_page;
	int m_lineNum;

	public:

	Text();
	Text(string filename);
	~Text();

	string* contents();
};

Text::Text()
{
	m_lineNum  = 0;
}

Text::Text(string filename)
{

	//m_page = new string;
	ifstream file(filename.c_str());
	string line;
	while(getline(file, line))
	{
		m_page += line;
		m_page += '\n';
	}
}

string* Text::contents()
{
	if(!m_page.empty())
	  return &m_page;
		  return 0;
}


Text::~Text()
{
}

int main()
{
	string fname;
	cout<<"please input filename:"<<endl;
	cin>>fname;
	Text t(fname);
	cout<<*t.contents()<<endl;
}

