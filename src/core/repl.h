#ifndef REPL_H
#define REPL_H

#include <stddef.h>
#include <stdbool.h>

#define REPL_HISTORY_SIZE 10
#define REPL_LINE_MAX 64

typedef struct {
    char expr[REPL_LINE_MAX];
    char result[REPL_LINE_MAX];
} repl_entry_t;

void repl_clear(void);
int repl_line_count(void);
void repl_add_entry(const char* expr, const char* result);
void repl_render(void);

#endif // REPL_H
