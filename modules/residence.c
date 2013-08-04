/* ---------------------------------------------------------------------- *
 * residence.c
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * (c) Corey Keasling, 2004
 * ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------- */

/* module header file */
#include "residence.h"

/* system libraries */
#include <stdlib.h> /* rand() */

/* app general headers */
#include "lcconfig.h"
#include "lctypes.h"
#include "lcintl.h"

/* other modules */
#include "mps.h"
#include "stats.h"
#include "engglobs.h"
#include "power.h"
#include "market.h"

/* ----------------------------------------------------------------- */


/* old lin-city.h definitions */
/* RESIDENCE?_BRM is the birth rate modifier */
/* RESIDENCE?_DRM is the death rate modifier */
#define RESIDENCE_BASE_BR     100
#define RESIDENCE_BASE_DR     (68*12)
#define RESIDENCE_BRM_HEALTH  5
#define RESIDENCE1_BRM (RESIDENCE_BASE_BR*12)
#define RESIDENCE1_DRM ((RESIDENCE_BASE_DR*3)/4)
#define RESIDENCE2_BRM 0
#define RESIDENCE2_DRM 0
#define RESIDENCE3_BRM (RESIDENCE_BASE_BR+RESIDENCE_BASE_BR/4)
#define RESIDENCE3_DRM ((RESIDENCE_BASE_DR)/2)
#define RESIDENCE4_BRM (RESIDENCE_BASE_BR*18)
#define RESIDENCE4_DRM ((RESIDENCE_BASE_DR*3)/4)
#define RESIDENCE5_BRM (RESIDENCE_BASE_BR/2)
#define RESIDENCE5_DRM ((RESIDENCE_BASE_DR)/4)
#define RESIDENCE6_BRM 0
#define RESIDENCE6_DRM ((RESIDENCE_BASE_DR)/4)
/* RESIDENCE_PPM is the people_pool mobitily. Higher number=less mobile. */
#define RESIDENCE_PPM   20
#define DAYS_PER_STARVE 20
#define POWER_USE_PER_PERSON 3
#define POWER_RES_OVERHEAD 30
#define WORKING_POP_PERCENT 45
#define JOB_SWING 15
#define CRICKET_JOB_SWING 4
#define HC_JOB_SWING 10
#define MIN_RES_POPULATION 10


void
do_residence (int x, int y)
{
    /*
      // int_1 is a job swingometer to choose +/- JOB_SWING% of normal
      // int_2 is the date of the last starve
      // int 3 is the real time for the next icon update
      // int_4 is the birth rate modifier.
      // int_5 is the death rate modifier.
      */
    int p;                           /* population */
    int bad = 35, good = 30;         /* (un)desirability of living here */
    int r, po, swing;
    int hc = 0;                      /* have health cover ? */
    int brm = 0, drm = 0;            /* birth/death rate modifier */
    int cc = 0;

    p = MP_INFO(x,y).population;
    if ((MP_INFO(x,y).flags & FLAG_HEALTH_COVER) != 0)
    {
	brm += RESIDENCE_BRM_HEALTH;
	good += 15;
	hc = 1;
    }
    if ((MP_INFO(x,y).flags & FLAG_FIRE_COVER) == 0)
	bad += 5;
    else
	good += 15;
    if ((MP_INFO(x,y).flags & FLAG_CRICKET_COVER) != 0)
    {
	good += 20;
	cc = CRICKET_JOB_SWING;
    }
    /* normal deaths + pollution deaths */
    po = ((MP_POL(x,y) / 50) + 1);
    if ((RESIDENCE_BASE_DR - MP_INFO(x,y).int_5 - po) > 1)
	r = rand () % (RESIDENCE_BASE_DR - MP_INFO(x,y).int_5 - po);
    else
	r = 2;
    if (p > 0 && (r < po))
    {
	if (r == 0 || hc == 0)
	    p--;
	else if (hc != 0 && po > 10 && rand () % 4 == 0)
	{
	    p--;
	    world->population.deaths.unnatural_month++;
	    world->population.deaths.pollution.total++;
	    world->population.deaths.pollution.history += 1.0;
	    bad += 100;
	}
	if (r > 0 && hc == 0)
	{
	    world->population.deaths.unnatural_month++;
	    world->population.deaths.pollution.total++;
	    world->population.deaths.pollution.history += 1.0;
	    bad += 100;
	}
    }
    /* normal births - must have food and jobs... and people */
    if ((MP_INFO(x,y).flags & (FLAG_FED + FLAG_EMPLOYED))
	== (FLAG_FED + FLAG_EMPLOYED)
	&& (rand () % (RESIDENCE_BASE_BR + MP_INFO(x,y).int_4) == 1) 
	&& p > 0)
    {
	p++;
	world->population.births++;
	good += 50;
    }
    /* are people starving. */
    if ((MP_INFO(x,y).flags & FLAG_FED) == 0 && p > 0)
    {
	if (rand () % DAYS_PER_STARVE == 1)
	{
	    p--;
	    world->population.deaths.unnatural_month++;
	    world->population.deaths.starve.total++;
	    world->population.deaths.starve.history += 1.0;
	}
	world->population.starving_day += p;
	bad += 250;
	drm += 100;
	MP_INFO(x,y).int_2 = world->time.total;	/* for the starve screen */
    }
    /* kick one out if overpopulated */
    if (MP_TYPE(x,y) == CST_RESIDENCE_LL)
    {
	brm += RESIDENCE1_BRM;
	drm += p * 8;
	if (p > 50)
	{
	    p--;
	    world->population.pool++;
	    brm += 20;
	}
    }
    else if (MP_TYPE(x,y) == CST_RESIDENCE_ML)
    {
	brm += RESIDENCE2_BRM;
	drm += p * 3;
	if (p > 100)
	{
	    p--;
	    world->population.pool++;
	    brm += 10;
	}
    }
    else if (MP_TYPE(x,y) == CST_RESIDENCE_HL)
    {
	brm += RESIDENCE3_BRM;
	drm += p;
	good += 40;
	if (p > 200)
	{
	    p--;
	    world->population.pool++;
	    brm += 10;
	}
    }
    else if (MP_TYPE(x,y) == CST_RESIDENCE_LH)
    {
	brm += RESIDENCE4_BRM;
	drm += p * 5;
	if (p > 100)
	{
	    p--;
	    world->population.pool++;
	    brm += 20;
	}
    }
    else if (MP_TYPE(x,y) == CST_RESIDENCE_MH)
    {
	brm += RESIDENCE5_BRM;
	drm += p / 2;
	if (p > 200)
	{
	    p--;
	    world->population.pool++;
	    brm += 10;
	}
    }
    else if (MP_TYPE(x,y) == CST_RESIDENCE_HH)
    {
	good += 100;
	brm += RESIDENCE6_BRM;
	drm += p;
	if (p > 400)
	{
	    p--;
	    world->population.pool++;
	    brm += 10;
	}
    }

    world->population.total_day += p;

    /* now get power */
    if (get_power (x, y, POWER_RES_OVERHEAD
		   + (POWER_USE_PER_PERSON * p), 0) != 0)
    {
	MP_INFO(x,y).flags |= FLAG_POWERED;
	MP_INFO(x,y).flags |= FLAG_HAD_POWER;
	good += 10;
    }
    else
    {
	MP_INFO(x,y).flags &= (0xffffffff - FLAG_POWERED);
	bad += 15;
	if ((MP_INFO(x,y).flags & FLAG_HAD_POWER) != 0)
	    bad += 50;
    }
    /* now get fed */
    if (get_food (x, y, p) != 0)
    {
	MP_INFO(x,y).flags |= FLAG_FED;
	good += 10;
    }
    else
	MP_INFO(x,y).flags &= (0xffffffff - FLAG_FED);
    /* now supply jobs and buy goods if employed */
    if (MP_INFO(x,y).int_1 > 0)
	swing = JOB_SWING + (hc * HC_JOB_SWING) + cc;
    else
	swing = -(JOB_SWING + (hc * HC_JOB_SWING) + cc);
    if (put_jobs (x, y, ((p * (WORKING_POP_PERCENT + swing)) / 100)) != 0)
    {
	MP_INFO(x,y).flags |= FLAG_EMPLOYED;
	MP_INFO(x,y).int_1++;
	if (MP_INFO(x,y).int_1 > 10)
	    MP_INFO(x,y).int_1 = 10;
	good += 20;
	if (get_goods (x, y, p / 4) != 0)
	{
	    good += 10;
	    if (get_power (x, y, p / 2, 0) != 0)	/* goods use power */

	    {
		good += 5;
		brm += 10;
		/*     buy more goods if got power for them */
		if (get_goods (x, y, p / 4) != 0)
		    good += 5;
	    }
	    else
		bad += 5;
	}
    }
    else if (MP_INFO(x,y).int_1 < 10)
    {
	MP_INFO(x,y).flags &= (0xffffffff - FLAG_EMPLOYED);
	MP_INFO(x,y).int_1 -= 11;
	if (MP_INFO(x,y).int_1 < -300)
	    MP_INFO(x,y).int_1 = -300;
	world->population.unemployed_day += p;
	world->population.unemployment.days += p;
	if (world->population.unemployment.days >= NUMOF_DAYS_IN_YEAR)
	{
	    world->population.unemployment.years++;
	    /* think we're ok doing this, max of about 120 added each time. */
	    world->population.unemployment.days -= NUMOF_DAYS_IN_YEAR;
	    world->population.unemployment.history += 1.0;
	}
	unemployment_cost += p;	/* hmmm */

	bad += 70;
    }
    else
    {
	MP_INFO(x,y).int_1 -= 20;
	bad += 50;
    }
    drm += p / 4;
    /* world->population.pool stuff */
    bad += p / 2;
    bad += MP_POL(x,y) / 20;
    good += world->population.pool / 27;
    r = rand () % ((good + bad) * RESIDENCE_PPM);
    if (r < bad)
    {
	if (p > MIN_RES_POPULATION)
	{
	    p--;
	    world->population.pool++;
	}
    }
    else if (world->population.pool > 0 && r > ((good + bad) * (RESIDENCE_PPM - 1) + bad))
    {
	p++;
	world->population.pool--;
    }
    MP_INFO(x,y).population = p;
    MP_INFO(x,y).int_4 = brm;
    MP_INFO(x,y).int_5 = drm;
}

void
mps_residence (int x, int y)
{
    int i = 0;
    char * p;

    mps_store_title(i++,_("Residence"));

    i++;

    mps_store_sd(i++,_("People"), MP_INFO(x,y).population);

    p = ((MP_INFO(x,y).flags & FLAG_POWERED) != 0) ? _("YES") : _("NO");
    mps_store_ss(i++, _("Power"), p);

    p = ((MP_INFO(x,y).flags & FLAG_FED) != 0) ? _("YES") : _("NO");
    mps_store_ss(i++, _("Fed"), p);

    p = ((MP_INFO(x,y).flags & FLAG_EMPLOYED) != 0) ? _("YES") : _("NO");
    mps_store_ss(i++, _("Employed"), p);

    p = ((MP_INFO(x,y).flags & FLAG_HEALTH_COVER) != 0) ? _("YES") : _("NO");
    mps_store_ss(i++, _("Health Cvr"), p);

    p = ((MP_INFO(x,y).flags & FLAG_FIRE_COVER) != 0) ? _("YES") : _("NO");
    mps_store_ss(i++, _("Fire"), p);

    p = ((MP_INFO(x,y).flags & FLAG_CRICKET_COVER) != 0) ? _("YES") : _("NO");
    mps_store_ss(i++, _("Cricket"), p);

    mps_store_sd(i++, _("Pollution"), MP_POL(x,y));

    p = (MP_INFO(x,y).int_1 >= 10) ? _("good") : _("poor");
    mps_store_ss(i++, _("Job"), p);

}
