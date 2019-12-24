c0702 : c0702.o
	g++ -g c0702.o -o c0702
c0702.o : c0702.cpp
.PHONY :
clean:
	rm c0702 c0702.o
