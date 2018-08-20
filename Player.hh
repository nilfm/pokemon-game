#ifndef PLAYER_HH
#define PLAYER_HH

#include "Includes.hh"
#include "Gamesave.hh"
#include "Pokemon.hh"
#include "Pokedex.hh"
#include "Pokebase.hh"
#include "Move.hh"
#include "Item.hh"

class Player {
private:
    const static int MAX_POKEMON = 6;
    std::string name;
    int money, trainers;
    std::vector<Pokemon> team;
    std::map<Item, int> inventory;
    
public:
    /* Pre: True */
    /* Post: Default constructor */
    Player();
    
    /* Pre: True */
    /* Post: New game constructor */
    Player(const std::string& name);

    /* Pre: True */
    /* Post: If gamesave is empty, makes new player. Else, loads up the player on the gamesave */
    Player(const Gamesave& gamesave);

    /* Pre: p is a valid Pokemon, i is a valid Item */
    /* Post: The item has been used on the Pokemon */
    void use_item(Pokemon& p, const Item& i);

    /* Pre: True */
    /* Post: Asks user for input and returns a starting team of Pokemon */
    std::vector<Pokemon> choose_starters() const;
    
    /* Pre: True */
    /* Post: Returns the player's name */
    std::string get_name() const;
    
    /* Pre: True */
    /* Post: Returns the player's money */
    int get_money() const;
    
    /* Pre: True */
    /* Post: Returns the player's amount of trainers beaten */
    int get_trainers() const;
    
    /* Pre: True */
    /* Post: Returns the player's team */
    std::vector<Pokemon> get_team() const;
    
    /* Pre: True */
    /* Post: Returns the player's inventory */
    std::map<Item, int> get_inventory() const;
    
    //switch_pokemon() BELONGS TO COMBAT CLASS MAYBE?
    //use_move() ALSO BELONGS TO COMBAT CLASS?
    //maybe by building up the main it'll be clearer which functions go here
};

#endif
