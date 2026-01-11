CC = gcc

SRC := $(shell find src -name "*.c")
OBJ := $(patsubst src/%.c, build/%.o, $(SRC))

CFLAGS := -Iinclude -g $(shell pkg-config --cflags glfw3) $(shell pkg-config --cflags cglm)
LDFLAGS := $(shell pkg-config --libs glfw3) -lGL -lpthread -rdynamic -lm $(shell pkg-config --libs cglm) -llua -ldl

TARGET := krabbacraft

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)
