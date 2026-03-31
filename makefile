.SILENT:
CC = gcc
FLAGS = -g 

BINDIR = ./bin

TARGET_RENDERER = $(BINDIR)/bindis
TARGET_CLIENT = $(BINDIR)/client

SOURCES_RENDERER = $(wildcard src/renderer/*.c)
SOURCES_CLIENT = $(wildcard src/client/*.c)

OBJS_RENDERER = $(SOURCES_RENDERER:.c=.o)
OBJS_CLIENT = $(SOURCES_CLIENT:.c=.o)


all : setup $(TARGET_RENDERER) $(TARGET_CLIENT)

setup:
	mkdir -p bin


$(TARGET_RENDERER): $(SOURCES_RENDERER)
	$(CC) -o $@ $^

$(TARGET_CLIENT): $(SOURCES_CLIENT)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean : 
	rm -rf bin/*
