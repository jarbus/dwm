/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 0;            /* 0 means bottom bar */
static const int showsystray = 1;
static const int swallowfloating =
    0; /* 1 means swallow floating windows by default */
static const int systrayspacing = 2;
static const int systraypinning = 1;
static const int systraypinningfailfirst = 1;

static const unsigned int gappih = 10; /* horiz inner gap between windows */
static const unsigned int gappiv = 10; /* vert inner gap between windows */
static const unsigned int gappoh =
    10; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov =
    10; /* vert outer gap between windows and screen edge */
static const int smartgaps =
    0; /* 1 means no outer gap when there is only one window */

static const char *fonts[] = {"Unifont:size=24"};
static const char dmenufont[] = "Unifont:size=20";
static const char col_gray1[] = "#000000";
static const char col_gray2[] = "#070B11";
static const char col_gray3[] = "#9099a2";
static const char col_gray4[] = "#ffffff";
static const char col_cyan[] = "#5f8787";
// static const char col_cyan[]        = "#005577";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};
//#9099a2#9099a2

static const char *const autostart[] = {
    "sh", "startup", NULL, NULL /* terminate */
};
/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */

    /* class     instance  title           tags mask  isfloating  isterminal
       noswallow  monitor */
    {"Gimp", NULL, NULL, 0, 1, 0, 0, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, 0, 0, -1},
    /* { "kitty",   NULL,     NULL,           0,         0,          1, 0, -1 },
     */
    {NULL, NULL, "Event Tester", 0, 1, 0, 1, -1}, /* xev */
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle}, {"(@)", spiral}, {"[\\]", dwindle},
};

#include <X11/XF86keysym.h>
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }
/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run","-m",dmenumon, NULL}; //,
// "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf",
// col_gray4, NULL };
static const char *dmenucmd[] = {
    "j4-dmenu-desktop",
    NULL}; //, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb",
           // col_cyan, "-sf", col_gray4, NULL };
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL}; //,
// "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf",
// col_gray4, NULL };
static const char *termcmd[] = {"kitty", NULL};

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY | ShiftMask, XK_d, spawn, SHCMD("dicclip")},
    {MODKEY, XK_q, spawn, SHCMD("qutebrowser")},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_o, spawn, SHCMD("screenshot-ocr")},
    //{MODKEY, XK_o, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_q, killclient, {0}},
    {MODKEY, XK_v, spawn, SHCMD("open-selection-in-vim")},
    {MODKEY, XK_t, spawn, SHCMD("en2es")},
    {MODKEY | ShiftMask, XK_t, spawn, SHCMD("es2en")},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)
    //{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
    // custom commands
    {MODKEY | ShiftMask, XK_m, spawn, SHCMD("automonitor")},
    {MODKEY, XK_p, spawn, SHCMD("passmenu")},
    {MODKEY | ShiftMask, XK_p, spawn, SHCMD("papers")},
    {MODKEY, XK_e, spawn, SHCMD("dmenuunicode -1")},
    {0, XK_F9, spawn,
     SHCMD("brightnessctl set +5% ;kill -45 $(pidof dwmblocks)")},
    {0, XK_F8, spawn,
     SHCMD("brightnessctl set 5%- ;kill -45 $(pidof dwmblocks)")},
    {MODKEY, XK_x, spawn, SHCMD("systemctl suspend")},
    {MODKEY, XK_c, spawn, SHCMD("gnome-screenshot -ic")},
    {MODKEY, XK_equal, spawn,
     SHCMD("pulseaudio-ctl up; kill -44 $(pidof dwmblocks)")},
    {MODKEY, XK_minus, spawn,
     SHCMD("pulseaudio-ctl down; kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_AudioMute, spawn,
     SHCMD("pulseaudio-ctl mute; kill -44 $(pidof dwmblocks)")},

    {0, XF86XK_AudioRaiseVolume, spawn,
     SHCMD("pulseaudio-ctl up; kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_AudioLowerVolume, spawn,
     SHCMD("pulseaudio-ctl down; kill -44 $(pidof dwmblocks)")},

    {MODKEY, XK_r, setlayout, {.v = &layouts[3]}},
    {MODKEY | ShiftMask, XK_r, setlayout, {.v = &layouts[4]}},
    //  { MODKEY,                       XK_s,      spawn, SHCMD("dicmenu") },
    {MODKEY | ShiftMask, XK_s, incrgaps, {.i = -1}},
    {MODKEY, XK_g, togglegaps, {0}},
    {MODKEY | ShiftMask, XK_g, spawn, SHCMD("galaxy")},

    {MODKEY, XK_a, spawn, SHCMD("audioswitch;kill -44 $(pidof dwmblocks)")}

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
