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
~~~



~~~shell
 use job;
 
~~~







# 高性能Mysql第三版

