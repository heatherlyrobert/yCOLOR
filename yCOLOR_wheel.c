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
   char        name        [LEN_HUND ];
   char        rating;
   char        type        [LEN_LABEL];
   char        bases       [MAX_BASE ][LEN_LABEL];
   char        notes       [LEN_HUND ];
};
tWHEEL    s_wheels      [MAX_WHEEL] = {
   /*     12345678901234567890  rate  --type--  ---120--- ---090--- ---060--- ---030--- || ---000--- ---030--- ---060--- ---090--- ---120--- ---150--- ---180--- ---210--- ---240--- ---270--- ---300--- ---330--- || ---300--- ---330--- ---360--- ---390--- ---420--- ---450--- ---480---   notes---------------------------------- */
   {  0, "paletton_default"    , '-', "roygbm", "õ4a2208","õ641e24","õ7f1a40","õbf0d20",   "õaa3939","õaa6c39","õaa8439","õaa9739","õaaaa39","õ7b9f35","õ2d882d","õ226666","õ2e4272","õ403075","õ592a72","õ882d61",   "õ------","õ7d0c8a","õ3f1959","õ46336c","õ4c4c7f","õ5f5f7f","õ72727f" , "base colors from website defaults"     },
   {  0, "paletton_full"       , '-', "roygbm", "õcc6633","õcc3366","õe01550","õff0033",   "õff0000","õff7400","õffaa00","õffd300","õffff00","õ9fee00","õ00cc00","õ009999","õ1240ab","õ3914af","õ7109aa","õcd0074",   "õ------","õ7d0c8a","õ3f1959","õ46336c","õ4c4c7f","õ5f5f7f","õ727272" , "base colors from website defaults"     },
   {  0, "paletton_adj"        , '-', "roygbm", "õcc6633","õcc3366","õe01550","õff0033",   "õff0000","õff7400","õffaa00","õffd300","õffff00","õ9fee00","õ00cc00","õ009999","õ1f50dd","õ6020ff","õ7109aa","õcd0074",   "õ------","õ7d0c8a","õ3f1959","õ46336c","õ4c4c7f","õ5f5f7f","õ727272" , "base colors from website defaults"     },
   {  0, "original"            , '-', "roygbm", "õ000000","õ000000","õ000000","õ000000",   "õff0000","õff7400","õffaa00","õffd300","õffff00","õ9fee00","õ00cc00","õ009999","õ1240ab","õ3914af","õ7109aa","õcd0074",   "õ------","õ000000","õ000000","õ000000","õ000000","õ000000","õ000000" , "" },
   {  0, "one"                 , '-', "roygbm", "õ99804d","õ8c4d46","õ801a40","õbf0d20",   "õff0000","õff4700","õff7400","õffb900","õffff00","õ7eff00","õ00ff00","õ00867e","õ0000ff","õ3f00bd","õ7e007e","õbd003f",   "õ------","õ530c81","õ3f1959","õ46336c","õ4c4c7f","õ5f5f7f","õ72727f" , "" },
   {  0, "two"                 , '-', "roygbm", "õ99401a","õ8c2c2d","õ801a40","õbf0d20",   "õff0000","õf33d00","õe87a00","õddb700","õd2f500","õ69e000","õ00cc15","õ157b8a","õ2a2aff","õ4d15d4","õ7100aa","õb70055",   "õ------","õ530c81","õ3f1959","õ46336c","õ4c4c7f","õ5f5f7f","õ72727f" , "" },
   {  0, "paletton_old"        , '-', "roygbm", "õ99804d","õ8c4d46","õ801a40","õbf0d20",   "õaa3939","õaa6c39","õaa8439","õaa9739","õaaaa39","õ7b9f35","õ2d882d","õ226666","õ2e4272","õ403075","õ582a72","õ882d61",   "õ------","õ530c81","õ3f1959","õ46336c","õ4c4c7f","õ5f5f7f","õ72727f" , "" },
   {  0, "four"                , '-', "roygbm", "õ4a2208","õ641e24","õ7f1a40","õbf0d20",   "õff0000","õff3f00","õff7f00","õedad00","õdddd00","õ6ee500","õ00ee00","õ00777f","õ0000ff","õ5d00dc","õbb00bb","õdd005d",   "õ------","õ7d0c8a","õ3f1959","õ46336c","õ4c4c7f","õ5f5f7f","õ72727f" , "" },
   {  0, "five"                , 'A', "roygbm", "õ4a2208","õ7a1e24","õaa1a40","õcc0d20",   "õee0000","õee3f00","õee7f00","õd49d00","õbbbb00","õ5dc300","õ00cc00","õ007f99","õ1022ff","õ7f11df","õbb00bb","õd6005f",   "õ------","õ8c0c8c","õ591959","õ52336c","õ4c4c7f","õ5f5f7f","õ72727f" , "" },
   {  0, "five_adj"            , 'A', "roygbm", "õ4a2208","õ7a1e24","õaa1a40","õcc0d20",   "õee0000","õee3f00","õee7f00","õd49d00","õbbbb00","õ5dc300","õ00cc00","õ007f99","õ1022ff","õ4719bf","õ7f117f","õb6083f",   "õ------","õ7f117f","õ591959","õ551f6a","õ52336c","õ4c4c7f","õ5f5f7f" , "" },
   {  0, "six"                 , '-', "roygbm", "õ4a2208","õ641e24","õ7f1a40","õbf0d20",   "õaa0000","õ952000","õ8f4000","õ856000","õ808000","õ5aa500","õ00aa00","õ005050","õ0000aa","õ400095","õ800080","õ900040",   "õ------","õ7d0c8a","õ3f1959","õ46336c","õ4c4c7f","õ5f5f7f","õ72727f" , "" },
   {  0, "seven"               , '-', "roygbm", "õ4a2208","õ641e24","õ7f1a40","õbf0d20",   "õff0000","õff3f00","õff7f00","õedad00","õdddd00","õ6ee500","õ00ee00","õ00777f","õ0000ff","õ5d00dc","õbb00bb","õdd005d",   "õ------","õ7d0c8a","õ3f1959","õ46336c","õ4c4c7f","õ5f5f7f","õ72727f" , "" },
   {  0, "eight"               , 'c', "roygTP", "õ4a2208","õ641e24","õ7f1a40","õbf0d20",   "õc80000","õd53c00","õe27800","õf0b400","õc3d200","õ84cc04","õ3cb40a","õ2b823f","õ1b5174","õ0c20aa","õ600888","õ9c004c",   "õ------","õ7d0c8a","õ3f1959","õ46336c","õ4c4c7f","õ5f5f7f","õ72727f" , "" },
   {  0, "eight_new"           , 'b', "roygTP", "õ4a2208","õ7a1e24","õaa1a40","õcc0d20",   "õee0000","õee3f00","õee7f00","õd49d00","õbbbb00","õ5dc300","õ00cc00","õ059355","õ0a5aaa","õ1022ff","õ5a16a9","õa40b54",   "õ------","õ8c0c8c","õ591959","õ52336c","õ4c4c7f","õ5f5f7f","õ72727f" , "" },
   {  0, "nine"                , '-', "roygbm", "õ4a2208","õ641e24","õ7f1a40","õbf0d20",   "õff0000","õff3f00","õff7f00","õedad00","õdddd00","õ6ee500","õ00ee00","õ00777f","õ0000ff","õ5d00dc","õbb00bb","õdd005d",   "õ------","õ7d0c8a","õ3f1959","õ46336c","õ4c4c7f","õ5f5f7f","õ72727f" , "" },
   { -1, ""                    , '-',"õ------","õ------","õ------","õ------",   "õ------","õ------","õ------","õ------","õ------","õ------","õ------","õ------","õ------","õ------","õ------","õ------",   "õ------","õ------","õ------","õ------","õ------","õ------","õ------" , "base colors from website defaults"     },
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
      strlcpy (s_RYB [i    ][1], "õ------", LEN_LABEL);
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
      ycolor_hex2rgb (s_RYB [(i    ) * 3][1], &r1, &g1, &b1);
      ycolor_hex2rgb (s_RYB [(i + 1) * 3][1], &r2, &g2, &b2);
      /*---(display)---------------------*/
      /*> printf ("   %-15.15s red %6.3f, grn %6.3f, blu %6.3f\n", s_RYB [(i    ) * 3][0], r1, g1, b1);   <*/
      /*> printf ("   %-15.15s red %6.3f, grn %6.3f, blu %6.3f\n", s_RYB [(i + 1) * 3][0], r2, g2, b2);   <*/
      ri = (r2 - r1) / 3.0;
      gi = (g2 - g1) / 3.0;
      bi = (b2 - b1) / 3.0;
      /*> printf ("   -------  red %6.3f, grn %6.3f, blu %6.3f\n", ri, gi, bi);       <*/
      for (j = 1; j < 3; ++j) {
         ycolor_rgb2hex (x_hex, r1 + (ri * j), g1 + (gi * j), b1 + (bi * j));
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

