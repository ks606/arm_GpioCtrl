CC=arm-linux-gnueabihf-g++

all: mgpio

mgpio: main.o GpioCtrl.o
	$(CC) main.o GpioCtrl.o -o mgpio

main.o: main.cpp
	$(CC) -c main.cpp

GpioCtrl.o: GpioCtrl.cpp
	$(CC) -c GpioCtrl.cpp

clean:
	rm *.o mgpio