.SILENT:
CC = gcc
CFLAGS = -g -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
BINDIR = ./bin
TARGET = $(BINDIR)/g-renderer
SOURCES = $(wildcard ./*.c) ../renderer/user.c

all: setup $(TARGET)

setup:
	mkdir -p $(BINDIR)

$(TARGET): $(SOURCES)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(BINDIR)
