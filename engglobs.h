/* ---------------------------------------------------------------------- *
 * engglobs.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */
#ifndef __engglobs_h__
#define __engglobs_h__

#include "lin-city.h" /* WORLD_SIDE_LEN dependency */

#include "boolean.h"

typedef struct
{
    int x; /* FIXME: should be unsigned int */
    int y; /* FIXME: should be unsigned int */

} Map_Coord;

typedef struct
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
  
} Map_Point_Info;

/* GCS -- One of these days I will get this right. */
typedef struct
{
    short type[WORLD_SIDE_LEN][WORLD_SIDE_LEN];
    short group[WORLD_SIDE_LEN][WORLD_SIDE_LEN];
    int pollution[WORLD_SIDE_LEN][WORLD_SIDE_LEN];
    Map_Point_Info info[WORLD_SIDE_LEN][WORLD_SIDE_LEN];
} Map;

extern Map map;

#define MP_TYPE(x,y)   map.type[x][y]
#define MP_GROUP(x,y)  map.group[x][y]
#define MP_POL(x,y)    map.pollution[x][y]
#define MP_INFO(x,y)   map.info[x][y]

extern Map_Coord mappoint_array[];
extern int numof_shanties, numof_communes;
/* GCS -- this one is difficult to deal with.
   LinCity will give your money back if you bulldoze
   the most recently constructed building (i.e. if
   you make a mistake.  How does this fit into a
   multiplayer game?  Not at all, I suppose... */
extern Map_Coord last_built;


typedef struct
{
    /* FIXME: unsigned */ int made;
    /* FIXME: unsigned */ int used;

} Resource_State;

typedef struct
{
    bool flag;

    struct
    {
        bool flag;
        /* FIXME: unsigned */ int count;

    } ore_coal_tip;

    struct
    {
        bool flag;
        /* FIXME: unsigned */ int count;

    } port;

    struct
    {
        int previous; /* same type than money.total */
        /* FIXME: unsigned */ int count;

    } money;

    struct
    {
        int previous; /* same type than population */
        /* FIXME: unsigned */ int count;

    } population;

    struct
    {
        int previous; /* same type than tech.level */
        /* FIXME: unsigned */ int count;

    } tech;

    struct
    {
        /* FIXME: unsigned */ int count;

    } fire;

} Sustainibility_State;

 /* game time in day/month/year format */
typedef struct
{
    unsigned int day;
    unsigned int month;
    unsigned int year;

} World_Date;

typedef struct
{
    struct
    {
        /* FIXME: unsigned */ int total;  /* game time */
        World_Date date; /* game time in day/month/year format */

    } time;

    struct
    {
        /* FIXME: unsigned */ int total_day; /* see Note (1) */
        /* FIXME: unsigned */ int starving_day; /* see Note (1) */
        /* FIXME: unsigned */ int housed;
        /* FIXME: unsigned */ int unemployed_day; /* see Note (1) */
        /* FIXME: unsigned */ int pool;
        /* FIXME: unsigned */ int highest; /* see Note (2) */
        /* FIXME: unsigned */ int evacuated; /* see Note (2) */
        /* FIXME: unsigned */ int births; /* see Note (2) */

        struct
        {
            /* FIXME: unsigned */ int days; /* see Note (3) */
            /* FIXME: unsigned */ int years;
            float history;

        } unemployment;

        struct
        {
            /* FIXME: unsigned */ int unnatural_month; /* see Note (3) */

            struct
            {
                /* FIXME: unsigned */ int total;
                float history;

            } starve;

            struct
            {
                /* FIXME: unsigned */ int total;
                float history;

            } pollution;

        } deaths;

    } population;

    struct
    {
        int total; /* can be negative */
        /* FIXME: unsigned */ int dole_rate; /* see Note (4) */

        struct
        {
            /* FIXME: unsigned */ int income; /* see Note (4) */
            /* FIXME: unsigned */ int exports; /* see Note (5) */
            /* FIXME: unsigned */ int goods; /* see Note (4) */
            /* FIXME: unsigned */ int coal; /* see Note (4) */

        } tax_rate;

        struct
        {
            /* FIXME: unsigned */ int imports;
            /* FIXME: unsigned */ int transport; /* see Note (4) */

        } cost_rate;

    } money;

    struct
    {
        /* FIXME: unsigned */ int university_intake_rate;

    } knowledge;

    struct
    {
        /* FIXME: unsigned */ int level;
        /* FIXME: unsigned */ int highest_level;
    } tech;

    struct
    {
        Resource_State power; /* see Note (5) */
        Resource_State coal; /* see Note (6) */
        Resource_State goods; /* see Note (6) */
        Resource_State ore; /* see Note (6) */

    } resources;

    Sustainibility_State sustain;

    struct
    {
        bool coal_survey_done; /* show minimap with coal resources or not */

    } flags;

    struct /* conditions of victory */
    {
        /* FIXME: unsigned */ int rockets_launched;
        /* FIXME: unsigned */ int rockets_launched_success;

    } victory;

} World_State;
/*
 * Notes:
 *
 * (1) Accumulator -- Not stored in game file (ldsvguts.c)
 * (2) Only used in the game file (ldsvguts.c) and in compile_results() of main.c
 * (3) Not stored in game file
 * (4) Its value doesn't change
 * (5) Not used, only stored in game file
 * (6) Only modified, and stored in game file, not used for anything
 */

extern World_State world_state;
extern World_State* world;

extern Map_Coord substations[];
extern unsigned int numof_substations;
extern Map_Coord markets[];
extern unsigned int numof_markets;
/*extern int numof_health_centres;*/ /* Not used */

/*extern int selected_type_cost;*/ /* Not used */

void world_init( World_State* world );

#endif /* __engglobs_h__ */
