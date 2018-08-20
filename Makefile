CC = g++
OPTIONS = -std=c++11 -Wall -Wextra -Wpedantic -O2

all: main.o Type.o Move.o Pokemon.o Pokebase.o Pokedex.o Item.o Player.o Input.o Random.o Gamesave.o
	$(CC) $(OPTIONS) -o Pokegame.x main.o Type.o Move.o Pokemon.o Pokebase.o Pokedex.o Item.o Player.o Gamesave.o Input.o Random.o

Type.o: Type.cc Type.hh Includes.hh Random.cc Random.hh
	$(CC) $(OPTIONS) -c Type.cc

Move.o: Move.cc Type.cc Move.hh Type.hh Includes.hh Random.cc Random.hh
	$(CC) $(OPTIONS) -c Move.cc

Pokemon.o: Pokemon.cc Pokemon.hh Move.cc Move.hh Type.cc Type.hh Pokebase.cc Pokebase.hh Includes.hh Random.cc Random.hh
	$(CC) $(OPTIONS) -c Pokemon.cc

Pokebase.o: Pokebase.cc Pokebase.hh Move.cc Move.hh Type.cc Type.hh Includes.hh Random.cc Random.hh Player.cc Player.hh
	$(CC) $(OPTIONS) -c Pokebase.cc

Pokedex.o: Pokedex.cc Pokedex.hh Pokebase.cc Pokebase.hh Includes.hh Random.cc Random.hh
	$(CC) $(OPTIONS) -c Pokedex.cc

Item.o: Item.cc Item.hh Includes.hh Random.cc Random.hh
	$(CC) $(OPTIONS) -c Item.cc

Player.o: Player.cc Player.hh Pokemon.cc Pokemon.hh Pokebase.cc Pokebase.hh Pokedex.cc Pokedex.hh Item.cc Item.hh Move.cc Move.hh Includes.hh Random.cc Random.hh Gamesave.cc Gamesave.hh
	$(CC) $(OPTIONS) -c Player.cc

Gamesave.o: Gamesave.cc Gamesave.hh Includes.hh Pokemon.cc Pokemon.hh Item.cc Item.hh Move.cc Move.hh Pokedex.cc Pokedex.hh Pokebase.cc Pokebase.hh
	$(CC) $(OPTIONS) -c Gamesave.cc

Input.o: Input.cc Input.hh
	$(CC) $(OPTIONS) -c Input.cc

Random.o: Random.cc Random.hh 
	$(CC) $(OPTIONS) -c Random.cc

main.o: Player.cc Player.hh Pokemon.cc Pokemon.hh Pokebase.cc Pokebase.hh Pokedex.cc Pokedex.hh Item.cc Item.hh Move.cc Move.hh Includes.hh Random.cc Random.hh Type.cc Type.hh Input.cc Input.hh Random.hh
	$(CC) $(OPTIONS) -c main.cc

clean:
	rm -f *.o *.x
