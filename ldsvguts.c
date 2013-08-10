/* ---------------------------------------------------------------------- *
 * ldsvguts.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------- */

/* module header file */
#include "ldsvguts.h"

/* system libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "lcintl.h"

/* other modules */
#include "screen.h"
#include "mouse.h"
#include "cliglobs.h"
#include "module_buttons.h"
#include "pbar.h"
#include "stats.h"
#include "engglobs.h"
#include "engine.h"
#include "power.h"
#include "simulate.h"
#include "fileutil.h"

/* ----------------------------------------------------------------- */


#if defined (WIN32) && !defined (NDEBUG)
#define START_FAST_SPEED 1
#define SKIP_OPENING_SCENE 1
#endif

#define SI_BLACK 252
#define SI_RED 253
#define SI_GREEN 254
#define SI_YELLOW 255

#define MP_SANITY_CHECK 1

/* ---------------------------------------------------------------------- *
 * Private Fn Prototypes
 * ---------------------------------------------------------------------- */
void dump_screen (void);
int verify_city (char *cname);
void reset_animation_times (void);
void check_endian (void);
void eswap32 (int *i);
void eswap16 (unsigned short *i);

/* ---------------------------------------------------------------------- *
 * Private Global Variables
 * ---------------------------------------------------------------------- */

char save_names[10][42];

/* ---------------------------------------------------------------------- *
 * Public functions
 * ---------------------------------------------------------------------- */
void remove_scene (char *cname)
{
    char *s;
    int l;
    if ((l = strlen (cname)) < 2)	/* Thanks to Chris J. Kiick */
	return;

    if ((s = (char *) malloc (lc_save_dir_len + l + 16)) == 0)
	malloc_failure ();
    sprintf (s, "%s%c%s", lc_save_dir, PATH_SLASH, cname);
    remove (s);
    free (s);
}

void
save_city_raw (char *cname)
{
    int x, y, z, n, p;
#if defined (WIN32)
    FILE *ofile = fopen (cname, "wb");
#else
    FILE *ofile = fopen (cname, "w");
#endif
    if (ofile == NULL) {
	printf (_("Save file <%s> - "), cname);
	do_error (_("Can't open save file!"));
    }

    fprintf (ofile, "%d\n", (int) VERSION_INT);
    prog_box (_("Saving scene"), 0);
    check_endian ();
    for (x = 0; x < WORLD_SIDE_LEN; x++) {
	for (y = 0; y < WORLD_SIDE_LEN; y++) {
	    for (z = 0; z < sizeof(int); z++) {
		n = *(((unsigned char *) &MP_INFO(x,y).population) + z);
		fprintf (ofile, "%d\n", n);
	    }
	    for (z = 0; z < sizeof(int); z++) {
		n = *(((unsigned char *) &MP_INFO(x,y).flags) + z);
		fprintf (ofile, "%d\n", n);
	    }
	    for (z = 0; z < sizeof(unsigned short); z++) {
		n = *(((unsigned char *) &MP_INFO(x,y).coal_reserve) + z);
		fprintf (ofile, "%d\n", n);
	    }
	    for (z = 0; z < sizeof(unsigned short); z++) {
		n = *(((unsigned char *) &MP_INFO(x,y).ore_reserve) + z);
		fprintf (ofile, "%d\n", n);
	    }
	    for (z = 0; z < sizeof(int); z++) {
		n = *(((unsigned char *) &MP_INFO(x,y).int_1) + z);
		fprintf (ofile, "%d\n", n);
	    }
	    for (z = 0; z < sizeof(int); z++) {
		n = *(((unsigned char *) &MP_INFO(x,y).int_2) + z);
		fprintf (ofile, "%d\n", n);
	    }
	    for (z = 0; z < sizeof(int); z++) {
		n = *(((unsigned char *) &MP_INFO(x,y).int_3) + z);
		fprintf (ofile, "%d\n", n);
	    }
	    for (z = 0; z < sizeof(int); z++) {
		n = *(((unsigned char *) &MP_INFO(x,y).int_4) + z);
		fprintf (ofile, "%d\n", n);
	    }
	    for (z = 0; z < sizeof(int); z++) {
		n = *(((unsigned char *) &MP_INFO(x,y).int_5) + z);
		fprintf (ofile, "%d\n", n);
	    }
	    for (z = 0; z < sizeof(int); z++) {
		n = *(((unsigned char *) &MP_INFO(x,y).int_6) + z);
		fprintf (ofile, "%d\n", n);
	    }
	    for (z = 0; z < sizeof(int); z++) {
		n = *(((unsigned char *) &MP_INFO(x,y).int_7) + z);
		fprintf (ofile, "%d\n", n);
	    }
	    fprintf (ofile, "%d\n", (int) MP_POL(x,y));
	    fprintf (ofile, "%d\n", (int) MP_TYPE(x,y));
	}
	prog_box ("", (90 * x) / WORLD_SIDE_LEN);
    }
    check_endian ();		/* we have to put the byte order back. */

    fprintf (ofile, "%d\n", main_screen_originx);
    fprintf (ofile, "%d\n", main_screen_originy);
    fprintf (ofile, "%d\n", world->time.total);
    for (x = 0; x < MAX_NUMOF_SUBSTATIONS; x++)
    {
        fprintf (ofile, "%d\n", substations[x].x);
        fprintf (ofile, "%d\n", substations[x].y);
    }
    prog_box ("", 92);
    fprintf (ofile, "%d\n", numof_substations); /* FIXME: beware, unsigned int */
    for (x = 0; x < MAX_NUMOF_MARKETS; x++)
    {
        fprintf (ofile, "%d\n", markets[x].x);
        fprintf (ofile, "%d\n", markets[x].y);
    }
    prog_box ("", 94);
    fprintf (ofile, "%d\n", numof_markets); /* FIXME: beware, unsigned int */
    fprintf (ofile, "%d\n", world->population.pool);
    fprintf (ofile, "%d\n", world->money.total);
    fprintf (ofile, "%d\n", world->money.tax_rate.income);
    fprintf (ofile, "%d\n", world->money.tax_rate.coal);
    fprintf (ofile, "%d\n", world->money.dole_rate);
    fprintf (ofile, "%d\n", world->money.cost_rate.transport);
    fprintf (ofile, "%d\n", world->money.tax_rate.goods);
    fprintf (ofile, "%d\n", export_tax);
    fprintf (ofile, "%d\n", world->money.tax_rate.exports);
    fprintf (ofile, "%d\n", import_cost);
    fprintf (ofile, "%d\n", world->money.cost_rate.imports);
    fprintf (ofile, "%d\n", world->tech.level);
    fprintf (ofile, "%d\n", tpopulation);
    fprintf (ofile, "%d\n", tstarving_population);
    fprintf (ofile, "%d\n", tunemployed_population);
    fprintf (ofile, "%d\n", 0); /* waste_goods is obsolete */
    fprintf (ofile, "%d\n", world->resources.power.made);
    fprintf (ofile, "%d\n", world->resources.power.used);
    fprintf (ofile, "%d\n", world->resources.coal.made);
    fprintf (ofile, "%d\n", world->resources.coal.used);
    fprintf (ofile, "%d\n", world->resources.goods.made);
    fprintf (ofile, "%d\n", world->resources.goods.used);
    fprintf (ofile, "%d\n", world->resources.ore.made);
    fprintf (ofile, "%d\n", world->resources.ore.used);
    fprintf (ofile, "%d\n", 0); /* Removed diff_old_population, version 1.12 */

    prog_box ("", 96);
    /* Changed, version 1.12 */
    fprintf (ofile, "%d\n", monthgraph_size);
    for (x = 0; x < monthgraph_size; x++) {
	fprintf (ofile, "%d\n", monthgraph_pop[x]);
	fprintf (ofile, "%d\n", monthgraph_starve[x]);
	fprintf (ofile, "%d\n", monthgraph_nojobs[x]);
	fprintf (ofile, "%d\n", monthgraph_ppool[x]);
#if defined (commentout)
	fprintf (ofile, "%d\n", diffgraph_power[x]);
	fprintf (ofile, "%d\n", diffgraph_coal[x]);
	fprintf (ofile, "%d\n", diffgraph_goods[x]);
	fprintf (ofile, "%d\n", diffgraph_ore[x]);
	fprintf (ofile, "%d\n", diffgraph_population[x]);
#endif
    }
    prog_box ("", 98);
    fprintf (ofile, "%d\n", world->victory.rockets_launched);
    fprintf (ofile, "%d\n", world->victory.rockets_launched_success);
    fprintf (ofile, "%d\n", world->flags.coal_survey_done);
    for (x = 0; x < PBAR_DATA_SIZE; x++)
	for (p = 0; p < NUM_PBARS; p++)
	    fprintf(ofile, "%d\n", pbars[p].data[x]);

    prog_box ("", 99);

    for (p = 0; p < NUM_PBARS; p++) {
	fprintf(ofile, "%d\n", pbars[p].oldtot);
	fprintf(ofile, "%d\n", pbars[p].diff);
    }

    fprintf (ofile, "%d\n", cheat_flag);
    fprintf (ofile, "%d\n", world->population.deaths.pollution.total);
    fprintf (ofile, "%f\n", world->population.deaths.pollution.history);
    fprintf (ofile, "%d\n", world->population.deaths.starve.total);
    fprintf (ofile, "%f\n", world->population.deaths.starve.history);
    fprintf (ofile, "%d\n", world->population.unemployment.years);
    fprintf (ofile, "%f\n", world->population.unemployment.history);
    fprintf (ofile, "%d\n", world->population.highest);
    fprintf (ofile, "%d\n", world->population.evacuated);
    fprintf (ofile, "%d\n", world->population.births);
    for (x = 0; x < NUMOF_MODULES; x++)
	fprintf (ofile, "%d\n", module_help_flag[x]);
    fprintf (ofile, "%d\n", 0);	/* dummy values */

    fprintf (ofile, "%d\n", 0);	/* backward compatibility */

    if (strlen (given_scene) > 1)
	fprintf (ofile, "%s\n", given_scene);
    else
	fprintf (ofile, "dummy\n");	/* 1 */

    fprintf (ofile, "%d\n", world->tech.highest_level);	/* 2 */

    fprintf (ofile, "sust %d %d %d %d %d %d %d %d %d %d\n",
                     world->sustain.ore_coal_tip.count,
                     world->sustain.port.count,
                     world->sustain.money.count,
                     world->sustain.population.count,
                     world->sustain.tech.count,
                     world->sustain.fire.count,
                     world->sustain.money.previous,
                     world->sustain.population.previous,
                     world->sustain.tech.previous,
                     world->sustain.flag );	/* 3 */

    fprintf (ofile, "dummy\n");	/* 4 */

    fprintf (ofile, "dummy\n");	/* 5 */

    fprintf (ofile, "dummy\n");	/* 6 */

    fprintf (ofile, "dummy\n");	/* 7 */

    fprintf (ofile, "dummy\n");	/* 8 */

    fprintf (ofile, "dummy\n");	/* 9 */

    fprintf (ofile, "dummy\n");	/* 10 */

    fclose (ofile);
    prog_box ("", 100);
}


void save_city (char *cname)
{
    char *s, *s2, *s3, *s4;
    int l;

    if ((l = strlen (cname)) < 2)
	return;
    if ((s = (char *) malloc (lc_save_dir_len + l + 16)) == 0)
	malloc_failure ();
    if ((s2 = (char *) malloc (lc_save_dir_len + l + 32)) == 0)
	malloc_failure ();
    if ((s3 = (char *) malloc ((lc_save_dir_len + l) * 2 + 32)) == 0)
	malloc_failure ();
    if ((s4 = (char *) malloc ((lc_save_dir_len + l) * 2 + 32)) == 0)
	malloc_failure ();

    sprintf (s, "%s%c%s", lc_save_dir, PATH_SLASH, cname);
    sprintf (s2, "%s%c%s", lc_save_dir, PATH_SLASH, "tmp-save");
    sprintf (s3, "gzip -f %s", s2);
    sprintf (s4, "mv %s.gz %s", s2, s);

#if defined (WIN32)
    save_city_raw (s);
#else
    save_city_raw (s2);
    if (system (s3) != 0)
	do_error ("gzip failed while in save_city");
    if (system (s4) != 0)
	do_error ("mv failed while in save_city");
#endif

    free (s);
    free (s2);
    free (s3);
    free (s4);
}

void load_city (char *cname)
{
    int i, x, y, z, n, p, ver;
    int num_pbars, pbar_data_size;
    int pbar_tmp;
    int dummy;
    FILE *ofile;
    char s[256];
    int tmp;

    if ((ofile = fopen_read_gzipped (cname)) == NULL) {
	printf (_("Can't open <%s> (gzipped)"), cname);
	do_error ("Can't open it!");
    }
    fscanf (ofile, "%d", &ver);
    if (ver < MIN_LOAD_VERSION) {
	ok_dial_box ("too-old.mes", BAD, 0L);
	fclose_read_gzipped (ofile);
	return;
    }

    init_pbars();
    num_pbars = NUM_PBARS;
    pbar_data_size = PBAR_DATA_SIZE;

    init_inventory();
    
    print_time_for_year();
    prog_box (_("Loading scene"), 0);

    for (x = 0; x < WORLD_SIDE_LEN; x++) {
	for (y = 0; y < WORLD_SIDE_LEN; y++) {
	    for (z = 0; z < sizeof(int); z++) {
		fscanf (ofile, "%d", &n);
		*(((unsigned char *) &MP_INFO(x,y).population) + z) = n;
	    }
	    for (z = 0; z < sizeof(int); z++) {
		fscanf (ofile, "%d", &n);
		*(((unsigned char *) &MP_INFO(x,y).flags) + z) = n;
	    }
	    for (z = 0; z < sizeof(unsigned short); z++) {
		fscanf (ofile, "%d", &n);
		*(((unsigned char *) &MP_INFO(x,y).coal_reserve) + z) = n;
	    }
	    for (z = 0; z < sizeof(unsigned short); z++) {
		fscanf (ofile, "%d", &n);
		*(((unsigned char *) &MP_INFO(x,y).ore_reserve) + z) = n;
	    }
	    for (z = 0; z < sizeof(int); z++) {
		fscanf (ofile, "%d", &n);
		*(((unsigned char *) &MP_INFO(x,y).int_1) + z) = n;
	    }
	    for (z = 0; z < sizeof(int); z++) {
		fscanf (ofile, "%d", &n);
		*(((unsigned char *) &MP_INFO(x,y).int_2) + z) = n;
	    }
	    for (z = 0; z < sizeof(int); z++) {
		fscanf (ofile, "%d", &n);
		*(((unsigned char *) &MP_INFO(x,y).int_3) + z) = n;
	    }
	    for (z = 0; z < sizeof(int); z++) {
		fscanf (ofile, "%d", &n);
		*(((unsigned char *) &MP_INFO(x,y).int_4) + z) = n;
	    }
	    for (z = 0; z < sizeof(int); z++) {
		fscanf (ofile, "%d", &n);
		*(((unsigned char *) &MP_INFO(x,y).int_5) + z) = n;
	    }
	    for (z = 0; z < sizeof(int); z++) {
		fscanf (ofile, "%d", &n);
		*(((unsigned char *) &MP_INFO(x,y).int_6) + z) = n;
	    }
	    for (z = 0; z < sizeof(int); z++) {
		fscanf (ofile, "%d", &n);
		*(((unsigned char *) &MP_INFO(x,y).int_7) + z) = n;
	    }
	    fscanf (ofile, "%d", &n);
	    MP_POL(x,y) = (unsigned short) n;
	    fscanf (ofile, "%d", &n);
	    MP_TYPE(x,y) = (short) n;

	    if (get_group_of_type(MP_TYPE(x,y)) == GROUP_MARKET)
		inventory(x,y);
	}
	if (((93 * x) / WORLD_SIDE_LEN) % 3 == 0)
	    prog_box ("", (93 * x) / WORLD_SIDE_LEN);
    }
    check_endian ();
    set_map_groups ();

    fscanf (ofile, "%d", &main_screen_originx);
    fscanf (ofile, "%d", &main_screen_originy);
    if (main_screen_originx > WORLD_SIDE_LEN - scr.main_win.w / 16 - 1)
	main_screen_originx = WORLD_SIDE_LEN - scr.main_win.w / 16 - 1;

    if (main_screen_originy > WORLD_SIDE_LEN - scr.main_win.h / 16 - 1)
	main_screen_originy = WORLD_SIDE_LEN - scr.main_win.h / 16 - 1;

    fscanf (ofile, "%d", &(world->time.total));
    simulate_calculate_date( world->time.total, &(world->time.date) );

    if (ver <= MM_MS_C_VER)
	i = OLD_MAX_NUMOF_SUBSTATIONS;
    else
	i = MAX_NUMOF_SUBSTATIONS;
    for (x = 0; x < i; x++)
    {
        fscanf (ofile, "%d", &(substations[x].x));
        fscanf (ofile, "%d", &(substations[x].y));
    }
    prog_box ("", 92);
    fscanf (ofile, "%d", &numof_substations); /* FIXME: beware, unsigned int */
    if (ver <= MM_MS_C_VER)
	i = OLD_MAX_NUMOF_MARKETS;
    else
	i = MAX_NUMOF_MARKETS;
    for (x = 0; x < i; x++)
    {
        fscanf (ofile, "%d", &(markets[x].x));
        fscanf (ofile, "%d", &(markets[x].y));
    }
    prog_box ("", 94);
    fscanf (ofile, "%d", &numof_markets); /* FIXME: beware, unsigned int */
    fscanf (ofile, "%d", &(world->population.pool));
    fscanf (ofile, "%d", &(world->money.total));
    fscanf (ofile, "%d", &(world->money.tax_rate.income));
    fscanf (ofile, "%d", &(world->money.tax_rate.coal));
    fscanf (ofile, "%d", &(world->money.dole_rate));
    fscanf (ofile, "%d", &(world->money.cost_rate.transport));
    fscanf (ofile, "%d", &(world->money.tax_rate.goods));
    fscanf (ofile, "%d", &export_tax);
    fscanf (ofile, "%d", &(world->money.tax_rate.exports));
    fscanf (ofile, "%d", &import_cost);
    fscanf (ofile, "%d", &(world->money.cost_rate.imports));
    fscanf (ofile, "%d", &(world->tech.level));
    if (world->tech.level > MODERN_WINDMILL_TECH)
	modern_windmill_flag = 1;
    fscanf (ofile, "%d", &tpopulation);
    fscanf (ofile, "%d", &tstarving_population);
    fscanf (ofile, "%d", &tunemployed_population);
    fscanf (ofile, "%d", &x);  /* waste_goods obsolete */
    fscanf (ofile, "%d", &(world->resources.power.made));
    fscanf (ofile, "%d", &(world->resources.power.used));
    fscanf (ofile, "%d", &(world->resources.coal.made));
    fscanf (ofile, "%d", &(world->resources.coal.used));
    fscanf (ofile, "%d", &(world->resources.goods.made));
    fscanf (ofile, "%d", &(world->resources.goods.used));
    fscanf (ofile, "%d", &(world->resources.ore.made));
    fscanf (ofile, "%d", &(world->resources.ore.used));
    fscanf (ofile, "%d", &dummy); /* &diff_old_population */

    /* Update variables calculated from those above */
    world->population.housed = tpopulation / NUMOF_DAYS_IN_MONTH;

    prog_box ("", 96);
    /* Get size of monthgraph array */
    if (ver <= MG_C_VER) {
	i = 120;
    } else {
	fscanf (ofile, "%d", &i);
    }
    for (x = 0; x < i; x++) {
	/* If more entries in file than will fit on screen, 
	   then we need to skip past them. */
	if (x >= monthgraph_size) {
	    fscanf (ofile, "%d", &dummy); /* &monthgraph_pop[x] */
	    fscanf (ofile, "%d", &dummy); /* &monthgraph_starve[x] */
	    fscanf (ofile, "%d", &dummy); /* &monthgraph_nojobs[x] */
	    fscanf (ofile, "%d", &dummy); /* &monthgraph_ppool[x] */
	} else {
	    fscanf (ofile, "%d", &monthgraph_pop[x]);
	    fscanf (ofile, "%d", &monthgraph_starve[x]);
	    fscanf (ofile, "%d", &monthgraph_nojobs[x]);
	    fscanf (ofile, "%d", &monthgraph_ppool[x]);
	}
	/* If our save file is old, skip past obsolete diffgraph entries */
	if (ver <= MG_C_VER) {
	    fscanf (ofile, "%d", &dummy); /* &diffgraph_power[x] */
	    fscanf (ofile, "%d", &dummy); /* &diffgraph_coal[x] */
	    fscanf (ofile, "%d", &dummy); /* &diffgraph_goods[x] */
	    fscanf (ofile, "%d", &dummy); /* &diffgraph_ore[x] */
	    fscanf (ofile, "%d", &dummy); /* &diffgraph_population[x] */
	}
    }
    /* If screen bigger than number of entries in file, pad with zeroes */
    while (x < monthgraph_size) {
	monthgraph_pop[x] = 0;
	monthgraph_starve[x] = 0;
	monthgraph_nojobs[x] = 0;
	monthgraph_ppool[x] = 0;
	x++;
    }
    prog_box ("", 98);
    fscanf (ofile, "%d", &(world->victory.rockets_launched));
    fscanf (ofile, "%d", &(world->victory.rockets_launched_success));
    fscanf (ofile, "%d", &(tmp));
    world->flags.coal_survey_done = (bool) tmp; /* convert integer to enum */
    
    for (x = 0; x < pbar_data_size; x++) {
	for (p = 0; p < num_pbars; p++) {
	    fscanf (ofile, "%d", &(pbar_tmp));
	    update_pbar(p,pbar_tmp,1);
/*	    fscanf (ofile, "%d", &(pbars[p].data[x])); */
	}
    }

    for (p = 0; p < num_pbars; p++)
	pbars[p].data_size = pbar_data_size;

    prog_box ("", 99);

    for (p = 0; p < num_pbars; p++) {
	fscanf (ofile, "%d", &(pbars[p].oldtot));
	fscanf (ofile, "%d", &(pbars[p].diff));
    }


    fscanf (ofile, "%d", &cheat_flag);
    fscanf (ofile, "%d", &(world->population.deaths.pollution.total));
    fscanf (ofile, "%f", &(world->population.deaths.pollution.history));
    fscanf (ofile, "%d", &(world->population.deaths.starve.total));
    fscanf (ofile, "%f", &(world->population.deaths.starve.history));
    fscanf (ofile, "%d", &(world->population.unemployment.years));
    fscanf (ofile, "%f", &(world->population.unemployment.history));
    fscanf (ofile, "%d", &(world->population.highest));
    fscanf (ofile, "%d", &(world->population.evacuated));
    fscanf (ofile, "%d", &(world->population.births));
    for (x = 0; x < NUMOF_MODULES; x++)
	fscanf (ofile, "%d", &(module_help_flag[x]));
    fscanf (ofile, "%d", &x);	/* just dummy reads */
    fscanf (ofile, "%d", &x);	/* for backwards compatibility. */

    /* 10 dummy strings, for missed out things, have been put in save. */
    /* Input from this point uses them. */
    /* XXX: WCK: Huh? Missed out things? */

    fscanf (ofile, "%128s", given_scene);
    if (strncmp (given_scene, "dummy", 5) == 0 || strlen (given_scene) < 3)
	given_scene[0] = 0;
    fscanf (ofile, "%128s", s);
    if (strncmp (given_scene, "dummy", 5) != 0)
	sscanf (s, "%d", &(world->tech.highest_level));
    else
	world->tech.highest_level = 0;
    fgets (s, 80, ofile);		/* this is the CR */

    fgets (s, 80, ofile);
    if (10 == sscanf( s, "sust %d %d %d %d %d %d %d %d %d %d",
                          &(world->sustain.ore_coal_tip.count),
                          &(world->sustain.port.count),
                          &(world->sustain.money.count),
                          &(world->sustain.population.count),
                          &(world->sustain.tech.count),
                          &(world->sustain.fire.count),
                          &(world->sustain.money.previous),
                          &(world->sustain.population.previous),
                          &(world->sustain.tech.previous),
                          &(tmp) ))
    {
        world->sustain.flag = (bool) tmp; /* convert integer to enum */
        world->sustain.ore_coal_tip.flag = true;
        world->sustain.port.flag = true;

        /* GCS FIX: Check after loading file if screen is drawn OK */
        /* draw_sustainable_window (); */
    }
    else
    {
	    world->sustain.flag = false;
	    world->sustain.ore_coal_tip.count = 0;
	    world->sustain.port.count = 0;
	    world->sustain.money.count = 0;
	    world->sustain.population.count = 0;
	    world->sustain.tech.count = 0;
	    world->sustain.fire.count = 0;
	    world->sustain.money.previous = 0;
	    world->sustain.population.previous = 0;
	    world->sustain.tech.previous = 0;
    }
    fclose_read_gzipped (ofile);

    numof_shanties = count_groups (GROUP_SHANTY);
    numof_communes = count_groups (GROUP_COMMUNE);
    prog_box ("", 100);

    /* set up the university intake. */
    x = count_groups (GROUP_UNIVERSITY);
    if (x > 0) {
	world->knowledge.university_intake_rate
		= (count_groups (GROUP_SCHOOL) * 20) / x;
	if (world->knowledge.university_intake_rate > 100)
	    world->knowledge.university_intake_rate = 100;
    }
    else
	world->knowledge.university_intake_rate = 50;
    for (x = 0; x < WORLD_SIDE_LEN; x++)
    {
	for (y = 0; y < WORLD_SIDE_LEN; y++)
	{
	    update_tech_dep (x, y);
	}
    }

    unhighlight_module_button (selected_module);
    selected_module = sbut[7];	/* 7 is track.  Watch out though! */
    highlight_module_button (selected_module);
    set_selected_module (CST_TRACK_LR);

    print_total_money ();
    reset_animation_times ();
    map_power_grid (); /* WCK:  Is this safe to do here? */
}

void
load_saved_city (char *s)
{
    char *cname = (char *) malloc (strlen (lc_save_dir) + strlen (s) + 2);
    sprintf (cname, "%s%c%s", lc_save_dir, PATH_SLASH, s);
    load_city (cname);
    free (cname);
}

void reset_animation_times (void)
{
    int x, y;
    for (y = 0; y < WORLD_SIDE_LEN; y++)
	for (x = 0; x < WORLD_SIDE_LEN; x++) {
	    if (GROUP_IS_RESIDENCE(MP_GROUP(x,y)))
		MP_INFO(x,y).int_3 = 0;
	    else if (MP_GROUP(x,y) == GROUP_WINDMILL)
		MP_INFO(x,y).int_4 = 0;
	    else if (MP_GROUP(x,y) == GROUP_BLACKSMITH)
		MP_INFO(x,y).int_4 = 0;
	    else if (MP_GROUP(x,y) == GROUP_MILL)
		MP_INFO(x,y).int_4 = 0;
	    else if (MP_GROUP(x,y) == GROUP_POTTERY)
		MP_INFO(x,y).int_4 = 0;
	    else if (MP_GROUP(x,y) == GROUP_CRICKET)
		MP_INFO(x,y).int_4 = 0;
	    else if (MP_GROUP(x,y) == GROUP_FIRESTATION)
		MP_INFO(x,y).int_4 = 0;
	    else if (MP_GROUP(x,y) == GROUP_FIRE)
	    {
		MP_INFO(x,y).int_1 = 0;
		MP_INFO(x,y).int_3 = 0;
	    }
	    else if (MP_GROUP(x,y) == GROUP_COMMUNE)
		MP_INFO(x,y).int_1 = 0;
	    else if (MP_GROUP(x,y) == GROUP_ROCKET)
		MP_INFO(x,y).int_5 = 0;
	    else if (MP_GROUP(x,y) == GROUP_INDUSTRY_H)
		MP_INFO(x,y).int_6 = 0;
	    else if (MP_GROUP(x,y) == GROUP_INDUSTRY_L)
		MP_INFO(x,y).int_7 = 0;
	}
}

/* Returns 1 if the city is proper version */
int 
verify_city (char *cname)
{
    FILE* fp;
    char* s;
    int v;

    if (strlen(cname) == 0) {
	return 0;
    }
    if ((s = (char *) malloc (lc_save_dir_len + strlen(cname) + 2)) == 0)
	malloc_failure ();
    sprintf (s, "%s%c%s", lc_save_dir, PATH_SLASH, cname);
    if (!file_exists(s)) {
	free (s);
	return 0;
    }
    fp = fopen_read_gzipped (s);
    if (fp == NULL) {
	v = 0;
    } else if (1 != fscanf (fp, "%d", &v)) {
	v = 0;
    }
    fclose_read_gzipped (fp);
    free (s);
    return v == VERSION_INT;
}

#ifdef MP_SANITY_CHECK
void
sanity_check (void)
{
    static int flag = 0;
    int x, y, xx, yy;
    for (x = 0; x < WORLD_SIDE_LEN; x++)
	for (y = 0; y < WORLD_SIDE_LEN; y++) {
	    if (MP_TYPE(x,y) == CST_USED) {
		xx = MP_INFO(x,y).int_1;
		yy = MP_INFO(x,y).int_2;
		if (xx < (x - 4) || yy < (y - 4) || xx > x || yy > y ||
		    xx < 0 || xx > WORLD_SIDE_LEN ||
		    yy < 0 || yy > WORLD_SIDE_LEN) {
		    printf ("Sanity failed at %d %d, points to %d %d\n", x, y, xx, yy);
		    if (flag == 0)
			yn_dial_box ("MP sanity check error",
				     "Please mail  lincity-users@lists.sourceforge.net",
				     "telling me what you just did.",
				     "Do you think I'll find this bug?");
		    flag = 1;
		}
	    }
	}
}
#endif


void check_endian (void)
{
    static int flag = 0;
    char *cs;
    int t, x, y;
    t = 0;
    cs = (char *) &t;
    *cs = 1;
    if (t == 1)			/* little endian */
	return;
    printf ("t=%x\n", t);
    if (flag == 0) {
	flag = 1;
    }
    for (y = 0; y < WORLD_SIDE_LEN; y++) {
	for (x = 0; x < WORLD_SIDE_LEN; x++) {
	    eswap32 (&(MP_INFO(x,y).population));
	    eswap32 (&(MP_INFO(x,y).flags));
	    if (sizeof (short) == 2) {
		eswap16 (&(MP_INFO(x,y).coal_reserve));
		eswap16 (&(MP_INFO(x,y).ore_reserve));
	    } else if (sizeof (short) == 4) {
		eswap32 ((int *) &(MP_INFO(x,y).coal_reserve));
		eswap32 ((int *) &(MP_INFO(x,y).ore_reserve));
	    } else {
		printf ("Strange size (%lu) for short, please mail me.\n",
			sizeof (short));
	    }
	    eswap32 (&(MP_INFO(x,y).int_1));
	    eswap32 (&(MP_INFO(x,y).int_2));
	    eswap32 (&(MP_INFO(x,y).int_3));
	    eswap32 (&(MP_INFO(x,y).int_4));
	    eswap32 (&(MP_INFO(x,y).int_5));
	    eswap32 (&(MP_INFO(x,y).int_6));
	    eswap32 (&(MP_INFO(x,y).int_7));
	}
    }
}

void eswap32 (int *i)
{
  char *cs, c1, c2, c3, c4;
  cs = (char *) i;
  c1 = *cs;
  c2 = *(cs + 1);
  c3 = *(cs + 2);
  c4 = *(cs + 3);
  *(cs++) = c4;
  *(cs++) = c3;
  *(cs++) = c2;
  *cs = c1;
}

void eswap16 (unsigned short *i)
{
  char *cs, c1, c2;
  cs = (char *) i;
  c1 = *cs;
  c2 = *(cs + 1);
  *(cs++) = c2;
  *cs = c1;
}
