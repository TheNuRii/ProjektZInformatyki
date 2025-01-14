#ifndef MENU_JEDZENIE_H
#define MENU_JEDZENIE_H

#include <string>
#include <vector>

class MenuJedzenie {
private:
    std::string fileName;          
    std::vector<std::string> dishes; 

public:
    MenuJedzenie(const std::string& file); 
    void loadMenu();                        
    void displayMenu() const;               
    std::string getDish(int index) const;   
};

#endif 