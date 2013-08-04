/* ---------------------------------------------------------------------- *
 * parkland.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * (c) Corey Keasling, 2004
 * ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------- */

/* module header file */
#include "parkland.h"

/* system libraries */

/* app general headers */
#include "lin-city.h"
#include "lctypes.h"

/* other modules */
#include "cliglobs.h"
#include "stats.h"
#include "engglobs.h"

/* ----------------------------------------------------------------- */

void
do_parkland (int x, int y)
{
  if (MP_POL(x,y) > 10 && (world->time.total & 1) == 0)
    MP_POL(x,y) -= 1;
}
