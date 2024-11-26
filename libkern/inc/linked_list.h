/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <sys/sys.h>

typedef struct sys_linked_list
{
    voidptr_t l_data;

    struct sys_linked_list* l_prev;
    struct sys_linked_list* l_next;
} linked_list_t;

linked_list_t* linked_list_new(void);
int linked_list_remove(linked_list_t* list);
void linked_list_clear(linked_list_t* list);
linked_list_t* linked_list_find(linked_list_t* list, voidptr_t data);

#define ll_get_next(LL) (LL->l_next)
#define ll_get_prev(LL) (LL->l_prev)
#define ll_get_data(LL) (LL->l_data)
