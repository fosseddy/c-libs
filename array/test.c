#include <stdio.h>
#include <assert.h>

#include "array.h"

void test_init()
{
    int *a = arrinit(sizeof(int), 0);
    assert(arrheader(a)->cap > 0);

    int *b = arrinit(sizeof(int), 1);
    assert(arrheader(b)->cap == 1);
}

int main(void)
{
    test_init();

    return 0;
}
