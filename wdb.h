/* wdb.h - v0.04 - WheatDog's Box, A Personal C Helper Library - public domain
                 - no warranty implied; use at your own risk

         This is a single header file with a bunch of useful stuff.

===========================================================================
    YOU MUST

        #define WDB_IMPLEMENTATION

    in EXACTLY _one_ C or C++ file that includes this header, BEFORE the
    include like this:

        #define WDB_IMPLEMENTATION
        #include "wdb.h"

    All other files should just #include "wdb.h" without #define

===========================================================================

LICENSE
    This software is dual-licensed to the public domain and under the following
    license: you are granted a perpetual, irrevocable license to copy, modify,
    publish, and distribute this file as you see fit.

WARNING
    - This library is _slightly_ experimental and features may not work as expected.
    - This also means that many functions are not documented.

CREDITS
    Written by Tim Liou

TODOS
    - Does I want wdb_arr dynamic shrink? or wdb_arr_set_capacity is good enough?

VERSION HISTORY
    - 0.04  - wdb_list
    - 0.03  - wdb_arr
    - 0.02  - Preset and Base Types
    - 0.01  - Initial Version

*/

#if !defined(WDB_INCLUDE)
#define WDB_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif
#if 0
}
#endif

//////////////////////////////////////////////////////////////////////////////
//
// Preset
//
//

#if defined(_WIN64) || defined(__x86_64__) || defined(_M_X64) || defined(__64BIT__) || defined(__powerpc64__) || defined(__ppc64__)
#ifndef WDB_ARCH_64_BIT
#define WDB_ARCH_64_BIT 1
#endif
#else
#ifndef WDB_ARCH_32_BIT
#define WDB_ARCH_32_BIT 1
#endif
#endif

#if defined(_MSC_VER)
#define WDB_COMPILER_MSVC 1
#elif defined(__GNUC__)
#define WDB_COMPILER_GCC 1
#elif defined(__clang__)
#define WDB_COMPILER_CLANG 1
#else
#error Unknown compiler
#endif

#if !defined(WDB_EDIAN_ORDER)
#define WDB_EDIAN_ORDER
#define WDB_IS_BIG_EDIAN    (!*(u8*)&(u16){1})
#define WDB_IS_LITTLE_EDIAN (!WDB_IS_BIG_EDIAN)
#endif

#if defined(__cplusplus)
#define WDB_EXTERN extern "C"
#else
#define WDB_EXTERN extern
#endif

#if defined(WDB_STATIC)
#define WDB_DEF static
#else
#define WDB_DEF extern
#endif

// Compile time static assertion
#ifndef WDB_STATIC_ASSERT
#define WDB_STATIC_ASSERT3(cond, msg) typedef char static_assertion_##msg[(!!(cond))*2-1]
#define WDB_STATIC_ASSERT2(cond, line) WDB_STATIC_ASSERT3(cond, static_assertion_at_line_##line)
#define WDB_STATIC_ASSERT1(cond, line) WDB_STATIC_ASSERT2(cond, line)
#define WDB_STATIC_ASSERT(cond)        WDB_STATIC_ASSERT1(cond, __LINE__)
#endif

#include <stddef.h> /* size_t, ptrdiff_t, sizeof() */
#include <stdarg.h> /* va_list */
#include <stdio.h>  /* vfprintf */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy, memmove */

//////////////////////////////////////////////////////////////////////////////
//
// Base Types
//
//

#if defined(WDB_COMPILER_MSVC)
#if _MSC_VER < 1300
typedef unsigned char     u8;
typedef   signed char     i8;
typedef unsigned short   u16;
typedef   signed short   i16;
typedef unsigned int     u32;
typedef   signed int     i32;
#else
typedef unsigned __int8   u8;
typedef   signed __int8   i8;
typedef unsigned __int16 u16;
typedef   signed __int16 i16;
typedef unsigned __int32 u32;
typedef   signed __int32 i32;
#endif
typedef unsigned __int64 u64;
typedef   signed __int64 i64;
#else
#include <stdint.h>
typedef uint8_t   u8;
typedef  int8_t   i8;
typedef uint16_t u16;
typedef  int16_t i16;
typedef uint32_t u32;
typedef  int32_t i32;
typedef uint64_t u64;
typedef  int64_t i64;
#endif

WDB_STATIC_ASSERT(sizeof(u8)  == sizeof(i8));
WDB_STATIC_ASSERT(sizeof(u16) == sizeof(i16));
WDB_STATIC_ASSERT(sizeof(u32) == sizeof(i32));
WDB_STATIC_ASSERT(sizeof(u64) == sizeof(i64));

WDB_STATIC_ASSERT(sizeof(u8)  == 1);
WDB_STATIC_ASSERT(sizeof(u16) == 2);
WDB_STATIC_ASSERT(sizeof(u32) == 4);
WDB_STATIC_ASSERT(sizeof(u64) == 8);

typedef size_t    usize;
typedef ptrdiff_t isize;

WDB_STATIC_ASSERT(sizeof(usize) == sizeof(isize));

typedef float  r32;
typedef double r64;

WDB_STATIC_ASSERT(sizeof(r32) == 4);
WDB_STATIC_ASSERT(sizeof(r64) == 8);

typedef i8  b8;
typedef i16 b16;
typedef i32 b32;

#if !defined(__cplusplus)
#if (defined(_MSC_VER) && _MSC_VER <= 1800) || !defined(__STDC_VERSION__)
#ifndef true
#define true  (0 == 0)
#endif
#ifndef false
#define false (0 != 0)
#endif
#else
#include <stdbool.h>
#endif
#endif

#ifndef U8_MIN
#define U8_MIN 0u
#define U8_MAX 0xffu
#define I8_MIN (-0x7f - 1)
#define I8_MAX 0x7f

#define U16_MIN 0u
#define U16_MAX 0xffffu
#define I16_MIN (-0x7fff - 1)
#define I16_MAX 0x7fff

#define U32_MIN 0u
#define U32_MAX 0xffffffffu
#define I32_MIN (-0x7fffffff - 1)
#define I32_MAX 0x7fffffff

#define U64_MIN 0ull
#define U64_MAX 0xffffffffffffffffull
#define I64_MIN (-0x7fffffffffffffffll - 1)
#define I64_MAX 0x7fffffffffffffffll

#if defined(WDB_ARCH_32_BIT)
#define USIZE_MIX U32_MIN
#define USIZE_MAX U32_MAX
#define ISIZE_MIX S32_MIN
#define ISIZE_MAX S32_MAX
#elif defined(WDB_ARCH_64_BIT)
#define USIZE_MIX U64_MIN
#define USIZE_MAX U64_MAX

#define ISIZE_MIX I64_MIN
#define ISIZE_MAX I64_MAX
#else
#error Unknown architecture size. This library only supports 32 bit and 64 bit architectures.
#endif

#define R32_MIN 1.17549435e-38f
#define R32_MAX 3.40282347e+38f

#define R64_MIN 2.2250738585072014e-308
#define R64_MAX 1.7976931348623157e+308

#endif

#ifndef NULL
#if defined(__cplusplus)
#if __cplusplus >= 201103L
#define NULL nullptr
#else
#define NULL 0
#endif
#else
#define NULL ((void *)0)
#endif
#endif

//////////////////////////////////////////////////////////////////////////////
//
// Useful Macros
//
//

#ifndef wdb_size_of
#define wdb_size_of(x) (isize)(sizeof(x))
#endif

// Only for static arrays like
// int a[32];
#ifndef wdb_count_of
#define wdb_count_of(x) ((wdb_size_of(x)/wdb_size_of(0[x])) / ((isize)(!(wdb_size_of(x) % wdb_size_of(0[x])))))
#endif

#ifndef wdb_offset_of
#define wdb_offset_of(type, element) ((isize)&(((type *)0)->element))
#endif

#ifndef WDB_BIT_AT
#define WDB_BIT_AT(x) (1<<(x))
#endif

#ifndef wdb_swap
#define wdb_swap(type, a, b) do { type tmp = (a); (a) = (b); (b) = tmp; } while (0)
#endif

#ifndef wdb_min
#define wdb_min(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef wdb_max
#define wdb_max(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef wdb_clamp
#define wdb_clamp(x, lower, upper) wdb_min(wdb_max((x), (lower)), (upper))
#endif

#ifndef wdb_clamp01
#define wdb_clamp01(x) wdb_clamp((x), 0, 1)
#endif

#ifndef wdb_global
#define wdb_global        static // Global variables
#define wdb_internal      static // Internal linkage
#define wdb_local_persist static // Local Persisting variables
#endif

//////////////////////////////////////////////////////////////////////////////
//
// Debug
//
//

#ifndef WDB_DEBUG_TRAP
#if defined(_MSC_VER)
#if _MSC_VER < 1300
#define WDB_DEBUG_TRAP() __asm int 3 /* Trap to debugger! */
#else
#define WDB_DEBUG_TRAP() __debugbreak()
#endif
#else
#define WDB_DEBUG_TRAP() __builtin_trap()
#endif
#endif

#if defined(WD_DEBUG)
#define WDB_DEBUG(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define WDB_DEBUG(fmt, ...)
#endif

#ifndef WDB_ASSERT_MSG
#define WDB_ASSERT_MSG(cond, msg, ...) do {                             \
        if (!(cond)) {                                                  \
            wdb_assert_handler(#cond, __FILE__, (i64)__LINE__, msg, ##__VA_ARGS__); \
            WDB_DEBUG_TRAP();                                           \
        }                                                               \
    } while (0)
#endif

#ifndef WDB_ASSERT
#define WDB_ASSERT(cond) WDB_ASSERT_MSG(cond, NULL)
#endif

#ifndef WDB_PANIC
#define WDB_PANIC(msg, ...) WDB_ASSERT_MSG(0, msg, ##__VA_ARGS__)
#endif

WDB_DEF void  wdb_assert_handler(char const *condition, char const *file, i32 line, char const *msg, ...);
WDB_DEF isize wdb_printf_err    (char const *fmt, ...);
WDB_DEF isize wdb_printf_err_va (char const *fmt, va_list va);

//////////////////////////////////////////////////////////////////////////////
//
// Dynamic Array
//
//

typedef struct
{
    isize count;
    isize capacity;
} wdb__arr_header;

#define wdb_arr(type) type *

#ifndef WDB_ARR_GROW_FORMULA
#define WDB_ARR_GROW_FORMULA(x) (2*(x))
#endif

WDB_STATIC_ASSERT(WDB_ARR_GROW_FORMULA(0) >= 0);

#define WDB_ARR_HEADER(x)   ((wdb__arr_header *)(x) - 1)
#define wdb_arr_count(x)    (WDB_ARR_HEADER(x)->count)
#define wdb_arr_capacity(x) (WDB_ARR_HEADER(x)->capacity)

#define wdb_arr_init_reserve(x, cap) do {                               \
        void **wdb__arr_ = (void **)&(x);                               \
        wdb__arr_header *wdb__ah_ = (wdb__arr_header *)malloc(wdb_size_of(wdb__arr_header) + wdb_size_of(*(x))*(cap)); \
        wdb__ah_->count = 0;                                            \
        wdb__ah_->capacity = cap;                                       \
        *wdb__arr_ = (void *)(wdb__ah_ + 1);                            \
    } while(0)

#define wdb_arr_init(x) wdb_arr_init_reserve(x, WDB_ARR_GROW_FORMULA(0))

#define wdb_arr_free(x) do {                            \
        wdb__arr_header *wdb__ah_ = WDB_ARR_HEADER(x);  \
        free(wdb__ah_);                                 \
    } while(0)

#define wdb_arr_set_capacity(x, capacity) do {                          \
        if (x) {                                                        \
            void **wdb_arr_ = (void **)&(x);                            \
            *wdb_arr_ = wdb__arr_set_capacity((x), (capacity), wdb_size_of(*(x))); \
        }                                                               \
    } while(0)
WDB_DEF void *wdb__arr_set_capacity(void *array, isize capacity, isize element_size);

#define wdb_arr_grow(x, min_capacity) do {                              \
        isize new__capacity_ = WDB_ARR_GROW_FORMULA(wdb_arr_capacity(x)); \
        if (new__capacity_ < (min_capacity)) {                          \
            new__capacity_ = (min_capacity);                            \
        }                                                               \
        wdb_arr_set_capacity(x, new__capacity_);                        \
    } while(0)

#define wdb_arr_push(x, item) do {                            \
        if (wdb_arr_capacity(x) < wdb_arr_count(x)+1) {       \
            wdb_arr_grow(x, wdb_arr_count(x)+1);              \
        }                                                     \
        WDB_ASSERT(wdb_size_of(item) == wdb_size_of((x)[0])); \
        (x)[wdb_arr_count(x)++] = (item);                     \
    } while(0)

#define wdb_arr_pushv(x, items, item_count) do {                        \
        wdb__arr_header *wdb__ah_ = WDB_ARR_HEADER(x);                  \
        WDB_ASSERT(wdb_size_of((items)[0]) == wdb_size_of((x)[0]));     \
        if (wdb__ah_->capacity < (wdb__ah_->count+(item_count))) {      \
            wdb_arr_grow(x, wdb__ah_->count+(item_count));              \
        }                                                               \
        memcpy(&(x)[wdb__ah_->count], (items), wdb_size_of((x)[0])*(item_count)); \
        wdb__ah_->count += (item_count);                                \
    } while(0)

#define wdb__arr_delv(x, i, n, element_size) do {                       \
        memmove((u8 *)(x) + (element_size)*(i), (u8 *)(x) + (element_size)*((i)+(n)), (element_size)*(wdb_arr_count(x)-((i)+(n)))); \
        wdb_arr_count(x) -= (n);                                        \
    } while(0)

#define wdb_arr_delv(x, i, n) do {                                      \
        if (n) {                                                        \
            WDB_ASSERT(((i) >= 0) && ((i)+n-1) < wdb_arr_count(x));     \
            wdb__arr_delv(x, i, n, wdb_size_of((x)[0]));                \
        }                                                               \
    } while(0)

#define wdb_arr_del(x, i) wdb_arr_delv(x, i, 1)

#define wdb_arr_empty(x) (wdb_arr_count(x) == 0)
#define wdb_arr_clear(x) (wdb_arr_count(x) = 0)
#define wdb_arr_last(x)  ((x)[wdb_arr_count(x)-1])
#define wdb_arr_pop(x)   ((x)[--wdb_arr_count(x)])

#define wdb_arr_resize(x, new_count) do {         \
        if (wdb_arr_capacity(x) < (new_count)) {  \
            wdb_arr_grow(x, (new_count));         \
        }                                         \
        wdb_arr_count(x) = (new_count);           \
    } while(0)

#define wdb_arr_reserve(x, new_capacity) do {       \
        if (wdb_arr_capacity(x) < (new_capacity)) { \
            wdb_arr_set_capacity(x, new_capacity);  \
        }                                           \
    } while(0)


#define wdb_arr_bin_search(ptr, target, cmp) wdb_arr__bin_search((ptr), wdb_arr_count(ptr), wdb_size_of((ptr)[0]), (target), (cmp))
WDB_DEF b32 wdb_arr__bin_search(void *ptr, isize count , isize element_size, const void *target, int (*cmp)(const void *, const void *));

//////////////////////////////////////////////////////////////////////////////
//
// Circular Double Linked List (linux-kernel-like)
//
//

struct wdb_list__ele
{
    struct wdb_list__ele *prev;
    struct wdb_list__ele *next;
};
typedef struct wdb_list__ele wdb_list_ele;

WDB_DEF void wdb_list_init(wdb_list_ele *head);
WDB_DEF void wdb_list__add(wdb_list_ele *new_ele, wdb_list_ele *prev, wdb_list_ele *next);
WDB_DEF void wdb_list_append(wdb_list_ele *new_ele, wdb_list_ele *head);
WDB_DEF void wdb_list_prepend(wdb_list_ele *new_ele, wdb_list_ele *head);

WDB_DEF void wdb_list__del_internal(wdb_list_ele *prev, wdb_list_ele *next);
WDB_DEF void wdb_list__del_entry(wdb_list_ele *entry);
WDB_DEF void wdb_list_del(wdb_list_ele *entry);
WDB_DEF void wdb_list_del_init(wdb_list_ele *entry);

WDB_DEF void wdb_list_move_append(wdb_list_ele *entry, wdb_list_ele *list);
WDB_DEF void wdb_list_move_prepend(wdb_list_ele *entry, wdb_list_ele *list);

WDB_DEF void wdb_list_replace(wdb_list_ele *old, wdb_list_ele *new_ele);
WDB_DEF void wdb_list_replace_init(wdb_list_ele *old, wdb_list_ele *new_ele);

WDB_DEF void wdb_list_rotate_left(wdb_list_ele *entry);

WDB_DEF void wdb_list__cut_position(wdb_list_ele *list, wdb_list_ele *head, wdb_list_ele *entry);
WDB_DEF void wdb_list_cut_position(wdb_list_ele *list, wdb_list_ele *head, wdb_list_ele *entry);

WDB_DEF void wdb_list__splice(const wdb_list_ele *list, wdb_list_ele *prev, wdb_list_ele *next);
WDB_DEF void wdb_list_splice(wdb_list_ele *list, wdb_list_ele *head);
WDB_DEF void wdb_list_splice_tail(wdb_list_ele *list, wdb_list_ele *head);
WDB_DEF void wdb_list_splice_init(wdb_list_ele *list, wdb_list_ele *head);
WDB_DEF void wdb_list_splice_tail_init(wdb_list_ele *list, wdb_list_ele *head);

WDB_DEF b32 wdb_list_is_last(const wdb_list_ele *ele, const wdb_list_ele *head);
WDB_DEF b32 wdb_list_is_empty(const wdb_list_ele *list);

#define wdb_list_entry(list_elem, type, member) ((type *) ((u8 *)(list_elem) - wdb_offset_of(type, member)))

#if 0
#define wdb_list_last_entry(list_elem, type, member) (wdb_list_is_empty(list_elem) ? NULL : wdb_list_entry((list_elem)->prev, type, member))
#define wdb_list_first_entry(list_elem, type, member) (wdb_list_is_empty(list_elem) ? NULL : wdb_list_entry((list_elem)->next, type, member))
#define wdb_list_next_entry(type_ptr, type, member) wdb_list_entry((type_ptr)->member.next, type, member)
#define wdb_list_prev_entry(type_ptr, type, member) wdb_list_entry((type_ptr)->member.prev, type, member)
#endif

#define wdb_list_for_each(cur, head) for (cur = (head)->next; cur != (head); cur = cur->next)
#define wdb_list_for_each_safe(cur, tmp, head) for (cur = (head)->next, tmp = cur->next; cur != (head); cur = tmp, tmp = cur->next)
#define wdb_list_for_each_rev(cur, head) for (cur = (head)->prev; cur != (head); cur = cur->prev)
#define wdb_list_for_each_rev_safe(cur, tmp, head) for (cur = (head)->prev, tmp = cur->prev; cur != (head); cur = tmp, tmp = cur->prev)

#if 0
{
#endif
#if defined(__cplusplus)
}
#endif

//
//
////   end header file   /////////////////////////////////////////////////////
#endif // WDB_INCLUDE


#ifdef WDB_IMPLEMENTATION

//////////////////////////////////////////////////////////////////////////////
//
// Debug
//
//

void wdb_assert_handler(char const *condition, char const *file, i32 line, char const *msg, ...)
{
    wdb_printf_err("%s:%d: Assert Failure: ", file, line);
    if (condition)
        wdb_printf_err("`%s` ", condition);
    if (msg) {
        va_list va;
        va_start(va, msg);
        wdb_printf_err_va(msg, va);
        va_end(va);
    }
    wdb_printf_err("\n");
}

isize wdb_printf_err(char const *fmt, ...)
{
    isize res;
    va_list va;
    va_start(va, fmt);
    res = wdb_printf_err_va(fmt, va);
    va_end(va);
    return res;
}

isize wdb_printf_err_va(char const *fmt, va_list va)
{
    isize res;
    res = vfprintf(stderr, fmt, va);
    return res;
}

//////////////////////////////////////////////////////////////////////////////
//
// Dynamic Array
//
//

void *wdb__arr_set_capacity(void *array, isize capacity, isize element_size)
{
    wdb__arr_header *header = WDB_ARR_HEADER(array);
    wdb__arr_header *new_header = NULL;

    WDB_ASSERT(element_size > 0);

    if (capacity == header->capacity) return array;

    if (capacity < header->count) header->count = capacity;

    new_header = (wdb__arr_header *)realloc(header, wdb_size_of(wdb__arr_header) + element_size*capacity);
    WDB_ASSERT(new_header != NULL);
    new_header->capacity = capacity;

    return new_header+1;
}

b32 wdb_arr__bin_search(void *ptr, isize count , isize element_size, const void *target, int (*cmp)(const void *, const void *))
{
    isize mid, left = 0, right = count;
    u8 *u8ptr = (u8 *)ptr;
    int ret;

    while (right != left) {
        mid = (left + right)/2;
        ret = cmp(u8ptr + element_size*mid, target);
        if (ret == 0) return true;
        if (ret > 0)
            right = mid;
        else
            left = mid+1;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////
//
// Circular Double Linked List (linux-kernel-like)
//
//

inline void wdb_list_init(wdb_list_ele *head)
{
    head->next = head;
    head->prev = head;
}

inline void wdb_list__add(wdb_list_ele *new_ele, wdb_list_ele *prev, wdb_list_ele *next)
{
    prev->next = new_ele;
    new_ele->prev = prev;
    new_ele->next = next;
    next->prev = new_ele;
}

inline void wdb_list_append(wdb_list_ele *new_ele, wdb_list_ele *head)
{
    wdb_list__add(new_ele, head, head->next);
}

inline void wdb_list_prepend(wdb_list_ele *new_ele, wdb_list_ele *head)
{
    wdb_list__add(new_ele, head->prev, head);
}

inline void wdb_list__del_internal(wdb_list_ele *prev, wdb_list_ele *next)
{
    next->prev = prev;
    prev->next = next;
}

inline void wdb_list__del_entry(wdb_list_ele *entry)
{
    wdb_list__del_internal(entry->prev, entry->next);
}

inline void wdb_list_del(wdb_list_ele *entry)
{
    wdb_list__del_entry(entry);
    entry->prev = NULL;
    entry->next = NULL;
}

inline void wdb_list_del_init(wdb_list_ele *entry)
{
    wdb_list__del_entry(entry);
    wdb_list_init(entry);
}

inline void wdb_list_move_append(wdb_list_ele *entry, wdb_list_ele *list)
{
    wdb_list__del_entry(entry);
    wdb_list_append(entry, list);
}

inline void wdb_list_move_prepend(wdb_list_ele *entry, wdb_list_ele *list)
{
    wdb_list__del_entry(entry);
    wdb_list_prepend(entry, list);
}

inline void wdb_list_replace(wdb_list_ele *old, wdb_list_ele *new_ele)
{
    new_ele->next = old->next;
    new_ele->prev = old->prev;
    old->next->prev = new_ele;
    old->prev->next = new_ele;
}

inline void wdb_list_replace_init(wdb_list_ele *old, wdb_list_ele *new_ele)
{
    wdb_list_replace(old, new_ele);
    wdb_list_init(old);
}

inline void wdb_list_rotate_left(wdb_list_ele *entry)
{
    if (!wdb_list_is_empty(entry)) {
        wdb_list_move_prepend(entry->next, entry);
    }
}

inline void wdb_list__cut_position(wdb_list_ele *list, wdb_list_ele *head, wdb_list_ele *entry)
{
    wdb_list_ele *new_first = entry->next;
    list->next = head->next;
    list->next->prev = list;
    list->prev = entry;
    entry->next = list;
    head->next = new_first;
    new_first->prev = head;
}

inline void wdb_list_cut_position(wdb_list_ele *list, wdb_list_ele *head, wdb_list_ele *entry)
{
    if (wdb_list_is_empty(head)) return;

    if (entry == head) wdb_list_init(list);
    else wdb_list__cut_position(list, head, entry);
}

inline void wdb_list__splice(const wdb_list_ele *list, wdb_list_ele *prev, wdb_list_ele *next)
{
    wdb_list_ele *first = list->next;
    wdb_list_ele *last = list->prev;

    first->prev = prev;
    prev->next = first;

    last->next = next;
    next->prev = last;
}

inline void wdb_list_splice(wdb_list_ele *list, wdb_list_ele *head)
{
    if (!wdb_list_is_empty(list)) {
        wdb_list__splice(list, head, head->next);
    }
}

inline void wdb_list_splice_tail(wdb_list_ele *list, wdb_list_ele *head)
{
    if (!wdb_list_is_empty(list)) {
        wdb_list__splice(list, head->prev, head);
    }
}

inline void wdb_list_splice_init(wdb_list_ele *list, wdb_list_ele *head)
{
    if (!wdb_list_is_empty(list)) {
        wdb_list__splice(list, head, head->next);
        wdb_list_init(list);
    }
}

inline void wdb_list_splice_tail_init(wdb_list_ele *list, wdb_list_ele *head)
{
    if (!wdb_list_is_empty(list)) {
        wdb_list__splice(list, head->prev, head);
        wdb_list_init(list);
    }
}

inline b32 wdb_list_is_last(const wdb_list_ele *ele, const wdb_list_ele *head)
{
    return (ele->next == head);
}

inline b32 wdb_list_is_empty(const wdb_list_ele *list)
{
    return (list->next == list);
}

#endif // WDB_IMPLEMENTATION
