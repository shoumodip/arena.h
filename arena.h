#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

#ifndef ARENA_MINIMUM_CAPACITY
#    define ARENA_MINIMUM_CAPACITY 16000
#endif // ARENA_MINIMUM_CAPACITY

typedef struct ArenaRegion ArenaRegion;

typedef struct {
    ArenaRegion *head;
} Arena;

void  arena_free(Arena *a);
void *arena_alloc(Arena *a, size_t size);

#endif // ARENA_H

#ifdef ARENA_IMPLEMENTATION

#include <stdlib.h>

struct ArenaRegion {
    ArenaRegion *next;
    size_t       count;
    size_t       capacity;
    char         data[];
};

void arena_free(Arena *a) {
    ArenaRegion *it = a->head;
    while (it) {
        ArenaRegion *next = it->next;
        free(it);
        it = next;
    }
}

void *arena_alloc(Arena *a, size_t size) {
    ArenaRegion *region = NULL;
    for (ArenaRegion *it = a->head; it; it = it->next) {
        if (it->count + size <= it->capacity) {
            region = it;
            break;
        }
    }

    if (!region) {
        size_t capacity = size;
        if (capacity < ARENA_MINIMUM_CAPACITY) {
            capacity = ARENA_MINIMUM_CAPACITY;
        }

        region = malloc(sizeof(ArenaRegion) + capacity);
        region->next = a->head;
        region->count = 0;
        region->capacity = capacity;
        a->head = region;
    }

    void *ptr = &region->data[region->count];
    region->count += size;
    return ptr;
}

#endif // ARENA_IMPLEMENTATION
