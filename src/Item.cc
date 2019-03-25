#include "../inc/Item.hh"

std::unordered_map<std::string, Item> Item::items;

//CONSTRUCTORS
Item::Item() {}

Item::Item(const std::string name, int price, int type, int restored_hp, int restored_pp, const Stats& improvement, const Status& status_heal) {
    this->name = name;
    this->type = type;
    this->restored_hp = restored_hp;
    this->restored_pp = restored_pp;
    this->improvement = improvement;
    this->price = price;
    this->status = status_heal;
}

//GETTERS
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

Status Item::get_status_heal() const {
    return status;
}

std::string Item::get_name() const {
    return name;
}

Item Item::get_item(const std::string& name) {
    std::unordered_map<std::string, Item>::const_iterator it = items.find(name);
    assert(it != items.end());
    return it->second;
}


//INITIALIZERS
void Item::initialize_items(const std::string address) {
    std::ifstream in(address);
    assert(in.is_open());
    std::string name;
    int type, price, restored_hp, restored_pp;
    Stats improv;
    Status status;
    while (in >> name >> type >> price >> restored_hp >> restored_pp >> improv.attack >> improv.defense >> improv.spattack >> improv.spdefense >> improv.speed >> improv.maxhp >> status.poison >> status.burn >> status.stun) {
        items[name] = Item(name, price, type, restored_hp, restored_pp, improv, status);
    }
}


//OPERATORS
bool Item::operator<(const Item& i) const {
    return name < i.name;
}

