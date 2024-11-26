/*
 *	========================================================
 *
 *	MP MicroKernel
 *
 * 	Date Added: 09/01/2023
 *	Date Edit: 22/01/2023
 *
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

/* not really for strings only, but sysctl was already taken. */

#include <sys/strctl.h>
#include <sys/errno.h>
#include <string.h>
#include <kernel.h>

static struct strctl* g_strctl_list = null;
static size_t g_count = 0;

int32_t sys_strctl_add(voidptr_t data, const char* hash)
{
	if (!hash || !data) return ESTRCTL;
	if (*hash == 0) return EBADMSG;

	struct strctl* prev = null;
	struct strctl* root_strctl = g_strctl_list;

	while (root_strctl != null)
	{
		prev = root_strctl;
		root_strctl = root_strctl->s_next;
	}

	root_strctl = sys_alloc_ptr(sizeof(struct strctl), SYS_PROT_WRITE | SYS_PROT_READ);

	for (size_t i = 0; i < strlen(hash); ++i)
	{
		root_strctl->s_hash |= hash[i];
	}

	root_strctl->s_data = data;

	root_strctl->s_prev = prev;
	root_strctl->s_next = null;

	++g_count;
	return 0;
}

voidptr_t sys_strctl_get_ptr(const char* hash)
{
	if (!g_strctl_list)
	{
		errno = EFAULT;
		return null;
	}

	struct strctl* root_strctl = g_strctl_list;
	size_t xhash = 0UL;

	while (root_strctl != null)
	{
		xhash = 0;

		for (size_t i = 0; i < strlen(hash); ++i)
		{
			xhash |= (size_t)hash[i];
		}

		if (xhash == root_strctl->s_hash)
			return root_strctl->s_data;

		root_strctl = root_strctl->s_next;
	}

	errno = ESTRCTL;
	return null;
}

size_t sys_strctl_get_size(void) { return g_count; }
