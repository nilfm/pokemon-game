#include "includes.hh"
#include "Item.hh"

Item::Item() {}

Item::Item(int restored_hp, int restored_pp) {
    this->restored_hp = restored_hp;
    this->restored_pp = restored_pp;
}

int Item::get_restored_hp() {
    return restored_hp;
}

int Item::get_restored_pp() {
    return restored_pp;
}
