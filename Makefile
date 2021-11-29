# Made by Gabriel Lüders
#   GRR20190172 

# Variaveis
CFLAGS = -Wall -std=c99
LDLIBS = -lallegro -lallegro_font -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_image -lm
CC = gcc 
OBJ = main.o game.o input.o display.o utils.o map.o sprite.o player.o object.o collision.o hud.o animation.o audio.o


# regra default e ligação
all: boulderdash

boulderdash: $(OBJ)
	$(CC) -o boulderdash $(OBJ) $(LDLIBS)

# Regras de compilação

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

game.o: game.c
	$(CC) -c game.c $(CFLAGS)

input.o: input.c
	$(CC) -c input.c $(CFLAGS)

display.o: display.c
	$(CC) -c display.c $(CFLAGS)

utils.o: utils.c
	$(CC) -c utils.c $(CFLAGS)

map.o: map.c
	$(CC) -c map.c $(CFLAGS)	

sprite.o: sprite.c
	$(CC) -c sprite.c $(CFLAGS)

player.o: player.c
	$(CC) -c player.c $(CFLAGS)

object.o: object.c
	$(CC) -c object.c $(CFLAGS)

collision.o: collision.c
	$(CC) -c collision.c $(CFLAGS)

hud.o: hud.c
	$(CC) -c hud.c $(CFLAGS)

animation.o: animation.c
	$(CC) -c animation.c $(CFLAGS)

audio.o: audio.c
	$(CC) -c audio.c $(CFLAGS)

# Regras de limpeza

run: all
	./boulderdash

valgrindFull: all
	valgrind --leak-check=full ./boulderdash

valgrind: all
	valgrind ./boulderdash

clean: 
	-rm -f *.o

purge: clean
	-rm -f boulderdash