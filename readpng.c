/* ---------------------------------------------------------------------- *
 * readpng.c
 * This file is part of lincity (see COPYRIGHT for copyright information).
 * ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------- */

/* module header file */
#include "readpng.h"

/* system libraries */
#include <stdlib.h>

#include <png.h>

/* app general headers */
#include "lintypes.h" /* GROUP_* dependencies */
#include "lctypes.h"  /* CST_* dependencies */

/* other modules */

/* ----------------------------------------------------------------- */

/* Read a PNG file.  You may want to return an error code if the read
 * fails (depending upon the failure).  There are two "prototypes" given
 * here - one where we are given the filename, and we need to open the
 * file, and the other where we are given an open file (possibly with
 * some or all of the magic bytes read - see comments above).
 */
#define ERROR -1
#define OK 0

/*
 * old name of graphic files -- now is a spritesheet in a .png file
 */
#define LCT_GREEN_G		"green"
#define LCT_POWERL_H_L_G	"powerlhl"
#define LCT_POWERL_V_L_G  	"powerlvl"
#define LCT_POWERL_LD_L_G 	"powerlldl"
#define LCT_POWERL_RD_L_G 	"powerlrdl"
#define LCT_POWERL_LU_L_G  	"powerllul"
#define LCT_POWERL_RU_L_G  	"powerlrul"
#define LCT_POWERL_LDU_L_G	"powerlldul"
#define LCT_POWERL_LDR_L_G	"powerlldrl"
#define LCT_POWERL_LUR_L_G	"powerllurl"
#define LCT_POWERL_UDR_L_G	"powerludrl"
#define LCT_POWERL_LUDR_L_G	"powerlludrl"
#define LCT_POWERL_H_D_G        "powerlhd"
#define LCT_POWERL_V_D_G        "powerlvd"
#define LCT_POWERL_LD_D_G       "powerlldd"
#define LCT_POWERL_RD_D_G       "powerlrdd"
#define LCT_POWERL_LU_D_G       "powerllud"
#define LCT_POWERL_RU_D_G       "powerlrud"
#define LCT_POWERL_LDU_D_G      "powerlldud"
#define LCT_POWERL_LDR_D_G      "powerlldrd"
#define LCT_POWERL_LUR_D_G      "powerllurd"
#define LCT_POWERL_UDR_D_G      "powerludrd"
#define LCT_POWERL_LUDR_D_G     "powerlludrd"
#define LCT_SHANTY_G            "shanty"
#define LCT_POWERS_SOLAR_G	"powerssolar"
#define LCT_POWERS_COAL_EMPTY_G	"powerscoal-empty"
#define LCT_POWERS_COAL_LOW_G   "powerscoal-low"
#define LCT_POWERS_COAL_MED_G   "powerscoal-med"
#define LCT_POWERS_COAL_FULL_G  "powerscoal-full"
#define LCT_BURNT_G		"burnt_land"
#define LCT_SUBSTATION_R_G	"substation-R"
#define LCT_SUBSTATION_G_G      "substation-G"
#define LCT_SUBSTATION_RG_G     "substation-RG"
#define LCT_UNIVERSITY_G	"university"
#define LCT_RESIDENCE_LL_G	"reslowlow"
#define LCT_RESIDENCE_ML_G	"resmedlow"
#define LCT_RESIDENCE_HL_G	"reshilow"
#define LCT_RESIDENCE_LH_G      "reslowhi"
#define LCT_RESIDENCE_MH_G      "resmedhi"
#define LCT_RESIDENCE_HH_G      "reshihi"
#define LCT_MARKET_EMPTY_G	"market-empty"
#define LCT_MARKET_LOW_G        "market-low"
#define LCT_MARKET_MED_G        "market-med"
#define LCT_MARKET_FULL_G       "market-full"
#define LCT_RECYCLE_G		"recycle-centre"
#define LCT_TRACK_LR_G		"tracklr"
#define LCT_TRACK_LU_G          "tracklu"
#define LCT_TRACK_LD_G          "trackld"
#define LCT_TRACK_UD_G          "trackud"
#define LCT_TRACK_UR_G          "trackur"
#define LCT_TRACK_DR_G          "trackdr"
#define LCT_TRACK_LUR_G         "tracklur"
#define LCT_TRACK_LDR_G         "trackldr"
#define LCT_TRACK_LUD_G         "tracklud"
#define LCT_TRACK_UDR_G         "trackudr"
#define LCT_TRACK_LUDR_G        "trackludr"
#define LCT_PARKLAND_PLANE_G	"parkland-plane"
#define LCT_PARKLAND_LAKE_G	"parkland-lake"
#define LCT_MONUMENT_0_G	"monument0"
#define LCT_MONUMENT_1_G        "monument1"
#define LCT_MONUMENT_2_G        "monument2"
#define LCT_MONUMENT_3_G        "monument3"
#define LCT_MONUMENT_4_G        "monument4"
#define LCT_MONUMENT_5_G        "monument5"
#define LCT_COALMINE_EMPTY_G	"coalmine-empty"
#define LCT_COALMINE_LOW_G	"coalmine-low"
#define LCT_COALMINE_MED_G	"coalmine-med"
#define LCT_COALMINE_FULL_G	"coalmine-full"
#define LCT_RAIL_LR_G          "raillr"
#define LCT_RAIL_LU_G          "raillu"
#define LCT_RAIL_LD_G          "railld"
#define LCT_RAIL_UD_G          "railud"
#define LCT_RAIL_UR_G          "railur"
#define LCT_RAIL_DR_G          "raildr"
#define LCT_RAIL_LUR_G         "raillur"
#define LCT_RAIL_LDR_G         "railldr"
#define LCT_RAIL_LUD_G         "raillud"
#define LCT_RAIL_UDR_G         "railudr"
#define LCT_RAIL_LUDR_G        "railludr"
#define LCT_FIRE_1_G           "fire1"
#define LCT_FIRE_2_G           "fire2"
#define LCT_FIRE_3_G           "fire3"
#define LCT_FIRE_4_G           "fire4"
#define LCT_FIRE_5_G           "fire5"
#define LCT_FIRE_DONE1_G       "firedone1"
#define LCT_FIRE_DONE2_G       "firedone2"
#define LCT_FIRE_DONE3_G       "firedone3"
#define LCT_FIRE_DONE4_G       "firedone4"
#define LCT_ROAD_LR_G          "roadlr"
#define LCT_ROAD_LU_G          "roadlu"
#define LCT_ROAD_LD_G          "roadld"
#define LCT_ROAD_UD_G          "roadud"
#define LCT_ROAD_UR_G          "roadur"
#define LCT_ROAD_DR_G          "roaddr"
#define LCT_ROAD_LUR_G         "roadlur"
#define LCT_ROAD_LDR_G         "roadldr"
#define LCT_ROAD_LUD_G         "roadlud"
#define LCT_ROAD_UDR_G         "roadudr"
#define LCT_ROAD_LUDR_G        "roadludr"
#define LCT_OREMINE_5_G         "oremine5"
#define LCT_OREMINE_6_G         "oremine6"
#define LCT_OREMINE_7_G         "oremine7"
#define LCT_OREMINE_8_G         "oremine8"
#define LCT_OREMINE_1_G		"oremine1"
#define LCT_OREMINE_2_G		"oremine2"
#define LCT_OREMINE_3_G		"oremine3"
#define LCT_OREMINE_4_G		"oremine4"
#define LCT_HEALTH_G		"health"
#define LCT_SCHOOL_G		"school0"
#define LCT_EX_PORT_G		"ex_port"
#define LCT_MILL_0_G            "mill0"
#define LCT_MILL_1_G            "mill1"
#define LCT_MILL_2_G            "mill2"
#define LCT_MILL_3_G            "mill3"
#define LCT_MILL_4_G            "mill4"
#define LCT_MILL_5_G            "mill5"
#define LCT_MILL_6_G            "mill6"
#define LCT_ROCKET_1_G          "rocket1"
#define LCT_ROCKET_2_G		"rocket2"
#define LCT_ROCKET_3_G		"rocket3"
#define LCT_ROCKET_4_G		"rocket4"
#define LCT_ROCKET_5_G          "rocket5"
#define LCT_ROCKET_6_G          "rocket6"
#define LCT_ROCKET_7_G		"rocket7"
#define LCT_ROCKET_FLOWN_G	"rocketflown"
#define LCT_WINDMILL_1_G_G      "windmill1g"
#define LCT_WINDMILL_2_G_G      "windmill2g"
#define LCT_WINDMILL_3_G_G      "windmill3g"
#define LCT_WINDMILL_1_RG_G     "windmill1rg"
#define LCT_WINDMILL_2_RG_G     "windmill2rg"
#define LCT_WINDMILL_3_RG_G     "windmill3rg"
#define LCT_WINDMILL_1_R_G      "windmill1r"
#define LCT_WINDMILL_2_R_G      "windmill2r"
#define LCT_WINDMILL_3_R_G      "windmill3r"
#define LCT_WINDMILL_1_W_G      "windmill1w"
#define LCT_WINDMILL_2_W_G      "windmill2w"
#define LCT_WINDMILL_3_W_G      "windmill3w"
#define LCT_BLACKSMITH_0_G        "blacksmith0"
#define LCT_BLACKSMITH_1_G        "blacksmith1"
#define LCT_BLACKSMITH_2_G        "blacksmith2"
#define LCT_BLACKSMITH_3_G        "blacksmith3"
#define LCT_BLACKSMITH_4_G        "blacksmith4"
#define LCT_BLACKSMITH_5_G        "blacksmith5"
#define LCT_BLACKSMITH_6_G        "blacksmith6"
#define LCT_POTTERY_0_G           "pottery0"
#define LCT_POTTERY_1_G           "pottery1"
#define LCT_POTTERY_2_G           "pottery2"
#define LCT_POTTERY_3_G           "pottery3"
#define LCT_POTTERY_4_G           "pottery4"
#define LCT_POTTERY_5_G           "pottery5"
#define LCT_POTTERY_6_G           "pottery6"
#define LCT_POTTERY_7_G           "pottery7"
#define LCT_POTTERY_8_G           "pottery8"
#define LCT_POTTERY_9_G           "pottery9"
#define LCT_POTTERY_10_G          "pottery10"
#define LCT_WATER_G             "water"
#define LCT_WATER_D_G           "waterd"
#define LCT_WATER_R_G           "waterr"
#define LCT_WATER_U_G           "wateru"
#define LCT_WATER_L_G           "waterl"
#define LCT_WATER_LR_G          "waterlr"
#define LCT_WATER_UD_G          "waterud"
#define LCT_WATER_LD_G          "waterld"
#define LCT_WATER_RD_G          "waterrd"
#define LCT_WATER_LU_G          "waterlu"
#define LCT_WATER_UR_G          "waterur"
#define LCT_WATER_LUD_G         "waterlud"
#define LCT_WATER_LRD_G         "waterlrd"
#define LCT_WATER_LUR_G         "waterlur"
#define LCT_WATER_URD_G         "waterurd"
#define LCT_WATER_LURD_G        "waterlurd"
#define LCT_CRICKET_1_G         "cricket1"
#define LCT_CRICKET_2_G         "cricket2"
#define LCT_CRICKET_3_G         "cricket3"
#define LCT_CRICKET_4_G         "cricket4"
#define LCT_CRICKET_5_G         "cricket5"
#define LCT_CRICKET_6_G         "cricket6"
#define LCT_CRICKET_7_G         "cricket7"
#define LCT_FIRESTATION_1_G       "firestation1"
#define LCT_FIRESTATION_2_G       "firestation2"
#define LCT_FIRESTATION_3_G       "firestation3"
#define LCT_FIRESTATION_4_G       "firestation4"
#define LCT_FIRESTATION_5_G       "firestation5"
#define LCT_FIRESTATION_6_G       "firestation6"
#define LCT_FIRESTATION_7_G       "firestation7"
#define LCT_FIRESTATION_8_G       "firestation8"
#define LCT_FIRESTATION_9_G       "firestation9"
#define LCT_FIRESTATION_10_G      "firestation10"
#define LCT_TIP_0_G             "tip0"
#define LCT_TIP_1_G             "tip1"
#define LCT_TIP_2_G             "tip2"
#define LCT_TIP_3_G             "tip3"
#define LCT_TIP_4_G             "tip4"
#define LCT_TIP_5_G             "tip5"
#define LCT_TIP_6_G             "tip6"
#define LCT_TIP_7_G             "tip7"
#define LCT_TIP_8_G             "tip8"
#define LCT_COMMUNE_1_G         "commune1"
#define LCT_COMMUNE_2_G         "commune2"
#define LCT_COMMUNE_3_G         "commune3"
#define LCT_COMMUNE_4_G         "commune4"
#define LCT_COMMUNE_5_G         "commune5"
#define LCT_COMMUNE_6_G         "commune6"
#define LCT_COMMUNE_7_G         "commune7"
#define LCT_COMMUNE_8_G         "commune8"
#define LCT_COMMUNE_9_G         "commune9"
#define LCT_COMMUNE_10_G        "commune10"
#define LCT_COMMUNE_11_G        "commune11"
#define LCT_COMMUNE_12_G        "commune12"
#define LCT_COMMUNE_13_G        "commune13"
#define LCT_COMMUNE_14_G        "commune14"
#define LCT_INDUSTRY_H_C_G      "industryhc"
#define LCT_INDUSTRY_H_L1_G      "industryhl1"
#define LCT_INDUSTRY_H_L2_G      "industryhl2"
#define LCT_INDUSTRY_H_L3_G      "industryhl3"
#define LCT_INDUSTRY_H_L4_G      "industryhl4"
#define LCT_INDUSTRY_H_L5_G      "industryhl5"
#define LCT_INDUSTRY_H_L6_G      "industryhl6"
#define LCT_INDUSTRY_H_L7_G      "industryhl7"
#define LCT_INDUSTRY_H_L8_G      "industryhl8"
#define LCT_INDUSTRY_H_M1_G      "industryhm1"
#define LCT_INDUSTRY_H_M2_G      "industryhm2"
#define LCT_INDUSTRY_H_M3_G      "industryhm3"
#define LCT_INDUSTRY_H_M4_G      "industryhm4"
#define LCT_INDUSTRY_H_M5_G      "industryhm5"
#define LCT_INDUSTRY_H_M6_G      "industryhm6"
#define LCT_INDUSTRY_H_M7_G      "industryhm7"
#define LCT_INDUSTRY_H_M8_G      "industryhm8"
#define LCT_INDUSTRY_H_H1_G      "industryhh1"
#define LCT_INDUSTRY_H_H2_G      "industryhh2"
#define LCT_INDUSTRY_H_H3_G      "industryhh3"
#define LCT_INDUSTRY_H_H4_G      "industryhh4"
#define LCT_INDUSTRY_H_H5_G      "industryhh5"
#define LCT_INDUSTRY_H_H6_G      "industryhh6"
#define LCT_INDUSTRY_H_H7_G      "industryhh7"
#define LCT_INDUSTRY_H_H8_G      "industryhh8"
#define LCT_INDUSTRY_L_C_G       "industrylq1"
#define LCT_INDUSTRY_L_Q1_G      "industrylq1"
#define LCT_INDUSTRY_L_Q2_G      "industrylq2"
#define LCT_INDUSTRY_L_Q3_G      "industrylq3"
#define LCT_INDUSTRY_L_Q4_G      "industrylq4"
#define LCT_INDUSTRY_L_L1_G      "industryll1"
#define LCT_INDUSTRY_L_L2_G      "industryll2"
#define LCT_INDUSTRY_L_L3_G      "industryll3"
#define LCT_INDUSTRY_L_L4_G      "industryll4"
#define LCT_INDUSTRY_L_M1_G      "industrylm1"
#define LCT_INDUSTRY_L_M2_G      "industrylm2"
#define LCT_INDUSTRY_L_M3_G      "industrylm3"
#define LCT_INDUSTRY_L_M4_G      "industrylm4"
#define LCT_INDUSTRY_L_H1_G      "industrylh1"
#define LCT_INDUSTRY_L_H2_G      "industrylh2"
#define LCT_INDUSTRY_L_H3_G      "industrylh3"
#define LCT_INDUSTRY_L_H4_G      "industrylh4"
#define LCT_FARM_O0_G            "farm0"
#define LCT_FARM_O1_G            "farm1"
#define LCT_FARM_O2_G            "farm2"
#define LCT_FARM_O3_G            "farm3"
#define LCT_FARM_O4_G            "farm4"
#define LCT_FARM_O5_G            "farm5"
#define LCT_FARM_O6_G            "farm6"
#define LCT_FARM_O7_G            "farm7"
#define LCT_FARM_O8_G            "farm8"
#define LCT_FARM_O9_G            "farm9"
#define LCT_FARM_O10_G           "farm10"
#define LCT_FARM_O11_G           "farm11"
#define LCT_FARM_O12_G           "farm12"
#define LCT_FARM_O13_G           "farm13"
#define LCT_FARM_O14_G           "farm14"
#define LCT_FARM_O15_G           "farm15"
#define LCT_FARM_O16_G           "farm16"

/* Private functions */
static char* 
load_png_graphic (short type, short group, char* id,
		  FILE* txt_fp,png_bytep *row_pointers, 
		  png_uint_32 width, png_uint_32 height);

/* Let errors and warnings be handled by setjmp/longjmp */
void* user_error_ptr = 0;

void user_error_fn(png_structp png_ptr, png_const_charp error_msg)
{
}

void user_warning_fn(png_structp png_ptr, png_const_charp warning_msg)
{
}

int
load_png_graphics (char *txt_filename, char *png_filename)
{
    png_uint_32 row;
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type;
    FILE *fp, *txt_fp;
    png_bytep *row_pointers;

    if ((fp = fopen(png_filename, "rb")) == NULL)
	return (ERROR);

    if ((txt_fp = fopen(txt_filename, "r")) == NULL)
	return (ERROR);

    /* Create and initialize the png_struct with the desired error handler
    * functions.  If you want to use the default stderr and longjump method,
    * you can supply NULL for the last three parameters.  We also supply the
    * the compiler header file version, so that we know if the application
    * was compiled with a compatible version of the library.  REQUIRED
    */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
	(png_voidp) user_error_ptr, user_error_fn, user_warning_fn);

    if (png_ptr == NULL) {
	fclose(fp);
	return (ERROR);
    }

    /* Allocate/initialize the memory for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
	fclose(fp);
#if defined (commentout)
	png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
#endif
	png_destroy_read_struct(&png_ptr, NULL, NULL);
	return (ERROR);
    }

   /* Set error handling if you are using the setjmp/longjmp method (this is
    * the normal method of doing things with libpng).  REQUIRED unless you
    * set up your own error handlers in the png_create_read_struct() earlier.
    */
    if (setjmp(png_jmpbuf(png_ptr))) {
	/* Free all of the memory associated with the png_ptr and info_ptr */
#if defined (commentout)
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
#endif
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	/* If we get here, we had a problem reading the file */
	return (ERROR);
    }

    /* Set up the input control if you are using standard C streams */
    png_init_io(png_ptr, fp);

    /* If we have already read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);

    /* OK, you're doing it the hard way, with the lower-level functions */
    /* The call to png_read_info() gives us all of the information from the
    * PNG file before the first IDAT (image data chunk).  REQUIRED
    */
    png_read_info(png_ptr, info_ptr);

#if defined (commentout)
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
	&interlace_type, int_p_NULL, int_p_NULL);
#endif
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
	&interlace_type, NULL, NULL);

    printf ("PNG Header: %d x %d, bd=%d, ct=%d\n", (int)height, (int)width,
	bit_depth, color_type);

    /* Set up the data transformations you want.  Note that these are all
     * optional.  Only call them if you want/need them.  Many of the
     * transformations only work on specific types of images, and many
     * are mutually exclusive.
     */

   /* tell libpng to strip 16 bit/color files down to 8 bits/color */
//   png_set_strip_16(png_ptr);

   /* Strip alpha bytes from the input data without combining with the
    * background (not recommended).
    */
//   png_set_strip_alpha(png_ptr);

   /* Extract multiple pixels with bit depths of 1, 2, and 4 from a single
    * byte into separate bytes (useful for paletted and grayscale images).
    */
//   png_set_packing(png_ptr);

   /* Change the order of packed pixels to least significant bit first
    * (not useful if you are using png_set_packing). */
//   png_set_packswap(png_ptr);

   /* Require color fmt w/ palette */
   if (color_type != PNG_COLOR_TYPE_PALETTE) {
	printf ("Error - png image wasn't PNG_COLOR_TYPE_PALETTE\n");
	/* Free all of the memory associated with the png_ptr and info_ptr */
#if defined (commentout)
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
#endif
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	/* If we get here, we had a problem reading the file */
	return (ERROR);
   }

   /* Require 1 byte per pixel */
   if (bit_depth != 8) {
	printf ("Error - png image wasn't bit_depth = 8\n");
	/* Free all of the memory associated with the png_ptr and info_ptr */
#if defined (commentout)
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
#endif
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	/* If we get here, we had a problem reading the file */
	return (ERROR);
   }

    /* The easiest way to read the image: */
    row_pointers = malloc (sizeof(void*)*height);
    for (row = 0; row < height; row++) {
	row_pointers[row] = png_malloc(png_ptr, 
	    png_get_rowbytes(png_ptr, info_ptr));
    }

    png_read_image(png_ptr, row_pointers);

#if defined (commentout)
    for (col = 0; col < 16; col++) {
	printf (" %02x ",row_pointers[0][col]);
    }
    printf ("\n");

    for (col = 0; col < 16; col++) {
	printf ("%3d ",row_pointers[0][col]);
    }
    printf ("\n");
#endif

    /* read rest of file, and get additional chunks in info_ptr - REQUIRED */
    png_read_end(png_ptr, info_ptr);

    /* close the png file */
    fclose(fp);

    /* get the icons out of the png */
#ifdef LG
#undef LG
#endif
#define LG(typ,grp,id) load_png_graphic(typ,grp,id,txt_fp,row_pointers,height,width)

    LG(CST_GREEN,GROUP_BARE,LCT_GREEN_G);

    LG(CST_FIRE_1,GROUP_FIRE,LCT_FIRE_1_G);
    LG(CST_FIRE_2,GROUP_FIRE,LCT_FIRE_2_G);
    LG(CST_FIRE_3,GROUP_FIRE,LCT_FIRE_3_G);
    LG(CST_FIRE_4,GROUP_FIRE,LCT_FIRE_4_G);
    LG(CST_FIRE_5,GROUP_FIRE,LCT_FIRE_5_G);

    LG(CST_FIRE_DONE1,GROUP_FIRE,LCT_FIRE_DONE1_G);
    LG(CST_FIRE_DONE2,GROUP_FIRE,LCT_FIRE_DONE2_G);
    LG(CST_FIRE_DONE3,GROUP_FIRE,LCT_FIRE_DONE3_G);
    LG(CST_FIRE_DONE4,GROUP_FIRE,LCT_FIRE_DONE4_G);

    LG(CST_BURNT,GROUP_BURNT,LCT_BURNT_G);

    LG(CST_PARKLAND_PLANE,GROUP_PARKLAND,LCT_PARKLAND_PLANE_G);
    LG(CST_PARKLAND_LAKE,GROUP_PARKLAND,LCT_PARKLAND_LAKE_G);

    LG(CST_POWERL_H_L,GROUP_POWER_LINE,LCT_POWERL_H_L_G);
    LG(CST_POWERL_V_L,GROUP_POWER_LINE,LCT_POWERL_V_L_G);
    LG(CST_POWERL_LD_L,GROUP_POWER_LINE,LCT_POWERL_LD_L_G);
    LG(CST_POWERL_RD_L,GROUP_POWER_LINE,LCT_POWERL_RD_L_G);
    LG(CST_POWERL_LU_L,GROUP_POWER_LINE,LCT_POWERL_LU_L_G);
    LG(CST_POWERL_RU_L,GROUP_POWER_LINE,LCT_POWERL_RU_L_G);
    LG(CST_POWERL_LDU_L,GROUP_POWER_LINE,LCT_POWERL_LDU_L_G);
    LG(CST_POWERL_LDR_L,GROUP_POWER_LINE,LCT_POWERL_LDR_L_G);
    LG(CST_POWERL_LUR_L,GROUP_POWER_LINE,LCT_POWERL_LUR_L_G);
    LG(CST_POWERL_UDR_L,GROUP_POWER_LINE,LCT_POWERL_UDR_L_G);
    LG(CST_POWERL_LUDR_L,GROUP_POWER_LINE,LCT_POWERL_LUDR_L_G);
    LG(CST_POWERL_H_D,GROUP_POWER_LINE,LCT_POWERL_H_D_G);
    LG(CST_POWERL_V_D,GROUP_POWER_LINE,LCT_POWERL_V_D_G);
    LG(CST_POWERL_LD_D,GROUP_POWER_LINE,LCT_POWERL_LD_D_G);
    LG(CST_POWERL_RD_D,GROUP_POWER_LINE,LCT_POWERL_RD_D_G);
    LG(CST_POWERL_LU_D,GROUP_POWER_LINE,LCT_POWERL_LU_D_G);
    LG(CST_POWERL_RU_D,GROUP_POWER_LINE,LCT_POWERL_RU_D_G);
    LG(CST_POWERL_LDU_D,GROUP_POWER_LINE,LCT_POWERL_LDU_D_G);
    LG(CST_POWERL_LDR_D,GROUP_POWER_LINE,LCT_POWERL_LDR_D_G);
    LG(CST_POWERL_LUR_D,GROUP_POWER_LINE,LCT_POWERL_LUR_D_G);
    LG(CST_POWERL_UDR_D,GROUP_POWER_LINE,LCT_POWERL_UDR_D_G);
    LG(CST_POWERL_LUDR_D,GROUP_POWER_LINE,LCT_POWERL_LUDR_D_G);

    LG(CST_RAIL_LR,GROUP_RAIL,LCT_RAIL_LR_G);
    LG(CST_RAIL_LU,GROUP_RAIL,LCT_RAIL_LU_G);
    LG(CST_RAIL_LD,GROUP_RAIL,LCT_RAIL_LD_G);
    LG(CST_RAIL_UD,GROUP_RAIL,LCT_RAIL_UD_G);
    LG(CST_RAIL_UR,GROUP_RAIL,LCT_RAIL_UR_G);
    LG(CST_RAIL_DR,GROUP_RAIL,LCT_RAIL_DR_G);
    LG(CST_RAIL_LUR,GROUP_RAIL,LCT_RAIL_LUR_G);
    LG(CST_RAIL_LDR,GROUP_RAIL,LCT_RAIL_LDR_G);
    LG(CST_RAIL_LUD,GROUP_RAIL,LCT_RAIL_LUD_G);
    LG(CST_RAIL_UDR,GROUP_RAIL,LCT_RAIL_UDR_G);
    LG(CST_RAIL_LUDR,GROUP_RAIL,LCT_RAIL_LUDR_G);

    LG(CST_ROAD_LR,GROUP_ROAD,LCT_ROAD_LR_G);
    LG(CST_ROAD_LU,GROUP_ROAD,LCT_ROAD_LU_G);
    LG(CST_ROAD_LD,GROUP_ROAD,LCT_ROAD_LD_G);
    LG(CST_ROAD_UD,GROUP_ROAD,LCT_ROAD_UD_G);
    LG(CST_ROAD_UR,GROUP_ROAD,LCT_ROAD_UR_G);
    LG(CST_ROAD_DR,GROUP_ROAD,LCT_ROAD_DR_G);
    LG(CST_ROAD_LUR,GROUP_ROAD,LCT_ROAD_LUR_G);
    LG(CST_ROAD_LDR,GROUP_ROAD,LCT_ROAD_LDR_G);
    LG(CST_ROAD_LUD,GROUP_ROAD,LCT_ROAD_LUD_G);
    LG(CST_ROAD_UDR,GROUP_ROAD,LCT_ROAD_UDR_G);
    LG(CST_ROAD_LUDR,GROUP_ROAD,LCT_ROAD_LUDR_G);

    LG(CST_TRACK_LR,GROUP_TRACK,LCT_TRACK_LR_G);
    LG(CST_TRACK_LU,GROUP_TRACK,LCT_TRACK_LU_G);
    LG(CST_TRACK_LD,GROUP_TRACK,LCT_TRACK_LD_G);
    LG(CST_TRACK_UD,GROUP_TRACK,LCT_TRACK_UD_G);
    LG(CST_TRACK_UR,GROUP_TRACK,LCT_TRACK_UR_G);
    LG(CST_TRACK_DR,GROUP_TRACK,LCT_TRACK_DR_G);
    LG(CST_TRACK_LUR,GROUP_TRACK,LCT_TRACK_LUR_G);
    LG(CST_TRACK_LDR,GROUP_TRACK,LCT_TRACK_LDR_G);
    LG(CST_TRACK_LUD,GROUP_TRACK,LCT_TRACK_LUD_G);
    LG(CST_TRACK_UDR,GROUP_TRACK,LCT_TRACK_UDR_G);
    LG(CST_TRACK_LUDR,GROUP_TRACK,LCT_TRACK_LUDR_G);

    LG(CST_WATER,GROUP_WATER,LCT_WATER_G);
    LG(CST_WATER_D,GROUP_WATER,LCT_WATER_D_G);
    LG(CST_WATER_R,GROUP_WATER,LCT_WATER_R_G);
    LG(CST_WATER_U,GROUP_WATER,LCT_WATER_U_G);
    LG(CST_WATER_L,GROUP_WATER,LCT_WATER_L_G);
    LG(CST_WATER_LR,GROUP_WATER,LCT_WATER_LR_G);
    LG(CST_WATER_UD,GROUP_WATER,LCT_WATER_UD_G);
    LG(CST_WATER_LD,GROUP_WATER,LCT_WATER_LD_G);
    LG(CST_WATER_RD,GROUP_WATER,LCT_WATER_RD_G);
    LG(CST_WATER_LU,GROUP_WATER,LCT_WATER_LU_G);
    LG(CST_WATER_UR,GROUP_WATER,LCT_WATER_UR_G);
    LG(CST_WATER_LUD,GROUP_WATER,LCT_WATER_LUD_G);
    LG(CST_WATER_LRD,GROUP_WATER,LCT_WATER_LRD_G);
    LG(CST_WATER_LUR,GROUP_WATER,LCT_WATER_LUR_G);
    LG(CST_WATER_URD,GROUP_WATER,LCT_WATER_URD_G);
    LG(CST_WATER_LURD,GROUP_WATER,LCT_WATER_LURD_G);

    LG(CST_BLACKSMITH_0,GROUP_BLACKSMITH,LCT_BLACKSMITH_0_G);
    LG(CST_BLACKSMITH_1,GROUP_BLACKSMITH,LCT_BLACKSMITH_1_G);
    LG(CST_BLACKSMITH_2,GROUP_BLACKSMITH,LCT_BLACKSMITH_2_G);
    LG(CST_BLACKSMITH_3,GROUP_BLACKSMITH,LCT_BLACKSMITH_3_G);
    LG(CST_BLACKSMITH_4,GROUP_BLACKSMITH,LCT_BLACKSMITH_4_G);
    LG(CST_BLACKSMITH_5,GROUP_BLACKSMITH,LCT_BLACKSMITH_5_G);
    LG(CST_BLACKSMITH_6,GROUP_BLACKSMITH,LCT_BLACKSMITH_6_G);

    LG(CST_CRICKET_1,GROUP_CRICKET,LCT_CRICKET_1_G);
    LG(CST_CRICKET_2,GROUP_CRICKET,LCT_CRICKET_2_G);
    LG(CST_CRICKET_3,GROUP_CRICKET,LCT_CRICKET_3_G);
    LG(CST_CRICKET_4,GROUP_CRICKET,LCT_CRICKET_4_G);
    LG(CST_CRICKET_5,GROUP_CRICKET,LCT_CRICKET_5_G);
    LG(CST_CRICKET_6,GROUP_CRICKET,LCT_CRICKET_6_G);
    LG(CST_CRICKET_7,GROUP_CRICKET,LCT_CRICKET_7_G);

    LG(CST_FIRESTATION_1,GROUP_FIRESTATION,LCT_FIRESTATION_1_G);
    LG(CST_FIRESTATION_2,GROUP_FIRESTATION,LCT_FIRESTATION_2_G);
    LG(CST_FIRESTATION_3,GROUP_FIRESTATION,LCT_FIRESTATION_3_G);
    LG(CST_FIRESTATION_4,GROUP_FIRESTATION,LCT_FIRESTATION_4_G);
    LG(CST_FIRESTATION_5,GROUP_FIRESTATION,LCT_FIRESTATION_5_G);
    LG(CST_FIRESTATION_6,GROUP_FIRESTATION,LCT_FIRESTATION_6_G);
    LG(CST_FIRESTATION_7,GROUP_FIRESTATION,LCT_FIRESTATION_7_G);
    LG(CST_FIRESTATION_8,GROUP_FIRESTATION,LCT_FIRESTATION_8_G);
    LG(CST_FIRESTATION_9,GROUP_FIRESTATION,LCT_FIRESTATION_9_G);
    LG(CST_FIRESTATION_10,GROUP_FIRESTATION,LCT_FIRESTATION_10_G);

    LG(CST_HEALTH,GROUP_HEALTH,LCT_HEALTH_G);

    LG(CST_MARKET_EMPTY,GROUP_MARKET,LCT_MARKET_EMPTY_G);
    LG(CST_MARKET_LOW,GROUP_MARKET,LCT_MARKET_LOW_G);
    LG(CST_MARKET_MED,GROUP_MARKET,LCT_MARKET_MED_G);
    LG(CST_MARKET_FULL,GROUP_MARKET,LCT_MARKET_FULL_G);

    LG(CST_MILL_0,GROUP_MILL,LCT_MILL_0_G);
    LG(CST_MILL_1,GROUP_MILL,LCT_MILL_1_G);
    LG(CST_MILL_2,GROUP_MILL,LCT_MILL_2_G);
    LG(CST_MILL_3,GROUP_MILL,LCT_MILL_3_G);
    LG(CST_MILL_4,GROUP_MILL,LCT_MILL_4_G);
    LG(CST_MILL_5,GROUP_MILL,LCT_MILL_5_G);
    LG(CST_MILL_6,GROUP_MILL,LCT_MILL_6_G);

    LG(CST_MONUMENT_0,GROUP_MONUMENT,LCT_MONUMENT_0_G);
    LG(CST_MONUMENT_1,GROUP_MONUMENT,LCT_MONUMENT_1_G);
    LG(CST_MONUMENT_2,GROUP_MONUMENT,LCT_MONUMENT_2_G);
    LG(CST_MONUMENT_3,GROUP_MONUMENT,LCT_MONUMENT_3_G);
    LG(CST_MONUMENT_4,GROUP_MONUMENT,LCT_MONUMENT_4_G);
    LG(CST_MONUMENT_5,GROUP_MONUMENT,LCT_MONUMENT_5_G);

    LG(CST_POTTERY_0,GROUP_POTTERY,LCT_POTTERY_0_G);
    LG(CST_POTTERY_1,GROUP_POTTERY,LCT_POTTERY_1_G);
    LG(CST_POTTERY_2,GROUP_POTTERY,LCT_POTTERY_2_G);
    LG(CST_POTTERY_3,GROUP_POTTERY,LCT_POTTERY_3_G);
    LG(CST_POTTERY_4,GROUP_POTTERY,LCT_POTTERY_4_G);
    LG(CST_POTTERY_5,GROUP_POTTERY,LCT_POTTERY_5_G);
    LG(CST_POTTERY_6,GROUP_POTTERY,LCT_POTTERY_6_G);
    LG(CST_POTTERY_7,GROUP_POTTERY,LCT_POTTERY_7_G);
    LG(CST_POTTERY_8,GROUP_POTTERY,LCT_POTTERY_8_G);
    LG(CST_POTTERY_9,GROUP_POTTERY,LCT_POTTERY_9_G);
    LG(CST_POTTERY_10,GROUP_POTTERY,LCT_POTTERY_10_G);

    LG(CST_RECYCLE,GROUP_RECYCLE,LCT_RECYCLE_G);

    LG(CST_SCHOOL,GROUP_SCHOOL,LCT_SCHOOL_G);

    LG(CST_SHANTY,GROUP_SHANTY,LCT_SHANTY_G);

    LG(CST_SUBSTATION_R,GROUP_SUBSTATION,LCT_SUBSTATION_R_G);
    LG(CST_SUBSTATION_G,GROUP_SUBSTATION,LCT_SUBSTATION_G_G);
    LG(CST_SUBSTATION_RG,GROUP_SUBSTATION,LCT_SUBSTATION_RG_G);

    LG(CST_WINDMILL_1_G,GROUP_WINDMILL,LCT_WINDMILL_1_G_G);
    LG(CST_WINDMILL_2_G,GROUP_WINDMILL,LCT_WINDMILL_2_G_G);
    LG(CST_WINDMILL_3_G,GROUP_WINDMILL,LCT_WINDMILL_3_G_G);
    LG(CST_WINDMILL_1_RG,GROUP_WINDMILL,LCT_WINDMILL_1_RG_G);
    LG(CST_WINDMILL_2_RG,GROUP_WINDMILL,LCT_WINDMILL_2_RG_G);
    LG(CST_WINDMILL_3_RG,GROUP_WINDMILL,LCT_WINDMILL_3_RG_G);
    LG(CST_WINDMILL_1_R,GROUP_WINDMILL,LCT_WINDMILL_1_R_G);
    LG(CST_WINDMILL_2_R,GROUP_WINDMILL,LCT_WINDMILL_2_R_G);
    LG(CST_WINDMILL_3_R,GROUP_WINDMILL,LCT_WINDMILL_3_R_G);
    LG(CST_WINDMILL_1_W,GROUP_WINDMILL,LCT_WINDMILL_1_W_G);
    LG(CST_WINDMILL_2_W,GROUP_WINDMILL,LCT_WINDMILL_2_W_G);
    LG(CST_WINDMILL_3_W,GROUP_WINDMILL,LCT_WINDMILL_3_W_G);

    LG(CST_INDUSTRY_L_C,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_C_G);
    LG(CST_INDUSTRY_L_Q1,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_Q1_G);
    LG(CST_INDUSTRY_L_Q2,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_Q2_G);
    LG(CST_INDUSTRY_L_Q3,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_Q3_G);
    LG(CST_INDUSTRY_L_Q4,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_Q4_G);
    LG(CST_INDUSTRY_L_L1,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_L1_G);
    LG(CST_INDUSTRY_L_L2,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_L2_G);
    LG(CST_INDUSTRY_L_L3,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_L3_G);
    LG(CST_INDUSTRY_L_L4,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_L4_G);
    LG(CST_INDUSTRY_L_M1,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_M1_G);
    LG(CST_INDUSTRY_L_M2,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_M2_G);
    LG(CST_INDUSTRY_L_M3,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_M3_G);
    LG(CST_INDUSTRY_L_M4,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_M4_G);
    LG(CST_INDUSTRY_L_H1,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_H1_G);
    LG(CST_INDUSTRY_L_H2,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_H2_G);
    LG(CST_INDUSTRY_L_H3,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_H3_G);
    LG(CST_INDUSTRY_L_H4,GROUP_INDUSTRY_L,LCT_INDUSTRY_L_H4_G);

    LG(CST_RESIDENCE_LL,GROUP_RESIDENCE_LL,LCT_RESIDENCE_LL_G);
    LG(CST_RESIDENCE_ML,GROUP_RESIDENCE_ML,LCT_RESIDENCE_ML_G);
    LG(CST_RESIDENCE_HL,GROUP_RESIDENCE_HL,LCT_RESIDENCE_HL_G);
    LG(CST_RESIDENCE_LH,GROUP_RESIDENCE_LH,LCT_RESIDENCE_LH_G);
    LG(CST_RESIDENCE_MH,GROUP_RESIDENCE_MH,LCT_RESIDENCE_MH_G);
    LG(CST_RESIDENCE_HH,GROUP_RESIDENCE_HH,LCT_RESIDENCE_HH_G);

    LG(CST_UNIVERSITY,GROUP_UNIVERSITY,LCT_UNIVERSITY_G);

    LG(CST_COALMINE_EMPTY,GROUP_COALMINE,LCT_COALMINE_EMPTY_G);
    LG(CST_COALMINE_LOW,GROUP_COALMINE,LCT_COALMINE_LOW_G);
    LG(CST_COALMINE_MED,GROUP_COALMINE,LCT_COALMINE_MED_G);
    LG(CST_COALMINE_FULL,GROUP_COALMINE,LCT_COALMINE_FULL_G);

    LG(CST_COMMUNE_1,GROUP_COMMUNE,LCT_COMMUNE_1_G);
    LG(CST_COMMUNE_2,GROUP_COMMUNE,LCT_COMMUNE_2_G);
    LG(CST_COMMUNE_3,GROUP_COMMUNE,LCT_COMMUNE_3_G);
    LG(CST_COMMUNE_4,GROUP_COMMUNE,LCT_COMMUNE_4_G);
    LG(CST_COMMUNE_5,GROUP_COMMUNE,LCT_COMMUNE_5_G);
    LG(CST_COMMUNE_6,GROUP_COMMUNE,LCT_COMMUNE_6_G);
    LG(CST_COMMUNE_7,GROUP_COMMUNE,LCT_COMMUNE_7_G);
    LG(CST_COMMUNE_8,GROUP_COMMUNE,LCT_COMMUNE_8_G);
    LG(CST_COMMUNE_9,GROUP_COMMUNE,LCT_COMMUNE_9_G);
    LG(CST_COMMUNE_10,GROUP_COMMUNE,LCT_COMMUNE_10_G);
    LG(CST_COMMUNE_11,GROUP_COMMUNE,LCT_COMMUNE_11_G);
    LG(CST_COMMUNE_12,GROUP_COMMUNE,LCT_COMMUNE_12_G);
    LG(CST_COMMUNE_13,GROUP_COMMUNE,LCT_COMMUNE_13_G);
    LG(CST_COMMUNE_14,GROUP_COMMUNE,LCT_COMMUNE_14_G);

    LG(CST_EX_PORT,GROUP_PORT,LCT_EX_PORT_G);

    LG(CST_FARM_O0,GROUP_ORGANIC_FARM,LCT_FARM_O0_G);
    LG(CST_FARM_O1,GROUP_ORGANIC_FARM,LCT_FARM_O1_G);
    LG(CST_FARM_O2,GROUP_ORGANIC_FARM,LCT_FARM_O2_G);
    LG(CST_FARM_O3,GROUP_ORGANIC_FARM,LCT_FARM_O3_G);
    LG(CST_FARM_O4,GROUP_ORGANIC_FARM,LCT_FARM_O4_G);
    LG(CST_FARM_O5,GROUP_ORGANIC_FARM,LCT_FARM_O5_G);
    LG(CST_FARM_O6,GROUP_ORGANIC_FARM,LCT_FARM_O6_G);
    LG(CST_FARM_O7,GROUP_ORGANIC_FARM,LCT_FARM_O7_G);
    LG(CST_FARM_O8,GROUP_ORGANIC_FARM,LCT_FARM_O8_G);
    LG(CST_FARM_O9,GROUP_ORGANIC_FARM,LCT_FARM_O9_G);
    LG(CST_FARM_O10,GROUP_ORGANIC_FARM,LCT_FARM_O10_G);
    LG(CST_FARM_O11,GROUP_ORGANIC_FARM,LCT_FARM_O11_G);
    LG(CST_FARM_O12,GROUP_ORGANIC_FARM,LCT_FARM_O12_G);
    LG(CST_FARM_O13,GROUP_ORGANIC_FARM,LCT_FARM_O13_G);
    LG(CST_FARM_O14,GROUP_ORGANIC_FARM,LCT_FARM_O14_G);
    LG(CST_FARM_O15,GROUP_ORGANIC_FARM,LCT_FARM_O15_G);
    LG(CST_FARM_O16,GROUP_ORGANIC_FARM,LCT_FARM_O16_G);

    LG(CST_INDUSTRY_H_C,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_C_G);
    LG(CST_INDUSTRY_H_L1,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_L1_G);
    LG(CST_INDUSTRY_H_L2,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_L2_G);
    LG(CST_INDUSTRY_H_L3,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_L3_G);
    LG(CST_INDUSTRY_H_L4,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_L4_G);
    LG(CST_INDUSTRY_H_L5,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_L5_G);
    LG(CST_INDUSTRY_H_L6,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_L6_G);
    LG(CST_INDUSTRY_H_L7,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_L7_G);
    LG(CST_INDUSTRY_H_L8,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_L8_G);
    LG(CST_INDUSTRY_H_M1,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_M1_G);
    LG(CST_INDUSTRY_H_M2,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_M2_G);
    LG(CST_INDUSTRY_H_M3,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_M3_G);
    LG(CST_INDUSTRY_H_M4,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_M4_G);
    LG(CST_INDUSTRY_H_M5,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_M5_G);
    LG(CST_INDUSTRY_H_M6,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_M6_G);
    LG(CST_INDUSTRY_H_M7,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_M7_G);
    LG(CST_INDUSTRY_H_M8,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_M8_G);
    LG(CST_INDUSTRY_H_H1,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_H1_G);
    LG(CST_INDUSTRY_H_H2,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_H2_G);
    LG(CST_INDUSTRY_H_H3,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_H3_G);
    LG(CST_INDUSTRY_H_H4,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_H4_G);
    LG(CST_INDUSTRY_H_H5,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_H5_G);
    LG(CST_INDUSTRY_H_H6,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_H6_G);
    LG(CST_INDUSTRY_H_H7,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_H7_G);
    LG(CST_INDUSTRY_H_H8,GROUP_INDUSTRY_H,LCT_INDUSTRY_H_H8_G);

    LG(CST_OREMINE_1,GROUP_OREMINE,LCT_OREMINE_1_G);
    LG(CST_OREMINE_2,GROUP_OREMINE,LCT_OREMINE_2_G);
    LG(CST_OREMINE_3,GROUP_OREMINE,LCT_OREMINE_3_G);
    LG(CST_OREMINE_4,GROUP_OREMINE,LCT_OREMINE_4_G);
    LG(CST_OREMINE_5,GROUP_OREMINE,LCT_OREMINE_5_G);
    LG(CST_OREMINE_6,GROUP_OREMINE,LCT_OREMINE_6_G);
    LG(CST_OREMINE_7,GROUP_OREMINE,LCT_OREMINE_7_G);
    LG(CST_OREMINE_8,GROUP_OREMINE,LCT_OREMINE_8_G);

    LG(CST_POWERS_COAL_EMPTY,GROUP_COAL_POWER,LCT_POWERS_COAL_EMPTY_G);
    LG(CST_POWERS_COAL_LOW,GROUP_COAL_POWER,LCT_POWERS_COAL_LOW_G);
    LG(CST_POWERS_COAL_MED,GROUP_COAL_POWER,LCT_POWERS_COAL_MED_G);
    LG(CST_POWERS_COAL_FULL,GROUP_COAL_POWER,LCT_POWERS_COAL_FULL_G);

    LG(CST_POWERS_SOLAR,GROUP_SOLAR_POWER,LCT_POWERS_SOLAR_G);

    LG(CST_ROCKET_1,GROUP_ROCKET,LCT_ROCKET_1_G);
    LG(CST_ROCKET_2,GROUP_ROCKET,LCT_ROCKET_2_G);
    LG(CST_ROCKET_3,GROUP_ROCKET,LCT_ROCKET_3_G);
    LG(CST_ROCKET_4,GROUP_ROCKET,LCT_ROCKET_4_G);
    LG(CST_ROCKET_5,GROUP_ROCKET,LCT_ROCKET_5_G);
    LG(CST_ROCKET_6,GROUP_ROCKET,LCT_ROCKET_6_G);
    LG(CST_ROCKET_7,GROUP_ROCKET,LCT_ROCKET_7_G);
    LG(CST_ROCKET_FLOWN,GROUP_ROCKET,LCT_ROCKET_FLOWN_G);

    LG(CST_TIP_0,GROUP_TIP,LCT_TIP_0_G);
    LG(CST_TIP_1,GROUP_TIP,LCT_TIP_1_G);
    LG(CST_TIP_2,GROUP_TIP,LCT_TIP_2_G);
    LG(CST_TIP_3,GROUP_TIP,LCT_TIP_3_G);
    LG(CST_TIP_4,GROUP_TIP,LCT_TIP_4_G);
    LG(CST_TIP_5,GROUP_TIP,LCT_TIP_5_G);
    LG(CST_TIP_6,GROUP_TIP,LCT_TIP_6_G);
    LG(CST_TIP_7,GROUP_TIP,LCT_TIP_7_G);
    LG(CST_TIP_8,GROUP_TIP,LCT_TIP_8_G);

    // main_t
#undef LG

#if defined (commentout)
    /* PROCESS IMAGE HERE */
    while (!feof(txt_fp)) {
	char buf[128];
	char *fnp,*rip,*cip;
	int ri,ci;

	/* Get line from text file */
	fgets (buf,128,txt_fp);

	/* Tokenize */
	fnp = strtok(buf," \t");
	if (!fnp || *fnp == '#') continue;
	if (*fnp == '@') break;
	rip = strtok(NULL," \t");
	if (!rip) continue;
	cip = strtok(NULL," \t");
	if (!cip) continue;
	ri = atoi(rip);
	ci = atoi(cip);

	/* Copy icon */
	if (!strcmp(fnp,LCT_GREEN_G)) {
	    int r,c;
	    char* p;
            main_types[CST_GREEN].graphic=malloc(16*16);
	    p = main_types[CST_GREEN].graphic;
	    for (r=ri*16;r<ri*16+16;r++) {
	    for (c=ci*16;c<ci*16+16;c++) {
		*p++ = row_pointers[r][c];
	    } }
	}
    }
#endif

    /* Free the memory */
    for (row = 0; row < height; row++) {
	png_free(png_ptr, row_pointers[row]);
    }
    free(row_pointers);

    /* clean up after the read, and free any memory allocated - REQUIRED */
#if defined (commentout)
    png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
#endif
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    /* that's it */
    return (OK);
}

static char* 
load_png_graphic (short type, short group, char* id,
		  FILE* txt_fp,png_bytep *row_pointers, 
		  png_uint_32 width, png_uint_32 height)
{
    char buf[128];
    char *fnp,*rip,*cip;
    int ri,ci;
    char *grphc = 0;

    while (!feof(txt_fp)) {
	/* Get line from text file */
	fgets (buf,128,txt_fp);

	/* Tokenize */
	fnp = strtok(buf," \t");
	if (!fnp || *fnp == '#') continue;
	if (*fnp == '@') break;
	rip = strtok(NULL," \t");
	if (!rip) continue;
	cip = strtok(NULL," \t");
	if (!cip) continue;
	ri = atoi(rip);
	ci = atoi(cip);

	/* Copy icon */
	if (!strcmp(fnp,id)) {
	    int r,c;
	    int nr,nc;
	    char* p;
	    nr = nc = main_groups[group].size;
	    p = grphc = malloc(nr*16*nc*16);
	    if (!grphc)
	    {
	        fprintf (stderr,"Out of memory: malloc failure\n");
            exit (-1);
	    }
	    for (r=ri*16;r<(ri+nr)*16;r++) {
		for (c=ci*16;c<(ci+nc)*16;c++) {
		    *p++ = row_pointers[r][c];
		}
	    }
	    break;
	} else {
	    fprintf (stderr,"Error, wrong id string");
	    exit(-1);
	}
    }

    /* Set the main_type info */
    if (grphc) {
        main_types[type].group = group;
	main_types[type].graphic = grphc;
    } else {
	fprintf (stderr,"Error, couldn't find id string");
	exit(-1);
    }
    return 0;
}
