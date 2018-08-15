#ifndef POKEMON_HH
#define POKEMON_HH

#include "Includes.hh"
#include "Move.hh"
#include "Type.hh"
#include "Pokebase.hh"
#include "Pokedex.hh"

class Pokemon {
private:
    const static int MAX_LEVEL = 100;
    const static int MAX_XP = 55000;
    const static int MAX_MOVES = 4;
    int level_evolution;
    std::string next_evolution;
    Type type;
    std::string name;
    int xp, hp, level;
    Stats stats;
    Stats per_level_min;
    Stats per_level_max;
    Stats battle_stats;
    std::map<int, Move> moveset;
    std::vector<Move> moves;
    
public:
    /* Pre: True */
    /* Post: Default constructor */
    Pokemon();

    /* Pre: Pokebase is a valid base for a pokemon, level is such that 0 < level < 101 */
    /* Post: Returns an instance of the pokemon described in the pokebase, at the level given */
    Pokemon(const Pokebase& p, int level);
    
    //This is for evolving Pokemon and keeping movesets
    /* Pre: Pokebase is a valid base for a pokemon, level is such that 0 < level < 101 */
    /* Post: Returns an instance of the pokemon described in the pokebase, at the level given, with the moveset given */
    Pokemon(const Pokebase& p, int level, const std::vector<Move>& moves);
    
    /* Pre: name_evolution is a valid pokemon name, 0 < level < 101 */
    /* Post: The pokemon object becomes its evolution, at the level give, with the same moveset */
    void evolve(const std::string& name_evolution, int level, const Pokedex& pokedex);

    /* Pre: True */
    /* Post: Returns the current total XP for this pokemon */
    int get_xp() const;
    
    /* Pre: True */
    /* Post: Returns the current level for this pokemon */
    int get_level() const;
    
    /* Pre: True */
    /* Post: Returns the current HP for this pokemon */
    int get_hp() const;
    
    /* Pre: True */
    /* Post: Returns the evolution level for this pokemon (-1 if it does not evolve) */
    int get_level_evolution() const;
    
    /* Pre: True */
    /* Post: Returns the next evolutionary stage for this pokemon */
    std::string get_next_evolution() const;
    
    /* Pre: True */
    /* Post: Returns the current stats for this pokemon */
    Stats get_stats() const;

    /* Pre: True */
    /* Post: Returns the type of this pokemon */
    Type get_type() const;
    
    /* Pre: True */
    /* Post: Returns the name of this pokemon */
    std::string get_name() const;
    
    /* Pre: health contains a positive integer or -1 */
    /* Post: If health was -1, hp was restored to full. Otherwise, the pokemon restores health hp, without going over maxhp */
    void restore_health(int health);
};

#endif
