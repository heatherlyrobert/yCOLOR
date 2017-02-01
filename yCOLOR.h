/*----------------------------------------------------------------------------*/
/*-------                 START OF SOURCE :: yCOLOR                    -------*/
/*----------------------------------------------------------------------------*/


/*===[[ START HDOC ]]=========================================================*/
/*---[[ HEADER ]]-------------------------------------------------*

 *   niche         : graphics
 *   application   : aesthetics
 *   module        : yPALETTE
 *   purpose       : provide aesthetic color palettes and transformations
 *   base_system   : gnu/linux
 *   lang_name     : c (primarily ansi-c, but with some C89 extensions)
 *   created       : 2009-09
 *   author        : the_heatherlys
 *   dependencies  : none
 *
 */
/*---[[ PURPOSE ]]------------------------------------------------*

 *   yPALETTE is a set of shared library functions to provide consistently
 *   aesthetic color palettes to programs.  the intent is to capture
 *   consistently strong logic for these activities that can be easily used by
 *   applications as widely dispersed as GUI themes, graphing tools, opengl
 *   simulation, web page CSS, and CLI syntax highlighting.
 *
 *   after reviewing existing libraries and color scheming sites, it appears
 *   that while most tools attempt to provide all formats and all conversions,
 *   only a few actually result in beautiful outputs.  the remaining are an
 *   effort to be technically cool and all things to all people, we are focused
 *   primarily on the beauty and aesthetics only.
 *
 *   yPALETTE will standardize on...
 *      - all hues/schemes will be relative to the artists color wheel (RYB)
 *      - all transformations will be in HSV providing best control
 *      - all colors will be stored in RGB HEX format as that is the cleanest
 *      - all outputs will be in RGB as that is the technical standard
 *
 *   yPALETTE will...
 *      - colors will be converted on use to keep processing clean and fast
 *      - easily generating a wide variety of color schemes (triads, ...)
 *      - easily applying color adjustments (pastel, grey, contrast,...)
 *      - clear, quick, approximate color (as good as eyes can tell)
 *
 *   yPALETTE will also provide...
 *      - string-formatted color data in easily displayable, consumable format
 *      - simple html formatted output for rapid verification/review
 *      - debugging capability to display key information on the process
 *      - unit testing interfaces to prove computational correctness
 *
 *   yPALETTE will NOT provide...
 *      - other specialty color formats, such as, CYMK, CIE, etc.
 *      - any direct graphics or graphical display
 *      - pure accuracy (beyond reasonable eyesight)
 *
 *   there are many, stable, accepted, existing libraries and utilities have
 *   been built by better programmers and are likely superior in speed, size,
 *   capability, and reliability; BUT, i would not have learned nearly as much
 *   using them, so i follow the adage..
 *
 *   TO TRULY LEARN> do not seek to follow in the footsteps of the men of old;
 *   seek what they sought ~ Matsuo Basho
 *
 *   the underlying idea is to use this build process to learn new programming
 *   capabilities and put additional pressure on me to improve my standards,
 *   maintenance, and coding environment.  just using does not lead to
 *   understanding
 *
 */
/*---[[ INTERFACE ]]-----------------------------------------------#

 *   palette       : a specifically limited set of well matched colors
 *   scheme        : method of choosing well matched colors within a palette
 *   variation     : alterations (such as pastel, pale, contrast, ...)
 *   accents       : recognizable changes within a single hue
 *
 *   norm          : rgb normals each running from 0.0 to 1.0 (opengl)
 *   byte          : rgb bytes   each running from 0   to 255
 *   hex           : rgb hex code in the format of #RRGGBB
 *
 *
 *   yPALETTE_new()                      - new color, makes that color current
 *   yPALETTE_artist(120, "pn", "n")     - sets the dominant color to RYB 120
 *   yPALETTE_scheme("ana_c", "m", "v")  - analogic w/complement, mothering
 *   x_color1 = yCOLOR(2, 0)             - select a color (2nd, base)
 *   x_color2 = yCOLOR(4, 3)             - select a color (4th, accent 3)
 *   x_color3 = yCOLOR(5, 2)             - select a color (5th, accent 2)
 *   yPALETTE_free()                     - releases a particular color
 *
 *
 */

/*---[[ DECISIONS ]]-----------------------------------------------#

 *   1) even though not technically required, the library will use dynamic
 *   memory allocation in order to be more flexible and aid my learning
 *
 *   2) while i have liked using opaque/void* pointers as identifiers for
 *   the using program in the past, it seems to be a bad idea.  these pointers
 *   are then beyond the control of the library, can be modified/trashed, and
 *   then drive a hard segfault or hidden failure.  i will change to the method
 *   used by most of the clib which is integer indentifiers that can be checked
 *   by the library and then used to find the actual pointer.  safer
 *
 *   3) do not make policy decisions like how many colors can be used and
 *   therefore limit the usefulness of the library
 *
 */
/*---[[ TERMINOLOGY ]]---------------------------------------------#

 *  RYB           : referred to as the "artistic" color wheel as it is typically
 *                  used in painting and related fields.  this scheme normally
 *                  results in more attractive color matches and variations than
 *                  the computer oriented RGB model or HSV/HSL that is based on
 *                  RGB.
 *
 *  RGB/24bit     : this is the most common computer format and encodes color in
 *                  a red-green-blue color format, typically shown in hex as
 *                  #RRGGBB with one byte for each of three color components.
 *                  - red          0-255
 *                  - green        0-255
 *                  - blue         0-255
 *                  there is really no way to adjust colors using RGB, its more
 *                  of an output format only
 *
 *  HSV/HSL       : believed to better represent human understanding of color,
 *                  they are a formats made up of hue (color), saturation
 *                  (intensity), and value (brightness).  best format for
 *                  transformations of color
 *                  - hue          0-359 (degree)
 *                  - saturation   0-100 (percent)
 *                  - value        0-100 (percent)
 *                  the results are 100% compatabile with RGB
 *
 */
/*---[[ BEST PRACTICE ]]-------------------------------------------#

 *   in our case, speed and directionally-correct is much more valuable than
 *   great accuracy or exact reversibliity.  as is proven out the normal
 *   use of a color wheel, colors that vary by only 1-2 in an RGB value are
 *   so close that the eye can not distinquish which is good enough for our use
 *
 */
/*---[[ NEXT STEPS ]]----------------------------------------------#

 *   TODO norm colors automatically to get the same intensities
 *   TODO use the mother color blending to harmonize the color schemes
 *   TODO hook the color scheming back up to get base colors
 */
/*===[[ END HDOC ]]===========================================================*/



/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef     YCOLOR
#define     YCOLOR   loaded



typedef unsigned char uchar;

#define  GEN_NORM    gen_norm
typedef struct cNORMAL tNORMAL;
struct cNORMAL {
   float red;
   float grn;
   float blu;
};
tNORMAL gen_norm;

/*===[[ PUBLIC INTERFACES ]]==================================================*/
/*---(constructor/destructor)--------------*/
int           yPALETTE_new        (void);
char          yPALETTE_clear      (void);
char          yPALETTE_select     (int     a_color);
char          yPALETTE_list       (void);
char          yPALETTE_free       (void);
char          yPALETTE_free_all   (void);
/*---(dominant)------------------*/
char          yPALETTE_artist     (int     a_angle, char *a_variation, char *norming);
char          yPALETTE__ryb       (int     a_angle);
/*---(setters)-------------------*/
char          yCOLOR_hue          (double  a_angle);
char          yCOLOR_hex          (char   *a_hex);
char          yCOLOR_rgb          (uchar   a_red, uchar a_grn, uchar a_blu);
char          yCOLOR_hsv          (double  a_hue, double a_sat, double a_val);
char          yCOLOR_hsl          (double  a_hue, double a_sat, double a_lig);
/*---(options)-------------------*/
char          yPALETTE__variant_set    (char *a_abbrev, int  *a_index);
char          yPALETTE__variant_make   (int   a_index,  char *a_hex,    char *a_out);
char          yPALETTE__norming_set    (char *a_abbrev, int  *a_index);
char          yPALETTE__norming_make   (int   a_index,  char *a_hex,    char *a_out);
char          yPALETTE__mothering_set  (char *a_abbrev, int *a_index);
char          yPALETTE__mothering_make (int   a_index,  char *a_mother, char *a_base, char *a_mixed);
char          yPALETTE_scheme          (char *a_scheme, char *a_mother, char *a_accenting);
char          yPALETTE__scheme_set     (char *a_abbrev, int  *a_scheme, int  *a_comp);
char          yPALETTE__switch         (int   a_dom,    int   a_scheme, int a_comp, int a_pos, int *a_hue);
char          yCOLOR_norming      (char   *a_norming);
char          yCOLOR_scheme       (char   *a_scheme);
char          yCOLOR_mothering    (char   *a_mothering);
char          yCOLOR_accenting    (char   *a_accenting);
/*---(schemes)-------------------*/
char          yPALETTE_well            (int   a_position, int a_accent, char *a_out);
char*         yPALETTE_well2hex        (int   a_position, int a_accent);
tNORMAL       yPALETTE_well2norm       (int   a_position, int a_accent);
char*         yCOLOR_single       (void   *a_color, char   a_type,  char a_option);
char*         yCOLOR_analogic     (void   *a_color, char   a_type,  char a_option);


int                /*  return  = simple integer error code                    */
yCOLOR_generate(   /*  PURPOSE = generate a scheme from config table          */
      char   *a_scheme,           /*  sub-type of this scheme                 */
      char    a_variant,          /*  variant scheme                          */
      char    a_output)           /*  style of output                         */
;

char*
yCOLOR_circle    (
      void   *a_color,
      char    a_type,
      char    a_inc,
      char    a_option)
;

void          yCOLOR_help      (void);

void          yCOLOR__varsetup (int);



#define       LEN_TEXT  2000
char          yCOLOR_answer [ LEN_TEXT ];



#endif
/*============================----end-of-source---============================*/
