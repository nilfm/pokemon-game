#include "Includes.hh"
#include "Type.hh"
#include "Move.hh"
#include "Pokedex.hh"
#include "Pokemon.hh"
#include "Pokebase.hh"
#include "Player.hh"
#include "Random.hh"
using std::unordered_map;
using std::vector;

int main() {
    srand(time(0));
    Type::initialize();
    Pokedex::initialize("addresses.txt");
    Pokemon poke(Pokedex::get_pokebase("Charmander"), 27);
    poke.print_stats();
    poke.level_up();
    poke.print_stats();
}
