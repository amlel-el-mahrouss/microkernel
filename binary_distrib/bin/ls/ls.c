/*
 *	========================================================
 *
 *	NonGNU 'ls'
 * 	Date Added: 04/11/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/dirent.h>
#include <sys/dir.h>
#include <string.h>
#include <stdio.h>

static void show_dir(const char* dir, int verbose);

int main(int argc, char** argv)
{
    if (argc <= 1)
    {
        show_dir("./", 1);
        return 0;
    }

    int verbose = 0;

    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0)
        {
            verbose = 1;
            continue;
        }

        show_dir(argv[i], verbose);
    }

    return 0;
}

static void show_dir(const char* dir, int verbose)
{
    if (dir == NULL ||
        *dir == 0)
        return;

    DIR* _dir = opendir(dir);

    if (_dir != NULL)
    {
        struct dirent* dir_entry = readdir(_dir);

        do
        {
            if (verbose)
                printf("\e[1;32m %iK %s \e[0m \n", dir_entry->d_reclen, dir_entry->d_name);
            else
                printf("\e[1;32m %s \e[0m \n", dir_entry->d_name);
        } while ((dir_entry = readdir(_dir)) != NULL);

        closedir(_dir);
    }
}