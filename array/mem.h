struct memheader {
    int len;
    int cap;
    int data_size;
};

void *meminit(int data_size, int cap);
void memfree(void *mem);

void *memgrow(void *mem);
void *memmaybe_grow(void *mem);

struct memheader *memheader(void *mem);

int memlen(void *mem);
int memcap(void *mem);

void *memnext(void *mem);
#define memnext_m(a) ((a) = memmaybe_grow((a)), memnext((a)))
#define mempush_m(a, b) ((a) = memmaybe_grow((a)), (a)[memheader((a))->len++] = (b))
