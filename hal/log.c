/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/log.h>
#include <hw/mmu.h>
#include <sys/sys.h>
#include <hw/uart.h>

#define FMT_NEW '%'
#define FMT_NEWLINE 'n'
#define FMT_TABULATE 't'
#define FMT_FLOAT 'f'
#define FMT_STRING 's'
#define FMT_CHAR 'c'
#define FMT_INT 'i'
#define FMT_BOOLEAN 'b'
#define FMT_HEX 'x'

__COPYRIGHT("$kernel$");

///////////////////////////////////////////////////////////////////////

// @brief printf implementation.

///////////////////////////////////////////////////////////////////////

static const char g_numbers[16] = "0123456789abcdef";

/* We still need these symbols */
#ifndef __x86_64__

/* No initialization needed */
void init_io(void) {}

void sys_print_str(char* label)
{
    if (label == null ||
        *label == 0)
        return;

    sys_putstr(label);
}

#endif

static bool sys_runtime_check_number(size_t c)
{
    return c != ~0;
}

void sys_print_int(int64_t x)
{
    int y = x / 10;
    int d = x % 10;

    if (y) sys_print_int(y);

    /* same as below but for base-10 */
    if (d > 10)
    {
        sys_print_str("?");
        return;
    }

	if (d < 0)
		d = -d;

    char num[2];

	num[0] = g_numbers[d];
    num[1] = '\0';

    sys_print_str(num);
}

void sys_print_hex(size_t x)
{
    int y = x / 16;
    int h = x % 16;

    if (y) sys_print_hex(y);

    /* fail if the hex number is not base-16 */
    if (h > 15)
	{
        sys_print_str("?");
        return;
    }

	if (y < 0)
		y = -y;

    char num[2];

    num[0] = g_numbers[h];
    num[1] = '\0';

    sys_print_str(num);
}

void sys_print_float(float x)
{
	float_cast_t num_x = { .f = x };

	sys_print_format("%s%i.%i", num_x.sign ? "-" : " ", num_x.exponent, num_x.mantisa);
}

bool g_is_processing = false;

size_t sys_print_format(char* fmt, ...)
{
#ifdef __KERNEL
    if (g_is_processing)
        return 0;

    g_is_processing = true;
    va_list ap;

    bool fmt_enabled = false;
    size_t size = 0UL;

    va_start(ap, fmt);

    while (fmt[size] != '\0')
    {
        switch (fmt[size])
        {
            case FMT_BOOLEAN:
            {
                if (!fmt_enabled) goto putc;

                sys_print_str(va_arg(ap, int) > 0 ? "yes\r\n" : "no\r\n");
                fmt_enabled = false;
                break;
            }
			case FMT_FLOAT:
			{
                if (!fmt_enabled) goto putc;
                float arg = va_arg(ap, double);

                sys_print_float(arg);

                fmt_enabled = false;
				break;
			}
            case FMT_HEX:
            {
                if (!fmt_enabled) goto putc;
                size_t arg = va_arg(ap, size_t);

                if (!sys_runtime_check_number(arg))
                    break;

                sys_print_str("0x");
                sys_print_hex(arg);

                fmt_enabled = false;
                break;
            }
            case FMT_INT:
            {
                if (!fmt_enabled) goto putc;
                int num = va_arg(ap, int);

                if (!sys_runtime_check_number(num))
                    break;

				if (num < 0)
					sys_print_str("-");

                sys_print_int(num);

                fmt_enabled = false;
                break;
            }
            case FMT_TABULATE:
            {
                if (!fmt_enabled) goto putc;

                sys_print_str("\t");

                fmt_enabled = false;
                break;
            }
            case FMT_NEWLINE:
            {
                if (!fmt_enabled) goto putc;

                sys_print_str("\r\n");

                fmt_enabled = false;
                break;
            }
            case FMT_STRING:
            {
                if (!fmt_enabled) goto putc;

                sys_print_str(va_arg(ap, char*));

                fmt_enabled = false;
                break;
            }
            case FMT_NEW:
            {
                fmt_enabled = true;
                break;
            }
            case FMT_CHAR:
			{
                if (!fmt_enabled) goto putc;

                char chr = (char)va_arg(ap, int);
                sys_putc(chr);
                break;
			}
            default:
            putc:
			{
				if (fmt_enabled)
					fmt_enabled = false;

                sys_putc(fmt[size]);
                break;
			}
        }

        ++size;
    }
    va_end(ap);

    g_is_processing = false;
    return size;
#else
    return 0;
#endif // ifdef __KERNEL
}
