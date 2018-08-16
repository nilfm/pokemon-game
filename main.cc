#include "Includes.hh"
#include "Type.hh"
#include "Move.hh"
#include "Pokedex.hh"
#include "Pokemon.hh"
#include "Pokebase.hh"
#include "Player.hh"
#include "Random.hh"

int main() {
    //Things to initialize
    srand(time(0));
    Type::initialize();
    Pokedex::initialize("addresses.txt");
    std::map<std::string, Item> items = Item::initialize_items("Pokedata/items.txt");
    
    Pokemon poke(Pokedex::get_pokebase("Charmander"), 27);
    poke.print_stats();
    poke.level_up();
    poke.print_stats();
}
