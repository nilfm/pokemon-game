#include "Gamesave.hh"

const std::string Gamesave::gamesave_address = "Saves/GameSave";
const std::string Gamesave::address_extension = ".txt";

Gamesave::Gamesave(int slot) {
    this->slot = slot;
}

void Gamesave::load() {
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

void Gamesave::save_empty() {
    std::string address = get_address();
    std::ifstream in(address);
    assert(in.is_open());
    
    in.close();
}

void Gamesave::update(const std::string& name, int money, int trainers, const std::vector<Pokemon>& team, const std::map<Item, int>& inventory) {
    this->name = name;
    this->money = money;
    this->trainers = trainers,
    this->team = team;
    this->inventory = inventory;
}

void Gamesave::save() {
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
    
    for (std::map<Item, int>::const_iterator it = inventory.begin(); it != inventory.end(); it++) {
        out << (it->first).get_name() << " " << it->second << std::endl;
    }
} 

void Gamesave::presentation() {
    std::cout << name << " - Trainer " << trainers << std::endl;
}

bool Gamesave::is_empty() {
    std::string address = get_address();
    std::ifstream in(address);
    assert(in.is_open());
    std::string s = "";
    int count = 0;
    while (in >> s) count++;
    return count == 0 and s == "";
    in.close();
}

std::string Gamesave::get_address() {
    return gamesave_address + std::to_string(slot) + address_extension;
}

std::string Gamesave::get_name() const {
    return name;
}

int Gamesave::get_money() const {
    return money;
}

int Gamesave::get_trainers() const {
    return trainers;
}

std::vector<Pokemon> Gamesave::get_team() const {
    return team;
}

std::map<Item, int> Gamesave::get_inventory() const {
    return inventory;    
}
