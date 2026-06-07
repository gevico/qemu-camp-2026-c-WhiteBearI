CC = gcc
CFLAGS = -Wall -g -O2

TARGET = 19_mytrans
LIBRARY = libmytrans.a
SRCS = 19_mytrans.c mytrans.c myhash.c
OBJS = 19_mytrans.o mytrans.o myhash.o

all: $(TARGET) $(LIBRARY)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(LIBRARY): mytrans.o myhash.o
	ar rcs $@ mytrans.o myhash.o

19_mytrans.o: 19_mytrans.c myhash.h
	$(CC) $(CFLAGS) -c 19_mytrans.c -o 19_mytrans.o

mytrans.o: mytrans.c myhash.h
	$(CC) $(CFLAGS) -c mytrans.c -o mytrans.o

myhash.o: myhash.c myhash.h
	$(CC) $(CFLAGS) -c myhash.c -o myhash.o

clean:
	rm -f $(OBJS) $(TARGET) $(LIBRARY)

.PHONY: all clean
