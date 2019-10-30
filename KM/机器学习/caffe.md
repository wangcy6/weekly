## 探索

 Caffe是一个清晰而高效的深度学习框架 

https://github.com/BVLC/caffe

## 第一步 部署

系统配置

Python 3.6.2

~~~shell
yum install -y  libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler libboost-all-dev libatlas-base-dev libgflags-dev libgoogle-glog-dev liblmdb-dev


~~~







### 报错信息：

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

