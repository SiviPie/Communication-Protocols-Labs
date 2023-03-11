# Laboratorul 1

## Ex1

Vrem să ne pregătim pentru a trimite date în format binar peste un mediu de transmisie. În fișierul de aici avem un array de structuri de tipul Packet în format binar.
Am realizat un program în C/C++ care să citească array-ul cu elemente de tip `Packet`din acest fișier și să afișeze conținutul din payload al fiecărei intrări. 
Procesul prin care acest fișier a fost creat se numește **serializare** și îl întâlnim atunci când serializam datele pentru a fi trimise spre rețea. 
Procesul invers, cel implementat, se numește **deserializare**.

## Ex4

Un utilitar similar cu cat în C++. Acesta afișează conținutul unui fișier, linie cu linie, la stdout. Folosim API-ul direct peste file descriptors (e.g. read, open).
