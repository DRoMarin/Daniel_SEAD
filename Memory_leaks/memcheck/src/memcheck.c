#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
int opt;
extern char *optarg;
char * program = NULL;
FILE *fp; 
char msg[100];
char ld_preload[] = "LD_PRELOAD=";
char libmem[] = "lib/libmemcheck.so $PWD/";
char memcheck_string[] = "bin/memcheck";
char redirect[] = " 2>&1 >/dev/null";


while ((opt = getopt(argc,argv,"ahp:")) != -1){
    switch (opt){
        case 'a':
            printf("mensaje autor TBD\n");
            break;
        case 'h':
            printf("mensaje ayuda TBD\n");
            break;
        case 'p':
            printf("%s\n",optarg);
            program = optarg;
            break; 
        default:
            break;
        }
    }
    if (program != NULL){
        char * fix_path = malloc(strlen(argv[0])-strlen(memcheck_string)+strlen(libmem)+1);
        strcpy(fix_path,argv[0]);
        char * replace = strstr(fix_path,memcheck_string);
        strcpy(replace,libmem);
        char * command = malloc(strlen(ld_preload)+strlen(fix_path)+strlen(program) +strlen(redirect) +1);
        strcpy(command,ld_preload);
        strcat(command,fix_path);
        strcat(command,program);
        strcat(command,redirect);
        
        printf("%s\n", command);

        fp = popen(command,"r");
        if (fp == NULL){
            printf("ERROR\n");
        }
        while (fgets(msg,sizeof(msg),fp) != NULL){
            printf("CMD: %s",msg);
        }
        free(command);
        free(fix_path);
        pclose(fp);
    }
    return 0;
}