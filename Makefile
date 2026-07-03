CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude -Itests/unity

APP_TARGET = log-parser
TEST_TARGET = test_runner

SRC = src/log_entry.c src/log_loader.c
APP_SRC = $(SRC) src/main.c

TEST_SRC = $(SRC) \
           tests/test_runner.c \
           tests/test_log_entry.c \
           tests/unity/unity.c

all: app

app:
	$(CC) $(CFLAGS) $(APP_SRC) -o $(APP_TARGET)

test:
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_TARGET)

clean:
	rm -f $(APP_TARGET) $(TEST_TARGET)