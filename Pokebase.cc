#include "includes.hh"
#include "Pokebase.hh"

Pokebase::Pokebase(const std::string& address) {
	std::ifstream in(address);
	assert(in.is_open());
	
	//TODO
	
	in.close();
}

std::string Pokebase::get_name() const {
	return name;
}
