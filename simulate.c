/* ---------------------------------------------------------------------- *
 * simulate.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------- */

/* module header file */
#include "simulate.h"

/* system libraries */
#include <stdio.h> /*printf() */
#include <stdlib.h>
#if defined (WIN32)
#include <winsock.h>
#include <io.h>
#include <direct.h>
#include <process.h>
#endif

/* app general headers */
#include "lcconfig.h"
#include "common.h"
#include "lin-city.h"
#include "lintypes.h"
#include "lctypes.h"

/* other modules */
#include "screen.h"
#include "cliglobs.h"
#include "module_buttons.h"
#include "pbar.h"
#include "stats.h"
#include "engglobs.h"
#include "engine.h"
#include "power.h"
#include "market.h"
#include "modules/blacksmith.h"
#include "modules/coalmine.h"
#include "modules/coal_power.h"
#include "modules/commune.h"
#include "modules/cricket.h"
#include "modules/fire.h"
#include "modules/firestation.h"
#include "modules/health_centre.h"
#include "modules/heavy_industry.h"
#include "modules/light_industry.h"
#include "modules/mill.h"
#include "modules/monument.h"
#include "modules/oremine.h"
#include "modules/organic_farm.h"
#include "modules/parkland.h"
#include "modules/port.h"
#include "modules/pottery.h"
#include "modules/power_line.h"
#include "modules/rail.h"
#include "modules/recycle.h"
#include "modules/residence.h"
#include "modules/road.h"
#include "modules/rocket_pad.h"
#include "modules/school.h"
#include "modules/shanty.h"
#include "modules/solar_power.h"
#include "modules/substation.h"
#include "modules/tip.h"
#include "modules/track.h"
#include "modules/university.h"
#include "modules/windmill.h"

/* ----------------------------------------------------------------- */

/* old lin-city.h definitions */
#define INCOME_TAX_RATE 8
#define COAL_TAX_RATE 20
#define GOODS_TAX_RATE 1
#define DOLE_RATE 15
#define TRANSPORT_COST_RATE 14
#define IM_PORT_COST_RATE 1
#define NUMOF_DISCOUNT_TRIGGERS 6
#define EX_DISCOUNT_TRIGGER_1   25000
#define EX_DISCOUNT_TRIGGER_2   50000
#define EX_DISCOUNT_TRIGGER_3  100000
#define EX_DISCOUNT_TRIGGER_4  200000
#define EX_DISCOUNT_TRIGGER_5  400000
#define EX_DISCOUNT_TRIGGER_6  800000
#define TECH_LEVEL_LOSS_START 11000
/*
   tech-level/TECH_LEVEL_LOSS is lost every month when
   above TECH_LEVEL_LOSS_START
 */
#define TECH_LEVEL_LOSS    500
#define TECH_LEVEL_UNAIDED 2
#define DAYS_PER_POLLUTION      14
/*#define PORT_POLLUTION          1*/
#define UNNAT_DEATHS_COST       500
/* interest rate *10  ie 10 is 1% */
#define INTEREST_RATE 15
#define DAYS_BETWEEN_FIRES (NUMOF_DAYS_IN_YEAR*2)
#define FIRESTATION_RUNNING_COST_MUL 6
#define DAYS_BETWEEN_SHANTY (NUMOF_DAYS_IN_MONTH*5)
#define HEALTH_RUNNING_COST_MUL 9
#define NUMOF_COAL_RESERVES 100
#define SUST_MIN_POPULATION 5000
#define SUST_MIN_TECH_LEVEL (MAX_TECH_LEVEL/2)


static const int ex_tax_dis[NUMOF_DISCOUNT_TRIGGERS] =
{
  EX_DISCOUNT_TRIGGER_1,
  EX_DISCOUNT_TRIGGER_2,
  EX_DISCOUNT_TRIGGER_3,
  EX_DISCOUNT_TRIGGER_4,
  EX_DISCOUNT_TRIGGER_5,
  EX_DISCOUNT_TRIGGER_6,
};

/* ---------------------------------------------------------------------- *
 * Private Fn Prototypes
 * ---------------------------------------------------------------------- */
static void do_periodic_events (void);
static void end_of_month_update (void);
static void start_of_year_update (void);
static void end_of_year_update (void);
static void random_start (int* originx, int* originy);
static void simulate_mappoints (void);
static void quick_start_add (int x, int y, short type, int size);
void coal_reserve_setup (void);
void ore_reserve_setup (void);
void setup_river (void);
void setup_river2 (int x, int y, int d);
void sustainability_test (void);
int sust_fire_cover (void);

/* ---------------------------------------------------------------------- *
 * Public Functions
 * ---------------------------------------------------------------------- */
void
do_time_step (void)
{
    /* Increment game time */
    world->time.total++;
#ifdef DEBUG_ENGINE
    printf ("In do_time_step (%d)\n", world->time.total);
#endif

    /* Initialize daily accumulators */
    init_daily();

    /* Initialize monthly accumulators */
    if (world->time.total % NUMOF_DAYS_IN_MONTH == 0) {
	init_monthly();
    }

    /* Initialize yearly accumulators */
    if ((world->time.total % NUMOF_DAYS_IN_YEAR) == 0) {
	init_yearly();
    }

    /* Clear the power grid */
    power_time_step ();

    /* Run through simulation equations for each farm, residence, etc. */
    simulate_mappoints ();

    /* Now do the stuff that happens once a year, once a month, etc. */
    do_periodic_events ();
}

void 
clear_mappoint (short fill, int x, int y)
{
    MP_TYPE(x,y) = fill;
    MP_GROUP(x,y) = get_group_of_type(fill);
    if (MP_GROUP(x,y) < 0) MP_GROUP(x,y) = GROUP_BARE;
    MP_INFO(x,y).population = 0;
    MP_INFO(x,y).coal_reserve = 0;
    MP_INFO(x,y).flags = 0;
    MP_INFO(x,y).int_1 = 0;
    MP_INFO(x,y).int_2 = 0;
    MP_INFO(x,y).int_3 = 0;
    MP_INFO(x,y).int_4 = 0;
    MP_INFO(x,y).int_5 = 0;
    MP_INFO(x,y).int_6 = 0;
    MP_INFO(x,y).int_7 = 0;
}

static void simulate_mappoints (void)
{
    Map_Coord coord;
    int x, y;
    short group;

    shuffle_mappoint_array ();

    for (coord.y = 0; coord.y < WORLD_SIDE_LEN; coord.y++)
    {
        /* indirection to rand array to stop lots of linear effects */
        y = mappoint_array[coord.y].y;
        for (coord.x = 0; coord.x < WORLD_SIDE_LEN; coord.x++)
        {
            x = mappoint_array[coord.x].x;
            group = MP_GROUP(x,y);

            if (group == GROUP_USED || group == GROUP_BARE)
                continue;

            switch (group)
            {
            case GROUP_TRACK:
                do_track (x, y);
                break;
            case GROUP_RAIL:
                do_rail (x, y);
                break;
            case GROUP_ROAD:
                do_road (x, y);
                break;
            case GROUP_ORGANIC_FARM:
                do_organic_farm (x, y);
                break;
            case GROUP_MARKET:
                do_market (x, y);
                break;
            case GROUP_RESIDENCE_LL:
            case GROUP_RESIDENCE_ML:
            case GROUP_RESIDENCE_HL:
            case GROUP_RESIDENCE_LH:
            case GROUP_RESIDENCE_MH:
            case GROUP_RESIDENCE_HH:
                do_residence (x, y);
                break;
            case GROUP_POWER_LINE:
                do_power_line (x, y);
                break;
            case GROUP_SOLAR_POWER:
                do_power_source (x, y);
                break;
            case GROUP_SUBSTATION:
                do_power_substation (x, y);
                break;
            case GROUP_COALMINE:
                do_coalmine (x, y);
                break;
            case GROUP_COAL_POWER:
                do_power_source_coal (x, y);
                break;
            case GROUP_INDUSTRY_L:
                do_industry_l (x, y);
                break;
            case GROUP_INDUSTRY_H:
                do_industry_h (x, y);
                break;
            case GROUP_COMMUNE:
                do_commune (x, y);
                break;
            case GROUP_OREMINE:
                do_oremine (x, y);
                break;
            case GROUP_PORT:
                do_port (x, y);
                break;
            case GROUP_TIP:
                do_tip (x, y);
                break;
            case GROUP_PARKLAND:
                do_parkland (x, y);
                break;
            case GROUP_UNIVERSITY:
                do_university (x, y);
                break;
            case GROUP_RECYCLE:
                do_recycle (x, y);
                break;
            case GROUP_HEALTH:
                do_health_centre (x, y);
                break;
            case GROUP_ROCKET:
                do_rocket_pad (x, y);
                break;
            case GROUP_WINDMILL:
                do_windmill (x, y);
                break;
            case GROUP_MONUMENT:
                do_monument (x, y);
                break;
            case GROUP_SCHOOL:
                do_school (x, y);
                break;
            case GROUP_BLACKSMITH:
                do_blacksmith (x, y);
                break;
            case GROUP_MILL:
                do_mill (x, y);
                break;
            case GROUP_POTTERY:
                do_pottery (x, y);
                break;
            case GROUP_FIRESTATION:
                do_firestation (x, y);
                break;
            case GROUP_CRICKET:
                do_cricket (x, y);
                break;
            case GROUP_FIRE:
                do_fire (x, y);
                break;
            case GROUP_SHANTY:
                do_shanty (x, y);
                break;
            }
        }
    }
}

/* ---------------------------------------------------------------------- *
 * Private Functions
 * ---------------------------------------------------------------------- */
static void
do_periodic_events (void)
{
  add_daily_to_monthly();


  if ((world->time.total % NUMOF_DAYS_IN_YEAR) == 0) {
    start_of_year_update ();
  }
  if ((world->time.total % DAYS_BETWEEN_FIRES) == 9
      && world->tech.level > (GROUP_FIRESTATION_TECH * MAX_TECH_LEVEL / 1000)) {
    do_random_fire (-1, -1, 1);
  }
  if ((world->time.total % DAYS_BETWEEN_COVER) == 75) {
    clear_fire_health_and_cricket_cover ();
    do_fire_health_and_cricket_cover ();
  }
  if ((world->time.total % DAYS_BETWEEN_SHANTY) == 85
      && world->tech.level > (GROUP_HEALTH_TECH * MAX_TECH_LEVEL / 1000)) {
   update_shanty ();
  }
  if (world->time.total % NUMOF_DAYS_IN_MONTH == (NUMOF_DAYS_IN_MONTH - 1)) {
    end_of_month_update ();
  }
  if (world->time.total % NUMOF_DAYS_IN_YEAR == (NUMOF_DAYS_IN_YEAR - 1)) {
    end_of_year_update ();
  }
  if ((world->time.total % DAYS_PER_POLLUTION) == 3) {
    do_pollution ();
  }
}


static void 
end_of_month_update (void)
{
  /* GCS FIX -- seems to be a bit of engine code embedded in 
     do_monthgraph(), such as coal_made, coal_used, etc.
     Check it out soon... */
  world->population.housed = (tpopulation / NUMOF_DAYS_IN_MONTH);
  if ((world->population.housed + world->population.pool) > world->population.highest)
    world->population.highest = world->population.housed + world->population.pool;

  if (world->population.pool > 100) {
    if (rand () % 1000 < world->population.pool)
      world->population.pool -= 10;
  }
  if (world->population.pool < 0)
    world->population.pool = 0;

  if (world->tech.level > TECH_LEVEL_LOSS_START)
    {
      world->tech.level -= world->tech.level * (1./TECH_LEVEL_LOSS)
	*(1+(tpopulation
	     *(1./NUMOF_DAYS_IN_MONTH/120
	       /(TECH_LEVEL_LOSS-200))));

    }
  else
    world->tech.level += TECH_LEVEL_UNAIDED;
  /* we can go over 100, but it's even more difficult */
  if (world->tech.level > MAX_TECH_LEVEL)
    world->tech.level -= (world->tech.level - MAX_TECH_LEVEL)
      *(1./TECH_LEVEL_LOSS)
      *(1+(tpopulation
	   *(1./NUMOF_DAYS_IN_MONTH/120
	     /(TECH_LEVEL_LOSS-100))));

  if (world->tech.highest_level < world->tech.level)
    world->tech.highest_level = world->tech.level;

  deaths_cost += world->population.deaths.unnatural_month * UNNAT_DEATHS_COST;

}


static void 
start_of_year_update (void)
{
  int u;

  sustainability_test ();

  world->population.deaths.pollution.history
    -= world->population.deaths.pollution.history / 100.0;
  world->population.deaths.starve.history
    -= world->population.deaths.starve.history / 100.0;
  world->population.unemployment.history
    -= world->population.unemployment.history / 100.0;
  u = count_groups (GROUP_UNIVERSITY);
  if (u > 0) {
    world->knowledge.university_intake_rate = (count_groups (GROUP_SCHOOL) * 20) / u;
    if (world->knowledge.university_intake_rate > 100)
      world->knowledge.university_intake_rate = 100;
  } else {
    world->knowledge.university_intake_rate = 50;
  }

  map_power_grid();
}


static void 
end_of_year_update (void)
{
    income_tax = (income_tax * world->money.tax_rate.income) / 100;
    ly_income_tax = income_tax;
    world->money.total += income_tax;

    coal_tax = (coal_tax * world->money.tax_rate.coal) / 100;
    ly_coal_tax = coal_tax;
    world->money.total += coal_tax;

    goods_tax = (goods_tax * world->money.tax_rate.goods) / 100;
    goods_tax += (int) ((float) (goods_tax * world->money.tax_rate.goods)
			   * (float) world->tech.level / 2000000.0);
    ly_goods_tax = goods_tax;
    world->money.total += goods_tax;

    /* The price of exports on the world market drops as you export more.
       The exporters have to discount there wares, therefore the 
       tax take is less.
    */
    if (export_tax > ex_tax_dis[0])
    {
	int discount, disi;
	discount = 0;
	for (disi = 0; disi < NUMOF_DISCOUNT_TRIGGERS
		     && export_tax > ex_tax_dis[disi]; disi++)
	    discount += (export_tax - ex_tax_dis[disi]) / 10;
	export_tax -= discount;
    }
    ly_export_tax = export_tax;
    world->money.total += export_tax;

    ly_university_cost = university_cost;
    ly_recycle_cost = recycle_cost;
    ly_deaths_cost = deaths_cost;
    ly_health_cost = (health_cost * (world->tech.level / 10000)
		      * HEALTH_RUNNING_COST_MUL) / (MAX_TECH_LEVEL / 10000);
    ly_rocket_pad_cost = rocket_pad_cost;
    ly_school_cost = school_cost;
    ly_windmill_cost = windmill_cost;
    ly_fire_cost = (fire_cost * (world->tech.level / 10000)
		    * FIRESTATION_RUNNING_COST_MUL) / (MAX_TECH_LEVEL / 10000);
    ly_cricket_cost = cricket_cost;
    if (world->money.total < 0)
    {
	ly_interest = ((-world->money.total / 1000) * INTEREST_RATE);
	if (ly_interest > 1000000)
	    ly_interest = 1000000;
    }
    else
	ly_interest = 0;

    other_cost = university_cost + recycle_cost + deaths_cost
	    + ly_health_cost + rocket_pad_cost + school_cost
	    + ly_interest + windmill_cost + ly_fire_cost
	    + ly_cricket_cost;
    ly_other_cost = other_cost;
    world->money.total -= other_cost;

    unemployment_cost = (unemployment_cost * world->money.dole_rate) / 100;
    ly_unemployment_cost = unemployment_cost;
    world->money.total -= unemployment_cost;

    transport_cost = (transport_cost * world->money.cost_rate.transport) / 100;
    ly_transport_cost = transport_cost;
    world->money.total -= transport_cost;

    import_cost = (import_cost * world->money.cost_rate.imports) / 100;
    ly_import_cost = import_cost;
    world->money.total -= import_cost;

    if (world->money.total > 2000000000)
	world->money.total = 2000000000;
    else if (world->money.total < -2000000000)
	world->money.total = -2000000000;

    print_total_money ();
}


static void
clear_game (void)
{
    int x, y;
    for (y = 0; y < WORLD_SIDE_LEN; y++) {
	for (x = 0; x < WORLD_SIDE_LEN; x++) {
	    clear_mappoint (CST_GREEN, x, y);
	    MP_POL(x,y) = 0;
	}
    }
    world->time.total = 0;
    world->flags.coal_survey_done = false;
    numof_shanties = 0;
    numof_communes = 0;
    numof_substations = 0;
    /*numof_health_centres = 0;*/ /* Not used */
    numof_markets = 0;
    world->population.highest = 0;
    world->population.evacuated = 0;
    world->population.births = 0;
    world->money.total = 0;
    world->tech.level = 0;
    init_inventory();
    update_avail_modules(0);
}

void
new_city (int* originx, int* originy, int random_village)
{
    clear_game ();
    coal_reserve_setup ();
    setup_river ();
    ore_reserve_setup ();
    init_pbars ();

    /* Initial population is 100 for empty board or 200 
       for random village (100 are housed). */
    world->population.pool = 100;

    if (random_village != 0) {
	random_start (originx, originy);
	update_pbar(PPOP,200,1); /* So pbars don't flash */
    } else {
	*originx = *originy = WORLD_SIDE_LEN/2 ;
	update_pbar(PPOP,100,1);
    }
    connect_transport (1,1,WORLD_SIDE_LEN-2,WORLD_SIDE_LEN-2);
    refresh_pbars ();
}

void coal_reserve_setup (void)
{
  int i, j, x, y, xx, yy;
  for (i = 0; i < NUMOF_COAL_RESERVES / 5; i++)
    {
      x = (rand () % (WORLD_SIDE_LEN - 12)) + 6;
      y = (rand () % (WORLD_SIDE_LEN - 10)) + 6;
      do
	{
	  xx = (rand () % 3) - 1;
	  yy = (rand () % 3) - 1;
	}
      while (xx == 0 && yy == 0);
      for (j = 0; j < 5; j++)
	{
	  MP_INFO(x,y).coal_reserve
	    += rand () % COAL_RESERVE_SIZE;
	  x += xx;
	  y += yy;
	}
    }
}

void ore_reserve_setup (void)
{
    int x, y;
    for (y = 0; y < WORLD_SIDE_LEN; y++)
	for (x = 0; x < WORLD_SIDE_LEN; x++)
	    MP_INFO(x,y).ore_reserve = ORE_RESERVE;
}

void setup_river (void)
{
    int x, y, i, j;
    x = WORLD_SIDE_LEN / 2;
    y = WORLD_SIDE_LEN - 1;
    i = (rand () % 12) + 6;
    for (j = 0; j < i; j++) {
	x += (rand () % 3) - 1;
	MP_TYPE(x,y) = CST_WATER;
	MP_GROUP(x,y) = GROUP_WATER;
	MP_INFO(x,y).flags |= FLAG_IS_RIVER;
	MP_TYPE(x+1,y) = CST_WATER;
	MP_GROUP(x+1,y) = GROUP_WATER;
	MP_INFO(x+1,y).flags |= FLAG_IS_RIVER;
	MP_TYPE(x-1,y) = CST_WATER;
	MP_GROUP(x-1,y) = GROUP_WATER;
	MP_INFO(x-1,y).flags |= FLAG_IS_RIVER;
	y--;
    }
    MP_TYPE(x,y) = CST_WATER;
    MP_GROUP(x,y) = GROUP_WATER;
    MP_INFO(x,y).flags |= FLAG_IS_RIVER;
    MP_TYPE(x+1,y) = CST_WATER;
    MP_GROUP(x+1,y) = GROUP_WATER;
    MP_INFO(x+1,y).flags |= FLAG_IS_RIVER;
    MP_TYPE(x-1,y) = CST_WATER;
    MP_GROUP(x-1,y) = GROUP_WATER;
    MP_INFO(x-1,y).flags |= FLAG_IS_RIVER;

    setup_river2 (x - 1, y, -1);	/* left tributary */
    setup_river2 (x + 1, y, 1);	/* right tributary */
}

void setup_river2 (int x, int y, int d)
{
    int i, j, r;
    i = (rand () % 55) + 15;
    for (j = 0; j < i; j++)
    {
	r = (rand () % 3) - 1 + (d * (rand () % 3));
	if (r < -1)
	    r = -1;
	else if (r > 1)
	    r = 1;
	x += r;
	if (MP_TYPE(x+(d+d),y) != 0
	    || MP_TYPE(x+(d+d+d),y) != 0)
	    return;
	if (x > 5 && x < WORLD_SIDE_LEN - 5)
	{
	    MP_TYPE(x,y) = CST_WATER;
	    MP_GROUP(x,y) = GROUP_WATER;
	    MP_INFO(x,y).flags |= FLAG_IS_RIVER;
	    MP_TYPE(x + d,y) = CST_WATER;
	    MP_GROUP(x+d,y) = GROUP_WATER;
	    MP_INFO(x+d,y).flags |= FLAG_IS_RIVER;
	}
	if (--y < 10 || x < 5 || x > WORLD_SIDE_LEN - 5)
	    break;
    }
    if (y > 20)
    {
	if (x > 5 && x < WORLD_SIDE_LEN - 5)
	    setup_river2 (x, y, -1);
	if (x > 5 && x < WORLD_SIDE_LEN - 5)
	    setup_river2 (x, y, 1);
    }
}

int count_groups (int g)
{
  int x, y, i;
  i = 0;
  for (y = 0; y < WORLD_SIDE_LEN; y++)
    for (x = 0; x < WORLD_SIDE_LEN; x++)
      if (MP_GROUP(x,y) == g)
	i++;
  return (i);
}

void count_all_groups (int* group_count)
{
    int x, y;
    unsigned short t, g;
    for (x = 0; x < NUM_OF_GROUPS; x++)
	group_count[x] = 0;
    for (y = 0; y < WORLD_SIDE_LEN; y++) {
	for (x = 0; x < WORLD_SIDE_LEN; x++) {
	    t = MP_TYPE(x,y);
	    if (t != CST_USED && t != CST_GREEN) {
		g = get_group_of_type(t);
		group_count[g]++;
	    }
	}
    }
}

static void
random_start (int* originx, int* originy)
{
    int x, y, xx, yy, flag, watchdog;

    /* first find a place that has some water. */
    watchdog = 90;        /* if too many tries, random placement. */
    do {
	do {
	    xx = rand () % (WORLD_SIDE_LEN - 25);
	    yy = rand () % (WORLD_SIDE_LEN - 25);
	    flag = 0;
	    for (y = yy + 2; y < yy + 23; y++)
		for (x = xx + 2; x < xx + 23; x++)
		    if (MP_GROUP(x,y) == GROUP_WATER)
		    {
			flag = 1;
			x = xx + 23;   /* break out of loop */
			y = yy + 23;   /* break out of loop */
		    }
	} while (flag == 0 || (--watchdog) < 1);
	for (y = yy + 4; y < yy + 22; y++)
	    for (x = xx + 4; x < xx + 22; x++)
		if (MP_GROUP(x,y) != GROUP_BARE) {
		    flag = 0;
		    x = xx + 22;   /* break out of loop */
		    y = yy + 22;   /* break out of loop */
		}
    } while (flag == 0 || (--watchdog) < 1);

    /* These are going to be the main_screen_origin? vars */
    *originx = xx;
    *originy = yy;

    /*  Draw the start scene. */
    quick_start_add (xx + 5, yy + 5, CST_FARM_O0, 4);
    quick_start_add (xx + 9, yy + 6, CST_RESIDENCE_ML, 3);
    MP_INFO(xx + 9,yy + 6).population = 50;
    MP_INFO(xx + 9,yy + 6).flags |= (FLAG_FED + FLAG_EMPLOYED);
    quick_start_add (xx + 7, yy + 9, CST_MARKET_EMPTY, 2);
    markets[numof_markets].x = xx + 7;
    markets[numof_markets].y = yy + 9;
    numof_markets++;
    /* Bootstap markets with some stuff. */
    MP_INFO(xx + 7,yy + 9).int_1 = 2000;
    MP_INFO(xx + 7,yy + 9).int_2 = 10000;
    MP_INFO(xx + 7,yy + 9).int_3 = 100;
    MP_INFO(xx + 7,yy + 9).int_5 = 10000;
    MP_INFO(xx + 7,yy + 9).flags 
	    |= (FLAG_MB_FOOD + FLAG_MS_FOOD + FLAG_MB_JOBS
		+ FLAG_MS_JOBS + FLAG_MB_COAL + FLAG_MS_COAL + FLAG_MB_ORE
		+ FLAG_MS_ORE + FLAG_MB_GOODS + FLAG_MS_GOODS + FLAG_MB_STEEL
		+ FLAG_MS_STEEL);


    quick_start_add (xx + 14, yy + 6, CST_RESIDENCE_ML, 3);
    MP_INFO(xx + 14,yy + 6).population = 50;
    MP_INFO(xx + 14,yy + 6).flags |= (FLAG_FED + FLAG_EMPLOYED);
    quick_start_add (xx + 17, yy + 5, CST_FARM_O0, 4);
    quick_start_add (xx + 17, yy + 9, CST_MARKET_EMPTY, 2);
    markets[numof_markets].x = xx + 17;
    markets[numof_markets].y = yy + 9;
    numof_markets++;
    MP_INFO(xx + 17,yy + 9).int_1 = 2000;
    MP_INFO(xx + 17,yy + 9).int_2 = 8000;
    MP_INFO(xx + 17,yy + 9).flags 
	    |= (FLAG_MB_FOOD + FLAG_MS_FOOD + FLAG_MB_JOBS
		+ FLAG_MS_JOBS + FLAG_MB_COAL + FLAG_MS_COAL + FLAG_MB_ORE
		+ FLAG_MS_ORE + FLAG_MB_GOODS + FLAG_MS_GOODS + FLAG_MB_STEEL
		+ FLAG_MS_STEEL);

    for (x = 5; x < 19; x++)
    {
	quick_start_add (xx + x, yy + 11, CST_TRACK_LR, 1);
	MP_INFO(xx + x,yy + 11).flags |= FLAG_IS_TRANSPORT;
    }
    for (y = 12; y < 18; y++)
    {
	quick_start_add (xx + 5, yy + y, CST_TRACK_LR, 1);
	MP_INFO(xx + 5,yy + y).flags |= FLAG_IS_TRANSPORT;
    }
    quick_start_add (xx + 6, yy + 12, CST_COMMUNE_1, 4);
    quick_start_add (xx + 6, yy + 17, CST_COMMUNE_1, 4);
    quick_start_add (xx + 11, yy + 12, CST_COMMUNE_1, 4);
    quick_start_add (xx + 11, yy + 17, CST_COMMUNE_1, 4);
    quick_start_add (xx + 16, yy + 12, CST_COMMUNE_1, 4);
    quick_start_add (xx + 16, yy + 17, CST_COMMUNE_1, 4);
    for (x = 6; x < 17; x++)
    {
	quick_start_add (xx + x, yy + 16, CST_TRACK_LR, 1);
	MP_INFO(xx + x,yy + 16).flags |= FLAG_IS_TRANSPORT;
    }
    for (y = 12; y < 16; y++)
    {
	quick_start_add (xx + 10, yy + y, CST_TRACK_LR, 1);
	MP_INFO(xx + 10,yy + y).flags |= FLAG_IS_TRANSPORT;
	quick_start_add (xx + 15, yy + y, CST_TRACK_LR, 1);
	MP_INFO(xx + 15,yy + y).flags |= FLAG_IS_TRANSPORT;
    }
    quick_start_add (xx + 10, yy + 17, CST_TRACK_LR, 1);
    MP_INFO(xx + 10,yy + 17).flags |= FLAG_IS_TRANSPORT;
    quick_start_add (xx + 15, yy + 17, CST_TRACK_LR, 1);
    MP_INFO(xx + 15,yy + 17).flags |= FLAG_IS_TRANSPORT;

    quick_start_add (xx + 9, yy + 9, CST_POTTERY_0, 2);
}

/* XXX: WCK: What is up with this?  Why not just use set_mappoint?! */
static void
quick_start_add (int x, int y, short type, int size)
{
  int xx, yy;
  if (size == 1) {
      MP_TYPE(x,y) = type;
      MP_GROUP(x,y) = get_group_of_type(type);
      return;
  }
  for (yy = 0; yy < size; yy++) {
    for (xx = 0; xx < size; xx++) {
	if (xx == 0 && yy == 0)
	  continue;
	set_mappoint_used (x, y, x + xx, y + yy);
      }
  }
  MP_TYPE(x,y) = type;
  MP_GROUP(x,y) = get_group_of_type(type);
}

void sustainability_test (void)
{
  int i;

    if (false == world->sustain.ore_coal_tip.flag)
    {
        world->sustain.ore_coal_tip.flag = true;
        world->sustain.ore_coal_tip.count = 0;
    }
    else
        world->sustain.ore_coal_tip.count++;

    if (false == world->sustain.port.flag)
    {
        world->sustain.port.flag = true;
        world->sustain.port.count = 0;
    }
    else
        world->sustain.port.count++;

  /* Money must be going up or the same. (ie can't build.) */
  if (world->sustain.money.previous > world->money.total)
    world->sustain.money.count = 0;
  else
    world->sustain.money.count++;
  world->sustain.money.previous = world->money.total;

  /* population must be withing 2% of when it started. */
  i = (world->population.housed + world->population.pool) - world->sustain.population.previous;
  if (abs (i) > (world->sustain.population.previous / 40)	/* 2.5%  */
      || (world->population.housed + world->population.pool) < SUST_MIN_POPULATION)
    {
      world->sustain.population.previous = (world->population.housed + world->population.pool);
      world->sustain.population.count = 0;
    }
  else
    world->sustain.population.count++;

  /* tech level must be going up or not fall more than 0.5% from it's
     highest during the sus count
  */
  i = world->tech.level - world->sustain.tech.previous;
  if (i < 0 || world->tech.level < SUST_MIN_TECH_LEVEL)
    {
      i = -i;
      if ((i > world->sustain.tech.previous / 100) || world->tech.level < SUST_MIN_TECH_LEVEL)
	{
	  world->sustain.tech.count = 0;
	  world->sustain.tech.previous = world->tech.level;
	}
      else
	world->sustain.tech.count++;
    }
  else
    {
      world->sustain.tech.count++;
      world->sustain.tech.previous = world->tech.level;
    }

  /* check fire cover only every three years */
  if (world->time.total % (NUMOF_DAYS_IN_YEAR * 3) == 0)
    {
      if (sust_fire_cover () != 0)
	world->sustain.fire.count += 3;
      else
	world->sustain.fire.count = 0;

    }
}

int sust_fire_cover (void)
{
  int x, y;
  for (x = 0; x < WORLD_SIDE_LEN; x++)
    for (y = 0; y < WORLD_SIDE_LEN; y++)
      {
	if (MP_GROUP(x,y) == GROUP_BARE
	    || MP_TYPE(x,y) == CST_USED
	    || MP_GROUP(x,y) == GROUP_WATER
	    || MP_GROUP(x,y) == GROUP_POWER_LINE
	    || MP_GROUP(x,y) == GROUP_OREMINE
	    || MP_GROUP(x,y) == GROUP_ROCKET
	    || MP_GROUP(x,y) == GROUP_MONUMENT
	    || MP_GROUP(x,y) == GROUP_BURNT)
	  ;			/* do nothing */

	else if ((MP_INFO(x,y).flags & FLAG_FIRE_COVER) == 0)
	  return (0);
      }
  return (1);
}

void 
debug_mappoints (void)
{
  int x, y;
  for (x = 0; x < WORLD_SIDE_LEN; x++) {
    for (y = 0; y < WORLD_SIDE_LEN; y++) {
      if ((MP_TYPE(x,y) < 0) || (MP_TYPE(x,y) > 400)) {
	printf ("Error in mappoint %d %d (%d)\n", x, y, MP_TYPE(x,y));
	exit(-1);
      }
    }
  }
}

void initialize_tax_rates (void)
{
  world->money.tax_rate.income = INCOME_TAX_RATE;
  world->money.tax_rate.coal = COAL_TAX_RATE;
  world->money.tax_rate.goods = GOODS_TAX_RATE;
  world->money.dole_rate = DOLE_RATE;
  world->money.cost_rate.transport = TRANSPORT_COST_RATE;
  world->money.cost_rate.imports = IM_PORT_COST_RATE;
}

