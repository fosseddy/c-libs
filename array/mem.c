#include <stdio.h>
#include <stdlib.h>

enum {
    INIT_CAP = 8
};

void *meminit(int data_size, int cap)
{
    void *buf, *mem;
    struct memheader *h;

    if (cap <= 0) {
        cap = INIT_CAP;
    }

    buf = malloc(data_size * cap + sizeof(struct memheader));
    if (buf == NULL) {
        perror("malloc failed");
        exit(1);
    }

    h = buf;
    mem = (char *) buf + sizeof(struct memheader);

    h->len = 0;
    h->cap = cap;
    h->data_size = data_size;

    return mem;
}

struct memheader *memheader(void *mem)
{
    return (struct memheader *) mem - 1;
}

int memlen(void *mem)
{
    return memheader(mem)->len;
}

int memcap(void *mem)
{
    return memheader(mem)->cap;
}

void *memgrow(void *mem)
{
    struct memheader *h = memheader(mem);
    int new_cap = h->cap * 2;

    void *buf;

    buf = realloc(h, h->data_size * new_cap + sizeof(struct memheader));
    if (buf == NULL) {
        perror("malloc failed");
        exit(1);
    }

    h = buf;
    mem = (char *) buf + sizeof(struct memheader);

    h->cap = new_cap;

    return mem;
}

void *memmaybe_grow(void *mem)
{
    if (memlen(mem) >= memcap(mem)) {
        return memgrow(mem);
    }

    return mem;
}

void *memnext(void *mem)
{
    struct memheader *h = memheader(mem);
    void *slot = (char *) mem + h->len * h->data_size;

    ++h->len;

    return slot;
}

void memfree(void *mem)
{
    free(memheader(mem));
}
