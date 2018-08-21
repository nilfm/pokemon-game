#ifndef COMBAT_HH
#define COMBAT_HH

#include "Includes.hh"
#include "Player.hh"
#include "Pokemon.hh"
#include "Enemy.hh"
#include "Move.hh"
#include "Type.hh"

class Combat {
private:
    Player& player;
    Enemy& enemy;
    Pokemon active_player, active_enemy;
    
public:
    //CONSTRUCTORS
    /* Pre: both player and enemy have a full Pokemon team (3) */
    /* Post: A combat is initialized between player and enemy */
    Combat(Player& _player, Enemy& _enemy);
    
    
    //ACTIONS
    /* Pre: True */
    /* Post: Returns 0 if battle goes on, 1 if player beats enemy, 2 if enemy beats player */
    int play_turn(); //TODO
    
    /* Pre: Player just won a combat */
    /* Post: Player has picked a pokemon from the enemy team to swap for one of his pokemon, or chosen to do nothing */
    void pick_enemy_pokemon();
    
    
    //SHOWERS
    /* Pre: True */
    /* Post: Shows current status of the game */
    void show_current_game();
    
    
    //AUXILIARY
    /* Pre: True */
    /* Post: Returns the damage done by this move on the defender. Critical indicates if the hit has been critical */
    static int calculate_damage(const Pokemon& attacker, const Pokemon& defender, const Move& move, bool& critical);
    
    /* Pre: True */
    /* Post: returns 1 if player1 attacks first, 2 otherwise */
    static int pick_first(int speed1, int speed2);
    
    /* Pre: True */
    /* Post: Returns true iff the player has no alive Pokemon */
    static bool has_lost(const Player& p);
    
    /* Pre: True */
    /* Post: Returns true iff the enemy has no alive Pokemon */
    static bool has_lost(const Enemy& p);
};

#endif
