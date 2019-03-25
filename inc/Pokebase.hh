#ifndef POKEBASE_HH
#define POKEBASE_HH

#include "Includes.hh"
#include "Type.hh"
#include "Move.hh"

class Pokebase {
private:
    std::string name;
    int level_evolution;
    std::string next_evolution;
    std::string type;
    Stats base_stats;
    Stats level_stats_min;
    Stats level_stats_max;
    
    std::map<int, std::vector<Move> > moveset;
    
public:
    //CONSTRUCTORS
    /* Pre: True */
    /* Post: Default constructor */
    Pokebase();

    /* Pre: address contains a valid address for the Pokemon information */
    /* Post: Returns a Pokebase from the address given */
    Pokebase(const std::string& address);
     
     
    //GETTERS
    /* Pre: True */
    /* Post: Returns the name of the Pokemon */
    std::string get_name() const;
     
    /* Pre: True */
    /* Post: Returns the level of evolution for this pokemon (-1 if it does not evolve) */
    int get_level_evolution() const;
    
    /* Pre: True */
    /* Post: Returns the name of the next evolution for this pokemon */
    std::string get_next_evolution() const; 
    
    /* Pre: True */
    /* Post: Returns the base stats for this pokemon */
    Stats get_base_stats() const;
    
    /* Pre: True */
    /* Post: Returns the minimum per level stats for this pokemon */
    Stats get_level_stats_min() const;

    /* Pre: True */
    /* Post: Returns the maximum per level stats for this pokemon */
    Stats get_level_stats_max() const;

    /* Pre: True */
    /* Post: Returns the type of this pokemon */
    std::string get_type() const;
    
    /* Pre: True */
    /* Post: Returns the whole moveset for this pokemon */
    std::map<int, std::vector<Move> > get_moveset() const;
    
    
    //OPERATORS
    bool operator<(const Pokebase& p2) const;
};

#endif
