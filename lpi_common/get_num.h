#ifndef MDS_GET_NUM_H
#define MDS_GET_NUM_H

#define GN_NONNEG 1 /* Non negative number */
#define GN_GT_0 2 /* Greater than zero */

#define GN_ANY_BASE (1 << 10)
#define GN_BASE_8 (1 << 8) /* In Octal */
#define GN_BASE_16 (1 << 16) /* In hexadecimal */

long getLong(const char* arg, int flags, const char *name);

int getInt(const char* arg, int flags, const char *name);

#endif
