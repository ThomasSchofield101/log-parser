CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

TARGET = app

all:
	@echo "No build configured yet"

clean:
	rm -f $(TARGET)