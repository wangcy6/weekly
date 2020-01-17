

# Android 开发环境

###  1 Ubuntu下全命令行搭建Android开发环境

Contents

- [安装 `JDK` 环境](https://qianngchn.github.io/wiki/8.html#安装-jdk-环境)
- [安装 `Android SDK`](https://qianngchn.github.io/wiki/8.html#安装-android-sdk)
- [安装 `Gradle`](https://qianngchn.github.io/wiki/8.html#安装-gradle)
- [编译 `Android` 应用](https://qianngchn.github.io/wiki/8.html#编译-android-应用)
- [安装 `Android Studio`](https://qianngchn.github.io/wiki/8.html#安装-android-studio)

安装 `Android SDK`



***

```powershell
sudo apt update && sudo apt install android-sdk
apt remove  android-sdk   --命令不起作用

# Export the Android SDK path 
export ANDROID_HOME=F:\sdk
export PATH=$PATH:$ANDROID_HOME/tools/bin
export PATH=$PATH:$ANDROID_HOME/platform-tools
android list sdk --all
F:\sdk\platform-tools;F:\sdk\tools\bin
```



安装 `Gradle`

使用`Ant`构建项目已经是过去式了，这里我们选用更加强悍和方便的构建工具`gradle`。

下载 `grdle` 二进制包

```
cd ~
wget https://services.gradle.org/distributions/gradle-2.12-bin.zip
```

释放到本地`Home`目录,创建名字为`gradle`的符号链接，符号连接的好处是方便版本更新，有了新的版本直接修改符号链接即可。

```
unzip gradle-2.12-bin.zip 
ln -s gradle-2.12 gradle
```

配置`gradle`环境变量并使其生效,编辑 `~/.profile` 文件增加下面内容

```
GRADLE_HOME=$HOME/gradle
export PATH=$PATH:$GRADLE_HOME/bin
```

保存后使环境变量使其生效

```
source ~/.profile
```

环境变量生效后你可以在终端敲入`gradle`命令并运行用以检测`gradle`是否安装成功。

```
gradle
```

如果安装配置的没有问题将会提示类似下面的信息

```
:help
Welcome to Gradle 2.12
To run a build, run gradle <task> ...
To see a list of available tasks, run gradle tasks
To see a list of command-line options, run gradle --help
BUILD SUCCESSFUL
```

编译 `Android` 应用

完成以上的环境配置，我们的一个`Android`下的基础构建环境就全部配置好了，接下来做的事情就是尝试使用`gradle` 编译一个`android` 应用出来验证我的编译环境是否`OK`,下载我写的一个`gadle demo`例子进行测试。

```
git clone https://github.com/examplecode/gradle_demo
cd gradle_demo/hello-apk-with-gradle
gradle build
```

一切顺利的话，编译完成后，你会在 `hello-apk-with-gradle/build/outputs/apk` 目录下找到编译好的`apk`包。至于如何整合到你自己的项目中去，只需要仿照例子给你的项目提供一个`build.gradle`脚本即可。

- `/home/AccountName/Android/Sdk`
- `/usr/lib/android-sdk`
- `/Library/Android/sdk/`
- `/Users/[USER]/Library/Android/sdk`



1.6 设置代理

 file -setting

1.7 Terminal



![image.png](https://i.loli.net/2020/01/17/JCHxn5tygW3OBpr.png)

### 2 adb命令

mumu

 myandrovm_vbox86.nemu

 <Forwarding name="ADB_PORT" proto="1" hostip="127.0.0.1" hostport="7555" guestport="5555"/>

```css
adb connect 127.0.0.1:7555
adb devices
adb shell pm list package -3 -f com.taou.maimai
Android Studio连接网易MuMu模拟器
1. AndroidStudio的命令行工具里面输入命令
    adb connect 127.0.0.1:7555
```