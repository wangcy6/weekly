#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;
int test_vector()
{
    {

        std::vector<std::string> strs;

        for (int i = 0; i < 100000000; i++)

        {

            strs.push_back("hello word.");
        }

        //std::vector<std::string>().swap(strs);

        printf("\n@@@@@@@@before call vector @@@@@@@@@@@\n");
        malloc_stats(); //在要执行内存检测的函数之后打印内存信息
    
    }

        printf("\n@@@@@@@@after call vector @@@@@@@@@@@\n");
        malloc_stats(); //在要执行内存检测的函数之后打印内存信息
}

int test_vector1()
{
    {

        std::vector<int* > strs;

        for (int i = 0; i < 100000000; i++)

        {

            strs.push_back(new int(i));
        }


        printf("\n@@@@@@@@after call func1 @@@@@@@@@@@\n");
        malloc_stats(); //在要执行内存检测的函数之后打印内存信息
    }

    //std::cout << "I'm out " << std::endl;
}
int main()
{


    test_vector();
 

    return 1;
}
