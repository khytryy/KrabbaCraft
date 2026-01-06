CC = gcc

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, build/%.o, $(SRC))

CFLAGS := -Iinclude -g $(shell pkg-config --cflags glfw3)
LDFLAGS := $(shell pkg-config --libs glfw3) -lGL -lpthread -rdynamic -lm

TARGET := krabbacraft

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

# Compile src/foo.c → build/foo.o
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build/ exists
build:
	mkdir -p build

clean:
	rm -rf build $(TARGET)
