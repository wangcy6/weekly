#include <fstream>

using namespace std;

ofstream test2("test2.out");

static int	local;
//extern int	a;
extern int	global;

void	g()
{
	local = 2;
	global = 2;
	test2 << local << endl;
	test2 << global << endl;
}
