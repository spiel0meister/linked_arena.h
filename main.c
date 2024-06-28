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

    Nums ns = {0};
    for (int i = 0; i < 100; ++i) nums_append(&ns, i);

    for (int i = 0; (size_t)i < ns.count; ++i) {
        printf("%d\n", ns.items[i]);
    }

    arena_free(&arena);
    return 0;
}
