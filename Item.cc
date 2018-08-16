#include "Item.hh"

Item::Item() {}

Item::Item(const std::string name, int price, int type, int restored_hp, int restored_pp, const Stats& improvement) {
    this->name = name;
    this->type = type;
    this->restored_hp = restored_hp;
    this->restored_pp = restored_pp;
    this->improvement = improvement;
    this->price = price;
}

int Item::get_type() const {
    return type;
}

int Item::get_restored_hp() const {
    return restored_hp;
}

int Item::get_restored_pp() const {
    return restored_pp;
}

int Item::get_price() const {
    return price;
}

Stats Item::get_improvement() const {
    return improvement;
}

std::string Item::get_name() const {
    return name;
}

std::map<std::string, Item> Item::initialize_items(const std::string address) {
    std::map<std::string, Item> items;
    std::ifstream in(address);
    assert(in.is_open());
    std::string name;
    int type, price, restored_hp, restored_pp;
    Stats improv;
    while (in >> name >> type >> price >> restored_hp >> restored_pp >> improv.attack >> improv.defense >> improv.spattack >> improv.spdefense >> improv.speed >> improv.maxhp) {
        items[name] = Item(name, price, type, restored_hp, restored_pp, improv);
    }
    return items;
}
