#include <stdio.h>
#include <stdlib.h>
#include "zmalloc.h"

static size_t used_memory = 0;       // 已经使用了的内存大小

void zmalloc_enable_thread_safeness(void) {
    zmalloc_thread_safe = 1;
}


// 异常处理函数
static void zmalloc_default_oom(size_t size) {
    fprintf(stderr, "zmalloc: Out of memory trying to allocate %zu bytes\n",
            size);
    fflush(stderr);
    abort();
}

static void (*zmalloc_oom_handler)(size_t) = zmalloc_default_oom;


// 如果没有定义宏HAVE_MALLOC_SIZE则需要有这个求指针开辟地址空间内存大小的函数
#ifndef HAVE_MALLOC_SIZE
size_t zmalloc_size(void *ptr) {
    void *realptr = (char*)ptr-PREFIX_SIZE;
    size_t size = *((size_t*)realptr);
    /* Assume at least that all the allocations are padded at sizeof(long) by
     * the underlying allocator. */
    if (size&(sizeof(long)-1)) size += sizeof(long)-(size&(sizeof(long)-1));
    return size+PREFIX_SIZE;
}
#endif

// 封装malloc()，内存申请
void *zmalloc(size_t size) {
    void *ptr = malloc(size + PREFIX_SIZE);

    if (!ptr) zmalloc_oom_handler(size);   // ptr==NULL 申请内存发生异常处理
#ifndef HAVE_MALLOC_SIZE
    update_zmalloc_stat_alloc(zmalloc_size(ptr)); // 更新可用内存的值
    return ptr;
#else
    *((size_t *) ptr) = size;  // 写上内存大小size
    update_zmalloc_stat_alloc(size + PREFIX_SIZE); // 更新可用内存的值
    return (char *) ptr + PREFIX_SIZE;
#endif
}

// 封装calloc()函数，内存申请
void *zcalloc(size_t size) {
    void *ptr = calloc(1, size + PREFIX_SIZE);
    // 异常处理函数
    if (!ptr) zmalloc_oom_handler(size);
    // 内存统计函数
    *((size_t *) ptr) = size;
    update_zmalloc_stat_alloc(size + PREFIX_SIZE);
    return (char *) ptr + PREFIX_SIZE;
}

// 内存调整函数 封装系统函数recalloc()
void *zrealloc(void *ptr, size_t size) {
#ifndef HAVE_MALLOC_SIZE
    void *realptr;
#endif
    size_t oldsize;
    void *newptr;

    if (ptr == NULL) return zmalloc(size);
#ifdef HAVE_MALLOC_SIZE
    oldsize = zmalloc_size(ptr);
    newptr = realloc(ptr,size);
    if (!newptr) zmalloc_oom_handler(size);

    update_zmalloc_stat_free(oldsize);
    update_zmalloc_stat_alloc(zmalloc_size(newptr));
    return newptr;
#else
    realptr = (char*)ptr-PREFIX_SIZE;
    oldsize = *((size_t*)realptr);
    newptr = realloc(realptr,size+PREFIX_SIZE);
    if (!newptr) zmalloc_oom_handler(size);

    *((size_t*)newptr) = size;
    update_zmalloc_stat_free(oldsize);
    update_zmalloc_stat_alloc(size+PREFIX_SIZE);
    return (char*)newptr+PREFIX_SIZE;
#endif
}

// 内存释放函数，封装free()
void zfree(void *ptr) {
    if (ptr == NULL) return;  // 为空直接返回
    void *realptr = (char *) ptr - PREFIX_SIZE; // 找到该段内存真正的起始位置
    size_t oldsize = *((size_t *) realptr);
    update_zmalloc_stat_free(oldsize + PREFIX_SIZE);// 更新use_memory函数
    free(realptr); // 调用系统的内存释放函数
}


int main() {
    char *p = zmalloc(100);
    p = "cxv";
    printf("%s used_memory=%d PREFIX_SIZE=%d\n", p, used_memory, PREFIX_SIZE);

    char *q = zcalloc(100);
    q = "sss";
    printf("%s used_memory=%d PREFIX_SIZE=%d\n", q, used_memory, PREFIX_SIZE);
    char *t = zrealloc(q, 120);
    printf("%s used_memory=%d PREFIX_SIZE=%d\n", t, used_memory, PREFIX_SIZE);
    return 0;
}