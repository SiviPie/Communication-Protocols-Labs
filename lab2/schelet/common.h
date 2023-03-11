#define DLE (char)0
#define STX (char)2
#define ETX (char)3

/* Atributul este folosit pentru a anunta compilatorul sa nu alinieze structura */
/* DELIM | DATE | DELIM */
struct __attribute__((packed)) Frame {
    char frame_delim_start[2]; /* DEL STX */
    /* TODO 2: Add source and destination */
    char payload[30];  /* Datele pe care vrem sa le transmitem */
    char frame_delim_end[2]; /* DEL ETX */
};

/* Sends one character to the other end via the Physical layer */
int send_byte(char c);
/* Receives one character from the other end, if nothing is sent by the other end, returns a random character */
char recv_byte();

