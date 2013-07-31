/* ---------------------------------------------------------------------- *
 * lintypes.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */
#ifndef __lintypes_h__
#define __lintypes_h__

#define NUM_OF_TYPES    400
#define NUM_OF_GROUPS    42
#define GROUP_NAME_LEN   20

/* groups */
#define GROUP_BARE 	   0
#define GROUP_POWER_LINE   1
#define GROUP_SOLAR_POWER 2
#define GROUP_SUBSTATION   3
#define GROUP_RESIDENCE_LL 4
#define GROUP_ORGANIC_FARM 5
#define GROUP_MARKET       6
#define GROUP_TRACK	   7
#define GROUP_COALMINE     8
#define GROUP_RAIL         9
#define GROUP_COAL_POWER 10
#define GROUP_ROAD         11
#define GROUP_INDUSTRY_L   12
#define GROUP_UNIVERSITY   13
#define GROUP_COMMUNE      14
#define GROUP_OREMINE      15
#define GROUP_TIP      16
#define GROUP_PORT      17
#define GROUP_INDUSTRY_H   18
#define GROUP_PARKLAND     19
#define GROUP_RECYCLE      20
#define GROUP_WATER	   21
#define GROUP_RIVER (GROUP_WATER)	/* oops -- GCS: Why oops? */
#define GROUP_HEALTH       22
#define GROUP_ROCKET	   23
#define GROUP_WINDMILL     24
#define GROUP_MONUMENT     25
#define GROUP_SCHOOL     26
#define GROUP_BLACKSMITH     27
#define GROUP_MILL     28
#define GROUP_POTTERY  29
#define GROUP_FIRESTATION 30
#define GROUP_CRICKET 31
#define GROUP_BURNT        32
#define GROUP_SHANTY        33
#define GROUP_FIRE        34
#define GROUP_USED        35
#define GROUP_RESIDENCE_ML 36
#define GROUP_RESIDENCE_HL 37
#define GROUP_RESIDENCE_LH 38
#define GROUP_RESIDENCE_MH 39
#define GROUP_RESIDENCE_HH 40

/* needed by engine.c */
#define GROUP_SHANTY_BUL_COST  100000
#define GROUP_BURNT_BUL_COST  1000

/* needed by simulate.c */
#define GROUP_FIRESTATION_TECH     22
#define GROUP_HEALTH_TECH     110

/* needed by module_button.c */
#define GROUP_OREMINE_TECH 0
#define GROUP_PARKLAND_TECH   2
#define GROUP_WATER_TECH      0
#define GROUP_SCHOOL_TECH   1
#define GROUP_BLACKSMITH_TECH   3
#define GROUP_MILL_TECH   25
#define GROUP_POTTERY_TECH  0

/*#define GROUP_POWER_SOURCE_NO_CREDIT*/
#define GROUP_SOLAR_POWER_NO_CREDIT
#define GROUP_UNIVERSITY_NO_CREDIT
#define GROUP_PARKLAND_NO_CREDIT
#define GROUP_RECYCLE_NO_CREDIT
#define GROUP_ROCKET_NO_CREDIT

/* macros for multiple group check operations */
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

#define GROUP_IS_POWER_SOURCE(group) \
            ((group == GROUP_COAL_POWER) || \
             (group == GROUP_SOLAR_POWER) || \
             (group == GROUP_WINDMILL))

#define GROUP_IS_GRID(group) \
            ((group == GROUP_COAL_POWER) ||\
             (group == GROUP_WINDMILL) || \
             (group == GROUP_POWER_LINE) || \
             (group == GROUP_SOLAR_POWER) || \
             (group == GROUP_SUBSTATION))


struct GROUP
{
    char  name[GROUP_NAME_LEN+1];      /* name of group */
    unsigned short        no_credit;   /* TRUE if need credit to build */
    unsigned short        group;       /* This is redundant: it must match
					  the index into the table */
    unsigned short        size;
    int   colour;         /* summary map colour */
    int   cost_mul;       /* group cost multiplier */
    int   bul_cost;       /* group bulldoze cost */
    int   fire_chance;    /* probability of fire */
    int   cost;           /* group cost */
    int   tech;           /* group cost */
};

struct TYPE
{
    int group;          /* What group does this type belong to? */
    char* graphic;      /* Bitmap of the graphic */
};

extern struct GROUP main_groups[];
extern struct TYPE main_types[];

void init_types (void);
int get_group_of_type (short selected_type);
void set_map_groups (void);
int get_group_cost (short group);
void get_type_name (short type, char * s);
int get_type_cost (short type);

#endif /* __lintypes_h__ */
