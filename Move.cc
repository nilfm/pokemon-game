#include "includes.hh"
#include "Move.hh"

Move::Move(bool special, std::string name, std::string type, int power, int accuracy, const std::string& description, int maxpp) {
	this->special = special;
	this->name = name;
	this->type = Type(type);
	this->power = power;
	this->accuracy = accuracy;
	this->description = description;
	this->pp = this->maxpp = maxpp;
}

std::string Move::get_name() {
	return name;
}

Type Move::get_type() {
	return type;
}

int Move::get_power() {
	return power;
}

int Move::get_accuracy() {
	return accuracy;
}

int Move::get_description() {
	return description;
}
