# docker学习笔记




## Dockerfile
- 安装 


1. CentOS7 配置阿里云yum源
~~~
第一步：备份你的原镜像文件，以免出错后可以恢复。

mv /etc/yum.repos.d/CentOS-Base.repo /etc/yum.repos.d/CentOS-Base.repo.backup
第二步：下载新的CentOS-Base.repo 到/etc/yum.repos.d/

curl -o /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo
sed -i '/aliyuncs.com/d' /etc/yum.repos.d/*.repo
安装epel仓库

curl -o /etc/yum.repos.d/epel.repo http://mirrors.aliyun.com/repo/epel-7.repo
第三步：运行yum makecache生成缓存

yum clean all
yum makecache

~~~

docker -v
Docker version 1.12.6, build 1398f24/1.12.6
curl https://releases.rancher.com/install-docker/1.12.sh | sh




Q 
~~
操作：
https://qizhanming.com/blog/2019/01/25/how-to-install-docker-ce-on-centos-7
sudo yum install -y yum-utils  device-mapper-persistent-data lvm2
描述~
错误：软件包：7:lvm2-2.02.180-10.el7_6.8.x86_64 (updates)
          需要：device-mapper-persistent-data >= 0.7.0-0.1.rc6
          已安装: device-mapper-persistent-data-0.6.3-1.el7.x86_64 (@base)
              device-mapper-persistent-data = 0.6.3-1.el7
          可用: device-mapper-persistent-data-0.5.5-1.el7.x86_64 (base)
              device-mapper-persistent-data = 0.5.5-1.el7
          可用: device-mapper-persistent-data-0.6.2-1.el7_2.x86_64 (gomedc-updates)
              device-mapper-persistent-data = 0.6.2-1.el7_2
 您可以尝试添加 --skip-broken 选项来解决该问题
 您可以尝试执行：rpm -Va --nofiles --nodigest
~~~
尝试办法：
https://my.oschina.net/dingdayu/blog/2966434 不行
https://www.bbsmax.com/A/WpdKqgEqJV/ 不行
https://www.jianshu.com/p/281a024e1abf 不行
https://www.cnblogs.com/dengdengkai/p/9340682.html 不行

https://www.cnblogs.com/zhenyuyaodidiao/p/4953143.html 删除ok
https://www.iirwt.com/2018/11/82.html OK -但是有问题


https://www.jianshu.com/p/3a4cd73e3272--- ok



- Q docker启动失败解决

systemctl status docker.service
https://www.cnblogs.com/SimonHu1993/p/9199566.html


A


Q  overlay2 docker 报错

分析
4.0内核,docker官方推荐的是overlay2 做storage driver，但是，xfs文件系统在4.0上与docker不能兼容，需要更改文件系统为ext4。

https://www.jianshu.com/p/aeef770fc66b
- 重启容器
   docker sart kms
   
- 停止容器
docker stop dd80793a1d92

- 查看正在启动容器 
    docker ps 
    docker ps -a

- 查看日志
docker logs  ede304afe46f\
- 查看docker信息

docker inspect dd80793a1d92

docker 数据卷轴 能挂在本地 etc var目录吗
数据卷的最大特定是：其生存周期独立于容器的生存周期。

Docker持久化数据的方案

基于本地文件系统的Volume。可以再执行Docker create或Docker run时，通过-v参数将主机的目录作为容器的数据卷。这部分功能便是基本的本地文件系统的volume管理。
基于plugin的Volume，支持第三方的存储方案，比如NAS，aws

作者：蒋老湿
链接：https://juejin.im/post/5b6d4439f265da0f800e0d5a
来源：掘金
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

首次docker run -v 运行，如果本机的文件夹是没有内容的，docker容器中的文件夹是有内容的，则本机的会覆盖dokcer容器中的，也就是容器中原本有内容的也会没有内容。


### 源码解析



### FQA

- q1 
docker info 
Cannot connect to the Docker daemon. Is the docker daemon running on this host?

a1:

需要root用户


