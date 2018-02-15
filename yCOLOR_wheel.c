/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"

//  a  vlllllllll"Byjjj
//  c  VdkkkkkpkvlllllllllllllllllllllllllllllllyjPllllllllllllllllllllllllllllllllllllllllli   i $hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhi   $hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhxxxxxxxxxx$i lA "" },0

#define    MAX_WHEEL      50
#define    MAX_BASE       23
typedef  struct cWHEEL   tWHEEL;
struct cWHEEL {
   int         slot;
   char        name        [LEN_DESC ];
   char        rating;
   char        type        [LEN_LABEL];
   char        bases       [MAX_BASE ][LEN_LABEL];
   char        notes       [LEN_DESC ];
};
tWHEEL    s_wheels      [MAX_WHEEL] = {
   /*     12345678901234567890  rate  --type--  ---120--- ---090--- ---060--- ---030--- || ---000--- ---030--- ---060--- ---090--- ---120--- ---150--- ---180--- ---210--- ---240--- ---270--- ---300--- ---330--- || ---300--- ---330--- ---360--- ---390--- ---420--- ---450--- ---480---   notes---------------------------------- */
   {  0, "paletton_default"    , '-', "roygbm", "#4a2208","#641e24","#7f1a40","#bf0d20",   "#aa3939","#aa6c39","#aa8439","#aa9739","#aaaa39","#7b9f35","#2d882d","#226666","#2e4272","#403075","#592a72","#882d61",   "#------","#7d0c8a","#3f1959","#46336c","#4c4c7f","#5f5f7f","#72727f" , "base colors from website defaults"     },
   {  0, "paletton_full"       , '-', "roygbm", "#cc6633","#cc3366","#e01550","#ff0033",   "#ff0000","#ff7400","#ffaa00","#ffd300","#ffff00","#9fee00","#00cc00","#009999","#1240ab","#3914af","#7109aa","#cd0074",   "#------","#7d0c8a","#3f1959","#46336c","#4c4c7f","#5f5f7f","#727272" , "base colors from website defaults"     },
   {  0, "paletton_adj"        , '-', "roygbm", "#cc6633","#cc3366","#e01550","#ff0033",   "#ff0000","#ff7400","#ffaa00","#ffd300","#ffff00","#9fee00","#00cc00","#009999","#1f50dd","#6020ff","#7109aa","#cd0074",   "#------","#7d0c8a","#3f1959","#46336c","#4c4c7f","#5f5f7f","#727272" , "base colors from website defaults"     },
   {  0, "original"            , '-', "roygbm", "#000000","#000000","#000000","#000000",   "#ff0000","#ff7400","#ffaa00","#ffd300","#ffff00","#9fee00","#00cc00","#009999","#1240ab","#3914af","#7109aa","#cd0074",   "#------","#000000","#000000","#000000","#000000","#000000","#000000" , "" },
   {  0, "one"                 , '-', "roygbm", "#99804d","#8c4d46","#801a40","#bf0d20",   "#ff0000","#ff4700","#ff7400","#ffb900","#ffff00","#7eff00","#00ff00","#00867e","#0000ff","#3f00bd","#7e007e","#bd003f",   "#------","#530c81","#3f1959","#46336c","#4c4c7f","#5f5f7f","#72727f" , "" },
   {  0, "two"                 , '-', "roygbm", "#99401a","#8c2c2d","#801a40","#bf0d20",   "#ff0000","#f33d00","#e87a00","#ddb700","#d2f500","#69e000","#00cc15","#157b8a","#2a2aff","#4d15d4","#7100aa","#b70055",   "#------","#530c81","#3f1959","#46336c","#4c4c7f","#5f5f7f","#72727f" , "" },
   {  0, "paletton_old"        , '-', "roygbm", "#99804d","#8c4d46","#801a40","#bf0d20",   "#aa3939","#aa6c39","#aa8439","#aa9739","#aaaa39","#7b9f35","#2d882d","#226666","#2e4272","#403075","#582a72","#882d61",   "#------","#530c81","#3f1959","#46336c","#4c4c7f","#5f5f7f","#72727f" , "" },
   {  0, "four"                , '-', "roygbm", "#4a2208","#641e24","#7f1a40","#bf0d20",   "#ff0000","#ff3f00","#ff7f00","#edad00","#dddd00","#6ee500","#00ee00","#00777f","#0000ff","#5d00dc","#bb00bb","#dd005d",   "#------","#7d0c8a","#3f1959","#46336c","#4c4c7f","#5f5f7f","#72727f" , "" },
   {  0, "five"                , 'A', "roygbm", "#4a2208","#7a1e24","#aa1a40","#cc0d20",   "#ee0000","#ee3f00","#ee7f00","#d49d00","#bbbb00","#5dc300","#00cc00","#007f99","#1022ff","#7f11df","#bb00bb","#d6005f",   "#------","#8c0c8c","#591959","#52336c","#4c4c7f","#5f5f7f","#72727f" , "" },
   {  0, "five_adj"            , 'A', "roygbm", "#4a2208","#7a1e24","#aa1a40","#cc0d20",   "#ee0000","#ee3f00","#ee7f00","#d49d00","#bbbb00","#5dc300","#00cc00","#007f99","#1022ff","#4719bf","#7f117f","#b6083f",   "#------","#7f117f","#591959","#551f6a","#52336c","#4c4c7f","#5f5f7f" , "" },
   {  0, "six"                 , '-', "roygbm", "#4a2208","#641e24","#7f1a40","#bf0d20",   "#aa0000","#952000","#8f4000","#856000","#808000","#5aa500","#00aa00","#005050","#0000aa","#400095","#800080","#900040",   "#------","#7d0c8a","#3f1959","#46336c","#4c4c7f","#5f5f7f","#72727f" , "" },
   {  0, "seven"               , '-', "roygbm", "#4a2208","#641e24","#7f1a40","#bf0d20",   "#ff0000","#ff3f00","#ff7f00","#edad00","#dddd00","#6ee500","#00ee00","#00777f","#0000ff","#5d00dc","#bb00bb","#dd005d",   "#------","#7d0c8a","#3f1959","#46336c","#4c4c7f","#5f5f7f","#72727f" , "" },
   {  0, "eight"               , 'c', "roygTP", "#4a2208","#641e24","#7f1a40","#bf0d20",   "#c80000","#d53c00","#e27800","#f0b400","#c3d200","#84cc04","#3cb40a","#2b823f","#1b5174","#0c20aa","#600888","#9c004c",   "#------","#7d0c8a","#3f1959","#46336c","#4c4c7f","#5f5f7f","#72727f" , "" },
   {  0, "eight_new"           , 'b', "roygTP", "#4a2208","#7a1e24","#aa1a40","#cc0d20",   "#ee0000","#ee3f00","#ee7f00","#d49d00","#bbbb00","#5dc300","#00cc00","#059355","#0a5aaa","#1022ff","#5a16a9","#a40b54",   "#------","#8c0c8c","#591959","#52336c","#4c4c7f","#5f5f7f","#72727f" , "" },
   {  0, "nine"                , '-', "roygbm", "#4a2208","#641e24","#7f1a40","#bf0d20",   "#ff0000","#ff3f00","#ff7f00","#edad00","#dddd00","#6ee500","#00ee00","#00777f","#0000ff","#5d00dc","#bb00bb","#dd005d",   "#------","#7d0c8a","#3f1959","#46336c","#4c4c7f","#5f5f7f","#72727f" , "" },
   { -1, ""                    , '-',"#------","#------","#------","#------",   "#------","#------","#------","#------","#------","#------","#------","#------","#------","#------","#------","#------",   "#------","#------","#------","#------","#------","#------","#------" , "base colors from website defaults"     },
};
int        s_nwheel   = 0;

char
WHEEL__find             (char *a_name)
{
   char        rce         =  -10;
   char        i           =    0;
   char        n           =   -1;
   --rce;  if (a_name == NULL)  return rce;
   /*> printf ("HARM__find %s\n", a_name);                                            <*/
   for (i = 0; i < s_nwheel; ++i) {
      /*---(filter)----------------------*/
      if (s_wheels [i].name [0] != a_name [0])      continue;
      if (strcmp (s_wheels [i].name, a_name) != 0)  continue;
      /*---(accept)----------------------*/
      n = i;
      break;
   }
   --rce;  if (n < 0)   return rce;
   return n;
}

char
WHEEL_set               (cchar *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   char        j           =    0;
   char        n           =   -1;
   float       r1, g1, b1;
   float       r2, g2, b2;
   float       ri, gi, bi;
   char        x_hex       [LEN_LABEL];
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)  return rce;
   /*---(find harmony)-------------------*/
   n = WHEEL__find (a_name);
   if (n < 0)  return n;
   /*---(set color degree)---------------*/
   myCOLOR.wheel  = n;
   /*---(clear)--------------------------*/
   for (i = 0; i < MAX_COLOR;  ++i) {
      strlcpy (s_RYB [i    ][1], "#------", LEN_LABEL);
   }
   /*---(add bases)----------------------*/
   for (i = 0; i <= MAX_BASE ; ++i) {
      strlcpy (s_RYB [i * 3][1], s_wheels [n].bases [i], LEN_LABEL);
      /*> printf ("color %2d at %3d is %s\n", i, i * 3, s_wheels [0].bases [i], LEN_LABEL);   <*/
   }
   /*---(fill in)------------------------*/
   for (i = 0; i <  MAX_BASE; ++i) {
      /*> printf ("%2d, %2d to %2d ================================\n", i, i * 3, (i + 1) * 3);   <*/
      /*---(switch placeholder)----------*/
      if (i == 15)  strlcpy (s_RYB [16 * 3][1], s_wheels [n].bases [ 4], LEN_LABEL);
      if (i == 16)  strlcpy (s_RYB [16 * 3][1], s_wheels [n].bases [14], LEN_LABEL);
      /*---(normal)----------------------*/
      yCOLOR_hex2rgb (s_RYB [(i    ) * 3][1], &r1, &g1, &b1);
      yCOLOR_hex2rgb (s_RYB [(i + 1) * 3][1], &r2, &g2, &b2);
      /*---(display)---------------------*/
      /*> printf ("   %-15.15s red %6.3f, grn %6.3f, blu %6.3f\n", s_RYB [(i    ) * 3][0], r1, g1, b1);   <*/
      /*> printf ("   %-15.15s red %6.3f, grn %6.3f, blu %6.3f\n", s_RYB [(i + 1) * 3][0], r2, g2, b2);   <*/
      ri = (r2 - r1) / 3.0;
      gi = (g2 - g1) / 3.0;
      bi = (b2 - b1) / 3.0;
      /*> printf ("   -------  red %6.3f, grn %6.3f, blu %6.3f\n", ri, gi, bi);       <*/
      for (j = 1; j < 3; ++j) {
         yCOLOR_rgb2hex (x_hex, r1 + (ri * j), g1 + (gi * j), b1 + (bi * j));
         strlcpy (s_RYB [(i * 3) + j][1], x_hex, LEN_LABEL);
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
WHEEL_init              (void)
{
   char        i           =    0;
   s_nwheel = 0;
   for (i = 0; i < MAX_WHEEL; ++i) {
      /*---(filter)----------------------*/
      if (s_wheels [i].slot <  0)      break;
      ++s_nwheel;
   }
   /*> WHEEL_set    ("five_adj");                                                     <*/
   return 0;
}

