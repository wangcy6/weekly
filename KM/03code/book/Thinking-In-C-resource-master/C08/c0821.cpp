#include <cstring>
//使用无标记enum来获取一个编译期间常量
class ConstMemberAndEnumMember {
	enum {
		size = 100
	};
	const int memberi;
	//疑问? 指针能够使用memset()进行初始化，然而整型不行
	const int* array[size];
	public:
	ConstMemberAndEnumMember();
};

ConstMemberAndEnumMember::ConstMemberAndEnumMember()
	:memberi(0)
{
	memset(array, 0, sizeof(int*) * size);
}

int
main(void)
{
	ConstMemberAndEnumMember	c;
	return 0;
}
