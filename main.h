#ifndef MAIN_H
#define MAIN_H

#define SUCCESS -1
#define FAILURE 0

#define CHUNK_SIZE 1024

#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

#include <stdio.h>
#include <string.h>


int invalid_command();
int display_help();
int validate_mp3(char *argv);

int view_mp3(char *argv[]);
int edit_mp3(int argc , char *argv[]);
#endif