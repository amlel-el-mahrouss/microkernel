/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 10/11/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __NVM_EXPRESS_H
#define __NVM_EXPRESS_H

#include <hw/pci_express.h>
#include <hw/mmap.h>

#include <assert.h>

union nvme_caps_low_register
{
    uint32_t raw;

    struct
    {
        /** maximum queue entries supported. */
        uint32_t mqes : 16;
        uint32_t cqr : 1;
        uint32_t ams : 2;
        uint32_t res : 5;
        uint32_t to  : 8;
    } bits;
} __attribute__((packed));

union nvme_caps_hi_register
{
    uint32_t raw;

    struct
    {
		/** doorbell stride */
		uint32_t dstrd		: 4;
		uint32_t reserved3	: 1;

		/** command sets supported */
		uint32_t css_nvm	: 1;

		uint32_t css_reserved	: 3;
		uint32_t reserved2	: 7;

		/** memory page size minimum */
		uint32_t mpsmin		: 4;

		/** memory page size maximum */
		uint32_t mpsmax		: 4;
		uint32_t reserved1	: 8;
    } bits; // no need to pack again.
} __attribute__((packed));

union nvme_command_ctrl_register
{
	uint32_t	raw;
	struct {
		/** enable */
		uint32_t en		: 1;

		uint32_t reserved1	: 3;

		/** i/o command set selected */
		uint32_t css		: 3;

		/** memory page size */
		uint32_t mps		: 4;

		/** arbitration mechanism selected */
		uint32_t ams		: 3;

		/** shutdown notification */
		uint32_t shn		: 2;

		/** i/o submission queue entry size */
		uint32_t iosqes		: 4;

		/** i/o completion queue entry size */
		uint32_t iocqes		: 4;

		uint32_t reserved2	: 8;
	} bits;
} __attribute__((packed));

enum
{
	NVME_SHN_NORMAL		= 0x1,
	NVME_SHN_ABRUPT		= 0x2,
};

union nvme_csts_register
{
	uint32_t	raw;
	struct {
		/** ready */
		uint32_t rdy		: 1;

		/** controller fatal status */
		uint32_t cfs		: 1;

		/** shutdown status */
		uint32_t shst		: 2;

		uint32_t reserved1	: 28;
	} bits;
} __attribute__((packed));

/* disk status */
enum
{
	NVME_SHST_NORMAL	= 0x0,
	NVME_SHST_OCCURRING	= 0x1,
	NVME_SHST_COMPLETE	= 0x2,
};

union nvme_aqa_register
{
	uint32_t raw;

	struct
    {
		/* Admin submission queue size */
		uint32_t asqs		: 12;

		uint32_t reserved1	: 4;

		/* Admin completion queue size */
		uint32_t acqs		: 12;

		uint32_t reserved2	: 4;
	} bits;

};

struct nvme_registers
{
	/** controller capabilities */
	union nvme_caps_low_register	cap_lo;
	union nvme_caps_hi_register	cap_hi;

	uint32_t		vs;	/* version */
	uint32_t		intms;	/* interrupt mask set */
	uint32_t		intmc;	/* interrupt mask clear */

	/** controller configuration */
	union nvme_command_ctrl_register	cc;

	uint32_t		reserved1;

	/** controller status */
	union nvme_csts_register	csts;

	uint32_t		reserved2;

	/** admin queue attributes */
	union nvme_aqa_register	aqa;

	uint64_t		asq;	/* admin submission queue base addr */
	uint64_t		acq;	/* admin completion queue base addr */
	uint32_t		reserved3[0x3f2];

	struct
    {
	    uint32_t		sq_tdbl; /* submission queue tail doorbell */
	    uint32_t		cq_hdbl; /* completion queue head doorbell */
	} doorbell[1];
} __attribute__((packed));

struct nvme_command
{
	/* dword 0 */
	uint16_t opc	:  8;	/* opcode */
	uint16_t fuse	:  2;	/* fused operation */
	uint16_t rsvd1	:  6;
	uint16_t cid;		/* command identifier */

	/* dword 1 */
	uint32_t nsid;		/* namespace identifier */

	/* dword 2-3 */
	uint32_t rsvd2;
	uint32_t rsvd3;

	/* dword 4-5 */
	uint64_t mptr;		/* metadata pointer */

	/* dword 6-7 */
	uint64_t prp1;		/* prp entry 1 */

	/* dword 8-9 */
	uint64_t prp2;		/* prp entry 2 */

	/* dword 10-15 */
	uint32_t cdw10;		/* command-specific */
	uint32_t cdw11;		/* command-specific */
	uint32_t cdw12;		/* command-specific */
	uint32_t cdw13;		/* command-specific */
	uint32_t cdw14;		/* command-specific */
	uint32_t cdw15;		/* command-specific */
} __attribute__((packed));

struct nvme_status
{
	uint16_t p	:  1;	/* phase tag */
	uint16_t sc	:  8;	/* status code */
	uint16_t sct	:  3;	/* status code type */
	uint16_t rsvd2	:  2;
	uint16_t m	:  1;	/* more */
	uint16_t dnr	:  1;	/* do not retry */
} __attribute__((packed));

struct nvme_completion
{
	/* dword 0 */
	uint32_t		cdw0;	/* command-specific */

	/* dword 1 */
	uint32_t		rsvd1;

	/* dword 2 */
	uint16_t		sqhd;	/* submission queue head pointer */
	uint16_t		sqid;	/* submission queue identifier */

	/* dword 3 */
	uint16_t		cid;	/* command identifier */
	struct nvme_status	status;
} __attribute__((packed));

struct nvme_dsm_range
{
	uint32_t attributes;
	uint32_t length;
	uint64_t starting_lba;
} __attribute__((packed));

#define NVME_32BIT_SIZE 4

static_assert(sizeof(union nvme_aqa_register) == NVME_32BIT_SIZE, "incorrect register size");

/* generate raw version used for device probing.
   maybe like ahci. */
#define NVME_VERSION(mjr, mnr, ter) \
	(((uint32_t)(mjr) << 16) |  \
	 ((uint32_t)(mnr) << 8) |   \
	 (uint32_t)(ter))


static_assert(NVME_VERSION(1, 0, 0) == 0x00010000, "version macro error");
static_assert(NVME_VERSION(1, 2, 1) == 0x00010201, "version macro error");

void hw_nvme_init(void);

#endif /* ifndef __NVM_EXPRESS_H */
