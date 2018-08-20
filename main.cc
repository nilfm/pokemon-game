#include "Includes.hh"
#include "Type.hh"
#include "Move.hh"
#include "Pokedex.hh"
#include "Pokemon.hh"
#include "Pokebase.hh"
#include "Player.hh"
#include "Random.hh"
#include "Enemy.hh"

int main() {
    //Things to initialize
    srand(time(0));
    Type::initialize();
    Pokedex::initialize("addresses.txt");
    Item::initialize_items("Pokedata/Items.txt");
    
    //Welcome message
    std::cout << "Welcome to Pokegame" << std::endl << std::endl;
    
    //Show all saved games
    for (int i = 1; i <= 9; i++) {
        std::cout << "Game " << i << ": ";
        Player save(i);
        if (save.is_empty()) { //file is empty
            std::cout << "Not started" << std::endl;
        }
        else {
            save.load();
            save.presentation();
        }
    }
    std::cout << std::endl;
    
    //Get input for which game to open
    std::string query = "Enter a number from 1 to 9 to choose the game to load. \nIf it's not started, a new game will start: ";
    std::string error = "Oops. Enter a number between 1 and 9."; 
    int slot = Input::read_int(1, 9, query, error);
    
    Player player(slot);
    //If new game
    if (player.is_empty()) { 
        std::cout << "New game!" << std::endl;
        std::cout << "What's your name?" << std::endl;
        std::string name;
        std::cin >> name;
        player.set_name(name);
        std::cout << std::endl;
        player.set_team(player.choose_starters());
    }
    //If continuing game
    else {
        std::cout << "Loading game " << slot << std::endl;
        player.load();
        std::cout << "Hi, " << player.get_name() << std::endl << std::endl;
    }
        
    bool cont = true;
    
    //MAIN LOOP
    while (cont) {
        player.save();
        std::cout << "\nTrainers beaten: " << player.get_trainers() << std::endl << std::endl;
        std::string menu_query = "Menu:\n  0. Quit game\n  1. Go to next fight\n  2. Go to the shop\n  3. See Pokemon stats\n  4. Order your team\n  5. See inventory\n";
        std::string menu_error = "Oops. Enter a number between 0 and 5";
        int choice = Input::read_int(0, 5, menu_query, menu_error);
        std::cout << std::endl;
        
        if (choice == 1) {
            std::cerr << "Sorry, the feature's not ready yet" << std::endl;
            player.increment_trainers();
            Enemy enemy(player.get_trainers());
            //Combat combat(player, enemy);
            //...
            //if (player_wins) 
            //  -"yes you won!"
            //  -Pick a pokemon from enemy team (0 = dont want to pick any)
            //else
            //  -"oh no you lost"
            //  -cont = false;
            //  -register to high scores
            //  -player.save_empty()
        }
        else if (choice == 2) {
            player.shop();
        }
        else if (choice == 3) {
            player.show_team_stats();
        }
        else if (choice == 4) {
            player.sort_team();
        }
        else if (choice == 5) {
            player.show_inventory();
        }
        else cont = false;
    }
    
    //Save and quit
    player.save();
}
