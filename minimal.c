/*
 * Source getopt : https://www.thegeekstuff.com/2013/01/c-argc-argv/
 * Source time unix : https://zetcode.com/articles/cdatetime/
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dataset.h"
#include "parameters.h"
#include "util.h"

#define MAX_HELPMSG 7

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



