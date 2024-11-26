/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <libfdt/libfdt_env.h>

#define FDT_FIRST_SUPPORTED_VERSION	(0x02)
#define FDT_LAST_COMPATIBLE_VERSION (0x10)
#define FDT_LAST_SUPPORTED_VERSION	(0x11)

#define FDT_ERR_NOTFOUND	(1U)
#define FDT_ERR_EXISTS      (2U)
#define FDT_ERR_NOSPACE     (3U)
#define FDT_ERR_BADOFFSET   (4U)
#define FDT_ERR_BADPATH     (5U)
#define FDT_ERR_BADPHANDLE  (6U)
#define FDT_ERR_BADSTATE    (7U)
#define FDT_ERR_TRUNCATED	(8U)
#define FDT_ERR_BADMAGIC	(9U)
#define FDT_ERR_BADVERSION	(10U)
#define FDT_ERR_BADSTRUCTURE (11U)
#define FDT_ERR_BADLAYOUT	(12U)
#define FDT_ERR_INTERNAL	(13U)
#define FDT_ERR_BADNCELLS	(14U)
#define FDT_ERR_BADVALUE	(15U)
#define FDT_ERR_BADOVERLAY	(16U)
#define FDT_ERR_NOPHANDLES	(17U)
#define FDT_ERR_BADFLAGS	(18U)
#define FDT_ERR_ALIGNMENT	(19U)

#define FDT_ERR_MAX		    (FDT_ERR_ALIGNMENT)

#define FDT_MAX_PHANDLE     (0xfffffffe)

#define FDT_MAGIC	0xd00dfeed	/* 4: version, 4: total size */
#define FDT_TAGSIZE	sizeof(fdt32_t)

struct fdt_header
{
	fdt32_t magic;			 /* magic word FDT_MAGIC */
	fdt32_t totalsize;		 /* total size of DT block */
	fdt32_t off_dt_struct;		 /* offset to structure */
	fdt32_t off_dt_strings;		 /* offset to strings */
	fdt32_t off_mem_rsvmap;		 /* offset to memory reserve map */
	fdt32_t version;		 /* format version */
	fdt32_t last_comp_version;	 /* last compatible version */

	/* version 2 fields below */
	fdt32_t boot_cpuid_phys;	 /* Which physical CPU id we're
					    booting on */
	/* version 3 fields below */
	fdt32_t size_dt_strings;	 /* size of the strings block */

	/* version 17 fields below */
	fdt32_t size_dt_struct;		 /* size of the structure block */
};

struct fdt_reserve_entry
{
	fdt64_t address;
	fdt64_t size;
};

struct fdt_node_header
{
	fdt32_t tag;
	char name[];
};

struct fdt_property
{
	fdt32_t tag;
	fdt32_t len;
	fdt32_t nameoff;
	char data[];
};

const void *fdt_offset_ptr(const void *fdt, int offset, unsigned int checklen);

static inline voidptr_t fdt_offset_ptr_w(const voidptr_t fdt, int32_t offset, uint32_t checklen)
{
    return (voidptr_t)(fdt_offset_ptr(fdt, offset, checklen));
}

/*
 *  External helpers to access words from a device tree blob.
*/

static inline uint16_t fdt16_ld(const fdt16_t *p)
{
	const uint8_t *bp = (const uint8_t *)p;

	return ((uint16_t)bp[0] << 8) | bp[1];
}

static inline uint32_t fdt32_ld(const fdt32_t *p)
{
	const uint8_t *bp = (const uint8_t *)p;

	return ((uint32_t)bp[0] << 24)
		| ((uint32_t)bp[1] << 16)
		| ((uint32_t)bp[2] << 8)
		| bp[3];
}

static inline void fdt32_st(void *property, uint32_t value)
{
	uint8_t *bp = (uint8_t *)property;

	bp[0] = value >> 24;
	bp[1] = (value >> 16) & 0xff;
	bp[2] = (value >> 8) & 0xff;
	bp[3] = value & 0xff;
}

static inline uint64_t fdt64_ld(const fdt64_t *p)
{
	const uint8_t *bp = (const uint8_t *)p;

	return ((uint64_t)bp[0] << 56)
		| ((uint64_t)bp[1] << 48)
		| ((uint64_t)bp[2] << 40)
		| ((uint64_t)bp[3] << 32)
		| ((uint64_t)bp[4] << 24)
		| ((uint64_t)bp[5] << 16)
		| ((uint64_t)bp[6] << 8)
		| bp[7];
}

static inline void fdt64_st(void *property, uint64_t value)
{
	uint8_t *bp = (uint8_t *)property;

	bp[0] = value >> 56;
	bp[1] = (value >> 48) & 0xff;
	bp[2] = (value >> 40) & 0xff;
	bp[3] = (value >> 32) & 0xff;
	bp[4] = (value >> 24) & 0xff;
	bp[5] = (value >> 16) & 0xff;
	bp[6] = (value >> 8) & 0xff;
	bp[7] = value & 0xff;
}

//
// Node traversal functions
//

int fdt_next_node(const void *fdt, int offset, int *depth);

/// @brief - get offset of first direct subnode
/// @param fdt fdt blob
/// @param offset offset of node to check
/// @return offset of first subnode, or -FDT_ERR_NOTFOUND if there is none

int fdt_first_subnode(const void *fdt, int offset);

/// @brief - get offset of next direct subnode
/// @param fdt fdt blob
/// @param offset  offset of node to check
/// @return offset of next subnode, or -FDT_ERR_NOTFOUND if there are no more subnodes.

int fdt_next_subnode(const void *fdt, int offset);

#define fdt_get_header(fdt, field) (fdt32_ld(&((const struct fdt_header *)(fdt))->field))

#define fdt_magic(fdt)			(fdt_get_header(fdt, magic))
#define fdt_totalsize(fdt)		(fdt_get_header(fdt, totalsize))
#define fdt_off_dt_struct(fdt)		(fdt_get_header(fdt, off_dt_struct))
#define fdt_off_dt_strings(fdt)		(fdt_get_header(fdt, off_dt_strings))
#define fdt_off_mem_rsvmap(fdt)		(fdt_get_header(fdt, off_mem_rsvmap))
#define fdt_version(fdt)		(fdt_get_header(fdt, version))
#define fdt_last_comp_version(fdt)	(fdt_get_header(fdt, last_comp_version))
#define fdt_boot_cpuid_phys(fdt)	(fdt_get_header(fdt, boot_cpuid_phys))
#define fdt_size_dt_strings(fdt)	(fdt_get_header(fdt, size_dt_strings))
#define fdt_size_dt_struct(fdt)		(fdt_get_header(fdt, size_dt_struct))

#define fdt_set_hdr_(name) \
	static inline void fdt_set_##name(void *fdt, uint32_t val) \
	{ \
		struct fdt_header *fdth = (struct fdt_header *)fdt; \
		fdth->name = cpu_to_fdt32(val); \
	}



fdt_set_hdr_(magic);
fdt_set_hdr_(totalsize);
fdt_set_hdr_(off_dt_struct);
fdt_set_hdr_(off_dt_strings);
fdt_set_hdr_(off_mem_rsvmap);
fdt_set_hdr_(version);
fdt_set_hdr_(last_comp_version);
fdt_set_hdr_(boot_cpuid_phys);
fdt_set_hdr_(size_dt_strings);
fdt_set_hdr_(size_dt_struct);

#undef fdt_set_hdr_
