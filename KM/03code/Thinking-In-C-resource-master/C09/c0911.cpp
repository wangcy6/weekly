//内联函数在常见的工程中主要用来获取和设置成员变量的值
//又被称为访问器和修改器
//访问器通常在成员函数前加get字样来标志
//修改器通常在成员函数前加set字样来标志

#include <iostream>

enum Hue {
	red,
	blue,
	yellow
};

class color {
	Hue	m_h;
	public:
		color(Hue h)
		{
			m_h = h;
		}

		Hue getColor() const
		{
			return m_h;
		}

		void setColor(Hue h)	
		{
			m_h = h;
		}
};

int main(void)
{
	color	c(red);
	std::cout << c.getColor() << std::endl;
	c.setColor(blue);
	std::cout << c.getColor() << std::endl;
	return 0;
}
