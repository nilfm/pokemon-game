#ifndef POKEBASE_HH
#define POKEBASE_HH

#include "includes.hh"
#include "Type.hh"
#include "Move.hh"

class Pokebase {
private:
    std::string name;
    Type type;
    Stats base_stats;
    Stats level_stats;
    
    std::map<int, Move> moveset;
    
public:
    /* Pre: True */
    /* Post: Default constructor */
    Pokebase();

    /* Pre: address contains a valid address for the Pokemon information */
    /* Post: Returns a Pokebase from the address given */
    Pokebase(const std::string& address);
     
    /* Pre: True */
    /* Post: Returns the name of the Pokemon */
    std::string get_name() const;
     
    /* Pre: True */
    /* Post: Returns the base stats for this pokemon */
    Stats get_base_stats() const;
    
    /* Pre: True */
    /* Post: Returns the per level stats for this pokemon */
    Stats get_level_stats() const;

    /* Pre: True */
    /* Post: Returns the type of this pokemon */
    Type get_type() const;
    
    /* Pre: True */
    /* Post: Returns the whole moveset for this pokemon */
    std::map<int, Move> get_moveset() const;
};

#endif
