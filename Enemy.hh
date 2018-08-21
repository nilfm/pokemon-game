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
    
    
    //GETTERS
    /* Pre: True */
    /* Post: Returns the enemy's team */
    std::vector<Pokemon> get_team() const;
    
    /* Pre: True */
    /* Post: Returns a reference to the enemy's first Pokemon */
    Pokemon& get_first_pokemon();
    
    
    //SHOWERS
    /* Pre: True */
    /* Post: Displays a formatted list with the stats for the team */
    void show_team_stats() const;


    //ACTIONS
    /* Pre: True */
    /* Post: Returns int between 1 and 3 representing action choice. Can't return 2 if no Pokemon are alive to swap. */
    int action_choice() const;
    
    /* Pre: True */
    /* Post: Returns int between 1 and amount of moves for own representing action choice */
    int move_choice(const Pokemon& own, const Pokemon& other) const;
    
    /* Pre: either the second or third Pokemon are alive */
    /* Post: Returns int between 2 and 3 representing action choice. */
    int swap_choice() const;
    
    /* Pre: 1 <= i, j <= MAX_POKEMON, a fainted Pokemon isn't going to be first */
    /* Post: The Pokemon at positions i and j have been swapped */
    void swap_pokemon(int i, int j);
    
    
    //AUXILIARY
    /* Pre: trainers > 0 */
    /* Post: Returns a vector of 4 positions indicating how many Pokemon of each tier this enemy will have */
    std::vector<int> calculate_tiers(int trainer);
    
};

#endif
