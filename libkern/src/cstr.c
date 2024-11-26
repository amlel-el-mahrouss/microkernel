/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/cstr.h>

#include <errno.h>
#include <sys/malloc.h>

struct cstr* sys_cstr_new(const char* buffer, size_t len)
{
	if (len < 1 ||
		buffer == null ||
		*buffer == 0)
		return null;

	struct cstr* new_cstr = sys_alloc_ptr(sizeof(struct cstr), SYS_PROT_READ | SYS_PROT_WRITE);

	if (new_cstr == null)
	{
		errno = ESTR;
		return null;
	}

	new_cstr->s_cursor = 0;
	new_cstr->s_length = len;
	new_cstr->s_buffer = sys_alloc_ptr(sizeof(char) * new_cstr->s_length, SYS_PROT_READ | SYS_PROT_WRITE);

	if (new_cstr->s_buffer == null)
	{
		sys_free_ptr(new_cstr);
		new_cstr = null;

		errno = ESTR;
		return null;
	}

	strncpy(new_cstr->s_buffer, buffer, len);

	return new_cstr;
}

void sys_cstr_merge(struct cstr* old_cstr, struct cstr* new_cstr)
{
	if (old_cstr == null || new_cstr == null) goto fail;
	if (new_cstr->s_buffer == null || old_cstr->s_buffer == null) goto fail;

	// cursors check.
	if (new_cstr->s_cursor > old_cstr->s_cursor) goto fail;

	void* ptr = old_cstr->s_buffer;
	old_cstr->s_buffer = sys_realloc_ptr(old_cstr->s_buffer, new_cstr->s_length, SYS_PROT_WRITE | SYS_PROT_READ);

	if (ptr != old_cstr->s_buffer)
	{
		sys_free_ptr(old_cstr->s_buffer);
		old_cstr->s_buffer = ptr;

		goto fail;
	}

	size_t i = 0;

	while (i < new_cstr->s_length)
	{
		int off = old_cstr->s_length + i;
		old_cstr->s_buffer[off] = new_cstr->s_buffer[off];
	}

	old_cstr->s_length += new_cstr->s_length;
	old_cstr->s_cursor += new_cstr->s_cursor;

	return;

// something has gone wrong if we arrive here!
// this could be -> string doesn't match
// or:
// cursor are out of bounds.
fail:
	IOLog("sys_cstr_merge - ESTR\r\n");
	errno = ESTR;

	return;
}

bool sys_cstr_chk(struct cstr* str)
{
	return str && str->s_buffer[str->s_length] == 0;
}

void sys_cstr_delete(struct cstr* str)
{
	if (str != null)
	{
		if (str->s_buffer != null)
			sys_free_ptr(str->s_buffer);

		sys_free_ptr(str);
		str = null;
	}
}
