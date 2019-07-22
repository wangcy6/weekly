kube-proxy # 资源

基本使用：
https://feisky.gitbooks.io/kubernetes/content/introduction/concepts.html
https://github.com/kubernetes/kubernetes

源码解析：
https://github.com/feiskyer/kubernetes-handbook/blob/master/components/kube-proxy.md


# 学习记录
## 第一天

- Kubernetes Basics
  Using the interactive tutorials, you can learn to:
  Deploy a containerized application on a cluster.
  Scale the deployment.
  Update the containerized application with a new software version.
  Debug the containerized application.
  
Kubernetes 是谷歌开源的容器集群管理系统，是 Google 多年大规模容器管理技术 Borg 的开源版本，主要功能包括：
基于容器的应用部署、维护和滚动升级
负载均衡和服务发现
跨机器和跨地区的集群调度
自动伸缩
无状态服务和有状态服务
广泛的 Volume 支持
插件机制保证扩展性
Kubernetes 发展非常迅速，已经成为容器编排领域的领导者


### 核心组件

Kubernetes 主要由以下几个核心组件组成：
etcd 保存了整个集群的状态；
apiserver 提供了资源操作的唯一入口，并提供认证、授权、访问控制、API 注册和发现等机制；
controller manager 负责维护集群的状态，比如故障检测、自动扩展、滚动更新等；
scheduler 负责资源的调度，按照预定的调度策略将 Pod 调度到相应的机器上；
kubelet 负责维护容器的生命周期，同时也负责 Volume（CVI）和网络（CNI）的管理；
Container runtime 负责镜像管理以及 Pod 和容器的真正运行（CRI）；

kube-proxy 负责为 Service 提供 cluster 内部的服务发现和负载均衡



![db](https://feisky.gitbooks.io/kubernetes/content/introduction/architecture.png)

###  部署



1.  安装kubectl 
- 方法1  通过 curl 命令安装 kubectl 可执行文件(翻墙版本)
   https://k8smeetup.github.io/docs/tasks/tools/install-kubectl/
   
- 方法2  源码安装 --没有验证过

- 方法3 :kubernetes HA集群在centos7无翻墙搭建
https://zhuanlan.zhihu.com/p/48346592
使用阿里镜像安装

配置源
~~~
sudo cat <<EOF > /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=https://mirrors.aliyun.com/kubernetes/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://mirrors.aliyun.com/kubernetes/yum/doc/yum-key.gpg https://mirrors.aliyun.com/kubernetes/yum/doc/rpm-package-key.gpg
exclude=kube*
EOF
~~~

安装
sudo yum install -y kubelet kubeadm kubectl ipvsadm --disableexcludes=kubernetes




2.安装 Minikube 

https://yq.aliyun.com/articles/221687

~~~
keytool -genkey -v -alias myapprtc -keyalg RSA -validity 3650 -keystore ./123456.keystore


alias: 别名 这里起名testKey
keyalg: 证书算法，RSA
validity：证书有效时间，10年
keystore：证书生成的目标路径和文件名,替换成你自己的路径即可,我定义的是~/Lee/test.keystore

~~~