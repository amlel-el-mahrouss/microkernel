/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

/**
 * @file libfdt_empty_tree.c
 * @author Amlal EL Mahrouss (amlalelmahrouss@icloud.com)
 * @brief Reimplementation of the libfdt_empty_free.c file.
 * @version 0.1
 * @date 2023-11-14
 *
 * @copyright Copyright (c) 2023 Amlal EL Mahrouss
 *
 */

#include <libfdt/libfdt_env.h>

extern int fdt_create(void* buf, int bufsize);
extern int fdt_open_into(void* buf, void* into, int bufsize);
extern int fdt_begin_node(void* buf, const char* name);
extern int fdt_end_node(void* buf);
extern int fdt_finish(void* buf);
extern int fdt_finish_reverse_map(void* buf);

#define fdt_check_err(err)\
    if (err)\
    return err\


/**
 * @brief creates a empty tree with a specified buffer and size.
 *
 * @param buf the buffer.
 * @param bufsize the size.
 * @return int
 */

int fdt_create_empty_tree(void* buf, int bufsize)
{
    int err;
    err = fdt_create(buf, bufsize);
    fdt_check_err(err);

    err = fdt_finish_reverse_map(buf);
    fdt_check_err(err);

    err = fdt_begin_node(buf, "");
    fdt_check_err(err);

    err = fdt_end_node(buf);
    fdt_check_err(err);

    err = fdt_finish(buf);
    fdt_check_err(err);

    return fdt_open_into(buf, buf, bufsize);
}

#undef fdt_check_err
