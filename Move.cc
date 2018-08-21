#include "Move.hh"

//CONSTRUCTORS
Move::Move() {}

Move::Move(bool special, const std::string& name, const std::string& type, int power, int accuracy, int maxpp, const Stats& change_stats_opponent, const Stats& change_stats_own, const Status& status) {
    this->special = special;
    this->name = name;
    this->type = Type(type);
    this->power = power;
    this->accuracy = accuracy;
    this->pp = this->maxpp = maxpp;
    this->change_stats_opponent = change_stats_opponent;
    this->change_stats_own = change_stats_own;
    this->status = status;
}


//GETTERS
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

Status Move::get_status() const {
    return status;
}

bool Move::is_special() const {
    return special;
}


//SETTERS
void Move::decrement_pp() {
    pp--;
}


//SHOWERS
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
    
    if (status.poison != 0) std::cout << "  Has a " << status.poison << "% chance of poisoning the enemy" << std::endl;
    if (status.burn != 0) std::cout << "  Has a " << status.burn << "% chance of burning the enemy" << std::endl;
    if (status.stun != 0) std::cout << "  Has a " << status.stun << "% chance of stunning the enemy" << std::endl;
}


//ACTIONS
void Move::restore_pp(int restore) {
    if (restore == -1) pp = maxpp;
    else pp = std::min(pp + restore, maxpp);
}


//SEARCHERS
Move Move::search_move(const std::string& name, const std::map<int, std::vector<Move> >& moveset) {
    Move to_return;
    bool found = false;
    for (std::map<int, std::vector<Move> >::const_iterator it = moveset.begin(); it != moveset.end() and not found; it++) {
        for (int j = 0; j < (int)(it->second).size() and not found; j++) {
            if ((it->second)[j].get_name() == name) {
                found = true;
                to_return = (it->second)[j];
            }
        }
    }
    return to_return;
}
