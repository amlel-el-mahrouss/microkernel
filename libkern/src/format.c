
/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/cstr.h>
#include <sys/format.h>
#include <string.h>

__COPYRIGHT("$kernel$");

static const char g_numbers[16] = "0123456789abcdef";

static char* sys_format_number(int64_t x, int base, char* ptr, size_t* cur)
{
    int y = x / 10;
    int d = x % 10;

    size_t _cur = 0UL;

    if (y) sys_format_number(y, base, ptr, *cur > 0 ? cur : &_cur);

    /* same as below but for base-10 */
    if (d > base)
    {
        return "?";
    }

	if (d < 0)
		d = -d;

	ptr[*cur] = *cur < 32 ? g_numbers[d] : '\0';
    ++*cur;

    return ptr;
}

#define sys_format_number_dec(n, s, cnt) sys_format_number(n, 10, s, cnt)
#define sys_format_number_hex(n, s, cnt) sys_format_number(n, 16, s, cnt)

size_t sys_fmt_string(char out[], size_t max_len, const char* fmt, ...)
{
    size_t idx = 0UL;
    bool enable = false;

    const size_t str_len = strnlen(out, max_len);
    size_t str_cur = 0UL;

    va_list ap;
    va_start(ap, fmt);

    while (fmt[idx] != 0)
    {
        if (str_cur > str_len)
            break;

        switch (fmt[idx])
        {
        case '%':
            enable = true;
            break;

        case '@':
        {
            if (enable)
            {
                struct cstr* cstr = va_arg(ap, struct cstr*);

                for (size_t i = 0; i < cstr->s_length; ++i)
                {
                    if (cstr->s_buffer[i] == 0)
                        break;

                    out[i] = cstr->s_buffer[i];
                    ++str_cur;
                }

                enable = false;
            }

            break;
        }
        case 'i':
        {
            if (enable)
            {
                char cstr[32];
                size_t cnt = 0;

                sys_format_number_hex(va_arg(ap, uint64_t), cstr, &cnt);

                for (size_t i = 0; i < strlen(cstr); ++i)
                {
                    out[str_cur] = cstr[i];
                    ++str_cur;
                }

                enable = false;
            }

            break;
        }
        case 's':
        {
            if (enable)
            {
                const char* cstr = va_arg(ap, const char*);

                for (size_t i = 0; i < strlen(cstr); ++i)
                {
                    out[str_cur] = cstr[i];
                    ++str_cur;
                }

                enable = false;
            }

            break;
        }
        default:
        {
            out[str_cur] = fmt[str_cur];
            ++str_cur;
            break;
        }
        }


        ++idx;
    }

    out[str_cur] = 0;

    va_end(ap);

    return idx;
}
