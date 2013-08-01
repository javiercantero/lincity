/* ---------------------------------------------------------------------- *
 * substation.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * (c) Corey Keasling, 2004
 * ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------- */

/* module header file */
#include "substation.h"

/* system libraries */
#include <stdio.h> /* printf() */

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
#include "power.h"
#include "lclib.h"

/* ----------------------------------------------------------------- */


/*** Substations ***/
/*
  int_5 is the power demand at this substation
  int_6 is the grid its connected to
  int_7 is a grid timestamp
*/

void 
do_power_substation (int x, int y) 
{
    switch(grid[MP_INFO(x,y).int_6]->powered) {
    case -1: {
	MP_TYPE(x,y) = CST_SUBSTATION_R; 
    } break;
    case 0 : {
	MP_TYPE(x,y) = CST_SUBSTATION_RG;
    } break;
    case 1 : {
	MP_TYPE(x,y) = CST_SUBSTATION_G;
    } break;
    default : {
	printf("Default case in do_power_substation\n");
    } break;
    }
}

int add_a_substation (int x, int y)	/* add to substations list */
{
    if (numof_substations >= MAX_NUMOF_SUBSTATIONS)
        return 0;

    substations[numof_substations].x = x;
    substations[numof_substations].y = y;
    numof_substations++;
    return 1;
}

void remove_a_substation (int x, int y)
{
    unsigned int i;

    /* search for coordinate of the substation */
    for (i = 0; i < numof_substations; i++)
    {
        if (substations[i].x == x && substations[i].y == y)
            break;
    }

    /* shift left the rest of the array */
    for (; i < numof_substations; i++)
    {
        substations[i] = substations[i + 1];
    }
    numof_substations--; /* FIXME: this always decrement the counter, not when found it */
}

#if 0 /* TODO: not in use */
void shuffle_substations (void)
{
    unsigned int num_swaps;
    unsigned int random_pos;
    Map_Coord tmp;
    unsigned int i;

    num_swaps = (numof_substations / 2) + 1;
    for (i = 0; i < num_swaps; i++)
    {
        random_pos = rand() % numof_substations;
        if (random_pos == i)
            continue;

        /* swap values */
        tmp = substations[i];
        substations[i] = substations[random_pos];
        substations[random_pos] = tmp;
    }
}
#endif

void
mps_substation (int x, int y)
{
    int i = 0;
    char s[12];
    
    mps_store_title(i++,_("Substation"));
    i++;

    format_power (s, sizeof(s), MP_INFO(x,y).int_5);    
    mps_store_title(i++,_("Local Demand"));
    mps_store_title(i++,s);

    if (MP_INFO(x,y).int_6 == 0)
      return;

    i++;
    mps_store_title(i++,_("Grid Status"));

    format_power (s, sizeof(s), grid[MP_INFO(x,y).int_6]->max_power);
    mps_store_ss(i++,_("T. Cap."), s);

    format_power (s, sizeof(s), grid[MP_INFO(x,y).int_6]->avail_power);
    mps_store_ss(i++,_("A. Cap."), s);
    
    format_power (s, sizeof(s), grid[MP_INFO(x,y).int_6]->demand);
    mps_store_ss(i++,_("Demand"), s);
    i++;

    mps_store_sd(i++,_("Grid ID"), MP_INFO(x,y).int_6);


}
