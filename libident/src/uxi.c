/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

/* Software Distribution Identification string */
#include <uxi.h>

#include <config.h>
#include <string.h>

const char* uxistr(uxi_t uxi, const char* seed)
{
  	char* bytes = uxi_alloc(sizeof(char) * strlen(seed));
  	if (!bytes) return null;

  	for (size_t i = 0; i < strlen(seed); ++i)
	{
    	if ((uxi & seed[i]) == seed[i])
		{
      		bytes[i] = seed[i];
    	}
		else
		{
      		bytes[i] = '?';
    	}
  	}

  	return bytes;
}

uxi_t struxi(const char* str)
{
  	if (!str) return -1;
  	if (*str == 0) return -1;

  	uxi_t ident = 0;

  	for (size_t i = 0; i < strlen(str); ++i)
	{
    	ident |= str[i];
  	}

  	return ident;
}
