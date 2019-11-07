来源： https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/README.md 

1. 类型推导
   1. [Item 1:理解模板类型推导](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/1.DeducingTypes/item1.md) **已修订**
   2. [Item 2:理解auto类型推导](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/1.DeducingTypes/item2.md)
   3. [Item 3:理解decltype](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/1.DeducingTypes/item3.md)
   4. [Item 4:学会查看类型推导结果](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/1.DeducingTypes/item4.md)
2. auto
   1. [Item 5:优先考虑auto而非显式类型声明](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/2.auto/item5.md)
   2. [Item 6:auto推导若非己愿，使用显式类型初始化惯用法](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/2.auto/item6.md)
3. 移步现代C++
   1. [Item 7:区别使用()和{}创建对象](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/3.MovingToModernCpp/item7.md)
   2. [Item 8:优先考虑nullptr而非0和NULL](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/3.MovingToModernCpp/item8.md)
   3. [Item 9:优先考虑别名声明而非typedefs](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/3.MovingToModernCpp/item9.md)
   4. [Item 10:优先考虑限域枚举而非未限域枚举](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/3.MovingToModernCpp/item10.md) **已修订**
   5. [Item 11:优先考虑使用deleted函数而非使用未定义的私有声明](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/3.MovingToModernCpp/item11.md)
   6. [Item 12:使用override声明重载函数](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/3.MovingToModernCpp/item12.md)
   7. [Item 13:优先考虑const_iterator而非iterator](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/3.MovingToModernCpp/item13.md)
   8. [Item 14:如果函数不抛出异常请使用noexcept](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/3.MovingToModernCpp/item14.md)
   9. [Item 15:尽可能的使用constexpr](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/3.MovingToModernCpp/item15.md)
   10. [Item 16:让const成员函数线程安全](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/3.MovingToModernCpp/item16.md) **由 @windski贡献**
   11. [Item 17:理解特殊成员函数函数的生成](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/3.MovingToModernCpp/item17.md)
4. 智能指针
   1. [Item 18:对于独占资源使用std::unique_ptr](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/4.SmartPointers/item18.md) **更新中**
   2. [Item 19:对于共享资源使用std::shared_ptr](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/4.SmartPointers/item19.md) **已修订**
   3. [Item 20:像std::shared_ptr一样使用std::weak_ptr可能造成dangle](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/4.SmartPointers/item20.md) **更新中**
   4. Item 21:优先考虑使用std::make_unique和std::make_shared而非new
   5. [Item 22:当使用Pimpl惯用法，请在实现文件中定义特殊成员函数](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/4.SmartPointers/item22.md)
5. 右值引用，移动语意，完美转发
   1. [Item 23:理解std::move和std::forward](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/5.RvalueReferences_MovingSemantics_And_PerfectForwarding/item23.md)
   2. [Item 24:区别通用引用和右值引用](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/5.RvalueReferences_MovingSemantics_And_PerfectForwarding/item24.md)
   3. Item 25:对于右值引用使用std::move，对于通用引用使用std::forward
   4. Item 26:避免重载通用引用
   5. Item 27:熟悉重载通用引用的替代品
   6. Item 28:理解引用折叠
   7. Item 29:认识移动操作的缺点
   8. Item 30:熟悉完美转发失败的情况
6. Lambda表达式
   1. Item 31:避免使用默认捕获模式
   2. Item 32:使用初始化捕获来移动对象到闭包中
   3. Item 33:对于std::forward的auto&&形参使用decltype
   4. Item 34:有限考虑lambda表达式而非std::bind
7. 并发API
   1. Item 35:优先考虑基于任务的编程而非基于线程的编程
   2. Item 36:如果有异步的必要请指定std::launch::threads
   3. Item 37:从各个方面使得std::threads unjoinable
   4. Item 38:知道不同线程句柄析构行为
   5. Item 39:考虑对于单次事件通信使用void
   6. Item 40:对于并发使用std::atomic，volatile用于特殊内存区
8. 微调
   1. Item 41:对于那些可移动总是被拷贝的形参使用传值方式
   2. Item 42:考虑就地创建而非插入