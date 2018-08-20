#include "Player.hh"

Player::Player() {}

Player::Player(const std::string& name) {
    this->name = name;
    money = 1000;
    trainers = 0;
    //TODO: choose 3 Pokemon from a list of starters
}

Player::Player(const Gamesave& gamesave) {
    name = gamesave.get_name();
    money = gamesave.get_money();
    trainers = gamesave.get_trainers();
    team = gamesave.get_team();
    inventory = gamesave.get_inventory();
}

void Player::use_item(Pokemon& p, const Item& it) {
    int type = it.get_type();
    if (type == 0) { //Restore PP for one move
        std::vector<Move> moves = p.get_moves();
        int n = moves.size();
        std::string query = "Which move do you want to restore PP for?";
        std::string error = "Oops. Enter a number between 1 and " + std::to_string(n) + ".";
        std::cout << "Moves:" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << i+1 << ": " << moves[i].get_name() << std::endl << std::endl;
        }
        std::cout << std::endl;
        int choice = Input::read_int(1, n, query, error);
        moves[choice-1].restore_pp(it.get_restored_pp());
        std::cout << "Restored PP for " << moves[choice-1].get_name() << "!" << std::endl;
    }
    else if (type == 1) { //Restore PP for all moves
        std::vector<Move> moves = p.get_moves();
        int n = moves.size();
        for (int i = 0; i < n; i++) {
            moves[i].restore_pp(it.get_restored_pp());
        }
        std::cout << "Restored PP for all moves!" << std::endl << std::endl;
    }
    else if (type == 2) { //Heal
        p.restore_health(it.get_restored_hp());
        std::cout << p.get_name() << " has restored its HP." << std::endl << std::endl;
    }
    else { //Increase stats
        p.add_battle_stats(it.get_improvement());
        std::cout << p.get_name() << "'s stats have improved!" << std::endl << std::endl;
    }
}
