#include "Player.hh"

const std::string Player::gamesave_address = "Saves/GameSave";
const std::string Player::address_extension = ".txt";

//CONSTRUCTORS
Player::Player(int slot) {
    this->slot = slot;
    this->money = 1000;
    this->trainers = 0;
}


//SAVE/LOAD
void Player::load() {
    std::string address = get_address();
    std::ifstream in(address);
    
    assert(in.is_open());
    assert(not is_empty());
    in >> name >> money >> trainers;
    
    std::string input;
    while (in >> input and input == "POKEMON") {
        std::string name;
        int level, xp;
        Stats current;
        in >> name >> level >> xp >> current.attack >> current.defense >> current.spattack >> current.spdefense >> current.speed >> current.maxhp;
        std::vector<std::string> moves;
        std::string m;
        while (in >> m and m != "ENDMOVES") moves.push_back(m);
        Pokebase p = Pokedex::get_pokebase(name);
        Pokemon poke(p, level, xp, current, moves);
        team.push_back(poke);
    }
    
    std::string item;
    int quantity;
    while (in >> item >> quantity) {
        Item it = Item::get_item(item);
        inventory[it] = quantity;
    }
    
    in.close();
}

void Player::save_empty() const {
    std::string address = get_address();
    std::ifstream in(address);
    assert(in.is_open());
    
    in.close();
}

void Player::save() const {
    std::string address = get_address();
    std::ofstream out(address);
    assert(out.is_open());
    
    out << name << " " << money << " " << trainers << std::endl;
    for (int i = 0; i < (int)team.size(); i++) {
        out << "POKEMON " << team[i].get_name() << " " << team[i].get_level() << " " << team[i].get_xp() << std::endl;
        Stats stats = team[i].get_stats();
        out << stats.attack << " " << stats.defense << " " << stats.spattack << " " << stats.spdefense << " " << stats.speed << " " << stats.maxhp << std::endl;
        std::vector<Move> moves = team[i].get_moves();
        for (int j = 0; j < (int)moves.size(); j++) {
            out << moves[j].get_name() << std::endl;
        }
        out << "ENDMOVES" << std::endl;
        out << std::endl;
    }
    
    out << "ITEMS" << std::endl;
    
    for (std::map<Item, int>::const_iterator it = inventory.begin(); it != inventory.end(); it++) {
        out << (it->first).get_name() << " " << it->second << std::endl;
    }
} 


//GETTERS
std::string Player::get_address() const {
    return gamesave_address + std::to_string(slot) + address_extension;
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

bool Player::is_empty() const {
    std::string address = get_address();
    std::ifstream in(address);
    assert(in.is_open());
    std::string s = "";
    int count = 0;
    while (in >> s) count++;
    return count == 0 and s == "";
    in.close();
}


//SETTERS
void Player::increment_trainers() {
    trainers++;
}

void Player::increment_money(int added) {
    money += added;
}

void Player::set_name(const std::string& name) {
    this->name = name;
}

void Player::set_team(const std::vector<Pokemon>& team) {
    this->team = team;
}


//SHOWERS
void Player::presentation() const {
    std::cout << name << " - Trainer " << trainers << std::endl;
}

void Player::show_team_stats() const {
    assert(team.size() == 3);

    std::cout << std::endl << "TEAM STATS" << std::endl << std::endl;
    for (int i = 0; i < 3; i++) {
        team[i].print_stats();
    }
}

void Player::show_inventory() const {
    std::cout << "\nInventory:\n\n";
    for (std::map<Item, int>::const_iterator it = inventory.begin(); it != inventory.end(); it++) {
        std::cout << it->second << " x " << (it->first).get_name() << std::endl;
    }
}


//ACTIONS
void Player::sort_team() {
    assert(team.size() == 3);

    std::cout << "Sorting team" << std::endl;
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
        std::cout << i+1 << " - " << team[i].get_name() << " (Level " << team[i].get_level() << ")" << std::endl;
    }
    std::cout << std::endl;
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
        std::string query = std::to_string(3-i) + " choice(s) left: ";
        std::string error = "Oops. That wasn't a correct name.";
        std::string choice = Input::read_string(starters, query, error);
        Pokebase chosen = Pokedex::get_pokebase(choice);
        team[i] = Pokemon(chosen, 1);
        starters.erase(choice);
    }
    return team;
}

void Player::shop() {
    std::vector<std::string> list_items(14);
    list_items = {"Ether", "MaxEther", "Elixir", "MaxElixir", "Potion", "Superpotion", "Hyperpotion", "MaxPotion", "XAttack", "XDefense", "XSpecialAttack", "XSpecialDefense", "XSpeed"};
    bool cont = true;
    while (cont) {
        std::cout << "\nWelcome to the shop!" << std::endl;
        std::cout << "You have " << money << " coins" << std::endl;
        std::string query = "\n  1. Ether              100\n  2. Max Ether          200\n  3. Elixir             250\n  4. Max Elixir         300\n  5. Potion              50\n  6. Superpotion        120\n  7. Hyperpotion        250\n  8. Max Potion         300\n  9. XAttack            200\n  10. XDefense          200\n  11. XSpecialAttack    200\n  12. XSpecialDefense   200\n  13. XSpeed            200\n\nEnter 0 to leave the shop\n\n";
        std::string error = "Oops. Enter a number between 0 and 13";
        bool corr = false;
        while (not corr) {
            int choice = Input::read_int(0, 13, query, error);
            if (choice == 0) {
                std::cout << "Good bye!" << std::endl;
                return;
            }
            else {
                std::string query2 = "How many do you want to buy? (1-10) ";
                std::string error2 = "Oops. Enter a number between 1 and 10";
                int amount = Input::read_int(1, 10, query2, error2);
                Item to_buy = Item::get_item(list_items[choice-1]);
                if (to_buy.get_price()*amount <= money) {
                    inventory[to_buy] += amount;
                    money -= to_buy.get_price()*amount;
                    std::cout << "You bought " << amount << " " << list_items[choice-1] << "(s)." << std::endl;
                    corr = true;
                }
                else {
                    std::cout << "You don't have enough money" << std::endl << std::endl;
                }
            }
        }
    }
}

