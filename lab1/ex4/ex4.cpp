/*
Pentru a ne obișnui cu programarea low level, scrieți un utilitar similar cu cat în C/C++. Acesta trebuie să afișeze conținutul unui fișier, linie cu linie, la stdout. Vom folosi API-ul direct peste file descriptors (e.g. read, open).
*/

#include <iostream>
#include <unistd.h>
#include <fcntl.h>


void eroare(const char * eroare) {
    perror(eroare);
    exit(-1);
}

int main() {

    int source_fd = open("test.txt", O_RDONLY);
    // int dest_fd = STDOUT_FILENO = 1

    int bytes_count;
    char buf[1024];    

    if (source_fd < 0)
        eroare("Nu pot deschide fisierul");

    while ((bytes_count = read(source_fd, buf, sizeof(buf)))) {

        if (bytes_count < 0)
            eroare("Eroare la citire");

        bytes_count = write(1, buf, bytes_count);
        if (bytes_count < 0)
            eroare("Eroare la scriere");
    }

    close(source_fd);

    return 0;
}