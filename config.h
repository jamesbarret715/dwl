#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */

static const int smartgaps 				   = 0;
static const int monoclegaps 			   = 0;
static const unsigned int borderpx         = 2;  /* border pixel of windows */
static const int gappih 				   = 10;
static const int gappiv 				   = 10;
static const int gappoh 				   = 10;
static const int gappov 				   = 10;

static const int showbar				   = 1;
static const int topbar 				   = 1;
static const int refresh_colors			   = 1;
static const char *colors_file			   = "/home/james/.cache/wal/dwl-colors";

static const char *barlayout               = "t|s";
static const char *fonts[] 				   = {"JetBrainsMono Nerd Font:size=12"};

static const float rootcolor[]             = COLOR(0x222222ff);
static const float fullscreen_bg[]         = COLOR(0x222222ff);

static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
	[SchemeNorm] = { 0xbbbbbbff, 0x222222ff, 0x444444aa },
	[SchemeSel]  = { 0xeeeeeeff, 0x005577ff, 0x666666aa },
	[SchemeUrg]  = { 0,          0,          0x770000aa },
};

/* tagging */
static char *tags[] = { "1", "2", "3" };

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
	/* app_id			title		tags mask	isfloating	monitor */
	{ "menu",  	NULL,       0,       	1,           -1 }, 
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
   /* name		mfact	nmaster	scale	layout			rotate/reflect				x	y */
	{ "eDP-1",	0.55f, 	1,      1.5,  	&layouts[0], 	WL_OUTPUT_TRANSFORM_NORMAL, 0, 0 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	.options = "ctrl:nocaps",
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 1;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;

static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

#define MODKEY WLR_MODIFIER_LOGO

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }

/* commands */

static const Key keys[] = {
	/* modifier                  key                  function          argument */
	{ MODKEY,                    XKB_KEY_Return,      spawn,            SHCMD("foot") },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,      spawn,            SHCMD("librewolf") },
	{ MODKEY,					 XKB_KEY_space,	      spawn,            SHCMD("$HOME/.scripts/launcher") },
	{ MODKEY,                    XKB_KEY_j,           focusstack,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,           focusstack,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_i,           incnmaster,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_d,           incnmaster,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,           setmfact,         {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,           setmfact,         {.f = +0.05f} },
	{ MODKEY,                    XKB_KEY_Tab,         view,             {0} },
	{ MODKEY,					 XKB_KEY_q,           killclient,       {0} },
	{ MODKEY,					 XKB_KEY_c,           reload_colors,    {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_q,           quit,             {0} },

	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),

	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkClient,  	MODKEY,	BTN_LEFT, 	moveresize,    	{.ui = CurMove} },
	{ ClkClient,    MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkClient,    MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkTagBar,    0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,    0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,    MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,    MODKEY, BTN_RIGHT,  toggletag,      {0} },
};
