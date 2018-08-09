#include "includes.hh"
#include "Pokebase.hh"

Pokebase::Pokebase() {}

Pokebase::Pokebase(const std::string& address) {
    std::ifstream in(address);
    assert(in.is_open());
    
    //TODO
    
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

int Pokebase::get_maxhp_level) const {
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

std::vector<Move> get_moveset() const {
    return moveset;
}

