/* ---------------------------------------------------------------------- *
 * engine.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */
#ifndef __engine_h__
#define __engine_h__

int place_item (int x, int y, short type);
int bulldoze_item (int x, int y);
void do_coal_survey (void);
void do_bulldoze_area (short fill, int xx, int yy);
void connect_rivers (void);
int adjust_money(int value);
void connect_transport (int originx, int originy, int w, int h);

void init_mappoint_array (void);
void shuffle_mappoint_array (void);
void set_mappoint (int x, int y, short selected_type);
void set_mappoint_used (int fromx, int fromy, int x, int y);

int buy_food (int xt, int yt);
/*int buy_jobs (int, int);*/
int buy_coal (int xt, int yt);
int buy_ore (int xt, int yt);
int buy_goods (int xt, int yt);
int buy_steel (int xt, int yt);
int sell_food (int xt, int yt);
/*int sell_jobs (int, int);*/
int sell_coal (int xt, int yt);
int sell_ore (int xt, int yt);
int sell_goods (int xt, int yt);
int sell_steel (int xt, int yt);

void do_pollution ();
void remove_people (int num);
void clear_fire_health_and_cricket_cover (void);
void do_fire_health_and_cricket_cover (void);
void do_random_fire (int x, int y, int pwarning);
int spiral_find_group (int startx, int starty, int group);
int spiral_find_2x2 (int startx, int starty);
void update_tech_dep (int x, int y);


#endif	/* __engine_h__ */
