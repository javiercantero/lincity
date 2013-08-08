/* ---------------------------------------------------------------------- *
 * lintypes.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------- */

/* module header file */
#include "lintypes.h"

/* system libraries */
#include <stdio.h> /* sprintf() */
#include <string.h> /* XXX: portability issue?  for strcpy */

/* app general headers */
#include "lcconfig.h"
#include "lctypes.h" /* CST_USED dependency */
#include "lcintl.h"

/* other modules */
#include "screen.h"
#include "engglobs.h"
#include "shrglobs.h"
#include "fileutil.h"
#include "readpng.h"

/* ----------------------------------------------------------------- */

/*#define GROUP_BARE_COLOUR  (green(12))
#define GROUP_BARE_COST    0
#define GROUP_BARE_COST_MUL 1
#define GROUP_BARE_BUL_COST 1
#define GROUP_BARE_TECH    0
#define GROUP_BARE_FIREC   0*/

#define GROUP_POWER_LINE_COLOUR (yellow(26))
#define GROUP_POWER_LINE_COST 100
#define GROUP_POWER_LINE_COST_MUL 2
#define GROUP_POWER_LINE_BUL_COST 100
#define GROUP_POWER_LINE_TECH 200
#define GROUP_POWER_LINE_FIREC 0

#define GROUP_SOLAR_POWER_COLOUR (yellow(22))
#define GROUP_SOLAR_POWER_COST 500000
#define GROUP_SOLAR_POWER_COST_MUL 5
#define GROUP_SOLAR_POWER_BUL_COST 100000
#define GROUP_SOLAR_POWER_TECH 500
#define GROUP_SOLAR_POWER_FIREC 33

#define GROUP_SUBSTATION_COLOUR (yellow(18))
#define GROUP_SUBSTATION_COST 500
#define GROUP_SUBSTATION_COST_MUL 2
#define GROUP_SUBSTATION_BUL_COST 100
#define GROUP_SUBSTATION_TECH 200
#define GROUP_SUBSTATION_FIREC 50

#define GROUP_RESIDENCE_LL_COLOUR (cyan(24))
#define GROUP_RESIDENCE_LL_COST 1000
#define GROUP_RESIDENCE_LL_COST_MUL 25
#define GROUP_RESIDENCE_LL_BUL_COST 1000
#define GROUP_RESIDENCE_LL_TECH 0
#define GROUP_RESIDENCE_LL_FIREC 75

#define GROUP_ORGANIC_FARM_COLOUR (green(30))
#define GROUP_ORGANIC_FARM_COST 1000
#define GROUP_ORGANIC_FARM_COST_MUL 20
#define GROUP_ORGANIC_FARM_BUL_COST 100
#define GROUP_ORGANIC_FARM_TECH 0
#define GROUP_ORGANIC_FARM_FIREC 20

#define GROUP_MARKET_COLOUR (blue(28))
#define GROUP_MARKET_COST 100
#define GROUP_MARKET_COST_MUL 25
#define GROUP_MARKET_BUL_COST 100
#define GROUP_MARKET_TECH 0
#define GROUP_MARKET_FIREC 80

#define GROUP_TRACK_COLOUR 32	/* 32 is a brown */
#define GROUP_TRACK_COST   1
#define GROUP_TRACK_COST_MUL 25
#define GROUP_TRACK_BUL_COST   10
#define GROUP_TRACK_TECH   0
#define GROUP_TRACK_FIREC  4

#define GROUP_COALMINE_COLOUR 0
#define GROUP_COALMINE_COST   10000
#define GROUP_COALMINE_COST_MUL 25
#define GROUP_COALMINE_BUL_COST   10000
#define GROUP_COALMINE_TECH   85
#define GROUP_COALMINE_FIREC  85

#define GROUP_RAIL_COLOUR  (magenta(18))
#define GROUP_RAIL_COST    500
#define GROUP_RAIL_COST_MUL 10
#define GROUP_RAIL_BUL_COST    1000
#define GROUP_RAIL_TECH    180
#define GROUP_RAIL_FIREC   6

#define GROUP_COAL_POWER_COLOUR 0
#define GROUP_COAL_POWER_COST   100000
#define GROUP_COAL_POWER_COST_MUL 5
#define GROUP_COAL_POWER_BUL_COST   200000
#define GROUP_COAL_POWER_TECH   200
#define GROUP_COAL_POWER_FIREC  80

#define GROUP_ROAD_COLOUR  (white(18))
#define GROUP_ROAD_COST    100
#define GROUP_ROAD_COST_MUL 25
#define GROUP_ROAD_BUL_COST    50
#define GROUP_ROAD_TECH    50
#define GROUP_ROAD_FIREC   4

#define GROUP_INDUSTRY_L_COLOUR (cyan(18))
#define GROUP_INDUSTRY_L_COST 20000
#define GROUP_INDUSTRY_L_COST_MUL 25
#define GROUP_INDUSTRY_L_BUL_COST 20000
#define GROUP_INDUSTRY_L_TECH 160
#define GROUP_INDUSTRY_L_FIREC 70

#define GROUP_UNIVERSITY_COLOUR (blue(22))
#define GROUP_UNIVERSITY_COST 20000
#define GROUP_UNIVERSITY_COST_MUL 25
#define GROUP_UNIVERSITY_BUL_COST 20000
#define GROUP_UNIVERSITY_TECH 150
#define GROUP_UNIVERSITY_FIREC 40

#define GROUP_COMMUNE_COLOUR (green(30))
#define GROUP_COMMUNE_COST  1
#define GROUP_COMMUNE_COST_MUL 2
#define GROUP_COMMUNE_BUL_COST  1000
#define GROUP_COMMUNE_TECH  0
#define GROUP_COMMUNE_FIREC 30

#define GROUP_OREMINE_COLOUR (red(18))
#define GROUP_OREMINE_COST 500
#define GROUP_OREMINE_COST_MUL 10
#define GROUP_OREMINE_BUL_COST 500000
/*#define GROUP_OREMINE_TECH 0*/
#define GROUP_OREMINE_FIREC 0

#define GROUP_TIP_COLOUR (white(16))
#define GROUP_TIP_COST 10000
#define GROUP_TIP_COST_MUL 25
#define GROUP_TIP_BUL_COST 1000000
#define GROUP_TIP_TECH 0
#define GROUP_TIP_FIREC 50

#define GROUP_PORT_COLOUR (blue(28))
#define GROUP_PORT_COST 100000
#define GROUP_PORT_COST_MUL 2
#define GROUP_PORT_BUL_COST 1000
#define GROUP_PORT_TECH 35
#define GROUP_PORT_FIREC 50

#define GROUP_INDUSTRY_H_COLOUR (7)	/* colour 7 is an orange, sort of */
#define GROUP_INDUSTRY_H_COST 50000
#define GROUP_INDUSTRY_H_COST_MUL 20
#define GROUP_INDUSTRY_H_BUL_COST 70000
#define GROUP_INDUSTRY_H_TECH 170
#define GROUP_INDUSTRY_H_FIREC 80

#define GROUP_PARKLAND_COLOUR (green(31))
#define GROUP_PARKLAND_COST   1000
#define GROUP_PARKLAND_COST_MUL 25
#define GROUP_PARKLAND_BUL_COST   1000
/*#define GROUP_PARKLAND_TECH   2*/
#define GROUP_PARKLAND_FIREC 1

#define GROUP_RECYCLE_COLOUR   (green(28))
#define GROUP_RECYCLE_COST    100000
#define GROUP_RECYCLE_COST_MUL 5
#define GROUP_RECYCLE_BUL_COST    1000
#define GROUP_RECYCLE_TECH    232
#define GROUP_RECYCLE_FIREC 10

#define GROUP_WATER_COLOUR    (blue(31))
#define GROUP_WATER_COST      1000000
#define GROUP_WATER_COST_MUL 2
#define GROUP_WATER_BUL_COST      1000000
/*#define GROUP_WATER_TECH      0*/
#define GROUP_WATER_FIREC 0

#define GROUP_HEALTH_COLOUR   (green(24))
#define GROUP_HEALTH_COST     100000
#define GROUP_HEALTH_COST_MUL 2
#define GROUP_HEALTH_BUL_COST     1000
/*#define GROUP_HEALTH_TECH     110*/
#define GROUP_HEALTH_FIREC 2

#define GROUP_ROCKET_COLOUR   (magenta(20))
#define GROUP_ROCKET_COST     700000
#define GROUP_ROCKET_COST_MUL 2
#define GROUP_ROCKET_BUL_COST     1
#define GROUP_ROCKET_TECH     750
#define GROUP_ROCKET_FIREC 0

#define GROUP_WINDMILL_COLOUR (green(25))
#define GROUP_WINDMILL_COST   20000
#define GROUP_WINDMILL_COST_MUL 25
#define GROUP_WINDMILL_BUL_COST   1000
#define GROUP_WINDMILL_TECH   30
#define GROUP_WINDMILL_FIREC  10

#define GROUP_MONUMENT_COLOUR (white(15))
#define GROUP_MONUMENT_COST   10000
#define GROUP_MONUMENT_COST_MUL 25
#define GROUP_MONUMENT_BUL_COST   1000000
#define GROUP_MONUMENT_TECH   0
#define GROUP_MONUMENT_FIREC  0

#define GROUP_SCHOOL_COLOUR (white(15))
#define GROUP_SCHOOL_COST   10000
#define GROUP_SCHOOL_COST_MUL 25
#define GROUP_SCHOOL_BUL_COST   10000
/*#define GROUP_SCHOOL_TECH   1*/
#define GROUP_SCHOOL_FIREC 40

#define GROUP_BLACKSMITH_COLOUR (white(15))
#define GROUP_BLACKSMITH_COST   5000
#define GROUP_BLACKSMITH_COST_MUL 25
#define GROUP_BLACKSMITH_BUL_COST   1000
/*#define GROUP_BLACKSMITH_TECH   3*/
#define GROUP_BLACKSMITH_FIREC 60

#define GROUP_MILL_COLOUR (white(15))
#define GROUP_MILL_COST   10000
#define GROUP_MILL_COST_MUL 25
#define GROUP_MILL_BUL_COST   1000
/*#define GROUP_MILL_TECH   25*/
#define GROUP_MILL_FIREC  60

#define GROUP_POTTERY_COLOUR (red(12))
#define GROUP_POTTERY_COST   1000
#define GROUP_POTTERY_COST_MUL 25
#define GROUP_POTTERY_BUL_COST 1000
/*#define GROUP_POTTERY_TECH  0*/
#define GROUP_POTTERY_FIREC 50

#define GROUP_FIRESTATION_COLOUR (red(20))
#define GROUP_FIRESTATION_COST   20000
#define GROUP_FIRESTATION_COST_MUL 10
#define GROUP_FIRESTATION_BUL_COST 1000
/*#define GROUP_FIRESTATION_TECH     22*/
#define GROUP_FIRESTATION_FIREC 0

#define GROUP_CRICKET_COLOUR (white(20))
#define GROUP_CRICKET_COST   2000
#define GROUP_CRICKET_COST_MUL 3
#define GROUP_CRICKET_BUL_COST 1000
#define GROUP_CRICKET_TECH     12
#define GROUP_CRICKET_FIREC 20

#define GROUP_BURNT_COLOUR    (red(30))
#define GROUP_BURNT_COST   0        /* Unused */
#define GROUP_BURNT_COST_MUL   1    /* Unused */
/*#define GROUP_BURNT_BUL_COST  1000*/
#define GROUP_BURNT_TECH   0        /* Unused */
#define GROUP_BURNT_FIREC  0

#define GROUP_SHANTY_COLOUR    (red(22))
#define GROUP_SHANTY_COST   0        /* Unused */
#define GROUP_SHANTY_COST_MUL   1    /* Unused */
/*#define GROUP_SHANTY_BUL_COST  100000*/
#define GROUP_SHANTY_TECH   0        /* Unused */
#define GROUP_SHANTY_FIREC     25

#define GROUP_FIRE_COLOUR    (red(30))
#define GROUP_FIRE_COST   0        /* Unused */
#define GROUP_FIRE_COST_MUL   1    /* Unused */
#define GROUP_FIRE_BUL_COST  1000
#define GROUP_FIRE_TECH   0        /* Unused */
#define GROUP_FIRE_FIREC  0

#define GROUP_USED_COLOUR (green(12))  /* Unused */
#define GROUP_USED_COST   0            /* Unused */
#define GROUP_USED_COST_MUL  1         /* Unused */
#define GROUP_USED_BUL_COST  0         /* Unused */
#define GROUP_USED_TECH   0            /* Unused */
#define GROUP_USED_FIREC  0            /* Unused */

#define GROUP_RESIDENCE_ML_COLOUR (cyan(24))
#define GROUP_RESIDENCE_ML_COST 2000
#define GROUP_RESIDENCE_ML_COST_MUL 25
#define GROUP_RESIDENCE_ML_BUL_COST 1000
#define GROUP_RESIDENCE_ML_TECH 0
#define GROUP_RESIDENCE_ML_FIREC 75

#define GROUP_RESIDENCE_HL_COLOUR (cyan(24))
#define GROUP_RESIDENCE_HL_COST 4000
#define GROUP_RESIDENCE_HL_COST_MUL 25
#define GROUP_RESIDENCE_HL_BUL_COST 1000
#define GROUP_RESIDENCE_HL_TECH 0
#define GROUP_RESIDENCE_HL_FIREC 75

#define GROUP_RESIDENCE_LH_COLOUR (cyan(24))
#define GROUP_RESIDENCE_LH_COST 800
#define GROUP_RESIDENCE_LH_COST_MUL 25
#define GROUP_RESIDENCE_LH_BUL_COST 1000
#define GROUP_RESIDENCE_LH_TECH 0          /* ?? */
#define GROUP_RESIDENCE_LH_FIREC 75

#define GROUP_RESIDENCE_MH_COLOUR (cyan(24))
#define GROUP_RESIDENCE_MH_COST 1600
#define GROUP_RESIDENCE_MH_COST_MUL 25
#define GROUP_RESIDENCE_MH_BUL_COST 1000
#define GROUP_RESIDENCE_MH_TECH 0
#define GROUP_RESIDENCE_MH_FIREC 75

#define GROUP_RESIDENCE_HH_COLOUR (cyan(24))
#define GROUP_RESIDENCE_HH_COST 3200
#define GROUP_RESIDENCE_HH_COST_MUL 25
#define GROUP_RESIDENCE_HH_BUL_COST 1000
#define GROUP_RESIDENCE_HH_TECH 0
#define GROUP_RESIDENCE_HH_FIREC 75


struct TYPE main_types[NUM_OF_TYPES];

struct GROUP main_groups[NUM_OF_GROUPS] =
{
    /* 0 */
    { N_("Empty"),       /* name */
      false,            /* need credit? */
      GROUP_BARE,       /* group number */
      1,                /* size */
      (green(12)),      /* color */
      1,                /* cost multiplier */
      1,                /* bulldoze cost */
      0,                /* probability of fire */
      0,                /* cost */
      0                 /* tech */
    },
    /* 1 */
    { N_("Power line"),
      false,                           /* need credit? */
      GROUP_POWER_LINE,
      1,                               /* size */
      GROUP_POWER_LINE_COLOUR,
      GROUP_POWER_LINE_COST_MUL,
      GROUP_POWER_LINE_BUL_COST,
      GROUP_POWER_LINE_FIREC,
      GROUP_POWER_LINE_COST,
      GROUP_POWER_LINE_TECH
    },
    /* 2 */
    { N_("Solar PS"),
      true,                            /* need credit? */
      GROUP_SOLAR_POWER,
      4,                               /* size */
      GROUP_SOLAR_POWER_COLOUR,
      GROUP_SOLAR_POWER_COST_MUL,
      GROUP_SOLAR_POWER_BUL_COST,
      GROUP_SOLAR_POWER_FIREC,
      GROUP_SOLAR_POWER_COST,
      GROUP_SOLAR_POWER_TECH
    },
    /* 3 */
    { N_("Substation"),
      false,                           /* need credit? */
      GROUP_SUBSTATION,
      2,                               /* size */
      GROUP_SUBSTATION_COLOUR,
      GROUP_SUBSTATION_COST_MUL,
      GROUP_SUBSTATION_BUL_COST,
      GROUP_SUBSTATION_FIREC,
      GROUP_SUBSTATION_COST,
      GROUP_SUBSTATION_TECH
    },
    /* 4 */
    { N_("Residential LL"),
      false,                           /* need credit? */
      GROUP_RESIDENCE_LL,
      3,                               /* size */
      GROUP_RESIDENCE_LL_COLOUR,
      GROUP_RESIDENCE_LL_COST_MUL,
      GROUP_RESIDENCE_LL_BUL_COST,
      GROUP_RESIDENCE_LL_FIREC,
      GROUP_RESIDENCE_LL_COST,
      GROUP_RESIDENCE_LL_TECH
    },
    /* 5 */
    { N_("Farm"),
      false,                           /* need credit? */
      GROUP_ORGANIC_FARM,
      4,                               /* size */
      GROUP_ORGANIC_FARM_COLOUR,
      GROUP_ORGANIC_FARM_COST_MUL,
      GROUP_ORGANIC_FARM_BUL_COST,
      GROUP_ORGANIC_FARM_FIREC,
      GROUP_ORGANIC_FARM_COST,
      GROUP_ORGANIC_FARM_TECH
    },
    /* 6 */
    { N_("Market"),
      false,                           /* need credit? */
      GROUP_MARKET,
      2,                               /* size */
      GROUP_MARKET_COLOUR,
      GROUP_MARKET_COST_MUL,
      GROUP_MARKET_BUL_COST,
      GROUP_MARKET_FIREC,
      GROUP_MARKET_COST,
      GROUP_MARKET_TECH
    },
    /* 7 */
    { N_("Track"),
      false,                           /* need credit? */
      GROUP_TRACK,
      1,                               /* size */
      GROUP_TRACK_COLOUR,
      GROUP_TRACK_COST_MUL,
      GROUP_TRACK_BUL_COST,
      GROUP_TRACK_FIREC,
      GROUP_TRACK_COST,
      GROUP_TRACK_TECH
    },
    /* 8 */
    { N_("Coalmine"),
      false,                           /* need credit? */
      GROUP_COALMINE,
      4,                               /* size */
      GROUP_COALMINE_COLOUR,
      GROUP_COALMINE_COST_MUL,
      GROUP_COALMINE_BUL_COST,
      GROUP_COALMINE_FIREC,
      GROUP_COALMINE_COST,
      GROUP_COALMINE_TECH
    },
    /* 9 */
    { N_("Railway"),
      false,                           /* need credit? */
      GROUP_RAIL,
      1,                               /* size */
      GROUP_RAIL_COLOUR,
      GROUP_RAIL_COST_MUL,
      GROUP_RAIL_BUL_COST,
      GROUP_RAIL_FIREC,
      GROUP_RAIL_COST,
      GROUP_RAIL_TECH
    },
    /* 10 */
    { N_("Coal PS"),
      false,                           /* need credit? */
      GROUP_COAL_POWER,
      4,                               /* size */
      GROUP_COAL_POWER_COLOUR,
      GROUP_COAL_POWER_COST_MUL,
      GROUP_COAL_POWER_BUL_COST,
      GROUP_COAL_POWER_FIREC,
      GROUP_COAL_POWER_COST,
      GROUP_COAL_POWER_TECH
    },
    /* 11 */
    { N_("Road"),
      false,                           /* need credit? */
      GROUP_ROAD,
      1,                               /* size */
      GROUP_ROAD_COLOUR,
      GROUP_ROAD_COST_MUL,
      GROUP_ROAD_BUL_COST,
      GROUP_ROAD_FIREC,
      GROUP_ROAD_COST,
      GROUP_ROAD_TECH
    },
    /* 12 */
    { N_("Lt. Industry"),
      false,                           /* need credit? */
      GROUP_INDUSTRY_L,
      3,                               /* size */
      GROUP_INDUSTRY_L_COLOUR,
      GROUP_INDUSTRY_L_COST_MUL,
      GROUP_INDUSTRY_L_BUL_COST,
      GROUP_INDUSTRY_L_FIREC,
      GROUP_INDUSTRY_L_COST,
      GROUP_INDUSTRY_L_TECH
    },
    /* 13 */
    { N_("University"),
      true,                           /* need credit? */
      GROUP_UNIVERSITY,
      3,                               /* size */
      GROUP_UNIVERSITY_COLOUR,
      GROUP_UNIVERSITY_COST_MUL,
      GROUP_UNIVERSITY_BUL_COST,
      GROUP_UNIVERSITY_FIREC,
      GROUP_UNIVERSITY_COST,
      GROUP_UNIVERSITY_TECH
    },
    /* 14 */
    { N_("Commune"),
      false,                           /* need credit? */
      GROUP_COMMUNE,
      4,                               /* size */
      GROUP_COMMUNE_COLOUR,
      GROUP_COMMUNE_COST_MUL,
      GROUP_COMMUNE_BUL_COST,
      GROUP_COMMUNE_FIREC,
      GROUP_COMMUNE_COST,
      GROUP_COMMUNE_TECH
    },
    /* 15 */
    { N_("Ore mine"),
      false,                           /* need credit? */
      GROUP_OREMINE,
      4,                               /* size */
      GROUP_OREMINE_COLOUR,
      GROUP_OREMINE_COST_MUL,
      GROUP_OREMINE_BUL_COST,
      GROUP_OREMINE_FIREC,
      GROUP_OREMINE_COST,
      GROUP_OREMINE_TECH
    },
    /* 16 */
    { N_("Rubbish tip"),
      false,                           /* need credit? */
      GROUP_TIP,
      4,                               /* size */
      GROUP_TIP_COLOUR,
      GROUP_TIP_COST_MUL,
      GROUP_TIP_BUL_COST,
      GROUP_TIP_FIREC,
      GROUP_TIP_COST,
      GROUP_TIP_TECH
    },
    /* 17 */
    { N_("Port"),
      false,                           /* need credit? */
      GROUP_PORT,
      4,                               /* size */
      GROUP_PORT_COLOUR,
      GROUP_PORT_COST_MUL,
      GROUP_PORT_BUL_COST,
      GROUP_PORT_FIREC,
      GROUP_PORT_COST,
      GROUP_PORT_TECH
    },
    /* 18 */
    { N_("Hv. Industry"),
      false,                           /* need credit? */
      GROUP_INDUSTRY_H,
      4,                               /* size */
      GROUP_INDUSTRY_H_COLOUR,
      GROUP_INDUSTRY_H_COST_MUL,
      GROUP_INDUSTRY_H_BUL_COST,
      GROUP_INDUSTRY_H_FIREC,
      GROUP_INDUSTRY_H_COST,
      GROUP_INDUSTRY_H_TECH
    },
    /* 19 */
    { N_("Park"),
      true,                           /* need credit? */
      GROUP_PARKLAND,
      1,                               /* size */
      GROUP_PARKLAND_COLOUR,
      GROUP_PARKLAND_COST_MUL,
      GROUP_PARKLAND_BUL_COST,
      GROUP_PARKLAND_FIREC,
      GROUP_PARKLAND_COST,
      GROUP_PARKLAND_TECH
    },
    /* 20 */
    { N_("Recycle"),
      true,                           /* need credit? */
      GROUP_RECYCLE,
      2,                               /* size */
      GROUP_RECYCLE_COLOUR,
      GROUP_RECYCLE_COST_MUL,
      GROUP_RECYCLE_BUL_COST,
      GROUP_RECYCLE_FIREC,
      GROUP_RECYCLE_COST,
      GROUP_RECYCLE_TECH
    },
    /* 21 */
    { N_("Water"),
      false,                           /* need credit? */
      GROUP_WATER,
      1,                               /* size */
      GROUP_WATER_COLOUR,
      GROUP_WATER_COST_MUL,
      GROUP_WATER_BUL_COST,
      GROUP_WATER_FIREC,
      GROUP_WATER_COST,
      GROUP_WATER_TECH
    },
    /* 22 */
    { N_("Health centre"),
      false,                           /* need credit? */
      GROUP_HEALTH,
      2,                               /* size */
      GROUP_HEALTH_COLOUR,
      GROUP_HEALTH_COST_MUL,
      GROUP_HEALTH_BUL_COST,
      GROUP_HEALTH_FIREC,
      GROUP_HEALTH_COST,
      GROUP_HEALTH_TECH
    },
    /* 23 */
    { N_("Rocket pad"),
      true,                            /* need credit? */
      GROUP_ROCKET,
      4,                               /* size */
      GROUP_ROCKET_COLOUR,
      GROUP_ROCKET_COST_MUL,
      GROUP_ROCKET_BUL_COST,
      GROUP_ROCKET_FIREC,
      GROUP_ROCKET_COST,
      GROUP_ROCKET_TECH
    },
    /* 24 */
    { N_("Windmill"),
      false,                           /* need credit? */
      GROUP_WINDMILL,
      2,                               /* size */
      GROUP_WINDMILL_COLOUR,
      GROUP_WINDMILL_COST_MUL,
      GROUP_WINDMILL_BUL_COST,
      GROUP_WINDMILL_FIREC,
      GROUP_WINDMILL_COST,
      GROUP_WINDMILL_TECH
    },
    /* 25 */
    { N_("Monument"),
      false,                           /* need credit? */
      GROUP_MONUMENT,
      2,                               /* size */
      GROUP_MONUMENT_COLOUR,
      GROUP_MONUMENT_COST_MUL,
      GROUP_MONUMENT_BUL_COST,
      GROUP_MONUMENT_FIREC,
      GROUP_MONUMENT_COST,
      GROUP_MONUMENT_TECH
    },
    /* 26 */
    { N_("School"),
      false,                           /* need credit? */
      GROUP_SCHOOL,
      2,                               /* size */
      GROUP_SCHOOL_COLOUR,
      GROUP_SCHOOL_COST_MUL,
      GROUP_SCHOOL_BUL_COST,
      GROUP_SCHOOL_FIREC,
      GROUP_SCHOOL_COST,
      GROUP_SCHOOL_TECH
    },
    /* 27 */
    { N_("Blacksmith"),
      false,                           /* need credit? */
      GROUP_BLACKSMITH,
      2,                               /* size */
      GROUP_BLACKSMITH_COLOUR,
      GROUP_BLACKSMITH_COST_MUL,
      GROUP_BLACKSMITH_BUL_COST,
      GROUP_BLACKSMITH_FIREC,
      GROUP_BLACKSMITH_COST,
      GROUP_BLACKSMITH_TECH
    },
    /* 28 */
    { N_("Mill"),
      false,                           /* need credit? */
      GROUP_MILL,
      2,                               /* size */
      GROUP_MILL_COLOUR,
      GROUP_MILL_COST_MUL,
      GROUP_MILL_BUL_COST,
      GROUP_MILL_FIREC,
      GROUP_MILL_COST,
      GROUP_MILL_TECH
    },
    /* 29 */
    { N_("Pottery"),
      false,                           /* need credit? */
      GROUP_POTTERY,
      2,                               /* size */
      GROUP_POTTERY_COLOUR,
      GROUP_POTTERY_COST_MUL,
      GROUP_POTTERY_BUL_COST,
      GROUP_POTTERY_FIREC,
      GROUP_POTTERY_COST,
      GROUP_POTTERY_TECH
    },
    /* 30 */
    { N_("Fire sta'n"),
      false,                           /* need credit? */
      GROUP_FIRESTATION,
      2,                               /* size */
      GROUP_FIRESTATION_COLOUR,
      GROUP_FIRESTATION_COST_MUL,
      GROUP_FIRESTATION_BUL_COST,
      GROUP_FIRESTATION_FIREC,
      GROUP_FIRESTATION_COST,
      GROUP_FIRESTATION_TECH
    },
    /* 31 */
    { N_("Cricket pitch"),
      false,                           /* need credit? */
      GROUP_CRICKET,
      2,                               /* size */
      GROUP_CRICKET_COLOUR,
      GROUP_CRICKET_COST_MUL,
      GROUP_CRICKET_BUL_COST,
      GROUP_CRICKET_FIREC,
      GROUP_CRICKET_COST,
      GROUP_CRICKET_TECH
    },
    /* 32 */
    /* there is no button for this. */
    { N_("Burnt"),
      false,                           /* need credit? */
      GROUP_BURNT,
      1,                               /* size */
      GROUP_BURNT_COLOUR,
      GROUP_BURNT_COST_MUL,
      GROUP_BURNT_BUL_COST,
      GROUP_BURNT_FIREC,
      GROUP_BURNT_COST,
      GROUP_BURNT_TECH
    },
    /* 33 */
    /* there is no button for this. */
    { N_("Shanty town"),
      false,                           /* need credit? */
      GROUP_SHANTY,
      2,                               /* size */
      GROUP_SHANTY_COLOUR,
      GROUP_SHANTY_COST_MUL,
      GROUP_SHANTY_BUL_COST,
      GROUP_SHANTY_FIREC,
      GROUP_SHANTY_COST,
      GROUP_SHANTY_TECH
    },
    /* 34 */
    /* there is no button for this. */
    { N_("Fire"),
      false,                           /* need credit? */
      GROUP_FIRE,
      1,                               /* size */
      GROUP_FIRE_COLOUR,
      GROUP_FIRE_COST_MUL,
      GROUP_FIRE_BUL_COST,
      GROUP_FIRE_FIREC,
      GROUP_FIRE_COST,
      GROUP_FIRE_TECH
    },
    /* 35 */
    /* there is no button for this. */
    { N_("Used"),
      false,                           /* need credit? */
      GROUP_USED,
      1,                               /* size */
      GROUP_USED_COLOUR,
      GROUP_USED_COST_MUL,
      GROUP_USED_BUL_COST,
      GROUP_USED_FIREC,
      GROUP_USED_COST,
      GROUP_USED_TECH
    },
    /* 36 */
    { N_("Residential ML"),
      false,                           /* need credit? */
      GROUP_RESIDENCE_ML,
      3,                               /* size */
      GROUP_RESIDENCE_ML_COLOUR,
      GROUP_RESIDENCE_ML_COST_MUL,
      GROUP_RESIDENCE_ML_BUL_COST,
      GROUP_RESIDENCE_ML_FIREC,
      GROUP_RESIDENCE_ML_COST,
      GROUP_RESIDENCE_ML_TECH
    },
    /* 37 */
    { N_("Residential HL"),
      false,                           /* need credit? */
      GROUP_RESIDENCE_HL,
      3,                               /* size */
      GROUP_RESIDENCE_HL_COLOUR,
      GROUP_RESIDENCE_HL_COST_MUL,
      GROUP_RESIDENCE_HL_BUL_COST,
      GROUP_RESIDENCE_HL_FIREC,
      GROUP_RESIDENCE_HL_COST,
      GROUP_RESIDENCE_HL_TECH
    },
    /* 38 */
    { N_("Residential"),
      false,                           /* need credit? */
      GROUP_RESIDENCE_LH,
      3,                               /* size */
      GROUP_RESIDENCE_LH_COLOUR,
      GROUP_RESIDENCE_LH_COST_MUL,
      GROUP_RESIDENCE_LH_BUL_COST,
      GROUP_RESIDENCE_LH_FIREC,
      GROUP_RESIDENCE_LH_COST,
      GROUP_RESIDENCE_LH_TECH
    },
    /* 39 */
    { N_("Residential"),
      false,                           /* need credit? */
      GROUP_RESIDENCE_MH,
      3,                               /* size */
      GROUP_RESIDENCE_MH_COLOUR,
      GROUP_RESIDENCE_MH_COST_MUL,
      GROUP_RESIDENCE_MH_BUL_COST,
      GROUP_RESIDENCE_MH_FIREC,
      GROUP_RESIDENCE_MH_COST,
      GROUP_RESIDENCE_MH_TECH
    },
    /* 40 */
    { N_("Residential"),
      false,                           /* need credit? */
      GROUP_RESIDENCE_LH,
      3,                               /* size */
      GROUP_RESIDENCE_HH_COLOUR,
      GROUP_RESIDENCE_HH_COST_MUL,
      GROUP_RESIDENCE_HH_BUL_COST,
      GROUP_RESIDENCE_HH_FIREC,
      GROUP_RESIDENCE_HH_COST,
      GROUP_RESIDENCE_HH_TECH
    },
    /* 41 */
    /* End of Data */
    { "EOF",
      false,                           /* need credit? */
      0,
      0,                               /* size */
      0,
      0,
      0,
      0,
      0,
      0
    }
};

#if defined (commentout)
/*
 * name of files with graphics (icons) in .csi format
 * -- obsoletes now 
 */
#define CST_GREEN_G		"green.csi"
#define CST_POWERL_H_L_G	"powerlhl.csi"
#define CST_POWERL_V_L_G  	"powerlvl.csi"
#define CST_POWERL_LD_L_G 	"powerlldl.csi"
#define CST_POWERL_RD_L_G 	"powerlrdl.csi"
#define CST_POWERL_LU_L_G  	"powerllul.csi"
#define CST_POWERL_RU_L_G  	"powerlrul.csi"
#define CST_POWERL_LDU_L_G	"powerlldul.csi"
#define CST_POWERL_LDR_L_G	"powerlldrl.csi"
#define CST_POWERL_LUR_L_G	"powerllurl.csi"
#define CST_POWERL_UDR_L_G	"powerludrl.csi"
#define CST_POWERL_LUDR_L_G	"powerlludrl.csi"
#define CST_POWERL_H_D_G        "powerlhd.csi"
#define CST_POWERL_V_D_G        "powerlvd.csi"
#define CST_POWERL_LD_D_G       "powerlldd.csi"
#define CST_POWERL_RD_D_G       "powerlrdd.csi"
#define CST_POWERL_LU_D_G       "powerllud.csi"
#define CST_POWERL_RU_D_G       "powerlrud.csi"
#define CST_POWERL_LDU_D_G      "powerlldud.csi"
#define CST_POWERL_LDR_D_G      "powerlldrd.csi"
#define CST_POWERL_LUR_D_G      "powerllurd.csi"
#define CST_POWERL_UDR_D_G      "powerludrd.csi"
#define CST_POWERL_LUDR_D_G     "powerlludrd.csi"
#define CST_SHANTY_G            "shanty.csi"
#define CST_POWERS_SOLAR_G	"powerssolar.csi"
#define CST_POWERS_COAL_EMPTY_G	"powerscoal-empty.csi"
#define CST_POWERS_COAL_LOW_G   "powerscoal-low.csi"
#define CST_POWERS_COAL_MED_G   "powerscoal-med.csi"
#define CST_POWERS_COAL_FULL_G  "powerscoal-full.csi"
#define CST_BURNT_G		"burnt_land.csi"
#define CST_SUBSTATION_R_G	"substation-R.csi"
#define CST_SUBSTATION_G_G      "substation-G.csi"
#define CST_SUBSTATION_RG_G     "substation-RG.csi"
#define CST_UNIVERSITY_G	"university.csi"
#define CST_RESIDENCE_LL_G	"reslowlow.csi"
#define CST_RESIDENCE_ML_G	"resmedlow.csi"
#define CST_RESIDENCE_HL_G	"reshilow.csi"
#define CST_RESIDENCE_LH_G      "reslowhi.csi"
#define CST_RESIDENCE_MH_G      "resmedhi.csi"
#define CST_RESIDENCE_HH_G      "reshihi.csi"
#define CST_MARKET_EMPTY_G	"market-empty.csi"
#define CST_MARKET_LOW_G        "market-low.csi"
#define CST_MARKET_MED_G        "market-med.csi"
#define CST_MARKET_FULL_G       "market-full.csi"
#define CST_RECYCLE_G		"recycle-centre.csi"
#define CST_TRACK_LR_G		"tracklr.csi"
#define CST_TRACK_LU_G          "tracklu.csi"
#define CST_TRACK_LD_G          "trackld.csi"
#define CST_TRACK_UD_G          "trackud.csi"
#define CST_TRACK_UR_G          "trackur.csi"
#define CST_TRACK_DR_G          "trackdr.csi"
#define CST_TRACK_LUR_G         "tracklur.csi"
#define CST_TRACK_LDR_G         "trackldr.csi"
#define CST_TRACK_LUD_G         "tracklud.csi"
#define CST_TRACK_UDR_G         "trackudr.csi"
#define CST_TRACK_LUDR_G        "trackludr.csi"
#define CST_PARKLAND_PLANE_G	"parkland-plane.csi"
#define CST_PARKLAND_LAKE_G	"parkland-lake.csi"
#define CST_MONUMENT_0_G	"monument0.csi"
#define CST_MONUMENT_1_G        "monument1.csi"
#define CST_MONUMENT_2_G        "monument2.csi"
#define CST_MONUMENT_3_G        "monument3.csi"
#define CST_MONUMENT_4_G        "monument4.csi"
#define CST_MONUMENT_5_G        "monument5.csi"
#define CST_COALMINE_EMPTY_G	"coalmine-empty.csi"
#define CST_COALMINE_LOW_G	"coalmine-low.csi"
#define CST_COALMINE_MED_G	"coalmine-med.csi"
#define CST_COALMINE_FULL_G	"coalmine-full.csi"
#define CST_RAIL_LR_G          "raillr.csi"
#define CST_RAIL_LU_G          "raillu.csi"
#define CST_RAIL_LD_G          "railld.csi"
#define CST_RAIL_UD_G          "railud.csi"
#define CST_RAIL_UR_G          "railur.csi"
#define CST_RAIL_DR_G          "raildr.csi"
#define CST_RAIL_LUR_G         "raillur.csi"
#define CST_RAIL_LDR_G         "railldr.csi"
#define CST_RAIL_LUD_G         "raillud.csi"
#define CST_RAIL_UDR_G         "railudr.csi"
#define CST_RAIL_LUDR_G        "railludr.csi"
#define CST_FIRE_1_G           "fire1.csi"
#define CST_FIRE_2_G           "fire2.csi"
#define CST_FIRE_3_G           "fire3.csi"
#define CST_FIRE_4_G           "fire4.csi"
#define CST_FIRE_5_G           "fire5.csi"
#define CST_FIRE_DONE1_G       "firedone1.csi"
#define CST_FIRE_DONE2_G       "firedone2.csi"
#define CST_FIRE_DONE3_G       "firedone3.csi"
#define CST_FIRE_DONE4_G       "firedone4.csi"
#define CST_ROAD_LR_G          "roadlr.csi"
#define CST_ROAD_LU_G          "roadlu.csi"
#define CST_ROAD_LD_G          "roadld.csi"
#define CST_ROAD_UD_G          "roadud.csi"
#define CST_ROAD_UR_G          "roadur.csi"
#define CST_ROAD_DR_G          "roaddr.csi"
#define CST_ROAD_LUR_G         "roadlur.csi"
#define CST_ROAD_LDR_G         "roadldr.csi"
#define CST_ROAD_LUD_G         "roadlud.csi"
#define CST_ROAD_UDR_G         "roadudr.csi"
#define CST_ROAD_LUDR_G        "roadludr.csi"
#define CST_OREMINE_5_G         "oremine5.csi"
#define CST_OREMINE_6_G         "oremine6.csi"
#define CST_OREMINE_7_G         "oremine7.csi"
#define CST_OREMINE_8_G         "oremine8.csi"
#define CST_OREMINE_1_G		"oremine1.csi"
#define CST_OREMINE_2_G		"oremine2.csi"
#define CST_OREMINE_3_G		"oremine3.csi"
#define CST_OREMINE_4_G		"oremine4.csi"
#define CST_HEALTH_G		"health.csi"
#define CST_SCHOOL_G		"school0.csi"
#define CST_EX_PORT_G		"ex_port.csi"
#define CST_MILL_0_G            "mill0.csi"
#define CST_MILL_1_G            "mill1.csi"
#define CST_MILL_2_G            "mill2.csi"
#define CST_MILL_3_G            "mill3.csi"
#define CST_MILL_4_G            "mill4.csi"
#define CST_MILL_5_G            "mill5.csi"
#define CST_MILL_6_G            "mill6.csi"
#define CST_ROCKET_1_G          "rocket1.csi"
#define CST_ROCKET_2_G		"rocket2.csi"
#define CST_ROCKET_3_G		"rocket3.csi"
#define CST_ROCKET_4_G		"rocket4.csi"
#define CST_ROCKET_5_G          "rocket5.csi"
#define CST_ROCKET_6_G          "rocket6.csi"
#define CST_ROCKET_7_G		"rocket7.csi"
#define CST_ROCKET_FLOWN_G	"rocketflown.csi"
#define CST_WINDMILL_1_G_G      "windmill1g.csi"
#define CST_WINDMILL_2_G_G      "windmill2g.csi"
#define CST_WINDMILL_3_G_G      "windmill3g.csi"
#define CST_WINDMILL_1_RG_G     "windmill1rg.csi"
#define CST_WINDMILL_2_RG_G     "windmill2rg.csi"
#define CST_WINDMILL_3_RG_G     "windmill3rg.csi"
#define CST_WINDMILL_1_R_G      "windmill1r.csi"
#define CST_WINDMILL_2_R_G      "windmill2r.csi"
#define CST_WINDMILL_3_R_G      "windmill3r.csi"
#define CST_WINDMILL_1_W_G      "windmill1w.csi"
#define CST_WINDMILL_2_W_G      "windmill2w.csi"
#define CST_WINDMILL_3_W_G      "windmill3w.csi"
#define CST_BLACKSMITH_0_G        "blacksmith0.csi"
#define CST_BLACKSMITH_1_G        "blacksmith1.csi"
#define CST_BLACKSMITH_2_G        "blacksmith2.csi"
#define CST_BLACKSMITH_3_G        "blacksmith3.csi"
#define CST_BLACKSMITH_4_G        "blacksmith4.csi"
#define CST_BLACKSMITH_5_G        "blacksmith5.csi"
#define CST_BLACKSMITH_6_G        "blacksmith6.csi"
#define CST_POTTERY_0_G           "pottery0.csi"
#define CST_POTTERY_1_G           "pottery1.csi"
#define CST_POTTERY_2_G           "pottery2.csi"
#define CST_POTTERY_3_G           "pottery3.csi"
#define CST_POTTERY_4_G           "pottery4.csi"
#define CST_POTTERY_5_G           "pottery5.csi"
#define CST_POTTERY_6_G           "pottery6.csi"
#define CST_POTTERY_7_G           "pottery7.csi"
#define CST_POTTERY_8_G           "pottery8.csi"
#define CST_POTTERY_9_G           "pottery9.csi"
#define CST_POTTERY_10_G          "pottery10.csi"
#define CST_WATER_G             "water.csi"
#define CST_WATER_D_G           "waterd.csi"
#define CST_WATER_R_G           "waterr.csi"
#define CST_WATER_U_G           "wateru.csi"
#define CST_WATER_L_G           "waterl.csi"
#define CST_WATER_LR_G          "waterlr.csi"
#define CST_WATER_UD_G          "waterud.csi"
#define CST_WATER_LD_G          "waterld.csi"
#define CST_WATER_RD_G          "waterrd.csi"
#define CST_WATER_LU_G          "waterlu.csi"
#define CST_WATER_UR_G          "waterur.csi"
#define CST_WATER_LUD_G         "waterlud.csi"
#define CST_WATER_LRD_G         "waterlrd.csi"
#define CST_WATER_LUR_G         "waterlur.csi"
#define CST_WATER_URD_G         "waterurd.csi"
#define CST_WATER_LURD_G        "waterlurd.csi"
#define CST_CRICKET_1_G         "cricket1.csi"
#define CST_CRICKET_2_G         "cricket2.csi"
#define CST_CRICKET_3_G         "cricket3.csi"
#define CST_CRICKET_4_G         "cricket4.csi"
#define CST_CRICKET_5_G         "cricket5.csi"
#define CST_CRICKET_6_G         "cricket6.csi"
#define CST_CRICKET_7_G         "cricket7.csi"
#define CST_FIRESTATION_1_G       "firestation1.csi"
#define CST_FIRESTATION_2_G       "firestation2.csi"
#define CST_FIRESTATION_3_G       "firestation3.csi"
#define CST_FIRESTATION_4_G       "firestation4.csi"
#define CST_FIRESTATION_5_G       "firestation5.csi"
#define CST_FIRESTATION_6_G       "firestation6.csi"
#define CST_FIRESTATION_7_G       "firestation7.csi"
#define CST_FIRESTATION_8_G       "firestation8.csi"
#define CST_FIRESTATION_9_G       "firestation9.csi"
#define CST_FIRESTATION_10_G      "firestation10.csi"
#define CST_TIP_0_G             "tip0.csi"
#define CST_TIP_1_G             "tip1.csi"
#define CST_TIP_2_G             "tip2.csi"
#define CST_TIP_3_G             "tip3.csi"
#define CST_TIP_4_G             "tip4.csi"
#define CST_TIP_5_G             "tip5.csi"
#define CST_TIP_6_G             "tip6.csi"
#define CST_TIP_7_G             "tip7.csi"
#define CST_TIP_8_G             "tip8.csi"
#define CST_COMMUNE_1_G         "commune1.csi"
#define CST_COMMUNE_2_G         "commune2.csi"
#define CST_COMMUNE_3_G         "commune3.csi"
#define CST_COMMUNE_4_G         "commune4.csi"
#define CST_COMMUNE_5_G         "commune5.csi"
#define CST_COMMUNE_6_G         "commune6.csi"
#define CST_COMMUNE_7_G         "commune7.csi"
#define CST_COMMUNE_8_G         "commune8.csi"
#define CST_COMMUNE_9_G         "commune9.csi"
#define CST_COMMUNE_10_G        "commune10.csi"
#define CST_COMMUNE_11_G        "commune11.csi"
#define CST_COMMUNE_12_G        "commune12.csi"
#define CST_COMMUNE_13_G        "commune13.csi"
#define CST_COMMUNE_14_G        "commune14.csi"
#define CST_INDUSTRY_H_C_G      "industryhc.csi"
#define CST_INDUSTRY_H_L1_G      "industryhl1.csi"
#define CST_INDUSTRY_H_L2_G      "industryhl2.csi"
#define CST_INDUSTRY_H_L3_G      "industryhl3.csi"
#define CST_INDUSTRY_H_L4_G      "industryhl4.csi"
#define CST_INDUSTRY_H_L5_G      "industryhl5.csi"
#define CST_INDUSTRY_H_L6_G      "industryhl6.csi"
#define CST_INDUSTRY_H_L7_G      "industryhl7.csi"
#define CST_INDUSTRY_H_L8_G      "industryhl8.csi"
#define CST_INDUSTRY_H_M1_G      "industryhm1.csi"
#define CST_INDUSTRY_H_M2_G      "industryhm2.csi"
#define CST_INDUSTRY_H_M3_G      "industryhm3.csi"
#define CST_INDUSTRY_H_M4_G      "industryhm4.csi"
#define CST_INDUSTRY_H_M5_G      "industryhm5.csi"
#define CST_INDUSTRY_H_M6_G      "industryhm6.csi"
#define CST_INDUSTRY_H_M7_G      "industryhm7.csi"
#define CST_INDUSTRY_H_M8_G      "industryhm8.csi"
#define CST_INDUSTRY_H_H1_G      "industryhh1.csi"
#define CST_INDUSTRY_H_H2_G      "industryhh2.csi"
#define CST_INDUSTRY_H_H3_G      "industryhh3.csi"
#define CST_INDUSTRY_H_H4_G      "industryhh4.csi"
#define CST_INDUSTRY_H_H5_G      "industryhh5.csi"
#define CST_INDUSTRY_H_H6_G      "industryhh6.csi"
#define CST_INDUSTRY_H_H7_G      "industryhh7.csi"
#define CST_INDUSTRY_H_H8_G      "industryhh8.csi"
#define CST_INDUSTRY_L_C_G       "industrylq1.csi"
#define CST_INDUSTRY_L_Q1_G      "industrylq1.csi"
#define CST_INDUSTRY_L_Q2_G      "industrylq2.csi"
#define CST_INDUSTRY_L_Q3_G      "industrylq3.csi"
#define CST_INDUSTRY_L_Q4_G      "industrylq4.csi"
#define CST_INDUSTRY_L_L1_G      "industryll1.csi"
#define CST_INDUSTRY_L_L2_G      "industryll2.csi"
#define CST_INDUSTRY_L_L3_G      "industryll3.csi"
#define CST_INDUSTRY_L_L4_G      "industryll4.csi"
#define CST_INDUSTRY_L_M1_G      "industrylm1.csi"
#define CST_INDUSTRY_L_M2_G      "industrylm2.csi"
#define CST_INDUSTRY_L_M3_G      "industrylm3.csi"
#define CST_INDUSTRY_L_M4_G      "industrylm4.csi"
#define CST_INDUSTRY_L_H1_G      "industrylh1.csi"
#define CST_INDUSTRY_L_H2_G      "industrylh2.csi"
#define CST_INDUSTRY_L_H3_G      "industrylh3.csi"
#define CST_INDUSTRY_L_H4_G      "industrylh4.csi"
#define CST_FARM_O0_G            "farm0.csi"
#define CST_FARM_O1_G            "farm1.csi"
#define CST_FARM_O2_G            "farm2.csi"
#define CST_FARM_O3_G            "farm3.csi"
#define CST_FARM_O4_G            "farm4.csi"
#define CST_FARM_O5_G            "farm5.csi"
#define CST_FARM_O6_G            "farm6.csi"
#define CST_FARM_O7_G            "farm7.csi"
#define CST_FARM_O8_G            "farm8.csi"
#define CST_FARM_O9_G            "farm9.csi"
#define CST_FARM_O10_G           "farm10.csi"
#define CST_FARM_O11_G           "farm11.csi"
#define CST_FARM_O12_G           "farm12.csi"
#define CST_FARM_O13_G           "farm13.csi"
#define CST_FARM_O14_G           "farm14.csi"
#define CST_FARM_O15_G           "farm15.csi"
#define CST_FARM_O16_G           "farm16.csi"
#endif

void init_types (void)
{
    char png_file[LC_PATH_MAX], txt_file[LC_PATH_MAX];
    sprintf (png_file, "%s%c%s", opening_path, PATH_SLASH, "icons.png");
    sprintf (txt_file, "%s%c%s", opening_path, PATH_SLASH, "iconlist.txt");

    load_png_graphics (txt_file,png_file);

#if defined (commentout)
    main_types[CST_GREEN].group=GROUP_BARE;
    main_types[CST_GREEN].graphic=load_graphic(CST_GREEN_G);

    main_types[CST_POWERL_H_L].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_H_L].graphic=load_graphic(CST_POWERL_H_L_G);

    main_types[CST_POWERL_V_L].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_V_L].graphic=load_graphic(CST_POWERL_V_L_G);

    main_types[CST_POWERL_LD_L].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LD_L].graphic=load_graphic(CST_POWERL_LD_L_G);

    main_types[CST_POWERL_RD_L].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_RD_L].graphic=load_graphic(CST_POWERL_RD_L_G);

    main_types[CST_POWERL_LU_L].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LU_L].graphic=load_graphic(CST_POWERL_LU_L_G);

    main_types[CST_POWERL_RU_L].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_RU_L].graphic=load_graphic(CST_POWERL_RU_L_G);

    main_types[CST_POWERL_LDU_L].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LDU_L].graphic=load_graphic(CST_POWERL_LDU_L_G);

    main_types[CST_POWERL_LDR_L].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LDR_L].graphic=load_graphic(CST_POWERL_LDR_L_G);

    main_types[CST_POWERL_LUR_L].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LUR_L].graphic=load_graphic(CST_POWERL_LUR_L_G);

    main_types[CST_POWERL_UDR_L].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_UDR_L].graphic=load_graphic(CST_POWERL_UDR_L_G);

    main_types[CST_POWERL_LUDR_L].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LUDR_L].graphic
	    =load_graphic(CST_POWERL_LUDR_L_G);

    main_types[CST_POWERL_H_D].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_H_D].graphic=load_graphic(CST_POWERL_H_D_G);

    main_types[CST_POWERL_V_D].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_V_D].graphic=load_graphic(CST_POWERL_V_D_G);

    main_types[CST_POWERL_LD_D].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LD_D].graphic=load_graphic(CST_POWERL_LD_D_G);

    main_types[CST_POWERL_RD_D].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_RD_D].graphic=load_graphic(CST_POWERL_RD_D_G);

    main_types[CST_POWERL_LU_D].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LU_D].graphic=load_graphic(CST_POWERL_LU_D_G);

    main_types[CST_POWERL_RU_D].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_RU_D].graphic=load_graphic(CST_POWERL_RU_D_G);

    main_types[CST_POWERL_LDU_D].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LDU_D].graphic=load_graphic(CST_POWERL_LDU_D_G);

    main_types[CST_POWERL_LDR_D].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LDR_D].graphic=load_graphic(CST_POWERL_LDR_D_G);

    main_types[CST_POWERL_LUR_D].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LUR_D].graphic=load_graphic(CST_POWERL_LUR_D_G);

    main_types[CST_POWERL_UDR_D].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_UDR_D].graphic=load_graphic(CST_POWERL_UDR_D_G);

    main_types[CST_POWERL_LUDR_D].group=GROUP_POWER_LINE;
    main_types[CST_POWERL_LUDR_D].graphic
	    =load_graphic(CST_POWERL_LUDR_D_G);

    main_types[CST_POWERS_SOLAR].group=GROUP_SOLAR_POWER;
    main_types[CST_POWERS_SOLAR].graphic=load_graphic(CST_POWERS_SOLAR_G);

    main_types[CST_POWERS_COAL_EMPTY].group=GROUP_COAL_POWER;
    main_types[CST_POWERS_COAL_EMPTY].graphic
	    =load_graphic(CST_POWERS_COAL_EMPTY_G);

    main_types[CST_POWERS_COAL_LOW].group=GROUP_COAL_POWER;
    main_types[CST_POWERS_COAL_LOW].graphic
	    =load_graphic(CST_POWERS_COAL_LOW_G);

    prog_box("",12);

    main_types[CST_POWERS_COAL_MED].group=GROUP_COAL_POWER;
    main_types[CST_POWERS_COAL_MED].graphic
	    =load_graphic(CST_POWERS_COAL_MED_G);

    main_types[CST_POWERS_COAL_FULL].group=GROUP_COAL_POWER;
    main_types[CST_POWERS_COAL_FULL].graphic
	    =load_graphic(CST_POWERS_COAL_FULL_G);

    main_types[CST_SUBSTATION_R].group=GROUP_SUBSTATION;
    main_types[CST_SUBSTATION_R].graphic=load_graphic(CST_SUBSTATION_R_G);

    main_types[CST_SUBSTATION_G].group=GROUP_SUBSTATION;
    main_types[CST_SUBSTATION_G].graphic=load_graphic(CST_SUBSTATION_G_G);

    main_types[CST_SUBSTATION_RG].group=GROUP_SUBSTATION;
    main_types[CST_SUBSTATION_RG].graphic
	    =load_graphic(CST_SUBSTATION_RG_G);

    main_types[CST_RESIDENCE_LL].group=GROUP_RESIDENCE_LL;
    main_types[CST_RESIDENCE_LL].graphic=load_graphic(CST_RESIDENCE_LL_G);

    main_types[CST_RESIDENCE_ML].group=GROUP_RESIDENCE_ML;
    main_types[CST_RESIDENCE_ML].graphic
	    =load_graphic(CST_RESIDENCE_ML_G);

    main_types[CST_RESIDENCE_HL].group=GROUP_RESIDENCE_HL;
    main_types[CST_RESIDENCE_HL].graphic
	    =load_graphic(CST_RESIDENCE_HL_G);

    main_types[CST_RESIDENCE_LH].group=GROUP_RESIDENCE_LH;
    main_types[CST_RESIDENCE_LH].graphic=load_graphic(CST_RESIDENCE_LH_G);

    main_types[CST_RESIDENCE_MH].group=GROUP_RESIDENCE_MH;
    main_types[CST_RESIDENCE_MH].graphic=load_graphic(CST_RESIDENCE_MH_G);

    main_types[CST_RESIDENCE_HH].group=GROUP_RESIDENCE_HH;
    main_types[CST_RESIDENCE_HH].graphic=load_graphic(CST_RESIDENCE_HH_G);


    main_types[CST_FARM_O0].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O0].graphic=load_graphic(CST_FARM_O0_G);

    main_types[CST_FARM_O1].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O1].graphic=load_graphic(CST_FARM_O1_G);

    main_types[CST_FARM_O2].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O2].graphic=load_graphic(CST_FARM_O2_G);

    main_types[CST_FARM_O3].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O3].graphic=load_graphic(CST_FARM_O3_G);

    main_types[CST_FARM_O4].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O4].graphic=load_graphic(CST_FARM_O4_G);

    main_types[CST_FARM_O5].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O5].graphic=load_graphic(CST_FARM_O5_G);

    main_types[CST_FARM_O6].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O6].graphic=load_graphic(CST_FARM_O6_G);

    main_types[CST_FARM_O7].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O7].graphic=load_graphic(CST_FARM_O7_G);

    main_types[CST_FARM_O8].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O8].graphic=load_graphic(CST_FARM_O8_G);

    main_types[CST_FARM_O9].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O9].graphic=load_graphic(CST_FARM_O9_G);

    main_types[CST_FARM_O10].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O10].graphic=load_graphic(CST_FARM_O10_G);

    main_types[CST_FARM_O11].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O11].graphic=load_graphic(CST_FARM_O11_G);

    main_types[CST_FARM_O12].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O12].graphic=load_graphic(CST_FARM_O12_G);

    main_types[CST_FARM_O13].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O13].graphic=load_graphic(CST_FARM_O13_G);

    main_types[CST_FARM_O14].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O14].graphic=load_graphic(CST_FARM_O14_G);

    main_types[CST_FARM_O15].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O15].graphic=load_graphic(CST_FARM_O15_G);

    main_types[CST_FARM_O16].group=GROUP_ORGANIC_FARM;
    main_types[CST_FARM_O16].graphic=load_graphic(CST_FARM_O16_G);

    main_types[CST_MARKET_EMPTY].group=GROUP_MARKET;
    main_types[CST_MARKET_EMPTY].graphic
	    =load_graphic(CST_MARKET_EMPTY_G);

    main_types[CST_MARKET_LOW].group=GROUP_MARKET;
    main_types[CST_MARKET_LOW].graphic
	    =load_graphic(CST_MARKET_LOW_G);

    main_types[CST_MARKET_MED].group=GROUP_MARKET;
    main_types[CST_MARKET_MED].graphic
	    =load_graphic(CST_MARKET_MED_G);

    main_types[CST_MARKET_FULL].group=GROUP_MARKET;
    main_types[CST_MARKET_FULL].graphic
	    =load_graphic(CST_MARKET_FULL_G);

    main_types[CST_TRACK_LR].group=GROUP_TRACK;
    main_types[CST_TRACK_LR].graphic=load_graphic(CST_TRACK_LR_G);

    main_types[CST_TRACK_LU].group=GROUP_TRACK;
    main_types[CST_TRACK_LU].graphic=load_graphic(CST_TRACK_LU_G);

    main_types[CST_TRACK_LD].group=GROUP_TRACK;
    main_types[CST_TRACK_LD].graphic=load_graphic(CST_TRACK_LD_G);

    main_types[CST_TRACK_UD].group=GROUP_TRACK;
    main_types[CST_TRACK_UD].graphic=load_graphic(CST_TRACK_UD_G);

    main_types[CST_TRACK_UR].group=GROUP_TRACK;
    main_types[CST_TRACK_UR].graphic=load_graphic(CST_TRACK_UR_G);

    main_types[CST_TRACK_DR].group=GROUP_TRACK;
    main_types[CST_TRACK_DR].graphic=load_graphic(CST_TRACK_DR_G);

    main_types[CST_TRACK_LUR].group=GROUP_TRACK;
    main_types[CST_TRACK_LUR].graphic=load_graphic(CST_TRACK_LUR_G);

    main_types[CST_TRACK_LDR].group=GROUP_TRACK;
    main_types[CST_TRACK_LDR].graphic=load_graphic(CST_TRACK_LDR_G);

    main_types[CST_TRACK_LUD].group=GROUP_TRACK;
    main_types[CST_TRACK_LUD].graphic=load_graphic(CST_TRACK_LUD_G);

    main_types[CST_TRACK_UDR].group=GROUP_TRACK;
    main_types[CST_TRACK_UDR].graphic=load_graphic(CST_TRACK_UDR_G);

    main_types[CST_TRACK_LUDR].group=GROUP_TRACK;
    main_types[CST_TRACK_LUDR].graphic=load_graphic(CST_TRACK_LUDR_G);

    main_types[CST_COALMINE_EMPTY].group=GROUP_COALMINE;
    main_types[CST_COALMINE_EMPTY].graphic
	    =load_graphic(CST_COALMINE_EMPTY_G);

    prog_box("",25);

    main_types[CST_COALMINE_LOW].group=GROUP_COALMINE;
    main_types[CST_COALMINE_LOW].graphic=load_graphic(CST_COALMINE_LOW_G);

    main_types[CST_COALMINE_MED].group=GROUP_COALMINE;
    main_types[CST_COALMINE_MED].graphic=load_graphic(CST_COALMINE_MED_G);

    main_types[CST_COALMINE_FULL].group=GROUP_COALMINE;
    main_types[CST_COALMINE_FULL].graphic
	    =load_graphic(CST_COALMINE_FULL_G);

    main_types[CST_RAIL_LR].group=GROUP_RAIL;
    main_types[CST_RAIL_LR].graphic=load_graphic(CST_RAIL_LR_G);

    main_types[CST_RAIL_LU].group=GROUP_RAIL;
    main_types[CST_RAIL_LU].graphic=load_graphic(CST_RAIL_LU_G);

    main_types[CST_RAIL_LD].group=GROUP_RAIL;
    main_types[CST_RAIL_LD].graphic=load_graphic(CST_RAIL_LD_G);

    main_types[CST_RAIL_UD].group=GROUP_RAIL;
    main_types[CST_RAIL_UD].graphic=load_graphic(CST_RAIL_UD_G);

    main_types[CST_RAIL_UR].group=GROUP_RAIL;
    main_types[CST_RAIL_UR].graphic=load_graphic(CST_RAIL_UR_G);

    main_types[CST_RAIL_DR].group=GROUP_RAIL;
    main_types[CST_RAIL_DR].graphic=load_graphic(CST_RAIL_DR_G);

    main_types[CST_RAIL_LUR].group=GROUP_RAIL;
    main_types[CST_RAIL_LUR].graphic=load_graphic(CST_RAIL_LUR_G);

    main_types[CST_RAIL_LDR].group=GROUP_RAIL;
    main_types[CST_RAIL_LDR].graphic=load_graphic(CST_RAIL_LDR_G);

    main_types[CST_RAIL_LUD].group=GROUP_RAIL;
    main_types[CST_RAIL_LUD].graphic=load_graphic(CST_RAIL_LUD_G);

    prog_box("",30);

    main_types[CST_RAIL_UDR].group=GROUP_RAIL;
    main_types[CST_RAIL_UDR].graphic=load_graphic(CST_RAIL_UDR_G);

    main_types[CST_RAIL_LUDR].group=GROUP_RAIL;
    main_types[CST_RAIL_LUDR].graphic=load_graphic(CST_RAIL_LUDR_G);

    main_types[CST_ROAD_LR].group=GROUP_ROAD;
    main_types[CST_ROAD_LR].graphic=load_graphic(CST_ROAD_LR_G);

    main_types[CST_ROAD_LU].group=GROUP_ROAD;
    main_types[CST_ROAD_LU].graphic=load_graphic(CST_ROAD_LU_G);

    main_types[CST_ROAD_LD].group=GROUP_ROAD;
    main_types[CST_ROAD_LD].graphic=load_graphic(CST_ROAD_LD_G);

    main_types[CST_ROAD_UD].group=GROUP_ROAD;
    main_types[CST_ROAD_UD].graphic=load_graphic(CST_ROAD_UD_G);

    main_types[CST_ROAD_UR].group=GROUP_ROAD;
    main_types[CST_ROAD_UR].graphic=load_graphic(CST_ROAD_UR_G);

    main_types[CST_ROAD_DR].group=GROUP_ROAD;
    main_types[CST_ROAD_DR].graphic=load_graphic(CST_ROAD_DR_G);

    main_types[CST_ROAD_LUR].group=GROUP_ROAD;
    main_types[CST_ROAD_LUR].graphic=load_graphic(CST_ROAD_LUR_G);

    main_types[CST_ROAD_LDR].group=GROUP_ROAD;
    main_types[CST_ROAD_LDR].graphic=load_graphic(CST_ROAD_LDR_G);

    main_types[CST_ROAD_LUD].group=GROUP_ROAD;
    main_types[CST_ROAD_LUD].graphic=load_graphic(CST_ROAD_LUD_G);

    main_types[CST_ROAD_UDR].group=GROUP_ROAD;
    main_types[CST_ROAD_UDR].graphic=load_graphic(CST_ROAD_UDR_G);

    main_types[CST_ROAD_LUDR].group=GROUP_ROAD;
    main_types[CST_ROAD_LUDR].graphic=load_graphic(CST_ROAD_LUDR_G);

    main_types[CST_INDUSTRY_L_C].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_C].graphic
	    =load_graphic(CST_INDUSTRY_L_C_G);

    main_types[CST_INDUSTRY_L_Q1].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_Q1].graphic
	    =load_graphic(CST_INDUSTRY_L_Q1_G);

    main_types[CST_INDUSTRY_L_Q2].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_Q2].graphic
	    =load_graphic(CST_INDUSTRY_L_Q2_G);

    main_types[CST_INDUSTRY_L_Q3].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_Q3].graphic
	    =load_graphic(CST_INDUSTRY_L_Q3_G);

    main_types[CST_INDUSTRY_L_Q4].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_Q4].graphic
	    =load_graphic(CST_INDUSTRY_L_Q4_G);

    main_types[CST_INDUSTRY_L_L1].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_L1].graphic
	    =load_graphic(CST_INDUSTRY_L_L1_G);

    main_types[CST_INDUSTRY_L_L2].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_L2].graphic
	    =load_graphic(CST_INDUSTRY_L_L2_G);

    main_types[CST_INDUSTRY_L_L3].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_L3].graphic
	    =load_graphic(CST_INDUSTRY_L_L3_G);

    main_types[CST_INDUSTRY_L_L4].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_L4].graphic
	    =load_graphic(CST_INDUSTRY_L_L4_G);


    main_types[CST_INDUSTRY_L_M1].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_M1].graphic
	    =load_graphic(CST_INDUSTRY_L_M1_G);

    main_types[CST_INDUSTRY_L_M2].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_M2].graphic
	    =load_graphic(CST_INDUSTRY_L_M2_G);

    main_types[CST_INDUSTRY_L_M3].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_M3].graphic
	    =load_graphic(CST_INDUSTRY_L_M3_G);

    main_types[CST_INDUSTRY_L_M4].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_M4].graphic
	    =load_graphic(CST_INDUSTRY_L_M4_G);


    main_types[CST_INDUSTRY_L_H1].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_H1].graphic
	    =load_graphic(CST_INDUSTRY_L_H1_G);

    main_types[CST_INDUSTRY_L_H2].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_H2].graphic
	    =load_graphic(CST_INDUSTRY_L_H2_G);

    main_types[CST_INDUSTRY_L_H3].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_H3].graphic
	    =load_graphic(CST_INDUSTRY_L_H3_G);

    main_types[CST_INDUSTRY_L_H4].group=GROUP_INDUSTRY_L;
    main_types[CST_INDUSTRY_L_H4].graphic
	    =load_graphic(CST_INDUSTRY_L_H4_G);

    main_types[CST_COMMUNE_1].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_1].graphic=load_graphic(CST_COMMUNE_1_G);

    main_types[CST_COMMUNE_2].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_2].graphic=load_graphic(CST_COMMUNE_2_G);

    main_types[CST_COMMUNE_3].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_3].graphic=load_graphic(CST_COMMUNE_3_G);

    main_types[CST_COMMUNE_4].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_4].graphic=load_graphic(CST_COMMUNE_4_G);

    main_types[CST_COMMUNE_5].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_5].graphic=load_graphic(CST_COMMUNE_5_G);

    main_types[CST_COMMUNE_6].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_6].graphic=load_graphic(CST_COMMUNE_6_G);

    main_types[CST_COMMUNE_7].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_7].graphic=load_graphic(CST_COMMUNE_7_G);

    main_types[CST_COMMUNE_8].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_8].graphic=load_graphic(CST_COMMUNE_8_G);

    main_types[CST_COMMUNE_9].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_9].graphic=load_graphic(CST_COMMUNE_9_G);

    main_types[CST_COMMUNE_10].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_10].graphic=load_graphic(CST_COMMUNE_10_G);

    main_types[CST_COMMUNE_11].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_11].graphic=load_graphic(CST_COMMUNE_11_G);

    main_types[CST_COMMUNE_12].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_12].graphic=load_graphic(CST_COMMUNE_12_G);

    main_types[CST_COMMUNE_13].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_13].graphic=load_graphic(CST_COMMUNE_13_G);

    main_types[CST_COMMUNE_14].group=GROUP_COMMUNE;
    main_types[CST_COMMUNE_14].graphic=load_graphic(CST_COMMUNE_14_G);

    main_types[CST_UNIVERSITY].group=GROUP_UNIVERSITY;
    main_types[CST_UNIVERSITY].graphic=load_graphic(CST_UNIVERSITY_G);

    main_types[CST_OREMINE_1].group=GROUP_OREMINE;
    main_types[CST_OREMINE_1].graphic=load_graphic(CST_OREMINE_1_G);

    main_types[CST_OREMINE_2].group=GROUP_OREMINE;
    main_types[CST_OREMINE_2].graphic=load_graphic(CST_OREMINE_2_G);

    main_types[CST_OREMINE_3].group=GROUP_OREMINE;
    main_types[CST_OREMINE_3].graphic=load_graphic(CST_OREMINE_3_G);

    main_types[CST_OREMINE_4].group=GROUP_OREMINE;
    main_types[CST_OREMINE_4].graphic=load_graphic(CST_OREMINE_4_G);

    main_types[CST_OREMINE_5].group=GROUP_OREMINE;
    main_types[CST_OREMINE_5].graphic=load_graphic(CST_OREMINE_5_G);

    main_types[CST_OREMINE_6].group=GROUP_OREMINE;
    main_types[CST_OREMINE_6].graphic=load_graphic(CST_OREMINE_6_G);

    main_types[CST_OREMINE_7].group=GROUP_OREMINE;
    main_types[CST_OREMINE_7].graphic=load_graphic(CST_OREMINE_7_G);

    main_types[CST_OREMINE_8].group=GROUP_OREMINE;
    main_types[CST_OREMINE_8].graphic=load_graphic(CST_OREMINE_8_G);

    main_types[CST_TIP_0].group=GROUP_TIP;
    main_types[CST_TIP_0].graphic=load_graphic(CST_TIP_0_G);

    main_types[CST_TIP_1].group=GROUP_TIP;
    main_types[CST_TIP_1].graphic=load_graphic(CST_TIP_1_G);

    main_types[CST_TIP_2].group=GROUP_TIP;
    main_types[CST_TIP_2].graphic=load_graphic(CST_TIP_2_G);

    main_types[CST_TIP_3].group=GROUP_TIP;
    main_types[CST_TIP_3].graphic=load_graphic(CST_TIP_3_G);

    main_types[CST_TIP_4].group=GROUP_TIP;
    main_types[CST_TIP_4].graphic=load_graphic(CST_TIP_4_G);

    main_types[CST_TIP_5].group=GROUP_TIP;
    main_types[CST_TIP_5].graphic=load_graphic(CST_TIP_5_G);

    main_types[CST_TIP_6].group=GROUP_TIP;
    main_types[CST_TIP_6].graphic=load_graphic(CST_TIP_6_G);

    main_types[CST_TIP_7].group=GROUP_TIP;
    main_types[CST_TIP_7].graphic=load_graphic(CST_TIP_7_G);

    main_types[CST_TIP_8].group=GROUP_TIP;
    main_types[CST_TIP_8].graphic=load_graphic(CST_TIP_8_G);

    main_types[CST_EX_PORT].group=GROUP_PORT;
    main_types[CST_EX_PORT].graphic=load_graphic(CST_EX_PORT_G);

    main_types[CST_INDUSTRY_H_C].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_C].graphic
	    =load_graphic(CST_INDUSTRY_H_C_G);

    main_types[CST_INDUSTRY_H_L1].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_L1].graphic
	    =load_graphic(CST_INDUSTRY_H_L1_G);

    main_types[CST_INDUSTRY_H_L2].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_L2].graphic
	    =load_graphic(CST_INDUSTRY_H_L2_G);

    main_types[CST_INDUSTRY_H_L3].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_L3].graphic
	    =load_graphic(CST_INDUSTRY_H_L3_G);

    main_types[CST_INDUSTRY_H_L4].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_L4].graphic
	    =load_graphic(CST_INDUSTRY_H_L4_G);

    main_types[CST_INDUSTRY_H_L5].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_L5].graphic
	    =load_graphic(CST_INDUSTRY_H_L5_G);

    main_types[CST_INDUSTRY_H_L6].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_L6].graphic
	    =load_graphic(CST_INDUSTRY_H_L6_G);

    main_types[CST_INDUSTRY_H_L7].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_L7].graphic
	    =load_graphic(CST_INDUSTRY_H_L7_G);

    main_types[CST_INDUSTRY_H_L8].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_L8].graphic
	    =load_graphic(CST_INDUSTRY_H_L8_G);


    main_types[CST_INDUSTRY_H_M1].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_M1].graphic
	    =load_graphic(CST_INDUSTRY_H_M1_G);

    main_types[CST_INDUSTRY_H_M2].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_M2].graphic
	    =load_graphic(CST_INDUSTRY_H_M2_G);

    main_types[CST_INDUSTRY_H_M3].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_M3].graphic
	    =load_graphic(CST_INDUSTRY_H_M3_G);

    main_types[CST_INDUSTRY_H_M4].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_M4].graphic
	    =load_graphic(CST_INDUSTRY_H_M4_G);

    main_types[CST_INDUSTRY_H_M5].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_M5].graphic
	    =load_graphic(CST_INDUSTRY_H_M5_G);

    main_types[CST_INDUSTRY_H_M6].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_M6].graphic
	    =load_graphic(CST_INDUSTRY_H_M6_G);

    main_types[CST_INDUSTRY_H_M7].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_M7].graphic
	    =load_graphic(CST_INDUSTRY_H_M7_G);

    main_types[CST_INDUSTRY_H_M8].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_M8].graphic
	    =load_graphic(CST_INDUSTRY_H_M8_G);

    main_types[CST_INDUSTRY_H_H1].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_H1].graphic
	    =load_graphic(CST_INDUSTRY_H_H1_G);

    main_types[CST_INDUSTRY_H_H2].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_H2].graphic
	    =load_graphic(CST_INDUSTRY_H_H2_G);

    main_types[CST_INDUSTRY_H_H3].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_H3].graphic
	    =load_graphic(CST_INDUSTRY_H_H3_G);

    main_types[CST_INDUSTRY_H_H4].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_H4].graphic
	    =load_graphic(CST_INDUSTRY_H_H4_G);

    main_types[CST_INDUSTRY_H_H5].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_H5].graphic
	    =load_graphic(CST_INDUSTRY_H_H5_G);

    main_types[CST_INDUSTRY_H_H6].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_H6].graphic
	    =load_graphic(CST_INDUSTRY_H_H6_G);

    main_types[CST_INDUSTRY_H_H7].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_H7].graphic
	    =load_graphic(CST_INDUSTRY_H_H7_G);

    main_types[CST_INDUSTRY_H_H8].group=GROUP_INDUSTRY_H;
    main_types[CST_INDUSTRY_H_H8].graphic
	    =load_graphic(CST_INDUSTRY_H_H8_G);

    main_types[CST_PARKLAND_PLANE].group=GROUP_PARKLAND;
    main_types[CST_PARKLAND_PLANE].graphic
	    =load_graphic(CST_PARKLAND_PLANE_G);

    prog_box("",50);

    main_types[CST_PARKLAND_LAKE].group=GROUP_PARKLAND;
    main_types[CST_PARKLAND_LAKE].graphic
	    =load_graphic(CST_PARKLAND_LAKE_G);

    main_types[CST_RECYCLE].group=GROUP_RECYCLE;
    main_types[CST_RECYCLE].graphic=load_graphic(CST_RECYCLE_G);

    main_types[CST_WATER].group=GROUP_WATER;
    main_types[CST_WATER].graphic=load_graphic(CST_WATER_G);

    main_types[CST_WATER_D].group=GROUP_WATER;
    main_types[CST_WATER_D].graphic=load_graphic(CST_WATER_D_G);

    main_types[CST_WATER_R].group=GROUP_WATER;
    main_types[CST_WATER_R].graphic=load_graphic(CST_WATER_R_G);

    main_types[CST_WATER_U].group=GROUP_WATER;
    main_types[CST_WATER_U].graphic=load_graphic(CST_WATER_U_G);

    main_types[CST_WATER_L].group=GROUP_WATER;
    main_types[CST_WATER_L].graphic=load_graphic(CST_WATER_L_G);

    main_types[CST_WATER_LR].group=GROUP_WATER;
    main_types[CST_WATER_LR].graphic=load_graphic(CST_WATER_LR_G);

    main_types[CST_WATER_UD].group=GROUP_WATER;
    main_types[CST_WATER_UD].graphic=load_graphic(CST_WATER_UD_G);

    main_types[CST_WATER_LD].group=GROUP_WATER;
    main_types[CST_WATER_LD].graphic=load_graphic(CST_WATER_LD_G);

    main_types[CST_WATER_RD].group=GROUP_WATER;
    main_types[CST_WATER_RD].graphic=load_graphic(CST_WATER_RD_G);

    main_types[CST_WATER_LU].group=GROUP_WATER;
    main_types[CST_WATER_LU].graphic=load_graphic(CST_WATER_LU_G);

    main_types[CST_WATER_UR].group=GROUP_WATER;
    main_types[CST_WATER_UR].graphic=load_graphic(CST_WATER_UR_G);

    main_types[CST_WATER_LUD].group=GROUP_WATER;
    main_types[CST_WATER_LUD].graphic=load_graphic(CST_WATER_LUD_G);

    main_types[CST_WATER_LRD].group=GROUP_WATER;
    main_types[CST_WATER_LRD].graphic=load_graphic(CST_WATER_LRD_G);

    main_types[CST_WATER_LUR].group=GROUP_WATER;
    main_types[CST_WATER_LUR].graphic=load_graphic(CST_WATER_LUR_G);

    main_types[CST_WATER_URD].group=GROUP_WATER;
    main_types[CST_WATER_URD].graphic=load_graphic(CST_WATER_URD_G);

    main_types[CST_WATER_LURD].group=GROUP_WATER;
    main_types[CST_WATER_LURD].graphic=load_graphic(CST_WATER_LURD_G);

    main_types[CST_HEALTH].group=GROUP_HEALTH;
    main_types[CST_HEALTH].graphic=load_graphic(CST_HEALTH_G);

    main_types[CST_ROCKET_1].group=GROUP_ROCKET;
    main_types[CST_ROCKET_1].graphic=load_graphic(CST_ROCKET_1_G);

    main_types[CST_ROCKET_2].group=GROUP_ROCKET;
    main_types[CST_ROCKET_2].graphic=load_graphic(CST_ROCKET_2_G);

    main_types[CST_ROCKET_3].group=GROUP_ROCKET;
    main_types[CST_ROCKET_3].graphic=load_graphic(CST_ROCKET_3_G);

    main_types[CST_ROCKET_4].group=GROUP_ROCKET;
    main_types[CST_ROCKET_4].graphic=load_graphic(CST_ROCKET_4_G);

    prog_box("",60);

    main_types[CST_ROCKET_5].group=GROUP_ROCKET;
    main_types[CST_ROCKET_5].graphic=load_graphic(CST_ROCKET_5_G);

    main_types[CST_ROCKET_6].group=GROUP_ROCKET;
    main_types[CST_ROCKET_6].graphic=load_graphic(CST_ROCKET_6_G);

    main_types[CST_ROCKET_7].group=GROUP_ROCKET;
    main_types[CST_ROCKET_7].graphic=load_graphic(CST_ROCKET_7_G);

    main_types[CST_ROCKET_FLOWN].group=GROUP_ROCKET;
    main_types[CST_ROCKET_FLOWN].graphic
	    =load_graphic(CST_ROCKET_FLOWN_G);


    main_types[CST_BURNT].group=GROUP_BURNT;
    main_types[CST_BURNT].graphic=load_graphic(CST_BURNT_G);

    main_types[CST_WINDMILL_1_G].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_1_G].graphic
	    =load_graphic(CST_WINDMILL_1_G_G);

    main_types[CST_WINDMILL_2_G].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_2_G].graphic
	    =load_graphic(CST_WINDMILL_2_G_G);

    main_types[CST_WINDMILL_3_G].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_3_G].graphic
	    =load_graphic(CST_WINDMILL_3_G_G);

    main_types[CST_WINDMILL_1_RG].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_1_RG].graphic
	    =load_graphic(CST_WINDMILL_1_RG_G);

    main_types[CST_WINDMILL_2_RG].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_2_RG].graphic
	    =load_graphic(CST_WINDMILL_2_RG_G);

    main_types[CST_WINDMILL_3_RG].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_3_RG].graphic
	    =load_graphic(CST_WINDMILL_3_RG_G);

    main_types[CST_WINDMILL_1_R].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_1_R].graphic
	    =load_graphic(CST_WINDMILL_1_R_G);

    main_types[CST_WINDMILL_2_R].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_2_R].graphic
	    =load_graphic(CST_WINDMILL_2_R_G);

    main_types[CST_WINDMILL_3_R].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_3_R].graphic
	    =load_graphic(CST_WINDMILL_3_R_G);

    main_types[CST_WINDMILL_1_W].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_1_W].graphic
	    =load_graphic(CST_WINDMILL_1_W_G);

    main_types[CST_WINDMILL_2_W].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_2_W].graphic
	    =load_graphic(CST_WINDMILL_2_W_G);

    main_types[CST_WINDMILL_3_W].group=GROUP_WINDMILL;
    main_types[CST_WINDMILL_3_W].graphic
	    =load_graphic(CST_WINDMILL_3_W_G);

    main_types[CST_MONUMENT_0].group=GROUP_MONUMENT;
    main_types[CST_MONUMENT_0].graphic=load_graphic(CST_MONUMENT_0_G);

    main_types[CST_MONUMENT_1].group=GROUP_MONUMENT;
    main_types[CST_MONUMENT_1].graphic=load_graphic(CST_MONUMENT_1_G);

    main_types[CST_MONUMENT_2].group=GROUP_MONUMENT;
    main_types[CST_MONUMENT_2].graphic=load_graphic(CST_MONUMENT_2_G);

    main_types[CST_MONUMENT_3].group=GROUP_MONUMENT;
    main_types[CST_MONUMENT_3].graphic=load_graphic(CST_MONUMENT_3_G);

    main_types[CST_MONUMENT_4].group=GROUP_MONUMENT;
    main_types[CST_MONUMENT_4].graphic=load_graphic(CST_MONUMENT_4_G);

    main_types[CST_MONUMENT_5].group=GROUP_MONUMENT;
    main_types[CST_MONUMENT_5].graphic=load_graphic(CST_MONUMENT_5_G);

    main_types[CST_SCHOOL].group=GROUP_SCHOOL;
    main_types[CST_SCHOOL].graphic=load_graphic(CST_SCHOOL_G);

    main_types[CST_BLACKSMITH_0].group=GROUP_BLACKSMITH;
    main_types[CST_BLACKSMITH_0].graphic
	    =load_graphic(CST_BLACKSMITH_0_G);

    main_types[CST_BLACKSMITH_1].group=GROUP_BLACKSMITH;
    main_types[CST_BLACKSMITH_1].graphic
	    =load_graphic(CST_BLACKSMITH_1_G);

    main_types[CST_BLACKSMITH_2].group=GROUP_BLACKSMITH;
    main_types[CST_BLACKSMITH_2].graphic
	    =load_graphic(CST_BLACKSMITH_2_G);

    main_types[CST_BLACKSMITH_3].group=GROUP_BLACKSMITH;
    main_types[CST_BLACKSMITH_3].graphic
	    =load_graphic(CST_BLACKSMITH_3_G);

    main_types[CST_BLACKSMITH_4].group=GROUP_BLACKSMITH;
    main_types[CST_BLACKSMITH_4].graphic
	    =load_graphic(CST_BLACKSMITH_4_G);

    main_types[CST_BLACKSMITH_5].group=GROUP_BLACKSMITH;
    main_types[CST_BLACKSMITH_5].graphic
	    =load_graphic(CST_BLACKSMITH_5_G);

    main_types[CST_BLACKSMITH_6].group=GROUP_BLACKSMITH;
    main_types[CST_BLACKSMITH_6].graphic
	    =load_graphic(CST_BLACKSMITH_6_G);

    prog_box("",75);

    main_types[CST_MILL_0].group=GROUP_MILL;
    main_types[CST_MILL_0].graphic=load_graphic(CST_MILL_0_G);

    main_types[CST_MILL_1].group=GROUP_MILL;
    main_types[CST_MILL_1].graphic=load_graphic(CST_MILL_1_G);

    main_types[CST_MILL_2].group=GROUP_MILL;
    main_types[CST_MILL_2].graphic=load_graphic(CST_MILL_2_G);

    main_types[CST_MILL_3].group=GROUP_MILL;
    main_types[CST_MILL_3].graphic=load_graphic(CST_MILL_3_G);

    main_types[CST_MILL_4].group=GROUP_MILL;
    main_types[CST_MILL_4].graphic=load_graphic(CST_MILL_4_G);

    main_types[CST_MILL_5].group=GROUP_MILL;
    main_types[CST_MILL_5].graphic=load_graphic(CST_MILL_5_G);

    main_types[CST_MILL_6].group=GROUP_MILL;
    main_types[CST_MILL_6].graphic=load_graphic(CST_MILL_6_G);

    main_types[CST_POTTERY_0].group=GROUP_POTTERY;
    main_types[CST_POTTERY_0].graphic=load_graphic(CST_POTTERY_0_G);

    main_types[CST_POTTERY_1].group=GROUP_POTTERY;
    main_types[CST_POTTERY_1].graphic=load_graphic(CST_POTTERY_1_G);

    main_types[CST_POTTERY_2].group=GROUP_POTTERY;
    main_types[CST_POTTERY_2].graphic=load_graphic(CST_POTTERY_2_G);

    main_types[CST_POTTERY_3].group=GROUP_POTTERY;
    main_types[CST_POTTERY_3].graphic=load_graphic(CST_POTTERY_3_G);

    main_types[CST_POTTERY_4].group=GROUP_POTTERY;
    main_types[CST_POTTERY_4].graphic=load_graphic(CST_POTTERY_4_G);

    main_types[CST_POTTERY_5].group=GROUP_POTTERY;
    main_types[CST_POTTERY_5].graphic=load_graphic(CST_POTTERY_5_G);

    main_types[CST_POTTERY_6].group=GROUP_POTTERY;
    main_types[CST_POTTERY_6].graphic=load_graphic(CST_POTTERY_6_G);

    main_types[CST_POTTERY_7].group=GROUP_POTTERY;
    main_types[CST_POTTERY_7].graphic=load_graphic(CST_POTTERY_7_G);

    main_types[CST_POTTERY_8].group=GROUP_POTTERY;
    main_types[CST_POTTERY_8].graphic=load_graphic(CST_POTTERY_8_G);

    main_types[CST_POTTERY_9].group=GROUP_POTTERY;
    main_types[CST_POTTERY_9].graphic=load_graphic(CST_POTTERY_9_G);

    main_types[CST_POTTERY_10].group=GROUP_POTTERY;
    main_types[CST_POTTERY_10].graphic=load_graphic(CST_POTTERY_10_G);

    main_types[CST_FIRESTATION_1].group=GROUP_FIRESTATION;
    main_types[CST_FIRESTATION_1].graphic
	    =load_graphic(CST_FIRESTATION_1_G);

    main_types[CST_FIRESTATION_2].group=GROUP_FIRESTATION;
    main_types[CST_FIRESTATION_2].graphic
	    =load_graphic(CST_FIRESTATION_2_G);

    main_types[CST_FIRESTATION_3].group=GROUP_FIRESTATION;
    main_types[CST_FIRESTATION_3].graphic
	    =load_graphic(CST_FIRESTATION_3_G);

    main_types[CST_FIRESTATION_4].group=GROUP_FIRESTATION;
    main_types[CST_FIRESTATION_4].graphic
	    =load_graphic(CST_FIRESTATION_4_G);

    main_types[CST_FIRESTATION_5].group=GROUP_FIRESTATION;
    main_types[CST_FIRESTATION_5].graphic
	    =load_graphic(CST_FIRESTATION_5_G);

    main_types[CST_FIRESTATION_6].group=GROUP_FIRESTATION;
    main_types[CST_FIRESTATION_6].graphic
	    =load_graphic(CST_FIRESTATION_6_G);

    main_types[CST_FIRESTATION_7].group=GROUP_FIRESTATION;
    main_types[CST_FIRESTATION_7].graphic
	    =load_graphic(CST_FIRESTATION_7_G);

    main_types[CST_FIRESTATION_8].group=GROUP_FIRESTATION;
    main_types[CST_FIRESTATION_8].graphic
	    =load_graphic(CST_FIRESTATION_8_G);

    main_types[CST_FIRESTATION_9].group=GROUP_FIRESTATION;
    main_types[CST_FIRESTATION_9].graphic
	    =load_graphic(CST_FIRESTATION_9_G);

    main_types[CST_FIRESTATION_10].group=GROUP_FIRESTATION;
    main_types[CST_FIRESTATION_10].graphic
	    =load_graphic(CST_FIRESTATION_10_G);

    main_types[CST_CRICKET_1].group=GROUP_CRICKET;
    main_types[CST_CRICKET_1].graphic
	    =load_graphic(CST_CRICKET_1_G);

    main_types[CST_CRICKET_2].group=GROUP_CRICKET;
    main_types[CST_CRICKET_2].graphic
	    =load_graphic(CST_CRICKET_2_G);

    main_types[CST_CRICKET_3].group=GROUP_CRICKET;
    main_types[CST_CRICKET_3].graphic
	    =load_graphic(CST_CRICKET_3_G);

    main_types[CST_CRICKET_4].group=GROUP_CRICKET;
    main_types[CST_CRICKET_4].graphic
	    =load_graphic(CST_CRICKET_4_G);

    prog_box("",90);

    main_types[CST_CRICKET_5].group=GROUP_CRICKET;
    main_types[CST_CRICKET_5].graphic
	    =load_graphic(CST_CRICKET_5_G);

    main_types[CST_CRICKET_6].group=GROUP_CRICKET;
    main_types[CST_CRICKET_6].graphic
	    =load_graphic(CST_CRICKET_6_G);

    main_types[CST_CRICKET_7].group=GROUP_CRICKET;
    main_types[CST_CRICKET_7].graphic
	    =load_graphic(CST_CRICKET_7_G);

    main_types[CST_FIRE_1].group=GROUP_FIRE;
    main_types[CST_FIRE_1].graphic
	    =load_graphic(CST_FIRE_1_G);

    main_types[CST_FIRE_2].group=GROUP_FIRE;
    main_types[CST_FIRE_2].graphic
	    =load_graphic(CST_FIRE_2_G);

    main_types[CST_FIRE_3].group=GROUP_FIRE;
    main_types[CST_FIRE_3].graphic
	    =load_graphic(CST_FIRE_3_G);

    main_types[CST_FIRE_4].group=GROUP_FIRE;
    main_types[CST_FIRE_4].graphic
	    =load_graphic(CST_FIRE_4_G);

    main_types[CST_FIRE_5].group=GROUP_FIRE;
    main_types[CST_FIRE_5].graphic
	    =load_graphic(CST_FIRE_5_G);

    main_types[CST_FIRE_DONE1].group=GROUP_FIRE;
    main_types[CST_FIRE_DONE1].graphic
	    =load_graphic(CST_FIRE_DONE1_G);

    main_types[CST_FIRE_DONE2].group=GROUP_FIRE;
    main_types[CST_FIRE_DONE2].graphic
	    =load_graphic(CST_FIRE_DONE2_G);

    main_types[CST_FIRE_DONE3].group=GROUP_FIRE;
    main_types[CST_FIRE_DONE3].graphic
	    =load_graphic(CST_FIRE_DONE3_G);

    main_types[CST_FIRE_DONE4].group=GROUP_FIRE;
    main_types[CST_FIRE_DONE4].graphic
	    =load_graphic(CST_FIRE_DONE4_G);

    main_types[CST_SHANTY].group=GROUP_SHANTY;
    main_types[CST_SHANTY].graphic=load_graphic(CST_SHANTY_G);
#endif

    main_types[CST_USED].group=GROUP_USED;
    main_types[CST_USED].graphic=0;         /* Won't be dereferenced! */
}

int get_group_of_type (short type)
{
    return main_types[type].group;
}

void set_map_groups (void)
{
    int x, y;
    for (x = 0; x < WORLD_SIDE_LEN; x++) {
        for (y = 0; y < WORLD_SIDE_LEN; y++) {
            MP_GROUP(x,y) = get_group_of_type(MP_TYPE(x,y));
        }
    }
}

int get_group_cost (short group)
{
    return (int) ((float) main_groups[group].cost
		  + ((float) main_groups[group].cost
		     * ((float) main_groups[group].cost_mul
			* (float) world->tech.level) 
		     / (float) MAX_TECH_LEVEL));
}

void get_type_name (short type, char * s)
{
     short g;
     g = get_group_of_type (type);
     strcpy (s, _(main_groups[g].name));
}

int get_type_cost (short type)
{
    return get_group_cost ((short) get_group_of_type (type));
}
