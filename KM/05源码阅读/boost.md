# day1 

### Ubuntu 安装boost 库 编译

```
git clone --recursive https://github.com/boostorg/boost.git
cd boost
git checkout develop # or whatever branch you want to use
./bootstrap.sh
./b2 headers
```

### book

http://zh.highscore.de/cpp/boost/introduction.html

Boost程序库完全开发指南

| Boost C++ 库                                                 | C++ 标准 | 简要说明                                                     |
| ------------------------------------------------------------ | -------- | ------------------------------------------------------------ |
| [Boost.Any](http://zh.highscore.de/cpp/boost/datastructures.html#datastructures_any) |          | Boost.Any 提供了一个名为 `boost::any` 的数据类型，可以存放任意的类型。 例如，一个类型为 `boost::any` 的变量可以先存放一个 `int` 类型的值，然后替换为一个 `std::string` 类型的字符串。 |
| [Boost.Array](http://zh.highscore.de/cpp/boost/containers.html#containers_array) | TR1      | Boost.Array 可以把 C++ 数组视同 C++ 标准的容器。             |
| [Boost.Asio](http://zh.highscore.de/cpp/boost/asio.html)     | TR2      | Boost.Asio 可用于开发异步处理数据的应用，如网络应用。        |
| [Boost.Bimap](http://zh.highscore.de/cpp/boost/containers.html#containers_bimap) |          | Boost.Bimap 提供了一个名为 `boost::bimap` 的类，它类似于 `std::map`. 主要的差别在于 `boost::bimap` 可以同时从键和值进行搜索。 |
| [Boost.Bind](http://zh.highscore.de/cpp/boost/functionobjects.html#functionobjects_bind) | TR1      | Boost.Bind 是一种适配器，可以将函数作为模板参数，即使该函数的签名与模板参数不兼容。 |
| [Boost.Conversion](http://zh.highscore.de/cpp/boost/castoperators.html#castoperators_conversion) |          | Boost.Conversion 提供了三个转型操作符，分别执行向下转型、交叉转型，以及不同数字类型间的值转换。 |
| [Boost.DateTime](http://zh.highscore.de/cpp/boost/datetime.html) |          | Boost.DateTime 可用于以灵活的格式处理、读入和写出日期及时间值。 |
| [Boost.Exception](http://zh.highscore.de/cpp/boost/errorhandling.html#errorhandling_exception) |          | Boost.Exception 可以在抛出的异常中加入额外的数据，以便在 `catch` 处理中提供更多的信息。 这有助于更容易地调试，以及对异常情况更好地作出反应。 |
| [Boost.Filesystem](http://zh.highscore.de/cpp/boost/filesystem.html) | TR2      | Boost.Filesystem 提供了一个类来处理路径信息，还包含了几个访问文件和目录的函数。 |
| [Boost.Format](http://zh.highscore.de/cpp/boost/stringhandling.html#stringhandling_format) |          | Boost.Format 以一个类型安全且可扩展的 `boost::format` 类替代了 `std::printf()` 函数。 |
| [Boost.Function](http://zh.highscore.de/cpp/boost/functionobjects.html#functionobjects_function) | TR1      | Boost.Function 简化了函数指针的定义。                        |
| [Boost.Interprocess](http://zh.highscore.de/cpp/boost/interprocesscommunication.html) |          | Boost.Interprocess 允许多个应用通过共享内存以快速、高效的方式进行通信。 |
| [Boost.Lambda](http://zh.highscore.de/cpp/boost/functionobjects.html#functionobjects_lambda) |          | Boost.Lambda 可以定义匿名的函数。 代码被内联地声明和执行，避免了单独的函数调用。 |
| [Boost.Multiindex](http://zh.highscore.de/cpp/boost/containers.html#containers_multiindex) |          | Boost.Multiindex 定义了一些新的容器，它们可以同时支持多个接口，如 `std::vector` 和 `std::map` 的接口。 |
| [Boost.NumericConversion](http://zh.highscore.de/cpp/boost/castoperators.html#castoperators_numeric_conversion) |          | Boost.NumericConversion 提供了一个转型操作符，可以安全地在不同的数字类型间进行值转换，不会生成上溢出或下溢出的条件。 |
| [Boost.PointerContainer](http://zh.highscore.de/cpp/boost/smartpointers.html#smartpointers_pointer_container) |          | Boost.PointerContainer 提供了专门为动态分配对象进行优化的容器。 |
| [Boost.Ref](http://zh.highscore.de/cpp/boost/functionobjects.html#functionobjects_ref) | TR1      | Boost.Ref 的适配器可以将不可复制对象的引用传给需要复制的函数。 |
| [Boost.Regex](http://zh.highscore.de/cpp/boost/stringhandling.html#stringhandling_regex) | TR1      | Boost.Regex 提供了通过正则表达式进行文本搜索的函数。         |
| [Boost.Serialization](http://zh.highscore.de/cpp/boost/serialization.html) |          | 通过 Boost.Serialization，对象可以被序列化，如保存在文件中，并在以后重新导入。 |
| [Boost.Signals](http://zh.highscore.de/cpp/boost/eventhandling.html) |          | Boost.Signal 是一个事件处理的框架，基于所谓的 signal/slot 概念。 函数与信号相关联并在信号被触发时自动被调用。 |
| [Boost.SmartPoiners](http://zh.highscore.de/cpp/boost/smartpointers.html) | TR1      | Boost.SmartPoiners 提供了多个智能指针，简化了动态分配对象的管理。 |
| [Boost.Spirit](http://zh.highscore.de/cpp/boost/parser.html) |          | Boost.Spirit 可以用类似于 EBNF (扩展巴科斯范式)的语法生成词法分析器。 |
| [Boost.StringAlgorithms](http://zh.highscore.de/cpp/boost/stringhandling.html#stringhandling_stringalgorithms) |          | Boost.StringAlgorithms 提供了多个独立的函数，以方便处理字符串。 |
| [Boost.System](http://zh.highscore.de/cpp/boost/errorhandling.html#errorhandling_system) | TR2      | Boost.System 提供了一个处理系统相关或应用相关错误代码的框架。 |
| [Boost.Thread](http://zh.highscore.de/cpp/boost/multithreading.html) | C++0x    | Boost.Thread 可用于开发多线程应用。                          |
| [Boost.Tokenizer](http://zh.highscore.de/cpp/boost/stringhandling.html#stringhandling_tokenizer) |          | Boost.Tokenizer 可以对一个字符串的各个组件进行迭代。         |
| [Boost.Tuple](http://zh.highscore.de/cpp/boost/datastructures.html#datastructures_tuple) | TR1      | Boost.Tuple 提供了泛化版的 `std::pair`，可以将任意数量的数据组在一起。 |
| [Boost.Unordered](http://zh.highscore.de/cpp/boost/containers.html#containers_unordered) | TR1      | Boost.Unordered 扩展了 C++ 标准的容器，增加了`boost::unordered_set` 和 `boost::unordered_map`. |
| [Boost.Variant](http://zh.highscore.de/cpp/boost/datastructures.html#datastructures_variant) |          | Boost.Variant 可以定义多个数据类型，类似于 `union`, 将多个数据类型组在一起。 Boost.Variant 比 `union` 优胜的地方在于它可以使用类。 |



### 第三章内存管理（76Page-）

