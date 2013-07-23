/* ---------------------------------------------------------------------- *
 * market.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */

int get_jobs (int x, int y, int jobs);
int put_jobs (int x, int y, int jobs);
int get_food (int x, int y, int food);
int put_food (int x, int y, int food);
int get_goods (int x, int y, int goods);
int put_goods (int x, int y, int goods);
int get_waste (int x, int y, int waste);
/*int put_waste (int x, int y, int waste);*/
int get_steel (int x, int y, int steel);
int put_steel (int x, int y, int steel);
int get_ore (int x, int y, int ore);
int put_ore (int x, int y, int ore);
int get_coal (int x, int y, int coal);
int put_coal (int x, int y, int coal);

int add_a_market (int x, int y);
void remove_a_market (int x, int y);
void do_market (int x, int y);

void mps_market(int x, int y);