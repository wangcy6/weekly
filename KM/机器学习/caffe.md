## 探索

 Caffe是一个清晰而高效的深度学习框架 

- 代码：https://github.com/BVLC/caffe

- 代码阅读 https://github.com/BUPTLdy/Caffe_Code_Analysis 

## 第一步 部署

#### 安装依赖 

| gcc    | gcc version 4.8.5   |                                      |
| ------ | ------------------- | ------------------------------------ |
| Python | 3.6.2               |                                      |
| protoc | protobuf-cpp-3.10.0 | 主要用于结构化数据的序列化和反序列化 |
| hdf5   |                     |                                      |
|        |                     |                                      |



> yum 安装



~~~shell
yum install -y  libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler libboost-all-dev libatlas-base-dev libgflags-dev libgoogle-glog-dev liblmdb-dev

yum -y install hdf5-devel
yum y install libprotobuf-dev
http://caffe.berkeleyvision.org/install_yum.html
~~~

> 源码安装

- [libprotobuf-dev](https://github.com/protocolbuffers/protobuf/releases/tag/v3.10.0)





#### Compilation

```
cp Makefile.config.example Makefile.config
# Adjust Makefile.config (for example, if using Anaconda Python, or if cuDNN is desired)
make all
make test
make runtest


https://www.jianshu.com/p/36badc9fbcc2
https://juejin.im/post/5b2a31e26fb9a00e3970566e
```



### 报错信息：

- older version of protoc

    https://github.com/BVLC/caffe/issues/5645 

   https://github.com/BVLC/caffe/issues/6527 

- 编译不过 gcc版本  https://github.com/BVLC/caffe/issues/6359 



- yum 不管用了

 CentOS 7升级[Python](http://lib.csdn.net/base/python)到3.6。2后，需要在/usr/bin/[python](http://lib.csdn.net/base/python)创建了一个指向Python 3的软连接 

**遇到的问题报错如下：**

File "/usr/bin/yum", line 30

  except KeyboardInterrupt, e

解决办法：

~~~shell
vi /usr/bin/yum 
vi /usr/libexec/urlgrabber-ext-down
将/usr/bin/python改为/usr/bin/python2
~~~





参考

 http://caffe.berkeleyvision.org/installation.html 

 https://www.jianshu.com/p/36badc9fbcc2 

