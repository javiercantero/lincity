#ifndef LINCITY_BOOLEAN_H
#define LINCITY_BOOLEAN_H

/*
 * boolean definitions
 */

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#if defined(__STDC__) && __STDC_VERSION__ >= 199901L
#include <stdbool.h> /* C99 */
#else
typedef enum { false, true } bool; /* C99 compatible */
#endif

#endif /* LINCITY_BOOLEAN_H */
