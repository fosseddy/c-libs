#include <stdlib.h>
#include <stdio.h>

enum {
    INIT_CAP = 8
};

struct header {
    int len;
    int cap;
    int data_size;
};

void *arrinit(int data_size, int cap)
{
    void *buf, *arr;
    struct header *h;

    if (cap <= 0) {
        cap = INIT_CAP;
    }

    // TODO: error
    buf = malloc(data_size * cap + sizeof(struct header));

    h = buf;
    arr = (char *) buf + sizeof(struct header);

    h->len = 0;
    h->cap = cap;
    h->data_size = data_size;

    return arr;
}

struct header *arrheader(void *arr)
{
    return (struct header *) arr - 1;
}

int arrlen(void *arr)
{
    return arrheader(arr)->len;
}

int arrcap(void *arr)
{
    return arrheader(arr)->cap;
}

void *arrgrow(void *arr)
{
    struct header *h = arrheader(arr);
    int new_cap = h->cap * 2;

    void *buf;

    // TODO: error
    buf = realloc(h, h->data_size * new_cap + sizeof(struct header));

    h = buf;
    arr = (char *) buf + sizeof(struct header);

    h->cap = new_cap;

    return arr;
}

void *arrmaybe_grow(void *arr)
{
    if (arrlen(arr) >= arrcap(arr)) {
        return arrgrow(arr);
    }

    return arr;
}

void *arrnext(void *arr)
{
    struct header *h = arrheader(arr);
    void *slot = (char *) arr + h->len * h->data_size;

    ++h->len;

    return slot;
}

int main(void)
{
    int *arr = NULL;

    arr = arrinit(sizeof(int), 1);

    arr = arrmaybe_grow(arr);
    arr[arrheader(arr)->len++] = 1;

    arr = arrmaybe_grow(arr);
    arr[arrheader(arr)->len++] = 2;

    arr = arrmaybe_grow(arr);
    arr[arrheader(arr)->len++] = 3;

    arr = arrmaybe_grow(arr);
    arr[arrheader(arr)->len++] = 4;

    arr = arrmaybe_grow(arr);
    int *slot = arrnext(arr);
    *slot = 5;

    for (int i = 0; i < arrlen(arr); ++i) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    return 0;
}
