all: a.out

a.out: main.o particle.o sistem.o painter.o
	g++ main.o particle.o sistem.o painter.o -lfltk -lX11

main.o: main.cpp
	g++ -c main.cpp

particle.o: particle.cpp
	g++ -c particle.cpp

sistem.o: sistem.cpp
	g++ -c sistem.cpp

painet.o: painter.cpp
	g++ -c painter.cpp -lfltk -lX11


clear:
	rm *.o ./a.out