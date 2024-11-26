/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 10/11/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _NVM_EXPRESS_H
#define _NVM_EXPRESS_H

/* split the header in two. */

#include <nvm_express/_nvm_express.h>

/* status code types */
enum nvme_status_code_type
{
	NVME_SCT_GENERIC		= 0x0,
	NVME_SCT_COMMAND_SPECIFIC	= 0x1,
	NVME_SCT_MEDIA_ERROR		= 0x2,
	/* 0x3-0x6 - reserved */
	NVME_SCT_VENDOR_SPECIFIC	= 0x7,
};

/* generic command status codes */
enum nvme_generic_command_status_code {
	NVME_SC_SUCCESS				= 0x00,
	NVME_SC_INVALID_OPCODE			= 0x01,
	NVME_SC_INVALID_FIELD			= 0x02,
	NVME_SC_COMMAND_ID_CONFLICT		= 0x03,
	NVME_SC_DATA_TRANSFER_ERROR		= 0x04,
	NVME_SC_ABORTED_POWER_LOSS		= 0x05,
	NVME_SC_INTERNAL_DEVICE_ERROR		= 0x06,
	NVME_SC_ABORTED_BY_REQUEST		= 0x07,
	NVME_SC_ABORTED_SQ_DELETION		= 0x08,
	NVME_SC_ABORTED_FAILED_FUSED		= 0x09,
	NVME_SC_ABORTED_MISSING_FUSED		= 0x0a,
	NVME_SC_INVALID_NAMESPACE_OR_FORMAT	= 0x0b,
	NVME_SC_COMMAND_SEQUENCE_ERROR		= 0x0c,

	NVME_SC_LBA_OUT_OF_RANGE		= 0x80,
	NVME_SC_CAPACITY_EXCEEDED		= 0x81,
	NVME_SC_NAMESPACE_NOT_READY		= 0x82,
};

/* command specific status codes */
enum nvme_command_specific_status_code {
	NVME_SC_COMPLETION_QUEUE_INVALID	= 0x00,
	NVME_SC_INVALID_QUEUE_IDENTIFIER	= 0x01,
	NVME_SC_MAXIMUM_QUEUE_SIZE_EXCEEDED	= 0x02,
	NVME_SC_ABORT_COMMAND_LIMIT_EXCEEDED	= 0x03,
	/* 0x04 - reserved */
	NVME_SC_ASYNC_EVENT_REQUEST_LIMIT_EXCEEDED = 0x05,
	NVME_SC_INVALID_FIRMWARE_SLOT		= 0x06,
	NVME_SC_INVALID_FIRMWARE_IMAGE		= 0x07,
	NVME_SC_INVALID_INTERRUPT_VECTOR	= 0x08,
	NVME_SC_INVALID_LOG_PAGE		= 0x09,
	NVME_SC_INVALID_FORMAT			= 0x0a,
	NVME_SC_FIRMWARE_REQUIRES_RESET		= 0x0b,

	NVME_SC_CONFLICTING_ATTRIBUTES		= 0x80,
	NVME_SC_INVALID_PROTECTION_INFO		= 0x81,
	NVME_SC_ATTEMPTED_WRITE_TO_RO_PAGE	= 0x82,
};

/* media error status codes */
enum nvme_media_error_status_code {
	NVME_SC_WRITE_FAULTS			= 0x80,
	NVME_SC_UNRECOVERED_READ_ERROR		= 0x81,
	NVME_SC_GUARD_CHECK_ERROR		= 0x82,
	NVME_SC_APPLICATION_TAG_CHECK_ERROR	= 0x83,
	NVME_SC_REFERENCE_TAG_CHECK_ERROR	= 0x84,
	NVME_SC_COMPARE_FAILURE			= 0x85,
	NVME_SC_ACCESS_DENIED			= 0x86,
};

/* admin opcodes */
enum nvme_admin_opcode {
	NVME_OPC_DELETE_IO_SQ			= 0x00,
	NVME_OPC_CREATE_IO_SQ			= 0x01,
	NVME_OPC_GET_LOG_PAGE			= 0x02,
	/* 0x03 - reserved */
	NVME_OPC_DELETE_IO_CQ			= 0x04,
	NVME_OPC_CREATE_IO_CQ			= 0x05,
	NVME_OPC_IDENTIFY			= 0x06,
	/* 0x07 - reserved */
	NVME_OPC_ABORT				= 0x08,
	NVME_OPC_SET_FEATURES			= 0x09,
	NVME_OPC_GET_FEATURES			= 0x0a,
	/* 0x0b - reserved */
	NVME_OPC_ASYNC_EVENT_REQUEST		= 0x0c,
	/* 0x0d-0x0f - reserved */
	NVME_OPC_FIRMWARE_ACTIVATE		= 0x10,
	NVME_OPC_FIRMWARE_IMAGE_DOWNLOAD	= 0x11,

	NVME_OPC_FORMAT_NVM			= 0x80,
	NVME_OPC_SECURITY_SEND			= 0x81,
	NVME_OPC_SECURITY_RECEIVE		= 0x82,
};

/* nvme nvm opcodes */
enum nvme_nvm_opcode {
	NVME_OPC_FLUSH				= 0x00,
	NVME_OPC_WRITE				= 0x01,
	NVME_OPC_READ				= 0x02,
	/* 0x03 - reserved */
	NVME_OPC_WRITE_UNCORRECTABLE		= 0x04,
	NVME_OPC_COMPARE			= 0x05,
	/* 0x06-0x07 - reserved */
	NVME_OPC_DATASET_MANAGEMENT		= 0x09,
};

enum nvme_feature {
	/* 0x00 - reserved */
	NVME_FEAT_ARBITRATION			= 0x01,
	NVME_FEAT_POWER_MANAGEMENT		= 0x02,
	NVME_FEAT_LBA_RANGE_TYPE		= 0x03,
	NVME_FEAT_TEMPERATURE_THRESHOLD		= 0x04,
	NVME_FEAT_ERROR_RECOVERY		= 0x05,
	NVME_FEAT_VOLATILE_WRITE_CACHE		= 0x06,
	NVME_FEAT_NUMBER_OF_QUEUES		= 0x07,
	NVME_FEAT_INTERRUPT_COALESCING		= 0x08,
	NVME_FEAT_INTERRUPT_VECTOR_CONFIGURATION = 0x09,
	NVME_FEAT_WRITE_ATOMICITY		= 0x0A,
	NVME_FEAT_ASYNC_EVENT_CONFIGURATION	= 0x0B,
	/* 0x0C-0x7F - reserved */
	NVME_FEAT_SOFTWARE_PROGRESS_MARKER	= 0x80,
	/* 0x81-0xBF - command set specific (reserved) */
	/* 0xC0-0xFF - vendor specific */
};

enum nvme_dsm_attribute {
	NVME_DSM_ATTR_INTEGRAL_READ		= 0x1,
	NVME_DSM_ATTR_INTEGRAL_WRITE		= 0x2,
	NVME_DSM_ATTR_DEALLOCATE		= 0x4,
};

enum nvme_activate_action {
	NVME_AA_REPLACE_NO_ACTIVATE		= 0x0,
	NVME_AA_REPLACE_ACTIVATE		= 0x1,
	NVME_AA_ACTIVATE			= 0x2,
};

#define NVME_SERIAL_NUMBER_LENGTH	20
#define NVME_MODEL_NUMBER_LENGTH	40
#define NVME_FIRMWARE_REVISION_LENGTH	8

struct nvme_controller_data {

	/* bytes 0-255: controller capabilities and features */

	/** pci vendor id */
	uint16_t		vid;

	/** pci subsystem vendor id */
	uint16_t		ssvid;

	/** serial number */
	uint8_t			sn[NVME_SERIAL_NUMBER_LENGTH];

	/** model number */
	uint8_t			mn[NVME_MODEL_NUMBER_LENGTH];

	/** firmware revision */
	uint8_t			fr[NVME_FIRMWARE_REVISION_LENGTH];

	/** recommended arbitration burst */
	uint8_t			rab;

	/** ieee oui identifier */
	uint8_t			ieee[3];

	/** multi-interface capabilities */
	uint8_t			mic;

	/** maximum data transfer size */
	uint8_t			mdts;

	uint8_t			reserved1[178];

	/* bytes 256-511: admin command set attributes */

	/** optional admin command support */
	struct {
		/* supports security send/receive commands */
		uint16_t	security  : 1;

		/* supports format nvm command */
		uint16_t	format    : 1;

		/* supports firmware activate/download commands */
		uint16_t	firmware  : 1;

		uint16_t	oacs_rsvd : 13;
	} __attribute__((packed)) oacs;

	/** abort command limit */
	uint8_t			acl;

	/** asynchronous event request limit */
	uint8_t			aerl;

	/** firmware updates */
	struct {
		/* first slot is read-only */
		uint8_t		slot1_ro  : 1;

		/* number of firmware slots */
		uint8_t		num_slots : 3;

		uint8_t		frmw_rsvd : 4;
	} __attribute__((packed)) frmw;

	/** log page attributes */
	struct {
		/* per namespace smart/health log page */
		uint8_t		ns_smart : 1;

		uint8_t		lpa_rsvd : 7;
	} __attribute__((packed)) lpa;

	/** error log page entries */
	uint8_t			elpe;

	/** number of power states supported */
	uint8_t			npss;

	/** admin vendor specific command configuration */
	struct {
		/* admin vendor specific commands use spec format */
		uint8_t		spec_format : 1;

		uint8_t		avscc_rsvd  : 7;
	} __attribute__((packed)) avscc;

	uint8_t			reserved2[247];

	/* bytes 512-703: nvm command set attributes */

	/** submission queue entry size */
	struct {
		uint8_t		min : 4;
		uint8_t		max : 4;
	} __attribute__((packed)) sqes;

	/** completion queue entry size */
	struct {
		uint8_t		min : 4;
		uint8_t		max : 4;
	} __attribute__((packed)) cqes;

	uint8_t			reserved3[2];

	/** number of namespaces */
	uint32_t		nn;

	/** optional nvm command support */
	struct {
		uint16_t	compare : 1;
		uint16_t	write_unc : 1;
		uint16_t	dsm: 1;
		uint16_t	reserved: 13;
	} __attribute__((packed)) oncs;

	/** fused operation support */
	uint16_t		fuses;

	/** format nvm attributes */
	uint8_t			fna;

	/** volatile write cache */
	struct {
		uint8_t		present : 1;
		uint8_t		reserved : 7;
	} __attribute__((packed)) vwc;

	/* TODO: flesh out remaining nvm command set attributes */
	uint8_t			reserved4[178];

	/* bytes 704-2047: i/o command set attributes */
	uint8_t			reserved5[1344];

	/* bytes 2048-3071: power state descriptors */
	uint8_t			reserved6[1024];

	/* bytes 3072-4095: vendor specific */
	uint8_t			vs[1024];
} __attribute__((packed)) __attribute__((aligned(4)));

struct nvme_namespace_data {

	/** namespace size */
	uint64_t		nsze;

	/** namespace capacity */
	uint64_t		ncap;

	/** namespace utilization */
	uint64_t		nuse;

	/** namespace features */
	struct {
		/** thin provisioning */
		uint8_t		thin_prov : 1;
		uint8_t		reserved1 : 7;
	} __attribute__((packed)) nsfeat;

	/** number of lba formats */
	uint8_t			nlbaf;

	/** formatted lba size */
	struct {
		uint8_t		format    : 4;
		uint8_t		extended  : 1;
		uint8_t		reserved2 : 3;
	} __attribute__((packed)) flbas;

	/** metadata capabilities */
	struct {
		/* metadata can be transferred as part of data prp list */
		uint8_t		extended  : 1;

		/* metadata can be transferred with separate metadata pointer */
		uint8_t		pointer   : 1;

		uint8_t		reserved3 : 6;
	} __attribute__((packed)) mc;

	/** end-to-end data protection capabilities */
	struct {
		/* protection information type 1 */
		uint8_t		pit1     : 1;

		/* protection information type 2 */
		uint8_t		pit2     : 1;

		/* protection information type 3 */
		uint8_t		pit3     : 1;

		/* first eight bytes of metadata */
		uint8_t		md_start : 1;

		/* last eight bytes of metadata */
		uint8_t		md_end   : 1;
	} __attribute__((packed)) dpc;

	/** end-to-end data protection type settings */
	struct {
		/* protection information type */
		uint8_t		pit       : 3;

		/* 1 == protection info transferred at start of metadata */
		/* 0 == protection info transferred at end of metadata */
		uint8_t		md_start  : 1;

		uint8_t		reserved4 : 4;
	} __attribute__((packed)) dps;

	uint8_t			reserved5[98];

	/** lba format support */
	struct {
		/** metadata size */
		uint32_t	ms	  : 16;

		/** lba data size */
		uint32_t	lbads	  : 8;

		/** relative performance */
		uint32_t	rp	  : 2;

		uint32_t	reserved6 : 6;
	} __attribute__((packed)) lbaf[16];

	uint8_t			reserved6[192];

	uint8_t			vendor_specific[3712];
} __attribute__((packed)) __attribute__((aligned(4)));

enum nvme_log_page {

	/* 0x00 - reserved */
	NVME_LOG_ERROR			= 0x01,
	NVME_LOG_HEALTH_INFORMATION	= 0x02,
	NVME_LOG_FIRMWARE_SLOT		= 0x03,
	/* 0x04-0x7F - reserved */
	/* 0x80-0xBF - I/O command set specific */
	/* 0xC0-0xFF - vendor specific */
};

struct nvme_error_information_entry {

	uint64_t		error_count;
	uint16_t		sqid;
	uint16_t		cid;
	struct nvme_status	status;
	uint16_t		error_location;
	uint64_t		lba;
	uint32_t		nsid;
	uint8_t			vendor_specific;
	uint8_t			reserved[35];
} __attribute__((packed)) __attribute__((aligned(4)));

union nvme_critical_warning_state {

	uint8_t		raw;

	struct {
		uint8_t	available_spare		: 1;
		uint8_t	temperature		: 1;
		uint8_t	device_reliability	: 1;
		uint8_t	read_only		: 1;
		uint8_t	volatile_memory_backup	: 1;
		uint8_t	reserved		: 3;
	} __attribute__((packed)) bits;
} __attribute__((packed));

struct nvme_health_information_page {

	union nvme_critical_warning_state	critical_warning;

	uint16_t		temperature;
	uint8_t			available_spare;
	uint8_t			available_spare_threshold;
	uint8_t			percentage_used;

	uint8_t			reserved[26];

	/*
	 * Note that the following are 128-bit values, but are
	 *  defined as an array of 2 64-bit values.
	 */
	/* Data Units Read is always in 512-byte units. */
	uint64_t		data_units_read[2];
	/* Data Units Written is always in 512-byte units. */
	uint64_t		data_units_written[2];
	/* For NVM command set, this includes Compare commands. */
	uint64_t		host_read_commands[2];
	uint64_t		host_write_commands[2];
	/* Controller Busy Time is reported in minutes. */
	uint64_t		controller_busy_time[2];
	uint64_t		power_cycles[2];
	uint64_t		power_on_hours[2];
	uint64_t		unsafe_shutdowns[2];
	uint64_t		media_errors[2];
	uint64_t		num_error_info_log_entries[2];

	uint8_t			reserved2[320];
} __attribute__((packed)) __attribute__((aligned(4)));

struct nvme_firmware_page {

	struct {
		uint8_t	slot		: 3; /* slot for current FW */
		uint8_t	reserved	: 5;
	} __attribute__((packed)) afi;

	uint8_t			reserved[7];
	uint64_t		revision[7]; /* revisions for 7 slots */
	uint8_t			reserved2[448];
} __attribute__((packed)) __attribute__((aligned(4)));

#define NVME_TEST_MAX_THREADS	128

struct nvme_io_test {

	enum nvme_nvm_opcode	opc;
	uint32_t		size;
	uint32_t		time;	/* in seconds */
	uint32_t		num_threads;
	uint32_t		flags;
	uint64_t		io_completed[NVME_TEST_MAX_THREADS];
};

enum nvme_io_test_flags {

	/*
	 * Specifies whether dev_refthread/dev_relthread should be
	 *  called during NVME_BIO_TEST.  Ignored for other test
	 *  types.
	 */
	NVME_TEST_FLAG_REFTHREAD =	0x1,
};

struct nvme_pt_command {

	/*
	 * cmd is used to specify a passthrough command to a controller or
	 *  namespace.
	 *
	 * The following fields from cmd may be specified by the caller:
	 *	* opc  (opcode)
	 *	* nsid (namespace id) - for admin commands only
	 *	* cdw10-cdw15
	 *
	 * Remaining fields must be set to 0 by the caller.
	 */
	struct nvme_command	cmd;

	/*
	 * cpl returns completion status for the passthrough command
	 *  specified by cmd.
	 *
	 * The following fields will be filled out by the driver, for
	 *  consumption by the caller:
	 *	* cdw0
	 *	* status (except for phase)
	 *
	 * Remaining fields will be set to 0 by the driver.
	 */
	struct nvme_completion	cpl;

	/* buf is the data buffer associated with this passthrough command. */
	void *			buf;

	/*
	 * len is the length of the data buffer associated with this
	 *  passthrough command.
	 */
	uint32_t		len;

	/*
	 * is_read = 1 if the passthrough command will read data into the
	 *  supplied buffer from the controller.
	 *
	 * is_read = 0 if the passthrough command will write data from the
	 *  supplied buffer to the controller.
	 */
	uint32_t		is_read;

	/*
	 * driver_lock is used by the driver only.  It must be set to 0
	 *  by the caller.
	 */
	struct mtx *		driver_lock;
};

#define nvme_completion_is_error(cpl)					\
	((cpl)->status.sc != 0 || (cpl)->status.sct != 0)



#endif /* ifndef _NVM_EXPRESS_H */
