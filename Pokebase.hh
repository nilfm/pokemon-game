#ifndef POKEBASE_HH
#define POKEBASE_HH

#include "includes.hh"
#include "Type.hh"
#include "Move.hh"

class Pokebase {
private:
    std::string name;
    Type type;
    int maxhp, attack, defense, spattack, spdefense, speed;
    int maxhp_level, attack_level, defense_level, spattack_level, spdefense_level, speed_level;
    
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
    /* Post: Returns the current maximum HP for this pokemon */
    int get_maxhp() const;
    
    /* Pre: True */
    /* Post: Returns the current Attack for this pokemon */
    int get_attack() const;
    
    /* Pre: True */
    /* Post: Returns the current Defense for this pokemon */
    int get_defense() const;
    
    /* Pre: True */
    /* Post: Returns the current Special Attack for this pokemon */
    int get_spattack() const;
    
    /* Pre: True */
    /* Post: Returns the current Special Defense for this pokemon */
    int get_spdefense() const;
    
    /* Pre: True */
    /* Post: Returns the current Speed for this pokemon */
    int get_speed() const;

    /* Pre: True */
    /* Post: Returns the current maximum HP per level for this pokemon */
    int get_maxhp_level() const;
    
    /* Pre: True */
    /* Post: Returns the current Attack per level for this pokemon */
    int get_attack_level() const;
    
    /* Pre: True */
    /* Post: Returns the current Defense per level for this pokemon */
    int get_defense_level() const;
    
    /* Pre: True */
    /* Post: Returns the current Special Attack per level for this pokemon */
    int get_spattack_level() const;
    
    /* Pre: True */
    /* Post: Returns the current Special Defense per level for this pokemon */
    int get_spdefense_level() const;
    
    /* Pre: True */
    /* Post: Returns the current Speed per level for this pokemon */
    int get_speed_level() const;
    
    /* Pre: True */
    /* Post: Returns the type of this pokemon */
    Type get_type() const;
    
    /* Pre: True */
    /* Post: Returns the whole moveset for this pokemon */
    std::vector<Move> get_moveset() const;
};

#endif
