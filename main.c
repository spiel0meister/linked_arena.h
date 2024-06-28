#define LINKED_ARENA_IMPLEMENTATION
#include "linked_arena.h"

typedef struct {
    int* items;
    size_t count;
    size_t capacity;
}Nums;

static Arena arena = {0};

void nums_append(Nums* n, int i) {
    if (n->count >= n->capacity) {
        if (n->capacity == 0) n->capacity = 1;
        while (n->count >= n->capacity) {
            n->capacity *= 2;
        }
        n->items = arena_realloc(&arena, n->items, n->capacity * sizeof(int));
    }
    n->items[n->count++] = i;
}

int main(void) {
    arena_set(&arena, 1024);

    Nums ns1 = {0};
    for (int i = 0; i < 100; ++i) nums_append(&ns1, rand() % 10);

    Nums ns2 = {0};
    for (int i = 0; i < 100; ++i) nums_append(&ns2, rand() % 10);

    print_arena(&arena);

    arena_free(&arena);
    return 0;
}
