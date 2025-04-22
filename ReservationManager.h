#pragma once
#include <vector>
#include <string>
#include "Reservation.h"
#include "Stolik.h"
#include "MenuJedzenie.h"
using namespace std;

class ReservationManager {
private:
    vector<Reservation> reservations;
    vector<Stolik> tables;
    int nextId = 1;

public:
    ReservationManager();

    void displayTables() const;
    void displayTablesClient() const;
    void addReservation();
    void addOrder();
    void displayOrders();
    void displayReservations() const;
    void deleteReservation();
    void editOrder();
    void deleteOrder();
};