CC = gcc

CFLAGS = -Wall -Wextra -pedantic

TARGET = sysinfo

SRCS = sysinfo.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET) install

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean install
