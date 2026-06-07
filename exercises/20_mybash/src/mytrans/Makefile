CC = gcc
CFLAGS = -Wall -g -O2 -fPIC -I../../include

TARGET = libmytrans.a
SRCS = mytrans.c myhash.c
OBJS = mytrans.o myhash.o

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean