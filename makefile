.SILENT:
CC     = gcc
CFLAGS = -g -Wall
RAYLIB_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

BINDIR = ./bin
OBJDIR = $(BINDIR)/obj
LIBDIR = $(BINDIR)/lib

TARGET_RENDERER = $(BINDIR)/bindis
TARGET_CLIENT   = $(BINDIR)/client
TARGET_G        = $(BINDIR)/g-renderer

LIB_COMMON = $(LIBDIR)/libcommon.a

SOURCES_COMMON   = $(wildcard src/common/*.c)
SOURCES_RENDERER = $(wildcard src/renderer/*.c)
SOURCES_CLIENT   = $(wildcard src/client/*.c)

OBJS_COMMON   = $(SOURCES_COMMON:src/%.c=$(OBJDIR)/%.o)
OBJS_RENDERER = $(SOURCES_RENDERER:src/%.c=$(OBJDIR)/%.o)
OBJS_CLIENT   = $(SOURCES_CLIENT:src/%.c=$(OBJDIR)/%.o)

.PHONY: all graphical setup clean

all: setup $(LIB_COMMON) $(TARGET_RENDERER) $(TARGET_CLIENT)

graphical: setup $(LIB_COMMON)
	$(MAKE) -C src/g-renderer

setup:
	mkdir -p $(OBJDIR)/common
	mkdir -p $(OBJDIR)/renderer
	mkdir -p $(OBJDIR)/client
	mkdir -p $(OBJDIR)/g-renderer
	mkdir -p $(LIBDIR)

$(LIB_COMMON): $(OBJS_COMMON)
	ar rcs $@ $^

$(TARGET_RENDERER): $(OBJS_RENDERER) $(LIB_COMMON)
	$(CC) -o $@ $^

$(TARGET_CLIENT): $(OBJS_CLIENT) $(LIB_COMMON)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -Isrc -c $< -o $@

clean:
	rm -rf $(BINDIR)
