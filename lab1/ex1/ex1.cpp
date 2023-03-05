/*
Vrem să ne pregătim pentru a trimite date în format binar peste un mediu de transmisie. În fișierul de aici avem un array de structuri de tipul Packet în format binar. Realizați un program în C/C++ care să citească array-ul cu elemente de tip Packet din acest fișier și să afișeze conținutul din payload al fiecărei intrări. Procesul prin care acest fișier a fost creat se numește serializare și îl vom întâlni atunci când vom serializa datele pentru a fi trimise spre rețea. Procesul invers, pe care îl veți implementa, se numește deserializare.
*/

#include <iostream>
#include <fstream>

using namespace std;

struct Packet {
    char payload[100];
    int sum;
    int size;
};

void eroare(const char* mesaj) {
    perror(mesaj);
    exit(-1);
}

int main(int argc, char** argv) {
    Packet p;

    if(argc != 2)
        eroare("Nu avem destule argumente sau avem prea multe!");

    ifstream fisier(argv[1], ios::binary);

    if (!fisier.is_open()) {
        eroare("Nu se poate deschide fisierul");
    }

    while(fisier.read((char*)&p, sizeof(Packet))) {
        cout << "Payload: " << p.payload << endl;
        cout << "Sum: " << p.sum << endl;
        cout << "Size: " << p.size <<endl;
    }

    /*
    sau:
    while(1) {
        struct Packet p;
        ...
    }
    */

    // De ce (char*) si &p?
    // istream& read (char* s, streamsize n);

    return 0;
}