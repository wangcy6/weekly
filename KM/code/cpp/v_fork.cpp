#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;




int main() {
        
	if (!vfork()) 
	{  
       cout<< "child "<<endl;
	   sleep(100);
	}else
	{
		cout<< "parent "<<endl;
	}

	return 0 ;
}