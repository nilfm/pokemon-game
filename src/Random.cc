#include "../inc/Random.hh"

int Random::randint(int minimum, int maximum) {
    return rand()%(maximum - minimum + 1) + minimum;
}
