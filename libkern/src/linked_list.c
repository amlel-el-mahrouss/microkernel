/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <linked_list.h>
#include <sys/malloc.h>

__COPYRIGHT("$kernel$");

linked_list_t* linked_list_new(void)
{
    return sys_alloc_ptr(sizeof(linked_list_t), SYS_PROT_READ | SYS_PROT_WRITE);
}

int linked_list_remove(linked_list_t* list)
{
    if (list != null)
    {
        list->l_next->l_prev = list->l_prev;
        list->l_prev->l_next = list->l_next;

        sys_free_ptr(list);

        return 0;
    }

    return -1;
}

void linked_list_clear(linked_list_t* list)
{
    if (list)
    {
        linked_list_t* rootLL = list;

        while (rootLL != null)
        {
            linked_list_t* next = rootLL->l_next;

            sys_free_ptr(rootLL);

            rootLL = next;
        }
    }
}

linked_list_t* linked_list_find(linked_list_t* list, voidptr_t data)
{
    if (list)
    {
        linked_list_t* rootLL = list;

        while (rootLL != null)
        {
            if (data == rootLL->l_data)
                return rootLL;

            rootLL = rootLL->l_next;
        }
    }

    return null;
}
