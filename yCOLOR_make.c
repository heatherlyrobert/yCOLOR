/*============================----beg-of-source---============================*/



/*===[[ HEADERS ]]========================================*/
/*---(local)-----------------------------*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"
/*---(heatherly made)--------------------*/
#include    <yX11.h>         /* CUSTOM  heatherly xlib/glx setup/teardown     */
#include    <yFONT.h>        /* CUSTOM  heatherly texture-mapped fonts        */
#include    <yGLTEX.h>       /* CUSTOM  heatherly texture handling            */
#include    <yVIKEYS.h>      /* CUSTOM  heatherly vi-keys library             */

#include    <time.h>         /* CLIBC   standard time and date handling       */

typedef struct timespec  tTSPEC;

static char  s_face     [LEN_LABEL] = "comfortaa";
static char  s_font     = -1;

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



char           DRAW_view_main     (void);
char           DRAW_view_alt      (void);
char           DRAW_view_prog     (void);
char           DRAW_view_nav      (void);

char
SET_names            (char *a_opt)
{
   if      (a_opt == NULL)                 myCOLOR.names = '-';
   else if (strcmp (a_opt, "show") == 0)   myCOLOR.names = 'y';
   else if (strcmp (a_opt, "hide") == 0)   myCOLOR.names = '-';
   return 0;
}

char
MAP_driver           (char a_dir)
{
   /*---(locals)-----------+-----------+-*/
   tMAPPED    *x_map       = NULL;
   int         x_min       =    0;
   int         x_max       =    0;
   int         i           =    0;
   int         c           =    0;
   int         x_unit      =    0;
   /*---(get the size)-------------------*/
   switch (a_dir) {
   case 'R' : case 'r' :
      x_map   = &g_ymap;
      x_max   = 500;
      break;
   case 'C' : case 'c' :
      x_map   = &g_xmap;
      x_max   = 500;
      break;
   }
   /*---(clear)--------------------------*/
   for (i= 0; i < LEN_HUGE; ++i)  x_map->map [i] =  YVIKEYS_EMPTY;
   x_map->gmin = x_map->gamin = x_map->glmin = x_map->gprev = -1;
   x_map->gmax = x_map->gamax = x_map->glmax = x_map->gnext = -1;
   /*---(do columns)---------------------*/
   for (i = 0; i <= x_max; ++i) {
      x_map->map [i] = ++x_unit - (x_max / 2);
      ++c;
   }
   x_map->uavail = x_max;
   x_map->gmin   = -(x_max / 2);
   x_map->gmax   =   x_max / 2;
   /*---(other)--------------------------*/
   if (a_dir != tolower (a_dir)) {
      x_map->ubeg  = 0;
      x_map->ucur  = 0;
      x_map->uend  = 0;
      x_map->ulen  = 0;
      x_map->utend = 0;
      x_map->gbeg  = 0;
      x_map->gcur  = 0;
      x_map->gend  = 0;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
MAP_col              (char a_type)
{
   /*> printf ("mapping cols\n");                                                     <*/
   if (a_type == YVIKEYS_INIT)  MAP_driver   ('C');
   else                         MAP_driver   ('c');
   return 0;
}

char
MAP_row              (char a_type)
{
   /*> printf ("mapping rows\n");                                                     <*/
   if (a_type == YVIKEYS_INIT)  MAP_driver   ('R');
   else                         MAP_driver   ('r');
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

/*---(opengl objects)--------------------*/
/*> static int  s_tex     =     0;                /+ texture for image              +/   <* 
 *> static int  s_fbo     =     0;                /+ framebuffer                    +/   <* 
 *> static int  s_depth   =     0;                /+ depth buffer                   +/   <*/

/*> static char        /+ PURPOSE : create a texture -----------------------------+/                               <* 
 *> TEX__create          (void)                                                                                    <* 
 *> {                                                                                                              <* 
 *>    DEBUG_GRAF  printf("texture_create () beg\n");                                                              <* 
 *>    /+---(generate)-----------------------+/                                                                    <* 
 *>    glGenFramebuffersEXT         (1, &s_fbo);                                                                   <* 
 *>    glGenTextures                (1, &s_tex);                                                                   <* 
 *>    glGenRenderbuffersEXT        (1, &s_depth);                                                                 <* 
 *>    /+---(bind)---------------------------+/                                                                    <* 
 *>    DEBUG_GRAF  printf("texture_create () bind\n");                                                             <* 
 *>    glBindFramebufferEXT         (GL_FRAMEBUFFER_EXT,  s_fbo);                                                  <* 
 *>    glBindTexture                (GL_TEXTURE_2D,       s_tex);                                                  <* 
 *>    /+---(settings)-----------------------+/                                                                    <* 
 *>    DEBUG_GRAF  printf("texture_create () settings\n");                                                         <* 
 *>    glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);              <* 
 *>    glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR);                            <* 
 *>    glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_REPEAT);                                <* 
 *>    glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_REPEAT);                                <* 
 *>    glTexEnvi                    (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);                             <* 
 *>    glTexParameteri              (GL_TEXTURE_2D,  GL_GENERATE_MIPMAP, GL_TRUE);                                 <* 
 *>    /+---(copy)---------------------------+/                                                                    <* 
 *>    DEBUG_GRAF  printf("texture_create () allocate\n");                                                         <* 
 *>    glTexImage2D                 (GL_TEXTURE_2D, 0, GL_RGBA, tex_w, tex_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);    <* 
 *>    DEBUG_GRAF  printf("texture_create () copy\n");                                                             <* 
 *>    glFramebufferTexture2DEXT    (GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, s_tex, 0);       <* 
 *>    /+---(depth)--------------------------+/                                                                    <* 
 *>    DEBUG_GRAF  printf("texture_create () depth\n");                                                            <* 
 *>    glBindRenderbufferEXT        (GL_RENDERBUFFER_EXT, s_depth);                                                <* 
 *>    glRenderbufferStorageEXT     (GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, tex_w, tex_h);                     <* 
 *>    glFramebufferRenderbufferEXT (GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, s_depth);   <* 
 *>    /+---(unbind)-------------------------+/                                                                    <* 
 *>    DEBUG_GRAF  printf("texture_create () unbind\n");                                                           <* 
 *>    glBindFramebufferEXT         (GL_FRAMEBUFFER_EXT, 0);                                                       <* 
 *>    /+---(complete)-----------------------+/                                                                    <* 
 *>    DEBUG_GRAF  printf("texture_create () end\n");                                                              <* 
 *>    return 0;                                                                                                   <* 
 *> }                                                                                                              <*/

/*> static char        /+ PURPOSE : delete a framebuffer -------------------------+/   <* 
 *> TEX__free            (void)                                                        <* 
 *> {                                                                                  <* 
 *>    DEBUG_GRAF  printf("texture_free () beg\n");                                    <* 
 *>    /+---(generate)-----------------------+/                                        <* 
 *>    glDeleteTextures                (1, &s_tex);                                    <* 
 *>    glDeleteRenderbuffersEXT        (1, &s_depth);                                  <* 
 *>    glDeleteFramebuffersEXT         (1, &s_fbo);                                    <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    DEBUG_GRAF  printf("texture_free () end\n");                                    <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

char         /*-> establish drawing settings ---------[ shoot  [gz.640.001.00]*/ /*-[00.0000.011.!]-*/ /*-[--.---.---.--]-*/
DRAW_init          (void)
{
   yVIKEYS_cmds_direct   (":layout ycolor");
   yVIKEYS_view_basic    (YVIKEYS_MAIN    , YVIKEYS_FLAT, YVIKEYS_MIDCEN, YCOLOR_GRY_MIN, DRAW_view_main );
   yVIKEYS_view_basic    (YVIKEYS_ALT     , YVIKEYS_FLAT, YVIKEYS_MIDCEN, YCOLOR_GRY_MIN, DRAW_view_alt  );
   yVIKEYS_view_simple   (YVIKEYS_PROGRESS, YCOLOR_GRY_MIN, DRAW_view_prog );
   yVIKEYS_view_simple   (YVIKEYS_NAV     , YCOLOR_GRY_MIN, DRAW_view_nav  );
   yVIKEYS_view_colors   (YCOLOR_POS, YCOLOR_BAS, YCOLOR_NEG, YCOLOR_POS);
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

char         /*-> tbd --------------------------------[ ------ [gz.SO0.1E1.D7]*/ /*-[05.00O0.012.!]-*/ /*-[--.---.---.--]-*/
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
   char        x_text      [LEN_FULL];
   char        x_base      [LEN_HEX] = "";
   char        x_hex       [LEN_HEX] = "";
   char        x_norm      [LEN_HEX] = "";
   char        x_save      = 0;
   yCOLOR_use (YCOLOR_WHEEL);
   glPushMatrix(); {
      /*> if      (a_which == 'o')  glTranslatef ( 380,  40.0,   0.0);                <* 
       *> else if (a_which == 'O')  glTranslatef ( 380,  40.0,   0.0);                <* 
       *> else                      glTranslatef (1100,  40.0,   0.0);                <*/
      for (x_deg = 0; x_deg < 360; x_deg += 10) {
         glPushMatrix(); {
            glRotatef    (x_deg + 90, 0.0f, 0.0f, 1.0f);
            /*---(set color)-------------*/
            yCOLOR_deg2hex     (x_deg, x_base);
            yCOLOR_deg2color   (x_deg, 1.0);
            strlcpy (x_norm, x_base, LEN_HEX);
            if (a_which != 'o') {
               /*> yCOLOR_variant ("--", "--", x_base, x_hex);                         <*/
               /*> yCOLOR__norming (s_cnorming, x_hex , x_norm);                      <*/
               yCOLOR_normalize (x_base, x_norm);
               yCOLOR_hex2color (x_norm, 1.0);
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
            if (x_deg % 30 == 0) {
               /*> x_save = s_cset;                                                   <* 
                *> s_cset = 7;                                                        <*/
               r2 = r1 + 20;
               yCOLOR_deg2color   (x_deg, 1.0);
               glBegin         (GL_POLYGON); {
                  glVertex3f  (r1,  r1 * sin (5.5 * DEG2RAD),     0.0);
                  glVertex3f  (r2,  r2 * sin (5.5 * DEG2RAD),     0.0);
                  glVertex3f  (r2, -r2 * sin (5.5 * DEG2RAD),     0.0);
                  glVertex3f  (r1, -r1 * sin (5.5 * DEG2RAD),     0.0);
               } glEnd   ();
               /*> s_cset = x_save;                                                   <*/
               yCOLOR_hex2color (x_norm, 1.0);
               /*> yCOLOR_deg2color   (x_deg, 1.0);                                   <*/
            }
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
               /*> glPushMatrix(); {                                                  <* 
                *>    x1 =  40.0 * sin (  60 * DEG2RAD);                              <* 
                *>    y1 =  40.0 * cos (  60 * DEG2RAD);                              <* 
                *>    x2 =  40.0 * sin ( 120 * DEG2RAD);                              <* 
                *>    y2 =  40.0 * cos ( 120 * DEG2RAD);                              <* 
                *>    glBegin         (GL_POLYGON); {                                 <* 
                *>       glVertex3f  ( 0.0,    0.0,     0.0);                         <* 
                *>       glVertex3f  (  x2,     y2,     0.0);                         <* 
                *>       glVertex3f  (  x1,     y1,     0.0);                         <* 
                *>       glVertex3f  ( 0.0,    0.0,     0.0);                         <* 
                *>    } glEnd   ();                                                   <* 
                *> } glPopMatrix();                                                   <*/
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
                  if (x_deg < 180) glRotatef    (180       , 0.0f, 0.0f, 1.0f);
                  yFONT_print  (s_font,   8, YF_MIDCEN, x_text);
               } glPopMatrix();
            }
            glColor4f    ( 0.0, 0.0, 0.0, 1.0);
            if (x_deg == myCOLOR.neg) {
               glPushMatrix(); {
                  glTranslatef ( 165,   0.0,   0.0);
                  DRAW_dot ('k', -1);
                  /*> if (x_deg < 180) glRotatef    (180       , 0.0f, 0.0f, 1.0f);   <* 
                   *> yFONT_print  (s_font,   8, YF_MIDCEN, "X");                     <*/
               } glPopMatrix();
            }
            if (x_deg == myCOLOR.pos) {
               glPushMatrix(); {
                  glTranslatef ( 165,   0.0,   0.0);
                  DRAW_dot ('k', -1);
                  /*> if (x_deg < 180) glRotatef    (180       , 0.0f, 0.0f, 1.0f);   <* 
                   *> yFONT_print  (s_font,   8, YF_MIDCEN, "X");                     <*/
               } glPopMatrix();
            }
            if (x_deg == myCOLOR.comp) {
               glPushMatrix(); {
                  glTranslatef ( 165,   0.0,   0.0);
                  DRAW_dot ('k', -1);
                  /*> if (x_deg < 180) glRotatef    (180       , 0.0f, 0.0f, 1.0f);   <* 
                   *> yFONT_print  (s_font,   8, YF_MIDCEN, "X");                     <*/
               } glPopMatrix();
            }
            if (myCOLOR.names == 'y') {
               glPushMatrix(); {
                  glTranslatef ( 200,   0.0,   0.0);
                  if (x_deg < 180) glRotatef    (180       , 0.0f, 0.0f, 1.0f);
                  /*> yFONT_print  (s_font,   8, YF_MIDCEN, x_norm);                  <*/
                  yFONT_print  (s_font,   8, YF_MIDCEN, yCOLOR_deg2name (x_deg));
               } glPopMatrix();
            }
            glColor4f    ( 1.0, 1.0, 1.0, 1.0);
            if (x_deg == myCOLOR.degree) {
               glPushMatrix(); {
                  glTranslatef ( 165,   0.0,  10.0);
                  DRAW_dot ('w', -1);
                  /*> if (x_deg < 180) glRotatef    (180       , 0.0f, 0.0f, 1.0f);   <*/
                  /*> yFONT_print  (s_font,   8, YF_MIDCEN, "X");                     <*/
               } glPopMatrix();
            }
         } glPopMatrix();
      }
   } glPopMatrix();
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.GC0.081.85]*/ /*-[05.0090.012.!]-*/ /*-[--.---.---.--]-*/
DRAW_variants       (void)
{
   char        x_base      [LEN_HEX]   = "";
   char        x_hex       [LEN_HEX]   = "";
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
            glPushMatrix(); {
               x_cur = ((x_row * 2) + x_col) * 10;
               x_pos = 2 + x_col * 500;
               y_pos = - 10 - (x_row * 30);
               VARS_seq (x_cur, &x_satname, &x_valname, &x_abbr);
               glTranslatef (x_pos , y_pos,  20.0);
               glColor4f   (  1.0,   1.0,   1.0, 1.0f);
               yFONT_print  (s_font,   7, YF_BOTLEF, x_satname);
            } glPopMatrix();
            for (x_val = 0; x_val < 10; ++x_val) {
               x_cur = ((x_row * 2) + x_col) * 10 + x_val;
               x_pos = 5 + x_col * 500 + x_val * 50;
               y_pos = -30 - (x_row * 30);
               VARS_seq (x_cur, &x_satname, &x_valname, &x_abbr);
               yCOLOR_variant   (x_satname, x_valname, x_base, x_hex);
               /*> printf ("row %d, col %d, val %2d, cur %3d, x %4.0f, y %4.0f, sat %-15.15s, val %-15.15s, base %-7.7s, hex  %-7.7s\n",   <* 
                *>       x_row, x_col, x_val, x_cur, x_pos, y_pos, x_satname, x_valname, x_base, x_hex);                                   <*/
               glPushMatrix(); {
                  glTranslatef (x_pos , y_pos,  20.0);
                  yCOLOR_hex2color (x_hex, 1.0);
                  glBegin         (GL_POLYGON); {
                     glVertex3f  (    0.0,  20.0,     0.0);
                     glVertex3f  (   40.0,  20.0,     0.0);
                     glVertex3f  (   40.0,   0.0,     0.0);
                     glVertex3f  (    0.0,   0.0,     0.0);
                  } glEnd   ();
                  glColor4f   (  0.0,   0.0,   0.0, 1.0f);
                  glTranslatef (0     , 0     ,  +5.0);
                  yFONT_print  (s_font,   7, YF_BOTLEF, x_valname);
                  if (strcmp (x_satname, myCOLOR.sat_name) == 0) {
                     if (strcmp (x_valname, myCOLOR.val_name) == 0) {
                        glTranslatef (20    ,  15   ,  +5.0);
                        DRAW_dot ('w', -1);
                     }
                  }
               } glPopMatrix();
            }
         }
      }
   } glPopMatrix();
   return 0;
}

/*> char         /+-> tbd --------------------------------[ ------ [gz.980.051.26]+/ /+-[04.0070.00#.!]-+/ /+-[--.---.---.--]-+/   <* 
 *> DRAW_normings       (void)                                                                                                     <* 
 *> {                                                                                                                              <* 
 *>    int         i           = 0;                                                                                                <* 
 *>    int         x_index     = 0;                                                                                                <* 
 *>    char        x_base      [LEN_HEX] = "";                                                                                     <* 
 *>    char        x_hex       [LEN_HEX] = "";                                                                                     <* 
 *>    char        x_norm      [LEN_HEX] = "";                                                                                     <* 
 *>    yCOLOR_use (YCOLOR_WHEEL);                                                                                                  <* 
 *>    yCOLOR_deg2hex     (myCOLOR.degree, x_base);                                                                                <* 
 *>    yCOLOR_variant ("--", "--", x_base, x_hex);                                                                                  <* 
 *>    glPushMatrix(); {                                                                                                           <* 
 *>       glTranslatef ( 730 , -win_h / 2 +  80,   0.0);                                                                           <* 
 *>       for (i = 0; i < s_nnorming; ++i) {                                                                                       <* 
 *>          if (s_normings [i].abbr[0] == '\0') break;                                                                            <* 
 *>          yCOLOR__norming (i, x_hex , x_norm);                                                                                  <* 
 *>          yCOLOR_hex2color (x_norm, 1.0);                                                                                       <* 
 *>          glBegin         (GL_POLYGON); {                                                                                       <* 
 *>             glVertex3f  (    0.0,  50.0,     0.0);                                                                             <* 
 *>             glVertex3f  (  100.0,  50.0,     0.0);                                                                             <* 
 *>             glVertex3f  (  100.0,   0.0,     0.0);                                                                             <* 
 *>             glVertex3f  (    0.0,   0.0,     0.0);                                                                             <* 
 *>          } glEnd   ();                                                                                                         <* 
 *>          glPushMatrix(); {                                                                                                     <* 
 *>             glColor4f   (  0.0,   0.0,   0.0, 1.0f);                                                                           <* 
 *>             glTranslatef (50.0,  10.0,   5.0);                                                                                 <* 
 *>             yFONT_print  (s_font,   8, YF_MIDCEN, x_norm);                                                                     <* 
 *>             glTranslatef ( 0.0,  10.0,   5.0);                                                                                 <* 
 *>             yFONT_print  (s_font,   8, YF_MIDCEN, s_normings [i].name);                                                        <* 
 *>          } glPopMatrix();                                                                                                      <* 
 *>          if (i == s_cnorming) {                                                                                                <* 
 *>             glPushMatrix(); {                                                                                                  <* 
 *>                glColor4f   (  1.0,   1.0,   1.0, 1.0f);                                                                        <* 
 *>                glTranslatef (+90 ,  12.0,   0.0);                                                                              <* 
 *>                yFONT_print  (s_font,   8, YF_MIDLEF, "curr");                                                                  <* 
 *>             } glPopMatrix();                                                                                                   <* 
 *>          }                                                                                                                     <* 
 *>          glTranslatef (   0,  50.0,   0.0);                                                                                    <* 
 *>       }                                                                                                                        <* 
 *>    } glPopMatrix();                                                                                                            <* 
 *>    return 0;                                                                                                                   <* 
 *> }                                                                                                                              <*/

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
DRAW_box            (cint a_slot, char a_size, int a_xpos, int a_ypos)
{  /*---(design notes)-------------------*/
   /*
    *  layout is a 12x12 grid  (0-11 each way)
    */
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
   case 's' : x_wide = x_tall = 30; a_xpos += 10;                 a_ypos += 10;  x_zpos = 20;  break;
   case 'c' : x_wide = x_tall = 30; a_xpos -=  5;                 a_ypos += 15;  x_zpos = 20;  break;
   case 'b' : x_wide = x_tall = 70; a_xpos += 10;                 a_ypos += 10;  x_zpos = 10;  break;
   case UPPER_LEFT  : x_wide = 365; x_tall = 365;                 a_ypos +=  5;  x_zpos =  6;  break;
   case UPPER_RIGHT : x_wide = 165; x_tall = 245;  a_xpos +=  5;  a_ypos +=  5;  x_zpos =  0;  break;
   case LOWER_LEFT  : x_wide = 245; x_tall = 165;                                x_zpos =  0;  break;
   case LOWER_RIGHT : x_wide = 325; x_tall = 325;  a_xpos +=  5;                 x_zpos =  3;  break;
   }
   yCOLOR_set       (a_slot, 1.0);
   glBegin         (GL_POLYGON); {
      glVertex3f  ( a_xpos         , a_ypos + x_tall, x_zpos);
      glVertex3f  ( a_xpos + x_wide, a_ypos + x_tall, x_zpos);
      glVertex3f  ( a_xpos + x_wide, a_ypos         , x_zpos);
      glVertex3f  ( a_xpos         , a_ypos         , x_zpos);
   } glEnd   ();
   /*---(example font)-------------------*/
   if (strchr ("scb", a_size) == NULL) {
      ;;
   }
   /*---(complete)-----------------------*/
   return 0;
}

/*> char         /+-> tbd --------------------------------[ ------ [gz.9D0.561.44]+/ /+-[02.0060.013.!]-+/ /+-[--.---.---.--]-+/   <* 
 *> DRAW_box            (char *a_base, char a_var, char a_size, int a_xpos, int a_ypos)                                            <* 
 *> {  /+---(design notes)-------------------+/                                                                                    <* 
 *>    /+                                                                                                                          <* 
 *>     *  layout is a 12x12 grid  (0-11 each way)                                                                                 <* 
 *>     +/                                                                                                                         <* 
 *>    /+---(locals)-----------+-----------+-+/                                                                                    <* 
 *>    int         x_var       =  0;             /+ loop iterator -- word          +/                                              <* 
 *>    char        x_hex       [LEN_HEX] = "";                                                                                     <* 
 *>    char        x_text      [LEN_HEX] = "";                                                                                     <* 
 *>    float       x_wide      = 70;                                                                                               <* 
 *>    float       x_tall      = 70;                                                                                               <* 
 *>    float       x_zpos      =  0;                                                                                               <* 
 *>    a_xpos = (a_xpos * 40.0);                                                                                                   <* 
 *>    a_ypos = (a_ypos * 40.0);                                                                                                   <* 
 *>    switch (a_size) {                                                                                                           <* 
 *>    case 's' : x_wide = x_tall = 30; a_xpos += 10;                 a_ypos += 10;  x_zpos = 20;  break;                          <* 
 *>    case 'c' : x_wide = x_tall = 30; a_xpos -=  5;                 a_ypos += 15;  x_zpos = 20;  break;                          <* 
 *>    case 'b' : x_wide = x_tall = 70; a_xpos += 10;                 a_ypos += 10;  x_zpos = 10;  break;                          <* 
 *>    case UPPER_LEFT  : x_wide = 365; x_tall = 365;                 a_ypos +=  5;  x_zpos =  6;  break;                          <* 
 *>    case UPPER_RIGHT : x_wide = 165; x_tall = 245;  a_xpos +=  5;  a_ypos +=  5;  x_zpos =  0;  break;                          <* 
 *>    case LOWER_LEFT  : x_wide = 245; x_tall = 165;                                x_zpos =  0;  break;                          <* 
 *>    case LOWER_RIGHT : x_wide = 325; x_tall = 325;  a_xpos +=  5;                 x_zpos =  3;  break;                          <* 
 *>    }                                                                                                                           <* 
 *>    yCOLOR_accent    (a_var, a_base, x_hex);                                                                                    <* 
 *>    yCOLOR_hex2color (x_hex, 1.0);                                                                                              <* 
 *>    glBegin         (GL_POLYGON); {                                                                                             <* 
 *>       glVertex3f  ( a_xpos         , a_ypos + x_tall, x_zpos);                                                                 <* 
 *>       glVertex3f  ( a_xpos + x_wide, a_ypos + x_tall, x_zpos);                                                                 <* 
 *>       glVertex3f  ( a_xpos + x_wide, a_ypos         , x_zpos);                                                                 <* 
 *>       glVertex3f  ( a_xpos         , a_ypos         , x_zpos);                                                                 <* 
 *>    } glEnd   ();                                                                                                               <* 
 *>    if (s_notation == 'y') {                                                                                                    <* 
 *>       /+> yCOLOR_variant ("none", a_base, x_hex);                                     <*                                       <* 
 *>        *> yCOLOR_hex2color (x_hex, 1.0);                                                     <+/                               <* 
 *>       glPushMatrix(); {                                                                                                        <* 
 *>          sprintf (x_text, "%-2.2s", a_var);                                                                                    <* 
 *>          glTranslatef ( a_xpos + (x_wide/2), a_ypos + 10, 30.0);                                                               <* 
 *>          glColor4f   (  0.0,   0.0,   0.0, 1.0f);                                                                              <* 
 *>          yFONT_print  (s_font,   8, YF_MIDCEN, x_text);                                                                        <* 
 *>          glTranslatef ( 0.0, 15.0, 0.0);                                                                                       <* 
 *>          yFONT_print  (s_font,   8, YF_MIDCEN, x_hex);                                                                         <* 
 *>       } glPopMatrix();                                                                                                         <* 
 *>    }                                                                                                                           <* 
 *>    return 0;                                                                                                                   <* 
 *> }                                                                                                                              <*/

char         /*-> tbd --------------------------------[ ------ [gz.JF0.0C1.25]*/ /*-[02.0000.012.!]-*/ /*-[--.---.---.--]-*/
DRAW_layout         (void)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =  0;             /* loop iterator -- word          */
   int         x_var       =  0;             /* loop iterator -- word          */
   float       x           =  0.0;
   float       y           =  0.0;
   float       x_inc       = 80.0;
   char        x_text      [LEN_FULL];
   int         x_set       =  0;             /* loop iterator -- word          */
   char        x_base      [LEN_HEX] = "";
   char        x_hex1      [LEN_HEX] = "";
   char        x_hex2      [LEN_HEX] = "";
   char        x_hex3      [LEN_HEX] = "";
   char        x_hex4      [LEN_HEX] = "";
   yCOLOR_use (YCOLOR_WHEEL);
   yCOLOR_palette (myCOLOR.degree, "--", myCOLOR.sat_name, myCOLOR.val_name);
   glPushMatrix(); {
      glTranslatef (-245 , -245,   0.0);
      /*---(lower-right)-----------------*/
      DRAW_box (YCOLOR_COM_MED, LOWER_RIGHT,  4,  0);
      DRAW_box (YCOLOR_COM_MUT, 's', 10,  1);
      DRAW_box (YCOLOR_COM_DRK, 's', 10,  0);
      DRAW_box (YCOLOR_COM_LIG, 's', 11,  1);
      DRAW_box (YCOLOR_COM_ACC, 's', 11,  0);
      DRAW_box (YCOLOR_COM_MOR, 's',  9,  2);
      DRAW_box (YCOLOR_COM_MIN, 's',  9,  1);
      DRAW_box (YCOLOR_COM_MAX, 's', 11,  2);
      /*---(upper-right)-----------------*/
      DRAW_box (YCOLOR_NEG_MED, UPPER_RIGHT,  8,  6);
      DRAW_box (YCOLOR_NEG_MUT, 's', 11, 11);
      DRAW_box (YCOLOR_NEG_DRK, 's', 11, 10);
      DRAW_box (YCOLOR_NEG_LIG, 's', 11,  9);
      DRAW_box (YCOLOR_NEG_ACC, 's', 11,  8);
      DRAW_box (YCOLOR_NEG_MOR, 's', 10, 10);
      DRAW_box (YCOLOR_NEG_MIN, 's', 10, 11);
      DRAW_box (YCOLOR_NEG_MAX, 's', 10,  8);
      /*---(lower-left)------------------*/
      DRAW_box (YCOLOR_POS_MED, LOWER_LEFT ,  0,  0);
      DRAW_box (YCOLOR_POS_MUT, 's',  0,  0);
      DRAW_box (YCOLOR_POS_DRK, 's',  1,  0);
      DRAW_box (YCOLOR_POS_LIG, 's',  2,  0);
      DRAW_box (YCOLOR_POS_ACC, 's',  3,  0);
      DRAW_box (YCOLOR_POS_MOR, 's',  1,  1);
      DRAW_box (YCOLOR_POS_MIN, 's',  0,  1);
      DRAW_box (YCOLOR_POS_MAX, 's',  3,  1);
      /*---(upper-left)------------------*/
      DRAW_box (YCOLOR_BAS_MED, UPPER_LEFT ,  0,  3);
      DRAW_box (YCOLOR_BAS_MAX, 's',  5,  9);
      DRAW_box (YCOLOR_BAS_ACC, 'b',  4, 10);
      DRAW_box (YCOLOR_BAS_LIG, 'b',  2, 10);
      DRAW_box (YCOLOR_BAS_DRK, 'b',  0,  8);
      DRAW_box (YCOLOR_BAS_MUT, 'b',  0,  6);
      DRAW_box (YCOLOR_BAS_MOR, 's',  2,  7);
      DRAW_box (YCOLOR_BAS_MIN, 's',  2,  8);
   } glPopMatrix();
   return 0;
}

/*> char         /+-> tbd --------------------------------[ ------ [gz.JF0.0C1.25]+/ /+-[02.0000.012.!]-+/ /+-[--.---.---.--]-+/   <* 
 *> DRAW_layout         (void)                                                                                                     <* 
 *> {                                                                                                                              <* 
 *>    /+---(locals)-----------+-----------+-+/                                                                                    <* 
 *>    int         x_deg       =  0;             /+ loop iterator -- word          +/                                              <* 
 *>    int         x_var       =  0;             /+ loop iterator -- word          +/                                              <* 
 *>    float       x           =  0.0;                                                                                             <* 
 *>    float       y           =  0.0;                                                                                             <* 
 *>    float       x_inc       = 80.0;                                                                                             <* 
 *>    char        x_text      [LEN_FULL];                                                                                         <* 
 *>    int         x_set       =  0;             /+ loop iterator -- word          +/                                              <* 
 *>    char        x_base      [LEN_HEX] = "";                                                                                     <* 
 *>    char        x_hex1      [LEN_HEX] = "";                                                                                     <* 
 *>    char        x_hex2      [LEN_HEX] = "";                                                                                     <* 
 *>    char        x_hex3      [LEN_HEX] = "";                                                                                     <* 
 *>    char        x_hex4      [LEN_HEX] = "";                                                                                     <* 
 *>    yCOLOR_use (YCOLOR_WHEEL);                                                                                                  <* 
 *>    yCOLOR_palette (myCOLOR.degree, myCOLOR.harmony, myCOLOR.sat_name, myCOLOR.val_name);                                       <* 
 *>    glPushMatrix(); {                                                                                                           <* 
 *>       glTranslatef (-245 , -245,   0.0);                                                                                       <* 
 *>       /+---(lower-right)-----------------+/                                                                                    <* 
 *>       yCOLOR_deg2hex   (myCOLOR.comp, x_base);                                                                                 <* 
 *>       yCOLOR_variant   ("--", "--", x_base, x_hex4);                                                                           <* 
 *>       yCOLOR_hex2color (x_hex4, 1.0);                                                                                          <* 
 *>       DRAW_box (x_hex4 , '.', LOWER_RIGHT,  4,  0);                                                                            <* 
 *>       DRAW_box (x_hex4 , 'v'       , 's', 10,  1);                                                                             <* 
 *>       DRAW_box (x_hex4 , '-'       , 's', 10,  0);                                                                             <* 
 *>       DRAW_box (x_hex4 , '+'       , 's', 11,  1);                                                                             <* 
 *>       DRAW_box (x_hex4 , '^'       , 's', 11,  0);                                                                             <* 
 *>       DRAW_box (x_hex4 , '#'       , 's',  9,  2);                                                                             <* 
 *>       /+---(upper-right)-----------------+/                                                                                    <* 
 *>       yCOLOR_deg2hex   (myCOLOR.neg, x_base);                                                                                  <* 
 *>       yCOLOR_variant   ("--", "--", x_base, x_hex2);                                                                           <* 
 *>       yCOLOR_hex2color (x_hex2, 1.0);                                                                                          <* 
 *>       DRAW_box (x_hex2 , '.'       , UPPER_RIGHT,  8,  6);                                                                     <* 
 *>       DRAW_box (x_hex2 , 'v'       , 's', 11, 11);                                                                             <* 
 *>       DRAW_box (x_hex2 , '-'       , 's', 11, 10);                                                                             <* 
 *>       DRAW_box (x_hex2 , '+'       , 's', 11,  9);                                                                             <* 
 *>       DRAW_box (x_hex2 , '^'       , 's', 11,  8);                                                                             <* 
 *>       DRAW_box (x_hex2 , '#'       , 's', 10, 10);                                                                             <* 
 *>       /+---(lower-left)------------------+/                                                                                    <* 
 *>       yCOLOR_deg2hex   (myCOLOR.pos, x_base);                                                                                  <* 
 *>       yCOLOR_variant   ("--", "--", x_base, x_hex3);                                                                           <* 
 *>       yCOLOR_hex2color (x_hex3, 1.0);                                                                                          <* 
 *>       DRAW_box (x_hex3 , '.'       , LOWER_LEFT ,  0,  0);                                                                     <* 
 *>       DRAW_box (x_hex3 , 'v'       , 's',  0,  0);                                                                             <* 
 *>       DRAW_box (x_hex3 , '-'       , 's',  1,  0);                                                                             <* 
 *>       DRAW_box (x_hex3 , '+'       , 's',  2,  0);                                                                             <* 
 *>       DRAW_box (x_hex3 , '^'       , 's',  3,  0);                                                                             <* 
 *>       DRAW_box (x_hex3 , '#'       , 's',  2,  1);                                                                             <* 
 *>       /+---(upper-left)------------------+/                                                                                    <* 
 *>       yCOLOR_deg2hex   (myCOLOR.degree, x_base);                                                                               <* 
 *>       yCOLOR_variant   ("--", "--", x_base, x_hex1);                                                                           <* 
 *>       yCOLOR_hex2color (x_hex1, 1.0);                                                                                          <* 
 *>       DRAW_box (x_hex1 , '.'       , UPPER_LEFT ,  0,  3);                                                                     <* 
 *>       DRAW_box (x_hex1 , 'v'       , 'b',  0,  6);                                                                             <* 
 *>       DRAW_box (x_hex1 , '-'       , 'b',  0,  8);                                                                             <* 
 *>       DRAW_box (x_hex1 , '+'       , 'b',  2, 10);                                                                             <* 
 *>       DRAW_box (x_hex1 , '^'       , 'b',  4, 10);                                                                             <* 
 *>       DRAW_box (x_hex1 , '#'       , 's',  2,  9);                                                                             <* 
 *>       /+> if (s_accent != 'y') {                                                      <+/                                      <* 
 *>       /+> /+---(on upper left)---------------+/                                       <*                                       <* 
 *>        *> DRAW_box (x_hex2 , '.'       , 's',  5,  5);                                <*                                       <* 
 *>        *> DRAW_box (x_hex4 , '.'       , 's',  6,  5);                                <*                                       <* 
 *>        *> DRAW_box (x_hex3 , '.'       , 's',  6,  6);                                <*                                       <* 
 *>        *> /+---(on lower left)---------------+/                                       <*                                       <* 
 *>        *> DRAW_box (x_hex4 , '.'       , 's',  3,  2);                                <*                                       <* 
 *>        *> DRAW_box (x_hex2 , '.'       , 's',  4,  2);                                <*                                       <* 
 *>        *> DRAW_box (x_hex1 , '.'       , 's',  5,  2);                                <*                                       <* 
 *>        *> /+---(on upper right)--------------+/                                       <*                                       <* 
 *>        *> DRAW_box (x_hex4 , '.'       , 's',  9,  8);                                <*                                       <* 
*>        *> DRAW_box (x_hex3 , '.'       , 's',  9,  7);                                <*                                       <* 
*>        *> DRAW_box (x_hex1 , '.'       , 's',  9,  6);                                <*                                       <* 
*>        *> /+---(on lower right)--------------+/                                       <*                                       <* 
*>        *> DRAW_box (x_hex2 , '.'       , 's',  8,  2);                                <*                                       <* 
*>        *> DRAW_box (x_hex3 , '.'       , 's',  9,  3);                                <+/                                      <* 
*>       /+> }                                                                           <+/                                      <* 
*>    } glPopMatrix();                                                                                                            <* 
*>    return 0;                                                                                                                   <* 
*> }                                                                                                                              <*/

char         /*-> tbd --------------------------------[ ------ [gz.750.021.05]*/ /*-[00.0000.021.!]-*/ /*-[--.---.---.--]-*/
DRAW_view_prog     (void)
{
   char        rc          =    0;
   rc = yVIKEYS_view_size  (YVIKEYS_PROGRESS, NULL, NULL, NULL, NULL, NULL);
   if (rc == 'y')  DRAW_variants   ();
}

char         /*-> tbd --------------------------------[ ------ [gz.750.021.05]*/ /*-[00.0000.021.!]-*/ /*-[--.---.---.--]-*/
DRAW_view_nav      (void)
{
   /*---(locals)-------------------------*/
   char        rc          =    0;
   int         x_left, x_bott, x_wide, x_tall;
   int         x_xmin, x_xlen, x_xmax;
   int         x_ymin, x_ylen, x_ymax;
   rc = yVIKEYS_view_size (YVIKEYS_NAV, &x_left, &x_wide, &x_bott, &x_tall, NULL);
   if (rc == 'y') {
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

char         /*-> tbd --------------------------------[ ------ [gz.750.021.05]*/ /*-[00.0000.021.!]-*/ /*-[--.---.---.--]-*/
DRAW_view_alt      (void)
{
   /*---(locals)-------------------------*/
   char        rc          =    0;
   rc = yVIKEYS_view_size (YVIKEYS_ALT, NULL, NULL, NULL, NULL, NULL);
   if (rc == 'y') DRAW_layout ();
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.750.021.05]*/ /*-[00.0000.021.!]-*/ /*-[--.---.---.--]-*/
DRAW_view_main     (void)
{
   /*---(locals)-------------------------*/
   char        rc          =    0;
   int         x_left, x_bott, x_wide, x_tall;
   int         x_xmin, x_xlen, x_xmax;
   int         x_ymin, x_ylen, x_ymax;
   /*---(progress)-----------------------*/
   /*> rc = yVIKEYS_view_size  (YVIKEYS_PROGRESS, &x_left, &x_wide, &x_bott, &x_tall, NULL);                                                        <* 
    *> if (rc == 'y') {                                                                                                                             <* 
    *>    /+> x_xmin = 0;                                                                                                                     <*    <* 
    *>     *> x_xmax = x_wide;                                                                                                                <*    <* 
    *>     *> x_ymax = 0;                                                                                                                     <*    <* 
    *>     *> x_ymin = -x_tall;                                                                                                               <*    <* 
    *>     *> DEBUG_GRAF   yLOG_complex ("progress" , "bott %4d, left %4d, wide %4d, tall %4d, on %c", x_bott, x_left, x_wide, x_tall, rc);   <*    <* 
    *>     *> DEBUG_WIND   yLOG_note    ("set viewport");                                                                                     <*    <* 
    *>     *> glViewport      (x_left, x_bott, x_wide, x_tall);                                                                               <*    <* 
    *>     *> glMatrixMode    (GL_PROJECTION);                                                                                                <*    <* 
    *>     *> glLoadIdentity  ();                                                                                                             <*    <* 
    *>     *> glOrtho         (x_xmin, x_xmax, x_ymin, x_ymax,  -500.0,   500.0);                                                             <*    <* 
    *>     *> glMatrixMode    (GL_MODELVIEW);                                                                                                 <*    <* 
    *>     *> DEBUG_GRAF   yLOG_note    ("draw background");                                                                                  <*    <* 
    *>     *> glPushMatrix    (); {                                                                                                           <*    <* 
    *>     *>    glColor4f      (0.0, 0.0, 0.0, 1.0);                                                                                         <*    <* 
    *>     *>    glBegin         (GL_POLYGON); {                                                                                              <*    <* 
    *>     *>       glVertex3f  (x_xmin          , x_ymax          ,  0.0f);                                                                  <*    <* 
    *>     *>       glVertex3f  (x_xmax          , x_ymax          ,  0.0f);                                                                  <*    <* 
    *>     *>       glVertex3f  (x_xmax          , x_ymin          ,  0.0f);                                                                  <*    <* 
    *>     *>       glVertex3f  (x_xmin          , x_ymin          ,  0.0f);                                                                  <*    <* 
    *>     *>    } glEnd   ();                                                                                                                <*    <* 
    *>     *> } glPopMatrix   ();                                                                                                             <+/   <* 
    *>    DRAW_variants   ();                                                                                                                       <* 
    *> }                                                                                                                                            <*/
   /*---(alt)----------------------------*/
   /*> rc = yVIKEYS_view_size (YVIKEYS_NAV, &x_left, &x_wide, &x_bott, &x_tall, NULL);                                               <* 
    *> if (rc == 'y') {                                                                                                              <* 
    *>    x_xmin = 0;                                                                                                                <* 
    *>    x_xmax = x_wide;                                                                                                           <* 
    *>    x_ymax = 0;                                                                                                                <* 
    *>    x_ymin = -x_tall;                                                                                                          <* 
    *>    DEBUG_GRAF   yLOG_complex ("alt" , "bott %4d, left %4d, wide %4d, tall %4d, on %c", x_bott, x_left, x_wide, x_tall, rc);   <* 
    *>    DEBUG_WIND   yLOG_note    ("set viewport");                                                                                <* 
    *>    /+> glViewport      (x_left, x_bott, x_wide, x_tall);                           <*                                         <* 
    *>     *> glMatrixMode    (GL_PROJECTION);                                            <*                                         <* 
    *>     *> glLoadIdentity  ();                                                         <*                                         <* 
    *>     *> glOrtho         (x_xmin, x_xmax, x_ymin, x_ymax,  -500.0,   500.0);         <*                                         <* 
    *>     *> glMatrixMode    (GL_MODELVIEW);                                             <*                                         <* 
    *>     *> DEBUG_GRAF   yLOG_note    ("draw background");                              <*                                         <* 
    *>     *> glPushMatrix    (); {                                                       <*                                         <* 
    *>     *>    glColor4f      (0.0, 0.0, 0.0, 1.0);                                     <*                                         <* 
    *>     *>    glBegin         (GL_POLYGON); {                                          <*                                         <* 
    *>     *>       glVertex3f  (x_xmin          , x_ymax          ,  0.0f);              <*                                         <* 
    *>     *>       glVertex3f  (x_xmax          , x_ymax          ,  0.0f);              <*                                         <* 
    *>     *>       glVertex3f  (x_xmax          , x_ymin          ,  0.0f);              <*                                         <* 
    *>     *>       glVertex3f  (x_xmin          , x_ymin          ,  0.0f);              <*                                         <* 
    *>     *>    } glEnd   ();                                                            <*                                         <* 
    *>     *> } glPopMatrix   ();                                                         <+/                                        <* 
    *>    int x, y;                                                                                                                  <* 
    *>    int c = 0;                                                                                                                 <* 
    *>    char x_name [LEN_LABEL];                                                                                                   <* 
    *>    char x_abbr;                                                                                                               <* 
    *>    int x_base, x_comp, x_neg, x_pos;                                                                                          <* 
    *>    for (x = 30; x <= 150; x += 90) {                                                                                          <* 
    *>       for (y = -40; y > -500; y -= 70) {                                                                                      <* 
    *>          rc = HARM_seq (c, x_name, &x_abbr, &x_base, &x_comp, &x_neg, &x_pos);                                                <* 
    *>          if (rc >= 0) {                                                                                                       <* 
    *>             glPushMatrix    (); {                                                                                             <* 
    *>                glTranslatef (x,y,20.0);                                                                                       <* 
    *>                DRAW_circle  (x_name, x_base, x_comp, x_neg, x_pos);                                                           <* 
    *>             } glPopMatrix   ();                                                                                               <* 
    *>             c++;                                                                                                              <* 
    *>          }                                                                                                                    <* 
    *>       }                                                                                                                       <* 
    *>    }                                                                                                                          <* 
    *>    x =  75;                                                                                                                   <* 
    *>    for (y = -75; y > -500; y -= 70) {                                                                                         <* 
    *>       rc = HARM_seq (c, x_name, &x_abbr, &x_base, &x_comp, &x_neg, &x_pos);                                                   <* 
    *>       if (rc >= 0) {                                                                                                          <* 
    *>          glPushMatrix    (); {                                                                                                <* 
    *>             glTranslatef (x,y,20.0);                                                                                          <* 
    *>             DRAW_circle  (x_name, x_base, x_comp, x_neg, x_pos);                                                              <* 
    *>          } glPopMatrix   ();                                                                                                  <* 
    *>          c++;                                                                                                                 <* 
    *>       }                                                                                                                       <* 
    *>    }                                                                                                                          <* 
    *> }                                                                                                                             <*/
   /*---(alt)----------------------------*/
   /*> rc = yVIKEYS_view_size (YVIKEYS_ALT, &x_left, &x_wide, &x_bott, &x_tall, NULL);                                               <* 
    *> if (rc == 'y') {                                                                                                              <* 
    *>    yVIKEYS_view_coords (YVIKEYS_ALT , &x_xmin, &x_xlen, &x_ymin, &x_ylen);                                                    <* 
    *>    x_xmax = x_xmin + x_xlen;                                                                                                  <* 
    *>    x_ymax = x_ymin + x_ylen;                                                                                                  <* 
    *>    DEBUG_GRAF   yLOG_complex ("alt" , "bott %4d, left %4d, wide %4d, tall %4d, on %c", x_bott, x_left, x_wide, x_tall, rc);   <* 
    *>    DEBUG_WIND   yLOG_note    ("set viewport");                                                                                <* 
    *>    /+> glViewport      (x_left, x_bott, x_wide, x_tall);                           <*                                         <* 
    *>     *> glMatrixMode    (GL_PROJECTION);                                            <*                                         <* 
    *>     *> glLoadIdentity  ();                                                         <*                                         <* 
    *>     *> glOrtho         (x_xmin, x_xmax, x_ymin, x_ymax,  -500.0,   500.0);         <*                                         <* 
    *>     *> glMatrixMode    (GL_MODELVIEW);                                             <*                                         <* 
    *>     *> DEBUG_GRAF   yLOG_note    ("draw background");                              <*                                         <* 
    *>     *> glPushMatrix    (); {                                                       <*                                         <* 
    *>     *>    glColor4f      (0.0, 0.0, 0.0, 1.0);                                     <*                                         <* 
    *>     *>    glBegin         (GL_POLYGON); {                                          <*                                         <* 
    *>     *>       glVertex3f  (x_xmin          , x_ymax          ,  0.0f);              <*                                         <* 
    *>     *>       glVertex3f  (x_xmax          , x_ymax          ,  0.0f);              <*                                         <* 
    *>     *>       glVertex3f  (x_xmax          , x_ymin          ,  0.0f);              <*                                         <* 
    *>     *>       glVertex3f  (x_xmin          , x_ymin          ,  0.0f);              <*                                         <* 
    *>     *>    } glEnd   ();                                                            <*                                         <* 
    *>     *> } glPopMatrix   ();                                                         <+/                                        <* 
    *>    /+> DRAW_layout ();                                                             <+/                                        <* 
    *>    DRAW_layout ();                                                                                                        <* 
    *> }                                                                                                                             <*/
   /*---(main)---------------------------*/
   yVIKEYS_view_size   (YVIKEYS_MAIN, &x_left, &x_wide, &x_bott, &x_tall, NULL);
   yVIKEYS_view_bounds (YVIKEYS_MAIN, &x_xmin, &x_xmax, &x_xlen, &x_ymin, &x_ymax, &x_ylen);
   DEBUG_GRAF   yLOG_complex ("main", "bott %4d, left %4d, wide %4d, tall %4d, on %c", x_bott, x_left, x_wide, x_tall, rc);
   DEBUG_WIND   yLOG_note    ("set viewport");
   /*> glViewport      (x_left, x_bott, x_wide, x_tall);                              <* 
    *> glMatrixMode    (GL_PROJECTION);                                               <* 
    *> glLoadIdentity  ();                                                            <* 
    *> glOrtho         (x_xmin, x_xmax, x_ymin, x_ymax,  -500.0,   500.0);            <* 
    *> glMatrixMode    (GL_MODELVIEW);                                                <* 
    *> DEBUG_GRAF   yLOG_note    ("draw background");                                 <* 
    *> glPushMatrix    (); {                                                          <* 
    *>    glColor4f      (0.0, 0.0, 0.0, 1.0);                                        <* 
    *>    glBegin         (GL_POLYGON); {                                             <* 
    *>       glVertex3f  (x_xmin          , x_ymax          ,  0.0f);                 <* 
    *>       glVertex3f  (x_xmax          , x_ymax          ,  0.0f);                 <* 
    *>       glVertex3f  (x_xmax          , x_ymin          ,  0.0f);                 <* 
    *>       glVertex3f  (x_xmin          , x_ymin          ,  0.0f);                 <* 
    *>    } glEnd   ();                                                               <* 
    *> } glPopMatrix   ();                                                            <*/
   DRAW_wheel     ('o');
   return 0;
}

/*> char         /+-> tbd --------------------------------[ ------ [gz.750.021.05]+/ /+-[00.0000.021.!]-+/ /+-[--.---.---.--]-+/   <* 
 *> DRAW_main          (void)                                                                                                      <* 
 *> {                                                                                                                              <* 
 *>    /+---(locals)-------------------------+/                                                                                    <* 
 *>    int       x_wide  = 0;                                                                                                      <* 
 *>    int       x_tall  = 0;                                                                                                      <* 
 *>    /+---(setup view)---------------------+/                                                                                    <* 
 *>    x_wide    = win_w / 2;                                                                                                      <* 
 *>    x_tall    = win_h / 2;                                                                                                      <* 
 *>    glClear         (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                                                <* 
 *>    glViewport      ( 0, 0, win_w, win_h);                                                                                      <* 
 *>    glMatrixMode    (GL_PROJECTION);                                                                                            <* 
 *>    glLoadIdentity  ();                                                                                                         <* 
 *>    glOrtho         ( 0.0, win_w, -x_tall, x_tall,  -500.0,   500.0);                                                           <* 
 *>    glMatrixMode    (GL_MODELVIEW);                                                                                             <* 
 *>    /+---(background)---------------------+/                                                                                    <* 
 *>    DRAW_wheel     ('o');                                                                                                       <* 
 *>    /+> DRAW_wheel     ('O');                                                          <+/                                      <* 
 *>    DRAW_column    ();                                                                                                          <* 
 *>    DRAW_variants  ();                                                                                                          <* 
 *>    /+> DRAW_normings  ();                                                             <+/                                      <* 
 *>    /+> DRAW_wheel     ('f');                                                          <+/                                      <* 
 *>    DRAW_scale     ();                                                                                                          <* 
 *>    DRAW_layout    ();                                                                                                          <* 
 *>    /+---(force the redraw)---------------+/                                                                                    <* 
 *>    glXSwapBuffers(DISP, BASE);                                                                                                 <* 
 *>    glFlush();                                                                                                                  <* 
 *>    /+---(complete)-----------------------+/                                                                                    <* 
 *>    return 0;                                                                                                                   <* 
 *> }                                                                                                                              <*/

char         /*-> tbd --------------------------------[ ------ [gc.JC0.052.E3]*/ /*-[03.0000.011.!]-*/ /*-[--.---.---.--]-*/
PROG_event    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   XKeyEvent  *key_event;
   tTSPEC      x_dur;
   int         loop        = 0;
   char        s           [LEN_LABEL];
   char        t           [5] = "";
   int         c           =    0;
   uchar       x_key       =  ' ';
   char        rc          =    0;;
   int         x_loop      =    0;
   /*---(for timer)----------------------*/
   x_dur.tv_sec    = 0;
   x_dur.tv_nsec   = 0.5 * 1000000;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter    (__FUNCTION__);
   /*---(event loop)---------------------*/
   while (1) {
      x_key = 0;
      if (XPending (YX_DISP)) {
         XNextEvent(YX_DISP, &YX_EVNT);
         switch(YX_EVNT.type) {
         case KeyPress:
            key_event  = (XKeyEvent *) &YX_EVNT;
            c = XLookupString((XKeyEvent *) &YX_EVNT, t, 5, NULL, NULL);
            if (c < 1) break;
            x_key = t [0];
            break;
         }
      }
      if (x_key != 0) {
         x_key = yVIKEYS_main_input  (RUN_USER, x_key);
         rc   = yVIKEYS_main_handle (x_key);
      }
      if (yVIKEYS_quit ())  break;
      ++x_loop;
      if ((x_loop % 20) == 0)  yVIKEYS_view_all (1.0);
      /*---(sleeping)--------------------*/
      nanosleep    (&x_dur, NULL);
   }
   /*> while (1) {                                                                              <* 
    *>    XNextEvent(YX_DISP, &YX_EVNT);                                                              <* 
    *>    /+> printf ("loop %d\n", loop++);                                               <+/   <* 
    *>    /+---(start)----------------------------+/                                            <* 
    *>    switch(YX_EVNT.type) {                                                                   <* 
    *>    case FocusIn:                                                                         <* 
    *>       break;                                                                             <* 
    *>    case FocusOut:                                                                        <* 
    *>       break;                                                                             <* 
    *>    case Expose:                                                                          <* 
    *>       break;                                                                             <* 
    *>    case ConfigureNotify:                                                                 <* 
    *>       break;                                                                             <* 
    *>    case KeyPress:                                                                        <* 
    *>       /+> printf ("key pressed\n");                                                <+/   <* 
    *>       key_event  = (XKeyEvent *) &YX_EVNT;                                                  <* 
    *>       the_bytes = XLookupString((XKeyEvent *) &YX_EVNT, the_key, 5, NULL, NULL);            <* 
    *>       if (the_bytes < 1) break;                                                          <* 
    *>       /+> printf ("the key %d\n", the_key [0]);                                    <+/   <* 
    *>       /+---(mode changes)-------+/                                                       <* 
    *>       switch (the_key[0]) {                                                              <* 
    *>       case 'Q' :                                                                         <* 
    *>          return 1;                                                                       <* 
    *>          break;                                                                          <* 
    *>       case '?' :                                                                         <* 
    *>          if (s_notation == 'y')   s_notation = '-';                                      <* 
    *>          else                     s_notation = 'y';                                      <* 
    *>          break;                                                                          <* 
    *>       case '!' :                                                                         <* 
    *>          if (s_accent   == 'y')   s_accent   = '-';                                      <* 
    *>          else                     s_accent   = 'y';                                      <* 
    *>          break;                                                                          <* 
    *>       case 'L' :                                                                         <* 
    *>          myCOLOR.degree   += 60;                                                             <* 
    *>          HARM_update ();                                                                 <* 
    *>          break;                                                                          <* 
    *>       case 'l' :                                                                         <* 
    *>          myCOLOR.degree   += 10;                                                             <* 
    *>          HARM_update ();                                                                 <* 
    *>          break;                                                                          <* 
    *>       case 'h' :                                                                         <* 
    *>          myCOLOR.degree   -= 10;                                                             <* 
    *>          HARM_update ();                                                                 <* 
    *>          break;                                                                          <* 
    *>       case 'H' :                                                                         <* 
    *>          myCOLOR.degree   -= 60;                                                             <* 
    *>          HARM_update ();                                                                 <* 
    *>          break;                                                                          <* 
    *>       case 'K' :                                                                         <* 
    *>          s_cvariant -=  5;                                                               <* 
    *>          break;                                                                          <* 
    *>       case 'k' :                                                                         <* 
    *>          s_cvariant -=  1;                                                               <* 
    *>          break;                                                                          <* 
    *>       case 'j' :                                                                         <* 
    *>          s_cvariant +=  1;                                                               <* 
    *>          break;                                                                          <* 
    *>       case 'J' :                                                                         <* 
    *>          s_cvariant +=  5;                                                               <* 
    *>          break;                                                                          <* 
    *>       case '+' :                                                                         <* 
    *>          s_cnorming +=  1;                                                               <* 
    *>          break;                                                                          <* 
    *>       case '-' :                                                                         <* 
    *>          s_cnorming -=  1;                                                               <* 
    *>          break;                                                                          <* 
    *>       case '0' : case '1' : case '2' : case '3' : case '4' :                             <* 
    *>       case '5' : case '6' : case '7' : case '8' : case '9' :                             <* 
    *>          s_cset      = the_key[0] - '0' + 1;                                             <* 
    *>          break;                                                                          <* 
    *>       case 'M' : case 'C' : case 'D' :                                                   <* 
   *>       case 'T' : case 'R' : case 'S' :                                                   <* 
      *>       case 'F' : case 'A' : case 'B' :                                                   <* 
      *>       case 'Z' : case 'Y' : case 'X' :                                                   <* 
      *>       case 'W' :                                                                         <* 
      *>          sprintf (s, "%c", the_key [0]);                                                 <* 
      *>          HARM_set (s);                                                                   <* 
      *>          break;                                                                          <* 
      *>       }                                                                                  <* 
      *>       break;                                                                             <* 
      *>    default:                                                                              <* 
      *>       break;                                                                             <* 
      *>    }                                                                                     <* 
      *>    if (s_cvariant <    0       )  s_cvariant  =   0;                                     <* 
      *>    if (s_cvariant >= s_nvariant)  s_cvariant  =  s_nvariant - 1;                         <* 
      *>    if (s_cnorming <    0       )  s_cnorming  =   0;                                     <* 
      *>    if (s_cnorming >= s_nnorming)  s_cnorming  =  s_nnorming - 1;                         <* 
      *>    x_ch = yVIKEYS_main_input  (RUN_USER, x_ch);                                          <* 
      *>    rc   = yVIKEYS_main_handle (x_ch);                                                    <* 
      *>    if (yVIKEYS_quit ())  break;                                                          <* 
      *>    ++x_loop;                                                                             <* 
      *>    if ((x_loop % 20) == 0)  yVIKEYS_view_all (s_mag);                                    <* 
      *>    /+> DRAW_main  ();                                                              <+/   <* 
      *>    /+> sleep( 1);                                                                  <+/   <* 
      *> }                                                                                        <*/
      /*---(complete)------------------------------*/
      DEBUG_TOPS   yLOG_exit     (__FUNCTION__);
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

char         /*-> tbd --------------------------------[ leaf   [gc.100.000.00]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
DUMP_scale         ()
{
}

char         /*-> tbd --------------------------------[ shoot  [gz.210.001.02]*/ /*-[00.0000.011.!]-*/ /*-[--.---.---.--]-*/
PROG_init          ()
{
   /*---(vikeys)-------------------------*/
   yVIKEYS_init         ('-');
   yVIKEYS_cmds_add     ('v', "labels"      , ""    , "s"    , SET_names                  , "" );
   yVIKEYS_view_config  ("yCOLOR_make", P_VERNUM, YVIKEYS_OPENGL, 500, 500, 500);
   yVIKEYS_cmds_direct  (":palette 0 fcomp full vivid");
   /*---(color)--------------------------*/
   /*> yCOLOR_init     (YCOLOR_REDBLU);                                               <*/
   /*> yCOLOR_init     (YCOLOR_WHEEL );                                               <*/
   /*> yCOLOR_scale    (YCOLOR_PARABOLIC,  0.0,  50.0);                               <*/
   /*> myCOLOR.degree     = 0;                                                        <*/
   /*> s_cset             = 1;                                                        <*/
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: process command line arguments ----------------------------*/
PROG_args          (int argc, char *argv[])
{
   char *a = NULL;
   int   i = 0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter    (__FUNCTION__);
   for (i = 1; i < argc; ++i) {
      a = argv[i];
      if (a[0] == '@')  continue;
      DEBUG_ARGS  yLOG_info    ("cli arg", a);
      if      (strncmp(a, "--degree"            , 20) == 0) {
         if (argc > i + 1)  myCOLOR.degree  = atoi (argv [++i]);
      }
      else if (strncmp(a, "--harmony"           , 20) == 0) {
         if (argc > i + 1)  HARM_set    (argv [++i]);
      }
      else if (strncmp(a, "--sat"               , 20) == 0) {
         if (argc > i + 1)  SATS_set    (argv [++i]);
      }
      else if (strncmp(a, "--val"               , 20) == 0) {
         if (argc > i + 1)  VALS_set    (argv [++i]);
      }
      else {
         /*> printf("\noption [%s] not understood\n", a);                             <*/
         exit (-1);
      }
   }
   /*> printf ("myCOLOR.degree    [%d]\n", myCOLOR.degree);                                   <*/
   /*> printf ("myCOLOR.harmony   [%s]\n" , myCOLOR.harmony);                                 <*/
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit     (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ shoot  [gz.210.001.02]*/ /*-[00.0000.011.!]-*/ /*-[--.---.---.--]-*/
PROG_begin         ()
{
   /*> yVIKEYS_map_config (YVIKEYS_RIGHT, MAP_col, MAP_row, NULL);                    <*/
   return 0;
}

int          /*-> tbd --------------------------------[ ------ [gn.ID0.254.H9]*/ /*-[05.0000.000.!]-*/ /*-[--.---.---.--]-*/
main               (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         rc          = 0;
   int         i           = 0;
   int         j           = 0;
   int         x_deg       = 0;
   char        x_base      [LEN_LABEL];
   /*---(read config)--------------------*/
   if (rc >= 0)  rc = yURG_logger          (argc, argv);
   if (rc >= 0)  rc = PROG_init            ();
   if (rc >= 0)  rc = yURG_urgs            (argc, argv);
   if (rc >= 0)  rc = PROG_args            (argc, argv);
   if (rc >= 0)  rc = PROG_begin           ();
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
    *>       return 0;                                                                                                      <* 
    *>    } else if (strcmp (argv [1], "--small") == 0) {                                                                   <* 
    *>       x_deg       = 0;                                                                                               <* 
    *>       printf ("   /+------------------------------------------------------------------------+/\n");                  <* 
    *>       printf ("   /+  RYB (artists color wheel)  25 total values                            +/\n");                  <* 
    *>       printf ("   /+     12 low  > reds and oranges                                         +/\n");                  <* 
    *>       printf ("   /+     middle  > yellow                                                   +/\n");                  <* 
    *>       printf ("   /+     12 high > greens and blues                                         +/\n");                  <* 
    *>       printf ("   /+------------------------------------------------------------------------+/\n");                  <* 
    *>       yCOLOR_use (YCOLOR_WHEEL);                                                                                     <* 
    *>       for (i = 0; i <=  240; i += 10) {                                                                              <* 
    *>          yCOLOR_deg2hex  (i, x_base);                                                                                <* 
    *>          printf ("   {  /+ %03d +/  \"%s\",  0.0,  0.0,  0.0 },\n", i, x_base);                                      <* 
    *>          /+> for (j = 0; j <   6; ++j) {                                              <*                             <* 
    *>           *>    if (x_deg <= 120)  printf ("\"%s\", ", s_RYB [(i * 6) + j][4]);       <*                             <* 
    *>           *>    if (x_deg >  120)  printf ("\"%s\", ", s_RYB [(i * 6) + j - 5][4]);   <*                             <* 
    *>           *>    if (x_deg == 120) {                                                   <*                             <* 
    *>           *>       x_deg -= 50;  break;                                               <*                             <* 
    *>           *>    }                                                                     <*                             <* 
    *>           *> }                                                                        <*                             <* 
    *>           *> x_deg += 60;                                                             <+/                            <* 
    *>          /+> printf ("\n");                                                        <+/                               <* 
    *>       }                                                                                                              <* 
    *>       printf ("   {  /+ %03d +/  \"\"       ,  0.0,  0.0,  0.0 },\n", 999);                                          <* 
    *>       printf ("   /+---------------------------------(done)---------------------------------+/\n");                  <* 
    *>       return 0;                                                                                                      <* 
    *>    }                                                                                                                 <* 
    *> }                                                                                                                    <*/
   DRAW_init          ();
   FONT_load          ();
   yCOLOR_clear  (5);
   /*> DRAW_scheme (SCHEME_DCOMP);                                                    <*/
   /*> DRAW_main          ();                                                         <*/
   /*---(main loop)----------------------*/
   while (!yVIKEYS_quit ()) {
      rc = PROG_event    ();
   }
   yVIKEYS_wrap ();
   /*---(complete)-----------------------*/
   return rc;
}





