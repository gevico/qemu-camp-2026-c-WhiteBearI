CC = gcc
CFLAGS = -Wall -g -O2 -fPIC -I../../include

TARGET = libmysed.a
SRCS = mysed.c
OBJS = mysed.o

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean