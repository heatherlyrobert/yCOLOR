/*============================----beg-of-source---============================*/


/*===[[ HEADERS ]]========================================*/
/*---(ansi-c standard)-------------------*/
#include    <stdio.h>        /* CLIBC   standard input/output                 */
#include    <stdlib.h>       /* CLIBC   standard general purpose              */
#include    <string.h>       /* CLIBC   standard string handling              */
#include    <stdint.h>       /* CLIBC   standard integer sizes                */
#include    <math.h>         /* CLIBC   standard math functions               */
#include    <memory.h>       /* CLIBC   standard memory management            */

/*---(posix standard)--------------------*/
#include    <unistd.h>       /* POSIX   standard operating system API         */
#include    <sys/time.h>     /* POSIX   standard time access                  */
#include    <regex.h>        /* POSIX   standard regular expressions          */

/*---(X11 standard)----------------------*/
#include    <X11/X.h>        /* X11     standard overall file                 */
#include    <X11/Xlib.h>     /* X11     standard C API                        */

/*---(opengl standard)-------------------*/
#include    <GL/gl.h>        /* OPENGL  standard primary header               */
#include    <GL/glx.h>       /* OPENGL  standard X11 integration              */

/*---(heatherly made)--------------------*/
#include    <yURG.h>         /* CUSTOM  heatherly urgent processing           */
#include    <yLOG.h>         /* CUSTOM  heatherly program logging             */
#include    <yFONT.h>        /* CUSTOM  heatherly texture-mapped fonts        */
#include    <ySTR.h>         /* CUSTOM  heatherly string handling             */
#include    <yVAR.h>         /* CUSTOM  heatherly variable testing            */
#include    <yX11.h>         /* CUSTOM  heatherly xlib/glx setup/teardown     */
#include    <yGLTEX.h>       /* CUSTOM  heatherly texture handling            */



/*===[[ RATIONAL LIMITS ]]====================================================*/
/*   LEN_ is a length or size of something
 *   MIN_ is a minimum count
 *   DEF_ is a default count
 *   MAX_ is a maximum count
 *
 */
/*3456789012+123456789012+123456789012+123456789012+123456789012+123456789012*/
/*---(string length)------------------*/
#define     LEN_RECD     2000
#define     LEN_STR      200
#define     LEN_LABEL    20
#define     LEN_HEX      10


static char  s_face     [LEN_LABEL] = "comfortaa";
static char  s_font     = -1;

static int   s_cset       =  4;
static int   s_ccolor     =  0;
static int   s_ncolor     =  0;
static int   s_cvariant   =  0;
static int   s_lvariant   =  0;
static int   s_nvariant   =  0;
static int   s_cnorming   =  0;
static int   s_nnorming   =  0;
static char  s_notation   = '-';

int       win_w = 1400;                     /* window width                   */
int       win_h =  600;                     /* window height                  */
int       tex_w = 1400;                     /* texture width                  */
int       tex_h =  600;                     /* texture height                 */

const    double   DEG2RAD   = M_PI / 180.0;

#define   MAX_COLOR    80
static const char s_RYB [MAX_COLOR][5][10] =
{  /*         original    pass 2     pass 1   paletton    latest    */
   /*-120 */ "#000000", "#99401a", "#99804d", "#99804d", "#4a2208",
   /*-110 */ "#000000", "#943920", "#946f4a", "#946f4a", "#522011",
   /*-100 */ "#000000", "#903326", "#905e48", "#905e48", "#5b1f1a",
   /*-090 */ "#000000", "#8c2c2d", "#8c4d46", "#8c4d46", "#641e24",
   /*-080 */ "#000000", "#882633", "#883c44", "#883c44", "#6d1c2d",
   /*-070 */ "#000000", "#842039", "#842b42", "#842b42", "#761b36",
   /*-060 */ "#000000", "#801a40", "#801a40", "#801a40", "#7f1a40",
   /*-050 */ "#000000", "#951535", "#951535", "#951535", "#941535",
   /*-040 */ "#000000", "#aa112a", "#aa112a", "#aa112a", "#a9112a",
   /*-030 */ "#000000", "#bf0d20", "#bf0d20", "#bf0d20", "#bf0d20",
   /*-020 */ "#000000", "#d40815", "#d40815", "#d40815", "#d40815",
   /*-010 */ "#000000", "#e9040a", "#e9040a", "#e9040a", "#e9040a",
   /*------------------------(normal wheel)----------------------*/
   /* 000 */ "#ff0000", "#ff0000", "#ff0000", "#aa3939", "#ff0000",
   /* 010 */ "#ff3500", "#fb1400", "#ff1700", "#aa5039", "#ff1500",
   /* 020 */ "#ff5900", "#f72800", "#ff3500", "#aa6039", "#ff2a00",
   /* 030 */ "#ff7400", "#f33d00", "#ff4700", "#aa6c39", "#ff3f00",
   /* 040 */ "#ff8900", "#f05100", "#ff5900", "#aa7539", "#ff5500",
   /* 050 */ "#ff9a00", "#ec6600", "#ff6700", "#aa7d39", "#ff6a00",
   /* 060 */ "#ffaa00", "#e87a00", "#ff7400", "#aa8439", "#ff7f00", /*  */
   /* 070 */ "#ffb800", "#e48e00", "#ff8b00", "#aa8b39", "#f98e00",
   /* 080 */ "#ffc600", "#e1a300", "#ffa200", "#aa9139", "#f39e00",
   /* 090 */ "#ffd300", "#ddb700", "#ffb900", "#aa9739", "#edad00",
   /* 100 */ "#ffe100", "#d9cc00", "#ffd000", "#aa9d39", "#e8bd00",
   /* 110 */ "#ffef00", "#d5e000", "#ffe500", "#aaa339", "#e2cd00",
   /* 120 */ "#ffff00", "#d2f500", "#ffff00", "#aaaa39", "#dddd00", /*  */
   /* 130 */ "#dcf900", "#afee00", "#d2ff00", "#99a637", "#b8df00",
   /* 140 */ "#bdf400", "#8ce700", "#a8ff00", "#8aa236", "#93e200",
   /* 150 */ "#9fee00", "#69e000", "#7eff00", "#7b9f35", "#6ee500",
   /* 160 */ "#7ce700", "#46d900", "#54ff00", "#6b9a33", "#49e800",
   /* 170 */ "#4dde00", "#23d200", "#2aff00", "#549431", "#24eb00",
   /* 180 */ "#00cc00", "#00cc15", "#00ff00", "#2d882d", "#00ee00", /*  */
   /* 190 */ "#00b64f", "#07b13c", "#00d22a", "#28794c", "#00c62a",
   /* 200 */ "#00a876", "#0e9663", "#00a854", "#25705a", "#009e55",
   /* 210 */ "#009999", "#157b8a", "#00867e", "#226666", "#00777f", /*  */
   /* 220 */ "#086fa1", "#1c60b1", "#0064a8", "#27556c", "#004faa",
   /* 230 */ "#0d56a6", "#2345d8", "#0032d2", "#2b4b6f", "#0027d4",
   /* 240 */ "#1240ab", "#2a2aff", "#0000ff", "#2e4272", "#0000ff", /*  */
   /* 250 */ "#1729b0", "#3523f0", "#1500e7", "#313975", "#1f00f3",
   /* 260 */ "#2618b1", "#411ce2", "#2a00d2", "#383276", "#3e00e8",
   /* 270 */ "#3914af", "#4d15d4", "#3f00bd", "#403075", "#5d00dc",
   /* 280 */ "#4a11ae", "#590ec6", "#5400a8", "#482e74", "#7c00d1",
   /* 290 */ "#5c0dac", "#6507b8", "#690093", "#4f2c73", "#9b00c6",
   /* 300 */ "#7109aa", "#7100aa", "#7e007e", "#582a72", "#bb00bb", /*  */
   /* 310 */ "#8f04a8", "#88008d", "#930069", "#652770", "#c6009b",
   /* 320 */ "#b70094", "#a00071", "#a80054", "#7a296a", "#d1007c",
   /* 330 */ "#cd0074", "#b70055", "#bd003f", "#882d61", "#dd005d",
   /* 340 */ "#dc0055", "#cf0038", "#d2002a", "#933157", "#e8003e",
   /* 350 */ "#ec0033", "#e7001c", "#e70015", "#9d344b", "#f3001f",
   /*---------------------(alternate ending)---------------------*/
   /* 310 */ "#000000", "#68049c", "#68049c", "#68049c", "#a604aa",
   /* 320 */ "#000000", "#60088f", "#60088f", "#60088f", "#91089a",
   /* 330 */ "#000000", "#530c81", "#530c81", "#530c81", "#7d0c8a",
   /* 340 */ "#000000", "#501174", "#501174", "#501174", "#681179",
   /* 350 */ "#000000", "#471566", "#471566", "#471566", "#541569",
   /* 360 */ "#000000", "#3f1959", "#3f1959", "#3f1959", "#3f1959",
   /* 370 */ "#000000", "#41225f", "#41225f", "#41225f", "#41225f",
   /* 380 */ "#000000", "#442a66", "#442a66", "#442a66", "#442a66",
   /* 390 */ "#000000", "#46336c", "#46336c", "#46336c", "#46336c",
   /* 400 */ "#000000", "#483b72", "#483b72", "#483b72", "#483b72",
   /* 410 */ "#000000", "#4a4479", "#4a4479", "#4a4479", "#4a4479",
   /* 420 */ "#000000", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f",
   /* 430 */ "#000000", "#52527f", "#52527f", "#52527f", "#52527f",
   /* 440 */ "#000000", "#59597f", "#59597f", "#59597f", "#59597f",
   /* 450 */ "#000000", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f",
   /* 460 */ "#000000", "#66667f", "#66667f", "#66667f", "#66667f",
   /* 470 */ "#000000", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f",
   /* 480 */ "#000000", "#72727f", "#72727f", "#72727f", "#72727f",
   /* --- */ ""       , ""       , ""       , ""       , ""       ,
};

/*---(color variations)------------------------------*/
#define    MAX_VARIANT      100
typedef struct cVARIANT tVARIANT;
struct cVARIANT
{
   char        abbr        [10];
   char        name        [35];
   char        method;                 /* absolute, percent, relative         */
   float       nsat;                   /* new saturation for HSV              */
   float       nval;                   /* new value for HSV                   */
   float       cS;
   float       cL;
};
tVARIANT    s_variants  [MAX_VARIANT] = {
   { "no"      , "none"                  , 'a' ,   0.00,  0.00,  0.50,  0.50 },
   /*---(full sat)--------------------*/
   { "vi"      , "vivid"                 , 'a' ,   1.00,  1.00,  0.50,  0.50 },
   { "st"      , "strong"                , 'a' ,   1.00,  0.90,  0.50,  0.50 },
   { "ba"      , "balanced"              , 'a' ,   1.00,  0.80,  0.50,  0.50 },
   { "wa"      , "warm"                  , 'a' ,   1.00,  0.70,  0.50,  0.50 },
   { "me"      , "medium"                , 'a' ,   1.00,  0.60,  0.50,  0.50 },
   { "ea"      , "earthy"                , 'a' ,   1.00,  0.50,  0.50,  0.50 },
   { "ri"      , "rich"                  , 'a' ,   1.00,  0.40,  0.50,  0.50 },
   { "da"      , "dark"                  , 'a' ,   1.00,  0.30,  0.50,  0.50 },
   { "de"      , "deep"                  , 'a' ,   1.00,  0.20,  0.50,  0.50 },
   /*---(strong sat)------------------*/
   { "br"      , "bright"                , 'a' ,   0.80,  1.00,  0.50,  0.50 },
   { "ar"      , "artists"               , 'a' ,   0.80,  0.80,  0.50,  0.50 },
   { "mo"      , "modern"                , 'a' ,   0.70,  0.50,  0.50,  0.50 },
   { "ne"      , "neutral"               , 'a' ,   0.70,  0.35,  0.50,  0.50 },
   /*---(moderate sat)----------------*/
   { "ch"      , "chalk"                 , 'a' ,   0.50,  1.00,  0.50,  0.50 },
   { "pa"      , "pastel"                , 'a' ,   0.50,  0.90,  0.50,  0.50 },
   { "xp"      , "csd_pastel"            , 'a' ,   0.56,  0.87,  0.50,  0.50 },
   { "op"      , "oil_pastel"            , 'a' ,   0.50,  0.75,  0.50,  0.50 },
   { "su"      , "subdued"               , 'a' ,   0.50,  0.50,  0.50,  0.50 },
   { "co"      , "cool"                  , 'a' ,   0.50,  0.30,  0.50,  0.50 },
   /*---(low sat)---------------------*/
   { "pl"      , "pale"                  , 'a' ,   0.30,  0.90,  0.50,  0.50 },
   { "li"      , "light"                 , 'a' ,   0.30,  0.70,  0.50,  0.50 },
   { "wa"      , "washout"               , 'a' ,   0.30,  0.50,  0.50,  0.50 },
   { "gr"      , "greyish"               , 'a' ,   0.30,  0.30,  0.50,  0.50 },
   /*---(nominal sat)-----------------*/
   { "wh"      , "whiteish"              , 'a' ,   0.15,  1.00,  0.50,  0.50 },
   /*---(older)-----------------------*/
   /*> { "--"      , "o_normal"              , '-' ,   1.000,  0.800,  0.50,  0.50 },   <*/
   /*> { "--"      , "o_medium"              , '-' ,   0.500, -0.220,  0.60,  0.60 },   <*/
   { "--"      , "o_dark"                , '-' ,   1.000,  0.600,  0.40,  0.40 },
   { "--"      , "o_darker"              , 'p' ,   1.000,  0.400,  0.25,  0.25 },
   { "--"      , "o_darkest"             , 'p' ,   1.000,  0.200,  0.10,  0.10 },
   { "--"      , "o_contrast_max"        , 'p' ,   1.000,  1.000,  1.00,  1.00 },
   { "--"      , "o_contrast_high"       , 'g' ,  -0.100, -0.100,  0.75,  0.75 },
   { "--"      , "o_contrast_more"       , 'g' ,  -0.100, -0.100,  0.66,  0.66 },
   { "--"      , "o_contrast_less"       , '-' ,   0.000,  0.000,  0.33,  0.33 },
   { "--"      , "o_contrast_low"        , '-' ,   0.000,  0.000,  0.20,  0.20 },
   { "--"      , "o_contrast_min"        , '-' ,   0.000,  0.000,  0.10,  0.10 },
   { "--"      , "o_pastel_dark"         , 'g' ,  -0.440, -0.440,  0.25,  0.25 },
   { "--"      , "o_pastel_darker"       , 'g' ,  -0.440, -0.700,  0.25,  0.25 },
   { "--"      , "o_pastel_darkest"      , 'g' ,  -0.440, -0.800,  0.10,  0.10 },
   { "--"      , "o_light/pale_normal"   , 'g' ,  -0.750, -0.100,  0.10,  0.10 },
   { "--"      , "o_light/pale_dark"     , 'g' ,  -0.750, -0.440,  0.10,  0.10 },
   { "--"      , "o_light/pale_darker"   , 'g' ,  -0.750, -0.700,  0.10,  0.10 },
   { "--"      , "o_light/pale_darkest"  , 'g' ,  -0.800, -0.800,  0.05,  0.05 },
   { "--"      , "o_accent_grey_light"   , 'g' ,  -0.950, -0.100,  0.50,  0.50 },
   { "--"      , "o_accent_grey_medium"  , 'g' ,  -0.950, -0.440,  0.50,  0.50 },
   { "--"      , "o_accent_grey_dark"    , 'g' ,  -0.950, -0.800,  0.50,  0.50 },
   { "--"      , "o_grey_light"          , 'g' ,  -0.950, -0.100,  0.10,  0.10 },
   { "--"      , "o_grey_medium"         , 'g' ,  -0.950, -0.440,  0.10,  0.10 },
   { "--"      , "o_grey_dark"           , 'g' ,  -0.950, -0.800,  0.10,  0.10 },
   { "--"      , "o_sat_less"            , 'g' ,  -0.333,  0.000,  0.50,  0.50 },
   { "--"      , "o_sat_low"             , 'g' ,  -0.666,  0.000,  0.50,  0.50 },
   { "--"      , "o_sat_min"             , 'g' ,  -1.000,  0.000,  0.50,  0.50 },
   /*---(complete)--------------------*/
   { ""        , "end of input"          , 'a' ,   0.00,  0.00,  0.00,  0.00 }
   /*---(older)-----------------------*/
};

/*> case MED            : DS =  0.500; DV = -0.220; CS =  0.60; CL =  0.60; break;   <* 
 *> case DARK           : DS =  0.500; DV = -0.440; CS =  0.40; CL =  0.40; break;   <* 
 *> case DARKER         : DS =  1.000; DV = -0.700; CS =  0.25; CL =  0.25; break;   <* 
 *> case DARKEST        : DS =  1.000; DV = -0.800; CS =  0.10; CL =  0.10; break;   <* 
 *>                       /+---(contrasts)----------------+/                         <* 
 *> case CONTRAST_MAX   : DS =  1.000; DV =  1.000; CS =  1.00; CL =  1.00; break;   <* 
 *> case CONTRAST_HIGH  : DS = -0.100; DV = -0.100; CS =  0.75; CL =  0.75; break;   <* 
 *> case CONTRAST_MORE  : DS = -0.100; DV = -0.100; CS =  0.66; CL =  0.66; break;   <* 
 *> case CONTRAST_LESS  : DS =  0.000; DV =  0.000; CS =  0.33; CL =  0.33; break;   <* 
 *> case CONTRAST_LOW   : DS =  0.000; DV =  0.000; CS =  0.20; CL =  0.20; break;   <* 
 *> case CONTRAST_MIN   : DS =  0.000; DV =  0.000; CS =  0.10; CL =  0.10; break;   <* 
 *>                       /+---(pastels)------------------+/                         <* 
 *> case PASTEL         : DS = -0.440; DV = -0.125; CS =  0.25; CL =  0.25; break;   <* 
 *> case PASTEL_DARK    : DS = -0.440; DV = -0.440; CS =  0.25; CL =  0.25; break;   <* 
 *> case PASTEL_DARKER  : DS = -0.440; DV = -0.700; CS =  0.25; CL =  0.25; break;   <* 
 *> case PASTEL_DARKEST : DS = -0.440; DV = -0.800; CS =  0.10; CL =  0.10; break;   <* 
 *>                       /+---(pale pastels)-------------+/                         <* 
 *> case PALE           : DS = -0.750; DV = -0.100; CS =  0.10; CL =  0.10; break;   <* 
 *> case PALE_DARK      : DS = -0.750; DV = -0.440; CS =  0.10; CL =  0.10; break;   <* 
 *> case PALE_DARKER    : DS = -0.750; DV = -0.700; CS =  0.10; CL =  0.10; break;   <* 
 *> case PALE_DARKEST   : DS = -0.800; DV = -0.800; CS =  0.05; CL =  0.05; break;   <* 
 *>                       /+---(greys)--------------------+/                         <* 
 *> case GREYACC_LIGHT  : DS = -0.950; DV = -0.100; CS =  0.50; CL =  0.50; break;   <* 
 *> case GREYACC_MEDIUM : DS = -0.950; DV = -0.440; CS =  0.50; CL =  0.50; break;   <* 
 *> case GREYACC_DARK   : DS = -0.950; DV = -0.800; CS =  0.50; CL =  0.50; break;   <* 
 *> case GREYISH_LIGHT  : DS = -0.950; DV = -0.100; CS =  0.10; CL =  0.10; break;   <* 
 *> case GREYISH_MEDIUM : DS = -0.950; DV = -0.440; CS =  0.10; CL =  0.10; break;   <* 
 *> case GREYISH_DARK   : DS = -0.950; DV = -0.800; CS =  0.10; CL =  0.10; break;   <* 
 *>                       /+---(pure saturation)----------+/                         <* 
 *> case SAT_LESS       : DS = -0.333; DV =  0.000; CS =  0.50; CL =  0.50; break;   <* 
 *> case SAT_LOW        : DS = -0.666; DV =  0.000; CS =  0.50; CL =  0.50; break;   <* 
 *> case SAT_MIN        : DS = -1.000; DV =  0.000; CS =  0.50; CL =  0.50; break;   <*/

/*---(color norming methods)-------------------------*/
#define    MAX_NORMING      100
typedef struct cNORMING tNORMING;
struct cNORMING
{
   char        abbr[8];
   char        name[35];
   double      red;
   double      grn;
   double      blu;
   char        is_value;
};
tNORMING s_normings   [MAX_NORMING] =
{
   { "no"  , "none"                           , 0.00, 0.00, 0.00, 'n' },
   { "bl"  , "byte_light"                     , 0.05, 0.05, 0.00, 'n' },
   { "bi"  , "byte_intensity"                 , 0.05, 0.10, 0.00, 'n' },
   { "bm"  , "byte_moderate"                  , 0.10, 0.10, 0.00, 'n' },
   { "bh"  , "byte_heavy"                     , 0.20, 0.20, 0.00, 'n' },
   { "bz"  , "byte_intensity+"                , 0.10, 0.20, 0.00, 'n' },
   { "bs"  , "byte_intensity++"               , 0.15, 0.30, 0.00, 'n' },
   { "tl"  , "total_light"                    , 0.05, 0.05, 0.00, 'y' },
   { "ti"  , "total_intensity"                , 0.05, 0.10, 0.00, 'y' },
   { "nw"  , "new one"                        , 0.05, 0.20, 0.05, 't' },
   { ""    , "end of input"                   , 0.00, 0.00, 0.00, 'n' }
};





double
yCOLOR__min3       (double a_one, double a_two, double a_three)
{
   if (a_one <= a_two) {
      if (a_one <= a_three) return a_one;
      return a_three;
   } else {
      if (a_two <= a_three) return a_two;
      return a_three;
   }
   return a_two;
}

double
yCOLOR__max3       (double a_one, double a_two, double a_three)
{
   if    (a_one >= a_two) {
      if (a_one >= a_three) return a_one;
      return                       a_three;
   } else {
      if (a_two >= a_three) return a_two;
      return                       a_three;
   }
   return                          a_two;
}

float
yCOLOR_unhex       (char a_one, char a_two)
{
   /*---(locals)-----------+-----------+-*/
   float       x_one       = 0.0;
   float       x_two       = 0.0;
   float       x_result    = 0.0;
   /*---(first char)---------------------*/
   if      (a_one >= '0' && a_one <= '9')   x_one = a_one - '0';
   else if (a_one >= 'a' && a_one <= 'f')   x_one = a_one - 'a' + 10;
   else if (a_one >= 'A' && a_one <= 'F')   x_one = a_one - 'A' + 10;
   else                                     x_one = 0.0;
   /*---(second char)--------------------*/
   if      (a_two >= '0' && a_two <= '9')   x_two = a_two - '0';
   else if (a_two >= 'a' && a_two <= 'f')   x_two = a_two - 'a' + 10;
   else if (a_two >= 'A' && a_two <= 'F')   x_two = a_two - 'A' + 10;
   else                                     x_two = 0.0;
   /*---(calc)---------------------------*/
   x_result =  ((x_one * 16.0) + x_two) / 255.0;
   /*---(complete)-----------------------*/
   return x_result;
}

char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR__hex2hsv      (     /* PURPOSE = convert RGB hex into HSV            */
      char     *a_hex,            /* RBG 24-bit hex code            (#RRGGBB) */
      float    *a_hue,            /* hue color component              (0-359) */
      float    *a_sat,            /* saturation color component     (0.0-1.0) */
      float    *a_val)            /* value color component          (0.0-1.0) */
{
   /*---(locals)-----------+-----------+-*/
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   float       x_min       = 0.0;
   float       x_max       = 0.0;
   float       x_del       = 0.0;
   /*---(simple defense)-------------------*/
   if (strlen(a_hex) != 7)    return -2;
   x_red = yCOLOR_unhex (a_hex [1], a_hex [2]);
   x_grn = yCOLOR_unhex (a_hex [3], a_hex [4]);
   x_blu = yCOLOR_unhex (a_hex [5], a_hex [6]);
   /*---(setup)----------------------------*/
   x_min   = yCOLOR__min3 (x_red, x_grn, x_blu);
   x_max   = yCOLOR__max3 (x_red, x_grn, x_blu);
   x_del   = x_max - x_min;
   /*---(value)----------------------------*/
   if (a_val)  *a_val = x_max;
   /*---(saturation)-----------------------*/
   if (x_max == 0.0) {
      *a_sat  = 0.0;
      *a_hue  = 0.0;
      return 0;
   }
   if (a_sat)  *a_sat = x_del / x_max;
   /*---(hue)------------------------------*/
   if      (x_del   == 0.0  )   *a_hue = 0.0;
   else if (x_red   == x_max)   *a_hue = 0.0 + (x_grn - x_blu) / x_del;
   else if (x_grn   == x_max)   *a_hue = 2.0 + (x_blu - x_red) / x_del;
   else                         *a_hue = 4.0 + (x_red - x_grn) / x_del;
   *a_hue *= 60;
   if (*a_hue < 0.0) *a_hue += 360.0;
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR__hsv2hex    (           /* PURPOSE = convert HSV to RGB HEX              */
      float     a_hue,            /* hue color component              (0-359) */
      float     a_sat,            /* saturation color component     (0.0-1.0) */
      float     a_val,            /* value color component          (0.0-1.0) */
      char     *a_hex)            /* RGB 24-bit hex code            (#RRGGBB) */
{
   /*---(defense)--------------------------*/
   while (a_hue <  0.0)     a_hue += 360.0;
   while (a_hue >= 360.0)   a_hue -= 360.0;
   if (a_sat < 0.0)         a_sat  = 0.0;
   if (a_sat > 1.0)         a_sat  = 1.0;
   if (a_val < 0.0)         a_val  = 0.0;
   if (a_val > 1.0)         a_val  = 1.0;
   /*---(locals)---------------------------*/
   int       i;
   float     h, f, p, q, t;
   float     x_red, x_grn, x_blu;
   /*---(check for grey)-------------------*/
   if (a_sat == 0) {
      x_red = x_grn = x_blu  = a_val;
   } else {
      /*---(prepare)-----------------------*/
      h = a_hue / 60;           /* divide into six sectors (0 - 5)            */
      i = floor(h);             /* section number as integer                  */
      f = h - i;                /* fractional part of section number          */
      p = a_val * (1 - a_sat);
      q = a_val * (1 - a_sat * f);
      t = a_val * (1 - a_sat * (1 - f));
      /*---(assign color)------------------*/
      switch (i) {
      case 0:  x_red = a_val; x_grn = t;     x_blu = p;     break;
      case 1:  x_red = q;     x_grn = a_val; x_blu = p;     break;
      case 2:  x_red = p;     x_grn = a_val; x_blu = t;     break;
      case 3:  x_red = p;     x_grn = q;     x_blu = a_val; break;
      case 4:  x_red = t;     x_grn = p;     x_blu = a_val; break;
      default: x_red = a_val; x_grn = p;     x_blu = q;     break;
      }
   }
   /*---(truncate into 0-255)--------------*/
   uchar u_red = x_red * 255;
   uchar u_grn = x_grn * 255;
   uchar u_blu = x_blu * 255;
   /*---(place into RGB hex)---------------*/
   snprintf(a_hex, LEN_HEX, "#%02x%02x%02x", u_red, u_grn, u_blu);
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((c_convert))===* return  = simple error code                   */
yCOLOR_variant       (       /* PURPOSE = apply a color variation             */
      char     *a_name,           /* variation name                           */
      char     *a_hex,            /* rgb three byte hex code        (#rrggbb) */
      char     *a_out)            /* rgb three byte hex code        (#rrggbb) */
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;      /* return code for errors              */
   int         i           =   0;      /* generic iterator                    */
   int         x_index     =  -1;      /* variant index                       */
   int         rc          =   0;      /* generic return code                 */
   float       x_hue       =   0.0;    /* HSV hue                             */
   float       x_sat       =   0.0;    /* HSV saturation                      */
   float       x_val       =   0.0;    /* HSV value                           */
   /*---(defense)--------------------------*/
   --rce;  if (a_name == NULL) {
      return rce;
   }
   --rce;  if (a_hex  == NULL) {
      return rce;
   }
   --rce;  if (a_out  == NULL) {
      return rce;
   }
   /*---(initialize)-----------------------*/
   strlcpy (a_out, a_hex, LEN_HEX);
   /*---(search)---------------------------*/
   if (strcmp (a_name, "CURRENT") == 0)  x_index = s_cvariant;
   if (strcmp (a_name, "SAME"   ) == 0)  x_index = s_lvariant;
   if (strcmp (a_name, "FIRST"  ) == 0)  x_index = 0;
   if (strcmp (a_name, "NEXT"   ) == 0)  x_index = ++s_lvariant;
   if (x_index < 0) {
      for (i = 0; i < MAX_VARIANT; ++i) {
         if (s_variants [i].abbr [0] == '\0')            break;
         if ((strcmp (s_variants [i].abbr, a_name) != 0) &&
               (strcmp (s_variants [i].name, a_name) != 0))  continue;
         x_index = i;
         break;
      }
   }
   --rce;  if (x_index < 0) {
      return rce;
   }
   s_lvariant = x_index;
   /*---(check for nothing)----------------*/
   if (x_index == 0) {
      return 0;
   }
   /*---(get the base)---------------------*/
   rc = yCOLOR__hex2hsv (a_hex, &x_hue, &x_sat, &x_val);
   --rce;  if (rc != 0) {
      return rce;
   }
   /*---(get the modifiers)----------------*/
   --rce;  switch (s_variants [x_index].method) {
   case 'a' :  /* simply force a new sat and val setting   */
      x_sat   = s_variants [x_index].nsat;
      x_val   = s_variants [x_index].nval;
      break;
   case 'r' :  /* make new settings relative to old ones   */
      x_sat  *= s_variants [x_index].nsat;
      x_val  *= s_variants [x_index].nval;
      break;
   case 'g' :  /* make new settings relative to gap        */
      x_sat  += (1 - x_sat) * s_variants [x_index].nsat;
      x_val  += (1 - x_val) * s_variants [x_index].nval;
      break;
   default  :
      return rce;
   }
   /*---(apply the modifiers)--------------*/
   rc = yCOLOR__hsv2hex (x_hue, x_sat, x_val, a_out);
   --rce;  if (rc != 0) {
      return rce;
   }
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((c_convert))===* return  = simple error code                   */
yCOLOR_norming_find  (char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   int         x_index     = 0;
   /*---(search)---------------------------*/
   for (i = 0; i < MAX_NORMING; ++i) {
      if (s_normings [i].abbr [0] == '\0')            break;
      if (s_normings [i].abbr [0] != a_name [0])      continue;
      if ((strcmp (s_normings [i].abbr, a_name) != 0) &&
            (strcmp (s_normings [i].name, a_name) != 0))  continue;
      x_index = i;
      break;
   }
   /*---(complete)-------------------------*/
   return x_index;
}

char       /*=((pUPDATE ]]=========* return  = simple error code              */
yCOLOR_norming    (      /* PURPOSE = level color intensity               */
      int       a_index,          /* norming index                            */
      char     *a_hex,            /* rgb three byte hex code        (#rrggbb) */
      char     *a_out)            /* rgb three byte hex code        (#rrggbb) */
{
   /*---(locals)-----------+-----------+-*/
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   float       x_hue       = 0.0;
   float       x_sat       = 0.0;
   float       x_val       = 0.0;
   float       x_total     = 0.0;
   int         rc          = 0;
   float       x_norm      = 0.0;
   float       x_redpct    = 0.0;
   float       x_grnpct    = 0.0;
   float       x_blupct    = 0.0;
   /*---(brightness)-----------------------*/
   float  d_red  = s_normings [a_index].red;
   float  d_grn  = s_normings [a_index].grn;
   float  d_blu  = s_normings [a_index].blu;
   /*> printf("norming [%d]... hsv based = %c\n", a_index, s_normings [a_index].is_value);   <* 
    *> printf("  factor    %5.3fr, %5.3fg, %5.3fb\n", d_red, d_grn, d_blu);                    <*/
   /*> printf("  color     %3dr, %3dg, %3db\n", x_red, x_grn, x_blu);                 <*/
   /*---(pull values)----------------------*/
   x_red = yCOLOR_unhex (a_hex [1], a_hex [2]);
   x_grn = yCOLOR_unhex (a_hex [3], a_hex [4]);
   x_blu = yCOLOR_unhex (a_hex [5], a_hex [6]);
   if (s_normings [a_index].is_value == 'y') {
      /*---(update)---------------------------*/
      x_red *= (s_normings [a_index].red);
      x_grn *= (s_normings [a_index].grn);
      x_blu *= (s_normings [a_index].blu);
      x_norm = 1.000 - x_red - x_grn - x_blu;
      yCOLOR__hex2hsv (a_hex, &x_hue, &x_sat, &x_val);
      yCOLOR__hsv2hex (x_hue, x_sat, x_val * x_norm, a_out);
   } else if (s_normings [a_index].is_value == 'n') {
      /*---(update)---------------------------*/
      x_red *= (1.0 - s_normings [a_index].red);
      x_grn *= (1.0 - s_normings [a_index].grn);
      x_blu *= (1.0 - s_normings [a_index].blu);
      /*---(truncate into 0-255)--------------*/
      uchar u_red = x_red * 255;
      uchar u_grn = x_grn * 255;
      uchar u_blu = x_blu * 255;
      /*---(place into RGB hex)---------------*/
      snprintf (a_out, LEN_HEX, "#%02x%02x%02x", u_red, u_grn, u_blu);
   } else if (s_normings [a_index].is_value == 't') {
      /*---(update)---------------------------*/
      x_total = x_red + x_grn + x_blu;
      x_redpct = x_red / x_total;
      x_grnpct = x_grn / x_total;
      x_blupct = x_blu / x_total;
      /*---(truncate into 0-255)--------------*/
      uchar u_red = x_redpct * 255;
      uchar u_grn = x_grnpct * 255;
      uchar u_blu = x_blupct * 255;
      /*---(place into RGB hex)---------------*/
      snprintf (a_out, LEN_HEX, "#%02x%02x%02x", u_red, u_grn, u_blu);
   }
   /*---(complete)-------------------------*/
   return 0;
}


char
FONT_load            (void)
{
   s_font  = yFONT_load (s_face);
   if (s_font <  0) {
      fprintf (stderr, "Problem loading %s\n", s_face);
      exit    (1);
   }
   return 0;
}

char
FONT_delete          (void)
{
   yFONT_free (s_font);
   return 0;
}


/*============================--------------------============================*/
/*===----                             draw                             ----===*/
/*============================--------------------============================*/
static void      o___OPENGL__________________o (void) {;}

/*---(opengl objects)--------------------*/
static int  s_tex     =     0;                /* texture for image              */
static int  s_fbo     =     0;                /* framebuffer                    */
static int  s_depth   =     0;                /* depth buffer                   */

static char        /* PURPOSE : create a texture -----------------------------*/
TEX__create          (void)
{
   DEBUG_GRAF  printf("texture_create () beg\n");
   /*---(generate)-----------------------*/
   glGenFramebuffersEXT         (1, &s_fbo);
   glGenTextures                (1, &s_tex);
   glGenRenderbuffersEXT        (1, &s_depth);
   /*---(bind)---------------------------*/
   DEBUG_GRAF  printf("texture_create () bind\n");
   glBindFramebufferEXT         (GL_FRAMEBUFFER_EXT,  s_fbo);
   glBindTexture                (GL_TEXTURE_2D,       s_tex);
   /*---(settings)-----------------------*/
   DEBUG_GRAF  printf("texture_create () settings\n");
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexEnvi                    (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glTexParameteri              (GL_TEXTURE_2D,  GL_GENERATE_MIPMAP, GL_TRUE);
   /*---(copy)---------------------------*/
   DEBUG_GRAF  printf("texture_create () allocate\n");
   glTexImage2D                 (GL_TEXTURE_2D, 0, GL_RGBA, tex_w, tex_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
   DEBUG_GRAF  printf("texture_create () copy\n");
   glFramebufferTexture2DEXT    (GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, s_tex, 0);
   /*---(depth)--------------------------*/
   DEBUG_GRAF  printf("texture_create () depth\n");
   glBindRenderbufferEXT        (GL_RENDERBUFFER_EXT, s_depth);
   glRenderbufferStorageEXT     (GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, tex_w, tex_h);
   glFramebufferRenderbufferEXT (GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, s_depth);
   /*---(unbind)-------------------------*/
   DEBUG_GRAF  printf("texture_create () unbind\n");
   glBindFramebufferEXT         (GL_FRAMEBUFFER_EXT, 0);
   /*---(complete)-----------------------*/
   DEBUG_GRAF  printf("texture_create () end\n");
   return 0;
}

static char        /* PURPOSE : delete a framebuffer -------------------------*/
TEX__free            (void)
{
   DEBUG_GRAF  printf("texture_free () beg\n");
   /*---(generate)-----------------------*/
   glDeleteTextures                (1, &s_tex);
   glDeleteRenderbuffersEXT        (1, &s_depth);
   glDeleteFramebuffersEXT         (1, &s_fbo);
   /*---(complete)-----------------------*/
   DEBUG_GRAF  printf("texture_free () end\n");
   return 0;
}

char       /* ---- : establish rational drawing settings ---------------------*/
DRAW_init          (void)
{
   /*---(color)--------------------------*/
   glClearColor    (0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth    (1.0f);
   /*---(textures)-----------------------*/
   glEnable        (GL_TEXTURE_2D);    /* NEW */
   /*---(blending)-----------------------*/
   glShadeModel    (GL_SMOOTH);
   glEnable        (GL_DEPTH_TEST);
   glEnable        (GL_ALPHA_TEST);
   glAlphaFunc     (GL_GEQUAL, 0.0125);
   glEnable        (GL_BLEND);
   glBlendFunc     (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glDepthFunc     (GL_LEQUAL);
   /*---(anti-aliasing)------------------*/
   glHint          (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   /*---(special polygon antialiasing)----------*/
   glEnable        (GL_POLYGON_SMOOTH);
   glPolygonMode   (GL_FRONT_AND_BACK, GL_FILL);
   glHint          (GL_POLYGON_SMOOTH_HINT, GL_NICEST);
   /*---(simple defaulting)--------------*/
   glLineWidth     (0.50f);
   /*---(process immediately)------------*/
   glFlush       ();
   /*---(complete)-----------------------*/
   return 0;
}

char
yCOLOR_hex      (int a_deg, char a_use, char *a_hex)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =   0;
   /*---(adjust)-------------------------*/
   if (a_use == 'w') {
      while (a_deg <    0)   a_deg +=  360;
      while (a_deg >= 360)   a_deg -=  360;
   }
   if (a_use == 's') {
      while (a_deg < -120)   a_deg  = -120;
      while (a_deg >  480)   a_deg  =  480;
      if (a_deg > 300)       a_deg +=   50;
   }
   /*---(parse color)--------------------*/
   x_deg = a_deg / 10 + 12;
   strlcpy (a_hex, s_RYB [x_deg][s_cset], LEN_HEX);
   /*---(complete)-----------------------*/
   return x_deg;
}

char
DRAW_color_hex  (char *a_hex)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =   0;
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   /*---(parse color)--------------------*/
   x_red = yCOLOR_unhex (a_hex[1], a_hex[2]);
   x_grn = yCOLOR_unhex (a_hex[3], a_hex[4]);
   x_blu = yCOLOR_unhex (a_hex[5], a_hex[6]);
   /*---(set color)----------------------*/
   glColor4f   (x_red, x_grn, x_blu, 1.0f);
   /*---(complete)-----------------------*/
   return 0;
}

char
DRAW_color      (int a_deg, char a_use, char *a_hex)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =   0;
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   /*---(adjust)-------------------------*/
   if (a_use == 'w') {
      while (a_deg <    0)   a_deg +=  360;
      while (a_deg >= 360)   a_deg -=  360;
   }
   if (a_use == 's') {
      while (a_deg < -120)   a_deg  = -120;
      while (a_deg >  480)   a_deg  =  480;
      if (a_deg > 300)       a_deg +=   50;
   }
   /*---(parse color)--------------------*/
   x_deg = (a_deg / 10) + 12;
   x_red = yCOLOR_unhex (s_RYB [x_deg][s_cset][1], s_RYB [x_deg][s_cset][2]);
   x_grn = yCOLOR_unhex (s_RYB [x_deg][s_cset][3], s_RYB [x_deg][s_cset][4]);
   x_blu = yCOLOR_unhex (s_RYB [x_deg][s_cset][5], s_RYB [x_deg][s_cset][6]);
   /*---(set color)----------------------*/
   glColor4f   (x_red, x_grn, x_blu, 1.0f);
   /*---(return hex)---------------------*/
   if (a_hex)  strlcpy (a_hex, s_RYB [x_deg][s_cset], LEN_HEX);
   /*---(complete)-----------------------*/
   return 0;
}

char
DRAW_column         (void)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =  0;             /* loop iterator -- word          */
   int         x_set       =  0;             /* loop iterator -- word          */
   float       x_wide      =  75.0;
   float       x_inc       =  0.0;
   char        x_text      [LEN_STR];
   x_inc = (win_h - 40) / 36.0;
   glPushMatrix(); {
      glTranslatef ( 20, -win_h / 2 + 20,   0.0);
      for (x_deg =  0; x_deg < 360; x_deg += 10) {
         glPushMatrix(); {
            DRAW_color   (x_deg, 'w', NULL);
            glBegin         (GL_POLYGON); {
               glVertex3f  (   0.0, x_inc,     0.0);
               glVertex3f  (x_wide, x_inc,     0.0);
               glVertex3f  (x_wide,   0.0,     0.0);
               glVertex3f  (   0.0,   0.0,     0.0);
            } glEnd   ();
         } glPopMatrix();
         if (x_deg % 30 == 0) {
            glPushMatrix(); {
               sprintf (x_text, "%03d", x_deg);
               glTranslatef ( 80 ,   3.0,   0.0);
               yFONT_print  (s_font,   8, YF_BASLEF, x_text);
            } glPopMatrix();
         }
         glTranslatef ( 0.0, x_inc,   0.0);
      }
   } glPopMatrix();
   return 0;
}

char
DRAW_wheel          (char a_which)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =  0;             /* loop iterator -- word          */
   int         i           =  0;             /* loop iterator -- word          */
   float       x1          =  0.0;
   float       y1          =  0.0;
   float       x2          =  0.0;
   float       y2          =  0.0;
   float       r1          =  0.0;
   float       r2          =  0.0;
   float       x_inc       = 80.0;
   char        x_text      [LEN_STR];
   char        x_base      [LEN_HEX] = "";
   char        x_hex       [LEN_HEX] = "";
   char        x_norm      [LEN_HEX] = "";
   glPushMatrix(); {
      if      (a_which == 'o')  glTranslatef ( 380,   0.0,   0.0);
      else if (a_which == 'O')  glTranslatef ( 380,   0.0,   0.0);
      else                      glTranslatef (1100,   0.0,   0.0);
      for (x_deg = 0; x_deg < 360; x_deg += 10) {
         glPushMatrix(); {
            glRotatef    (x_deg + 90, 0.0f, 0.0f, 1.0f);
            /*---(set color)-------------*/
            DRAW_color   (x_deg, 'w', x_base);
            strlcpy (x_norm, x_base, LEN_HEX);
            if (a_which != 'o') {
               yCOLOR_variant ("CURRENT", x_base, x_hex);
               yCOLOR_norming (s_cnorming, x_hex , x_norm);
               DRAW_color_hex (x_norm);
            }
            /*---(draw)------------------*/
            r1  = win_h / 4.0;
            r2  = r1 + x_inc;
            glBegin         (GL_POLYGON); {
               glVertex3f  (r1,  r1 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r2,  r2 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r2, -r2 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r1, -r1 * sin (5.5 * DEG2RAD),     0.0);
            } glEnd   ();
            if (x_deg % 60 == 0) {
               glPushMatrix(); {
                  glTranslatef ( 80,   0.0,   0.0);
                  x2 = y2 = 0;
                  for (i = 0; i <= 360; i += 10) {
                     x1 =  40.0 * sin (i * DEG2RAD);
                     y1 =  40.0 * cos (i * DEG2RAD);
                     glBegin         (GL_POLYGON); {
                        glVertex3f  ( 0.0,    0.0,     0.0);
                        glVertex3f  (  x2,     y2,     0.0);
                        glVertex3f  (  x1,     y1,     0.0);
                        glVertex3f  ( 0.0,    0.0,     0.0);
                     } glEnd   ();
                     x2 = x1;
                     y2 = y1;
                  }
               } glPopMatrix();
            }
            if (x_deg % 60 == 30) {
               glPushMatrix(); {
                  glTranslatef ( 120,   0.0,   0.0);
                  x2 = y2 = 0;
                  for (i = 0; i <= 360; i += 10) {
                     x1 =  25.0 * sin (i * DEG2RAD);
                     y1 =  25.0 * cos (i * DEG2RAD);
                     glBegin         (GL_POLYGON); {
                        glVertex3f  ( 0.0,    0.0,     0.0);
                        glVertex3f  (  x2,     y2,     0.0);
                        glVertex3f  (  x1,     y1,     0.0);
                        glVertex3f  ( 0.0,    0.0,     0.0);
                     } glEnd   ();
                     x2 = x1;
                     y2 = y1;
                  }
               } glPopMatrix();
            }
            if (x_deg % 30 == 0) {
               glPushMatrix(); {
                  sprintf (x_text, "%03d", x_deg);
                  glTranslatef ( 240,   0.0,   0.0);
                  yFONT_print  (s_font,   8, YF_MIDCEN, x_text);
               } glPopMatrix();
            }
            if (x_deg == s_ccolor) {
               glPushMatrix(); {
                  glTranslatef ( 145,   0.0,   0.0);
                  yFONT_print  (s_font,   8, YF_MIDRIG, "curr");
               } glPopMatrix();
            }
            if (s_notation == 'y') {
               glPushMatrix(); {
                  glTranslatef ( 200,   0.0,   0.0);
                  glColor4f    ( 0.0, 0.0, 0.0, 1.0);
                  yFONT_print  (s_font,   8, YF_MIDCEN, x_norm);
               } glPopMatrix();
            }
         } glPopMatrix();
      }
   } glPopMatrix();
   return 0;
}

char
DRAW_variants       (void)
{
   int         i           = 0;
   int         x_index     = 0;
   char        x_base      [LEN_HEX] = "";
   char        x_hex       [LEN_HEX] = "";
   yCOLOR_hex  (s_ccolor, 'w', x_base);
   glPushMatrix(); {
      glTranslatef ( 650 , -win_h / 2 + 40.0,   0.0);
      for (i = 0; i < s_nvariant; ++i) {
         if (s_variants [i].abbr[0] == '\0') break;
         if (i == 0)  yCOLOR_variant ("FIRST", x_base, x_hex);
         else         yCOLOR_variant ("NEXT" , x_base, x_hex);
         DRAW_color_hex (x_hex);
         glBegin         (GL_POLYGON); {
            glVertex3f  (    0.0,  22.0,     0.0);
            glVertex3f  (   80.0,  22.0,     0.0);
            glVertex3f  (   80.0,   0.0,     0.0);
            glVertex3f  (    0.0,   0.0,     0.0);
         } glEnd   ();
         glPushMatrix(); {
            glColor4f   (  0.0,   0.0,   0.0, 1.0f);
            glTranslatef (40.0,   7.0,   5.0);
            yFONT_print  (s_font,   8, YF_MIDCEN, x_hex);
            glTranslatef ( 0.0,  10.0,   0.0);
            yFONT_print  (s_font,   8, YF_MIDCEN, s_variants [i].name);
         } glPopMatrix();
         if (i == s_cvariant) {
            glPushMatrix(); {
               glColor4f   (  1.0,   1.0,   1.0, 1.0f);
               glTranslatef (  -5,  12.0,   0.0);
               yFONT_print  (s_font,   8, YF_MIDLEF, "curr");
            } glPopMatrix();
         }
         glTranslatef (   0,  22.0,   0.0);
      }
   } glPopMatrix();
   return 0;
}

char
DRAW_normings       (void)
{
   int         i           = 0;
   int         x_index     = 0;
   char        x_base      [LEN_HEX] = "";
   char        x_hex       [LEN_HEX] = "";
   char        x_norm      [LEN_HEX] = "";
   yCOLOR_hex     (s_ccolor, 'w', x_base);
   yCOLOR_variant ("CURRENT", x_base, x_hex);
   glPushMatrix(); {
      glTranslatef ( 730 , -win_h / 2 +  80,   0.0);
      for (i = 0; i < s_nnorming; ++i) {
         if (s_normings [i].abbr[0] == '\0') break;
         yCOLOR_norming (i, x_hex , x_norm);
         DRAW_color_hex (x_norm);
         glBegin         (GL_POLYGON); {
            glVertex3f  (    0.0,  50.0,     0.0);
            glVertex3f  (  100.0,  50.0,     0.0);
            glVertex3f  (  100.0,   0.0,     0.0);
            glVertex3f  (    0.0,   0.0,     0.0);
         } glEnd   ();
         glPushMatrix(); {
            glColor4f   (  0.0,   0.0,   0.0, 1.0f);
            glTranslatef (50.0,  10.0,   5.0);
            yFONT_print  (s_font,   8, YF_MIDCEN, x_norm);
            glTranslatef ( 0.0,  10.0,   5.0);
            yFONT_print  (s_font,   8, YF_MIDCEN, s_normings [i].name);
         } glPopMatrix();
         if (i == s_cnorming) {
            glPushMatrix(); {
               glColor4f   (  1.0,   1.0,   1.0, 1.0f);
               glTranslatef (+90 ,  12.0,   0.0);
               yFONT_print  (s_font,   8, YF_MIDLEF, "curr");
            } glPopMatrix();
         }
         glTranslatef (   0,  50.0,   0.0);
      }
   } glPopMatrix();
   return 0;
}

char
DRAW_scale          (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           =  0;             /* loop iterator -- word          */
   float       x           =  0.0;
   float       y           =  0.0;
   float       x_inc       = 80.0;
   char        x_text      [LEN_STR];
   int         x_set       =  0;             /* loop iterator -- word          */
   char        x_base      [LEN_HEX] = "";
   char        x_hex       [LEN_HEX] = "";
   for (i = -120; i <= 480; i += 10) {
      glPushMatrix(); {
         yCOLOR_hex  (i, 's', x_base);
         DRAW_color_hex (x_base);
         /*> DRAW_color   (i, 's', NULL);                                             <*/
         glTranslatef ( 370 + (i * 2.0), -win_h / 2 - 10,   0.0);
         glBegin         (GL_POLYGON); {
            glVertex3f  (    0.0,  30.0,     0.0);
            glVertex3f  (   20.0,  30.0,     0.0);
            glVertex3f  (   20.0,   0.0,     0.0);
            glVertex3f  (    0.0,   0.0,     0.0);
         } glEnd   ();
      } glPopMatrix();
      if (i % 30 == 0) {
         glPushMatrix(); {
            sprintf (x_text, "%d", i);
            glTranslatef ( 370 + (i * 2.0), -win_h / 2 - 10,   0.0);
            glTranslatef (  10,  40.0,   0.0);
            /*> glColor4f   (  1.0,   1.0,   1.0, 1.0f);                              <*/
            yFONT_print  (s_font,   8, YF_MIDCEN, x_text);
         } glPopMatrix();
      }
   }
   return 0;
}

char
DRAW_box            (char *a_base, char *a_var, char a_size, int a_xpos, int a_ypos)
{
   /*---(locals)-----------+-----------+-*/
   int         x_var       =  0;             /* loop iterator -- word          */
   char        x_hex       [LEN_HEX] = "";
   char        x_text      [LEN_HEX] = "";
   float       x_wide      = 70;
   float       x_tall      = 70;
   float       x_zpos      =  0;
   a_xpos = (a_xpos * 40.0);
   a_ypos = (a_ypos * 40.0);
   switch (a_size) {
   case 's' : x_wide = x_tall = 30; a_xpos += 15;  a_ypos += 15;  x_zpos = 20;  break;
   case 'c' : x_wide = x_tall = 30; a_xpos += 23;  a_ypos +=  5;  x_zpos = 20;  break;
   case 'b' : x_wide = x_tall = 70; a_xpos += 15;  a_ypos += 15;  x_zpos = 10;  break;
   case '1' : x_wide = 300; x_tall = 300;                         x_zpos =  0;  break;
   case '2' : x_wide = 200; x_tall = 300; a_xpos -= 22;           x_zpos =  4;  break;
   case '3' : x_wide = 300; x_tall = 200;                         x_zpos =  2;  break;
   case '4' : x_wide = 200; x_tall = 200; a_xpos -= 22;           x_zpos =  8;  break;
   }
   yCOLOR_variant (a_var, a_base, x_hex);
   DRAW_color_hex (x_hex);
   glBegin         (GL_POLYGON); {
      glVertex3f  ( a_xpos         , a_ypos + x_tall, x_zpos);
      glVertex3f  ( a_xpos + x_wide, a_ypos + x_tall, x_zpos);
      glVertex3f  ( a_xpos + x_wide, a_ypos         , x_zpos);
      glVertex3f  ( a_xpos         , a_ypos         , x_zpos);
   } glEnd   ();
   if (s_notation == 'y') {
      yCOLOR_variant ("none", a_base, x_hex);
      DRAW_color_hex (x_hex);
      glPushMatrix(); {
         sprintf (x_text, "%-2.2s", a_var);
         glTranslatef ( a_xpos + (x_wide/2), a_ypos + 10, 30.0);
         glColor4f   (  0.0,   0.0,   0.0, 1.0f);
         yFONT_print  (s_font,   8, YF_MIDCEN, x_text);
      } glPopMatrix();
   }
   return 0;
}

char
DRAW_layout         (void)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =  0;             /* loop iterator -- word          */
   int         x_var       =  0;             /* loop iterator -- word          */
   float       x           =  0.0;
   float       y           =  0.0;
   float       x_inc       = 80.0;
   char        x_text      [LEN_STR];
   int         x_set       =  0;             /* loop iterator -- word          */
   char        x_base      [LEN_HEX] = "";
   char        x_hex1      [LEN_HEX] = "";
   char        x_hex2      [LEN_HEX] = "";
   char        x_hex3      [LEN_HEX] = "";
   char        x_hex4      [LEN_HEX] = "";
   glPushMatrix(); {
      glTranslatef ( 850 , -win_h / 2 + 50,   0.0);
      /*---(upper-left)------------------*/
      yCOLOR_hex  (s_ccolor, 'w', x_base);
      yCOLOR_variant ("CURRENT", x_base, x_hex1);
      DRAW_color_hex (x_hex1);
      strlcpy  (x_hex1 , x_base    , LEN_HEX);
      DRAW_box (x_hex1 , "current" , '1',  0,  5);
      DRAW_box (x_hex1 , "chalk"   , 'b',  4, 10);
      DRAW_box (x_hex1 , "bright"  , 'b',  2, 10);
      DRAW_box (x_hex1 , "balanced", 'b',  0,  8);
      DRAW_box (x_hex1 , "medium"  , 'b',  0,  6);
      DRAW_box (x_hex1 , "strong"  , 'b',  2,  8);
      DRAW_box (x_hex1 , "earthy"  , 's',  4,  7);
      DRAW_box (x_hex1 , "artists" , 's',  1, 10);
      /*---(upper-right)-----------------*/
      yCOLOR_hex  (s_ccolor -  30, 'w', x_base);
      yCOLOR_variant ("CURRENT", x_base, x_hex2);
      DRAW_color_hex (x_hex2);
      strlcpy  (x_hex2 , x_base    , LEN_HEX);
      DRAW_box (x_hex2 , "current" , '2',  8,  5);
      DRAW_box (x_hex2 , "chalk"   , 's', 11, 11);
      DRAW_box (x_hex2 , "bright"  , 's', 11, 10);
      DRAW_box (x_hex2 , "balanced", 's', 11,  9);
      DRAW_box (x_hex2 , "medium"  , 's', 11,  8);
      DRAW_box (x_hex2 , "strong"  , 's', 10, 10);
      DRAW_box (x_hex2 , "earthy"  , 's',  9, 10);
      DRAW_box (x_hex2 , "artists" , 's', 10,  7);
      /*---(lower-left)------------------*/
      yCOLOR_hex  (s_ccolor +  30, 'w', x_base);
      yCOLOR_variant ("CURRENT", x_base, x_hex3);
      DRAW_color_hex (x_hex3);
      strlcpy  (x_hex3 , x_base    , LEN_HEX);
      DRAW_box (x_hex3 , "current" , '3',  0,  0);
      DRAW_box (x_hex3 , "chalk"   , 's',  0,  0);
      DRAW_box (x_hex3 , "bright"  , 's',  1,  0);
      DRAW_box (x_hex3 , "balanced", 's',  2,  0);
      DRAW_box (x_hex3 , "medium"  , 's',  3,  0);
      DRAW_box (x_hex3 , "strong"  , 's',  2,  1);
      DRAW_box (x_hex3 , "earthy"  , 's',  3,  1);
      DRAW_box (x_hex3 , "artists" , 's',  4,  1);
      /*---(lower-right)-----------------*/
      yCOLOR_hex  (s_ccolor + 180, 'w', x_base);
      yCOLOR_variant ("CURRENT", x_base, x_hex4);
      DRAW_color_hex (x_hex4);
      strlcpy  (x_hex4 , x_base    , LEN_HEX);
      DRAW_box (x_hex4 , "current" , '4',  8,  0);
      DRAW_box (x_hex4 , "chalk"   , 's', 10,  1);
      DRAW_box (x_hex4 , "bright"  , 's', 10,  0);
      DRAW_box (x_hex4 , "balanced", 's', 11,  1);
      DRAW_box (x_hex4 , "medium"  , 's', 11,  0);
      DRAW_box (x_hex4 , "strong"  , 's',  9,  2);
      DRAW_box (x_hex4 , "earthy"  , 's',  9,  3);
      DRAW_box (x_hex4 , "artists" , 's',  8,  2);
      /*---(accents)---------------------*/
      /*> DRAW_box (x_hex1 , "current" , 'c',  7,  4);                                <* 
       *> DRAW_box (x_hex2 , "current" , 'c',  6,  4);                                <* 
       *> DRAW_box (x_hex3 , "current" , 'c',  7,  5);                                <* 
       *> DRAW_box (x_hex4 , "current" , 'c',  6,  5);                                <*/
   } glPopMatrix();
   return 0;
}

char
DRAW_main          (void)
{
   /*---(locals)-------------------------*/
   int       x_wide  = 0;
   int       x_tall  = 0;
   /*---(setup view)---------------------*/
   x_wide    = win_w / 2;
   x_tall    = win_h / 2;
   glClear         (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glViewport      ( 0, 0, win_w, win_h);
   glMatrixMode    (GL_PROJECTION);
   glLoadIdentity  ();
   glOrtho         ( 0.0, win_w, -x_tall, x_tall,  -500.0,   500.0);
   glMatrixMode    (GL_MODELVIEW);
   /*---(background)---------------------*/
   DRAW_wheel     ('o');
   DRAW_column    ();
   DRAW_variants  ();
   /*> DRAW_normings  ();                                                             <*/
   /*> DRAW_wheel     ('f');                                                          <*/
   DRAW_scale     ();
   DRAW_layout    ();
   /*---(force the redraw)---------------*/
   glXSwapBuffers(DISP, BASE);
   glFlush();
   /*---(complete)-----------------------*/
   return 0;
}

char        /* PURPOSE : process the xwindows event stream                    */
PROG_event    (void)
{
   /*---(locals)--------------------------------*/
   XKeyEvent *key_event;
   char       the_key[5];
   int        the_bytes;
   char       x_search[100];
   int        loop = 0;
   /*---(event loop)----------------------------*/
   while (1) {
      XNextEvent(DISP, &EVNT);
      /*> printf ("loop %d\n", loop++);                                               <*/
      /*---(start)----------------------------*/
      switch(EVNT.type) {
      case FocusIn:
         break;
      case FocusOut:
         break;
      case Expose:
         break;
      case ConfigureNotify:
         break;
      case KeyPress:
         /*> printf ("key pressed\n");                                                <*/
         key_event  = (XKeyEvent *) &EVNT;
         the_bytes = XLookupString((XKeyEvent *) &EVNT, the_key, 5, NULL, NULL);
         if (the_bytes < 1) break;
         /*> printf ("the key %d\n", the_key [0]);                                    <*/
         /*---(mode changes)-------*/
         switch (the_key[0]) {
         case 'Q' :
            return 1;
            break;
         case '?' :
            if (s_notation == 'y')   s_notation = '-';
            else                     s_notation = 'y';
            break;
         case 'L' :
            s_ccolor   += 60;
            break;
         case 'l' :
            s_ccolor   += 10;
            break;
         case 'h' :
            s_ccolor   -= 10;
            break;
         case 'H' :
            s_ccolor   -= 60;
            break;
         case 'K' :
            s_cvariant +=  5;
            break;
         case 'k' :
            s_cvariant +=  1;
            break;
         case 'j' :
            s_cvariant -=  1;
            break;
         case 'J' :
            s_cvariant -=  5;
            break;
         case '+' :
            s_cnorming +=  1;
            break;
         case '-' :
            s_cnorming -=  1;
            break;
         case '0' :
            s_cset      =  0;
            break;
         case '1' :
            s_cset      =  1;
            break;
         case '2' :
            s_cset      =  2;
            break;
         case '3' :
            s_cset      =  3;
            break;
         case '4' :
            s_cset      =  4;
            break;
         }
         break;

      default:
         break;
      }
      if (s_ccolor   >= 360       )  s_ccolor   -= 360;
      if (s_ccolor   <    0       )  s_ccolor   += 360;
      if (s_cvariant <    0       )  s_cvariant  =   0;
      if (s_cvariant >= s_nvariant)  s_cvariant  =  s_nvariant - 1;
      if (s_cnorming <    0       )  s_cnorming  =   0;
      if (s_cnorming >= s_nnorming)  s_cnorming  =  s_nnorming - 1;
      DRAW_main  ();
      /*> sleep( 1);                                                                  <*/
   }
   /*---(complete)------------------------------*/
   return 0;
}


/*> char       /+=((c_convert))===* return  = simple error code                   +/      <* 
 *> yPALETTE__variant_make   (      /+ PURPOSE = apply a color variation             +/   <* 
 *>       int       a_index,          /+ variation index                          +/      <* 
 *>       char     *a_hex,            /+ rgb three byte hex code        (#rrggbb) +/      <* 
 *>       char     *a_out)            /+ rgb three byte hex code        (#rrggbb) +/      <* 
 *> {                                                                                     <* 
 *>    strncpy(a_out, a_hex, HEXMAX);                                                     <* 
 *>    /+---(defense on a_variation)-----------+/                                         <* 
 *>    if (a_index     >= TABLEMAX)       return -2;                                      <* 
 *>    /+---(get the base)---------------------+/                                         <* 
 *>    int    x_rc = 0;                                                                   <* 
 *>    float  x_hue, x_sat, x_val;                                                        <* 
 *>    x_rc = yPALETTE__hex2hsv(a_hex, &x_hue, &x_sat, &x_val);                           <* 
 *>    if (x_rc != 0) return x_rc;                                                        <* 
 *>    /+---(get the modifiers)----------------+/                                         <* 
 *>    float  dsat  = table_variation[a_index].saturation;                                <* 
 *>    float  dval  = table_variation[a_index].intensity;                                 <* 
 *>    /+---(defense on modifiers)-------------+/                                         <* 
 *>    if (dsat <  0.0 || dsat >  1.0)    return -3;                                      <* 
 *>    if (dval <  0.0 || dval >  1.0)    return -4;                                      <* 
 *>    if (dsat == 0.0 && dval == 0.0)    return  0;  /+ avoid rounding errors    +/      <* 
 *>    /+---(apply the modifiers)--------------+/                                         <* 
 *>    x_rc = yPALETTE__hsv2hex(x_hue, dsat, dval, a_out);                                <* 
 *>    /+---(complete)-------------------------+/                                         <* 
 *>    return x_rc;                                                                       <* 
 *> }                                                                                     <*/


/*> char               /+  return  = nothing                                      +/       <* 
 *> yCOLOR__accents()  /+  PURPOSE = generate base, shadow and accent variations  +/       <* 
 *> {                                                                                      <* 
 *>    printf("colors = ");                                                                <* 
 *>    /+---(defense on my_curr)---------------+/                                          <* 
 *>    tCOLOR *o  = yPALETTE__current();                                                   <* 
 *>    if (o == NULL)                return -1;                                            <* 
 *>    /+---(adjust the main)------------------+/                                          <* 
 *>    char    x_hex[10];                                                                  <* 
 *>    strncpy(x_hex, CURRENT, 10);                                                        <* 
 *>    if (DSAT != 0 || DINT != 0) {           /+ avoid rounding errors in conversion +/   <* 
 *>       yCOLOR__hsv(HUE,                                                                 <* 
 *>             yCOLOR__varcalc(SAT, DSAT),                                                <* 
 *>             yCOLOR__varcalc(VAL, DINT));                                               <* 
 *>    }                                                                                   <* 
 *>    strncpy(VAR0, HEX, 10);                                                             <* 
 *>    printf(" %s", HEX);                                                                 <* 
 *>    /+---(darkest)--------------------------+/                                          <* 
 *>    yCOLOR__hex(VAR0);                                                                  <* 
 *>    yCOLOR__hsv(HUE,                                                                    <* 
 *>          yCOLOR__varcalc(SAT,  1.00 * CS),                                             <* 
 *>          yCOLOR__varcalc(VAL, -0.70 * CS));                                            <* 
 *>    strncpy(VAR1, HEX, 10);                                                             <* 
 *>    printf(" %s", HEX);                                                                 <* 
 *>    /+---(reset and darker)-----------------+/                                          <* 
 *>    yCOLOR__hex(VAR0);                                                                  <* 
 *>    yCOLOR__hsv(HUE,                                                                    <* 
 *>          yCOLOR__varcalc(SAT, -0.50 * CS),                                             <* 
 *>          yCOLOR__varcalc(VAL, -0.50 * CS));                                            <* 
 *>    strncpy(VAR2, HEX, 10);                                                             <* 
 *>    printf(" %s", HEX);                                                                 <* 
 *>    /+---(reset and lighter)----------------+/                                          <* 
 *>    yCOLOR__hex(VAR0);                                                                  <* 
 *>    yCOLOR__hsv(HUE,                                                                    <* 
 *>          yCOLOR__varcalc(SAT, -0.50 * CL),                                             <* 
 *>          yCOLOR__varcalc(VAL,  1.00 * CL));                                            <* 
 *>    strncpy(VAR3, HEX, 10);                                                             <* 
 *>    printf(" %s", HEX);                                                                 <* 
 *>    /+---(reset and lightest)---------------+/                                          <* 
 *>    yCOLOR__hex(VAR0);                                                                  <* 
 *>    yCOLOR__hsv(HUE,                                                                    <* 
 *>          yCOLOR__varcalc(SAT, -0.90 * CL),                                             <* 
 *>          yCOLOR__varcalc(VAL,  1.00 * CL));                                            <* 
 *>    strncpy(VAR4, HEX, 10);                                                             <* 
 *>    printf(" %s", HEX);                                                                 <* 
 *>    /+---(complete)-------------------------+/                                          <* 
 *>    printf(" << done\n");                                                               <* 
 *>    yCOLOR__hex(x_hex);                                                                 <* 
 *>    return 0;                                                                           <* 
 *> }                                                                                      <*/

char
DUMP_scale         ()
{
}

char
PROG_init          ()
{
   int         i           = 0;
   s_ncolor   = 0;
   for (i = 0; i < MAX_COLOR  ; ++i) {
      if (s_RYB      [i][0][0] == '\0')            break;
      ++s_ncolor;
   }
   s_nvariant = 0;
   for (i = 0; i < MAX_VARIANT; ++i) {
      if (s_variants [i].abbr [0] == '\0')            break;
      ++s_nvariant;
   }
   s_nnorming = 0;
   for (i = 0; i < MAX_NORMING; ++i) {
      if (s_normings [i].abbr[0] == '\0') break;
      ++s_nnorming;
   }
   return 0;
}

int
main               (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         rc          = 0;
   int         i           = 0;
   int         j           = 0;
   int         x_deg       = 0;
   /*---(read config)--------------------*/
   if (rc >= 0)  rc = yURG_logger          (argc, argv);
   if (rc >= 0)  rc = PROG_init            ();
   if (rc >= 0)  rc = yURG_urgs            (argc, argv);
   /*> if (rc >= 0)  rc = PROG_args            (argc, argv);                          <*/
   /*> if (rc >= 0)  rc = yFONT__conf_parse    ();                                    <*/
   if (rc <  0) {
      return rc;
   }
   /*> if (argc > 0) {                                                                                                      <* 
    *>    if (strcmp (argv [1], "--big") == 0) {                                                                            <* 
    *>       x_deg       = -120;                                                                                            <* 
    *>       printf ("   /+------------------------------------------------------------------------+/\n");                  <* 
    *>       printf ("   /+  RYB (artists color wheel)  61 total values                            +/\n");                  <* 
    *>       printf ("   /+     30 warm > browns, reds, oranges, yellows                           +/\n");                  <* 
    *>       printf ("   /+     middle  > green                                                    +/\n");                  <* 
    *>       printf ("   /+     30 cool > blues, purples, steels, greys                            +/\n");                  <* 
    *>       printf ("   /+-----------------------------(prefix wheel)-----------------------------+/\n");                  <* 
    *>       for (i = 0; i <  11; ++i) {                                                                                    <* 
    *>          if (i == 2) printf ("   /+-----------------------------(normal wheel)-----------------------------+/\n");   <* 
    *>          if (i == 8) printf ("   /+-----------------------------(suffix wheel)-----------------------------+/\n");   <* 
    *>          printf ("   /+ %04d /+ ", x_deg);                                                                           <* 
    *>          /+> if (x_deg == 180) {                                                      <*                             <* 
    *>           *>    printf ("\"%s\",\n", s_RYB [(i * 6)][4]);                             <*                             <* 
    *>           *>    x_deg += 10;                                                          <*                             <* 
    *>           *>    continue;                                                             <*                             <* 
    *>           *> }                                                                        <+/                            <* 
    *>          for (j = 0; j <   6; ++j) {                                                                                 <* 
    *>             printf ("\"%s\", ", s_RYB [(i * 6) + j][4]);                                                             <* 
    *>             if (x_deg == 180) {                                                                                      <* 
    *>                x_deg -= 50;  break;                                                                                  <* 
    *>             }                                                                                                        <* 
    *>          }                                                                                                           <* 
    *>          x_deg += 60;                                                                                                <* 
    *>          printf ("\n");                                                                                              <* 
    *>       }                                                                                                              <* 
    *>       printf ("   /+---------------------------------(done)---------------------------------+/\n");                  <* 
    *>    } else if (strcmp (argv [1], "--small") == 0) {                                                                   <* 
    *>       x_deg       = 0;                                                                                               <* 
    *>       printf ("   /+------------------------------------------------------------------------+/\n");                  <* 
    *>       printf ("   /+  RYB (artists color wheel)  25 total values                            +/\n");                  <* 
    *>       printf ("   /+     12 low  > reds and oranges                                         +/\n");                  <* 
    *>       printf ("   /+     middle  > yellow                                                   +/\n");                  <* 
    *>       printf ("   /+     12 high > greens and blues                                         +/\n");                  <* 
    *>       printf ("   /+------------------------------------------------------------------------+/\n");                  <* 
    *>       for (i = 2; i <  7; ++i) {                                                                                     <* 
    *>          printf ("   /+ %04d /+ ", x_deg);                                                                           <* 
    *>          for (j = 0; j <   6; ++j) {                                                                                 <* 
    *>             if (x_deg <= 120)  printf ("\"%s\", ", s_RYB [(i * 6) + j][4]);                                          <* 
    *>             if (x_deg >  120)  printf ("\"%s\", ", s_RYB [(i * 6) + j - 5][4]);                                      <* 
    *>             if (x_deg == 120) {                                                                                      <* 
    *>                x_deg -= 50;  break;                                                                                  <* 
    *>             }                                                                                                        <* 
    *>          }                                                                                                           <* 
    *>          x_deg += 60;                                                                                                <* 
    *>          printf ("\n");                                                                                              <* 
    *>       }                                                                                                              <* 
    *>       printf ("   /+---------------------------------(done)---------------------------------+/\n");                  <* 
    *>    }                                                                                                                 <* 
    *> }                                                                                                                    <*/
   yXINIT_start ("yCOLOR_make", win_w, win_h, YX_FOCUSABLE, YX_FIXED, YX_SILENT);
   printf ("past window open\n");
   DRAW_init          ();
   printf ("past draw init\n");
   FONT_load          ();
   printf ("past font load\n");
   DRAW_main          ();
   printf ("past first draw\n");
   /*---(main loop)----------------------*/
   while (rc == 0) {
      rc = PROG_event    ();
   }
   /*---(complete)-----------------------*/
   return rc;
}





