#include <iostream>
using namespace std;
class L{
	long l;
	public:
	L(long ll): l(ll)
	{}

	friend ostream&
		operator<<(ostream& os, const L& l);

	friend istream&
		operator>>(istream& is, L& l);
};

ostream&
operator<<(ostream& os, const L& l)
{
	os<<l.l;
	return os;
}

istream&
operator>>(istream& is, L& l)
{	
	is>>l.l;	
	return is;
}

int main()
{
	long x = 100;
	L l1(x);
	cout<<l1<<endl;
	cin>>l1;
	cout<<l1<<endl;
}
