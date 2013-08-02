/* ---------------------------------------------------------------------- *
 * engglobs.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */
#ifndef __engglobs_h__
#define __engglobs_h__

#include "lin-city.h" /* WORLD_SIDE_LEN dependency */

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
    /* FIXME: boolean */ int flag;

    struct
    {
        /* FIXME: boolean */ int flag;
        /* FIXME: unsigned */ int counter;

    } ore_coal_tip;

    struct
    {
        /* FIXME: boolean */ int flag;
        /* FIXME: unsigned */ int counter;

    } port;

    struct
    {
        int last_value; /* same type than money.total */
        /* FIXME: unsigned */ int counter;

    } money;

    struct
    {
        int last_value; /* same type than population */
        /* FIXME: unsigned */ int counter;

    } population;

    struct
    {
        int last_value; /* same type than tech.level */
        /* FIXME: unsigned */ int counter;

    } tech;

    struct
    {
        /* FIXME: unsigned */ int counter;

    } fire;

} Sustainibility_State;

typedef struct
{
    struct
    {
        /* FIXME: unsigned */ int total;

    } time;

    struct
    {
        /* FIXME: unsigned */ int total;
        /* FIXME: unsigned */ int starving;
        /* FIXME: unsigned */ int housed;
        /* FIXME: unsigned */ int unemployed;
        /* FIXME: unsigned */ int pool;
        /* FIXME: unsigned */ int max_ever;
        /* FIXME: unsigned */ int evacuated;

        struct
        {
            /* FIXME: unsigned */ int total;

        } births;

        struct
        {
            /* FIXME: unsigned */ int days;
            /* FIXME: unsigned */ int years;
            float history;

        } unemployment;

        struct
        {
            /* FIXME: unsigned */ int unnat_month;

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
        /* FIXME: unsigned */ int dole_rate;

        struct
        {
            /* FIXME: unsigned */ int income;
            /* FIXME: unsigned */ int exports;
            /* FIXME: unsigned */ int goods;
            /* FIXME: unsigned */ int coal;

        } tax_rate;

        struct
        {
            /* FIXME: unsigned */ int imports;
            /* FIXME: unsigned */ int transport;

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
        Resource_State power; /* not used */
        Resource_State coal;
        Resource_State goods;
        Resource_State ore;

    } resources;

    Sustainibility_State sustain;

    struct
    {
        /* FIXME: boolean */ int coal_survey_done; /* show minimap with coal resources or not */

    } flags;

    struct /* conditions of victory */
    {
        /* FIXME: unsigned */ int rockets_launched;
        /* FIXME: unsigned */ int rockets_launched_success;

    } victory;

} World_State;

#if 0
extern World_State world_state;
extern World_State* world;
#endif

extern int sust_dig_ore_coal_tip_flag, sust_port_flag, sustain_flag;
extern int sust_dig_ore_coal_count, sust_port_count, sust_old_money;
extern int sust_old_money_count, sust_old_population, sust_old_population_count;
extern int sust_old_tech, sust_old_tech_count, sust_fire_count;

extern int total_time;    /* game time */

extern int population, starving_population;
extern int housed_population;
extern int unemployed_population, people_pool;
extern Map_Coord substations[];
extern unsigned int numof_substations;
extern Map_Coord markets[];
extern unsigned int numof_markets;
extern int numof_health_centres, max_pop_ever, total_evacuated, total_births;

extern int total_money, income_tax_rate, coal_tax_rate;
extern int dole_rate, transport_cost_rate;
extern int goods_tax_rate;
extern int export_tax_rate, import_cost_rate;
extern int tech_level, highest_tech_level, unnat_deaths;

extern int total_pollution_deaths, total_starve_deaths, total_unemployed_days;
extern int total_unemployed_years;
extern float pollution_deaths_history, starve_deaths_history;
extern float unemployed_history;

extern int university_intake_rate;
extern int power_made, power_used, coal_made, coal_used;
extern int goods_made, goods_used, ore_made, ore_used;
extern int rockets_launched, rockets_launched_success;
extern int coal_survey_done;

/*extern int selected_type_cost;*/ /* Not used */

#endif /* __engglobs_h__ */
