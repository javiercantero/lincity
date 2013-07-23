/* ---------------------------------------------------------------------- *
 * ldsvguts.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */
#ifndef __ldsvguts_h__
#define __ldsvguts_h__

void remove_scene (char *cname);

void load_saved_city (char *s);
void sanity_check (void);

void load_city (char *cname);
void save_city (char *cname);

#endif	/* __ldsvguts_h__ */
