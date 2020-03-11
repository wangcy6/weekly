# 一、docker 

## 1 docker 基本操作

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