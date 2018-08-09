#ifndef MOVE_HH
#define MOVE_HH

#include "includes.hh"
#include "Type.hh"

class Move {
private:
	std::string name;
	Type type;
	int power, accuracy, maxpp, pp;
	bool special;
	
	std::string description;

public:
	/* Pre: TODO */
	/* Post: TODO */
	Move(bool special, std::string name, std::string type, int power, int accuracy, const std::string& description, int maxpp);

	/* Pre: TODO */
	/* Post: TODO */
	std::string get_name();
	
	/* Pre: TODO */
	/* Post: TODO */
	Type get_type();
	
	/* Pre: TODO */
	/* Post: TODO */
	int get_power();
	
	/* Pre: TODO */
	/* Post: TODO */
	int get_accuracy();
	
	/* Pre: TODO */
	/* Post: TODO */
	int get_description();
};

#endif
