CC = gcc
CFLAGS = -Wall -g -O2 -fPIC -I../../include

TARGET = libmywc.a
SRCS = mywc.c
OBJS = mywc.o

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean