/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



/*============================--------------------============================*/
/*===----                           utility                            ----===*/
/*============================--------------------============================*/
static void      o___UTILITY_________________o (void) {;}

static char      yCOLOR_ver [200] = "";



char         /*-> tbd --------------------------------[ shoot  [gc.650.121.32]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_init          (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   char        x_ncolor    =   0;
   /*---(header)-------------------------*/
   DEBUG_YCOLOR   yLOG_enter   (__FUNCTION__);
   /*---(counts)-------------------------*/
   s_tcolor = 0;
   for (i = 0; i < MAX_COLOR  ; ++i) {
      if (s_RYB      [i][1][0] == '\0')            break;
      ++s_tcolor;
   }
   /*> s_nvariant = 0;                                                                <* 
    *> for (i = 0; i < MAX_VARIANT; ++i) {                                            <* 
    *>    if (s_variants [i].abbr [0] == '\0')            break;                      <* 
    *>    ++s_nvariant;                                                               <* 
    *> }                                                                              <*/
   s_nnorming = 0;
   for (i = 0; i < MAX_NORMING; ++i) {
      if (s_normings [i].abbr[0] == '\0') break;
      ++s_nnorming;
   }
   ycolor_palette_init ();
   ycolor_har_init     ();
   ycolor_sat_init     ();
   ycolor_val_init     ();
   WHEEL_init  ();
   myCOLOR.names = '-';
   myCOLOR.extra = '-';
   myCOLOR.conf  = '-';
   /*---(complete)-----------------------*/
   DEBUG_YCOLOR   yLOG_exit    (__FUNCTION__);
   return x_ncolor;
}

char
ycolor_ycmd_labels      (char *a_label)
{
}
