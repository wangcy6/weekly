#include <algorithm> // this header is required for std::sort to work
#include <iostream>
#include <vector>
using namespace std;


class  Big {
public:

  bool operator()(char a,char b) 
  { 
	return  a<b;
  }
};


class Cmp2
{
public:
    Cmp2()
    {
        cout<<" Cmp2()"<<endl;
    }
	bool operator()(int a,int b)
	{   
        cout<<"a="<<a<<"b="<<b<<endl;
		return a>b;
	}
};


class printElem
{
public:
	void operator () (int elem)
	{
		cout<<elem<<" ";
	}
};
int main()
{
    std::string s = "dacb";
    std::sort(s.begin(), s.end(),Big());
    std::cout << s << std::endl;

    vector<int> ver;
   
    for (int i = 0; i < 17; i++)
    {
        ver.push_back(i);
    }
    sort(ver.begin(),ver.end(),Cmp2());
    
    // Cmp2() ---Cmp2 b()
    //int a(19)
    /**
     ???????????????
    ??????????
    ????
    ?????????
     * **/
	for_each(ver.begin(),ver.end(),printElem ());

    return 0;
}