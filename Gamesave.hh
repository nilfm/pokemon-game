#ifndef GAMESAVE_HH
#define GAMESAVE_HH

#include "Includes.hh"
#include "Pokemon.hh"
#include "Item.hh"
#include "Move.hh"
#include "Pokedex.hh"
#include "Pokebase.hh"

class Gamesave {
private:
    static const std::string gamesave_address;
    static const std::string address_extension;
    std::string name;
    int slot; //from 1 to 9
    int money;
    int trainers; //trainers beaten
    std::vector<Pokemon> team;
    std::map<Item, int> inventory;

public:
    /* Pre: 1 <= slot <= 9 */
    /* Post: Returns an empty gamesave, using the given slot */
    Gamesave(int slot);
    
    /* Pre: This gamesave hasn't loaded yet, the slot isn't empty */
    /* Post: Reads the file at the corresponding slot and loads the game */
    void load();
    
    /* Pre: True */
    /* Post: Removes all the contents from the file associated to the gamesave */
    void save_empty();
    
    /* Pre: True */
    /* Post: Updates the internal state of the gamesave with the information given */
    void update(const std::string& name, int money, int trainers, const std::vector<Pokemon>& team, const std::map<Item, int>& inventory);
    
    /* Pre: True */
    /* Post: Saves the given data to the file associated to the gamesave */
    void save();
    
    /* Pre: The file is not empty, the gamesave is loaded */
    /* Post: Prints a formatted output to the console of name and trainers */
    void presentation();
    
    /* Pre: True */
    /* Post: Returns true if the gamesave address refers to an empty file */
    bool is_empty();
    
    /* Pre: True */
    /* Post: Returns the address for the file for the gamesave */
    std::string get_address();
    
    /* Pre: True */
    /* Post: Returns the name saved */
    std::string get_name() const;
    
    /* Pre: True */
    /* Post: Returns the money saved */
    int get_money() const;
    
    /* Pre: True */
    /* Post: Returns the trainers saved */
    int get_trainers() const;
    
    /* Pre: True */
    /* Post: Returns the team saved */
    std::vector<Pokemon> get_team() const;
    
    /* Pre: True */
    /* Post: Returns the inventory saved */
    std::map<Item, int> get_inventory() const;
    
};

#endif
