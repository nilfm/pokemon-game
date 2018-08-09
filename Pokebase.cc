#include "includes.hh"
#include "Pokebase.hh"

Pokebase::Pokebase() {}

Pokebase::Pokebase(const std::string& address) {
    std::ifstream in(address);
    assert(in.is_open());
    
    in >> name;
    std::string garbage;
    in >> garbage >> attack >> attack_level;
    in >> garbage >> defense >> defense_level;
    in >> garbage >> speed >> speed_level;
    in >> garbage >> spdefense >> spdefense_level;
    in >> garbage >> maxhp >> maxhp_level;
    
    std::string move_name;
    int move_level, move_maxpp;
    std::string move_type;
    char move_special;
    int move_power, move_accuracy;
    while (in >> move_name >> move_level >> move_maxpp >> move_type >> move_special >> move_power >> move_accuracy) {
        std::string move_description;
        getline(in, move_description);
        bool special = (move_special == 'S');
        Move m(special, move_name, move_type, move_power, move_accuracy, move_description, move_maxpp);
        moveset[move_level] = m;
    }
    
    in.close();
}

std::string Pokebase::get_name() const {
    return name;
}

int Pokebase::get_maxhp() const {
    return maxhp;
}

int Pokebase::get_attack() const {
    return attack;
}

int Pokebase::get_defense() const {
    return defense;
}

int Pokebase::get_spattack() const {
    return spattack;
}

int Pokebase::get_spdefense() const {
    return spdefense;
}

int Pokebase::get_speed() const {
    return speed;
}

int Pokebase::get_maxhp_level() const {
    return maxhp_level;
}

int Pokebase::get_attack_level() const {
    return attack_level;
}

int Pokebase::get_defense_level() const {
    return defense_level;
}

int Pokebase::get_spattack_level() const {
    return spattack_level;
}

int Pokebase::get_spdefense_level() const {
    return spdefense_level;
}

int Pokebase::get_speed_level() const {
    return speed_level;
}

Type Pokebase::get_type() const {
    return type;
}

std::map<int, Move> Pokebase::get_moveset() const{
    return moveset;
}

