#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>

static void* (*real_malloc)(size_t)=NULL;
static void* (*real_free)(void*)=NULL;

void *malloc(size_t size)
{
    if(real_malloc==NULL) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
        if (NULL == real_malloc) {
        }
    }
    void *p = NULL;
    fprintf(stderr,"malloc\n");
    p = real_malloc(size);
    return p;
}

void free(void *ptr)
{
    if(real_free==NULL) {
        real_free = dlsym(RTLD_NEXT, "free");
        if (NULL == real_free) {
        }
    }
    fprintf(stderr,"free\n");
    real_free(ptr);
}