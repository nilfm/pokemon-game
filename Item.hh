#ifndef ITEM_HH
#define ITEM_HH

class Item {
private:
    int restored_hp;
    int restored_pp;
    
public:
    /* Pre: True */
    /* Post: Default constructor */
    Item();
    
    /* Pre: True */
    /* Post: Creates an Item object that has the given stats */
    Item(int restored_hp, int restored_pp);
    
    /* Pre: True */
    /* Post: Returns the HP restored by this item */
    int get_restored_hp();
    
    /* Pre: True */
    /* Post: Returns the PP restored by this item */
    int get_restored_pp();
};

#endif
