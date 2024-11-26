/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

.macro sys_reg_save BASE
	sd ra, 0(\BASE)
	sd sp, 8(\BASE)
	sd gp, 16(\BASE)
	sd tp, 24(\BASE)
	sd t0, 32(\BASE)
	sd t1, 40(\BASE)
	sd t2, 48(\BASE)
	sd s0, 56(\BASE)
	sd s1, 64(\BASE)
	sd a1, 72(\BASE)
	sd a2, 80(\BASE)
	sd a3, 88(\BASE)
	sd a4, 96(\BASE)
	sd a5, 104(\BASE)
	sd a6, 112(\BASE)
	sd a7, 116(\BASE)
	sd s2, 124(\BASE)
	sd s3, 132(\BASE)
	sd s4, 140(\BASE)
	sd s5, 148(\BASE)
	sd s6, 156(\BASE)
	sd s7, 164(\BASE)
	sd s8, 172(\BASE)
	sd s9, 180(\BASE)
	sd s10, 188(\BASE)
	sd s11, 196(\BASE)
	sd t3, 200(\BASE)
	sd t4, 208(\BASE)
	sd t5, 216(\BASE)
.endm

.macro sys_reg_load BASE
	ld ra, 0(\BASE)
	ld sp, 8(\BASE)
	ld gp, 16(\BASE)
	ld tp, 24(\BASE)
	ld t0, 32(\BASE)
	ld t1, 40(\BASE)
	ld t2, 48(\BASE)
	ld s0, 56(\BASE)
	ld s1, 64(\BASE)
	ld a1, 72(\BASE)
	ld a2, 80(\BASE)
	ld a3, 88(\BASE)
	ld a4, 96(\BASE)
	ld a5, 104(\BASE)
	ld a6, 112(\BASE)
	ld a7, 116(\BASE)
	ld s2, 124(\BASE)
	ld s3, 132(\BASE)
	ld s4, 140(\BASE)
	ld s5, 148(\BASE)
	ld s6, 156(\BASE)
	ld s7, 164(\BASE)
	ld s8, 172(\BASE)
	ld s9, 180(\BASE)
	ld s10, 188(\BASE)
	ld s11, 196(\BASE)
	ld t3, 200(\BASE)
	ld t4, 208(\BASE)
	ld t5, 216(\BASE)
.endm
