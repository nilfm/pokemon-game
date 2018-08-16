#ifndef MOVE_HH
#define MOVE_HH

#include "Includes.hh"
#include "Type.hh"

class Move {
private:
    std::string name;
    Type type;
    int power, accuracy, maxpp, pp;
    bool special;
    Stats change_stats_opponent;
    Stats change_stats_own;
    
public:
    /* Pre: True */
    /* Post: Default constructor */
    Move();

    /* Pre: True */
    /* Post: Assigns to the move the stats given */
    Move(bool special, const std::string& name, const std::string& type, int power, int accuracy, int maxpp, const Stats& change_stats_opponent, const Stats& change_stats_own);

    /* Pre: True */
    /* Post: Returns the name of the move */
    std::string get_name() const;
    
    /* Pre: True */
    /* Post: Returns the type of the move */
    Type get_type() const;
    
    /* Pre: True */
    /* Post: Returns the power of the move */
    int get_power() const;
    
    /* Pre: True */
    /* Post: Returns the accuracy of the move */
    int get_accuracy() const;
    
    /* Pre: True */
    /* Post: Returns the PP of the move */
    int get_pp() const;

    /* Pre: True */
    /* Post: Returns the maximum PP of the move */
    int get_maxpp() const;
    
    /* Pre: True */
    /* Post: Returns the struct that holds the stat changes caused on the opponent by the move */
    Stats get_change_stats_opponent() const;
    
    /* Pre: True */
    /* Post: Returns the struct that holds the stat changes caused on itself by the move */
    Stats get_change_stats_own() const;
    
    /* Pre: True */
    /* Post: Restores this move's PP to its maximum value */
    void restore_pp();
    
    /* Pre: True */
    /* Post: Prints a formatted list with the stats for this move */
    void print_stats() const;
};

#endif
