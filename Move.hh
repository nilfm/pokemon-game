#ifndef MOVE_HH
#define MOVE_HH

#include "includes.hh"
#include "Type.hh"

class Move {
private:
    std::string name;
    Type type;
    int power, accuracy, maxpp, pp;
    bool special;
    
    std::string description;

public:
    /* Pre: True */
    /* Post: Default constructor */
    Move();

    /* Pre: TODO */
    /* Post: TODO */
    Move(bool special, const std::string& name, const std::string& type, int power, int accuracy, const std::string& description, int maxpp);

    /* Pre: TODO */
    /* Post: TODO */
    std::string get_name() const;
    
    /* Pre: TODO */
    /* Post: TODO */
    Type get_type() const;
    
    /* Pre: TODO */
    /* Post: TODO */
    int get_power() const;
    
    /* Pre: TODO */
    /* Post: TODO */
    int get_accuracy() const;
    
    /* Pre: TODO */
    /* Post: TODO */
    std::string get_description() const;
    
    /* Pre: TODO */
    /* Post: TODO */
    int get_pp() const;

    /* Pre: TODO */
    /* Post: TODO */
    int get_maxpp() const;
    
    /* Pre: TODO */
    /* Post: TODO */
    void restore_pp();
};

#endif
