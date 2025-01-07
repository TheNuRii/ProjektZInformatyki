#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Stolik {
public:

    string toString() const {
        return to_string(numer_) + " " + (zajety_ ? "1" : "0") + " " + to_string(liczba_miejsc_) + " " + (zajety_ ? nazwisko_ : "");
    }

    friend ostream& operator<<(ostream& os, const Stolik& stolik) {
        os << stolik.toString();
        return os;
    }

    int getNumer() const{
        return numer_;
    }

    bool getZajety() const{
        return zajety_;
    }

    int getLiczbaMiejsc() const{
        return liczba_miejsc_;
    }

    string getNazwisko() const{
        return nazwisko_;
    }

    void setNumer(int numer) {
        numer_ = numer;
    }

    void setZajety(bool zajety) {
        zajety_ = zajety;
    }

    void setLiczbaMiejsc(int liczba_miejsc) {
        liczba_miejsc_ = liczba_miejsc;
    }

    void setNazwisko(string nazwisko) {
        nazwisko_ = nazwisko;
    } 
private:
    int numer_;
    bool zajety_;
    int liczba_miejsc_;
    string nazwisko_;
};

class Rezerwacja {
public:
    string toString() const {
        return nazwisko + " " + to_string(numer_stolika) + " " + data + " " + to_string(liczba_osob);
    }

    string getNazwisko() const {
        return nazwisko;
    }

    int getNumerStolika() const {
        return numer_stolika;
    }

    string getData() const {
        return data;
    }

    int getLiczbaOsob() const {
        return liczba_osob;
    }
private:
    string nazwisko;
    int numer_stolika;
    string data;
    int liczba_osob;
};

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

    void usunElementZListy(const T& data) {
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
                linked_list_tail_ = linked_list_tail_->setNextElement(nullptr);
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
        Container<T>* temp = linked_list_head_;
        while (temp != nullptr) {
            cout << temp->getContainerElement();
            temp = temp->getNextElement();
        }
        cout << endl;
    }

private:
    Container<T> *linked_list_head_;
    Container<T> *linked_list_tail_;
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

void saveTablesToFile(const string& filename, const ::vector<Stolik>& tables) {
    ofstream file{filename};

    if (!file.is_open()) {
        cout << "Niepoprawnie otworzenie pliku do zapisu: " << filename << endl;
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

void wyswietlStoliki(const DoubleLinkedList<Stolik>& stoliki) {
    Container<Stolik>* temp = stoliki.linked_list_head_;
    while(temp != nullptr) {
        Stolik stolik = temp->getContainerElement();
        cout << "Stolik nr " << stolik.numer << " | Miejsca: " << stolik.liczba_miejsc 
             << " | Zajęty: " << (stolik.zajety ? "Tak" : "Nie")
             << " | Nazwisko: " << (stolik.zajety ? stolik.nazwisko : "Brak") << endl;
        temp = temp->getNextElement();
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
        case 1:{
            stoliki.printFromTheEndList();
            break;
        }
        case 2:{
            string nazwisko_osoby_rezerwujacej;
            int numer_stolkia;
            string data_rezerwacji;
            int maksymalna_liczba_osob;

            cout << "Podaj nazwisko: ";
            cin >> nazwisko_osoby_rezerwujacej;
            cout << "Podaj numer stolika: ";
            cin >> numer_stolkia;
            cout << "Enter date (yyyy-mm-dd): ";
            cin >> data_rezerwacji;
            cout << "Enter number of people: ";
            cin >> maksymalna_liczba_osob;

   
            rezerwacje.addElementToList(Rezerwacja{nazwisko_osoby_rezerwujacej, numer_stolkia, data_rezerwacji, maksymalna_liczba_osob});
            break;
        }
        case 3:{
            int numer_stolika;
            cout << "Podaj numer stolika by usunąć rezerwacje: ";
            cin >> numer_stolika;

            rezerwacje.usunElementZListy(numer_stolika);
            break;
        }
        case 4:{   
            cout << "Zapisano dane. Do widzenia!" << endl;
            break;
        }
        default:
            cout << "Nieprawidłowy wybór!" << endl;
        }
    } while (wybor != 4);

    return 0;
}
