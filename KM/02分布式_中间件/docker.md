# 一、docker 

## 基本操作

### 安装

~~~
[root@fhb ~]# cat /etc/redhat-release
CentOS release 6.8 (Final)
[root@fhb ~]# sudo rpm -iUvh http://dl.fedoraproject.org/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm
[root@fhb ~]# sudo yum update -y

curl -sSL https://get.docker.com/ | sh
docker version
service docker start

yum install -y nginx
service nginx start
~~~



### docker 基本操作

- 启动

  ```shell
  systemctl restart docker
  ```

- 停止所有的容器

​    docker stop $(docker ps -aq)



- 删除所有的容器

 docker rm $(docker ps -aq)

- 删除所有的镜像

docker rmi $(docker images -q)

- 查看指定时间后的日志，只显示最后100行：

```shell
$ docker logs -f -t --since="2018-02-08" --tail=100 CONTAINER_ID
$ docker logs --since 30m CONTAINER_ID
docker logs -f --tail=100 f215dfab44fd
```