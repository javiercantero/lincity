/* ---------------------------------------------------------------------- *
 * water.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * (c) Corey Keasling, 2004
 * ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------- */

/* module header file */
#include "water.h"

/* system libraries */

/* app general headers */
#include "lcconfig.h"
#include "lin-city.h"
#include "lctypes.h"
#include "lcintl.h"

/* other modules */
#include "cliglobs.h"
#include "mps.h"
#include "stats.h"
#include "engglobs.h"

/* ----------------------------------------------------------------- */


void
mps_water (int x, int y)
{
    int i = 0;

    char * p;

    mps_store_title(i++,_("Water"));
    i++;

    p = (MP_INFO(x,y).flags & FLAG_IS_RIVER) ? _("Yes") : _("No");
    mps_store_ss(i++,_("Navigable"),p);
      
}
