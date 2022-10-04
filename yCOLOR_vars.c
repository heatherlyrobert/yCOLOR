/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



#define  MAX_SATS      20
typedef  struct cSATS  tSATS;
struct cSATS {
   char        abbr;
   char        name        [LEN_LABEL];
   float       sat;
};
static tSATS  s_sats [MAX_SATS] = {
   { 'f', "full"               ,  1.00 },
   { 's', "soft"               ,  0.80 },
   { 'm', "modern"             ,  0.65 },
   { 'p', "pastel"             ,  0.55 },
   { 'l', "pale"               ,  0.33 },
   { 'w', "washed"             ,  0.15 },
   {  0 , ""                   ,  0.00 },
};
static int  s_nsats       = 0;



#define  MAX_VALS      20
typedef  struct cVALS  tVALS;
struct cVALS {
   char        abbr;
   char        name        [LEN_LABEL];
   float       val;
};
static tVALS  s_vals [MAX_VALS] = {
   { 'v', "vivid"              ,  1.00 },
   { 's', "strong"             ,  0.90 },
   { 'b', "balanced"           ,  0.80 },
   { 'w', "warm"               ,  0.70 },
   { 'm', "medium"             ,  0.60 },
   { 'e', "earthy"             ,  0.50 },
   { 'r', "rich"               ,  0.40 },
   { 'd', "dark"               ,  0.30 },
   { 'e', "deep"               ,  0.20 },
   { 'k', "blackish"           ,  0.10 },
   {  0 , ""                   ,  0.00 },
};
static int  s_nvals       = 0;



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

tVARIANT    s_variants  [MAX_VARIANT] = {
   { "-"         , "no", "none"                  ,   0.00,  0.00,  0.35 },
   /*---(full sat)--------------------*/
   { "fullsome"  , "vi", "vivid"                 ,   1.00,  1.00,  0.50 },
   { "fullsome"  , "st", "strong"                ,   1.00,  0.90,  0.50 },
   { "fullsome"  , "ba", "balanced"              ,   1.00,  0.80,  0.50 },
   { "fullsome"  , "wa", "warm"                  ,   1.00,  0.70,  0.50 },
   { "fullsome"  , "me", "medium"                ,   1.00,  0.60,  0.50 },
   { "fullsome"  , "ea", "earthy"                ,   1.00,  0.50,  0.50 },
   { "fullsome"  , "ri", "rich"                  ,   1.00,  0.40,  0.50 },
   { "fullsome"  , "da", "dark"                  ,   1.00,  0.30,  0.50 },
   { "fullsome"  , "de", "deep"                  ,   1.00,  0.20,  0.50 },
   { "fullsome"  , "bk", "black"                 ,   1.00,  0.10,  0.50 },
   /*---(strong sat)------------------*/
   { "warmer"    , "br", "bright"                ,   0.80,  1.00,  0.50 },
   { "warmer"    , "ar", "artists"               ,   0.80,  0.90,  0.50 },
   { "warmer"    , "ar", "artists"               ,   0.80,  0.80,  0.50 },
   { "warmer"    , "ar", "artists"               ,   0.80,  0.70,  0.50 },
   { "warmer"    , "ar", "artists"               ,   0.80,  0.60,  0.50 },
   { "warmer"    , "ar", "artists"               ,   0.80,  0.50,  0.50 },
   { "warmer"    , "ar", "artists"               ,   0.80,  0.40,  0.50 },
   { "warmer"    , "ar", "artists"               ,   0.80,  0.30,  0.50 },
   { "warmer"    , "ar", "artists"               ,   0.80,  0.20,  0.50 },
   { "warmer"    , "ar", "artists"               ,   0.80,  0.10,  0.50 },
   /*---(whiteish)--------------------*/
   { "whites"    , "--", "whiteish"              ,   0.15,  1.00,  0.50 },
   { "whites"    , "--", "pale"                  ,   0.15,  0.90,  0.50 },
   { "whites"    , "--", "pale"                  ,   0.15,  0.70,  0.50 },
   /*---(modern)----------------------*/
   { "modern"    , "22", "modern"                ,   0.65,  1.00,  0.50 },
   { "modern"    , "mo", "modern"                ,   0.65,  0.90,  0.50 },
   { "modern"    , "mo", "modern"                ,   0.65,  0.80,  0.50 },
   { "modern"    , "mo", "modern"                ,   0.65,  0.70,  0.50 },
   { "modern"    , "mo", "modern"                ,   0.65,  0.60,  0.50 },
   { "modern"    , "mo", "modern"                ,   0.65,  0.50,  0.50 },
   { "modern"    , "ne", "neutral"               ,   0.65,  0.35,  0.50 },
   /*---(moderate sat)----------------*/
   { "pastels"   , "ch", "chalk"                 ,   0.50,  1.00,  0.50 },
   { "pastels"   , "pa", "pastel"                ,   0.50,  0.90,  0.50 },
   { "pastels"   , "xp", "pastel_csd"            ,   0.50,  0.80,  0.50 },
   { "pastels"   , "op", "pastel_oil"            ,   0.50,  0.70,  0.50 },
   { "pastels"   , "--", "pastel_med"            ,   0.50,  0.60,  0.25 },
   { "pastels"   , "su", "pastel_rich"           ,   0.50,  0.50,  0.50 },
   { "pastels"   , "co", "pastel_dark"           ,   0.50,  0.40,  0.50 },
   { "pastels"   , "co", "pastel_deep"           ,   0.50,  0.30,  0.50 },
   /*---(low sat)---------------------*/
   { "pales"     , "--", "whiteish"              ,   0.30,  1.00,  0.50 },
   { "pales"     , "--", "pale"                  ,   0.30,  0.90,  0.50 },
   { "pales"     , "--", "pale"                  ,   0.30,  0.80,  0.50 },
   { "pales"     , "li", "light"                 ,   0.30,  0.70,  0.50 },
   { "pales"     , "li", "light"                 ,   0.30,  0.60,  0.50 },
   { "pales"     , "wa", "washout"               ,   0.30,  0.50,  0.50 },
   { "pales"     , "wa", "washout"               ,   0.30,  0.40,  0.50 },
   { "pales"     , "gr", "greyish"               ,   0.30,  0.30,  0.50 },
   { "pales"     , "gr", "least"                 ,   0.30,  0.20,  0.50 },
   /*---(complete)--------------------*/
   { "-"         , ""  , "end of input"          ,   0.00,  0.00,  0.00 },
   /*---(older)-----------------------*/
};



/*============================--------------------============================*/
/*===----                         saturations                          ----===*/
/*============================--------------------============================*/
static void      o___SATURATION______________o (void) {;}

char
ycolor_sat_init         (void)
{
   char        i           =    0;
   DEBUG_YCOLOR   yLOG_senter  (__FUNCTION__);
   s_nsats  = 0;
   for (i = 0; i < MAX_SATS; ++i) {
      /*---(filter)----------------------*/
      if (s_sats [i].abbr ==  0)      break;
      ++s_nsats;
   }
   ycolor_saturation ("pastel");
   DEBUG_YCOLOR   yLOG_sint    ("s_nsats");
   DEBUG_YCOLOR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ycolor_sat_by_abbr      (cchar a_abbr)
{
   char        rce         =  -10;
   char        i           =    0;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_senter  (__FUNCTION__);
   DEBUG_YCOLOR   yLOG_sint    (a_abbr);
   /*---(defense)------------------------*/
   --rce;  if (a_abbr <= G_KEY_SPACE) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_abbr >= G_KEY_TILDA) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_schar   (a_abbr);
   /*---(find)---------------------------*/
   for (i = 0; i < s_nsats; ++i) {
      /*---(filter)----------------------*/
      if (s_sats [i].abbr != a_abbr)      continue;
      /*---(accept)----------------------*/
      n = i;
      break;
   }
   DEBUG_YCOLOR   yLOG_sint    (n);
   /*---(check for error)----------------*/
   --rce;  if (n < 0) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_sexit   (__FUNCTION__);
   return n;
}

char
ycolor_sat_by_name      (cchar *a_name)
{
   char        rce         =  -10;
   char        i           =    0;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCOLOR   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_snote   (a_name);
   /*---(find)---------------------------*/
   for (i = 0; i < s_nsats; ++i) {
      /*---(filter)----------------------*/
      if (s_sats [i].name [0] != a_name [0])      continue;
      if (strcmp (s_sats [i].name, a_name) != 0)  continue;
      /*---(accept)----------------------*/
      n = i;
      break;
   }
   DEBUG_YCOLOR   yLOG_sint    (n);
   /*---(check for error)----------------*/
   --rce;  if (n < 0) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_sexit   (__FUNCTION__);
   return n;
}

char
ycolor_saturation       (cchar *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(current)------------------------*/
   DEBUG_YCOLOR   yLOG_value   ("sat"       , myCOLOR.sat);
   DEBUG_YCOLOR   yLOG_info    ("sat_name"  , myCOLOR.sat_name);
   /*---(leave alone)--------------------*/
   DEBUG_YCOLOR   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_info    ("a_name"    , a_name);
   if (strcmp (a_name, "=") == 0) {
      DEBUG_YCOLOR   yLOG_note    ("leave same, nothing to do");
      DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(have no effect)-----------------*/
   if (strcmp (a_name, "-") == 0 || strcmp (a_name, "none") == 0) {
      DEBUG_YCOLOR   yLOG_note    ("leave same, nothing to do");
      strlcpy (myCOLOR.sat_name, "NONE", LEN_LABEL);
      myCOLOR.sat    = -1.0;
      DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(find harmony)-------------------*/
   if (strlen (a_name) == 1)   n = ycolor_sat_by_abbr (a_name [0]);
   else                        n = ycolor_sat_by_name (a_name);
   if (n < 0)  {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, n);
      return n;
   }
   /*---(set color degree)---------------*/
   myCOLOR.sat    = s_sats [n].sat;
   strlcpy (myCOLOR.sat_name, s_sats [n].name, LEN_LABEL);
   /*---(display)------------------------*/
   DEBUG_YCOLOR   yLOG_value   ("sat"       , myCOLOR.sat);
   DEBUG_YCOLOR   yLOG_info    ("sat_name"  , myCOLOR.sat_name);
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yCOLOR_sat           (cchar *a_name)
{
   ycolor_saturation    (a_name);
   yCOLOR__palette_fresh ();
   return 0;
}



/*============================--------------------============================*/
/*===----                           values                             ----===*/
/*============================--------------------============================*/
static void      o___VALUES__________________o (void) {;}

char
ycolor_val_init         (void)
{
   char        i           =    0;
   DEBUG_YCOLOR   yLOG_senter  (__FUNCTION__);
   s_nvals  = 0;
   for (i = 0; i < MAX_VALS; ++i) {
      /*---(filter)----------------------*/
      if (s_vals [i].abbr ==  0)      break;
      ++s_nvals;
   }
   ycolor_value ("warm");
   DEBUG_YCOLOR   yLOG_sint    ("s_nvals");
   DEBUG_YCOLOR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ycolor_val_by_abbr      (cchar a_abbr)
{
   char        rce         =  -10;
   char        i           =    0;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_senter  (__FUNCTION__);
   DEBUG_YCOLOR   yLOG_sint    (a_abbr);
   /*---(defense)------------------------*/
   --rce;  if (a_abbr <= G_KEY_SPACE) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_abbr >= G_KEY_TILDA) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_schar   (a_abbr);
   /*---(find)---------------------------*/
   for (i = 0; i < s_nvals; ++i) {
      /*---(filter)----------------------*/
      if (s_vals [i].abbr != a_abbr)      continue;
      /*---(accept)----------------------*/
      n = i;
      break;
   }
   DEBUG_YCOLOR   yLOG_sint    (n);
   /*---(check for error)----------------*/
   --rce;  if (n < 0) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_sexit   (__FUNCTION__);
   return n;
}

char
ycolor_val_by_name      (cchar *a_name)
{
   char        rce         =  -10;
   char        i           =    0;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCOLOR   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_snote   (a_name);
   /*---(find)---------------------------*/
   for (i = 0; i < s_nvals; ++i) {
      /*---(filter)----------------------*/
      if (s_vals [i].name [0] != a_name [0])      continue;
      if (strcmp (s_vals [i].name, a_name) != 0)  continue;
      /*---(accept)----------------------*/
      n = i;
      break;
   }
   DEBUG_YCOLOR   yLOG_sint    (n);
   /*---(check for error)----------------*/
   --rce;  if (n < 0) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_sexit   (__FUNCTION__);
   return n;
}

char
ycolor_value            (cchar *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(current)------------------------*/
   DEBUG_YCOLOR   yLOG_value   ("val"       , myCOLOR.val);
   DEBUG_YCOLOR   yLOG_info    ("val_name"  , myCOLOR.val_name);
   /*---(leave alone)--------------------*/
   DEBUG_YCOLOR   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_info    ("a_name"    , a_name);
   if (strcmp (a_name, "=") == 0) {
      DEBUG_YCOLOR   yLOG_note    ("leave same, nothing to do");
      DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(have no effect)-----------------*/
   if (strcmp (a_name, "-") == 0 || strcmp (a_name, "none") == 0) {
      DEBUG_YCOLOR   yLOG_note    ("leave same, nothing to do");
      strlcpy (myCOLOR.val_name, "NONE", LEN_LABEL);
      myCOLOR.val    = -1.0;
      DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(find harmony)-------------------*/
   if (strlen (a_name) == 1)   n = ycolor_val_by_abbr (a_name [0]);
   else                        n = ycolor_val_by_name (a_name);
   DEBUG_YCOLOR   yLOG_sint    (n);
   /*---(check for error)----------------*/
   if (n < 0)  {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, n);
      return n;
   }
   /*---(set color degree)---------------*/
   myCOLOR.val    = s_vals [n].val;
   strlcpy (myCOLOR.val_name, s_vals [n].name, LEN_LABEL);
   /*---(display)------------------------*/
   DEBUG_YCOLOR   yLOG_value   ("val"       , myCOLOR.val);
   DEBUG_YCOLOR   yLOG_info    ("val_name"  , myCOLOR.val_name);
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yCOLOR_val           (cchar *a_name)
{
   ycolor_value    (a_name);
   yCOLOR__palette_fresh ();
   return 0;
}



/*============================--------------------============================*/
/*===----                         color changes                        ----===*/
/*============================--------------------============================*/
static void      o___CHANGES_________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [ge.E90.179.52]*/ /*-[01.0000.104.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_accent        (       /* PURPOSE = apply a color variation             */
      cchar    a_level,           /* accent level                             */
      cchar    *a_hex,            /* rgb three byte hex code        (#rrggbb) */
      char     *a_out)            /* rgb three byte hex code        (#rrggbb) */
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;      /* return code for errors              */
   int         i           =   0;      /* generic iterator                    */
   /*> int         x_index     =  -1;      /+ variant index                       +/   <*/
   int         rc          =   0;      /* generic return code                 */
   float       x_hue       =   0.00;   /* HSV hue                             */
   float       x_sat       =   0.00;   /* HSV saturation                      */
   float       x_val       =   0.00;   /* HSV value                           */
   float       x_acc       =   0.50;
   /*---(defense)--------------------------*/
   --rce;  if (a_hex  == NULL) {
      return rce;
   }
   --rce;  if (a_out  == NULL) {
      return rce;
   }
   /*---(initialize)-----------------------*/
   strlcpy (a_out, a_hex, LEN_TERSE);
   /*---(search)---------------------------*/
   /*> x_index = s_cvariant;                                                          <*/
   /*> x_accent = s_variants [x_index].accent;                                        <*/
   /*---(get the base)---------------------*/
   rc = yCOLOR_hex2hsv (a_hex, &x_hue, &x_sat, &x_val);
   --rce;  if (rc != 0) {
      return rce;
   }
   /*> printf ("\n");                                                                                     <* 
    *> printf ("base   hex = %s, hue = %4.2f, sat = %4.2f, val = %4.2f\n", a_hex, x_hue, x_sat, x_val);   <*/
   /*---(get the modifiers)----------------*/
   --rce;  switch (a_level) {
   case '.' : /* normal        */
      return  0;
      break;
   case '!' : /* max/palest    */
      x_sat   = x_sat - (x_sat * (x_acc * 1.25));
      x_val   = x_val + (x_val * (x_acc * 1.50));
      break;
   case '^' : /* lightest      */
      x_sat   = x_sat - (x_sat * (x_acc * 0.95));
      x_val   = x_val + (x_val * (x_acc * 0.95));
      break;
   case '+' : /* lighter       */
      x_sat   = x_sat - (x_sat * (x_acc * 0.50));
      x_val   = x_val + (x_val * (x_acc * 0.45));
      break;
   case '-' : /* darker        */
      x_sat   = x_sat;
      x_val   = x_val - (x_val * (x_acc * 0.45));
      break;
   case 'v' : /* darkest       */
      x_sat   = x_sat;
      x_val   = x_val - (x_val * (x_acc * 0.95));
      break;
   case '#' : /* deep          */
      x_sat   = x_sat + (x_sat * (x_acc * 0.75));
      x_val   = x_val - (x_val * (x_acc * 1.25));
      break;
   case '@' : /* min/black     */
      x_sat   = x_sat + (x_sat * (x_acc * 1.40));
      x_val   = x_val - (x_val * (x_acc * 1.75));
      break;
   default  :
      return rce;
      break;
   }
   /*---(apply the modifiers)--------------*/
   rc = yCOLOR_hsv2hex (a_out, x_hue, x_sat, x_val);
   /*> printf ("modded hex = %s, hue = %4.2f, sat = %4.2f, val = %4.2f\n", a_out, x_hue, x_sat, x_val);   <*/
   --rce;  if (rc != 0) {
      return rce;
   }
   /*---(complete)-------------------------*/
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [ge.E80.17#.F2]*/ /*-[04.0000.403.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_variant       (       /* PURPOSE = apply a color variation             */
      cchar    *a_sat,            /* variation saturation name                */
      cchar    *a_val,            /* variation value name                     */
      cchar    *a_hex,            /* rgb three byte hex code        (#rrggbb) */
      char     *a_out)            /* rgb three byte hex code        (#rrggbb) */
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;      /* return code for errors              */
   int         rc          =   0;      /* generic return code                 */
   float       x_newsat    =   0.0;    /* HSV saturation                      */
   float       x_newval    =   0.0;    /* HSV saturation                      */
   float       x_hue       =   0.0;    /* HSV hue                             */
   float       x_sat       =   0.0;    /* HSV saturation                      */
   float       x_val       =   0.0;    /* HSV value                           */
   int         n           =   0;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCOLOR   yLOG_point   ("a_hex"     , a_hex);
   --rce;  if (a_hex == NULL) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_info    ("a_hex"     , a_hex);
   DEBUG_YCOLOR   yLOG_point   ("a_out"     , a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, a_hex, LEN_TERSE);
   /*---(saturation)---------------------*/
   DEBUG_YCOLOR   yLOG_point   ("a_sat"     , a_sat);
   --rce; if (a_sat == NULL) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_info    ("a_sat"     , a_sat);
   --rce; if (strcmp (a_sat, "=") == 0)  x_newsat = myCOLOR.sat;
   else if   (strcmp (a_sat, "-") == 0)  x_newsat = -1.00;
   else {
      if (strlen (a_sat) == 1)  n = ycolor_sat_by_abbr (a_sat);
      else                      n = ycolor_sat_by_name (a_sat);
      if (n <  0)  {
         DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_newsat = s_sats [n].sat;
   }
   DEBUG_YCOLOR   yLOG_double  ("x_newsat"  , x_newsat);
   /*---(value)--------------------------*/
   DEBUG_YCOLOR   yLOG_point   ("a_val"     , a_val);
   --rce; if (a_val == NULL) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_info    ("a_val"     , a_val);
   --rce; if (strcmp (a_val, "=") == 0)  x_newval = myCOLOR.val;
   else if   (strcmp (a_val, "-") == 0)  x_newval = -1.00;
   else {
      if (strlen (a_val) == 1)  n = ycolor_val_by_abbr (a_val);
      else                      n = ycolor_val_by_name (a_val);
      if (n <  0) {
         DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_newval = s_vals [n].val;
   }
   DEBUG_YCOLOR   yLOG_double  ("x_newval"  , x_newval);
   /*---(get the base)---------------------*/
   rc = yCOLOR_hex2hsv (a_hex, &x_hue, &x_sat, &x_val);
   DEBUG_YCOLOR   yLOG_value   ("hex2hsv"   , rc);
   --rce;  if (rc != 0) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_complex ("as is"     , "%6.3fh, %6.3fs, %6.3fv", x_hue, x_sat, x_val);
   /*---(get the modifiers)----------------*/
   if (x_newsat >= 0)  x_sat = x_newsat;
   if (x_newval >= 0)  x_val = x_newval;
   /*---(apply the modifiers)--------------*/
   DEBUG_YCOLOR   yLOG_complex ("becoming"  , "%6.3fh, %6.3fs, %6.3fv", x_hue, x_sat, x_val);
   rc = yCOLOR_hsv2hex (a_out, x_hue, x_sat, x_val);
   DEBUG_YCOLOR   yLOG_value   ("hsv2hex"   , rc);
   --rce;  if (rc != 0) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_info    ("a_out"     , a_out);
   /*---(complete)-------------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gc.430.242.02]*/ /*-[00.0000.103.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_normalize     (cchar *a_hex, char *a_out)
{
   /*---(locals)-----------+-----------+-*/
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   float       x_squared   = 0.0;
   ycolor_hex2rgb (a_hex, &x_red, &x_grn, &x_blu);
   x_squared = (x_red * x_red) + (x_grn * x_grn) + (x_blu * x_blu);
   x_squared = sqrt (x_squared);
   x_red = x_red / x_squared;
   x_grn = x_grn / x_squared;
   x_blu = x_blu / x_squared;
   ycolor_rgb2hex (a_out, x_red, x_grn, x_blu);
   /*> printf ("yCOLOR_normalize, a_hex=%s, a_out=%s\n", a_hex, a_out);               <*/
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [gc.430.122.30]*/ /*-[03.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_norming_find  (char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   int         x_index     = 0;
   /*---(search)---------------------------*/
   for (i = 0; i < MAX_NORMING; ++i) {
      if (s_normings [i].abbr [0] == '\0')            break;
      if (s_normings [i].abbr [0] != a_name [0])      continue;
      if ((strcmp (s_normings [i].abbr, a_name) != 0) &&
            (strcmp (s_normings [i].name, a_name) != 0))  continue;
      x_index = i;
      break;
   }
   /*---(complete)-------------------------*/
   return x_index;
}

char         /*-> tbd --------------------------------[ ------ [fc.E90.1L2.33]*/ /*-[01.0000.10#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR__norming        (      /* PURPOSE = level color intensity               */
      int       a_index,          /* norming index                            */
      char     *a_hex,            /* rgb three byte hex code        (#rrggbb) */
      char     *a_out)            /* rgb three byte hex code        (#rrggbb) */
{
   /*---(locals)-----------+-----------+-*/
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   float       x_hue       = 0.0;
   float       x_sat       = 0.0;
   float       x_val       = 0.0;
   float       x_total     = 0.0;
   int         rc          = 0;
   float       x_norm      = 0.0;
   float       x_redpct    = 0.0;
   float       x_grnpct    = 0.0;
   float       x_blupct    = 0.0;
   /*---(brightness)-----------------------*/
   float  d_red  = s_normings [a_index].red;
   float  d_grn  = s_normings [a_index].grn;
   float  d_blu  = s_normings [a_index].blu;
   /*> printf("norming [%d]... hsv based = %c\n", a_index, s_normings [a_index].is_value);   <* 
    *> printf("  factor    %5.3fr, %5.3fg, %5.3fb\n", d_red, d_grn, d_blu);                    <*/
   /*> printf("  color     %3dr, %3dg, %3db\n", x_red, x_grn, x_blu);                 <*/
   /*---(pull values)----------------------*/
   ycolor_hex2rgb (a_hex, &x_red, &x_grn, &x_blu);
   if (s_normings [a_index].is_value == 'y') {
      /*---(update)---------------------------*/
      x_red *= (s_normings [a_index].red);
      x_grn *= (s_normings [a_index].grn);
      x_blu *= (s_normings [a_index].blu);
      x_norm = 1.000 - x_red - x_grn - x_blu;
      yCOLOR_hex2hsv (a_hex, &x_hue, &x_sat, &x_val);
      yCOLOR_hsv2hex (a_out, x_hue, x_sat, x_val * x_norm);
   } else if (s_normings [a_index].is_value == 'n') {
      /*---(update)---------------------------*/
      x_red *= (1.0 - s_normings [a_index].red);
      x_grn *= (1.0 - s_normings [a_index].grn);
      x_blu *= (1.0 - s_normings [a_index].blu);
      /*---(truncate into 0-255)--------------*/
      uchar u_red = x_red * 255;
      uchar u_grn = x_grn * 255;
      uchar u_blu = x_blu * 255;
      /*---(place into RGB hex)---------------*/
      snprintf (a_out, LEN_TERSE, "õ%02x%02x%02x", u_red, u_grn, u_blu);
   } else if (s_normings [a_index].is_value == 't') {
      /*---(update)---------------------------*/
      x_total = x_red + x_grn + x_blu;
      x_redpct = x_red / x_total;
      x_grnpct = x_grn / x_total;
      x_blupct = x_blu / x_total;
      /*---(truncate into 0-255)--------------*/
      uchar u_red = x_redpct * 255;
      uchar u_grn = x_grnpct * 255;
      uchar u_blu = x_blupct * 255;
      /*---(place into RGB hex)---------------*/
      snprintf (a_out, LEN_TERSE, "õ%02x%02x%02x", u_red, u_grn, u_blu);
   }
   /*---(complete)-------------------------*/
   return 0;
}

char
VARS_seq                (int a_seq, char *a_sat, char *a_val, char *a_abbr)
{
   char        rce         =  -10;
   char        x_sat       =    0;
   char        x_val       =    0;
   --rce;  if (a_seq < 0 )                  return rce;
   --rce;  if (a_seq >= s_nsats * s_nvals)  return rce;
   x_sat = a_seq / s_nvals;
   x_val = a_seq % s_nvals;
   if (a_sat  != NULL)  strlcpy (a_sat, s_sats [x_sat].name, LEN_LABEL);
   if (a_val  != NULL)  strlcpy (a_val, s_vals [x_val].name, LEN_LABEL);
   if (a_abbr != NULL)  *a_abbr = s_vals [x_val].abbr;
   return 0;
}



