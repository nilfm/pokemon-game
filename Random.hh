#ifndef Random_HH
#define Random_HH

#include <ctime>
#include <cstdlib>

namespace Random {
    /* Pre: maximum >= minimum */
    /* Post: Returns a Random number n such that minimum <= n <= maximum */
    int randint(int minimum, int maximum);
}

#endif
