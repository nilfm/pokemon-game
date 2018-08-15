#include "Pokedex.hh"

Pokedex::Pokedex(const std::string file_addresses) {
    std::ifstream in(file_addresses);
    std::vector<std::string> addresses;
    std::string addr;
    while (in >> addr) addresses.push_back(addr);
    int size = addresses.size();
    for (int i = 0; i < size; i++) {
        Pokebase p(addresses[i]);
        std::string s = p.get_name();
        pokedex[s] = p;
    }
}

Pokebase Pokedex::get_pokebase(const std::string& name) const {
    std::unordered_map<std::string, Pokebase>::const_iterator it = pokedex.find(name);
    assert(it != pokedex.end());
    return it->second;
} 
