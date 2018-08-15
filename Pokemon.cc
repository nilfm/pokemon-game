#include "includes.hh"
#include "Pokemon.hh"

Pokemon::Pokemon(const Pokebase& p, int level) {
    //Copy type, name
    type = p.get_type();
    name = p.get_name();
    //Calculate stats at that level
    xp = 5*level*(level-1);
    stats.attack = p.get_base_stats().attack + (level-1)*p.get_level_stats().attack;
    stats.defense = p.get_base_stats().defense + (level-1)*p.get_level_stats().defense;
    stats.spattack = p.get_base_stats().spattack + (level-1)*p.get_level_stats().spattack;
    stats.spdefense = p.get_base_stats().spdefense + (level-1)*p.get_level_stats().spdefense;
    stats.speed = p.get_base_stats().speed + (level-1)*p.get_level_stats().speed;
    stats.maxhp = p.get_base_stats().maxhp + (level-1)*p.get_level_stats().maxhp;
    battle_stats = stats;
    //Choose the 4 (at most) latest moves the Pokemon can learn at that level
    moveset = p.get_moveset();
    int count_moves = 0;
    for (int i = level; i > 0 and count_moves < MAX_MOVES; i--) {
        std::map<int, Move>::iterator it = moveset.find(i);
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

int Pokemon::get_hp() const {
    return hp;
}

Stats Pokemon::get_stats() const {
    return stats;
}

std::string Pokemon::get_name() const {
    return name;
}

Type Pokemon::get_type() const {
    return type;
}

void Pokemon::restore_health(int health) {
    if (health == -1) hp = stats.maxhp;
    else hp = std::min(stats.maxhp, hp + health);
}
