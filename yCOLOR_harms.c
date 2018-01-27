/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



#define    MAX_HARMONY    26
typedef  struct cHARMONY  tHARMONY;
struct cHARMONY {
   char        abbr;
   char        name        [LEN_LABEL];
   char        desc        [LEN_DESC ];
   int         comp;
   int         neg;
   int         pos;
};


tHARMONY s_harmony  [MAX_HARMONY] =
{
   /*---   abbr     ---desc-----------------------   comp   neg   pos */
   { 'M', "mono"  , "monochromatic"                ,    0,    0,    0 },
   /*---(complements)--------*/
   { 'C', "comp"  , "complement"                   , -180,    0,    0 },
   { 'D', "scomp" , "split/double complement"      ,    0, -150, +150 },
   { 'F', "fcomp" , "full complement"              , -180, -150, +150 },
   { 'W', "wcomp" , "wide complement"              , -180, -120, +120 },
   /*---(triangles)----------*/
   { 'A', "ana"   , "analogous"                    ,    0,  -30,  +30 },
   { 'B', "anac"  , "analogous (comp)"             , -180,  -30,  +30 },
   { ' ', "wana"  , "wide analogous"               ,    0,  -60,  +60 },
   { 'Y', "wanac" , "wide analogous (comp)"        , -180,  -60,  +60 },
   { '-', "rana"  , "analogous right"              ,  +30,  -30,  +60 },
   { '-', "lana"  , "analogous left"               ,  -30,  -60,  +30 },
   { ' ', "tana"  , "tee analogous"                ,    0,  -90,  +90 },
   { 'T', "tri"   , "triangle"                     ,    0, -120, +120 },
   /*---(squares)------------*/
   { 'S', "sqr"   , "square"                       , -180,  -90,  +90 },
   { 'R', "rect"  , "rectangle"                    , -180,  -60, +120 },
   { 'Z', "mrect" , "mirror rectangle"             , -180, -120,  +60 },
   { '-', "pole"  , "narrow rectangle"             , -180,  -30, +150 },
   { '-', "mpole" , "mirror narrow rectangle"      , -180, -150,  +30 },
   /*---(done)---------------*/
   {  0 , ""      , ""                             ,    0,    0,    0 },
};
int      s_nharmony    = 0;

char
HARM_degree          (int  a_deg)
{
   /*> printf ("deg        = %d\n", a_deg);                                           <*/
   myCOLOR.degree = yCOLOR_deg_fix (a_deg);
   HARM_update ();
   /*> printf ("myCOLOR.degree = %d\n", myCOLOR.degree);                              <*/
   return 0;
}

char
HARM__abbr              (char a_abbr)
{
   char        rce         =  -10;
   char        i           =    0;
   char        n           =   -1;
   /*> printf ("HARM__abbr %c\n", a_abbr);                                            <*/
   --rce;  if (a_abbr <= G_KEY_SPACE)  return rce;
   --rce;  if (a_abbr >= G_KEY_TILDA)  return rce;
   for (i = 0; i < s_nharmony; ++i) {
      /*---(filter)----------------------*/
      if (s_harmony [i].abbr != a_abbr)      continue;
      /*---(accept)----------------------*/
      n = i;
      break;
   }
   --rce;  if (n < 0)   return rce;
   strlcpy (myCOLOR.harmony, s_harmony [i].name, LEN_LABEL);
   return n;
}

char
HARM__find              (char *a_name)
{
   char        rce         =  -10;
   char        i           =    0;
   char        n           =   -1;
   char        x_name      [LEN_LABEL];
   --rce;  if (a_name == NULL)  return rce;
   if (strcmp ("--", a_name) == 0)  strlcpy (x_name, myCOLOR.harmony, LEN_LABEL);
   else                             strlcpy (x_name, a_name         , LEN_LABEL);
   /*> printf ("HARM__find %s\n", x_name);                                            <*/
   for (i = 0; i < s_nharmony; ++i) {
      /*---(filter)----------------------*/
      if (s_harmony [i].name [0] != x_name [0])      continue;
      if (strcmp (s_harmony [i].name, x_name) != 0)  continue;
      /*---(accept)----------------------*/
      n = i;
      break;
   }
   --rce;  if (n < 0)   return rce;
   strlcpy (myCOLOR.harmony, s_harmony [i].name, LEN_LABEL);
   return n;
}

char
HARM_set                (char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        n           =   -1;
   /*---(defense)------------------------*/
   if      (a_name == NULL)         n = HARM__find ("--");
   else if (strlen (a_name) == 1)   n = HARM__abbr (a_name [0]);
   else                             n = HARM__find (a_name);
   /*> printf ("HARM_set asked %s, was %s, found %d\n", a_name, myCOLOR.harmony, n);      <*/
   if (n < 0)  return n;
   /*---(set color degree)---------------*/
   myCOLOR.comp   = yCOLOR_deg_fix (myCOLOR.degree + s_harmony [n].comp);
   myCOLOR.neg    = yCOLOR_deg_fix (myCOLOR.degree + s_harmony [n].neg );
   myCOLOR.pos    = yCOLOR_deg_fix (myCOLOR.degree + s_harmony [n].pos );
   /*---(complete)-----------------------*/
   return 0;
}

char
HARM_update             (void)
{
   yCOLOR_deg_fix (myCOLOR.degree);
   HARM_set ("--");
   return 0;
}

char
HARM_init               (void)
{
   char        i           =    0;
   s_nharmony = 0;
   for (i = 0; i < MAX_HARMONY; ++i) {
      /*---(filter)----------------------*/
      if (s_harmony [i].abbr == 0)      break;
      ++s_nharmony;
   }
   return 0;
}

static int  s_curr   =  0;

char
HARM_seq                (int a_seq, char *a_name, char *a_abbr, int *a_base, int *a_comp, int *a_neg, int *a_pos)
{
   char        rce         =  -10;
   --rce;  if (a_seq < 0          )  return rce;
   --rce;  if (a_seq >= s_nharmony)  return rce;
   if (a_name != NULL)  strlcpy (a_name, s_harmony [a_seq].name, LEN_LABEL);
   if (a_abbr != NULL)  *a_abbr = s_harmony [a_seq].abbr;
   if (a_base != NULL)  *a_base = yCOLOR_deg_fix (myCOLOR.degree);
   if (a_comp != NULL)  *a_comp = yCOLOR_deg_fix (myCOLOR.degree + s_harmony [a_seq].comp);
   if (a_neg  != NULL)  *a_neg  = yCOLOR_deg_fix (myCOLOR.degree + s_harmony [a_seq].neg );
   if (a_pos  != NULL)  *a_pos  = yCOLOR_deg_fix (myCOLOR.degree + s_harmony [a_seq].pos );
   return 0;
}

