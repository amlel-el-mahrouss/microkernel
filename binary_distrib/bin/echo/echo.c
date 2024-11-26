/*
 *	========================================================
 *
 *	NonGNU 'echo'
 * 	Date Added: 04/11/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <stdio.h>

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; ++i) 
    {
        printf("%s", argv[i]);
        printf(" ");
    }

    printf("\n");

    return 0;
}