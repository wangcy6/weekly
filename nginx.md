## day2 浅谈内存池技术

- 类STL的内存池技术
- nginx内存池技术



如果申请的内存块大于128字节，就将申请的操作移交std::new去处理；

如果申请的区块大小小于128字节时，就从本分配器维护的内存池中分配内存。

该Allocator最小的分配单位为8Byte，其内部维护了一个长度为维护128/8=16的空闲链表数组，

每个链表管理着固定大小的内存

- _S_free_list[0] ——–> 8 byte
- _S_free_list[1] ——–> 16 byte
- _S_free_list[2] ——–> 24 byte
- _S_free_list[3] ——–> 32 byte
- … …
- _S_free_list[15] ——-> 128 byte









std::allocator 

https://www.youtube.com/watch?v=LIb3L4vKZ7U&t=428s

http://blog.yaoyumeng.com/2014/08/31/Memory_Pool