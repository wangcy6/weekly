#include<stdio.h>

#include<assert.h>

#include<string.h>

void *my_memcpy(void *dest, const void *src, size_t count)
{

	assert(dest!=NULL || src!=NULL);

	char *ptmpDest = (char *)dest;

	const char *ptmpSrc = (const char *)src;

	// 源地址在目的地址的右边，或者目的地址在源地址的右边，但没有交集
	// 直接拷贝
	if(ptmpSrc>= ptmpDest || ptmpDest >= ptmpSrc+count)

	{

		while(count--> 0)

		{

			*ptmpDest++ = *ptmpSrc++;

		}

	}else // 源地址在目的地址左边，并产生交集，形成内存覆盖，反着拷贝

	{

		while(count--> 0)

		{

		    *(ptmpDest + count) = *(ptmpSrc + count);

		}

	}

	return dest;

}


void *my_memcpy_err(void *dest, const void *src, size_t count)

{

assert(dest!=NULL || src!=NULL);

char *ptmpDest = (char *)dest;

const char *ptmpSrc = (const char *)src;

while(count--> 0)

{

*ptmpDest++ = *ptmpSrc++;

}

return dest;

}


void main()

{

	char str[20] = "abcdefghij";

	char str1[20];

	my_memcpy(str1,str,strlen(str)+1);// 正确拷贝

	printf("str1 = %s\n",str1);

	my_memcpy(str+2,str,4);// 错误，拷贝出现了内存覆盖

	printf("str = %s\n",str);

}