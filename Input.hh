#ifndef INPUT_HH
#define INPUT_HH

#include <limits>
#include <iostream>
#include <unordered_set>
#include <string>
#include <cassert>

namespace Input {
    /* Pre: choices (non-empty) contains all possible correct choices, query and error are the displayed messages */
    /* Post: returns a string entered by the user which is in the set */
    std::string read_string(const std::unordered_set<std::string>& choices, const std::string& query, const std::string& err);
    
    /* Pre: minimum <= maximum, query and error are the displayed messages */
    /* Post: returns an int (n) entered by the user, minimum <= n <= maximum  */
    int read_int(int minimum, int maximum, const std::string& query, const std::string& err);
    
    /* Pre: minimum <= maximum, query and error are the displayed messages */
    /* Post: returns a double (n) entered by the user, minimum <= n <= maximum  */
    double read_double(int minimum, int maximum, const std::string& query, const std::string& err);
}

#endif
