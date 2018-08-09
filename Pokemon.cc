#include "includes.hh"
#include "Pokemon.hh"
#include "Type.hh"

Pokemon::Pokemon(const Pokebase& p, int level) {
	//TODO
}

int Pokemon::get_xp() const {
	return xp;
}

int Pokemon::get_level() const {
	return level;
}

int Pokemon::get_maxhp() const {
	return maxhp;
}

int Pokemon::get_hp() const {
	return hp;
}

int Pokemon::get_attack() const {
	return attack;
}

int Pokemon::get_defense() const {
	return defense;
}

int Pokemon::get_spattack() const {
	return spattack;
}

int Pokemon::get_spdefense() const {
	return spdefense;
}

int Pokemon::get_speed() const {
	return speed;
}

std::string Pokemon::get_name() const {
	return name;
}

Type get_type() const {
	return type;
}

void Pokemon::restore_health(int health) {
	if (health == -1) hp = maxhp;
	else hp = std::min(maxhp, hp + health);
}
