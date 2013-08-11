#ifndef LINCITY_RESOURCES_H
#define LINCITY_RESOURCES_H

/*
 * There are 6 different resources in lincity (usually showed in this order):
 *
 *    food, jobs, coal, goods, ore and steel
 *
 * The seventh one (waste) was being deprecated in the last version, so
 * it isn't defined here.
 */

#define NUM_RESOURCES  6

typedef enum
{
    RESOURCE_FOOD,
    RESOURCE_JOBS,
    RESOURCE_COAL,
    RESOURCE_GOODS,
    RESOURCE_ORE,
    RESOURCE_STEEL,

} Resource;


#endif /* LINCITY_RESOURCES_H */
