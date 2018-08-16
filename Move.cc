#include "Move.hh"

Move::Move() {}

Move::Move(bool special, const std::string& name, const std::string& type, int power, int accuracy, int maxpp, const Stats& change_stats_opponent, const Stats& change_stats_own) {
    this->special = special;
    this->name = name;
    this->type = Type(type);
    this->power = power;
    this->accuracy = accuracy;
    this->pp = this->maxpp = maxpp;
    this->change_stats_opponent = change_stats_opponent;
    this->change_stats_own = change_stats_own;
}

std::string Move::get_name() const {
    return name;
}

Type Move::get_type() const {
    return type;
}

int Move::get_power() const {
    return power;
}

int Move::get_accuracy() const {
    return accuracy;
}

int Move::get_maxpp() const {
    return maxpp;
}

int Move::get_pp() const {
    return pp;
}

Stats Move::get_change_stats_opponent() const {
    return change_stats_opponent;
}

Stats Move::get_change_stats_own() const {
    return change_stats_own;
}

void Move::restore_pp() {
    pp = maxpp;
}

void Move::print_stats() const {
    std::cout << "  Name: " << name << std::endl;
    std::cout << "  Type: " << type.get_name() << std::endl;
    std::cout << "  PP: " << pp << std::endl;
    std::cout << "  Power: " << power << std::endl;
    std::cout << "  Accuracy: " << accuracy << std::endl;
    
    if (change_stats_opponent.attack < 0) std::cout << "  Opponent's attack is reduced by " << -change_stats_opponent.attack << std::endl;
    if (change_stats_opponent.attack > 0) std::cout << "  Opponent's attack is increased by " << change_stats_opponent.attack << std::endl;
    if (change_stats_opponent.defense < 0) std::cout << "  Opponent's defense is reduced by " << -change_stats_opponent.defense << std::endl;
    if (change_stats_opponent.defense > 0) std::cout << "  Opponent's defense is increased by " << change_stats_opponent.defense << std::endl;
    if (change_stats_opponent.spattack < 0) std::cout << "  Opponent's special attack is reduced by " << -change_stats_opponent.spattack << std::endl;
    if (change_stats_opponent.spattack > 0) std::cout << "  Opponent's special attack is increased by " << change_stats_opponent.spattack << std::endl;
    if (change_stats_opponent.spdefense < 0) std::cout << "  Opponent's special defense is reduced by " << -change_stats_opponent.spdefense << std::endl;
    if (change_stats_opponent.spdefense > 0) std::cout << "  Opponent's special defense is increased by " << change_stats_opponent.spdefense << std::endl;
    if (change_stats_opponent.speed < 0) std::cout << "  Opponent's speed is reduced by " << -change_stats_opponent.speed << std::endl;
    if (change_stats_opponent.speed > 0) std::cout << "  Opponent's speed is increased by " << change_stats_opponent.speed << std::endl;

    if (change_stats_own.attack < 0) std::cout << "  Own attack is reduced by " << -change_stats_own.attack << std::endl;
    if (change_stats_own.attack > 0) std::cout << "  Own attack is increased by " << change_stats_own.attack << std::endl;
    if (change_stats_own.defense < 0) std::cout << "  Own defense is reduced by " << -change_stats_own.defense << std::endl;
    if (change_stats_own.defense > 0) std::cout << "  Own defense is increased by " << change_stats_own.defense << std::endl;
    if (change_stats_own.spattack < 0) std::cout << "  Own special attack is reduced by " << -change_stats_own.spattack << std::endl;
    if (change_stats_own.spattack > 0) std::cout << "  Own special attack is increased by " << change_stats_own.spattack << std::endl;
    if (change_stats_own.spdefense < 0) std::cout << "  Own special defense is reduced by " << -change_stats_own.spdefense << std::endl;
    if (change_stats_own.spdefense > 0) std::cout << "  Own special defense is increased by " << change_stats_own.spdefense << std::endl;
    if (change_stats_own.speed < 0) std::cout << "  Own speed is reduced by " << -change_stats_own.speed << std::endl;
    if (change_stats_own.speed > 0) std::cout << "  Own speed is increased by " << change_stats_own.speed << std::endl;
}
