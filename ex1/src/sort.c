/**
 * @file sort.c
 * @brief Implementation of sorting algorithms
 * @details Implements merge sort and quicksort along with helper functions
 */

#include "sort.h"

#define CAPACITY 20000000

/**
 * @brief Creates and initializes Records array
 * @return Initialized array of Record pointers
 */
Records** records_create(){
    Records **records = malloc(CAPACITY * sizeof(Records*));

    if(records == NULL){
        printf("MEMORY EMPTY");
        exit(1);
    }
    
    for(size_t i = 0; i < CAPACITY; i++){
        records[i] = malloc(sizeof(Records));
        if(records[i] == NULL){
            for(size_t j = 0; j < i; j++) {
                free(records[j]);
            }
            free(records);
            puts("EMPTY MEMORY");
            exit(1);
        }
    }

    for(size_t i = 0; i < CAPACITY; i++){
        records[i]->id = 0;
        records[i]->field1[0] = '\0';
        records[i]->field2 = 0;
        records[i]->field3 = 0;
    }

    return records;
}

/**
 * @brief String field comparison implementation
 */
int compare_f1(const void* a, const void* b){
    return strcmp(((Records*)a)->field1, ((Records*)b)->field1);
}

/**
 * @brief Integer field comparison implementation
 */
int compare_f2(const void* a, const void* b){
    return ((Records*)a)->field2 - ((Records*)b)->field2;
}

/**
 * @brief Float field comparison implementation
 */
int compare_f3(const void* a, const void* b){
    float diff = ((Records*)a)->field3 - ((Records*)b)->field3;
    return (diff > 0) - (diff < 0);
}

/**
 * @brief Merge implementation
 * @details Merges two sorted subarrays using temporary arrays
 */
void merge(void **base, int first, int mid, int last, int (*compar)(const void *, const void*)) {
    int n1 = mid - first + 1;
    int n2 = last - mid;
    
    void **ArrayLeft = (void**)malloc(n1 * sizeof(void*));
    if(!ArrayLeft) {
        puts("ERROR ALLOCATION ARRAYLEFT");
        exit(1);
    }

    void **ArrayRight = (void**)malloc(n2 * sizeof(void*));
    if(!ArrayRight) {
        puts("ERROR ALLOCATION ARRAYRIGHT");
        free(ArrayLeft);
        exit(1);
    }
    
    for(int i = 0; i < n1; i++) {
        ArrayLeft[i] = base[first + i];
    }
    for(int j = 0; j < n2; j++) {
        ArrayRight[j] = base[mid + j + 1];
    }
    
    int i = 0, j = 0, k = first;
    
    while (i < n1 && j < n2) {
        if (compar(ArrayLeft[i], ArrayRight[j]) <= 0) {
            base[k] = ArrayLeft[i];
            i++;
        } else {
            base[k] = ArrayRight[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        base[k] = ArrayLeft[i];
        i++;
        k++;
    }
    while (j < n2) {
        base[k] = ArrayRight[j];
        j++;
        k++;
    }
    
    free(ArrayLeft);
    free(ArrayRight);
}

/**
 * @brief Recursive merge sort implementation
 */
void merge_sort_rec(void **base, int first, int last, int (*compar)(const void *, const void*)){
    if(first < last){
        size_t mid = floor((first + last) / 2);
        merge_sort_rec(base, first, mid, compar);
        merge_sort_rec(base, mid + 1, last, compar);
        merge(base, first, mid, last, compar);
    }
    return;
}

/**
 * @brief Merge sort wrapper with timing measurement
 */
void merge_sort(void **base, int nitems, int (*compar)(const void *, const void*)) {
    clock_t from = clock();
    merge_sort_rec(base, 0, nitems - 1, compar);
    clock_t to = clock();
    double time_taken = (double)(to - from) / CLOCKS_PER_SEC;
    printf("The time taken by the merge_sort function is: %f sec\n", time_taken);
}

/**
 * @brief Element swap implementation
 */
void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Recursive quicksort implementation
 */
void quick_sort_rec(void **arr, int left, int right, int (*compar)(const void *, const void *)) {
    if (left >= right) return;

    void *pivot = arr[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (compar(arr[i], pivot) < 0) i++;
        while (compar(arr[j], pivot) > 0) j--;
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) quick_sort_rec(arr, left, j, compar);
    if (i < right) quick_sort_rec(arr, i, right, compar);
}

/**
 * @brief Quicksort wrapper with timing
 */
void quick_sort(void **base, size_t nitems, int (*compar)(const void *, const void *)) {
    clock_t from = clock();

    if (nitems > 0) {
        quick_sort_rec(base, 0, nitems - 1, compar);
    }

    clock_t to = clock();
    double time_taken = (double)(to - from) / CLOCKS_PER_SEC;
    printf("The time taken by quick_sort function is: %f sec\n", time_taken);
}

/**
 * @brief Frees all allocated memory
 */
void free_records(Records **records) {
    puts("destruction of data structure");
    for (int i = 0; i < CAPACITY; i++) {
        free(records[i]);
    }
    free(records);
}

/**
 * @brief Main sorting function implementation
 */
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo){
    puts("creation data structure");
    Records **records = records_create();
    int cont = 0;

    puts("reading file");
    while(fscanf(infile, "%d,%[^,],%d,%f\n", &records[cont]->id, 
          records[cont]->field1, &records[cont]->field2, 
          &records[cont]->field3) == 4){
        cont++;
    }

    int (*compare)(const void*, const void*) = NULL;
    if(field == 1){compare = compare_f1;}
    else if(field == 2){compare = compare_f2;}
    else if(field == 3){compare = compare_f3;}
    else{printf("FIELD VALUE NOT VALID"); exit(1);}

    puts("sorting...");
    if(algo == 1){merge_sort((void **)records, cont, compare);}
    else if(algo == 2){quick_sort((void **)records, cont, compare);}
    else{printf("ALGO VALUE NOT VALID"); exit(1);}

    puts("printing result");
    for(int i = 0; i < cont; i++){
        fprintf(outfile, "%d,%s,%d,%.2f\n", records[i]->id, 
                records[i]->field1, records[i]->field2, records[i]->field3);
    }

    free_records(records);
}