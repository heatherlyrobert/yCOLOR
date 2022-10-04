/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



#define    MAX_HARMONY    26
typedef  struct cHARMONY  tHARMONY;
struct cHARMONY {
   char        abbr;
   char        name        [LEN_LABEL];
   char        desc        [LEN_HUND ];
   int         comp;
   int         neg;
   int         pos;
};


tHARMONY s_harmony  [MAX_HARMONY] =
{
   /*---   abbr     ---desc-----------------------   comp   neg   pos */
   { 'm', "mono"  , "monochromatic"                ,    0,    0,    0 },
   /*---(complements)--------*/
   { 'c', "comp"  , "complement"                   , -180,    0,    0 },
   { 's', "scomp" , "split complement"             ,    0, -150, +150 },
   { 'd', "dcomp" , "double complement"            , -180,  -30, +150 },
   { 'D', "rcomp" , "double complement (reversed)" , -180, -150,  +30 },
   { 'f', "fcomp" , "full complement"              , -180, -150, +150 },
   { 'w', "wcomp" , "wide complement"              , -180, -120, +120 },
   /*---(triangles)----------*/
   { 'a', "ana"   , "analogous"                    ,    0,  -30,  +30 },
   { 'A', "anac"  , "analogous (comp)"             , -180,  -30,  +30 },
   { '-', "wana"  , "wide analogous"               ,    0,  -60,  +60 },
   { 'Y', "wanac" , "wide analogous (comp)"        , -180,  -60,  +60 },
   { '-', "rana"  , "analogous right"              ,  +30,  -30,  +60 },
   { '-', "lana"  , "analogous left"               ,  -30,  -60,  +30 },
   { ' ', "tana"  , "tee analogous"                ,    0,  -90,  +90 },
   { 'T', "tri"   , "triangle"                     ,    0, -120, +120 },
   /*---(squares)------------*/
   { 'S', "sqr"   , "square"                       , -180,  -90,  +90 },
   { 'r', "rect"  , "rectangle"                    , -180,  -60, +120 },
   { 'R', "mrect" , "rectangle (reversed)"         , -180, -120,  +60 },
   /*---(done)---------------*/
   {  0 , ""      , ""                             ,    0,    0,    0 },
};
int      s_nharmony    = 0;


char
ycolor_degree          (int  a_deg)
{
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   if (a_deg != 666)  myCOLOR.degree = ycolor_deg2fix (a_deg);
   ycolor_harmony ("=");
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycolor_har_by_abbr      (cchar a_abbr)
{
   char        rce         =  -10;
   char        i           =    0;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_senter  (__FUNCTION__);
   DEBUG_YCOLOR   yLOG_sint    (a_abbr);
   /*---(defense)------------------------*/
   --rce;  if (a_abbr <= G_KEY_SPACE) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_abbr >= G_KEY_TILDA) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_schar   (a_abbr);
   /*---(find)---------------------------*/
   for (i = 0; i < s_nharmony; ++i) {
      /*---(filter)----------------------*/
      if (s_harmony [i].abbr != a_abbr)      continue;
      /*---(accept)----------------------*/
      n = i;
      break;
   }
   DEBUG_YCOLOR   yLOG_sint    (n);
   /*---(check for error)----------------*/
   --rce;  if (n < 0) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_sexit   (__FUNCTION__);
   return n;
}

char
ycolor_har_by_name      (cchar *a_name)
{
   char        rce         =  -10;
   char        i           =    0;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCOLOR   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCOLOR   yLOG_snote   (a_name);
   /*---(find)---------------------------*/
   for (i = 0; i < s_nharmony; ++i) {
      /*---(filter)----------------------*/
      if (s_harmony [i].name [0] != a_name [0])      continue;
      if (strcmp (s_harmony [i].name, a_name) != 0)  continue;
      /*---(accept)----------------------*/
      n = i;
      break;
   }
   DEBUG_YCOLOR   yLOG_sint    (n);
   /*---(check for error)----------------*/
   --rce;  if (n < 0) {
      DEBUG_YCOLOR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_sexit   (__FUNCTION__);
   return n;
}

char
ycolor_harmony          (cchar *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(current)------------------------*/
   DEBUG_YCOLOR   yLOG_info    ("saved"     , myCOLOR.harmony);
   DEBUG_YCOLOR   yLOG_value   ("comp"      , myCOLOR.comp);
   DEBUG_YCOLOR   yLOG_value   ("neg"       , myCOLOR.neg);
   DEBUG_YCOLOR   yLOG_value   ("pos"       , myCOLOR.pos);
   /*---(leave alone)--------------------*/
   DEBUG_YCOLOR   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find harmony)-------------------*/
   DEBUG_YCOLOR   yLOG_info    ("a_name"    , a_name);
   if      (strcmp (a_name, "=") == 0)  n = ycolor_har_by_name (myCOLOR.harmony);
   else if (strcmp (a_name, "-") == 0)  n = ycolor_har_by_name ("mono");
   else if (strlen (a_name) == 1)       n = ycolor_har_by_abbr (a_name [0]);
   else                                 n = ycolor_har_by_name (a_name);
   if (n < 0)  {
      DEBUG_YCOLOR   yLOG_exitr   (__FUNCTION__, n);
      return n;
   }
   /*---(set color degree)---------------*/
   strlcpy (myCOLOR.harmony, s_harmony [n].name, LEN_LABEL);
   myCOLOR.comp   = ycolor_deg2fix (myCOLOR.degree + s_harmony [n].comp);
   myCOLOR.neg    = ycolor_deg2fix (myCOLOR.degree + s_harmony [n].neg );
   myCOLOR.pos    = ycolor_deg2fix (myCOLOR.degree + s_harmony [n].pos );
   /*---(display)------------------------*/
   DEBUG_YCOLOR   yLOG_info    ("saved"     , myCOLOR.harmony);
   DEBUG_YCOLOR   yLOG_value   ("comp"      , myCOLOR.comp);
   DEBUG_YCOLOR   yLOG_value   ("neg"       , myCOLOR.neg);
   DEBUG_YCOLOR   yLOG_value   ("pos"       , myCOLOR.pos);
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycolor_har_init               (void)
{
   char        i           =    0;
   s_nharmony = 0;
   for (i = 0; i < MAX_HARMONY; ++i) {
      /*---(filter)----------------------*/
      if (s_harmony [i].abbr == 0)      break;
      ++s_nharmony;
   }
   ycolor_degree  (0);
   ycolor_harmony ("fcomp");
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
   if (a_base != NULL)  *a_base = ycolor_deg2fix (myCOLOR.degree);
   if (a_comp != NULL)  *a_comp = ycolor_deg2fix (myCOLOR.degree + s_harmony [a_seq].comp);
   if (a_neg  != NULL)  *a_neg  = ycolor_deg2fix (myCOLOR.degree + s_harmony [a_seq].neg );
   if (a_pos  != NULL)  *a_pos  = ycolor_deg2fix (myCOLOR.degree + s_harmony [a_seq].pos );
   return 0;
}

