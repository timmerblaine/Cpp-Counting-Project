driver: main.o usage.o
	g++6 -o driver main.o usage.o
main.o: main.cpp usage.h
	g++6 -c main.cpp
usage.o: usage.cpp usage.h
	g++6 -c usage.cpp

clean:
	rm *.o driver
