#include "Combat.hh"

//CONSTRUCTORS
//Necessary to initialize the reference through this weird stuff down here
Combat::Combat(Player& _player, Enemy& _enemy) : player(_player), enemy(_enemy) {
    this->player = _player;
    this->enemy = _enemy;
    active_player = player.get_team()[0];
    active_enemy = enemy.get_team()[0];
}


//ACTIONS
int Combat::play_turn() {
    show_current_game();
    bool corr = false;
    //bool picked_move = false;
    while (not corr) {
        std::string query = "  1. Attack\n  2. Switch Pokemon\n  3. Use Item\n";
        std::string error = "Oops. Enter a number between 1 and 3";
        int choice = Input::read_int(1, 3, query, error);
        if (choice == 1) {
            //picked_move = true;
            //TO DO: Pick move
        }
        else if (choice == 2) {
            player.show_team_inline();
            std::string query1 = "Enter 2 or 3 to swap to that Pokemon. Enter 1 to cancel: ";
            std::string error1 = "Oops. Enter a number between 1 and 3";
            int swap = Input::read_int(1, 3, query1, error1);
            if (swap == 1) std::cout << std::endl;
            else {
                player.swap_pokemon(0, swap-1);
                active_player = player.get_team()[0];
                corr = true;
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
    //bool enemy_picked_move = false;
    //int choice_ai = enemy.get_choice();
    //if (choice_ai == 1) {
    //    enemy.get_move(active_enemy, active_player);
    //    enemy_picked_move = true;
    //if (picked_move and enemy_picked_move)
    //    int first = Combat::pick_first(active_player.get_combat_stats().speed, active_enemy.get_combat_stats().speed)
    //    if (first == 1) 
    //        blah
    //    else
    //        blah
    //else if (picked_move)
    //    blah
    //else 
    //    blah
    //something about if (active_player.get_hp() == 0) bool rip = has_lost(player) i analogament per lenemic
    return 1;
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


//SHOWERS
void Combat::show_current_game() {
    std::cout << std::endl << std::endl;
    std::cout << active_enemy.get_name() << " (Level " << active_enemy.get_level() << ")    HP " << active_enemy.get_hp() << "/" << active_enemy.get_battle_stats().maxhp << std::endl;
    std::cout << std::endl << "           VS            " << std::endl << std::endl;
    std::cout << "         " << active_player.get_name() << " (Level " << active_player.get_level() << ")    HP " << active_player.get_hp() << "/" << active_player.get_battle_stats().maxhp << std::endl;
    std::cout << std::endl << std::endl;
}


//AUXILIARY
int Combat::calculate_damage(const Pokemon& attacker, const Pokemon& defender, const Move& move, bool& critical) {
    critical = false;
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
    
    double type = 1;
    if (type_adv == -2 or hitormiss > accuracy) return 0;
    if (type_adv == -1) type = 0.5;
    else if (type_adv == 1) type = 2; 
    
    if (crit >= 95) {
        crit = 2;
        critical = true;
    }
    else crit = 1;
    
    double modifier = stab*rnd*crit*type/100;
    double damage = (((2.0*level)/5.0 + 2)*power*(double)attack/(double)defense)/50 + 2;
    return (int)(damage*modifier);
}

int Combat::pick_first(int speed1, int speed2) {
    if (speed1 > speed2) return 1;
    else if (speed2 > speed1) return 2;
    else return Random::randint(1, 2);
}

bool has_lost(const Player& p) {
    for (int i = 0; i < (int)p.get_team().size(); i++) {
        if (p.get_team()[i].get_hp() != 0) return false;
    }
    return true;
}

bool has_lost(const Enemy& p) {
    for (int i = 0; i < (int)p.get_team().size(); i++) {
        if (p.get_team()[i].get_hp() != 0) return false;
    }
    return true;
}
