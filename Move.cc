#include "includes.hh"
#include "Move.hh"

//TOFIX
Move::Move(bool special, std::string name, std::string type, int power, int accuracy, const std::string& description, int maxpp) {
	this->special = special;
	this->name = name;
	this->type = Type(type);
	this->power = power;
	this->accuracy = accuracy;
	this->description = description;
	this->pp = this->maxpp = maxpp;
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

void Move::restore_pp() {
	pp = maxpp;
}
