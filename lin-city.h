/* ---------------------------------------------------------------------- *
 * lin-city.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */

#ifndef __lin_city_h__
#define __lin_city_h__


#include "boolean.h"

/*
  The mouse sensitivity can be an integer such as 1, 2, 3 etc.
  The higher the number the less you have to move the mouse.
  It's a bit crude, it just multiples the mouse movement by this
  amount. IMHO 3 is about the maximum useful value, 2 is quite
  comfortable.
    ** This is only relevant for linux-svgalib. **
*/
#define MOUSE_SENSITIVITY 1

/*
  When your money reaches 1 million or more, to make it easier to
  read, it is split into two parts; a millions part, and the rest.
   For example  12,355232    You can choose any character you like,
   but I have given some other examples. Just comment out the one 
   above, and uncomment one below. IT MUST NOT BE NULL.
  #define MONEY_SEPARATOR '.'
  #define MONEY_SEPARATOR ' '
  #define MONEY_SEPARATOR ':'
*/
#define MONEY_SEPARATOR ','

/*
   #define MP_SANITY_CHECK
*/

/* The number of milliseconds between scrolling text on the initial screen */
#define SPLASH_SCROLL_DELAY 30  /* was 30 */

/*
       ************************************************
        NO USER CONFIGURABLE OPTIONS BEYOND THIS POINT
       ************************************************
*/

/* VERSION_INT is used in the load/save code.  All other code uses 
   the symbol VERSION in config.h */
#define VERSION_INT 112

/* Don't load if < MIN_LOAD_VERSION */
#define MIN_LOAD_VERSION 97

/* Load corrections if version <= MM_MS_C_VER (max markets/substations) */
#define MM_MS_C_VER 97

/* Load corrections if version <= MG_C_VER (max monthgraph size) */
#define MG_C_VER 111

#if defined (WIN32)
#define PATH_SLASH '\\'
#define PATH_SLASH_STRING "\\"
#else
#define PATH_SLASH '/'
#define PATH_SLASH_STRING "/"
#endif

#define USE_X11_PIXMAPS

/* Used by HandleError () */
#define FATAL   -1
#define WARNING -2

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif


/* comment out the the next three lines for _slightly_ faster X drawing. */
#ifdef LC_X11
#define ALLOW_PIX_DOUBLING
#endif

/*
  Gamma correction. The numbers GAMMA_CORRECT_X are between 0.0 and 1.0
  The following values are enabled with the -w option. This seems quite
  good for 'washed out' monitors that lack red.
  You can also set the values from the command line.
   [x]lincity -R 1.0 -G 0.0 -B 0.4  is the same as [x]lincity -w
 */
#define GAMMA_CORRECT_RED   1.0
#define GAMMA_CORRECT_GREEN 0.0
#define GAMMA_CORRECT_BLUE  0.4

#define PROFILE_COUNTDOWN 10000

/* hof is 70 from 28/12 */

#define DEBUG

/*
#define DEBUG_ENGINE 1
   #define ALLOW_TCORE_DUMP
   #define DEBUG_ROCKETS
   #define DEBUGMOUSE
   #define DEBUG_MOUSE
   #define DEBUG_MAIN_SCREEN
   #define DEBUG_GET_POWER
   if DEBUG_KEYS is defined, pressing certain keys add money, tech points etc.
   #define DEBUG_KEYS 1
*/
/*
   #define CS_PROFILE
*/

#if defined (LC_X11) || defined (WIN32)
#define BORDERX 30
#define BORDERY 30
#endif

#define TEXT_FG_COLOUR  (white(24))
#define TEXT_BG_COLOUR  105
#define YN_DIALBOX_BG_COLOUR (red(10))
#define LOAD_BG_COLOUR       (cyan(10))
#define SAVE_BG_COLOUR       (magenta(10))
#define NW_BG_COLOUR         (green(10))

/* GCS: We are about to run out of bits on the flags, so in the future we
   might need to implement compression.  For example, FLAG_IS_RIVER is 
   only used for GROUP_WATER, FLAG_MB_COAL for GROUP_MARKET, and so on. */
/* WCK: Compression would work, but that's complicated.   I would rather move
   FLAG_M?_* into an int_? variable.  And add more int_? variables.  That keeps
   it simple and squeezes some life out of 32 bits.  I don't think we need to
   hurry.  I'd rather replace the whole scheme. */
#define FLAG_LEFT               (1)
#define FLAG_UP                 (2)
#define FLAG_RIGHT              (4)
#define FLAG_DOWN               (8)
#define FLAG_POWERED            (0x10)
#define FLAG_FED                (0x20)
#define FLAG_EMPLOYED           (0x40)
#define FLAG_IS_TRANSPORT       (0x80)
#define FLAG_MB_FOOD            (0x100)
#define FLAG_MS_FOOD            (0x200)
#define FLAG_MB_JOBS            (0x400)
#define FLAG_MS_JOBS            (0x800)
#define FLAG_MB_COAL            (0x1000)
#define FLAG_MS_COAL            (0x2000)
#define FLAG_MB_ORE             (0x4000)
#define FLAG_MS_ORE             (0x8000)
#define FLAG_MB_GOODS           (0x10000)
#define FLAG_MS_GOODS           (0x20000)
#define FLAG_MB_STEEL           (0x40000)
#define FLAG_MS_STEEL           (0x80000)
#define FLAG_FIRE_COVER         (0x100000)
#define FLAG_HEALTH_COVER       (0x200000)
#define FLAG_CRICKET_COVER      (0x400000)
#define FLAG_IS_RIVER           (0x800000)
#define FLAG_HAD_POWER          (0x1000000)
#define FLAG_MULTI_TRANSPORT    (0x2000000)   /* Is it a multitransport? */
#define FLAG_MULTI_TRANS_PREV   (0x4000000)
#define FLAG_POWER_LINE         (0x8000000)

#define T_FOOD  0
#define T_JOBS  1
#define T_COAL  2
#define T_GOODS 3
#define T_ORE   4
#define T_STEEL 5
#define T_WASTE 6

#define MT_FAIL     0
#define MT_START    1
#define MT_CONTINUE 2
#define MT_SUCCESS  3

#define HOF_START 845830134
#define HOF_STOP 857843038

#define MINI_SCREEN_NORMAL_FLAG    (0)
#define MINI_SCREEN_POL_FLAG       (1)
#define MINI_SCREEN_UB40_FLAG      (2)
#define MINI_SCREEN_STARVE_FLAG    (3)
#define MINI_SCREEN_PORT_FLAG      (4)
#define MINI_SCREEN_POWER_FLAG     (5)
#define MINI_SCREEN_FIRE_COVER     (6)
#define MINI_SCREEN_CRICKET_COVER  (7)
#define MINI_SCREEN_HEALTH_COVER   (8)
#define MINI_SCREEN_COAL_FLAG      (9)

#define MAIN_SCREEN_NORMAL_FLAG    (1)
#define MAIN_SCREEN_EQUALS_MINI    (2)

#define SEED_RAND
#define OLD_LC_SAVE_DIR "Lin-city"
#if defined (WIN32)
#define LC_SAVE_DIR "SAVED_GAMES"
#define LINCITYRC_FILENAME "lincity.ini"
#else
/* GCS: Changed for 1.12 */
/* #define LC_SAVE_DIR ".Lin-city" */
#define LC_SAVE_DIR ".lincity"
#define LINCITYRC_FILENAME ".lincityrc"
#endif
#define RESULTS_FILENAME "results"

#define MAX_ICON_LEN 4096
#define WORLD_SIDE_LEN 100
#define NUMOF_DAYS_IN_MONTH 100
#define NUMOF_DAYS_IN_YEAR (NUMOF_DAYS_IN_MONTH*12)
#define FAST_TIME_FOR_YEAR 1
#define MED_TIME_FOR_YEAR  20
#define SLOW_TIME_FOR_YEAR  60

/* interest rate *10  ie 10 is 1% */
#define INTEREST_RATE 15

#if defined (commentout)
#define HELP_BUTTON_X 608
#define HELP_BUTTON_Y 448
#define HELP_BUTTON_W 32
#define HELP_BUTTON_H 32
#define QUIT_BUTTON_X 608
#define QUIT_BUTTON_Y 416
#define QUIT_BUTTON_W 32
#define QUIT_BUTTON_H 32
#define LOAD_BUTTON_X 576
#define LOAD_BUTTON_Y 416
#define LOAD_BUTTON_W 32
#define LOAD_BUTTON_H 32
#define SAVE_BUTTON_X 576
#define SAVE_BUTTON_Y 448
#define SAVE_BUTTON_W 32
#define SAVE_BUTTON_H 32
#endif

#define HELPERRORPAGE "error.hlp"
#define HELPBACKGROUNDCOLOUR (white(8))
#define HELPBUTTON_COLOUR (white(25))
#define MAX_NUMOF_HELP_BUTTONS 40
#define MAX_LENOF_HELP_FILENAME 40
#define MAX_HELP_HISTORY 20
#define CS_MOUSE_BUTTON_DELAY 5
#define RIGHT_MOUSE_MOVE_VAL 5

#define GOOD 1
#define BAD (-1)
#define RESULTS 0

#define PROGBOXX 170
#define PROGBOXY 180
#define PROGBOXW 300
#define PROGBOXH 120
#define PROGBOX_BG_COLOUR 114
#define PROGBOX_DONE_COL 4
#define PROGBOX_NOTDONE_COL 2

#define POWER_LINE_CAPACITY 1000000
#define POWERS_SOLAR_OUTPUT 1800
#define WINDMILL_POWER      450

#define OLD_MAX_NUMOF_SUBSTATIONS 100
#define MAX_NUMOF_SUBSTATIONS 512
#define POWERS_COAL_OUTPUT 22000

#define DAYS_PER_POLLUTION      14
#define PORT_POLLUTION          1
#define UNNAT_DEATHS_COST       500
#define POL_DIV                 64	/* GCS -- from engine.c */

#define FINANCE_X 91
#define FINANCE_W 120
#define FINANCE_Y 200
#define FINANCE_H 56
#define INCOME_TAX_RATE 8
#define COAL_TAX_RATE 20
#define GOODS_TAX_RATE 1
#define DOLE_RATE 15
#define TRANSPORT_COST_RATE 14
#define IM_PORT_COST_RATE 1
#define PORT_FOOD_RATE    1
#define PORT_JOBS_RATE    5
#define PORT_COAL_RATE    50
#define PORT_ORE_RATE     1
#define PORT_GOODS_RATE   3
#define PORT_STEEL_RATE   100
/*
  These next two control the stuff bought or sold as a % of what's on the
  transport.  1000=100%  500=50% etc.
*/
#define PORT_EXPORT_RATE  500
#define PORT_IMPORT_RATE  500

#define NUMOF_DISCOUNT_TRIGGERS 6
#define EX_DISCOUNT_TRIGGER_1   25000
#define EX_DISCOUNT_TRIGGER_2   50000
#define EX_DISCOUNT_TRIGGER_3  100000
#define EX_DISCOUNT_TRIGGER_4  200000
#define EX_DISCOUNT_TRIGGER_5  400000
#define EX_DISCOUNT_TRIGGER_6  800000

#define MAX_TECH_LEVEL	   1000000
#define TECH_LEVEL_LOSS_START 11000
/*
   tech-level/TECH_LEVEL_LOSS is lost every month when
   above TECH_LEVEL_LOSS_START
 */
#define TECH_LEVEL_LOSS    500
#define TECH_LEVEL_UNAIDED 2
#define MODERN_WINDMILL_TECH 450000

#define DAYS_BETWEEN_COVER (NUMOF_DAYS_IN_MONTH*3)
#define DAYS_BETWEEN_FIRES (NUMOF_DAYS_IN_YEAR*2)
#define FIRESTATION_RUNNING_COST_MUL 6
#define FIRE_LENGTH (NUMOF_DAYS_IN_YEAR*5)

#define ROCKET_LAUNCH_BAD       1
#define ROCKET_LAUNCH_GOOD      2
#define ROCKET_LAUNCH_EVAC      3

#define TIP_DEGRADE_TIME 200 * NUMOF_DAYS_IN_YEAR

#define HEALTH_RUNNING_COST_MUL 9

#define OLD_MAX_NUMOF_MARKETS 100
#define MAX_NUMOF_MARKETS 512
#define MAX_FOOD_ON_TRACK 2048
#define MAX_FOOD_ON_RIVER (MAX_FOOD_ON_TRACK*2)
#define MAX_FOOD_ON_ROAD (MAX_FOOD_ON_TRACK*4)
#define MAX_FOOD_ON_RAIL (MAX_FOOD_ON_ROAD*4)
#define MAX_FOOD_IN_MARKET (MAX_FOOD_ON_RAIL*8)
#define MARKET_FOOD_SEARCH_TRIGGER (MAX_FOOD_IN_MARKET/5)
#define MAX_JOBS_ON_TRACK 1024
#define MAX_JOBS_ON_RIVER (MAX_JOBS_ON_TRACK*2)
#define MAX_JOBS_ON_ROAD (MAX_JOBS_ON_TRACK*5)
#define MAX_JOBS_ON_RAIL (MAX_JOBS_ON_ROAD*5)
#define MAX_JOBS_IN_MARKET (MAX_JOBS_ON_RAIL*3)
#define MARKET_JOBS_SEARCH_TRIGGER (MAX_JOBS_IN_MARKET/5)

#define ORGANIC_FARM_FOOD_OUTPUT 550

#define MAX_WASTE_ON_TRACK 1024
#define MAX_WASTE_ON_ROAD (MAX_WASTE_ON_TRACK*5)
#define MAX_WASTE_ON_RAIL (MAX_WASTE_ON_ROAD*5)
#define MAX_WASTE_IN_MARKET (MAX_WASTE_ON_RAIL*3)
#define MARKET_WASTE_SEARCH_TRIGGER (MAX_WASTE_IN_MARKET/5)

#define NUMOF_COAL_RESERVES 100
#define COAL_RESERVE_SIZE 10000
#define ORE_RESERVE       1000
#define MIN_ORE_RESERVE_FOR_MINE (ORE_RESERVE)
#define MAX_ORE_AT_MINE 100000
#define JOBS_DIG_ORE  200
#define JOBS_COALPS_GENERATE 100
#define MAX_JOBS_AT_COALPS 2000
#define JOBS_LOAD_COAL 18
#define JOBS_LOAD_ORE  9
#define JOBS_LOAD_STEEL 15
#define JOBS_AT_COMMUNE_GATE 4
#define COMMUNE_POP  5

#define DIG_MORE_ORE_TRIGGER  (MAX_ORE_AT_MINE)
#define MAX_COAL_ON_TRACK 64
#define MAX_COAL_ON_RIVER (MAX_COAL_ON_TRACK*2)
#define MAX_COAL_ON_ROAD (MAX_COAL_ON_TRACK*8)
#define MAX_COAL_ON_RAIL (MAX_COAL_ON_ROAD*8)
#define MAX_COAL_IN_MARKET (MAX_COAL_ON_RAIL*2)
#define MARKET_COAL_SEARCH_TRIGGER (MAX_COAL_IN_MARKET/5)

#define MAX_GOODS_ON_TRACK 2048
#define MAX_GOODS_ON_RIVER (MAX_GOODS_ON_TRACK*2)
#define MAX_GOODS_ON_ROAD (MAX_GOODS_ON_TRACK*5)
#define ROAD_GOODS_USED_MASK 0x1f
#define MAX_GOODS_ON_RAIL (MAX_GOODS_ON_ROAD*5)
#define RAIL_GOODS_USED_MASK 0xf
#define MAX_GOODS_IN_MARKET (MAX_GOODS_ON_RAIL*4)
#define MARKET_GOODS_SEARCH_TRIGGER (MAX_GOODS_IN_MARKET/5)
#define MAX_ORE_ON_TRACK 4096
#define MAX_ORE_ON_RIVER (MAX_ORE_ON_TRACK*2)
#define MAX_ORE_ON_ROAD (MAX_ORE_ON_TRACK*4)
#define MAX_ORE_ON_RAIL (MAX_ORE_ON_ROAD*4)
#define MAX_ORE_IN_MARKET (MAX_ORE_ON_RAIL*2)
#define MARKET_ORE_SEARCH_TRIGGER (MAX_ORE_IN_MARKET/5)


#define MAX_STEEL_ON_TRACK 128
#define MAX_STEEL_ON_RIVER (MAX_STEEL_ON_TRACK*2)
#define MAX_STEEL_ON_ROAD (MAX_STEEL_ON_TRACK*4)
#define MAX_STEEL_ON_RAIL (MAX_STEEL_ON_ROAD*4)


#if defined (commentout)
#define MAIN_WIN_W 448
#define MAIN_WIN_X (640-MAIN_WIN_W-8)
#define MAIN_WIN_Y 8
#define MAIN_WIN_H 400
#endif

#define SUST_MIN_POPULATION 5000
#define SUST_MIN_TECH_LEVEL (MAX_TECH_LEVEL/2)

#define STATS_X 232
#define STATS_Y 428
#define STATS_W 304
#define STATS_H 32

/* GCS FIX: This is still used in static data structure for size 
   of monthgraph.  Fix by encapsulating the monthgraph and dynamically
   allocating.  */
#if defined (commentout)
#ifndef MONTHGRAPH_W
#define MONTHGRAPH_X 91
#define MONTHGRAPH_W 120
#define MONTHGRAPH_Y 116
#define MONTHGRAPH_H 64
#endif
#define DIFFGRAPH_POWER_COLOUR (yellow(28))
#define DIFFGRAPH_COAL_COLOUR  (white(18))
#define DIFFGRAPH_GOODS_COLOUR (cyan(24))
#define DIFFGRAPH_ORE_COLOUR   (red(22))
#define DIFFGRAPH_POPULATION_COLOUR 7
#endif

#define GRAPHS_B_COLOUR (white(6))

/* These constants are still used by save-under buffer */
#if defined (commentout)
#define MARKET_CB_X (79)
#define MARKET_CB_Y 0
#endif
//#define MARKET_CB_W (18*8)
#define MARKET_CB_W (17*8 - 2)
#define MARKET_CB_H (23*8)

#define SCROLL_LONG_COUNT 5
#define SCROLL_RIGHT_BUTTON_X 100
#define SCROLL_RIGHT_BUTTON_W 32
#define SCROLL_RIGHT_BUTTON_Y 100
#define SCROLL_RIGHT_BUTTON_H 32
#define SCROLL_LEFT_BUTTON_X 100
#define SCROLL_LEFT_BUTTON_W 32
#define SCROLL_LEFT_BUTTON_Y 132
#define SCROLL_LEFT_BUTTON_H 32
#define SCROLL_DOWN_BUTTON_X 100
#define SCROLL_DOWN_BUTTON_W 32
#define SCROLL_DOWN_BUTTON_Y 164
#define SCROLL_DOWN_BUTTON_H 32
#define SCROLL_UP_BUTTON_X 100
#define SCROLL_UP_BUTTON_W 32
#define SCROLL_UP_BUTTON_Y 196
#define SCROLL_UP_BUTTON_H 32

#define SHUFFLE_MAPPOINT_COUNT 4

#if defined (commentout)
#define MAPPOINT_STATS_X 91
/* MAPPOINT_STATS_W must be == MONTHGRAPH_W because of the graph drawing. */
#define MAPPOINT_STATS_W MONTHGRAPH_W
#define MAPPOINT_STATS_Y 8
#define MAPPOINT_STATS_H (11*8)
#endif

#define GROUP_BARE 	   0
#define GROUP_BARE_COLOUR  (green(12))
#define GROUP_BARE_COST    0
#define GROUP_BARE_COST_MUL 1
#define GROUP_BARE_BUL_COST 1
#define GROUP_BARE_TECH    0
#define GROUP_BARE_FIREC   0

#define GROUP_POWER_LINE   1
#define GROUP_POWER_LINE_COLOUR (yellow(26))
#define GROUP_POWER_LINE_COST 100
#define GROUP_POWER_LINE_COST_MUL 2
#define GROUP_POWER_LINE_BUL_COST 100
#define GROUP_POWER_LINE_TECH 200
#define GROUP_POWER_LINE_FIREC 0

#if defined (commentout)
/* GROUP_POWER_SOURCE is a solar ps - change the names  - real soon */
#define GROUP_POWER_SOURCE 2
#define GROUP_POWER_SOURCE_COLOUR (yellow(22))
#define GROUP_POWER_SOURCE_COST 500000
#define GROUP_POWER_SOURCE_COST_MUL 5
#define GROUP_POWER_SOURCE_BUL_COST 100000
#define GROUP_POWER_SOURCE_TECH 500
#define GROUP_POWER_SOURCE_NO_CREDIT
#define GROUP_POWER_SOURCE_FIREC 33
#endif

#define GROUP_SOLAR_POWER 2
#define GROUP_SOLAR_POWER_COLOUR (yellow(22))
#define GROUP_SOLAR_POWER_COST 500000
#define GROUP_SOLAR_POWER_COST_MUL 5
#define GROUP_SOLAR_POWER_BUL_COST 100000
#define GROUP_SOLAR_POWER_TECH 500
#define GROUP_SOLAR_POWER_NO_CREDIT
#define GROUP_SOLAR_POWER_FIREC 33

#define GROUP_SUBSTATION   3
#define GROUP_SUBSTATION_COLOUR (yellow(18))
#define GROUP_SUBSTATION_COST 500
#define GROUP_SUBSTATION_COST_MUL 2
#define GROUP_SUBSTATION_BUL_COST 100
#define GROUP_SUBSTATION_TECH 200
#define GROUP_SUBSTATION_FIREC 50

#define GROUP_RESIDENCE_LL 4
#define GROUP_RESIDENCE_LL_COLOUR (cyan(24))
#define GROUP_RESIDENCE_LL_COST 1000
#define GROUP_RESIDENCE_LL_COST_MUL 25
#define GROUP_RESIDENCE_LL_BUL_COST 1000
#define GROUP_RESIDENCE_LL_TECH 0
#define GROUP_RESIDENCE_LL_FIREC 75

#if defined (commentout)
#define GROUP_RESIDENCE    4
#define GROUP_RESIDENCE_COLOUR (cyan(24))
#define GROUP_RESIDENCE_COST   0
#define GROUP_RESIDENCE_COST1  1000
#define GROUP_RESIDENCE_COST2  2000
#define GROUP_RESIDENCE_COST3  4000
#define GROUP_RESIDENCE_COST4  800
#define GROUP_RESIDENCE_COST5  1600
#define GROUP_RESIDENCE_COST6  3200
#define GROUP_RESIDENCE_COST_MUL 25
#define GROUP_RESIDENCE_BUL_COST 1000
#define GROUP_RESIDENCE_TECH 0
#define GROUP_RESIDENCE_FIREC 75
#endif

#define GROUP_ORGANIC_FARM 5
#define GROUP_ORGANIC_FARM_COLOUR (green(30))
#define GROUP_ORGANIC_FARM_COST 1000
#define GROUP_ORGANIC_FARM_COST_MUL 20
#define GROUP_ORGANIC_FARM_BUL_COST 100
#define GROUP_ORGANIC_FARM_TECH 0
#define GROUP_ORGANIC_FARM_FIREC 20

#define GROUP_MARKET       6
#define GROUP_MARKET_COLOUR (blue(28))
#define GROUP_MARKET_COST 100
#define GROUP_MARKET_COST_MUL 25
#define GROUP_MARKET_BUL_COST 100
#define GROUP_MARKET_TECH 0
#define GROUP_MARKET_FIREC 80

#define GROUP_TRACK	   7
#define GROUP_TRACK_COLOUR 32	/* 32 is a brown */
#define GROUP_TRACK_COST   1
#define GROUP_TRACK_COST_MUL 25
#define GROUP_TRACK_BUL_COST   10
#define GROUP_TRACK_TECH   0
#define GROUP_TRACK_FIREC  4

#define GROUP_COALMINE     8
#define GROUP_COALMINE_COLOUR 0
#define GROUP_COALMINE_COST   10000
#define GROUP_COALMINE_COST_MUL 25
#define GROUP_COALMINE_BUL_COST   10000
#define GROUP_COALMINE_TECH   85
#define GROUP_COALMINE_FIREC  85

#define GROUP_RAIL         9
#define GROUP_RAIL_COLOUR  (magenta(18))
#define GROUP_RAIL_COST    500
#define GROUP_RAIL_COST_MUL 10
#define GROUP_RAIL_BUL_COST    1000
#define GROUP_RAIL_TECH    180
#define GROUP_RAIL_FIREC   6

#define GROUP_COAL_POWER 10
#define GROUP_COAL_POWER_COLOUR 0
#define GROUP_COAL_POWER_COST   100000
#define GROUP_COAL_POWER_COST_MUL 5
#define GROUP_COAL_POWER_BUL_COST   200000
#define GROUP_COAL_POWER_TECH   200
#define GROUP_COAL_POWER_FIREC  80

#define GROUP_ROAD         11
#define GROUP_ROAD_COLOUR  (white(18))
#define GROUP_ROAD_COST    100
#define GROUP_ROAD_COST_MUL 25
#define GROUP_ROAD_BUL_COST    50
#define GROUP_ROAD_TECH    50
#define GROUP_ROAD_FIREC   4

#define GROUP_INDUSTRY_L   12
#define GROUP_INDUSTRY_L_COLOUR (cyan(18))
#define GROUP_INDUSTRY_L_COST 20000
#define GROUP_INDUSTRY_L_COST_MUL 25
#define GROUP_INDUSTRY_L_BUL_COST 20000
#define GROUP_INDUSTRY_L_TECH 160
#define GROUP_INDUSTRY_L_FIREC 70

#define GROUP_UNIVERSITY   13
#define GROUP_UNIVERSITY_COLOUR (blue(22))
#define GROUP_UNIVERSITY_COST 20000
#define GROUP_UNIVERSITY_COST_MUL 25
#define GROUP_UNIVERSITY_BUL_COST 20000
#define GROUP_UNIVERSITY_TECH 150
#define GROUP_UNIVERSITY_NO_CREDIT
#define GROUP_UNIVERSITY_FIREC 40

#define GROUP_COMMUNE      14
#define GROUP_COMMUNE_COLOUR (green(30))
#define GROUP_COMMUNE_COST  1
#define GROUP_COMMUNE_COST_MUL 2
#define GROUP_COMMUNE_BUL_COST  1000
#define GROUP_COMMUNE_TECH  0
#define GROUP_COMMUNE_FIREC 30

#define GROUP_OREMINE      15
#define GROUP_OREMINE_COLOUR (red(18))
#define GROUP_OREMINE_COST 500
#define GROUP_OREMINE_COST_MUL 10
#define GROUP_OREMINE_BUL_COST 500000
#define GROUP_OREMINE_TECH 0
#define GROUP_OREMINE_FIREC 0

#define GROUP_TIP      16
#define GROUP_TIP_COLOUR (white(16))
#define GROUP_TIP_COST 10000
#define GROUP_TIP_COST_MUL 25
#define GROUP_TIP_BUL_COST 1000000
#define GROUP_TIP_TECH 0
#define GROUP_TIP_FIREC 50

#define GROUP_PORT      17
#define GROUP_PORT_COLOUR (blue(28))
#define GROUP_PORT_COST 100000
#define GROUP_PORT_COST_MUL 2
#define GROUP_PORT_BUL_COST 1000
#define GROUP_PORT_TECH 35
#define GROUP_PORT_FIREC 50

#define GROUP_INDUSTRY_H   18
#define GROUP_INDUSTRY_H_COLOUR (7)	/* colour 7 is an orange, sort of */
#define GROUP_INDUSTRY_H_COST 50000
#define GROUP_INDUSTRY_H_COST_MUL 20
#define GROUP_INDUSTRY_H_BUL_COST 70000
#define GROUP_INDUSTRY_H_TECH 170
#define GROUP_INDUSTRY_H_FIREC 80

#define GROUP_PARKLAND     19
#define GROUP_PARKLAND_COLOUR (green(31))
#define GROUP_PARKLAND_COST   1000
#define GROUP_PARKLAND_COST_MUL 25
#define GROUP_PARKLAND_BUL_COST   1000
#define GROUP_PARKLAND_TECH   2
#define GROUP_PARKLAND_NO_CREDIT
#define GROUP_PARKLAND_FIREC 1

#define GROUP_RECYCLE      20
#define GROUP_RECYCLE_COLOUR   (green(28))
#define GROUP_RECYCLE_COST    100000
#define GROUP_RECYCLE_COST_MUL 5
#define GROUP_RECYCLE_BUL_COST    1000
#define GROUP_RECYCLE_TECH    232
#define GROUP_RECYCLE_NO_CREDIT
#define GROUP_RECYCLE_FIREC 10

#define GROUP_WATER	   21
#define GROUP_WATER_COLOUR    (blue(31))
#define GROUP_WATER_COST      1000000
#define GROUP_WATER_COST_MUL 2
#define GROUP_WATER_BUL_COST      1000000
#define GROUP_WATER_TECH      0
#define GROUP_RIVER (GROUP_WATER)	/* oops -- GCS: Why oops? */
#define GROUP_WATER_FIREC 0

#define GROUP_HEALTH       22
#define GROUP_HEALTH_COLOUR   (green(24))
#define GROUP_HEALTH_COST     100000
#define GROUP_HEALTH_COST_MUL 2
#define GROUP_HEALTH_BUL_COST     1000
#define GROUP_HEALTH_TECH     110
#define GROUP_HEALTH_FIREC 2

#define GROUP_ROCKET	   23
#define GROUP_ROCKET_COLOUR   (magenta(20))
#define GROUP_ROCKET_COST     700000
#define GROUP_ROCKET_COST_MUL 2
#define GROUP_ROCKET_BUL_COST     1
#define GROUP_ROCKET_TECH     750
#define GROUP_ROCKET_NO_CREDIT
#define GROUP_ROCKET_FIREC 0

#define GROUP_WINDMILL     24
#define GROUP_WINDMILL_COLOUR (green(25))
#define GROUP_WINDMILL_COST   20000
#define GROUP_WINDMILL_COST_MUL 25
#define GROUP_WINDMILL_BUL_COST   1000
#define GROUP_WINDMILL_TECH   30
#define GROUP_WINDMILL_FIREC  10

#define GROUP_MONUMENT     25
#define GROUP_MONUMENT_COLOUR (white(15))
#define GROUP_MONUMENT_COST   10000
#define GROUP_MONUMENT_COST_MUL 25
#define GROUP_MONUMENT_BUL_COST   1000000
#define GROUP_MONUMENT_TECH   0
#define GROUP_MONUMENT_FIREC  0

#define GROUP_SCHOOL     26
#define GROUP_SCHOOL_COLOUR (white(15))
#define GROUP_SCHOOL_COST   10000
#define GROUP_SCHOOL_COST_MUL 25
#define GROUP_SCHOOL_BUL_COST   10000
#define GROUP_SCHOOL_TECH   1
#define GROUP_SCHOOL_FIREC 40

#define GROUP_BLACKSMITH     27
#define GROUP_BLACKSMITH_COLOUR (white(15))
#define GROUP_BLACKSMITH_COST   5000
#define GROUP_BLACKSMITH_COST_MUL 25
#define GROUP_BLACKSMITH_BUL_COST   1000
#define GROUP_BLACKSMITH_TECH   3
#define GROUP_BLACKSMITH_FIREC 60

#define GROUP_MILL     28
#define GROUP_MILL_COLOUR (white(15))
#define GROUP_MILL_COST   10000
#define GROUP_MILL_COST_MUL 25
#define GROUP_MILL_BUL_COST   1000
#define GROUP_MILL_TECH   25
#define GROUP_MILL_FIREC  60

#define GROUP_POTTERY  29
#define GROUP_POTTERY_COLOUR (red(12))
#define GROUP_POTTERY_COST   1000
#define GROUP_POTTERY_COST_MUL 25
#define GROUP_POTTERY_BUL_COST 1000
#define GROUP_POTTERY_TECH  0
#define GROUP_POTTERY_FIREC 50

#define GROUP_FIRESTATION 30
#define GROUP_FIRESTATION_COLOUR (red(20))
#define GROUP_FIRESTATION_COST   20000
#define GROUP_FIRESTATION_COST_MUL 10
#define GROUP_FIRESTATION_BUL_COST 1000
#define GROUP_FIRESTATION_TECH     22
#define GROUP_FIRESTATION_FIREC 0

#define GROUP_CRICKET 31
#define GROUP_CRICKET_COLOUR (white(20))
#define GROUP_CRICKET_COST   2000
#define GROUP_CRICKET_COST_MUL 3
#define GROUP_CRICKET_BUL_COST 1000
#define GROUP_CRICKET_TECH     12
#define GROUP_CRICKET_FIREC 20

#define GROUP_BURNT        32
#define GROUP_BURNT_COLOUR    (red(30))
#define GROUP_BURNT_COST   0        /* Unused */
#define GROUP_BURNT_COST_MUL   1    /* Unused */
#define GROUP_BURNT_BUL_COST  1000
#define GROUP_BURNT_TECH   0        /* Unused */
#define GROUP_BURNT_FIREC  0

#define GROUP_SHANTY        33
#define GROUP_SHANTY_COLOUR    (red(22))
#define GROUP_SHANTY_COST   0        /* Unused */
#define GROUP_SHANTY_COST_MUL   1    /* Unused */
#define GROUP_SHANTY_BUL_COST  100000
#define GROUP_SHANTY_TECH   0        /* Unused */
#define GROUP_SHANTY_FIREC     25

#define SHANTY_MIN_PP     150
#define SHANTY_POP        50
#define DAYS_BETWEEN_SHANTY (NUMOF_DAYS_IN_MONTH*5)
#define SHANTY_GET_FOOD   50
#define SHANTY_GET_JOBS   5
#define SHANTY_GET_GOODS  50
#define SHANTY_GET_COAL   1
#define SHANTY_GET_ORE    10
#define SHANTY_GET_STEEL  1

#define GROUP_FIRE        34
#define GROUP_FIRE_COLOUR    (red(30))
#define GROUP_FIRE_COST   0        /* Unused */
#define GROUP_FIRE_COST_MUL   1    /* Unused */
#define GROUP_FIRE_BUL_COST  1000
#define GROUP_FIRE_TECH   0        /* Unused */
#define GROUP_FIRE_FIREC  0

#define GROUP_USED        35
#define GROUP_USED_COLOUR (green(12))  /* Unused */
#define GROUP_USED_COST   0            /* Unused */
#define GROUP_USED_COST_MUL  1         /* Unused */
#define GROUP_USED_BUL_COST  0         /* Unused */
#define GROUP_USED_TECH   0            /* Unused */
#define GROUP_USED_FIREC  0            /* Unused */

#define GROUP_RESIDENCE_ML 36
#define GROUP_RESIDENCE_ML_COLOUR (cyan(24))
#define GROUP_RESIDENCE_ML_COST 2000
#define GROUP_RESIDENCE_ML_COST_MUL 25
#define GROUP_RESIDENCE_ML_BUL_COST 1000
#define GROUP_RESIDENCE_ML_TECH 0
#define GROUP_RESIDENCE_ML_FIREC 75

#define GROUP_RESIDENCE_HL 37
#define GROUP_RESIDENCE_HL_COLOUR (cyan(24))
#define GROUP_RESIDENCE_HL_COST 4000
#define GROUP_RESIDENCE_HL_COST_MUL 25
#define GROUP_RESIDENCE_HL_BUL_COST 1000
#define GROUP_RESIDENCE_HL_TECH 0
#define GROUP_RESIDENCE_HL_FIREC 75

#define GROUP_RESIDENCE_LH 38
#define GROUP_RESIDENCE_LH_COLOUR (cyan(24))
#define GROUP_RESIDENCE_LH_COST 800
#define GROUP_RESIDENCE_LH_COST_MUL 25
#define GROUP_RESIDENCE_LH_BUL_COST 1000
#define GROUP_RESIDENCE_LH_TECH 0          /* ?? */
#define GROUP_RESIDENCE_LH_FIREC 75

#define GROUP_RESIDENCE_MH 39
#define GROUP_RESIDENCE_MH_COLOUR (cyan(24))
#define GROUP_RESIDENCE_MH_COST 1600
#define GROUP_RESIDENCE_MH_COST_MUL 25
#define GROUP_RESIDENCE_MH_BUL_COST 1000
#define GROUP_RESIDENCE_MH_TECH 0
#define GROUP_RESIDENCE_MH_FIREC 75

#define GROUP_RESIDENCE_HH 40
#define GROUP_RESIDENCE_HH_COLOUR (cyan(24))
#define GROUP_RESIDENCE_HH_COST 3200
#define GROUP_RESIDENCE_HH_COST_MUL 25
#define GROUP_RESIDENCE_HH_BUL_COST 1000
#define GROUP_RESIDENCE_HH_TECH 0
#define GROUP_RESIDENCE_HH_FIREC 75

#define GROUP_IS_TRANSPORT(group) \
            ((group == GROUP_TRACK) || \
             (group == GROUP_ROAD) || \
             (group == GROUP_RAIL) || \
             (group == GROUP_POWER_LINE))

#define GROUP_IS_RESIDENCE(group) \
            ((group == GROUP_RESIDENCE_LL) || \
             (group == GROUP_RESIDENCE_ML) || \
             (group == GROUP_RESIDENCE_HL) || \
             (group == GROUP_RESIDENCE_LH) || \
             (group == GROUP_RESIDENCE_MH) || \
             (group == GROUP_RESIDENCE_HH))

#define GROUP_RESIDENCE_LL 4
#define GROUP_RESIDENCE_LL_COLOUR (cyan(24))
#define GROUP_RESIDENCE_LL_COST 1000
#define GROUP_RESIDENCE_LL_COST_MUL 25
#define GROUP_RESIDENCE_LL_BUL_COST 1000
#define GROUP_RESIDENCE_LL_TECH 0
#define GROUP_RESIDENCE_LL_FIREC 75


#define MOUSE_TYPE_NORMAL 1
#define MOUSE_TYPE_SQUARE 2
#define MOUSE_BUTTON_REPEAT 4

#define red(x) (32 + x)
#define green(x) (64 + x)
#define yellow(x) (96 + x)
#define blue(x) (128 + x)
#define magenta(x) (160 + x)
#define cyan(x) (192 + x)
#define white(x) (224 + x)


struct map_point_info_struct
{
  int population;
  int flags;
  unsigned short coal_reserve;
  unsigned short ore_reserve;
  int int_1;
  int int_2;
  int int_3;
  int int_4;
  int int_5;
  int int_6;
  int int_7;
};
typedef struct map_point_info_struct Map_Point_Info;


/* Set these flags to true when they need to be updated on the screen */
struct update_scoreboard_struct
{
  int mps;
  int mini;
  int date;
  int money;
  int monthly;
  int yearly_1;
  int yearly_2;
  long int message_area;
};
typedef struct update_scoreboard_struct Update_Scoreboard;


/*
  main functions
  **************
*/
extern int lincity_main (int, char **);
extern void do_error (char *);
extern void window_results (void);
#ifndef LC_X11
extern void parse_args (int, char **);
#endif

/*
  opening
  *******
*/
void load_start_image (void);


/*
  screen functions
  ****************
*/
#ifdef CS_PROFILE
extern void FPgl_write (int, int, char *);
extern void FPgl_getbox (int, int, int, int, void *);
extern void FPgl_putbox (int, int, int, int, void *);
extern void FPgl_fillbox (int, int, int, int, int);
extern void FPgl_hline (int, int, int, int);
extern void FPgl_line (int, int, int, int, int);
extern void FPgl_setpixel (int, int, int);
#endif
extern void setcustompalette (void);
extern void initfont (void);


#ifdef LC_X11
/* ----- X11 functions ----- */
extern void Fgl_write (int, int, char *);
extern void open_write (int, int, char *);
extern void Fgl_getbox (int, int, int, int, void *);
extern void Fgl_putbox (int, int, int, int, void *);
extern void Fgl_fillbox (int, int, int, int, int);
extern void Fgl_hline (int, int, int, int);
extern void Fgl_line (int, int, int, int, int);
extern void Fgl_setpixel (int, int, int);
extern void Fgl_setfontcolors (int, int);
extern void Fgl_setfont (int, int, void*);
extern void Fgl_enableclipping (void);
extern void Fgl_setclippingwindow (int, int, int, int);
extern void Fgl_disableclipping (void);
#ifdef USE_X11_PIXMAPS
#define USE_PIXMAPS
extern void init_pixmaps (void);
extern void init_icon_pixmap (short);
extern void update_pixmap (int, int, int, int, int, int, int, char *);
#endif

#elif defined (WIN32)
/* ----- Win32 functions ----- */
extern void gl_setpalettecolor (long, long, long, long);
extern void Fgl_write (int, int, char *);
extern void open_write (int, int, char *);
extern void Fgl_getbox (int, int, int, int, void *);
extern void Fgl_putbox (int, int, int, int, void *);
extern void Fgl_fillbox (int, int, int, int, int);
extern void Fgl_hline (int, int, int, int);
extern void Fgl_line (int, int, int, int, int);
extern void Fgl_setpixel (int, int, int);
extern void Fgl_setfontcolors (int, int);
extern void Fgl_setfont (int, int, void*);
extern void Fgl_enableclipping (void);
extern void Fgl_setclippingwindow (int, int, int, int);
extern void Fgl_disableclipping (void);
#define USE_PIXMAPS		/* Always */
extern void init_pixmaps (void);
extern void init_icon_pixmap (short);
extern void update_pixmap (int, int, int, int, int, int, int, char *);

#else
/* ----- SVGALIB functions ----- */
/* profiling */
#ifdef CS_PROFILE
#define Fgl_write(a,b,c) FPgl_write(a,b,c)
#define Fgl_getbox(a,b,c,d,e) FPgl_getbox(a,b,c,d,e)
#define Fgl_putbox(a,b,c,d,e) FPgl_putbox(a,b,c,d,e)
#define Fgl_fillbox(a,b,c,d,e) FPgl_fillbox(a,b,c,d,e)
#define Fgl_hline(a,b,c,d) FPgl_hline(a,b,c,d)
#define Fgl_line(a,b,c,d,e) FPgl_line(a,b,c,d,e)
#define Fgl_setpixel(a,b,c) FPgl_setpixel(a,b,c)
#define Fgl_setfontcolors(a,b) gl_setfontcolors(a,b)
#define Fgl_setfont(a,b,c) gl_setfont(a,b,c)
#define Fgl_enableclipping()   gl_enableclipping()
#define Fgl_setclippingwindow(a,b,c,d)   gl_setclippingwindow(a,b,c,d)
#define Fgl_disableclipping()   gl_disableclipping()
#else
#define Fgl_write(a,b,c) gl_write(a,b,c)
#define Fgl_getbox(a,b,c,d,e) gl_getbox(a,b,c,d,e)
#define Fgl_putbox(a,b,c,d,e) gl_putbox(a,b,c,d,e)
#define Fgl_fillbox(a,b,c,d,e) gl_fillbox(a,b,c,d,e)
#define Fgl_hline(a,b,c,d) gl_hline(a,b,c,d)
#define Fgl_line(a,b,c,d,e) gl_line(a,b,c,d,e)
#define Fgl_setpixel(a,b,c) gl_setpixel(a,b,c)
#define Fgl_setfontcolors(a,b) gl_setfontcolors(a,b)
#define Fgl_setfont(a,b,c) gl_setfont(a,b,c)
#define Fgl_enableclipping()   gl_enableclipping()
#define Fgl_setclippingwindow(a,b,c,d)   gl_setclippingwindow(a,b,c,d)
#define Fgl_disableclipping()   gl_disableclipping()
#endif

#endif
/*
  *******   end of lin-city.h   ***********
  *****************************************
*/

#endif /* __lin_city_h__ */
