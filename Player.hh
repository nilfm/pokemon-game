#ifndef PLAYER_HH
#define PLAYER_HH

#include "includes.hh"
#include "Pokemon.hh"
#include "Pokedex.hh"
#include "Pokebase.hh"
#include "Move.hh"
#include "Item.hh"

class Player {
private:
    const static int MAX_POKEMON = 6;
    std::vector<Pokemon> team;
    std::vector<Item> inventory;
    
public:
    //This class's member functions will ask user for input
    //use_item()
    //use_item();
    //switch_pokemon()
    //use_move()
};

#endif
