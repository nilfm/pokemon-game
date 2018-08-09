#ifndef POKEBASE_HH
#define POKEBASE_HH

#include "includes.hh"
#include "Move.hh"

class Pokebase {
private:
	std::string name;
	int maxhp, attack, defense, spattack, spdefense, speed;
	int maxhp_level, attack_level, defense_level, spattack_level, spdefense_level, speed_level;
	
	std::map<int, Move> moveset;
	
public:
	/* Pre: address contains a valid address for the Pokemon information */
	/* Post: Returns a Pokebase from the address given */
	 Pokebase(const std::string& address);
	 
	 /* Pre: True */
	 /* Post: Returns the name of the Pokemon */
	 std::string get_name() const;
};

#endif
