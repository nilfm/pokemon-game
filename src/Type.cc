#include "../inc/Type.hh"

std::unordered_map<std::string, int> Type::types;
std::vector<std::vector <int> > Type::weaknesses;

//INFORMATION
int Type::advantage(std::string t1, std::string t2) {
    std::unordered_map<std::string, int>::iterator it1 = types.find(t1);
    std::unordered_map<std::string, int>::iterator it2 = types.find(t2);
    assert(it1 != types.end() and it2 != types.end());
    int n1 = types[t1];
    int n2 = types[t2];
    return weaknesses[n1][n2];
}


//INITIALIZERS
void Type::initialize() {
    types["NORMAL"] = 0;
    types["FIGHTING"] = 1;
    types["FLYING"] = 2;
    types["POISON"] = 3;
    types["GROUND"] = 4;
    types["ROCK"] = 5;
    types["BUG"] = 6;
    types["GHOST"] = 7;
    types["STEEL"] = 8;
    types["FIRE"] = 9;
    types["WATER"] = 10;
    types["GRASS"] = 11;
    types["ELECTRIC"] = 12;
    types["PSYCHIC"] = 13;
    types["ICE"] = 14;
    types["DRAGON"] = 15;
    types["DARK"] = 16;
    
    weaknesses.resize(17, std::vector<int>(17));
    weaknesses[0] = {0, 0, 0, 0, 0, -1, 0, -2, -1, 0, 0, 0, 0, 0, 0, 0, 0};
    weaknesses[1] = {1, 0, -1, -1, 0, 1, -1, -2, 1, 0, 0, 0, 0, -1, 1, 0, 1};
    weaknesses[2] = {0, 1, 0, 0, 0, -1, 1, 0, -1, 0, 0, 1, -1, 0, 0, 0, 0};
    weaknesses[3] = {0, 0, 0, -1, -1, -1, 0, -1, -2, 0, 0, 1, 0, 0, 0, 0, 0};
    weaknesses[4] = {0, 0, -2, 1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0, 0, 0, 0};
    weaknesses[5] = {0, -1, 1, 0, -1, 0, 1, 0, -1, 1, 0, 0, 0, 0, 1, 0, 0};
    weaknesses[6] = {0, -1, -1, -1, 0, 0, 0, -1, -1, -1, 0, 1, 0, 1, 0, 0, 1};
    weaknesses[7] = {-2, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 1, 0, 0, -1};
    weaknesses[8] = {0, 0, 0, 0, 0, 1, 0, 0, -1, -1, -1, 0, -1, 0, 1, 0, 0};
    weaknesses[9] = {0, 0, 0, 0, 0, -1, 1, 0, 1, -1, -1, 1, 0, 0, 1, -1, 0};
    weaknesses[10] = {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, -1, -1, 0, 0, 0, -1, 0};
    weaknesses[11] = {0, 0, -1, -1, 1, 1, -1, 0, -1, -1, 1, -1, 0, 0, 0, -1, 0};
    weaknesses[12] = {0, 0, 1, 0, -2, 0, 0, 0, 0, 0, 1, -1, -1, 0, 0, -1, 0};
    weaknesses[13] = {0, 1, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, -2};
    weaknesses[14] = {0, 0, 1, 0, 1, 0, 0, 0, -1, -1, -1, 1, 0, 0, -1, 1, 0};
    weaknesses[15] = {0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1, 0};
    weaknesses[16] = {0, -1, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 1, 0, 0, -1};
}

