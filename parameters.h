#ifndef PARAMETERS_H
#define PARAMETERS_H

#define MAX_SUPPORTED_FILES 2
#define SUPPORTED_FILES     "*.c, *.h\r\n"
#define SUPPORTED_ARRAY     "c", "h"

#define MAX_INFO            5

extern const char *sformat[MAX_SUPPORTED_FILES];

struct parameters{
    char *author;
    char *add[MAX_INFO];
    char *fname;

    int maxadd;
};

#endif // PARAMETERS_H
