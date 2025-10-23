/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 30;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "CaskaydiaCove Nerd Font Mono:style:Bold:size=27:antialias=true:autohint=true" };
static const char dmenufont[]       = "CaskaydiaCove Nerd Font Mono:style:Bold:size=27";

/* Catppuccin Macchiato core */
static const char col_black[]     = "#000000";
static const char col_base[]      = "#24273a"; /* dark bar/background */
static const char col_mantle[]    = "#1e2030"; /* dark text on accent */
static const char col_surface1[]  = "#363a4f"; /* subtle borders */
static const char col_text[]      = "#cad3f5"; /* normal text */
static const char col_lavender[]  = "#b7bdf8"; /* accent for selected tag and focused border */

static const char *colors[][3] = {
    [SchemeNorm]     = { col_text,  col_black, col_black },
    [SchemeSel]      = { col_text,  col_black, col_black },

    [SchemeStatus]   = { col_text,  col_black, col_black },
    [SchemeTagsNorm] = { col_text,  col_black, col_black },
    [SchemeTagsSel]  = { col_lavender, col_black, col_black },
    [SchemeInfoNorm] = { col_text,  col_black, col_black },
    [SchemeInfoSel]  = { col_text,  col_black, col_black },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact        = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate    = 120;  /* refresh rate (per second) for client move/resize */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	{ "󰕰", tile },      /* tiled */
	{ "󰊠", monocle },   /* monocle */
	{ "󰌶", spiral },    /* spiral */
	{ "󰍉", dwindle },   /* dwindle */
	{ NULL, NULL },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
  "dmenu_run", "-m", dmenumon, "-fn", dmenufont,
  "-nb", col_black,     // background = true black
  "-nf", col_text,      // normal text = Catppuccin text color (#cad3f5)
  "-sb", col_black,     // selected background = black too (no highlight)
  "-sf", col_lavender,  // selected text = Catppuccin lavender accent (#b7bdf8)
  NULL
};
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
static const char *volupcmd[]   = { "sh", "-c", "~/.local/bin/volstep up", NULL };
static const char *voldowncmd[] = { "sh", "-c", "~/.local/bin/volstep down", NULL };
static const char *mutecmd[]    = { "sh", "-c", "~/.local/bin/volstep toggle", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY,                       XK_0,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
	{ MODKEY,                       XK_space,  cyclelayout,    {.i = +1} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY|ControlMask,           XK_a,      spawn,          SHCMD("~/.local/bin/connect-airpods.sh") },
    { MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("~/.local/bin/screenshot") },
    { MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("~/.local/bin/screenshot select") },
    { MODKEY|ControlMask,           XK_l,      spawn,          SHCMD("~/.local/bin/lock-sleep") },
    { 0, XF86XK_AudioRaiseVolume,              spawn,          {.v = volupcmd } },
    { 0, XF86XK_AudioLowerVolume,              spawn,          {.v = voldowncmd } },
    { 0, XF86XK_AudioMute,                     spawn,          {.v = mutecmd } },

    /* tag keys */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
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
