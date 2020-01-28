#include "libc-lock.h"
#include <sys/types.h>

struct dirstream {
    int fd;      /* File descriptor.  */
    __libc_lock_define0 (lock); /* Mutex lock for this structure.  */
    size_t allocation;                /* Space allocated for the block.  */
    size_t size;                /* Total valid data in the block.  */
    size_t offset;                /* Current offset into the block.  */
    off_t filepos;                /* Position of next entry to read.  */
    int errcode;                /* Delayed error code.  */
    /* Directory block.  We must make sure that this block starts
       at an address that is aligned adequately enough to store
       dirent entries.  Using the alignment of "void *" is not
       sufficient because dirents on 32-bit platforms can require
       64-bit alignment.  We use "long double" here to be consistent
       with what malloc uses.  */
    char data[0] __attribute__ ((aligned (__alignof__ (long double))));
};
