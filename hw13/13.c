#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char *directory = "./dir";
    
    char link[128];
    char file[128];
 
    int fd; 
    int depth = 0;

    mkdir(directory, 0777);
    chdir(directory);
    fd = creat("a", 0644);
    snprintf(file, sizeof(file), "a");
    snprintf(link, sizeof(link), "aa");
    symlink(file, link);

    while((fd = open(link, O_RDONLY)) != -1 && depth++ < 100) {
        close(fd);
        
        snprintf(file, sizeof(file), "aa");
        snprintf(link, sizeof(link), "ab");
       
        symlink(file, link);
    }
    
    unlink("a");
    unlink("aa");
    
    for(int i = 0; i < depth; ++i) {
        snprintf(link, sizeof(link), "%s/%c%c", directory, 'a' + i, 'a' + i);
        unlink(link);
    }
    rmdir(directory);
    
    printf("Depth : %d", depth);
    return 0;
}
