/*============================----beg-of-source---============================*/
#include "yCOLOR.h"



/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef     yCOLOR_PRIV
#define     yCOLOR_PRIV    loaded



/* rapidly evolving version number to aid with visual change confirmation     */
#define     YFONT_VER_NUM   "1.0g"
#define     YFONT_VER_TXT   "added extra color spectrums"



/*===[[ HEADERS ]]========================================*/
/*---(ansi-c standard)-------------------*/
#include    <stdio.h>        /* CLIBC   standard input/output                 */
#include    <stdlib.h>       /* CLIBC   standard general purpose              */
#include    <string.h>       /* CLIBC   standard string handling              */
#include    <math.h>         /* CLIBC   standard math functions               */
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



/*===[[ TYPEDEFS ]]===========================================================*/
/*3456789012+123456789012+123456789012+123456789012+123456789012+123456789012-*/
/*---(basics)--------------------------*/
typedef     signed      char        schar;
typedef     unsigned    char        uchar;
typedef     const       char        cchar;
typedef     unsigned    short       ushort;
typedef     signed      long        slong;
typedef     unsigned    long        ulong;
typedef     signed      long long   llong;
typedef     unsigned    long long   ullong;
/*---(data structures)-----------------*/
typedef     struct      cYFONT      tYFONT;
typedef     struct      cGLYPH      tGLYPH;
typedef     struct      cPOINT      tPOINT;
typedef     struct      cVERT       tVERT;




/*===[[ RYB ARTISTS COLOR SPECTRUM ]]=========================================*/
#define   MAX_COLOR    80
#define   MAX_OPTION   10

extern char s_RYB [MAX_COLOR][MAX_OPTION + 1][LEN_LABEL];

typedef struct cCOLORS tCOLORS;
struct cCOLORS {
   char        name        [LEN_LABEL];
   char        hex         [LEN_HEX];
   float       pct;
   float       cut;
   float       red;
   float       grn;
   float       blu;
   char        norm        [LEN_HEX];
};
extern  tCOLORS  s_colors  [MAX_COLOR];


/*---(color variations)------------------------------*/
#define    MAX_VARIANT      100
typedef struct cVARIANT tVARIANT;
struct cVARIANT {
   char        cat         [10];       /* category of variations              */
   char        abbr        [10];       /* abbreviation for variant            */
   char        name        [35];       /* full name of variant                */
   float       new_sat;                /* new saturation for HSV              */
   float       new_val;                /* new value for HSV                   */
   float       accent;                 /* accent percentage                   */
};
extern tVARIANT    s_variants  [MAX_VARIANT];



/*---(color norming methods)-------------------------*/
#define    MAX_NORMING      100
typedef struct cNORMING tNORMING;
struct cNORMING {
   char        abbr[8];
   char        name[35];
   double      red;
   double      grn;
   double      blu;
   char        is_value;
};
tNORMING s_normings   [MAX_NORMING];



extern char  s_use;
extern char  s_scale;
extern int   s_cset;
extern int   s_ccolor;
extern int   s_tcolor;
extern int   s_ncolor;
extern int   s_cvariant;
extern int   s_lvariant;
extern int   s_nvariant;
extern int   s_cnorming;
extern int   s_nnorming;








float       yCOLOR__min3         (float  a_one  , float  a_two, float  a_three);
float       yCOLOR__max3         (float  a_one  , float  a_two, float  a_three);

float       yCOLOR__unhex        (char   a_one  , char   a_two  );

























#endif
/*============================----end-of-source---============================*/
