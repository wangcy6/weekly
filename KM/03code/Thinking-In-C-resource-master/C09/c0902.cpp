#include <fstream>

using namespace std;

/*
 *宏容易出现问题的地方就是直接替换所带来的优先级问题
 *以及自增自减带来．
 *不加括号带来的优先级问题
 */

#define	FLOOR(x,b)	x>=b?0:1

/*
 *增加括号来避免优先级的问题
 */
#define	FLOOR2(x,b)	((x)>=(b)?0:1)

/*
 *由于自增自减带来的问题
 */
#define	BAND(x)	(((x)>5 && (x)<10) ? (x) : 0)

int main(void)
{
	ofstream	out("macro.out");
	int	m = 0x00;
	if(FLOOR(m&0x0f, 0x07))
		out << "wrong marco" << endl;

	for (int i = 4; i < 11; i++) {
		int a = i;
		out << "a = "<< a << endl << '\t';
		//++a会根据不同的情况产生不同的情况，这并不是我们想要的结果．
		out << "BAND(++a) = " << BAND(++a) << endl;
		out << "\t a = " << a << endl;
	}
	return 0;
}
