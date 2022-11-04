#ifndef PARAMETERS_H
#define PARAMETERS_H

#define MAX_SUPPORTED_FILES 4
#define SUPPORTED_FILES     "*.c, *.cpp, *.h, *.hpp\r\n"
#define SUPPORTED_ARRAY     "c", "cpp", "h", "hpp"

#define MAX_INFO            5

extern const char *sformat[MAX_SUPPORTED_FILES];

struct parameters{
    char *author;
    char *add[MAX_INFO];
    char *fname;

    int maxadd;
};

#endif // PARAMETERS_H
