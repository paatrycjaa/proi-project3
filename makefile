#PLIK MAKEFILE

CC = g++
CFLAGS = -std=c++11
TARGET = poly

$(TARGET): main.o shell.o point.o
	$(CC) main.o shell.o point.o -g -o $(TARGET)

main.o: main.cpp shell.h
	$(CC) $(CFLAGS) -c -g main.cpp

shell.o: shell.cpp listofpolyminoes.h polyminoe.h
	$(CC) $(CFLAGS) -c -g shell.cpp

point.o: point.cpp point.h 
	$(CC) $(CFLAGS) -c -g point.cpp

clean:
	rm -f *.o $(TARGET)
