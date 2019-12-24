# Makefile  exe程序

CC=g++
#C 编译器的选项
CFLAGS=-Wall -O2 -g -I. 
# C++ 编译器的选项
CXXFLAGS=$CFLAGS
DEPS=effective-cpp-9.h
#OBJ += hellofunc.o

OBJS     = effective-cpp-9.o 
SRCS     = effective-cpp-9.cpp

#指明需要链接动态库 
#LIBVAR   = -lmytest
LIBVAR   =  
#动态库路径            
#LIBPATH  = -L./dynamiclib/libs 
LIBPATH  = 
 ##头文件路径
CPPFLAGS   = -I .


#编译制定文件
$(OBJS):$(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^
 
# Compiles each of the object files as separate targets 全部文件
%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# -o $@ -> Tells make to put the output in a file named after the target
# $^ 	-> all of the file names in $(OBJS) separated by a space
test: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIBVAR)

.PHONY: clean

# Target to clean files created during compilation
clean:
	rm -f *.o 

#有一些软件包一次完成四个步骤：
#$(CC) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) example.c   -o example

