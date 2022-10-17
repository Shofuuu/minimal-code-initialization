#include "util.h"

/* Files and edit */
char *format(struct parameters *p){
    unsigned char str = len(p->fname);
    char *fmt = malloc((size_t)str * sizeof(char));

    for(int x=0;x<str;x++){
        if(p->fname[(str-1)-x] != '.'){
            fmt[x] = p->fname[(str-1)-x];
        }
    }

    return rev(fmt);
}

int ftype(struct parameters *p){
    int valid = -1;
    char *fmt = format(p);

    for(int x=0;x<MAX_SUPPORTED_FILES;x++){
        if(cmp(fmt, sformat[x], len(sformat[x])) == 0){
            valid = 0;
            break;
        }
    }

    return valid;
}

char *gtime(void){
    size_t size = 22;
    char *data = malloc(sizeof(char) * size);

    time_t ntime;
    struct tm *ntm;

    if((ntime = time(NULL)) == -1) data = NULL;
    if((ntm = localtime(&ntime))  == NULL) data = NULL;

    strftime(data, size, "%d/%m/%Y - %H:%M:%S", ntm);

    return data;
}

/* write files contain all pattern neededs */
int wfile(struct parameters *p){
    int valid = 0;

    FILE *file = fopen(p->fname, "w");

    if(file == NULL) valid = -1;

    if(cmp(format(p), "c", 1) == 0){
        for(int x=0;x<MAX_LINE_C;x++){
            if( (EOC_C) == x && p->maxadd > 0){
                fprintf(file, "*\n* -- Additional Info -- \n");
                
                for(int y=0;y<p->maxadd;y++){
                    fprintf(file, "* %s\n", p->add[y]);
                }
            }
            
            if(x == DATASET_DOC) fprintf(file, "%s%s\n", dataset_c[x], p->fname);
            else if(x == DATASET_DATE) fprintf(file, "%s%s\n", dataset_c[x], gtime());
            else if(x == DATASET_AUTHOR) fprintf(file, "%s%s\n", dataset_c[x], p->author);
            else fprintf(file, "%s\n", dataset_c[x]);
        }
    }else if(cmp(format(p), "h", 1) == 0){
        char *upper = malloc(len((const char*)p->fname) * sizeof(char));
        char *libdef = malloc(len((const char*)p->fname) * sizeof(char));
        upper = uphead(p->fname);
        cpy(libdef, (const char*)upper, len((const char*)p->fname) * sizeof(char));

        for(int x=0;x<MAX_LINE_H;x++){
            if( (EOC_H) == x && p->maxadd > 0){
                fprintf(file, "*\n* -- Additional Info -- \n");
                
                for(int y=0;y<p->maxadd;y++){
                    fprintf(file, "* %s\n", p->add[y]);
                }
            }
            
            if(x == DATASET_DOC) fprintf(file, "%s%s\n", dataset_h[x], p->fname);
            else if(x == DATASET_DATE) fprintf(file, "%s%s\n", dataset_h[x], gtime());
            else if(x == DATASET_AUTHOR) fprintf(file, "%s%s\n", dataset_h[x], p->author);
            else if(x == DATASET_H_IFNDEF) fprintf(file, "%s%s\n", dataset_h[x], upper);
            else if(x == DATASET_H_DEFINE) fprintf(file, "%s%s\n", dataset_h[x], upper);
            else if(x == DATASET_H_ENDIF) fprintf(file, "%s%s\n", dataset_h[x], upper);
            else fprintf(file, "%s\n", dataset_h[x]);
        }
    }

    fclose(file);

    return valid;
}

/* String needs */
char *rev(char *str){
    char *nstr = malloc(len((const char*)str) * sizeof(char));
    int sz = len((const char*)str);

    for(int x=0;x<sz;x++) nstr[x] = str[(sz-1)-x];

    return nstr;
}

int cmp(char *src, const char *str, size_t size){
    int valid = 0;

    for(int x=0;x<size;x++){
        if(*str++ != *src++)
            valid -= 1;
    }

    return valid;
}

size_t len(const char *str){
    size_t count = 0;

    while(*str++) count++;
    return count;
}

char *uphead(char *str){
    size_t size = len((const char*)str);
    char *data = malloc(size * sizeof(char));

    for(int x=0;x<size;x++){
        if( (str[x] >= 97) && (str[x] <= 122) ){
            data[x] = str[x]-32;
            //printf("[Debug:uphead:0] %d [%d]\r\n", data[x], x);
        }else if( (str[x] == '.') || (str[x] == '-') || (str[x] == '_') ){
            data[x] = '_';
            //printf("[Debug:uphead:1] %d [%d]\r\n", data[x], x);
        }else{
            data[x] = str[x];
            //printf("[Debug:uphead:2] %d [%d]\r\n", data[x], x);
        }
    }

    //char *ndata = malloc(size * sizeof(char));
    //cpy(ndata, (const char*)data, size);

    return data;
}

int cpy(char *dst, const char *src, size_t size){
    int valid = 0;

    if(size < 1) valid = -1;

    for(int x=0;x<size;x++){
        *dst++ = *src++;
    }

    return valid;
}



