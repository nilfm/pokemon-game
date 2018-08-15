#include "Move.hh"

Move::Move() {}

Move::Move(bool special, const std::string& name, const std::string& type, int power, int accuracy, const std::string& description, int maxpp, const Stats& change_stats_opponent, const Stats& change_stats_own) {
    this->special = special;
    this->name = name;
    this->type = Type(type);
    this->power = power;
    this->accuracy = accuracy;
    this->description = description;
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

std::string Move::get_description() const {
    return description;
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
