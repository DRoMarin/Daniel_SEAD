#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[]){
int opt;
extern char *optarg;
char * program = NULL;
FILE *fp; 
char msg[10];

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
        fp = popen("ls","r");
        if (fp == NULL){
            printf("ERROR\n");
        }
        while (fgets(msg,sizeof(msg),fp) != NULL){
            printf("%s",msg);
        }
    }
    return 0;
}