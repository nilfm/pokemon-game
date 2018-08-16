#include "Includes.hh"
#include "Globals.hh"

int main() {
    srand(time(0));
    Type::initialize();
    Pokedex::initialize("addresses.txt");
    Player player;
    std::cout << "Welcome to Pokemon Battles" << std::endl;
}
