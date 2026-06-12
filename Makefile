CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

TARGET = app

all:
	gcc $(CFLAGS) src/*.c -o $(TARGET)

clean:
	rm -f $(TARGET)