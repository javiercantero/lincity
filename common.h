/* ---------------------------------------------------------------------- *
 * common.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */
#ifndef __common_h__
#define __common_h__

#ifdef LC_X11
#include "lcx11.h"

#elif defined WIN32
#include "lcwin32.h"

#elif defined SVGALIB
#include "lcsvga.h"

#endif

#endif	/* __common_h__ */
