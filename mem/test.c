#include <assert.h>
#include <stddef.h>

#include "mem.h"

struct intarr {
    int len;
    int cap;
    int data_size;
    int *buf;
};

static void test_init()
{
    struct intarr arr, arr2;

    meminit(&arr, sizeof(int), 0);
    meminit(&arr2, sizeof(int), 32);

    assert(arr.cap > 0);
    assert(arr2.cap == 32);
}

static void test_memgrow()
{
    struct intarr arr;

    meminit(&arr, sizeof(int), 0);

    for (int i = 0; i < 15; ++i) {
        memgrow(&arr);
        arr.buf[arr.len++] = i;
    }

    assert(arr.len == 15);
    assert(arr.cap > arr.len);
    for (int i = 0; i < arr.len; ++i) {
        assert(arr.buf[i] == i);
    }

    arr.len += 15;
    memgrow(&arr);
    assert(arr.cap > arr.len);
}

static void test_memnext()
{
    struct intarr arr;

    meminit(&arr, sizeof(int), 0);

    for (int i = 0; i < 15; ++i) {
        int *val = memnext(&arr);
        *val = i;
    }

    assert(arr.len == 15);
    assert(arr.cap > arr.len);
    for (int i = 0; i < arr.len; ++i) {
        assert(arr.buf[i] == i);
    }
}

int main(void)
{
    test_init();
    test_memgrow();
    test_memnext();

    return 0;
}
