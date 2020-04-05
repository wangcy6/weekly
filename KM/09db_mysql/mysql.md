---
title: "mysql "
date: 2019-11-27
description: " 你明明知道数据库是你弱点，你为什么不现在补救一下 必须掌握"
draft: false
tags: ["mysql"]
categories: ["book"]

---



# sql

## 参考资料1 [廖雪峰的官方网站](https://www.liaoxuefeng.com/)

https://www.liaoxuefeng.com/wiki/1177760294764384/1179611448454560

https://github.com/michaelliao/learn-sql/blob/master/mysql/init-test-data.sql

- 请使用一条语句 统计各班的男生和女生人数

SELECT class_id, gender, COUNT(*) num FROM students GROUP BY class_id, gender;

- 请使用一条SELECT查询查出每个班级男生和女生的平均分：

```mysql
select class_id, gender,AVG(score)
 from students
 group by class_id,gender
```

[一次group by 优化之旅](https://juejin.im/post/5ced5191e51d455070226f26)





## 部署安装

~~~shell
centos6.8
yum -y install mysql mysql-server mysql-devel //从yum库中的安装mysql
rpm -qi mysql-server //验证是否安装成功
 service mysqld start //启动mysql服务
输入命令： 
 mysql -u root
mysql -u root -p

建立远程root用户

GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY '123456' WITH GRANT OPTION;

flush privileges;

修改密码
更改mysql密码，要FLUSH PRIVILEGES; 才生效
mysql -u root 
mysql> use mysql; 
mysql> update user set password=password('123456') where user='root'; 
mysql> FLUSH PRIVILEGES; 
mysql> quit; 
# service mysqld restart

mysql -u root -p  123456

sudo apt-get install mysql-client mysql-server
sudo service mysql status
sudo service mysqld start

/etc/init.d/networking restart
select user, plugin from mysql.user;	
update mysql.user set authentication_string=PASSWORD('123456'), plugin='mysql_native_password' where user='root';

~~~



~~~shell

 mysql> create database  dream;
Query OK, 1 row affected (0.01 sec)

mysql> use dream;
Database changed

mysql+5.7+设置远程登录
在ubuntu14.04上安装好mysql5.7之后，本地可以连接mysql服务器。
远程就不行。

注释掉在/etc/mysql/mysql.conf.d/mysqld.cnf里面的bind-address = 127.0.0.1

GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY 'root' WITH GRANT OPTION;

~~~



#### ubuntu mysql 5.7

https://cloud.tencent.com/developer/article/1392435

~~~shell
sudo apt-get autoremove --purge mysql-server-5.0
sudo apt-get remove mysql-server
sudo apt-get autoremove mysql-server
sudo apt-get remove mysql-common //这个很重要
上面的其实有一些是多余的
dpkg -l |grep ^rc|awk '{print $2}' |sudo xargs dpkg -P
sudo apt-get install mysql-server
sudo apt-get install mysql-client
sudo apt-get install php5-mysql 
// 安装php5-mysql 是将php和mysql连接起来
一旦安装完成，MySQL 服务器应该自动启动。您可以在终端提示符后运行以下命令来检查 MySQL 服务器是否正在运行：
sudo netstat -tap | grep mysql

 mysql -V
mysql  Ver 14.14 Distrib 5.7.29, for Linux (x86_64) using  EditLine wrapper
root@work:~# 


mysqladmin -uroot -p password 123456 



#查看mysql状态
/etc/init.d/mysql status 或者 service mysql status
#启动mysql
/etc/init.d/mysql start 或者 service mysql start
#停止mysql
/etc/init.d/mysql stop 或者 service mysql stop
#重新启动mysql
/etc/init.d/mysql restart 或者 service mysql restart
查看mysql服务说明启动成功

————————————————
版权声明：本文为CSDN博主「南有乔木灬」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/wudawei071193/java/article/details/100777206

 /etc/init.d/networking restart
~~~



# 高性能Mysql第三版

