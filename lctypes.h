/* ---------------------------------------------------------------------- *
 * lctypes.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */
#ifndef __lctypes_h__
#define __lctypes_h__

#define CST_GREEN		0

/* H=horiz V=vertical LD=left down etc.   L= Live D=dead */
#define CST_POWERL_H_L		1
#define CST_POWERL_V_L  	2
#define CST_POWERL_LD_L   	3
#define CST_POWERL_RD_L   	4
#define CST_POWERL_LU_L    	5
#define CST_POWERL_RU_L    	6
#define CST_POWERL_LDU_L	7
#define CST_POWERL_LDR_L	8
#define CST_POWERL_LUR_L	9
#define CST_POWERL_UDR_L	10
#define CST_POWERL_LUDR_L	11

#define CST_POWERL_H_D          12
#define CST_POWERL_V_D          13
#define CST_POWERL_LD_D         14
#define CST_POWERL_RD_D         15
#define CST_POWERL_LU_D         16
#define CST_POWERL_RU_D         17
#define CST_POWERL_LDU_D        18
#define CST_POWERL_LDR_D        19
#define CST_POWERL_LUR_D        20
#define CST_POWERL_UDR_D        21
#define CST_POWERL_LUDR_D       22

#define CST_SHANTY              23

/* move this to number 1 or 255 or something. OK here for now. */
#define CST_USED		39

#define CST_POWERS_SOLAR	40

#define CST_POWERS_COAL_EMPTY	41
#define CST_POWERS_COAL_LOW     42
#define CST_POWERS_COAL_MED     43
#define CST_POWERS_COAL_FULL    44


#define CST_BURNT		49

#define CST_SUBSTATION_R	50
#define CST_SUBSTATION_G        51
#define CST_SUBSTATION_RG       52

#define CST_UNIVERSITY		53

#define CST_RESIDENCE_LL	61
#define CST_RESIDENCE_ML	62
#define CST_RESIDENCE_HL	63
#define CST_RESIDENCE_LH        64
#define CST_RESIDENCE_MH        65
#define CST_RESIDENCE_HH        66


#define CST_MARKET_EMPTY	71
#define CST_MARKET_LOW          72
#define CST_MARKET_MED          73
#define CST_MARKET_FULL         74


#define CST_RECYCLE		79

#define CST_TRACK_LR		80
#define CST_TRACK_LU            81
#define CST_TRACK_LD            82
#define CST_TRACK_UD            83
#define CST_TRACK_UR            84
#define CST_TRACK_DR            85
#define CST_TRACK_LUR           86
#define CST_TRACK_LDR           87
#define CST_TRACK_LUD           88
#define CST_TRACK_UDR           89
#define CST_TRACK_LUDR          90

#define CST_PARKLAND_PLANE	91
#define CST_PARKLAND_LAKE	92

#define CST_MONUMENT_0		93
#define CST_MONUMENT_1          94
#define CST_MONUMENT_2          95
#define CST_MONUMENT_3          96
#define CST_MONUMENT_4          97
#define CST_MONUMENT_5          98


#define CST_COALMINE_EMPTY	100
#define CST_COALMINE_LOW	101
#define CST_COALMINE_MED	102
#define CST_COALMINE_FULL	103

#define CST_RAIL_LR            110
#define CST_RAIL_LU            111
#define CST_RAIL_LD            112
#define CST_RAIL_UD            113
#define CST_RAIL_UR            114
#define CST_RAIL_DR            115
#define CST_RAIL_LUR           116
#define CST_RAIL_LDR           117
#define CST_RAIL_LUD           118
#define CST_RAIL_UDR           119
#define CST_RAIL_LUDR          120

#define CST_FIRE_1             121
#define CST_FIRE_2             122
#define CST_FIRE_3             123
#define CST_FIRE_4             124
#define CST_FIRE_5             125
#define CST_FIRE_DONE1         126
#define CST_FIRE_DONE2         127
#define CST_FIRE_DONE3         128
#define CST_FIRE_DONE4         129


#define CST_ROAD_LR            130
#define CST_ROAD_LU            131
#define CST_ROAD_LD            132
#define CST_ROAD_UD            133
#define CST_ROAD_UR            134
#define CST_ROAD_DR            135
#define CST_ROAD_LUR           136
#define CST_ROAD_LDR           137
#define CST_ROAD_LUD           138
#define CST_ROAD_UDR           139
#define CST_ROAD_LUDR          140


#define CST_OREMINE_5           146
#define CST_OREMINE_6           147
#define CST_OREMINE_7           148
#define CST_OREMINE_8           149

#define CST_OREMINE_1		150
#define CST_OREMINE_2		151
#define CST_OREMINE_3		152
#define CST_OREMINE_4		153


#define CST_HEALTH		155

#define CST_SCHOOL		156

#define CST_EX_PORT		161

#define CST_MILL_0              162
#define CST_MILL_1              163
#define CST_MILL_2              164
#define CST_MILL_3              165
#define CST_MILL_4              166
#define CST_MILL_5              167
#define CST_MILL_6              168


#define CST_ROCKET_1		180
#define CST_ROCKET_2            181
#define CST_ROCKET_3		182
#define CST_ROCKET_4		183
#define CST_ROCKET_5            184
#define CST_ROCKET_6            185
#define CST_ROCKET_7		186
#define CST_ROCKET_FLOWN	187

#define CST_WINDMILL_1_G        190
#define CST_WINDMILL_2_G        191
#define CST_WINDMILL_3_G        192

#define CST_WINDMILL_1_RG       193
#define CST_WINDMILL_2_RG       194
#define CST_WINDMILL_3_RG       195

#define CST_WINDMILL_1_R        196
#define CST_WINDMILL_2_R        197
#define CST_WINDMILL_3_R        198

#define CST_WINDMILL_1_W        199
#define CST_WINDMILL_2_W        200
#define CST_WINDMILL_3_W        201


#define CST_BLACKSMITH_0          202
#define CST_BLACKSMITH_1          203
#define CST_BLACKSMITH_2          204
#define CST_BLACKSMITH_3          205
#define CST_BLACKSMITH_4          206
#define CST_BLACKSMITH_5          207
#define CST_BLACKSMITH_6          208

#define CST_POTTERY_0             210
#define CST_POTTERY_1             211
#define CST_POTTERY_2             212
#define CST_POTTERY_3             213
#define CST_POTTERY_4             214
#define CST_POTTERY_5             215
#define CST_POTTERY_6             216
#define CST_POTTERY_7             217
#define CST_POTTERY_8             218
#define CST_POTTERY_9             219
#define CST_POTTERY_10            220

#define CST_WATER               221
#define CST_WATER_D             222
#define CST_WATER_R             223
#define CST_WATER_U             224
#define CST_WATER_L             225
#define CST_WATER_LR            226
#define CST_WATER_UD            227
#define CST_WATER_LD            228
#define CST_WATER_RD            229
#define CST_WATER_LU            230
#define CST_WATER_UR            231
#define CST_WATER_LUD           232
#define CST_WATER_LRD           233
#define CST_WATER_LUR           234
#define CST_WATER_URD           235
#define CST_WATER_LURD          236

#define CST_CRICKET_1           240
#define CST_CRICKET_2           241
#define CST_CRICKET_3           242
#define CST_CRICKET_4           243
#define CST_CRICKET_5           244
#define CST_CRICKET_6           245
#define CST_CRICKET_7           246

#define CST_FIRESTATION_1         250
#define CST_FIRESTATION_2         251
#define CST_FIRESTATION_3         252
#define CST_FIRESTATION_4         253
#define CST_FIRESTATION_5         254
#define CST_FIRESTATION_6         255
#define CST_FIRESTATION_7         256
#define CST_FIRESTATION_8         257
#define CST_FIRESTATION_9         258
#define CST_FIRESTATION_10        259

#define CST_TIP_0               260
#define CST_TIP_1               261
#define CST_TIP_2               262
#define CST_TIP_3               263
#define CST_TIP_4               264
#define CST_TIP_5               265
#define CST_TIP_6               266
#define CST_TIP_7               267
#define CST_TIP_8               268


#define CST_COMMUNE_1           270
#define CST_COMMUNE_2           271
#define CST_COMMUNE_3           272
#define CST_COMMUNE_4           273
#define CST_COMMUNE_5           274
#define CST_COMMUNE_6           275
#define CST_COMMUNE_7           276
#define CST_COMMUNE_8           277
#define CST_COMMUNE_9           278
#define CST_COMMUNE_10          279
#define CST_COMMUNE_11          280
#define CST_COMMUNE_12          281
#define CST_COMMUNE_13          282
#define CST_COMMUNE_14          283


#define CST_INDUSTRY_H_C        290

#define CST_INDUSTRY_H_L1        291
#define CST_INDUSTRY_H_L2        292
#define CST_INDUSTRY_H_L3        293
#define CST_INDUSTRY_H_L4        294
#define CST_INDUSTRY_H_L5        295
#define CST_INDUSTRY_H_L6        296
#define CST_INDUSTRY_H_L7        297
#define CST_INDUSTRY_H_L8        298

#define CST_INDUSTRY_H_M1        299
#define CST_INDUSTRY_H_M2        300
#define CST_INDUSTRY_H_M3        301
#define CST_INDUSTRY_H_M4        302
#define CST_INDUSTRY_H_M5        303
#define CST_INDUSTRY_H_M6        304
#define CST_INDUSTRY_H_M7        305
#define CST_INDUSTRY_H_M8        306

#define CST_INDUSTRY_H_H1        307
#define CST_INDUSTRY_H_H2        308
#define CST_INDUSTRY_H_H3        309
#define CST_INDUSTRY_H_H4        310
#define CST_INDUSTRY_H_H5        311
#define CST_INDUSTRY_H_H6        312
#define CST_INDUSTRY_H_H7        313
#define CST_INDUSTRY_H_H8        314

#define CST_INDUSTRY_L_C         315

#define CST_INDUSTRY_L_Q1        316
#define CST_INDUSTRY_L_Q2        317
#define CST_INDUSTRY_L_Q3        318
#define CST_INDUSTRY_L_Q4        319

#define CST_INDUSTRY_L_L1        320
#define CST_INDUSTRY_L_L2        321
#define CST_INDUSTRY_L_L3        322
#define CST_INDUSTRY_L_L4        323

#define CST_INDUSTRY_L_M1        324
#define CST_INDUSTRY_L_M2        325
#define CST_INDUSTRY_L_M3        326
#define CST_INDUSTRY_L_M4        327

#define CST_INDUSTRY_L_H1        328
#define CST_INDUSTRY_L_H2        329
#define CST_INDUSTRY_L_H3        330
#define CST_INDUSTRY_L_H4        331

#define CST_FARM_O0              332
#define CST_FARM_O1              333
#define CST_FARM_O2              334
#define CST_FARM_O3              335
#define CST_FARM_O4              336
#define CST_FARM_O5              337
#define CST_FARM_O6              338
#define CST_FARM_O7              339
#define CST_FARM_O8              340
#define CST_FARM_O9              341
#define CST_FARM_O10             342
#define CST_FARM_O11             343
#define CST_FARM_O12             344
#define CST_FARM_O13             345
#define CST_FARM_O14             346
#define CST_FARM_O15             347
#define CST_FARM_O16             348

/*
  //    *********************************
  //    400 is the maximum at the moment.
  //    *********************************
*/

#endif /* __lctypes_h__ */
