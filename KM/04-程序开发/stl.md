# SGI-STL V3.3 源代码的学习



* SGI-STL V3.3(源代码)
  + STL 标准头文件(无扩展名)，例如 `vector`，`deque`，`list`...
  + C++ Standard 定案前，HP 规范的 STL 头文件(扩展名 .h)
  + SGI STL 内部私用文件(SGI STL 真正实现于此)

* The Annotated STL Sources V3.3(学习源代码的注释)
  + [容器 (container)](https://github.com/steveLauwh/SGI-STL/tree/master/The%20Annotated%20STL%20Sources%20V3.3/container) ：序列式容器 (sequence container) 和 关联式容器 (associattive container)
  + [算法 (algorithm)](https://github.com/steveLauwh/SGI-STL/tree/master/The%20Annotated%20STL%20Sources%20V3.3/algorithm)
  + [迭代器 (iterator)](https://github.com/steveLauwh/SGI-STL/tree/master/The%20Annotated%20STL%20Sources%20V3.3/iterator)
  + [仿函数或函数对象 (functor / function object)](https://github.com/steveLauwh/SGI-STL/tree/master/The%20Annotated%20STL%20Sources%20V3.3/functor-function%20object)
  + [配接器(adapter)](https://github.com/steveLauwh/SGI-STL/tree/master/The%20Annotated%20STL%20Sources%20V3.3/adapter)
  + [配置器(allocator)](https://github.com/steveLauwh/SGI-STL/tree/master/The%20Annotated%20STL%20Sources%20V3.3/allocator)

* SGI-STL Test(代码测试)

  + [Code Test](https://github.com/steveLauwh/SGI-STL/tree/master/SGI-STL%20Test)

## GCC 编译器

SGI STL 被归纳到 GNU C++ 标准程序库中，例如 gcc 使用 4.8.4 版本，STL源码 在 Linux 系统的位置是：/usr/include/c++/4.8.4/bits。

 STL另一个重要特性是它不是面向对象的。为了具有足够通用性，STL主要依赖于模板而不是封装，继承和虚函数（多态性）——OOP的三个要素 

提示

确保在编译使用了STL的程序中至少要使用-O优化来保证内联扩展。

STL提供了大量的模板类和函数，可以在OOP和常规编程中使用



 注意，模板只是实例化的模式，函数模板根本不是函数，类模板也根本不是类 







## 参考资料

* <<STL 源代码剖析>> 侯捷
*  http://net.pku.edu.cn/~yhf/UsingSTL.htm 

--------------------------------------------------------------------------

# stl 特点





----------------------------------------------------------------------



QA

为什么priortiy_queue 适配类型 不用list？ 因为list 访问是o(n)
为什么priortiy_queue 适配类型 必杀技红黑树？是大材小用



Adapter Design Pattern（相同的放在一起）
https://sourcemaking.com/design_patterns/adapter



----------------------------------------------------------------------
目录：

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



​     

# 为什么STL容器没有虚拟析构函数【QA】

# 内联函数可以是虚函数吗[QA]

>Note: It's imperative that the function's definition (the part between the {...}) be placed in a header file, unless the function is used only in a single .cpp file. In particular, if you put the inline function's definition into a .cpp file and you call it from some other .cpp file, you'll get an "unresolved external" error from the linker.

1）如果在头文件中定义非inline函数，一旦该头文件被多个文件包含，就会造成该非inline函数的“重定义”，因而，不建议将非inline函数的定义放在头文件中，但是非inline函数的声明是可以放在头文件中的。

.头文件中有些声明但没有定义的函数，是在库中定义的，当然这些库是不包含在
      内核代码中的。比如unistd.h中的系统调用都是在库里面封装的。再如sys/stat.h
      中chmod函数其实在unistd.h中也有声明，我





![image.png](https://i.loli.net/2019/11/25/tIArW36vhuSp2Fl.png)

- 内联函数是弱符号

```c
[root@VM-10-112-178-190 c++]# nm a.out |c++filt |grep -E "test|inlineFunc"
0000000000400977 t _GLOBAL__sub_I__Z4testv
000000000040098c W inlineFunc(int)
00000000004008c0 T test()
```





# 1 分配器（ stl_alloc.h ）

 [栗子](https://gcc.godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAOgAYB2ACwBOAKyCATAGZhsucIAcpAFZdSrZrVDIApBIBCe/aQDOqAK7FkHAOR6peWslbmsAah1SAwgFtMPkgBPT2wdXgARMIBBe0dnV0wPbwJAgAdMAH0CYmZCExCwyN4YiOjaZj8TVOZrN1opADYGwQ9%2BQ1Lity63An9UjV6kr2dmExM3ABUCjqjutxGxtzZWVBYiYjcQN1TzACNWPGQ3EwJ0EBBl1eZ1zy8pqWxW9qLZ7p39w5BC6Lm58xNHMBjqdzpc1iRbvdsKDWCtwcRPM8fr8ur0fP1rolbgtxgBVaYvFFdE7EczIAhuYiYXaOdBPNz/QFuVAEBCYDaecJLWFXG7efEPRE6fiRKRI4rfTpEnSiQyy2gYPAmFjEdAyyKiLkTNwAKjBmIgJzOIABAC9MhTaKR5nQTm4AG6oPB0nVJLm0cyw1LZACUT0lryJ3TwVBttBOmAAHqkNoaQSAlVliHh7Xg2Bl7ZCQn7heLA0HflSCJZaJsQLRMAB3SYy/S0dVCmYF7rCoqE5tuTCsExYtoBjuFzDF4ilo0wuHXCHeKHj3mYCC0H2N9vN1v96UigPrlGO51uLD63oQbU671kYHGs0Wup%2BhVR6ze/1NjshsMR6OxscJkxJlNp1gZlmDw5n2z4Dl05xYOwvS1uq2zZMuyKrpuYEFl2PZPiu4FfoeU53CEkGYIe85ntai6IVKyFtkhvxrqha5iluqFohigzYhoiwTNaOJuAKoSoY4BwVm4uyoKgrDMukOR8qK4QQLhCLTiEb4EHoDTWgptx8Spam3qg96YI%2BubboOw6ltk5iYBR%2BZ0VhLEDFi3g8Vx8wcXiBI0YJjiJKJ4mSeyk7EGAYCcvJPLwkBjxoOGqkSOp3ITnyXjadFJy6XU%2BmRg%2BFLGahcxFiWbhUGwPbWXMtnRBVEozLETguO4tz2pg5JTvxLwBo4FIAGJkgA1hAIF5nMX5NS1ileJ1ZGNM0s4Rd4nUFA8RVicZm6MahNCoNwVI9sQTUQJwvBLutWGbdwji7QQ1BidwuyYMAjgDdaEjHUN3RnRd7JXWdd0PbQT1uFIr0mQVI7Lagta8HBRjg7WnANidlUoS8Ng%2BuoIA2KINikLQGO8NjqAY14Rgw2Yli1PYnDYwQeOo2jvUgIIvDcA0whSAoDQc5z7NM0orAY4I2O4zY%2BOkITNjYyYIC8KQNMi6jpBwLASBoOieDsGQFAQKrqTq%2ByKAaFoDS8DLVDq70xBSxAuy06QNLlMQgQY1TpCq349AAPK0KwTvy6QWA%2BJowDsLb%2BBUuSKaYFLftRs15i9M72OdV2iey8mPi02jhvaCTBjqHguxS5AaOoN6eC2hjAC0RqcroBhGJw/BuJXHsSJLFhWBwnBZxjWM47b4uRhzlfNK5QduA0fB8G4EC4IQJAeNInDWl4qBqxri9SN3bjE/XBjU5n9MgFIUjcHFQjCEzDT8AoojCI3ojozYgv9374uS9LsuZ4rMCICAFgEB2AQcglAdZ62IGoTA%2BB1hqErDkVIice6YyFgPDGlM3CVkIAgNwQ8GgjxaCMLQE8p6izlvjH0R84p8HZg0KQ/A4p0NENfQQT8X7C1Fu/Uwn8yF0yfm3V%2BHCMYH3lhQ0gTVLbl1xoIIAA%3D)

https://github.com/TsReaper/My-Allocator



![image.png](https://i.loli.net/2019/12/10/ixyIPrjtXWebF4v.png)

#### 输出

SGI　STL标准库源码 stl_alloc.h 文件209 行到 246行 debug_alloc类模板的设计：

delete []p

### 默认分配debug_alloc

```cpp
// Allocator adaptor to check size arguments for debugging.
// Reports errors using assert.  Checking can be disabled with
// NDEBUG, but it's far better to just use the underlying allocator
// instead when no checking is desired.
// There is some evidence that this can confuse Purify.
template <class _Alloc>
class debug_alloc {

private:

  enum {_S_extra = 8};  // Size of space used to store size.  Note
                        // that this must be large enough to preserve
                        // alignment.

                        //这儿就像它所说的那样
public:

  static void* allocate(size_t __n)
  {
    //这里实际申请的内存大小要多 8 个字节
    char* __result = (char*)_Alloc::allocate(__n + (int) _S_extra);
    *(size_t*)__result = __n;//前 4 个字节用于存储区块大小，可以看到，它预留了4个字节的空白区，具体原由 还望大牛能指出，==。
    return __result + (int) _S_extra;//最后返回相对于原始指针偏移8个字节的新指针
  }

  static void deallocate(void* __p, size_t __n)
  {
    char* __real_p = (char*)__p - (int) _S_extra;//获得原始指针
    assert(*(size_t*)__real_p == __n);//这里增加了一个断言，防止析构了被破坏的指针
    _Alloc::deallocate(__real_p, __n + (int) _S_extra);
  }

  static void* reallocate(void* __p, size_t __old_sz, size_t __new_sz)
  {
    char* __real_p = (char*)__p - (int) _S_extra;
    assert(*(size_t*)__real_p == __old_sz);
    char* __result = (char*)
      _Alloc::reallocate(__real_p, __old_sz + (int) _S_extra,
                                   __new_sz + (int) _S_extra);
    *(size_t*)__result = __new_sz;
    return __result + (int) _S_extra;
  }

};

《深入理解计算机系统》动态存储分配。负荷块之前存在头部，记录负荷大小与标志（是否存储内容），好像共计8字节。
    
```


再来看看 gcc 下，其实也有类似的设计：

```cpp
#if(defined(_X86_) && !defined(__x86_64))
#define _ALLOCA_S_MARKER_SIZE 8
#elif defined(__ia64__) || defined(__x86_64)
#define _ALLOCA_S_MARKER_SIZE 16
#endif

#if !defined(RC_INVOKED)
  static __inline void *_MarkAllocaS(void *_Ptr,unsigned int _Marker) {
    if(_Ptr) {
      *((unsigned int*)_Ptr) = _Marker;
      _Ptr = (char*)_Ptr + _ALLOCA_S_MARKER_SIZE;
    }
    return _Ptr;
  }
#endif
#ifndef RC_INVOKED
#undef _freea
  static __inline void __cdecl _freea(void *_Memory) {
    unsigned int _Marker;
    if(_Memory) {
      _Memory = (char*)_Memory - _ALLOCA_S_MARKER_SIZE;
      _Marker = *(unsigned int *)_Memory;
      if(_Marker==_ALLOCA_S_HEAP_MARKER) {
	free(_Memory);
      }
#ifdef _ASSERTE
      else if(_Marker!=_ALLOCA_S_STACK_MARKER) {
	_ASSERTE(("Corrupted pointer passed to _freea",0));
      }
#endif
    }
  }
#endif /* RC_INVOKED */
```

https://stackoverflow.com/questions/1518711/how-does-free-know-how-much-to-free

https://www.zhihu.com/question/25556263

```python
 ____ The allocated block ____
/                             \
+--------+--------------------+
| Header | Your data area ... |
+--------+--------------------+
          ^
          |
          +-- The address you are given
            

When you call malloc(), you specify the amount of memory to allocate. The amount of memory actually used is slightly more than this, and includes extra information that records (at least) how big the block is.(实际申请大小大于申请的大小)
```

### 二级配置器__default_alloc_template

~~~c++
// SGI STL 第二级配置器，GCC 默认使用第二级配置器，其作用是避免太多小额区块造成内存的碎片
// 无 “template 类型参数”，且第二参数也没有用，其中第一参数用于多线程环境下
template <bool threads, int inst>
class __default_alloc _template {

private:
  // Really we should use static const int x = N
  // instead of enum { x = N }, but few compilers accept the former.
#if ! (defined(__SUNPRO_CC) || defined(__GNUC__))
    enum {_ALIGN = 8};  // 小型区块的上调边界
    enum {_MAX_BYTES = 128}; // 小区区块的上限
    enum {_NFREELISTS = 16}; // _MAX_BYTES/_ALIGN  free-list 的个数
    
    
# endif 
  // 将任何小额区块的内存需求量上调至 8 的倍数
  static size_t
  _S_round_up(size_t __bytes) 
    { return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1)); }
    
    所以有 16 个 free lists，分别为 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128 bytes。例如需要 20 bytes，将会被自动调整为 24 bytes

__PRIVATE:
  // free-list 的节点结构，降低维护链表 list 带来的额外负担
  union _Obj {
        union _Obj* _M_free_list_link;  // 利用联合体特点
        char _M_client_data[1];    /* The client sees this.        */
  };
private:
# if defined(__SUNPRO_CC) || defined(__GNUC__) || defined(__HP_aCC)
    static _Obj* __STL_VOLATILE _S_free_list[]; 
        // Specifying a size results in duplicate def for 4.1
# else
    static _Obj* __STL_VOLATILE _S_free_list[_NFREELISTS];  // 维护 16 个空闲链表(free list)，初始化为0，即每个链表中都没有空闲数据块  
# endif 
  //根据申请数据块大小找到相应空闲链表的下标，n 从 0 起算
  static  size_t _S_freelist_index(size_t __bytes) {
        return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1);
  }

  // Returns an object of size __n, and optionally adds to size __n free list.
  static void* _S_refill(size_t __n);
  // Allocates a chunk for nobjs of size size.  nobjs may be reduced
  // if it is inconvenient to allocate the requested number.
  static char* _S_chunk_alloc(size_t __size, int& __nobjs);

  // Chunk allocation state.
  static char* _S_start_free;  // 内存池起始位置。只在 _S_chunk_alloc() 中变化
  static char* _S_end_free;    // 内存池结束位置。只在 _S_chunk_alloc() 中变化
  static size_t _S_heap_size;

# ifdef __STL_THREADS
    static _STL_mutex_lock _S_node_allocator_lock;
# endif

    // It would be nice to use _STL_auto_lock here.  But we
    // don't need the NULL check.  And we do need a test whether
    // threads have actually been started.
    class _Lock;
    friend class _Lock;
    class _Lock {
        public:
            _Lock() { __NODE_ALLOCATOR_LOCK; }
            ~_Lock() { __NODE_ALLOCATOR_UNLOCK; }
    };

public:

  /* __n must be > 0      */
  // 申请大小为n的数据块，返回该数据块的起始地址 
  static void* allocate(size_t __n)
  {
    void* __ret = 0;

    // 如果需求区块大于 128 bytes，就转调用第一级配置
    if (__n > (size_t) _MAX_BYTES) {
      __ret = malloc_alloc::allocate(__n);
    }
    else {
      // 根据申请空间的大小寻找相应的空闲链表（16个空闲链表中的一个）
      _Obj* __STL_VOLATILE* __my_free_list
          = _S_free_list + _S_freelist_index(__n);
      // Acquire the lock here with a constructor call.
      // This ensures that it is released in exit or during stack
      // unwinding.
#     ifndef _NOTHREADS
      /*REFERENCED*/
      _Lock __lock_instance;
#     endif
      _Obj* __RESTRICT __result = *__my_free_list;
      // 空闲链表没有可用数据块，就将区块大小先调整至 8 倍数边界，然后调用 _S_refill() 重新填充
      if (__result == 0)
        __ret = _S_refill(_S_round_up(__n));
      else {
        // 如果空闲链表中有空闲数据块，则取出一个，并把空闲链表的指针指向下一个数据块  
        *__my_free_list = __result -> _M_free_list_link;
        __ret = __result;
      }
    }

    return __ret;
  };

  /* __p may not be 0 */
  // 空间释放函数 deallocate()
  static void deallocate(void* __p, size_t __n)
  {
    if (__n > (size_t) _MAX_BYTES)   
      malloc_alloc::deallocate(__p, __n);   // 大于 128 bytes，就调用第一级配置器的释放
    else {
      _Obj* __STL_VOLATILE*  __my_free_list
          = _S_free_list + _S_freelist_index(__n);   // 否则将空间回收到相应空闲链表（由释放块的大小决定）中  
      _Obj* __q = (_Obj*)__p;

      // acquire lock
#       ifndef _NOTHREADS
      /*REFERENCED*/
      _Lock __lock_instance;
#       endif /* _NOTHREADS */
      __q -> _M_free_list_link = *__my_free_list;   // 调整空闲链表，回收数据块
      *__my_free_list = __q;
      // lock is released here
    }
  }

  static void* reallocate(void* __p, size_t __old_sz, size_t __new_sz);

} ;

    
~~~



# 2. 容器


STL对定义的通用容器分三类：
顺序性容器、关联式容器和容器适配器。

- 顺序性容器：vector、list、deque 双向队列

- 关联性容器：set、multiset、map、multimap

- 容器适配器：stack、queue、priority_queue

  stack 模板类的底层容器是:deque/list 容器
  queue 模板类的底层容器是:deque/list 容器
  priority_queue 模板类底层容器是array/vector 模拟二叉树





## 1 vector

### 1.1 理解

- vector的 capacity减少内存分配次数（优点）。大小指数级增长，但是

  每次分配，vector内部地址随时被改变。

  - 禁止 用data（）获取首地址来操作数据，因为随时会失效。

     iterator来操作管理

  

  

  

​    https://stackoverflow.com/questions/5232198/about-vectors-growth





### 1、stl_vector.h

~~~c++
// 默认走这里，vector base 构造函数和析构函数
// vector 继承 _Vector_base
template <class _Tp, class _Alloc> 
class _Vector_base {
public:
  typedef _Alloc allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }
  
  // 初始化
  _Vector_base(const _Alloc&)
    : _M_start(0), _M_finish(0), _M_end_of_storage(0) {}
  
  // 初始化，分配空间 
  _Vector_base(size_t __n, const _Alloc&)
    : _M_start(0), _M_finish(0), _M_end_of_storage(0) 
  {
    _M_start = _M_allocate(__n);
    _M_finish = _M_start;
    _M_end_of_storage = _M_start + __n;
  }
  
  // 释放空间
  ~_Vector_base() { _M_deallocate(_M_start, _M_end_of_storage - _M_start); }

protected:
  _Tp* _M_start;  // 表示目前使用空间的头
  _Tp* _M_finish; // 表示目前使用空间的尾
  _Tp* _M_end_of_storage; // 表示目前可用空间的尾

  // simple_alloc 是 SGI STL 的空间配置器
  typedef simple_alloc<_Tp, _Alloc> _M_data_allocator;  // 以元素大小为配置单位
  _Tp* _M_allocate(size_t __n)
    { return _M_data_allocator::allocate(__n); }
  void _M_deallocate(_Tp* __p, size_t __n) 
    { _M_data_allocator::deallocate(__p, __n); }
};


template <class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp) >
class vector : protected _Vector_base<_Tp, _Alloc> 
    
    
doc:
template < class T, class Alloc = allocator<T> > class vector; // generic template

- 构造函数
    
// 构造拥有 n 个有值 value 的元素的容器
vector(size_type __n, const _Tp& __value,
         const allocator_type& __a = allocator_type()) 
    : _Base(__n, __a)
    { _M_finish = uninitialized_fill_n(_M_start, __n, __value); }


http://luodw.cc/2015/10/27/STL-vec/
http://luodw.cc/2015/10/26/Calloc/#more
https://wetest.qq.com/lab/view/318.html?from=content_testerhome
https://www.zhihu.com/question/274802525
https://www.zhihu.com/question/274802525
~~~



- 解析 https://www.kancloud.cn/digest/stl-sources/177263





  ### 内存占用统计

https://rextester.com/THGSQZ86778

















--------------------------------------------------------------------------

# 空间配置器

https://www.kancloud.cn/digest/stl-sources/177263





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



- 



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



 # adapter （ 适配器 设计模式）

![image.png](https://i.loli.net/2019/11/25/R5fdYHSjNIJQok4.png)

 将一个class的接口转换为另一个class的接口，使原本因接口不兼容而不能合作的classes，可以一起运作 





- 函数适配器
- 容器适配器
- 迭代器适配器

// **学习STL，设计模式，chromium的源码是最好的教材。** 

![容器适配器](https://upload-images.jianshu.io/upload_images/1837968-341ccb6ba217e986.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![类型](https://github.com/steveLauwh/SGI-STL/raw/master/The%20Annotated%20STL%20Sources%20V3.3/Other/adapter.PNG)





#### 说明：

测试代码：stl_adapter.cpp

注释代码：









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

作用：克服类组合和基础的编译依赖问题


https://blog.csdn.net/ww32zz/article/details/49277605

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
-不过bind1st和bind2nd在C++ 11中已经被deprecated，被std::bind取代。


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


STL源码——function adapter函数适配器/函数配接器

function adapters是指能够将function objects(函数对象)与另一个function objects、某个值、某个一般函数结合起来的function objects
通过function adapter的绑定、组合、修饰能力，可以创造出用户所需的各种表达式


https://blog.csdn.net/huazhongkejidaxuezpp/article/details/19420727
用于成员函数指针

c++ 对象与对象之间传递方式
这里不socket等方式。
指针和引用

>这种配接器使我们能够将成员函数当做仿函数来使用，于是成员函数可以搭配各种泛型算法。当容器的元素型式是X& 或X* ，而我们又以虚拟成员函数作为仿函数，便可以藉由泛型算法完成所谓的多态调用。这是泛型与多态之间的一个重要接轨。

c语言中 声明一个函数指针，并且规定参数类型 ,调用op(10,20),在函数之间进程传递--函数传递
在c++中，声明一个函数对象，自定义opeartor（）操作，通过像函数一样调用 A a a（10，20） 在对象构造时候传递 对象传递
A[1] A++ A()

函数适配器

## 函数适配器



### 参考

-  https://www.kancloud.cn/digest/mystl/192544   《STL源码剖析》 P430、P454. 
- 



### lambda表达式的本质(函数对象)

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



 status = array_each(&ctx->pool, server_pool_each_preconnect, NULL);

## 

### 函数对象模块

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

------------------------------------------------------------------------
### std::function

C++11中，callable object 包括传统
1 C函数， 
2 C++成员函数，
3 函数对象（实现了（）运算符的类的实例），
4 lambda表达式（特殊函数对象）

----------------------------------------------------------
`void print( State* pstate )
{
    pstate->print();
}

于是就可以简化为下面代码：
std::for_each( vect.begin(), vect.end(), &print );

上面这段代码有点丑陋，看起来不太爽，主要是函数指针的原因。
在这种应用环境下，C++有仿函数来替代，我们定义一个仿函数，如下：

struct Printer
{
    template<typename T> void operator()( T* t ) { t->print(); }
};

于是就可以简化为下面代码：
std::for_each( vect.begin(), vect.end(), Printer() );`

---------------------------------------------------------

~~~

// for_each.  Apply a function to every element of a range.
template <class _InputIter, class _Function>

_Function for_each(_InputIter __first, _InputIter __last, _Function __f) {
  __STL_REQUIRES(_InputIter, _InputIterator);
  
  for ( ; __first != __last; ++__first)
    
    __f(*__first);
    
  return __f;
}
~~~




`std::function`类模板是一种通用的函数包装器，它可以容纳所有可以调用的对象（[Callable](http://en.cppreference.com/w/cpp/concept/Callable)），

包括 **函数**、**函数指针**、**Lambda表达式**、**bind表达式**、成员函数及成员变量或者其他函数对象。

通过 `std::function` 可以储存、拷贝或调用 Callable 对象。它的模板参数如下：



# std::bind

 顾名思义，`std::bind`函数用来绑定函数的某些参数并生成一个新的`function`对象。
`bind`用于实现偏函数（Partial Function），[相当于实现了函数式编程中的 **Currying**](https://www.sczyh30.com/posts/C-C/cpp-stl-functional/)（柯里化）。 



c++线程函数可以是lambda吗?可以是c++成员函数吗?





#   迭代器  (迭代器模式)

![image.png](https://i.loli.net/2019/11/25/6eVPDNxAr9GgtRv.png)

 [http://www.wtango.com/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F17-%E8%BF%AD%E4%BB%A3%E5%99%A8%E6%A8%A1%E5%BC%8F/](http://www.wtango.com/设计模式17-迭代器模式/) 





