#ifndef PLAYER_HH
#define PLAYER_HH

#include "Includes.hh"
#include "Pokemon.hh"
#include "Pokedex.hh"
#include "Pokebase.hh"
#include "Move.hh"
#include "Item.hh"

class Player {
private:
    const static int MAX_POKEMON = 6;
    std::vector<Pokemon> team;
    std::map<Item, int> inventory;
    
public:
    /* Pre: p is a valid Pokemon, i is a valid Item */
    /* Post: The item has been used on the Pokemon */
    void use_item(Pokemon& p, const Item& i);
    //switch_pokemon() BELONGS TO COMBAT CLASS MAYBE?
    //use_move() ALSO BELONGS TO COMBAT CLASS?
    //maybe by building up the main it'll be clearer which functions go here
};

#endif
