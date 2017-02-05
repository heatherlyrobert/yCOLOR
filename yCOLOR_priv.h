/*============================----beg-of-source---============================*/
#include "yCOLOR.h"



/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef     yCOLOR_priv
#define     yCOLOR_priv    loaded



/* rapidly evolving version number to aid with visual change confirmation     */
#define     YFONT_VER_NUM   "1.0c"
#define     YFONT_VER_TXT   "fixed yCOLOR_variant to take text name"



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








/*============================--------------------============================*/
/*===----                       beginning of file                      ----===*/
/*============================--------------------============================*/




/*----------------------------------------------------------------------------*/
/*-------                           constants                          -------*/
/*----------------------------------------------------------------------------*/
/*---(palette)------------------*/
#define  DOMINANT_HEX    o->dom_hex
#define  DOMINANT_HUE    o->dom_hue
/*---(table indexes)------------*/
#define  SCHEME_ID       o->scheme_id
#define  COMP_ID         o->complement_id
#define  VARIANT_ID      o->variation_id
#define  NORMING_ID      o->norming_id
#define  MOTHERING_ID    o->mothering_id
#define  ACCENTING_ID    o->accenting_id
/*---(current)------------------*/
#define  POSITION        o->position
#define  ACCENT          o->accent
#define  ANGLE           o->angle
#define  WELL            o->well
/*---(modified color)-----------*/
#define  BASE            o->base
#define  VARIANT         o->variant
#define  NORMED          o->normed
#define  MOTHERED        o->mothered
#define  MIXED           o->mixed
#define  ACCENTED        o->accented

#define  MOTHER          o->mother

/*---(main)---------------------*/
#define  HEX         o->hex
#define  CURRENT     o->current
/*---(ryb bytes)----------------*/
#define  RED_BYTE    o->r
#define  GRN_BYTE    o->g
#define  BLU_BYTE    o->b
/*---(ryb integers)-------------*/
#define  RED         o->rp
#define  GRN         o->gp
#define  BLU         o->bp
/*---(HSV integers)-------------*/
#define  HUE         o->h
#define  SAT         o->s
#define  VAL         o->v
/*---(HSL integers)-------------*/
#define  HSL_HUE     o->hsl_h
#define  HSL_SAT     o->hsl_s
#define  HSL_LIG     o->hsl_l
/*---(flags/states)-------------*/
#define  COMP        o->complement
#define  CIRCLE      o->circle

#define  DSAT        o->saturation
#define  DINT        o->intensity
#define  CS          o->cS
#define  CL          o->cL
#define  NORMING     o->norming
/*---(accents)------------------*/
#define  VAR0        o->var[0]
#define  VAR1        o->var[1]
#define  VAR2        o->var[2]
#define  VAR3        o->var[3]
#define  VAR4        o->var[4]
#define  VAR5        o->var[5]
#define  VAR6        o->var[6]
#define  VAR7        o->var[7]
#define  VAR8        o->var[8]
#define  VAR9        o->var[9]
#define  VARA        o->var[10]
#define  VARB        o->var[11]
#define  VARC        o->var[12]
#define  VARD        o->var[13]
#define  VARE        o->var[14]
#define  VARF        o->var[15]

#define  HEXMAX     8

#define  GEN_HEX     gen_hex
char  gen_hex [HEXMAX];


typedef struct  cCOLR  tCOLR;
struct cCOLR  {
   char        hex         [LEN_HEX];
   float       red;
   float       grn;
   float       blu;
};


typedef struct cCOLOR  tCOLOR;
struct cCOLOR
{
   /*---(unique id)---------------*/
   int       iden;                  /* color identifier                       */
   /*---(dominant)----------------*/
   char      dom_hex  [HEXMAX];   /* dominant/primary color of palette        */
   int       dom_hue;             /* dominant/primary RYB hue angle           */
   char      mother   [HEXMAX];   /* variant/normed color for mothering       */
   /*---(settings)----------------*/
   int       variation_id;        /* color variant, such as pastel, cool, ... */
   int       norming_id;          /* cross color intensity norming option     */
   int       scheme_id;           /* color scheme index                       */
   int       complement_id;       /* color scheme complement index            */
   int       mothering_id;        /* cross color mixing                       */
   int       accenting_id;        /* option to create color accents           */
   /*---(current)-----------------*/
   int       position;            /* sequence number of current color         */
   int       accent;              /* sequence number of accent color          */
   int       angle;
   int       well;
   /*---(modified)----------------*/
   char      base     [HEXMAX];   /* current color in the scheme              */
   char      variant  [HEXMAX];   /* after applying color variation           */
   char      normed   [HEXMAX];   /* after applying color norming             */
   char      mothered [HEXMAX];   /* after applying color mothering           */
   char      mixed    [HEXMAX];   /* final color for use                      */
   char      accented [HEXMAX];   /* particular accent                        */



   char      is_ryb;              /* is it an RYB scheme                      */
   /*---(working area)------------*/
   int       curr;                /* number of the current color in scheme    */
   char      current [HEXMAX];    /* rgb hexadecimal representation as text   */
   /*---(color information)-------*/
   char      hex[HEXMAX];         /* rgb hexadecimal representation as text   */
   uchar     r, g, b;             /* red, green, and blue as 0-255            */
   double    rp, gp, bp;          /* red, green, and blue as pecentages       */
   float     h, s, v;             /* HSV : hue, saturation, and value         */
   double    hsl_h, hsl_s, hsl_l; /* HSL : hue, saturation, and lightness     */
   /*---(artists wheel)-----------*/
   int       ryb_hue;             /* RYB angle                                */
   double    rr, yy, bb;          /* RYB : components                         */
   double    ryb_h, ryb_s, ryb_v; /* RYB : hsv calculation                    */
   double    ryb_hh;              /* RYB : inferred hue                       */
   /*---(scheme information)------*/
   int       scheme;              /* color scheme index                       */
   int       complement;          /* color scheme complement index            */
   char      circle;              /* circle type                              */
   int       variation;           /* method to create accents                 */
   int       mothering;           /* method to create accents                 */
   int       norming;             /* norming factor for intensity             */
   int       accenting;           /* color adjustments, like pastel or dark   */
   double    saturation;          /* saturation delta/change                  */
   double    intensity;           /* intensity delta/change                   */
   double    cS;                  /* shadow change/adjustment (darker)        */
   double    cL;                  /* light  change/adjustment (brighter)      */
   /*---(variants)----------------*/
   char      var[16][HEXMAX];     /* color variants                           */
   char      grey[HEXMAX];        /* greyscale equivalent                     */
   char      web[HEXMAX];         /* websafe equivalent                       */
   char      css[5];              /* css hex equivalent                       */
   /*---(to take out)-------------*/
   long      its_grey;
   /*---(linked list)-------------*/
   tCOLOR   *next;                /* next color                               */
   tCOLOR   *prev;                /* prev color                               */
};


#endif
/*----------------------------------------------------------------------------*/
/*--------------------------------end-of-file---------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*---------------------------beginning-of-file--------------------------------*/
/*----------------------------------------------------------------------------*/

#ifndef  yCOLOR_table
#define  yCOLOR_table yes



/*============================--------------------============================*/
/*===----                         lookup tables                        ----===*/
/*============================--------------------============================*/
/* NOTES...
 *    - all tables defined as "const" so as to be shared, single copy, non-data
 *    - have defined all tables as the same length to avoid difficulties
 *    - even the structures are similar to make searching more generic
 *    - first entry should always be default (0 is not set)
 *    - last entry should always be "eoi" or end-of-input to signal end
 */

/*---(max size of table)-----------------------------*/
#define  TABLEMAX    50

/*---(color entry methods)---------------------------*/
struct cENTRY
{
   char   abbr[8];
   char   name[50];
};
typedef struct cENTRY tENTRY;
extern  const  tENTRY table_entry[TABLEMAX];
extern  tENTRY *my_entry;

/*---(color variations)------------------------------*/
struct cVARIATION
{
   char   abbr[10];
   char   name[35];
   float  saturation;
   float  intensity;
   float  cS;
   float  cL;
};
typedef struct cVARIATION tVARIATION;
extern  const  tVARIATION table_variation[TABLEMAX];
extern  tVARIATION *my_variation;

/*---(color norming methods)-------------------------*/
struct cNORMING
{
   char   abbr[8];
   char   name[35];
   double red;
   double grn;
   double blu;
   char   is_value;
};
typedef struct cNORMING tNORMING;
extern  const  tNORMING table_norming[TABLEMAX];
extern  tNORMING *my_norming;

/*---(color scheme options)--------------------------*/
struct cSCHEME
{
   char   abbr[8];
   char   name[35];
   short  count;
   char   comp;
   char   circle;
   short  angle[20];
};
typedef struct cSCHEME tSCHEME;
extern  const  tSCHEME table_scheme[TABLEMAX];
extern  tSCHEME *my_scheme;

/*---(color complement options)----------------------*/
struct cCOMP
{
   char   abbr[8];
   char   name[50];
   short  count;
   short  angle[20];
};
typedef struct cCOMP tCOMP;
extern  const  tCOMP table_comp[TABLEMAX];
extern  tCOMP *my_comp;

/*---(color mothering methods)-----------------------*/
struct cMOTHER
{
   char   abbr[8];
   char   name[35];
   double value;
   char   style;
};
typedef struct cMOTHER tMOTHER;
extern  const  tMOTHER table_mother[TABLEMAX];
extern  tMOTHER *my_mother;

/*---(color accenting options)-----------------------*/
struct cACCENT
{
   char   abbr[8];
   int    count;
   char   name[35];
};
typedef struct cACCENT tACCENT;
extern  const tACCENT table_accent[TABLEMAX];
extern  tACCENT *my_accent;

/*---(color variations)------------------------------*/
struct cCONTRAST
{
   char   abbr[10];
   char   name[35];
   double saturation;
   double intensity;
   double cS;
   double cL;
};
typedef struct cCONTRAST tCONTRAST;
extern  const tCONTRAST table_contrast[TABLEMAX];
extern  tCONTRAST *my_contrast;

#endif

/*----------------------------------------------------------------------------*/
/*--------------------------------end-of-file---------------------------------*/
/*----------------------------------------------------------------------------*/


/*============================--------------------============================*/
/*===----                      private prototypes                      ----===*/
/*============================--------------------============================*/
/* NOTES...
 *    - these are functions that are not accessable outside this source file
 *    - all should be named with a "<file>__<function>" format
 */

#ifndef  yPALETTE_proto
#define  yPALETTE_proto yes

#include "yPALETTE_color.h"

tCOLOR*       yPALETTE__current   (void);
/*---(setters)-------------------*/
char          yCOLOR__hex         (char   *a_hex);
char          yCOLOR__rgb         (uchar   a_red, uchar  a_grn, uchar  a_blu);
char          yCOLOR__hsv         (double  a_hue, double a_sat, double a_val);
char          yCOLOR__hsl         (double  a_hue, double a_sat, double a_lig);
char          yCOLOR__dominant    (void);
char          yCOLOR__run         (void);
char          yCOLOR__complement  (char   *a_scheme);
/*---(drivers)-------------------*/
char          yCOLOR_variant      (int     a_variation, char   *a_hex, char   *a_out);
char          yCOLOR__mother      (int   a_style, long a_mother, long  a_base, long *a_mixed);
char          yCOLOR__norming     (void);
/*---(internal utils)------------*/
double        yCOLOR__min3        (double a_one, double a_two, double a_three);
double        yCOLOR__max3        (double a_one, double a_two, double a_three);
int           yCOLOR__dehex       (char   a_ch);
uchar         yCOLOR__webhex      (uchar  a_hex);
uchar         yCOLOR__csshex      (uchar  a_hex);
/*---(internal convertors)-------*/
char          yCOLOR_ryb_hex      (int a_deg, char *a_hex);
/*---(HSV conversions)-----------*/
char          yPALETTE__hsv2hex   (float    a_hue, float    a_sat, float   a_val, char   *a_hex);
char          yPALETTE__hex2hsv   (char    *a_hex, float   *a_hue, float  *a_sat, float  *a_val);
char          yPALETTE__hex2norm  (char    *a_hex, float   *a_red, float  *a_grn, float  *a_blu);
char          yPALETTE__hex2byte  (char    *a_hex, uchar   *a_red, uchar  *a_grn, uchar  *a_blu);
char          yPALETTE__norm2hex  (float    a_red, float    a_grn, float   a_blu, char   *a_hex);
char          yPALETTE__byte2hex  (uchar    a_red, uchar    a_grn, uchar   a_blu, char   *a_hex);
char          yPALETTE__hsv2int   (float    a_hue, float    a_sat, float   a_val, long   *a_rgb);
char          yPALETTE__int2hsv   (long     a_rgb, float   *a_hue, float  *a_sat, float  *a_val);
/*---(HEX conversions)-----------*/
char          yPALETTE__hex2int   (char    *a_hex, long    *a_rgb);
char          yPALETTE__int2hex   (long     a_rgb, char    *a_hex);
/*---(RGB conversions)-----------*/
char          yCOLOR__rgb2int     (float    a_red, float    a_grn,  float  a_blu, long   *a_rgb);
char          yCOLOR__chr2int     (uchar    a_red, uchar    a_grn,  uchar  a_blu, long   *a_rgb);
/*---(other conversions)---------*/
char          yCOLOR__int2grey    (long     a_rgb, long    *a_grey);
/*---(ACCESSORS)-----------------*/
float         R_FLOAT             (long     a_rgb);
float         G_FLOAT             (long     a_rgb);
float         B_FLOAT             (long     a_rgb);
uchar         R_BYTE              (char    *a_hex);
uchar         G_BYTE              (char    *a_hex);
uchar         B_BYTE              (char    *a_hex);
/*---(convert from int)----------*/
int           yCOLOR__hsv2rgb     (void *a_color);
int           yCOLOR__rgb2hsv     (void *a_color);
int           yCOLOR__hsv2hsl     (void *a_color);
int           yCOLOR__hsl2hsv     (void *a_color);
int           yCOLOR__rgb2ryb     (void *a_color);
int           yCOLOR__ryb2hsv     (void *a_color);
int           yCOLOR__greyscale   (void *a_color);
int           yCOLOR__websafe     (void *a_color);
int           yCOLOR__css         (void *a_color);
int           yCOLOR__rybindex    (int a_index);
int           yCOLOR__loadryb     (void);
/*---(unit testing)--------------*/
char*         yPALETTE__getter    (char *a_question);
/*---(scheme generation)---------*/
char          yCOLOR__accents     (void);
char          yCOLOR__descending  (void);
void          yCOLOR__reduction   (char  a_extended);
char*         yCOLOR__line        (float a_hue, char a_variant, int a_count, char a_format);
char          yCOLOR__html        (int   a_count, char a_format);
char          yCOLOR__stdout      (void);



#endif
/*============================----end-of-source---============================*/
