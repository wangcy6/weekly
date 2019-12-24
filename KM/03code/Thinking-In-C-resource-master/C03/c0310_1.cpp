extern int fs;

void func()
{
fs = 100;
}

//编译器报错 在函数 func()中：
//fs 未定义的引用
//未发现c0310.cpp中的static int fs;
