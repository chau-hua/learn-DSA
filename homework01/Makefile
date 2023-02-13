TARGET = student_menu

SOURCES = student_menu.c

OBJECTS = $(SOURCES:.c=.o)

CC = gcc

CFLAGS = -Wall -std=c11 -g

LDFLAGS =

.PHONY:

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
