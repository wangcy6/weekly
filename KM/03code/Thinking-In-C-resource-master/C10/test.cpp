#include <fstream>

using namespace std;

ofstream test1("test1.out");

static int	local;

int	global;
void	g();

int	main()
{
	local = 1;
	global = 1;
	test1 <<"before g():" <<endl;
	test1 << local << endl;
	test1 << global << endl;

	g();

	test1 <<"after	g():" <<endl;
	test1 << local << endl;
	test1 << global << endl;
}
