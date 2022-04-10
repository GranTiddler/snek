output: main.o
	echo "linking"
	g++ main.o -o snek -lsfml-graphics -lsfml-window -lsfml-system
	echo "running"
	./snek


main.o: main.cpp
	echo "compiling main"
	g++ -c main.cpp

clean:
	rm *.o


target: dependencies
	action