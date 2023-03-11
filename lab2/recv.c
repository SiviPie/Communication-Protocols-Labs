#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

/* Do not touch these two */
#define HOST "127.0.0.1"
#define PORT 10001

#include "common.h"

/* Our unqiue layer 2 ID */
static int ID = 123131;

/* Function which our protocol implementation will provide to the upper layer. */
int recv_frame(char *buf, int size)
{
	/* TODO 1.1: Call recv_byte() until we receive the frame start
	 * delimitator. This operation makes this function blocking until it
	 * receives a frame. */

	char c1, c2;
	c1 = recv_byte();
	c2 = recv_byte();

	/* Cat timp nu am primit DLE STX citim bytes */
	while ((c1 != DLE) && (c2 != STX))
	{
		c1 = c2;
		c2 = recv_byte();
	}

	printf("%d ## %d\n", c1, c2);

	/* TODO 2.1: The first two 2 * sizeof(int) bytes represent sender and receiver ID */

	/* TODO 2.2: Check that the frame was sent to me */

	/* TODO 1.2: Read bytes and copy them to buff until we receive the end of the frame */

	int index=0;
	char c;

	while(index < size) {
		c = recv_byte();
		if (c == DLE) {
			c = recv_byte();
			if(c == DLE) {
				buf[index++] = c;
				printf("%c\n",c);
			} else if (c == ETX){
				return index;
			} else {
				printf("EROARE");
				return -1;
			}
			//continue;
		} else {
		buf[index++] = c;
		printf("%c\n",c);
		}
	}

	/* If everything went well return the number of bytes received */
	return index;
}

int main(int argc, char **argv)
{
	/* Do not touch this */
	init(HOST, PORT);

	/* TODO 1.0: Allocate a buffer and call recv_frame */
	char buf[30];
	int size = recv_frame(buf,30);

	printf("Size: %d\n",size);

	/* TODO 3: Measure latency in a while loop for any frame that contains
	 * a timestamp we receive, print frame_size and latency */

	printf("[RECEIVER] Finished transmission\n");
	return 0;
}
