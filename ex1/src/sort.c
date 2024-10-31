#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sort.h"

#define CAPACITY 20000000

//&   := parte di codice da sostituire con una chiamata a funzione

struct _Records{
    int     id;
    char    field1[20];
    int     field2;
    float   field3;
};

Records* records_create(){
    Records *records = malloc(CAPACITY * sizeof(Records));

    if(records == NULL){
        printf("MEMORY EMPTY");
        exit(1);
    }

    records->id = 0;
    records->field1[0] = '\0';
    records->field2 = 0;
    records->field3 = 0;

    return records;
}

int compare_f1(const void* a, const void* b){
    return strcmp(((Records*)a)->field1, ((Records*)b)->field1);
}

int compare_f2(const void* a, const void* b){
    return ((Records*)a)->field2 - ((Records*)b)->field2;
}

int compare_f3(const void* a, const void* b){
    float diff = ((Records*)a)->field3 - ((Records*)b)->field3;
    return (diff > 0) - (diff < 0);
}

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo){

    Records *records = malloc(CAPACITY * sizeof(Records));//
    unsigned long cont = 0;//&

    while(fscanf(infile, "%d, %19[^,],%d,%f\n", &records[cont].id, &records[cont].field1, &records[cont].field2, &records[cont].field3)){
        cont++;
    }

    int (*compare)(void*, void*) = NULL;
    if(field == 1){compare = compare_f1;}
    else if(field == 2){compare = compare_f2;}
    else if(field == 3){compare = compare_f3;}
    else{printf("FIELD VALUE NOT VALID"); exit(1);}

    if(algo == 1){merge_sort(records, cont, sizeof(records), compare);}
    else if(algo == 2){quick_sort(records, cont, sizeof(records), compare);}
    else{printf("ALGO VALUE NOT VALID"); exit(1);}

    for(unsigned long i = 0; i < cont; i++){
        fprintf(outfile, "%d,%s,%d,%.2f", records[i].id, records[i].field1, records[i].field2, records[i].field3);
    }

    free(records);
}

void merge_sort(Records*, unsigned long, size_t, int (*compare)(void*, void*));

void quick_sort(Records*, unsigned long, size_t, int (*compare)(void*, void*));

int partition(Records*, void*, unsigned long);
