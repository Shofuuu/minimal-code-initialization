#ifndef DATASET_H
#define DATASET_H

#define DATASET_DOC         1
#define DATASET_DATE        2
#define DATASET_AUTHOR      3

#define MAX_LINE_C          9
#define EOC_C               4 // END OF COMMENT of C

#define DATASET_H_IFNDEF    6
#define DATASET_H_DEFINE    7
#define DATASET_H_ENDIF     10
#define MAX_LINE_H          11
#define EOC_H               4 // END OF COMMENT of H

extern const char *dataset_c[MAX_LINE_C];
extern const char *dataset_h[MAX_LINE_H];

#endif // DATASET_H
