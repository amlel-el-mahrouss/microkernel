/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <stddef.h>
#include <string.h>

size_t strncmp(const char* src, const char* cmp, size_t size)
{
    if (src == null) return 0;

    int32_t counter = 0;

    for (size_t index = 0; index < size; ++index)
    {
        if (src[index] != cmp[index])
            ++counter;
    }

    return counter;
}

void* memset(void* ptr, const char value, size_t len)
{
    if (ptr == null) return null;

    char* start = ptr;

    while (len)
    {
        *start = value;
        ++start;

        --len;
    }

    return (void*)start;
}

void* memmove(void* dest, const void* src, size_t len)
{
    memncpy(dest, src, len);
    return dest;
}

size_t memcpy(void* dst, const void* src)
{
    if (src == null || dst == null) return 0;

    const char* src_chr = src;
    char* dst_chr = dst;
    size_t index = 0;
    size_t len = strlen(src);

    while (index < len)
    {
        dst_chr[index] = src_chr[index];
        ++index;
    }

    return 0;
}

/* @brief unoptimized memcpy, TODO: use isa specific memcpy. */
size_t memncpy(void* dst, const void* src, size_t len)
{
#if __OL == 3 && defined(__riscv)
    riscv_memncpy(dst, src, len);
#else

    if (src == null || dst == null) return 0;

    const char* src_chr = src;
    char* dst_chr = dst;
    size_t index = 0;

    while (index < len)
    {
        dst_chr[index] = src_chr[index];
        ++index;
    }

    return 0;
#endif
}

size_t strlen(const char* str)
{
	if (*str == 0) return 0;

    size_t len = 0;
    while (str[len] != '\0')
        ++len;

    return len;
}

size_t strnlen(const char* str, size_t len)
{
    size_t cnt = 0;

    while (len > cnt)
    {
        ++cnt;

        if (str[cnt] == '\0')
            return (size_t)-1;
    }

    return len;
}

void strreverse(char *s)
{
    if (s == null) return;
    if (*s == '\0') return;

    char *first, *last, temp;

    first = s;
    last = s + strlen(s) - 1;

    while (first != last)
    {
        temp = *first;
        *(first++) = *last;
        *(last--) = temp;
    }
}

char* strchr(char* str, const char chr)
{
    while (*str != chr)
    {
      ++str;

      if (*str == 0)
        return null;
    }

    return str;
}
