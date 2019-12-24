#include <iostream>
#include <string>

using namespace std;


class Message{

	string m_s;

	public:

	Message(const string& s = "MSG");
	~Message();
	void print();
	void print(const string &outs);
};


Message::Message(const string& s)
{
	m_s = s;
}


void Message::print()
{
	cout<<m_s<<endl;
}
void Message::print(const string &outs)
{
	cout<<m_s<<outs<<endl;
}

Message::~Message()
{}
int main()
{

	Message m("goodbye");
	m.print();
	m.print("girl");

}
