/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

/* MP MicroKernel archive format */

#define ARMAG   "!<arch>\n"      /* magic format string */
#define SARMAG  8
#define ARFMAG  "`\n"     /* header trailer string */

// ----------------------------------------------------------------
// Structure: sys_ar_hdr
// Purpose: Library information.
// ----------------------------------------------------------------

struct sys_ar_hdr                  /* file member header */
{
    char    obj_name[16];        /* '/' terminated file member name */
    char    obj_date[12];        /* file member date */
    char    obj_uid[6];           /* file member user identification */
    char    obj_gid[6];           /* file member group identification */
    char    obj_mode[8];          /* file member mode (ACL) */
    char    obj_size[10];        /* file member size */
    char    obj_fmag[3];         /* header trailer string */
};
