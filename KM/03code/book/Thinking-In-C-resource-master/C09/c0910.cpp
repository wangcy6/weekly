//内联函数在常见的工程中主要用来获取和设置成员变量的值
//又被称为访问器和修改器

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

		Hue get() const
		{
			return m_h;
		}

		void set(Hue h)	
		{
			m_h = h;
		}
};

int main(void)
{
	color	c(red);
	std::cout << c.get() << std::endl;
	c.set(blue);
	std::cout << c.get() << std::endl;
	return 0;
}
