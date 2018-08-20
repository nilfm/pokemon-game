#ifndef ENEMY_HH
#define ENEMY_HH

#include "Includes.hh"
#include "Pokemon.hh"
#include "Pokedex.hh"
#include "Pokebase.hh"
#include "Move.hh"
#include "Item.hh"

class Enemy {
private:
    const static std::string tiers_address;
    const static std::string address_extension;
    const static std::vector<std::string> hp_items;
    const static std::vector<std::string> pp_items;
    const static std::vector<std::string> x_items;
    const static int MAX_POKEMON = 3;
    int trainer; //which trainer this enemy is
    std::vector<Pokemon> team;

    
public:
    //CONSTRUCTORS
    /* Pre: trainers > 0 */
    /* Post: Returns an enemy at the level required */
    Enemy(int trainers);
    
    
    //SHOWERS
    /* Pre: True */
    /* Post: Displays a formatted list with the stats for the team */
    void show_team_stats() const;

    
    //AUXILIARY
    /* Pre: trainers > 0 */
    /* Post: Returns a vector of 4 positions indicating how many Pokemon of each tier this enemy will have */
    std::vector<int> calculate_tiers(int trainer);
    
};

#endif
