#include "includes"
#include "Type.hh"

Type::Type(std::string name) {
	this->name = name;
}

std::string Type::get_name() {
	std::unordered_map<std::string, int>::iterator it = types.find(name);
	assert(it != types.end());
	return name;
}

static int Type::advantage(Type t1, Type t2) {
	std::string name1 = t1.get_name();
	std::string name2 = t2.get_name();
	return advantage(name1, name2);
}

static int Type::advantage(std::string t1, std::string t2) {
	std::unordered_map<std::string, int>::iterator it1 = types.find(t1);
	std::unordered_map<std::string, int>::iterator it2 = types.find(t2);
	assert(it1 != types.end() and it2 != types.end());
	int n1 = types[name1];
	int n2 = types[name2];
	return weaknesses[n1][n2];
}

static void Type::initialize() {
	types["FIGHT"] = 0;
	types["FLYING"] = 1;
	types["POISON"] = 2;
	types["GROUND"] = 3;
	types["ROCK"] = 4;
	types["BUG"] = 5;
	types["FIRE"] = 6;
	types["WATER"] = 7;
	types["GRASS"] = 8;
	types["ELECTRIC"] = 9;
	types["PSYCHIC"] = 10;
	types["ICE"] = 11;
	
	weaknesses.resize(12, vector<int>(12));
	weaknesses[0] = {0, -1, -1, 0, 1, -1, 0, 0, 0, 0, 0, 0}
	weaknesses[1] = {1, 0, 0, 0, -1, 1, 0, 0, 1, -1, 0, 0}
	weaknesses[2] = {0, 0, -1, -1, -1, 1, 0, 0, 1, 0, 0, 0}
	weaknesses[3] = {0, -2, 1, 0, 1, -1, 1, 0, -1, 1, 0, 0}
	weaknesses[4] = {-1, 1, 0, -1, 0, 1, 1, 0, 0, 0, 0, 1,}
	weaknesses[5] = {-1, -1, 1, 0, 0, 0, -1, 0, 1, 0, 1, 0}
	weaknesses[6] = {0, 0, 0, 0, -1, 1, -1, -1, 1, 0, 0, 1}
	weaknesses[7] = {0, 0, 0, 1, 1, 0, 1, -1, -1, 0, 0, 0} 
	weaknesses[8] = {0, -1, -1, 1, 1, -1, -1, 1, -1, 0, 0, 0}
	weaknesses[9] = {0, 1, 0, -2, 0, 0, 0, 1, -1, -1, 0, 0}
	weaknesses[10] = {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0}
	weaknesses[11] = {0, 1, 0, 1, 0, 0, 0, -1, 1, 0, 0, -1}
}

