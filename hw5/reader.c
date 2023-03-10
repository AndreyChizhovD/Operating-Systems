#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	size_t size;
	int fd;
	char string[15];
	char name[] = "FIFO.fifo";

	if ((fd = open(name, O_RDONLY)) < 0) {
    	printf("ERROR opening FIFO for reading\n");
    	exit(-1);
	}

	size = read(fd, string, 15);
	if (size < 0) {
	    printf("ERROR reading string\n");
    	exit(-1);
    }

    printf("Result of reading program : %s\n", string);
    if (close(fd) < 0) {
    	printf("ERROR closing FIFO\n"); 
    	exit(-1);
    }

    return 0;
}
