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
{  /* 250+ colors taken from Tatarize at "godsnotwheregodsnot.ru" */

   "õ000000", "õFFFF00", "õ1CE6FF", "õFF34FF", "õFF4A46", "õ008941", "õ006FA6", "õA30059",
   "õFFDBE5", "õ7A4900", "õ0000A6", "õ63FFAC", "õB79762", "õ004D43", "õ8FB0FF", "õ997D87",
   "õ5A0007", "õ809693", "õFEFFE6", "õ1B4400", "õ4FC601", "õ3B5DFF", "õ4A3B53", "õFF2F80",
   "õ61615A", "õBA0900", "õ6B7900", "õ00C2A0", "õFFAA92", "õFF90C9", "õB903AA", "õD16100",
   "õDDEFFF", "õ000035", "õ7B4F4B", "õA1C299", "õ300018", "õ0AA6D8", "õ013349", "õ00846F",
   "õ372101", "õFFB500", "õC2FFED", "õA079BF", "õCC0744", "õC0B9B2", "õC2FF99", "õ001E09",
   "õ00489C", "õ6F0062", "õ0CBD66", "õEEC3FF", "õ456D75", "õB77B68", "õ7A87A1", "õ788D66",
   "õ885578", "õFAD09F", "õFF8A9A", "õD157A0", "õBEC459", "õ456648", "õ0086ED", "õ886F4C",

   "õ34362D", "õB4A8BD", "õ00A6AA", "õ452C2C", "õ636375", "õA3C8C9", "õFF913F", "õ938A81",
   "õ575329", "õ00FECF", "õB05B6F", "õ8CD0FF", "õ3B9700", "õ04F757", "õC8A1A1", "õ1E6E00",
   "õ7900D7", "õA77500", "õ6367A9", "õA05837", "õ6B002C", "õ772600", "õD790FF", "õ9B9700",
   "õ549E79", "õFFF69F", "õ201625", "õ72418F", "õBC23FF", "õ99ADC0", "õ3A2465", "õ922329",
   "õ5B4534", "õFDE8DC", "õ404E55", "õ0089A3", "õCB7E98", "õA4E804", "õ324E72", "õ6A3A4C",
   "õ83AB58", "õ001C1E", "õD1F7CE", "õ004B28", "õC8D0F6", "õA3A489", "õ806C66", "õ222800",
   "õBF5650", "õE83000", "õ66796D", "õDA007C", "õFF1A59", "õ8ADBB4", "õ1E0200", "õ5B4E51",
   "õC895C5", "õ320033", "õFF6832", "õ66E1D3", "õCFCDAC", "õD0AC94", "õ7ED379", "õ012C58",

   "õ7A7BFF", "õD68E01", "õ353339", "õ78AFA1", "õFEB2C6", "õ75797C", "õ837393", "õ943A4D",
   "õB5F4FF", "õD2DCD5", "õ9556BD", "õ6A714A", "õ001325", "õ02525F", "õ0AA3F7", "õE98176",
   "õDBD5DD", "õ5EBCD1", "õ3D4F44", "õ7E6405", "õ02684E", "õ962B75", "õ8D8546", "õ9695C5",
   "õE773CE", "õD86A78", "õ3E89BE", "õCA834E", "õ518A87", "õ5B113C", "õ55813B", "õE704C4",
   "õ00005F", "õA97399", "õ4B8160", "õ59738A", "õFF5DA7", "õF7C9BF", "õ643127", "õ513A01",
   "õ6B94AA", "õ51A058", "õA45B02", "õ1D1702", "õE20027", "õE7AB63", "õ4C6001", "õ9C6966",
   "õ64547B", "õ97979E", "õ006A66", "õ391406", "õF4D749", "õ0045D2", "õ006C31", "õDDB6D0",
   "õ7C6571", "õ9FB2A4", "õ00D891", "õ15A08A", "õBC65E9", "õFFFFFE", "õC6DC99", "õ203B3C",

   "õ671190", "õ6B3A64", "õF5E1FF", "õFFA0F2", "õCCAA35", "õ374527", "õ8BB400", "õ797868",
   "õC6005A", "õ3B000A", "õC86240", "õ29607C", "õ402334", "õ7D5A44", "õCCB87C", "õB88183",
   "õAA5199", "õB5D6C3", "õA38469", "õ9F94F0", "õA74571", "õB894A6", "õ71BB8C", "õ00B433",
   "õ789EC9", "õ6D80BA", "õ953F00", "õ5EFF03", "õE4FFFC", "õ1BE177", "õBCB1E5", "õ76912F",
   "õ003109", "õ0060CD", "õD20096", "õ895563", "õ29201D", "õ5B3213", "õA76F42", "õ89412E",
   "õ1A3A2A", "õ494B5A", "õA88C85", "õF4ABAA", "õA3F3AB", "õ00C6C8", "õEA8B66", "õ958A9F",
   "õBDC9D2", "õ9FA064", "õBE4700", "õ658188", "õ83A485", "õ453C23", "õ47675D", "õ3A3F00",
   "õ061203", "õDFFB71", "õ868E7E", "õ98D058", "õ6C8F7D", "õD7BFC2", "õ3C3E6E", "õD83D66",

   "õ2F5D9B", "õ6C5E46", "õD25B88", "õ5B656C", "õ00B57F", "õ545C46", "õ866097", "õ365D25",
   "õ252F99", "õ00CCFF", "õ674E60", "õFC009C", "õ92896B", "-------", "-------", "-------",
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
};

static char s_monos [MAX_DIFF][10] =
{  /* shades of red (32)           */
   "õD83060", "õ800020", "õ403078", "õ92000A", "õD86048", "õFF0038",
   "õD81878", "õBF0A30", "õA80000", "õCC3333", "õ901818", "õFF2800",
   "õ900000", "õFF0800", "õF00048", "õE30B5D", "õFF0000", "õA45A52",
   "õFF4860", "õB03060", "õC00000", "õ5E1921", "õFF3030", "õCD5C5C",
   "õC03048", "õED2939", "õC01800", "õ7C0A02", "õFF0048", "õFF2400",
   "õFF3048", "õ780018",
   /* shades of yellow (32)        */
   "õFFC048", "õFFD800", "õF0A830", "õA8FF48", "õD8F000", "õF8DE7E",
   "õFFD300", "õFAFAD2", "õD8F000", "õF8DE7E", "õFFD300", "õFAFAD2",
   "õFFDAB9", "õFFBD2E", "õEEDC82", "õFADFAD", "õFFDB58", "õFFDEAD",
   "õFFF44F", "õFFFDD0", "õCC7722", "õCBBD55", "õFFE135", "õEEE8AA",
   "õF0E68C", "õBDB76B", "õFFFF00", "õ808000", "õADFF2F", "õ9ACD32",
   "õFFBF00", "õC09999",
   /* shades of green (32)         */
   "õA8D8A8", "õ00A890", "õ00F0A8", "õ609060", "õD8F0C0", "õ486060",
   "õ007848", "õ183030", "õ609078", "õ909078", "õ609048", "õ309030",
   "õ00C0A8", "õ48A890", "õ90C0A8", "õ487800", "õA8C090", "õ186048",
   "õF0FFF0", "õ30FF60", "õA8FFA8", "õ00C000", "õ487830", "õ007878",
   "õA8FF48", "õ48A860", "õ30A860", "õC0C030", "õ30C078", "õ90C0C0",
   "õ78D878", "õ004830",
   /* shades of orange (32)        */
   "õF09030", "õFFC048", "õFF6030", "õFFA800", "õFF6000", "õFF4848",
   "õFF3030", "õFCD667", "õFDB064", "õF99245", "õCC5500", "õFFA500",
   "õCB7119", "õF4AE72", "õB06500", "õB29082", "õE89362", "õD8A175",
   "õ877548", "õF2A337", "õFF7518", "õCC5500", "õCD7F32", "õ996633",
   "õFBCEB1", "õFFBF00", "õF8BA37", "õE6292C", "õFF8066", "õD23B05",
   "õF7DCB4", "õ985629",
   /* shades of blue (32)          */
   "õ000090", "õ4848D8", "õ7878D8", "õ60C0C0", "õ489090", "õ006060",
   "õ1890F0", "õ6078F0", "õ90D8C0", "õA8D8F0", "õ4890A8", "õD8F0FF",
   "õ48A8A8", "õ006090", "õ00D8D8", "õ6078D8", "õ007890", "õ78C0F0",
   "õ6890D8", "õ3048C0", "õ486078", "õ004860", "õ0090A8", "õ6060C0",
   "õ1890A8", "õ184878", "õ1800C0", "õ6048C0", "õ003048", "õ18A8D8",
   "õA8FFD8", "õ004878",
   /* shades of brown (32)         */
   "õ7F4737", "õ8A3324", "õE97451", "õ954535", "õEECEAC", "õCC7722",
   "õA89A8F", "õ906E3E", "õ800000", "õ8B4513", "õD2691E", "õCD853F",
   "õDAA520", "õF4A460", "õBC8F8F", "õD2B48C", "õDEB887", "õF5DEB3",
   "õFFDEAD", "õFFE4C4", "õFFF8DC", "õ452A19", "õ996515", "õC19A6B",
   "õ704214", "õ75463A", "õ59260B", "õBF914B", "õC19A6B", "õ5D432C",
   "õ674C47", "õ4A2C2A", 
   /* shades of purple (32)        */
   "õA32CC4", "õ7A4988", "õ710393", "õ630436", "õE39FF6", "õ601A35",
   "õA1045A", "õB65FCF", "õ663046", "õ8E93D4", "õ4D0F28", "õ9078C0",
   "õ311432", "õ6030A8", "õ67032F", "õ9867C5", "õ800080", "õ9E7BB5",
   "õ4B0082", "õA45EE5", "õ183078", "õ290916", "õAF69EF", "õ4C0121",
   "õD89EA6", "õ4B0082", "õ8A2BE2", "õDA70D6", "õ543948", "õFF1CAE",
   "õ9932CC", "õ8B008B",
   /* shades of grey (32)          */
   "õ6D616F", "õD9DDDC", "õ373737", "õ828282", "õ594D5B", "õD6CFC7", 
   "õ322D31", "õ787276", "õ696860", "õ999DA0", "õC5C6D0", "õ88807B", 
   "õADADC9", "õ877F7D", "õ59515E", "õBDB7AB", "õ3E3D53", "õB9BBB6", 
   "õ41424C", "õBEBDB8", "õ564C4D", "õ97978F", "õ4D4C5C", "õC7C6C1", 
   "õ7C6E7F", "õ222021", "õ655967", "õ808588", "õ7F7D9C", "õ777B7E", 
   "õ232023", "õ544C4A",
   /* shades of pink (32)          */
   "õFFC0C0", "õFF1493", "õFF90D8", "õFFB6C1", "õF09090", "õDB7093",
   "õF0D808", "õC71585", "õFF90A8", "õFEC5E5", "õF078C0", "õFC94AF",
   "õFFD8F0", "õFAB6CA", "õFF7890", "õFCBACB", "õ904860", "õ9E4244",
   "õFF60A8", "õFD5DA8", "õC060A8", "õF26BBA", "õFFA878", "õF25278",
   "õFFF0D8", "õFDA4BA", "õF0C0A8", "õFF6090", "õA84860", "õD87878",
   "õ783030", "õD8A8A8",
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
   --rce;  if (a_color >= s_ndiff)  return "õ------";
   return s_bases [s_diffs [a_color].map];
}




/*===============================[[ end-code ]]===============================*/
