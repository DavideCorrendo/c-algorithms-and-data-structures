#ifndef SORTING_H
#define SORTING_H

typedef struct _Records Records;

Records* records_create();

int compare_f1(const void*, const void*);

int compare_f2(const void*, const void*);

int compare_f3(const void*, const void*);

void sort_records(FILE*, FILE*, size_t, size_t);

void merge_sort(Records*, unsigned long, size_t, int (*compare)(void*, void*));

void quick_sort(Records*, unsigned long, size_t, int (*compare)(void*, void*));

int partition(Records*, void*, unsigned long);

#endif