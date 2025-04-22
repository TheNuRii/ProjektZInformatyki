#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Reservation {
public:
    int id;
    string customerName;
    int tableNumber;
    string reservationTime;

    Reservation(int id, const string& customerName, int tableNumber, const string& reservationTime);

    void display() const;
};