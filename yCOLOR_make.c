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

static int   s_curr     =  0;

int       win_w = 1400;                     /* window width                   */
int       win_h =  600;                     /* window height                  */
int       tex_w = 1400;                     /* texture width                  */
int       tex_h =  600;                     /* texture height                 */

const    double   DEG2RAD   = M_PI / 180.0;

static const char s_RYB [36][5][10] =
{  /*         original    pass 2     pass 1                         */
   /* 000 */ "#ff0000", "#ff0000", "#ff0000", "#ff0000", "#ff0000",
   /* 010 */ "#ff3500", "#ff1700", "#ff1700", "#ff3500", "#ff3500",
   /* 020 */ "#ff5900", "#ff3500", "#ff3500", "#ff5900", "#ff5900",
   /* 030 */ "#ff7400", "#ff4700", "#ff4700", "#ff7400", "#ff7400",
   /* 040 */ "#ff8900", "#ff5900", "#ff5900", "#ff8900", "#ff8900",
   /* 050 */ "#ff9a00", "#ff6700", "#ff6700", "#ff9a00", "#ff9a00",
   /* 060 */ "#ffaa00", "#ff7400", "#ff7400", "#ffaa00", "#ffaa00",
   /* 070 */ "#ffb800", "#ff8b00", "#ff8b00", "#ffb800", "#ffb800",
   /* 080 */ "#ffc600", "#ffa200", "#ffa200", "#ffc600", "#ffc600",
   /* 090 */ "#ffd300", "#ffb900", "#ffb900", "#ffd300", "#ffd300",
   /* 100 */ "#ffe100", "#ffd000", "#ffd000", "#ffe100", "#ffe100",
   /* 110 */ "#ffef00", "#ffe500", "#ffe500", "#ffef00", "#ffef00",
   /* 120 */ "#ffff00", "#ffff00", "#ffff00", "#ffff00", "#ffff00",
   /* 130 */ "#dcf900", "#d2ff00", "#d2ff00", "#dcf900", "#dcf900",
   /* 140 */ "#bdf400", "#a8ff00", "#a8ff00", "#bdf400", "#bdf400",
   /* 150 */ "#9fee00", "#7eff00", "#7eff00", "#9fee00", "#9fee00",
   /* 160 */ "#7ce700", "#54ff00", "#54ff00", "#7ce700", "#7ce700",
   /* 170 */ "#4dde00", "#2aff00", "#2aff00", "#4dde00", "#4dde00",
   /* 180 */ "#00cc00", "#00ff00", "#00ff00", "#00cc00", "#00cc00",
   /* 190 */ "#00b64f", "#00d22a", "#00d22a", "#00b64f", "#00b64f",
   /* 200 */ "#00a876", "#00a854", "#00a854", "#00a876", "#00a876",
   /* 210 */ "#009999", "#00867e", "#00867e", "#009999", "#009999",
   /* 220 */ "#086fa1", "#0064a8", "#0064a8", "#086fa1", "#086fa1",
   /* 230 */ "#0d56a6", "#1532d2", "#0032d2", "#0d56a6", "#0d56a6",
   /* 240 */ "#1240ab", "#2a00ff", "#0000ff", "#1240ab", "#1240ab",
   /* 250 */ "#1729b0", "#2a00e7", "#1500e7", "#1729b0", "#1729b0",
   /* 260 */ "#2618b1", "#2a00d2", "#2a00d2", "#2618b1", "#2618b1",
   /* 270 */ "#3914af", "#3f00bd", "#3f00bd", "#3914af", "#3914af",
   /* 280 */ "#4a11ae", "#5400a8", "#5400a8", "#4a11ae", "#4a11ae",
   /* 290 */ "#5c0dac", "#690093", "#690093", "#5c0dac", "#5c0dac",
   /* 300 */ "#7109aa", "#7e007e", "#7e007e", "#7109aa", "#7109aa",
   /* 310 */ "#8f04a8", "#930069", "#930069", "#8f04a8", "#8f04a8",
   /* 320 */ "#b70094", "#a80054", "#a80054", "#b70094", "#b70094",
   /* 330 */ "#cd0074", "#bd003f", "#bd003f", "#cd0074", "#cd0074",
   /* 340 */ "#dc0055", "#d2002a", "#d2002a", "#dc0055", "#dc0055",
   /* 350 */ "#ec0033", "#e70015", "#e70015", "#ec0033", "#ec0033",
};

/*---(color variations)------------------------------*/
#define    MAX_VARIANT      100
typedef struct cVARIANT tVARIANT;
struct cVARIANT
{
   char        abbr        [10];
   char        name        [35];
   float       nsat;                   /* new saturation for HSV              */
   float       nval;                   /* new value for HSV                   */
   float       cS;
   float       cL;
};
tVARIANT    s_variants  [MAX_VARIANT] = {
   { "no"      , "none"                        ,   0.00,  0.00,  0.50,  0.50 },
   { "--"      , "default"                     ,   1.00,  0.80,  0.50,  0.50 },
   /*---(full sat)--------------------*/
   { "vi"      , "vivid"                       ,   1.00,  1.00,  0.50,  0.50 },
   { "ba"      , "balanced"                    ,   1.00,  0.80,  0.50,  0.50 },
   { "me"      , "medium"                      ,   1.00,  0.65,  0.50,  0.50 },
   { "da"      , "dark"                        ,   1.00,  0.50,  0.50,  0.50 },
   { "ea"      , "earthy"                      ,   1.00,  0.30,  0.50,  0.50 },
   { "ri"      , "rich"                        ,   1.00,  0.15,  0.50,  0.50 },
   { "de"      , "deep"                        ,   1.00,  0.10,  0.50,  0.50 },
   /*---(strong sat)------------------*/
   { "br"      , "bright"                      ,   0.80,  1.00,  0.50,  0.50 },
   { "ar"      , "artists"                     ,   0.80,  0.80,  0.50,  0.50 },
   { "mo"      , "modern"                      ,   0.70,  0.50,  0.50,  0.50 },
   { "ne"      , "neutral"                     ,   0.70,  0.35,  0.50,  0.50 },
   /*---(moderate sat)----------------*/
   { "ch"      , "chalk"                       ,   0.50,  1.00,  0.50,  0.50 },
   { "pa"      , "pastel"                      ,   0.50,  0.90,  0.50,  0.50 },
   { "xp"      , "csd_pastel"                  ,   0.56,  0.87,  0.50,  0.50 },
   { "op"      , "oil_pastel"                  ,   0.50,  0.75,  0.50,  0.50 },
   { "su"      , "subdued"                     ,   0.50,  0.50,  0.50,  0.50 },
   { "co"      , "cool"                        ,   0.50,  0.30,  0.50,  0.50 },
   /*---(low sat)---------------------*/
   { "pl"      , "pale"                        ,   0.30,  1.00,  0.50,  0.50 },
   { "li"      , "light"                       ,   0.30,  0.70,  0.50,  0.50 },
   { "wa"      , "washout"                     ,   0.30,  0.50,  0.50,  0.50 },
   { "gr"      , "greyish"                     ,   0.30,  0.30,  0.50,  0.50 },
   /*---(nominal sat)-----------------*/
   { "wh"      , "whiteish"                    ,   0.15,  1.00,  0.50,  0.50 },
   /*---(complete)--------------------*/
   { ""        , "end of input"                ,   0.00,  0.00,  0.00,  0.00 }
   /*---(older)-----------------------*/
};
int         s_cvariant   = 0;

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
yCOLOR_variant_find  (char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   int         x_index     = 0;
   /*---(search)---------------------------*/
   for (i = 0; i < MAX_VARIANT; ++i) {
      if (s_variants [i].abbr [0] == '\0')            break;
      if (s_variants [i].abbr [0] != a_name [0])      continue;
      if (strcmp (s_variants [i].abbr, a_name) != 0)  continue;
      x_index = i;
      break;
   }
   /*---(complete)-------------------------*/
   return x_index;
}

char       /*=((c_convert))===* return  = simple error code                   */
yCOLOR_variant       (       /* PURPOSE = apply a color variation             */
      int       a_index,          /* variation index                          */
      char     *a_hex,            /* rgb three byte hex code        (#rrggbb) */
      char     *a_out)            /* rgb three byte hex code        (#rrggbb) */
{
   /*---(locals)-----------+-----------+-*/
   float       x_hue       = 0.0;
   float       x_sat       = 0.0;
   float       x_val       = 0.0;
   int         rc          = 0;
   /*---(get the base)---------------------*/
   rc = yCOLOR__hex2hsv (a_hex, &x_hue, &x_sat, &x_val);
   if (rc != 0) return rc;
   /*---(get the modifiers)----------------*/
   x_sat  = s_variants [a_index].nsat;
   x_val  = s_variants [a_index].nval;
   /*---(apply the modifiers)--------------*/
   rc = yCOLOR__hsv2hex (x_hue, x_sat, x_val, a_out);
   /*---(complete)-------------------------*/
   return rc;
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
yCOLOR_hex      (int a_deg, char a_ver, char *a_hex)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =   0;
   /*---(adjust)-------------------------*/
   while (a_deg <  0.0)     a_deg += 360.0;
   while (a_deg >= 360.0)   a_deg -= 360.0;
   /*---(parse color)--------------------*/
   x_deg = a_deg / 10;
   strlcpy (a_hex, s_RYB [x_deg][a_ver], LEN_HEX);
   /*---(complete)-----------------------*/
   return 0;
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
DRAW_color      (int a_deg, char a_ver)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =   0;
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   /*---(adjust)-------------------------*/
   while (a_deg <  0.0)     a_deg += 360.0;
   while (a_deg >= 360.0)   a_deg -= 360.0;
   /*---(parse color)--------------------*/
   x_deg = a_deg / 10;
   x_red = yCOLOR_unhex (s_RYB [x_deg][a_ver][1], s_RYB [x_deg][a_ver][2]);
   x_grn = yCOLOR_unhex (s_RYB [x_deg][a_ver][3], s_RYB [x_deg][a_ver][4]);
   x_blu = yCOLOR_unhex (s_RYB [x_deg][a_ver][5], s_RYB [x_deg][a_ver][6]);
   /*---(set color)----------------------*/
   glColor4f   (x_red, x_grn, x_blu, 1.0f);
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
            DRAW_color   (x_deg, x_set);
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
DRAW_column_three   (void)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =  0;             /* loop iterator -- word          */
   int         x_set       =  0;             /* loop iterator -- word          */
   float       x_wide      = 30.0;
   float       x_inc       =  0.0;
   char        x_text      [LEN_STR];
   x_inc = (win_h - 40) / 36.0;
   for (x_set = 0; x_set <= 1; ++x_set) {
      glPushMatrix(); {
         glTranslatef ( -win_w / 2 + 20 + (x_set * 40), -win_h / 2 + 20,   0.0);
         for (x_deg =  0; x_deg < 360; x_deg += 10) {
            glPushMatrix(); {
               DRAW_color   (x_deg, x_set);
               glBegin         (GL_POLYGON); {
                  glVertex3f  (   0.0, x_inc,     0.0);
                  glVertex3f  (x_wide, x_inc,     0.0);
                  glVertex3f  (x_wide,   0.0,     0.0);
                  glVertex3f  (   0.0,   0.0,     0.0);
               } glEnd   ();
            } glPopMatrix();
            if (x_deg % 30 == 0 && x_set == 1) {
               glPushMatrix(); {
                  sprintf (x_text, "%03d", x_deg);
                  glTranslatef ( 40 ,   0.0,   0.0);
                  yFONT_print  (s_font,   8, YF_BASLEF, x_text);
               } glPopMatrix();
            }
            glTranslatef ( 0.0, x_inc,   0.0);
            /*> if (x_deg == s_curr) {                                                <* 
             *>    glPushMatrix(); {                                                  <* 
             *>       glTranslatef ( 120,   0.0,   0.0);                              <* 
             *>       yFONT_print  (s_font,   8, YF_MIDCEN, "current");               <* 
             *>    } glPopMatrix();                                                   <* 
             *> }                                                                     <*/
         }
      } glPopMatrix();
   }
}

char
DRAW_wheel          (void)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =  0;             /* loop iterator -- word          */
   float       x           =  0.0;
   float       y           =  0.0;
   float       r1          =  0.0;
   float       r2          =  0.0;
   float       x_inc       = 80.0;
   char        x_text      [LEN_STR];
   glPushMatrix(); {
      glTranslatef ( 380,   0.0,   0.0);
      for (x_deg = 0; x_deg < 360; x_deg += 10) {
         glPushMatrix(); {
            glRotatef    (x_deg + 90, 0.0f, 0.0f, 1.0f);
            DRAW_color   (x_deg, 0);
            r1  = win_h / 4.0;
            r2  = r1 + x_inc;
            glBegin         (GL_POLYGON); {
               glVertex3f  (r1,  r1 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r2,  r2 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r2, -r2 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r1, -r1 * sin (5.5 * DEG2RAD),     0.0);
            } glEnd   ();
            if (x_deg % 30 == 0) {
               glPushMatrix(); {
                  sprintf (x_text, "%03d", x_deg);
                  glTranslatef ( 240,   0.0,   0.0);
                  yFONT_print  (s_font,   8, YF_MIDCEN, x_text);
               } glPopMatrix();
            }
            if (x_deg == s_curr) {
               glPushMatrix(); {
                  glTranslatef ( 120,   0.0,   0.0);
                  yFONT_print  (s_font,   8, YF_MIDCEN, "current");
               } glPopMatrix();
            }
         } glPopMatrix();
      }
   } glPopMatrix();
   return 0;
}

char
DRAW_wheel_three    (void)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =  0;             /* loop iterator -- word          */
   float       x           =  0.0;
   float       y           =  0.0;
   float       r1          =  0.0;
   float       r2          =  0.0;
   float       x_inc       = 35.0;
   char        x_text      [LEN_STR];
   glPushMatrix(); {
      glTranslatef ( -50,   0.0,   0.0);
      for (x_deg = 0; x_deg < 360; x_deg += 10) {
         glPushMatrix(); {
            glRotatef    (x_deg + 90, 0.0f, 0.0f, 1.0f);
            DRAW_color   (x_deg, 0);
            r1  = win_h / 5.0;
            r2  = r1 + x_inc;
            glBegin         (GL_POLYGON); {
               glVertex3f  (r1,  r1 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r2,  r2 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r2, -r2 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r1, -r1 * sin (5.5 * DEG2RAD),     0.0);
            } glEnd   ();
            DRAW_color   (x_deg, 1);
            r1  = r2 + 5;
            r2  = r1 + x_inc;
            glBegin         (GL_POLYGON); {
               glVertex3f  (r1,  r1 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r2,  r2 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r2, -r2 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r1, -r1 * sin (5.5 * DEG2RAD),     0.0);
            } glEnd   ();
            DRAW_color   (x_deg, 2);
            r1  = r2 + 5;
            r2  = r1 + x_inc;
            glBegin         (GL_POLYGON); {
               glVertex3f  (r1,  r1 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r2,  r2 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r2, -r2 * sin (5.5 * DEG2RAD),     0.0);
               glVertex3f  (r1, -r1 * sin (5.5 * DEG2RAD),     0.0);
            } glEnd   ();
            if (x_deg % 30 == 0) {
               glPushMatrix(); {
                  sprintf (x_text, "%03d", x_deg);
                  glTranslatef ( 240,   0.0,   0.0);
                  yFONT_print  (s_font,   8, YF_MIDCEN, x_text);
               } glPopMatrix();
            }
            if (x_deg == s_curr) {
               glPushMatrix(); {
                  glTranslatef ( 120,   0.0,   0.0);
                  yFONT_print  (s_font,   8, YF_MIDCEN, "current");
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
   yCOLOR_hex  (s_curr, 0, x_base);
   glPushMatrix(); {
      glTranslatef ( 650 , -win_h / 2 - 15,   0.0);
      for (i = 0; i < MAX_VARIANT; ++i) {
         if (s_variants [i].abbr[0] == '\0') break;
         yCOLOR_variant (i, x_base, x_hex);
         DRAW_color_hex (x_hex);
         glBegin         (GL_POLYGON); {
            glVertex3f  (    0.0,  25.0,     0.0);
            glVertex3f  (   80.0,  25.0,     0.0);
            glVertex3f  (   80.0,   0.0,     0.0);
            glVertex3f  (    0.0,   0.0,     0.0);
         } glEnd   ();
         glPushMatrix(); {
            glColor4f   (  0.0,   0.0,   0.0, 1.0f);
            glTranslatef (40.0,  10.0,   5.0);
            yFONT_print  (s_font,   8, YF_MIDCEN, x_hex);
            glTranslatef ( 0.0,  10.0,   5.0);
            yFONT_print  (s_font,   8, YF_MIDCEN, s_variants [i].name);
         } glPopMatrix();
         glTranslatef (   0,  25.0,   0.0);
      }
   } glPopMatrix();
   return 0;
}

char
DRAW_one            (void)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =  0;             /* loop iterator -- word          */
   float       x           =  0.0;
   float       y           =  0.0;
   float       x_inc       = 80.0;
   char        x_text      [LEN_STR];
   int         x_set       =  0;             /* loop iterator -- word          */
   glPushMatrix(); {
      glTranslatef ( 800 , -win_h / 2 + 20,   0.0);
      DRAW_color   ( s_curr, 0);
      glBegin         (GL_POLYGON); {
         glVertex3f  (    0.0, 550.0,     0.0);
         glVertex3f  (  550.0, 550.0,     0.0);
         glVertex3f  (  550.0,   0.0,     0.0);
         glVertex3f  (    0.0,   0.0,     0.0);
      } glEnd   ();
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
   DRAW_wheel     ();
   DRAW_column    ();
   DRAW_variants  ();
   DRAW_one       ();
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
         case 'L' :
            s_curr += 60;
            break;
         case 'l' :
            s_curr += 10;
            break;
         case 'h' :
            s_curr -= 10;
            break;
         case 'H' :
            s_curr -= 60;
            break;
         }
         break;

      default:
         break;
      }
      if (s_curr >= 360)  s_curr -= 360;
      if (s_curr <    0)  s_curr += 360;
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

int
main               (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         rc          = 0;
   /*---(read config)--------------------*/
   /*> if (argc > 0) {                                                                <* 
    *>    rc = yCOLOR_variant_find (argv [1]);                                        <* 
    *>    printf ("%2d = %s = %s\n", rc, argv [1], s_variants [rc].name);             <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   yXINIT_start ("yCOLOR_make", win_w, win_h, YX_FOCUSABLE, YX_FIXED, YX_SILENT);
   DRAW_init          ();
   FONT_load          ();
   DRAW_main          ();
   /*---(main loop)----------------------*/
   while (rc == 0) {
      rc = PROG_event    ();
   }
   /*---(complete)-----------------------*/
   return rc;
}




/*============================----end-of-source---============================*/
