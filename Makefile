CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude -Itests/unity

TARGET = app

all:
	$(CC) $(CFLAGS) src/*.c -o $(TARGET)

clean:
	rm -f $(TARGET)