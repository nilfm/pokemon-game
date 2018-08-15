#ifndef TYPE_HH
#define TYPE_HH

#include "Includes.hh"

class Type {
private:
    static std::unordered_map<std::string, int> types;
    static std::vector<std::vector <int> > weaknesses;
    std::string name;

public:
    /* Pre: True */
    /* Post: Default constructor */
    Type();
    
    /* Pre: True */
    /* Post: Creates a type object with the name given */
    Type(std::string name);

    /* Pre: True */
    /* Post: Returns the name of the type */
    std::string get_name();
    
    /* Pre: Type 1 and 2 are valid types */
    /* Post: Returns 1 if t1 is super effective vs t2
     *       Returns 0 if t1 is neutral vs t2
     *       Returns -1 if t1 is not very effective vs t2
     *       Returns -2 if t1 can't damage t2 */
    static int advantage(Type t1, Type t2);
    
    /* Pre: Type 1 and 2 are valid names for types */
    /* Post: Returns 1 if t1 is super effective vs t2
     *       Returns 0 if t1 is neutral vs t2
     *       Returns -1 if t1 is not very effective vs t2
     *       Returns -2 if t1 can't damage t2 */
    static int advantage(std::string t1, std::string t2);
        
    /* Pre: True */
    /* Post: When called, fills up the data tables for this class */
    static void initialize();
};

#endif
