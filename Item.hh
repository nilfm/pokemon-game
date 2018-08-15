#ifndef ITEM_HH
#define ITEM_HH

class Item {
private:
    int type;
    int restored_hp;
    int restored_pp;
    Stats improvement;
    
public:
    /* Pre: True */
    /* Post: Default constructor */
    Item();
    
    /* Pre: True */
    /* Post: Creates an Item object that has the given stats */
    Item(int type, int restored_hp, int restored_pp, const Stats& improvement);
    
    /* Pre: True */
    /* Post: Returns 0 if the item is used on a move (restore PP's)
     *       Returns 1 if the item is used on all 4 moves (restore PP's)
     *       Returns 2 if the item is used on a Pokemon (restore HP)
     *       Returns 3 if the item is used on a Pokemon (improve stats) */
    int get_type();
    
    /* Pre: True */
    /* Post: Returns the HP restored by this item */
    int get_restored_hp();
    
    /* Pre: True */
    /* Post: Returns the PP restored by this item */
    int get_restored_pp();
    
    /* Pre: True */
    /* Post: Returns the stat improvement caused by this item */
    Stats get_improvement();
};

#endif
