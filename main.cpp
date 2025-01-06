#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

template <typename T>
class Container {
public:
    Container(T data, Container *next = nullptr, Container *prev = nullptr){
        prev_element_ = prev;
        Container_element_ = data;
        next_element_ = next;
    }
    T getContainerElement() const { 
        return Container_element_; 
    }
    Container* getNextElement() const {
        return next_element_;
    }
    Container* getPrevElement() const {
        return prev_element_;
    }
    void setContainerElement(T data) {
        Container_element_ = data;
    }
    void setNextElement(Container *next) {
        next_element_ = next;
    }
    void setPrevElement(Container *prev) {
        prev_element_ = prev;
    }

private:
    T Container_element_;
    Container* next_element_;
    Container* prev_element_;
};

template <typename T>
class DoubleLinkedList {
public:

     DoubleLinkedList(){
        linked_list_head_ = nullptr;
        linked_list_tail_ = nullptr;
    }

    ~DoubleLinkedList() {
        while (linked_list_head_ != nullptr) {
            Container<T> *temp = linked_list_head_;
            linked_list_head_ = linked_list_head_->getNextElement();
            delete temp;
        }
    }

    void addElementToList(const T& data) {
        Container<T>* newContainer = new Container<T>(data);

        if (!linked_list_head_) { 
            linked_list_head_ = linked_list_tail_ = newContainer;
            return;
        }

        Container<T>* current = linked_list_tail_;

        if (!current) { 
            linked_list_tail_->setNextElement(newContainer);
            newContainer->setPrevElement(linked_list_tail_);
            linked_list_tail_ = newContainer;
        } else if (current == linked_list_head_) { 
            newContainer->setNextElement(linked_list_head_);
            linked_list_head_->setPrevElement(newContainer);
            linked_list_head_ = newContainer;
        } else { 
            Container<T>* prev = current->getPrevElement();
            prev->setNextElement(newContainer);
            newContainer->setPrevElement(prev);
            newContainer->setNextElement(current);
            current->setPrevElement(newContainer);
        }
    }

    void deleteElementFromList(const T& data) {
        if (!linked_list_head_) return;

        Container<T>* current = linked_list_head_;
        while (current && !(current->getContainerElement() == data)) {
            current = current->getNextElement();
        }

        if (!current) return;

        if (current == linked_list_head_) { 
            linked_list_head_ = linked_list_head_->getNextElement();
            if (linked_list_head_)
                linked_list_head_->setPrevElement(nullptr);
            else
                linked_list_tail_ = nullptr;
        } else if (current == linked_list_tail_) { 
            linked_list_tail_ = linked_list_tail_->getPrevElement();
            if (linked_list_tail_)
                linked_list_tail_->setNextElement(nullptr);
            else
                linked_list_head_ = nullptr;
        } else { 
            Container<T>* prev = current->getPrevElement();
            Container<T>* next = current->getNextElement();
            prev->setNextElement(next);
            next->setPrevElement(prev);
        }

        delete current;
    }

    void printFromTheEndList() const {
        Container<T>* temp = linked_list_tail_;
        while (temp) {
            cout << temp->getContainerElement() << " ";
            temp = temp->getPrevElement();
        }
        cout << endl;
    }

private:
    Container<T> *linked_list_head_;
    Container<T> *linked_list_tail_;
};

struct Stolik {
    int numer;
    bool zajety;
    int liczba_miejsc;
    string nazwisko;

    string toString() const {
        return to_string(numer) + " " + (zajety ? "1" : "0") + " " + to_string(liczba_miejsc) + " " + (zajety ? nazwisko : "");
    }
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

DoubleLinkedList<Stolik> wczytajStoliki(const string& plik) {
    DoubleLinkedList<Stolik> stoliki;
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
        stoliki.addElementToList(stolik);
    }

    in.close();
    return stoliki;
}

DoubleLinkedList<Rezerwacja> wczytajRezerwacje(const string& plik) {
    DoubleLinkedList<Rezerwacja> rezerwacje;
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
        rezerwacje.addElementToList(rezerwacja);
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
    string name;
    int tableNumber;
    string date;
    int numberOfPeople;

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter table number: ";
    cin >> tableNumber;
    cout << "Enter date (yyyy-mm-dd): ";
    cin >> date;
    cout << "Enter number of people: ";
    cin >> numberOfPeople;

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

void usunRezerwacje(DoubleLinkedList<Stolik>& stoliki, DoubleLinkedList<Rezerwacja>& rezerwacje) {
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

    DoubleLinkedList<Stolik> stoliki = wczytajStoliki(plik_stoliki);
    DoubleLinkedList<Rezerwacja> rezerwacje = wczytajRezerwacje(plik_rezerwacje);

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
            stoliki.printFromTheEndList();
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
