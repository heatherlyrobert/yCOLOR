/*============================----beg-of-source---============================*/
#include    "yCOLOR.h"
#include    "yCOLOR_priv.h"



#define     MAX_PRIMARY    20
typedef  struct cCOLOR  tCOLOR;
struct cCOLOR {
   char        abbr;
   char        terse       [LEN_LABEL];
   char        desc        [LEN_LABEL];
   short       value;
};
static tCOLOR  s_primary [MAX_PRIMARY] = {
   {  ' ' , "trn" , "transparent"          , -1                    },
   {  'k' , "blk" , "black"                , COLOR_BLACK           },
   {  'r' , "red" , "red"                  , COLOR_RED             },
   {  'g' , "grn" , "green"                , COLOR_GREEN           },
   {  'y' , "yel" , "yellow"               , COLOR_YELLOW          },
   {  'b' , "blu" , "blue"                 , COLOR_BLUE            },
   {  'm' , "mag" , "magenta"              , COLOR_MAGENTA         },
   {  'c' , "cyn" , "cyan"                 , COLOR_CYAN            },
   {  'w' , "whi" , "white"                , COLOR_WHITE           },
   {  '-' , "---" , "end-of-colors"        , -1                    },
};

#define     MAX_NCURSE  100
typedef  struct cCOLOR_INFO  tCOLOR_INFO;
struct cCOLOR_INFO {
   char        terse       [LEN_LABEL];     /* short description              */
   char        abbr;                        /* quick ref                      */
   char        desc        [LEN_DESC ];     /* description/reason             */
   char        fg;                          /* foreground color               */
   char        bg;                          /* background color               */
   char        bold;                        /* bold y/n                       */
   int         value;                       /* curses attribute value         */
};
static tCOLOR_INFO  s_curses [MAX_NCURSE];
static int          s_ncurse  = 0;



int          /*-> tbd --------------------------------[ leaf   [gn.422.112.20]*/ /*-[01.0000.015.!]-*/ /*-[--.---.---.--]-*/
CURS__primary             (char a_abbr)
{
   DEBUG_GRAF  yLOG_senter  (__FUNCTION__);
   DEBUG_GRAF  yLOG_schar   (a_abbr);
   int         i           = 0;
   for (i = 0; i < MAX_PRIMARY; ++i) { 
      if (s_primary [i].abbr == '-')              break;
      if (s_primary [i].abbr != a_abbr)           continue;
      DEBUG_GRAF  yLOG_svalue  ("found"     , s_primary [i].value);
      DEBUG_GRAF  yLOG_sinfo   ("name"      , s_primary [i].terse);
      DEBUG_GRAF  yLOG_sexit   (__FUNCTION__);
      return s_primary [i].value;
   }
   DEBUG_GRAF  yLOG_snote   ("FAIL, not found");
   DEBUG_GRAF  yLOG_sexit   (__FUNCTION__);
   return -2;
}

char
CURS__find                (cchar *a_terse)
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (a_terse == NULL)  return rce;
   for (i = 0; i < s_ncurse; ++i) {
      if (s_curses [i].terse [0] != a_terse [0])       continue;
      if (strcmp (s_curses [i].terse, a_terse) != 0)   continue;
      return i;
   }
   return -1;
}

int          /*-> tbd --------------------------------[ ------ [gc.842.031.62]*/ /*-[02.0000.014.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_curs_add           (cchar *a_terse, cchar a_abbr, cchar *a_desc, cchar a_fg, cchar a_bg, cchar a_bold)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   int         x_fg        =    0;
   int         x_bg        =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_terse == NULL) {
      DEBUG_GRAF  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(identify)-----------------------*/
   n = CURS__find (a_terse);
   if (n <  0) {
      n = s_ncurse;
      DEBUG_GRAF  yLOG_value   ("new"       , n);
   } else {
      DEBUG_GRAF  yLOG_value   ("existing"  , n);
   }
   DEBUG_GRAF  yLOG_info    ("terse"     , a_terse);
   /*---(retrieve primaries)-------------*/
   x_fg = CURS__primary  (a_fg);
   if (x_fg == -2)   x_fg  = CURS__primary  ('w');
   x_bg = CURS__primary  (a_bg);
   if (x_bg == -2)   x_bg  = CURS__primary  (' ');
   /*---(save)---------------------------*/
   strlcpy (s_curses [n].terse, a_terse, LEN_LABEL);
   s_curses [n].abbr  = a_abbr;
   if (a_desc != NULL)  strlcpy (s_curses [n].desc, a_desc, LEN_DESC);
   s_curses [n].fg    = a_fg;
   s_curses [n].bg    = a_bg;
   s_curses [n].bold  = a_bold;
   DEBUG_GRAF  yLOG_char    ("abbr"      , s_curses [n].abbr);
   DEBUG_GRAF  yLOG_value   ("fg"        , s_curses [n].fg);
   DEBUG_GRAF  yLOG_value   ("bg"        , s_curses [n].bg);
   /*---(create)-------------------------*/
   init_pair (n + 20, x_fg, x_bg);
   if (a_bold == 'y') {
      s_curses [n].value = COLOR_PAIR (n + 20) | A_BOLD;
      DEBUG_GRAF  yLOG_value   ("bold"      , s_curses [n].value);
   } else if (a_bold == 'b') {
      s_curses [n].value = COLOR_PAIR (n + 20) | A_BLINK;
      DEBUG_GRAF  yLOG_value   ("blink"     , s_curses [n].value);
   } else {
      s_curses [n].value = COLOR_PAIR (n + 20);
      DEBUG_GRAF  yLOG_value   ("normal"    , s_curses [n].value);
   }
   /*---(update)-------------------------*/
   if (n == s_ncurse)  ++s_ncurse;
   DEBUG_GRAF  yLOG_value   ("s_ncurse"  , s_ncurse);
   /*---(complete)-----------------------*/
   DEBUG_GRAF  yLOG_exit    (__FUNCTION__);
   return  s_curses [n].value;
}

char         /*-> tbd --------------------------------[ ------ [gc.842.031.62]*/ /*-[02.0000.014.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_curs_init          (void)
{
   /*---(globals)------------------------*/
   s_ncurse = 0;
   /*---(window parts)-------------------*/
   yCOLOR_curs_add ("title"    , ' ', "normal title color"                                 , 'k' , 'k' , 'y');
   yCOLOR_curs_add ("version"  , ' ', "version number color"                               , 'k' , 'k' , 'y');
   yCOLOR_curs_add ("status"   , ' ', "normal status color"                                , 'k' , 'y' , '-');
   yCOLOR_curs_add ("command"  , ' ', "window message"                                     , 'y' , ' ' , '-');
   yCOLOR_curs_add ("keys"     , ' ', "window keystoke display"                            , 'r' , ' ' , 'y');
   yCOLOR_curs_add ("menu"     , ' ', "menus and menu entries "                            , 'k' , 'y' , 'b');
   /*---(trouble)------------------------*/
   yCOLOR_curs_add ("warn"     , 'w', "cell warning"                                       , 'w' , 'r' , 'y');
   yCOLOR_curs_add ("error"    , 'E', "cell error"                                         , 'w' , 'r' , 'y');
   yCOLOR_curs_add ("found"    , ' ', "cell found in most recent search"                   , 'g' , 'w' , 'y');
   /*---(formula modes)------------------*/
   yCOLOR_curs_add ("map"      , ' ', "map mode (2d review of sheet/cell collection"       , 'k' , 'y' , 'b');
   yCOLOR_curs_add ("source"   , ' ', "source mode (single cell review)"                   , 'k' , 'g' , 'b');
   yCOLOR_curs_add ("textreg"  , ' ', "text register sub-mode"                             , 'k' , 'c' , 'b');
   yCOLOR_curs_add ("input"    , ' ', "input sub-mode"                                     , 'k' , 'b' , 'b');
   yCOLOR_curs_add ("replace"  , ' ', "replace sub-mode"                                   , 'k' , 'm' , 'b');
   yCOLOR_curs_add ("wander"   , ' ', "wander sub-mode"                                    , 'k' , 'r' , 'b');
   yCOLOR_curs_add ("select"   , ' ', "source mode text selection"                         , 'k' , 'w' , 'b');
   /*---(selection)------*/
   yCOLOR_curs_add ("curr"     , ' ', "current cell"                                       , 'k' , 'y' , 'b');
   yCOLOR_curs_add ("root"     , ' ', "root of visual selection"                           , 'y' , 'k' , 'y');
   yCOLOR_curs_add ("visu"     , ' ', "selected, not root/curr"                            , 'y' , 'y' , 'y');
   yCOLOR_curs_add ("mark"     , ' ', "location marks"                                     , 'w' , 'c' , 'y');
   yCOLOR_curs_add ("srch"     , ' ', "found by search"                                    , 'k' , 'r' , 'y');
   /*---(complete)-----------------------*/
   return 0;
}

int          /*-> return the color value -------------[ leaf   [gn.532.112.30]*/ /*-[01.0000.014.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_curs_value         (cchar *a_terse)
{
   int         n           = 0;
   n = CURS__find (a_terse);
   if (n < 0)  return -1;
   return s_curses [n].value;
}

char
yCOLOR_curs          (cchar *a_terse)
{
   int         n           = 0;
   n = CURS__find (a_terse);
   if (n < 0)  return -1;
   attron  (s_curses [n].value);
}

char
yCOLOR_cursa         (cchar a_abbr)
{
   int         n           = 0;
   for (n = 0; n < s_ncurse; ++n) {
      if (s_curses [n].abbr != a_abbr)  continue;
      attron  (s_curses [n].value);
   }
   return -1;
}



