//
//  main.c
//  hw6
//
//  Created by Akin Korkmaz on 1/28/25.
//

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(void) {
        
    int fd = open("/tmp/hello.c", O_CREAT | O_RDWR, 0644);
        
        if (fd == -1) {
            perror("Error opening file");
            return 1;
        }

        printf("File opened successfully with file descriptor: %d\n", fd);
        close(fd);
        return 0;
    
    return 0;
}
