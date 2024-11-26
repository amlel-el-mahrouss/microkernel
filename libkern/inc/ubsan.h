/*
 *	========================================================
 *
 *	MP MicroKernel
 *  Last Edited: 13/04/2023
 *
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <sys/sys.h>

struct ubsan_typedesc;
struct ubsan_source_location;
struct ubsan_overflow_data;
struct ubsan_mismatch_data;
struct ubsan_nonnull_arg_data;
struct ubsan_nonnull_return_data;
struct ubsan_vla_bound_data;
struct ubsan_out_of_bounds_data;
struct ubsan_shift_out_of_bounds_data;
struct ubsan_unreachable_data;
struct ubsan_invalid_value_data;

enum UBSAN_TYPE_KIND
{
	TYPE_KIND_INTEGER = 0,
	TYPE_KIND_FLOAT = 1,
	TYPE_UNKNOWN = 0xffff,
};

struct ubsan_typedesc
{
	uint16_t type_kind;
	uint16_t type_info;
	char type_name[1];
};

struct ubsan_source_location
{
	const char *file_name;
	union {
		unsigned long reported;
		struct {
			uint32_t line;
			uint32_t column;
		};
	};
};

struct ubsan_overflow_data
{
	struct ubsan_source_location location;
	struct ubsan_typedesc *type;
};

struct ubsan_mismatch_data
{
	struct ubsan_source_location location;
	struct ubsan_typedesc *type;
	unsigned long alignment;
	unsigned char type_check_kind;
};

struct ubsan_nonnull_arg_data
{
	struct ubsan_source_location location;
	struct ubsan_source_location attr_location;
	int arg_index;
};

struct ubsan_nonnull_return_data
{
	struct ubsan_source_location location;
	struct ubsan_source_location attr_location;
};

struct ubsan_vla_bound_data
{
	struct ubsan_source_location location;
	struct ubsan_typedesc *type;
};

struct ubsan_out_of_bounds_data
{
	struct ubsan_source_location location;
	struct ubsan_typedesc *array_type;
	struct ubsan_typedesc *index_type;
};

struct ubsan_shift_out_of_bounds_data
{
	struct ubsan_source_location location;
	struct ubsan_typedesc *lhs_type;
	struct ubsan_typedesc *rhs_type;
};

struct ubsan_unreachable_data
{
	struct ubsan_source_location location;
};

struct ubsan_invalid_value_data
{
	struct ubsan_source_location location;
	struct ubsan_typedesc *type;
};
