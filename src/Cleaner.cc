#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    int n;
    cout << "1 - Clean all saves.\n2 - Clean a specific save." << endl;
    cin >> n;
    if (n == 1) {
        for (int i = 1; i < 9; i++) {
            string address = "Data/Saves/GameSave" + to_string(i) + ".txt";
            ofstream out(address);
            out.close();
        }
    }
    else if (n == 2) {
        cout << "Input number of save to clean: ";
        int k;
        cin >> k;
        string address = "Data/Saves/GameSave" + to_string(k) + ".txt";
        ofstream out(address);
        out.close();
    }
}
