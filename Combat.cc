#include "Combat.hh"

//CONSTRUCTORS
//Necessary to initialize the reference through this weird stuff down here
Combat::Combat(Player& _player, Enemy& _enemy) : player(_player), enemy(_enemy) {
    this->player = _player;
    this->enemy = _enemy;
}


//ACTIONS
int Combat::play_turn() {
    show_current_game();
    Move player_move;
    Move enemy_move;
    bool picked_move = false;
    bool enemy_picked_move = false;

    bool corr = false;
    
    player.get_first_pokemon().handle_status();
    enemy.get_first_pokemon().handle_status();
    
    while (not corr) {
        std::string query = "\nWhat to do?\n  1. Attack\n  2. Switch Pokemon\n  3. Use Item\n";
        std::string error = "Oops. Enter a number between 1 and 3";
        int choice = Input::read_int(1, 3, query, error);
        if (choice == 1) {
            player.get_first_pokemon().print_moves();
            int howmany = player.get_first_pokemon().get_moves().size();
            std::string query0 = "Select a move to perform: ";
            std::string error0 = "Oops. Enter a number between 1 and " + std::to_string(howmany) + " (0 to cancel): ";
            int move_picked = Input::read_int(0, howmany, query0, error0);
            if (player.get_first_pokemon().get_moves()[move_picked-1].get_pp() > 0) {
                picked_move = true;
                player_move = player.get_first_pokemon().get_moves()[move_picked-1];
                corr = true;
            }
            else std::cout << "This move has no PP!" << std::endl << std::endl;
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
                else std::cout << "Can't have a fainted Pokemon as your leader" << std::endl;
            }
        }
        else {
            std::cout << "\nYour inventory:" << std::endl;
            std::map<Item, int> inv = player.get_inventory();
            std::vector<std::string> choices;
            for (auto it = inv.begin(); it != inv.end(); it++) {
                choices.push_back((it->first).get_name());
            }
            for (int i = 0; i < (int)choices.size(); i++) {
                std::cout << "  " << i+1 << ". " << choices[i] << std::endl;
            }
            std::string query2 = "Select one of the items (0 to cancel) : ";
            std::string error2 = "Oops. Enter a number between 1 and " + std::to_string(choices.size());
            int item = Input::read_int(0, (int)choices.size(), query2, error2);
            if (item == 0) std::cout << std::endl;
            else {
                player.show_team_inline();
                std::string query3 = "Select a Pokemon to use the item on (0 to cancel): ";
                std::string error3 = "Oops. Enter a number between 0 and 3";
                int poke = Input::read_int(0, 3, query3, error3);
                if (poke == 0) std::cout << std::endl;
                else {
                    player.use_item(poke-1, Item::get_item(choices[item-1]));
                    player.decrement_item(choices[item-1]);
                }
            } 
        }
    }
    int choice_ai = enemy.action_choice();
    if (choice_ai == 1) {
        int enemy_move_picked = enemy.move_choice(enemy.get_first_pokemon(), player.get_first_pokemon());
        enemy_picked_move = true;
        enemy_move = enemy.get_first_pokemon().get_moves()[enemy_move_picked-1];
    }
    else if (choice_ai == 2) {
        int swap = enemy.swap_choice();
        enemy.swap_pokemon(1, swap);
        enemy.get_first_pokemon() = enemy.get_first_pokemon();
    }
    else {
        //TODO: enemy.choose_item()
    }
    if (picked_move and enemy_picked_move) {
        int first = Combat::pick_first(player.get_first_pokemon().get_battle_stats().speed, enemy.get_first_pokemon().get_battle_stats().speed);
        if (first == 1) {
            bool fainted_enemy = Combat::attack(1, player, enemy, player_move);
            if (fainted_enemy) {
                std::cout << "The enemy " << enemy.get_first_pokemon().get_name() << " has fainted!" << std::endl;
                int xp_gained = enemy.get_first_pokemon().get_level()*Random::randint(2, 5);
                std::cout << "Your " << player.get_first_pokemon().get_name() << " has gained " << xp_gained << " XP." << std::endl;
                player.get_first_pokemon().gain_xp(xp_gained);
                if (Combat::has_lost(enemy)) return 1;
                else {
                    int swap = enemy.swap_choice();
                    enemy.swap_pokemon(1, swap);
                }
            }
            else {
                bool fainted_player = Combat::attack(2, player, enemy, enemy_move);
                if (fainted_player) {
                    std::cout << "Your " << player.get_first_pokemon().get_name() << " has fainted!" << std::endl;
                    if (Combat::has_lost(player)) return 2;
                    else {
                        int swap = player.swap_fainted();
                        player.swap_pokemon(0, swap-1);
                    }
                }
            }
        }
        else {
            bool fainted_player = Combat::attack(2, player, enemy, enemy_move);
            if (fainted_player) {
                std::cout << "Your " << player.get_first_pokemon().get_name() << " has fainted!" << std::endl;
                if (Combat::has_lost(player)) return 2;
                else {
                    int swap = player.swap_fainted();
                    player.swap_pokemon(0, swap-1);
                }            
            }
            else {
                bool fainted_enemy = Combat::attack(1, player, enemy, player_move);
                if (fainted_enemy) {
                    std::cout << "The enemy " << enemy.get_first_pokemon().get_name() << " has fainted!" << std::endl;
                    int xp_gained = enemy.get_first_pokemon().get_level()*Random::randint(2, 5);
                    std::cout << "Your " << player.get_first_pokemon().get_name() << " has gained " << xp_gained << " XP." << std::endl;
                    if (Combat::has_lost(enemy)) return 1;
                    else {
                        int swap = enemy.swap_choice();
                        enemy.swap_pokemon(1, swap);
                    }
                }
            }    
        }
    }
    else if (picked_move) { //only player attacks
        bool fainted_enemy = Combat::attack(1, player, enemy, player_move);
        if (fainted_enemy) {
            std::cout << "The enemy " << enemy.get_first_pokemon().get_name() << " has fainted!" << std::endl;
            int xp_gained = enemy.get_first_pokemon().get_level()*Random::randint(2, 5);
            std::cout << "Your " << player.get_first_pokemon().get_name() << " has gained " << xp_gained << " XP." << std::endl;
            if (Combat::has_lost(enemy)) return 1;
            else {
                int swap = enemy.swap_choice();
                enemy.swap_pokemon(1, swap);
            }
        } 
    }
    else { //only enemy attacks
        bool fainted_player = Combat::attack(2, player, enemy, enemy_move);
        if (fainted_player) {
            std::cout << "Your " << player.get_first_pokemon().get_name() << " has fainted!" << std::endl;
            if (Combat::has_lost(player)) return 2;
            else {
                int swap = player.swap_fainted();
                player.swap_pokemon(0, swap-1);
            } 
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


bool Combat::attack(int k, Player& player, Enemy& enemy, Move& move) {
    move.decrement_pp();
    if (k == 1) {
        std::cout << std::endl << "Your " <<  player.get_first_pokemon().get_name() << " used " << move.get_name() << "." << std::endl << std::endl;
        bool critical, missed, not_effective, little_effective, very_effective, stunned;
        critical = missed = not_effective = little_effective = very_effective = stunned = false;
        int dmg = calculate_damage(player.get_first_pokemon(), enemy.get_first_pokemon(), move, critical, missed, not_effective, little_effective, very_effective, stunned);
        if (stunned) std::cout << "But it was stunned" << std::endl << std::endl;
        else if (missed) std::cout << "But it missed!" << std::endl << std::endl;
        else if (not_effective) std::cout << "But it didn't affect " << enemy.get_first_pokemon().get_name() << std::endl << std::endl;
        else if (little_effective) std::cout << "It wasn't very effective..." << std::endl << std::endl;
        else if (very_effective) std::cout << "It was very effective!" << std::endl << std::endl;
        if (dmg > 0 and critical) std::cout << "Critical hit!" << std::endl << std::endl;
        if (dmg > 0) std::cout << "It did " << dmg << " damage to " << enemy.get_first_pokemon().get_name() << std::endl << std::endl;
        bool fainted = enemy.get_first_pokemon().receive_damage(dmg);
        if (not fainted) {
            Status move_status = move.get_status();
            if (move_status.poison > 0) {
                int rnd = Random::randint(0, 100);
                if (move_status.poison > rnd) {
                    enemy.get_first_pokemon().get_poisoned();
                    std::cout << "The enemy's " << enemy.get_first_pokemon().get_name() << " was poisoned!" << std::endl;
                }
            }
            if (move_status.burn > 0) {
                int rnd = Random::randint(0, 100);
                if (move_status.burn > rnd) {
                    enemy.get_first_pokemon().get_burned();
                    std::cout << "The enemy's " << enemy.get_first_pokemon().get_name() << " was burned!" << std::endl;
                }
            }
            if (move_status.stun > 0) {
                int rnd = Random::randint(0, 100);
                if (move_status.stun > rnd) {
                    enemy.get_first_pokemon().get_stunned();
                    std::cout << "The enemy's " << enemy.get_first_pokemon().get_name() << " was stunned!" << std::endl;
                }
            }
        }
        return fainted;
    }
    else {
        std::cout << std::endl << "The enemy " << enemy.get_first_pokemon().get_name() << " used " << move.get_name() << "." << std::endl << std::endl;
        bool critical, missed, not_effective, little_effective, very_effective, stunned;
        critical = missed = not_effective = little_effective = very_effective = stunned = false;
        int dmg = calculate_damage(enemy.get_first_pokemon(), player.get_first_pokemon(), move, critical, missed, not_effective, little_effective, very_effective, stunned);
        if (stunned) std::cout << "But it was stunned" << std::endl << std::endl;
        else if (missed) std::cout << "But it missed!" << std::endl << std::endl;
        else if (not_effective) std::cout << "But it didn't affect " << player.get_first_pokemon().get_name() << std::endl << std::endl;
        else if (little_effective) std::cout << "It wasn't very effective..." << std::endl << std::endl;
        else if (very_effective) std::cout << "It was very effective!" << std::endl << std::endl;
        if (dmg > 0 and critical) std::cout << "Critical hit!" << std::endl << std::endl;
        if (dmg > 0) std::cout << "It did " << dmg << " damage to " << player.get_first_pokemon().get_name() << std::endl << std::endl;
        bool fainted = player.get_first_pokemon().receive_damage(dmg);
        if (not fainted) {
            Status move_status = move.get_status();
            if (move_status.poison > 0) {
                int rnd = Random::randint(0, 100);
                if (move_status.poison > rnd) {
                    player.get_first_pokemon().get_poisoned();
                    std::cout << "Your " << player.get_first_pokemon().get_name() << " was poisoned!" << std::endl;
                }
            }
            if (move_status.burn > 0) {
                int rnd = Random::randint(0, 100);
                if (move_status.burn > rnd) {
                    player.get_first_pokemon().get_burned();
                    std::cout << "Your " << player.get_first_pokemon().get_name() << " was burned!" << std::endl;
                }
            }
            if (move_status.stun > 0) {
                int rnd = Random::randint(0, 100);
                if (move_status.stun > rnd) {
                    player.get_first_pokemon().get_stunned();
                    std::cout << "Your " << player.get_first_pokemon().get_name() << " was stunned!" << std::endl;
                }
            }
        }
        return fainted;
    }
}


//SHOWERS
void Combat::show_current_game() {
    std::cout << std::endl << std::endl;
    std::cout << enemy.get_first_pokemon().get_name() << " (Level " << enemy.get_first_pokemon().get_level() << ")    HP " << enemy.get_first_pokemon().get_hp() << "/" << enemy.get_first_pokemon().get_battle_stats().maxhp << std::endl;
    std::cout << std::endl << "           VS            " << std::endl << std::endl;
    std::cout << "         " << player.get_first_pokemon().get_name() << " (Level " << player.get_first_pokemon().get_level() << ")    HP " << player.get_first_pokemon().get_hp() << "/" << player.get_first_pokemon().get_battle_stats().maxhp << std::endl;
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
    if (attacker.get_type().get_name() == move.get_type().get_name()) stab = 1.5;
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

bool Combat::has_lost(const Enemy& p) {
    for (int i = 0; i < (int)p.get_team().size(); i++) {
        if (p.get_team()[i].get_hp() != 0) return false;
    }
    return true;
}
