CC = gcc
CFILES = $(wildcard src/*.c)
CFLAGS = -Iinclude -lpthread -rdynamic -g $(shell pkg-config --cflags glfw3) $(shell pkg-config --libs glfw3) -lGL

default: all
all:
	$(CC) $(CFILES) $(CFLAGS) -o krabbacraft