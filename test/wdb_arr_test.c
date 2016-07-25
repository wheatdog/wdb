#include "../wdb.h"
#include <stdlib.h>

wdb_internal WDB_ARR_CMP(i32_cmp)
{
    i32 i32_a = *(i32 *)a;
    i32 i32_b = *(i32 *)b;

    if (i32_a < i32_b) return -1;
    if (i32_a > i32_b) return 1;
    return 0;
}

void wdb_arr_test()
{
    wdb_arr(i32) array;
    wdb_arr_init(array);

    printf(">> init: cap: %ld count: %ld\n", wdb_arr_capacity(array), wdb_arr_count(array));
    wdb_arr_push(array, 0);
    wdb_arr_push(array, 0);
    wdb_arr_push(array, 0);
    wdb_arr_push(array, 0);
    printf(">> init: cap: %ld count: %ld\n", wdb_arr_capacity(array), wdb_arr_count(array));
    for (i32 round = 0; round < 32; ++round) {
        wdb_arr_push(array, round);
        printf(">> %d: cap: %ld count: %ld\n", round, wdb_arr_capacity(array), wdb_arr_count(array));
        isize len = wdb_arr_count(array);
        for (isize i = 0; i < len; ++i) {
            printf("%d\n", array[i]);
        }

        wdb_arr_del(array, 0);
        printf(">> %d: cap: %ld count: %ld\n", round, wdb_arr_capacity(array), wdb_arr_count(array));
        len = wdb_arr_count(array);
        for (isize i = 0; i < len; ++i) {
            printf("%d\n", array[i]);
        }
    }

    qsort(array, wdb_arr_count(array), wdb_size_of(array[0]), i32_cmp);
    i32 target = 30;
    int ret = wdb_arr_bin_search(array, &target, i32_cmp);
    printf("%d: %s\n", target, ret? "found" : "not-found");

    wdb_arr_free(array);
}
