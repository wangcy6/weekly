



# 文件系统-知识地图



### 我的理解

小王：文件名就是文件系统呀？

小王：目录就是目录 怎么可能是文件呢？



### 第一性原理

- 为什么需要进行“格式化”呢

- 元信息数据是啥
- 文件系统对象是啥
- inode没有存储文件名，但是缓存目录文件名从哪来来，缓存数据不会自己凭空冒出来？
- ls -i 显示inode 就是 long 类型的编号 还有什么呀？
- Superblock  是啥东西？

### 索引



# 基础篇

## 文件系统



在 Linux 中一切皆文件。不仅普通的文件和目录，就连块设备、套接字、管道等，也都要通过统一的文件系统来管理。



Linux 下的文件系统主要可分为三大块：

一是上层的文件系统的系统调用，

二是虚拟文件系统 VFS(Virtual Filesystem Switch)，

三是挂载到 VFS 中的各实际文件系统



![1568019662577.jpg](https://upload-images.jianshu.io/upload_images/1837968-14fbf22dc1ac6cb1.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://pic3.zhimg.com/80/v2-212ca855ac2dad87983b23b6539e21ce_hd.jpg)

### 第一个问题：文件系统类型有哪些？

> 字符设备、块设备、网络设备



```shell
 df -h
Filesystem                Size  Used Avail Use% Mounted on
/dev/mapper/vg_root-root   19G  6.5G   12G  37% /
devtmpfs                  7.8G     0  7.8G   0% /dev
tmpfs                     7.8G     0  7.8G   0% /dev/shm
tmpfs                     7.8G  4.3G  3.6G  55% /run
tmpfs                     7.8G     0  7.8G   0% /sys/fs/cgroup
/dev/sda1                 190M  100M   77M  57% /boot
/dev/vda1                 493G  350M  467G   1% /app
tmpfs                     1.6G     0  1.6G   0% /run/user/0
tmpfs                     1.6G     0  1.6G   0% /run/user/888

tmpfs是最好的基于RAM的文件系统。是一种基于内存的文件系
/dev目录下的每一个文件都对应的是一个设备
proc文件系统为操作系统本身和应用程序之间的通信提供了一个安全的接口
https://blog.csdn.net/qq_27840681/article/details/77567094
```

.上层应用如何调用底层驱动？

## VFS



文件系统是如何运行的 

>那么文件系统是如何运行的呢？这与操作系统的文件数据有关。较新的操作系统的文件数据
>除了文件实际内容外， 通常含有非常多的属性，
>
>例如 Linux 操作系统的文件权限（rwx） 与文
>件属性（拥有者、群组、时间参数等） 。
>
> 文件系统通常会将这两部份的数据分别存放在不同
>的区块，权限与属性放置到 inode 中，
>
>至于实际数据则放置到 data block 区块中。 另外，还
>有一个超级区块 （superblock） 会记录整个文件系统的整体信息，包括 inode 与 block 的总
>量、使用量、剩余量等 

- 构成

VFS （virtual File System）

目录项、索引节点、逻辑块以及超级块，构成了 Linux 文件系统的四大基本要素。



目录项对象 (dentry object) 



> 目录项，简称为 dentry，用来记录文件的名字、索引节点指针以及与其他目录项的关联关系。
>
> 多个关联的目录项，就构成了文件系统的目录结构。
>
> 不过，不同于索引节点，目录项是由内核维护的一个内存数据结构，所以通常也被叫做目录项缓存。
>
> 一个目录文件包含了一组目录项，目录项是放在data block中的。(参考《Unix环境高级编程》Page87)



索引节点对象 (inode object)



> 索引节点，简称为 inode，用来记录文件的元数据，
>
> 比如 inode 编号、文件大小、访问权限、修改日期、数据的位置等。
>
> 索引节点和文件一一对应，它跟文件内容一样，都会被持久化存储到磁盘中。
>
> 所以记住，索引节点同样占用磁盘空间。



文件对象 (file object)：

​	数据块是记录文件真实内容的地方

在格式化时 block 的大小就固定了，且每个 block 都有编号，以方便 inode
的记录啦 



比较：

文件系统通常会将这两部份的数据分别存放在不同
的区块，权限与属性放置到 inode 中，至于实际数据则放置到 data block 区块中 



超级块对象 (superblock object)

会记录整个文件系统的整体信息，包括 inode 与 block 的总
量、使用量、剩余量等。 

> 磁盘在执行文件系统格式化时，会被分成三个存储区域，超级块、索引节点区和数据块区。其中，
>
> 超级块，存储整个文件系统的状态。
> 索引节点区，用来存储索引节点。
> 数据块区，则用来存储文件数据。





- 关系：

![image.png](https://upload-images.jianshu.io/upload_images/1837968-67064997f97bc05d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



![](https://www.ibm.com/developerworks/cn/linux/l-cn-hardandsymb-links/image004.jpg)



![](https://pic1.zhimg.com/80/v2-b5d3e0b7b1f2a1aecb89ed0c93ac907c_hd.jpg)

![](https://pic3.zhimg.com/80/v2-1bbe92018e1fb7bb11cc5b11e806c43a_hd.jpg)

![](http://www.opsers.org/wp-content/uploads/2011/04/inode_thumb.png)



### inode 结构

*inode* 是 UNIX 操作系统中的一种数据结构

 *inode* 指的是数据结构；而*索引编号*实际上是 inode 的标识编号



##### VFS 中的 inode 与 inode_operations 结构体



```c
struct inode { 
   ... 
   const struct inode_operations   *i_op; // 索引节点操作
   unsigned long           i_ino;      // 索引节点号
   atomic_t                i_count;    // 引用计数器
   unsigned int            i_nlink;    // 硬链接数目
   ... 
} 

struct inode_operations { 
   ... 
   int (*create) (struct inode *,struct dentry *,int, struct nameidata *); 
   int (*link) (struct dentry *,struct inode *,struct dentry *); 
   int (*unlink) (struct inode *,struct dentry *); 
   int (*symlink) (struct inode *,struct dentry *,const char *); 
   int (*mkdir) (struct inode *,struct dentry *,int); 
   int (*rmdir) (struct inode *,struct dentry *); 
   ... 
}


```



```c
struct ext4_inode { 
   ``... 
   ``__le32  i_atime;        // 文件内容最后一次访问时间
   ``__le32  i_ctime;        // inode 修改时间
   ``__le32  i_mtime;        // 文件内容最后一次修改时间
   ``__le16  i_links_count;  // 硬链接计数
   ``__le32  i_blocks_lo;    // Block 计数
   ``__le32  i_block[EXT4_N_BLOCKS];  // 指向具体的 block 
   ``... 
};
```

inode保存了文件系统中的一个**文件系统对象**（包括[文件](https://zh.wikipedia.org/wiki/计算机文件)、[目录](https://zh.wikipedia.org/wiki/目录_(文件系统))、[设备文件](https://zh.wikipedia.org/wiki/设备文件)、[socket](https://zh.wikipedia.org/wiki/Unix域套接字)、[管道](https://zh.wikipedia.org/wiki/管道_(Unix)), 等等）的元信息数据，**但不包括数据内容或者文件名**

- inode 编号

- 用来识别文件类型，以及用于 `stat C` 函数的模式信息

- 文件的链接数目

- 属主的 UID

- 属主的组 ID (GID)

- 文件的大小

- 文件所使用的磁盘块的实际数目

- 最近一次修改的时间

- 最近一次访问的时间

- 最近一次更改的时间

   都会被持久化存储到磁盘中。所以记住，索引节点同样占用磁盘空间。
   
   等等。



画外音：

通过 inode 找到数据快才是重点，这样数据库 可能存储在任何一个角落里



文件系统一开始就将 inode 与 block 规划好了，除非重新格式化 

### Superblock （超级区块） 

```
block 与 inode 的总量；

未使用与已使用的 inode / block 数量；

block 与 inode 的大小 （block 为 1, 2, 4K，inode 为 128Bytes 或 256Bytes） ；

filesystem 的挂载时间、最近一次写入数据的时间、最近一次检验磁盘 （fsck） 的时间
等文件系统的相关信息；

一个 val
id bit 数值，若此文件系统已被挂载，则 valid bit 为 0 ，若未被挂载，则 valid bit
为

dumpe2fs -h /dev/sda2

```

### 目录与文件 

> 文件名 存储在哪里?



当我们在 Linux 下的文件系统创建一个目录时(目录是文件)，文件系统会分配一个 inode 与**至少**一块 block
（根据文件数量有关系）

其中，inode 记录该目录的相关权限与属性，并可记录分配到的那块 block 号码；

而 block 则是记录在这个目录下的文件名与该文件名占用的 inode 号码数据 



- 知识点1  inode 本身并不记录文件名，文件名的记录
  是在目录的 block 当中 

![inode 本身并不记录文件名，文件名的记录
是在目录的 block 当中 ](https://upload-images.jianshu.io/upload_images/1837968-67064997f97bc05d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



- 如果我想要读取 /etc/passwd 这个文件时，
  系统是如何读取的呢？ 





# 工具篇

### ln

- 知识点：

  1. 目录是也是一个文件
  2. 不同文件名 可以使用相同inode
  3.  

  

- 使用场景

ln - make links between files

当我们需要在不同的目录，用到相同的文件时，我们不需要在每一个需要的目录下都放一个必须相同的文件，

我们只要在某个固定的目录，放上该文件，

然后在 其它的目录下用ln命令链接（link）它就可以，不必重复的占用磁盘空间。

- 基本用法



![ 硬链接](https://s3.51cto.com/wyfs02/M01/9C/5C/wKioL1lvUGjQ8TirAAAnGNq3aDs576.png)



![软连接](https://s5.51cto.com/wyfs02/M01/9C/5C/wKiom1lvUGjTXRJMAAAtjT6GldQ692.png)

画外音：

> 软连接就 c++指针， 2个对象
> 硬链接就是 c++的 引用 是一个对象
>
> 无论是软链接还是硬链接，文件都保持同步变化

```shell
 ln -s  turn.log  symbolic_link.log
 -s, --symbolic
              make symbolic links instead of hard links

ls  turn.log  hard_link.log

[root@vm-10-115-37-45 log]# ls -lri
total 8
30932995 -rw-r--r-- 2 root root 3482 Jul 19 10:08 turn.log
30933373 lrwxrwxrwx 1 root root    8 Sep  9 15:42 symbolic_link.log -> turn.log
30932995 -rw-r--r-- 2 root root 3482 Jul 19 10:08 hard_link.log（inode相同）
[root@vm-10-115-37-45 log]# 



```



###  stat

- 基本用法



stat - display file or file system status

stat log
  File: ‘log’
  Size: 4096            Blocks: 8          IO Block: 4096   directory
Device: fc01h/64513d    Inode: 30932994    Links: 2
Access: (0755/drwxr-xr-x)  Uid: (    0/    root)   Gid: (    0/    root)
Access: 2019-09-09 16:00:38.715192930 +0800
Modify: 2019-09-09 16:00:37.679198767 +0800
Change: 2019-09-09 16:00:37.679198767 +0800

- 使用细节
- 背后原理



### df

1 基本用法

2 使用细节

3 背后原理

### strace 跟踪进程中的系统调用

1 基本用法

2 使用细节

3 背后原理

# 动手实践



### 实验： 查看文件系统 缓存占用情况 



```
# 按下 c 按照缓存大小排序，按下 a 按照活跃对象数排序 

$ slabtop 
Active / Total Objects (% used)    : 277970 / 358914 (77.4%) 
Active / Total Slabs (% used)      : 12414 / 12414 (100.0%) 
Active / Total Caches (% used)     : 83 / 135 (61.5%) 
Active / Total Size (% used)       : 57816.88K / 73307.70K (78.9%) 
Minimum / Average / Maximum Object : 0.01K / 0.20K / 22.88K 

  OBJS ACTIVE  USE OBJ SIZE  SLABS OBJ/SLAB CACHE SIZE NAME 
69804  23094   0%    0.19K   3324       21     13296K dentry 
16380  15854   0%    0.59K   1260       13     10080K inode_cache 
58260  55397   0%    0.13K   1942       30      7768K kernfs_node_cache 
   485    413   0%    5.69K     97        5      3104K task_struct 
  1472   1397   0%    2.00K     92       16      2944K kmalloc-2048 
```



从这个结果你可以看到，在我的系统中，

目录项和索引节点占用了最多的 Slab 缓存。

不过它们占用的内存其实并不大，加起来也只有 23MB 左右。



创建文件消耗一个inode

```powershell
cp a b

df -i;df  
一个Inode对应一个文件
```

​	

###  实验 ：**硬链接不占用磁盘空间，软链接占用的空间只是存储路径所占用的极小空间。**


  ![](https://s1.51cto.com/wyfs02/M00/9C/5C/wKioL1lvTvryo42DAAAOvuFDmTM298.png)

![](https://s1.51cto.com/wyfs02/M01/9C/5C/wKioL1lvTvqiTbORAAAZIXyN4JU168.png)

![https://s1.51cto.com/wyfs02/M01/9C/5C/wKioL1lvT2XBfAylAAAVvciajlY492.png](https://s1.51cto.com/wyfs02/M01/9C/5C/wKioL1lvT2XBfAylAAAVvciajlY492.png)

![](https://s1.51cto.com/wyfs02/M00/9C/5C/wKiom1lvT5yjPmFAAAAZoX9y70M036.png)





/dev/sda2      2536000 703264 1832736   28% /

### 实验：文件的打开过程

### 实验 设备文件的类型



# 参考

https://wizardforcel.gitbooks.io/vbird-linux-basic-4e/content/59.html

https://www.cnblogs.com/xiaojiang1025/p/6363626.html