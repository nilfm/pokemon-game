#include "Includes.hh"
#include "Type.hh"
#include "Move.hh"
#include "Pokedex.hh"
#include "Pokemon.hh"
#include "Pokebase.hh"
#include "Player.hh"
#include "Random.hh"
#include "Combat.hh"

int main() {
    //Things to initialize
    srand(time(0));
    Type::initialize(); //has to be before Pokedex and Move
    Move::initialize_moves("Data/Moves.txt"); //has to be before Pokedex
    Pokedex::initialize("Data/Addresses.txt");
    Item::initialize_items("Data/Items.txt");
    
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
        std::cout << std::endl;
        player.set_name(name);
        player.set_team(player.choose_starters());
    }
    //If continuing game
    else {
        std::cout << "Loading game " << slot << std::endl;
        player.load();
        std::cout << "Hi, " << player.get_name() << "!" << std::endl << std::endl;
    }
        
    bool cont = true;
    
    //MAIN LOOP
    while (cont) {
        player.save();
        std::cout << "\nTrainers beaten: " << player.get_trainers() << std::endl << std::endl;
        std::string menu_query = "Menu:\n  0. Quit game\n  1. Go to next fight\n  2. Go to the shop\n  3. See Pokemon stats\n  4. Sort your team\n  5. See inventory\n";
        std::string menu_error = "Oops. Enter a number between 0 and 5";
        int choice = Input::read_int(0, 5, menu_query, menu_error);
        std::cout << std::endl;
        
        if (choice == 1) {
            player.increment_trainers();
            Player enemy(player.get_trainers(), true);
            Combat combat(player, enemy);
            int winner = 0;
            while (not winner) {
                winner = combat.play_turn();
            }
            if (winner == 1) {
                std::cout << "You won!" << std::endl;
                std::cout << "You earned 500 coins" << std::endl << std::endl;
                player.increment_money(500);
                combat.pick_enemy_pokemon();
                player.heal_pokemon();
            }
            else {
                std::cout << "Oh no! You lost!" << std::endl;
                player.clear_file();
                cont = false;
                //register high score
            }
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
}
