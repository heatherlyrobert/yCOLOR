/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"






const tENTRY table_entry[TABLEMAX] =
{
   { "hex" , "RGB Hex Code"                          },
   { "ryb" , "RYB (Artistic) Angle"                  },
   { "hue" , "RGB (Technical) Angle"                 },
   { "hsl" , "HSL (hue, saturation, and lightness)"  },
   { "hsv" , "HSV (hue, saturation, and value)"      },
   { "rgb" , "RGB (red, green, blue)"                },
   { "eoi" , "end of input"                          },
};

const tVARIATION table_variation[TABLEMAX] =
{
   { "no"      , "none"                        ,   0.00,  0.00,  0.50,  0.50 },
   { "--"      , "default"                     ,   1.00,  0.80,  0.50,  0.50 },
   /*---(full sat)--------------------*/
   { "vi"      , "vivid"                       ,   1.00,  1.00,  0.50,  0.50 },
   { "ba"      , "balanced"                    ,   1.00,  0.80,  0.50,  0.50 },
   { "me"      , "medium"                      ,   1.00,  0.65,  0.50,  0.50 },
   { "da"      , "dark"                        ,   1.00,  0.50,  0.50,  0.50 },
   { "ea"      , "earthy"                      ,   1.00,  0.30,  0.50,  0.50 },
   { "ri"      , "rich"                        ,   1.00,  0.15,  0.50,  0.50 },
   { "de"      , "deep"                        ,   1.00,  0.10,  0.50,  0.50 },
   /*---(strong sat)------------------*/
   { "br"      , "bright"                      ,   0.80,  1.00,  0.50,  0.50 },
   { "ar"      , "artists"                     ,   0.80,  0.80,  0.50,  0.50 },
   { "mo"      , "modern"                      ,   0.70,  0.50,  0.50,  0.50 },
   { "ne"      , "neutral"                     ,   0.70,  0.35,  0.50,  0.50 },
   /*---(moderate sat)----------------*/
   { "ch"      , "chalk"                       ,   0.50,  1.00,  0.50,  0.50 },
   { "pa"      , "pastel"                      ,   0.50,  0.90,  0.50,  0.50 },
   { "xp"      , "csd_pastel"                  ,   0.56,  0.87,  0.50,  0.50 },
   { "op"      , "oil_pastel"                  ,   0.50,  0.75,  0.50,  0.50 },
   { "su"      , "subdued"                     ,   0.50,  0.50,  0.50,  0.50 },
   { "co"      , "cool"                        ,   0.50,  0.30,  0.50,  0.50 },
   /*---(low sat)---------------------*/
   { "pl"      , "pale"                        ,   0.30,  1.00,  0.50,  0.50 },
   { "li"      , "light"                       ,   0.30,  0.70,  0.50,  0.50 },
   { "wa"      , "washout"                     ,   0.30,  0.50,  0.50,  0.50 },
   { "gr"      , "greyish"                     ,   0.30,  0.30,  0.50,  0.50 },
   /*---(nominal sat)-----------------*/
   { "wh"      , "whiteish"                    ,   0.15,  1.00,  0.50,  0.50 },
   /*---(complete)--------------------*/
   { "eoi" , "end of input"                    ,   0.00,  0.00,  0.00,  0.00 }
   /*---(older)-----------------------*/
   /*> { "nn"  , "normal"                      ,   1.000,  0.800,  0.50,  0.50 },     <* 
    *> { "me"  , "medium"                      ,   0.500, -0.220,  0.60,  0.60 },     <* 
    *> { "dk"  , "dark"                        ,   1.000,  0.600,  0.40,  0.40 },     <* 
    *> { "dr"  , "darker"                      ,   1.000,  0.400,  0.25,  0.25 },     <* 
    *> { "dt"  , "darkest"                     ,   1.000,  0.200,  0.10,  0.10 },     <* 
    *> { "cx"  , "contrast max"                ,   1.000,  1.000,  1.00,  1.00 },     <* 
    *> { "ch"  , "contrast high"               ,  -0.100, -0.100,  0.75,  0.75 },     <* 
    *> { "ce"  , "contrast more"               ,  -0.100, -0.100,  0.66,  0.66 },     <* 
    *> { "cs"  , "contrast less"               ,   0.000,  0.000,  0.33,  0.33 },     <* 
    *> { "cw"  , "contrast low"                ,   0.000,  0.000,  0.20,  0.20 },     <* 
    *> { "cn"  , "contrast min"                ,   0.000,  0.000,  0.10,  0.10 },     <* 
    *> { "pk"  , "pastel dark"                 ,  -0.440, -0.440,  0.25,  0.25 },     <* 
    *> { "pr"  , "pastel darker"               ,  -0.440, -0.700,  0.25,  0.25 },     <* 
    *> { "pt"  , "pastel darkest"              ,  -0.440, -0.800,  0.10,  0.10 },     <* 
    *> { "ln"  , "light/pale normal"           ,  -0.750, -0.100,  0.10,  0.10 },     <* 
    *> { "lk"  , "light/pale dark"             ,  -0.750, -0.440,  0.10,  0.10 },     <* 
    *> { "lr"  , "light/pale darker"           ,  -0.750, -0.700,  0.10,  0.10 },     <* 
    *> { "lt"  , "light/pale darkest"          ,  -0.800, -0.800,  0.05,  0.05 },     <* 
    *> { "at"  , "accent on grey light"        ,  -0.950, -0.100,  0.50,  0.50 },     <* 
    *> { "am"  , "accent on grey medium"       ,  -0.950, -0.440,  0.50,  0.50 },     <* 
    *> { "ak"  , "accent on grey dark"         ,  -0.950, -0.800,  0.50,  0.50 },     <* 
    *> { "gt"  , "grey light"                  ,  -0.950, -0.100,  0.10,  0.10 },     <* 
    *> { "gm"  , "grey medium"                 ,  -0.950, -0.440,  0.10,  0.10 },     <* 
    *> { "gk"  , "grey dark"                   ,  -0.950, -0.800,  0.10,  0.10 },     <* 
    *> { "ss"  , "sat less"                    ,  -0.333,  0.000,  0.50,  0.50 },     <* 
    *> { "sw"  , "sat low"                     ,  -0.666,  0.000,  0.50,  0.50 },     <* 
    *> { "sn"  , "sat min"                     ,  -1.000,  0.000,  0.50,  0.50 },     <*/
};

const tNORMING table_norming[TABLEMAX] =
{
   { "no"  , "none"                           , 0.00, 0.00, 0.00, 'n' },
   { "bl"  , "byte_light"                     , 0.05, 0.05, 0.00, 'n' },
   { "bi"  , "byte_intensity"                 , 0.05, 0.10, 0.00, 'n' },
   { "bm"  , "byte_moderate"                  , 0.10, 0.10, 0.00, 'n' },
   { "bh"  , "byte_heavy"                     , 0.20, 0.20, 0.00, 'n' },
   { "bz"  , "byte_intensity_heavy"           , 0.10, 0.20, 0.00, 'n' },
   { "bs"  , "byte_intensity_strong"          , 0.15, 0.30, 0.00, 'n' },
   { "tl"  , "total_light"                    , 0.05, 0.05, 0.00, 'y' },
   { "ti"  , "total_intensity"                , 0.05, 0.10, 0.00, 'y' },
   { "eoi" , "end of input"                   , 0.00, 0.00, 0.00, 'n' }
};

const tSCHEME table_scheme[TABLEMAX] =
{  /*-------------------------------------------------------------------------*
    * all schemes will match the order used on the most beautiful color scheme
    * designer site on the web "colorschemedesigner.com" and therefore the
    * order, for example, accented analogic is key, positive, negative, accent
    */
   /*---(monochrome)-------------------*/
   {"mon"   , "monochromme"                        ,  1, 'y', 'n', { 360,   0 }},
   /*---(complex)----------------------*/
   {"neu"   , "neutral           (+/- 15)"         ,  3, 'y', 'n', { 360,  15, -15,   0 }},
   {"ana"   , "analogic          (+/- 30)"         ,  3, 'y', 'n', { 360,  30, -30,   0 }},
   {"equ"   , "equidistant       (+/- 15,30)"      ,  3, 'y', 'n', { 360,  30, -15,  15, -30,   0 }},
   {"umb"   , "unbrella          (+/- 30,60)"      ,  3, 'y', 'n', { 360,  60, -30,  30, -60,   0 }},
   /*---(not complementable)-----------*/
   {"cla"   , "clash             (+/- 90)"         ,  3, 'n', 'n', { 360, -90,  90,   0 }},
   {"tri"   , "triad             (+/- 120)"        ,  3, 'n', 'n', { 360,-120, 120,   0 }},
   {"tet"   , "tetrad            (+30,comps)"      ,  4, 'n', 'n', { 360,  30,-150, 180,   0 }},
   {"rec"   , "rectangle         (+45,comps)"      ,  4, 'n', 'n', { 360,  45,-135, 180,   0 }},
   {"squ"   , "square            (+90,comps)"      ,  4, 'n', 'n', { 360,  90, -90, 180,   0 }},
   /*---(circles)----------------------*/
   {"cir"   , "circle            (+30s)"           , 12, 'n', 'y', { 360,  30,  60,  90, 120, 150, 180, 210, 240, 270, 300, 330,   0 }},
   {"jum"   , "jumping           (+30s,by 150's)"  , 12, 'n', 'n', { 360, 150, 300,  90, 240,  30, 180, 330, 120, 270,  60, 210,   0 }},
   {"alt"   , "alternating       (+30s,by 180's)"  , 12, 'n', 'n', { 360, 180,  30, 210,  60, 240,  90, 270, 120, 300, 150, 330,   0 }},
   {"hex"   , "full hex          (by 16ths)"       , 16, 'n', 'n', { 360,  22,  45,  67,  90, 112, 135, 157, 180, 202, 225, 247, 270, 292, 315, 337,   0 }},
   {"yaf"   , "yafla             (30, 120, 150)"   ,  8, 'n', 'n', { 360, 120,  30, 150, 180, 210, 330, 240,   0 }},
   /*> {"ana_w" , "analogic wide     (+/- 45)"         ,  3, { 360,  45, -45,   0 }},                            <* 
    *> {"ana_wa", "analogic wide+    (+/- 45,comp)"    ,  4, { 360,  45, -45, 180,   0 }},                       <* 
    *> {"ana_p" , "analogic packed   (+/- 15,30)"      ,  5, { 360, -30,  15, -15,  30,   0 }},                  <* 
    *> {"ana_pa", "analogic packed+  (+/- 15,30,comp)" ,  6, { 360, -30,  15, -15,  30, 180,   0 }},             <* 
    *> {"ana_ps", "analogic packed^  (+/- 15,30,split)",  7, { 360, -30,  15, -15,  30,-150, 150,   0 }},        <* 
    *> {"ana_pf", "analogic packed#  (+/- 15,30,fan)"  ,  8, { 360, -30,  15, -15,  30,-150, 150, 180,   0 }},   <* 
    *> {"ana_c" , "analogic crowded  (+/- 30,60)"      ,  5, { 360, -60,  30, -30,  60,   0 }},                  <* 
    *> {"ana_ca", "analogic crowded+ (+/- 30,60,comp)" ,  6, { 360, -60,  30, -30,  60, 180,   0 }},             <* 
    *> {"ana_cs", "analogic crowded^ (+/- 30,60,split)",  7, { 360, -60,  30, -30,  60,-150, 150,   0 }},        <* 
    *> {"ana_cf", "analogic crowded# (+/- 30,60,fan)"  ,  8, { 360, -60,  30, -30,  60,-150, 150, 180,   0 }},   <*/
   /*---(triads)-----------------------*/
   /*> {"tri_n" , "triad narrow      (+/- 165)"        ,  3, { 360,-165, 165,   0 }},   <*/
   /*---(clash)------------------------*/
   /*---(tetrads)----------------------*/
   /*> {"tet_n" , "tetrad narrow     (+15, comps)"     ,  4, { 360,  15,-165, 180,   0 }},   <* 
    *> {"tet_w" , "tetrad wide       (+45, comps)"     ,  4, { 360,  45,-135, 180,   0 }},   <* 
    *> {"tet_f" , "tetrad four-tone  (+60, comps)"     ,  4, { 360,  60,-120, 180,   0 }},   <* 
    *> {"tet_s" , "tetrad square     (+90, comps)"     ,  4, { 360,  90, -90, 180,   0 }},   <*/
   /*---(circles)----------------------*/
   /*---(others)-----------------------*/
   /*> {"ana_p" , "analogic pack     (+/- 15,30)"      ,{ 360, -30, +15, -15, +30,   0 }},        <* 
    *> {"ana_c" , "analogic crowd    (+/- 15,30,45)"   ,{ 360, -45, +15, -30, +30, -15, +45 }},   <* 
    *> {"ana_w" , "analogic wide     (+/- 30,60)"      ,{ 360, -60, +30, -30, +60,   0 }},        <* 
    *> {"ana_h" , "analogic huge     (+/- 30,60,90)"   ,{ 360, -90, +30, -60, +60, -30, +90 }},   <*/
   {"eoi"   , "end of input"                       ,  0, 'n', 'n', {    0 }},
};

const tCOMP table_comp[TABLEMAX] =
{
   { "b"   , "none"                            ,  0, {   0 }},
   { "c"   , "complement        (+180)"        ,  1, {  180,   0 }},
   { "s"   , "split complement  (+/- 150)"     ,  2, { -150, 150,   0 }},
   { "n"   , "narrow complement (+/- 165)"     ,  2, { -165, 165,   0 }},
   { "f"   , "fan complement    (+/- 150,180)" ,  3, { -150, 150, 180,   0 }},
   { "e"   , "equi complement   (+/- 165,180)" ,  3, { -165, 165, 180,   0 }},
   { "eoi" , "end of input"                    ,  0, {   0 }},
};

const tMOTHER table_mother[TABLEMAX] =
{
   { "no"  , "none"                           , 0.00, 'l' },
   { "ll"  , "linear_light"                   , 0.10, 'l' },
   { "ln"  , "linear_normal"                  , 0.20, 'l' },
   { "lm"  , "linear_moderate"                , 0.30, 'l' },
   { "lh"  , "linear_heavy"                   , 0.40, 'l' },
   { "lt"  , "linear_test"                    , 0.50, 'l' },
   { "lx"  , "linear_max"                     , 0.70, 'l' },
   { "eoi" , "end of input"                   , 0.00, 'n' }
};

const tACCENT table_accent[TABLEMAX] =
{
   { "n"   ,  0, "None"                        },
   { "v"   ,  5, "ColorSchemeDesigner.com"     },
   { "r"   ,  5, "SitePro Color Schemer"       },
   { "e"   , 16, "SitePro plus extended"       },
   { "m"   , 16, "SitePro plus extended with \\n" },
   { "a"   ,  6, "Ascending Variations"        },
   { "d"   ,  6, "Descending Variations"       },
   { "eoi" ,  0, "end of input"                }
};

const tCONTRAST table_contrast[TABLEMAX] =
{
   { "no"      , "none"                        ,   0.00,  0.00,  0.50,  0.50 },
   { "--"      , "default"                     ,   1.00,  0.80,  0.50,  0.50 },
   /*---(full sat)--------------------*/
   { "vi"      , "vivid"                       ,   1.00,  1.00,  0.50,  0.50 },
   { "ba"      , "balanced"                    ,   1.00,  0.80,  0.50,  0.50 },
   { "me"      , "medium"                      ,   1.00,  0.65,  0.50,  0.50 },
   { "da"      , "dark"                        ,   1.00,  0.50,  0.50,  0.50 },
   { "ea"      , "earthy"                      ,   1.00,  0.30,  0.50,  0.50 },
   { "ri"      , "rich"                        ,   1.00,  0.15,  0.50,  0.50 },
   { "de"      , "deep"                        ,   1.00,  0.10,  0.50,  0.50 },
   /*---(strong sat)------------------*/
   { "br"      , "bright"                      ,   0.80,  1.00,  0.50,  0.50 },
   { "ar"      , "artists"                     ,   0.80,  0.80,  0.50,  0.50 },
   { "mo"      , "modern"                      ,   0.70,  0.50,  0.50,  0.50 },
   { "ne"      , "neutral"                     ,   0.70,  0.35,  0.50,  0.50 },
   /*---(moderate sat)----------------*/
   { "ch"      , "chalk"                       ,   0.50,  1.00,  0.50,  0.50 },
   { "pa"      , "pastel"                      ,   0.50,  0.90,  0.50,  0.50 },
   { "xp"      , "csd_pastel"                  ,   0.56,  0.87,  0.50,  0.50 },
   { "op"      , "oil_pastel"                  ,   0.50,  0.75,  0.50,  0.50 },
   { "su"      , "subdued"                     ,   0.50,  0.50,  0.50,  0.50 },
   { "co"      , "cool"                        ,   0.50,  0.30,  0.50,  0.50 },
   /*---(low sat)---------------------*/
   { "pl"      , "pale"                        ,   0.30,  1.00,  0.50,  0.50 },
   { "li"      , "light"                       ,   0.30,  0.70,  0.50,  0.50 },
   { "wa"      , "washout"                     ,   0.30,  0.50,  0.50,  0.50 },
   { "gr"      , "greyish"                     ,   0.30,  0.30,  0.50,  0.50 },
   /*---(nominal sat)-----------------*/
   { "wh"      , "whiteish"                    ,   0.15,  1.00,  0.50,  0.50 },
   /*---(legacy)----------------------*/
   /*---(complete)--------------------*/
   { "eoi"     , "end of input"                ,   0.00,  0.00,  0.00,  0.00 },
   /*---(older)-----------------------*/
   /*> { "nn"  , "normal"                      ,   1.000,  0.800,  0.50,  0.50 },     <* 
    *> { "me"  , "medium"                      ,   0.500, -0.220,  0.60,  0.60 },     <* 
    *> { "dk"  , "dark"                        ,   1.000,  0.600,  0.40,  0.40 },     <* 
    *> { "dr"  , "darker"                      ,   1.000,  0.400,  0.25,  0.25 },     <* 
    *> { "dt"  , "darkest"                     ,   1.000,  0.200,  0.10,  0.10 },     <* 
    *> { "cx"  , "contrast max"                ,   1.000,  1.000,  1.00,  1.00 },     <* 
    *> { "ch"  , "contrast high"               ,  -0.100, -0.100,  0.75,  0.75 },     <* 
    *> { "ce"  , "contrast more"               ,  -0.100, -0.100,  0.66,  0.66 },     <* 
    *> { "cs"  , "contrast less"               ,   0.000,  0.000,  0.33,  0.33 },     <* 
    *> { "cw"  , "contrast low"                ,   0.000,  0.000,  0.20,  0.20 },     <* 
    *> { "cn"  , "contrast min"                ,   0.000,  0.000,  0.10,  0.10 },     <* 
    *> { "pk"  , "pastel dark"                 ,  -0.440, -0.440,  0.25,  0.25 },     <* 
    *> { "pr"  , "pastel darker"               ,  -0.440, -0.700,  0.25,  0.25 },     <* 
    *> { "pt"  , "pastel darkest"              ,  -0.440, -0.800,  0.10,  0.10 },     <* 
    *> { "ln"  , "light/pale normal"           ,  -0.750, -0.100,  0.10,  0.10 },     <* 
    *> { "lk"  , "light/pale dark"             ,  -0.750, -0.440,  0.10,  0.10 },     <* 
    *> { "lr"  , "light/pale darker"           ,  -0.750, -0.700,  0.10,  0.10 },     <* 
    *> { "lt"  , "light/pale darkest"          ,  -0.800, -0.800,  0.05,  0.05 },     <* 
    *> { "at"  , "accent on grey light"        ,  -0.950, -0.100,  0.50,  0.50 },     <* 
    *> { "am"  , "accent on grey medium"       ,  -0.950, -0.440,  0.50,  0.50 },     <* 
    *> { "ak"  , "accent on grey dark"         ,  -0.950, -0.800,  0.50,  0.50 },     <* 
    *> { "gt"  , "grey light"                  ,  -0.950, -0.100,  0.10,  0.10 },     <* 
    *> { "gm"  , "grey medium"                 ,  -0.950, -0.440,  0.10,  0.10 },     <* 
    *> { "gk"  , "grey dark"                   ,  -0.950, -0.800,  0.10,  0.10 },     <* 
    *> { "ss"  , "sat less"                    ,  -0.333,  0.000,  0.50,  0.50 },     <* 
    *> { "sw"  , "sat low"                     ,  -0.666,  0.000,  0.50,  0.50 },     <* 
    *> { "sn"  , "sat min"                     ,  -1.000,  0.000,  0.50,  0.50 },     <*/
};



/*==========================---------------------=============================*/
/*===----                      setting options                         ----===*/
/*==========================---------------------=============================*/

char       /*=((a_set))=======* return  = simple error code                   */
yPALETTE__variant_set(       /* PURPOSE = identify color variation            */
      char   *a_abbrev,           /* variation abbreviation                   */
      int    *a_index)            /* variation id                             */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   *a_index = 0;
   /*---(length defense)-------------------*/
   if (strlen(a_abbrev) != 2)    return -2;
   /*---(local variables)------------------*/
   int       x_variant = 0;                /* variant index (default = 0)     */
   int       i = 0;                        /* loop counter                    */
   /*---(find complement)------------------*/
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_variation[i].abbr, "eoi") == 0)    break;
      if (strcmp(table_variation[i].abbr, a_abbrev) == 0) x_variant = i;
      if (strcmp(table_variation[i].name, a_abbrev) == 0) x_variant = i;
   }
   *a_index = x_variant;
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((c_convert))===* return  = simple error code                   */
yPALETTE__variant_make(      /* PURPOSE = apply a color variation             */
      int       a_index,          /* variation index                          */
      char     *a_hex,            /* rgb three byte hex code        (#rrggbb) */
      char     *a_out)            /* rgb three byte hex code        (#rrggbb) */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                     return -1;
   strncpy(a_out, a_hex, HEXMAX);
   /*---(defense on a_variation)-----------*/
   if (a_index     >= TABLEMAX)       return -2;
   /*---(get the base)---------------------*/
   int    x_rc = 0;
   float  x_hue, x_sat, x_val;
   x_rc = yPALETTE__hex2hsv(a_hex, &x_hue, &x_sat, &x_val);
   if (x_rc != 0) return x_rc;
   /*---(get the modifiers)----------------*/
   float  dsat  = table_variation[a_index].saturation;
   float  dval  = table_variation[a_index].intensity;
   /*---(defense on modifiers)-------------*/
   if (dsat <  0.0 || dsat >  1.0)    return -3;
   if (dval <  0.0 || dval >  1.0)    return -4;
   if (dsat == 0.0 && dval == 0.0)    return  0;  /* avoid rounding errors    */
   /*---(apply the modifiers)--------------*/
   x_rc = yPALETTE__hsv2hex(x_hue, dsat, dval, a_out);
   /*---(complete)-------------------------*/
   return x_rc;
}

char      /*=((a_set))========* return  = simple error code                   */
yPALETTE__norming_set(       /* PURPOSE = set the norming state               */
      char   *a_abbrev,           /* norming abbreviation                     */
      int    *a_index)            /* norming id                               */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   *a_index = 0;
   /*---(length defense)-------------------*/
   if (strlen(a_abbrev) != 2)    return -2;
   /*---(local variables)------------------*/
   int       x_norm    = 0;                /* variant index (default = 0)     */
   int       i = 0;                        /* loop counter                    */
   /*---(find complement)------------------*/
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_norming[i].abbr, "eoi") == 0)      break;
      if (strcmp(table_norming[i].abbr, a_abbrev) == 0)   x_norm = i;
      if (strcmp(table_norming[i].name, a_abbrev) == 0)   x_norm = i;
   }
   *a_index = x_norm;
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((pUPDATE ]]=========* return  = simple error code              */
yPALETTE__norming_make(      /* PURPOSE = level color intensity               */
      int       a_index,          /* norming index                            */
      char     *a_hex,            /* rgb three byte hex code        (#rrggbb) */
      char     *a_out)            /* rgb three byte hex code        (#rrggbb) */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                     return -1;
   strncpy(a_out, a_hex, HEXMAX);
   /*---(brightness)-----------------------*/
   if (a_index     >= TABLEMAX)       return -2;
   float  d_red  = table_norming[a_index].red;
   float  d_grn  = table_norming[a_index].grn;
   float  d_blu  = table_norming[a_index].blu;
   /*> printf("norming [%d]... hsv based = %c\n", a_index, table_norming[a_index].is_value);   <* 
    *> printf("  factor    %5.3fr, %5.3fg, %5.3fb\n", d_red, d_grn, d_blu);                    <*/
   /*> printf("  color     %3dr, %3dg, %3db\n", x_red, x_grn, x_blu);                 <*/
   if (table_norming[a_index].is_value == 'y') {
      float  x_red, x_grn, x_blu;
      yPALETTE__hex2norm(a_hex, &x_red, &x_grn, &x_blu);
      x_red *= d_red;
      x_grn *= d_grn;
      x_blu *= d_blu;
      float  x_norm = 1.000 - x_red - x_grn - x_blu;
      float  x_hue, x_sat, x_val;
      yPALETTE__hex2hsv(a_hex, &x_hue, &x_sat, &x_val);
      yPALETTE__hsv2hex(x_hue, x_sat, x_val * x_norm, a_out);
   } else {
      uchar  x_red, x_grn, x_blu;
      yPALETTE__hex2byte(a_hex, &x_red, &x_grn, &x_blu);
      x_red *= (1.0 - d_red);
      x_grn *= (1.0 - d_grn);
      x_blu *= (1.0 - d_blu);
      /*> printf("  after     %3dr, %3dg, %3db\n", x_red, x_grn, x_blu);                 <*/
      yPALETTE__byte2hex(x_red, x_grn, x_blu, a_out);
      /*> printf("  result    %s\n", a_out);                                             <*/
   }
   /*---(complete)-------------------------*/
   return 0;
}

char      /*=[[ SET ]]========* return  = simple error code                   */
yPALETTE__mothering_set(     /* PURPOSE = set the mothering state             */
      char   *a_abbrev,           /* mothering abbreviation                   */
      int    *a_index)            /* mothering id                             */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   *a_index = 0;
   /*---(length defense)-------------------*/
   if (strlen(a_abbrev) != 2)    return -2;
   /*---(local variables)------------------*/
   int       x_entry   = 0;                /* variant index (default = 0)     */
   int       i = 0;                        /* loop counter                    */
   /*---(find complement)------------------*/
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_mother[i].abbr, "eoi")    == 0) break;
      if (strcmp(table_mother[i].abbr, a_abbrev) == 0) x_entry = i;
   }
   *a_index = x_entry;
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=((p_convert))===* return  = simple error code                   */
yPALETTE__mothering_make(    /* PURPOSE = mix with the mother color           */
      int   a_index,              /* mothering style index                    */
      char *a_mother,             /* mother color                             */
      char *a_base,               /* base/original color                      */
      char *a_mixed)              /* final mixed color                        */
{
   /*---NOTES...
    *    - already have (l) linear, pure mixing
    *    - need to add HSV (h) avg HUE, avg SAT, avg VAL
    *    - need to add max (m) add the two RED and take max with 255, etc.
    */
   /*> printf("starting to mother...\n");                                             <*/
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   /*---(get mothering value)--------------*/
   double mval  = table_mother[a_index].value;
   /*> printf("   using value of %f\n", mval);                                        <*/
   if (mval == 0.0) {
      strncpy(a_mixed, a_base, HEXMAX);
      return 0;
   }
   /*---(parse mother color)---------------*/
   /*> printf("   mother is      %7s at %4.2lf\n", a_mother, mval);                   <*/
   /*> printf("      which means %03dr, %03dg, %03db\n", R_BYTE(a_mother), G_BYTE(a_mother), B_BYTE(a_mother));   <*/
   uchar m_red  = (int) (R_BYTE(a_mother) * mval);
   uchar m_grn  = (int) (G_BYTE(a_mother) * mval);
   uchar m_blu  = (int) (B_BYTE(a_mother) * mval);
   /*> printf("      contributes %03dr, %03dg, %03db\n", m_red, m_grn, m_blu);        <*/
   /*> printf("   base is        %7s at %4.2lf\n", a_base, 1 - mval);                 <*/
   /*> printf("      which means %03dr, %03dg, %03db\n", R_BYTE(a_base), G_BYTE(a_base), B_BYTE(a_base));   <*/
   uchar c_red  = (int) (R_BYTE(a_base) * (1 - mval));
   uchar c_grn  = (int) (G_BYTE(a_base) * (1 - mval));
   uchar c_blu  = (int) (B_BYTE(a_base) * (1 - mval));
   /*> printf("      contributes %03dr, %03dg, %03db\n", c_red, c_grn, c_blu);        <*/
   uchar x_red  = m_red + c_red;
   uchar x_grn  = m_grn + c_grn;
   uchar x_blu  = m_blu + c_blu;
   yPALETTE__byte2hex(x_red, x_grn, x_blu, a_mixed);
   /*> printf("   mixed is       %s\n", a_mixed);                                     <*/
   /*> printf("      which means %03dr, %03dg, %03db\n", x_red, x_grn, x_blu);        <*/
   /*---(complete)-------------------------*/
   return 0;
}

char
yPALETTE_scheme(             /* PURPOSE = set color scheme option             */
      char   *a_scheme,           /* scheme abbrev                            */
      char   *a_mother,           /* mothering abbrev                         */
      char   *a_accenting)        /* accenting abbrev                         */
{
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   yPALETTE__scheme_set(a_scheme, &SCHEME_ID, &COMP_ID);
   yPALETTE__mothering_set(a_mother, &MOTHERING_ID);
   return 0;
}


char       /*=((p_set))=======* return  = simple error code                   */
yPALETTE__scheme_set(        /* PURPOSE = set color scheme option             */
      char   *a_abbrev,           /* scheme abbreviation                      */
      int    *a_scheme,           /* scheme id                                */
      int    *a_comp)             /* comp id                                  */
{
   /*---(defense on my_curr)---------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)                return -1;
   *a_scheme = 0;
   *a_comp   = 0;
   /*---(argument defense)-----------------*/
   if (strlen(a_abbrev) <  3)    return -2;
   if (strlen(a_abbrev) >  5)    return -2;
   if (strlen(a_abbrev) == 4)    return -2;
   /*---(local variables)------------------*/
   char      x_abbr[10] = "";
   int       x_index = 0;                  /* scheme index (default = 0)      */
   int       i = 0;                        /* loop counter                    */
   /*---(scheme first)------------------*/
   x_abbr[0] = a_abbrev[0];
   x_abbr[1] = a_abbrev[1];
   x_abbr[2] = a_abbrev[2];
   x_abbr[3] = '\0';
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_scheme[i].abbr, "eoi")  == 0) break;
      if (strcmp(table_scheme[i].abbr, x_abbr) == 0) x_index = i;
   }
   *a_scheme = x_index;
   /*---(defense)-----------------------*/
   if (table_scheme[x_index].comp == 'n') return 0;
   /*---(next comp)---------------------*/
   if (strlen(a_abbrev) != 5) return 0;
   x_abbr[0] = a_abbrev[4];
   x_abbr[1] = '\0';
   x_index = 0;
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_comp[i].abbr, "eoi")  == 0) break;
      if (strcmp(table_comp[i].abbr, x_abbr) == 0) x_index = i;
   }
   *a_comp  = x_index;
   /*---(complete)-------------------------*/
   return 0;
}

tNORMAL
yPALETTE_well2norm(
      int       a_position,
      int       a_accent)
{
   yPALETTE_well(a_position, a_accent, GEN_HEX);
   yPALETTE__hex2norm(GEN_HEX, &GEN_NORM.red, &GEN_NORM.grn, &GEN_NORM.blu);
   return GEN_NORM;
}

char*
yPALETTE_well2hex(
      int       a_position,
      int       a_accent)
{
   yPALETTE_well(a_position, a_accent, GEN_HEX);
   return GEN_HEX;
}


char
yPALETTE_well(
      int       a_position,
      int       a_accent,
      char     *a_out)
{
   /*---(get color)------------------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)          return -1;
   int x_rc = 0;
   if (x_rc == 0) x_rc = yPALETTE__switch(DOMINANT_HUE, SCHEME_ID, COMP_ID, a_position, &ANGLE);
   if (x_rc == 0) {
      x_rc = yCOLOR_ryb_hex   (ANGLE, BASE);
      if (x_rc == 0) x_rc = yPALETTE__variant_make  (VARIANT_ID,   BASE,    VARIANT);
      if (x_rc == 0) x_rc = yPALETTE__norming_make  (NORMING_ID,   VARIANT, NORMED);
      /*> strncpy(MOTHERED, NORMED,       HEXMAX);                                    <*/
      if (x_rc == 0) x_rc = yPALETTE__mothering_make(MOTHERING_ID, MOTHER,  NORMED,  MOTHERED);
      /*> printf("mothering at %3d giving %7s\n", MOTHERING_ID, MOTHERED);            <*/
   } else {
      ANGLE = 0;
      strncpy(BASE,      "#000000", HEXMAX);
      strncpy(VARIANT,   BASE,      HEXMAX);
      strncpy(NORMED,    BASE,      HEXMAX);
      strncpy(MOTHERED,  BASE,      HEXMAX);
      strncpy(MIXED,     BASE,      HEXMAX);
      a_position = -1;
      x_rc       = 0;
   }
   if (x_rc == 0) {
      strncpy(MIXED   , MOTHERED,     HEXMAX);
      strncpy(a_out   , MIXED,        HEXMAX);
      POSITION = a_position;
      ACCENT   = a_accent;
   }
   return x_rc;
}

char
yPALETTE__switch(
      int       a_dom,
      int       a_scheme,
      int       a_comp,
      int       a_pos,
      int      *a_hue)
{
   /*---(get color)------------------------*/
   tCOLOR *o  = yPALETTE__current();
   if (o == NULL)          return -1;
   /*---(defense)----------------------------*/
   if (a_pos < 0)          return -2;
   /*---(loop through angles)----------------*/
   int    i = 0;
   int    x_next  = table_scheme[a_scheme].angle[i];
   int    x_angle = -1;
   while (x_next != 0) {
      if (i >=  20)       break;
      if (i == a_pos) {
         x_angle = x_next;
         break;
      }
      ++i;
      x_next  = table_scheme[a_scheme].angle[i];
   }
   /*---(loop through angles)----------------*/
   int j = 0;
   if (x_angle == -1) {
      x_next  = table_comp[a_comp].angle[j];
      while (x_next != 0) {
         if (j >= 20)       break;
         if (i + j == a_pos) {
            x_angle = x_next;
            break;
         }
         ++j;
         x_next  = table_comp[a_comp].angle[j];
      }
   }
   /*---(check for position not found)-----*/
   if (x_angle == -1) {
      *a_hue  = 0;
      return -3;
   }
   /*---(fix angle)------------------------*/
   int x_new = (int) (a_dom + x_angle);
   while (x_new < 0)    x_new += 360;
   while (x_new >= 360) x_new -= 360;
   *a_hue = x_new;
   /*---(complete)--------------------------*/
   return 0;
}



/*==========================---------------------=============================*/
/*===----                        list options                          ----===*/
/*==========================---------------------=============================*/

void               /*  return  = none                                         */
yCOLOR_help()      /*  PURPOSE = print the availible schemes                  */
{
   int i = 0;
   printf("yCOLOR -- heatherly color scheming and conversion --------------------------- (start)\n");
   printf("  niche         : gui aesthetics\n");
   printf("  purpose       : provide beautiful, consistent, and aesthetic color combinations\n");
   printf("  type          : shared library\n");
   printf("  base_system   : gnu/linux\n");
   printf("  lang_name     : ansi-c\n");
   printf("  created       : 2009-10\n");
   printf("  author        : the_heatherlys\n");
   printf("  dependencies  : none\n");
   printf("------------------------------------------------------------------------------ (help)\n");
   printf("\n");
   /*---(print entry)----------------------*/
   printf("   color entry options...\n");
   printf("      abbr-- = desc----------------------------------------\n");
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_entry[i].abbr, "eoi") == 0) break;
      printf("      %-6.6s = %-50.50s\n",
            table_entry[i].abbr, table_entry[i].name);
   }
   printf("      ---done with %02d entry options------------------------\n\n", i);
   /*---(print variations)-----------------*/
   printf("   color variation options...\n");
   printf("      abbr-- = desc--------------------------  -sat-  -val-\n");
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_variation[i].abbr, "eoi") == 0) break;
      printf("      %-6.6s = %-30.30s  %4.2fs  %4.2fv\n",
            table_variation[i].abbr, table_variation[i].name,
            table_variation[i].saturation, table_variation[i].intensity);
   }
   printf("      ---done with %02d variation options------  -----  -----\n\n", i);
   /*---(print norming)--------------------*/
   printf("   color norming options...\n");
   printf("      abbr-- = desc----------------------------------------\n");
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_norming[i].abbr, "eoi") == 0) break;
      printf("      %-6.6s = %-35.35s\n",
            table_norming[i].abbr, table_norming[i].name);
   }
   printf("      ---done with %02d norming options----------------------\n\n", i);
   /*---(print schemes)--------------------*/
   printf("   color scheme options...\n");
   printf("      abbr-- = (no) desc-----------------------------------\n");
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_scheme[i].abbr, "eoi") == 0) break;
      printf("      %-6.6s = (%2d) %-35.35s [%c]\n",
            table_scheme[i].abbr, table_scheme[i].count,
            table_scheme[i].name, table_scheme[i].comp);
   }
   printf("      ---done with %02d scheme options-----------------------\n\n", i);
   /*---(print complements)----------------*/
   printf("   color complement options...\n");
   printf("      abbr-- = (no) desc-----------------------------------\n");
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_comp[i].abbr, "eoi") == 0) break;
      printf("      %-6.6s = (%2d) %-35.35s\n",
            table_comp[i].abbr, table_comp[i].count, table_comp[i].name);
   }
   printf("      ---done with %02d complement options-------------------\n\n", i);
   /*---(print mothering)------------------*/
   printf("   color mothering options...\n");
   printf("      abbr-- = desc----------------------------------------\n");
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_mother[i].abbr, "eoi") == 0) break;
      printf("      %-6.6s = %-35.35s\n",
            table_mother[i].abbr, table_mother[i].name);
   }
   printf("      ---done with %02d mother options-----------------------\n\n", i);
   /*---(print variants)-------------------*/
   printf("   color accenting options...\n");
   printf("      abbr-- = desc----------------------------------------\n");
   for (i = 0; i < TABLEMAX; ++i) {
      if (strcmp(table_accent[i].abbr, "eoi") == 0) break;
      printf("      %-6.6s = (%2d) %-35.35s\n",
            table_accent[i].abbr, table_accent[i].count, table_accent[i].name);
   }
   printf("      ---done with %02d accenting options--------------------\n\n", i);
   /*---(complete)-------------------------*/
   printf("------------------------------------------------------------------------------- (end)\n");
   return;
}




/*================================ end-of-file ===============================*/
