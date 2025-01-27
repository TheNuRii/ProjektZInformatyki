#pragma once
#include <iostream>
#include <cstdlib>
#include <thread>
#include "MenuJedzenie.h"
#include <chrono>

using namespace std;

void menu();

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

void displayOrder() {
    
}

void editOrderStatus() {
    
}

void checkOrderStatus() {

}

void displayReservations() {

}

void editReservations() {
    
}

void deleteReservations() {
    
}

void browseMenu() {
    
}

void reserveTable() {
    
}

void client_Menu() {
    int choice;
    do {
        cout << "=== Menu Klienta ===" << endl;
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
            clear_Console();
            menuJedzenie.displayMenu();
            cout << "Aby powrocic na poprzednia zakladke wpisz 1\n";
            int powrot_wczesniej;
            cin >> powrot_wczesniej;
            while (powrot_wczesniej != 1) {
                
                cout << "Nieprawidlowy wybor. Sprobuj ponownie. Aby powrocic na poprzednia zakladke wpisz 1\n";
                cin >> powrot_wczesniej;

            }
            clear_Console();
            client_Menu();
            break;
        case 2:
            //chyba potrzebna lista ? jezeli zarezerwowany stolik to zloz zamowienie???
            cout << "1. Zarezerwuj stolik" << endl;
            cout << "2. Zloz zamowienie" << endl;
            clear_Console();
            break;
        case 3:
            //lista ? jezeli rezerwacja to status zamowienia???
            cout << "2. Sprawdz status zamowienia" << endl;
            clear_Console();
            break;
        case 4:
            clear_Console();
            cout << "Wylogowano z profilu klienta." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            clear_Console();
            menu();
        default:
            clear_Console();
            cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
            
        }
    } while (choice != 4);
}

void admin_Menu() {

    int choice;
    do {
        cout << "=== Menu Admin ===" << endl;
        cout << "1. Wyswietl zamowienie" << endl;
        cout << "2. Edycja statusu zamowienia" << endl;
        cout << "3. Sprawdz status zamowienia" << endl;
        cout << "4. Wyswietl rezerwacje" << endl;
        cout << "5. Edytuj rezerwacje" << endl;
        cout << "6. Usun rezerwacje" << endl;
        cout << "7. Wyjscie" << endl;
        cout << "Wybierz opcje: ";
        cin >> choice;

        switch (choice) {
        case 1:

            clear_Console();
            break;
        case 2:

            clear_Console();
            break;
        case 3:

            clear_Console();
            break;
        case 4:

            clear_Console();
            break;
        case 5:

            clear_Console();
            break;
        case 7:
            clear_Console();
            
            cout << "Wylogowano z profilu administratora." << endl;
            this_thread::sleep_for(std::chrono::seconds(2));
            clear_Console();
            menu();
            
            break;

        default:
            clear_Console();
            cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;

        }
    } while (choice != 7);
}

void menu() { 
    cout << "\n=============Menu=============\n";
    cout << "Klient czy Admin?\n[K dla Klienta , A dla Admina]\nWybierz opcje : ";
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
            admin_Menu();
        }
        break;

    default:
        cout << "ERROR404NOTFOUND";
        break;
    }
}