#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    for (int i = 1; i < 9; i++) {
        string address = "Saves/GameSave" + to_string(i) + ".txt";
        ofstream out(address);
        out.close();
    }
}
