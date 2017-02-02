/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"


float rgb_ryb[360];

/*====================------------------------------------====================*/
/*===----                     artists palette                          ----===*/
/*====================------------------------------------====================*/
static void      o___ARTISTS_________________o (void) {;}

static const char s_rybhex [360][10] =
{
   /* 000 */ "#ff0000", "#ff0700", "#ff0d00", "#ff1300", "#ff1800", "#ff1e00", "#ff2300", "#ff2800", "#ff2c00", "#ff3100",
   /* 010 */ "#ff3500", "#ff3900", "#ff3d00", "#ff4100", "#ff4500", "#ff4900", "#ff4c00", "#ff4f00", "#ff5300", "#ff5600",
   /* 020 */ "#ff5900", "#ff5c00", "#ff5f00", "#ff6200", "#ff6400", "#ff6700", "#ff6a00", "#ff6c00", "#ff6f00", "#ff7100",
   /* 030 */ "#ff7400", "#ff7600", "#ff7800", "#ff7a00", "#ff7c00", "#ff7f00", "#ff8100", "#ff8300", "#ff8500", "#ff8700",
   /* 040 */ "#ff8900", "#ff8b00", "#ff8c00", "#ff8e00", "#ff9000", "#ff9200", "#ff9400", "#ff9500", "#ff9700", "#ff9900",
   /* 050 */ "#ff9a00", "#ff9c00", "#ff9e00", "#ff9f00", "#ffa100", "#ffa200", "#ffa400", "#ffa500", "#ffa700", "#ffa900",
   /* 060 */ "#ffaa00", "#ffab00", "#ffad00", "#ffae00", "#ffb000", "#ffb100", "#ffb300", "#ffb400", "#ffb600", "#ffb700",
   /* 070 */ "#ffb800", "#ffba00", "#ffbb00", "#ffbc00", "#ffbe00", "#ffbf00", "#ffc000", "#ffc200", "#ffc300", "#ffc500",
   /* 080 */ "#ffc600", "#ffc700", "#ffc900", "#ffca00", "#ffcb00", "#ffcd00", "#ffce00", "#ffcf00", "#ffd100", "#ffd200",
   /* 090 */ "#ffd300", "#ffd500", "#ffd600", "#ffd700", "#ffd900", "#ffda00", "#ffdb00", "#ffdd00", "#ffde00", "#ffdf00",
   /* 100 */ "#ffe100", "#ffe200", "#ffe400", "#ffe500", "#ffe700", "#ffe800", "#ffe900", "#ffeb00", "#ffec00", "#ffee00",
   /* 110 */ "#ffef00", "#fff100", "#fff200", "#fff400", "#fff500", "#fff700", "#fff800", "#fffa00", "#fffc00", "#fffd00",
   /* 120 */ "#ffff00", "#fbfe00", "#f7fe00", "#f3fd00", "#f0fc00", "#ecfc00", "#e9fb00", "#e5fb00", "#e2fa00", "#dffa00",
   /* 130 */ "#dcf900", "#d8f800", "#d5f800", "#d2f700", "#cff700", "#ccf600", "#c9f600", "#c6f500", "#c3f500", "#c0f400",
   /* 140 */ "#bdf400", "#baf300", "#b7f200", "#b4f200", "#b1f100", "#aef100", "#abf000", "#a8f000", "#a5ef00", "#a2ef00",
   /* 150 */ "#9fee00", "#9bed00", "#98ed00", "#95ec00", "#92ec00", "#8eeb00", "#8bea00", "#87ea00", "#84e900", "#80e800",
   /* 160 */ "#7ce700", "#78e700", "#74e600", "#70e500", "#6be400", "#67e300", "#62e200", "#5de100", "#58e000", "#53df00",
   /* 170 */ "#4dde00", "#48dd00", "#41db00", "#38da00", "#34d800", "#2dd700", "#25d500", "#1dd300", "#14d100", "#0acf00",
   /* 180 */ "#00cc00", "#00c90d", "#00c618", "#00c322", "#00c12b", "#00bf32", "#00bd39", "#00bb3f", "#00b945", "#00b74a",
   /* 190 */ "#00b64f", "#00b454", "#00b358", "#00b25c", "#00b060", "#00af64", "#00ae68", "#00ac6b", "#00ab6f", "#00aa72",
   /* 200 */ "#00a876", "#00a779", "#00a67c", "#00a480", "#00a383", "#00a287", "#00a08a", "#009e8e", "#009d91", "#009b95",
   /* 210 */ "#009999", "#01939a", "#028e9b", "#03899c", "#04859d", "#04819e", "#057d9f", "#06799f", "#0776a0", "#0772a1",
   /* 220 */ "#086fa1", "#086ca2", "#0969a2", "#0a67a3", "#0a64a4", "#0b61a4", "#ob5fa5", "#0c5da5", "#0c5aa6", "#0d58a6",
   /* 230 */ "#0d56a6", "#0e53a7", "#0e51a7", "#0f4fa8", "#0f4da8", "#104ba9", "#1049a9", "#1047a9", "#1144aa", "#1142aa",
   /* 240 */ "#1240ab", "#123eab", "#133cac", "#133aac", "#1437ad", "#1435ad", "#1533ad", "#1531ae", "#162eae", "#172caf",
   /* 250 */ "#1729b0", "#1826b0", "#1924b1", "#1921b1", "#1a1eb2", "#1b1bb3", "#1d1ab2", "#1f1ab2", "#2219b2", "#2419b2",
   /* 260 */ "#2618b1", "#2818b1", "#2a17b1", "#2c17b1", "#2e16b1", "#3016b0", "#3216b0", "#3415b0", "#3515b0", "#3714b0",
   /* 270 */ "#3914af", "#3b14af", "#3c13af", "#3e13af", "#4013af", "#4212af", "#4312ae", "#4512ae", "#4711ae", "#4811ae",
   /* 280 */ "#4a11ae", "#4c10ae", "#4e10ae", "#4f10ad", "#510fad", "#530fad", "#540ead", "#560ead", "#580ead", "#5a0dac",
   /* 290 */ "#5c0dac", "#5e0dac", "#600cac", "#620cac", "#640cab", "#660bab", "#680bab", "#6a0aab", "#6c0aab", "#6f0aaa",
   /* 300 */ "#7109aa", "#7309aa", "#7608aa", "#7908aa", "#7c07a9", "#7e07a9", "#8106a9", "#8506a9", "#8805a8", "#8c04a8",
   /* 310 */ "#8f04a8", "#9303a7", "#9702a7", "#9c02a7", "#a101a6", "#a600a6", "#aa00a2", "#ad009f", "#b1009b", "#b40097",
   /* 320 */ "#b70094", "#b90091", "#bc008d", "#be008a", "#c10087", "#c30083", "#c50080", "#c7007d", "#c9007a", "#cb0077",
   /* 330 */ "#cd0074", "#ce0071", "#d0006e", "#d2006b", "#d30068", "#d50065", "#d60062", "#d8005f", "#d9005b", "#db0058",
   /* 340 */ "#dc0055", "#de0052", "#df004f", "#e1004c", "#e20048", "#e40045", "#e60042", "#e7003e", "#e9003a", "#ea0037",
   /* 350 */ "#ec0033", "#ed002f", "#ef002a", "#f10026", "#f30021", "#f5001d", "#f60018", "#f80012", "#fb000d", "#fd0006",
};



/*==========================---------------------=============================*/
/*===----                   conversion workhorses                      ----===*/
/*==========================---------------------=============================*/

char         /*--> convert ryb angle to rgb hex ----------[ ------ [ ------ ]-*/
yCOLOR_ryb_hex       (int a_deg, char *a_hex)
{
   /*---(adjust)-------------------------*/
   while (a_deg <  0.0)     a_deg += 360.0;
   while (a_deg >= 360.0)   a_deg -= 360.0;
   /*---(get hex)------------------------*/
   if (a_hex != NULL)   strlcpy (a_hex, s_rybhex  [a_deg], LEN_HEX);
   /*---(complete)-----------------------*/
   return 0;
}

int
yCOLOR__loadryb()
{
   tCOLOR *o    = yPALETTE__current();
   int i = 0;          /* loop index                  */
   /*---(initialize)-----------------------*/
   for (i = 0; i < 360; ++i) rgb_ryb[i] = 0.0;
   /*---(put in direct)--------------------*/
   char x_hex[10];
   for (i = 0; i < 360; ++i) {
      strncpy(x_hex, s_rybhex [i], 10);
      yCOLOR__hex(x_hex);
      rgb_ryb[i] = HUE;
   }
   /*---(complete)-------------------------*/
   return 0;
}




char       /*=((p_convert))===* return  = simple error code                   */
yPALETTE__hsv2hex(           /* PURPOSE = convert HSV to RGB HEX              */
      float     a_hue,            /* hue color component              (0-359) */
      float     a_sat,            /* saturation color component     (0.0-1.0) */
      float     a_val,            /* value color component          (0.0-1.0) */
      char     *a_hex)            /* RGB 24-bit hex code            (#RRGGBB) */
{
   /*---(defense)--------------------------*/
   while (a_hue <  0.0)     a_hue += 360.0;
   while (a_hue >= 360.0)   a_hue -= 360.0;
   if (a_sat < 0.0)         a_sat  = 0.0;
   if (a_sat > 1.0)         a_sat  = 1.0;
   if (a_val < 0.0)         a_val  = 0.0;
   if (a_val > 1.0)         a_val  = 1.0;
   /*---(locals)---------------------------*/
   int       i;
   float     h, f, p, q, t;
   float     x_red, x_grn, x_blu;
   /*---(check for grey)-------------------*/
   if (a_sat == 0) {
      x_red = x_grn = x_blu  = a_val;
   } else {
      /*---(prepare)-----------------------*/
      h = a_hue / 60;           /* divide into six sectors (0 - 5)            */
      i = floor(h);             /* section number as integer                  */
      f = h - i;                /* fractional part of section number          */
      p = a_val * (1 - a_sat);
      q = a_val * (1 - a_sat * f);
      t = a_val * (1 - a_sat * (1 - f));
      /*---(assign color)------------------*/
      switch (i) {
      case 0:  x_red = a_val; x_grn = t;     x_blu = p;     break;
      case 1:  x_red = q;     x_grn = a_val; x_blu = p;     break;
      case 2:  x_red = p;     x_grn = a_val; x_blu = t;     break;
      case 3:  x_red = p;     x_grn = q;     x_blu = a_val; break;
      case 4:  x_red = t;     x_grn = p;     x_blu = a_val; break;
      default: x_red = a_val; x_grn = p;     x_blu = q;     break;
      }
   }
   /*---(truncate into 0-255)--------------*/
   uchar u_red = x_red * 255;
   uchar u_grn = x_grn * 255;
   uchar u_blu = x_blu * 255;
   /*---(place into RGB hex)---------------*/
   snprintf(a_hex, HEXMAX, "#%02x%02x%02x", u_red, u_grn, u_blu);
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yPALETTE__hex2hsv(           /* PURPOSE = convert RGB hex into HSV            */
      char     *a_hex,            /* RBG 24-bit hex code            (#RRGGBB) */
      float    *a_hue,            /* hue color component              (0-359) */
      float    *a_sat,            /* saturation color component     (0.0-1.0) */
      float    *a_val)            /* value color component          (0.0-1.0) */
{
   /*---(simple defense)-------------------*/
   if (strlen(a_hex) != 7)    return -2;
   /*---(regex defense)--------------------*/
   int         x_rc = 0;
   regex_t     x_comp;
   x_rc = regcomp(&x_comp, "^#[0-9a-fA-F]{6}$", REG_EXTENDED);
   if (x_rc != 0)               return -3;
   x_rc = regexec(&x_comp, a_hex, 0, NULL, 0);
   if (x_rc != 0)               return -4;
   regfree(&x_comp);
   /*---(convert)--------------------------*/
   char  x_hex[HEXMAX] = "0x";
   long  x_rgb     = 0;
   strncat(x_hex, a_hex + 1, HEXMAX);
   sscanf(x_hex, "%lx", &x_rgb);
   /*---(create RGB components)------------*/
   float  x_red = (x_rgb / (256 * 256)) / 256.0;
   float  x_grn = ((x_rgb / 256) % 256) / 256.0;
   float  x_blu = (x_rgb % 256)         / 256.0;
   /*---(setup)----------------------------*/
   float  x_min   = yCOLOR__min3(x_red, x_grn, x_blu);
   float  x_max   = yCOLOR__max3(x_red, x_grn, x_blu);
   float  x_del   = x_max - x_min;
   /*---(value)----------------------------*/
   *a_val = x_max;
   /*---(saturation)-----------------------*/
   if (x_max == 0.0) {
      *a_sat  = 0.0;
      *a_hue  = 0.0;
      return 0;
   }
   *a_sat = x_del / x_max;
   if (x_del == 0.0) {
      *a_hue = 0.0;
      return 0;
   }
   /*---(hue)------------------------------*/
   if      (x_red   == x_max)   *a_hue = 0.0 + (x_grn - x_blu) / x_del;
   else if (x_grn   == x_max)   *a_hue = 2.0 + (x_blu - x_red) / x_del;
   else                         *a_hue = 4.0 + (x_red - x_grn) / x_del;
   *a_hue *= 60;
   if (*a_hue < 0.0) *a_hue += 360.0;
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yPALETTE__hex2byte(          /* PURPOSE = convert RGB hex into RGB bytes      */
      char     *a_hex,            /* RBG 24-bit hex code            (#RRGGBB) */
      uchar    *a_red,            /* red byte                         (0-255) */
      uchar    *a_grn,            /* green byte                       (0-255) */
      uchar    *a_blu)            /* blue byte                        (0-255) */
{
   /*---(simple defense)-------------------*/
   if (strlen(a_hex) != 7)    return -2;
   /*---(regex defense)--------------------*/
   int         x_rc = 0;
   regex_t     x_comp;
   x_rc = regcomp(&x_comp, "^#[0-9a-fA-F]{6}$", REG_EXTENDED);
   if (x_rc != 0)               return -3;
   x_rc = regexec(&x_comp, a_hex, 0, NULL, 0);
   if (x_rc != 0)               return -4;
   regfree(&x_comp);
   /*---(convert)--------------------------*/
   char  x_hex[HEXMAX] = "0x";
   long  x_rgb     = 0;
   strncat(x_hex, a_hex + 1, HEXMAX);
   sscanf(x_hex, "%lx", &x_rgb);
   /*---(create RGB components)------------*/
   *a_red = (x_rgb / (256 * 256));
   *a_grn = ((x_rgb / 256) % 256);
   *a_blu = (x_rgb % 256);
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yPALETTE__hex2norm(          /* PURPOSE = convert RGB hex into RGB normals    */
      char     *a_hex,            /* RBG 24-bit hex code            (#RRGGBB) */
      float    *a_red,            /* red byte                         (0-255) */
      float    *a_grn,            /* green byte                       (0-255) */
      float    *a_blu)            /* blue byte                        (0-255) */
{
   /*---(simple defense)-------------------*/
   if (strlen(a_hex) != 7)    return -2;
   /*---(regex defense)--------------------*/
   int         x_rc = 0;
   regex_t     x_comp;
   x_rc = regcomp(&x_comp, "^#[0-9a-fA-F]{6}$", REG_EXTENDED);
   if (x_rc != 0)               return -3;
   x_rc = regexec(&x_comp, a_hex, 0, NULL, 0);
   if (x_rc != 0)               return -4;
   regfree(&x_comp);
   /*---(convert)--------------------------*/
   char  x_hex[HEXMAX] = "0x";
   long  x_rgb     = 0;
   strncat(x_hex, a_hex + 1, HEXMAX);
   sscanf(x_hex, "%lx", &x_rgb);
   /*---(create RGB components)------------*/
   *a_red = (x_rgb / (256 * 256)) / 256.0;
   *a_grn = ((x_rgb / 256) % 256) / 256.0;
   *a_blu = (x_rgb % 256)         / 256.0;
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yPALETTE__byte2hex(          /* PURPOSE = convert RGB bytes into RGB hex      */
      uchar     a_red,            /* red byte                         (0-255) */
      uchar     a_grn,            /* green byte                       (0-255) */
      uchar     a_blu,            /* blue byte                        (0-255) */
      char     *a_hex)            /* RGB 24-bit true color hex      (#RRGGBB) */
{
   /*---(place into RGB hex)---------------*/
   snprintf(a_hex, HEXMAX, "#%02x%02x%02x", a_red, a_grn, a_blu);
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yPALETTE__norm2hex(          /* PURPOSE = convert RGB components into RGB hex */
      float     a_red,            /* red color component            (0.0-1.0) */
      float     a_grn,            /* green color component          (0.0-1.0) */
      float     a_blu,            /* blue color component           (0.0-1.0) */
      char     *a_hex)            /* RGB 24-bit true color hex      (#RRGGBB) */
{
   /*---(defense)--------------------------*/
   if (a_red < 0.0)         a_red  = 0.0;
   if (a_red > 1.0)         a_red  = 1.0;
   if (a_grn < 0.0)         a_grn  = 0.0;
   if (a_grn > 1.0)         a_grn  = 1.0;
   if (a_blu < 0.0)         a_blu  = 0.0;
   if (a_blu > 1.0)         a_blu  = 1.0;
   /*---(truncate into 0-255)--------------*/
   uchar u_red = a_red * 255.0;
   uchar u_grn = a_grn * 255.0;
   uchar u_blu = a_blu * 255.0;
   /*---(place into RGB hex)---------------*/
   snprintf(a_hex, HEXMAX, "#%02x%02x%02x", u_red, u_grn, u_blu);
   /*---(complete)-------------------------*/
   return 0;
}





char       /*=((p_convert))===* return  = simple error code                   */
yPALETTE__hsv2int(             /* PURPOSE = convert HSV to RGB int              */
      float     a_hue,            /* hue color component              (0-359) */
      float     a_sat,            /* saturation color component     (0.0-1.0) */
      float     a_val,            /* value color component          (0.0-1.0) */
      long     *a_rgb)            /* RGB 24-bit true color             (long) */
{
   /*---(defense)--------------------------*/
   while (a_hue <  0.0)     a_hue += 360.0;
   while (a_hue >= 360.0)   a_hue -= 360.0;
   if (a_sat < 0.0)         a_sat  = 0.0;
   if (a_sat > 1.0)         a_sat  = 1.0;
   if (a_val < 0.0)         a_val  = 0.0;
   if (a_val > 1.0)         a_val  = 1.0;
   /*---(locals)---------------------------*/
   int       i;
   double    h, f, p, q, t;
   double    x_red, x_grn, x_blu;
   /*---(check for grey)-------------------*/
   if (a_sat == 0) {
      x_red = x_grn = x_blu  = a_val;
   } else {
      /*---(prepare)-----------------------*/
      h = a_hue / 60;           /* divide into six sectors (0 - 5)            */
      i = floor(h);             /* section number as integer                  */
      f = h - i;                /* fractional part of section number          */
      p = a_val * (1 - a_sat);
      q = a_val * (1 - a_sat * f);
      t = a_val * (1 - a_sat * (1 - f));
      /*---(assign color)------------------*/
      switch (i) {
      case 0:  x_red = a_val; x_grn = t;     x_blu = p;     break;
      case 1:  x_red = q;     x_grn = a_val; x_blu = p;     break;
      case 2:  x_red = p;     x_grn = a_val; x_blu = t;     break;
      case 3:  x_red = p;     x_grn = q;     x_blu = a_val; break;
      case 4:  x_red = t;     x_grn = p;     x_blu = a_val; break;
      default: x_red = a_val; x_grn = p;     x_blu = q;     break;
      }
   }
   /*---(place into RGB int)---------------*/
   uchar u_red = x_red * 255;
   uchar u_grn = x_grn * 255;
   uchar u_blu = x_blu * 255;
   x_red = u_red * 0x010000;
   x_grn = u_grn * 0x000100;
   x_blu = u_blu * 0x000001;
   *a_rgb = x_red + x_grn + x_blu;
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR__rgb2int(             /* PURPOSE = convert RGB components into RGB int */
      float     a_red,            /* red color component            (0.0-1.0) */
      float     a_grn,            /* green color component          (0.0-1.0) */
      float     a_blu,            /* blue color component           (0.0-1.0) */
      long     *a_rgb)            /* RGB 24-bit true color             (long) */
{
   /*---(defense)--------------------------*/
   if (a_red < 0.0)         a_red  = 0.0;
   if (a_red > 1.0)         a_red  = 1.0;
   if (a_grn < 0.0)         a_grn  = 0.0;
   if (a_grn > 1.0)         a_grn  = 1.0;
   if (a_blu < 0.0)         a_blu  = 0.0;
   if (a_blu > 1.0)         a_blu  = 1.0;
   /*---(place into RGB int)---------------*/
   int x_red, x_grn, x_blu;                /* must move to int's */
   x_red = round(a_red * 255) * 0x010000;
   x_grn = round(a_grn * 255) * 0x000100;
   x_blu = round(a_blu * 255) * 0x000001;
   /*> printf("original :: red = %4.2f, grn = %4.2f blu = %4.2f\n", a_red, a_grn, a_blu);   <* 
    *> printf("nex      :: red = %4.4d, grn = %4.4d blu = %4.4d\n", x_red, x_grn, x_blu);   <*/
   *a_rgb = x_red + x_grn + x_blu;
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR__chr2int(             /* PURPOSE = convert RGB bytes into RGB int      */
      uchar     a_red,            /* red color component            (0 - 255) */
      uchar     a_grn,            /* green color component          (0 - 255) */
      uchar     a_blu,            /* blue color component           (0 - 255) */
      long     *a_rgb)            /* RGB 24-bit true color             (long) */
{
   /*---(defense)--------------------------*/
   /* not necessary as the "uchar" data type takes care of that ;) */
   /*---(place into RGB int)---------------*/
   int x_red, x_grn, x_blu;                /* must move to int's */
   x_red = a_red * 0x010000;
   x_grn = a_grn * 0x000100;
   x_blu = a_blu * 0x000001;
   *a_rgb = x_red + x_grn + x_blu;
   /*---(complete)-------------------------*/
   return 0;
}




char       /*=((p_convert))===* return  = simple error code                   */
yPALETTE__hex2int(           /* PURPOSE = convert RGB hex into RGB int        */
      char     *a_hex,            /* RGB hex code for return        (#RRGGBB) */
      long     *a_rgb)            /* RBG 24-bit true color             (long) */
{
   /*---(simple defense)-------------------*/
   if (strlen(a_hex) != 7)    return -2;
   /*---(regex defense)--------------------*/
   int         x_rc = 0;
   regex_t     x_comp;
   x_rc = regcomp(&x_comp, "^#[0-9a-fA-F]{6}$", REG_EXTENDED);
   if (x_rc != 0)               return -3;
   x_rc = regexec(&x_comp, a_hex, 0, NULL, 0);
   if (x_rc != 0)               return -4;
   regfree(&x_comp);
   /*---(convert)--------------------------*/
   char  x_hex[10] = "0x";
   strncat(x_hex, a_hex + 1, 10);
   sscanf(x_hex, "%lx", a_rgb);
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yPALETTE__int2hex(             /* PURPOSE = convert RGB int into RGB hex        */
      long      a_rgb,            /* RBG 24-bit true color             (long) */
      char     *a_hex)            /* RGB hex code                   (#RRGGBB) */
{
   /*---(defensive)------------------------*/
   if (a_rgb < 0)                    return -1;
   if (a_rgb > (256 * 256 * 256))    return -2;
   /*---(convert)--------------------------*/
   snprintf(a_hex, HEXMAX, "#%06x", (unsigned int) a_rgb);
   /*---(complete)-------------------------*/
   return  0;
}




char       /*=((p_convert))===* return  = simple error code                   */
yPALETTE__int2hsv(             /* PURPOSE = convert RGB int into HSV            */
      long      a_rgb,            /* RBG 24-bit true color             (long) */
      float    *a_hue,            /* hue color component              (0-359) */
      float    *a_sat,            /* saturation color component     (0.0-1.0) */
      float    *a_val)            /* value color component          (0.0-1.0) */
{
   /*---(defensive)------------------------*/
   if (a_rgb < 0)                    return -1;
   if (a_rgb > (256 * 256 * 256))    return -2;
   /*---(create RGB components)------------*/
   float  x_red = (a_rgb / (256 * 256)) / 256.0;
   float  x_grn = ((a_rgb / 256) % 256) / 256.0;
   float  x_blu = (a_rgb % 256)         / 256.0;
   printf("red = %f, grn = %f, blu = %f\n", x_red, x_grn, x_blu);
   /*---(setup)----------------------------*/
   float  x_min   = yCOLOR__min3(x_red, x_grn, x_blu);
   float  x_max   = yCOLOR__max3(x_red, x_grn, x_blu);
   float  x_del   = x_max - x_min;
   printf("min = %f, max = %f, del = %f\n", x_min, x_max, x_del);
   /*---(value)----------------------------*/
   *a_val = x_max;
   /*---(saturation)-----------------------*/
   if (x_max == 0.0) {
      *a_sat  = 0.0;
      *a_hue  = 0.0;
      return 0;
   }
   *a_sat = x_del / x_max;
   if (x_del == 0.0) {
      *a_hue = 0.0;
      return 0;
   }
   /*---(hue)------------------------------*/
   if      (x_red   == x_max)   *a_hue = 0.0 + (x_grn - x_blu) / x_del;
   else if (x_grn   == x_max)   *a_hue = 2.0 + (x_blu - x_red) / x_del;
   else                         *a_hue = 4.0 + (x_red - x_grn) / x_del;
   *a_hue *= 60;
   if (*a_hue < 0.0) *a_hue += 360.0;
   /*---(complete)-------------------------*/
   printf("hue = %f, sat = %f, val = %f\n", *a_hue, *a_sat, *a_val);
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR__int2rgb(             /* PURPOSE = convert RGB int to RGB components   */
      long      a_rgb,            /* RGB 24-bit true color             (long) */
      float    *a_red,            /* red color component            (0.0-1.0) */
      float    *a_grn,            /* green color component          (0.0-1.0) */
      float    *a_blu)            /* blue color component           (0.0-1.0) */
{
   /*---(defensive)------------------------*/
   if (a_rgb < 0)                    return -1;
   if (a_rgb > (256 * 256 * 256))    return -2;
   /*---(place into RGB int)---------------*/
   *a_red = (float) (a_rgb / (256 * 256))  / 256.0;
   *a_grn = (float) ((a_rgb / 256) % 256)  / 256.0;
   *a_blu = (float) (a_rgb % 256)          / 256.0;
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR__int2chr(             /* PURPOSE = convert RGB int to RGB bytes        */
      long      a_rgb,            /* RGB 24-bit true color             (long) */
      uchar    *a_red,            /* red color byte                 (0 - 255) */
      uchar    *a_grn,            /* green color byte               (0 - 255) */
      uchar    *a_blu)            /* blue color byte                (0 - 255) */
{
   /*---(defensive)------------------------*/
   if (a_rgb < 0)                    return -1;
   if (a_rgb > (256 * 256 * 256))    return -2;
   /*---(place into RGB int)---------------*/
   *a_red = a_rgb / (256 * 256);
   *a_grn = (a_rgb / 256) % 256;
   *a_blu = a_rgb % 256;
   /*---(complete)-------------------------*/
   return 0;
}




uchar R_BYTE   (char *a_hex) { long x_rgb; yPALETTE__hex2int(a_hex, &x_rgb); return (uchar) (x_rgb / (256 * 256)); }
uchar G_BYTE   (char *a_hex) { long x_rgb; yPALETTE__hex2int(a_hex, &x_rgb); return (uchar) ((x_rgb / 256) % 256); }
uchar B_BYTE   (char *a_hex) { long x_rgb; yPALETTE__hex2int(a_hex, &x_rgb); return (uchar) (x_rgb % 256); }

float R_FLOAT  (long a_rgb) { return (float) (a_rgb / (256 * 256)) / 256.0; }
float G_FLOAT  (long a_rgb) { return (float) ((a_rgb / 256) % 256) / 256.0; }
float B_FLOAT  (long a_rgb) { return (float) (a_rgb % 256) / 256.0; }




char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR__int2mother(          /* PURPOSE = dominant to mother color            */
      long      a_rgb,            /* RGB 24-bit true color             (long) */
      long     *a_mother)         /* RGB 24-bit true color             (long) */
{
   /*---(defensive)------------------------*/
   if (a_rgb < 0)                    return -1;
   if (a_rgb > (256 * 256 * 256))    return -2;
   /*---(place into RGB int)---------------*/
   /*> *a_red = a_rgb / (256 * 256);                                                  <* 
    *> *a_grn = (a_rgb / 256) % 256;                                                  <* 
    *> *a_blu = a_rgb % 256;                                                          <*/
   /*---(complete)-------------------------*/
   return 0;
}



/*> int                                                                               <* 
 *> yCOLOR__hsv2rgb_NEWER(                                                            <* 
 *>       void *a_color)                                                              <* 
 *> {                                                                                 <* 
 *>    /+---(check for null/default)-----------+/                                     <* 
 *>    if (a_color == NULL) a_color = yPALETTE__current();                              <* 
 *>    if (a_color == NULL) return -1;                                                <* 
 *>    /+---(cast the color)-------------------+/                                     <* 
 *>    tCOLOR *o  = (tCOLOR *) a_color;                                               <* 
 *>    /+---(call converter)-------------------+/                                     <* 
 *>    yCOLOR__HSV2RGB(HUE, SAT, VAL, &RED, &GRN, &BLU);                              <* 
 *>    yCOLOR__RGB2BYTE(RED, GRN, BLU, &RED_BYTE, &GRN_BYTE, &BLU_BYTE);              <* 
 *>    yCOLOR__BYTE2HEX(RED_BYTE, GRN_BYTE, BLU_BYTE, &HEX);                          <* 
 *>    /+---(complete)-------------------------+/                                     <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char       /+=[[ CONVERT ]]===* return  = simple error code                   +/   <* 
 *> yCOLOR__HSV2HEX(             /+ PURPOSE = convert HSV to RGB hex code         +/   <* 
 *>       double    a_hue,            /+ hue color component              (0-359) +/   <* 
 *>       double    a_sat,            /+ saturation color component     (0.0-1.0) +/   <* 
 *>       double    a_val,            /+ value color component          (0.0-1.0) +/   <* 
 *>       char     *a_hex)            /+ RGB hex code for return        (#RRGGBB) +/   <* 
 *> {                                                                                  <* 
 *>    double x_red, x_grn, x_blu;                                                     <* 
 *>    yCOLOR__HSV2RGB(a_hue, a_sat, a_val, &x_red, &x_grn, &x_blu);                   <* 
 *>    yCOLOR__RGB2HEX(x_red, x_grn, x_blu, a_hex);                                    <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

/*> char                                                                               <* 
 *> yCOLOR__HEX2RGB(                                                                   <* 
 *>       char     *a_hex,            /+ RGB hex code for return        (#RRGGBB) +/   <* 
 *>       uchar    &a_red,            /+ red component byte               (0-255) +/   <* 
 *>       uchar    &a_grn,            /+ green component byte             (0-255) +/   <* 
 *>       uchar    &a_blu)            /+ blue component byte              (0-255) +/   <* 
 *> {                                                                                  <* 
 *>    /+---(simple defense)-------------------+/                                      <* 
 *>    if (strlen(a_hex) != 7)    return -2;                                           <* 
 *>    /+---(regex defense)--------------------+/                                      <* 
 *>    int         x_rc = 0;                                                           <* 
 *>    regex_t     x_comp;                                                             <* 
 *>    x_rc = regcomp(&x_comp, "^#[0-9a-fA-F]{6}$", REG_EXTENDED);                     <* 
 *>    if (x_rc != 0)               return -3;                                         <* 
 *>    x_rc = regexec(&x_comp, a_hex, 0, NULL, 0);                                     <* 
 *>    if (x_rc != 0)               return -4;                                         <* 
 *>    regfree(&x_comp);                                                               <* 
 *>    /+---(parse color bytes)----------------+/                                      <* 
 *>    a_red  = (yCOLOR__dehex(a_hex[1]) * 16) + yCOLOR__dehex(a_hex[2]);              <* 
 *>    a_grn  = (yCOLOR__dehex(a_hex[3]) * 16) + yCOLOR__dehex(a_hex[4]);              <* 
 *>    a_blu  = (yCOLOR__dehex(a_hex[5]) * 16) + yCOLOR__dehex(a_hex[6]);              <* 
 *> }                                                                                  <*/

int
yCOLOR__hsv2rgb(void *a_color)
{
   /*---(check for null/default)-----------*/
   if (a_color == NULL) a_color = yPALETTE__current();
   if (a_color == NULL) return -1;
   /*---(cast the color)-------------------*/
   tCOLOR *o  = (tCOLOR *) a_color;
   /*---(setup)----------------------------*/
   int    i;
   double h, f, p, q, t;
   /*---(check for grey)-------------------*/
   if (SAT == 0) {
      RED = GRN = BLU  = VAL;
   } else {
      /*---(prepare)--------------------------*/
      h = HUE / 60;                /* divide into six sectors (0 - 5)            */
      i = floor(h);                /* section number as integer                  */
      f = h - i;                   /* fractional part of section number          */
      p = VAL * (1 - SAT);
      q = VAL * (1 - SAT * f);
      t = VAL * (1 - SAT * (1 - f));
      switch (i) {
      case 0:  RED = VAL; GRN = t;   BLU = p;   break;
      case 1:  RED = q  ; GRN = VAL; BLU = p;   break;
      case 2:  RED = p  ; GRN = VAL; BLU = t;   break;
      case 3:  RED = p  ; GRN = q;   BLU = VAL; break;
      case 4:  RED = t  ; GRN = p;   BLU = VAL; break;
      default: RED = VAL; GRN = p;   BLU = q;   break;
      }
   }
   /*---(final conversions)----------------*/
   RED_BYTE = RED * 255.0;
   GRN_BYTE = GRN * 255.0;
   BLU_BYTE = BLU * 255.0;
   snprintf(HEX, HEXMAX, "#%02x%02x%02x", RED_BYTE, GRN_BYTE, BLU_BYTE);
   /*---(complete)-------------------------*/
   return 0;
}

int
yCOLOR__rgb2hsv(void *a_color)
{
   /*---(check for null/default)-----------*/
   if (a_color == NULL) a_color = yPALETTE__current();
   if (a_color == NULL) return -1;
   /*---(cast the color)-------------------*/
   tCOLOR *o  = (tCOLOR *) a_color;
   /*---(setup)----------------------------*/
   double x_min   = yCOLOR__min3(RED, GRN, BLU);
   double x_max   = yCOLOR__max3(RED, GRN, BLU);
   double x_del   = x_max - x_min;
   /*---(value)----------------------------*/
   VAL = x_max;
   /*---(saturation)-----------------------*/
   if (x_max == 0.0) {
      SAT = 0.0;
      HUE = 0.0;
      return 0;
   }
   SAT = x_del / x_max;
   if (x_del == 0.0) {
      HUE = 0.0;
      return 0;
   }
   /*---(hue)------------------------------*/
   if      (RED   == x_max)   HUE = 0.0 + (GRN - BLU) / x_del;
   else if (GRN   == x_max)   HUE = 2.0 + (BLU - RED) / x_del;
   else                       HUE = 4.0 + (RED - GRN) / x_del;
   HUE *= 60;
   if (HUE < 0.0) HUE += 360.0;
   /*---(complete)-------------------------*/
   return 0;
}

int
yCOLOR__hsv2hsl(void *a_color)
{
   /*---(check for null/default)-----------*/
   if (a_color == NULL) a_color = yPALETTE__current();
   if (a_color == NULL) return -1;
   /*---(cast the color)-------------------*/
   tCOLOR *o  = (tCOLOR *) a_color;
   /*---(convert)--------------------------*/
   HSL_HUE  = HUE;                            /* hue means the same              */
   HSL_LIG  = (2.0 - SAT) * VAL;
   HSL_SAT  = SAT * VAL;
   HSL_SAT /= (HSL_LIG <= 1.0) ? HSL_LIG : 2.0 - HSL_LIG;
   HSL_LIG /= 2.0;
   /*---(complete)-------------------------*/
   return 0;
}

int
yCOLOR__hsl2hsv(void *a_color)
{
   /*---(check for null/default)-----------*/
   if (a_color == NULL) a_color = yPALETTE__current();
   if (a_color == NULL) return -1;
   /*---(cast the color)-------------------*/
   tCOLOR *o  = (tCOLOR *) a_color;
   double  ll = HSL_LIG;
   double  ss = HSL_SAT;
   /*---(convert)--------------------------*/
   HUE   = HSL_HUE;                           /* hue means the same              */
   ll   *= 2.0;
   ss   *= (ll <= 1) ? ll : 2.0 - ll;
   VAL   = (ll + ss) / 2.0;
   SAT   = (2.0 * ss) / (ll + ss);
   /*---(complete)-------------------------*/
   return 0;
}

int                /*  return  = error code                                   */
yCOLOR__rgb2ryb(   /*  PURPOSE = turn rgb colors into artistic ryb ones       */
      void *a_color)              /*  color object                            */
{
   /*> printf("running ryb2rgb...\n");                                                <*/
   /*---(check for null/default)-----------*/
   if (a_color == NULL) a_color = yPALETTE__current();
   if (a_color == NULL) return -1;
   /*---(cast the color)-------------------*/
   tCOLOR *o  = (tCOLOR *) a_color;
   /*---(isolate/remove white)------------------*/
   double  w      = yCOLOR__min3(RED, GRN, BLU);
   double  r      = RED - w;
   double  g      = GRN - w;
   double  b      = BLU - w;
   /*---(get the max)---------------------------*/
   double  x_max1 = yCOLOR__max3(r, g, b);
   /*---(get yellow out of red/green)-----------*/
   double  y      = yCOLOR__min3(r, g, 10000);
   r  -= y;
   g  -= y;
   /*---(handle both blue and green)------------*/
   if (BLU > 0.0 && GRN > 0.0) {
      b  /= 2.0;
      g  /= 2.0;
   }
   /*---(redistribute remaining green)----------*/
   y  += g;
   b  += g;
   /*---(normalize)-----------------------------*/
   double  x_max2 = yCOLOR__max3(r, y, b);
   if (x_max2 > 0.0) {
      double n = x_max1 / x_max2;
      r  *= n;
      y  *= n;
      b  *= n;
   }
   /*--(add back in white)----------------------*/
   r  += w;
   y  += w;
   b  += w;
   /*---(save)----------------------------------*/
   o->rr = r;
   o->yy = y;
   o->bb = b;
   /*---(now convert hue separately)-------*/
   int       i=0;    /* loop interator       */
   int       x_hue  = round(HUE);
   /*> printf("HUE = %5d\n", x_hue);                                                  <*/
   float     x_low  = 0.0;
   float     x_high = 0.0;
   if (x_hue != 0) {
      for (i = 1; i < 360; ++i) {
         x_hue  = round(rgb_ryb[i]);
         if (x_hue > HUE) {
            x_hue  = i;
            x_low  = fabs(HUE - rgb_ryb[i - 1]);
            x_high = fabs(rgb_ryb[i] - HUE);
            if (x_low < x_high) x_hue  = i - 1;
            /*> printf("found = %5d at %5d\n", x_hue, i);                             <*/
            break;
         }
      }
   }
   /*> printf("HUE AFTER = %5d\n", x_hue);                                            <*/
   o->ryb_hh = x_hue;
   /*---(complete)------------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR__int2grey(            /* PURPOSE = generate equivalent greyscale color */
      long      a_rgb,            /* RGB 24-bit true color             (long) */
      long     *a_grey)           /* RGB 24-bit true color greyscale   (long) */
{
   /*---(design notes)--------------------------------------------------------*
    *   followed general, simple rule which weigths the three color components
    *   based on their brightness, rather than a simple average.
    */
   /*---(calc)-----------------------------*/
   long    x_grey;
   /*> x_grey   = (R_BYTE(a_rgb) * 0.30) + (G_BYTE(a_rgb) * 0.59) + (B_BYTE(a_rgb) * 0.11);   <*/
   *a_grey  = (x_grey * 0x010000) + (x_grey * 0x000100) + (x_grey);
   return 0;
}

int                /*  return  = error code                                   */
yCOLOR__greyscale(           /* PURPOSE = generate equivalent greyscale color */
      void *a_color)              /*  color object                            */
{
   /*---(design notes)--------------------------------------------------------*
    *   followed general, simple rule which weigths the three color components
    *   based on their brightness, rather than a simple average.
    */
   /*---(check for null/default)-----------*/
   if (a_color == NULL) a_color = yPALETTE__current();
   if (a_color == NULL) return -1;
   /*---(cast the color)-------------------*/
   tCOLOR *o  = (tCOLOR *) a_color;
   /*---(calc)-----------------------------*/
   /*> int x_avg = (RED_BYTE * 0.30) + (GRN_BYTE * 0.59) + (BLU_BYTE * 0.11);         <*/
   /*> printf("grey=%3d, red=%3d, grn=%3d, blu=%3d\n",                                <* 
    *>      x_avg, RED_BYTE, GRN_BYTE, BLU_BYTE);                                     <*/
   /*> snprintf(o->grey, 10, "#%02x%02x%02x", x_avg, x_avg, x_avg);                   <*/
   /*---(complete)-------------------------*/
   return 0;
}

int                /*  return  = error code                                   */
yCOLOR__websafe(             /* PURPOSE = generate equivalent websafe color   */
      void *a_color)              /*  color object                            */
{
   /*---(design notes)--------------------------------------------------------*
    *   followed general, websafe is six variations in the three primaries
    *   meaning hex codes 00, 33, 66, 99, CC, and FF which totals 216 colors
    */
   /*---(check for null/default)-----------*/
   if (a_color == NULL) a_color = yPALETTE__current();
   if (a_color == NULL) return -1;
   /*---(cast the color)-------------------*/
   tCOLOR *o  = (tCOLOR *) a_color;
   /*---(calc)-----------------------------*/
   uchar x_red = yCOLOR__webhex(RED_BYTE);
   uchar x_grn = yCOLOR__webhex(GRN_BYTE);
   uchar x_blu = yCOLOR__webhex(BLU_BYTE);
   /*> printf("red=%3d, grn=%3d, blu=%3d\n",                                          <* 
    *>       x_red, x_grn, x_blu);                                                    <*/
   snprintf(o->web, 10, "#%02x%02x%02x", x_red, x_grn, x_blu);
   /*---(complete)-------------------------*/
   return 0;
}

int                /*  return  = error code                                   */
yCOLOR__css(                 /* PURPOSE = generate equivalent css hex color   */
      void *a_color)              /*  color object                            */
{
   /*---(design notes)--------------------------------------------------------*
    *   followed general guide of css is 0-f for each of RGB vs 00-ff        
    */
   /*---(check for null/default)-----------*/
   if (a_color == NULL) a_color = yPALETTE__current();
   if (a_color == NULL) return -1;
   /*---(cast the color)-------------------*/
   tCOLOR *o  = (tCOLOR *) a_color;
   /*---(calc)-----------------------------*/
   uchar x_red = yCOLOR__csshex(RED_BYTE);
   uchar x_grn = yCOLOR__csshex(GRN_BYTE);
   uchar x_blu = yCOLOR__csshex(BLU_BYTE);
   /*> printf("red=%3d, grn=%3d, blu=%3d\n",                                          <* 
    *>       x_red, x_grn, x_blu);                                                    <*/
   snprintf(o->css, 5, "%x%x%x", x_red, x_grn, x_blu);
   /*---(complete)-------------------------*/
   return 0;
}




/*==========================---------------------=============================*/
/*===----                      utility routines                        ----===*/
/*==========================---------------------=============================*/

double
yCOLOR__min3(double a_one, double a_two, double a_three)
{
   if (a_one <= a_two) {
      if (a_one <= a_three) return a_one;
      return a_three;
   } else {
      if (a_two <= a_three) return a_two;
      return a_three;
   }
   return a_two;
}

double
yCOLOR__max3(double a_one, double a_two, double a_three)
{
   if (a_one >= a_two) {
      if (a_one >= a_three) return a_one;
      return a_three;
   } else {
      if (a_two >= a_three) return a_two;
      return a_three;
   }
   return a_two;
}

int
yCOLOR__dehex(char a_ch)
{
   int x_int = 0;
   if (a_ch >= '0' && a_ch <= '9') {
      x_int = a_ch - '0';
   } else if  (a_ch >= 'a' && a_ch <= 'f') {
      x_int = a_ch - 'a' + 10;
   } else if  (a_ch >= 'A' && a_ch <= 'F') {
      x_int = a_ch - 'A' + 10;
   }
   return x_int;
}

uchar
yCOLOR__webhex(uchar a_value)
{
   /*  0---1---2---3---4---5---6---7---8---9---a---b---c---d---e---f       */
   /*  *           *           *           *           *           *       */
   /*        |           |           |           |           |             */
   float x_factor = 255.0 / 10.0;
   int   x_value  = (int) (a_value / x_factor);
   /*> printf("webhex :: %d = %d\n", a_value, x_value);                               <*/
   switch (x_value) {
   case   0 : x_value = 0x00; break;
   case   1 :
   case   2 : x_value = 0x33; break;
   case   3 :
   case   4 : x_value = 0x66; break;
   case   5 :
   case   6 : x_value = 0x99; break;
   case   7 :
   case   8 : x_value = 0xcc; break;
   case   9 :
   case  10 : x_value = 0xff; break;
   default  : x_value = 0xbb; break;
   }
   /*> printf("          %02x\n", x_value);                                           <*/
   /*> uchar x_hex = ((int) (a_hex / 42.5)) * 3;                                      <*/
   /*> x_hex = (x_hex * 16) + x_hex;                                                  <*/
   return x_value;
}

uchar
yCOLOR__csshex(uchar a_value)
{
   /*  0---1---2---3---4---5---6---7---8---9---a---b---c---d---e---f       */
   /*  *           *           *           *           *           *       */
   /*        |           |           |           |           |             */
   int   x_major  = trunc(a_value / 16);
   int   x_minor  = ((int) a_value) % 16;
   /*> printf("major = %x, minor = %x\n", x_major, x_minor);                          <*/
   if (x_major == 15) return 0xf;
   if (x_minor >= 8)  return x_major + 1;
   return x_major;
}

int
yCOLOR__rybindex(int a_index)
{
   if (a_index >= 0 && a_index < 360)
      return rgb_ryb[a_index];
   else
      return -1;
}


/*----------------------------------------------------------------------------*/
/*--------------------------------end-of-file---------------------------------*/
/*----------------------------------------------------------------------------*/
