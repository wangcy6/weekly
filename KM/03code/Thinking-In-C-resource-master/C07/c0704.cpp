#include <iostream>

class defaultargument{

	public:

		//void argument();
		//void argument(int i);
		//void argument(int i, int j);
		//void argument(int i, int j, int k);
		void argument(int i = 0, int j = 0, int k = 0);

};


void defaultargument::argument(int i, int j, int k)
{
	std::cout<<"i = "<<i<<" j = "<<j<<" k = "<<k<<std::endl;
}


int main()
{
	defaultargument d;

	d.argument();
	d.argument(1);
	d.argument(1, 2);
	d.argument(1, 2, 3);

}
