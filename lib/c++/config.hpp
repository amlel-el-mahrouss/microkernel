/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 18/01/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#define COPY_DELETE(KLASS)\
KLASS& operator=(const KLASS&) = delete;\
KLASS(const KLASS&) = delete;\



#define COPY_DEFAULT(KLASS)\
KLASS& operator=(const KLASS&) = default;\
KLASS(const KLASS&) = default;\



// eof
