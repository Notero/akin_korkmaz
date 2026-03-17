//
//  main.c
//  mysh
//
//  Created by Akin Korkmaz on 3/12/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024
#define MAX_ARGS 128

// Function prototypes.
void execute_command(char **args, char *in_file, char *out_file);
void execute_pipe(char **left_args, char *left_in, char *left_out,
                  char **right_args, char *right_in, char *right_out);

int main(void) {
    char line[MAX_LINE];

    while (1) {
        // Only print the prompt if input is from a terminal.
        if (isatty(STDIN_FILENO)) {
            printf("$ ");
            fflush(stdout);
        }
        
        // Read input from stdin.
        if (!fgets(line, MAX_LINE, stdin)) {
            break;  // End-of-file or error.
        }

        // Remove the newline character.
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) continue;  // Skip empty input.

        if(strcmp(line, "EXIT") == 0){
            exit(0);
        }
        
        // Check if the input contains a pipe.
        if (strchr(line, '|') != NULL) {
            // Split the input into two commands at the pipe.
            char *left_str = strtok(line, "|");
            char *right_str = strtok(NULL, "|");

            if (left_str == NULL || right_str == NULL) {
                fprintf(stderr, "Error: invalid pipe usage\n");
                continue;
            }

            // Process left command.
            char *left_tokens[MAX_ARGS];
            int left_count = 0;
            char *left_in = NULL;
            char *left_out = NULL;  // Not allowed with pipe.
            char *token = strtok(left_str, " ");
            while (token != NULL) {
                if (token[0] == '<') {
                    if (left_in != NULL) {
                        fprintf(stderr, "Error: multiple input redirections in left command\n");
                        left_count = -1;
                        break;
                    }
                    if (strlen(token) == 1) {
                        fprintf(stderr, "Error: input redirection file is empty in left command\n");
                        left_count = -1;
                        break;
                    }
                    left_in = token + 1;  // Skip the '<'
                } else if (token[0] == '>') {
                    if (left_out != NULL) {
                        fprintf(stderr, "Error: multiple output redirections in left command\n");
                        left_count = -1;
                        break;
                    }
                    if (strlen(token) == 1) {
                        fprintf(stderr, "Error: output redirection file is empty in left command\n");
                        left_count = -1;
                        break;
                    }
                    left_out = token + 1;
                } else {
                    left_tokens[left_count++] = token;
                }
                token = strtok(NULL, " ");
            }
            if (left_count == -1) continue;
            left_tokens[left_count] = NULL;

            // Process right command.
            char *right_tokens[MAX_ARGS];
            int right_count = 0;
            char *right_in = NULL;   // Not allowed with pipe.
            char *right_out = NULL;
            token = strtok(right_str, " ");
            while (token != NULL) {
                if (token[0] == '<') {
                    if (right_in != NULL) {
                        fprintf(stderr, "Error: multiple input redirections in right command\n");
                        right_count = -1;
                        break;
                    }
                    if (strlen(token) == 1) {
                        fprintf(stderr, "Error: input redirection file is empty in right command\n");
                        right_count = -1;
                        break;
                    }
                    right_in = token + 1;
                } else if (token[0] == '>') {
                    if (right_out != NULL) {
                        fprintf(stderr, "Error: multiple output redirections in right command\n");
                        right_count = -1;
                        break;
                    }
                    if (strlen(token) == 1) {
                        fprintf(stderr, "Error: output redirection file is empty in right command\n");
                        right_count = -1;
                        break;
                    }
                    right_out = token + 1;
                } else {
                    right_tokens[right_count++] = token;
                }
                token = strtok(NULL, " ");
            }
            if (right_count == -1) continue;
            right_tokens[right_count] = NULL;

            // Check for redirection conflicts with pipe.
            if (left_out != NULL) {
                fprintf(stderr, "Error: left pipe command cannot have output redirection\n");
                continue;
            }
            if (right_in != NULL) {
                fprintf(stderr, "Error: right pipe command cannot have input redirection\n");
                continue;
            }
            
            execute_pipe(left_tokens, left_in, left_out, right_tokens, right_in, right_out);
        } else {
            // No pipe: process a single command.
            char *tokens[MAX_ARGS];
            int count = 0;
            char *in_file = NULL;
            char *out_file = NULL;
            char *token = strtok(line, " ");
            while (token != NULL) {
                if (token[0] == '<') {
                    if (in_file != NULL) {
                        fprintf(stderr, "Error: multiple input redirections\n");
                        count = -1;
                        break;
                    }
                    if (strlen(token) == 1) {
                        fprintf(stderr, "Error: input redirection file is empty\n");
                        count = -1;
                        break;
                    }
                    in_file = token + 1;
                } else if (token[0] == '>') {
                    if (out_file != NULL) {
                        fprintf(stderr, "Error: multiple output redirections\n");
                        count = -1;
                        break;
                    }
                    if (strlen(token) == 1) {
                        fprintf(stderr, "Error: output redirection file is empty\n");
                        count = -1;
                        break;
                    }
                    out_file = token + 1;
                } else {
                    tokens[count++] = token;
                }
                token = strtok(NULL, " ");
            }
            if (count == -1) continue;
            tokens[count] = NULL;

            // Skip if no command provided.
            if (tokens[0] == NULL) continue;

            execute_command(tokens, in_file, out_file);
        }
    }

    return 0;
}

// Executes a single command with optional input and output redirection.
void execute_command(char **args, char *in_file, char *out_file) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {  // Child process.
        if (in_file) {
            int fd_in = open(in_file, O_RDONLY);
            if (fd_in < 0) {
                perror("open input file");
                exit(EXIT_FAILURE);
            }
            if (dup2(fd_in, STDIN_FILENO) < 0) {
                perror("dup2 input");
                exit(EXIT_FAILURE);
            }
            close(fd_in);
        }
        if (out_file) {
            int fd_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("open output file");
                exit(EXIT_FAILURE);
            }
            if (dup2(fd_out, STDOUT_FILENO) < 0) {
                perror("dup2 output");
                exit(EXIT_FAILURE);
            }
            close(fd_out);
        }
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {  // Parent process.
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}

// Executes two commands connected by a pipe.
// The left command may have input redirection,
// while the right command may have output redirection.
void execute_pipe(char **left_args, char *left_in, char *left_out,
                  char **right_args, char *right_in, char *right_out) {
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the left child.
    pid_t left_pid = fork();
    if (left_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (left_pid == 0) {
        if (dup2(pipefd[1], STDOUT_FILENO) < 0) {
            perror("dup2 pipe write");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        close(pipefd[1]);

        if (left_in) {
            int fd_in = open(left_in, O_RDONLY);
            if (fd_in < 0) {
                perror("open left input file");
                exit(EXIT_FAILURE);
            }
            if (dup2(fd_in, STDIN_FILENO) < 0) {
                perror("dup2 left input");
                exit(EXIT_FAILURE);
            }
            close(fd_in);
        }
        execvp(left_args[0], left_args);
        perror("execvp left");
        exit(EXIT_FAILURE);
    }

    // Fork the right child.
    pid_t right_pid = fork();
    if (right_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (right_pid == 0) {
        if (dup2(pipefd[0], STDIN_FILENO) < 0) {
            perror("dup2 pipe read");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        close(pipefd[1]);

        if (right_out) {
            int fd_out = open(right_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("open right output file");
                exit(EXIT_FAILURE);
            }
            if (dup2(fd_out, STDOUT_FILENO) < 0) {
                perror("dup2 right output");
                exit(EXIT_FAILURE);
            }
            close(fd_out);
        }
        execvp(right_args[0], right_args);
        perror("execvp right");
        exit(EXIT_FAILURE);
    }

    // Parent process: close both ends of the pipe.
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both children.
    int status;
    waitpid(left_pid, &status, 0);
    waitpid(right_pid, &status, 0);
}

