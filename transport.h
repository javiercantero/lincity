/* ---------------------------------------------------------------------- *
 * transport.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */

#ifndef __TRANSPORT_H__
#define __TRANSPORT_H__

#include "lin-city.h" /* Map_Point_Info dependency */


void general_transport (Map_Point_Info *minfo, int *pol,
                        int max_waste, int *waste_count);


#endif
