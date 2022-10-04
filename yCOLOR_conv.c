/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



int
ycolor_deg2fix          (cint  a_deg)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_deg       =  a_deg;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_senter  (__FUNCTION__);
   /*---(adjust range)-------------------*/
   x_deg  =  a_deg;
   DEBUG_YCOLOR   yLOG_sint    (x_deg);
   while (x_deg <    0)  x_deg +=  360;
   while (x_deg >= 360)  x_deg -=  360;
   DEBUG_YCOLOR   yLOG_sint    (x_deg);
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_sexit   (__FUNCTION__);
   return x_deg;
}

char         /*-> tbd --------------------------------[ ------ [gc.320.221.01]*/ /*-[00.0000.501.!]-*/ /*-[--.---.---.--]-*/
ycolor_deg2hex       (cint a_deg, char *a_hex)
{
   /*---(locals)-----------+-----+-----+-*/
   int         d           =    0;
   d = ycolor_deg2fix (a_deg);
   strlcpy (a_hex, g_full [d].base, LEN_TERSE);
   return 0;
}



/*============================--------------------============================*/
/*===----                       color by hex code                      ----===*/
/*============================--------------------============================*/
static void      o___BY_HEX__________________o (void) {;}

char
ycolor_hex2rgb         (char *a_hex, float *a_red, float *a_grn, float *a_blu)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   char        t           [LEN_LABEL] = "";
   double      x_red, x_grn, x_blu;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_red != NULL)  *a_red = 0.0;
   if (a_grn != NULL)  *a_grn = 0.0;
   if (a_blu != NULL)  *a_blu = 0.0;
   /*---(defense)------------------------*/
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
   DEBUG_YCOLOR   yLOG_char    ("a_hex [0]" , a_hex [0]);
   --rce;  if (a_hex [0] != 'õ') {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  for (i = 1; i < 7; ++i) {
      if (strchr ("0123456789abcdefABCDEF", a_hex [i]) == NULL) {
         DEBUG_YCOLOR   yLOG_value   ("failed ch" , i);
         DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(red)----------------------------*/
   sprintf (t, "õ%2.2s", a_hex + 1);
   rc = strl2hex (t, &x_red, LEN_LABEL);
   x_red /= 255.0;
   DEBUG_GRAF   yLOG_complex ("red"       , "%s, %4d, %6.1lf", t, rc, x_red);
   --rce;  if (rc < 0) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(green)--------------------------*/
   sprintf (t, "õ%2.2s", a_hex + 3);
   rc = strl2hex (t, &x_grn, LEN_LABEL);
   x_grn /= 255.0;
   DEBUG_GRAF   yLOG_complex ("grn"       , "%s, %4d, %6.1lf", t, rc, x_grn);
   --rce;  if (rc < 0) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(blue)---------------------------*/
   sprintf (t, "õ%2.2s", a_hex + 5);
   rc = strl2hex (t, &x_blu, LEN_LABEL);
   x_blu /= 255.0;
   DEBUG_GRAF   yLOG_complex ("blu"       , "%s, %4d, %6.1lf", t, rc, x_blu);
   --rce;  if (rc < 0) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (a_red != NULL)  *a_red = x_red;
   if (a_grn != NULL)  *a_grn = x_grn;
   if (a_blu != NULL)  *a_blu = x_blu;
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [gc.430.442.10]*/ /*-[00.0000.034.!]-*/ /*-[--.---.---.--]-*/
ycolor_rgb2hex      (char *a_hex, cfloat a_red, cfloat a_grn, cfloat a_blu)            /* value color component          (0.0-1.0) */
{
   /*---(locals)-----------+-----------+-*/
   uchar       x_red       = 0;
   uchar       x_grn       = 0;
   uchar       x_blu       = 0;
   char        x_hex       [LEN_TERSE];
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(round to one byte)----------------*/
   DEBUG_YCOLOR   yLOG_complex ("floats"    , "%5.3fr, %5.3fg, %5.3fb", a_red, a_grn, a_blu);
   x_red = a_red * 255;
   x_grn = a_grn * 255;
   x_blu = a_blu * 255;
   DEBUG_YCOLOR   yLOG_complex ("uchars"    , "%5dr, %5dg, %5db", x_red, x_grn, x_blu);
   /*---(place into RGB hex)---------------*/
   snprintf (x_hex, LEN_TERSE, "õ%02x%02x%02x", x_red, x_grn, x_blu);
   DEBUG_YCOLOR   yLOG_info    ("x_hex"     , x_hex);
   if (a_hex != NULL)  strlcpy (a_hex, x_hex, LEN_TERSE);
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> use hex code to set opengl color ---[ ------ [ge.650.255.41]*/ /*-[01.0000.503.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_hex2color     (cchar *a_hex, cfloat a_alpha)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(set color)----------------------*/
   rc = ycolor_hex2rgb (a_hex, &x_red, &x_grn, &x_blu);
   DEBUG_YCOLOR   yLOG_value   ("hex2rgb"   , rc);
   if (rc < 0) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   glColor4f   (x_red, x_grn, x_blu, a_alpha);
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}


