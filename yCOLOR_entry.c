/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"




#define  HEXMAX     8




/*==========================---------------------=============================*/
/*===----            change dominant color (convienence)               ----===*/
/*==========================---------------------=============================*/
/* NOTES...
 *    - these functions do no real conversions or work
 *    - they are only here to provide additional flexibility
 */

char       /*=((p_simplify))==* return  = simple error code                   */
yPALETTE_artist(             /* PURPOSE = set color from RYB wheel angle      */
      int       a_angle,          /* angle on ryb wheel               (0-359) */
      char     *a_variation,      /* color variation                     (xx) */
      char     *a_norming)        /* color norming                       (xx) */
{
   /*---(palette defense)------------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   /*---(clear out the palette)------------*/
   char x_rc = 0;
   if (x_rc == 0) x_rc = yPALETTE_clear();
   /*---(update the settings)--------------*/
   if (x_rc == 0) x_rc = yPALETTE__ryb(a_angle);
   if (x_rc == 0) strncpy(BASE,     DOMINANT_HEX, HEXMAX);
   if (x_rc == 0) x_rc = yPALETTE__variant_set(a_variation, &VARIANT_ID);
   if (x_rc == 0) x_rc = yPALETTE__variant_make(VARIANT_ID, BASE,    VARIANT);
   if (x_rc == 0) x_rc = yPALETTE__norming_set(a_norming  , &NORMING_ID);
   if (x_rc == 0) x_rc = yPALETTE__norming_make(NORMING_ID, VARIANT, NORMED);
   /*---(default due to being dominant)----*/
   if (x_rc == 0) strncpy(MOTHER  , NORMED,       HEXMAX);
   if (x_rc == 0) strncpy(MOTHERED, NORMED,       HEXMAX);
   if (x_rc == 0) strncpy(MIXED   , NORMED,       HEXMAX);
   /*---(default current)------------------*/
   if (x_rc == 0) POSITION = 0;
   if (x_rc == 0) ACCENT   = 0;
   if (x_rc == 0) ANGLE    = DOMINANT_HUE;
   /*---(complete)-------------------------*/
   return x_rc;
}

char       /*=((p_simplify))==* return  = simple error code                   */
yPALETTE__ryb(               /* PURPOSE = set color from RYB wheel angle      */
      int       a_angle)          /* angle on ryb wheel               (0-359) */
{
   /*---(check/fix angle)------------------*/
   while (a_angle < 0)    a_angle += 360;
   while (a_angle >= 360) a_angle -= 360;
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   /*---(convert to RGB hex)---------------*/
   char   x_rc = 0;                          /* generic return code           */
   if (x_rc == 0) x_rc = yPALETTE__ryb2hex(a_angle, DOMINANT_HEX);
   if (x_rc == 0) DOMINANT_HUE = a_angle;
   /*---(complete)-------------------------*/
   return x_rc;
}




/*==========================---------------------=============================*/
/*===----               change dominant color (primary)                ----===*/
/*==========================---------------------=============================*/
/* NOTES...
 *    - these are still just shells, but the set the dominant colors
 */

char       /*=((p_change))====* return  = simple error code                   */
yCOLOR_hex(                  /* PURPOSE = set color using RGB hex code        */
      char     *a_hex)            /* rgb three byte hex code        (#rrggbb) */
{
   char x_rc = yCOLOR__hex(a_hex);
   if (x_rc == 0) yCOLOR__dominant();
   return x_rc;
}

char       /*=((p_change))====* return  = simple error code                   */
yCOLOR_rgb(                  /* PURPOSE = update color from RGB components    */
      uchar     a_red,            /* red component byte               (0-255) */
      uchar     a_grn,            /* green component byte             (0-255) */
      uchar     a_blu)            /* blue component byte              (0-255) */
{
   char x_rc = yCOLOR__rgb(a_red, a_grn, a_blu);
   if (x_rc == 0) yCOLOR__dominant();
   return x_rc;
}

char       /*=((p_change))====* return  = simple error ocde                   */
yCOLOR_hsv(                  /* PURPOSE = update color from HSV components    */
      double    a_hue,            /* hue color component              (0-359) */
      double    a_sat,            /* saturation color component     (0.0-1.0) */
      double    a_val)            /* value color component          (0.0-1.0) */
{
   char x_rc = yCOLOR__hsv(a_hue, a_sat, a_val);
   if (x_rc == 0) yCOLOR__dominant();
   return x_rc;
}

char       /*=((p_change))====* return  = simple error code                   */
yCOLOR_hsl(                  /* PURPOSE = update color from a HSL components  */
      double    a_hue,            /* hue color component              (0-359) */
      double    a_sat,            /* saturation color component     (0.0-1.0) */
      double    a_lig)            /* light color component          (0.0-1.0) */
{
   char x_rc = yCOLOR__hsl(a_hue, a_sat, a_lig);
   if (x_rc == 0) yCOLOR__dominant();
   return x_rc;
}

char
yCOLOR__dominant()
{
   char x_rc = 0;
   tCOLOR *o  = yPALETTE__current();
   strncpy(CURRENT , HEX, HEXMAX);
   /*> yPALETTE__hsv2int(HUE, SAT, VAL, DOMINANT_HEX);                                    <*/
   /*> o->base  = DOMINANT_HEX;                                                <*/
   /*> printf("new dominant is %ld\n", DOMINANT_HEX);                              <*/
   o->is_ryb  = 0;     /* means RGB        */
   /*> x_rc = yCOLOR__mother();                                                       <*/
   return x_rc;
}

/*> char                                                                                        <* 
 *> yCOLOR__mother()                                                                            <* 
 *> {                                                                                           <* 
 *>    return 0;                                                                                <* 
 *>    char x_rc = 0;                                                                           <* 
 *>    tCOLOR *o  = yPALETTE__current();                                                        <* 
 *>    /+> char x_hex[HEXMAX] = "";                                                       <+/   <* 
 *>    /+> strncpy(x_hex, HEX, HEXMAX);                                                   <+/   <* 
 *>    /+> yCOLOR__hex(DOMINANT_HEX);                                                         <+/   <* 
 *>    /+> x_rc = yCOLOR__variation();                                                    <+/   <* 
 *>    /+> if (x_rc == 0) strncpy(MOTHER  , HEX, HEXMAX);                                 <+/   <* 
 *>    /+> yCOLOR__hex(x_hex);                                                            <+/   <* 
 *>    /+> yCOLOR__hex(CURRENT);                                                          <+/   <* 
 *>    return x_rc;                                                                             <* 
 *> }                                                                                           <*/

char       /*=((p_set))=======* return  = simple error code                   */
yCOLOR_scheme(               /* PURPOSE = set color scheme option             */
      char   *a_scheme)           /* scheme name abbreviation                 */
{
   /*---(palette defense)------------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   /*---(argument defense)-----------------*/
   SCHEME_ID = 0;
   CIRCLE = 'n';
   if (strlen(a_scheme) < 3)     return -2;
   if (strlen(a_scheme) > 5)     return -3;
   /*---(local variables)------------------*/
   char      x_abbr[10] = "";              /* scheme abbreviation             */
   int       x_scheme = 0;                 /* scheme index (default = 0)      */
   int       i = 0;                        /* loop counter                    */
   /*---(find scheme)----------------------*/
   if (strlen(a_scheme) >= 3) {
      /*---(load the abbr)-----------------*/
      x_abbr[0] = a_scheme[0];
      x_abbr[1] = a_scheme[1];
      x_abbr[2] = a_scheme[2];
      x_abbr[3] = '\0';
      /*---(cycle table)-------------------*/
      for (i = 0; i < TABLEMAX; ++i) {
         if (strcmp(table_scheme[i].abbr, "eoi")  == 0) break;
         if (strcmp(table_scheme[i].abbr, x_abbr) == 0) x_scheme = i;
      }
   }
   /*---(load information)-----------------*/
   SCHEME_ID = x_scheme;
   CIRCLE = table_scheme[x_scheme].circle;
   /*---(look for complement)--------------*/
   yCOLOR__complement(a_scheme);
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=[[ SET ]]=======* return  = simple error code                   */
yCOLOR__complement(          /* PURPOSE = set color complement option         */
      char   *a_scheme)           /* complement name abbreviation             */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)          return -1;
   /*---(local variables)------------------*/
   char      x_abbr[10] = "";              /* scheme abbreviation             */
   int       x_comp = 0;                   /* complement index (default = 0)  */
   int       i = 0;                        /* loop counter                    */
   /*---(find complement)------------------*/
   if (strlen(a_scheme) == 5) {
      x_abbr[0] = a_scheme[3];
      x_abbr[1] = a_scheme[4];
      x_abbr[2] = '\0';
      for (i = 0; i < TABLEMAX; ++i) {
         if (strcmp(table_comp[i].abbr, "eoi")  == 0) break;
         if (strcmp(table_comp[i].abbr, x_abbr) == 0) x_comp = i;
      }
   }
   /*---(load information)-----------------*/
   COMP   = x_comp;
   /*---(complete)-------------------------*/
   return 0;
}


/*==========================---------------------=============================*/
/*===----                    change current color                      ----===*/
/*==========================---------------------=============================*/
void o___DRIVERS__________x() {}

char       /*=((p_change))====* return  = simple error code                   */
yCOLOR__hex(                 /* PURPOSE = set color using RGB hex code        */
      char     *a_hex)            /* rgb three byte hex code        (#rrggbb) */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)          return -1;
   /*---(simple defense)-------------------*/
   if (strlen(a_hex) != 7)    return -2;
   /*---(regex defense)--------------------*/
   int         rc = 0;
   regex_t     x_comp;
   rc = regcomp(&x_comp, "^#[0-9a-fA-F]{6}$", REG_EXTENDED);
   if (rc != 0)               return -3;
   rc = regexec(&x_comp, a_hex, 0, NULL, 0);
   if (rc != 0)               return -4;
   regfree(&x_comp);
   /*---(parse color bytes)----------------*/
   uchar x_red  = (yCOLOR__dehex(a_hex[1]) * 16) + yCOLOR__dehex(a_hex[2]);
   uchar x_grn  = (yCOLOR__dehex(a_hex[3]) * 16) + yCOLOR__dehex(a_hex[4]);
   uchar x_blu  = (yCOLOR__dehex(a_hex[5]) * 16) + yCOLOR__dehex(a_hex[6]);
   yCOLOR__rgb(x_red, x_grn, x_blu);
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_change))====* return  = simple error code                   */
yCOLOR__chr(                 /* PURPOSE = update color from RGB bytes         */
      uchar     a_red,            /* red component byte               (0-255) */
      uchar     a_grn,            /* green component byte             (0-255) */
      uchar     a_blu)            /* blue component byte              (0-255) */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)          return -1;
   /*---(initialize r, g, b)---------------*/
   RED_BYTE  = a_red;
   GRN_BYTE  = a_grn;
   BLU_BYTE  = a_blu;
   /*---(calc percentages)-----------------*/
   RED       = (double) RED_BYTE / 255;
   GRN       = (double) GRN_BYTE / 255;
   BLU       = (double) BLU_BYTE / 255;
   /*---(set hex)--------------------------*/
   snprintf(HEX, HEXMAX, "#%02x%02x%02x", RED_BYTE, GRN_BYTE, BLU_BYTE);
   /*---(conversions)----------------------*/
   yCOLOR__rgb2hsv(o);
   yCOLOR__hsv2hsl(o);
   yCOLOR__rgb2ryb(o);
   yCOLOR__greyscale(o);
   yCOLOR__websafe(o);
   yCOLOR__css(o);
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_change))====* return  = simple error code                   */
yCOLOR__rgb(                 /* PURPOSE = update color from RGB components    */
      uchar     a_red,            /* red component byte               (0-255) */
      uchar     a_grn,            /* green component byte             (0-255) */
      uchar     a_blu)            /* blue component byte              (0-255) */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)          return -1;
   /*---(initialize r, g, b)---------------*/
   RED_BYTE  = a_red;
   GRN_BYTE  = a_grn;
   BLU_BYTE  = a_blu;
   /*---(calc percentages)-----------------*/
   RED       = (double) RED_BYTE / 255;
   GRN       = (double) GRN_BYTE / 255;
   BLU       = (double) BLU_BYTE / 255;
   /*---(set hex)--------------------------*/
   snprintf(HEX, HEXMAX, "#%02x%02x%02x", RED_BYTE, GRN_BYTE, BLU_BYTE);
   /*---(conversions)----------------------*/
   yCOLOR__rgb2hsv(o);
   yCOLOR__hsv2hsl(o);
   yCOLOR__rgb2ryb(o);
   yCOLOR__greyscale(o);
   yCOLOR__websafe(o);
   yCOLOR__css(o);
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_change))====* return  = simple error ocde                   */
yCOLOR__hsv(                 /* PURPOSE = update color from HSV components    */
      double    a_hue,            /* hue color component              (0-359) */
      double    a_sat,            /* saturation color component     (0.0-1.0) */
      double    a_val)            /* value color component          (0.0-1.0) */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)          return -1;
   /*---(defense)--------------------------*/
   while (a_hue <  0.0)     a_hue += 360.0;
   while (a_hue >= 360.0)   a_hue -= 360.0;
   if (a_sat < 0.0)         a_sat  = 0.0;
   if (a_sat > 1.0)         a_sat  = 1.0;
   if (a_val < 0.0)         a_val  = 0.0;
   if (a_val > 1.0)         a_val  = 1.0;
   /*---(initialize hsv values)------------*/
   HUE  = a_hue;
   SAT  = a_sat;
   VAL  = a_val;
   /*---(NEW CONVERSIONS)------------------*/
   /*> yPALETTE__hsv2int  (a_hue, a_sat, a_val, DOMINANT_HEX);                      <* 
    *> yCOLOR__int2grey (DOMINANT_HEX,     &o->its_grey);                          <* 
    *> char x_hex[HEXMAX];                                                            <* 
    *> yPALETTE__int2hex(o->its_grey, x_hex);                                           <* 
    *> printf("greyscale is %ld == %s\n", o->its_grey, x_hex);                        <*/
   /*---(conversions)----------------------*/
   yCOLOR__hsv2rgb(o);
   yCOLOR__hsv2hsl(o);
   yCOLOR__rgb2ryb(o);
   yCOLOR__greyscale(o);
   yCOLOR__websafe(o);
   yCOLOR__css(o);
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_change))====* return  = simple error code                   */
yCOLOR__hsl(                 /* PURPOSE = update color from a HSL components  */
      double    a_hue,            /* hue color component              (0-359) */
      double    a_sat,            /* saturation color component     (0.0-1.0) */
      double    a_lig)            /* light color component          (0.0-1.0) */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)          return -1;
   /*---(defense)--------------------------*/
   while (a_hue <  0.0)     a_hue += 360.0;
   while (a_hue >= 360.0)   a_hue -= 360.0;
   if (a_sat < 0.0)         a_sat  = 0.0;
   if (a_sat > 1.0)         a_sat  = 1.0;
   if (a_lig < 0.0)         a_lig  = 0.0;
   if (a_lig > 1.0)         a_lig  = 1.0;
   /*---(initialize r, g, b)---------------*/
   HSL_HUE = a_hue;
   HSL_SAT = a_sat;
   HSL_LIG = a_lig;
   /*---(conversions)----------------------*/
   yCOLOR__hsl2hsv(o);
   yCOLOR__hsv2rgb(o);
   yCOLOR__rgb2ryb(o);
   yCOLOR__greyscale(o);
   yCOLOR__websafe(o);
   yCOLOR__css(o);
   /*---(complete)-------------------------*/
   return 0;
}


/*================================ end-of-file ===============================*/
