/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



/*===[[ HEADERS ]]========================================*/
/*---(local)-----------------------------*/


#include    <time.h>         /* CLIBC   standard time and date handling       */


/*---(vi-keys foundation)----------------*/
#include    <yMODE.h>             /* heatherly vikeys mode tracking           */
#include    <yKEYS.h>             /* heatherly vikeys key handling            */
#include    <yFILE.h>             /* heatherly vikeys content file handling   */
#include    <yVIEW.h>             /* heatherly vikeys view management         */
/*---(vi-keys major)---------------------*/
#include    <yMAP.h>              /* heatherly vikeys location management     */
#include    <yCMD.h>              /* heatherly vikeys command processing      */
#include    <yMACRO.h>            /* heatherly vikeys macro processing        */
#include    <ySRC.h>              /* heatherly vikeys source editing          */
#include    <yMARK.h>             /* heatherly vikeys search and marking      */
#include    <yGOD.h>         /* CUSTOM  heatherly opengl godview              */
/*---(custom opengl)---------------------*/
#include    <yVIOPENGL.h>    /* heatherly vikeys opengl handler          */
#include    <yX11.h>         /* CUSTOM  heatherly xlib/glx setup/teardown     */
#include    <yFONT.h>        /* CUSTOM  heatherly texture-mapped fonts        */
#include    <yGLTEX.h>       /* CUSTOM  heatherly texture handling            */


typedef struct timespec  tTSPEC;

static char  s_face     [LEN_LABEL] = "shrike";
static char  s_font     = -1;

static char  s_alt      = 'y';
static char  s_notation   = '-';
static char  s_accent     = 'y';

int       win_w = 1400;                     /* window width                   */
int       win_h =  600;                     /* window height                  */

const    double   DEG2RAD   = M_PI / 180.0;



int      s_scheme   =    0;

#define  SCHEME_CURRENT     '-'
#define  SCHEME_MONO        'M'
#define  SCHEME_ANA         'A'
#define  SCHEME_ANAB        'B'
#define  SCHEME_ANAB2       'Y'
#define  SCHEME_COMP        'C'
#define  SCHEME_DCOMP       'D'
#define  SCHEME_FCOMP       'F'
#define  SCHEME_FCOMPR      'X'
#define  SCHEME_TRIAD       'T'
#define  SCHEME_RECT        'R'
#define  SCHEME_RECTM       'Z'
#define  SCHEME_SQUARE      'S'


char           DRAW_view_prog     (void);
char           DRAW_view_nav      (void);

char           DRAW_init            (void);
char           DRAW_wheel               (void);
char           DRAW_layout         (void);

char           FONT_load            (void);
char           FONT_delete          (void);




char
DRAW_labels_set      (char *a_opt)
{
   if      (a_opt == NULL)                 myCOLOR.names = '-';
   else if (strcmp (a_opt, "on"  ) == 0)   myCOLOR.names = 'y';
   else if (strcmp (a_opt, "show") == 0)   myCOLOR.names = 'y';
   else if (strcmp (a_opt, "name") == 0)   myCOLOR.names = 'y';
   else if (strcmp (a_opt, "hex" ) == 0)   myCOLOR.names = 'h';
   else if (strcmp (a_opt, "deg" ) == 0)   myCOLOR.names = 'd';
   else if (strcmp (a_opt, "off" ) == 0)   myCOLOR.names = '-';
   else if (strcmp (a_opt, "hide") == 0)   myCOLOR.names = '-';
   return 0;
}

char
DRAW_extras_set      (char *a_opt)
{
   if      (a_opt == NULL)                 myCOLOR.extra = '-';
   else if (strcmp (a_opt, "on"  ) == 0)   myCOLOR.extra = 'y';
   else if (strcmp (a_opt, "show") == 0)   myCOLOR.extra = 'y';
   else if (strcmp (a_opt, "off" ) == 0)   myCOLOR.extra = '-';
   else if (strcmp (a_opt, "hide") == 0)   myCOLOR.extra = '-';
   return 0;
}

char
DRAW_conf_set        (char *a_opt)
{
   if      (a_opt == NULL)                 myCOLOR.conf  = '-';
   else if (strcmp (a_opt, "on"  ) == 0)   myCOLOR.conf  = 'y';
   else if (strcmp (a_opt, "show") == 0)   myCOLOR.conf  = 'y';
   else if (strcmp (a_opt, "off" ) == 0)   myCOLOR.conf  = '-';
   else if (strcmp (a_opt, "hide") == 0)   myCOLOR.conf  = '-';
   return 0;
}

char
DRAW_refs_set        (char *a_opt)
{
   if      (a_opt == NULL)                 myCOLOR.refs  = '-';
   else if (strcmp (a_opt, "on"  ) == 0)   myCOLOR.refs  = 'y';
   else if (strcmp (a_opt, "show") == 0)   myCOLOR.refs  = 'y';
   else if (strcmp (a_opt, "off" ) == 0)   myCOLOR.refs  = '-';
   else if (strcmp (a_opt, "hide") == 0)   myCOLOR.refs  = '-';
   return 0;
}


/*====================------------------------------------====================*/
/*===----                     null maps and labels                     ----===*/
/*====================------------------------------------====================*/
static void   o___YMAP____________o (void) { return; }

char api_ymap_locator        (char a_strict, char *a_label, ushort *u, ushort *x, ushort *y, ushort *z) { return -1; }
char api_ymap_addressor      (char a_strict, char *a_label, ushort u, ushort x, ushort y, ushort z)     { return -1; }

char api_ymap_sizer          (char a_axis, ushort *n, ushort *a, ushort *b, ushort *c, ushort *e, ushort *m, ushort *x) { return 0; }
char api_ymap_entry          (char a_axis, ushort a_pos, short *r_ref, uchar *r_wide, uchar *r_used)                    { return 0; }

char api_ymap_placer         (char a_axis, ushort b, ushort c, ushort e)                                                { return 0; }
char api_ymap_done           (void) { return 0; }



/*====================------------------------------------====================*/
/*===----                        program wide                          ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;}

char      verstring    [500];

char*      /* ---- : return library versioning information -------------------*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __CBANG__  > 0
   strncpy (t, "[cbang      ]", 15);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (verstring, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return verstring;
}



/*====================------------------------------------====================*/
/*===----                       pre-initialization                     ----===*/
/*====================------------------------------------====================*/
static void      o___PREINIT_________________o (void) {;}

char       /*----: very first setup ------------------s-----------------------*/
PROG__header            (void)
{
   /*---(header)----------------------*/
   DEBUG_PROG   yLOG_enter (__FUNCTION__);
   /*---(versioning)------------------*/
   DEBUG_PROG   yLOG_info     ("arachne" , PROG_version      ());
   DEBUG_PROG   yLOG_info     ("purpose" , P_PURPOSE);
   DEBUG_PROG   yLOG_info     ("namesake", P_NAMESAKE);
   DEBUG_PROG   yLOG_info     ("heritage", P_HERITAGE);
   DEBUG_PROG   yLOG_info     ("imagery" , P_IMAGERY);
   DEBUG_PROG   yLOG_note     ("custom core");
   DEBUG_PROG   yLOG_info     ("yURG"    , yURG_version      ());
   DEBUG_PROG   yLOG_info     ("yLOG"    , yLOGS_version     ());
   DEBUG_PROG   yLOG_info     ("ySTR"    , ySTR_version      ());
   DEBUG_PROG   yLOG_note     ("yvikeys foundation");
   DEBUG_PROG   yLOG_info     ("yMODE"   , yMODE_version     ());
   DEBUG_PROG   yLOG_info     ("yKEYS"   , yKEYS_version     ());
   DEBUG_PROG   yLOG_info     ("yFILE"   , yFILE_version     ());
   DEBUG_PROG   yLOG_info     ("yVIEW"   , yVIEW_version     ());
   DEBUG_PROG   yLOG_note     ("yvikeys major");
   DEBUG_PROG   yLOG_info     ("yMAP"    , yMAP_version      ());
   DEBUG_PROG   yLOG_info     ("yCMD"    , yCMD_version      ());
   DEBUG_PROG   yLOG_info     ("yMACRO"  , yMACRO_version    ());
   DEBUG_PROG   yLOG_info     ("ySRC"    , ySRC_version      ());
   DEBUG_PROG   yLOG_info     ("yMARK"   , yMARK_version     ());
   DEBUG_PROG   yLOG_info     ("yGOD"    , yGOD_version      ());
   DEBUG_PROG   yLOG_note     ("custom opengl");
   DEBUG_PROG   yLOG_info     ("yVIOP"   , yVIOPENGL_version ());
   DEBUG_PROG   yLOG_info     ("yX11"    , yX11_version      ());
   DEBUG_PROG   yLOG_info     ("yFONT"   , yFONT_version     ());
   DEBUG_PROG   yLOG_info     ("yCOLOR"  , yCOLOR_version    ());
   DEBUG_PROG   yLOG_info     ("yGLTEX"  , yGLTEX_version    ());
   DEBUG_PROG   yLOG_note     ("custom other");
   DEBUG_PROG   yLOG_info     ("yVAR"    , yVAR_version      ());
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG_urgents            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(set mute)-----------------------*/
   yURG_all_mute ();
   /*---(start logger)-------------------*/
   rc = yURG_logger  (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = yURG_urgs    (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = PROG__header ();
   DEBUG_PROG   yLOG_value    ("header"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        program startup                       ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP_________________o (void) {;}

char       /*----: very first setup ------------------s-----------------------*/
PROG__init              (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   DEBUG_PROG   yLOG_enter (__FUNCTION__);
   /*---(yvicurses config)---------------*/
   rc = yVIOPENGL_init   (P_NAMESAKE, P_VERNUM, MODE_MAP, 500, 500);
   DEBUG_PROG   yLOG_value    ("yVICURSES" , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*> strlcpy (my.t_text     , "arachne, spider robot visualization and simulation"       , LEN_STR  );   <*/
   /*---(library config)-----------------*/
   rc = yMAP_config       (YMAP_OFFICE, api_ymap_locator, api_ymap_addressor, api_ymap_sizer, api_ymap_entry, api_ymap_placer, api_ymap_done);
   DEBUG_PROG   yLOG_value    ("yMAP"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*> rc = FILE_init      ();                                                        <* 
    *> DEBUG_PROG   yLOG_value    ("yFILE"     , rc);                                 <* 
    *> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);                             <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(setup yVIKEYS)------------------*/
   DEBUG_PROG   yLOG_note  ("prepare modes");
   /*> yVIKEYS_init         ('-');                                                    <*/
   yCMD_add             ('v', "labels"      , ""    , "s"    , DRAW_labels_set            , "show color labels (y/n)" );
   yCMD_add             ('v', "extras"      , ""    , "s"    , DRAW_extras_set            , "show extra colors (y/n)" );
   yCMD_add             ('v', "conf"        , ""    , "s"    , DRAW_conf_set              , "show conf details (y/n)" );
   yCMD_add             ('v', "refs"        , ""    , "s"    , DRAW_refs_set              , "show conf details (y/n)" );
   /*> yVIKEYS_view_config  ("yCOLOR_make", P_VERNUM, YVIKEYS_OPENGL, 500, 500, 500);   <*/
   /*> yCMD_direct          (":palette 0 fcomp full vivid");                          <*/
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG__args              (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   char       *a           = NULL;
   char       *b           = NULL;
   int         x_total     =    0;
   int         x_args      =    0;
   uchar       x_name      [LEN_FULL]  = "";
   uchar       t           [LEN_FULL]  = "";
   /*---(header)-------------------------*/
   /*> printf ("entering PROG_args\n");                                               <*/
   DEBUG_ARGS  yLOG_enter   (__FUNCTION__);
   /*---(process)------------------------*/
   for (i = 1; i < a_argc; ++i) {
      /*---(set up args)-----------------*/
      DEBUG_ARGS  yLOG_value   ("check----" , i);
      a = a_argv [i];
      if (i + 1 < a_argc)  b = a_argv [i + 1];
      else                 b = NULL;
      DEBUG_ARGS  yLOG_info    ("a"         , a);
      DEBUG_ARGS  yLOG_info    ("b"         , b);
      ++x_total;
      /*---(check vikeys)----------------*/
      rc = yKEYS_arg_handle (&i, a, b);
      DEBUG_ARGS  yLOG_value   ("ykeys"     , rc);
      if (rc == 1) {
         DEBUG_ARGS  yLOG_note    ("handled by yKEYS_arg_handle");
         DEBUG_ARGS  yLOG_value   ("bumped i"  , i);
         continue;
      }
      /*---(filter)----------------------*/
      if (a[0] == '@') {
         DEBUG_ARGS  yLOG_note    ("skipped urgent");
         continue;
      }
      /*---(local)-----------------------*/
      DEBUG_ARGS  yLOG_note    ("check for local argument handling");
      ++x_args;
      if      (strncmp(a, "--deg"               , 20) == 0) {
         if (a_argc > i + 1)  ycolor_degree     (atoi (a_argv [++i]));
      }
      else if (strncmp(a, "--har"               , 20) == 0) {
         if (a_argc > i + 1)  ycolor_harmony    (a_argv [++i]);
      }
      else if (strncmp(a, "--sat"               , 20) == 0) {
         if (a_argc > i + 1)  ycolor_saturation (a_argv [++i]);
      }
      else if (strncmp(a, "--val"               , 20) == 0) {
         if (a_argc > i + 1)  ycolor_value      (a_argv [++i]);
      }
      else if (strncmp(a, "--labels"            , 20) == 0) {
         if (a_argc > i + 1)  DRAW_labels_set   (a_argv [++i]);
      }
      else if (strncmp(a, "--noalt"             , 20) == 0)  s_alt = '-';
   }
   DEBUG_ARGS  yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS  yLOG_value  ("arguments" , x_args);
   if (x_args == 0) {
      DEBUG_ARGS  yLOG_note   ("no arguments identified");
   }
   /*---(complete)-----------------------*/
   DEBUG_ARGS  yLOG_exit  (__FUNCTION__);
   return 0;
}


char       /*----: drive program setup activities ----------------------------*/
PROG__begin             (void)
{
   char        rc          =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_startup            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   yURG_stage_check (YURG_BEG);
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = PROG__init   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(arguments)----------------------*/
   rc = PROG__args   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("args"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)--------------------------*/
   rc = PROG__begin  ();
   DEBUG_PROG   yLOG_value    ("begin"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   yURG_stage_check (YURG_MID);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        program execution                     ----===*/
/*====================------------------------------------====================*/
static void      o___EXECUTION_______________o (void) {;}

char       /*----: process the xwindows event stream -------------------------*/
PROG_dawn          (void)
{
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   yVIOPENGL_dawn ();
   DRAW_init    ();
   FONT_load    ();
   /*> yKEYS_progress_config ('-', NULL, NULL, NULL, '-');                            <*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_dusk          (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter (__FUNCTION__);
   /*---(process)------------------------*/
   yVIOPENGL_dusk ();
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program shutdown                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN________________o (void) {;}

char       /*----: drive the program closure activities ----------------------*/
PROG__end               (void)
{
   /*---(shutdown)--------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   FONT_delete ();
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] drive the program closure activities ------------*/
PROG_shutdown           (void)
{
   /*---(header)-------------------------*/
   yURG_stage_check (YURG_END);
   DEBUG_PROG   yLOG_enter    (__FUNCTION__);
   PROG__end ();
   DEBUG_PROG   yLOG_exit     (__FUNCTION__);
   DEBUG_PROG   yLOGS_end    ();
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.310.001.11]*/ /*-[01.0000.011.!]-*/ /*-[--.---.---.--]-*/
FONT_load            (void)
{
   s_font  = yFONT_load (s_face);
   if (s_font <  0) {
      fprintf (stderr, "Problem loading %s\n", s_face);
      exit    (1);
   }
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
FONT_delete          (void)
{
   yFONT_free (s_font);
   return 0;
}


/*============================--------------------============================*/
/*===----                             draw                             ----===*/
/*============================--------------------============================*/
static void      o___OPENGL__________________o (void) {;}

char         /*-> establish drawing settings ---------[ shoot  [gz.640.001.00]*/ /*-[00.0000.011.!]-*/ /*-[--.---.---.--]-*/
DRAW_init          (void)
{
   yCMD_direct   (":layout min");
   if (s_alt == 'y')  yCMD_direct   (":alt show");
   yVIEW_full     (YVIEW_MAIN , YVIEW_FLAT , YVIEW_MIDCEN, YCOLOR_SPE, YCOLOR_BLK, DRAW_wheel );
   yVIEW_simple   (YVIEW_PROGRESS, YCOLOR_SPE, YCOLOR_BLK, DRAW_view_prog);
   yVIEW_full     (YVIEW_ALT  , YVIEW_FLAT , YVIEW_MIDCEN, YCOLOR_SPE, YCOLOR_BLK, DRAW_layout);
   yVIEW_defsize  (YVIEW_ALT, 500, 0);
   yVIEW_simple   (YVIEW_NAV     , YCOLOR_SPE, YCOLOR_BLK, DRAW_view_nav );
   yVIEW_defsize  (YVIEW_NAV,   0, 0);
   yVIEW_resize   (0, 0, 0);
   /*> yVIKEYS_view_colors   (YCOLOR_POS, YCOLOR_BAS, YCOLOR_NEG, YCOLOR_POS);        <*/
   /*---(complete)-----------------------*/
   return 0;
}


char         /*-> tbd --------------------------------[ ------ [gz.970.051.24]*/ /*-[04.0070.012.!]-*/ /*-[--.---.---.--]-*/
DRAW_column         (void)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =  0;             /* loop iterator -- word          */
   int         x_set       =  0;             /* loop iterator -- word          */
   float       x_wide      =  75.0;
   float       x_inc       =  0.0;
   char        x_text      [LEN_FULL];
   x_inc = (win_h - 40) / 36.0;
   yCOLOR_use (YCOLOR_WHEEL);
   glPushMatrix(); {
      glTranslatef ( 20, -win_h / 2 + 20,   0.0);
      for (x_deg =  0; x_deg < 360; x_deg += 10) {
         glPushMatrix(); {
            yCOLOR_deg2color   (x_deg, 1.0);
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
         if (myCOLOR.names == 'y') {
            glPushMatrix(); {
               glTranslatef (  37,   x_inc / 2 + 1,   0.0);
               glColor4f    ( 0.0, 0.0, 0.0, 1.0);
               /*> yFONT_print  (s_font,   8, YF_MIDCEN, x_norm);                  <*/
               yFONT_print  (s_font,   6, YF_MIDCEN, yCOLOR_deg2name (x_deg));
            } glPopMatrix();
         }
         glTranslatef ( 0.0, x_inc,   0.0);
      }
   } glPopMatrix();
   return 0;
}

char
DRAW_color          (int d)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_deg       =    0;
   char        x_base      [LEN_LABEL] = "";
   char        t           [LEN_LABEL] = "";
   double      x_red, x_grn, x_blu;
   /*---(prepare)------------------------*/
   x_deg = d;
   if (x_deg >= 360)  x_deg -= 360;
   /*---(set color)-------------*/
   strlcpy (x_base, g_full [x_deg].base , LEN_LABEL);
   if (strcmp (x_base, "õ------") == 0)  strlcpy (x_base, g_full [x_deg].base, LEN_LABEL);
   sprintf (t, "õ%2.2s", x_base + 1);
   strl2hex (t, &x_red, LEN_LABEL);
   x_red /= 255.0;
   DEBUG_GRAF   yLOG_complex ("red"       , "%s, %s, %6.1lf", x_base, t, x_red);
   sprintf (t, "õ%2.2s", x_base + 3);
   strl2hex (t, &x_grn, LEN_LABEL);
   x_grn /= 255.0;
   DEBUG_GRAF   yLOG_complex ("grn"       , "%s, %s, %6.1lf", x_base, t, x_grn);
   sprintf (t, "õ%2.2s", x_base + 5);
   strl2hex (t, &x_blu, LEN_LABEL);
   x_blu /= 255.0;
   DEBUG_GRAF   yLOG_complex ("blu"       , "%s, %s, %6.1lf", x_base, t, x_blu);
   glColor4f (x_red, x_grn, x_blu, 1.0);
   /*---(complete)-----------------------*/
   return 0;
}

char
DRAW_curve          (char a_type, int d, float z)
{
   static float       x_controls  [4][3];
   float              x_pos  = 0.0;
   float              ri     = 0.0;
   ri  = (win_h / 5.0) - 40;
   if (a_type == 'b') {
      x_controls [0][0] = ri * sin (d * DEG2RAD);
      x_controls [0][1] = ri * cos (d * DEG2RAD);
      x_controls [0][2] = z;
      DEBUG_GRAF   yLOG_complex ("base"      , "%dc, %3.0fx, %3.0fy, %3.0fz", 0, x_controls [0][0], x_controls [0][1], x_controls [0][2]);
      x_controls [1][0] = 0;
      x_controls [1][1] = 0;
      x_controls [1][2] = z;
      DEBUG_GRAF   yLOG_complex ("center"    , "%dc, %3.0fx, %3.0fy, %3.0fz", 1, x_controls [1][0], x_controls [1][1], x_controls [1][2]);
      return 0;
   }
   if (a_type != '-') {
      x_controls [2][0] = ri * sin (d * DEG2RAD);
      x_controls [2][1] = ri * cos (d * DEG2RAD);
      x_controls [2][2] = z;
      DEBUG_GRAF   yLOG_complex ("other"     , "%dc, %3.0fx, %3.0fy, %3.0fz", 2, x_controls [2][0], x_controls [2][1], x_controls [2][2]);
      DRAW_color (d);
      /*> if (a_type == 'c')  glColor4f (1.0f, 1.0f, 1.0f, 1.00f);                    <* 
       *> else                glColor4f (0.5f, 0.5f, 0.5f, 1.00f);                    <*/
      glLineWidth (20);
      glMap1f   (GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &x_controls [0][0]);
      glEnable  (GL_MAP1_VERTEX_3);
      glBegin   (GL_LINE_STRIP); {
         for (x_pos = 0.0; x_pos <= 1.0; x_pos += 0.05) {
            glEvalCoord1f (x_pos);
         }
      } glEnd();
      glDisable (GL_MAP1_VERTEX_3);
   }   
   return 0;
}

char
DRAW_ball           (int d, int c, int ro, int rc, float z)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_deg       =    0;
   int         i           =    0;
   float       x, y;
   float       r           =   0;
   /*---(prepare)------------------------*/
   if (c >= 360)  c -= 360;
   /*---(set color)-------------*/
   if      (c < -2)  glColor4f (0.0, 0.0, 0.0, 1.0);
   else if (c < -1)  glColor4f (0.0, 0.0, 0.0, 0.7);
   else if (c <  0)  glColor4f (0.0, 0.0, 0.0, 0.3);
   else              DRAW_color (c);
   /*---draw)-------------------*/
   glPushMatrix(); {
      glRotatef    (90 - d, 0.0f, 0.0f, 1.0f);
      glTranslatef (ro, 0.0,   0.0);
      glBegin         (GL_POLYGON); {
         for (i = 0; i <= 360; i += 10) {
            x =  rc * sin (i * DEG2RAD);
            y =  rc * cos (i * DEG2RAD);
            glVertex3f  (x, y, z);
         }
      } glEnd   ();
      if (d == c) {
         glBegin         (GL_POLYGON); {
            glVertex3f  ( 0.0,  3.0, z);
            glVertex3f  (40.0,  3.0, z);
            glVertex3f  (40.0, -3.0, z);
            glVertex3f  ( 0.0, -3.0, z);
         } glEnd   ();
      }
   } glPopMatrix();
   /*---(complete)-----------------------*/
   return 0;
}

char
DRAW_wedge          (char a_type, float ri, float ro, int d, int w, float z)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_deg       =    0;
   float       xi, yi;
   float       xo, yo;
   float       r           =   0;
   /*---(prepare)------------------------*/
   x_deg = d;
   if (x_deg >= 360)  x_deg -= 360;
   if (w == 0)  w = 1;
   /*---(set color)-------------*/
   DRAW_color (x_deg);
   /*---draw)-------------------*/
   glBegin       (GL_POLYGON); {
      r    = (90 - x_deg    )  * DEG2RAD;
      xi   = ri * cos (r);
      yi   = ri * sin (r);
      xo   = ro * cos (r);
      yo   = ro * sin (r);
      glVertex3f ( xi  , yi  , z);
      glVertex3f ( xo  , yo  , z);
      r    = (90 - x_deg + w)  * DEG2RAD;
      if (a_type != 'Õ') {
         xi   = ri * cos (r);
         yi   = ri * sin (r);
      }
      if (a_type != 'Ô') {
         xo   = ro * cos (r);
         yo   = ro * sin (r);
      }
      glVertex3f ( xo  , yo  , z);
      glVertex3f ( xi  , yi  , z);
   } glEnd         ();
   /*---(complete)-----------------------*/
   return 0;
}

char
DRAW_little         (int n, float ri, float ro, int d, int w, float z)
{
   /*---(locals)-----------+-----+-----+-*/
   float       xi, yi;
   float       xo, yo;
   float       r           =   0;
   /*---(set color)-------------*/
   yCOLOR_opengl (YCOLOR_VAR, n, 0.6);
   /*---draw)-------------------*/
   glBegin       (GL_POLYGON); {
      r    = (90 - d - w / 2.0)  * DEG2RAD;
      xi   = ri * cos (r);
      yi   = ri * sin (r);
      xo   = ro * cos (r);
      yo   = ro * sin (r);
      glVertex3f ( xi  , yi  , z);
      glVertex3f ( xo  , yo  , z);
      r    = (90 - d + w / 2.0)  * DEG2RAD;
      xi   = ri * cos (r);
      yi   = ri * sin (r);
      xo   = ro * cos (r);
      yo   = ro * sin (r);
      glVertex3f ( xo  , yo  , z);
      glVertex3f ( xi  , yi  , z);
   } glEnd         ();
   /*---(complete)-----------------------*/
   return 0;
}

char
DRAW_labels             (int d, float ri)
{
   char        t           [LEN_LABEL] = "";
   if (d <    0)  return 0;
   if (d >= 360)  return 0;
   if (myCOLOR.names != '-') {
      switch (myCOLOR.names) {
      case 'y':
         strlcpy (t, g_full [d].name, LEN_LABEL);
         break;
      case 'h':
         strlcpy (t, g_full [d].base, LEN_LABEL);
         break;
      case 'd':
         sprintf (t, "%d", d);
         break;
      }
      glPushMatrix(); {
         glColor4f    (0.0, 0.0, 0.0, 1.0);
         glRotatef    (90 - d        , 0.0f, 0.0f, 1.0f);
         glTranslatef ( ri,   0.0,  50.0);
         /*> yFONT_print  (s_font,   8, YF_MIDCEN, x_norm);                  <*/
         if (d <= 180) {
            yFONT_print  (s_font, 8, YF_MIDLEF, t);
         } else {
            glRotatef    (180, 0.0f, 0.0f, 1.0f);
            yFONT_print  (s_font, 8, YF_MIDRIG, t);
         }
      } glPopMatrix();
   }
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.SO0.1E1.D7]*/ /*-[05.00O0.012.!]-*/ /*-[--.---.---.--]-*/
DRAW_wheel               (void)
{
   /*---(locals)-----------+-----------+-*/
   int         d           =    0;          /* degree iterator                */
   float       ri          =  0.0;          /* inner radius                   */
   float       ro          =  0.0;          /* outer radius                   */
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   ri  = win_h / 5.0;
   ro  = ri + win_h / 5.0;
   glPushMatrix(); {
      glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
      for (d = 0; d <= 360; ++d) {
         DRAW_wedge ('-', ri, ro, d, 0, 0);
      }
      for (d = 0; d <= 360; ++d) {
         if (d % 30 == 0) {
            DRAW_wedge ('Õ', ri + 50, ro, d, -15, 20);
            DRAW_wedge ('Õ', ri + 50, ro, d,  15, 20);
         }
      }
      for (d = 0; d <= 360; ++d) {
         if      (d == myCOLOR.degree)   DRAW_curve ('b', d, 30);
         if      (d == myCOLOR.comp  )   DRAW_curve ('c', d, 30);
         else if (d == myCOLOR.neg   )   DRAW_curve ('n', d, 30);
         else if (d == myCOLOR.pos   )   DRAW_curve ('p', d, 30);
      }
      for (d = 0; d <= 360; ++d) {
         if      (d == myCOLOR.degree)   DRAW_ball (d, d      , ri - 40, 30, 40);
         else if (d == myCOLOR.comp  )   DRAW_ball (d, d      , ri - 40, 15, 40);
         else if (d == myCOLOR.neg   )   DRAW_ball (d, d      , ri - 40, 20, 40);
         else if (d == myCOLOR.pos   )   DRAW_ball (d, d      , ri - 40, 20, 40);
      }
      for (d = 0; d <= 360; d += 10) {
         DRAW_labels (d, ri + 30);
         if      (d % 90 == 0) {
            DRAW_ball (d, -3     , ri + 20,  5, 30);
            DRAW_ball (d, -3     , ro     , 10, 30);
         } else if (d % 30 == 0) {
            DRAW_ball (d, -2     , ri + 20,  4, 30);
            DRAW_ball (d, -3     , ro     ,  8, 30);
         } else {
            DRAW_ball (d, -1     , ri + 20,  3, 30);
            DRAW_ball (d, -3     , ro     ,  6, 30);
         }
      }
   } glPopMatrix();
   glBegin         (GL_POLYGON); {
      glColor4f   (  0.6,   0.6,   0.6, 1.0f);
      glVertex3f  (-245.0, 145.0,    5.0);
      glVertex3f  (-245.0, 190.0,    5.0);
      glVertex3f  (-190.0, 245.0,    5.0);
      glVertex3f  (-145.0, 245.0,    5.0);
   } glEnd   ();
   glPushMatrix(); {
      glColor4f   (  0.0,   0.0,   0.0, 1.0f);
      glTranslatef (-210 ,  210,  50.0);
      glRotatef    ( 45.0, 0.0f, 0.0f, 1.0f);
      yFONT_print  (s_font,  8, YF_TOPCEN, "layout 90%");
      glTranslatef (   0 ,  -15,   0.0);
      yFONT_print  (s_font,  8, YF_TOPCEN, "paletton.com");
   } glPopMatrix();
   if (yMACRO_exe_mode () == MACRO_RUN) {
      glColor4f  (0.7f, 0.0f, 0.0f, 1.0f);
      glBegin    (GL_POLYGON); {
         glVertex3f (-230.0, -200.0, 10);
         glVertex3f (-200.0, -200.0, 10);
         glVertex3f (-200.0, -230.0, 10);
         glVertex3f (-230.0, -230.0, 10);
      } glEnd();
   }
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.GC0.081.85]*/ /*-[05.0090.012.!]-*/ /*-[--.---.---.--]-*/
DRAW_variants       (void)
{
   char        x_base      [LEN_LABEL]   = "";
   char        x_hex       [LEN_LABEL]   = "";
   float       x_pos       = 0.0;
   float       y_pos       = 0.0;
   int         x_col       =   0;
   int         x_row       =   0;
   int         x_val       =   0;
   int         x_cur       =   0;
   char        x_satname   [LEN_LABEL] = "";
   char        x_valname   [LEN_LABEL] = "";
   char        x_abbr      = ' ';
   glPushMatrix(); {
      glTranslatef (0.0, 50.0,  20.0);
      yCOLOR_use (YCOLOR_WHEEL);
      yCOLOR_deg2hex  (myCOLOR.degree, x_base);
      for (x_row = 0; x_row < 3; ++x_row) {
         for (x_col = 0; x_col < 2; ++x_col) {
            /*---(main labels)-----------*/
            glPushMatrix(); {
               x_cur = ((x_row * 2) + x_col) * 10;
               x_pos = 2 + x_col * 500;
               /*> y_pos = - 10 - (x_row * 30);                                       <*/
               y_pos = x_row * 30;
               VARS_seq (x_cur, &x_satname, &x_valname, &x_abbr);
               glTranslatef (x_pos , y_pos,  20.0);
               glColor4f   (  1.0,   1.0,   1.0, 1.0f);
               yFONT_print  (s_font,   7, YF_BOTLEF, x_satname);
            } glPopMatrix();
         }
      }
   } glPopMatrix();
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.860.021.24]*/ /*-[03.0060.012.!]-*/ /*-[--.---.---.--]-*/
DRAW_scale          (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           =  0;             /* loop iterator -- word          */
   char        x_text      [LEN_FULL];
   yCOLOR_use (YCOLOR_GIANT);
   for (i = -120; i <= 480; i += 10) {
      glPushMatrix(); {
         yCOLOR_deg2color  (i, 1.0);
         glTranslatef ( 370 + (i * 2.0), -win_h / 2 - 10,   0.0);
         glBegin         (GL_POLYGON); {
            glVertex3f  (    0.0,  70.0,     0.0);
            glVertex3f  (   20.0,  70.0,     0.0);
            glVertex3f  (   20.0,   0.0,     0.0);
            glVertex3f  (    0.0,   0.0,     0.0);
         } glEnd   ();
         if (s_notation == 'y') {
            glRotatef    (90, 0.0f, 0.0f, 1.0f);
            glTranslatef (  40,  -8.0,   0.0);
            glColor4f   (  0.0,   0.0,   0.0, 1.0f);
            yFONT_print  (s_font,   7, YF_MIDCEN, yCOLOR_deg2name (i));
         }
      } glPopMatrix();
      if (i % 30 == 0) {
         glPushMatrix(); {
            yCOLOR_deg2color  (i, 1.0);
            sprintf (x_text, "%d", i);
            glTranslatef ( 370 + (i * 2.0), -win_h / 2 - 10,   0.0);
            glTranslatef (  10,  80.0,   0.0);
            yFONT_print  (s_font,   8, YF_MIDCEN, x_text);
         } glPopMatrix();
      }
   }
   return 0;
}

char
DRAW_dot            (char a_type, int a_deg)
{
   float       x1, y1;
   float       x2, y2;
   float       i           =    0;
   glPushMatrix(); {
      if (a_deg >= 0) {
         glRotatef      (a_deg + 90, 0.0f, 0.0f, 1.0f);
         glTranslatef   (  20,   0.0,   5.0);
      }
      switch (a_type) {
      case  'b':  glColor4f      (0.5, 0.0, 0.0, 1.0); break;
      case  'c':  glColor4f      (0.0, 0.0, 0.5, 1.0); break;
      case  '-':  glColor4f      (0.3, 0.3, 0.3, 1.0); break;
      case  'w':  glColor4f      (1.0, 1.0, 1.0, 1.0); break;
      case  'k':  glColor4f      (0.0, 0.0, 0.0, 1.0); break;
      case  'g':  glColor4f      (0.2, 0.2, 0.2, 1.0); break;
      }
      x2 =   5.0 * sin (0 * DEG2RAD);
      y2 =   5.0 * cos (0 * DEG2RAD);
      for (i = 10; i <= 360; i +=  5) {
         x1 =   5.0 * sin (i * DEG2RAD);
         y1 =   5.0 * cos (i * DEG2RAD);
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

char
DRAW_circle         (char *a_name, int a_base, int a_comp, int a_neg, int a_pos)
{
   float       x1, y1;
   float       x2, y2;
   float       i           =    0;
   float       x_radius    =   20;
   glPushMatrix(); {
      if (strcmp (a_name, myCOLOR.harmony) == 0)  glColor4f      (0.6, 0.6, 0.6, 1.0);
      else                                        glColor4f      (0.0, 0.6, 0.0, 1.0);
      x2 =  x_radius * sin (0 * DEG2RAD);
      y2 =  x_radius * cos (0 * DEG2RAD);
      for (i = 10; i <= 360; i +=  5) {
         x1 =  x_radius * sin (i * DEG2RAD);
         y1 =  x_radius * cos (i * DEG2RAD);
         glBegin         (GL_POLYGON); {
            glVertex3f  ( 0.0,    0.0,     0.0);
            glVertex3f  (  x2,     y2,     0.0);
            glVertex3f  (  x1,     y1,     0.0);
            glVertex3f  ( 0.0,    0.0,     0.0);
         } glEnd   ();
         x2 = x1;
         y2 = y1;
      }
      if (a_neg  != a_base)  DRAW_dot ('g', a_neg);
      if (a_pos  != a_base)  DRAW_dot ('g', a_pos);
      if (a_comp != a_base)  DRAW_dot ('g', a_comp);
      DRAW_dot ('w', a_base);
      glColor4f      (0.0, 0.0, 0.0, 1.0);
      yFONT_print  (s_font,   8, YF_MIDCEN, a_name);
   } glPopMatrix();
}




#define    UPPER_LEFT    '1'
#define    UPPER_RIGHT   '2'
#define    LOWER_LEFT    '3'
#define    LOWER_RIGHT   '4'

char         /*-> tbd --------------------------------[ ------ [gz.9D0.561.44]*/ /*-[02.0060.013.!]-*/ /*-[--.---.---.--]-*/
DRAW_box            (cchar a_major, cchar a_minor, char a_size, int a_xpos, int a_ypos)
{  /*---(design notes)-------------------*/
   /*
    *  layout is a 12x12 grid  (0-11 each way)
    */
   /*---(locals)-----------+-----------+-*/
   int         x_var       =  0;             /* loop iterator -- word          */
   char        x_hex       [LEN_LABEL] = "";
   char        t           [LEN_LABEL] = "";
   float       x_wide      = 70;
   float       x_tall      = 70;
   float       x_zpos      = 10;
   a_xpos = (a_xpos * 40.0);
   a_ypos = (a_ypos * 40.0);
   switch (a_size) {
   case 'L' : x_wide = 18; x_tall = 18; a_xpos +=  2;             a_ypos += 22;  x_zpos = 20;  break;
   case 'R' : x_wide = 18; x_tall = 18; a_xpos += 22;             a_ypos += 22;  x_zpos = 20;  break;
   case 'T' : x_wide = 18; x_tall =  6; a_xpos += 10;             a_ypos += 30;  x_zpos = 20;  break;
   case 'K' : x_wide = 18; x_tall =  6; a_xpos += 10;             a_ypos += 20;  x_zpos = 20;  break;
   case 'J' : x_wide = 18; x_tall =  6; a_xpos += 10;             a_ypos += 10;  x_zpos = 20;  break;
   case 'B' : x_wide = 18; x_tall =  6; a_xpos += 10;             a_ypos +=  0;  x_zpos = 20;  break;
   case 's' : x_wide = x_tall = 30; a_xpos += 10;                 a_ypos += 10;  x_zpos = 20;  break;
   case 'c' : x_wide = x_tall = 30; a_xpos -=  5;                 a_ypos += 15;  x_zpos = 20;  break;
   case 'b' : x_wide = x_tall = 70; a_xpos += 10;                 a_ypos += 10;  x_zpos = 10;  break;
              /*> case UPPER_LEFT  : x_wide = 365; x_tall = 365;                 a_ypos +=  5;  x_zpos =  6;  break;   <* 
               *> case UPPER_RIGHT : x_wide = 165; x_tall = 245;  a_xpos +=  5;  a_ypos +=  5;  x_zpos =  0;  break;   <* 
               *> case LOWER_LEFT  : x_wide = 245; x_tall = 165;                                x_zpos =  0;  break;   <* 
               *> case LOWER_RIGHT : x_wide = 325; x_tall = 325;  a_xpos +=  5;                 x_zpos =  3;  break;   <*/
   case UPPER_LEFT  : x_wide = 365; x_tall = 365;                 a_ypos +=  5;  x_zpos =  6;  break;
   case UPPER_RIGHT : x_wide = 165; x_tall = 325;  a_xpos +=  5;  a_ypos +=  5;  x_zpos =  0;  break;
   case LOWER_LEFT  : x_wide = 325; x_tall = 165;                                x_zpos =  0;  break;
   case LOWER_RIGHT : x_wide = 165; x_tall = 165;  a_xpos +=  5;                 x_zpos =  3;  break;
   }
   if (strchr ("TKJB", a_size) != NULL) {
      glColor4f (0.0, 0.0, 0.0, 1.0);
      glBegin         (GL_POLYGON); {
         glVertex3f  ( a_xpos          - 3, a_ypos + x_tall + 3, x_zpos - 5);
         glVertex3f  ( a_xpos + x_wide + 3, a_ypos + x_tall + 3, x_zpos - 5);
         glVertex3f  ( a_xpos + x_wide + 3, a_ypos          - 3, x_zpos - 5);
         glVertex3f  ( a_xpos          - 3, a_ypos          - 3, x_zpos - 5);
      } glEnd   ();
   }
   yCOLOR_set       (a_major + a_minor, 1.0);
   glBegin         (GL_POLYGON); {
      glVertex3f  ( a_xpos         , a_ypos + x_tall, x_zpos);
      glVertex3f  ( a_xpos + x_wide, a_ypos + x_tall, x_zpos);
      glVertex3f  ( a_xpos + x_wide, a_ypos         , x_zpos);
      glVertex3f  ( a_xpos         , a_ypos         , x_zpos);
   } glEnd   ();
   if (strchr ("scb" , a_size) != NULL && myCOLOR.refs != '-') {
      glPushMatrix(); {
         if (a_minor <= 4) glColor4f    (0.0, 0.0, 0.0, 1.0);
         else              glColor4f    (1.0, 1.0, 1.0, 1.0);
         glTranslatef (a_xpos + x_wide / 2.0, a_ypos + x_tall / 2.0,  x_zpos);
         sprintf (t, "%d", a_minor);
         yFONT_print  (s_font, 8, YF_MIDCEN, t);
      } glPopMatrix();
   }
   if (strchr ("TKJB", a_size) != NULL && myCOLOR.names != '-') {
      switch (a_minor) {
      case YCOLOR_ERR : strlcpy (t, "error"    , LEN_LABEL); break;
      case YCOLOR_WRN : strlcpy (t, "warning"  , LEN_LABEL); break;
      case YCOLOR_SRC : strlcpy (t, "source"   , LEN_LABEL); break;
      case YCOLOR_SEL : strlcpy (t, "selection", LEN_LABEL); break;
      case YCOLOR_REG : strlcpy (t, "register" , LEN_LABEL); break;
      case YCOLOR_REP : strlcpy (t, "replace"  , LEN_LABEL); break;
      case YCOLOR_INP : strlcpy (t, "input"    , LEN_LABEL); break;
      case YCOLOR_WDR : strlcpy (t, "wander"   , LEN_LABEL); break;
      case YCOLOR_CUR : strlcpy (t, "cursor"   , LEN_LABEL); break;
      case YCOLOR_BLK : strlcpy (t, "black"    , LEN_LABEL); break;
      }
      glPushMatrix(); {
         glColor4f    (0.0, 0.0, 0.0, 1.0);
         glTranslatef (a_xpos - 5, a_ypos + 4,  x_zpos);
         yFONT_print  (s_font, 8, YF_MIDRIG, t);
      } glPopMatrix();
   }
   /*---(example font)-------------------*/
   if (strchr ("scb", a_size) == NULL) {
      ;;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.JF0.0C1.25]*/ /*-[02.0000.012.!]-*/ /*-[--.---.---.--]-*/
DRAW_layout         (void)
{
   /*---(locals)-----------+-----------+-*/
   int         d           =  0;             /* loop iterator -- word          */
   float       ri, ro;
   int         n           =  0;
   char        t           [LEN_LABEL] = "";
   char        x_on        =  '-';
   yVIEW_curses            (YVIEW_ALT, NULL, &x_on, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   if (x_on != 'y') return 0;
   yLOG_enter   (__FUNCTION__);
   yCOLOR_palette (myCOLOR.degree, "=", "=", "=");
   glPushMatrix(); {
      glTranslatef (-245 , -245,   0.0);
      /*---(lower-right)-----------------*/
      DRAW_box (YCOLOR_COM, YCOLOR_MED, LOWER_RIGHT,  8,  0);
      DRAW_box (YCOLOR_COM, YCOLOR_MUT, 's', 10,  1);
      DRAW_box (YCOLOR_COM, YCOLOR_DRK, 's', 10,  0);
      DRAW_box (YCOLOR_COM, YCOLOR_LIG, 's', 11,  1);
      DRAW_box (YCOLOR_COM, YCOLOR_ACC, 's', 11,  0);
      DRAW_box (YCOLOR_COM, YCOLOR_MOR, 's',  9,  2);
      DRAW_box (YCOLOR_COM, YCOLOR_MIN, 's',  9,  1);
      DRAW_box (YCOLOR_COM, YCOLOR_MAX, 's', 11,  2);
      /*---(upper-right)-----------------*/
      DRAW_box (YCOLOR_NEG, YCOLOR_MED, UPPER_RIGHT,  8,  4);
      DRAW_box (YCOLOR_NEG, YCOLOR_MUT, 's', 11, 11);
      DRAW_box (YCOLOR_NEG, YCOLOR_DRK, 's', 11, 10);
      DRAW_box (YCOLOR_NEG, YCOLOR_LIG, 's', 11,  9);
      DRAW_box (YCOLOR_NEG, YCOLOR_ACC, 's', 11,  8);
      DRAW_box (YCOLOR_NEG, YCOLOR_MOR, 's', 10, 10);
      DRAW_box (YCOLOR_NEG, YCOLOR_MIN, 's', 10, 11);
      DRAW_box (YCOLOR_NEG, YCOLOR_MAX, 's', 10,  8);
      /*---(lower-left)------------------*/
      DRAW_box (YCOLOR_POS, YCOLOR_MED, LOWER_LEFT ,  0,  0);
      DRAW_box (YCOLOR_POS, YCOLOR_MUT, 's',  0,  0);
      DRAW_box (YCOLOR_POS, YCOLOR_DRK, 's',  1,  0);
      DRAW_box (YCOLOR_POS, YCOLOR_LIG, 's',  2,  0);
      DRAW_box (YCOLOR_POS, YCOLOR_ACC, 's',  3,  0);
      DRAW_box (YCOLOR_POS, YCOLOR_MOR, 's',  1,  1);
      DRAW_box (YCOLOR_POS, YCOLOR_MIN, 's',  0,  1);
      DRAW_box (YCOLOR_POS, YCOLOR_MAX, 's',  3,  1);
      /*---(upper-left)------------------*/
      DRAW_box (YCOLOR_BAS, YCOLOR_MED, UPPER_LEFT ,  0,  3);
      DRAW_box (YCOLOR_BAS, YCOLOR_MAX, 's',  5,  9);
      DRAW_box (YCOLOR_BAS, YCOLOR_ACC, 'b',  4, 10);
      DRAW_box (YCOLOR_BAS, YCOLOR_LIG, 'b',  2, 10);
      DRAW_box (YCOLOR_BAS, YCOLOR_DRK, 'b',  0,  8);
      DRAW_box (YCOLOR_BAS, YCOLOR_MUT, 'b',  0,  6);
      DRAW_box (YCOLOR_BAS, YCOLOR_MOR, 's',  2,  7);
      DRAW_box (YCOLOR_BAS, YCOLOR_MIN, 's',  2,  8);
      /*---(browns)----------------------*/
      if (myCOLOR.extra != '-') {
         DRAW_box (YCOLOR_BRN, YCOLOR_MAX, 'R',  3,  3);
         DRAW_box (YCOLOR_BRN, YCOLOR_ACC, 'L',  3,  3);
         DRAW_box (YCOLOR_BRN, YCOLOR_LIG, 'R',  2,  3);
         DRAW_box (YCOLOR_BRN, YCOLOR_MED, 'L',  2,  3);
         DRAW_box (YCOLOR_BRN, YCOLOR_DRK, 'R',  1,  3);
         DRAW_box (YCOLOR_BRN, YCOLOR_MUT, 'L',  1,  3);
         DRAW_box (YCOLOR_BRN, YCOLOR_MOR, 'R',  0,  3);
         DRAW_box (YCOLOR_BRN, YCOLOR_MIN, 'L',  0,  3);
      }
      /*---(greys)-----------------------*/
      if (myCOLOR.extra != '-') {
         DRAW_box (YCOLOR_GRY, YCOLOR_MAX, 'R',  3,  4);
         DRAW_box (YCOLOR_GRY, YCOLOR_ACC, 'L',  3,  4);
         DRAW_box (YCOLOR_GRY, YCOLOR_LIG, 'R',  2,  4);
         DRAW_box (YCOLOR_GRY, YCOLOR_MED, 'L',  2,  4);
         DRAW_box (YCOLOR_GRY, YCOLOR_DRK, 'R',  1,  4);
         DRAW_box (YCOLOR_GRY, YCOLOR_MUT, 'L',  1,  4);
         DRAW_box (YCOLOR_GRY, YCOLOR_MOR, 'R',  0,  4);
         DRAW_box (YCOLOR_GRY, YCOLOR_MIN, 'L',  0,  4);
      }
      /*---(specials)--------------------*/
      if (myCOLOR.extra != '-') {
         DRAW_box (YCOLOR_SPE, YCOLOR_ERR, 'T',  8, 11);
         DRAW_box (YCOLOR_SPE, YCOLOR_WRN, 'J',  8, 11);
         DRAW_box (YCOLOR_SPE, YCOLOR_SRC, 'T',  8, 10);
         DRAW_box (YCOLOR_SPE, YCOLOR_INP, 'J',  8, 10);
         DRAW_box (YCOLOR_SPE, YCOLOR_REP, 'T',  8,  9);
         DRAW_box (YCOLOR_SPE, YCOLOR_SEL, 'J',  8,  9);
         DRAW_box (YCOLOR_SPE, YCOLOR_REG, 'T',  8,  8);
         DRAW_box (YCOLOR_SPE, YCOLOR_WDR, 'J',  8,  8);
         DRAW_box (YCOLOR_SPE, YCOLOR_CUR, 'T',  8,  7);
         DRAW_box (YCOLOR_SPE, YCOLOR_BLK, 'J',  8,  7);
      }
      /*---(variegated)------------------*/
      glTranslatef ( 245 ,  245,   0.0);
      if (myCOLOR.extra != '-') {
         ri  = 40;
         ro  = 20;
         for (d = 0; d <  360; d += 36) {
            DRAW_little (n++, ri, ro, d, 15, 50);
         }
      }
      /*---(done)------------------------*/
      if (myCOLOR.names != '-') {
         glColor4f    (0.0, 0.0, 0.0, 1.0);
         if (myCOLOR.conf  != '-') {
            glPushMatrix(); {
               glTranslatef (  20 ,  -55,  50.0);
               sprintf (t, ":deg %d", myCOLOR.degree);
               yFONT_print  (s_font, 8, YF_MIDLEF, t);
               glTranslatef (   0 ,  -15,   0.0);
               sprintf (t, ":har %s", myCOLOR.harmony);
               yFONT_print  (s_font, 8, YF_MIDLEF, t);
               glTranslatef (   0 ,  -15,   0.0);
               sprintf (t, ":sat %s", myCOLOR.sat_name);
               yFONT_print  (s_font, 8, YF_MIDLEF, t);
               glTranslatef (   0 ,  -15,   0.0);
               sprintf (t, ":val %s", myCOLOR.val_name);
               yFONT_print  (s_font, 8, YF_MIDLEF, t);
            } glPopMatrix();
         }
         glPushMatrix(); {
            glTranslatef (-200 ,  200,  50.0);
            yFONT_print  (s_font, 12, YF_MIDCEN, "BASE");
         } glPopMatrix();
         glPushMatrix(); {
            glTranslatef (-200 , -140,  50.0);
            yFONT_print  (s_font, 12, YF_MIDCEN, "NEG");
         } glPopMatrix();
         glPushMatrix(); {
            glTranslatef ( 150 ,  140,  50.0);
            yFONT_print  (s_font, 12, YF_MIDCEN, "POS");
         } glPopMatrix();
         glPushMatrix(); {
            glTranslatef ( 120 , -220,  50.0);
            yFONT_print  (s_font, 12, YF_MIDCEN, "COM");
         } glPopMatrix();
         if (myCOLOR.extra != '-') {
            glPushMatrix(); {
               glTranslatef (-240 ,  -43,  50.0);
               yFONT_print  (s_font,  8, YF_BOTLEF, "system greys");
            } glPopMatrix();
            glPushMatrix(); {
               glTranslatef (-240 ,  -83,  50.0);
               yFONT_print  (s_font,  8, YF_BOTLEF, "system browns");
            } glPopMatrix();
            glPushMatrix(); {
               glTranslatef (   0 ,    0,  50.0);
               yFONT_print  (s_font,  8, YF_MIDLEF, "variegated");
            } glPopMatrix();
         }
      }
      /*---(done)------------------------*/
   } glPopMatrix();
   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.750.021.05]*/ /*-[00.0000.021.!]-*/ /*-[--.---.---.--]-*/
DRAW_view_prog     (void)
{
   char        x_on        =  '-';
   /*> rc = yVIKEYS_view_size  (YVIKEYS_PROGRESS, NULL, NULL, NULL, NULL, NULL);      <*/
   /*> char yVIEW_curses            (char a_part, char *r_name, char *r_on, char *r_source, char *r_text, char *r_orient, short *r_left, short *r_wide, short *r_bott, short *r_tall)   <*/
   yVIEW_curses            (YVIEW_PROGRESS, NULL, &x_on, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   if (x_on == 'y')  DRAW_variants   ();
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.750.021.05]*/ /*-[00.0000.021.!]-*/ /*-[--.---.---.--]-*/
DRAW_view_nav      (void)
{
   /*---(locals)-------------------------*/
   char        rc          =    0;
   char        x_on        =  '-';
   int         x_left, x_bott, x_wide, x_tall;
   int         x_xmin, x_xlen, x_xmax;
   int         x_ymin, x_ylen, x_ymax;
   /*> x_on = yVIKEYS_view_size (YVIKEYS_NAV, &x_left, &x_wide, &x_bott, &x_tall, NULL);   <*/
   yVIEW_curses            (YVIEW_NAV, NULL, &x_on, NULL, NULL, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   if (x_on == 'y') {
      x_xmin = 0;
      x_xmax = x_wide;
      x_ymax = 0;
      x_ymin = -x_tall;
      DEBUG_GRAF   yLOG_complex ("alt" , "bott %4d, left %4d, wide %4d, tall %4d, on %c", x_bott, x_left, x_wide, x_tall, rc);
      DEBUG_WIND   yLOG_note    ("set viewport");
      int x, y;
      int c = 0;
      char x_name [LEN_LABEL];
      char x_abbr;
      int x_base, x_comp, x_neg, x_pos;
      for (x = 30; x <= 150; x += 90) {
         for (y = -40; y > -500; y -= 70) {
            rc = HARM_seq (c, x_name, &x_abbr, &x_base, &x_comp, &x_neg, &x_pos);
            if (rc >= 0) {
               glPushMatrix    (); {
                  glTranslatef (x,y,20.0);
                  DRAW_circle  (x_name, x_base, x_comp, x_neg, x_pos);
               } glPopMatrix   ();
               c++;
            }
         }
      }
      x =  75;
      for (y = -75; y > -500; y -= 70) {
         rc = HARM_seq (c, x_name, &x_abbr, &x_base, &x_comp, &x_neg, &x_pos);
         if (rc >= 0) {
            glPushMatrix    (); {
               glTranslatef (x,y,20.0);
               DRAW_circle  (x_name, x_base, x_comp, x_neg, x_pos);
            } glPopMatrix   ();
            c++;
         }
      }
   }
   return 0;
}

int
main                    (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(debugging)----------------------*/
   rc = PROG_urgents (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("urgents"   , rc);
   if (rc <  0) { PROG_shutdown (); return -1; }
   /*---(initialization)-----------------*/
   rc = PROG_startup (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("startup"   , rc);
   if (rc <  0) { PROG_shutdown (); return -2; }
   /*---(visual setup)-------------------*/
   rc = PROG_dawn    ();
   DEBUG_PROG   yLOG_value    ("dawn"      , rc);
   if (rc <  0) { PROG_shutdown (); return -3; }
   /*---(main-loop)----------------------*/
   rc = yVIOPENGL_main  ("10ms", "100ms", NULL);
   DEBUG_PROG   yLOG_value    ("main"      , rc);
   rc = PROG_dusk     ();
   DEBUG_PROG   yLOG_value    ("dusk"      , rc);
   /*---(wrap-up)------------------------*/
   rc = PROG_shutdown ();
   /*---(complete)-----------------------*/
   return 0;
}


