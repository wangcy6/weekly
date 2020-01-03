# Windows下nodeppt安装

### 1. 下载官方Nodejs的版本

nodeppt可能是最好的网页ppt, 下载官方的nodejs，

- 下载官方的安装包之后，可以将安装路径加入系统环境变量（手工）

我的安装路径为:
path=D:\local\nodejs\

- 也可以下载官方的.exe版本，将.exe文件所在路径写入系统环境变量（自动安装路径）

> [下载链接 ](https://nodejs.org/en/) [node-v13.5.0-x64.msi](https://nodejs.org/dist/v13.5.0/node-v13.5.0-x64.msi)

- [python](https://www.python.org/downloads/release/python-381/)  

  path =D:\local\python

------

### 2. 下载npm代码

npm是nodejs的官方包管理

~~~powershell
npm update npm -g
npm -v
6.13.4
~~~



- 修改镜像源

```powershell
npm config get registry
https://registry.npmjs.org/ --默认
--临时指定
npm --registry https://registry.npm.taobao.org info underscore
--长久指定
npm config set registry https://registry.npm.taobao.org 
```



------

### 3. 安装express

```
npm install express -g
```

```
npm remove express -g
```

------

### 4. nodeppt安装

https://github.com/ksky521/nodeppt

安装命令如下

```python

npm install -g nodeppt 
npm install -g nodeppt --force
nodeppt  -v   (检查下是否下载成功)
2.1.8
set-ExecutionPolicy RemoteSigned

```

shell使用

```
nodeppt start -h
```

获取帮助

```
nodeppt start -p port
nodeppt start -p 8090 -d path//ppts
```

绑定端口

```
nodeppt start -p 8080 -d path//ppts -H 127.0.0.1
```

绑定host，默认绑定0.0.0.0

https://github.com/winterZhao/nodeppt

~~~shell
 Examples:

   # create a new slide with an official template
   $ nodeppt new slide.md

   # create a new slide straight from a github template
   $ nodeppt new slide.md -t username/repo

   # start local sever show slide
   $ nodeppt serve slide.md

   # to build a slide
   $ nodeppt build slide.md
~~~

