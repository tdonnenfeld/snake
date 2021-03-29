all: snake

snake: main.o map.o matrix.o
	g++ main.o map.o matrix.o -o snake -lsfml-graphics -lsfml-window -lsfml-system

main.o:
	g++ -c main.cpp common.h map.h

map.o:
	g++ -c map.cpp common.h map.h matrix.h

matrix.o:
	g++ -c matrix.cpp matrix.h common.h

clean:
	rm *.o snake *.gch
