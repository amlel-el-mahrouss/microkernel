#pragma once

#include <sys/sys.h>

struct cstr;

struct cstr {
	char* s_buffer;
	size_t s_cursor;
	size_t s_length;
};

bool sys_cstr_chk(struct cstr* str);
void sys_cstr_delete(struct cstr* str);
struct cstr* sys_cstr_new(const char* buffer, size_t len);
void sys_cstr_merge(struct cstr* str1, struct cstr* str2);
