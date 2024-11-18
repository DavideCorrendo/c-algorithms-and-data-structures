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
    merge_sort_rec(base, 0, nitems - 1, compar);
}

/*Quick sort*/
/*swap function*/
void swap(void** x, void** y) {
    void* temp = *x;
    *x = *y;
    *y = temp;
}

/*partition function of the quick*/
int partition(void** base, int first, int last, int (*compar)(const void*, const void*)) {
    /*Initialization of supporting variables*/
    int random_index = rand() % (last - first + 1) + first;
    void* pivot = base[random_index];
    
    if(random_index < last) swap(&base[random_index], &base[last]);
    
    int i = first-1;
    
    /*Effective body*/
    for(int j = first; j < last; j++) {
        
        if(compar(base[j], pivot) < 0) {
            i++;
            swap(&base[i], &base[j]);
        }
    }
    swap(&base[i+1], &base[last]);
    
    return (i + 1);
}

void quick_sort_rec(void **base, int first, int last, int (*compar)(const void*, const void*)) {
    /**base case (first = last) => 1 elemnt
     * general case */
    if(first < last) {
        int p_pos = partition(base, first, last, compar);
        quick_sort_rec(base, first, p_pos - 1, compar);
        quick_sort_rec(base, p_pos + 1, last, compar);
    }
}

void quick_sort(void **base, size_t nitems, int (*compar)(const void *, const void*)) {
    /** insert your code here
     * control for the validity of base */
    if(base == NULL) return;
    
    /*control for see if base is empty*/
    if(nitems == 0) return;
    
    /*control the validity of compar*/
    if(compar == NULL) return;
    
    if( nitems > 1) quick_sort_rec(base, 0, (int)(nitems - 1), compar);
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
