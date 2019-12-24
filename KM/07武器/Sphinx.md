### 什么是Sphinx

就是一个软件,用来代替MySQL全文检索

Sphinx是SQL Parse Index（查询词组索引）缩写，基于SQL的全文检索引擎。Coreseek支持中文的全文检索引擎。

##### 优势

sphinx单一索引最大可包含1亿条记录,在1千万记录情况下的查询速度为0.x秒(毫秒级)

sphinx创建索引的速度为: 创建100万条记录的索引只需3~4分钟,创建1000万条记录的索引可以在50分钟内完成,而值包含最新10万条记录增量索引,重建一次只需十几秒

![img](https:////upload-images.jianshu.io/upload_images/12410545-3e2fd87fd484565e.png?imageMogr2/auto-orient/strip|imageView2/2/w/691/format/webp)



如何对索引进行搜索：

　　1. 输入查询语句，提交给Sphinx。

　　2. Sphinx对查询语句进行词法分析，语法分析及语言处理。

　　3. 搜索索引，得到符合语法树的文档。

　　4. 根据得到的文档和查询语句的相关性，对结果排序。

