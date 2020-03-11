#include "../require.h"
#include <iostream>
using namespace std;

#define IFOPEN(VAR, NAME)	\
	ifstream VAR(NAME);	\
	assure(VAR, NAME)

int main()
{
	IFOPEN(file, "../require.h");
	return 0;
}
