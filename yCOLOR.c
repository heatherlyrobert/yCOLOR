/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



char        s_use       = YCOLOR_WHEEL;
char        s_scale     = YCOLOR_LINEAR;
int         s_cset      =  1;
int         s_tcolor    =  0;
int         s_ncolor    =  0;
int         s_cvariant  =  0;
int         s_lvariant  =  0;
int         s_nvariant  =  0;
int         s_cnorming  =  0;
int         s_nnorming  =  0;



tCOLORS     s_colors    [MAX_COLOR];
tACCESSOR   myCOLOR;

tPALETTE    s_palette   [MAX_COLOR];



/*============================--------------------============================*/
/*===----                           utility                            ----===*/
/*============================--------------------============================*/
static void      o___UTILITY_________________o (void) {;}

static char      yCOLOR_ver [200] = "";

char*        /*-> return versioning info -------------[ leaf   [gs.420.012.00]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_version      (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 15);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yCOLOR_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yCOLOR_ver;
}

float        /*-> tbd --------------------------------[ leaf   [fn.320.305.40]*/ /*-[01.0000.015.!]-*/ /*-[--.---.---.--]-*/
yCOLOR__min3       (float a_1st, float a_2nd, float a_3rd)
{
   if    (a_1st <= a_2nd) {
      if (a_1st <= a_3rd)  return a_1st;
      return                      a_3rd;
   } else {
      if (a_2nd <= a_3rd)  return a_2nd;
      return                      a_3rd;
   }
   return                         a_2nd;
}

float        /*-> tbd --------------------------------[ leaf   [fn.320.305.40]*/ /*-[01.0000.015.!]-*/ /*-[--.---.---.--]-*/
yCOLOR__max3       (float a_1st, float a_2nd, float a_3rd)
{
   if    (a_1st >= a_2nd) {
      if (a_1st >= a_3rd)  return a_1st;
      return                      a_3rd;
   } else {
      if (a_2nd >= a_3rd)  return a_2nd;
      return                      a_3rd;
   }
   return                         a_2nd;
}



/*============================--------------------============================*/
/*===----                         preparation                          ----===*/
/*============================--------------------============================*/
static void      o___PREPARATION_____________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [ge.MI0.152.81]*/ /*-[02.0000.711.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_use           (char  a_use)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;      /* return code for errors              */
   char        x_ncolor    =   0;
   int         i           =   0;
   int         x_index     =   0;
   char        x_hex       [LEN_TERSE];
   /*---(defense)------------------------*/
   --rce;  if (strchr ("wkrmBbslg", a_use) == NULL) {
      a_use = YCOLOR_WHEEL;   /* safe default */
   }
   /*---(set global)---------------------*/
   s_use = a_use;
   switch (a_use) {
   case YCOLOR_WHEEL   :
      x_ncolor = 36;
      for (i = 0; i < x_ncolor; ++i) {
         x_index = i + 12;
         strlcpy (s_colors [i].name, s_RYB [x_index][0     ], LEN_LABEL);
         strlcpy (s_colors [i].hex , s_RYB [x_index][s_cset], LEN_LABEL);
      }
      break;
   case YCOLOR_SPOKES  :
      x_ncolor = 12;
      for (i = 0; i < x_ncolor; ++i) {
         x_index  = i * 3;
         x_index += 12;
         strlcpy (s_colors [i].name, s_RYB [x_index][0     ], LEN_LABEL);
         strlcpy (s_colors [i].hex , s_RYB [x_index][s_cset], LEN_LABEL);
      }
      break;
   case YCOLOR_REDBLU  :
      x_ncolor = 25;
      for (i = 0; i < x_ncolor; ++i) {
         x_index = i + 12;
         strlcpy (s_colors [i].name, s_RYB [x_index][0     ], LEN_LABEL);
         strlcpy (s_colors [i].hex , s_RYB [x_index][s_cset], LEN_LABEL);
      }
      break;
   case YCOLOR_REDMAU  :
      x_ncolor = 37;
      for (i = 0; i < x_ncolor; ++i) {
         x_index = i + 12;
         if (x_index > 12 + 30)  x_index += 6;
         strlcpy (s_colors [i].name, s_RYB [x_index][0     ], LEN_LABEL);
         strlcpy (s_colors [i].hex , s_RYB [x_index][s_cset], LEN_LABEL);
      }
      break;
   case YCOLOR_BROMAU  :
      x_ncolor = 49;
      for (i = 0; i < x_ncolor; ++i) {
         x_index = i;
         if (x_index > 12 + 30)  x_index += 6;
         strlcpy (s_colors [i].name, s_RYB [x_index][0     ], LEN_LABEL);
         strlcpy (s_colors [i].hex , s_RYB [x_index][s_cset], LEN_LABEL);
      }
      break;
   case YCOLOR_BROMAU2 :
      x_ncolor = 25;
      for (i = 0; i < x_ncolor; ++i) {
         x_index = i * 2;
         if (x_index > 12 + 30)  x_index += 6;
         strlcpy (s_colors [i].name, s_RYB [x_index][0     ], LEN_LABEL);
         strlcpy (s_colors [i].hex , s_RYB [x_index][s_cset], LEN_LABEL);
      }
      break;
   case YCOLOR_SMALL   :
      x_ncolor = 21;
      for (i = 0; i < x_ncolor; ++i) {
         x_index = i * 3;
         if (x_index > 12 + 30)  x_index += 6;
         strlcpy (s_colors [i].name, s_RYB [x_index][0     ], LEN_LABEL);
         strlcpy (s_colors [i].hex , s_RYB [x_index][s_cset], LEN_LABEL);
      }
      break;
   case YCOLOR_LARGE   :
      x_ncolor = 31;
      for (i = 0; i < x_ncolor; ++i) {
         x_index = i * 2;
         if (x_index > 12 + 30)  x_index += 6;
         strlcpy (s_colors [i].name, s_RYB [x_index][0     ], LEN_LABEL);
         strlcpy (s_colors [i].hex , s_RYB [x_index][s_cset], LEN_LABEL);
      }
      break;
   case YCOLOR_GIANT  :
      x_ncolor = 61;
      for (i = 0; i < x_ncolor; ++i) {
         x_index = i;
         if (x_index > 12 + 30)  x_index += 6;
         strlcpy (s_colors [i].name, s_RYB [x_index][0     ], LEN_LABEL);
         strlcpy (s_colors [i].hex , s_RYB [x_index][s_cset], LEN_LABEL);
      }
      break;
   default           :  x_ncolor =  0;  break;
   }
   /*---(set rgb values)-----------------*/
   for (i = 0; i < x_ncolor; ++i) {
      strlcpy (x_hex, s_colors [i].hex, LEN_TERSE);
      ycolor_hex2rgb (x_hex, &s_colors [i].red, &s_colors [i].grn, &s_colors [i].blu);
   }
   /*---(complete)-----------------------*/
   s_ncolor = x_ncolor;
   return x_ncolor;
}

char         /*-> tbd --------------------------------[ leaf   [ge.C90.373.40]*/ /*-[02.0000.102.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_scale         (char  a_scale, float a_min, float a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;      /* return code for errors              */
   float       x_inc       = 0.0;
   float       x_range     = 0.0;
   float       x_max       = 0.0;
   int         x_end       = 0.0;
   int         i           =   0;
   int         c           =   0;
   /*---(defense)------------------------*/
   --rce;  if (strchr ("lsp", a_scale) == NULL) {
      s_scale = YCOLOR_LINEAR;   /* safe default */
      return rce;
   }
   /*---(set global)---------------------*/
   s_scale = a_scale;
   switch (a_scale) {
   case YCOLOR_LINEAR    :
      x_range = a_max - a_min;
      x_inc   = x_range / s_ncolor;
      for (c = 0; c < s_ncolor; ++c) {
         s_colors [c].pct = (float) c / (float) s_ncolor;
         s_colors [c].cut  = s_colors [c].pct * a_max;
         /*> printf ("%2d   %6.2f  >= %6.2f\n", c, s_colors [c].pct, s_colors [c].cut);   <*/
      }
      break;
   case YCOLOR_SQUARED   :
      break;
   case YCOLOR_PARABOLIC :
      x_end   = (s_ncolor / 2) + 1;
      x_max   = x_end * x_end;
      /*> printf ("s_ncolor = %2d\n", s_ncolor);                                      <* 
       *> printf ("a_min    = %6.2f\n", a_min);                                       <* 
       *> printf ("a_max    = %6.2f\n", a_max);                                       <* 
       *> printf ("x_max    = %6.2f\n", x_max);                                       <* 
       *> printf ("x_end    = %2d\n", x_end);                                         <*/
      for (i = -x_end; i <= x_end; ++i) {
         if (i <= 1.5 && i >= -1.5)  continue;
         s_colors [c].pct = (float) (i * i) / x_max;
         if (i < 0.0)  s_colors [c].pct *= -1;
         s_colors [c].cut  = s_colors [c].pct * a_max;
         /*> printf ("%2d   %4d   %4d   %5.2f   %6.1f\n", c,  i, (i * i), s_colors [c].pct, s_colors [c].cut);   <*/
         ++c;
      }
      /*> s_colors [0].cut = - (a_max * a_max);                                       <*/
      s_colors [s_ncolor - 1].cut = a_max * a_max;
      break;
   default               :
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [fz.CA0.2H1.12]*/ /*-[02.0000.014.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_clear         (int a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        i           =    0;
   for (i = 0; i < MAX_COLOR; ++i) {
      strlcpy (s_RYB [i][a_index], "�000000", LEN_TERSE);
   }
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [fz.CA0.2H1.12]*/ /*-[02.0000.014.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_load          (int a_deg, char *a_hex)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_base      =    0;
   char        x_sub       =    0;
   char        x_index     =    0;
   float       x_red1      =  0.0;
   float       x_red2      =  0.0;
   float       x_grn1      =  0.0;
   float       x_grn2      =  0.0;
   float       x_blu1      =  0.0;
   float       x_blu2      =  0.0;
   float       x_rinc      =  0.0;
   float       x_ginc      =  0.0;
   float       x_binc      =  0.0;
   char        x_hex       [LEN_TERSE];
   uchar       u_red       =    0;
   uchar       u_grn       =    0;
   uchar       u_blu       =    0;
   /*---(check color)--------------------*/
   rc = yCOLOR_hex2color (a_hex, 1.0);
   --rce;  if (rc < 0)  return  rce;
   /*---(find last)----------------------*/
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [fz.CA0.2H1.12]*/ /*-[02.0000.014.!]-*/ /*-[--.---.---.--]-*/
yCOLOR__interpolate  (int a_beg, int a_end)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   char        x_base      =   0;
   char        x_sub       =   0;
   char        x_index     =   0;
   float       x_red1      = 0.0;
   float       x_red2      = 0.0;
   float       x_grn1      = 0.0;
   float       x_grn2      = 0.0;
   float       x_blu1      = 0.0;
   float       x_blu2      = 0.0;
   float       x_rinc      = 0.0;
   float       x_ginc      = 0.0;
   float       x_binc      = 0.0;
   char        x_hex       [LEN_TERSE];
   uchar       u_red       =   0;
   uchar       u_grn       =   0;
   uchar       u_blu       =   0;
   /*---(interpolate to 360)-------------*/
   for (x_base = a_beg; x_base <  a_end; ++x_base) {
      /*---(calc offset)-----------------*/
      x_index = x_base * 6;
      /*> if (x_base >= 8)  x_index += 6;                                             <*/
      /*---(calc start)------------------*/
      strlcpy (x_hex , s_RYB [x_index + 0][10], LEN_TERSE);
      ycolor_hex2rgb (x_hex, &x_red1, &x_grn1, &x_blu1);
      /*---(calc end)--------------------*/
      strlcpy (x_hex , s_RYB [x_index + 6][10], LEN_TERSE);
      ycolor_hex2rgb (x_hex, &x_red2, &x_grn2, &x_blu2);
      /*---(calc increments)-------------*/
      x_rinc = (x_red2 - x_red1) / 6.0;
      x_ginc = (x_grn2 - x_grn1) / 6.0;
      x_binc = (x_blu2 - x_blu1) / 6.0;
      /*---(get colors)------------------*/
      for (x_sub  = 1; x_sub  <  6; ++x_sub ) {
         x_red1 += x_rinc;
         x_grn1 += x_ginc;
         x_blu1 += x_binc;
         /*---(truncate into 0-255)--------------*/
         ycolor_rgb2hex  (x_hex, x_red1, x_grn1, x_blu1);
         /*> u_red = x_red1 * 255;                                                    <* 
          *> u_grn = x_grn1 * 255;                                                    <* 
          *> u_blu = x_blu1 * 255;                                                    <* 
          *> /+---(place into RGB hex)---------------+/                               <* 
          *> snprintf (x_hex, LEN_TERSE, "�%02x%02x%02x", u_red, u_grn, u_blu);         <*/
         strlcpy (s_RYB [x_index + x_sub][10], x_hex, LEN_TERSE);
      }
   }
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.640.031.01]*/ /*-[01.0000.013.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_custom        (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   char        x_base      =   0;
   char        x_index     =   0;
   /*---(clear hexes)--------------------*/
   for (x_index = 0; x_index < MAX_COLOR; ++x_index) {
      strlcpy (s_RYB [x_index][10], "�------"        , LEN_TERSE);
   }
   /*---(copy bases)---------------------*/
   for (x_base = 0; x_base < 12; ++x_base) {
      x_index = x_base * 6;
      strlcpy (s_RYB [x_index][10], s_newRYB [x_base], LEN_TERSE);
   }
   /*---(interpolate to 360)-------------*/
   x_base  = 2;
   x_index = 8 * 6;
   strlcpy (s_RYB [x_index][10], s_newRYB [x_base], LEN_TERSE);
   yCOLOR__interpolate ( 0,  8);
   /*---(interpolate to end)-------------*/
   x_base  = 7;
   x_index = 8 * 6;
   strlcpy (s_RYB [x_index][10], s_newRYB [x_base], LEN_TERSE);
   yCOLOR__interpolate ( 8, 11);
   /*---(complete)-----------------------*/
   return 0;
}



/*============================--------------------============================*/
/*===----                       color by degree                        ----===*/
/*============================--------------------============================*/
static void      o___BY_DEGREE_______________o (void) {;}

char         /*-> tbd --------------------------------[ leaf   [ge.750.232.C0]*/ /*-[01.0000.032.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_deg2index     (cint a_deg, int *a_index)
{  /*---(design notes)-------------------*/
   /*
    *  always returns a valid index, but sends a positive return code if it
    *  must adjust to obtain a valid degree.
    */
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   char        rc          =   0;
   int         x_index     =   0;
   int         x_deg       = a_deg;
   /*---(adjust)-------------------------*/
   if        (s_use == YCOLOR_WHEEL) {
      while (x_deg <    0)  { x_deg +=  360; rc = -rce; }
      while (x_deg >= 360)  { x_deg -=  360; rc = -rce; }
   } else if (s_use == YCOLOR_REDBLU) {
      if    (x_deg <    0)  { x_deg  =    0; rc = -rce; }
      if    (x_deg >  240)  { x_deg  =  240; rc = -rce; }
   } else if (s_use == YCOLOR_LARGE || s_use == YCOLOR_GIANT) {
      if    (x_deg < -120)  { x_deg  = -120; rc = -rce; }
      if    (x_deg >  480)  { x_deg  =  480; rc = -rce; }
      x_deg += 120;
   } else {
      x_deg = 0;
      rc = -rce;
   }
   /*---(calculate)----------------------*/
   x_index = x_deg / 10;
   if (s_use == YCOLOR_LARGE)  x_index /= 2;
   if (a_index)  *a_index = x_index;
   /*---(complete)-----------------------*/
   return rc;
}

char         /*-> use degree to set opengl color -----[ ------ [gc.320.221.01]*/ /*-[00.0000.303.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_deg2color     (cint a_deg, float a_alpha)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   int         x_index     =   0;
   /*---(parse color)--------------------*/
   rc = yCOLOR_deg2index (a_deg, &x_index);
   /*---(set color)----------------------*/
   glColor4f   (s_colors [x_index].red, s_colors [x_index].grn, s_colors [x_index].blu, a_alpha);
   /*---(complete)-----------------------*/
   return rc;
}

char         /*-> tbd --------------------------------[ ------ [gc.320.221.01]*/ /*-[00.0000.501.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_deg2hex       (cint a_deg, char *a_hex)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   int         x_index     =   0;
   /*---(parse color)--------------------*/
   rc = yCOLOR_deg2index (a_deg, &x_index);
   strlcpy (a_hex, s_colors [x_index].hex, LEN_TERSE);
   /*---(complete)-----------------------*/
   return rc;
}

char*        /*-> use degree to retrieve name --------[ ------ [gs.320.122.11]*/ /*-[00.0000.303.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_deg2name      (cint a_deg)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   int         x_index     =   0;
   /*---(parse color)--------------------*/
   rc = yCOLOR_deg2index (a_deg, &x_index);
   if (rc < 0)  return "";
   /*---(complete)-----------------------*/
   return s_colors [x_index].name;
}



/*============================--------------------============================*/
/*===----                        color by number                       ----===*/
/*============================--------------------============================*/
static void      o___BY_NUMBER_______________o (void) {;}

char         /*-> use color index to set opengl ------[ leaf   [gz.310.201.20]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_num2color     (cint a_num, cfloat a_alpha)
{
   /*---(locals)-------------------------*/
   int         x_num       = a_num;
   /*---(parse color)--------------------*/
   if (x_num <  0       )   x_num = 0;
   if (x_num >= s_ncolor)   x_num = s_ncolor - 1;
   /*---(set color)----------------------*/
   glColor4f   (s_colors [x_num].red, s_colors [x_num].grn, s_colors [x_num].blu, a_alpha);
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> use color index to retrieve hex ----[ leaf   [gz.310.201.30]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_num2hex       (cint a_num, char *a_hex)
{
   /*---(locals)-------------------------*/
   int         x_num       = a_num;
   /*---(parse color)--------------------*/
   if (x_num <  0       )   x_num = 0;
   if (x_num >= s_ncolor)   x_num = s_ncolor - 1;
   /*---(complete)-----------------------*/
   if (a_hex)  strlcpy (a_hex, s_colors [a_num].hex, LEN_TERSE);
   return 0;
}

char*        /*-> use color index to retrieve name ---[ leaf   [gs.210.101.20]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_num2name      (cint a_num)
{
   /*---(locals)-------------------------*/
   int         x_num       = a_num;
   /*---(parse color)--------------------*/
   if (x_num <  0       )   x_num = 0;
   if (x_num >= s_ncolor)   x_num = s_ncolor - 1;
   /*---(complete)-----------------------*/
   return s_colors [x_num].name;
}

float        /*-> use index to retrieve cutoff -------[ leaf   [gn.210.101.20]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_num2cutoff    (cint a_num)
{
   /*---(locals)-------------------------*/
   int         x_num       = a_num;
   /*---(parse color)--------------------*/
   if (x_num <  0       )   x_num = 0;
   if (x_num >= s_ncolor)   x_num = s_ncolor - 1;
   /*---(complete)-----------------------*/
   return s_colors [x_num].cut;
}



/*============================--------------------============================*/
/*===----                       color by value                         ----===*/
/*============================--------------------============================*/
static void      o___BY_VALUE________________o (void) {;}

char         /*-> use hex code to set opengl color ---[ leaf   [gz.210.101.00]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_val2error     (cfloat a_alpha)
{
   glColor4f (0.998, 0.059, 0.690, a_alpha);
   return 0;
}

char         /*-> use hex code to set opengl color ---[ leaf   [gz.430.221.40]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_val2color     (cdouble a_val, cfloat a_alpha)
{
   /*---(locals)-----------+-----------+-*/
   int         x_index     = -1;
   int         i           =  0;
   /*---(find color)---------------------*/
   for (i = 0; i < s_ncolor; ++i) {
      if (s_colors [i].cut <  0 && a_val >= s_colors [i].cut)  continue;
      if (s_colors [i].cut >= 0 && a_val >  s_colors [i].cut)  continue;
      x_index = i;
      break;
   }
   /*---(set color)----------------------*/
   if (x_index < 0)  glColor4f (0.998, 0.059, 0.690, a_alpha);
   else              glColor4f (s_colors [i].red, s_colors [i].grn, s_colors [i].blu, a_alpha);
   /*---(complete)-----------------------*/
   return 0;
}


/*============================--------------------============================*/
/*===----                             hsv                              ----===*/
/*============================--------------------============================*/
static void      o___BY_HSV__________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [gc.960.164.93]*/ /*-[01.0000.034.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_hex2hsv      (     /* PURPOSE = convert RGB hex into HSV            */
      cchar    *a_hex,            /* RBG 24-bit hex code            (#RRGGBB) */
      float    *a_hue,            /* hue color component              (0-359) */
      float    *a_sat,            /* saturation color component     (0.0-1.0) */
      float    *a_val)            /* value color component          (0.0-1.0) */
{
   /*---(locals)-----------+-----------+-*/
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   float       x_min       = 0.0;
   float       x_max       = 0.0;
   float       x_del       = 0.0;
   /*---(simple defense)-------------------*/
   if (strlen(a_hex) != 7)    return -2;
   ycolor_hex2rgb  (a_hex, &x_red, &x_grn, &x_blu);
   /*---(setup)----------------------------*/
   x_min   = yCOLOR__min3 (x_red, x_grn, x_blu);
   x_max   = yCOLOR__max3 (x_red, x_grn, x_blu);
   x_del   = x_max - x_min;
   /*---(value)----------------------------*/
   if (a_val)  *a_val = x_max;
   /*---(saturation)-----------------------*/
   if (x_max == 0.0) {
      *a_sat  = 0.0;
      *a_hue  = 0.0;
      return 0;
   }
   if (a_sat)  *a_sat = x_del / x_max;
   /*---(hue)------------------------------*/
   if      (x_del   == 0.0  )   *a_hue = 0.0;
   else if (x_red   == x_max)   *a_hue = 0.0 + (x_grn - x_blu) / x_del;
   else if (x_grn   == x_max)   *a_hue = 2.0 + (x_blu - x_red) / x_del;
   else                         *a_hue = 4.0 + (x_red - x_grn) / x_del;
   *a_hue *= 60;
   if (*a_hue < 0.0) *a_hue += 360.0;
   /*---(complete)-------------------------*/
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gc.AA0.192.91]*/ /*-[01.0000.034.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_hsv2hex    (           /* PURPOSE = convert HSV to RGB HEX              */
      char     *a_hex,            /* RGB 24-bit hex code            (#RRGGBB) */
      cfloat    a_hue,            /* hue color component              (0-359) */
      cfloat    a_sat,            /* saturation color component     (0.0-1.0) */
      cfloat    a_val)            /* value color component          (0.0-1.0) */
{
   /*---(locals)-------------------------*/
   float        x_hue       = a_hue;
   float        x_sat       = a_sat;
   float        x_val       = a_val;
   /*---(defense)------------------------*/
   while (x_hue <  0.0)     x_hue += 360.0;
   while (x_hue >= 360.0)   x_hue -= 360.0;
   if (x_sat < 0.0)         x_sat  = 0.0;
   if (x_sat > 1.0)         x_sat  = 1.0;
   if (x_val < 0.0)         x_val  = 0.0;
   if (x_val > 1.0)         x_val  = 1.0;
   /*---(locals)-------------------------*/
   int       i;
   float     h, f, p, q, t;
   float     x_red, x_grn, x_blu;
   /*---(check for grey)-----------------*/
   if (x_sat == 0) {
      x_red = x_grn = x_blu  = x_val;
   } else {
      /*---(prepare)---------------------*/
      h = x_hue / 60;           /* divide into six sectors (0 - 5)            */
      i = floor(h);             /* section number as integer                  */
      f = h - i;                /* fractional part of section number          */
      p = x_val * (1 - x_sat);
      q = x_val * (1 - x_sat * f);
      t = x_val * (1 - x_sat * (1 - f));
      /*---(assign color)----------------*/
      switch (i) {
      case 0:  x_red = x_val; x_grn = t;     x_blu = p;     break;
      case 1:  x_red = q;     x_grn = x_val; x_blu = p;     break;
      case 2:  x_red = p;     x_grn = x_val; x_blu = t;     break;
      case 3:  x_red = p;     x_grn = q;     x_blu = x_val; break;
      case 4:  x_red = t;     x_grn = p;     x_blu = x_val; break;
      default: x_red = x_val; x_grn = p;     x_blu = q;     break;
      }
   }
   ycolor_rgb2hex (a_hex, x_red, x_grn, x_blu);
   /*> /+---(truncate into 0-255)------------+/                                     <* 
    *> uchar u_red = x_red * 255;                                                     <* 
    *> uchar u_grn = x_grn * 255;                                                     <* 
    *> uchar u_blu = x_blu * 255;                                                     <* 
    *> /+---(place into RGB hex)-------------+/                                     <* 
    *> snprintf(a_hex, LEN_TERSE, "�%02x%02x%02x", u_red, u_grn, u_blu);                <*/
   /*---(complete)-----------------------*/
   return 0;
}


