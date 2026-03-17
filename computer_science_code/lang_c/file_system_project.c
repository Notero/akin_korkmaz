//
//  main.c
//  FsProject
//
//  Created by Akin Korkmaz on 2/19/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, const char * argv[]) {
    
    if (argc != 3){
        fprintf(stderr, "USAGE: ./mvplus source_file target_file\n");
        exit(3);
    }
    
    //path1 stat
    struct stat statbuf1;
    
    //paths
    const char *source_file = argv[1];
    const char *target_file = argv[2];

    //check if file exists
    if(stat(source_file, &statbuf1) == -1){
        exit(4);
    }
    //check if file is a file
    if((statbuf1.st_mode & S_IFMT) != S_IFREG){
        exit(5);
    }
    
    //opens file for read only
    int of = open(source_file, O_RDONLY);
    
    // Creates char pointer and allocates memory enough to get all the contents
    char *contents = malloc(statbuf1.st_size + 2);
    //allocation failed
    if (contents == NULL) {
        exit(EXIT_FAILURE);
    }
    
    
    // Read file into contents from file of at the size of the file
    ssize_t bytes_read = read(of, contents, statbuf1.st_size);
    if (bytes_read != statbuf1.st_size) {
        free(contents);
        close(of);
        exit(EXIT_FAILURE);
    }
    
    close(of);
    
    int tf = open(target_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    
    ssize_t bytes_written = write(tf, contents, statbuf1.st_size);
    if (bytes_written != statbuf1.st_size){
        free(contents);
        close(tf);
        exit(EXIT_FAILURE);
    }
    
    close(tf);
    free(contents);
    return EXIT_SUCCESS;
}
