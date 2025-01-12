#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 2;        /* vertical padding for statusbar */
static const char *fonts[]          = { "Hack:size=14" };
static const char dmenufont[]       = "Hack:size=14";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#504945";
static const char col_gray3[]       = "#ebdbb2";
static const char col_gray4[]       = "#1d2021";
static const char col_cyan[]        = "#ebdbb2";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* User Defined Functions */
static const char *firefox[] = {"firefox", NULL};
static const char *ranger[] = {"st", "ranger", NULL};
static const char *ncmpcpp[] = {"st","ncmpcpp", NULL};
static const char *brightnessup[] = {"xbacklight", "-inc", "5", NULL};
static const char *brightnessdown[] = {"xbacklight", "-dec", "5", NULL};
static const char *volup[] = {"pactl", "set-sink-volume", "0","+5%", NULL};
static const char *voldown[] = {"pactl", "set-sink-volume", "0", "-5%", NULL};
static const char *volmute[] = {"pactl", "set-sink-mute", "0", "toggle", NULL};
static const char *playpause[] = {"mpc", "toggle", NULL};



/* tagging */
static const char *tags[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 "};
static const char *alttags[] = { "[1]", "[2]", "[3]", "[4]", "[5]", "[6]"};

static const char *tagsel[][2][2] = {
	/*      norm                          sel       */
	/*  fg          bg              fg          bg  */
	{ { "#cc241d", "#fb4934" }, { col_gray3, "#fb4934" } },
	{ { "#d65d0e", "#fe8019" }, { col_gray3, "#fe8019" } },
	{ { "#d79921", "#fabd2f" }, { col_gray3, "#fabd2f" } },
	{ { "#689d6a", "#8ec07c" }, { col_gray3, "#8ec07c" } },
	{ { "#458588", "#83a598" }, { col_gray3, "#83a598" } },
	{ { "#b16286", "#d3869b" }, { col_gray3, "#d3869b" } },
	{ { "#928374", "#a89984" }, { col_gray3, "#a89984" } },
	{ { "#282828", "#504945" }, { col_gray3, "#504945" } },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_e, spawn,          {.v = ncmpcpp } },
	{ MODKEY,                       XK_r, spawn,          {.v = ranger } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_w,      spawn,          {.v = firefox } },
	{ 0,                            XF86XK_MonBrightnessUp,spawn,{.v = brightnessup } },
	{ 0,                            XF86XK_MonBrightnessDown,spawn,{.v = brightnessdown } },
	{ 0,                       XF86XK_AudioMute,      spawn,          {.v = volmute } },
	{ 0,                       XF86XK_AudioLowerVolume,      spawn,          {.v = voldown } },
	{ 0,                       XF86XK_AudioRaiseVolume,      spawn,          {.v = volup } },
	{ 0,                       XF86XK_AudioPlay,      spawn,          {.v = playpause } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

