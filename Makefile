CC = g++
OPTIONS = -std=c++11 -Wall -Wextra -Wpedantic -O2

Type.o: Type.cc Type.hh includes.hh
	$(CC) $(OPTIONS) -c Type.cc

Move.o: Move.cc Type.cc Move.hh Type.hh includes.hh
	$(CC) $(OPTIONS) -c Move.cc

Input.o: Input.cc Input.hh includes.hh
	$(CC) $(OPTIONS) -c Input.cc

Pokemon.o: Pokemon.cc Pokemon.hh Move.cc Move.hh Type.cc Type.hh Pokebase.cc Pokebase.hh includes.hh
	$(CC) $(OPTIONS) -c Pokemon.cc

Pokebase.o: Pokebase.cc Pokebase.hh Move.cc Move.hh Type.cc Type.hh includes.hh
	$(CC) $(OPTIONS) -c Pokebase.cc

Pokedex.o: Pokedex.cc Pokedex.hh Pokebase.cc Pokebase.hh includes.hh
	$(CC) $(OPTIONS) -c Pokedex.cc

Item.o: Item.cc Item.hh includes.hh
	$(CC) $(OPTIONS) -c Item.cc

Player.o: Player.cc Player.hh Pokemon.cc Pokemon.hh Pokebase.cc Pokebase.hh Pokedex.cc Pokedex.hh Item.cc Item.hh Move.cc Move.hh includes.hh
	$(CC) $(OPTIONS) -c Player.cc

clean:
	rm -f *.o *.x
