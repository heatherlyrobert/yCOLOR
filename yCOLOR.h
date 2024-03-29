/*----------------------------------------------------------------------------*/
/*-------                 START OF SOURCE :: yCOLOR                    -------*/
/*----------------------------------------------------------------------------*/

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

#include    "yCOLOR_solo.h"




typedef     const       char        cchar;
typedef     const       int         cint;
typedef     const       float       cfloat;
typedef     const       double      cdouble;

/*---(program color scheme)-----------*/
char        yCOLOR_set           (cint   a_slot , cfloat a_alpha);
char        yCOLOR_set_clear     (cint   a_slot);
char        yCOLOR_wheel         (cchar *a_name);
char        yCOLOR_deg           (cint   a_deg );
char        yCOLOR_harm          (cchar *a_name);
char        yCOLOR_sat           (cchar *a_name);
char        yCOLOR_val           (cchar *a_name);
/*---(utility)------------------------*/
char*       yCOLOR_version       (void);
char        yCOLOR_init          (void);
char        yCOLOR_use           (char    a_use);
char        yCOLOR_scale         (char    a_scale, float a_min, float a_max);
char        yCOLOR_custom        (void);
char        yCOLOR_clear         (int     a_index);
/*---(color by degree)----------------*/
char        yCOLOR_deg2index     (cint    a_deg  , int    *a_index);
char        yCOLOR_deg2color     (cint    a_deg  , cfloat  a_alpha);
char        yCOLOR_deg2hex       (cint    a_deg  , char   *a_out  );
char       *yCOLOR_deg2name      (cint    a_deg  );
/*---(color by index number)----------*/
char        yCOLOR_num2color     (cint    a_num  , cfloat  a_alpha);
char        yCOLOR_num2hex       (cint    a_num  , char  *a_out);
char       *yCOLOR_num2name      (cint    a_num  );
float       yCOLOR_num2cutoff    (cint    a_num  );
/*---(color by value)-----------------*/
char        yCOLOR_val2error     (cfloat  a_alpha);
char        yCOLOR_val2color     (cdouble a_val  , cfloat a_alpha);
/*---(color by hex)-------------------*/
char        yCOLOR_hex2color     (cchar   *a_hex , cfloat  a_alpha);
/*---(HSV color format)---------------*/
char        yCOLOR_hex2hsv       (cchar   *a_hex , float  *a_hue, float  *a_sat, float  *a_val);
char        yCOLOR_hsv2hex       (char    *a_out , cfloat  a_hue, cfloat  a_sat, cfloat  a_val);
/*---(variations)---------------------*/
char        yCOLOR_variant       (cchar  *a_sat  , cchar *a_val , cchar  *a_hex, char   *a_out);
char        yCOLOR_accent        (cchar   a_level, cchar  *a_hex, char   *a_out);
char        yCOLOR_normalize     (cchar  *a_hex  , char   *a_out);
/*---(special)------------------------*/
char        yCOLOR_error         (char   a_level, char  *a_hex, char  *a_out);
/*---(max-diff)-----------------------*/
char        yCOLOR_diff_scheme      (char a_scheme);
char        yCOLOR_diff_start       (int a_start);
char        yCOLOR_diff_chaos       (int a_seed);
int         yCOLOR_diff_total       (void);
int         yCOLOR_diff_count       (void);
int         yCOLOR_diff_first       (void);
int         yCOLOR_diff_next        (void);
char        yCOLOR_diff_color       (int a_color, float a_alpha);
char        yCOLOR_diff_label       (int a_color, float a_alpha);
char        yCOLOR_diff_fore        (void);
char        yCOLOR_diff_back        (void);
char*       yCOLOR_diff_mapped      (int a_color);


char        yCOLOR_curs_init          (void);
char        yCOLOR_curs_wrap          (void);
int         yCOLOR_curs_add           (cchar *a_terse, cchar a_abbr, cchar *a_desc, cchar a_fg, cchar a_bg);
int         yCOLOR_curs_value         (cchar *a_terse);
char        yCOLOR_curs               (cchar *a_terse);
char        yCOLOR_cursa              (cchar  a_abbr);

#define       LEN_TEXT  2000
extern char          yCOLOR_answer [ LEN_TEXT ];


char        yCOLOR_palette          (cint   a_deg  , cchar *a_harm, cchar *a_sat, cchar *a_val);
char        yCOLOR_opengl           (char a_major, char a_minor, float a_alpha);
char        yCOLOR_opengl_clear     (char a_major, char a_minor);


#endif
/*============================----end-of-source---============================*/
