/* See LICENSE file for copyright and license details. */
/* key definitions */
#define XF86AudioRaiseVolume 0x1008ff13
#define XF86AudioLowerVolume 0x1008ff11
#define XF86AudioMute 0x1008ff12

/* appearance */
static const unsigned int borderpx = 7; /* border pixel of windows */
static const unsigned int gappx = 6;    /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayonleft =
    0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 1;      /* 0 means bottom bar */
static char font[] = "DejaVu Sans Mono:size=10";
static const char *fonts[] = {font, "Noto Color Emoji:pixelsize=16",
                              "JoyPixels:pixelsize=20",
                              "FontAwesome:style=Regular:pixelsize=20"};
static const char dmenufont[] = "DejaVu Sans Mono:size=10";
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#005577";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

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
static const char *dmenucmd[] = {
    "dmenu_run", "-c",       "-l",  "5",         "-m",  dmenumon,
    "-fn",       dmenufont,  "-nb", normbgcolor, "-nf", normfgcolor,
    "-sb",       selbgcolor, "-sf", selfgcolor,  NULL};
static const char *passmenucmd[] = {
    "passmenu-otp", "-c",       "-l",  "5",         "-m",  dmenumon,
    "-fn",          dmenufont,  "-nb", normbgcolor, "-nf", normfgcolor,
    "-sb",          selbgcolor, "-sf", selfgcolor,  NULL};
static const char *clipmenucmd[] = {
    "clipmenu", "-c",       "-l",  "5",         "-m",  dmenumon,
    "-fn",      dmenufont,  "-nb", normbgcolor, "-nf", normfgcolor,
    "-sb",      selbgcolor, "-sf", selfgcolor,  NULL};
static const char *termcmd[] = {"st", NULL};
static const char *normie_browser[] = {"firefox", "-p", "normie-browsing",
                                       NULL};
static const char *web_browser[] = {"firefox", NULL};
static const char *text_editor[] = {"emacsclient", "-c", "-a", "emacs", NULL};
static const char *task_manager[] = {"st", "-e", "htop", NULL};
static const char *network_manager[] = {"st", "-e", "nmtui", NULL};
static const char *kubernetes_client[] = {"st", "-e", "k9s", NULL};
static const char *calculator[] = {"speedcrunch", NULL};
static const char *file_browser[] = {"st", "-e", "lf", NULL};
static const char *instant_messenger[] = {"telegram-desktop", NULL};
static const char *change_keyboard_layout[] = {"ch-keyboard-layout", NULL};
static const char *increase_volume[] = {"vol-increase", NULL};
static const char *decrease_volume[] = {"vol-decrease", NULL};
static const char *toggle_mute_volume[] = {"vol-mute-toggle", NULL};
static const char *screen_shot_utility[] = {"flameshot", "launcher", NULL};
static const char *lockscreen_cmd[] = {"betterlockscreen", "-l", NULL};
static const char *divar_programs[] = {"divar-programs", NULL};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    {"font", STRING, &font},
    {"dmenufont", STRING, &dmenufont},
    {"color0", STRING, &normbgcolor},
    {"color8", STRING, &normbordercolor},
    {"color7", STRING, &normfgcolor},
    {"color2", STRING, &selbgcolor},
    {"color3", STRING, &selbordercolor},
    {"color7", STRING, &selfgcolor},
    {"borderpx", INTEGER, &borderpx},
    {"snap", INTEGER, &snap},
    {"showbar", INTEGER, &showbar},
    {"topbar", INTEGER, &topbar},
    {"nmaster", INTEGER, &nmaster},
    {"resizehints", INTEGER, &resizehints},
    {"mfact", FLOAT, &mfact},
};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {0, XF86AudioLowerVolume, spawn, {.v = decrease_volume}},
    {0, XF86AudioRaiseVolume, spawn, {.v = increase_volume}},
    {0, XF86AudioMute, spawn, {.v = toggle_mute_volume}},
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY, XK_s, spawn, {.v = passmenucmd}},
    {MODKEY, XK_o, spawn, {.v = clipmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY | ShiftMask, XK_w, spawn, {.v = normie_browser}},
    {MODKEY | ShiftMask, XK_l, spawn, {.v = lockscreen_cmd}},
    {MODKEY, XK_w, spawn, {.v = web_browser}},
    {MODKEY | ShiftMask, XK_p, spawn, {.v = screen_shot_utility}},
    {MODKEY, XK_e, spawn, {.v = text_editor}},
    {MODKEY | ShiftMask, XK_t, spawn, {.v = task_manager}},
    {MODKEY | ShiftMask, XK_k, spawn, {.v = kubernetes_client}},
    {MODKEY | ShiftMask, XK_d, spawn, {.v = divar_programs}},
    {MODKEY, XK_n, spawn, {.v = network_manager}},
    {MODKEY, XK_c, spawn, {.v = calculator}},
    {MODKEY, XK_v, spawn, {.v = file_browser}},
    {MODKEY | ShiftMask, XK_m, spawn, {.v = instant_messenger}},
    {MODKEY, XK_space, spawn, {.v = change_keyboard_layout}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY | ShiftMask, XK_space, setlayout, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_minus, setgaps, {.i = -1}},
    {MODKEY, XK_equal, setgaps, {.i = +1}},
    {MODKEY | ShiftMask, XK_equal, setgaps, {.i = 0}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
    /* signum       function        argument  */
    {1, reload_xresources, {.v = NULL}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
