#include "includes.hh"
#include "Pokedex.hh"

Pokedex::Pokedex(const std::vector<std::string>& addresses) {
    int size = addresses.size();
    for (int i = 0; i < size; i++) {
        Pokebase p(addresses[i]);
        std::string s = p.get_name();
        pokedex[s] = p;
    }
}

Pokebase Pokedex::get_pokebase(const std::string& name) {
    std::unordered_map<std::string, Pokebase>::iterator it = pokedex.find(name);
    assert(it != pokedex.end());
    return it->second;
} 
