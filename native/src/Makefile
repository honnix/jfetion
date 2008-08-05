CC=gcc
LD=g++

CFLAGS=-ggdb -Wall -I/opt/jdk/include -I/opt/jdk/include/linux -I../include
LDFLAGS=-shared -Wall -fpic ../lib/libfetion_32.a -lpthread -lcurl

all: libjfetion.so

libjfetion.so: FetionImpl.o
	$(LD) -o libjfetion.so FetionImpl.o $(LDFLAGS)

FetionImpl.o: FetionImpl.c FetionImpl.h FetionHelper.h
	$(CC) $(CFLAGS) -c -o FetionImpl.o FetionImpl.c

clean:
	rm -rf libjfetion.so *.o TAGS

etags:
	find ./ -name '*.[hc]' | xargs etags

.PHONY: all clean etags
