#include "Player.hh"

const std::string Player::gamesave_address = "Data/Saves/GameSave";
const std::string Player::tiers_address = "Data/Tiers/Tier";
const std::string Player::starters_address = "Data/Tiers/Starters";
const std::string Player::address_extension = ".txt";
const std::vector<std::string> Player::hp_items = {"Potion", "Superpotion", "Hyperpotion", "MaxPotion", "RestoreAll"};
const std::vector<std::string> Player::pp_items = {"Ether", "MaxEther", "Elixir", "MaxElixir"};
const std::vector<std::string> Player::x_items = {"XAttack", "XDefense", "XSpecialAttack", "XSpecialDefense", "XSpeed"};

//CONSTRUCTORS
Player::Player() {}

Player::Player(int slot) {
    this->slot = slot;
    this->money = 1000;
    this->trainers = 0;
}

Player::Player(int trainers, bool AI) { //AI related
    assert(AI);
    //Set the trainer variable
    this->trainers = trainers;
    //Calculate how many Pokemon for each tier
    std::vector<int> tiers = calculate_tiers(trainers);
    //Retrieve those Pokemon on the team vector
    for (int i = 0; i < 4; i++) {
        if (tiers[i] != 0) {
            std::string address = tiers_address + std::to_string(i) + address_extension;
            std::ifstream in(address);
            assert(in.is_open());
            std::vector<std::string> available;
            std::string s;
            while (in >> s) available.push_back(s);
            for (int j = 0; j < tiers[i]; j++) {
                int rnd = Random::randint(0, (int)available.size()-1);
                Pokebase chosen = Pokedex::get_pokebase(available[rnd]);
                //1 <= level <= 100, 0.9*trainer <= level <= trainer
                int level = std::min(std::max(1, Random::randint((int)(0.7*trainers), trainers)), 100);
                team.push_back(Pokemon(chosen, level));
                available.erase(available.begin()+rnd);
            }
            in.close();
        }
    }
}


//SAVE/LOAD
void Player::load() {
    std::string address = get_address();
    std::ifstream in(address);
    
    assert(in.is_open());
    assert(not is_empty());
    in >> name >> money >> trainers;
    
    std::string input;
    while (in >> input and input == "POKEMON") {
        std::string name;
        int level, xp;
        Stats current;
        in >> name >> level >> xp >> current.attack >> current.defense >> current.spattack >> current.spdefense >> current.speed >> current.maxhp;
        std::vector<std::string> moves;
        std::string m;
        while (in >> m and m != "ENDMOVES") moves.push_back(m);
        Pokebase p = Pokedex::get_pokebase(name);
        Pokemon poke(p, level, xp, current, moves);
        team.push_back(poke);
    }
    
    std::string item;
    int quantity;
    while (in >> item >> quantity) {
        Item it = Item::get_item(item);
        inventory[it] = quantity;
    }
    
    in.close();
}

void Player::clear_file() const {
    std::cout << "Cleaning file..." << std::endl;
    std::string address = get_address();
    std::ofstream out(address, std::ios::out | std::ios::trunc);
    out.close();
}

void Player::save() {
    std::string address = get_address();
    std::ofstream out(address);
    assert(out.is_open());
    
    out << name << " " << money << " " << trainers << std::endl;
    for (int i = 0; i < (int)team.size(); i++) {
        out << "POKEMON " << team[i].get_name() << " " << team[i].get_level() << " " << team[i].get_xp() << std::endl;
        Stats stats = team[i].get_stats();
        out << stats.attack << " " << stats.defense << " " << stats.spattack << " " << stats.spdefense << " " << stats.speed << " " << stats.maxhp << std::endl;
        std::vector<Move> moves = team[i].get_moves();
        for (int j = 0; j < (int)moves.size(); j++) {
            out << moves[j].get_name() << std::endl;
        }
        out << "ENDMOVES" << std::endl;
        out << std::endl;
    }
    
    out << "ITEMS" << std::endl;
    
    for (std::map<Item, int>::const_iterator it = inventory.begin(); it != inventory.end(); it++) {
        out << (it->first).get_name() << " " << it->second << std::endl;
    }
    out.close();
} 


//GETTERS
std::string Player::get_address() const {
    return gamesave_address + std::to_string(slot) + address_extension;
}

std::string Player::get_name() const {
    return name;
}

int Player::get_money() const {
    return money;
}

int Player::get_trainers() const {
    return trainers;
}

std::vector<Pokemon> Player::get_team() const {
    return team;
}

Pokemon& Player::get_first_pokemon() {
    return team[0];
}

std::map<Item, int> Player::get_inventory() const {
    return inventory;
}

bool Player::is_empty() const {
    std::string address = get_address();
    std::ifstream in(address);
    assert(in.is_open());
    std::string s = "";
    int count = 0;
    while (in >> s) count++;
    return count == 0 and s == "";
    in.close();
}


//SETTERS
void Player::increment_trainers() {
    trainers++;
}

void Player::increment_money(int added) {
    money += added;
}

void Player::set_name(const std::string& name) {
    this->name = name;
}

void Player::set_team(const std::vector<Pokemon>& team) {
    this->team = team;
}

void Player::heal_pokemon() {
    for (int i = 0; i < (int)team.size(); i++) {
        team[i].reset_battle_stats();
        team[i].restore_health(-1);
        team[i].restore_all_pp();
        Status change;
        change.poison = change.burn = change.stun = 1;
        team[i].restore_status(change);
    }
}

void Player::set_pokemon(const Pokemon& p, int i) {
    team[i] = p;
}

void Player::decrement_item(const std::string& item) {
    Item it = Item::get_item(item);
    inventory[it]--;
    if (inventory[it] == 0) inventory.erase(it);
}


//SHOWERS
void Player::presentation() const {
    std::cout << name << " - Trainer " << trainers << std::endl;
}

void Player::show_team_stats() const {
    assert(team.size() == 3);

    std::cout << std::endl << "TEAM STATS" << std::endl << std::endl;
    for (int i = 0; i < 3; i++) {
        team[i].print_stats();
    }
}

void Player::show_team_inline() const {
    assert(team.size() == 3);
    
    std::cout << "\nYour Pokemon" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "  " << i+1 << ". " << team[i].get_name() << " (Level " << team[i].get_level() << ")   HP " << team[i].get_hp() << "/" << team[i].get_battle_stats().maxhp << std::endl;
    }
}

void Player::show_inventory() const {
    std::cout << "\nInventory:\n";
    for (std::map<Item, int>::const_iterator it = inventory.begin(); it != inventory.end(); it++) {
        std::cout << "  " << it->second << " x " << (it->first).get_name() << std::endl;
    }
    std::cout << std::endl << std::endl;
}


//ACTIONS
void Player::sort_team() {
    assert(team.size() == 3);

    std::cout << "Sorting team" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "  " << i+1 << ". " << team[i].get_name() << "(Level " << team[i].get_level() << ")" << std::endl;
    }
    std::cout << std::endl;

    std::string query1 = "Choose first pokemon to swap (1-3) (0 to exit): ";
    std::string query2 = "Choose second pokemon to swap (1-3) (0 to exit): ";
    std::string error = "Oops. Enter a number between 1 and 3";
    int p1 = Input::read_int(0, 3, query1, error);
    if (p1 == 0) return;
    int p2 = Input::read_int(0, 3, query2, error);
    if (p2 == 0) return;
    bool corr = swap_pokemon(p1-1, p2-1);
    if (not corr) std::cout << "Can't have a fainted Pokemon as your leader" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "  " << i+1 << ". " << team[i].get_name() << " (Level " << team[i].get_level() << ")" << std::endl;
    }
    std::cout << std::endl;
}

bool Player::use_item(int k, const Item& it) {
    int type = it.get_type();
    if (type == 0) { //Restore PP for one move
        std::vector<Move> moves = team[k].get_moves();
        int n = moves.size();
        std::string query = "Which move do you want to restore PP for? ";
        std::string error = "Oops. Enter a number between 1 and " + std::to_string(n) + ".";
        std::cout << std::endl << "Moves:" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "  " << i+1 << ". " << moves[i].get_name() << std::endl;
        }
        std::cout << std::endl;
        int choice = Input::read_int(1, n, query, error);
        team[k].restore_pp(choice-1, it.get_restored_pp());
        std::cout << "Restored PP for " << moves[choice-1].get_name() << "!" << std::endl;
    }
    else if (type == 1) { //Restore PP for all moves
        team[k].restore_all_moves_pp(it.get_restored_pp());
        std::cout << "Restored PP for all moves!" << std::endl << std::endl;
    }
    else if (type == 2) { //Heal
        if (team[k].get_hp() == 0) {
            std::cout << "Cannot heal a fainted Pokemon" << std::endl;
            return false;
        }
        team[k].restore_health(it.get_restored_hp());
        std::cout << team[k].get_name() << " has restored its HP." << std::endl << std::endl;
    }
    else if (type == 3) { //Increase stats
        team[k].add_battle_stats(it.get_improvement());
        std::cout << team[k].get_name() << "'s stats have improved!" << std::endl << std::endl;
    }
    else if (type == 4) { //Heal one type of status
        team[k].restore_status(it.get_status_heal());
        if (it.get_status_heal().poison == 1) std::cout << team[k].get_name() << " is no longer poisoned!" << std::endl << std::endl;
        if (it.get_status_heal().burn == 1) std::cout << team[k].get_name() << " is no longer burnt!" << std::endl << std::endl;
        if (it.get_status_heal().stun == 1) std::cout << team[k].get_name() << " is no longer stunned!" << std::endl << std::endl;
    }
    else if (type == 5) { //Restore all
        team[k].restore_status(it.get_status_heal());
        team[k].restore_health(it.get_restored_hp());
        std::cout << team[k].get_name() << " is fully healed!" << std::endl;
    }
    return true;
}

void Player::use_item_AI(int k) { //AI related
    if (k == 0) { //restore HP
        // up to 15 uses potion, up to 30 uses superpotion, up to 45 uses hyperpotion, up to 60 uses max potion, then uses restore all
        int choice = std::min(trainers/15, 4); 
        Item it = Item::get_item(Player::hp_items[choice]);
        std::cout << "The enemy used " << it.get_name() << "." << std::endl;
        if (choice < 4) { //one of the *potions
            team[0].restore_health(it.get_restored_hp());
            std::cout << "The enemy " << team[0].get_name() << " has restored its HP." << std::endl << std::endl;
        }
        else { //restore all
            team[0].restore_status(it.get_status_heal());
            team[0].restore_health(it.get_restored_hp());
            std::cout << "The enemy " << team[0].get_name() << " is fully healed!" << std::endl;
        }
    }
    else { //restore PP
        int choice = Random::randint(0, 3);
        Item it = Item::get_item(Player::hp_items[choice]);
        std::cout << "The enemy used " << it.get_name() << "." << std::endl;
        if (choice < 2) { //Ether, MaxEther
            std::vector<Move> moves = team[0].get_moves();
            assert(moves.size() > 0); //the move list is not empty
            int minindex = 0;
            int min = moves[0].get_pp();
            for (int i = 1; i < (int)moves.size(); i++) { //search for move with least PP
                if (moves[i].get_pp() < min) {
                    minindex = i;
                    min = moves[i].get_pp();
                }
            }
            team[0].restore_pp(minindex, it.get_restored_pp());
            std::cout << "The enemy restored PP for " << moves[minindex].get_name() << "!" << std::endl;
        }
        else { //Elixir, MaxElixir
            team[0].restore_all_moves_pp(it.get_restored_pp());
            std::cout << "The enemy restored PP for all moves!" << std::endl << std::endl;
        }
    }
}

std::vector<Pokemon> Player::choose_starters() const {
    std::set<std::string> starters;
    std::ifstream in(starters_address + address_extension);
    assert(in.is_open());
    std::string name;
    while (in >> name) starters.insert(name);
    in.close();
    
    std::vector<Pokemon> team(3);
    std::cout << "Choose three Pokemon for your starting team out of the following:" << std::endl;
    for (auto it = starters.begin(); it != starters.end(); it++) {
        std::cout << "  " << *it << std::endl;
    }
            
    std::cout << std::endl;
    for (int i = 0; i < 3; i++) {
        std::string query = std::to_string(3-i) + " choice(s) left: ";
        std::string error = "Oops. That wasn't a correct name.";
        std::string choice = Input::read_string(starters, query, error);
        Pokebase chosen = Pokedex::get_pokebase(choice);
        team[i] = Pokemon(chosen, 1);
        starters.erase(choice);
    }
    return team;
}

void Player::shop() {
    std::vector<std::string> list_items(18);
    list_items = {"Ether", "MaxEther", "Elixir", "MaxElixir", "Potion", "Superpotion", "Hyperpotion", "MaxPotion", "XAttack", "XDefense", "XSpecialAttack", "XSpecialDefense", "XSpeed", "Antidote", "Antiburn", "Antistun", "RestoreAll"};
    bool cont = true;
    while (cont) {
        std::cout << "\nWelcome to the shop!" << std::endl;
        std::cout << "You have " << money << " coins" << std::endl;
        std::string query1 = "\n  1. Ether              100\n  2. Max Ether          200\n  3. Elixir             250\n  4. Max Elixir         300\n  5. Potion              50\n  6. Superpotion        120\n  7. Hyperpotion        250\n  8. Max Potion         300\n  9. XAttack            200\n  10. XDefense          200\n  11. XSpecialAttack    200\n  12. XSpecialDefense   200\n ";
        std::string query2 = " 13. XSpeed            200\n  14. Antidote          100\n  15. Antiburn          100\n  16. Antistun          100\n  17. Restore All       500\n\nEnter 0 to leave the shop\n\n";
        std::string error = "Oops. Enter a number between 0 and 17";
        bool corr = false;
        while (not corr) {
            int choice = Input::read_int(0, 17, query1+query2, error);
            if (choice == 0) {
                std::cout << "Goodbye!" << std::endl;
                return;
            }
            else {
                std::string query2 = "How many do you want to buy? (1-10) ";
                std::string error2 = "Oops. Enter a number between 1 and 10";
                int amount = Input::read_int(1, 10, query2, error2);
                Item to_buy = Item::get_item(list_items[choice-1]);
                if (to_buy.get_price()*amount <= money) {
                    inventory[to_buy] += amount;
                    money -= to_buy.get_price()*amount;
                    std::cout << "You bought " << amount << " " << list_items[choice-1] << "(s)." << std::endl;
                    corr = true;
                }
                else {
                    std::cout << "You don't have enough money" << std::endl << std::endl;
                }
            }
        }
    }
}

int Player::swap_fainted() const {
    std::vector<Pokemon> options;
    if (team[1].get_hp() != 0) options.push_back(team[1]);
    if (team[2].get_hp() != 0) options.push_back(team[2]);
    
    if (options.size() == 1) {
        if (team[1].get_hp() != 0) return 2;
        else return 3;
    }

    std::cout << "Alive Pokemon: " << std::endl;
    for (int i = 0; i < (int)options.size(); i++) {
        std::cout << "  " << i+1 << ". " << options[i].get_name() << " (Level " << options[i].get_level() << ")   HP " << options[i].get_hp() << "/" << options[i].get_battle_stats().maxhp << std::endl;
    }
    std::string query = "Which Pokemon do you want to swap in? ";
    std::string error = "Oops. Enter a number between 1 and 2";
    int choice = Input::read_int(1, 2, query, error);
    return choice+1;
}

bool Player::swap_pokemon(int i, int j) {
    if (i == 0 and team[j].get_hp() == 0) {
        std::cout << "Can't have a fainted Pokemon as your leader" << std::endl;
        return false;
    }
    Pokemon aux = team[i];
    team[i] = team[j];
    team[j] = aux;
    return true;
}

int Player::action_choice() const { //AI related
    bool can_swap (team[1].get_hp() != 0 or team[2].get_hp() != 0);
    int percent_hp = 100*team[0].get_hp()/team[0].get_battle_stats().maxhp;
    int move_no_pp = 0; //0 -> all moves have pp, 1 -> move 1 has no pp, etc
    for (int i = 0; i < (int)team[0].get_moves().size(); i++) {
        if (team[0].get_moves()[i].get_pp() < 2) move_no_pp = i+1;
    }
    if (can_swap and percent_hp < Random::randint(10, 40) and Random::randint(0, 1) == 0) { //swap
        return 2;
    }
    else if (percent_hp < Random::randint(10, 30) and Random::randint(0, 2) == 0) { //use healing item
        return 3;
    }
    else if (move_no_pp != 0 and Random::randint(0, 3) == 0) { //use pp item
        return 4;
    }
    return 1; //attack
}

int Player::move_choice(const Pokemon& own, const Pokemon& other) const { //AI related
    std::vector<int> points(4, 0);
    
    int choice = 0;
    int max = 0;
    
    for (int i = 0; i < (int)(own.get_moves().size()); i++) {
        Move curr = own.get_moves()[i];
        if (curr.get_type() == own.get_type()) points[i] += 3;
        if (Type::advantage(curr.get_type(), other.get_type())) points[i] += 7;
        points[i] += curr.get_power()/20;
        points[i] -= (100-curr.get_accuracy())/10;
        Stats opp = curr.get_change_stats_opponent();
        Stats own = curr.get_change_stats_own();
        points[i] += own.attack + own.defense + own.spattack + own.spdefense + own.speed + own.maxhp
            - opp.attack - opp.defense - opp.spattack - opp.spdefense - opp.speed - opp.maxhp;
        Status st = curr.get_status();
        if (st.poison != 0 or st.stun != 0 or st.burn != 0) points[i] += 5;
        int rnd = Random::randint(1, 3);
        points[i] *= rnd;
        points[i] /= 2;
        if (curr.get_pp() == 0) points[i] = -100;
        
        if (points[i] > max) {
            max = points[i];
            choice = i;
        }
    }
 
    return choice+1;
}

int Player::swap_choice(const Pokemon& enemy) const { //AI related
    int choice = 1;
    if (team[1].get_hp() != 0 and team[2].get_hp() != 0) { //both alive
        if (Type::advantage(team[1].get_type(), enemy.get_type())) choice = 1;
        else if (Type::advantage(team[1].get_type(), enemy.get_type())) choice =  2;
        else choice = Random::randint(1, 2);
    }
    else if (team[1].get_hp() != 0) choice = 1;
    else choice = 2;
    if (team[0].get_hp() != 0) {
        std::cout << std::endl << "The enemy took back " << team[0].get_name() << "." << std::endl;
        std::cout << "And the enemy brought out " << team[choice].get_name() << "!" << std::endl;
    }
    return choice;
}


//AUXILIARY
std::vector<int> Player::calculate_tiers(int trainer) { //AI related
    std::vector<int> tiers(4, 0);
    if (trainer < 5) {
        tiers[0] = 3;
    }
    else if (trainer < 10) {
        tiers[0] = 2;
        tiers[1] = 1;
    }
    else if (trainer < 15) {
        tiers[0] = 1;
        tiers[1] = 2;
    }
    else if (trainer < 20) {
        tiers[0] = 1;
        tiers[1] = 1;
        tiers[2] = 1;
    }
    else if (trainer < 30) {
        tiers[1] = 2;
        tiers[2] = 1;
    }
    else if (trainer < 50) {
        tiers[1] = 1;
        tiers[2] = 2;
    }
    else if (trainer < 75) {
        tiers[2] = 3;
    }
    else if (trainer < 100) { //33% of a legendary
        int rnd = Random::randint(0, 2);
        if (rnd == 3) tiers[3] = 1;
        else tiers[3] = 0;
        tiers[2] = 3-tiers[3];
    }
    else if (trainer < 200) { //0-2 legendaries
        tiers[3] = Random::randint(0, 2);
        tiers[2] = 3-tiers[3];
    }
    else { //0-3 legendaries
        tiers[3] = Random::randint(0, 3);
        tiers[2] = 3-tiers[3];
    }
    return tiers;
}


