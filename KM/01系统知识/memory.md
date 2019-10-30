







### 资料

  [Linux中的虚拟内存系统](https://app.yinxiang.com/shard/s39/nl/8226829/72805ed3-e659-4310-bf67-bad3d4dfea70)  

### 虚拟内存（概念）

- 术语

  ![image-20191029155741853](../images/201909/image-20191029155741853.png)

- 虚拟内存是真正的内存，而是模拟出来内存一样功能（不担心竞争）

![image-20191029155920627](../images/201909/image-20191029155920627.png)

![image-20191029144046878](../images/201909/image-20191029144046878.png)

 ![进程的角度](https://static001.geekbang.org/resource/image/af/83/afa4beefd380effefb0e54a8d9345c83.jpeg) 

  ![内核角度](https://static001.geekbang.org/resource/image/4e/9d/4ed91c744220d8b4298237d2ab2eda9d.jpeg) ![img](https://static001.geekbang.org/resource/image/7a/4c/7af58012466c7d006511a7e16143314c.jpeg) 

 ![img](https://static001.geekbang.org/resource/image/28/e8/2861968d1907bc314b82c34c221aace8.jpeg) 

 ![img](https://static001.geekbang.org/resource/image/2a/ce/2ad275ff8fdf6aafced4a7aeea4ca0ce.jpeg) 

 ![img](https://static001.geekbang.org/resource/image/52/54/527e5c861fd06c6eb61a761e4214ba54.jpeg) 

 ![img](https://static001.geekbang.org/resource/image/27/9a/274e22b3f5196a4c68bb6813fb643f9a.png) 

![image-20191029161649283](../images/201909/image-20191029161649283.png)

![image-20191029160324488](../images/201909/image-20191029160324488.png)

![image-20191029160456490](../images/201909/image-20191029160456490.png)



- 内存回收kswapd

![image-20191029161027376](../images/201909/image-20191029161027376.png)

- 内存分配



![image-20191029162139890](../images/201909/image-20191029162139890.png)

![image-20191029160941280](../images/201909/image-20191029160941280.png)

### 手动实验（指标）

 ![img](https://static001.geekbang.org/resource/image/8f/ed/8f477035fc4348a1f80bde3117a7dfed.png) 

 ![img](https://static001.geekbang.org/resource/image/d7/fe/d79cd017f0c90b84a36e70a3c5dccffe.png)



 ![img](https://static001.geekbang.org/resource/image/52/9b/52bb55fba133401889206d02c224769b.png)  

![image-20191029162958919](../images/201909/image-20191029162958919.png)

- 查看进程的内存布局

​    cat /proc/$pid/map

```
fishcried@kali:~$ pmap -x 4751
4751:   -bash
Address           Kbytes     RSS   Dirty Mode   Mapping
0000000000400000     916     716       0 r-x-- bash
......
00007fffaa366000     132      32      32 rw--- [ stack ]
00007fffaa3c5000       8       4       0 r-x-- [ anon ]
ffffffffff600000       4       0       0 r-x-- [ anon ]
---------------- ------ ------ ------
total kB           23560    6548    4684
```

| Address  | Kbytes | Rss                  | Dirty  | Mode Mapping |      |
| :------- | :----- | :------------------- | :----- | :----------- | :--- |
| 起始地址 | 大小   | 实际占用物理内存大小 | 脏页数 | 权限         | 名字 |

`pmap`命令读取了`/proc/pid/maps`和`/porc/pid/smaps`文件.可以直接查看以上两个文件.smaps的格式更为详细可读.





```
cat /proc/25282/status
VmRSS: 113612 kB 表示占用的物理内存
```





```shell
# 首先清理缓存

$ echo 3 > /proc/sys/vm/drop_caches

# 运行dd命令读取文件
$ dd if=/dev/sda1 of=/dev/null bs=1M count=1024
/dev/zero在类UNIX系统中是一个特殊的设备文件，当你读它的时候，它会提供无限的空字符（NULL, ASCII NUL, 0x00）
# 通过读取随机设备，生成一个 500MB 大小的文件 
$ dd if=/dev/urandom of=/tmp/file bs=1M count=500k


 strace -c dd if=/dev/sda1 of=/dev/null bs=1k count=5000k
```



- slabtop - display kernel slab cache information in real time

~~~shell
[root@vm-10-115-37-60 tmp]# slabtop 
 Active / Total Objects (% used)    : 544976 / 2097754 (26.0%)
 Active / Total Slabs (% used)      : 91582 / 91582 (100.0%)
 Active / Total Caches (% used)     : 76 / 99 (76.8%)
 Active / Total Size (% used)       : 179469.16K / 472463.97K (38.0%)
 Minimum / Average / Maximum Object : 0.01K / 0.22K / 8.00K

  OBJS ACTIVE  USE OBJ SIZE  SLABS OBJ/SLAB CACHE SIZE NAME                   
1648836 166695  10%    0.19K  78516       21    314064K dentry
136608 136571  99%    0.66K   5692       24     91072K shmem_inode_cache
 66963  31605  47%    0.10K   1717       39      6868K buffer_head
 31424  23189  73%    0.06K    491       64      1964K kmalloc-64
 21056   8266  39%    0.57K    752       28     12032K radix_tree_node
 18468  18468 100%    0.11K    513       36      2052K sysfs_dir_cache
 18020  10667  59%    0.05K    212       85       848K shared_policy_node
 15708  15011  95%    0.04K    154      102       616K ext4_extent_status
 15687  15687 100%    0.58K    581       27      9296K inode_cache
 11648  11648 100%    0.03K     91      128       364K jbd2_revoke_record_s
 11322  10762  95%    0.08K    222       51       888K selinux_inode_security
  9139   8478  92%    0.21K    247       37      1976K vm_area_struct
  8463   7481  88%    1.02K    273       31      8736K ext4_inode_cache
  7350   7181  97%    0.09K    175       42       700K kmalloc-96
  7168   7168 100%    0.01K     14      512        56K kmalloc-8
  6976   6976 100%    0.06K    109       64       436K anon_vma
  5376   5376 100%    0.02K     21      256        84K kmalloc-16
  4512   3491  77%    0.12K    141       32       564K kmalloc-128
  4170   4170 100%    0.13K    139       30       556K ext4_groupinfo_4k
  3744   2733  72%    0.25K    117       32       936K kmalloc-256
  3712   3712 100%    0.06K     58       64       232K ext4_free_data
  3549   3265  91%    0.19K    169       21       676K kmalloc-192
  3072   3072 100%    0.50K     96       32      1536K kmalloc-512
  2700   2700 100%    0.11K     75       36       300K jbd2_journal_head
  2688   2688 100%    0.03K     21      128        84K kmalloc-32
  2409   2409 100%    0.05K     33       73       132K uhci_urb_priv
~~~





- perf - Performance analysis tools for Linux



### 参考

-  https://www.cnblogs.com/kerrycode/p/10383328.html 