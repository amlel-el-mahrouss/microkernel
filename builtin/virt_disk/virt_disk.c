/* based on  -- https://github.com/mit-pdos/xv6-riscv/ */
/* with changes from Amlal EL Mahrouss, (c) Amlal EL Mahrouss */

#include <virt_disk/virt_disk.h>
#include <sys/timer.h>
#include <sys/attr.h>
#include <sys/dev.h>

/* include heap routines */
#include <sys/malloc.h>

__COPYRIGHT("$kernel$");

static dev_t *g_dev = nil;
static virtio_disk_t g_disk;

static int virt_write_wrapper(pipe_t *pipe);
static int virt_read_wrapper(pipe_t *pipe);

#define VIRTIO_MAGIC 		0x74726976
#define VIRTIO_VENDOR_ID 	0x554d4551
#define VIRTIO_VERSION 		2
#define VIRTIO_DEVICE_ID 	2

//////////////////////////////////////////////////////////////////////////////////////////////

void hw_virt_disk_init(void)
{
	uint32_t status = 0;

	/* RISC-V specific. */
	if (*VIRT_REG(VIRTIO_MMIO_MAGIC_VALUE) != VIRTIO_MAGIC ||
		*VIRT_REG(VIRTIO_MMIO_VERSION) != VIRTIO_VERSION ||
		*VIRT_REG(VIRTIO_MMIO_DEVICE_ID) != VIRTIO_DEVICE_ID ||
		*VIRT_REG(VIRTIO_MMIO_VENDOR_ID) != VIRTIO_VENDOR_ID)
	{
		sys_print_format("virtio_disk_probe_failed, magic: %x, version: %x, devid: %x, vendor_id: %x\r\n",
						*VIRT_REG(VIRTIO_MMIO_MAGIC_VALUE),
						*VIRT_REG(VIRTIO_MMIO_VERSION),
						*VIRT_REG(VIRTIO_MMIO_DEVICE_ID),
						*VIRT_REG(VIRTIO_MMIO_VENDOR_ID));

		return;
	}

	sys_print_format("virtio_disk_probe_success, magic: %x, version: %x, devid: %x, vendor_id: %x\r\n",
					*VIRT_REG(VIRTIO_MMIO_MAGIC_VALUE),
					*VIRT_REG(VIRTIO_MMIO_VERSION),
					*VIRT_REG(VIRTIO_MMIO_DEVICE_ID),
					*VIRT_REG(VIRTIO_MMIO_VENDOR_ID));



	/* Reset the device */
	*VIRT_REG(VIRTIO_MMIO_STATUS) = status;
	/* Set the ACKNOWLEDGE status bit to the status register. */



	status |= VIRTIO_CONFIG_S_ACKNOWLEDGE;
	*VIRT_REG(VIRTIO_MMIO_STATUS) = status;



	/* Set the DRIVER status bit to the status register. */
	status |= VIRTIO_CONFIG_S_DRIVER;
	*VIRT_REG(VIRTIO_MMIO_STATUS) = status;



	/* negotiate features */
	uint32_t features = *VIRT_REG(VIRTIO_MMIO_DEVICE_FEATURES);

	features &= ~(1 << VIRTIO_BLK_F_RO);
	features &= ~(1 << VIRTIO_BLK_F_SCSI);
	features &= ~(1 << VIRTIO_BLK_F_CONFIG_WCE);
	features &= ~(1 << VIRTIO_BLK_F_MQ);
	features &= ~(1 << VIRTIO_F_ANY_LAYOUT);
	features &= ~(1 << VIRTIO_RING_F_EVENT_IDX);
	features &= ~(1 << VIRTIO_RING_F_INDIRECT_DESC);

	*VIRT_REG(VIRTIO_MMIO_DEVICE_FEATURES) = features;



	/* tell device that feature negotiation is complete. */

	status |= VIRTIO_CONFIG_S_FEATURES_OK;
	*VIRT_REG(VIRTIO_MMIO_STATUS) = status;



	if ((*VIRT_REG(VIRTIO_MMIO_STATUS) & VIRTIO_CONFIG_S_FEATURES_OK) == 0)
		panic("virtdisk_queue_not_ok");

	/* tell device we're completely ready. */

	status |= VIRTIO_CONFIG_S_DRIVER_OK;
	*VIRT_REG(VIRTIO_MMIO_STATUS) = status;



	if (!(*VIRT_REG(VIRTIO_MMIO_STATUS) & VIRTIO_CONFIG_S_DRIVER_OK))
		panic("virtdisk_queue_not_ok");

	*VIRT_REG(VIRTIO_MMIO_GUEST_PAGE_SIZE) = __PAGE_SIZE__;



	g_disk.pages = sys_alloc_ptr(2 * __PAGE_SIZE__, SYS_PROT_READ | SYS_PROT_WRITE);
	memset(g_disk.pages, 0, (2 * __PAGE_SIZE__));

	assert(g_disk.pages);

	*VIRT_REG(VIRTIO_MMIO_QUEUE_PFN) = ((*(uint32_t *)g_disk.pages) / __PAGE_SIZE__);



	*VIRT_REG(VIRTIO_MMIO_QUEUE_ALIGN) = __PAGE_SIZE__;



	*VIRT_REG(VIRTIO_MMIO_QUEUE_SEL) = 0;



	// desc = pages -- num * virtq_desc
	// avail = pages + 0x40 -- 2 * uint16_t, then num * uint16_t
	// used = pages + 4096 -- 2 * uint16_t, then num * vRingUsedElem

	g_disk.desc = (struct virtq_desc *)g_disk.pages;

	g_disk.avail = (struct virtq_avail *)(g_disk.pages + VIRTIO_NUM * sizeof(virtq_desc_t));
	g_disk.used = (struct virtq_used *)(g_disk.pages + __PAGE_SIZE__);

	*VIRT_REG(VIRTIO_MMIO_QUEUE_DESC_LOW) = *(uint32_t *)g_disk.desc;
	*VIRT_REG(VIRTIO_MMIO_QUEUE_DESC_HIGH) = 0;



	*VIRT_REG(VIRTIO_MMIO_QUEUE_AVAIL_LOW) = *(uint32_t *)g_disk.avail;
	*VIRT_REG(VIRTIO_MMIO_QUEUE_AVAIL_HIGH) = 0;



	*VIRT_REG(VIRTIO_MMIO_QUEUE_USED_LOW) = *(uint32_t *)g_disk.used;
	*VIRT_REG(VIRTIO_MMIO_QUEUE_USED_HIGH) = 0;

	// all VIRTIO_NUM descriptors start out unused.
	for (int i = 0; i < VIRTIO_NUM; i++)
		g_disk.free[i] = true;

	*VIRT_REG(VIRTIO_MMIO_QUEUE_READY) = 1;

	g_dev = sys_make_dev("/dev/vdk0", strlen("/dev/vdk0"), 2);

	assert(g_dev != null);

	g_dev->fn_list[VIRT_READ_INDEX].fn = virt_read_wrapper;
	g_dev->fn_list[VIRT_WRITE_INDEX].fn = virt_write_wrapper;
}

// find a free descriptor, mark it non-free, return its index.
static int
virt_alloc_desc(void)
{
	for (int i = 0; i < VIRTIO_NUM; i++)
	{
		if (g_disk.free[i])
		{
			g_disk.free[i] = 0;
			return i;
		}
	}

	return -1;
}

// mark a descriptor as free.
static void
virt_free_desc(int i)
{
	if (i >= VIRTIO_NUM)
		panic("[virtio] virt_free_desc, i >= VIRTIO_NUM");

	if (g_disk.free[i])
		panic("[virtio] virt_free_desc, is already free!");

	g_disk.desc[i].addr = 0;
	g_disk.desc[i].len = 0;
	g_disk.desc[i].flags = 0;
	g_disk.desc[i].next = 0;
	g_disk.free[i] = true;
}

// free a chain of descriptors.
static void __attribute__((unused))
virt_free_chain(int i)
{
	while (1)
	{
		int flag = g_disk.desc[i].flags;
		int nxt = g_disk.desc[i].next;

		virt_free_desc(i);

		if (flag & VRING_DESC_F_NEXT)
			i = nxt;
		else
			break;
	}
}

// allocate three descriptors (they need not be contiguous).
// disk transfers always use three descriptors.
static int __attribute__((unused))
virt_alloc3_desc(int *idx)
{
	for (int i = 0; i < 3; ++i)
	{
		idx[i] = virt_alloc_desc();

		if (idx[i] < 0)
		{
			for (int j = 0; j < i; ++j)
				virt_free_desc(idx[j]);

			return -1;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////

#define VIRT_CHECK_MAG 0x55ff

void virtio_disk_rw(struct virtio_blk* b, int write)
{
	uint64_t sector = b->blockno * (VIRT_BLK_SIZE / 512);

	g_disk.vdisk_lock = core_lock_acquire();

	// allocate the three descriptors.
	int32_t idx = virt_alloc_desc();

	// format the three descriptors.
	// qemu's virtio-blk.c reads them.

	virtio_blk_req_t* buf0 = &g_disk.ops[idx];

	if (write)
		buf0->type = VIRTIO_BLK_T_OUT; // write the disk
	else
		buf0->type = VIRTIO_BLK_T_IN; // read the disk

	buf0->reserved = 0;				  // The reserved portion is used to pad the header to 16 bytes and move the 32-bit sector field to the correct place.
	buf0->sector = sector;			  // specify the sector that we wanna modified.

	g_disk.desc[idx].addr = (uint64_t)buf0;
	g_disk.desc[idx].len = sizeof(struct virtio_blk_req);
	g_disk.desc[idx].flags = VRING_DESC_F_NEXT;

	int32_t idx2 = virt_alloc_desc();
	g_disk.desc[idx].next = idx2;


	g_disk.desc[idx2].addr = ((uint64_t)b->data) & 0xffffffff;
	g_disk.desc[idx2].len = VIRT_BLK_SIZE;

	if (!write)
		g_disk.desc[idx2].flags = 0; // device reads b->data
	else
		g_disk.desc[idx2].flags = VRING_DESC_F_WRITE; // device writes b->data

	g_disk.desc[idx2].flags |= VRING_DESC_F_NEXT;

	int32_t idx3 = virt_alloc_desc();
	g_disk.desc[idx2].next = idx3;

	g_disk.info[idx3].status = 0;
	g_disk.desc[idx3].addr = (uint64_t)&g_disk.info[idx].status;
	g_disk.desc[idx3].len = 1;
	g_disk.desc[idx3].flags = VRING_DESC_F_WRITE; // device writes the status
	g_disk.desc[idx3].next = 0;

	g_disk.info[idx].b = b;
	g_disk.info[idx].b->disk = VIRT_CHECK_MAG;

	// sys_sync_synchronize();

	// tell the device the first index in our chain of descriptors.
	g_disk.avail->ring[g_disk.avail->idx] = idx;



	// tell the device another avail ring entry is available.
	g_disk.avail->idx += 1; // not % VIRTIO_NUM ...



	*VIRT_REG(VIRTIO_MMIO_QUEUE_NOTIFY) = 0; // The device starts immediately when we write 0 to queue_notify.

	int64_t timeout = 10000;

	while (g_disk.info[idx].b->disk == VIRT_CHECK_MAG)
	{
		sys_sleep_for(1000);

		--timeout;

		if (timeout < 1)
			break;
	}

	g_disk.info[idx].b = nil;

	virt_free_desc(idx);
	virt_free_desc(idx2);
	virt_free_desc(idx3);

	core_lock_unlock(g_disk.vdisk_lock);
}

//////////////////////////////////////////////////////////////////////////////////////////////

static int virt_write_wrapper(pipe_t *pipe)
{
	assert(pipe);

	struct virtio_blk* blk = sys_alloc_ptr(sizeof(struct virtio_blk), SYS_PROT_READ | SYS_PROT_WRITE);

	assert(pipe->io_ptr);

	blk->blockno = *((virtio_lba_desc_t *)pipe->io_ptr);
	memncpy(blk->data, sys_get_buffer(pipe, true), VIRT_BLK_SIZE);

	virtio_disk_rw(blk, true);

	pipe->in->buf_cur += pipe->in->buf_size;

	sys_free_ptr(blk);

	return 0;
}

static int virt_read_wrapper(pipe_t *pipe)
{
	assert(pipe);

	struct virtio_blk* blk = sys_alloc_ptr(sizeof(struct virtio_blk), SYS_PROT_READ | SYS_PROT_WRITE);

	assert(pipe->io_ptr);

	blk->blockno = *((virtio_lba_desc_t *)pipe->io_ptr);
	memncpy(blk->data, sys_get_buffer(pipe, true), VIRT_BLK_SIZE);

	virtio_disk_rw(blk, false);

	pipe->in->buf_cur += pipe->in->buf_size;

	sys_free_ptr(blk);

	return 0;
}

// ----------------------------------------------------------------
// Function: virtio_disk_isr
// Purpose: ISR for virtio disk service
// ----------------------------------------------------------------

void virtio_disk_isr(void)
{
	/* notify for the next interrupt, by acknowlegding this one. */
	*VIRT_REG(VIRTIO_MMIO_INTERRUPT_ACK) = *VIRT_REG(VIRTIO_MMIO_INTERRUPT_STATUS) & 0x3;

	// the device increments g_disk.used->idx when it
	// adds an entry to the used ring.

	while (g_disk.used_idx != g_disk.used->idx)
	{
		// sys_sync_synchronize();

		int id = g_disk.used->ring[g_disk.used_idx % VIRTIO_NUM].id;

		if (g_disk.info[id].status != 0)
			panic("virtio_disk_intr_status notequal 0");

		struct virtio_blk *b = g_disk.info[id].b;

		b->disk = 0;
		g_disk.used_idx += 1;
	}
}
