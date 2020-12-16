/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



#define     MAX_DIFF    400
typedef     struct      cDIFF       tDIFF;
struct      cDIFF {
   float       red;
   float       grn;
   float       blu;
   float       bri;
   short       map;
};
static      tDIFF       s_diffs [MAX_DIFF];
static      int         s_adiff;       /* count of all colors                */
static      int         s_ndiff;       /* count of filtered colors           */

static      char        s_scheme   = YCOLOR_WHITE;
static      char        s_chaos    = '-';
static      float       s_cutoff   = 2.3;
static      int         s_curr     = 0;
static      int         s_start    = 0;
static      int         s_seed     = 1;


static char s_bases [MAX_DIFF][10] =
{  /* colors taken from Tatarize at "godsnotwheregodsnot.ru" */

   "#000000", "#FFFF00", "#1CE6FF", "#FF34FF", "#FF4A46", "#008941", "#006FA6", "#A30059",
   "#FFDBE5", "#7A4900", "#0000A6", "#63FFAC", "#B79762", "#004D43", "#8FB0FF", "#997D87",
   "#5A0007", "#809693", "#FEFFE6", "#1B4400", "#4FC601", "#3B5DFF", "#4A3B53", "#FF2F80",
   "#61615A", "#BA0900", "#6B7900", "#00C2A0", "#FFAA92", "#FF90C9", "#B903AA", "#D16100",
   "#DDEFFF", "#000035", "#7B4F4B", "#A1C299", "#300018", "#0AA6D8", "#013349", "#00846F",
   "#372101", "#FFB500", "#C2FFED", "#A079BF", "#CC0744", "#C0B9B2", "#C2FF99", "#001E09",
   "#00489C", "#6F0062", "#0CBD66", "#EEC3FF", "#456D75", "#B77B68", "#7A87A1", "#788D66",
   "#885578", "#FAD09F", "#FF8A9A", "#D157A0", "#BEC459", "#456648", "#0086ED", "#886F4C",

   "#34362D", "#B4A8BD", "#00A6AA", "#452C2C", "#636375", "#A3C8C9", "#FF913F", "#938A81",
   "#575329", "#00FECF", "#B05B6F", "#8CD0FF", "#3B9700", "#04F757", "#C8A1A1", "#1E6E00",
   "#7900D7", "#A77500", "#6367A9", "#A05837", "#6B002C", "#772600", "#D790FF", "#9B9700",
   "#549E79", "#FFF69F", "#201625", "#72418F", "#BC23FF", "#99ADC0", "#3A2465", "#922329",
   "#5B4534", "#FDE8DC", "#404E55", "#0089A3", "#CB7E98", "#A4E804", "#324E72", "#6A3A4C",
   "#83AB58", "#001C1E", "#D1F7CE", "#004B28", "#C8D0F6", "#A3A489", "#806C66", "#222800",
   "#BF5650", "#E83000", "#66796D", "#DA007C", "#FF1A59", "#8ADBB4", "#1E0200", "#5B4E51",
   "#C895C5", "#320033", "#FF6832", "#66E1D3", "#CFCDAC", "#D0AC94", "#7ED379", "#012C58",

   "#7A7BFF", "#D68E01", "#353339", "#78AFA1", "#FEB2C6", "#75797C", "#837393", "#943A4D",
   "#B5F4FF", "#D2DCD5", "#9556BD", "#6A714A", "#001325", "#02525F", "#0AA3F7", "#E98176",
   "#DBD5DD", "#5EBCD1", "#3D4F44", "#7E6405", "#02684E", "#962B75", "#8D8546", "#9695C5",
   "#E773CE", "#D86A78", "#3E89BE", "#CA834E", "#518A87", "#5B113C", "#55813B", "#E704C4",
   "#00005F", "#A97399", "#4B8160", "#59738A", "#FF5DA7", "#F7C9BF", "#643127", "#513A01",
   "#6B94AA", "#51A058", "#A45B02", "#1D1702", "#E20027", "#E7AB63", "#4C6001", "#9C6966",
   "#64547B", "#97979E", "#006A66", "#391406", "#F4D749", "#0045D2", "#006C31", "#DDB6D0",
   "#7C6571", "#9FB2A4", "#00D891", "#15A08A", "#BC65E9", "#FFFFFE", "#C6DC99", "#203B3C",

   "#671190", "#6B3A64", "#F5E1FF", "#FFA0F2", "#CCAA35", "#374527", "#8BB400", "#797868",
   "#C6005A", "#3B000A", "#C86240", "#29607C", "#402334", "#7D5A44", "#CCB87C", "#B88183",
   "#AA5199", "#B5D6C3", "#A38469", "#9F94F0", "#A74571", "#B894A6", "#71BB8C", "#00B433",
   "#789EC9", "#6D80BA", "#953F00", "#5EFF03", "#E4FFFC", "#1BE177", "#BCB1E5", "#76912F",
   "#003109", "#0060CD", "#D20096", "#895563", "#29201D", "#5B3213", "#A76F42", "#89412E",
   "#1A3A2A", "#494B5A", "#A88C85", "#F4ABAA", "#A3F3AB", "#00C6C8", "#EA8B66", "#958A9F",
   "#BDC9D2", "#9FA064", "#BE4700", "#658188", "#83A485", "#453C23", "#47675D", "#3A3F00",
   "#061203", "#DFFB71", "#868E7E", "#98D058", "#6C8F7D", "#D7BFC2", "#3C3E6E", "#D83D66",

   "#2F5D9B", "#6C5E46", "#D25B88", "#5B656C", "#00B57F", "#545C46", "#866097", "#365D25",
   "#252F99", "#00CCFF", "#674E60", "#FC009C", "#92896B", "-------", "-------", "-------",
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
};

static char s_monos [MAX_DIFF][10] =
{  /* shades of red (32)           */
   "#D83060", "#800020", "#403078", "#92000A", "#D86048", "#FF0038",
   "#D81878", "#BF0A30", "#A80000", "#CC3333", "#901818", "#FF2800",
   "#900000", "#FF0800", "#F00048", "#E30B5D", "#FF0000", "#A45A52",
   "#FF4860", "#B03060", "#C00000", "#5E1921", "#FF3030", "#CD5C5C",
   "#C03048", "#ED2939", "#C01800", "#7C0A02", "#FF0048", "#FF2400",
   "#FF3048", "#780018",
   /* shades of yellow (32)        */
   "#FFC048", "#FFD800", "#F0A830", "#A8FF48", "#D8F000", "#F8DE7E",
   "#FFD300", "#FAFAD2", "#D8F000", "#F8DE7E", "#FFD300", "#FAFAD2",
   "#FFDAB9", "#FFBD2E", "#EEDC82", "#FADFAD", "#FFDB58", "#FFDEAD",
   "#FFF44F", "#FFFDD0", "#CC7722", "#CBBD55", "#FFE135", "#EEE8AA",
   "#F0E68C", "#BDB76B", "#FFFF00", "#808000", "#ADFF2F", "#9ACD32",
   "#FFBF00", "#C09999",
   /* shades of green (32)         */
   "#A8D8A8", "#00A890", "#00F0A8", "#609060", "#D8F0C0", "#486060",
   "#007848", "#183030", "#609078", "#909078", "#609048", "#309030",
   "#00C0A8", "#48A890", "#90C0A8", "#487800", "#A8C090", "#186048",
   "#F0FFF0", "#30FF60", "#A8FFA8", "#00C000", "#487830", "#007878",
   "#A8FF48", "#48A860", "#30A860", "#C0C030", "#30C078", "#90C0C0",
   "#78D878", "#004830",
   /* shades of orange (32)        */
   "#F09030", "#FFC048", "#FF6030", "#FFA800", "#FF6000", "#FF4848",
   "#FF3030", "#FCD667", "#FDB064", "#F99245", "#CC5500", "#FFA500",
   "#CB7119", "#F4AE72", "#B06500", "#B29082", "#E89362", "#D8A175",
   "#877548", "#F2A337", "#FF7518", "#CC5500", "#CD7F32", "#996633",
   "#FBCEB1", "#FFBF00", "#F8BA37", "#E6292C", "#FF8066", "#D23B05",
   "#F7DCB4", "#985629",
   /* shades of blue (32)          */
   "#000090", "#4848D8", "#7878D8", "#60C0C0", "#489090", "#006060",
   "#1890F0", "#6078F0", "#90D8C0", "#A8D8F0", "#4890A8", "#D8F0FF",
   "#48A8A8", "#006090", "#00D8D8", "#6078D8", "#007890", "#78C0F0",
   "#6890D8", "#3048C0", "#486078", "#004860", "#0090A8", "#6060C0",
   "#1890A8", "#184878", "#1800C0", "#6048C0", "#003048", "#18A8D8",
   "#A8FFD8", "#004878",
   /* shades of brown (32)         */
   "#7F4737", "#8A3324", "#E97451", "#954535", "#EECEAC", "#CC7722",
   "#A89A8F", "#906E3E", "#800000", "#8B4513", "#D2691E", "#CD853F",
   "#DAA520", "#F4A460", "#BC8F8F", "#D2B48C", "#DEB887", "#F5DEB3",
   "#FFDEAD", "#FFE4C4", "#FFF8DC", "#452A19", "#996515", "#C19A6B",
   "#704214", "#75463A", "#59260B", "#BF914B", "#C19A6B", "#5D432C",
   "#674C47", "#4A2C2A", 
   /* shades of purple (32)        */
   "#A32CC4", "#7A4988", "#710393", "#630436", "#E39FF6", "#601A35",
   "#A1045A", "#B65FCF", "#663046", "#8E93D4", "#4D0F28", "#9078C0",
   "#311432", "#6030A8", "#67032F", "#9867C5", "#800080", "#9E7BB5",
   "#4B0082", "#A45EE5", "#183078", "#290916", "#AF69EF", "#4C0121",
   "#D89EA6", "#4B0082", "#8A2BE2", "#DA70D6", "#543948", "#FF1CAE",
   "#9932CC", "#8B008B",
   /* shades of grey (32)          */
   "#6D616F", "#D9DDDC", "#373737", "#828282", "#594D5B", "#D6CFC7", 
   "#322D31", "#787276", "#696860", "#999DA0", "#C5C6D0", "#88807B", 
   "#ADADC9", "#877F7D", "#59515E", "#BDB7AB", "#3E3D53", "#B9BBB6", 
   "#41424C", "#BEBDB8", "#564C4D", "#97978F", "#4D4C5C", "#C7C6C1", 
   "#7C6E7F", "#222021", "#655967", "#808588", "#7F7D9C", "#777B7E", 
   "#232023", "#544C4A",
   /* shades of pink (32)          */
   "#FFC0C0", "#FF1493", "#FF90D8", "#FFB6C1", "#F09090", "#DB7093",
   "#F0D808", "#C71585", "#FF90A8", "#FEC5E5", "#F078C0", "#FC94AF",
   "#FFD8F0", "#FAB6CA", "#FF7890", "#FCBACB", "#904860", "#9E4244",
   "#FF60A8", "#FD5DA8", "#C060A8", "#F26BBA", "#FFA878", "#F25278",
   "#FFF0D8", "#FDA4BA", "#F0C0A8", "#FF6090", "#A84860", "#D87878",
   "#783030", "#D8A8A8",
};



/*====================------------------------------------====================*/
/*===----                        overall program                       ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
ycolor__diff_purge   (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR  yLOG_senter  (__FUNCTION__);
   DEBUG_YCOLOR  yLOG_sint    (MAX_DIFF);
   /*---(default values)-----------------*/
   for (i = 0; i < MAX_DIFF; ++i) {
      s_diffs [i].red = -1.000;
      s_diffs [i].grn = -1.000;
      s_diffs [i].blu = -1.000;
      s_diffs [i].bri = -1.000;
      s_diffs [i].map = -1;
   }
   /*---(reset globals)------------------*/
   s_ndiff  = 0;
   s_adiff  = 0;
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR  yLOG_sexit   (__FUNCTION__);
   return 0;
}

static char  /*-> tbd --------------------------------[ leaf   [fz.320.001.00]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
ycolor__diff_reset   (void)
{
   s_scheme   = YCOLOR_WHITE;
   s_chaos    =  '-';
   s_cutoff   =  2.3;
   s_start    =  0;
   s_seed     =  1;
   s_curr     =  0;
   ycolor__diff_purge ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        general/support                       ----===*/
/*====================------------------------------------====================*/
static void      o___GENERAL_________________o (void) {;}

float        /*-> tbd --------------------------------[ leaf   [fn.430.221.80]*/ /*-[00.0000.01#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR__diff_unhex   (char a_one, char a_two)
{
   float       x_one       = 0.0;
   float       x_two       = 0.0;
   if      (a_one >= '0' && a_one <= '9')   x_one = a_one - '0';
   else if (a_one >= 'a' && a_one <= 'f')   x_one = a_one - 'a' + 10;
   else if (a_one >= 'A' && a_one <= 'F')   x_one = a_one - 'A' + 10;
   else                                     x_one = 0.0;
   if      (a_two >= '0' && a_two <= '9')   x_two = a_two - '0';
   else if (a_two >= 'a' && a_two <= 'f')   x_two = a_two - 'a' + 10;
   else if (a_two >= 'A' && a_two <= 'F')   x_two = a_two - 'A' + 10;
   else                                     x_two = 0.0;
   return ((x_one * 16.0) + x_two) / 255;
}



/*====================------------------------------------====================*/
/*===----                       filtering/selecting                    ----===*/
/*====================------------------------------------====================*/
static void      o___FILTERING_______________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [fz.B62.051.31]*/ /*-[02.0000.01#.!]-*/ /*-[--.---.---.--]-*/
ycolor__diff_filter  (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   float       x_bri       = 0.0;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR  yLOG_enter   (__FUNCTION__);
   DEBUG_YCOLOR  yLOG_note    ("set global values");
   /*---(establish values)---------------*/
   for (i = 0; i < MAX_DIFF; ++i) {
      /*---(filter)----------------------*/
      if (s_bases [i][0] == '-')  break;
      /*---(read scheme)-----------------*/
      x_red =  yCOLOR__diff_unhex (s_bases [i][1], s_bases [i][2]);
      x_grn =  yCOLOR__diff_unhex (s_bases [i][3], s_bases [i][4]);
      x_blu =  yCOLOR__diff_unhex (s_bases [i][5], s_bases [i][6]);
      x_bri =  x_red + x_grn + x_blu;
      ++s_adiff;
      /*---(filter)----------------------*/
      if (s_cutoff > 1.5 && x_bri > s_cutoff) {
         DEBUG_YCOLOR  yLOG_complex ("skipped"   , "%3d, red=%4.2f, grn=%4.2f, blu=%4.2f, bri=%4.2f", s_adiff, x_red, x_grn, x_blu, x_bri);
         /*> printf ("skipped1  %3d, red=%4.2f, grn=%4.2f, blu=%4.2f, bri=%4.2f\n", s_adiff, x_red, x_grn, x_blu, x_bri);   <*/
         continue;
      }
      if (s_cutoff <= 1.5 && x_bri < s_cutoff) {
         DEBUG_YCOLOR  yLOG_complex ("skipped"   , "%3d, red=%4.2f, grn=%4.2f, blu=%4.2f, bri=%4.2f", s_adiff, x_red, x_grn, x_blu, x_bri);
         /*> printf ("skipped2  %3d, red=%4.2f, grn=%4.2f, blu=%4.2f, bri=%4.2f\n", s_adiff, x_red, x_grn, x_blu, x_bri);   <*/
         continue;
      }
      /*---(save to palette)-------------*/
      s_diffs [s_ndiff].red = x_red;
      s_diffs [s_ndiff].grn = x_grn;
      s_diffs [s_ndiff].blu = x_blu;
      s_diffs [s_ndiff].bri = x_bri;
      s_diffs [s_ndiff].map = i;
      ++s_ndiff;
      DEBUG_YCOLOR  yLOG_complex ("saved"     , "%3d, red=%4.2f, grn=%4.2f, blu=%4.2f, bri=%4.2f, new=%3d", s_adiff, x_red, x_grn, x_blu, x_bri, s_ndiff);
      /*---(done)------------------------*/
   } 
   /*> printf ("s_adiff = %d\n", s_adiff);                                            <*/
   /*> printf ("s_ndiff = %d\n", s_ndiff);                                            <*/
   /*---(summary)------------------------*/
   DEBUG_YCOLOR  yLOG_value   ("s_adiff"   , s_adiff);
   DEBUG_YCOLOR  yLOG_value   ("s_ndiff"   , s_ndiff);
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        color setting                         ----===*/
/*====================------------------------------------====================*/
static void      o___SETTING_________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [gz.740.101.12]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_diff_scheme   (char a_scheme)
{
   /*---(clear out)----------------------*/
   ycolor__diff_reset  ();
   /*---(set scheme)---------------------*/
   switch (a_scheme) {
   case YCOLOR_BLACK :
      s_scheme  = YCOLOR_BLACK;
      s_cutoff  = 0.7;
      break;
   case YCOLOR_DARK  :
      s_scheme  = YCOLOR_DARK;
      s_cutoff  = 1.2;
      break;
   case YCOLOR_LIGHT :
      s_scheme  = YCOLOR_LIGHT;
      s_cutoff  = 1.7;
      break;
   case YCOLOR_MAX   :
      s_scheme  = YCOLOR_WHITE;
      s_cutoff  = 2.8;
      break;
   default          :
   case YCOLOR_WHITE :
      s_scheme  = YCOLOR_WHITE;
      s_cutoff  = 2.3;
      break;
   }
   /*---(filter)-------------------------*/
   ycolor__diff_filter ();
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [gz.210.101.00]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_diff_chaos    (int a_seed )
{
   s_chaos = 'y';
   s_seed  = a_seed;
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [gz.210.101.00]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_diff_start    (int a_start)
{
   s_start = a_start;
   s_curr  = a_start;
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [gz.210.201.00]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_diff_color    (int a_color, float a_alpha)
{
   char        rce         =  -10;
   --rce;  if (a_color >= s_ndiff) {
      DEBUG_YCOLOR  yLOG_complex ("diff_color", "%3d, no color set by that number", a_color);
      return rce;
   }
   glColor4f (s_diffs [a_color].red, s_diffs [a_color].grn, s_diffs [a_color].blu, a_alpha);
   DEBUG_YCOLOR  yLOG_complex ("diff_color", "%3d, %5.3fr, %5.3fg, %5.3fb", a_color, s_diffs [a_color].red, s_diffs [a_color].grn, s_diffs [a_color].blu);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [gz.210.201.20]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_diff_label    (int a_color, float a_alpha)
{
   if (s_diffs [a_color].bri < 1.5)
      glColor4f   (1.0f, 1.0f, 1.0f, a_alpha);
   else  
      glColor4f   (0.0f, 0.0f, 0.0f, a_alpha);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [gz.420.001.10]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_diff_fore   (void)
{
   switch (s_scheme) {
   case  'w' :
   case  'l' :
      glColor4f (0.0f, 0.0f, 0.0f, 1.0f);
      break;
   case  'd' :
   case  'b' :
      glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
      break;
   }
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [gz.430.001.10]*/ /*-[04.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_diff_back   (void)
{
   switch (s_scheme) {
   case  'w' : glClearColor  (1.0f, 1.0f, 1.0f, 1.0f);   /* white */
               glColor4f     (1.0f, 1.0f, 1.0f, 1.0f);   /* white */
               break;
   case  'l' : glClearColor  (0.6f, 0.6f, 0.6f, 1.0f);   /* light */
               glColor4f     (0.6f, 0.6f, 0.6f, 1.0f);   /* light */
               break;
   case  'd' : glClearColor  (0.2f, 0.2f, 0.2f, 1.0f);   /* dark  */
               glColor4f     (0.2f, 0.2f, 0.2f, 1.0f);   /* dark  */
               break;
   case  'b' : glClearColor  (0.0f, 0.0f, 0.0f, 1.0f);   /* black */
               glColor4f     (0.0f, 0.0f, 0.0f, 1.0f);   /* black */
               break;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        color cursor                          ----===*/
/*====================------------------------------------====================*/
static void      o___CURSOR__________________o (void) {;}

int          /*-> tbd --------------------------------[ leaf   [gn.210.001.00]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_diff_total    (void)
{
   return s_adiff;
}

int          /*-> tbd --------------------------------[ leaf   [gn.210.001.00]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_diff_count    (void)
{
   return s_ndiff;
}

int          /*-> tbd --------------------------------[ leaf   [gn.430.021.50]*/ /*-[02.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_diff_first    (void)
{
   s_curr = s_start;
   return yCOLOR_diff_next ();
}

int          /*-> tbd --------------------------------[ leaf   [gn.430.021.50]*/ /*-[02.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_diff_next     (void)
{
   int         x_color     = 0;
   int         i           = 0;
   if (s_chaos == 'y') {
      if (s_curr == s_start) {
         for (i = 0; i < s_start; ++i) x_color  = rand_r (&(s_seed)) % s_ndiff;
         ++s_curr;
      }
      x_color  = rand_r (&(s_seed)) % s_ndiff;
   } else {
      if (s_curr >= s_ndiff)  s_curr = 0;
      if (s_curr <  0)        s_curr = 0;
      x_color  = s_curr;
      ++s_curr;
   }
   return x_color;
}

char*
yCOLOR_diff_mapped      (int a_color)
{
   char        rce         =  -10;
   --rce;  if (a_color >= s_ndiff)  return "#------";
   return s_bases [s_diffs [a_color].map];
}




/*===============================[[ end-code ]]===============================*/
