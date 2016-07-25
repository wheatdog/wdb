#define WDB_IMPLEMENTATION
#include "../wdb.h"
#include <vector>
#include <sys/time.h>

double get_current_time()
{
    struct timeval t;
    gettimeofday(&t, 0);

    return t.tv_sec + t.tv_usec*1e-6;
}

int main()
{
    double begin, end, interval;
    std::vector<i32> vec;

    const i32 max = 2048;

    for (i32 j = 1; j < 64; ++j)
    {
        wdb_arr(i32) arr;

        wdb_arr_init(arr);

        i32 limit = j*max;
        begin = get_current_time();
        for (i32 i = 0; i < limit; ++i) {
            wdb_arr_push(arr, i);
        }
        end = get_current_time();
        interval = end - begin;

        wdb_arr_free(arr);
        printf("%d: %.4fs\n", j, interval);
    }

    begin = get_current_time();
    for (i32 i = 0; i < max; ++i) {
        vec.push_back(i);
    }
    end = get_current_time();
    interval = end - begin;

    printf("%.4fs\n", interval);

    return 0;
}
