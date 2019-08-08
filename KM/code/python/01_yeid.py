def func():
    while True:
        print("before yield")
        x = yield
        print("after yield:",x)

g = func()
next(g) # 程序运行到yield并停在该处,等待下一个next
g.send(1) # 给yield发送值1,这个值被赋值给了x，并且打印出来,然后继续下一次循环停在yield处
g.send(2) # 给yield发送值2,这个值被赋值给了x，并且打印出来,然后继续下一次循环停在yield处
next(g) # 没有给x赋值，执行print语句，打印出None,继续循环停在yield处