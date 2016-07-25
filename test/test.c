#define WDB_IMPLEMENTATION
/* #define WD_DEBUG */
#include "../wdb.h"
#include <stdio.h>
#include <stdlib.h>

extern void wdb_arr_test();
extern void wdb_list_test();
extern void wdb_heap_test();

struct foo
{
    b16 r;
    i32 i;
    b8  b;
};

int main()
{
    i32 array[32];

    printf("This machine is %s.\n", (WDB_IS_BIG_EDIAN)? "Big Edian" : ((WDB_IS_LITTLE_EDIAN)? "Little Edian" : "Strange" ));
    printf("array has %ld bytes and %ld entries.\n", wdb_size_of(array), wdb_count_of(array));
    printf("offset of foo.b: %lu\n", wdb_offset_of(struct foo, b));

    if (true)
    {
        WDB_DEBUG("test here!\n");
    }
    else
    {
        WDB_PANIC("Something Strange Here!");
    }

    printf("===> wdb_arr_test:\n");
    wdb_arr_test();
    printf("===> wdb_list_test:\n");
    wdb_list_test();
    printf("===> wdb_heap_test:\n");
    wdb_heap_test();

    return 0;
}
