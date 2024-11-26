/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <libfdt/libfdt_env.h>

extern fdt32_t* fdt_getprop(const void* fdt, int nodeoffset, const char* name, int* len);
extern fdt32_t* fdt_append_prop(const void* fdt, int nodeoffset, const char* name, uint8_t* data, int32_t len);

#ifndef FDT_MAX_NCELLS
#define FDT_MAX_NCELLS	(4)
#endif

#ifndef FDT_BAD_NCELLS
#define FDT_BAD_NCELLS	(14)
#endif

#ifndef FDT_NOT_FOUND
#define FDT_NOT_FOUND	(1)
#endif

#ifndef FDT_BAD_VALUE
#define FDT_BAD_VALUE	(15)
#endif

static int fdt_cells(const void* fdt, int nodeoffset, const char* name)
{
    const fdt32_t* c = null;
    uint32_t val = 0;
    int len = 0;

    c = fdt_getprop(fdt, nodeoffset, name, &len);
    if (c == null)
        return len;

    if (len != sizeof(*c))
        return len;

    val = fdt32_to_cpu(*c);
    if (val > FDT_MAX_NCELLS)
        return -FDT_BAD_NCELLS;

    return (int)val;
}

int fdt_address_cells(const void* fdt, int nodeoffset)
{
    int val = 0;
    val = fdt_cells(fdt, nodeoffset, "#address-cells");
    if (val == 0)
        return -FDT_BAD_NCELLS;

    if (val == -FDT_NOT_FOUND)
        return 2;

    return (int)val;
}

int fdt_size_cells(const void* fdt, int nodeoffset) {
    int val = 0;
    val = fdt_cells(fdt, nodeoffset, "#size-cells");

    if (val == -FDT_NOT_FOUND)
        return 2;

    return (int)val;
}

int fdt_append_prop_addr_range(void* fdt, int parent, int nodeoffset,
			     const char *name, uint64_t addr, uint64_t size)
{
    int addr_cells, size_cells, ret;
    uint8_t data[sizeof(fdt64_t) * 2], *prop;

    ret = fdt_address_cells(fdt, nodeoffset);
    if (ret < 0)
        return ret;

    addr_cells = ret;

    ret = fdt_size_cells(fdt, nodeoffset);
    if (ret < 0)
        return ret;

    size_cells = ret;

    // check address validity
    prop = data;
	if (addr_cells == 1) {
        // seems to do a check according to two parameters.
        // addr > __UINT32_MAX__ detects any out of range addresses?
        // ((__UINT32_MAX__ + 1 - addr) < size check if it's lower than it's size

		if ((addr > __UINT32_MAX__) || ((__UINT32_MAX__ + 1 - addr) < size))
			return -FDT_BAD_VALUE;

        // finally set the flat device tree.
		fdt32_st(prop, (uint32_t)addr);
	} else if (addr_cells == 2) {
        // no need to check, apparently.
		fdt64_st(prop, addr);
	} else {
		return -FDT_BAD_NCELLS;
	}

    // access size
	prop += addr_cells * sizeof(fdt32_t);
	if (size_cells == 1) {
		if (size > __UINT32_MAX__)
			return -FDT_BAD_VALUE;

		fdt32_st(prop, (uint32_t)size);
	} else if (size_cells == 2) {
		fdt64_st(prop, size);
	} else {
		return -FDT_BAD_NCELLS;
	}

	return fdt_append_prop(fdt, nodeoffset, name, data,
			      (addr_cells + size_cells) * sizeof(fdt32_t));
}
