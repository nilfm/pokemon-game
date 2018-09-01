#ifndef TYPE_HH
#define TYPE_HH

#include "Includes.hh"

namespace Type {
    extern std::unordered_map<std::string, int> types;
    extern std::vector<std::vector <int> > weaknesses;

    //INFORMATION
    /* Pre: Type 1 and 2 are valid names for types */
    /* Post: Returns 1 if t1 is super effective vs t2
     *       Returns 0 if t1 is neutral vs t2
     *       Returns -1 if t1 is not very effective vs t2
     *       Returns -2 if t1 can't damage t2 */
    int advantage(std::string t1, std::string t2);
    
    
    //INITIALIZERS
    /* Pre: True */
    /* Post: When called, fills up the data tables for this class */
    void initialize();
}

#endif
