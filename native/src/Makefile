CC=gcc
LD=g++

OS=$(shell uname)

ifeq ($(OS), Darwin)
	CFLAGS=-DDEBUG -arch i386 -arch ppc -ggdb -Wall -I/System/Library/Frameworks/JavaVM.framework/Versions/Current/Headers/ -I../include
	LDFLAGS=-dynamiclib -arch i386 -arch ppc -Wall -fpic ../lib/libfetion_mac.a -lpthread -lcurl
	TARGET=libjfetion.dylib
else
	CFLAGS=-DDEBUG -ggdb -Wall -I/opt/jdk/include -I/opt/jdk/include/linux -I../include
	LDFLAGS=-shared -Wall -fpic ../lib/libfetion_32.a -lpthread -lcurl
	TARGET=libjfetion.so
endif

all: $(TARGET)

$(TARGET): FetionImpl.o
	$(LD) -o $(TARGET) FetionImpl.o $(LDFLAGS)

FetionImpl.o: FetionImpl.c FetionImpl.h FetionHelper.h
	$(CC) $(CFLAGS) -c -o FetionImpl.o FetionImpl.c

clean:
	rm -rf $(TARGET) *.o TAGS

etags:
	find ./ -name '*.[hc]' | xargs etags

.PHONY: all clean etags
