#include "Input.hh"

std::string Input::read_string(const std::set<std::string>& choices, const std::string& query, const std::string& err) {
    assert(choices.size() > 0);
    std::string s;
    while ((std::cout << query and !(std::cin >> s)) or choices.find(s) == choices.end() or std::cin.peek() != '\n'){    
        std::cout << err << std::endl;    
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return s;
}

int Input::read_int(int minimum, int maximum, const std::string& query, const std::string& err) {
    assert(minimum <= maximum);
    int n;
    while ((std::cout << query and !(std::cin >> n))  or (n < minimum) or (n > maximum) or std::cin.peek() != '\n'){    
        std::cout << err << std::endl;    
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return n;
}

int Input::read_int(int minimum, int maximum, const std::set<int>& banned, const std::string& query, const std::string& err) {
    assert(minimum <= maximum);
    int n;
    while ((std::cout << query and !(std::cin >> n))  or (n < minimum) or (banned.count(n)) or (n > maximum) or std::cin.peek() != '\n'){    
        std::cout << err << std::endl;    
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return n;
}

double Input::read_double(int minimum, int maximum, const std::string& query, const std::string& err) {
    assert(minimum <= maximum);
    double n;
    while ((std::cout << query and !(std::cin >> n))  or (n < minimum) or (n > maximum) or std::cin.peek() != '\n'){    
        std::cout << err << std::endl;    
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return n;
}
