#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

class Stolik {
public:
    int tableNumber;
    bool isReserved;
    string reservationDetails;
    vector<string> orders;

    Stolik(int number);

    void addOrder(const string& order);
    void display() const;
    void displayOrders() const;
    void displayClient() const;
};