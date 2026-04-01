.SILENT:
CC     = gcc
CFLAGS = -g -Wall -I../../src
LIBS   = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

BINDIR = ../../bin
OBJDIR = $(BINDIR)/obj/g-renderer
LIBDIR = $(BINDIR)/lib

TARGET     = $(BINDIR)/g-renderer
LIB_COMMON = $(LIBDIR)/libcommon.a

LOCAL_SRCS = $(wildcard *.c)
OBJS       = $(patsubst %.c, $(OBJDIR)/%.o, $(LOCAL_SRCS))

all: setup $(TARGET)

setup:
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJS) $(LIB_COMMON)
	$(CC) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
