#include "../wdb.h"

struct i32_list
{
    i32 e;
    wdb_list_ele list;
};

void wdb_list_test()
{
    wdb_list_ele *cur, *tmp;
    wdb_list_ele head, newhead;
    wdb_list_init(&newhead);
    wdb_list_init(&head);

    for (i32 i = 0; i < 30; ++i) {
        struct i32_list *tmp = (struct i32_list *)malloc(wdb_size_of(struct i32_list));
        tmp->e = i;
        wdb_list_append(&tmp->list, &head);
    }

    wdb_list_for_each(cur, &head) {
        struct i32_list *entry = wdb_list_entry(cur, struct i32_list, list);
        printf("e = %d\n", entry->e);
    }

    wdb_list_for_each(cur, &head) {
        struct i32_list *entry = wdb_list_entry(cur, struct i32_list, list);
        if (entry->e == 15) {
            wdb_list_del(&entry->list);
            free(entry);
            break;
        }
    }

    wdb_list_for_each(cur, &head) {
        struct i32_list *entry = wdb_list_entry(cur, struct i32_list, list);
        printf("e = %d\n", entry->e);
    }

    printf("Cut when e = 10\n");

    wdb_list_for_each(cur, &head) {
        struct i32_list *entry = wdb_list_entry(cur, struct i32_list, list);
        if (entry->e == 10) {
            wdb_list_cut_position(&newhead, &head, cur);
            break;
        }
    }

    printf("New Part:\n");
    wdb_list_for_each(cur, &head) {
        struct i32_list *entry = wdb_list_entry(cur, struct i32_list, list);
        printf("e = %d\n", entry->e);
    }

    printf("Remain Part:\n");
    wdb_list_for_each(cur, &newhead) {
        struct i32_list *entry = wdb_list_entry(cur, struct i32_list, list);
        printf("e = %d\n", entry->e);
    }

    printf("Splice these two part\n");
    wdb_list_splice_tail_init(&newhead, &head);

    wdb_list_for_each(cur, &head) {
        struct i32_list *entry = wdb_list_entry(cur, struct i32_list, list);
        printf("e = %d\n", entry->e);
    }

    wdb_list_for_each(cur, &newhead) {
        struct i32_list *entry = wdb_list_entry(cur, struct i32_list, list);
        printf("e = %d\n", entry->e);
    }

    wdb_list_for_each_safe(cur, tmp, &head) {
        struct i32_list *entry = wdb_list_entry(cur, struct i32_list, list);
        free(entry);
    }

    printf("%s\n", wdb_list_is_empty(&head)? "empty" : "non-empty");
}
