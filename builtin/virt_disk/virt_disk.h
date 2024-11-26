/* based on  -- https://github.com/mit-pdos/xv6-riscv/ */
/* with changes from Amlal EL Mahrouss, (c) Amlal EL Mahrouss */

#pragma once

#include <sys/sys.h>
#include <sys/lock.h>
#include <hw/mmap.h>
#include <hw/mmu.h>
#include <string.h>

/* offsets */
#define VIRTIO_MMIO_MAGIC_VALUE 0x000 // Magic value must be 0x74726976
#define VIRTIO_MMIO_VERSION		0x004     // Version: 1 (Legacy)

/*
 * Device ID:
 * 1 (Network Device)
 * 2 (Block Device)
 * 4 (Random number generator Device)
 * 16 (GPU Device)
 * 18 (Input Device)
 */

#define VIRTIO_MMIO_DEVICE_ID 0x008
#define VIRTIO_MMIO_VENDOR_ID 0x00c // 0x554d4551
#define VIRTIO_MMIO_DEVICE_FEATURES 0x010
#define VIRTIO_MMIO_DRIVER_FEATURES 0x020
#define VIRTIO_MMIO_GUEST_PAGE_SIZE 0x028  // page size for PFN, write-only
#define VIRTIO_MMIO_QUEUE_SEL 0x030        // select queue, write-only
#define VIRTIO_MMIO_QUEUE_NUM_MAX 0x034    // max size of current queue, read-only
#define VIRTIO_MMIO_QUEUE_NUM 0x038        // size of current queue, write-only
#define VIRTIO_MMIO_QUEUE_ALIGN 0x03c      // used ring alignment, write-only
#define VIRTIO_MMIO_QUEUE_PFN 0x040        // physical page number for queue, read/write
#define VIRTIO_MMIO_QUEUE_READY 0x044      // ready bit
#define VIRTIO_MMIO_QUEUE_NOTIFY 0x050     // write-only
#define VIRTIO_MMIO_INTERRUPT_STATUS 0x060 // read-only
#define VIRTIO_MMIO_INTERRUPT_ACK 0x064    // write-only
#define VIRTIO_MMIO_STATUS 0x070           // read/write
#define VIRTIO_MMIO_QUEUE_DESC_LOW 0x080
#define VIRTIO_MMIO_QUEUE_DESC_HIGH 0x084
#define VIRTIO_MMIO_QUEUE_AVAIL_LOW 0x090
#define VIRTIO_MMIO_QUEUE_AVAIL_HIGH 0x094
#define VIRTIO_MMIO_QUEUE_USED_LOW 0x0a0
#define VIRTIO_MMIO_QUEUE_USED_HIGH 0x0a4

// status register bits, from qemu virtio_config.h
#define VIRTIO_CONFIG_S_ACKNOWLEDGE 1
#define VIRTIO_CONFIG_S_DRIVER 2
#define VIRTIO_CONFIG_S_DRIVER_OK 4
#define VIRTIO_CONFIG_S_FEATURES_OK 8

// device feature bits
#define VIRTIO_BLK_F_RO 5          /* Disk is read-only */
#define VIRTIO_BLK_F_SCSI 7        /* Supports scsi command passthru */
#define VIRTIO_BLK_F_CONFIG_WCE 11 /* Writeback mode available in config */
#define VIRTIO_BLK_F_MQ 12         /* support more than one vq */
#define VIRTIO_F_ANY_LAYOUT 27
#define VIRTIO_RING_F_INDIRECT_DESC 28
#define VIRTIO_RING_F_EVENT_IDX 29

// this many virtio descriptors.
#define VIRTIO_NUM 8

typedef struct virtq_desc
{
  uint64_t addr;
  uint32_t len;
  uint16_t flags;
  uint16_t next;
} virtq_desc_t;

#define VRING_DESC_F_NEXT 1     // chained with another descriptor
#define VRING_DESC_F_WRITE 2    // device writes (vs read)
#define VRING_DESC_F_INDIRECT 4 // buffer contains a list of buffer descriptors

typedef struct virtq_avail
{
  uint16_t flags;     // always zero
  uint16_t idx;       // driver will write ring[idx] next
  uint16_t ring[VIRTIO_NUM]; // descriptor numbers of chain heads
} virtq_avail_t;


typedef struct virtq_used_elem
{
  uint32_t id; // index of start of completed descriptor chain
  uint32_t len;
} virtq_used_elem_t;

typedef struct virtq_used
{
  uint16_t flags; // always zero
  uint16_t idx;   // device increments when it adds a ring[] entry
  struct virtq_used_elem ring[VIRTIO_NUM];
} virtq_used_t;

// these are specific to virtio block devices, e.g. disks,
// described in Section 5.2 of the spec.

#define VIRTIO_BLK_T_IN 0  // read the disk
#define VIRTIO_BLK_T_OUT 1 // write the disk

// the format of the first descriptor in a disk request.
// to be followed by two more descriptors containing
// the block, and a one-byte status.
typedef struct virtio_blk_req
{
  uint32_t type;     // VIRTIO_BLK_T_IN or ..._OUT
  uint16_t reserved;
  uint64_t sector;
} virtio_blk_req_t;

typedef uint64_t virtio_lba_desc_t;

#define VIRT_REG(r) (((volatile uint32_t*)(sys_get_mmap()[HW_MEMMAP_VIRT_BLK].base_ptr + (r))))

#define VIRT_BLK_SIZE 512 // block size
#define VIRT_PGSHIFT  12

void hw_virt_disk_init(void);

/**
 * @brief virt block device structure
 */

typedef struct virtio_blk
{
	uint32_t dev;
	uint32_t blockno;
	lock_t lock;
	int disk;
	unsigned char data[VIRT_BLK_SIZE];
} virtio_blk_t;

/**
 * @brief virt context disk structure.
 */

typedef struct disk
{
	char* pages;
	/* descriptor */
	virtq_desc_t *desc;
	/* AvailableRing */
	virtq_avail_t *avail;
	/* UsedRing */
	virtq_used_t *used;
	/* For decord each descriptor is free or not */
	char free[VIRTIO_NUM];

	struct
	{
		struct virtio_blk *b;
		char status;
	} info[VIRTIO_NUM];
	uint16_t used_idx;

	/* Disk command headers */
	virtio_blk_req_t ops[VIRTIO_NUM];

	lock_t *vdisk_lock;
} __attribute__((aligned(__PAGE_SIZE__))) virtio_disk_t;

#define VIRT_READ_INDEX  0
#define VIRT_WRITE_INDEX 1