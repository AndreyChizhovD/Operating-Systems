#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    size_t size;
    int fd;
    char name[] = "FIFO.fifo";
    (void)umask(0);

    if (mknod(name, S_IFIFO | 0666, 0) < 0) {
    	printf("ERROR creating FIFO\n");
    	exit(-1);
    }

    if ((fd = open(name, O_WRONLY)) < 0) {
    	printf("ERROR opening FIFO for writing\n");
    	exit(-1);
    }

    size = write(fd, "This is a text", 15);
    if (size != 15) {
    	printf("ERROR writing the hole string\n"); 
    	exit(-1);
    }

    if (close(fd) < 0) {
    	printf("ERROR closing FIFO\n"); 
    	exit(-1);
    }

    return 0;
}
