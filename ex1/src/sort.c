#include "sort.h"

#define CAPACITY 20000000


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

void merge(void **base, int first, int mid, int last, int (*compar)(const void *, const void*)) {
    // ArrayLeft dimension
    int n1 = mid - first + 1;
    // ArrayRight dimension
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
    
    int i = 0;
    int j = 0;
    int k = first;
    
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

void merge_sort_rec(void **base, int first, int last, int (*compar)(const void *, const void*)){
    if(first < last){
        size_t mid = floor((first + last) / 2);
        merge_sort_rec(base, first, mid, compar);
        merge_sort_rec(base, mid + 1, last, compar);
        merge(base, first, mid, last, compar);
    }

    return;
}

void merge_sort(void **base, int nitems, int (*compar)(const void *, const void*)) {
    clock_t from = clock();

    merge_sort_rec(base, 0, nitems - 1, compar);

    clock_t to = clock();
    double time_taken = (double)(to - from) / CLOCKS_PER_SEC;
    printf("The time taken by the merge_sort function is: %f sec\n", time_taken);
}

void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

// Partizione in tre sezioni
void threewaypartition(void **arr, int n, void *low, void *high, int (*compar)(const void *, const void *), int *start, int *end) {
    *start = 0;
    *end = n - 1;

    for (int i = 0; i <= *end;) {
        if (compar(arr[i], low) < 0) {
            swap(&arr[i++], &arr[(*start)++]);
        } else if (compar(arr[i], high) > 0) {
            swap(&arr[i], &arr[(*end)--]);
        } else {
            i++;
        }
    }
}

// Funzione ricorsiva di QuickSort
void quick_sort_rec(void **arr, int left, int right, int (*compar)(const void *, const void *)) {
    if (left >= right) return;

    // Scegli un pivot (in questo esempio il valore centrale)
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

    // Ordina ricorsivamente le due partizioni
    if (left < j) quick_sort_rec(arr, left, j, compar);
    if (i < right) quick_sort_rec(arr, i, right, compar);
}

// QuickSort wrapper
void quick_sort(void **base, size_t nitems, int (*compar)(const void *, const void *)) {
    clock_t from = clock();

    int start, end;

    int low = nitems;
    int high = nitems - low;

    // Partizione in tre sezioni
    threewaypartition(base, nitems, &low, &high, compar, &start, &end);

    // Ordina ogni sezione
    quick_sort_rec(base, 0, start - 1, compar);   // Sezione inferiore
    quick_sort_rec(base, start, end, compar);    // Sezione centrale
    quick_sort_rec(base, end + 1, nitems - 1, compar); // Sezione superiore

    clock_t to = clock();
    double time_taken = (double)(to - from) / CLOCKS_PER_SEC;
    printf("The time taken by the quick_sort function is: %f sec\n", time_taken);
}

void free_records(Records **records) {
    puts("destruction of data structure");

    for (int i = 0; i < CAPACITY; i++) {
        free(records[i]);
    }

    free(records);
}

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo){

    puts("creation data structure");
    Records **records = records_create();
    int cont = 0;

    puts("reading file");
    while(fscanf(infile, "%d,%[^,],%d,%f\n", &records[cont]->id, records[cont]->field1, &records[cont]->field2, &records[cont]->field3) == 4){
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
        fprintf(outfile, "%d,%s,%d,%.2f\n", records[i]->id, records[i]->field1, records[i]->field2, records[i]->field3);
    }

    free_records(records);
}
