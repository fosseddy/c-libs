#include <stdlib.h>
#include <stdio.h>

#include "mem.h"

enum { INIT_CAP = 8 };

void meminit(mem_t *m, int data_size, int cap)
{
    if (cap == 0) {
        cap = INIT_CAP;
    }

    m->len = 0;
    m->cap = cap;
    m->data_size = data_size;

    m->buf = malloc(m->cap * m->data_size);
    if (m->buf == NULL) {
        perror("meminit malloc");
        exit(1);
    }
}

void memgrow(mem_t *m)
{
    if (m->len >= m->cap) {
        m->cap = m->len * 2;
        m->buf = realloc(m->buf, m->cap * m->data_size);
        if (m->buf == NULL) {
            perror("memgrow malloc");
            exit(1);
        }
    }
}

void *memnext(mem_t *m)
{
    void *slot;

    memgrow(m);

    slot = (char *) m->buf + m->len * m->data_size;
    m->len++;

    return slot;
}

void memfree(mem_t *m)
{
    free(m->buf);
}
