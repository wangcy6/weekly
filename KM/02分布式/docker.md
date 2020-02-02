# 一、docker 

## 1 docker 基本操作

- 停止所有的容器

​    docker stop $(docker ps -aq)



- 删除所有的容器

 docker rm $(docker ps -aq)

- 删除所有的镜像

docker rmi $(docker images -q)