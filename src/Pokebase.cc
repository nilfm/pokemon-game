#include "../inc/Pokebase.hh"

//CONSTRUCTORS
Pokebase::Pokebase() {}

Pokebase::Pokebase(const std::string& address) {
    std::ifstream in(address);
    assert(in.is_open());
    
    std::string type;
    in >> name >> type >> level_evolution >> next_evolution;
    this->type = type;
    std::string garbage;
    in >> garbage >> base_stats.attack    >> level_stats_min.attack    >> level_stats_max.attack;
    in >> garbage >> base_stats.defense   >> level_stats_min.defense   >> level_stats_max.defense;
    in >> garbage >> base_stats.spattack  >> level_stats_min.spattack  >> level_stats_max.spattack;
    in >> garbage >> base_stats.spdefense >> level_stats_min.spdefense >> level_stats_max.spdefense;
    in >> garbage >> base_stats.speed     >> level_stats_min.speed     >> level_stats_max.speed;
    in >> garbage >> base_stats.maxhp     >> level_stats_min.maxhp     >> level_stats_max.maxhp;
    
    std::string move_name;
    int move_level;
    while (in >> move_name >> move_level) {
        moveset[move_level].push_back(Move::get_move(move_name));
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

std::string Pokebase::get_type() const {
    return type;
}

std::map<int, std::vector<Move> > Pokebase::get_moveset() const{
    return moveset;
}


//OPERATORS
bool Pokebase::operator<(const Pokebase& p2) const {
    return name < p2.name;
}
