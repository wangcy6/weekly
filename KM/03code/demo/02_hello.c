#include <stdio.h>
/**
分离编译
 将预处理之后的文件放至main.i
$ gcc -E main.c -o main.i
# 将编译后的结果放至main.s
$ gcc -S main.i -o main.s
 将目标文件存储为main.o
$ gcc -c main.s -o main.o
# 无参gcc/g++为链接目标文件
$ gcc main.o maxDefine.o
# 无参gcc/g++为链接目标文件
$ gcc main.o maxDefine.o
不出意外，会在当前目录下生成一个a.exe，这就是我们需要的可执行程序。

**/
int main(void){
	printf("helloworld!\n");
	return 0;
}
/**
GCC工具链编译和链接参数

# 预处理：#include和宏定义以及条件编译
$ cpp main.cc main.i
$ g++ -E main.cc -o main.i
# 编译成汇编代码
$ g++ -S main.i -o main.s
# 从汇编代码生成目标文件
$ g++ -c main.s -o main.o
# 直接从源文件生成目标文件
$ g++ -c main.cc
# 查看.o中的符号
$ nm main.o
# 将name mangling后的符号转换为原始符号
$ c++filt _Z3maxii

# 从源文件生成静态链接库
# 首先要生成目标文件
$ g++ -c slib.cc -o slib.o
# 然后使用ar来创建一个lib.a
$ ar rcs libslib.a slib.o
# 本地生成的libslib.a就是我们源文件编译出来的静态链接库
# 使用方法
# -L是指定链接库所在的目录(.是当前目录)，-l是gcc的链接方式会自动匹配到libxxx.a这样的链接库
# 比如-L. -lslib 就是链接当前目录下的libslib.a文件
$ g++ -o main.exe main.cc -L. -llib

# 从源文件编译动态链接库
# 生成目标文件时需要使用-fPIC/-fpic参数
# -fPIC参数声明链接库的代码段是可以共享的
$ gcc -c -fpic dylib.c -o dylib.o
# 使用-shared参数来生成动态链接库so
$ gcc -shared -fpic dylib.o -o dylib.so
# 生成DLL并生成导入库，链接时可以通过导入库lib来导入动态链接库中的符号
$ g++ dylib.cpp -shared -o dylib.dll -Wl,--out-implib,impdylib.lib

# 查看二进制依赖的符号
$ ldd main.exe

# 也可以通过nm来查看静态链接库和动态链接库以及可执行程序中的符号信息
$ nm slib.a
$ nm sylib.so
$ nm main.exe

# ldd可以查看可执行程序具有的外部链接信息
$ ldd main.exe
ntdll.dll => /c/Windows/SYSTEM32/ntdll.dll (0x7ffb24f80000)
KERNEL32.DLL => /c/Windows/System32/KERNEL32.DLL (0x7ffb22d40000)
KERNELBASE.dll => /c/Windows/System32/KERNELBASE.dll (0x7ffb218a0000)
msvcrt.dll => /c/Windows/System32/msvcrt.dll (0x7ffb22e50000)
目标文件中常见的符号类型:

A 该符号的值在今后的链接中将不再改变；
B 该符号放在BSS段中，通常是那些未初始化的全局变量；
D 该符号放在普通的数据段中，通常是那些已经初始化的全局变量；
T 该符号放在代码段中，通常是那些全局非静态函数；
U 该符号未定义过，需要自其他对象文件中链接进来；
W 未明确指定的弱链接符号；同链接的其他对象文件中有它的定义就用上，否则就用一个系统特别指定的默认值。
R符号位于只读数据区。比如C语言中的file scope的const int(C语言和C++不同)。
**/