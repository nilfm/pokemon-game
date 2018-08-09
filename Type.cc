#include "includes.hh"
#include "Type.hh"

Type::Type(std::string name) {
	this->name = name;
}

std::string Type::get_name() {
	std::unordered_map<std::string, int>::iterator it = types.find(name);
	assert(it != types.end());
	return name;
}

int Type::advantage(Type t1, Type t2) {
	std::string name1 = t1.get_name();
	std::string name2 = t2.get_name();
	return advantage(name1, name2);
}

int Type::advantage(std::string t1, std::string t2) {
	std::unordered_map<std::string, int>::iterator it1 = types.find(t1);
	std::unordered_map<std::string, int>::iterator it2 = types.find(t2);
	assert(it1 != types.end() and it2 != types.end());
	int n1 = types[t1];
	int n2 = types[t2];
	return weaknesses[n1][n2];
}

void Type::initialize() {
	types["NORMAL"] = 0;
	types["FIGHT"] = 1;
	types["FLYING"] = 2;
	types["POISON"] = 3;
	types["GROUND"] = 4;
	types["ROCK"] = 5;
	types["BUG"] = 6;
	types["GHOST"] = 7;
	types["FIRE"] = 8;
	types["WATER"] = 9;
	types["GRASS"] = 10;
	types["ELECTRIC"] = 11;
	types["PSYCHIC"] = 12;
	types["ICE"] = 13;
	types["DRAGON"] = 14;
	
	weaknesses.resize(15, std::vector<int>(15));
	weaknesses[0] = {0, 0, 0, 0, 0, -1, 0, -2, 0, 0, 0, 0, 0, 0, 0};
	weaknesses[1] = {1, 0, -1, -1, 0, 1, -1, -2, 0, 0, 0, 0, -1, 1, 0};
	weaknesses[2] = {0, 1, 0, 0, 0, -1, 1, 0, 0, 0, 1, -1, 0, 0, 0};
	weaknesses[3] = {0, 0, 0, -1, -1, -1, 1, -1, 0, 0, 1, 0, 0, 0, 0};
	weaknesses[4] = {0, 0, -2, 1, 0, 1, -1, 0, 1, 0, -1, 1, 0, 0, 0};
	weaknesses[5] = {0, -1, 1, 0, -1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0};
	weaknesses[6] = {0, -1, -1, 1, 0, 0, 0, -1, -1, 0, 1, 0, 1, 0, 0};
	weaknesses[7] = {-2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0};
	weaknesses[8] = {0, 0, 0, 0, 0, -1, 1, 0, -1, -1, 1, 0, 0, 1, -1};
	weaknesses[9] = {0, 0, 0, 0, 1, 1, 0, 0, 1, -1, -1, 0, 0, 0, -1};
	weaknesses[10] = {0, 0, -1, -1, 1, 1, -1, 0, -1, 1, -1, 0, 0, 0, -1};
	weaknesses[11] = {0, 0, 1, 0, -2, 0, 0, 0, 0, 1, -1, -1, 0, 0, -1};
	weaknesses[12] = {0, 1, 0, 1, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0};
	weaknesses[13] = {0, 0, 1, 0, 1, 0, 0, 0, 0, -1, 1, 0, 0, -1, 1};
	weaknesses[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
}

