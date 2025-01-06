/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/malloc.h>
#include <sys/errno.h>
#include <sys/dev.h>
#include <string.h>
#include <sys/log.h>

__COPYRIGHT("$kernel$");

/*
 *	name: sys_device_tree
 *
 *	purpose: Device tree information,
 * 	store device pointers and the namespace.
 *
 */

struct sys_device_tree
{
	char p_name[DEV_TREE_LEN];
	uintptr_t p_devices[DEV_ARR_LEN];
	size_t p_cnt;

	struct sys_device_tree* p_prev;
	struct sys_device_tree* p_next;
};

/* forward decl */
static const char* str_dev_stat(struct sys_dev* dev);
static bool sys_dev_check(struct sys_dev* dev);

static struct sys_device_tree* g_device_tree = null;
static struct sys_device_tree* g_device_tree_prev = null;

/* checks the device itself. */
static bool sys_dev_check(struct sys_dev* dev)
{
	return dev != null && *dev->name == 0;
}

/* get the status and return value as a string. */
static const char* str_dev_stat(struct sys_dev* dev)
{
	if (!dev)
		return ("(null)");

	switch (dev->state)
	{
		case DEV_STATUS_WORKING:
			return ("(working)");

		case DEV_STATUS_IDLE:
			return ("(idle)");

		case DEV_STATUS_BUSY:
			return ("(busy)");

		case DEV_STATUS_FATAL:
			return ("(fatal)");

		default:
			return ("(null)");
	}
}

const char* sys_dev_status(struct sys_dev* dev)
{
	if (!sys_dev_check(dev))
		return ("(null)");

	return str_dev_stat(dev);
}

struct sys_dev* sys_make_dev(const char* name, size_t len, size_t nums)
{
	if (len > DEV_NAME_LENGTH || len < 1) return null;
	if (name == null) return null;
	if (*name == 0) return null;

	struct sys_dev* device = sys_alloc_ptr(sizeof(struct sys_dev),
            SYS_PROT_READ | SYS_PROT_WRITE);

	if (device == null)
        return null;

    memncpy(device->name, name, len);

	struct sys_device_tree* root = g_device_tree;

	while (root != nil)
	{
		char* tmp = sys_alloc_ptr(sizeof(char) * strlen(root->p_name), SYS_PROT_READ | SYS_PROT_WRITE);
		memncpy(tmp, device->name, strlen(root->p_name));

		if (strncmp(tmp, root->p_name, strlen(tmp)) == 0)
		{
			root->p_devices[root->p_cnt] = (uintptr_t)device;
			++root->p_cnt;

			break;
		}

		root = root->p_next;
	}

	device->length = len;
	device->count = nums;

	//! setup software descriptor.
	device->desc.access = SD_ACCESS_STANDARD;
	device->desc.type = SD_TYPE_DEVICE;
	device->desc.perms = 0U;

	//! and set it as working.
	device->state = DEV_STATUS_WORKING;

	return device;
}

int32_t sys_free_dev(struct sys_dev* dev)
{
    /* if device is null, then return an address fault */

    if (dev == null ||
		dev->state == DEV_STATUS_BUSY)
    {
        errno = EFAULT;
        return -1;
    }
    else
    {
        if (dev->state == DEV_STATUS_IDLE)
        {
			dev->state = DEV_STATUS_BUSY;

			struct sys_device_tree* root = g_device_tree;

			while (root != nil)
			{
				char* tmp = sys_alloc_ptr(sizeof(char) * strlen(root->p_name), SYS_PROT_READ | SYS_PROT_WRITE);
				memncpy(tmp, dev->name, strlen(root->p_name));

				if (strncmp(tmp, root->p_name, strlen(tmp)) == 0)
				{
					for (size_t i = 0; i < DEV_ARR_LEN; ++i)
					{
						if (root->p_devices[i] == (uintptr_t)dev)
						{
							--root->p_cnt;
							break;
						}
					}
				}

				root = root->p_next;
			}

            sys_free_ptr(dev);

            return 0;
        }
    }

    return -EACCES;
}

uintptr_t* sys_dev_find_tree(const char* name)
{
	struct sys_device_tree* root = g_device_tree;

	while (root != nil)
	{
		char* tmp = sys_alloc_ptr(sizeof(char) * strlen(root->p_name), SYS_PROT_READ | SYS_PROT_WRITE);

		memncpy(tmp, name, strlen(root->p_name));

		if (strncmp(tmp, root->p_name, strlen(tmp)) == 0)
		{
            sys_free_ptr(tmp);
			return root->p_devices;
		}

		sys_free_ptr(tmp);

		root = root->p_next;
	}

	return nil;
}

int32_t sys_dev_ctl(struct sys_dev* dev, pipe_t* pipe, ssize_t index)
{
	if (pipe != null &&
		dev != null)
	{
		if (dev->count < 1)
		{
			errno = ENOTSUP;
			return -1;
		}
		else if (index > dev->count)
		{
			errno = ENOTSUP;
			return -1;
		}

		if (dev->fn_list[index].fn != nil)
		{
			int32_t ret = dev->fn_list[index].fn(pipe);
			return ret;
		}
	}

	errno = ERANGE;
	return -1;
}

voidptr_t sys_create_dev_tree(const char* name, size_t len)
{
	if (!name || len == 0)
		return null;

	struct sys_device_tree* tree = sys_alloc_ptr(sizeof(struct sys_device_tree), SYS_PROT_READ | SYS_PROT_WRITE);

	tree->p_cnt = 0UL;
	tree->p_prev = g_device_tree_prev;

	if (tree->p_prev)
		tree->p_prev->p_next = tree;

	tree->p_next = null;

	memncpy(tree->p_name, name, len);

	sys_print_format("[dev] init %s tree.\r\n", tree->p_name);

	g_device_tree_prev = tree;

	return tree;
}

bool sys_init_device_system(void)
{
	if (g_device_tree != nil)
		return false;

	g_device_tree = sys_create_dev_tree("/dev/", strlen("/dev/"));

	sys_create_dev_tree("/proc/", strlen("/proc/")); /* process device */
	sys_create_dev_tree("/pipe/", strlen("/pipe/")); /* pipe device */
	sys_create_dev_tree("/netdev/", strlen("/netdev/")); /* network device */

	sys_make_dev("/dev/null", strlen("/dev/null"), 0);

	return true;
}

void sys_reset_device_system(void)
{
	while (g_device_tree)
	{
		voidptr_t tree = g_device_tree;
		g_device_tree = ((struct sys_device_tree*)tree)->p_next;

		sys_free_ptr(tree);
	}
}
