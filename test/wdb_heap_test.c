#include "../wdb.h"

typedef struct {
    i32 i;
    i32 c;
} foo;

wdb_internal WDB_ARR_CMP(i32_cmp)
{
    i32 i32_a = *(i32 *)a;
    i32 i32_b = *(i32 *)b;

    if (i32_a < i32_b) return -1;
    if (i32_a > i32_b) return 1;
    return 0;
}

wdb_internal WDB_ARR_CMP(foo_cmp)
{
    foo *foo_a = (foo *)a;
    foo *foo_b = (foo *)b;

    i32 m_a = foo_a->i*foo_a->c;
    i32 m_b = foo_b->i*foo_b->c;

    if (m_a < m_b) return -1;
    if (m_a > m_b) return 1;
    if (foo_a->i < foo_b->i) return -1;
    if (foo_a->i > foo_b->i) return 1;
    if (foo_a->c < foo_b->c) return -1;
    if (foo_a->c > foo_b->c) return 1;
    return 0;
}

void wdb_heap_foo_test()
{
    wdb_heap(foo) heap;
    foo input[8] = {
        {.i = 0, .c = 7},
        {.i = 1, .c = 6},
        {.i = 2, .c = 5},
        {.i = 3, .c = 4},
        {.i = 4, .c = 3},
        {.i = 5, .c = 2},
        {.i = 6, .c = 1},
        {.i = 7, .c = 0},
    };
    foo *tmp;
    wdb_heap_init(heap, foo_cmp);

    for (isize i = 0; i < 8; ++i) {
        wdb_heap_push(heap, input[i]);
    }


    for (isize i = 0; i < wdb_arr_count(heap); ++i) {
        printf("%ld: %d, %d\n", i, heap[i].i, heap[i].c);
    }

    isize l = wdb_arr_count(heap);
    for (isize i = 0; i < l; ++i) {
        tmp = &(wdb_heap_peak(heap));
        printf("==top is %d, %d, %d\n", tmp->i, tmp->c, tmp->i*tmp->c);
        wdb_heap_del_top(heap);
        for (isize i = 0; i < wdb_arr_count(heap); ++i) {
            printf("%ld: %d, %d\n", i, heap[i].i, heap[i].c);
        }
    }

    wdb_heap_free(heap);
}

void wdb_heap_i32_test()
{
    wdb_heap(i32) heap;
    wdb_heap_init(heap, i32_cmp);

    wdb_heap_push(heap, 3);
    wdb_heap_push(heap, 1);
    wdb_heap_push(heap, 2);
    wdb_heap_push(heap, 13);
    wdb_heap_push(heap, 7);
    wdb_heap_push(heap, 4);
    wdb_heap_push(heap, 5);
    wdb_heap_push(heap, 6);

    for (isize i = 0; i < wdb_arr_count(heap); ++i) {
        printf("%ld: %d\n", i, heap[i]);
    }

    isize l = wdb_arr_count(heap);
    for (isize i = 0; i < l; ++i) {
        printf("==top is %d\n", wdb_heap_peak(heap));
        wdb_heap_del_top(heap);
        for (isize i = 0; i < wdb_arr_count(heap); ++i) {
            printf("%ld: %d\n", i, heap[i]);
        }
    }

    wdb_heap_free(heap);
}

void wdb_heap_test()
{
    wdb_heap_i32_test();
    wdb_heap_foo_test();
}
