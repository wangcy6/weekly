# Windows下nodeppt安装

### 1. 下载官方Nodejs的版本

nodeppt可能是最好的网页ppt, 下载官方的nodejs，下载官方的安装包之后，可以将安装路径加入系统环境变量，我的安装路径为:
`D:\Program Files\nodejs`
也可以下载官方的.exe版本，将.exe文件所在路径写入系统环境变量。

> [下载链接](https://nodejs.org/en/)

------

### 2. 下载npm代码

下载npm代码，并把代码解压到`D:\Program Files\nodejs`中，

解压后的路径例如：`D:\Program Files\nodejs\npm-3.3.12`,从命令行进入该路径下，执行如下命令：

```
D:\Program Files\nodejs\npm-3.3.12\node cli.js install -gf
```

> node cli.js install npm -gf 
>
> 可以安装最新版的NPMnode cli.js install [npm@1.0.105](mailto:npm@1.0.105) -gf 可以安装指定版本的NPM

NPM安装完成后，将`D:\Program Files\nodejs\node_modules`加入系统环境变量中。

------

### 3. 安装express

```
npm install express -g
```

> 安装最新版expressnpm install [express@2.5.0](mailto:express@2.5.0) 安装指定版本express

```
npm remove express -g
```

> 删除express

------

### 4. nodeppt安装

安装命令如下

```
npm install -g nodeppt
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