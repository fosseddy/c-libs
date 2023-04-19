typedef struct {
    int len;
    int cap;
    int data_size;
    void *buf;
} mem_t;

void meminit(mem_t *m, int data_size, int cap);
void memfree(mem_t *m);

void memgrow(mem_t *m);

void *memnext(mem_t *m);
