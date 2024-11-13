#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef SORTING_H
#define SORTING_H

typedef struct _Records Records;

struct _Records{
    int     id;
    char    field1[15];
    int     field2;
    float   field3;
};

Records** records_create();

void free_records(Records **);

int compare_f1(const void*, const void*);

int compare_f2(const void*, const void*);

int compare_f3(const void*, const void*);

void sort_records(FILE*, FILE*, size_t, size_t);

void merge(void **, int , int, int, int (*compar)(const void *, const void*));

void merge_sort_rec(void **,int, int, int (*compar)(const void *, const void*));

void merge_sort(void**, int, int (*compar)(const void*, const void*));

int partition(void**, int, int, int (*compar)(const void*, const void*));

void quick_sortRec(void**, int, int (*compar)(const void*, const void*));

void quick_sort(void**, int, int (*compar)(const void*, const void*));


#endif