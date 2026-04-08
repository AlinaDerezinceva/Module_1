CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -D_POSIX_C_SOURCE=200809L

TARGET = contacts
SRCS = main.c actions.c interface.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) contacts.dat

.PHONY: all clean