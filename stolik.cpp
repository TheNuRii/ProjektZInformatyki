#include "Stolik.h"
using namespace std;

Stolik::Stolik(int number) : tableNumber(number), isReserved(false), reservationDetails("") {}

void Stolik::addOrder(const string& order) {
    orders.push_back(order);
}

void Stolik::display() const {
    cout << left << setw(10) << tableNumber
        << setw(15) << (isReserved ? "Zarezerwowany" : "Wolny")
        << setw(25) << reservationDetails << endl;
}

void Stolik::displayClient() const {
    cout << left << setw(10) << tableNumber
        << setw(15) << (isReserved ? "Zarezerwowany" : "Wolny")
        << endl;
}

void Stolik::displayOrders() const {
    if (orders.empty()) {
        cout << "Brak zamowien dla tego stolika." << endl;
    }
    else {
        cout << "Zamowienia dla stolika " << tableNumber << ":" << endl;
        int iterator = 1;
        for (const auto& order : orders) {
            cout << "["<<iterator<<"]" << order << endl;
            iterator++;
        }
    }
}