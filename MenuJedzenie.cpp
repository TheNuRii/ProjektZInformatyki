#include "MenuJedzenie.h"
#include <iostream>
#include <fstream>

using namespace std;

MenuJedzenie::MenuJedzenie(const std::string& file) : fileName(file) {}

void MenuJedzenie::loadMenu() {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Nie mozna otworzyc pliku: " << fileName << endl;
        return;
    }
    dishes.clear();
    string line;
    while (getline(file, line)) {
        dishes.push_back(line);
    }
    file.close();
}

void MenuJedzenie::displayMenu() const {
    cout << "\n==================== MENU ====================\n";
    for (size_t i = 0; i < dishes.size(); ++i) {
        cout << "["<<i+1 <<"]" << dishes[i] << endl;
    }
}

string MenuJedzenie::getDish(int index) const {

    if (index >= 0 && index < 6) {
        return dishes[index];
    }
    return "";
}

