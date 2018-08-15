#include "includes.hh"
#include "Pokebase.hh"

Pokebase::Pokebase() {}

Pokebase::Pokebase(const std::string& address) {
    std::ifstream in(address);
    assert(in.is_open());
    
    in >> name;
    std::string garbage;
    in >> garbage >> base_stats.attack >> level_stats.attack;
    in >> garbage >> base_stats.defense >> level_stats.defense;
    in >> garbage >> base_stats.spattack >> level_stats.spattack;
    in >> garbage >> base_stats.spdefense >> level_stats.spdefense;
    in >> garbage >> base_stats.speed >> level_stats.speed;
    in >> garbage >> base_stats.maxhp >> level_stats.maxhp;
    
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

Stats Pokebase::get_base_stats() const {
    return base_stats;
}

Stats Pokebase::get_level_stats() const {
    return level_stats;
}

Type Pokebase::get_type() const {
    return type;
}

std::map<int, Move> Pokebase::get_moveset() const{
    return moveset;
}

