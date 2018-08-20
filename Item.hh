#ifndef ITEM_HH
#define ITEM_HH

#include "Includes.hh"

class Item {
private:
    std::string name;
    int type;
    int restored_hp;
    int restored_pp;
    int price;
    Stats improvement;
    static std::unordered_map<std::string, Item> items;
    
public:
    //CONSTRUCTORS
    /* Pre: True */
    /* Post: Default constructor */
    Item();
    
    /* Pre: True */
    /* Post: Creates an Item object that has the given stats */
    Item(const std::string name, int price, int type, int restored_hp, int restored_pp, const Stats& improvement);
    
    
    //GETTERS
    /* Pre: True */
    /* Post: Returns 0 if the item is used on a move (restore PP's)
     *       Returns 1 if the item is used on all 4 moves (restore PP's)
     *       Returns 2 if the item is used on a Pokemon (restore HP)
     *       Returns 3 if the item is used on a Pokemon (improve stats) */
    int get_type() const;
    
    /* Pre: True */
    /* Post: Returns the HP restored by this item */
    int get_restored_hp() const;
    
    /* Pre: True */
    /* Post: Returns the PP restored by this item */
    int get_restored_pp() const;
    
    /* Pre: True */
    /* Post: Returns the item's price */
    int get_price() const;
    
    /* Pre: True */
    /* Post: Returns the item's name */
    std::string get_name() const;
    
    /* Pre: True */
    /* Post: Returns the stat improvement caused by this item */
    Stats get_improvement() const;
    
    /* Pre: name is a valid name for an item */
    /* Post: Returns the item with the given name */
    static Item get_item(const std::string& name);
    
    
    //INITIALIZERS
    /* Pre: address contains the address for a file with all the item info */
    /* Post: Returns a map with all items with their names as keys */
    static void initialize_items(const std::string address);
    
    
    //OPERATORS
    bool operator<(const Item& i) const;
};

#endif
