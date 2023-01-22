/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



/*============================--------------------============================*/
/*===----                        program level                         ----===*/
/*============================--------------------============================*/
static void      o___PROGRAM_________________o (void) {;}

char
ycolor_palette_purge    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =  -10;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(clear)--------------------------*/
   for (i = 0; i < MAX_COLOR; ++i) {
      strlcpy (s_palette [i].hex, "", LEN_TERSE);
      s_palette [i].red  = 0.00;
      s_palette [i].grn  = 0.00;
      s_palette [i].blu  = 0.00;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycolor_palette_init     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =  -10;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(clear)--------------------------*/
   ycolor_palette_purge ();
   ycolor_constant ();
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*============================--------------------============================*/
/*===----                      generate a palette                      ----===*/
/*============================--------------------============================*/
static void      o___GENERATE________________o (void) {;}

char
ycolor_palette__save    (cint a_major, cint a_minor, cchar *a_hex)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         l           =    0;
   int         x_slot      =    0;
   float       x_red       =  0.0;
   float       x_grn       =  0.0;
   float       x_blu       =  0.0;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCOLOR   yLOG_value   ("a_major"   , a_major);
   --rce;  if (a_major < 0 || a_major > MAX_COLOR) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_value   (" % 10"     , a_major % 10);
   --rce;  if (a_major % 10 != 0) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_value   ("a_minor"   , a_minor);
   --rce;  if (a_major != YCOLOR_VAR && (a_minor < YCOLOR_NOR || a_minor > YCOLOR_TBD)) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_major == YCOLOR_VAR && (a_minor < YCOLOR_ONE || a_minor > YCOLOR_TWE)) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_point   ("a_hex"     , a_hex);
   --rce;  if (a_hex == NULL) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_info    ("a_hex"     , a_hex);
   l = strlen (a_hex);
   DEBUG_YCOLOR   yLOG_value   ("l"         , l);
   --rce;  if (l != 7) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(convert)------------------------*/
   ycolor_hex2rgb  (a_hex, &x_red, &x_grn, &x_blu);
   /*---(save)---------------------------*/
   strlcpy   (s_palette [a_major + a_minor].hex, a_hex, LEN_TERSE);
   s_palette [a_major + a_minor].red = x_red;
   s_palette [a_major + a_minor].grn = x_grn;
   s_palette [a_major + a_minor].blu = x_blu;
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yCOLOR__palette_save  (cint a_slot, char *a_hex)
{
   return 0;
}

char
yCOLOR_set           (cint a_slot, cfloat a_alpha)
{
   glColor4f   (s_palette [a_slot].red, s_palette [a_slot].grn, s_palette [a_slot].blu, a_alpha);
   return 0;
}

char
yCOLOR_set_clear     (cint a_slot)
{
   glClearColor   (s_palette [a_slot].red, s_palette [a_slot].grn, s_palette [a_slot].blu, 1.0);
   return 0;
}

char
ycolor_palette__hex  (cint a_deg, char *a_out)
{
   /*> yCOLOR_deg2hex (myCOLOR.pos   , x_orig);                                 <*/
}

char
ycolor_palette__one  (cchar a_major, cint a_deg)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         d           =    0;
   char        x_orig      [LEN_TERSE] = "";
   char        x_base      [LEN_TERSE] = "";
   char        x_hex       [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   d  = ycolor_deg2fix (a_deg);
   /*---(get original color)-------------*/
   --rce;  switch (a_major) {
   default          :
      rc = ycolor_deg2hex (d, x_orig);
      DEBUG_YCOLOR   yLOG_value   ("deg2hex"   , rc);
      if (rc < 0) {
         DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      break;
   }
   DEBUG_YCOLOR   yLOG_info    ("x_orig"    , x_orig);
   /*---(make base and place)---------*/
   yCOLOR_variant       ("=", "=", x_orig, x_base);
   DEBUG_YCOLOR   yLOG_info    ("x_base"    , x_base);
   ycolor_palette__save (a_major, YCOLOR_NOR, x_base);
   ycolor_palette__save (a_major, YCOLOR_MED, x_base);
   ycolor_palette__save (a_major, YCOLOR_TBD, x_base);
   /*---(lighter)---------------------*/
   yCOLOR_accent        ('!', x_base, x_hex);
   DEBUG_YCOLOR   yLOG_info    ("!"         , x_hex);
   ycolor_palette__save (a_major, YCOLOR_MAX, x_hex);
   yCOLOR_accent        ('^', x_base, x_hex);
   DEBUG_YCOLOR   yLOG_info    ("^"         , x_hex);
   ycolor_palette__save (a_major, YCOLOR_ACC, x_hex);
   yCOLOR_accent        ('+', x_base, x_hex);
   DEBUG_YCOLOR   yLOG_info    ("+"         , x_hex);
   ycolor_palette__save (a_major, YCOLOR_LIG, x_hex);
   /*---(darker)----------------------*/
   yCOLOR_accent        ('-', x_base, x_hex);
   DEBUG_YCOLOR   yLOG_info    ("-"         , x_hex);
   ycolor_palette__save (a_major, YCOLOR_DRK, x_hex);
   yCOLOR_accent        ('v', x_base, x_hex);
   DEBUG_YCOLOR   yLOG_info    ("v"         , x_hex);
   ycolor_palette__save (a_major, YCOLOR_MUT, x_hex);
   yCOLOR_accent        ('#', x_base, x_hex);
   DEBUG_YCOLOR   yLOG_info    ("#"         , x_hex);
   ycolor_palette__save (a_major, YCOLOR_MOR, x_hex);
   yCOLOR_accent        ('@', x_base, x_hex);
   DEBUG_YCOLOR   yLOG_info    ("@"         , x_hex);
   ycolor_palette__save (a_major, YCOLOR_MIN, x_hex);
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycolor_constant      (void)
{
   char        x_orig      [LEN_TERSE] = "";
   char        x_base      [LEN_TERSE] = "";
   /*---(brown)--------------------------*/
   ycolor_palette__save (YCOLOR_BRN, YCOLOR_NOR, "õ994500");
   ycolor_palette__save (YCOLOR_BRN, YCOLOR_MAX, "õffca9f");
   ycolor_palette__save (YCOLOR_BRN, YCOLOR_ACC, "õe1a06b");
   ycolor_palette__save (YCOLOR_BRN, YCOLOR_LIG, "õbb6e2e");
   ycolor_palette__save (YCOLOR_BRN, YCOLOR_MED, "õ994500");
   ycolor_palette__save (YCOLOR_BRN, YCOLOR_DRK, "õ763500");
   ycolor_palette__save (YCOLOR_BRN, YCOLOR_MUT, "õ502400");
   ycolor_palette__save (YCOLOR_BRN, YCOLOR_MOR, "õ391900");
   ycolor_palette__save (YCOLOR_BRN, YCOLOR_MIN, "õ130800");
   ycolor_palette__save (YCOLOR_BRN, YCOLOR_TBD, "õ994500");
   /*---(brown)--------------------------*/
   ycolor_palette__save (YCOLOR_GRY, YCOLOR_NOR, "õ777777");
   ycolor_palette__save (YCOLOR_GRY, YCOLOR_MAX, "õeeeeee");
   ycolor_palette__save (YCOLOR_GRY, YCOLOR_ACC, "õbbbbbb");
   ycolor_palette__save (YCOLOR_GRY, YCOLOR_LIG, "õ999999");
   ycolor_palette__save (YCOLOR_GRY, YCOLOR_MED, "õ777777");
   ycolor_palette__save (YCOLOR_GRY, YCOLOR_DRK, "õ606060");
   ycolor_palette__save (YCOLOR_GRY, YCOLOR_MUT, "õ404040");
   ycolor_palette__save (YCOLOR_GRY, YCOLOR_MOR, "õ202020");
   ycolor_palette__save (YCOLOR_GRY, YCOLOR_MIN, "õ101010");
   ycolor_palette__save (YCOLOR_GRY, YCOLOR_TBD, "õ777777");
   /*---(black)--------------------------*/
   ycolor_palette__save (YCOLOR_SPE, YCOLOR_BLK, "õ000000");
   /*---(error)--------------------------*/
   ycolor_deg2hex (  0, x_orig);
   yCOLOR_variant       ("-", "vivid"   , x_orig, x_base);
   ycolor_palette__save (YCOLOR_SPE, YCOLOR_ERR, x_base);
   /*---(warning)------------------------*/
   ycolor_deg2hex (120, x_orig);
   yCOLOR_variant       ("-", "vivid"   , x_orig, x_base);
   ycolor_palette__save (YCOLOR_SPE, YCOLOR_WRN, x_base);
   /*---(source)-------------------------*/
   ycolor_deg2hex (180, x_orig);
   yCOLOR_variant       ("-", "balanced", x_orig, x_base);
   ycolor_palette__save (YCOLOR_SPE, YCOLOR_SRC, x_base);
   /*---(select)-------------------------*/
   ycolor_deg2hex ( 60, x_orig);
   yCOLOR_variant       ("-", "balanced", x_orig, x_base);
   ycolor_palette__save (YCOLOR_SPE, YCOLOR_SEL, x_base);
   /*---(textreg)------------------------*/
   ycolor_deg2hex (210, x_orig);
   yCOLOR_variant       ("-", "balanced", x_orig, x_base);
   ycolor_palette__save (YCOLOR_SPE, YCOLOR_REG, x_base);
   /*---(replace)------------------------*/
   ycolor_deg2hex (315, x_orig);
   yCOLOR_variant       ("-", "balanced", x_orig, x_base);
   ycolor_palette__save (YCOLOR_SPE, YCOLOR_REP, x_base);
   /*---(input)--------------------------*/
   ycolor_deg2hex (230, x_orig);
   yCOLOR_variant       ("-", "vivid"   , x_orig, x_base);
   ycolor_palette__save (YCOLOR_SPE, YCOLOR_INP, x_base);
   /*---(wander)-------------------------*/
   ycolor_deg2hex (  0, x_orig);
   yCOLOR_variant       ("-", "balanced", x_orig, x_base);
   ycolor_palette__save (YCOLOR_SPE, YCOLOR_WDR, x_base);
   /*---(cursor)-------------------------*/
   ycolor_deg2hex (120, x_orig);
   yCOLOR_variant       ("-", "balanced", x_orig, x_base);
   ycolor_palette__save (YCOLOR_SPE, YCOLOR_CUR, x_base);
   /*---(complete)-----------------------*/
   return 0;
}


char
yCOLOR_palette       (cint a_deg, cchar *a_harm, cchar *a_sat, cchar *a_val)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   int         d           =    0;
   float       x_beg, x_red, x_grn, x_blu;
   char        x_orig      [LEN_TERSE] = "";
   char        x_base      [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(report out)---------------------*/
   ycolor_palette_purge    ();
   ycolor_palette_debug    ();
   /*---(passed values)------------------*/
   ycolor_degree     (a_deg);
   DEBUG_YCOLOR   yLOG_value   ("degree"    , myCOLOR.degree);
   ycolor_harmony    (a_harm);
   DEBUG_YCOLOR   yLOG_info    ("harmony"   , myCOLOR.harmony);
   ycolor_saturation (a_sat);
   DEBUG_YCOLOR   yLOG_info    ("sat_name"  , myCOLOR.sat_name);
   ycolor_value      (a_val);
   DEBUG_YCOLOR   yLOG_info    ("val_name"  , myCOLOR.val_name);
   /*---(save values)--------------------*/
   ycolor_palette__one (YCOLOR_BAS, myCOLOR.degree);
   ycolor_palette__one (YCOLOR_COM, myCOLOR.comp);
   ycolor_palette__one (YCOLOR_NEG, myCOLOR.neg);
   ycolor_palette__one (YCOLOR_POS, myCOLOR.pos);
   /*---(constants)----------------------*/
   ycolor_constant ();
   /*> ycolor_palette__save (YCOLOR_BRN, YCOLOR_NOR, "õ994500");                      <* 
    *> ycolor_palette__save (YCOLOR_BRN, YCOLOR_MAX, "õffca9f");                      <* 
    *> ycolor_palette__save (YCOLOR_BRN, YCOLOR_ACC, "õe1a06b");                      <* 
    *> ycolor_palette__save (YCOLOR_BRN, YCOLOR_LIG, "õbb6e2e");                      <* 
    *> ycolor_palette__save (YCOLOR_BRN, YCOLOR_MED, "õ994500");                      <* 
    *> ycolor_palette__save (YCOLOR_BRN, YCOLOR_DRK, "õ763500");                      <* 
    *> ycolor_palette__save (YCOLOR_BRN, YCOLOR_MUT, "õ502400");                      <* 
    *> ycolor_palette__save (YCOLOR_BRN, YCOLOR_MOR, "õ391900");                      <* 
    *> ycolor_palette__save (YCOLOR_BRN, YCOLOR_MIN, "õ130800");                      <* 
    *> ycolor_palette__save (YCOLOR_BRN, YCOLOR_TBD, "õ994500");                      <*/
   /*---(brown)--------------------------*/
   /*> ycolor_palette__save (YCOLOR_GRY, YCOLOR_NOR, "õ777777");                      <* 
    *> ycolor_palette__save (YCOLOR_GRY, YCOLOR_MAX, "õeeeeee");                      <* 
    *> ycolor_palette__save (YCOLOR_GRY, YCOLOR_ACC, "õbbbbbb");                      <* 
    *> ycolor_palette__save (YCOLOR_GRY, YCOLOR_LIG, "õ999999");                      <* 
    *> ycolor_palette__save (YCOLOR_GRY, YCOLOR_MED, "õ777777");                      <* 
    *> ycolor_palette__save (YCOLOR_GRY, YCOLOR_DRK, "õ606060");                      <* 
    *> ycolor_palette__save (YCOLOR_GRY, YCOLOR_MUT, "õ404040");                      <* 
    *> ycolor_palette__save (YCOLOR_GRY, YCOLOR_MOR, "õ202020");                      <* 
    *> ycolor_palette__save (YCOLOR_GRY, YCOLOR_MIN, "õ101010");                      <* 
    *> ycolor_palette__save (YCOLOR_GRY, YCOLOR_TBD, "õ777777");                      <*/
   /*---(rainbow)------------------------*/
   for (i = 0; i < 10; ++i) {
      ycolor_deg2hex (i * 36 + myCOLOR.degree, x_base);
      ycolor_palette__save (YCOLOR_VAR, i, x_base);
   }
   /*---(black)--------------------------*/
   /*> ycolor_palette__save (YCOLOR_SPE, YCOLOR_BLK, "õ000000");                      <*/
   /*---(error)--------------------------*/
   /*> ycolor_deg2hex (  0, x_orig);                                                  <* 
    *> yCOLOR_variant       ("-", "vivid"   , x_orig, x_base);                        <* 
    *> ycolor_palette__save (YCOLOR_SPE, YCOLOR_ERR, x_base);                         <*/
   /*---(warning)------------------------*/
   /*> ycolor_deg2hex (120, x_orig);                                                  <* 
    *> yCOLOR_variant       ("-", "vivid"   , x_orig, x_base);                        <* 
    *> ycolor_palette__save (YCOLOR_SPE, YCOLOR_WRN, x_base);                         <*/
   /*---(source)-------------------------*/
   /*> ycolor_deg2hex (180, x_orig);                                                  <* 
    *> yCOLOR_variant       ("-", "balanced", x_orig, x_base);                        <* 
    *> ycolor_palette__save (YCOLOR_SPE, YCOLOR_SRC, x_base);                         <*/
   /*---(select)-------------------------*/
   /*> ycolor_deg2hex ( 60, x_orig);                                                  <* 
    *> yCOLOR_variant       ("-", "balanced", x_orig, x_base);                        <* 
    *> ycolor_palette__save (YCOLOR_SPE, YCOLOR_SEL, x_base);                         <*/
   /*---(textreg)------------------------*/
   /*> ycolor_deg2hex (210, x_orig);                                                  <* 
    *> yCOLOR_variant       ("-", "balanced", x_orig, x_base);                        <* 
    *> ycolor_palette__save (YCOLOR_SPE, YCOLOR_REG, x_base);                         <*/
   /*---(replace)------------------------*/
   /*> ycolor_deg2hex (315, x_orig);                                                  <* 
    *> yCOLOR_variant       ("-", "balanced", x_orig, x_base);                        <* 
    *> ycolor_palette__save (YCOLOR_SPE, YCOLOR_REP, x_base);                         <*/
   /*---(input)--------------------------*/
   /*> ycolor_deg2hex (230, x_orig);                                                  <* 
    *> yCOLOR_variant       ("-", "vivid"   , x_orig, x_base);                        <* 
    *> ycolor_palette__save (YCOLOR_SPE, YCOLOR_INP, x_base);                         <*/
   /*---(wander)-------------------------*/
   /*> ycolor_deg2hex (  0, x_orig);                                                  <* 
    *> yCOLOR_variant       ("-", "balanced", x_orig, x_base);                        <* 
    *> ycolor_palette__save (YCOLOR_SPE, YCOLOR_WDR, x_base);                         <*/
   /*---(cursor)-------------------------*/
   /*> ycolor_deg2hex (120, x_orig);                                                  <* 
    *> yCOLOR_variant       ("-", "balanced", x_orig, x_base);                        <* 
    *> ycolor_palette__save (YCOLOR_SPE, YCOLOR_CUR, x_base);                         <*/
   /*---(report out)---------------------*/
   ycolor_palette_debug    ();
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycolor_opengl           (char a_type, char a_major, char a_minor, float a_alpha)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCOLOR   yLOG_value   ("a_major"   , a_major);
   --rce;  if (a_major < 0 || a_major > MAX_COLOR) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_value   (" % 10"     , a_major % 10);
   --rce;  if (a_major % 10 != 0) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_value   ("a_minor"   , a_minor);
   --rce;  if (a_major != YCOLOR_VAR && (a_minor < YCOLOR_NOR || a_minor > YCOLOR_TBD)) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_major == YCOLOR_VAR && (a_minor < YCOLOR_ONE || a_minor > YCOLOR_TWE)) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set color)----------------------*/
   DEBUG_YCOLOR   yLOG_complex ("color"     , "%5.3fr, %5.3fg, %5.3fb, %5.3fa", s_palette [a_major + a_minor].red, s_palette [a_major + a_minor].grn, s_palette [a_major + a_minor].blu, a_alpha);
   if (a_type == 'c')  glClearColor(s_palette [a_major + a_minor].red, s_palette [a_major + a_minor].grn, s_palette [a_major + a_minor].blu, a_alpha);
   else                glColor4f   (s_palette [a_major + a_minor].red, s_palette [a_major + a_minor].grn, s_palette [a_major + a_minor].blu, a_alpha);
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yCOLOR_opengl       (char a_major, char a_minor, float a_alpha) { return ycolor_opengl ('-', a_major, a_minor, a_alpha); }
char yCOLOR_opengl_clear (char a_major, char a_minor)                { return ycolor_opengl ('c', a_major, a_minor, 1.0); }

char
yCOLOR__palette_fresh (void)
{
   yCOLOR_palette (666, "=" , "=" , "=" );
   return 0;
}

char
yCOLOR_wheel         (cchar *a_name)
{
   WHEEL_set   (a_name);
   yCOLOR__palette_fresh ();
   return 0;
}

char
yCOLOR_deg           (cint a_deg)
{
   ycolor_degree (a_deg);
   yCOLOR__palette_fresh ();
   return 0;
}

char
yCOLOR_harm          (cchar *a_name)
{
   ycolor_harmony    (a_name);
   yCOLOR__palette_fresh ();
   return 0;
}


char
ycolor_palette_debug    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =  -10;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(clear)--------------------------*/
   for (i = 0; i < MAX_COLOR; ++i) {
      if      (i == YCOLOR_BAS) {
         DEBUG_YCOLOR yLOG_note    ("base colors ----------------------------");
      } else if (i == YCOLOR_COM) {
         DEBUG_YCOLOR yLOG_note    ("complementary colors -------------------");
      } else if (i == YCOLOR_NEG) {
         DEBUG_YCOLOR yLOG_note    ("negative colors ------------------------");
      } else if (i == YCOLOR_POS) {
         DEBUG_YCOLOR yLOG_note    ("positive colors ------------------------");
      } else if (i == YCOLOR_BRN) {
         DEBUG_YCOLOR yLOG_note    ("brown colors ---------------------------");
      } else if (i == YCOLOR_GRY) {
         DEBUG_YCOLOR yLOG_note    ("grey colors ----------------------------");
      } else if (i == YCOLOR_SPE) {
         DEBUG_YCOLOR yLOG_note    ("special colors -------------------------");
      } else if (i == YCOLOR_VAR) {
         DEBUG_YCOLOR yLOG_note    ("rainbow colors -------------------------");
      }
      DEBUG_YCOLOR yLOG_complex ("palette"   , "(%2d) %-7.7s, %5.3fr, %5.3fg, %5.3fb", i, s_palette [i].hex, s_palette [i].red, s_palette [i].grn, s_palette [i].blu);
   }
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}
