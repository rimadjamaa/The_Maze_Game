CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
LDFLAGS = -lSDL2

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
TARGET = build/maze_game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean


gcc -o myproject build/map.o build/main.o build/renderer.o -I./src/include -L./src/lib -lmingw32 -lSDL2main -lSDL2
gcc -Wall -Werror -Wextra -pedantic ./src/*.c -lm$(sdl2-confiig --cflags --libs) -SDL2_image -o image 
gcc -o myproject src/main.c -I./src/include -L./src/lib -lSDL2 -lSDL2main