#include "includes.hh"
#include "Pokemon.hh"
#include "Type.hh"

Pokemon::Pokemon(const Pokebase& p, int level) {
    //Copy type, name
    type = p.get_type();
    name = p.get_name();
    //Calculate stats at that level
    xp = 5*level*(level-1);
    attack = p.get_attack() + (level-1)*p.get_attack_level();
    defense = p.get_defense() + (level-1)*p.get_defense_level();
    spattack = p.get_spattack() + (level-1)*p.get_spattack_level();
    spdefense = p.get_spdefense() + (level-1)*p.get_spdefense_level();
    speed = p.get_speed() + (level-1)*p.get_speed_level();
    maxhp = p.get_maxhp() + (level-1)*p.get_maxhp_level();
    //Choose the 4 (at most) latest moves the Pokemon can learn at that level
    moveset = p.get_moveset();
    int count_moves = 0;
    for (int i = level; i > 0 and count_moves < MAX_MOVES; i--) {
        map<int, Move>::iterator it = moveset.find(i);
        if (it != moveset.end()) {
            moves.push_back(it->second);
            count_moves++;
        }
    }
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

Type Pokemon::get_type() const {
    return type;
}

void Pokemon::restore_health(int health) {
    if (health == -1) hp = maxhp;
    else hp = std::min(maxhp, hp + health);
}
