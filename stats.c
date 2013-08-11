/* ---------------------------------------------------------------------- *
 * ldsvguts.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2002.
 * Portions copyright (c) Corey Keasling, 2000-2002.
 * ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------- */

/* module header file */
#include "stats.h"

/* system libraries */
#include <stdio.h>
#include <stdlib.h>

/* app general headers */
#include "lcconfig.h"
#include "lin-city.h"
#include "lintypes.h"
#include "lctypes.h"

/* other modules */
#include "pbar.h"
#include "engglobs.h"

/* ----------------------------------------------------------------- */

/* ---------------------------------------------------------------------- *
 * Public Global Variables
 * ---------------------------------------------------------------------- */

const unsigned int stats_resources_scale[NUM_RESOURCES] = { 1000, /* food */
                                                            1000, /* jobs */
                                                             250, /* coal */
                                                             500, /* goods */
                                                             500, /* ore */
                                                              25  /* steel */  };

Stats stats_state;
Stats* stats = &stats_state;

/* Daily accumulators */

/* Monthly accumulators */
int tpopulation;
int tstarving_population;
int tunemployed_population;

/* yearly */
int income_tax; 
int coal_tax; 
int goods_tax; 
int export_tax; 
int import_cost;
int unemployment_cost; 
int transport_cost; 
int windmill_cost; 
int university_cost; 
int recycle_cost; 
int deaths_cost; 
int health_cost; 
int rocket_pad_cost; 
int school_cost; 
int fire_cost; 
int cricket_cost; 
int other_cost;

/* Last Year's totals */
int ly_income_tax;
int ly_coal_tax;
int ly_goods_tax;
int ly_export_tax;
int ly_import_cost;
int ly_other_cost;
int ly_unemployment_cost;
int ly_transport_cost;
int ly_university_cost;
int ly_recycle_cost;
int ly_school_cost;
int ly_deaths_cost;
int ly_health_cost;
int ly_rocket_pad_cost;
int ly_interest;
int ly_windmill_cost;
int ly_cricket_cost;
int ly_fire_cost;

/* Averaging variables */
int data_last_month;


/* ---------------------------------------------------------------------- *
 * Private Function Prototypes
 * ---------------------------------------------------------------------- */
void inventory_market(int x, int y);


void
init_daily(void)
{
    unsigned int i;

    world->population.total_day = 0;
    world->population.starving_day = 0;
    world->population.unemployed_day = 0;

    for (i = 0; i < NUM_RESOURCES; i++)
        stats->daily.markets.resource[i].total = 0;
}

void
init_monthly(void)
{
    unsigned int i;

    data_last_month = 0;
    
    tpopulation = 0;
    tstarving_population = 0;
    tunemployed_population = 0;
    world->population.deaths.unnatural_month = 0;

    for (i = 0; i < NUM_RESOURCES; i++)
        stats->monthly.markets.resource[i].total = 0;
}

void
init_yearly(void)
{
    income_tax = 0;
    coal_tax = 0;
    unemployment_cost = 0;
    transport_cost = 0;
    goods_tax = 0;
    export_tax = 0;
    import_cost = 0;
    windmill_cost = 0;
    university_cost = 0;
    recycle_cost = 0;
    deaths_cost = 0;
    health_cost = 0;
    rocket_pad_cost = 0;
    school_cost = 0;
    fire_cost = 0;
    cricket_cost = 0;
}

void
init_lastyear(void)
{
    ly_income_tax = 0;
    ly_coal_tax = 0;
    ly_goods_tax = 0;
    ly_export_tax = 0;
    ly_import_cost = 0;
    ly_other_cost = 0;
    ly_unemployment_cost = 0;
    ly_transport_cost = 0;
    ly_university_cost = 0;
    ly_recycle_cost = 0;
    ly_school_cost = 0;
    ly_deaths_cost = 0;
    ly_health_cost = 0;
    ly_rocket_pad_cost = 0;
    ly_interest = 0;
    ly_windmill_cost = 0;
    ly_cricket_cost = 0;
    ly_fire_cost = 0;
}

void
inventory(int x, int y)
{

    switch(get_group_of_type(MP_TYPE(x,y))) {

    case GROUP_MARKET: 
	inventory_market(x, y); 
	break;
    
    default: {
	printf("Default in inventory(%d,%d): got %d\n", 
	    x, y, get_group_of_type(MP_TYPE(x,y)));
	break;
    }

    }
}

void
init_inventory(void)
{
    init_daily();
    init_monthly();
    init_yearly();
    init_lastyear();
}

void
inventory_market(int x, int y) 
{
    /* FIXME: change MP_INFO(x,y).int_X from int to unsigned int ?? */
    stats->daily.markets.resource[RESOURCE_FOOD].total += MP_INFO(x,y).int_1;
    stats->daily.markets.resource[RESOURCE_JOBS].total += MP_INFO(x,y).int_2;
    stats->daily.markets.resource[RESOURCE_COAL].total += MP_INFO(x,y).int_3;
    stats->daily.markets.resource[RESOURCE_GOODS].total += MP_INFO(x,y).int_4;
    stats->daily.markets.resource[RESOURCE_ORE].total += MP_INFO(x,y).int_5;
    stats->daily.markets.resource[RESOURCE_STEEL].total += MP_INFO(x,y).int_6;
}


/* XXX: WCK:  Why oh why must we divide by arbitrary values, below? */
/* If this is fixed, make sure to fix it in pbar also! */

void
add_daily_to_monthly(void)
{
    unsigned int i;

    data_last_month++;
    
    tpopulation += world->population.total_day;
    tstarving_population += world->population.starving_day;
    tunemployed_population += world->population.unemployed_day;

    for (i = 0; i < NUM_RESOURCES; i++)
        stats->monthly.markets.resource[i].total += stats->daily.markets.resource[i].total / stats_resources_scale[i];
}
