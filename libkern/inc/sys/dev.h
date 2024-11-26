/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 09/01/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * ========================================================
 */

#ifndef _SYS_DEV_H
#define _SYS_DEV_H

#include <sys/sys.h>
#include <sys/pipe.h>
#include <sys/sdctl.h>

/* some device control helpers. */
#define DEV_ARR_LEN 128
#define DEV_TREE_LEN 256

/* device status helpers. */
#define DEV_STATUS_WORKING (200U)
#define DEV_STATUS_BUSY    (201U)
#define DEV_STATUS_FATAL   (203U)
#define DEV_STATUS_IDLE    (204U)
#define DEV_STATUS_UNKNOWN (0xFF)
#define DEV_NAME_LENGTH    (256U)

// device procedure call type.
typedef int(*dev_opt_t)(pipe_t* pipe);

// ----------------------------------------------------------------
// Structure: sys_dev_opt
// Purpose: Device operation abstraction structure.
// ----------------------------------------------------------------

struct sys_dev_opt
{
   char      name[DEV_ARR_LEN]; /* i/o name */
   dev_opt_t fn;
};

// max dev i/o
#define DEV_MAX_FN 16

// ----------------------------------------------------------------
// Structure: sys_dev
// Purpose: Device abstraction structure.
// ----------------------------------------------------------------

struct sys_dev
{
   char name[DEV_NAME_LENGTH]; /*  \IO\TERM0 */
   size_t length; /* length of name */
   uint16_t count; /* number of functions */
   uint16_t state; /* it's current state */
   struct sys_sdctl desc; /* software descriptor */
   struct sys_dev_opt fn_list[DEV_MAX_FN]; /* it's io/functions */
};

typedef uintptr_t* device_tree_t;

struct sys_dev* sys_make_dev(const char* name, size_t nameLen, size_t nums); /* make a device fron a tree. */
int32_t sys_dev_ctl(struct sys_dev* dev, pipe_t* pipe, ssize_t index); /* device control. */
const char* sys_dev_status(struct sys_dev* dev); /* get the device status. */
int32_t sys_free_dev(struct sys_dev* pipe); /* free a device. */
uintptr_t* sys_dev_find_tree(const char* name); /* finds a device tree from the OS. */
voidptr_t sys_create_dev_tree(const char* name, size_t len);
bool sys_init_device_system(void); /* devices initialization. */
void sys_reset_device_system(void);

typedef struct sys_dev dev_t;

#endif /* ifndef _SYS_DEV_H */
