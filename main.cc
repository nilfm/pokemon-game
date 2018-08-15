#include "Includes.hh"

int main() {
    srand(time(0));
    Type::initialize();
    Pokedex pokedex("addresses.txt");
    Player player;
    std::cout << "Welcome to Pokemon Battles" << std::endl;
}
