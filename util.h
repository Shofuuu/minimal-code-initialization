#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dataset.h"
#include "parameters.h"

/* Files and edit */
char *format(struct parameters *p);
int ftype(struct parameters *p);
char *gtime(void);
int wfile(struct parameters *p);

/* String needs */
char *rev(char *str);
int cmp(char *src, const char *str, size_t size);
size_t len(const char *str);
char *uphead(char *str);

#endif // UTIL_H
