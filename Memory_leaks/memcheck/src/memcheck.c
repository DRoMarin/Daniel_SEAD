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
char redirect[] = " 2>&1 1>/dev/null";


if (argc==1)
{
    printf("ERROR: no options\n");
    abort();        /* code */
}
while ((opt = getopt(argc,argv,"ahp:")) != -1){ 
    switch (opt){
        case 'a':
            printf("Author: Daniel Rojas M.\n San José, Costa Rica\n");
            break;
        case 'h':
            printf("Usage: ./memcheck [-p $PATH/PROGRAM][-h][-a]\n");
            printf("  -p $PATH/PROGRAM    Run program and determine memory leaks\n");
            printf("  -a                  Display information about the author\n");
            printf("  -h                  Display this help message with usage instructions\n");
            break;
        case 'p':
            //printf("%s\n",optarg);
            program = optarg;
            break; 
        default:
            abort();
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
        
        //printf("%s\n", command);

        fp = popen(command,"r");

        if (fp == NULL){
            printf("ERROR\n");
        }
        int malloc_count = 0;
        int free_count = 0;

        while (fgets(msg,sizeof(msg),fp) != NULL){
            //printf("%s",msg);
            if (!strcmp(msg,"malloc\n")){
                //printf("Malloc!\n");
                malloc_count++;
            }
            else if (!strcmp(msg,"free\n"))
            {
                //printf("Free!\n");
                free_count++;
            }
        }

        printf("***********************************************\n");
        printf(" Analysis Complete \n");
        printf("Memory Allocations: %d\n",malloc_count);
        printf("Memory Freed: %d\n", free_count);
        printf("Total Memory Leaks: %d\n", malloc_count-free_count);
        printf("***********************************************\n");

        free(command);
        free(fix_path);
        pclose(fp);
    }
    return 0;
}