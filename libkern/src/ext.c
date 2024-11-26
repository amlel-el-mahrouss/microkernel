/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 01/19/2023
 *  Last Edited: 05/07/2023
 *
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sched/sched.h>
#include <sys/malloc.h>
#include <sys/errno.h>
#include <sys/ext.h>

__COPYRIGHT("$kernel$");

/* root extension linked list */
static struct sys_ext* g_root = null;

// just in case we forgot.
#ifdef sys_alloc_ext
#undef sys_alloc_ext
#endif // sys_alloc_ext

#define sys_alloc_ext(ext, open, close, module_name)\
	ext = sys_alloc_ptr(sizeof(struct sys_ext), SYS_PROT_READ | SYS_PROT_WRITE);\
	if (ext == null) return false;\
	ext->e_open = open;\
	ext->e_close = close;\
	memncpy(ext->e_name, module_name, strlen(module_name));\
	ext->e_free = false


static int ext_print_status(bool ret, const char* prefix)
{
    sys_print_format("[ EXT ] %s", prefix);
    sys_print_format(ret ? " [ OK ]\r\n" : " [ FAIL ]\r\n");

    return 0;
}

// this field tells if we cold reboot
extern bool g_reboot_requested;

// @brief init extensions

bool sys_init_root_extension(const char* name, bool(*open)(void), bool(*close)(void))
{
    if (g_root)
        return false;

    // allocate a new extension
    sys_alloc_ext(g_root, open, close, name);

    return true;
}

bool sys_add_ext_by_name(const char* name, bool(*open)(void), bool(*close)(void))
{
    if (name == null) return false;
    if (*name == 0) return false;
    if (strlen(name) > EXT_NAME_LEN) return false;
    if (open == null) return false; //! don't bother trying
    if (close == null) return false; //! don't bother trying

    if (g_root != null)
    {
        struct sys_ext* extension = g_root;

        while (extension != null)
        {
            if (extension->e_free)
            {
                sys_alloc_ext(extension, open, close, name);

                extension->e_next = sys_alloc_ptr(sizeof(struct sys_ext), SYS_PROT_READ | SYS_PROT_WRITE);
                assert(extension->e_next != null);

                extension->e_next->e_free = true;

                return true;
            }

            extension = extension->e_next;
        }

        return false;
    }

    return true;
}

void sys_load_ext(void)
{
    struct sys_ext* extension = g_root;

    while (extension != null)
    {
        if (extension->e_free)
        {
            extension = extension->e_next;

            continue;
        }

        bool ret = extension->e_open();
        ext_print_status(ret, "load");

        extension = extension->e_next;
    }
}

void sys_unload_ext(void)
{
    struct sys_ext* extension = g_root;

    while (extension != null)
    {
        if (extension->e_free)
            continue;

        bool ret = extension->e_close();
        ext_print_status(ret, "unload");

        extension = extension->e_next;
    }
}

int32_t sys_unload_ext_by_name(const char* name)
{
    if (name == null || *name == 0)
        return -1;

    if (strnlen(name, EXT_NAME_LEN + 1) > EXT_NAME_LEN)
        return -2;

    struct sys_ext* extension = g_root;

    while (extension != null)
    {
        if (extension->e_free)
            continue;

        if (strncmp(extension->e_name, name, EXT_NAME_LEN) == 0)
        {
            if (extension->e_close == null)
                return ENOTSUP;

            bool ret = extension->e_close();

            return !ret; // should return zero if everything did go as intended
        }
    }

    return 0;
}

int32_t sys_load_ext_by_name(const char* name)
{
    if (name == null || *name == 0)
        return -1;

    if (strnlen(name, EXT_NAME_LEN + 1) > EXT_NAME_LEN)
        return -2;

    struct sys_ext* extension = g_root;

    while (extension != null)
    {
        if (extension->e_free)
            continue;

        if (strncmp(extension->e_name, name, EXT_NAME_LEN) == 0)
        {
            bool ret = extension->e_open();

            return !ret; // should return zero if everything did go as intended
        }
    }

    return 0;
}
