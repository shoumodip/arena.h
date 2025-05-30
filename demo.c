#include <stdio.h>

#define ARENA_IMPLEMENTATION
#include "arena.h"

int main(void) {
    Arena arena = {0};

    void *a = arena_alloc(&arena, 69);
    void *b = arena_alloc(&arena, 420);
    void *c = arena_alloc(&arena, 1337);
    void *d = arena_alloc(&arena, 80085);

    printf("a: %p\n", a);
    printf("b: %p\n", b);
    printf("c: %p\n", c);
    printf("d: %p\n", d);

    arena_free(&arena);
}
