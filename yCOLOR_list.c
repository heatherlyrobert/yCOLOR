/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



/*==========================---------------------=============================*/
/*===----                        header files                          ----===*/
/*==========================---------------------=============================*/



/*==========================---------------------=============================*/
/*===----                     private variables                        ----===*/
/*==========================---------------------=============================*/
tCOLOR  *my_head = NULL;
tCOLOR  *my_tail = NULL;
tCOLOR  *my_curr = NULL;
int      my_next = 1;



/*==========================---------------------=============================*/
/*===----                 creating/destroying colors                   ----===*/
/*==========================---------------------=============================*/

int        /*=[[ ADD ]]=======* return  = color identifier                    */
yPALETTE_new()               /* PURPOSE = create a new, blank color           */
{
   /*---(create a new object)--------------*/
   tCOLOR *o = NULL;
   o = malloc(sizeof(tCOLOR));
   if (o == NULL) return -1;
   /*---(initialize)-----------------------*/
   my_curr       = o;
   yPALETTE_clear();
   o->iden       = my_next++;
   /*---(update forward links)-------------*/
   if (my_head == NULL) {
      my_head       = o;
      o->prev       = NULL;
   } else {
      o->prev       = my_tail;
      my_tail->next = o;
   }
   o->next       = NULL;
   /*---(update backward links)------------*/
   my_tail       = o;
   /*---(prepare translation)--------------*/
   if (yCOLOR__rybindex(120) != 60) yCOLOR__loadryb();
   /*---(complete)-------------------------*/
   return o->iden;
}

char       /*=[[ CLEAR ]]=====* return  = simple error code                   */
yPALETTE_clear()             /* PURPOSE = fully clear/initialize a color      */
{
   /*---(locate the color)-----------------*/
   tCOLOR *o  = my_curr;
   if (o == NULL)          return -1;
   /*---(cstrings)-------------------------*/
   strncpy(DOMINANT_HEX,  "", 10);
   strncpy(BASE    ,  "", 10);
   strncpy(VARIANT ,  "", 10);
   strncpy(NORMED  ,  "", 10);
   strncpy(MOTHERED,  "", 10);
   strncpy(MIXED   ,  "", 10);
   strncpy(CURRENT ,  "", 10);
   strncpy(MODIFIED,  "", 10);
   strncpy(HEX,       "", 10);
   int      i = 0;                         /* loop iterator                   */
   for (i = 0; i < 16; ++i) {
      strncpy(o->var[i], "", 10);
   }
   /*---(color components)-----------------*/
   RED_BYTE = BLU_BYTE = GRN_BYTE = 0;     /* RGB byte fields                 */
   RED      = BLU      = GRN      = 0.0;   /* RGB percentages                 */
   o->rr    = o->yy    = o->bb    = 0.0;   /* RYB percentages                 */
   HUE      = SAT      = VAL      = 0.0;   /* HSV                             */
   HSL_HUE  = HSL_SAT  = HSL_LIG  = 0.0;   /* HSL                             */
   o->ryb_hue      = -1;
   /*---(configuration)--------------------*/
   o->is_ryb       = 0;
   o->curr         = 0;
   o->scheme       = 0;
   o->complement   = 0;
   NORMING         = 0;
   o->variation    = 0;
   o->accenting    = 0;
   o->circle       = ' ';
   /*---(palette)--------------------------*/
   o->scheme_id       = 0;
   o->complement_id   = 0;
   VARIANT_ID      = 0;
   NORMING_ID      = 0;
   o->mothering_id    = 0;
   o->accenting_id    = 0;
   /*---(well)-----------------------------*/
   POSITION        = 0;
   ACCENT          = 0;
   o->its_varied      = 0;
   o->its_normed      = 0;
   o->its_mothered    = 0;
   for (i = 0; i < 20; ++i) {
      o->its_accents[i]  = 0;
   }
   /*---(complete)-------------------------*/
   return 0;
}

char       /*=[[ FIND ]]======* return  = simple error code                   */
yPALETTE_select(             /* PURPOSE = locate an existing color            */
      int       a_color)          /* color identifier                         */
{
   tCOLOR *o = my_head;
   while (o != NULL) {
      if (o->iden == a_color) {
         my_curr = o;
         return o->iden;
      }
      o = o->next;
   }
   my_curr = NULL;
   return -1;
}

tCOLOR*    /*=[[ GET ]]=======* return  = color pointer                       */
yPALETTE__current()          /* PURPOSE = get current color for internal use  */
{
   return my_curr;
}

char       /*=[[ LIST ]]======* return  = simple error code                   */
yPALETTE_list()              /* PURPOSE = list the full set of colors         */
{
   tCOLOR *o = my_head;
   printf("\ncolors-=--------)\n");
   while (o != NULL) {
      if (o == my_curr) printf("  * ");
      else              printf("    ");
      printf("%2d = %s\n", o->iden, DOMINANT_HEX);
      o = o->next;
   }
   printf("-------=--------)\n\n");
   return 0;
}

char       /*=[[ REMOVE ]]====* return  = simple error code                   */
yPALETTE_free()              /* PURPOSE = remove/free the current color       */
{
   /*---(locate the color)-----------------*/
   tCOLOR *o  = my_curr;
   if (o == NULL)          return -1;
   /*---(check for the tail)---------------*/
   if (o->next == NULL && o->prev == NULL) {
      my_head  = NULL;
      my_tail  = NULL;
   } else if (o->next == NULL) {
      my_tail       = o->prev;             /* get the tail moved              */
      my_tail->next = NULL;                /* fix last node                   */
   } else if (o->prev == NULL) {
      my_head       = o->next;             /* get the head moved              */
      my_head->prev = NULL;                /* fix first node                  */
   } else {
      o->prev->next = o->next;             /* get the tail moved              */
      o->next->prev = o->prev;             /* get the tail moved              */
   }
   /*---(free it up)-----------------------*/
   free(o);
   my_curr = my_head;
   /*---(complete)-------------------------*/
   return  0;
}

char       /*=[[ REMOVE ]]====* return  = simple error code                   */
yPALETTE_free_all()          /* PURPOSE = remove/free all colors              */
{
   tCOLOR *o = my_curr = my_head;
   while (o != NULL) {
      yPALETTE_free();
      o = my_curr = my_head;
      /*> o = o->next;                                                                <*/
   }
   my_next = 1;
   return 0;
}



/*=============================== end-of-file ================================*/
