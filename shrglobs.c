/* ---------------------------------------------------------------------- *
 * engglobs.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------- */

/* module header file */
#include "engglobs.h"

/* system libraries */

/* app general headers */
#include "common.h"

/* other modules */
#include "fileutil.h"

/* ----------------------------------------------------------------- */

Map map;

Map_Coord mappoint_array[WORLD_SIDE_LEN];
int numof_shanties;
int numof_communes;
Map_Coord last_built;
int main_screen_originx, main_screen_originy;

int pix_double = 0;

#if defined (WIN32)
char windowsfontfile[LC_PATH_MAX];
#endif

int cheat_flag;
int modern_windmill_flag = 0;

int askdir_lines;
char *askdir_path[4];

int monthgraph_size = 0;
int *monthgraph_pop;
int *monthgraph_starve;
int *monthgraph_nojobs;
int *monthgraph_ppool;

#if defined (commentout)
int monthgraph_pop[MAPPOINT_STATS_W], monthgraph_starve[MAPPOINT_STATS_W];
int monthgraph_nojobs[MAPPOINT_STATS_W], monthgraph_ppool[MAPPOINT_STATS_W];
#endif

#if defined (commentout)
int diffgraph_power[MAPPOINT_STATS_W], diffgraph_coal[MAPPOINT_STATS_W];
int diffgraph_goods[MAPPOINT_STATS_W], diffgraph_ore[MAPPOINT_STATS_W];
int diffgraph_population[MAPPOINT_STATS_W];
int diff_old_population;
#endif

World_State world_state;
World_State* world = &world_state;

Map_Coord substations[MAX_NUMOF_SUBSTATIONS];
unsigned int numof_substations = 0;
Map_Coord markets[MAX_NUMOF_MARKETS];
unsigned int numof_markets = 0;
/*int numof_health_centres; */

/*int selected_type_cost;*/


void world_init( World_State* world )
{
    world->time.total = 0;

    world->money.total = 0;

    world->population.highest = 0;
    world->population.births = 0;
    world->population.evacuated = 0;

    world->population.deaths.pollution.total = 0;
    world->population.deaths.pollution.history = 0.0;
    world->population.deaths.starve.total = 0;
    world->population.deaths.starve.history = 0.0;

    world->population.unemployment.days = 0;
    world->population.unemployment.years = 0;
    world->population.unemployment.history = 0.0;

    world->sustain.flag = false;

    world->sustain.ore_coal_tip.flag = false;
    world->sustain.ore_coal_tip.count = 0;

    world->sustain.port.flag = false;
    world->sustain.port.count = 0;

    world->sustain.money.previous = 0;
    world->sustain.money.count = 0;

    world->sustain.population.previous = 0;
    world->sustain.population.count = 0;

    world->sustain.tech.previous = 0;
    world->sustain.tech.count = 0;

    world->sustain.fire.count = 0;
}
