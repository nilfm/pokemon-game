#include "Pokemon.hh"

Pokemon::Pokemon() {}

Pokemon::Pokemon(const Pokebase& p, int level) {
    //Copy type, name
    type = p.get_type();
    name = p.get_name();
    
    //Calculate stats at that level
    xp = 5*level*(level-1);
    per_level_min   = p.get_level_stats_min();
    per_level_max   = p.get_level_stats_max();
    stats.attack    = p.get_base_stats().attack    + (level-1)*Random::randint(per_level_min.attack, per_level_max.attack);
    stats.defense   = p.get_base_stats().defense   + (level-1)*Random::randint(per_level_min.defense, per_level_max.defense);
    stats.spattack  = p.get_base_stats().spattack  + (level-1)*Random::randint(per_level_min.spattack, per_level_max.spattack);
    stats.spdefense = p.get_base_stats().spdefense + (level-1)*Random::randint(per_level_min.spdefense, per_level_max.spdefense);
    stats.speed     = p.get_base_stats().speed     + (level-1)*Random::randint(per_level_min.speed, per_level_max.speed);
    stats.maxhp     = p.get_base_stats().maxhp     + (level-1)*Random::randint(per_level_min.maxhp, per_level_max.maxhp);
    battle_stats    = stats;
    
    //Evolution stuff
    level_evolution = p.get_level_evolution();
    if (level_evolution != -1) next_evolution = p.get_next_evolution();
    
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

Pokemon::Pokemon(const Pokebase& p, int level, const std::vector<Move>& moves) {
    //Copy type, name
    type = p.get_type();
    name = p.get_name();
    
    //Calculate stats at that level
    xp = 5*level*(level-1);
    per_level_min   = p.get_level_stats_min();
    per_level_max   = p.get_level_stats_max();
    stats.attack    = p.get_base_stats().attack    + (level-1)*Random::randint(per_level_min.attack, per_level_max.attack);
    stats.defense   = p.get_base_stats().defense   + (level-1)*Random::randint(per_level_min.defense, per_level_max.defense);
    stats.spattack  = p.get_base_stats().spattack  + (level-1)*Random::randint(per_level_min.spattack, per_level_max.spattack);
    stats.spdefense = p.get_base_stats().spdefense + (level-1)*Random::randint(per_level_min.spdefense, per_level_max.spdefense);
    stats.speed     = p.get_base_stats().speed     + (level-1)*Random::randint(per_level_min.speed, per_level_max.speed);
    stats.maxhp     = p.get_base_stats().maxhp     + (level-1)*Random::randint(per_level_min.maxhp, per_level_max.maxhp);
    battle_stats    = stats;
    
    //Evolution stuff
    level_evolution = p.get_level_evolution();
    if (level_evolution != -1) next_evolution = p.get_next_evolution();

    //Give it the given moves
    this->moves = moves;
    this->moveset = p.get_moveset();
}

void Pokemon::evolve(const std::string& name_evolution, int level, const Pokedex& pokedex) {
    Pokebase p = pokedex.get_pokebase(name_evolution);
    *this = Pokemon(p, level, this->moves);
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

int Pokemon::get_level_evolution() const {
    return level_evolution;
}

std::string Pokemon::get_next_evolution() const {
    return next_evolution;
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
