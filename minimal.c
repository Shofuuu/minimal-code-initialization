/*
 * Source getopt : https://www.thegeekstuff.com/2013/01/c-argc-argv/
 * Source time unix : https://zetcode.com/articles/cdatetime/
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "dataset.h"
#include "parameters.h"

#define MAX_HELPMSG 7

/* Files and edit */
char *format(struct parameters *p);
int ftype(struct parameters *p);
int wfile(struct parameters *p);
char *gtime(void);

/* String needs */
char *rev(char *str);
int cmp(char *src, const char *str, size_t size);
size_t len(const char *str);

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("[Err:argc] Please specify at least one argument!\r\n");
        exit(-1);
    }

    char opt = 0;
    unsigned char idx = 0;
    unsigned char valid = 0;

    const char *helpmsg[MAX_HELPMSG] = {
        "Help information : \r\n",
        " minimal [h, f, a, i]\r\n",
        "\nExample : \r\n",
        " minimal -f \"main.c\"\r\n",
        " minimal -f \"main.c\" -a \"Shofuwan\"\r\n",
        "\nSupported files :\r\n",
        SUPPORTED_FILES
    };

    struct parameters p = { NULL, {NULL}, NULL, 0 };

    while((opt = getopt(argc, argv, "hf:a:i:")) != -1){
        switch(opt){
            case 'h':
                for(int x=0;x<MAX_HELPMSG;x++) printf("%s", helpmsg[x]);
                valid = 0;
            break;

            case 'f':
                p.fname = optarg;
                
                if(ftype(&p) != 0){
                    printf("[Err:file] Sorry, \"%s\" is not supported yet.\r\n", format(&p));
                    exit(-1);
                }

                valid++;
            break;

            case 'a':
                p.author = optarg;
                valid++;
            break;

            case 'i':
                if(idx < MAX_INFO){
                    p.add[idx] = optarg;

                    idx++;
                    p.maxadd = idx;
                }else{
                    printf("[Warn:MAX_INFO] Maximum additional information is %d.", idx);
                }

                valid++;
            break;

            case '?':
                if('f' == optopt) printf("[Err:file] Please mention the file name using -f [file name]\r\n");
                else if('a' == optopt) printf("[Err:author] Did you not mentioning any author name? use -a [author]\r\n");
                else if('i' == optopt) printf("[Err:information] Additional information needed. use -i [info1]\r\n");
                else printf("[Err:?] Unknown error caught while parsing the arguments!\r\n");

                exit(-1);
            break;
        }
    }

    if( (valid > 0) && ((p.fname != NULL) || (p.author != NULL)) ){
        printf("[Info:summary] Document name : %s\r\n", p.fname);
        printf("[Info:summary] Format : %s\r\n", format(&p));
        printf("[Info:summary] Author : %s\r\n", (p.author != NULL ? p.author : "-"));
    }else{
        exit(-1);
    }
    
    if(p.maxadd > 0){
        for(int x=0;x<p.maxadd;x++){
            printf("[Info:summary] Additional info %d : %s\r\n", x, p.add[x]);
        }
    }

    /* Begin processing and generating files */
    wfile(&p);
    printf("[Info:generate] OK\r\n");

    return 0;
}

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

int wfile(struct parameters *p){
    int valid = 0;

    FILE *file = fopen(p->fname, "w");

    if(file == NULL) valid = -1;

    if(cmp(format(p), "c", 1) == 0){
        for(int x=0;x<MAX_LINE_C;x++){
            if( (EOC_C) == x && p->maxadd > 0){
                for(int y=0;y<p->maxadd;y++){
                    fprintf(file, "*\n* -- Additional Info -- \r\n");
                    fprintf(file, "* %s\r\n", p->add[y]);
                }
            }
            
            if(x == DATASET_DOC) fprintf(file, "%s%s\r\n", dataset_c[x], p->fname);
            else if(x == DATASET_DATE) fprintf(file, "%s%s\r\n", dataset_c[x], gtime());
            else if(x == DATASET_AUTHOR) fprintf(file, "%s%s\r\n", dataset_c[x], p->author);
            else fprintf(file, "%s\r\n", dataset_c[x]);
        }
    }

    fclose(file);

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



