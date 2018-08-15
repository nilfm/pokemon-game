#ifndef POKEDEX_HH
#define POKEDEX_HH

#include "Includes.hh"
#include "Pokebase.hh"

class Pokedex {
private:
    std::unordered_map<std::string, Pokebase> pokedex;
    
public:
    /* Pre: addresses contains a sequence of strings for the files that contain every Pokemon's info */
    /* Post: Returns a full Pokedex with the info for every Pokemon */
    Pokedex(const std::vector<std::string>& addresses);
    
    /* Pre: name contains a valid Pokemon name */
    /* Post: Returns the pokebase for the Pokemon that corresponds to the name given */
    Pokebase get_pokebase(const std::string& name) const; 
};

#endif
