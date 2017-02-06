/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



char  s_use        = YCOLOR_WHEEL;
int   s_cset       =  6;
int   s_ccolor     =  0;
int   s_ncolor     =  0;
int   s_cvariant   =  0;
int   s_lvariant   =  0;
int   s_nvariant   =  0;
int   s_cnorming   =  0;
int   s_nnorming   =  0;


const char s_RYB [MAX_COLOR][MAX_OPTION + 1][LEN_HEX] =
{  /*         original    pass 2     pass 1   paletton    latest      feb 5                                               */
   /*-120 */ "brown"           , "#000000", "#99401a", "#99804d", "#99804d", "#4a2208", "#4a2208", "#4a2208", "#4a2208", "#4a2208", "#4a2208",
   /*-110 */ ""                , "#000000", "#943920", "#946f4a", "#946f4a", "#522011", "#5a2011", "#522011", "#522011", "#522011", "#522011",
   /*-100 */ ""                , "#000000", "#903326", "#905e48", "#905e48", "#5b1f1a", "#6a1f1a", "#5b1f1a", "#5b1f1a", "#5b1f1a", "#5b1f1a",
   /*-090 */ ""                , "#000000", "#8c2c2d", "#8c4d46", "#8c4d46", "#641e24", "#7a1e24", "#641e24", "#641e24", "#641e24", "#641e24",
   /*-080 */ ""                , "#000000", "#882633", "#883c44", "#883c44", "#6d1c2d", "#8a1c2d", "#6d1c2d", "#6d1c2d", "#6d1c2d", "#6d1c2d",
   /*-070 */ ""                , "#000000", "#842039", "#842b42", "#842b42", "#761b36", "#9a1b36", "#761b36", "#761b36", "#761b36", "#761b36",
   /*-060 */ "blood"           , "#000000", "#801a40", "#801a40", "#801a40", "#7f1a40", "#aa1a40", "#7f1a40", "#7f1a40", "#7f1a40", "#7f1a40",
   /*-050 */ ""                , "#000000", "#951535", "#951535", "#951535", "#941535", "#b51535", "#941535", "#941535", "#941535", "#941535",
   /*-040 */ ""                , "#000000", "#aa112a", "#aa112a", "#aa112a", "#a9112a", "#c0112a", "#a9112a", "#a9112a", "#a9112a", "#a9112a",
   /*-030 */ ""                , "#000000", "#bf0d20", "#bf0d20", "#bf0d20", "#bf0d20", "#cc0d20", "#bf0d20", "#bf0d20", "#bf0d20", "#bf0d20",
   /*-020 */ ""                , "#000000", "#d40815", "#d40815", "#d40815", "#d40815", "#d70815", "#d40815", "#d40815", "#d40815", "#d40815",
   /*-010 */ ""                , "#000000", "#e9040a", "#e9040a", "#e9040a", "#e9040a", "#e2040a", "#e9040a", "#e9040a", "#e9040a", "#e9040a",
   /*------------------------(normal wheel)----------------------*/
   /* 000 */ "red"             , "#ff0000", "#ff0000", "#ff0000", "#aa3939", "#ff0000", "#ee0000", "#ff0000", "#ff0000", "#ff0000", "#ff0000",
   /* 010 */ ""                , "#ff3500", "#fb1400", "#ff1700", "#aa5039", "#ff1500", "#ee1500", "#ff1500", "#ff1500", "#ff1500", "#ff1500",
   /* 020 */ ""                , "#ff5900", "#f72800", "#ff3500", "#aa6039", "#ff2a00", "#ee2a00", "#ff2a00", "#ff2a00", "#ff2a00", "#ff2a00",
   /* 030 */ ""                , "#ff7400", "#f33d00", "#ff4700", "#aa6c39", "#ff3f00", "#ee3f00", "#ff3f00", "#ff3f00", "#ff3f00", "#ff3f00",
   /* 040 */ ""                , "#ff8900", "#f05100", "#ff5900", "#aa7539", "#ff5500", "#ee5500", "#ff5500", "#ff5500", "#ff5500", "#ff5500",
   /* 050 */ ""                , "#ff9a00", "#ec6600", "#ff6700", "#aa7d39", "#ff6a00", "#ee6900", "#ff6a00", "#ff6a00", "#ff6a00", "#ff6a00",
   /* 060 */ "orange"          , "#ffaa00", "#e87a00", "#ff7400", "#aa8439", "#ff7f00", "#ee7f00", "#ff7f00", "#ff7f00", "#ff7f00", "#ff7f00",
   /* 070 */ ""                , "#ffb800", "#e48e00", "#ff8b00", "#aa8b39", "#f98e00", "#e58900", "#f98e00", "#f98e00", "#f98e00", "#f98e00",
   /* 080 */ ""                , "#ffc600", "#e1a300", "#ffa200", "#aa9139", "#f39e00", "#dd9300", "#f39e00", "#f39e00", "#f39e00", "#f39e00",
   /* 090 */ ""                , "#ffd300", "#ddb700", "#ffb900", "#aa9739", "#edad00", "#d49d00", "#edad00", "#edad00", "#edad00", "#edad00",
   /* 100 */ ""                , "#ffe100", "#d9cc00", "#ffd000", "#aa9d39", "#e8bd00", "#cca700", "#e8bd00", "#e8bd00", "#e8bd00", "#e8bd00",
   /* 110 */ ""                , "#ffef00", "#d5e000", "#ffe500", "#aaa339", "#e2cd00", "#c3b100", "#e2cd00", "#e2cd00", "#e2cd00", "#e2cd00",
   /* 120 */ "yellow"          , "#ffff00", "#d2f500", "#ffff00", "#aaaa39", "#dddd00", "#bbbb00", "#dddd00", "#dddd00", "#dddd00", "#dddd00",
   /* 130 */ ""                , "#dcf900", "#afee00", "#d2ff00", "#99a637", "#b8df00", "#9bbd00", "#b8df00", "#b8df00", "#b8df00", "#b8df00",
   /* 140 */ ""                , "#bdf400", "#8ce700", "#a8ff00", "#8aa236", "#93e200", "#7cbd00", "#93e200", "#93e200", "#93e200", "#93e200",
   /* 150 */ ""                , "#9fee00", "#69e000", "#7eff00", "#7b9f35", "#6ee500", "#5dc300", "#6ee500", "#6ee500", "#6ee500", "#6ee500",
   /* 160 */ ""                , "#7ce700", "#46d900", "#54ff00", "#6b9a33", "#49e800", "#3ec600", "#49e800", "#49e800", "#49e800", "#49e800",
   /* 170 */ ""                , "#4dde00", "#23d200", "#2aff00", "#549431", "#24eb00", "#1fc900", "#24eb00", "#24eb00", "#24eb00", "#24eb00",
   /* 180 */ "green"           , "#00cc00", "#00cc15", "#00ff00", "#2d882d", "#00ee00", "#00cc00", "#00ee00", "#00ee00", "#00ee00", "#00ee00",
   /* 190 */ ""                , "#00b64f", "#07b13c", "#00d22a", "#28794c", "#00c62a", "#00af2a", "#00c62a", "#00c62a", "#00c62a", "#00c62a",
   /* 200 */ ""                , "#00a876", "#0e9663", "#00a854", "#25705a", "#009e55", "#009955", "#009e55", "#009e55", "#009e55", "#009e55",
   /* 210 */ ""                , "#009999", "#157b8a", "#00867e", "#226666", "#00777f", "#007f99", "#00777f", "#00777f", "#00777f", "#00777f",
   /* 220 */ ""                , "#086fa1", "#1c60b1", "#0064a8", "#27556c", "#004faa", "#0066aa", "#004faa", "#004faa", "#004faa", "#004faa",
   /* 230 */ ""                , "#0d56a6", "#2345d8", "#0032d2", "#2b4b6f", "#0027d4", "#0044dd", "#0027d4", "#0027d4", "#0027d4", "#0027d4",
   /* 240 */ "blue"            , "#1240ab", "#2a2aff", "#0000ff", "#2e4272", "#0000ff", "#0022ff", "#0000ff", "#0000ff", "#0000ff", "#0000ff",
   /* 250 */ ""                , "#1729b0", "#3523f0", "#1500e7", "#313975", "#1f00f3", "#1f11f3", "#1f00f3", "#1f00f3", "#1f00f3", "#1f00f3",
   /* 260 */ ""                , "#2618b1", "#411ce2", "#2a00d2", "#383276", "#3e00e8", "#3e00e8", "#3e00e8", "#3e00e8", "#3e00e8", "#3e00e8",
   /* 270 */ ""                , "#3914af", "#4d15d4", "#3f00bd", "#403075", "#5d00dc", "#5d00dc", "#5d00dc", "#5d00dc", "#5d00dc", "#5d00dc",
   /* 280 */ ""                , "#4a11ae", "#590ec6", "#5400a8", "#482e74", "#7c00d1", "#7c00d1", "#7c00d1", "#7c00d1", "#7c00d1", "#7c00d1",
   /* 290 */ ""                , "#5c0dac", "#6507b8", "#690093", "#4f2c73", "#9b00c6", "#9b00c6", "#9b00c6", "#9b00c6", "#9b00c6", "#9b00c6",
   /* 300 */ "royal"           , "#7109aa", "#7100aa", "#7e007e", "#582a72", "#bb00bb", "#bb00bb", "#bb00bb", "#bb00bb", "#bb00bb", "#bb00bb",
   /* 310 */ ""                , "#8f04a8", "#88008d", "#930069", "#652770", "#c6009b", "#c3009b", "#c6009b", "#c6009b", "#c6009b", "#c6009b",
   /* 320 */ ""                , "#b70094", "#a00071", "#a80054", "#7a296a", "#d1007c", "#cc007c", "#d1007c", "#d1007c", "#d1007c", "#d1007c",
   /* 330 */ ""                , "#cd0074", "#b70055", "#bd003f", "#882d61", "#dd005d", "#d4005d", "#dd005d", "#dd005d", "#dd005d", "#dd005d",
   /* 340 */ ""                , "#dc0055", "#cf0038", "#d2002a", "#933157", "#e8003e", "#dd003e", "#e8003e", "#e8003e", "#e8003e", "#e8003e",
   /* 350 */ ""                , "#ec0033", "#e7001c", "#e70015", "#9d344b", "#f3001f", "#e5001f", "#f3001f", "#f3001f", "#f3001f", "#f3001f",
   /*---------------------(alternate ending)---------------------*/
   /* 310 */ ""                , "#000000", "#68049c", "#68049c", "#68049c", "#a604aa", "#a404aa", "#a604aa", "#a604aa", "#a604aa", "#a604aa",
   /* 320 */ ""                , "#000000", "#60088f", "#60088f", "#60088f", "#91089a", "#9a089a", "#91089a", "#91089a", "#91089a", "#91089a",
   /* 330 */ ""                , "#000000", "#530c81", "#530c81", "#530c81", "#7d0c8a", "#8a0c8a", "#7d0c8a", "#7d0c8a", "#7d0c8a", "#7d0c8a",
   /* 340 */ ""                , "#000000", "#501174", "#501174", "#501174", "#681179", "#791179", "#681179", "#681179", "#681179", "#681179",
   /* 350 */ ""                , "#000000", "#471566", "#471566", "#471566", "#541569", "#691569", "#541569", "#541569", "#541569", "#541569",
   /* 360 */ "purple"          , "#000000", "#3f1959", "#3f1959", "#3f1959", "#3f1959", "#591959", "#3f1959", "#3f1959", "#3f1959", "#3f1959",
   /* 370 */ ""                , "#000000", "#41225f", "#41225f", "#41225f", "#41225f", "#57225f", "#41225f", "#41225f", "#41225f", "#41225f",
   /* 380 */ ""                , "#000000", "#442a66", "#442a66", "#442a66", "#442a66", "#552a66", "#442a66", "#442a66", "#442a66", "#442a66",
   /* 390 */ ""                , "#000000", "#46336c", "#46336c", "#46336c", "#46336c", "#52336c", "#46336c", "#46336c", "#46336c", "#46336c",
   /* 400 */ ""                , "#000000", "#483b72", "#483b72", "#483b72", "#483b72", "#503b72", "#483b72", "#483b72", "#483b72", "#483b72",
   /* 410 */ ""                , "#000000", "#4a4479", "#4a4479", "#4a4479", "#4a4479", "#4e4479", "#4a4479", "#4a4479", "#4a4479", "#4a4479",
   /* 420 */ "steel"           , "#000000", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f",
   /* 430 */ ""                , "#000000", "#52527f", "#52527f", "#52527f", "#52527f", "#52527f", "#52527f", "#52527f", "#52527f", "#52527f",
   /* 440 */ ""                , "#000000", "#59597f", "#59597f", "#59597f", "#59597f", "#59597f", "#59597f", "#59597f", "#59597f", "#59597f",
   /* 450 */ ""                , "#000000", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f",
   /* 460 */ ""                , "#000000", "#66667f", "#66667f", "#66667f", "#66667f", "#66667f", "#66667f", "#66667f", "#66667f", "#66667f",
   /* 470 */ ""                , "#000000", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f",
   /* 480 */ "grey"            , "#000000", "#72727f", "#72727f", "#72727f", "#72727f", "#72727f", "#72727f", "#72727f", "#72727f", "#72727f",
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
   { "fullsome"  , "de", "deeper"                ,   1.00,  0.10,  0.50 },
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

tNORMING s_normings   [MAX_NORMING] =
{
   { "no"  , "none"                           , 0.00, 0.00, 0.00, 'n' },
   { "bl"  , "byte_light"                     , 0.05, 0.05, 0.00, 'n' },
   { "bi"  , "byte_intensity"                 , 0.05, 0.10, 0.00, 'n' },
   { "bm"  , "byte_moderate"                  , 0.10, 0.10, 0.00, 'n' },
   { "bh"  , "byte_heavy"                     , 0.20, 0.20, 0.00, 'n' },
   { "bz"  , "byte_intensity+"                , 0.10, 0.20, 0.00, 'n' },
   { "bs"  , "byte_intensity++"               , 0.15, 0.30, 0.00, 'n' },
   { "tl"  , "total_light"                    , 0.05, 0.05, 0.00, 'y' },
   { "ti"  , "total_intensity"                , 0.05, 0.10, 0.00, 'y' },
   { "nw"  , "new one"                        , 0.05, 0.20, 0.05, 't' },
   { ""    , "end of input"                   , 0.00, 0.00, 0.00, 'n' }
};



/*============================--------------------============================*/
/*===----                           utility                            ----===*/
/*============================--------------------============================*/
static void      o___UTILITY_________________o (void) {;}

float
yCOLOR__min3       (float a_one, float a_two, float a_three)
{
   if    (a_one <= a_two) {
      if (a_one <= a_three)  return a_one;
      return                        a_three;
   } else {
      if (a_two <= a_three)  return a_two;
      return                        a_three;
   }
   return                           a_two;
}

float
yCOLOR__max3       (float a_one, float a_two, float a_three)
{
   if    (a_one >= a_two) {
      if (a_one >= a_three)  return a_one;
      return                        a_three;
   } else {
      if (a_two >= a_three)  return a_two;
      return                        a_three;
   }
   return                           a_two;
}



/*============================--------------------============================*/
/*===----                         preparation                          ----===*/
/*============================--------------------============================*/
static void      o___PREPARATION_____________o (void) {;}

char
yCOLOR_use           (char  a_use)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;      /* return code for errors              */
   char        x_ncolor    =   0;
   /*---(defense)------------------------*/
   --rce;  if (strchr ("wsl", a_use) == NULL) {
      s_use = YCOLOR_WHEEL;   /* safe default */
      return rce;
   }
   /*---(set global)---------------------*/
   s_use = a_use;
   switch (a_use) {
   case YCOLOR_WHEEL :  x_ncolor = 36;  break;
   case YCOLOR_SMALL :  x_ncolor = 25;  break;
   case YCOLOR_LARGE :  x_ncolor = 67;  break;
   default           :  x_ncolor =  0;  break;
   }
   /*---(complete)-----------------------*/
   return x_ncolor;
}

char
yCOLOR_init          (char  a_use)
{
   int         i           = 0;
   char        x_ncolor    =   0;
   s_ncolor   = 0;
   x_ncolor = yCOLOR_use (a_use);
   for (i = 0; i < MAX_COLOR  ; ++i) {
      if (s_RYB      [i][1][0] == '\0')            break;
      ++s_ncolor;
   }
   s_nvariant = 0;
   for (i = 0; i < MAX_VARIANT; ++i) {
      if (s_variants [i].abbr [0] == '\0')            break;
      ++s_nvariant;
   }
   s_nnorming = 0;
   for (i = 0; i < MAX_NORMING; ++i) {
      if (s_normings [i].abbr[0] == '\0') break;
      ++s_nnorming;
   }
   return x_ncolor;
}



/*============================--------------------============================*/
/*===----                           accessors                          ----===*/
/*============================--------------------============================*/
static void      o___ACCESSOR________________o (void) {;}

char
yCOLOR_deg2index     (int a_deg, int *a_index)
{  /*---(design notes)-------------------*/
   /*
    *  always returns a valid index, but sends a positive return code if it
    *  must adjust to obtain a valid degree.
    */
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   char        rc          =   0;
   int         x_index     =   0;
   /*---(adjust)-------------------------*/
   if        (s_use == YCOLOR_WHEEL) {
      while (a_deg <    0)  { a_deg +=  360; rc = -rce; }
      while (a_deg >= 360)  { a_deg -=  360; rc = -rce; }
   } else if (s_use == YCOLOR_SMALL) {
      if    (a_deg <    0)  { a_deg  =    0; rc = -rce; }
      if    (a_deg >  240)  { a_deg  =  240; rc = -rce; }
   } else if (s_use == YCOLOR_LARGE) {
      if    (a_deg < -120)  { a_deg  = -120; rc = -rce; }
      if    (a_deg >  300)  { a_deg +=   50;            }
      if    (a_deg >  480)  { a_deg  =  480; rc = -rce; }
   } else {
      a_deg = 0;
      rc = -rce;
   }
   /*---(calculate)----------------------*/
   x_index = a_deg / 10 + 12;
   if (a_index)  *a_index = x_index;
   /*---(complete)-----------------------*/
   return rc;
}

char
yCOLOR_deg2hex       (int a_deg, char *a_hex)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   int         x_index     =   0;
   /*---(parse color)--------------------*/
   rc = yCOLOR_deg2index (a_deg, &x_index);
   strlcpy (a_hex, s_RYB [x_index][s_cset], LEN_HEX);
   /*---(complete)-----------------------*/
   return rc;
}

char         /*--> use hex code to set opengl color ------[ ------ [ ------ ]-*/
yCOLOR_hex2color     (char *a_hex)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   int         i           =   0;
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   /*---(defense)------------------------*/
   --rce;  if (a_hex == NULL)        return rce;
   --rce;  if (strlen (a_hex) != 7)  return rce;
   --rce;  if (a_hex [0] != '#')     return rce;
   --rce;  for (i = 1; i < 7; ++i) {
      if (strchr ("0123456789abcdefABCDEF", a_hex [i]) == NULL)  return rce;
   }
   /*---(parse color)--------------------*/
   x_red = yCOLOR__unhex (a_hex[1], a_hex[2]);
   x_grn = yCOLOR__unhex (a_hex[3], a_hex[4]);
   x_blu = yCOLOR__unhex (a_hex[5], a_hex[6]);
   /*---(set color)----------------------*/
   glColor4f   (x_red, x_grn, x_blu, 1.0f);
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> use degree to set opengl color --------[ ------ [ ------ ]-*/
yCOLOR_deg2color     (int a_deg)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   int         x_index     =   0;
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   /*---(parse color)--------------------*/
   rc = yCOLOR_deg2index (a_deg, &x_index);
   x_red   = yCOLOR__unhex (s_RYB [x_index][s_cset][1], s_RYB [x_index][s_cset][2]);
   x_grn   = yCOLOR__unhex (s_RYB [x_index][s_cset][3], s_RYB [x_index][s_cset][4]);
   x_blu   = yCOLOR__unhex (s_RYB [x_index][s_cset][5], s_RYB [x_index][s_cset][6]);
   /*---(set color)----------------------*/
   glColor4f   (x_red, x_grn, x_blu, 1.0f);
   /*---(complete)-----------------------*/
   return rc;
}



/*============================--------------------============================*/
/*===----                          conversions                         ----===*/
/*============================--------------------============================*/
static void      o___CONVERSION______________o (void) {;}

float
yCOLOR__unhex        (char a_one, char a_two)
{
   /*---(locals)-----------+-----------+-*/
   float       x_one       = 0.0;
   float       x_two       = 0.0;
   float       x_result    = 0.0;
   /*---(first char)---------------------*/
   if      (a_one >= '0' && a_one <= '9')   x_one = a_one - '0';
   else if (a_one >= 'a' && a_one <= 'f')   x_one = a_one - 'a' + 10;
   else if (a_one >= 'A' && a_one <= 'F')   x_one = a_one - 'A' + 10;
   else                                     x_one = 0.0;
   /*---(second char)--------------------*/
   if      (a_two >= '0' && a_two <= '9')   x_two = a_two - '0';
   else if (a_two >= 'a' && a_two <= 'f')   x_two = a_two - 'a' + 10;
   else if (a_two >= 'A' && a_two <= 'F')   x_two = a_two - 'A' + 10;
   else                                     x_two = 0.0;
   /*---(calc)---------------------------*/
   x_result =  ((x_one * 16.0) + x_two) / 255.0;
   /*---(complete)-----------------------*/
   return x_result;
}

char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR_hex2hsv      (     /* PURPOSE = convert RGB hex into HSV            */
      char     *a_hex,            /* RBG 24-bit hex code            (#RRGGBB) */
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
   x_red = yCOLOR__unhex (a_hex [1], a_hex [2]);
   x_grn = yCOLOR__unhex (a_hex [3], a_hex [4]);
   x_blu = yCOLOR__unhex (a_hex [5], a_hex [6]);
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

char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR_hsv2hex    (           /* PURPOSE = convert HSV to RGB HEX              */
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
   snprintf(a_hex, LEN_HEX, "#%02x%02x%02x", u_red, u_grn, u_blu);
   /*---(complete)-------------------------*/
   return 0;
}



/*============================--------------------============================*/
/*===----                         color changes                        ----===*/
/*============================--------------------============================*/
static void      o___CHANGES_________________o (void) {;}

char       /*=((c_convert))===* return  = simple error code                   */
yCOLOR_accent        (       /* PURPOSE = apply a color variation             */
      char      a_level,          /* accent level                             */
      char     *a_hex,            /* rgb three byte hex code        (#rrggbb) */
      char     *a_out)            /* rgb three byte hex code        (#rrggbb) */
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;      /* return code for errors              */
   int         i           =   0;      /* generic iterator                    */
   int         x_index     =  -1;      /* variant index                       */
   int         rc          =   0;      /* generic return code                 */
   float       x_hue       =   0.0;    /* HSV hue                             */
   float       x_sat       =   0.0;    /* HSV saturation                      */
   float       x_val       =   0.0;    /* HSV value                           */
   /*---(defense)--------------------------*/
   --rce;  if (a_hex  == NULL) {
      return rce;
   }
   --rce;  if (a_out  == NULL) {
      return rce;
   }
   /*---(initialize)-----------------------*/
   strlcpy (a_out, a_hex, LEN_HEX);
   /*---(search)---------------------------*/
   x_index = s_cvariant;
   /*---(get the base)---------------------*/
   rc = yCOLOR_hex2hsv (a_hex, &x_hue, &x_sat, &x_val);
   --rce;  if (rc != 0) {
      return rce;
   }
   /*> printf ("\n");                                                                                     <* 
    *> printf ("base   hex = %s, hue = %4.2f, sat = %4.2f, val = %4.2f\n", a_hex, x_hue, x_sat, x_val);   <*/
   /*---(get the modifiers)----------------*/
   --rce;  switch (a_level) {
   case '^' :  /* lightest      */
      x_sat   = x_sat - (x_sat * (s_variants [x_index].accent * 1.75));
      x_val   = x_val + (x_val * (s_variants [x_index].accent * 1.00));
      /*> printf ("top    hue = %4.2f, sat = %4.2f, val = %4.2f\n", x_hue, x_sat, x_val);   <*/
      break;
   case '+' :  /* lighter       */
      x_sat   = x_sat - (x_sat * (s_variants [x_index].accent * 1.25));
      x_val   = x_val + (x_val * (s_variants [x_index].accent * 0.50));
      /*> printf ("plus   hue = %4.2f, sat = %4.2f, val = %4.2f\n", x_hue, x_sat, x_val);   <*/
      break;
   case '-' :  /* darker        */
      x_sat   = x_sat;
      x_val   = x_val - (x_val * (s_variants [x_index].accent * 0.45));
      /*> printf ("minus  hue = %4.2f, sat = %4.2f, val = %4.2f\n", x_hue, x_sat, x_val);   <*/
      break;
   case 'v' :  /* darkest       */
      x_sat   = x_sat;
      x_val   = x_val - (x_val * (s_variants [x_index].accent * 0.95));
      /*> printf ("bot    hue = %4.2f, sat = %4.2f, val = %4.2f\n", x_hue, x_sat, x_val);   <*/
      break;
   default  :
      return rce;
      break;
   }
   /*---(apply the modifiers)--------------*/
   rc = yCOLOR_hsv2hex (x_hue, x_sat, x_val, a_out);
   /*> printf ("modded hex = %s, hue = %4.2f, sat = %4.2f, val = %4.2f\n", a_out, x_hue, x_sat, x_val);   <*/
   --rce;  if (rc != 0) {
      return rce;
   }
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((c_convert))===* return  = simple error code                   */
yCOLOR_variant       (       /* PURPOSE = apply a color variation             */
      char     *a_name,           /* variation name                           */
      char     *a_hex,            /* rgb three byte hex code        (#rrggbb) */
      char     *a_out)            /* rgb three byte hex code        (#rrggbb) */
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;      /* return code for errors              */
   int         i           =   0;      /* generic iterator                    */
   int         x_index     =  -1;      /* variant index                       */
   int         rc          =   0;      /* generic return code                 */
   float       x_hue       =   0.0;    /* HSV hue                             */
   float       x_sat       =   0.0;    /* HSV saturation                      */
   float       x_val       =   0.0;    /* HSV value                           */
   /*---(defense)--------------------------*/
   --rce;  if (a_name == NULL) {
      return rce;
   }
   --rce;  if (a_hex  == NULL) {
      return rce;
   }
   --rce;  if (a_out  == NULL) {
      return rce;
   }
   /*---(initialize)-----------------------*/
   strlcpy (a_out, a_hex, LEN_HEX);
   /*---(search)---------------------------*/
   if (strcmp (a_name, "CURRENT") == 0)  x_index = s_cvariant;
   if (strcmp (a_name, "SAME"   ) == 0)  x_index = s_lvariant;
   if (strcmp (a_name, "FIRST"  ) == 0)  x_index = 0;
   if (strcmp (a_name, "NEXT"   ) == 0)  x_index = ++s_lvariant;
   if (x_index < 0) {
      for (i = 0; i < MAX_VARIANT; ++i) {
         if (s_variants [i].abbr [0] == '\0')            break;
         if ((strcmp (s_variants [i].abbr, a_name) != 0) &&
               (strcmp (s_variants [i].name, a_name) != 0))  continue;
         x_index = i;
         break;
      }
   }
   --rce;  if (x_index < 0) {
      return rce;
   }
   --rce;  if (x_index >= s_nvariant) {
      return rce;
   }
   s_lvariant = x_index;
   /*---(check for nothing)----------------*/
   if (x_index == 0) {
      return 0;
   }
   /*---(get the base)---------------------*/
   rc = yCOLOR_hex2hsv (a_hex, &x_hue, &x_sat, &x_val);
   --rce;  if (rc != 0) {
      return rce;
   }
   /*---(get the modifiers)----------------*/
   x_sat   = s_variants [x_index].new_sat;
   x_val   = s_variants [x_index].new_val;
   /*---(apply the modifiers)--------------*/
   rc = yCOLOR_hsv2hex (x_hue, x_sat, x_val, a_out);
   --rce;  if (rc != 0) {
      return rce;
   }
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((c_convert))===* return  = simple error code                   */
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

char       /*=((pUPDATE ]]=========* return  = simple error code              */
yCOLOR__norming    (      /* PURPOSE = level color intensity               */
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
   x_red = yCOLOR__unhex (a_hex [1], a_hex [2]);
   x_grn = yCOLOR__unhex (a_hex [3], a_hex [4]);
   x_blu = yCOLOR__unhex (a_hex [5], a_hex [6]);
   if (s_normings [a_index].is_value == 'y') {
      /*---(update)---------------------------*/
      x_red *= (s_normings [a_index].red);
      x_grn *= (s_normings [a_index].grn);
      x_blu *= (s_normings [a_index].blu);
      x_norm = 1.000 - x_red - x_grn - x_blu;
      yCOLOR_hex2hsv (a_hex, &x_hue, &x_sat, &x_val);
      yCOLOR_hsv2hex (x_hue, x_sat, x_val * x_norm, a_out);
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
      snprintf (a_out, LEN_HEX, "#%02x%02x%02x", u_red, u_grn, u_blu);
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
      snprintf (a_out, LEN_HEX, "#%02x%02x%02x", u_red, u_grn, u_blu);
   }
   /*---(complete)-------------------------*/
   return 0;
}
