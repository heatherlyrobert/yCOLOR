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
   char        light;
};
static tCOLOR  s_primary [MAX_PRIMARY] = {
   {  ' ' , "trn" , "transparent"          , -1                    , '-' },
   {  'k' , "blk" , "black"                , COLOR_BLACK           , '-' },
   {  'r' , "red" , "red"                  , COLOR_RED             , '-' },
   {  'g' , "grn" , "green"                , COLOR_GREEN           , '-' },
   {  'y' , "yel" , "yellow"               , COLOR_YELLOW          , '-' },
   {  'b' , "blu" , "blue"                 , COLOR_BLUE            , '-, '-' ' },
   {  'm' , "mag" , "magenta"              , COLOR_MAGENTA         , '-' },
   {  'c' , "cyn" , "cyan"                 , COLOR_CYAN            , '-' },
   {  'w' , "whi" , "white"                , COLOR_WHITE           , '-' },
   {  'K' , "BLK" , "black"                , COLOR_BLACK           , 'y' },
   {  'R' , "RED" , "red"                  , COLOR_RED             , 'y' },
   {  'G' , "GRN" , "green"                , COLOR_GREEN           , 'y' },
   {  'Y' , "YEL" , "yellow"               , COLOR_YELLOW          , 'y' },
   {  'B' , "BLU" , "blue"                 , COLOR_BLUE            , 'y' },
   {  'M' , "MAG" , "magenta"              , COLOR_MAGENTA         , 'y' },
   {  'C' , "CYN" , "cyan"                 , COLOR_CYAN            , 'y' },
   {  'W' , "WHI" , "white"                , COLOR_WHITE           , 'y' },
   {  '-' , "---" , "end-of-colors"        , -1                    , '-' },
};

#define     MAX_NCURSE  100
typedef  struct cCOLOR_INFO  tCOLOR_INFO;
struct cCOLOR_INFO {
   char        terse       [LEN_LABEL];     /* short description              */
   char        abbr;                        /* quick ref                      */
   char        desc        [LEN_HUND ];     /* description/reason             */
   char        fg;                          /* foreground color               */
   char        bg;                          /* background color               */
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
yCOLOR_curs_add           (cchar *a_terse, cchar a_abbr, cchar *a_desc, cchar a_fg, cchar a_bg)
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
   if (a_desc != NULL)  strlcpy (s_curses [n].desc, a_desc, LEN_HUND);
   s_curses [n].fg    = a_fg;
   s_curses [n].bg    = a_bg;
   DEBUG_GRAF  yLOG_char    ("abbr"      , s_curses [n].abbr);
   DEBUG_GRAF  yLOG_value   ("fg"        , s_curses [n].fg);
   DEBUG_GRAF  yLOG_value   ("bg"        , s_curses [n].bg);
   /*---(create)-------------------------*/
   init_pair (n + 20, x_fg, x_bg);
   s_curses [n].value = COLOR_PAIR (n + 20);
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
   /*---(globals)------------------------*//*-------------------------------------------------fg----bg--*/
   s_ncurse = 0;
   /*---(window parts)-------------------*/
   yCOLOR_curs_add  ("w_titl"    , ' ', "window, normal title"                               , 'k' , 'K' );
   yCOLOR_curs_add  ("w_vers"    , ' ', "window, version number"                             , 'k' , 'K' );
   yCOLOR_curs_add  ("w_sbar"    , ' ', "window, normal status"                              , 'k' , 'y' );
   yCOLOR_curs_add  ("w_cmds"    , ' ', "window, command message"                            , 'y' , ' ' );
   yCOLOR_curs_add  ("w_keys"    , ' ', "window, keystoke display"                           , 'r' , ' ' );
   /*---(trouble)------------------------*/
   yCOLOR_curs_add  ("!_warn"    , 'w', "trouble, warning"                                   , 'w' , 'R' );
   yCOLOR_curs_add  ("!_errs"    , 'E', "trouble, error"                                     , 'W' , 'R' );
   /*---(formula modes)------------------*/
   yCOLOR_curs_add  ("i_maps"    , ' ', "map mode (2d review of sheet/cell collection"       , 'k' , 'Y' );
   yCOLOR_curs_add  ("i_srcs"    , ' ', "source mode (single cell review)"                   , 'k' , 'G' );
   yCOLOR_curs_add  ("i_treg"    , ' ', "text register sub-mode"                             , 'k' , 'C' );
   yCOLOR_curs_add  ("i_inpt"    , ' ', "input sub-mode"                                     , 'k' , 'B' );
   yCOLOR_curs_add  ("i_repl"    , ' ', "replace sub-mode"                                   , 'k' , 'M' );
   yCOLOR_curs_add  ("i_wand"    , ' ', "wander sub-mode"                                    , 'k' , 'R' );
   yCOLOR_curs_add  ("i_sele"    , ' ', "source mode text selection"                         , 'k' , 'W' );
   /*---(visual)---------*/
   yCOLOR_curs_add  ("v_curr"    , ' ', "current cell"                                       , 'k' , 'Y' );
   yCOLOR_curs_add  ("v_root"    , ' ', "root of visual selection"                           , 'Y' , 'k' );
   yCOLOR_curs_add  ("v_fill"    , ' ', "selected, not root/curr"                            , 'Y' , 'y' );
   /*---(marking)--------*/
   yCOLOR_curs_add  ("m_hint"    , ' ', "marks for extended hinting"                         , 'C' , 'c' );
   yCOLOR_curs_add  ("m_temp"    , ' ', "marks for temporary locations"                      , 'Y' , 'y' );
   yCOLOR_curs_add  ("m_srch"    , ' ', "marks for search results"                           , 'R' , 'r' );
   /*---(menus)----------*/
   yCOLOR_curs_add  ("m_menu"    , ' ', "menu, normal item"                                  , 'K' , 'y' );
   yCOLOR_curs_add  ("m_cant"    , ' ', "menu, item not available"                           , 'w' , 'y' );
   yCOLOR_curs_add  ("m_errs"    , ' ', "menu, item in error"                                , 'R' , 'y' );
   /*---(overlays)-------*/
   yCOLOR_curs_add  ("m_main"    , ' ', "note, main title/subject"                           , 'W' , 'M' );
   yCOLOR_curs_add  ("m_warn"    , ' ', "note, displaying a warning"                         , 'W' , 'R' );
   yCOLOR_curs_add  ("m_curr"    , ' ', "note, current note item"                            , 'k' , 'Y' );
   yCOLOR_curs_add  ("m_prev"    , ' ', "note, old note item"                                , 'Y' , 'y' );
   /*---(headers)--------*/
   yCOLOR_curs_add  ("h_curr"    , ' ', "header (row/col) current"                           , 'k' , 'y' );
   yCOLOR_curs_add  ("h_lock"    , ' ', "header (row/col) locked in place"                   , 'k' , 'r' );
   yCOLOR_curs_add  ("h_used"    , ' ', "header (row/col) with used cells"                   , 'y' , 'k' );
   yCOLOR_curs_add  ("h_norm"    , ' ', "header (row/col) normal"                            , 'y' , ' ' );
   /*---(dependencies)---*/
   yCOLOR_curs_add  ("d_reqs"    , ' ', "depends, current cell uses this value"              , 'M' , 'm' );
   yCOLOR_curs_add  ("d_pros"    , ' ', "depends, provides a value to current cell"          , 'G' , 'g' );
   yCOLOR_curs_add  ("d_like"    , ' ', "depends, adapts formula from current cell"          , 'B' , 'b' );
   /*---(cell types)-----*/
   yCOLOR_curs_add  ("9_norm"   , 'n', "numeric, literal"                                    , 'B' , ' ' );
   yCOLOR_curs_add  ("9_form"   , 'f', "numeric, formula"                                    , 'G' , ' ' );
   yCOLOR_curs_add  ("9_dang"   , 'f', "numeric, complex/dangerous formula"                  , 'R' , ' ' );
   yCOLOR_curs_add  ("9_like"   , 'l', "numeric, formula adapted from elsewhere"             , 'w' , ' ' );
   yCOLOR_curs_add  ("#_norm"   , 's', "string, literal"                                     , 'Y' , ' ' );
   yCOLOR_curs_add  ("#_form"   , 'm', "string, formula"                                     , 'M' , ' ' );
   yCOLOR_curs_add  ("#_dang"   , 'm', "string, complex/dangerous formula"                   , 'R' , ' ' );
   yCOLOR_curs_add  ("#_like"   , 'L', "string, formula adapted from elsewhere"              , 'w' , ' ' );
   yCOLOR_curs_add  ("p_rang"   , 'p', "range pointer"                                       , 'C' , ' ' );
   yCOLOR_curs_add  ("p_addr"   , 'p', "address pointer"                                     , 'C' , ' ' );
   /*---(other)----------*/
   yCOLOR_curs_add  (">_null"   , '-', "blank cell"                                          , 'b' , ' ' );
   yCOLOR_curs_add  (">_unkn"   , ' ', "default for unidentified cells"                      , 'Y' , ' ' );
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gc.842.031.62]*/ /*-[02.0000.014.!]-*/ /*-[--.---.---.--]-*/
yCOLOR_curs_wrap          (void)
{
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
   attroff (A_BOLD);
   attroff (A_BLINK);
   if (s_curses [n].fg != tolower (s_curses [n].fg)) attron (A_BOLD);
   if (s_curses [n].bg != tolower (s_curses [n].bg)) attron (A_BLINK);
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

char
yCOLOR_cursx          (char a_fg, char a_bg)
{
   return 0;
}



