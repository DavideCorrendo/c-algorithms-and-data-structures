/**
 * @file main.c
 * @brief Main program entry point
 * @details Handles command line arguments and initiates sorting
 * 
 * Usage: program input_file output_file field_num algo_num
 * - field_num: 1=string, 2=integer, 3=float
 * - algo_num: 1=merge sort, 2=quicksort
 */

#include "sort.h"

/**
 * @brief Main function
 * @param argc Argument count
 * @param argv Argument values
 * @return 0 on success, 1 on error
 */
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