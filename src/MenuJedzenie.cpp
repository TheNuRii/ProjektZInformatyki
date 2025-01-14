#include "../include/MenuJedzenie.h"
#include <iostream>
#include <fstream>

using namespace std;

MenuJedzenie::MenuJedzenie(const std::string& file) : fileName(file) {}

void MenuJedzenie::loadMenu() {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Nie można otworzyć pliku: " << fileName << endl;
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
    cout << "\n=== MENU JEDZENIE ===\n";
    for (size_t i = 0; i < dishes.size(); ++i) {
        cout << dishes[i] << endl;
    }
}

string MenuJedzenie::getDish(int index) const {
    if (index < 1 || index > int(dishes.size())) {
        return "Nieprawidłowy wybór.";
    }
    return dishes[index - 1];
}