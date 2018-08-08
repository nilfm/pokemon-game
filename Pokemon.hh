#ifndef POKEMON_HH
#define POKEMON_HH

#include "includes.hh"
#include "Move.hh"

class Pokemon {
private:
	static int MAX_LEVEL = 100;
	static int MAX_XP = 55000;
	static int MAX_MOVES = 4;
	int xp, level, hp, attack, defense, spattack, spdefense, speed;
	
	std::vector<Move> moves;
	
public:
	/* Pre: TODO */
	/* Post: TODO */
	int get_xp();
	
	/* Pre: TODO */
	/* Post: TODO */
	int get_level();
	
	/* Pre: TODO */
	/* Post: TODO */
	int get_hp();
	
	/* Pre: TODO */
	/* Post: TODO */
	int get_attack();
	
	/* Pre: TODO */
	/* Post: TODO */
	int get_defense();
	
	/* Pre: TODO */
	/* Post: TODO */
	int get_spattack();
	
	/* Pre: TODO */
	/* Post: TODO */
	int get_spdefense();
	
	/* Pre: TODO */
	/* Post: TODO */
	int get_speed();
};

#endif
