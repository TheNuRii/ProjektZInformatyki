#pragma once
using namespace std;
#include <iostream>
#include <cstdlib>
#include <thread>
#include "MenuJedzenie.h"
#include <chrono>
#include "Stolik.h"
#include "ReservationManager.h"

void menu();
ReservationManager reservationManager;

void clear_Console() {
    system("cls");
}

bool adminLogin() {
    const string ADMIN_PASSWORD = "haslo";
    string enteredPassword;

    cout << "=== Logowanie jako administrator ===\n";
    cout << "Podaj haslo: ";
    cin >> enteredPassword;

    if (enteredPassword == ADMIN_PASSWORD) {
        clear_Console();
        cout << "Logowanie pomyslne. Witamy, administratorze!\n";
        return true;
    }
    else {
        cout << "Nieprawidlowe haslo!\n";
        return false;
    }
}

void Browsemenu() {
    MenuJedzenie menuJedzenie("jedzenie.txt");
    menuJedzenie.loadMenu();
    clear_Console();
    menuJedzenie.displayMenu();
    cout << "Nacisnij dowolny klawisz, aby wrocic.\n";
    cin.ignore();
    cin.get();
    clear_Console();
}

void client_Menu() {
    int choice;
    do {
        cout << "==== PANEL KLIENTA ====" << endl;
        cout << "1. Przegladaj menu" << endl;
        cout << "2. Zarezerwuj stolik" << endl;
        cout << "3. Wyswietl rezerwacje" << endl;
        cout << "4. Wyjscie" << endl;
        cout << "Wybierz opcje: ";
        cin >> choice;

        MenuJedzenie menuJedzenie("jedzenie.txt");
        menuJedzenie.loadMenu();
        switch (choice) {
        case 1:
            Browsemenu();
            client_Menu();
            break;
        case 2:
            clear_Console();
            reservationManager.addReservation();
            this_thread::sleep_for(chrono::seconds(2));
            clear_Console();
            break;
        case 3:
            clear_Console();
            reservationManager.displayTablesClient();
            clear_Console();
            break;
        case 4:
            clear_Console();
            cout << "Wylogowano z panelu klienta." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            clear_Console();
            menu();
            break;
        default:
            clear_Console();
            cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;

        }
    } while (choice != 4);
}

void admin_Menu() {
    MenuJedzenie menuJedzenie("jedzenie.txt");
    int choice;
    do {
        cout << "==== PANEL ADMIN/KELNER ====" << endl;
        cout << "1. Wyswietl rezerwacje" << endl;
        cout << "2. Przyjmij zamowienie" << endl;
        cout << "3. Sprawdz status zamowienia" << endl;
        cout << "4. Usun rezerwacje" << endl;
        cout << "5. Edytuj zamowienie" << endl;
        cout << "6. Usun zamowienie" << endl;
        cout << "7. Wyjscie" << endl;
        cout << "Wybierz opcje: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            clear_Console();
            reservationManager.displayTables();
            clear_Console();
            break;
        }
        case 2: {
            clear_Console();
            reservationManager.addOrder();
            clear_Console();
            break;
        }
        case 3: {
            reservationManager.displayOrders();
            clear_Console();
            break;
        }
        case 4: {
            reservationManager.deleteReservation();
            clear_Console();
            break;
        }
        case 5: {
            reservationManager.editOrder();
            clear_Console();
            break;
        }
        case 6: {
            reservationManager.deleteOrder();
            clear_Console();
            break;
        }
        case 7: {
            clear_Console();
            cout << "Wylogowano z panelu Kelnera." << endl;
            this_thread::sleep_for(std::chrono::seconds(2));
            clear_Console();
            menu();
            break;
        }
        default: {
            clear_Console();
            cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
            }
        }
    } while (choice != 7);
}

void menu() {
    cout << "\n============ WYBIERZ PANEL ============\n";
    cout << "Klient czy Admin/Kelner?\n[K dla Klienta , A dla Admina/Kelnera]\nWybierz opcje : ";
    char wybor;
    cin >> wybor;
    switch ((wybor)) {
    case 'K':

        clear_Console();
        client_Menu();
        break;

    case 'A':

        clear_Console();
        if (adminLogin()) {
            this_thread::sleep_for(std::chrono::seconds(2));
            clear_Console();
            admin_Menu();
        }
        break;

    default:
        cout << "ERROR404NOTFOUND";
        break;
    }
}