#ifndef DATASET_H
#define DATASET_H

#define DATASET_DOC     1
#define DATASET_DATE    2
#define DATASET_AUTHOR  3

#define MAX_LINE_C      9
#define EOC_C           4 // END OF COMMENT of C

const char *dataset_c[MAX_LINE_C] = {
    "/*",
    "* Document : ",
    "* Date     : ",
    "* Author   : ",
    "*/",
    "\r",
    "int main(int argc, char* argv[]) {",
    "/* Code here! */",
    "}"
};

#endif // DATASET_H
