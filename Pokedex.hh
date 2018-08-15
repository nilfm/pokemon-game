#ifndef POKEDEX_HH
#define POKEDEX_HH

#include "Includes.hh"
#include "Pokebase.hh"

class Pokedex {
private:
    std::unordered_map<std::string, Pokebase> pokedex;
    
public:
    /* Pre: addresses contains a filename that contains a sequence of filenames that contain every Pokemon's info */
    /* Post: Returns a full Pokedex with the info for every Pokemon */
    Pokedex(const std::string file_addresses);
    
    /* Pre: name contains a valid Pokemon name */
    /* Post: Returns the pokebase for the Pokemon that corresponds to the name given */
    Pokebase get_pokebase(const std::string& name) const; 
};

#endif
