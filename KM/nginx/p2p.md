### 1.媒体服务器搭建

#### centos  28 10.115.37.45

- 版本
 1. 版本6.8的根本不支持 
 >cat /etc/redhat-release
 
 CentOS release 6.8 (Final)
 
 >cat /proc/version
 Linux version 2.6.32-642.gome.el6.x86_64
  
  建议安装最新的docker使用centos7
  官方文档要求Linux kernel至少3.8以上，且docker只能运行在64位的系统中。由于RHEL6和CentOS6的内核版本为2.6，
  

2. centos7
  cat /etc/redhat-release
  CentOS Linux release 7.2.1511 (Core) 

- 更新 yum源改为阿里 (解决翻墙问题)

~~~

1. 把/etc/yum.repos.d下的文件全部删除

2. yum源更改为阿里云的yum源
get -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-6.repo

3. 
Create the repository config file /etc/yum.repos.d/slce.repo:
[slce]
name=Scientific Linux Cyrillic Edition
baseurl=http://downloads.naulinux.ru/pub/SLCE/6x/$basearch/CyrEd/RPMS/
enabled=0
gpgcheck=1
gpgkey=http://downloads.naulinux.ru/pub/SLCE/RPM-GPG-KEY-linux-ink
Install rpmforge-release rpm package:
# yum --enablerepo=slce install rpmforge-release

4

yum clean
yum makecache
yum update

yum list
~~~

- docker安装

#查看你当前的内核版本
uname -r

#安装 Docker
yum -y install docker

#启动 Docker 后台服务
service docker start

sudo systemctl enable docker


说明：
~~~
6.8版本不行，内核不支持

rpm -iUvh http://dl.fedoraproject.org/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm
yum update -y
~~~

------------------------------------------------------------------

- Kurento Media Server – RPM packages for RHEL / CentOS 7
   
docker：  https://hub.docker.com/r/kurento/kurento-media-server

https://blog.gmem.cc/webrtc-server-basedon-kurento#entrypoint

https://www.jianshu.com/p/762a4587346d


~~~
docker run -d --name kms -p 8888:8888 \
    kurento/kurento-media-server:latest \
     -v /etc/kurento/:/etc/kurento/
    
telnet 127.0.0.1  8888    
    
~~~








kurento设置打洞服务器地址




----------------------------------------------------------------------------

程序：

https://github.com/pkgs-cloud/kurento

~~~
Installation
Install Kurento RPM packages with required dependencies
Install pkgs.cloud release repository
yum install kurento-release epel-release -y
yum install kms -y
List all available packages
yum --disablerepo="*" --enablerepo="pkgs.cloud-kurento" list available
Additional (optional) Kurento filters
yum install kms-filters-chroma -y
yum install kms-filters-crowddetector -y
yum install kms-filters-platedetector -y
yum install kms-filters-pointerdetector -y


Usage
Modify default settings
/etc/sysconfig/kms
/etc/kurento:
/etc/kurento
	├── kurento.conf.json
	└── modules
	    └── kurento
	        ├── BaseRtpEndpoint.conf.ini
	        ├── HttpEndpoint.conf.ini
	        ├── MediaElement.conf.ini
	        ├── SdpEndpoint.conf.json
	        ├── UriEndpoint.conf.ini
	        └── WebRtcEndpoint.conf.ini
            
Enable, start, restart Kurento service
systemctl enable kms.service
systemctl start kms.service
systemctl restart kms.service

~~~

日志：
/var/log/kurento
/etc/kurento/modules/kurento/WebRtcEndpoint.conf.ini
- mysql
~~~
Centos 7 安装 MySQL
wget 'https://dev.mysql.com/get/mysql57-community-release-el7-11.noarch.rpm'
sudo rpm -Uvh mysql57-community-release-el7-11.noarch.rpm
sudo yum install mysql-community-server
sudo service mysqld start 


安装提示，查看密码，登录数据库，然后修改密码：
mysql -uroot -p  #输入查看到的密码


mysql -u root -p'/sy)f2fz&eFO' //-p 后面就是密码 不能有空格
mysql -u root -p'12345678' //-p 后面就是密码 不能有空格



ALTER USER USER() IDENTIFIED BY '12345678';


set global validate_password_policy=0;



~~~

- ssl tomcat证书生成

https://www.jianshu.com/p/a55590f486a2

~~~
keytool -genkey -v -alias myapprtc -keyalg RSA -validity 3650 -keystore ./123456.keystore

alias: 别名 这里起名testKey
keyalg: 证书算法，RSA
validity：证书有效时间，10年
keystore：证书生成的目标路径和文件名,替换成你自己的路径即可,我定义的是~/Lee/test.keystore
https://10.115.37.45/webrtc-conference_v5/

~~~

- coturn服务的安装


首先克隆这个项目：https://github.com/konoui/kurento-coturn-docker.git（可以给个star，毕竟帮忙解决问题了），克隆好了执行以下操作：
cd /kurento-coturn-docker/coturn/
//使用dockerfile,记住加点
sudo docker build --tag coturn .
//后台运行coturn
sudo docker run -p 3478:3478 -p 3478:3478/udp coturn

嗯，这个dockerfile给你配置turn的用户名和密码都是kurent

作者：许瑞锐
链接：https://www.jianshu.com/p/762a4587346d
来源：简书
简书著作权归作者所有，任何形式的转载都请联系作者获得授权并注明出处。


./turnutils_stunclient  10.115.37.45


turnutils_uclient -u kurento -w kurento 10.115.37.45

