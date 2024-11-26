#include <oseek.h>

lba_t oseek(lba_t source, lba_t reach, lba_t amount)
{
    lba_t sum = (source + amount);
    
    if (sum > reach)
    {
        errno = EACCES;
        return -1; // you should look at the errno now.
    }

    return sum;
}