CC = gcc

CFLAGS = -Wall -Wextra -pedantic

TARGET = sysinfo

SRCS = sysinfo.c

OBJS = $(SRCS:.c=.o)

PREFIX = /usr/local/bin

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -m 755 $(TARGET) $(PREFIX)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean install
