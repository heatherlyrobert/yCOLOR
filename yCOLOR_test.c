/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



char       /*----: set up program urgents/debugging --------------------------*/
ycolor_unit_quiet       (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yCOLOR_unit" };
   yCOLOR_init ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ycolor_unit_loud        (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yCOLOR_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_name     ("ycolor"       , YURG_ON);
   DEBUG_YCOLOR  yLOG_info     ("yCOLOR"    , yCOLOR_version   ());
   yCOLOR_init ();
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ycolor_unit_end         (void)
{
   yLOGS_end    ();
   return 0;
}

char          unit_answer [ LEN_TEXT ];

char*
ycolor_unit_accessor    (char *a_question, int n)
{
   /*---(defense)-----------------------------------------*/
   if (strcmp (a_question, "palette"  ) == 0) {
      if (n >= 0 && n < MAX_COLOR) {
         if (strcmp (s_palette [n].hex, "") != 0) {
            sprintf(unit_answer, "palette   (%2d) : %-7.7s, %5.3fr, %5.3fg, %5.3fb", n,
                  s_palette [n].hex, s_palette [n].red, s_palette [n].grn, s_palette [n].blu);
         } else {
            sprintf(unit_answer, "palette   (%2d) : ·······, ·.···r, ·.···g, ·.···b", n);
         }
      } else {
         sprintf(unit_answer, "palette   (--) : %d slot out of range", n);
      }
   }
   else if (strcmp (a_question, "sat"      ) == 0) {
      sprintf(unit_answer, "saturation     : %-10.10s, %5.2f", myCOLOR.sat_name, myCOLOR.sat);
   }
   else if (strcmp (a_question, "val"      ) == 0) {
      sprintf(unit_answer, "value          : %-10.10s, %5.2f", myCOLOR.val_name, myCOLOR.val);
   }
   return unit_answer;
}
