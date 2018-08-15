#include "Item.hh"

Item::Item() {}

Item::Item(int type, int restored_hp, int restored_pp, const Stats& improvement) {
    this->type = type;
    this->restored_hp = restored_hp;
    this->restored_pp = restored_pp;
    this->improvement = improvement;
}

int Item::get_type() {
    return type;
}

int Item::get_restored_hp() {
    return restored_hp;
}

int Item::get_restored_pp() {
    return restored_pp;
}

Stats Item::get_improvement() {
    return improvement;
}
