#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Stolik {
public:
    string toString() const {
        return to_string(numer_) + " " + (zajety_ ? "1" : "0") + " " + to_string(liczba_miejsc_) + " " + nazwisko_;
    }

private:
    int numer_;
    bool zajety_;
    int liczba_miejsc_;
    string nazwisko_;
};


};

struct Rezerwacja {
    string nazwisko;
    int numer_stolika;
    string data;
    int liczba_osob;

    string toString() const {
        return nazwisko + " " + to_string(numer_stolika) + " " + data + " " + to_string(liczba_osob);
    }
};

vector<Stolik> wczytajStoliki(const string& plik) {
    vector<Stolik> stoliki;
    ifstream in(plik);

    if (!in.is_open()) {
        cerr << "Nie można otworzyć pliku: " << plik << endl;
        return stoliki;
    }

    string linia;
    while (getline(in, linia)) {
        stringstream ss(linia);
        Stolik stolik;
        int zajety_int;
        ss >> stolik.numer >> zajety_int >> stolik.liczba_miejsc;
        getline(ss, stolik.nazwisko);
        stolik.zajety = (zajety_int == 1);
        stoliki.push_back(stolik);
    }

    in.close();
    return stoliki;
}

vector<Rezerwacja> wczytajRezerwacje(const string& plik) {
    vector<Rezerwacja> rezerwacje;
    ifstream in(plik);

    if (!in.is_open()) {
        cerr << "Nie można otworzyć pliku: " << plik << endl;
        return rezerwacje;
    }

    string linia;
    while (getline(in, linia)) {
        stringstream ss(linia);
        Rezerwacja rezerwacja;
        ss >> rezerwacja.nazwisko >> rezerwacja.numer_stolika >> rezerwacja.data >> rezerwacja.liczba_osob;
        rezerwacje.push_back(rezerwacja);
    }

    in.close();
    return rezerwacje;
}

void saveTablesToFile(const std::string& filename, const std::vector<Stolik>& tables) {
    std::ofstream file{filename};

    if (!file.is_open()) {
        return;
    }

    for (const auto& table : tables) {
        file << table.toString() << '\n';
    }

    file.close();
}

void zapiszRezerwacje(const string& plik, const vector<Rezerwacja>& rezerwacje) {
    ofstream out(plik);

    if (!out.is_open()) {
        cerr << "Nie można otworzyć pliku do zapisu: " << plik << endl;
        return;
    }

    for (const auto& rezerwacja : rezerwacje) {
        out << rezerwacja.toString() << endl;
    }

    out.close();
}

void addReservation(std::vector<Stolik>& tables, std::vector<Rezerwacja>& reservations) {
    std::string name;
    int tableNumber;
    std::string date;
    int numberOfPeople;

    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter table number: ";
    std::cin >> tableNumber;
    std::cout << "Enter date (yyyy-mm-dd): ";
    std::cin >> date;
    std::cout << "Enter number of people: ";
    std::cin >> numberOfPeople;

    auto foundTable = std::find_if(tables.begin(), tables.end(),
        [tableNumber](const Stolik& table) { return table.numer == tableNumber; });

    if (foundTable == tables.end() || foundTable->reserved || numberOfPeople > foundTable->numberOfSeats) {
        std::cout << "Table is already reserved or not enough seats!" << std::endl;
        return;
    }

    foundTable->reserved = true;
    foundTable->name = name;
    reservations.push_back({name, tableNumber, date, numberOfPeople});
    std::cout << "Reservation added." << std::endl;
}

void usunRezerwacje(vector<Stolik>& stoliki, vector<Rezerwacja>& rezerwacje) {
    string nazwisko;
    cout << "Podaj nazwisko do usunięcia rezerwacji: ";
    cin >> nazwisko;

    for (size_t i = 0; i < rezerwacje.size(); ++i) {
        if (rezerwacje[i].nazwisko == nazwisko) {
            int numer_stolika = rezerwacje[i].numer_stolika;

            for (auto& stolik : stoliki) {
                if (stolik.numer == numer_stolika) {
                    stolik.zajety = false;
                    stolik.nazwisko = "";
                    break;
                }
            }

            rezerwacje.erase(rezerwacje.begin() + i);
            cout << "Rezerwacja została usunięta." << endl;
            return;
        }
    }

    cout << "Nie znaleziono rezerwacji dla podanego nazwiska!" << endl;
}

void wyswietlStoliki(const vector<Stolik>& stoliki) {
    for (const auto& stolik : stoliki) {
        cout << "Stolik nr " << stolik.numer << " | Miejsca: " << stolik.liczba_miejsc 
             << " | Zajęty: " << (stolik.zajety ? "Tak" : "Nie")
             << " | Nazwisko: " << (stolik.zajety ? stolik.nazwisko : "Brak") << endl;
    }
}

int main() {
    const string plik_stoliki = "lista-stolkiow.txt";
    const string plik_rezerwacje = "rezerwacje.txt";

    vector<Stolik> stoliki = wczytajStoliki(plik_stoliki);
    vector<Rezerwacja> rezerwacje = wczytajRezerwacje(plik_rezerwacje);

    int wybor;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Wyświetl stoliki\n";
        cout << "2. Dodaj rezerwację\n";
        cout << "3. Usuń rezerwację\n";
        cout << "4. Zakończ\n";
        cout << "Wybór: ";
        cin >> wybor;

        switch (wybor) {
        case 1:
            wyswietlStoliki(stoliki);
            break;
        case 2:
            rezerwacje.push_back(dodajRezerwacje(stoliki, rezerwacje));
            break;
        case 3:
            usunRezerwacje(stoliki, rezerwacje);
            break;
        case 4:
            zapiszStoliki(plik_stoliki, stoliki);
            zapiszRezerwacje(plik_rezerwacje, rezerwacje);
            cout << "Zapisano dane. Do widzenia!" << endl;
            break;
        default:
            cout << "Nieprawidłowy wybór!" << endl;
        }
    } while (wybor != 4);

    return 0;
}
