#ifndef PARAMETERS_H
#define PARAMETERS_H

#define MAX_SUPPORTED_FILES 1
#define SUPPORTED_FILES     "*.c\r\n"
#define MAX_INFO            5

const char* sformat[MAX_SUPPORTED_FILES] = {"c"};

struct parameters{
    char *author;
    char *add[MAX_INFO];
    char *fname;

    int maxadd;
};

#endif // PARAMETERS_H
