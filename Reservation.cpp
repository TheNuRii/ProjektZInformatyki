#include "Reservation.h"
#include <iostream>
using namespace std;

Reservation::Reservation(int id, const string& customerName, int tableNumber, const string& reservationTime)
    : id(id), customerName(customerName), tableNumber(tableNumber), reservationTime(reservationTime) {}

void Reservation::display() const {
    cout << left << setw(5) << id
        << setw(20) << customerName
        << setw(10) << tableNumber
        << setw(15) << reservationTime << endl;
}