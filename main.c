#define LINKED_ARENA_IMPLEMENTATION
#include "linked_arena.h"

Arena arena = {0};

int main(void) {
    arena_set(&arena, 1024);

    arena_free(&arena);

    return 0;
}
