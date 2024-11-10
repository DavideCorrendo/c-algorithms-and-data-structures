#include "sort.h"

int main(int argc, char *argv[]){
    if(argc != 5){
        puts("ERRORE NELL'INSERIMENTO DEL COMANDO");
        exit(1);
    }

    FILE *infile = fopen(argv[1], "r");
    if(!infile){
        puts("ERRORE NELL'APERTURA DEL FILE IN INPUT");
        exit(1);
    }
    
    FILE *outfile = fopen(argv[2], "w");
    if(!outfile){
        puts("ERRORE NELL'APERTURA DEL FILE DI OUTPUT");
        exit(1);
    }
    
    size_t field = atoi(argv[3]);
    size_t algo  = atoi(argv[4]);
    
    sort_records(infile, outfile, field, algo);
    
    fclose(infile);
    fclose(outfile);
    return 0;
}