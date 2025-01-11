#ifndef DISTANCE_H
#define DISTANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    char *word;
    int distance;
} WordDistance;

int min3(int a, int b, int c);
int **initialize_memo(int rows, int cols);
void reset_memo(int **memo, int rows, int cols);
void free_memo(int **memo, int rows);
int edit_distance(const char *s1, const char *s2, int **memo);
int compare_distance(const void *, const void *);
void find_closest_words(const char **, int , char *, int **);

#endif
