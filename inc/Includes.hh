#ifndef INCLUDES_HH
#define INCLUDES_HH

#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <unordered_map>
#include <map>
#include <cassert>
#include <iomanip>
#include "Random.hh"
#include "Input.hh"

struct Stats {
    int attack, defense, spattack, spdefense, speed, maxhp;
};

struct Status {
    int poison, burn, stun;
};

#endif
