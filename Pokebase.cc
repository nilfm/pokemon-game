#include "Pokebase.hh"

//CONSTRUCTORS
Pokebase::Pokebase() {}

Pokebase::Pokebase(const std::string& address) {
    std::ifstream in(address);
    assert(in.is_open());
    
    std::string type;
    in >> name >> type >> level_evolution >> next_evolution;
    this->type = Type(type);
    std::string garbage;
    in >> garbage >> base_stats.attack    >> level_stats_min.attack    >> level_stats_max.attack;
    in >> garbage >> base_stats.defense   >> level_stats_min.defense   >> level_stats_max.defense;
    in >> garbage >> base_stats.spattack  >> level_stats_min.spattack  >> level_stats_max.spattack;
    in >> garbage >> base_stats.spdefense >> level_stats_min.spdefense >> level_stats_max.spdefense;
    in >> garbage >> base_stats.speed     >> level_stats_min.speed     >> level_stats_max.speed;
    in >> garbage >> base_stats.maxhp     >> level_stats_min.maxhp     >> level_stats_max.maxhp;
    
    std::string move_name;
    int move_level, move_maxpp;
    std::string move_type;
    char move_special;
    int move_power, move_accuracy;
    while (in >> move_name >> move_level >> move_maxpp >> move_type >> move_special >> move_power >> move_accuracy) {
        bool special = (move_special == 'S');
        Stats s_opp, s_own;
        in >> s_opp.attack >> s_opp.defense >> s_opp.spattack >> s_opp.spdefense >> s_opp.speed >> s_opp.maxhp;
        in >> s_own.attack >> s_own.defense >> s_own.spattack >> s_own.spdefense >> s_own.speed >> s_own.maxhp;
        Status status;
        in >> status.poison >> status.burn >> status.stun;
        Move m(special, move_name, move_type, move_power, move_accuracy, move_maxpp, s_opp, s_own, status);
        (moveset[move_level]).push_back(m);
    }
    in.close();
}


//GETTERS
std::string Pokebase::get_name() const {
    return name;
}

int Pokebase::get_level_evolution() const {
    return level_evolution;
}

std::string Pokebase::get_next_evolution() const {
    return next_evolution;
}

Stats Pokebase::get_base_stats() const {
    return base_stats;
}

Stats Pokebase::get_level_stats_min() const {
    return level_stats_min;
}

Stats Pokebase::get_level_stats_max() const {
    return level_stats_max;
}

Type Pokebase::get_type() const {
    return type;
}

std::map<int, std::vector<Move> > Pokebase::get_moveset() const{
    return moveset;
}


//OPERATORS
bool Pokebase::operator<(const Pokebase& p2) const {
    return name < p2.name;
}
