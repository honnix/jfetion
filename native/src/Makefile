CC=gcc
LD=g++

CFLAGS=-Wall -I/opt/jdk/include -I/opt/jdk/include/linux -I../include
LDFLAGS=-shared -Wall ../lib/libfetion_32.a -lpthread -lcurl

all: libjfetion.so

libjfetion.so: FetionImpl.o
	$(LD) -o libjfetion.so FetionImpl.o $(LDFLAGS)

FetionImpl.o:
	$(CC) $(CFLAGS) -c -o FetionImpl.o FetionImpl.c

clean:
	rm -rf libjfetion.so *.o

.PHONY: all clean