



# 版本

gcc 使用 4.8.4 版本，

STL源码 在 Linux 系统的位置是：/usr/include/c++/4.8.4/bits (79个文件)



参考 ：[STL源码分析](https://www.kancloud.cn/digest/mystl/192549)



# 目录：

[小王职场记 谈谈你的STL理解（1）](https://mp.weixin.qq.com/s/yOyLsW1PZfLZJqXeWR0Y6w)





STL读后感：



看完STL 你会发一切解对象



这个对象 STL主要依赖**封装，继承**和没用使用虚函数





- 看完STL 你会发一切解对象，

STL的实现 是从c语言脱离开来另外一种思维方式，
不仅仅隐藏指针，引用这些复杂概念
还通过类的继承完成对接口的封装。和以前上学概念不一样！！！。
难怪c++创始人“夫妇”给新手建议 

> 多使用框架， 多使用框架， 多使用框架，重要事情说三遍

可以当作java c#一样来使用了，尤其c++11出现更是如此


为什么c++写出STL 核心一点
利用c++特点之一：支持 重载，
具体来说就是运算符的重载。
那个运算符？

>  重载函数调用运算符()    ，实现对类的重载，这个方式成为仿函数，或者函数对象    
>
>  重载函数调用运算符()    ，实现对类的重载，这个方式成为仿函数，或者函数对象    
>
>  重载函数调用运算符()    ，实现对类的重载，这个方式成为仿函数，或者函数对象    
>
> 重要事情说三遍



- 这个对象 STL主要依赖**封装，继承**和没用使用虚函数（不使用virtual还是其他方式实现多态？）






## 1. 编译期多态优点（函数重载和模板）

1. 它带来了泛型编程的概念，使得C++拥有泛型编程与STL这样的强大武器。
2. 在编译器完成多态，提高运行期效率。
3. 具有很强的适配性与松耦合性，对于特殊类型可由模板偏特化、全特化来处理。

静态多态中，是必须实现统一的接口才能够达到功能

```c++
代码：function_virutal.cpp
//静态多态：静态多态其实就是泛型，在静态编译的时候实现多态。
template <typename T>
void AnimalShot(T & anim)
{
    anim.shout(); //shout()是啥东东这里不清楚,必须在编译时候决定
} //函数重载可以在编译时候就确定我们应该调用哪个函数，所谓我们称之为编译期的多态。

//动态多态：动态多态就是在程序运行过程中，拿着父类的指针去访问子类的对象。
void AnimalShot(Animal & anim)
{
    anim.shout(); // shout是Animal类的接口 //运行期多态
}

```

对于anim来说，必须支持哪一种接口，要由模板参数执行于anim身上的操作来决定，

在上面这个例子中，T必须支持shout()操作，**那么shout就是T的一个隐式接口**。

## 编译期多态缺点

1. 程序可读性降低，代码调试带来困难。
2. 无法实现模板的分离编译，当工程很大时，编译时间不可小觑。
3. 无法处理异质对象集合。

## 运行期多态优点（virtual）

1. OO设计中重要的特性，对客观世界直觉认识。
2. 能够处理同一个继承体系下的异质类集合。



## 运行期多态缺点

1. 运行期间进行虚函数绑定，提高了程序运行开销。
2. 庞大的类继承层次，对接口的修改易影响类继承层次。
3. 由于虚函数在运行期在确定，**所以编译器无法对虚函数进行优化**。
4. 虚表指针增大了对象体积，类也多了一张虚函数表，当然，这是理所应当值得付出的资源消耗，列为缺点有点勉强。



总结：

![1548314223531](C:\Users\wangchuanyi\AppData\Roaming\Typora\typora-user-images\1548314223531.png)



运行期多态是通过 继承基类, 确保双方有享有共同的接口。有语法上规定



静态多态 通过是提前约定好，双方必须实现这样接口,



几个问题：

​     

# 为什么STL容器没有虚拟析构函数【QA】

# 内联函数可以是虚函数吗[QA]

>Note: It's imperative that the function's definition (the part between the {...}) be placed in a header file, unless the function is used only in a single .cpp file. In particular, if you put the inline function's definition into a .cpp file and you call it from some other .cpp file, you'll get an "unresolved external" error from the linker.

1）如果在头文件中定义非inline函数，一旦该头文件被多个文件包含，就会造成该非inline函数的“重定义”，因而，不建议将非inline函数的定义放在头文件中，但是非inline函数的声明是可以放在头文件中的。

.头文件中有些声明但没有定义的函数，是在库中定义的，当然这些库是不包含在
      内核代码中的。比如unistd.h中的系统调用都是在库里面封装的。再如sys/stat.h
      中chmod函数其实在unistd.h中也有声明，我







- 内联函数是弱符号

```c
[root@VM-10-112-178-190 c++]# nm a.out |c++filt |grep -E "test|inlineFunc"
0000000000400977 t _GLOBAL__sub_I__Z4testv
000000000040098c W inlineFunc(int)
00000000004008c0 T test()
```



# 功能划分

STL中包括四大部分：容器、迭代器、算法、函数对象

STL的一个重要特点是数据结构和算法的分离



1. 算法模块

algorithm

algo.h

 stl_algo.h 

stl_numeric.h

2. 函数对象模块

stl_function.h

3. 迭代器模块

iterator

stl_iterator.h



# 函数对象模块

- 定义：

  重载了“operaotr()”操作符的普通类对象 ，

  这个对象具备了具有函数行为

  > 调用类(), 相当于调用类.成员函数()

```c++

 // 大于
template <class _Tp>
struct greater : public binary_function<_Tp,_Tp,bool> 
{
  bool operator()(const _Tp& __x, const _Tp& __y) const { return __x > __y; }
};
//这个函数对象没有数据成员、没有虚函数、没有显示声明的构造函数和析构函数，且对operator()的实现是内联的。用作STL比较器的函数对象一般都很小

greater<int> greaterobj;
greaterobj(3, 5)//等价于greaterobj.operator(3,5) 效果等价于函数调用function(3, 5); 

    
```



- 函数对象作用：1 可调用的表达式

![func_objets](https://github.com/wangcy6/reading_code_note/blob/master/SGI-STL/images/func_object_call.PNG)

> 使用函数对象作为比较器还有一个额外的好处，就是比较操作将被内联处理，

> 而使用函数指针则不允许内联
>
> 《C++Primer Plus》第16章“函数对象”这一节，发现C++中还有比函数指针更高层次的抽象——functor，中文名为“仿函数”“类函数”或“函数对象”。它的实际就是“重载了'operator()'的类”，并兼容函数指针



- 函数对象作用： 2以函数对象的临时对象履行函数功能

```c++
cout << greater<int>()(3, 5) << endl;
```

- 函数对象作用  ： lambda表达式原理



Lambda表达式来源于函数式编程，说白就了就是在**使用的地方定义函数**，有的语言叫“闭包”

C++引入Lambda的最主要原因就是

1）可以定义匿名函数，

2）编译器会把其转成**函数对象**

**编译器会把一个lambda表达式生成一个匿名类的匿名对象，并在类中重载函数调用运算符**

![func_objets](https://github.com/wangcy6/reading_code_note/blob/master/SGI-STL/images/func_objets.PNG)

- 函数对象作用:函数适配器【待学习】

![](https://github.com/steveLauwh/SGI-STL/raw/master/The%20Annotated%20STL%20Sources%20V3.3/Other/functionobject.png)

塔山

- https://www.youtube.com/watch?v=482weZjwVHY



 # 算法模块



## std:sort 

```c++
template <class _RandomAccessIter>
inline void sort(_RandomAccessIter __first, _RandomAccessIter __last) {
  __STL_REQUIRES(_RandomAccessIter, _Mutable_RandomAccessIterator);
  __STL_REQUIRES(typename iterator_traits<_RandomAccessIter>::value_type,
                 _LessThanComparable);
  if (__first != __last) { //只有一个记录 ，不需要排序
    __introsort_loop(__first, __last,
                     __VALUE_TYPE(__first),
                     __lg(__last - __first) * 2);//快速排序，整体有序
    __final_insertion_sort(__first, __last); //剩下未排序的数据，直接插入排序
    
  }
}
template <class _RandomAccessIter, class _Tp, class _Size>
void __introsort_loop(_RandomAccessIter __first,
                      _RandomAccessIter __last, _Tp*,
                      _Size __depth_limit)
{
  while (__last - __first > __stl_threshold) { ///长度大于16才进行一次快排分割
    if (__depth_limit == 0) 
    {
      partial_sort(__first, __last, __last); //堆排序
      return;
    }
    --__depth_limit;
    _RandomAccessIter __cut =
      __unguarded_partition(__first, __last,
                            _Tp(__median(*__first,
                                         *(__first + (__last - __first)/2),
                                         *(__last - 1))));////找三个位置的中位数作为快排依据
    __introsort_loop(__cut, __last, (_Tp*) 0, __depth_limit); //排后一部分
    __last = __cut; //排前一部分
  }
}
```



### sort描述

维基百科 [内省排序](https://zh.wikipedia.org/wiki/%E5%86%85%E7%9C%81%E6%8E%92%E5%BA%8F)

**内省排序**（英语：Introsort）是由David Musser在1997年设计的[排序算法](https://zh.wikipedia.org/wiki/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95)。

- 这个排序算法首先从[快速排序](https://zh.wikipedia.org/wiki/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F)开始，当递归深度超过一定深度（深度为排序元素数量的对数值）后转为[堆排序](https://zh.wikipedia.org/wiki/%E5%A0%86%E6%8E%92%E5%BA%8F)。采用这个方法，

内省排序既能在常规数据集上实现快速排序的高性能，又能在最坏情况下仍保持{\displaystyle O(nlogn)}![O(nlogn)](https://wikimedia.org/api/rest_v1/media/math/render/svg/e2f45af346af19e39ee9f58975dbab9740f475da)的[时间复杂度](https://zh.wikipedia.org/wiki/%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6)。由于这两种算法都属于[比较排序](https://zh.wikipedia.org/wiki/%E6%AF%94%E8%BE%83%E6%8E%92%E5%BA%8F)算法，所以内省排序也是一个比较排序算法。

- 2000年6月，[SGI](https://zh.wikipedia.org/wiki/%E7%A1%85%E8%B0%B7%E5%9B%BE%E5%BD%A2%E5%85%AC%E5%8F%B8)的C++[标准模板库](https://zh.wikipedia.org/wiki/%E6%A0%87%E5%87%86%E6%A8%A1%E6%9D%BF%E5%BA%93)的[stl_algo.h](http://www.sgi.com/tech/stl/stl_algo.h)中的不稳定排序算法采用了Musser的内省排序算法。在此实现中，切换到插入排序的数据量阈值为16个。



主要因素：

if 递归深度 多大 then 改为堆排序 有不稳定排序改成稳定排序

if  数据少于16个 then 改为 插入排序，降低递归堆栈消耗





，因此Musser在1996年发表了一遍论文，提出了[Introspective Sorting](http://www.cs.rpi.edu/~musser/gp/index_1.html)(内省式排序)，这里可以找到[PDF版本](http://www.researchgate.net/profile/David_Musser/publication/2476873_Introspective_Sorting_and_Selection_Algorithms/file/3deec518194fb4a32f.pdf)。它是一种混合式的排序算法，集成了前面提到的三种算法各自的优点：

- 在数据量很大时采用正常的快速排序，此时效率为O(logN)。

- 一旦分段后的数据量小于某个阈值，就改用插入排序，因为此时这个分段是基本有序的，这时效率可达O(N)。

- 在递归过程中，如果递归层次过深，分割行为有恶化倾向时，它能够自动侦测出来，使用堆排序来处理，在此情况下，使其效率维持在堆排序的O(N logN)，但这又比一开始使用堆排序好。



  ### 复杂度

![1548126290890 (1)](../../images/1548126290890 (1).png)

参考

1. http://feihu.me/blog/2014/sgi-std-sort/
2. 动画：https://www.youtube.com/watch?v=67ta5WTjjUo
3. https://paste.ubuntu.com/p/Y8k2DKCTX5/
4. http://blog.sina.com.cn/s/blog_79d599dc01012m7l.html

## std::for_each

```c++
// for_each.  Apply a function to every element of a range.
template <class _InputIter, class _Function>
_Function for_each(_InputIter __first, _InputIter __last, _Function __f) {
  for ( ; __first != __last; ++__first)
    __f(*__first);// 调用类_f(),相当于调用类._f.opeartor() 函数
  return __f;//临时对象
}


//Lambda 
int total = 0;
std::for_each(myvector.begin(), myvector.end(), [&total](int x) { total += x; });
std::cout <<"Lambda: "<< total<<endl;

//函数对象
struct Sum
{
    Sum(): sum{0} { }
    void operator()(int x) { total += x; } //只有一个函数
    int total;
};
// calls Sum::operator() for each number
Sum s = std::for_each(myvector.begin(), myvector.end(), Sum());
std::cout << "sum: " << s.sum <<endl;
```



# 容器部分

# 适配器模块

#### 说明：

测试代码：stl_adapter.cpp

注释代码：



### 几个问题

如何理解下面这句话【我反正是不理解】

![1548213025843](C:\Users\wangchuanyi\AppData\Roaming\Typora\typora-user-images\1548213025843.png)



![1548213506553](C:\Users\wangchuanyi\AppData\Roaming\Typora\typora-user-images\1548213506553.png)	





### 容器适配器类型

- Insert Iterator   替换的容器的插入接口  ，高度抽象出来的（vecotr，stack）

```c++
template <class _Container>
class back_insert_iterator 
{
protected:
  _Container* container;


  explicit back_insert_iterator(_Container& __x) : container(&__x) {} 
/**
explicit:禁止隐式调用类内的单参数构造函数
当传入参数是 容器时候，只能这样构造
 从上面的解释可以看到， explicit关键字的作用：禁止隐式调用类内的单参数构造函数，这主要包括如下三层意思：
         （1）该关键字只能用来修饰类内部的构造函数
         （2）禁止隐式调用拷贝构造函数
         （3）禁止类对象之间的隐式转换
**/

  back_insert_iterator<_Container>&
  operator=(const typename _Container::value_type& __value) 
  { 
    container->push_back(__value);
    return *this; //对迭代器适配器的赋值变成了对容器的插入操作。
  }
};
```

![1548331051824](C:\Users\wangchuanyi\AppData\Roaming\Typora\typora-user-images\1548331051824.png)

![1548331065491](C:\Users\wangchuanyi\AppData\Roaming\Typora\typora-user-images\1548331065491.png)

- class front_insert_iterator

- class reverse_iterator  stl_iterator.h::293





- ### 函数适配器(很重要)

####  第一个问题：理解typedef含义

- struct unary_function

定义一个类，然后 里面有几个个成员，没有看出里面的有什么作用呀？



> 提前定义好成员变量，这样才能实现类型多态的调用
>
> binary_function is a base class for creating function objects with two arguments.

```c
// 一元函数的参数类型和返回值类型
template <class _Arg, class _Result>
//stl_function.h::38
struct unary_function {

  typedef _Arg argument_type; //类的成员函数 是变量的类型

  typedef _Result result_type; //类的成员函数 是变量的类型
};
// 二元函数的第一个参数类型和第二个参数类型，以及返回值类型
template <class _Arg1, class _Arg2, class _Result>
struct binary_function {
  typedef _Arg1 first_argument_type;
  typedef _Arg2 second_argument_type;
  typedef _Result result_type;
};  

std::unary_function<int,bool>

```



# 

**### 应用于仿函数，function adapter**

\> 对返回值进行逻辑否定：not1, not2

\> 对参数进行绑定：bind1st, bind2nd

\> 用于函数合成：compose1, compose2

\> 用于函数指针：ptr_fun

\> 用于成员函数指针：mem_fun, mem_fun_ref



| 成员类型      | 定义                   | 注释                     |
| ------------- | ---------------------- | ------------------------ |
| argument_type | 第一个模板参数 (Arg)   | `()重载函数的参数类型`   |
| result_type   | 第二个模板参数(Result) | `()重载函数的返回值类型` |

| 成员类型             | 定义                   | 注释                         |
| -------------------- | ---------------------- | ---------------------------- |
| first_argument_type  | 第一个模板参数(Arg1)   | `()重载函数的第一个参数类型` |
| second_argument_type | 第一个模板参数 (Arg2)  | `()重载函数的第二个参数类型` |
| return_type          | 第一个模板参数(Result) | `()重载函数的返回值类型`     |

- class binder2nd



```c++
//第一次分析：class binder2nd 声明一个类 这个语法你肯定明白
//第二次分析：class binder2nd:public unary_function 
//binder2nd继承来了模板类unary_function，typename _Operation::first_argument_type 是参数类型 
//vector<int> int就是类型  vector就是模板类  这个对比应该明白  
//第三次分析：  _<typename _Operation::first_argument_type
//请问 class  _Operation是任意类， typename first_argument_type任意类型之间关系是什么？
//但是在stl语法中 typename T 代码是 成员变量的类型（int ，char*）   class T 代表类的类型
//vector:base, a.m_i 
//T::T
//第四次分析：
// _Operation::second_argument_type 你怎么确定  类_Operation里面一定有成员变量 second_argument_type
// 
//binary_function is a base class for creating function objects with two arguments.
//stl 规定 函数对象必须这个类， 这样函数对象之间（虽然不是继承，但是可以调用），但是相互使用了（佩服呀，因此函数对象适配器，可以适配任何同类对象）
// 这就是编译期间的多态

////第五次分析：重载 返回值 operator()(参数)
//typename _Operation::result_type operator()(const typename _Operation::first_argument_type& __x) const 
 //返回的结果是不是具体类型 是模板  result_type是unary_function实现的
 //op(__x, value) 

////第6次分析：
//binder2nd::unary_function
//_Operation::binary_function
//这是一次更强大的适配
//这个是第六次分析   关键点 
//value 是 binder2nd是创建时候调用构造时候设置的，
//_x 调用函数关系()设置的
//A a(10)  构造(a) 
// a(20)   函数调用(a,b)
/**
此函数适配器必须要继承自unary_function对象，满足可配接性。
解释一下可配接性。less_equal类继承自binary_function，便有了内部嵌套类型second_argument_type，
而这个类型正好需要用在binder2nd中，以保存（绑定）某个参数。这样，less_equal就变为了可配接的。
纵观整个适配器系统，基本上都是把某个对象或指向对象的指针封装在一个适配器类中，对适配器的操作最终都会传递到对所包含对象的操作
**/

template <class _Operation>
class binder2nd
  : public unary_function<typename _Operation::first_argument_type,
                          typename _Operation::result_type> {
protected:
  _Operation op;//第一个成员变量是：是函数对象
  typename _Operation::second_argument_type value;//第二个成员变量是：函数对象的参数
public:
 //构造函数 函数对象的创建
  binder2nd(const _Operation& __x,  // 仿函数
            const typename _Operation::second_argument_type& __y) 
      : op(__x), value(__y) // 绑定的第二个数
  {

  }
  typename _Operation::result_type //返回的结果是不是具体类型 是模板  result_type是unary_function实现的

 
  typename _Operation::result_type operator()(const typename _Operation::first_argument_type& __x) const 
  {
     return op(__x, value);  
     //这个是第六次分析   关键点 
     //value 是 binder2nd是创建时候调用构造时候设置的，
     //_x 调用函数关系()设置的
     //A a(10)  构造(a) 
     // a(20)   函数调用(a,b)
    
  }
};
```



- 测试程序；

```c++
std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//计算容器中小于等于3的元素个数
cout << count_if(vec.begin(), vec.end(), bind2nd(less_equal<int>(), 3));
int count  = std::count_if(vec.begin(), vec.end(), [](int x) {return x >  3;})
```

![1548330412420](C:\Users\wangchuanyi\AppData\Roaming\Typora\typora-user-images\1548330412420.png)



![1548330412420](https://github.com/wangcy6/reading_code_note/blob/master/SGI-STL/images/1548330412420.png)





# lambda表达式的本质(函数对象)

**lambda表达式就是一个函数对象**。

当编写了一个lambda表达式的时候，编译器将该表达式翻译成一**个未命名类的未命名对象**

​	

```c++
int num = 100;
auto f = [num](){return num; };//等价于F

class F
{
public:
    F(int n) :num(n){}
    int operator()() const { return num; }
private:
    int num;
};
ambda表达式产生的类，不含有默认构造函数、赋值运算符和默认析构函数，其他成员由需要捕获的类型确定。
```

塔山：

https://www.youtube.com/watch?v=a-MXdU-SWp0

https://stackoverflow.com/questions/22386882/why-have-unary-function-binary-function-been-removed-from-c11

https://zhuanlan.zhihu.com/p/35923250

https://stackoverflow.com/questions/30873206/header-file-included-only-once-in-entire-program

https://www.zhihu.com/question/40793741/answer/88412179

https://jiadebin.github.io/2017/04/03/%E5%A4%B4%E6%96%87%E4%BB%B6%E4%B8%AD%E5%AE%9A%E4%B9%89%E5%87%BD%E6%95%B0%E5%BC%95%E5%8F%91%E7%9A%84multiple-definition/



https://zybuluo.com/uuprince/note/81709

