CPP = g++ -c 
GPP = g++ -g
OBJ = c0302.o

c0302main:c0302.o
	$(GPP) c0302.o -o c0302main

c0302.o : 
	$(CPP) c0302.cpp -o c0302.o

.PHONY:clean
clean:
	rm c0302main $(OBJ)
