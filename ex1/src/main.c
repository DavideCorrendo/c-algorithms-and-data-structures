#include "sort.h"

int main(int argc, char *argv[]){
    if(argc != 5){
        puts("ERROR IN THE INSERT OF THE COMMANDS");
        exit(1);
    }

    FILE *infile = fopen(argv[1], "r");
    if(!infile){
        puts("ERROR IN THE INPUT FILE OPENING");
        exit(1);
    }
    
    FILE *outfile = fopen(argv[2], "w");
    if(!outfile){
        fclose(outfile);
        puts("ERROR IN THE OUTPUT FILE OPENING");
        exit(1);
    }
    
    size_t field = atoi(argv[3]);
    size_t algo  = atoi(argv[4]);
    
    sort_records(infile, outfile, field, algo);
    
    fclose(infile);
    fclose(outfile);
    return 0;
}