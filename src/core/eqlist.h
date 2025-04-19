#ifndef EQLIST_H
#define EQLIST_H

#include <stdbool.h>

#define MAX_EQUATIONS 10
#define EQUATION_LEN 64

typedef struct {
    char expr[EQUATION_LEN];
    bool active;
} equation_t;

extern equation_t eq_list[MAX_EQUATIONS];

#endif // EQLIST_H
