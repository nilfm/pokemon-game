#include "Player.hh"

Player::Player() {}

Player::Player(const std::string& name) {
    this->name = name;
    money = 1000;
    trainers = 0;
    team = choose_starters();
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

std::vector<Pokemon> Player::choose_starters() const {
    std::set<std::string> starters;
    std::ifstream in("Pokedata/Starters.txt");
    assert(in.is_open());
    std::string name;
    while (in >> name) starters.insert(name);
    in.close();
    
    std::vector<Pokemon> team(3);
    std::cout << "Choose three Pokemon for your starting team out of the following:" << std::endl;
    for (auto it = starters.begin(); it != starters.end(); it++) {
        std::cout << *it << std::endl;
    }
            
    std::cout << std::endl;
    for (int i = 0; i < 3; i++) {
        std::string query = std::to_string(3-i) + " choices left: ";
        std::string error = "Oops. That wasn't a correct name.";
        std::string choice = Input::read_string(starters, query, error);
        Pokebase chosen = Pokedex::get_pokebase(choice);
        team[i] = Pokemon(chosen, 1);
        starters.erase(choice);
    }
    return team;
}

std::string Player::get_name() const {
    return name;
}

int Player::get_money() const {
    return money;
}

int Player::get_trainers() const {
    return trainers;
}

std::vector<Pokemon> Player::get_team() const {
    return team;
}

std::map<Item, int> Player::get_inventory() const {
    return inventory;
}

void Player::sort_team() {
    std::cout << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << i+1 << " - " << team[i].get_name() << "(Level " << team[i].get_level() << ")" << std::endl;
    }
    std::cout << std::endl;

    std::string query1 = "Choose first pokemon to swap (1-3) (0 to exit): ";
    std::string query2 = "Choose second pokemon to swap (1-3) (0 to exit): ";
    std::string error = "Oops. Enter a number between 1 and 3";
    int p1 = Input::read_int(0, 3, query1, error);
    if (p1 == 0) return;
    int p2 = Input::read_int(0, 3, query2, error);
    if (p2 == 0) return;
    Pokemon aux = team[p1-1];
    team[p1-1] = team[p2-1];
    team[p2-1] = aux;

    std::cout << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << i+1 << " - " << team[i].get_name() << "(Level " << team[i].get_level() << ")" << std::endl;
    }
    std::cout << std::endl;
}
