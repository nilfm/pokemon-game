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
    //TODO
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
