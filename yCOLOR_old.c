/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"

#define  HEXMAX     8




/*============================--------------------============================*/
/*===----                       beginning of file                      ----===*/
/*============================--------------------============================*/
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

/*> void          yCOLOR_help      (void);                                            <*/

/*> void          yCOLOR__varsetup (int);                                             <*/





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


/*----------------------------------------------------------------------------*/
/*--------------------------------end-of-file---------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*---------------------------beginning-of-file--------------------------------*/
/*----------------------------------------------------------------------------*/




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





#ifdef NORMAL
int
main (int argc, char *argv[])
{
   long x_col = -1;
   int  x_red, x_grn, x_blu;
   float x_hue, x_sat, x_val;
   /*---(try HEX)---------------------*/
   yPALETTE__hex2int("#ffff00", &x_col);
   x_red = x_col / (256 * 256);
   x_grn = (x_col / 256) % 256;
   x_blu = x_col % 256;
   printf("color %10ld = #%06lx, red = %3d, grn = %3d, blu = %3d\n",
         x_col, x_col, x_red, x_grn, x_blu);
   printf("RED = %4.2f or %3d\n", R_FLOAT(x_col), R_BYTE(x_col));
   printf("GRN = %4.2f or %3d\n", G_FLOAT(x_col), G_BYTE(x_col));
   printf("BLU = %4.2f or %3d\n", B_FLOAT(x_col), B_BYTE(x_col));
   yPALETTE__int2hsv(x_col, &x_hue, &x_sat, &x_val);
   printf("back to HSV :: hue = %3.0f, sat = %4.2f, val = %4.2f\n", x_hue, x_sat, x_val);
   /*---(try HSV)---------------------*/
   yPALETTE__hsv2int( 60.0, 1.0, 1.0, &x_col);
   x_red = x_col / (256 * 256);
   x_grn = (x_col / 256) % 256;
   x_blu = x_col % 256;
   printf("color %10ld = #%06lx, red = %3d, grn = %3d, blu = %3d\n",
         x_col, x_col, x_red, x_grn, x_blu);
   printf("RED = %4.2f or %3d\n", R_FLOAT(x_col), R_BYTE(x_col));
   printf("GRN = %4.2f or %3d\n", G_FLOAT(x_col), G_BYTE(x_col));
   printf("BLU = %4.2f or %3d\n", B_FLOAT(x_col), B_BYTE(x_col));
   yPALETTE__int2hsv(x_col, &x_hue, &x_sat, &x_val);
   printf("back to HSV :: hue = %3.0f, sat = %4.2f, val = %4.2f\n", x_hue, x_sat, x_val);
   /*---(try RGB)---------------------*/
   yCOLOR__rgb2int(  1.0, 1.0, 0.0, &x_col);
   x_red = x_col / (256 * 256);
   x_grn = (x_col / 256) % 256;
   x_blu = x_col % 256;
   printf("color %10ld = #%06lx, red = %3d, grn = %3d, blu = %3d\n",
         x_col, x_col, x_red, x_grn, x_blu);
   printf("RED = %4.2f or %3d\n", R_FLOAT(x_col), R_BYTE(x_col));
   printf("GRN = %4.2f or %3d\n", G_FLOAT(x_col), G_BYTE(x_col));
   printf("BLU = %4.2f or %3d\n", B_FLOAT(x_col), B_BYTE(x_col));
   yPALETTE__int2hsv(x_col, &x_hue, &x_sat, &x_val);
   printf("back to HSV :: hue = %3.0f, sat = %4.2f, val = %4.2f\n", x_hue, x_sat, x_val);
   /*---(try CHR)---------------------*/
   yCOLOR__chr2int(  255,   0,   0, &x_col);
   x_red = x_col / (256 * 256);
   x_grn = (x_col / 256) % 256;
   x_blu = x_col % 256;
   printf("color %10ld = #%06lx, red = %3d, grn = %3d, blu = %3d\n",
         x_col, x_col, x_red, x_grn, x_blu);
   printf("RED = %4.2f or %3d\n", R_FLOAT(x_col), R_BYTE(x_col));
   printf("GRN = %4.2f or %3d\n", G_FLOAT(x_col), G_BYTE(x_col));
   printf("BLU = %4.2f or %3d\n", B_FLOAT(x_col), B_BYTE(x_col));
   yPALETTE__int2hsv(x_col, &x_hue, &x_sat, &x_val);
   printf("new dominant is %ld\n", DOMINANT_HEX);
   printf("back to HSV :: hue = %3.0f, sat = %4.2f, val = %4.2f\n", x_hue, x_sat, x_val);
   /*---(try CHR)---------------------*/
   yCOLOR__chr2int(    0, 127, 127, &x_col);
   x_red = x_col / (256 * 256);
   x_grn = (x_col / 256) % 256;
   x_blu = x_col % 256;
   printf("color %10ld = #%06lx, red = %3d, grn = %3d, blu = %3d\n",
         x_col, x_col, x_red, x_grn, x_blu);
   printf("RED = %4.2f or %3d\n", R_FLOAT(x_col), R_BYTE(x_col));
   printf("GRN = %4.2f or %3d\n", G_FLOAT(x_col), G_BYTE(x_col));
   printf("BLU = %4.2f or %3d\n", B_FLOAT(x_col), B_BYTE(x_col));
   yPALETTE__int2hsv(x_col, &x_hue, &x_sat, &x_val);
   printf("back to HSV :: hue = %3.0f, sat = %4.2f, val = %4.2f\n", x_hue, x_sat, x_val);
   /*---(try CHR)---------------------*/
   yCOLOR__rgb2int( 0.25,0.25, 0.0, &x_col);
   x_red = x_col / (256 * 256);
   x_grn = (x_col / 256) % 256;
   x_blu = x_col % 256;
   printf("color %10ld = #%06lx, red = %3d, grn = %3d, blu = %3d\n",
         x_col, x_col, x_red, x_grn, x_blu);
   printf("RED = %4.2f or %3d\n", R_FLOAT(x_col), R_BYTE(x_col));
   printf("GRN = %4.2f or %3d\n", G_FLOAT(x_col), G_BYTE(x_col));
   printf("BLU = %4.2f or %3d\n", B_FLOAT(x_col), B_BYTE(x_col));
   yPALETTE__int2hsv(x_col, &x_hue, &x_sat, &x_val);
   printf("back to HSV :: hue = %3.0f, sat = %4.2f, val = %4.2f\n", x_hue, x_sat, x_val);
   /*---(complete)--------------------*/
   yCOLOR_help();
   return 0;
}
#endif






/*----------------------------------------------------------------------------*/
/*-------                      color variants                          -------*/
/*----------------------------------------------------------------------------*/
/*
 * THE FOLLOWING ONLY APPLIES TO THE FOLLOWING THREE (3) FUNCTIONS
 *    - yCOLOR__varsetup()
 *    - yCOLOR__varcalc()
 *    - yCOLOR__variants()
 *
 * Color.js library
 *
 *  Copyright (c) 2002-2009, Petr Stanicek, pixy@pixy.cz ("the author")
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Any commercial use of this software is not allowed unless an exemption
 *     was granted by the author.
 *
 *  This software is provided by the author "as is" and any express or implied
 *  warranties, including, but not limited to, the implied warranties or
 *  merchantability and fitness for a particular purpose are disclaimed.
 *  In no event shall the author be liable for any direct, indirect, incidental,
 *  special, exemplary, or consequential damages (including, but not limited to,
 *  procurement of substitute goods or services; loss of use, data, or profits;
 *  or business interruption) however caused and on any theory of liability,
 *  whether in contract, strict liability, or tort (including negligence or
 *  otherwise) arising in any way out of the use of this software, even if
 *  advised of the possibility of such damage.
 *
 */


enum yCOLOR_variants
{
   /*  0 */ NORMAL,          MED,
   /*  2 */ DARK,             DARKER,           DARKEST,
   /*  5 */ CONTRAST_MAX,    CONTRAST_HIGH,    CONTRAST_MORE,
   /*  8 */ CONTRAST_LESS,   CONTRAST_LOW,     CONTRAST_MIN,
   /* 11 */ PASTEL,          PASTEL_DARK,      PASTEL_DARKER,    PASTEL_DARKEST,
   /* 15 */ PALE,            PALE_DARK,        PALE_DARKER,      PALE_DARKEST,
   /* 19 */ GREYISH_LIGHT,   GREYISH_MEDIUM,   GREYISH_DARK,
   /* 22 */ GREYACC_LIGHT,   GREYACC_MEDIUM,   GREYACC_DARK,
   /* 25 */ SAT_LESS,        SAT_LOW,          SAT_MIN,
};

void               /* return  = nothing                                       */
yCOLOR__varsetup(  /* PURPOSE = set parameters driving shadow and accents     */
      int   a_variation)          /* particular accenting scheme              */
{
   /*> tCOLOR *o  = my_curr;                                                          <*/
   /*> VARIATION  = a_variation;                                                        <* 
    *> switch (VARIATION) {                                                             <* 
    *> case MED            : DS =  0.500; DV = -0.220; CS =  0.60; CL =  0.60; break;   <* 
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
    *> case SAT_MIN        : DS = -1.000; DV =  0.000; CS =  0.50; CL =  0.50; break;   <* 
    *>                       /+---(default)------------------+/                         <* 
    *> default             :                                                            <* 
    *> case NORMAL         : DS =  0.000; DV =  0.000; CS =  0.50; CL =  0.50; break;   <* 
    *> }                                                                                <*/
   return;
}

double             /* return  = adjusted color delta                          */
yCOLOR__varcalc(   /* PURPOSE = calculate the proper adjusted sat/val         */
      double x,                   /* base SAT/VAR number                      */
      double d)                   /* delta                                    */
{
   if (d <= 0)    return x * (d + 1);
   else           return x + ((1 - x) * d);
}

char               /*  return  = nothing                                      */
yCOLOR__accents()  /*  PURPOSE = generate base, shadow and accent variations  */
{
   printf("colors = ");
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   /*---(adjust the main)------------------*/
   char    x_hex[10];
   if (DSAT != 0 || DINT != 0) {           /* avoid rounding errors in conversion */
      yCOLOR__hsv(HUE,
            yCOLOR__varcalc(SAT, DSAT),
            yCOLOR__varcalc(VAL, DINT));
   }
   strncpy(VAR0, HEX, 10);
   printf(" %s", HEX);
   /*---(darkest)--------------------------*/
   yCOLOR__hex(VAR0);
   yCOLOR__hsv(HUE,
         yCOLOR__varcalc(SAT,  1.00 * CS),
         yCOLOR__varcalc(VAL, -0.70 * CS));
   strncpy(VAR1, HEX, 10);
   printf(" %s", HEX);
   /*---(reset and darker)-----------------*/
   yCOLOR__hex(VAR0);
   yCOLOR__hsv(HUE,
         yCOLOR__varcalc(SAT, -0.50 * CS),
         yCOLOR__varcalc(VAL, -0.50 * CS));
   strncpy(VAR2, HEX, 10);
   printf(" %s", HEX);
   /*---(reset and lighter)----------------*/
   yCOLOR__hex(VAR0);
   yCOLOR__hsv(HUE,
         yCOLOR__varcalc(SAT, -0.50 * CL),
         yCOLOR__varcalc(VAL,  1.00 * CL));
   strncpy(VAR3, HEX, 10);
   printf(" %s", HEX);
   /*---(reset and lightest)---------------*/
   yCOLOR__hex(VAR0);
   yCOLOR__hsv(HUE,
         yCOLOR__varcalc(SAT, -0.90 * CL),
         yCOLOR__varcalc(VAL,  1.00 * CL));
   strncpy(VAR4, HEX, 10);
   printf(" %s", HEX);
   /*---(complete)-------------------------*/
   printf(" << done\n");
   yCOLOR__hex(x_hex);
   return 0;
}

/*-----------------------------end-of-copyright-------------------------------*/

void               /*  return  = none                                         */
yCOLOR__ascending()/*  PURPOSE = generate an ascending monochrome variant set */
{
   /*---(get the current color)------------*/
   tCOLOR *o  = yPALETTE__current();
   yCOLOR__varsetup(VARIANT_ID);
   char    x_hex[10], x_orig[10];
   /*---(save the main)--------------------*/
   strncpy(x_hex, HEX, 10);
   /*---(adjust the main)------------------*/
   /*> yCOLOR__hsv(o, HUE, SAT * 1.000, VAL * 0.800);                                 <*/
   if (DSAT != 0 || DINT != 0) {           /* avoid rounding errors in conversion */
      yCOLOR__hsv(HUE, yCOLOR__varcalc(SAT, DSAT), yCOLOR__varcalc(VAL, DINT));
   }
   strncpy(x_orig, HEX, 10);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 1.000, VAL * 0.200);
   strncpy(VAR0, HEX, 10);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 1.000, VAL * 0.500);
   strncpy(VAR1, HEX, 10);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 1.000, VAL * 0.750);
   strncpy(VAR2, HEX, 10);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 0.800, VAL * 0.900);
   strncpy(VAR3, HEX, 10);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 0.500, VAL * 1.000);
   strncpy(VAR4, HEX, 10);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 0.150, VAL * 1.000);
   strncpy(VAR5, HEX, 10);
   /*---(complete)-------------------------*/
   return;
}

char               /*  return  = none                                         */
yCOLOR__descending()/* PURPOSE = generate an ascending monochrome variant set */
{
   printf("colors =");
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   char    x_hex[10], x_orig[10];
   /*---(save the main)--------------------*/
   strncpy(x_hex, CURRENT, 10);
   /*---(adjust the main)------------------*/
   /*> yCOLOR__hsv(o, HUE, SAT * 1.000, VAL * 0.800);                                 <*/
   if (DSAT != 0 || DINT != 0) {           /* avoid rounding errors in conversion */
      yCOLOR__hsv(HUE, yCOLOR__varcalc(SAT, DSAT), yCOLOR__varcalc(VAL, DINT));
   }
   strncpy(x_orig, HEX, 10);
   printf(" %s", HEX);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 1.000, VAL * 0.200);
   strncpy(VAR5, HEX, 10);
   printf(" %s", HEX);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 1.000, VAL * 0.500);
   strncpy(VAR4, HEX, 10);
   printf(" %s", HEX);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 1.000, VAL * 0.750);
   strncpy(VAR3, HEX, 10);
   printf(" %s", HEX);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 0.800, VAL * 0.900);
   strncpy(VAR2, HEX, 10);
   printf(" %s", HEX);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 0.500, VAL * 1.000);
   strncpy(VAR1, HEX, 10);
   printf(" %s", HEX);
   /*---*/
   yCOLOR__hex(x_orig);
   yCOLOR__hsv(HUE, SAT * 0.150, VAL * 1.000);
   strncpy(VAR0, HEX, 10);
   printf(" %s", HEX);
   /*---(complete)-------------------------*/
   printf("\n");
   return 0;
}

void               /*  return  = none                                         */
yCOLOR__reduction( /*  PURPOSE = generate a broad monochrome variant set      */
      char a_extended)            /*  option to extend variations             */
{
   /*---(get the current color)------------*/
   tCOLOR *o  = yPALETTE__current();
   yCOLOR__varsetup(VARIANT_ID);
   char    x_hex[10];
   /*---(save the main)--------------------*/
   strncpy(x_hex, HEX, 10);
   /*---(adjust the main)------------------*/
   /*> yCOLOR__hsv(o, HUE, SAT * 1.000, VAL * 0.800);                                 <*/
   if (DSAT != 0 || DINT != 0) {           /* avoid rounding errors in conversion */
      yCOLOR__hsv(HUE, yCOLOR__varcalc(SAT, DSAT), yCOLOR__varcalc(VAL, DINT));
   }
   strncpy(VAR0, HEX, 10);
   /*===[[ sitepro central : color scheme chooser ]]================*/
   /*> yCOLOR__hsv(o, HUE, SAT * 0.250, VAL * 1.000);                                 <* 
    *> yCOLOR__hsv(o, HUE, SAT * 0.666, VAL * 0.666);                                 <* 
    *> yCOLOR__hsv(o, HUE, SAT * 0.500, VAL * 1.000);                                 <* 
    *> yCOLOR__hsv(o, HUE, SAT * 0.666, VAL * 0.333);                                 <*/
   /*---*/
   yCOLOR__hex(VAR0);
   yCOLOR__hsv(HUE, SAT * 0.250, VAL * 1.000);
   strncpy(VAR1, HEX, 10);
   /*---*/
   yCOLOR__hex(VAR0);
   yCOLOR__hsv(HUE, SAT * 0.666, VAL * 0.666);
   strncpy(VAR2, HEX, 10);
   /*---*/
   yCOLOR__hex(VAR0);
   yCOLOR__hsv(HUE, SAT * 0.500, VAL * 1.000);
   strncpy(VAR3, HEX, 10);
   /*---*/
   yCOLOR__hex(VAR0);
   /*> yCOLOR__hsv(o, HUE, SAT * 1.000, VAL * 0.333);                                 <*/
   yCOLOR__hsv(HUE, SAT * 0.666, VAL * 0.333);
   strncpy(VAR4, HEX, 10);
   /*===[[ heatherly extended for a big monochrome set ]]===========*/
   if (a_extended == 'e') {
      yCOLOR__hex(VAR0);
      yCOLOR__hsv(HUE, SAT * 1.250, VAL * 0.750);
      strncpy(VAR5, HEX, 10);
      /*---*/
      yCOLOR__hex(VAR0);
      yCOLOR__hsv(HUE, SAT * 1.250, VAL * 0.500);
      strncpy(VAR7, HEX, 10);
      /*---*/
      yCOLOR__hex(VAR0);
      yCOLOR__hsv(HUE, SAT * 0.500, VAL * 0.750);
      strncpy(VAR6, HEX, 10);
      /*---*/
      yCOLOR__hex(VAR0);
      yCOLOR__hsv(HUE, SAT * 0.800, VAL * 0.850);
      strncpy(VAR8, HEX, 10);
      /*---*/
      yCOLOR__hex(VAR0);
      yCOLOR__hsv(HUE, SAT * 0.700, VAL * 0.650);
      strncpy(VAR9, HEX, 10);
      /*---*/
      yCOLOR__hex(VAR0);
      yCOLOR__hsv(HUE, SAT * 0.750, VAL * 0.333);
      strncpy(VARA, HEX, 10);
      /*---*/
      yCOLOR__hex(VAR0);
      yCOLOR__hsv(HUE, SAT * 0.333, VAL * 0.650);
      strncpy(VARB, HEX, 10);
      /*---*/
      yCOLOR__hex(VAR0);
      yCOLOR__hsv(HUE, SAT * 0.500, VAL * 0.500);
      strncpy(VARC, HEX, 10);
      /*---*/
      yCOLOR__hex(VAR0);
      yCOLOR__hsv(HUE, SAT * 0.250, VAL * 0.870);
      strncpy(VARD, HEX, 10);
      /*---*/
      yCOLOR__hex(VAR0);
      /*> yCOLOR__hsv(o, HUE, SAT * 0.500, VAL * 0.333);                              <*/
      yCOLOR__hsv(HUE, SAT * 0.700, VAL * 1.200);
      strncpy(VARE, HEX, 10);
      /*---*/
      yCOLOR__hex(VAR0);
      yCOLOR__hsv(HUE, SAT * 0.750, VAL * 0.200);
      strncpy(VARF, HEX, 10);
   }
   /*---(complete)-------------------------*/
   yCOLOR__hex(x_hex);
   return;
}


/*----------------------------------------------------------------------------*/
/*-------                       unit test                              -------*/
/*----------------------------------------------------------------------------*/

char*      /*=[[ FAQ ]]======* return  : cstring answer                       */
yPALETTE__getter(           /* PURPOSE : unit test state accessor             */
      char *a_question)           /* request for information                  */
{
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL) return "no current color";
   /*---(answer question)-----------------------*/
   strncpy(yCOLOR_answer, "unknown request", 100);
   if        (strcmp(a_question, "Dominant")    == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Dominant Color   : %7s at %3dh",
            DOMINANT_HEX, DOMINANT_HUE);
   } else if (strcmp(a_question, "Base")        == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Base Color       : %7s at %3dh",
            BASE, ANGLE);
   } else if (strcmp(a_question, "Modifiers")   == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Color Modifiers  : %3dv,  %3dn,  %3dm", 
            VARIANT_ID, NORMING_ID, MOTHERING_ID);
   } else if (strcmp(a_question, "Variant")     == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Variant     (%2s) : %s (%s)", 
            table_variation[VARIANT_ID].abbr, VARIANT, table_variation[VARIANT_ID].name);
   } else if (strcmp(a_question, "Norming")     == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Norming     (%2s) : %s (%s)", 
            table_norming[NORMING_ID].abbr, NORMED , table_norming[NORMING_ID].name);
   } else if (strcmp(a_question, "Mother")      == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Mothering   (%2s) : %s (%s)", 
            table_mother[MOTHERING_ID].abbr, MOTHERED , table_mother[MOTHERING_ID].name);
   } else if (strcmp(a_question, "Well")        == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Well Color       : %7s (%02dp, %02da)", 
            MIXED, POSITION, ACCENT);
   } else if (strcmp(a_question, "hex2norm")    == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "HEX2NORM         :  %4.2fr,   %4.2fg,   %4.2fb", 
            GEN_NORM.red, GEN_NORM.grn, GEN_NORM.blu);
   } else if (strcmp(a_question, "HSV_norm")    == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "HSV normals      : %5.0fh,  %5.2fs,  %5.2fv", 
            HUE, SAT, VAL);
   } else if (strcmp(a_question, "HSL_norm")    == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Color HSL norms  : %5.0fh,  %5.2fs,  %5.2fb", 
            HSL_HUE, HSL_SAT, HSL_LIG);
   } else if (strcmp(a_question, "RGB_norm")    == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Color RGB norms  :  %4.2fr,   %4.2fg,   %4.2fb", 
            RED, GRN, BLU);
   } else if (strcmp(a_question, "RYB_norm")    == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Color RYB norms  :  %4.2fr,   %4.2fy,   %4.2fb", 
            o->rr, o->yy, o->bb);
   } else if (strcmp(a_question, "RYB_hsv")     == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Color RYB rev    : %5.0fhh", 
            o->ryb_hh);
   } else if (strcmp(a_question, "RGB_byte")    == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Color RGB bytes  :   %3dr,    %3dg,    %3db", 
            RED_BYTE, GRN_BYTE, BLU_BYTE);
   } else if (strcmp(a_question, "RGB_hex")     == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "RGB Hex Code     : %s", 
            HEX);
   } else if (strcmp(a_question, "RYB_hue")    == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Color RYB hue    :   %3.0f", 
            (float) o->ryb_hue);
   } else if (strcmp(a_question, "RGB_hue")     == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Color RGB hue    :   %3.0f", 
            HUE);
   } else if (strcmp(a_question, "variant")     == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Variants: %s, %s, %s, %s, %s", 
            VAR0, VAR1, VAR2, VAR3, VAR4);
   } else if (strcmp(a_question, "Greyscale")   == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Greyscale        : %s", 
            o->grey);
   } else if (strcmp(a_question, "Websafe")     == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Websafe          : %s", 
            o->web);
   } else if (strcmp(a_question, "CSS_hex")     == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "CSS hex          : %s", 
            o->css);
   } else if (strcmp(a_question, "Top")         == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Top               : d=%s, m=%s, h=%s", 
            DOMINANT_HEX, MOTHERED, HEX);
   } else if (strcmp(a_question, "Scheme")      == 0) {
      snprintf(yCOLOR_answer, LEN_TEXT, "Color Scheme     : %02ds, %02dc",  
            SCHEME_ID, COMP_ID);
   } else if (strcmp(a_question, "Linked_list") == 0) {
      char hex1[20] = "--#------";
      char hex2[20] = "--#------";
      char hex3[20] = "--#------";
      snprintf(hex2, 20, "%02d%s", o->iden, o->hex);
      if (o->prev != NULL)
         snprintf(hex1, 20, "%02d%s", o->prev->iden, o->prev->hex);
      if (o->next != NULL)
         snprintf(hex3, 20, "%02d%s", o->next->iden, o->next->hex);
      snprintf(yCOLOR_answer, LEN_TEXT, "Linked list      : %s, %s, %s", 
            hex1, hex2, hex3);
   }
   return yCOLOR_answer;
}

/*> int                          /+  return  = index to table                     +/   <* 
 *> yCOLOR_variant(              /+  PURPOSE = identify color variant index       +/   <* 
 *>       void   *a_color,            /+  color object                            +/   <* 
 *>       char    a_scheme[8])        /+  scheme name abbreviation                +/   <* 
 *> {                                                                                  <* 
 *>    /+---(check for null/default)-----------+/                                      <* 
 *>    if (a_color == NULL) a_color = my_curr;                                         <* 
 *>    if (a_color == NULL) return -1;                                                 <* 
 *>    tCOLOR *o   = my_curr  = (tCOLOR *) a_color;                                    <* 
 *>    /+---(local variables)------------------+/                                      <* 
 *>    int       x_variant = 0;                /+ variant index (default = 0)     +/   <* 
 *>    int       i = 0;                        /+ loop counter                    +/   <* 
 *>    char      x_abbr[10] = "";              /+ scheme abbreviation             +/   <* 
 *>    /+---(find complement)------------------+/                                      <* 
 *>    if (strlen(a_scheme) == 5) {                                                    <* 
 *>       x_abbr[0] = a_scheme[3];                                                     <* 
 *>       x_abbr[1] = a_scheme[4];                                                     <* 
 *>       x_abbr[2] = '\0';                                                            <* 
 *>       for (i = 0; i < 50; ++i) {                                                   <* 
 *>          if (strcmp(g_variant[i].abbr, "eoi") == 0) break;                         <* 
 *>          if (strcmp(g_variant[i].abbr, x_abbr) == 0) x_variant = i;                <* 
 *>       }                                                                            <* 
 *>    }                                                                               <* 
 *>    /+---(load information)-----------------+/                                      <* 
 *>    VARIANT = x_variant;                                                            <* 
 *>    /+---(complete)-------------------------+/                                      <* 
 *>    return x_variant;                                                               <* 
 *> }                                                                                  <*/





char               /*  return  = simple error code                            */
yCOLOR__html(      /*  PURPOSE = create a output html line for a single color */
      int     a_count,            /*  color sequence number                   */
      char    a_format)           /*  type of output (html, tagged, ascii,...)*/
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   int i;
   char hex0[10] = "";
   char hex1[10] = "";
   char hex2[10] = "";
   char hex3[10] = "";
   char hex4[10] = "";
   strncpy(hex0, VAR0, 10);
   strncpy(hex1, VAR1, 10);
   strncpy(hex2, VAR2, 10);
   strncpy(hex3, VAR3, 10);
   strncpy(hex4, VAR4, 10);
   printf("<tr height=%d valign=center align=center>\n", a_count * 8);
   printf("<td bgcolor=%s width=200>%s</td>\n", hex2, (a_format == 't') ? hex2 : "");
   printf("<td rowspan=2 bgcolor=%s width=400>%s</td>\n", hex0, (a_format == 't') ? hex0 : "");
   printf("<td bgcolor=%s width=200>%s</td>\n", hex3, (a_format == 't') ? hex3 : "");
   /*---(the full 16)-------------------------------*/
   yCOLOR__reduction('e');
   for (i = 0; i < 16; ++i) {
      printf("<td rowspan=2 bgcolor=%s width=50>%s</td>\n", o->var[i], (a_format == 't') ? o->var[i] : "");
   }
   /*---(rest of original)--------------------------*/
   printf("</tr>\n");
   printf("<tr height=%d valign=center align=center>\n", a_count * 8);
   printf("<td bgcolor=%s width=200>%s</td>\n", hex1, (a_format == 't') ? hex1 : "");
   printf("<td bgcolor=%s width=200>%s</td>\n", hex4, (a_format == 't') ? hex4 : "");
   /*---(finish)------------------------------------*/
   printf("</tr>\n\n");
   return 0;
}

char*              /*  return  = c-string of space-delimeted hex colors       */
yCOLOR__line(      /*  PURPOSE = create a output string for a single color    */
      float   a_hue,              /*  hue (degree) to use                     */
      char    a_variant,          /*  variant flag                            */
      int     a_count,            /*  number of the color                     */
      char    a_format)           /*  stlye of output                         */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)          return "nada";
   /*---(process)--------------------------*/
   char x_text[200] = "";
   int x_new = (int) a_hue;
   while (x_new < 0)    x_new += 360;
   while (x_new >= 360) x_new -= 360;
   char  x_ryb[10];
   yCOLOR_ryb_hex   (x_new, x_ryb);
   if (o->is_ryb  == 1) yCOLOR__hex(x_ryb);
   else                 yCOLOR__hsv(x_new, 1, 1);
   if (a_variant == 'v') {
      yCOLOR__accents();
      snprintf(x_text, 200, "%s %s %s %s %s\n", VAR0, VAR1, VAR2, VAR3, VAR4);
   } else if (a_variant == 'a') {
      yCOLOR__ascending();
      snprintf(x_text, 200, "%s %s %s %s %s %s\n", VAR0, VAR1, VAR2, VAR3, VAR4, VAR5);
   } else if (a_variant == 'd') {
      yCOLOR__descending();
      snprintf(x_text, 200, "%s %s %s %s %s %s\n", VAR0, VAR1, VAR2, VAR3, VAR4, VAR5);
   } else if (a_variant == 'r') {
      yCOLOR__reduction('-');
      snprintf(x_text, 200, "%s %s %s %s %s\n", VAR0, VAR1, VAR2, VAR3, VAR4);
   } else if (a_variant == 'e') {
      yCOLOR__reduction('e');
      snprintf(x_text, 200, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s\n",
            VAR0, VAR1, VAR2, VAR3, VAR4, VAR5, VAR6, VAR7, VAR8, VAR9,
            VARA, VARB, VARC, VARD, VARE, VARF);
   } else if (a_variant == 'm') {
      yCOLOR__reduction('e');
      snprintf(x_text, 200, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
            VAR0, VAR1, VAR2, VAR3, VAR4, VAR5, VAR6, VAR7, VAR8, VAR9,
            VARA, VARB, VARC, VARD, VARE, VARF);
}
strncat(yCOLOR_answer, x_text, 200);
if (a_format == 'a') {
   printf("%s", x_text);
} else if (a_format == 's') {
   /*---(nothing)----*/
} else {
   yCOLOR__accents();                /* just to load the basics           */
   yCOLOR__html(a_count, a_format);
}
/*---(complete)-------------------------*/
return yCOLOR_answer;
}

char
yCOLOR__stdout()
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)          return -1;
   printf("%s %s %s %s %s\n", VAR0, VAR1, VAR2, VAR3, VAR4);
   return 0;
}

/*> int                /+  return  = simple integer error code                    +/                                                                                         <* 
 *> yCOLOR_generate(   /+  PURPOSE = generate a scheme from config table          +/                                                                                         <* 
 *>       char   *a_scheme,           /+  scheme name abbreviation                +/                                                                                         <* 
 *>       char    a_variant,          /+  variant style                           +/                                                                                         <* 
 *>       char    a_format)           /+  type of output (html, tagged, ascii,...)+/                                                                                         <* 
 *> {                                                                                                                                                                        <* 
 *>    /+---(defense on my_curr)---------------+/                                                                                                                            <* 
 *>    tCOLOR *o  = yPALETTE__current();                                                                                                                                     <* 
 *>    if (o == NULL)                return -1;                                                                                                                              <* 
 *>    /+---(set the base color)---------------+/                                                                                                                            <* 
 *>    int x_base = HUE;                                                                                                                                                     <* 
 *>    if (o->is_ryb  == 1) x_base = o->base;                                                                                                                                <* 
 *>    /+---(identify)-------------------------+/                                                                                                                            <* 
 *>    yCOLOR_scheme(a_scheme);                                                                                                                                              <* 
 *>    /+> yCOLOR_variant(a_scheme);                                                      <+/                                                                                <* 
 *>    /+---(print header)---------------------+/                                                                                                                            <* 
 *>    if (a_format == 'a') {                                                                                                                                                <* 
 *>       printf("_colorscheme : %-15.15s at %03dd using %-3.3s%-2.2s [%c] adj=%2d\n",                                                                                       <* 
 *>             (o->is_ryb == 1) ? "RYB (artistic)" : "RGB (technical)",                                                                                                     <* 
 *>             o->base, table_scheme[SCHEME_ID].abbr, table_comp[COMP].abbr,                                                                                                <* 
 *>             table_accent[ACCENTING_ID].abbr[0], VARIANT_ID);                                                                                                             <* 
 *>    } else if (a_format == 's') {                                                                                                                                         <* 
 *>       int z = 0;                                                                                                                                                         <* 
 *>       /+> printf("FORMAT FORMAT FORMAT :: <<%c>>\n", a_format);                       <+/                                                                                <* 
 *>    } else {                                                                                                                                                              <* 
 *>       printf("<html><head><title>swatch</title></head><body>\n\n<h1>_colorscheme : %-15.15s at %03dd using %-3.3s%-2.2s [%c] adj=%2d</h1>\n",                            <* 
 *>             (o->is_ryb == 1) ? "RYB (artistic)" : "RGB (technical)",                                                                                                     <* 
 *>             o->base, table_scheme[SCHEME_ID].abbr, table_comp[COMP].abbr,                                                                                                <* 
 *>             table_accent[ACCENTING_ID].abbr[0], VARIANT_ID);                                                                                                             <* 
 *>       printf("<table border=0 cellspacing=0><tr><th>shadows</th><th>dominant</th><th>accents</th><th colspan=5>reductions</th><th colspan=11>extended</th></tr>\n\n");   <* 
 *>    }                                                                                                                                                                     <* 
 *>    /+---(generate colors)------------------+/                                                                                                                            <* 
 *>    int j;                                                                                                                                                                <* 
 *>    int x_angle;                                                                                                                                                          <* 
 *>    int x_size;                                                                                                                                                           <* 
 *>    j = 0;                                                                                                                                                                <* 
 *>    x_size = 10;                                                                                                                                                          <* 
 *>    x_angle = table_scheme[SCHEME_ID].angle[j];                                                                                                                           <* 
 *>    if (CIRCLE == 'n') {                                                                                                                                                  <* 
 *>       while (x_angle != 0) {                                                                                                                                             <* 
 *>          strncpy(yCOLOR_answer, yCOLOR__line(x_base + x_angle, a_variant, x_size, a_format), LEN_TEXT);                                                                  <* 
 *>          x_size = 5;                                                                                                                                                     <* 
 *>          ++j;                                                                                                                                                            <* 
 *>          x_angle = table_scheme[SCHEME_ID].angle[j];                                                                                                                     <* 
 *>       }                                                                                                                                                                  <* 
 *>       j = 0;                                                                                                                                                             <* 
 *>       x_size = 3;                                                                                                                                                        <* 
 *>       x_angle = table_comp[COMP].angle[j];                                                                                                                               <* 
 *>       while (x_angle != 0) {                                                                                                                                             <* 
 *>          strncpy(yCOLOR_answer, yCOLOR__line(x_base + x_angle, a_variant, x_size, a_format), LEN_TEXT);                                                                  <* 
 *>          ++j;                                                                                                                                                            <* 
 *>          x_angle = table_comp[COMP].angle[j];                                                                                                                            <* 
 *>       }                                                                                                                                                                  <* 
 *>    } else {                                                                                                                                                              <* 
 *>       int   x_seg = atoi(a_scheme + 3);                                                                                                                                  <* 
 *>       float x_deg = 360 / x_seg;                                                                                                                                         <* 
 *>       /+> printf("circle <<%s>> with %d segments and %d degrees\n",                   <*                                                                                 <* 
 *>        *>       a_scheme, x_seg, (int) x_deg);                                        <+/                                                                                <* 
 *>       for (j = 0; j < x_seg; ++j) {                                                                                                                                      <* 
 *>          strncpy(yCOLOR_answer, yCOLOR__line(x_base + (int) (x_deg * j), a_variant, x_size, a_format), LEN_TEXT);                                                        <* 
 *>          x_size = 5;                                                                                                                                                     <* 
 *>       }                                                                                                                                                                  <* 
 *>    }                                                                                                                                                                     <* 
 *>    if (a_format == 'a') {                                                                                                                                                <* 
 *>       int z = 0;                                                                                                                                                         <* 
 *>    } else if (a_format == 's') {                                                                                                                                         <* 
 *>       int z = 0;                                                                                                                                                         <* 
 *>    } else {                                                                                                                                                              <* 
 *>       printf("</table></body></html>\n");                                                                                                                                <* 
 *>    }                                                                                                                                                                     <* 
 *>    /+---(complete)-------------------------+/                                                                                                                            <* 
 *>    return 0;                                                                                                                                                             <* 
 *> }                                                                                                                                                                        <*/

char       /*=((p_uptate))=========* return  = simple error code              */
yCOLOR__run()                     /* PURPOSE = regen a specific color         */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   char x_rc = 0;
   if (x_rc == 0) x_rc = yCOLOR_ryb_hex   (ANGLE, BASE);
   if (x_rc == 0) x_rc = yPALETTE__variant_make  (VARIANT_ID,   BASE,    VARIANT);
   if (x_rc == 0) x_rc = yPALETTE__norming_make  (NORMING_ID,   VARIANT, NORMED);
   /*> if (x_rc == 0) x_rc = yPALETTE__mothering_make(MOTHERING_ID, MOTHER,  NORMED,  MOTHERED);   <*/
   /*---(complete)-------------------------*/
   /*> x_rc = yCOLOR__hex(CURRENT);                                                   <*/
   /*> if (x_rc == 0) x_rc = yCOLOR_variant();                                        <*/
   /*> if (x_rc == 0) x_rc = yCOLOR__mother(MOTHERING_ID, MOTHER, BASE, MIXED);       <*/
   /*> if (x_rc == 0) x_rc = yCOLOR__norming();                                       <*/
   /*> if (x_rc == 0) x_rc = yCOLOR__descending();                                    <*/
   /*> if (x_rc == 0) x_rc = yCOLOR__stdout();                                        <*/
   return x_rc;
}


/*----------------------------------------------------------------------------*/
/*--------------------------------end-of-file---------------------------------*/
/*----------------------------------------------------------------------------*/
