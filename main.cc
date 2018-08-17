#include "Includes.hh"
#include "Type.hh"
#include "Move.hh"
#include "Pokedex.hh"
#include "Pokemon.hh"
#include "Pokebase.hh"
#include "Player.hh"
#include "Random.hh"

//Add a number between 1 and 9 and the extension .txt to the end to get the full address
const std::string gamesave_address = "Saves/GameSave";

bool is_empty(const std::string& address) {
    std::ifstream in(address);
    assert(in.is_open());
    std::string s = "";
    int count = 0;
    while (in >> s) count++;
    return count == 0 and s == "";
    in.close();
}

int main() {
    //Things to initialize
    srand(time(0));
    Type::initialize();
    Pokedex::initialize("addresses.txt");
    std::map<std::string, Item> items = Item::initialize_items("Pokedata/Items.txt");
    
    //Start game! (Should refactor this into a class maybe, GameStatus/whatever)
    std::cout << "Welcome to Pokegame" << std::endl << std::endl;
    
    for (int i = 1; i <= 9; i++) {
        std::cout << "Game " << i << ": ";
        std::string addr = gamesave_address + std::to_string(i) + ".txt";
        std::ifstream in(addr);
        assert(in.is_open());
        
        if (is_empty(addr)) { //file is empty
            std::cout << "Not started" << std::endl;
        }
        
        else {
            std::string name;
            int trainers;
            in >> name >> trainers;
            std::cout << name << " - Trainer " << trainers << std::endl;
        }
        
        in.close();
    }
    std::cout << std::endl;
    
    std::string query = "Enter a number from 1 to 9 to choose the game to load. \nIf it's not started, a new game will start: ";
    std::string error = "Oops. Enter a number between 1 and 9."; 
    int choice = Input::read_int(1, 9, query, error);
    
    std::string addr = gamesave_address + std::to_string(choice) + ".txt";
    std::ifstream in(addr);
    assert(in.is_open());
    if (is_empty(addr)) std::cout << "New game!" << std::endl;
    else std::cout << "Loading game " << choice << std::endl;
    
    in.close();
}
