#ifndef MENU_JEDZENIE_H
#define MENU_JEDZENIE_H

#include <string>
#include <vector>
#include "double-linked-list.h"

using namespace std;

class MenuJedzenie {
private:
    string fileName;          
    DoubleLinkedList<string> dishes; 

public:
    MenuJedzenie(const string& file); 
    void loadMenu();                        
    void displayMenu() const;               
    string getDish(int index) const;   
};

#endif 