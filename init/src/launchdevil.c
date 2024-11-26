/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <cpu.h>
#include <escape_codes.h>
#include <launchdevil.h>
#include <kernel.h>
#include <string.h>
#include <envvar.h>
#include <hw/pci_express.h>
#include <hw/mmap.h>
#include <sys/format.h>
#include <sys/user.h>
#include <sys/info.h>
#include <strerror.h>
#include <sys/utils.h>
#include <sys/errno.h>
#include <sys/timer.h>
#include <sys/malloc.h>
#include <machine/exec.h>
#include <sched/sched.h>
#include <hw/pci.h>
#include <procfs/procfs.h>
#include <ffs_2/disklabel.h>
#include <virt_disk/virt_disk.h>
#include <builtin/uptime/uptime.h>

/*
 * launchdevil is a process which is called when the kernel is loaded into memory
 * It has commands such as clear, sysinfo, uname, exit and whoami.
 */

__COPYRIGHT("$kernel$");

extern int64_t __sys_hart_present;

// kernel shell context
struct launchd_term g_launchdevil = { .name = "launchdevil", .buffer = { 0 }, .cursor_x = 0, .cursor_y = 0 };

// ----------------------------------------------------------------//
// Function: launchdevil_main                                            //
// Purpose: launchdevil shell                                      //
// ----------------------------------------------------------------//

int launchdevil_main(int argc, char** argv, char** envp, int envp_count)
{
    sys_print_format("\033[2J"); /* Clear screen */
    sys_print_format("\033[%i;%iH", g_launchdevil.cursor_x, g_launchdevil.cursor_y); /*  set cursor_x to 0:0 */

    /* main serial sell loop */

    while (true)
    {
        sys_print_format("\nok # "); // TODO: domain name
        int backspace_cnter = 0;

		utf32_char_t ch = 0U;

        while (true) // if not = to enter
        {
            ch = uart_get_char();

            /* check for \n or \r or \r\n */
            if (ch == '\n' ||
                ch == '\r')
                break;

            /* check for line break */
            if (ch == 0x007F ||
                ch == 0x08) // DEL
            {
                if (g_launchdevil.cursor_x < 1)
                    continue;

                sys_print_format("\x1B[%iD", 1);
                sys_print_format(" ");
                sys_print_format("\x1B[%iD", 1);

                --g_launchdevil.cursor_x;
                g_launchdevil.buffer[g_launchdevil.cursor_x] = ' ';

                ++backspace_cnter;
                continue;
            }

            uart_put_char(ch);
            g_launchdevil.buffer[g_launchdevil.cursor_x] = ch;

            if (g_launchdevil.cursor_x > 1024)
                break;

            ++g_launchdevil.cursor_x;
        }

        g_launchdevil.buffer[g_launchdevil.cursor_x] = 0;
        g_launchdevil.cursor_x = 0UL;

        // we use register for faster lookup, we also store strlen's result, so we don't have to recall the procedure
        // each time.

        register size_t len = strlen(g_launchdevil.buffer);

        // if there is input.
        // g_launchdevil is assumed to be null terminated.

        if (len > 0)
        {
            if (strncmp("echo ", g_launchdevil.buffer, strlen("echo ")) == 0)
            {
                const char* ptr = g_launchdevil.buffer + strlen("echo ");

                sys_print_format("\n");

                if (ptr[0] != '\'')
                    continue;

                ++ptr; /* pass the the first quote to prevent collision with condition. */

                for (size_t i = 0UL; ptr[i] != 0; ++i)
                {
                    if (ptr[i] == ';' ||
                        ptr[i] == '\'')
                        break;

                    sys_print_format("%c", ptr[i]);
                }
            }

            if (len == strlen("dinfo") &&
                strncmp("dinfo", g_launchdevil.buffer, strlen("dinfo")) == 0)
            {
                sys_print_format("\n%s", g_launchdevil.name);
            }

            if (len == strlen("uptime") &&
                strncmp("uptime", g_launchdevil.buffer, strlen("uptime")) == 0)
            {
                struct _mpux_time tim = hw_uptime_fetch();

                sys_print_format("\nuptime: %i", tim.epoch_time);
            }

            if (len == strlen("clear") && strncmp("clear", g_launchdevil.buffer, strlen("clear")) == 0)
            {
                sys_print_format("\x1b[2J");
                sys_print_format("\033[0;0H");
            }

            if (len == strlen("whoami") &&
                strncmp("whoami", g_launchdevil.buffer, strlen("whoami")) == 0)
            {
                sys_print_format("\n%s", sys_get_user_name());
            }

            if (len == strlen("exit") &&
                strncmp("exit", g_launchdevil.buffer, strlen("exit")) == 0)
            {
                sys_request_poweroff();
            }

            if (len == strlen("poweroff") &&
                strncmp("poweroff", g_launchdevil.buffer, strlen("poweroff")) == 0)
            {

                sys_print_format("\n[%s] shutdown requested by user: %s\n", g_launchdevil.name, sys_get_user_name());
                sys_request_poweroff();
            }

            if (len == strlen("reboot") && strncmp("reboot", g_launchdevil.buffer, strlen("reboot")) == 0)
            {
                sys_print_format("\n[%s] reboot requested by user: %s\n", g_launchdevil.name, sys_get_user_name());
                sys_request_reboot();
            }

            if (len == strlen("cpu") && strncmp("cpu", g_launchdevil.buffer, strlen("cpu")) == 0)
            {
                sys_print_format("\n> Arch: %s\n", __arch__);
                sys_print_format("> Cores: %i\n", __sys_hart_present);

                if (__sys_hart_present > 0)
                {
                    sys_print_format("> Multi Processing is ON.");
                }
                else
                {
                    sys_print_format("> Multi Processing is OFF.");
                }
            }

            if (len == strlen("uname") && strncmp("uname", g_launchdevil.buffer, strlen("uname")) == 0)
            {
                struct sys_diag_info name;
                sys_get_info(&name);

                sys_print_format("\r\n%s, %s, %s", name.sysname, __DATE__, __arch__);
            }

            if (len == strlen("sysinfo") && strncmp("sysinfo", g_launchdevil.buffer, strlen("sysinfo")) == 0)
            {
                struct sys_diag_info name;
                sys_get_info(&name);

                struct sys_mem_info info;
                sys_get_mem_info(&info);

                sys_print_format("\n> Kernel: %s \n> Network: %s \n> Release: %s \n> Version: %s \n> Arch: %s \n",
                                 name.sysname, name.nodename, name.release, name.version, name.machine);
                sys_print_format("> Init: %s\n", g_launchdevil.name);

                sys_print_format("> Used kernel heap: %i KiB\n> Total kernel heap: %i GiB", info.heap_size / KIB, info.heap_left / GIB);
            }
        }

        memset(g_launchdevil.buffer, 0, LD_MAX_BUF);
        ++g_launchdevil.cursor_y;
    }

    mpux_no_reach();
}
