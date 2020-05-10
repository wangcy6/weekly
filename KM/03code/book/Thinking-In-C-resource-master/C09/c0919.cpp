#include <iostream>
#include <string>
using namespace std;

#define	FIELD(type, name)				\
private:						\
	type name##_;					\
public:							\
	type get##name() const { return name##_;}	\
	void set##name(type val) {name##_ = val;}

class C {
	FIELD(int, foo);
	FIELD(float, bar);
	FIELD(string, baz);
};

//展开后的原型
/*
 *class A {
 *        private:
 *                int foo_;
 *        public:
 *                int getfoo() const
 *                {
 *                        return foo_;
 *                }
 *                void setfoo(int val)
 *                {
 *                        foo_ = val;
 *                }
 *};
 */

int main(void)
{
	C	c;
	c.setfoo(1);
	c.setbar(2.0);
	c.setbaz("three");
	cout << c.getfoo() << endl;
	cout << c.getbar() << endl;
	cout << c.getbaz() << endl;
	return 0;
}

