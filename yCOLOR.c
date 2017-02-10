/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



char        s_use       = YCOLOR_WHEEL;
char        s_scale     = YCOLOR_LINEAR;
int         s_cset      = 10;
int         s_ccolor    =  0;
int         s_tcolor    =  0;
int         s_ncolor    =  0;
int         s_cvariant  =  0;
int         s_lvariant  =  0;
int         s_nvariant  =  0;
int         s_cnorming  =  0;
int         s_nnorming  =  0;



tCOLORS     s_colors    [MAX_COLOR];



char s_RYB [MAX_COLOR][MAX_OPTION + 1][LEN_LABEL] =
{  /*                             original    pass 2     pass 1   paletton    latest      feb 5                                               */
   /*-120 */ "brown"           , "#000000", "#99401a", "#99804d", "#99804d", "#4a2208", "#4a2208", "#4a2208", "#4a2208", "#4a2208", "#4a2208",
   /*-110 */ "ginderbread"     , "#000000", "#943920", "#946f4a", "#946f4a", "#522011", "#5a2011", "#522011", "#522011", "#522011", "#522011",
   /*-100 */ "carmel"          , "#000000", "#903326", "#905e48", "#905e48", "#5b1f1a", "#6a1f1a", "#5b1f1a", "#5b1f1a", "#5b1f1a", "#5b1f1a",
   /*-090 */ "chocolate"       , "#000000", "#8c2c2d", "#8c4d46", "#8c4d46", "#641e24", "#7a1e24", "#641e24", "#641e24", "#641e24", "#641e24",
   /*-080 */ "chestnut"        , "#000000", "#882633", "#883c44", "#883c44", "#6d1c2d", "#8a1c2d", "#6d1c2d", "#6d1c2d", "#6d1c2d", "#6d1c2d",
   /*-070 */ "cinnamon"        , "#000000", "#842039", "#842b42", "#842b42", "#761b36", "#9a1b36", "#761b36", "#761b36", "#761b36", "#761b36",
   /*-060 */ "burnt umber"     , "#000000", "#801a40", "#801a40", "#801a40", "#7f1a40", "#aa1a40", "#7f1a40", "#7f1a40", "#7f1a40", "#7f1a40",
   /*-050 */ "libstick"        , "#000000", "#951535", "#951535", "#951535", "#941535", "#b51535", "#941535", "#941535", "#941535", "#941535",
   /*-040 */ "auburn"          , "#000000", "#aa112a", "#aa112a", "#aa112a", "#a9112a", "#c0112a", "#a9112a", "#a9112a", "#a9112a", "#a9112a",
   /*-030 */ "cherry"          , "#000000", "#bf0d20", "#bf0d20", "#bf0d20", "#bf0d20", "#cc0d20", "#bf0d20", "#bf0d20", "#bf0d20", "#bf0d20",
   /*-020 */ "candy"           , "#000000", "#d40815", "#d40815", "#d40815", "#d40815", "#d70815", "#d40815", "#d40815", "#d40815", "#d40815",
   /*-010 */ "carmine"         , "#000000", "#e9040a", "#e9040a", "#e9040a", "#e9040a", "#e2040a", "#e9040a", "#e9040a", "#e9040a", "#e9040a",
   /*------------------------(normal wheel)----------------------*/
   /* 000 */ "red"             , "#ff0000", "#ff0000", "#ff0000", "#aa3939", "#ff0000", "#ee0000", "#aa0000", "#ff0000", "#ff0000", "#ff0000",
   /* 010 */ "ferrari"         , "#ff3500", "#fb1400", "#ff1700", "#aa5039", "#ff1500", "#ee1500", "#000000", "#ff1500", "#ff1500", "#ff1500",
   /* 020 */ "scarlet"         , "#ff5900", "#f72800", "#ff3500", "#aa6039", "#ff2a00", "#ee2a00", "#000000", "#ff2a00", "#ff2a00", "#ff2a00",
   /* 030 */ "cinnibar"        , "#ff7400", "#f33d00", "#ff4700", "#aa6c39", "#ff3f00", "#ee3f00", "#952000", "#ff3f00", "#ff3f00", "#ff3f00",
   /* 040 */ "vermillion"      , "#ff8900", "#f05100", "#ff5900", "#aa7539", "#ff5500", "#ee5500", "#000000", "#ff5500", "#ff5500", "#ff5500",
   /* 050 */ "pumpkin"         , "#ff9a00", "#ec6600", "#ff6700", "#aa7d39", "#ff6a00", "#ee6900", "#000000", "#ff6a00", "#ff6a00", "#ff6a00",
   /* 060 */ "orange"          , "#ffaa00", "#e87a00", "#ff7400", "#aa8439", "#ff7f00", "#ee7f00", "#8f4000", "#ff7f00", "#ff7f00", "#ff7f00",
   /* 070 */ "amber"           , "#ffb800", "#e48e00", "#ff8b00", "#aa8b39", "#f98e00", "#e58900", "#000000", "#f98e00", "#f98e00", "#f98e00",
   /* 080 */ "apricot"         , "#ffc600", "#e1a300", "#ffa200", "#aa9139", "#f39e00", "#dd9300", "#000000", "#f39e00", "#f39e00", "#f39e00",
   /* 090 */ "gold"            , "#ffd300", "#ddb700", "#ffb900", "#aa9739", "#edad00", "#d49d00", "#856000", "#edad00", "#edad00", "#edad00",
   /* 100 */ "honey"           , "#ffe100", "#d9cc00", "#ffd000", "#aa9d39", "#e8bd00", "#cca700", "#000000", "#e8bd00", "#e8bd00", "#e8bd00",
   /* 110 */ "burnt"           , "#ffef00", "#d5e000", "#ffe500", "#aaa339", "#e2cd00", "#c3b100", "#000000", "#e2cd00", "#e2cd00", "#e2cd00",
   /* 120 */ "yellow"          , "#ffff00", "#d2f500", "#ffff00", "#aaaa39", "#dddd00", "#bbbb00", "#808000", "#dddd00", "#dddd00", "#dddd00",
   /* 130 */ "lime"            , "#dcf900", "#afee00", "#d2ff00", "#99a637", "#b8df00", "#9bbd00", "#000000", "#b8df00", "#b8df00", "#b8df00",
   /* 140 */ "chartreuse"      , "#bdf400", "#8ce700", "#a8ff00", "#8aa236", "#93e200", "#7cbd00", "#000000", "#93e200", "#93e200", "#93e200",
   /* 150 */ "spring"          , "#9fee00", "#69e000", "#7eff00", "#7b9f35", "#6ee500", "#5dc300", "#5aa500", "#6ee500", "#6ee500", "#6ee500",
   /* 160 */ "harlequin"       , "#7ce700", "#46d900", "#54ff00", "#6b9a33", "#49e800", "#3ec600", "#000000", "#49e800", "#49e800", "#49e800",
   /* 170 */ "apple"           , "#4dde00", "#23d200", "#2aff00", "#549431", "#24eb00", "#1fc900", "#000000", "#24eb00", "#24eb00", "#24eb00",
   /* 180 */ "green"           , "#00cc00", "#00cc15", "#00ff00", "#2d882d", "#00ee00", "#00cc00", "#00aa00", "#00ee00", "#00ee00", "#00ee00",
   /* 190 */ "teal"            , "#00b64f", "#07b13c", "#00d22a", "#28794c", "#00c62a", "#00af2a", "#000000", "#00c62a", "#00c62a", "#00c62a",
   /* 200 */ "turquoise"       , "#00a876", "#0e9663", "#00a854", "#25705a", "#009e55", "#009955", "#000000", "#009e55", "#009e55", "#009e55",
   /* 210 */ "cyan"            , "#009999", "#157b8a", "#00867e", "#226666", "#00777f", "#007f99", "#005050", "#00777f", "#00777f", "#00777f",
   /* 220 */ "aqua"            , "#086fa1", "#1c60b1", "#0064a8", "#27556c", "#004faa", "#0066aa", "#000000", "#004faa", "#004faa", "#004faa",
   /* 230 */ "sky"             , "#0d56a6", "#2345d8", "#0032d2", "#2b4b6f", "#0027d4", "#0044dd", "#000000", "#0027d4", "#0027d4", "#0027d4",
   /* 240 */ "blue"            , "#1240ab", "#2a2aff", "#0000ff", "#2e4272", "#0000ff", "#1022ff", "#0000aa", "#0000ff", "#0000ff", "#0000ff",
   /* 250 */ "navy"            , "#1729b0", "#3523f0", "#1500e7", "#313975", "#1f00f3", "#3f11f4", "#000000", "#1f00f3", "#1f00f3", "#1f00f3",
   /* 260 */ "indigo"          , "#2618b1", "#411ce2", "#2a00d2", "#383276", "#3e00e8", "#5f11e9", "#000000", "#3e00e8", "#3e00e8", "#3e00e8",
   /* 270 */ "purple"          , "#3914af", "#4d15d4", "#3f00bd", "#403075", "#5d00dc", "#7f11df", "#400095", "#5d00dc", "#5d00dc", "#5d00dc",
   /* 280 */ "royal"           , "#4a11ae", "#590ec6", "#5400a8", "#482e74", "#7c00d1", "#8f00d4", "#000000", "#7c00d1", "#7c00d1", "#7c00d1",
   /* 290 */ "violet"          , "#5c0dac", "#6507b8", "#690093", "#4f2c73", "#9b00c6", "#a500c9", "#000000", "#9b00c6", "#9b00c6", "#9b00c6",
   /* 300 */ "magenta"         , "#7109aa", "#7100aa", "#7e007e", "#582a72", "#bb00bb", "#bb00bb", "#800080", "#bb00bb", "#bb00bb", "#bb00bb",
   /* 310 */ "pink"            , "#8f04a8", "#88008d", "#930069", "#652770", "#c6009b", "#c6009f", "#000000", "#c6009b", "#c6009b", "#c6009b",
   /* 320 */ "rose"            , "#b70094", "#a00071", "#a80054", "#7a296a", "#d1007c", "#ce007f", "#000000", "#d1007c", "#d1007c", "#d1007c",
   /* 330 */ "crimson"         , "#cd0074", "#b70055", "#bd003f", "#882d61", "#dd005d", "#d6005f", "#900040", "#dd005d", "#dd005d", "#dd005d",
   /* 340 */ "ruby"            , "#dc0055", "#cf0038", "#d2002a", "#933157", "#e8003e", "#de003f", "#000000", "#e8003e", "#e8003e", "#e8003e",
   /* 350 */ "spanish"         , "#ec0033", "#e7001c", "#e70015", "#9d344b", "#f3001f", "#e6001f", "#000000", "#f3001f", "#f3001f", "#f3001f",
   /*---------------------(alternate ending)---------------------*/
   /* 300 */ "PLACEHOLDER"     , "#000000", "#000000", "#000000", "#000000", "#000000", "#000000", "#000000", "#000000", "#000000", "#000000",
   /* 310 */ "lilac"           , "#000000", "#68049c", "#68049c", "#68049c", "#a604aa", "#ae04ae", "#a604aa", "#a604aa", "#a604aa", "#a604aa",
   /* 320 */ "iris"            , "#000000", "#60088f", "#60088f", "#60088f", "#91089a", "#9d089d", "#91089a", "#91089a", "#91089a", "#91089a",
   /* 330 */ "eggplant"        , "#000000", "#530c81", "#530c81", "#530c81", "#7d0c8a", "#8c0c8c", "#7d0c8a", "#7d0c8a", "#7d0c8a", "#7d0c8a",
   /* 340 */ "grape"           , "#000000", "#501174", "#501174", "#501174", "#681179", "#7b117b", "#681179", "#681179", "#681179", "#681179",
   /* 350 */ "velvet"          , "#000000", "#471566", "#471566", "#471566", "#541569", "#6a156a", "#541569", "#541569", "#541569", "#541569",
   /* 360 */ "mauve"           , "#000000", "#3f1959", "#3f1959", "#3f1959", "#3f1959", "#591959", "#3f1959", "#3f1959", "#3f1959", "#3f1959",
   /* 370 */ "petunia"         , "#000000", "#41225f", "#41225f", "#41225f", "#41225f", "#57225f", "#41225f", "#41225f", "#41225f", "#41225f",
   /* 380 */ "geranium"        , "#000000", "#442a66", "#442a66", "#442a66", "#442a66", "#552a66", "#442a66", "#442a66", "#442a66", "#442a66",
   /* 390 */ "slate"           , "#000000", "#46336c", "#46336c", "#46336c", "#46336c", "#52336c", "#46336c", "#46336c", "#46336c", "#46336c",
   /* 400 */ "graphite"        , "#000000", "#483b72", "#483b72", "#483b72", "#483b72", "#503b72", "#483b72", "#483b72", "#483b72", "#483b72",
   /* 410 */ "smoke"           , "#000000", "#4a4479", "#4a4479", "#4a4479", "#4a4479", "#4e4479", "#4a4479", "#4a4479", "#4a4479", "#4a4479",
   /* 420 */ "steel"           , "#000000", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f", "#4c4c7f",
   /* 430 */ "pewter"          , "#000000", "#52527f", "#52527f", "#52527f", "#52527f", "#52527f", "#52527f", "#52527f", "#52527f", "#52527f",
   /* 440 */ "ash"             , "#000000", "#59597f", "#59597f", "#59597f", "#59597f", "#59597f", "#59597f", "#59597f", "#59597f", "#59597f",
   /* 450 */ "silver"          , "#000000", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f", "#5f5f7f",
   /* 460 */ "flint"           , "#000000", "#66667f", "#66667f", "#66667f", "#66667f", "#66667f", "#66667f", "#66667f", "#66667f", "#66667f",
   /* 470 */ "cloud"           , "#000000", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f", "#6c6c7f",
   /* 480 */ "grey"            , "#000000", "#72727f", "#72727f", "#72727f", "#72727f", "#72727f", "#72727f", "#72727f", "#72727f", "#72727f",
};

const char s_newRYB [12][1][LEN_LABEL] = {
   /*-120 */ "#4a2222", /* "#4a2222", */
   /*-060 */ "#a52a2a", /* "#bb5050", */
   /* 000 */ "#ee0000",
   /* 060 */ "#ee7f00",
   /* 120 */ "#ccbb00",
   /* 180 */ "#00cc11",
   /* 240 */ "#2222ff",
   /* 300 */ "#bb00bb",
   /* 360 */ "#SPACER",
   /* 360 */ "#591959",
   /* 420 */ "#536878", /* "#4c4c7f", */
   /* 480 */ "#7f7f7f",
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

float
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

char
yCOLOR_use           (char  a_use)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;      /* return code for errors              */
   char        x_ncolor    =   0;
   int         i           =   0;
   int         x_index     =   0;
   char        x_hex       [LEN_HEX];
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
      strlcpy (x_hex, s_colors [i].hex, LEN_HEX);
      yCOLOR_hex2rgb (x_hex, &s_colors [i].red, &s_colors [i].grn, &s_colors [i].blu);
   }
   /*---(complete)-----------------------*/
   s_ncolor = x_ncolor;
   return x_ncolor;
}

char
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
         printf ("%2d   %4d   %4d   %5.2f   %6.1f\n", c,  i, (i * i), s_colors [c].pct, s_colors [c].cut);
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

char
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
   char        x_hex       [LEN_HEX];
   uchar       u_red       =   0;
   uchar       u_grn       =   0;
   uchar       u_blu       =   0;
   /*---(interpolate to 360)-------------*/
   for (x_base = a_beg; x_base <  a_end; ++x_base) {
      /*---(calc offset)-----------------*/
      x_index = x_base * 6;
      /*> if (x_base >= 8)  x_index += 6;                                             <*/
      /*---(calc start)------------------*/
      strlcpy (x_hex , s_RYB [x_index + 0][10], LEN_HEX);
      yCOLOR_hex2rgb (x_hex, &x_red1, &x_grn1, &x_blu1);
      /*> x_red1 = yCOLOR__unhex (x_hex[1], x_hex[2]);                                <* 
       *> x_grn1 = yCOLOR__unhex (x_hex[3], x_hex[4]);                                <* 
       *> x_blu1 = yCOLOR__unhex (x_hex[5], x_hex[6]);                                <*/
      /*---(calc end)--------------------*/
      strlcpy (x_hex , s_RYB [x_index + 6][10], LEN_HEX);
      yCOLOR_hex2rgb (x_hex, &x_red2, &x_grn2, &x_blu2);
      /*> x_red2 = yCOLOR__unhex (x_hex[1], x_hex[2]);                                <* 
       *> x_grn2 = yCOLOR__unhex (x_hex[3], x_hex[4]);                                <* 
       *> x_blu2 = yCOLOR__unhex (x_hex[5], x_hex[6]);                                <*/
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
         yCOLOR_rgb2hex  (x_hex, x_red1, x_grn1, x_blu1);
         /*> u_red = x_red1 * 255;                                                    <* 
          *> u_grn = x_grn1 * 255;                                                    <* 
          *> u_blu = x_blu1 * 255;                                                    <* 
          *> /+---(place into RGB hex)---------------+/                               <* 
          *> snprintf (x_hex, LEN_HEX, "#%02x%02x%02x", u_red, u_grn, u_blu);         <*/
         strlcpy (s_RYB [x_index + x_sub][10], x_hex, LEN_HEX);
      }
   }
   return 0;
}

char
yCOLOR_custom        (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   char        x_base      =   0;
   char        x_index     =   0;
   /*---(clear hexes)--------------------*/
   for (x_index = 0; x_index < MAX_COLOR; ++x_index) {
      strlcpy (s_RYB [x_index][10], "#------"        , LEN_HEX);
   }
   /*---(copy bases)---------------------*/
   for (x_base = 0; x_base < 12; ++x_base) {
      x_index = x_base * 6;
      strlcpy (s_RYB [x_index][10], s_newRYB [x_base], LEN_HEX);
   }
   /*---(interpolate to 360)-------------*/
   x_base  = 2;
   x_index = 8 * 6;
   strlcpy (s_RYB [x_index][10], s_newRYB [x_base], LEN_HEX);
   yCOLOR__interpolate ( 0,  8);
   /*---(interpolate to end)-------------*/
   x_base  = 7;
   x_index = 8 * 6;
   strlcpy (s_RYB [x_index][10], s_newRYB [x_base], LEN_HEX);
   yCOLOR__interpolate ( 8, 11);
   /*---(complete)-----------------------*/
   return 0;
}

char
yCOLOR_init          (char  a_use)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   char        x_ncolor    =   0;
   /*---(setup)--------------------------*/
   yCOLOR_custom ();
   /*---(use)----------------------------*/
   x_ncolor = yCOLOR_use (a_use);
   /*---(counts)-------------------------*/
   s_tcolor = 0;
   for (i = 0; i < MAX_COLOR  ; ++i) {
      if (s_RYB      [i][1][0] == '\0')            break;
      ++s_tcolor;
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
   /*---(complete)-----------------------*/
   return x_ncolor;
}



/*============================--------------------============================*/
/*===----                       color by degree                        ----===*/
/*============================--------------------============================*/
static void      o___BY_DEGREE_______________o (void) {;}

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
   } else if (s_use == YCOLOR_REDBLU) {
      if    (a_deg <    0)  { a_deg  =    0; rc = -rce; }
      if    (a_deg >  240)  { a_deg  =  240; rc = -rce; }
   } else if (s_use == YCOLOR_LARGE || s_use == YCOLOR_GIANT) {
      if    (a_deg < -120)  { a_deg  = -120; rc = -rce; }
      if    (a_deg >  480)  { a_deg  =  480; rc = -rce; }
      a_deg += 120;
   } else {
      a_deg = 0;
      rc = -rce;
   }
   /*---(calculate)----------------------*/
   x_index = a_deg / 10;
   if (s_use == YCOLOR_LARGE)  x_index /= 2;
   if (a_index)  *a_index = x_index;
   /*---(complete)-----------------------*/
   return rc;
}

char         /*--> use degree to set opengl color --------[ ------ [ ------ ]-*/
yCOLOR_deg2color     (int a_deg, float a_alpha)
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

char
yCOLOR_deg2hex       (int a_deg, char *a_hex)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =   0;
   int         x_index     =   0;
   /*---(parse color)--------------------*/
   rc = yCOLOR_deg2index (a_deg, &x_index);
   strlcpy (a_hex, s_colors [x_index].hex, LEN_HEX);
   /*---(complete)-----------------------*/
   return rc;
}

char*        /*--> use degree to retrieve name ----s------[ ------ [ ------ ]-*/
yCOLOR_deg2name      (int a_deg)
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

char         /*--> use color index to set opengl color ---[ ------ [ ------ ]-*/
yCOLOR_num2color     (int a_num, float a_alpha)
{
   /*---(parse color)--------------------*/
   if (a_num <  0       )   a_num = 0;
   if (a_num >= s_ncolor)   a_num = s_ncolor - 1;
   /*---(set color)----------------------*/
   glColor4f   (s_colors [a_num].red, s_colors [a_num].grn, s_colors [a_num].blu, a_alpha);
   /*---(complete)-----------------------*/
   return 0;
}

char*        /*--> use color index to retrieve hex -------[ ------ [ ------ ]-*/
yCOLOR_num2hex       (int a_num)
{
   /*---(parse color)--------------------*/
   if (a_num <  0       )   a_num = 0;
   if (a_num >= s_ncolor)   a_num = s_ncolor - 1;
   /*---(complete)-----------------------*/
   return s_colors [a_num].hex;
}

char*        /*--> use color index to retrieve name ------[ ------ [ ------ ]-*/
yCOLOR_num2name      (int a_num)
{
   /*---(parse color)--------------------*/
   if (a_num <  0       )   a_num = 0;
   if (a_num >= s_ncolor)   a_num = s_ncolor - 1;
   /*---(complete)-----------------------*/
   return s_colors [a_num].name;
}

float        /*--> use color index to retrieve cutoff ----[ ------ [ ------ ]-*/
yCOLOR_num2cutoff    (int a_num)
{
   /*---(parse color)--------------------*/
   if (a_num <  0       )   a_num = 0;
   if (a_num >= s_ncolor)   a_num = s_ncolor - 1;
   /*---(complete)-----------------------*/
   return s_colors [a_num].cut;
}



/*============================--------------------============================*/
/*===----                       color by value                         ----===*/
/*============================--------------------============================*/
static void      o___BY_VALUE________________o (void) {;}

char         /*--> use hex code to set opengl color ------[ ------ [ ------ ]-*/
yCOLOR_val2error     (float a_alpha)
{
   glColor4f (0.998, 0.059, 0.690, a_alpha);
   return 0;
}

char         /*--> use hex code to set opengl color ------[ ------ [ ------ ]-*/
yCOLOR_val2color     (double a_val, float a_alpha)
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
/*===----                       color by hex code                      ----===*/
/*============================--------------------============================*/
static void      o___BY_HEX__________________o (void) {;}

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

char         /*--> use hex code to set opengl color ------[ ------ [ ------ ]-*/
yCOLOR_hex2color     (char *a_hex, float a_alpha)
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
   glColor4f   (x_red, x_grn, x_blu, a_alpha);
   /*---(complete)-----------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR_hex2rgb      (char *a_hex, float *a_red, float *a_grn, float *a_blu)            /* value color component          (0.0-1.0) */
{
   /*---(locals)-----------+-----------+-*/
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   /*---(remove from hex)----------------*/
   x_red = yCOLOR__unhex (a_hex [1], a_hex [2]);
   x_grn = yCOLOR__unhex (a_hex [3], a_hex [4]);
   x_blu = yCOLOR__unhex (a_hex [5], a_hex [6]);
   /*---(return values)------------------*/
   if (a_red)  *a_red = x_red;
   if (a_grn)  *a_grn = x_grn;
   if (a_blu)  *a_blu = x_blu;
   /*---(complete)-----------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yCOLOR_rgb2hex      (char *a_hex, float a_red, float a_grn, float a_blu)            /* value color component          (0.0-1.0) */
{
   /*---(locals)-----------+-----------+-*/
   uchar       x_red       = 0;
   uchar       x_grn       = 0;
   uchar       x_blu       = 0;
   char        x_hex       [LEN_HEX];
   /*---(round to one byte)----------------*/
   x_red = a_red * 255;
   x_grn = a_grn * 255;
   x_blu = a_blu * 255;
   /*---(place into RGB hex)---------------*/
   snprintf (x_hex, LEN_HEX, "#%02x%02x%02x", x_red, x_grn, x_blu);
   if (a_hex)  strlcpy (a_hex, x_hex, LEN_HEX);
   /*---(complete)-----------------------*/
   return 0;
}



/*============================--------------------============================*/
/*===----                             hsv                              ----===*/
/*============================--------------------============================*/
static void      o___BY_HSV__________________o (void) {;}

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
   yCOLOR_hex2rgb  (a_hex, &x_red, &x_grn, &x_blu);
   /*> x_red = yCOLOR__unhex (a_hex [1], a_hex [2]);                                  <* 
    *> x_grn = yCOLOR__unhex (a_hex [3], a_hex [4]);                                  <* 
    *> x_blu = yCOLOR__unhex (a_hex [5], a_hex [6]);                                  <*/
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
   yCOLOR_rgb2hex (a_hex, x_red, x_grn, x_blu);
   /*> /+---(truncate into 0-255)--------------+/                                     <* 
    *> uchar u_red = x_red * 255;                                                     <* 
    *> uchar u_grn = x_grn * 255;                                                     <* 
    *> uchar u_blu = x_blu * 255;                                                     <* 
    *> /+---(place into RGB hex)---------------+/                                     <* 
    *> snprintf(a_hex, LEN_HEX, "#%02x%02x%02x", u_red, u_grn, u_blu);                <*/
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

char       /*=((pUPDATE ]]=========* return  = simple error code              */
yCOLOR_normalize     (char *a_hex, char *a_out)
{
   /*---(locals)-----------+-----------+-*/
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   float       x_squared   = 0.0;
   yCOLOR_hex2rgb (a_hex, &x_red, &x_grn, &x_blu);
   x_squared = (x_red * x_red) + (x_grn * x_grn) + (x_blu * x_blu);
   x_squared = sqrt (x_squared);
   x_red = x_red / x_squared;
   x_grn = x_grn / x_squared;
   x_blu = x_blu / x_squared;
   yCOLOR_rgb2hex (a_out, x_red, x_grn, x_blu);
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
   yCOLOR_hex2rgb (a_hex, &x_red, &x_grn, &x_blu);
   /*> x_red = yCOLOR__unhex (a_hex [1], a_hex [2]);                                  <* 
    *> x_grn = yCOLOR__unhex (a_hex [3], a_hex [4]);                                  <* 
    *> x_blu = yCOLOR__unhex (a_hex [5], a_hex [6]);                                  <*/
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
