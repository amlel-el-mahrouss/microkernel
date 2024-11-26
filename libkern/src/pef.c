/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

/**
 * @file pef.c
 * @author amlel
 * @date 16 May 2023
 * @brief Preferred Executable Format for kernel.
 */

#include <pef.h>
#include <sys/fd.h>
#include <sys/malloc.h>

/* read as binary */
#define PEF_OPEN_AS "rb"

struct mpux_glob sys_load_exec_glob(const char* filename)
{
    fd_t file = sys_open(filename, PEF_OPEN_AS);

    struct mpux_glob glob;
    zero_memory(&glob, sizeof(struct mpux_glob));

    strncpy(glob.filename, filename, strlen(filename));

    if (file != -1)
    {
        sys_seek(file, 0, SEEK_END);
        size_t tell_len = sys_tell(file);

        glob.glob_sz = tell_len;

        char* buf = kalloc(sizeof(char) * tell_len,
                                  SYS_PROT_READ | SYS_PROT_WRITE);

        if (buf == nil)
        {
            glob.glob_sz = -1;
            glob.glob = nil;

            sys_close(file);
            return glob;
        }

        /* read all of file */
        sys_seek(file, 0, SEEK_SET);
        sys_read(file, buf, SEEK_SET, tell_len);

        struct pef_exec_header* exec = (struct pef_exec_header*)(buf);

        if (exec->mag[0] != PEF_MAGIC[0] &&
            exec->mag[1] != PEF_MAGIC[1] &&
            exec->mag[2] != PEF_MAGIC[2] &&
            exec->abi != PEF_ABI)
        {
            kfree(buf);
            sys_close(file);

            buf = nil;

            glob.glob_sz = -1;
            glob.glob = nil;

            return glob;
        }

        glob.glob = buf;
    }

    sys_close(file);
    return glob;
}
