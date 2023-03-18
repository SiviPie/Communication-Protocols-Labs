#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include "common.h"
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int send_status(struct l3_msg t) {
	// this function applies crc on received data
	// and returns the status
	// ACK = AAAAA
	// NACK = NNNNN

	struct l3_msg conf;

	int ok;

	uint32_t recv_sum = ntohl(t.hdr.sum);
	t.hdr.sum = 0;
	int sum_ok = (crc32((void *)&t, sizeof(struct l3_msg)) == recv_sum);

	if(sum_ok) {
		strncpy(conf.payload, "AAAAA", 6);
		ok = 1;
	} else {
		strncpy(conf.payload, "NNNNN", 6);
		ok = 0;
	}

	// printf("[RECV] len=%d; sum(%s)=0x%04hx; payload=\"%s\";\n", t.hdr.len, sum_ok ? "GOOD" : "BAD", recv_sum, t.payload);
	printf("[RECV] len=%d; sum(%s)=0x%04hx;\";\n", t.hdr.len, sum_ok ? "GOOD" : "BAD", recv_sum);

	link_send(&conf, sizeof(struct l3_msg));
	// printf("[RECV] Conf payload: %s\n", conf.payload);

	return ok;
}

int main(int argc, char **argv) {

	//O_TRUNC flag makes sure that the file is empty before writing to it
	int outputFile = open("data.out", O_WRONLY | O_CREAT | O_TRUNC , 0644);

	if (outputFile == -1) {
        perror("Error opening file.");
        exit(1);
    }

	printf("[RECEIVER] Starting.\n");	
	
	init(HOST, PORT);

	/* TODO 3.1: In a loop, recv a frame and check if the CRC is good */
	
	while (1) {
		struct l3_msg t;

		/* Receive the frame from the link */
		int len = link_recv(&t, sizeof(struct l3_msg));
		if (len < 0) {
			perror("Receive message");
			return -1;
		}

		if(len == 0) {
			break;
		}

		if(send_status(t)) {
			write(outputFile, t.payload, t.hdr.len);
		}

	}

	/* TODO 3.2: If the crc is bad, send a NACK frame */

	/* TODO 3.2: Otherwise, write the frame payload to a file recv.data */

	/* TODO 3.3: Adjust the corruption rate */
	close(outputFile);

	return 0;
}
