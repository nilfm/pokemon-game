#include "Enemy.hh"

const std::string Enemy::tiers_address = "Tiers/Tier";
const std::string Enemy::address_extension = ".txt";
const std::vector<std::string> hp_items = {"Potion", "Superpotion", "Hyperpotion", "MaxPotion"};
const std::vector<std::string> pp_items = {"Ether", "MaxEther", "Elixir", "MaxElixir"};
const std::vector<std::string> x_items = {"XAttack", "XDefense", "XSpecialAttack", "XSpecialDefense", "XSpeed"};

//CONSTRUCTORS
Enemy::Enemy(int trainers) {
    //Set the trainer variable
    trainer = trainers;
    //Calculate how many Pokemon for each tier
    std::vector<int> tiers = calculate_tiers(trainer);
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
                std::cerr << "Name: " << available[rnd] << std::endl;
                Pokebase chosen = Pokedex::get_pokebase(available[rnd]);
                //1 <= level <= 100, 0.9*trainer <= level <= 1.1*trainer
                int level = std::min(std::max(1, Random::randint((int)(0.9*trainer), (int)1.1*trainer)), 100);
                team.push_back(Pokemon(chosen, level));
                available.erase(available.begin()+rnd);
            }
            in.close();
        }
    }
}


//SHOWERS
void Enemy::show_team_stats() const {
    assert(team.size() == 3);
    
    std::cout << std::endl << "ENEMY TEAM'S STATS" << std::endl << std::endl;
    for (int i = 0; i < 3; i++) {
        team[i].print_stats();
    }
}


//AUXILIARY
std::vector<int> Enemy::calculate_tiers(int trainer) {
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
    else if (trainer < 100) {
        tiers[2] = 2;
        tiers[3] = 1;
    }
    else {
        tiers[3] = Random::randint(1, 3);
        tiers[2] = 3-tiers[3];
    }
    return tiers;
}

