#include "common.h"

#include <sys/socket.h>
#include <sys/types.h>

/*
    TODO 1.1: Rescrieți funcția de mai jos astfel încât ea să facă primirea
    a exact len octeți din buffer.
*/
int recv_all(int sockfd, void *buffer, size_t len)
{
    size_t bytes_received = 0;
    size_t bytes_remaining = len;
    char *buff = buffer;
    while (bytes_remaining)
    {
        int rc = recv(sockfd, buffer + bytes_received, bytes_remaining, 0);
        // rc == 0, daca s-a inchis conexiunea
        // rc < 0, in caz de eroare
        // rc == cati octeti s-au primit, in caz de succes
        if (rc <= 0)
        {
            break;
        }
        bytes_received += rc;
        bytes_remaining -= rc;
    }
    return bytes_received;
}
/*
    TODO 1.2: Rescrieți funcția de mai jos astfel încât ea să facă trimiterea
    a exact len octeți din buffer.
*/
int send_all(int sockfd, void *buffer, size_t len)
{
    size_t bytes_sent = 0;
    size_t bytes_remaining = len;
    char *buff = buffer;
    while (bytes_remaining)
    {
        int rc = send(sockfd, buffer + bytes_sent, bytes_remaining, 0);
        
        if (rc <= 0)
        {
            break;
        }
        bytes_sent += rc;
        bytes_remaining -= rc;
    }
    return bytes_sent;
}