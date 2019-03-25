CC = g++
OPTIONS = -std=c++11 -Wall -Wextra -Wpedantic -O2

all: obj/main.o obj/Type.o obj/Move.o obj/Pokemon.o obj/Pokebase.o obj/Pokedex.o obj/Item.o obj/Player.o obj/Input.o obj/Random.o obj/Combat.o src/Cleaner.cc
	$(CC) $(OPTIONS) -o Pokegame obj/main.o obj/Type.o obj/Move.o obj/Pokemon.o obj/Pokebase.o obj/Pokedex.o obj/Item.o obj/Player.o obj/Input.o obj/Random.o obj/Combat.o
	$(CC) $(OPTIONS) -o Cleaner src/Cleaner.cc

obj/Type.o: src/Type.cc inc/Type.hh inc/Includes.hh src/Random.cc inc/Random.hh
	$(CC) $(OPTIONS) -c src/Type.cc -o obj/Type.o

obj/Move.o: src/Move.cc src/Type.cc inc/Move.hh inc/Type.hh inc/Includes.hh src/Random.cc inc/Random.hh
	$(CC) $(OPTIONS) -c src/Move.cc -o obj/Move.o

obj/Pokemon.o: src/Pokemon.cc inc/Pokemon.hh src/Move.cc inc/Move.hh src/Type.cc inc/Type.hh src/Pokebase.cc inc/Pokebase.hh inc/Includes.hh src/Random.cc inc/Random.hh
	$(CC) $(OPTIONS) -c src/Pokemon.cc -o obj/Pokemon.o

obj/Pokebase.o: src/Pokebase.cc inc/Pokebase.hh src/Move.cc inc/Move.hh src/Type.cc inc/Type.hh inc/Includes.hh src/Random.cc inc/Random.hh src/Player.cc inc/Player.hh
	$(CC) $(OPTIONS) -c src/Pokebase.cc -o obj/Pokebase.o

obj/Pokedex.o: src/Pokedex.cc inc/Pokedex.hh src/Pokebase.cc inc/Pokebase.hh inc/Includes.hh src/Random.cc inc/Random.hh
	$(CC) $(OPTIONS) -c src/Pokedex.cc -o obj/Pokedex.o

obj/Item.o: src/Item.cc inc/Item.hh inc/Includes.hh src/Random.cc inc/Random.hh
	$(CC) $(OPTIONS) -c src/Item.cc -o obj/Item.o

obj/Player.o: src/Player.cc inc/Player.hh src/Pokemon.cc inc/Pokemon.hh src/Pokebase.cc inc/Pokebase.hh src/Pokedex.cc inc/Pokedex.hh src/Item.cc inc/Item.hh src/Move.cc inc/Move.hh inc/Includes.hh src/Random.cc inc/Random.hh
	$(CC) $(OPTIONS) -c src/Player.cc -o obj/Player.o

obj/Input.o: src/Input.cc inc/Input.hh
	$(CC) $(OPTIONS) -c src/Input.cc -o obj/Input.o

obj/Random.o: src/Random.cc inc/Random.hh 
	$(CC) $(OPTIONS) -c src/Random.cc -o obj/Random.o

obj/Combat.o: src/Combat.cc inc/Combat.hh inc/Includes.hh src/Player.cc inc/Player.hh src/Pokemon.cc inc/Pokemon.hh src/Move.cc inc/Move.hh src/Random.cc inc/Random.hh
	$(CC) $(OPTIONS) -c src/Combat.cc -o obj/Combat.o

obj/main.o: src/main.cc src/Player.cc inc/Player.hh src/Pokemon.cc inc/Pokemon.hh src/Pokebase.cc inc/Pokebase.hh src/Pokedex.cc inc/Pokedex.hh src/Item.cc inc/Item.hh src/Move.cc inc/Move.hh inc/Includes.hh src/Random.cc inc/Random.hh src/Type.cc inc/Type.hh src/Input.cc inc/Input.hh inc/Random.hh
	$(CC) $(OPTIONS) -c src/main.cc -o obj/main.o

clean:
	rm -f obj/*.o Pokegame Cleaner
