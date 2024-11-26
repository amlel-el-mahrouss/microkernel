/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/sys.h>
#include <ubsan.h>

/* last rev 23/10/23 */
/* undefined behavior sanitizer */

struct ubsan_report
{
	struct ubsan_source_location location;
	struct ubsan_typedesc *type;
};

/* Verbose reporting. */
#define ubsan_print_report(DATA)\
	IOLogFormat("%s %s %n", "source:", DATA->location.file_name);\
	IOLogFormat("%s %s %n", "type:", DATA->type->type_name);\
	IOLogFormat("%s %i %n", "line:", DATA->location.line);



void __ubsan_advanced_report(voidptr_t _data)
{
	struct ubsan_report* data = _data;
	ubsan_print_report(data);

	switch (data->type->type_kind)
	{
	case sizeof(uint64_t):
		IOLog("typeof: uint64_t\r\n");
		break;
	case sizeof(uint32_t):
		IOLog("typeof: uint32_t\r\n");
		break;
	case sizeof(uint16_t):
		IOLog("typeof: uint16_t\r\n");
		break;
	case sizeof(uint8_t):
		IOLog("typeof: uint8_t\r\n");
		break;
	default:
		IOLog("typeof: ?\r\n");
		break;
	}
}

//
//	The following procedures each implement an ubsan handler.
//	Such as: type mismatch, pointer overflow, number overflow.
//

void __ubsan_handle_negate_overflow(struct ubsan_overflow_data *data,
				unsigned long lhs,
				unsigned long rhs)
{
	__ubsan_advanced_report(data);

#ifdef __KSTRICT__
	mpux_panic("[UBSAN]: __ubsan_handle_negate_overflow triggered! halting!\r\n");
#endif
}

void __ubsan_handle_type_mismatch_v1(struct ubsan_mismatch_data* data, uintptr_t ptr)
{
	__ubsan_advanced_report(data);

#ifdef __KSTRICT__
	mpux_panic("[UBSAN]: __ubsan_handle_negate_overflow triggered! halting!\r\n");
#endif
}

void __ubsan_handle_pointer_overflow(struct ubsan_overflow_data *data,
				unsigned long lhs,
				unsigned long rhs)
{
	__ubsan_advanced_report(data);

#ifdef __KSTRICT__
	mpux_panic("[UBSAN]: __ubsan_handle_pointer_overflow triggered! halting!\r\n");
#endif
}

void __ubsan_handle_add_overflow(struct ubsan_overflow_data *data,
				unsigned long lhs,
				unsigned long rhs)
{
	__ubsan_advanced_report(data);

#ifdef __KSTRICT__
	mpux_panic("[UBSAN]: __ubsan_handle_add_overflow triggered! halting!\r\n");
#endif
}

void __ubsan_handle_mul_overflow(struct ubsan_overflow_data *data,
                                 unsigned long lhs,
                                 unsigned long rhs)
{
    __ubsan_advanced_report(data);

#ifdef __KSTRICT__
    mpux_panic("[UBSAN]: __ubsan_handle_mul_overflow triggered! halting!\r\n");
#endif
}

void __ubsan_handle_divrem_overflow(struct ubsan_overflow_data *data,
                                    unsigned long lhs,
                                    unsigned long rhs)
{
    __ubsan_advanced_report(data);

#ifdef __KSTRICT__
    mpux_panic("[UBSAN]: __ubsan_advanced_report triggered! halting!\r\n");
#endif
}

void __ubsan_handle_out_of_bounds(struct ubsan_out_of_bounds_data *data,
				unsigned long index)
{
	__ubsan_advanced_report(data);

#ifdef __KSTRICT__
	mpux_panic("[UBSAN]: __ubsan_handle_out_of_bounds triggered! halting!\r\n");
#endif
}

void __ubsan_handle_shift_out_of_bounds(struct ubsan_shift_out_of_bounds_data *data,
					unsigned long lhs, unsigned long rhs)
{
	__ubsan_advanced_report(data);

#ifdef __KSTRICT__
	mpux_panic("[UBSAN]: __ubsan_handle_shift_out_of_bounds triggered! halting!\r\n");
#endif
}
