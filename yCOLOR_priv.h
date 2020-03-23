/*============================----beg-of-source---============================*/
/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef     yCOLOR_PRIV
#define     yCOLOR_PRIV    loaded

#include "yCOLOR.h"


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



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "as (aesthetics)"
#define     P_PURPOSE   "predictably aesthetic color palettes and transformations"

#define     P_NAMESAKE  "iris-chrysopteros (golden-winged)"
#define     P_HERITAGE  "iris is the goddess of rainbow, color, and messenger of zeus"
#define     P_IMAGERY   "beautiful young maiden with golden wings and a coat of rainbows"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2009-09"
#define     P_DEPENDS   "none"

#define     P_VERNUM    "1.2h"
#define     P_VERTXT    "added empty wrap up, but not used yet"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/



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
#include    <ncurses.h>      /* NCURSES standard integration                  */
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
#define   MAX_OPTION   11

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


typedef struct cPALETTE tPALETTE;
struct cPALETTE {
   char        hex         [LEN_HEX];
   float       red;
   float       grn;
   float       blu;
};
extern  tPALETTE  s_palette  [MAX_COLOR];





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


typedef  struct cACCESSOR  tACCESSOR;
struct cACCESSOR {
   /*---(primary info)-------------------*/
   int         wheel;                       /* color wheel variation          */
   int         degree;                      /* color degree                   */
   /*---(harmony info)-------------------*/
   char        harmony      [LEN_LABEL];    /* complement, triad, etc         */
   int         comp;                        /* color degree -- complement     */
   int         neg;                         /* color degree -- accent A       */
   int         pos;                         /* color degree -- accent B       */
   /*---(specific colors)----------------*/
   int         reg;
   int         repl;
   int         inpt;
   int         bad;
   /*---(variant)------------------------*/
   char        sat_name     [LEN_LABEL];    /* variant saturation name        */
   char        val_name     [LEN_LABEL];    /* variant value name             */
   float       sat;
   float       val;
   float       acc;
   /*---(display)------------------------*/
   char        names;
   char        hexes;
   /*---(done)---------------------------*/
};
extern tACCESSOR  myCOLOR;

extern char  s_use;
extern char  s_scale;
extern int   s_cset;
extern int   s_tcolor;
extern int   s_ncolor;
extern int   s_cvariant;
extern int   s_lvariant;
extern int   s_nvariant;
extern int   s_cnorming;
extern int   s_nnorming;

extern char s_RYB [MAX_COLOR][MAX_OPTION + 1][LEN_LABEL];
extern const char s_newRYB [12][1][LEN_LABEL];




char        WHEEL_init              (void);


char        HARM_init               (void);
char        HARM_update             (void);
char        HARM_seq                (int a_seq, char *a_name, char *a_abbr, int *a_base, int *a_comp, int *a_neg, int *a_pos);

int         yCOLOR_deg_fix          (cint  a_deg);
float       yCOLOR__min3         (float  a_one  , float  a_two, float  a_three);
float       yCOLOR__max3         (float  a_one  , float  a_two, float  a_three);

float       yCOLOR__unhex        (char   a_one  , char   a_two  );


char        DRAW_dot            (char a_type, int a_deg);

char        yCOLOR__palette_fresh (void);

char        WHEEL_set            (cchar *a_name);
char        HARM_degree          (cint   a_deg );
char        HARM_set             (cchar *a_name);
char        SATS_set             (cchar *a_name);
char        VALS_set             (cchar *a_name);


char        VARS_seq                (int a_seq, char *a_sat, char *a_val, char *a_abbr);



















#endif
/*============================----end-of-source---============================*/
