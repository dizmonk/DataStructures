llcp: llcpImp.o Assign06P1B.o
	g++ llcpImp.o Assign06P1B.o -o a6p1B
llcpImp.o: llcpImp.cpp llcpInt.h
	g++ -Wall -ansi -pedantic -std=c++11 -c llcpImp.cpp
Assign06P1B.o: Assign06P1B.cpp llcpInt.h
	g++ -Wall -ansi -pedantic -std=c++11 -c Assign06P1B.cpp

go:
	./a6p1B
gogo:
	./a6p1B > a6p1Btest.out

clean:
	@rm -rf llcpImp.o Assign06P1B.o
cleanall:
	@rm -rf llcpImp.o Assign06P1B.o a6p1B
