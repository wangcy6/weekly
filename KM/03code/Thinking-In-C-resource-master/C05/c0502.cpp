#include <iostream>
#include <string>

using namespace std;

struct Lib
{
	string m_a;
	string m_b;
	string m_c;
	string s[3];
};

struct Libc
{
	private:
		string m_a;
		string m_b;
		string m_c;
	public:
		void seta(string s)
		{
			m_a = s;
		}
		void setb(string s)
		{
			m_b = s;
		}
		void setc(string s)
		{
			m_c = s;
		}

		string geta()
		{
			return m_a;
		}
		string getb()
		{
			return m_b;
		}
		string getc()
		{
			return m_c;
		}
};
int main()
{
	Lib x;
	x.m_a = "Hello!";
	x.m_b = "MyLady";
	x.m_c = "Girl Lsy";

	// no problem with this Change. Author ... why?
	x.s[0] = "what? ";
	x.s[1] = "wrong ";
	x.s[2] = "with you?";
	cout<< x.m_a << x.m_b << x.m_c <<endl;
	cout<< x.s[0] << x.s[1]<< x.s[2] <<endl;

	Libc y;
	y.seta("good bye!");
	y.setb("my girl");
	y.setc("i wish see you again!");
	cout<<y.geta()<<y.getb()<<y.getc()<<endl;

}
