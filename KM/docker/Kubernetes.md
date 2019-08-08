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
http://hutao.tech/k8s-source-code-analysis/prepare/debug-environment.html

1. 步骤1 
- 方法 :kubernetes HA集群在centos7无翻墙搭建
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




安装k8s master
tip：下面的ip地址(192.168.19.100)大家需要替换成自己机器上的！

kubeadm init --pod-network-cidr=10.100.0.0/16 --service-cidr=10.101.0.0/16 --kubernetes-version=v1.13.3 --apiserver-advertise-address 10.115.37.45



方法2 .安装 Minikube 舍去 

https://github.com/kubernetes/minikube


### 第一步

minikube start defaults to virtualbox, but supports other drivers using the --vm-driver argument:

KVM2 - Recommended Linux driver
查看cpu是否支持虚拟化
cat /proc/cpuinfo | egrep 'vmx|svm'

hyperkit - Recommended macOS driver
virtualbox - Recommended Windows driver
none - bare-metal execution on Linux, at the expense of system security and reliability

[root@vm-10-115-37-45 gadmin]# cat /etc/centos-release
CentOS Linux release 7.2.1511 (Core) 
[root@vm-10-115-37-45 gadmin]# uname -r
3.10.0-327.el7.x86_64
