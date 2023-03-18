#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "common.h"
#include "link_emulator/lib.h"
#include <arpa/inet.h>

#define HOST "127.0.0.1"
#define PORT 10000


struct l3_msg send_data(struct l3_msg *t) {
	// this function sends a chunk of data
	// and it returns the response
	link_send(t, sizeof(struct l3_msg));

	//receive ACK or NACK:

	struct l3_msg conf;
	int len = link_recv(&conf, sizeof(struct l3_msg));
	if (len < 0) {
		perror("Error receiving message\n");
		exit(1);
	}

	// printf("[SEND] Conf payload: %s\n\n", conf.payload);

	return conf;
}

int is_ack(struct l3_msg conf) {
	int count=0;
	for(int i=0; i<5; i++) {
		if(!strncmp(conf.payload+i, "A", 1))
			count++;
	}

	return (count >= 2);
}


int main(int argc, char **argv) {
	printf("[SENDER] Starting.\n\n");

	init(HOST, PORT);

	int inputFile = open("data.in", O_RDONLY);

	if (inputFile == -1) {
		perror("Failed to open file!\n");
		exit(1);
	}

	unsigned char buffer[PAYLOAD_SIZE];
	ssize_t bytesRead;

	while ((bytesRead = read(inputFile, buffer, PAYLOAD_SIZE)) > 0) {
		// zero out the buffer to ensure that it does not contain data from previous iterations
		if (bytesRead < PAYLOAD_SIZE) {
			memset(buffer + bytesRead, 0, PAYLOAD_SIZE - bytesRead);
		}

		struct l3_msg t;

		strncpy(t.payload, buffer, bytesRead);

		// zero out the remaining bytes in the payload if the number of bytes read is less than PAYLOAD_SIZE
		if (bytesRead < PAYLOAD_SIZE) {
			memset(t.payload + bytesRead, 0, PAYLOAD_SIZE - bytesRead);
		}

		t.hdr.len = bytesRead;
		t.hdr.sum = 0;
		t.hdr.sum = htonl(crc32((void *)&t, sizeof(struct l3_msg)));

		struct l3_msg conf;

		int max_tries = 5;
		int try = max_tries;

		int ok = 0;
		do{
			printf("[SEND] Sending %d\\%d\n", (max_tries+1 - try), max_tries);
			conf = send_data(&t);
			if(is_ack(conf)) {
				ok = 1;
				break;
			}
			try--;
		} while (try);

		if(!ok) {
			perror("[SEND]File corrupted, abort!\n");
			exit(1);
		}
	}

	/* TODO 3.1: Receive the confirmation */

	/* TODO 3.2: If we received a NACK, retransmit the previous frame */

	/* TODO 3.3: Update this to read the content of a file and send it as
	 * chunks of that file given a MTU of 1500 bytes */

	write(1, "[SENDER] Job done, all sent.\n", 29);
	close(inputFile);

	return 0;
}
