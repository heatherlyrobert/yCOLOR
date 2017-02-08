/*============================----beg-of-source---============================*/



/*===[[ HEADERS ]]========================================*/
/*---(local)-----------------------------*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"
/*---(heatherly made)--------------------*/
#include    <yFONT.h>        /* CUSTOM  heatherly texture-mapped fonts        */
#include    <yX11.h>         /* CUSTOM  heatherly xlib/glx setup/teardown     */
#include    <yGLTEX.h>       /* CUSTOM  heatherly texture handling            */



static char  s_face     [LEN_LABEL] = "comfortaa";
static char  s_font     = -1;

static char  s_notation   = '-';
static char  s_accent     = '-';

int       win_w = 1400;                     /* window width                   */
int       win_h =  600;                     /* window height                  */
int       tex_w = 1400;                     /* texture width                  */
int       tex_h =  600;                     /* texture height                 */

const    double   DEG2RAD   = M_PI / 180.0;








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
DRAW_column         (void)
{
   /*---(locals)-----------+-----------+-*/
   int         x_deg       =  0;             /* loop iterator -- word          */
   int         x_set       =  0;             /* loop iterator -- word          */
   float       x_wide      =  75.0;
   float       x_inc       =  0.0;
   char        x_text      [LEN_STR];
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
         if (s_notation == 'y') {
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
   char        x_save      = 0;
   yCOLOR_use (YCOLOR_WHEEL);
   glPushMatrix(); {
      if      (a_which == 'o')  glTranslatef ( 380,  40.0,   0.0);
      else if (a_which == 'O')  glTranslatef ( 380,  40.0,   0.0);
      else                      glTranslatef (1100,  40.0,   0.0);
      for (x_deg = 0; x_deg < 360; x_deg += 10) {
         glPushMatrix(); {
            glRotatef    (x_deg + 90, 0.0f, 0.0f, 1.0f);
            /*---(set color)-------------*/
            yCOLOR_deg2hex     (x_deg, x_base);
            yCOLOR_deg2color   (x_deg, 1.0);
            strlcpy (x_norm, x_base, LEN_HEX);
            if (a_which != 'o') {
               yCOLOR_variant ("CURRENT", x_base, x_hex);
               yCOLOR__norming (s_cnorming, x_hex , x_norm);
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
               x_save = s_cset;
               s_cset = 7;
               r2 = r1 + 20;
               yCOLOR_deg2color   (x_deg, 1.0);
               glBegin         (GL_POLYGON); {
                  glVertex3f  (r1,  r1 * sin (5.5 * DEG2RAD),     0.0);
                  glVertex3f  (r2,  r2 * sin (5.5 * DEG2RAD),     0.0);
                  glVertex3f  (r2, -r2 * sin (5.5 * DEG2RAD),     0.0);
                  glVertex3f  (r1, -r1 * sin (5.5 * DEG2RAD),     0.0);
               } glEnd   ();
               s_cset = x_save;
               yCOLOR_deg2color   (x_deg, 1.0);
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
            if (x_deg == s_ccolor) {
               glPushMatrix(); {
                  glTranslatef ( 135,   0.0,   0.0);
                  if (x_deg < 180) glRotatef    (180       , 0.0f, 0.0f, 1.0f);
                  yFONT_print  (s_font,   8, YF_MIDCEN, "curr");
               } glPopMatrix();
            }
            if (s_notation == 'y') {
               glPushMatrix(); {
                  glTranslatef ( 200,   0.0,   0.0);
                  if (x_deg < 180) glRotatef    (180       , 0.0f, 0.0f, 1.0f);
                  glColor4f    ( 0.0, 0.0, 0.0, 1.0);
                  /*> yFONT_print  (s_font,   8, YF_MIDCEN, x_norm);                  <*/
                  yFONT_print  (s_font,   8, YF_MIDCEN, yCOLOR_deg2name (x_deg));
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
   char        rc          = 0;
   int         i           = 0;
   int         x_index     = 0;
   char        x_cat       [LEN_LABEL] = "";
   char        x_base      [LEN_HEX]   = "";
   char        x_hex       [LEN_HEX]   = "";
   float       x_pos       = 0.0;
   float       y_pos       = 0.0;
   yCOLOR_use (YCOLOR_WHEEL);
   yCOLOR_deg2hex  (s_ccolor, x_base);
   glPushMatrix(); {
      x_pos  = 660;
      y_pos  = win_h / 2 - 30;
      for (i = 0; i < s_nvariant; ++i) {
         /*---(identify variant)---------*/
         if (i == 0)  rc = yCOLOR_variant ("FIRST", x_base, x_hex);
         else         rc = yCOLOR_variant ("NEXT" , x_base, x_hex);
         if (rc < 0) break;
         /*---(check column change)------*/
         if (s_variants [i].abbr[0] == '2' ) {
            x_pos += 100;
            y_pos  = win_h / 2 - 20;
         }
         glPushMatrix(); {
            glTranslatef (x_pos , y_pos,   0.0);
            /*---(set color)----------------*/
            yCOLOR_hex2color (x_hex, 1.0);
            /*---(show category)------------*/
            if (s_variants [i].cat[0] != '-' && strcmp (x_cat, s_variants [i].cat) != 0) {
               glTranslatef (   0, -10.0,   0.0);
               y_pos -= 10;
               glPushMatrix(); {
                  /*> glColor4f   (  1.0,   1.0,   1.0, 1.0f);                           <*/
                  glTranslatef ( -15,  20.0,   0.0);
                  glRotatef    (90, 0.0f, 0.0f, 1.0f);
                  yFONT_print  (s_font,  12, YF_MIDRIG, s_variants [i].cat);
                  strlcpy (x_cat, s_variants [i].cat, LEN_LABEL);
               } glPopMatrix();
            }
            /*---(draw box)-----------------*/
            glBegin         (GL_POLYGON); {
               glVertex3f  (    0.0,  20.0,     0.0);
               glVertex3f  (   80.0,  20.0,     0.0);
               glVertex3f  (   80.0,   0.0,     0.0);
               glVertex3f  (    0.0,   0.0,     0.0);
            } glEnd   ();
            /*---(label it)-----------------*/
            glPushMatrix(); {
               glColor4f   (  0.0,   0.0,   0.0, 1.0f);
               if (s_notation == 'y') {
                  glTranslatef (40.0,  17.0,   5.0);
                  yFONT_print  (s_font,   8, YF_MIDCEN, s_variants [i].name);
                  glTranslatef ( 0.0, -10.0,   0.0);
                  yFONT_print  (s_font,   8, YF_MIDCEN, x_hex);
               } else {
                  glTranslatef (40.0,  11.0,   5.0);
                  yFONT_print  (s_font,   8, YF_MIDCEN, s_variants [i].name);
               }
            } glPopMatrix();
            /*---(mark current)-------------*/
            if (i == s_cvariant) {
               glPushMatrix(); {
                  glColor4f   (  1.0,   1.0,   1.0, 1.0f);
                  glTranslatef (  -5,  12.0,   0.0);
                  yFONT_print  (s_font,   8, YF_MIDLEF, "curr");
               } glPopMatrix();
            }
            /*---(prepare for next)---------*/
            y_pos -= 20;
            /*---(done)---------------------*/
         } glPopMatrix();
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
   yCOLOR_use (YCOLOR_WHEEL);
   yCOLOR_deg2hex     (s_ccolor, x_base);
   yCOLOR_variant ("CURRENT", x_base, x_hex);
   glPushMatrix(); {
      glTranslatef ( 730 , -win_h / 2 +  80,   0.0);
      for (i = 0; i < s_nnorming; ++i) {
         if (s_normings [i].abbr[0] == '\0') break;
         yCOLOR__norming (i, x_hex , x_norm);
         yCOLOR_hex2color (x_norm, 1.0);
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
   char        x_text      [LEN_STR];
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
   if (strlen (a_var) == 1)  yCOLOR_accent  (a_var [0], a_base, x_hex);
   else                      yCOLOR_variant (a_var    , a_base, x_hex);
   yCOLOR_hex2color (x_hex, 1.0);
   glBegin         (GL_POLYGON); {
      glVertex3f  ( a_xpos         , a_ypos + x_tall, x_zpos);
      glVertex3f  ( a_xpos + x_wide, a_ypos + x_tall, x_zpos);
      glVertex3f  ( a_xpos + x_wide, a_ypos         , x_zpos);
      glVertex3f  ( a_xpos         , a_ypos         , x_zpos);
   } glEnd   ();
   if (s_notation == 'y') {
      /*> yCOLOR_variant ("none", a_base, x_hex);                                     <* 
       *> yCOLOR_hex2color (x_hex, 1.0);                                                     <*/
      glPushMatrix(); {
         sprintf (x_text, "%-2.2s", a_var);
         glTranslatef ( a_xpos + (x_wide/2), a_ypos + 10, 30.0);
         glColor4f   (  0.0,   0.0,   0.0, 1.0f);
         yFONT_print  (s_font,   8, YF_MIDCEN, x_text);
         glTranslatef ( 0.0, 15.0, 0.0);
         yFONT_print  (s_font,   8, YF_MIDCEN, x_hex);
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
   yCOLOR_use (YCOLOR_WHEEL);
   glPushMatrix(); {
      glTranslatef ( 850 , -win_h / 2 + 80,   0.0);
      /*---(upper-left)------------------*/
      yCOLOR_deg2hex  (s_ccolor, x_base);
      yCOLOR_variant ("CURRENT", x_base, x_hex1);
      yCOLOR_hex2color (x_hex1, 1.0);
      if (s_accent == 'y') {
         DRAW_box (x_hex1 , "CURRENT" , '1',  0,  5);
         DRAW_box (x_hex1 , "v"       , 'b',  0,  6);
         DRAW_box (x_hex1 , "-"       , 'b',  0,  8);
         DRAW_box (x_hex1 , "+"       , 'b',  2, 10);
         DRAW_box (x_hex1 , "^"       , 'b',  4, 10);
      } else {
         strlcpy  (x_hex1 , x_base    , LEN_HEX);
         DRAW_box (x_hex1 , "CURRENT" , '1',  0,  5);
         DRAW_box (x_hex1 , "chalk"   , 'b',  4, 10);
         DRAW_box (x_hex1 , "bright"  , 'b',  2, 10);
         DRAW_box (x_hex1 , "balanced", 'b',  0,  8);
         DRAW_box (x_hex1 , "medium"  , 'b',  0,  6);
         DRAW_box (x_hex1 , "strong"  , 'b',  2,  8);
         DRAW_box (x_hex1 , "earthy"  , 's',  4,  7);
         DRAW_box (x_hex1 , "artists" , 's',  1, 10);
      }
      /*---(upper-right)-----------------*/
      yCOLOR_deg2hex  (s_ccolor -  30, x_base);
      yCOLOR_variant ("CURRENT", x_base, x_hex2);
      yCOLOR_hex2color (x_hex2, 1.0);

      strlcpy  (x_hex2 , x_base    , LEN_HEX);
      DRAW_box (x_hex2 , "CURRENT" , '2',  8,  5);
      DRAW_box (x_hex2 , "chalk"   , 's', 11, 11);
      DRAW_box (x_hex2 , "bright"  , 's', 11, 10);
      DRAW_box (x_hex2 , "balanced", 's', 11,  9);
      DRAW_box (x_hex2 , "medium"  , 's', 11,  8);
      DRAW_box (x_hex2 , "strong"  , 's', 10, 10);
      DRAW_box (x_hex2 , "earthy"  , 's',  9, 10);
      DRAW_box (x_hex2 , "artists" , 's', 10,  7);
      /*---(lower-left)------------------*/
      yCOLOR_deg2hex  (s_ccolor +  30, x_base);
      yCOLOR_variant ("CURRENT", x_base, x_hex3);
      yCOLOR_hex2color (x_hex3, 1.0);

      strlcpy  (x_hex3 , x_base    , LEN_HEX);
      DRAW_box (x_hex3 , "CURRENT" , '3',  0,  0);
      DRAW_box (x_hex3 , "chalk"   , 's',  0,  0);
      DRAW_box (x_hex3 , "bright"  , 's',  1,  0);
      DRAW_box (x_hex3 , "balanced", 's',  2,  0);
      DRAW_box (x_hex3 , "medium"  , 's',  3,  0);
      DRAW_box (x_hex3 , "strong"  , 's',  2,  1);
      DRAW_box (x_hex3 , "earthy"  , 's',  3,  1);
      DRAW_box (x_hex3 , "artists" , 's',  4,  1);
      /*---(lower-right)-----------------*/
      yCOLOR_deg2hex  (s_ccolor + 180, x_base);
      yCOLOR_variant ("CURRENT", x_base, x_hex4);
      yCOLOR_hex2color (x_hex4, 1.0);

      strlcpy  (x_hex4 , x_base    , LEN_HEX);
      DRAW_box (x_hex4 , "CURRENT" , '4',  8,  0);
      DRAW_box (x_hex4 , "chalk"   , 's', 10,  1);
      DRAW_box (x_hex4 , "bright"  , 's', 10,  0);
      DRAW_box (x_hex4 , "balanced", 's', 11,  1);
      DRAW_box (x_hex4 , "medium"  , 's', 11,  0);
      DRAW_box (x_hex4 , "strong"  , 's',  9,  2);
      DRAW_box (x_hex4 , "earthy"  , 's',  9,  3);
      DRAW_box (x_hex4 , "artists" , 's',  8,  2);
      /*---(accents)---------------------*/
      /*> DRAW_box (x_hex1 , "CURRENT" , 'c',  7,  4);                                <* 
       *> DRAW_box (x_hex2 , "CURRENT" , 'c',  6,  4);                                <* 
       *> DRAW_box (x_hex3 , "CURRENT" , 'c',  7,  5);                                <* 
       *> DRAW_box (x_hex4 , "CURRENT" , 'c',  6,  5);                                <*/
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
         case '!' :
            if (s_accent   == 'y')   s_accent   = '-';
            else                     s_accent   = 'y';
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
            s_cvariant -=  5;
            break;
         case 'k' :
            s_cvariant -=  1;
            break;
         case 'j' :
            s_cvariant +=  1;
            break;
         case 'J' :
            s_cvariant +=  5;
            break;
         case '+' :
            s_cnorming +=  1;
            break;
         case '-' :
            s_cnorming -=  1;
            break;
         case '0' : case '1' : case '2' : case '3' : case '4' :
         case '5' : case '6' : case '7' : case '8' : case '9' :
            s_cset      = the_key[0] - '0' + 1;
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
   yCOLOR_init     (YCOLOR_WHEEL);
   yCOLOR_scale    (YCOLOR_LINEAR   ,  0.0, 100.0);
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
   char        x_base      [LEN_LABEL];
   /*---(read config)--------------------*/
   if (rc >= 0)  rc = yURG_logger          (argc, argv);
   if (rc >= 0)  rc = PROG_init            ();
   if (rc >= 0)  rc = yURG_urgs            (argc, argv);
   /*> if (rc >= 0)  rc = PROG_args            (argc, argv);                          <*/
   /*> if (rc >= 0)  rc = yFONT__conf_parse    ();                                    <*/
   if (rc <  0) {
      return rc;
   }
   if (argc > 0) {
      if (strcmp (argv [1], "--big") == 0) {
         x_deg       = -120;
         printf ("   /*------------------------------------------------------------------------*/\n");
         printf ("   /*  RYB (artists color wheel)  61 total values                            */\n");
         printf ("   /*     30 warm > browns, reds, oranges, yellows                           */\n");
         printf ("   /*     middle  > green                                                    */\n");
         printf ("   /*     30 cool > blues, purples, steels, greys                            */\n");
         printf ("   /*-----------------------------(prefix wheel)-----------------------------*/\n");
         for (i = 0; i <  11; ++i) {
            if (i == 2) printf ("   /*-----------------------------(normal wheel)-----------------------------*/\n");
            if (i == 8) printf ("   /*-----------------------------(suffix wheel)-----------------------------*/\n");
            printf ("   /* %04d /* ", x_deg);
            /*> if (x_deg == 180) {                                                      <* 
             *>    printf ("\"%s\",\n", s_RYB [(i * 6)][4]);                             <* 
             *>    x_deg += 10;                                                          <* 
             *>    continue;                                                             <* 
             *> }                                                                        <*/
            for (j = 0; j <   6; ++j) {
               printf ("\"%s\", ", s_RYB [(i * 6) + j][4]);
               if (x_deg == 180) {
                  x_deg -= 50;  break;
               }
            }
            x_deg += 60;
            printf ("\n");
         }
         printf ("   /*---------------------------------(done)---------------------------------*/\n");
         return 0;
      } else if (strcmp (argv [1], "--small") == 0) {
         x_deg       = 0;
         printf ("   /*------------------------------------------------------------------------*/\n");
         printf ("   /*  RYB (artists color wheel)  25 total values                            */\n");
         printf ("   /*     12 low  > reds and oranges                                         */\n");
         printf ("   /*     middle  > yellow                                                   */\n");
         printf ("   /*     12 high > greens and blues                                         */\n");
         printf ("   /*------------------------------------------------------------------------*/\n");
         yCOLOR_use (YCOLOR_WHEEL);
         for (i = 0; i <=  240; i += 10) {
            yCOLOR_deg2hex  (i, x_base);
            printf ("   {  /* %03d */  \"%s\",  0.0,  0.0,  0.0 },\n", i, x_base);
            /*> for (j = 0; j <   6; ++j) {                                              <* 
             *>    if (x_deg <= 120)  printf ("\"%s\", ", s_RYB [(i * 6) + j][4]);       <* 
             *>    if (x_deg >  120)  printf ("\"%s\", ", s_RYB [(i * 6) + j - 5][4]);   <* 
             *>    if (x_deg == 120) {                                                   <* 
             *>       x_deg -= 50;  break;                                               <* 
             *>    }                                                                     <* 
             *> }                                                                        <* 
             *> x_deg += 60;                                                             <*/
            /*> printf ("\n");                                                        <*/
         }
         printf ("   {  /* %03d */  \"\"       ,  0.0,  0.0,  0.0 },\n", 999);
         printf ("   /*---------------------------------(done)---------------------------------*/\n");
         return 0;
      }
   }
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





