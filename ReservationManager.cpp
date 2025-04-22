#include "ReservationManager.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
using namespace std;
string reservationDetails;

void clear_Console1() {
    system("cls");
}

ReservationManager::ReservationManager() {
    for (int i = 1; i <= 6; i++) {
        tables.emplace_back(i);
    }
}

void ReservationManager::displayTables() const {
    cout << left << setw(10) << "Stolik"
        << setw(15) << "Status"
        << setw(25) << "Rezerwacja" << endl;
    cout << string(50, '-') << endl;

    for (const auto& table : tables) {
        table.display();
    }
    cout << "Nacisnij dowolny klawisz, aby wrocic.\n";
    cin.ignore();
    cin.get();
}

void ReservationManager::displayTablesClient() const {
    cout << left << setw(10) << "Stolik"
        << setw(15) << "Status"
        << endl;
    cout << string(50, '-') << endl;

    for (const auto& table : tables) {
        table.displayClient();
    }
    cout << "Nacisnij dowolny klawisz, aby wrocic.\n";
    cin.ignore();
    cin.get();
}
string  reservationTime;
void ReservationManager::addReservation() {
    string reservationTime;
    int newDuration;
    string customerName;
    int tableNumber;

    // Pobranie imienia klienta
    cout << "Podaj imie klienta: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Czyszczenie bufora
    getline(cin, customerName);

    if (customerName.empty()) {
        cout << "Imie klienta nie mo¿e byc puste!" << endl;
        return;
    }

    // Pobranie godziny rezerwacji
    while (true) {
        cout << "Podaj czas rezerwacji (np. 17) od 10:00 do 22:00: ";
        getline(cin, reservationTime);

        if (reservationTime.length() < 2) { // Sprawdzenie minimalnej d³ugoœci
            cout << "Niepoprawny format godziny! Sprobuj ponownie." << endl;
            continue;
        }

        try {
            int newHour = stoi(reservationTime.substr(0, 2));
            if (newHour >= 10 && newHour <= 22) {
                break;
            }
            else {
                cout << "Godzina musi byc w zakresie od 10:00 do 22:00!" << endl;
            }
        }
        catch (const invalid_argument&) {
            cout << "Niepoprawny format godziny! Sprobuj ponownie." << endl;
        }
    }

    // Pobranie nowego czasu trwania rezerwacji
    while (true) {
        cout << "Podaj czas trwania rezerwacji (1-2 godziny): ";
        cin >> newDuration;

        if (cin.fail()) { // Obs³uga b³êdnego wejœcia (np. wpisanie liter)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Niepoprawny format! Podaj liczbê od 1 do 2." << endl;
            continue;
        }

        if (newDuration >= 1 && newDuration <= 2) {
            break;
        }
        else {
            cout << "Czas rezerwacji musi byc w zakresie od 1 do 2 godzin!" << endl;
        }
    }

    // Sprawdzenie, czy rezerwacja nie wykracza poza godziny otwarcia restauracji
    int newHour = stoi(reservationTime.substr(0, 2));
    if (newHour + newDuration > 22) {
        cout << "Rezerwacja wykracza poza godziny pracy restauracji (22:00). Rezerwacja anulowana." << endl;
        return;
    }

    // Wyœwietlenie dostêpnych stolików
    cout << "Wolne stoliki:" << endl;
    bool freeTables = false;
    for (const auto& table : tables) {
        if (!table.isReserved) {
            cout << "Stolik " << table.tableNumber << endl;
            freeTables = true;
        }
    }

    if (!freeTables) {
        cout << "Brak dostepnych stolikow!" << endl;
        return;
    }

    // Wybór stolika
    cout << "Wybierz numer stolika: ";
    cin >> tableNumber;

    if (tableNumber < 1 || tableNumber > 6 || tables[tableNumber - 1].isReserved) {
        cout << "Wybrany stolik jest niedostepny!" << endl;
        return;
    }

    // Dodanie rezerwacji
    reservationDetails = customerName + " (" + reservationTime + ":00-" + to_string(newHour + newDuration) + ":00)";
    tables[tableNumber - 1].isReserved = true;
    tables[tableNumber - 1].reservationDetails = reservationDetails;
    reservations.emplace_back(nextId++, customerName, tableNumber, reservationDetails);

    clear_Console1();
    cout << "Rezerwacja dodana pomyslnie!" << endl;
}

void ReservationManager::addOrder() {
    if (reservations.empty()) {
        clear_Console1();
        cout << "Brak rezerwacji." << endl;
        this_thread::sleep_for(std::chrono::seconds(2));
        clear_Console1();
        return;
    }

    int tableNumber;
    cout << "Podaj numer stolika, do ktorego chcesz dodac zamowienie: ";
    cin >> tableNumber;

    if (tableNumber < 1 || tableNumber > 6 || !tables[tableNumber - 1].isReserved) {
        cout << "Wybrany stolik jest niedostepny lub niezarezerwowany!" << endl;
        return;
    }

    MenuJedzenie menuJedzenie("jedzenie.txt");
    menuJedzenie.loadMenu();
    menuJedzenie.displayMenu();

    int orderNumber;
    cout << "Podaj numer dania do zamowienia: ";
    cin >> orderNumber;

    // SprawdŸ, czy numer dania jest prawid³owy
    if (orderNumber < 1 || orderNumber > 6) {
        cout << "Nieprawidlowy numer dania!" << endl;
        return;
    }

    // Pobierz nazwê dania na podstawie numeru
    string order = menuJedzenie.getDish(orderNumber - 1); // Indeks w wektorze zaczyna siê od 0
    tables[tableNumber - 1].addOrder(order);

    cout << "Dodano zamowienie: " << order << " do stolika " << tableNumber << endl;
}

void ReservationManager::displayOrders() {
    if (reservations.empty()) {
        clear_Console1();
        cout << "Brak rezerwacji." << endl;
        this_thread::sleep_for(std::chrono::seconds(2));
        clear_Console1();
        return;
    }
    clear_Console1();
    cout << "Podaj numer stolika: ";
    int tableNumber;
    cin >> tableNumber;

    if (tableNumber < 1 || tableNumber > 6) {
        cout << "Nieprawidlowy numer stolika!" << endl;
        return;
    }

    tables[tableNumber - 1].displayOrders();
    cout << "Nacisnij dowolny klawisz, aby wrocic.\n";
    cin.ignore();
    cin.get();
}

void ReservationManager::displayReservations() const {
    if (reservations.empty()) {
        cout << "Brak rezerwacji." << endl;
        return;
    }
    cout << left << setw(5) << "ID"
        << setw(20) << "Klient"
        << setw(10) << "Stolik"
        << setw(15) << "Czas" << endl;
    cout << string(50, '-') << endl;

    for (const auto& res : reservations) {
        res.display();
    }
}

void ReservationManager::deleteReservation() {
    if (reservations.empty()) {
        clear_Console1();
        cout << "Brak rezerwacji." << endl;
        this_thread::sleep_for(std::chrono::seconds(2));
        clear_Console1();
        return;
    }
    clear_Console1();
    cout << "Podaj numer stolika do usuniecia rezerwacji: ";
    int index;
    cin >> index;

    if (index < 1 || index > tables.size()) {
        cout << "Niepoprawny numer stolika!" << endl;
        return;
    }

    // Indeks w tabeli (stoliki numerujemy od 1, ale indeksy zaczynaj¹ siê od 0)
    int tableIndex = index - 1;

    // Sprawdzenie, czy stolik jest zarezerwowany
    if (!tables[tableIndex].isReserved) {
        cout << "Stolik " << index << " nie ma aktywnej rezerwacji!" << endl;
        return;
    }

    // Wyczyœæ rezerwacjê
    tables[tableIndex].isReserved = false;
    tables[tableIndex].reservationDetails.clear();

    cout << "Rezerwacja dla stolika " << index << " zostala wyczyszczona." << endl;
}

void ReservationManager::editOrder() {
    if (reservations.empty()) {
        clear_Console1();
        cout << "Brak rezerwacji." << endl;
        this_thread::sleep_for(std::chrono::seconds(2));
        clear_Console1();
        return;
    }
    int tableNumber;
    clear_Console1();
    cout << "Podaj numer stolika, w ktorym chcesz edytowac zamowienie: ";
    cin >> tableNumber;

    // Sprawdzenie poprawnoœci numeru stolika
    if (tableNumber < 1 || tableNumber > 6 || !tables[tableNumber - 1].isReserved) {
        cout << "Wybrany stolik jest niedostepny lub niezarezerwowany!" << endl;
        return;
    }

    // Wyœwietl aktualne zamówienia dla danego stolika
    cout << "Aktualne zamowienia dla stolika " << tableNumber << ":" << endl;
    tables[tableNumber - 1].displayOrders();

    cout << "Podaj numer dania do edycji: ";
    int orderIndex;
    cin >> orderIndex;

    // Sprawdzenie poprawnoœci numeru zamówienia
    if (orderIndex < 1 || orderIndex > tables[tableNumber - 1].orders.size()) {
        cout << "Nieprawidlowy numer zamowienia!" << endl;
        return;
    }

    // Wyœwietl menu jedzenia, aby wybraæ nowe zamówienie
    MenuJedzenie menuJedzenie("jedzenie.txt");
    menuJedzenie.loadMenu();
    menuJedzenie.displayMenu();

    cout << "Podaj nowy numer dania: ";
    int newOrderNumber;
    cin >> newOrderNumber;

    // Sprawdzenie poprawnoœci nowego numeru dania
    if (newOrderNumber < 1 || newOrderNumber > 6) {
        cout << "Nieprawidlowy numer dania!" << endl;
        return;
    }

    // Pobierz now¹ nazwê dania na podstawie numeru i zaktualizuj zamówienie
    string newOrder = menuJedzenie.getDish(newOrderNumber - 1); // Indeks w wektorze zaczyna siê od 0
    tables[tableNumber - 1].orders[orderIndex - 1] = newOrder;

    cout << "Zamowienie zostalo zaktualizowane na: " << newOrder << endl;
}

void ReservationManager::deleteOrder() {
    if (reservations.empty()) {
        clear_Console1();
        cout << "Brak rezerwacji." << endl;
        this_thread::sleep_for(std::chrono::seconds(2));
        clear_Console1();
        return;
    }
    clear_Console1();
    cout << "Podaj numer stolika, z ktorego chcesz usunac zamowienie: ";
    int tableNumber;
    cin >> tableNumber;

    if (tableNumber < 1 || tableNumber > tables.size() || !tables[tableNumber - 1].isReserved) {
        cout << "Wybrany stolik jest niedostepny lub niezarezerwowany!" << endl;
        return;
    }

    tables[tableNumber - 1].displayOrders(); // Wyœwietl wszystkie zamówienia dla stolika

    cout << "Podaj numer zamowienia do usuniecia: ";
    int orderIndex;
    cin >> orderIndex;

    // Sprawdzenie poprawnoœci indeksu zamówienia
    if (orderIndex < 1 || orderIndex > tables[tableNumber - 1].orders.size()) {
        cout << "Niepoprawny numer zamowienia!" << endl;
        return;
    }

    // Usuñ zamówienie
    tables[tableNumber - 1].orders.erase(tables[tableNumber - 1].orders.begin() + (orderIndex - 1));
    cout << "Zamowienie zostalo usuniete." << endl;
}


