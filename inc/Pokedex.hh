#ifndef POKEDEX_HH
#define POKEDEX_HH

#include "Includes.hh"
#include "Pokebase.hh"

class Pokedex {
private:
    static std::unordered_map<std::string, Pokebase> pokedex;
    
public:
    /* Pre: addresses contains a filename that contains a sequence of filenames that contain every Pokemon's info */
    /* Post: The object becomes a full Pokedex with the info for every Pokemon */
    static void initialize(const std::string file_addresses);
    
    /* Pre: name contains a valid Pokemon name */
    /* Post: Returns the pokebase for the Pokemon that corresponds to the name given */
    static Pokebase get_pokebase(const std::string& name); 
};

#endif
