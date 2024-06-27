#ifndef LINKED_ARENA_H
#define LINKED_ARENA_H
#include <stddef.h>

typedef struct MemoryBite MemoryBite;

typedef struct {
    size_t count;
    size_t capacity;
    MemoryBite* root;
}Arena;

void arena_set(Arena* a, size_t size);
void* arena_alloc(Arena* a, size_t bytes);
void* arena_realloc(Arena* a, void* data, size_t new_size);
void arena_free(Arena* a);

#endif // LINKED_ARENA_H

#ifdef LINKED_ARENA_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct MemoryBite {
    MemoryBite* next;
    size_t size;
    char data[];
};

static MemoryBite* memory_bite_new(size_t bytes) {
    MemoryBite* b = malloc(sizeof(b->next) + sizeof(b->size) + bytes);
    b->next = NULL;
    b->size = bytes;
    return b;
}

static void* memory_bite_alloc(MemoryBite* b, size_t bytes) {
    if (b == NULL) return NULL;
    b->next = memory_bite_new(bytes);
    return b->next->data;
}

static void* memory_bite_realloc(MemoryBite* b, void* data, size_t new_bytes) {
    if (b == NULL) return NULL;
    if (b->next == NULL) return NULL;
    if (b->next->data == data) {
        assert(new_bytes >= b->next->size);
        MemoryBite* new_bite = memory_bite_new(new_bytes);
        memcpy(new_bite->data, b->next->data, b->next->size);
        b->next = new_bite;

        return b->next->data;
    }

    return memory_bite_realloc(b->next, data, new_bytes);
}

static void memory_bite_free(MemoryBite* b) {
    if (b->next != NULL) memory_bite_free(b->next);
    free(b);
}

void arena_set(Arena* a, size_t size) {
    a->capacity = size;
}

void* arena_alloc(Arena* a, size_t bytes) {
    if (a->count + bytes >= a->capacity) return NULL;

    a->count += bytes;
    if (a->root != NULL) {
        return memory_bite_alloc(a->root, bytes);
    }

    a->root = memory_bite_new(bytes);
    return a->root->data;
}

void* arena_realloc(Arena* a, void* data, size_t new_size) {
    if (a->root == NULL) {
        a->root = memory_bite_new(new_size);
        memcpy(a->root->data, data, new_size);
        return a->root->data;
    }

    if (a->root != NULL && a->root->data == data) {
        MemoryBite* new_bite = memory_bite_new(new_size);
        memcpy(new_bite->data, a->root->data, a->root->size);
        a->root = new_bite;

        return new_bite->data;
    }

    return memory_bite_realloc(a->root, data, new_size);
}

void arena_free(Arena* a) {
    memory_bite_free(a->root);
    a->count = 0;
    a->capacity = 0;
}
#endif
