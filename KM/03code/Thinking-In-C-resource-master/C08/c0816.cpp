void t(int*) {}

void u(const int* cip) {
	// assignment of read-only location ‘* cip’
	//*cip = 2;
	int i = *cip;
	// invalid conversion from ‘const int*’ to ‘int*’
	// int* ip2 = cip;
}


const char* v() {
	return "result of function v()";
}

const int* const w() {
	static int i;
	return &i;
}

int main()
{
	int x = 0;
	int* ip = &x;
	const int* cip = &x;
	t(ip);
	
	// 不能将一个常量指针赋值给一个非常量指针
	// invalid conversion from ‘const int*’ to ‘int*’ 
	// t(cip);
	u(ip);
	u(cip);
	// invalid conversion from ‘const char*’ to ‘char*’ 
	// 不能将一个常量指针赋值给一个非常量指针
	// char* cp = v();
	const char* ccp = v();
	//invalid conversion from ‘const int*’ to ‘int*’
	//int* ip2 = w();
	const int* const ccip = w();
	//不修改指针这是允许的
	const int* cip2 = w();
	//返回一个常量指针，不能通过指针修改这个值
	//assignment of read-only location ‘* w()’
	//*w() = 1;
}
