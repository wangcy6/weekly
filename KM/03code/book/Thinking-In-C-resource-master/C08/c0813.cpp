/*
 *函数参数用const修饰后，在函数内是不能修改i值的, 
 *如果函数不会修改传递的参数值的话，应该尽量使用
 *const进行修饰
 */
void passValueByConst(const int i)
{
	//错误
	//assignment of read-only parameter 'i';
	//i = 10;
}

int
main(void)
{
	return 0;
}
