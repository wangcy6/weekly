

### Item M19：理解临时对象的来源

Understand the origin of temporary objects.

### 1 什么是临时对象?



Q1:  temp 对c++而言是临时对象吗？

```c
template<class T>
void swap(T& object1, T& object2)
{
 T temp = object1;
 object1 = object2; 
 object2 = temp;
}
```

A1:  不是 

temp 根本不是临时变量，它只是一个函 
数的局部对象。 temp就是名字



无法获取地址的对象



> 在 C++ 中真正的临时对象是看不见的，它们不出现在你的源代码中。

建立一个没有命名 的非堆（non-heap）对象会产生临时对象





### 2 临时对象的来源（函数调用）



### 2.1【类型隐式自动转换】

Q2   看到下面代码 你想到了什么？

~~~c++
void uppercasify(string& str); 
~~~

-  函数传参方式：引用传递，避免对象的copy（真的避免copy了吗）

- 因为传递是地址，可以修改参数里面的值 （真的能修改地址吗？）
- 引用必须绑定对象，str不能为null，定义（真的能绑定吗？） 

这还用问吗？ 最基本的内容，已经考虑很全面了，还用问吗



A2: 是报错

~~~c++
void uppercasify(string& str);

int main()
{
	char subtleBookPlug[] = "Effective C++";//char
	uppercasify(subtleBookPlug); //string 
	return 0;
}
~~~



reference  定义规定了 不能指向右值（数字 10， 表达式 ‘1+2’，临时对象）

item19.cpp:15:28: error: invalid **initialization** of non-const reference of type ‘std::__cxx11::string& {aka std::__cxx11::basic_string<char>&}’ from an **rvalue** of type ‘std::__cxx11::string {aka std::__cxx11::basic_string<char>}’





类型不相同，重新构造一个临时对象（拷贝一次），必须是常量 引用 ，无法修改里面数值

类型不相同，重新构造一个临时对象（拷贝一次），必须是常量 引用 ，无法修改里面数值

类型不相同，重新构造一个临时对象（拷贝一次），必须是常量 引用 ，无法修改里面数值








- 什么是右值



![image.png](https://upload-images.jianshu.io/upload_images/1837968-af59c27f551b488d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 什么是右值引用  (rvalue reference)

![右值引用](https://upload-images.jianshu.io/upload_images/1837968-304c075871ce1c7e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

 

 ### 2.1 编程规范 禁止non-const-reference

[Google 开源项目风格指南](https://zh-google-styleguide.readthedocs.io/en/latest/contents/)

> > **规定 所有按引用传递的参数必须加上 `const**`

![1553303673088](https://i.ibb.co/njJGHTd/1553303673088.png)



### 2.1编程规范 不要使用 C 风格类型转换. 而应该使用 C++ 风格

![image.png](https://upload-images.jianshu.io/upload_images/1837968-a5a7ce62cf0671bc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![image.png](https://upload-images.jianshu.io/upload_images/1837968-9b5f9bac86a756a6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 2.2  函数 返回值和参数 （by value） 

   when passing objects by value or when passing to a reference-to-const parameter

###  2.3 对象定义



```c++
int a = int(100); *// 编译器可能生成临时对象*  Integer(100)

for_each(iv.begin(),iv.end(),print<int>());//stl print<int>()


```

4 引用

https://blog.csdn.net/sunnyyoona/article/details/43149569

http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2027.html

 关注



![微信图片_20190117214437](../../qrcode__860.jpg)