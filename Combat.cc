#include "Combat.hh"

//CONSTRUCTORS
//Necessary to initialize the reference through this weird stuff down here
Combat::Combat(Player& _player, Player& _enemy) : player(_player), enemy(_enemy) {
    this->player = _player;
    this->enemy = _enemy;
}


//ACTIONS
int Combat::play_turn() {
    player.get_first_pokemon().handle_status();
    enemy.get_first_pokemon().handle_status();
    
    show_current_game();
    Move player_move;
    Move enemy_move;
    bool picked_move = false;
    bool enemy_picked_move = false;

    bool corr = false;
    
    //PLAYER CHOICES
    while (not corr) {
        std::string query = "\nWhat to do?\n  1. Attack\n  2. Switch Pokemon\n  3. Use Item\n";
        std::string error = "Oops. Enter a number between 1 and 3";
        int choice = Input::read_int(1, 3, query, error);
        if (choice == 1) {
            player.get_first_pokemon().print_moves();
            int howmany = player.get_first_pokemon().get_moves().size();
            std::string query0 = "Select a move to perform (0 to cancel): ";
            std::string error0 = "Oops. Enter a number between 1 and " + std::to_string(howmany) + " (0 to cancel): ";
            int move_picked = Input::read_int(0, howmany, query0, error0);
            if (move_picked != 0) {
                if (player.get_first_pokemon().get_moves()[move_picked-1].get_pp() > 0) {
                    picked_move = true;
                    player_move = player.get_first_pokemon().get_moves()[move_picked-1];
                    corr = true;
                }
                else std::cout << "This move has no PP!" << std::endl << std::endl;
            }
        }
        else if (choice == 2) {
            player.show_team_inline();
            std::string query1 = "Enter 2 or 3 to swap to that Pokemon. Enter 1 to cancel: ";
            std::string error1 = "Oops. Enter a number between 1 and 3";
            int swap = Input::read_int(1, 3, query1, error1);
            if (swap == 1) std::cout << std::endl;
            else {
                corr = player.swap_pokemon(0, swap-1);
                if (corr) player.get_first_pokemon() = player.get_first_pokemon();
            }
        }
        else {
            std::cout << "\nYour inventory:" << std::endl;
            std::map<Item, int> inv = player.get_inventory();
            std::vector<std::string> choices;
            std::vector<int> amounts;
            for (auto it = inv.begin(); it != inv.end(); it++) {
                choices.push_back((it->first).get_name());
                amounts.push_back(it->second);
            }
            for (int i = 0; i < (int)choices.size(); i++) {
                std::cout << "  " << i+1 << ". " << choices[i] << " x" << amounts[i] << std::endl;
            }
            std::string query2 = "\nSelect one of the items (0 to cancel): ";
            std::string error2 = "Oops. Enter a number between 1 and " + std::to_string(choices.size());
            int item = Input::read_int(0, (int)choices.size(), query2, error2);
            if (item == 0) std::cout << std::endl;
            else {
                player.show_team_inline();
                std::string query3 = "\nSelect a Pokemon to use the item on (0 to cancel): ";
                std::string error3 = "Oops. Enter a number between 0 and 3";
                int poke = Input::read_int(0, 3, query3, error3);
                if (poke == 0) std::cout << std::endl;
                else {
                    corr = player.use_item(poke-1, Item::get_item(choices[item-1]));
                    if (corr) player.decrement_item(choices[item-1]);

                }
            } 
        }
    }
    
    //AI CHOICES
    int choice_ai = enemy.action_choice();
    if (choice_ai == 1) {
        int enemy_move_picked = enemy.move_choice(enemy.get_first_pokemon(), player.get_first_pokemon());
        enemy_picked_move = true;
        enemy_move = enemy.get_first_pokemon().get_moves()[enemy_move_picked-1];
    }
    else if (choice_ai == 2) {
        int swap = enemy.swap_choice(player.get_first_pokemon());
        enemy.swap_pokemon(0, swap);
    }
    else {
        if (choice_ai == 3) {
            //TODO: Use healing item
        }
        else if (choice_ai == 4) {
            //TODO: Use PP item
        }
    }
    
    //Handle who attacks first and second (if they do attack)
    bool fainted_enemy = false, fainted_player = false;
    if (picked_move and enemy_picked_move) {
        int first = Combat::pick_first(player.get_first_pokemon().get_battle_stats().speed, enemy.get_first_pokemon().get_battle_stats().speed);
        if (first == 1) {
            fainted_enemy = Combat::attack(1, player, enemy, player_move);
            if (not fainted_enemy) {
                fainted_player = Combat::attack(2, player, enemy, enemy_move);
            }
        }
        else if (first == 2) {
            fainted_player = Combat::attack(2, player, enemy, enemy_move);
            if (not fainted_player) {
                fainted_enemy = Combat::attack(1, player, enemy, player_move);
            }
        }
    }
    else if (picked_move) {
        fainted_enemy = Combat::attack(1, player, enemy, player_move);
    }
    else if (enemy_picked_move) {
        fainted_player = Combat::attack(2, player, enemy, enemy_move);
    }
    
    //Handle fainted Pokemon
    if (fainted_player) {
        std::cout << "Your " << player.get_first_pokemon().get_name() << " has fainted!" << std::endl;
        if (Combat::has_lost(player)) return 2;
        else {
            int swap = player.swap_fainted();
            player.swap_pokemon(0, swap-1);
        }
    }
    if (fainted_enemy) {
        std::cout << "The enemy " << enemy.get_first_pokemon().get_name() << " has fainted!" << std::endl;
        int xp_gained = enemy.get_first_pokemon().get_level()*Random::randint(3, 10);
        std::cout << "Your " << player.get_first_pokemon().get_name() << " has gained " << xp_gained << " XP." << std::endl;
        player.get_first_pokemon().gain_xp(xp_gained);
        if (Combat::has_lost(enemy)) return 1;
        else {
            int swap = enemy.swap_choice(player.get_first_pokemon());
            enemy.swap_pokemon(0, swap);
        }
    }
    return 0; //battle continues
}

void Combat::pick_enemy_pokemon() {
    std::cout << "Since you have won, you can swap one of your Pokemon with one of your enemy's Pokemon!" << std::endl;
    std::vector<Pokemon> team1 = player.get_team();
    std::vector<Pokemon> team2 = enemy.get_team();
    std::cout << std::endl << "YOUR TEAM:" << std::endl;
    for (int i = 0; i < (int)team1.size(); i++) {
        std::cout << "  " << i+1 << ". " << team1[i].get_name() << " (Level " << team1[i].get_level() << ")" << std::endl;
    }
    std::cout << std::endl << "ENEMY TEAM:" << std::endl;
    for (int i = 0; i < (int)team2.size(); i++) {
        std::cout << "  " << i+1 << ". " << team2[i].get_name() << " (Level " << team2[i].get_level() << ")" << std::endl;
    }
    
    std::cout << std::endl;
    std::string query = "Which one of your opponent's Pokemon do you want? (0 to exit) ";
    std::string query2 = "Which one of your Pokemon do you want to lose? (0 to exit) ";
    std::string error = "Oops. Enter a number between 0 and 3";
    
    int choice1 = Input::read_int(0, 3, query, error);
    if (choice1 == 0) {
        std::cout << "No trade has been made" << std::endl;
        return;
    }
    int choice2 = Input::read_int(0, 3, query2, error);
    if (choice2 == 0) {
        std::cout << "No trade has been made" << std::endl;
        return;
    }
    player.set_pokemon(team2[choice1-1], choice2-1);
}


bool Combat::attack(int k, Player& player, Player& enemy, Move& move) {
    if (k == 1) player.get_first_pokemon().decrement_pp(move);
    else enemy.get_first_pokemon().decrement_pp(move);
    
    bool critical, missed, not_effective, little_effective, very_effective, stunned;
    critical = missed = not_effective = little_effective = very_effective = stunned = false;

    int dmg;
    if (k == 1) {
        dmg = calculate_damage(player.get_first_pokemon(), enemy.get_first_pokemon(), move, critical, missed, not_effective, little_effective, very_effective, stunned);
    }
    else {
        dmg = calculate_damage(enemy.get_first_pokemon(), player.get_first_pokemon(), move, critical, missed, not_effective, little_effective, very_effective, stunned);
    }
    
    std::string owner = "Your ";
    if (k == 2) owner = "The enemy ";
    
    std::string ownerdef = "The enemy ";
    if (k == 2) ownerdef = "Your ";
    
    std::string attacker_name = player.get_first_pokemon().get_name();
    if (k == 2) attacker_name = enemy.get_first_pokemon().get_name();
    
    std::string defender_name = enemy.get_first_pokemon().get_name();
    if (k == 2) defender_name = player.get_first_pokemon().get_name();  
      
    std::cout << std::endl << owner << attacker_name << " used " << move.get_name() << "." << std::endl;
    if (stunned) std::cout << "But it was stunned" << std::endl;
    else if (missed) std::cout << "But it missed!" << std::endl;
    else if (not_effective) std::cout << "But it didn't affect " << player.get_first_pokemon().get_name() << std::endl;
    else if (little_effective) std::cout << "It wasn't very effective..." << std::endl;
    else if (very_effective) std::cout << "It was very effective!" << std::endl;
    if (dmg > 0 and critical) std::cout << "Critical hit!" << std::endl;
    if (dmg > 0) std::cout << "It did " << dmg << " damage to " << defender_name << std::endl;
    bool fainted = false;
    if (k == 1) fainted = enemy.get_first_pokemon().receive_damage(dmg);
    else fainted = player.get_first_pokemon().receive_damage(dmg);
    
    if (not fainted and not missed) {
        Pokemon& defending_pokemon = (k == 1 ? enemy.get_first_pokemon() : player.get_first_pokemon());
        Pokemon& attacking_pokemon = (k == 1 ? player.get_first_pokemon() : enemy.get_first_pokemon());
        Status move_status = move.get_status();
        if (move_status.poison > 0) {
            int rnd = Random::randint(0, 100);
            if (move_status.poison > rnd) {
                defending_pokemon.get_poisoned();
                std::cout << ownerdef << defender_name << " was poisoned!" << std::endl;
            }
        }
        if (move_status.burn > 0) {
            int rnd = Random::randint(0, 100);
            if (move_status.burn > rnd) {
                defending_pokemon.get_burned();
                std::cout << ownerdef << defender_name << " was burned!" << std::endl;
            }
        }
        if (move_status.stun > 0) {
            int rnd = Random::randint(0, 100);
            if (move_status.stun > rnd) {
                defending_pokemon.get_stunned();
                std::cout << ownerdef << defender_name << " was stunned!" << std::endl;
            }
        }
        
        Stats change_stats_opponent = move.get_change_stats_opponent();
        Stats change_stats_own = move.get_change_stats_own();
        
        //Change stats opponent
        defending_pokemon.add_battle_stats(change_stats_opponent);
        if (change_stats_opponent.attack < 0) std::cout << ownerdef << defender_name << "'s attack is reduced by " << -change_stats_opponent.attack << std::endl;
        if (change_stats_opponent.attack > 0) std::cout << ownerdef << defender_name << "'s attack is increased by " << change_stats_opponent.attack << std::endl;
        if (change_stats_opponent.defense < 0) std::cout << ownerdef << defender_name << "'s defense is reduced by " << -change_stats_opponent.defense << std::endl;
        if (change_stats_opponent.defense > 0) std::cout << ownerdef << defender_name << "'s defense is increased by " << change_stats_opponent.defense << std::endl;
        if (change_stats_opponent.spattack < 0) std::cout << ownerdef << defender_name << "'s special attack is reduced by " << -change_stats_opponent.spattack << std::endl;
        if (change_stats_opponent.spattack > 0) std::cout << ownerdef << defender_name << "'s special attack is increased by " << change_stats_opponent.spattack << std::endl;
        if (change_stats_opponent.spdefense < 0) std::cout << ownerdef << defender_name << "'s special defense is reduced by " << -change_stats_opponent.spdefense << std::endl;
        if (change_stats_opponent.spdefense > 0) std::cout << ownerdef << defender_name << "'s special defense is increased by " << change_stats_opponent.spdefense << std::endl;
        if (change_stats_opponent.speed < 0) std::cout << ownerdef << defender_name << "'s speed is reduced by " << -change_stats_opponent.speed << std::endl;
        if (change_stats_opponent.speed > 0) std::cout << ownerdef << defender_name << "'s speed is increased by " << change_stats_opponent.speed << std::endl;
        
        //Change stats own
        attacking_pokemon.add_battle_stats(change_stats_own);
        if (change_stats_own.attack < 0) std::cout << owner << attacker_name << "'s attack is reduced by " << -change_stats_own.attack << std::endl;
        if (change_stats_own.attack > 0) std::cout << owner << attacker_name << "'s attack is increased by " << change_stats_own.attack << std::endl;
        if (change_stats_own.defense < 0) std::cout << owner << attacker_name << "'s defense is reduced by " << -change_stats_own.defense << std::endl;
        if (change_stats_own.defense > 0) std::cout << owner << attacker_name << "'s defense is increased by " << change_stats_own.defense << std::endl;
        if (change_stats_own.spattack < 0) std::cout << owner << attacker_name << "'s special attack is reduced by " << -change_stats_own.spattack << std::endl;
        if (change_stats_own.spattack > 0) std::cout << owner << attacker_name << "'s special attack is increased by " << change_stats_own.spattack << std::endl;
        if (change_stats_own.spdefense < 0) std::cout << owner << attacker_name << "'s special defense is reduced by " << -change_stats_own.spdefense << std::endl;
        if (change_stats_own.spdefense > 0) std::cout << owner << attacker_name << "'s special defense is increased by " << change_stats_own.spdefense << std::endl;
        if (change_stats_own.speed < 0) std::cout << owner << attacker_name << "'s speed is reduced by " << -change_stats_own.speed << std::endl;
        if (change_stats_own.speed > 0) std::cout << owner << attacker_name << "'s speed is increased by " << change_stats_own.speed << std::endl;
    }
    return fainted;
}


//SHOWERS
void Combat::show_current_game() {
    std::cout << std::endl << std::endl;
    std::cout << enemy.get_first_pokemon().get_name() << " (Level " << enemy.get_first_pokemon().get_level() << ")    HP " << enemy.get_first_pokemon().get_hp() << "/" << enemy.get_first_pokemon().get_battle_stats().maxhp << std::endl;
    std::cout << std::endl << "           VS            " << std::endl << std::endl;
    std::cout << "         " << player.get_first_pokemon().get_name() << " (Level " << player.get_first_pokemon().get_level() << ")    HP " << player.get_first_pokemon().get_hp() << "/" << player.get_first_pokemon().get_battle_stats().maxhp << std::endl;
    int xp = player.get_first_pokemon().get_xp();
    int level = player.get_first_pokemon().get_level();
    std::cout << "         " << "XP: " << xp - 5*level*(level-1) << "/" << 10*level << std::endl; 
    std::cout << std::endl << std::endl;
}


//AUXILIARY
int Combat::calculate_damage(const Pokemon& attacker, const Pokemon& defender, const Move& move, bool& critical, bool& missed, bool& not_effective, bool& little_effective, bool& very_effective, bool& stunned) {
    if (move.get_power() == 0) return 0;
    critical = false;
    missed = false;
    not_effective = false;
    little_effective = false;
    very_effective = false;
    stunned = false;
    bool special = move.is_special();
    int attack, defense;
    if (special) {
        attack = attacker.get_battle_stats().spattack;
        defense = defender.get_battle_stats().spdefense;
    }
    else {
        attack = attacker.get_battle_stats().attack;
        defense = defender.get_battle_stats().defense;
    }
    double stab = 1;
    if (attacker.get_type() == move.get_type()) stab = 1.5;
    int power = move.get_power();
    int accuracy = move.get_accuracy();
    int level = attacker.get_level();
    int rnd = Random::randint(85, 100);
    int crit = Random::randint(0, 100); //More than or 95 -> Critical
    int type_adv = Type::advantage(move.get_type(), defender.get_type());
    int hitormiss = Random::randint(0, 100); //More than accuracy -> Miss
    if (hitormiss > accuracy) missed = true;
    if (type_adv == -2) not_effective = true;
    
    if (attacker.get_status().stun != 0) {
        if (Random::randint(0, 100) > 50) {
            stunned = true;
            return 0;
        }
    }
    
    double type = 1;
    if (type_adv == -2 or hitormiss > accuracy) return 0;
    if (type_adv == -1) type = 0.5;
    else if (type_adv == 1) type = 2; 
    
    if (crit >= 95) {
        crit = 2;
        critical = true;
    }
    else crit = 1;

    if (type_adv == -1) little_effective = true;
    if (type_adv == 1) very_effective = true;
    
    double modifier = stab*rnd*crit*type/100;
    double damage = (((2.0*level)/5.0 + 2)*power*(double)attack/(double)defense)/50 + 2;
    return (int)(damage*modifier);
}

int Combat::pick_first(int speed1, int speed2) {
    if (speed1 > speed2) return 1;
    else if (speed2 > speed1) return 2;
    else return Random::randint(1, 2);
}

bool Combat::has_lost(const Player& p) {
    for (int i = 0; i < (int)p.get_team().size(); i++) {
        if (p.get_team()[i].get_hp() != 0) return false;
    }
    return true;
}

