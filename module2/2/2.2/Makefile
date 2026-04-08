CC = gcc
CFLAGS = -Wall
TARGET = calculator
SRCS = main.c menu.c operations.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean