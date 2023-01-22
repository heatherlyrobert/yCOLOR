/*============================----beg-of-source---============================*/


/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "as (aesthetics)"
#define     P_SUBJECT   "color palettes and control"
#define     P_PURPOSE   "predictably aesthetic color palettes and transformations"

#define     P_NAMESAKE  "iris-chrysopteros (golden-winged)"
#define     P_HERITAGE  "iris is the goddess of rainbow, color, and messenger of zeus"
#define     P_IMAGERY   "beautiful young maiden with golden wings and a coat of rainbows"
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2009-09"

#define     P_VERMAJOR  ""
#define     P_VERMINOR  ""
#define     P_VERNUM    "1.3f"
#define     P_VERTXT    "updated to yURG_by_name after yURG change"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/

/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef     yCOLOR_PRIV
#define     yCOLOR_PRIV    loaded

#include    "yCOLOR.h"


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
/*---(custom core)-----------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
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
#define   MAX_COLOR    90
#define   MAX_OPTION   16

extern const char s_RYB [MAX_COLOR][MAX_OPTION + 1][LEN_LABEL];

typedef struct cCOLORS tCOLORS;
struct cCOLORS {
   char        name        [LEN_LABEL];
   char        hex         [LEN_TERSE];
   float       pct;
   float       cut;
   float       red;
   float       grn;
   float       blu;
   char        norm        [LEN_TERSE];
};
extern  tCOLORS  s_colors  [MAX_COLOR];


typedef struct cPALETTE tPALETTE;
struct cPALETTE {
   char        hex         [LEN_TERSE];
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
extern const tNORMING s_normings   [MAX_NORMING];


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
   char        extra;
   char        conf;
   char        refs;
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

extern const char s_newRYB [12][1][LEN_LABEL];



typedef struct cOGL  tOPL;
struct cOGL    {
   short       deg;
   char        name        [LEN_LABEL];
   char        base        [LEN_TERSE];
};
extern const tOPL g_full [700];



extern char  unit_answer [ LEN_TEXT ];



char        WHEEL_init              (void);


char        ycolor_har_init               (void);
char        HARM_seq                (int a_seq, char *a_name, char *a_abbr, int *a_base, int *a_comp, int *a_neg, int *a_pos);

float       yCOLOR__min3         (float  a_one  , float  a_two, float  a_three);
float       yCOLOR__max3         (float  a_one  , float  a_two, float  a_three);



char        DRAW_dot            (char a_type, int a_deg);

char        yCOLOR__palette_fresh (void);

char        WHEEL_set            (cchar *a_name);
char        ycolor_degree        (cint   a_deg);
char        ycolor_harmony             (cchar *a_name);
char        ycolor_value             (cchar *a_name);


char        VARS_seq                (int a_seq, char *a_sat, char *a_val, char *a_abbr);





/*===[[ yCOLOR_conv.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
int         ycolor_deg2fix          (cint  a_deg);
char        ycolor_deg2hex          (cint a_deg, char *a_hex);
/*---(hex)------------------*/
char        ycolor_hex2rgb          (char *a_hex, float *a_red, float *a_grn, float *a_blu);
char        ycolor_rgb2hex          (char *a_hex, cfloat a_red, cfloat a_grn, cfloat a_blu);





/*===[[ yCOLOR_pal.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        ycolor_palette_purge    (void);
char        ycolor_palette_init     (void);
char        ycolor_constant         (void);
/*---(generate)-------------*/
char        ycolor_palette__save    (cint a_major, cint a_minor, cchar *a_hex);
/*---(report)---------------*/
char        ycolor_palette_debug    (void);
/*---(done)-----------------*/




/*===[[ yCOLOR_pal.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ycolor_unit__quiet      (void);
char        ycolor_unit__loud       (void);
char        ycolor_unit__end        (void);



/*---(saturation)-----------*/
char        ycolor_sat_init         (void);
char        ycolor_sat_by_abbr      (cchar a_abbr);
char        ycolor_sat_by_name      (cchar *a_name);
char        ycolor_saturation       (cchar *a_name);
/*---(value)----------------*/
char        ycolor_val_init         (void);
char        ycolor_val_by_abbr      (cchar a_abbr);
char        ycolor_val_by_name      (cchar *a_name);
char        ycolor_value            (cchar *a_name);
/*---(done)-----------------*/

#endif
/*============================----end-of-source---============================*/
