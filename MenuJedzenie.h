#ifndef MENU_JEDZENIE_H
#define MENU_JEDZENIE_H

#include <string>
#include <vector>
using namespace std;

class MenuJedzenie {
private:
    string fileName;
    vector<string> dishes;

public:
    MenuJedzenie(const string& file);
    void loadMenu();
    void displayMenu() const;
    string getDish(int index) const;
};

#endif 