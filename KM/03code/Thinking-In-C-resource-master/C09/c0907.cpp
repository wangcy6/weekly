#include <iostream>
#include <string.h>

/*
 *类里定义的成员函数会被自动扩展为内联函数，
 *故要满足条件，只需要在类里面定义成员函数即可
 */

class CInt {
	public:
		CInt()
		{
			memset(m_array, 0, size * sizeof(int));
		}
		void print() const
		{
			for (int i = 0; i < size; i++)
				std::cout<<m_array[i]<<std::endl;
		}
	private:
		enum {
			size = 10
		};
		int m_array[size];
};

int main(void)
{
	CInt m;
	m.print();

	return 0;
}
