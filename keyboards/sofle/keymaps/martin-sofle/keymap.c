// STATE = TO VERIFY


 /* Copyright 2021 Dane Evans
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */
  // SOFLE RGB
#include <stdio.h>

#include QMK_KEYBOARD_H

char wpm_str[10];





#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {36+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {36+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
	{36+15, 5, hsv},\
	  {36+22, 3, hsv},\
	  {36+27, 3, hsv}
#define SET_NUMROW(hsv) \
	{10, 2, hsv}, \
		{20, 2, hsv}, \
		{30, 2, hsv}, \
	  {36+ 10, 2, hsv}, \
	  {36+ 20, 2, hsv}, \
	  {36+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
	{33, 4, hsv}, \
	  {36+ 33, 4, hsv}

#define SET_OUTER_COL(hsv) \
	{7, 4, hsv}, \
	  {36+ 7, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
	{25, 2, hsv}, \
	  {36+ 25, 2, hsv}
#define SET_LAYER_ID(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {36+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
		{1, 6, hsv}, \
    {36+1, 6, hsv}, \
		{7, 4, hsv}, \
	  {36+ 7, 4, hsv}, \
		{25, 2, hsv}, \
	  {36+ 25, 2, hsv}


enum sofle_layers {
    _DEFAULTS = 0,
    _BASE = 0,
    _SETTINGS,
	_SYMBOLS,
    _SHORTCUTS,
    _NUMPAD,
    _EXTRAS,
	_BOARD
};






typedef struct {
  bool is_press_action;
  int state;
} tap;

//Define a type for as many tap dance states as you need
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3
};

enum {
  RCTRL_LAYR = 0     //Our custom tap dance key; add any other tap dance keys to this enum 
};

//Declare the functions to be used with your tap dance key(s)

//Function associated with all tap dances
int cur_dance (tap_dance_state_t *state);

//Functions associated with individual tap dances
void rctrl_finished (tap_dance_state_t *state, void *user_data);
void rctrl_reset (tap_dance_state_t *state, void *user_data);




// const ATDD = ACTION_TAP_DANCE_DOUBLE;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
	// 0
	[_BASE] = LAYOUT(
	//+--------------------+------+---------+---------+----------------+--------------------+---------+------+------+---------+--------------------+--------------+---------------+---------+---------+---------+
	          KC_ESC       , KC_1 ,  KC_2   ,  KC_3   ,      KC_4      , LT(_SETTINGS,KC_5) ,                                   LT(_SETTINGS,KC_6) ,     KC_7     ,     KC_8      ,  KC_9   ,  KC_0   , KC_GRV  ,
	//+--------------------+------+---------+---------+----------------+--------------------+---------+------+------+---------+--------------------+--------------+---------------+---------+---------+---------+
	    LT(_NUMPAD,KC_TAB) , KC_Q ,  KC_W   ,  KC_E   ,      KC_R      ,        KC_T        ,                                          KC_Y        ,     KC_U     ,     KC_I      ,  KC_O   ,  KC_P   , KC_BSPC ,
 	//+--------------------+------+---------+---------+----------------+--------------------+---------+------+------+---------+--------------------+--------------+---------------+---------+---------+---------+
	         KC_LSFT       , KC_A ,  KC_S   ,  KC_D   ,      KC_F      ,        KC_G        ,                                          KC_H        ,     KC_J     ,     KC_K      ,  KC_L   , KC_SCLN , KC_QUOT ,
	//+--------------------+------+---------+---------+----------------+--------------------+---------+------+------+---------+--------------------+--------------+---------------+---------+---------+---------+
	         KC_LCTL       , KC_Z ,  KC_X   ,  KC_C   ,      KC_V      ,        KC_B        , KC_MPLY ,               KC_MUTE ,        KC_N        ,     KC_M     ,    KC_COMM    , KC_DOT  , KC_SLSH , KC_RSFT ,
	//+--------------------+------+---------+---------+----------------+--------------------+---------+------+------+---------+--------------------+--------------+---------------+---------+---------+---------+
	                                KC_LALT , KC_LGUI , MO(_SHORTCUTS) ,       KC_SPC       , KC_ENT  ,               KC_ENT  ,        KC_SPC      , MO(_SYMBOLS) , TD(RCTRL_LAYR) , KC_RALT                     
	//+--------------------+------+---------+---------+----------------+--------------------+---------+------+------+---------+--------------------+--------------+---------------+---------+---------+---------+
),

	// 1
	[_SETTINGS] = LAYOUT(
	//+---------+---------+---------+---------+--------------+---------+---------+------+------+---------+---------+----------------+---------+---------+-------+---------+
	    KC_TRNS , BL_DOWN ,  BL_UP  , BL_STEP ,   RGB_HUD    , RGB_HUI ,                                    KC_NO  ,     KC_NO      ,  KC_NO  ,  KC_NO  , KC_NO , KC_TRNS ,
	//+---------+---------+---------+---------+--------------+---------+---------+------+------+---------+---------+----------------+---------+---------+-------+---------+
	    KC_TRNS ,  KC_NO  ,  KC_NO  ,  KC_NO  ,   RGB_RMOD   , RGB_MOD ,                                    KC_NO  ,     KC_NO      , KC_VOLU ,  KC_NO  , KC_NO , KC_TRNS ,
	//+---------+---------+---------+---------+--------------+---------+---------+------+------+---------+---------+----------------+---------+---------+-------+---------+
	    KC_TRNS ,  KC_NO  ,  KC_NO  ,  KC_NO  ,   RGB_SPD    , RGB_SPI ,                                    KC_NO  ,    KC_MPRV     , KC_VOLD ,  KC_MNXT  , KC_NO , KC_TRNS ,
	//+---------+---------+---------+---------+--------------+---------+---------+------+------+---------+---------+----------------+---------+---------+-------+---------+
	    KC_TRNS , RGB_TOG , BL_TOGG ,  KC_NO  ,   RGB_VAD    , RGB_VAI , KC_TRNS ,               KC_TRNS ,  KC_NO  ,     KC_NO      ,  KC_NO  ,  KC_NO  , KC_NO , KC_TRNS ,
	//+---------+---------+---------+---------+--------------+---------+---------+------+------+---------+---------+----------------+---------+---------+-------+---------+
	                        KC_TRNS , KC_TRNS , MO(_SYMBOLS) , KC_TRNS , KC_TRNS ,               KC_MPLY , KC_TRNS , MO(_SHORTCUTS) , KC_TRNS , KC_TRNS                   
	//+---------+---------+---------+---------+--------------+---------+---------+------+------+---------+---------+----------------+---------+---------+-------+---------+
),

	// 2
	[_SYMBOLS] = LAYOUT(
	//+---------+---------+---------+-------------+----------------+-------------+---------+------+------+---------+------------+---------------+--------------+---------------+---------------+---------+
	    KC_TRNS ,  KC_F1  ,  KC_F2  ,    KC_F3    ,      KC_F4     ,     KC_F5   ,                                      KC_F6   ,     KC_F7     ,    KC_F8     ,     KC_F9     ,    KC_F10     , KC_F11  ,
	//+---------+---------+---------+-------------+----------------+-------------+---------+------+------+---------+------------+---------------+--------------+---------------+---------------+---------+
	    KC_TRNS ,  KC_NO  ,  KC_NO  ,    KC_NO    ,      KC_NO     ,     KC_NO   ,                                      KC_5    ,  RALT(KC_5)   ,  RALT(KC_4)  , LSFT(KC_LBRC) ,  RALT(KC_E)   , KC_F12  ,
	//+---------+---------+---------+-------------+----------------+-------------+---------+------+------+---------+------------+---------------+--------------+---------------+---------------+---------+
	    KC_TRNS ,  KC_NO  ,  KC_NO  ,    KC_NO    ,      KC_NO     ,     KC_NO   ,                                     KC_MINS  , RALT(KC_MINS) , RALT(KC_EQL) ,    KC_LBRC    ,    KC_RBRC    , KC_TRNS ,
	//+---------+---------+---------+-------------+----------------+-------------+---------+------+------+---------+------------+---------------+--------------+---------------+---------------+---------+
	    KC_TRNS ,  KC_NO  ,  KC_P1  ,   KC_PSLS   ,     KC_PAST    ,   KC_EQUAL  , KC_TRNS ,               KC_TRNS ,  KC_EQUAL  ,   KC_PPLS     ,   KC_PMNS    ,   RALT(KC_8)  , LSFT(KC_RBRC) , KC_TRNS ,
	//+---------+---------+---------+-------------+----------------+-------------+---------+------+------+---------+------------+---------------+--------------+---------------+---------------+---------+
	                        KC_TRNS ,   KC_TRNS   ,   MO(_EXTRAS)  ,   KC_TRNS   , KC_TRNS ,               KC_TRNS ,   KC_TRNS  ,    KC_TRNS    ,   KC_TRNS    ,    KC_TRNS                              
	//+---------+---------+---------+-------------+----------------+-------------+---------+------+------+---------+------------+---------------+--------------+---------------+---------------+---------+
),

	// 3
	[_SHORTCUTS] = LAYOUT(
	//+---------+------------+------------+------------+------------+---------------+---------+------+------+---------+---------+---------------+---------+---------------+---------------+---------+
	    KC_TRNS ,  KC_TRNS   ,  KC_TRNS   ,  KC_TRNS   ,  KC_TRNS   ,    KC_TRNS    ,                                   KC_TRNS ,    KC_TRNS    , KC_TRNS ,    KC_TRNS    ,    KC_TRNS    , KC_DEL  ,
	//+---------+------------+------------+------------+------------+---------------+---------+------+------+---------+---------+---------------+---------+---------------+---------------+---------+
	    KC_TRNS ,   KC_INS   ,  KC_PSCR   ,   KC_APP   ,   KC_NO    , LCTL(KC_PSLS) ,                                   KC_PGUP , LCTL(KC_LEFT) ,  KC_UP  , LCTL(KC_RGHT) , LCTL(KC_BSPC) , KC_BSPC ,
	//+---------+------------+------------+------------+------------+---------------+---------+------+------+---------+---------+---------------+---------+---------------+---------------+---------+
	    KC_TRNS ,   KC_BSLS  ,  KC_LCTL   ,  KC_LSFT   ,   KC_NO    ,    KC_TRNS    ,                                   KC_PGDN ,    KC_LEFT    , KC_DOWN ,    KC_RGHT    ,    KC_DEL     , KC_BSPC ,
	//+---------+------------+------------+------------+------------+---------------+---------+------+------+---------+---------+---------------+---------+---------------+---------------+---------+
	    KC_LALT , LCTL(KC_Z) , LCTL(KC_X) , LCTL(KC_C) , LCTL(KC_V) ,     KC_NO     , KC_TRNS ,               KC_TRNS ,  KC_NO  ,    KC_HOME    ,  KC_NO  ,    KC_END     ,     KC_NO     , KC_CAPS ,
	//+---------+------------+------------+------------+------------+---------------+---------+------+------+---------+---------+---------------+---------+---------------+---------------+---------+
	                            KC_TRNS   ,  KC_TRNS   ,  KC_TRNS   ,    KC_TRNS    , KC_TRNS ,               KC_TRNS , KC_TRNS ,  MO(_EXTRAS)  , KC_TRNS ,    KC_TRNS                              
	//+---------+------------+------------+------------+------------+---------------+---------+------+------+---------+---------+---------------+---------+---------------+---------------+---------+
),

	// 4
	[_NUMPAD] = LAYOUT(
	//+-------+-------+-------+-------+-------+---------+--------+------+------+--------+---------+-------+---------+-------+-------+---------+
	    KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , QK_BOOT ,                                 KC_PPLS , KC_NO ,  KC_NO  , KC_NO , KC_NO ,  KC_NO  ,
	//+-------+-------+-------+-------+-------+---------+--------+------+------+--------+---------+-------+---------+-------+-------+---------+
	    KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,  KC_NO  ,                                 KC_PMNS , KC_P7 ,  KC_P8  , KC_P9 , KC_NO , KC_BSPC ,
	//+-------+-------+-------+-------+-------+---------+--------+------+------+--------+---------+-------+---------+-------+-------+---------+
	    KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,  KC_NO  ,                                 KC_PAST , KC_P4 ,  KC_P5  , KC_P6 , KC_NO ,  KC_NO  ,
	//+-------+-------+-------+-------+-------+---------+--------+------+------+--------+---------+-------+---------+-------+-------+---------+
	    KC_NO , KC_NO , KC_NO , KC_NO , KC_NO ,  KC_NO  , KC_NO  ,               KC_NO  , KC_PSLS , KC_P1 ,  KC_P2  , KC_P3 , KC_NO ,  KC_NO  ,
	//+-------+-------+-------+-------+-------+---------+--------+------+------+--------+---------+-------+---------+-------+-------+---------+
	                    KC_NO , KC_NO , KC_NO , KC_SPC  , KC_ENT ,               KC_ENT , KC_SPC  , KC_P0 , KC_EQL , KC_PDOT                 
	//+-------+-------+-------+-------+-------+---------+--------+------+------+--------+---------+-------+---------+-------+-------+---------+
),

	// 5
	[_EXTRAS] = LAYOUT(
	//+------------+-------+-------+-------+---------+-------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
	    MO(_BOARD) , KC_NO , KC_NO , KC_NO ,  KC_NO  , KC_NO ,                                   KC_NO     ,  KC_NO  , KC_NO ,     KC_NO     , KC_NO , KC_NO ,
	//+------------+-------+-------+-------+---------+-------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
	      KC_NO    , KC_NO , KC_NO , KC_NO ,  KC_NO  , KC_NO ,                                   KC_NO     ,  KC_NO  , KC_NO ,     KC_NO     , KC_NO , KC_NO ,
	//+------------+-------+-------+-------+---------+-------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
	      KC_NO    , KC_NO , KC_NO , KC_NO ,  KC_NO  , KC_NO ,                               C(G(KC_LEFT)) ,  KC_NO  , KC_NO , C(G(KC_RGHT)) , KC_NO , KC_NO ,
	//+------------+-------+-------+-------+---------+-------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
	      KC_NO    , KC_NO , KC_NO , KC_NO ,  KC_NO  , KC_NO , KC_NO ,               KC_NO ,     KC_NO     ,  KC_NO  , KC_NO ,     KC_NO     , KC_NO , KC_NO ,
	//+------------+-------+-------+-------+---------+-------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
	                         KC_NO , KC_NO , KC_TRNS , KC_NO , KC_NO ,               KC_NO ,     KC_NO     , KC_TRNS , KC_NO ,     KC_NO                     
	//+------------+-------+-------+-------+---------+-------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
),

	// 6
	[_BOARD] = LAYOUT(
	//+-------+-------+-------+-------+---------+---------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
	    KC_NO , KC_NO , KC_NO , KC_NO ,  KC_NO  , EE_CLR  ,                                  QK_BOOT    ,  KC_NO  , KC_NO ,     KC_NO     , KC_NO , KC_NO ,
	//+-------+-------+-------+-------+---------+---------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
	    KC_NO , KC_NO , KC_NO , KC_NO ,  KC_NO  , DB_TOGG ,                                  QK_RBT     ,  KC_NO  , KC_NO ,     KC_NO     , KC_NO , KC_NO ,
	//+-------+-------+-------+-------+---------+---------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
	    KC_NO , KC_NO , KC_NO , KC_NO ,  KC_NO  ,  KC_NO  ,                                   KC_NO     ,  KC_NO  , KC_NO ,     KC_NO     , KC_NO , KC_NO ,
	//+-------+-------+-------+-------+---------+---------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
	    KC_NO , KC_NO , KC_NO , KC_NO ,  KC_NO  ,  KC_NO  , KC_NO ,               KC_NO ,     KC_NO     ,  KC_NO  , KC_NO ,     KC_NO     , KC_NO , KC_NO ,
	//+-------+-------+-------+-------+---------+---------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
	                    KC_NO , KC_NO ,  KC_NO  ,  KC_NO  , KC_NO ,               KC_NO ,     KC_NO     ,  KC_NO  , KC_NO ,     KC_NO                     
	//+-------+-------+-------+-------+---------+---------+-------+------+------+-------+---------------+---------+-------+---------------+-------+-------+
	
)

};

/* keymap ugly format
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        
[0] = LAYOUT(
KC_ESC, KC_1, KC_2, KC_3, KC_4, LT(1,KC_6), LT(1,KC_6), KC_7, KC_8, KC_9, KC_0, KC_BSPC, LT(4,KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_GRV, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MPLY, KC_MUTE, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LALT, KC_LGUI, MO(3), KC_SPC, KC_ENT, KC_SPC, KC_ENT, MO(2), KC_RCTL, KC_RALT
),

[1] = LAYOUT(
KC_TRNS, BL_DOWN, BL_UP, BL_STEP, RGB_HUD, RGB_HUI, KC_NO, KC_NO, KC_VOLU, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_MOD, KC_NO, KC_MPRV, KC_VOLD, KC_MNXT, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, RGB_SPD, RGB_SPI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, RGB_TOG, BL_TOGG, KC_NO, RGB_VAD, RGB_VAI, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, MO(2), KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS, MO(3), KC_TRNS, KC_TRNS
),

[2] = LAYOUT(
KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_5, RALT(KC_5), RALT(KC_4), LSFT(KC_LBRC), RALT(KC_E), KC_F12, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_MINS, RALT(KC_MINS), RALT(KC_EQL), KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_NO, KC_P1, KC_PLUS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, LSFT(KC_RBRC), KC_TRNS, KC_TRNS, KC_TRNS, MO(5), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[3] = LAYOUT(
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_PSCR, KC_APP, KC_NO, KC_NO, KC_PGUP, LCTL(KC_LEFT), KC_UP, LCTL(KC_RGHT), LCTL(KC_BSPC), KC_BSPC, KC_TRNS, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_CAPS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL, KC_BSPC, KC_TRNS, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_HOME, KC_NO, KC_END, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(5), KC_TRNS, KC_TRNS
),

[4] = LAYOUT(
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_PPLS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PMNS, KC_P7, KC_P8, KC_P9, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PAST, KC_P4, KC_P5, KC_P6, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSLS, KC_P1, KC_P2, KC_P3, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SPC, KC_ENT, KC_SPC, KC_ENT, KC_P0, KC_PDOT, KC_NO
),

[5] = LAYOUT(
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, C(G(KC_LEFT)), KC_NO, KC_NO, C(G(KC_RGHT)), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO
)
}; 
*/

/* python layout template

keyboard_layouts = {
"sofle":[
    [   0,    1,    2,    3,    4,    5, None, None, None, None,    6,    7,    8,    9,   10,   11],
    [  12,   13,   14,   15,   16,   17, None, None, None, None,   18,   19,   20,   21,   22,   23],
    [  24,   25,   26,   27,   28,   29, None, None, None, None,   30,   31,   32,   33,   34,   35],
    [  36,   37,   38,   39,   40,   41,   42, None, None,   43,   44,   45,   46,   47,   48,   49],
    [None, None,   50,   51,   52,   53,   54, None, None,   55,   56,   57,   58,   59, None, None]
]
}

*/








#ifdef RGBLIGHT_ENABLE

	// https://nest.pijul.com/sunflower/qmk_firmware:main/BYRPMFHCIOX2Y.T6BJIBA
	
    // _BASE = 0,
    // _SETTINGS,
	// _SYMBOLS,
    // _SHORTCUTS,
    // _NUMPAD,
    // _EXTRAS,
	// _BOARD
	
	char layer_state_str[70];
	
	// _BASE,
	const rgblight_segment_t PROGMEM layer_base_lights[] = RGBLIGHT_LAYER_SEGMENTS(
		SET_LAYER_ID(HSV_YELLOW)
	);
	
	// _SETTINGS,
	const rgblight_segment_t PROGMEM layer_settings_lights[] = RGBLIGHT_LAYER_SEGMENTS(
		SET_LAYER_ID(HSV_PINK)
	);
	
	// _SYMBOLS,
	const rgblight_segment_t PROGMEM layer_symbols_lights[] = RGBLIGHT_LAYER_SEGMENTS(
		SET_LAYER_ID(HSV_TEAL)
	);
	
	// _SHORTCUTS,
	const rgblight_segment_t PROGMEM layer_shortcuts_lights[] = RGBLIGHT_LAYER_SEGMENTS(
		SET_LAYER_ID(HSV_GREEN)
	);
	
	// _NUMPAD,
	const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
		SET_LAYER_ID(HSV_PURPLE)
	);
	
	// _EXTRAS,
	const rgblight_segment_t PROGMEM layer_extras_lights[] = RGBLIGHT_LAYER_SEGMENTS(
		SET_LAYER_ID(HSV_ORANGE)
	);
	
	// _BOARD,
	const rgblight_segment_t PROGMEM layer_board_lights[] = RGBLIGHT_LAYER_SEGMENTS(
		SET_LAYER_ID(HSV_WHITE)
	);
	
	const rgblight_segment_t* const my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
		layer_base_lights,
		layer_settings_lights,
		layer_symbols_lights,
		layer_shortcuts_lights,
		layer_numpad_lights,
		layer_extras_lights,
		layer_board_lights
	);
	
	layer_state_t layer_state_set_user(layer_state_t state) {
		rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
		rgblight_set_layer_state(1, layer_state_cmp(state, _SETTINGS));
		rgblight_set_layer_state(2, layer_state_cmp(state, _SYMBOLS));
		rgblight_set_layer_state(3, layer_state_cmp(state, _SHORTCUTS));
		rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
		rgblight_set_layer_state(5, layer_state_cmp(state, _EXTRAS));
		rgblight_set_layer_state(6, layer_state_cmp(state, _BOARD));
		return state;
	}
	
	void keyboard_post_init_user(void) {
		// Enable the LED layers
		rgblight_layers = my_rgb_layers;
		rgblight_mode(10);// haven't found a way to set this in a more useful way
	}
#endif


#ifdef OLED_ENABLE
	static void render_logo(void) {
		static const char PROGMEM raw_logo[] = {
			0,  0,  0,128,192,224,240,120, 56, 60, 28, 14, 14, 14, 14,142, 14, 14, 14, 14, 28, 28, 60,120,240,240,224,128,  0,  0,  0,  0,  0,248,254,255, 15,  1,  0,  0,  0,  0,  0,192,240,248,254,223,255,254,248,224,240,112,112, 56, 56, 61, 31,127,255,252,224,  0,  0, 31, 63,255,252,220,156,254,254,255,255,239,231,227,227,225,225,224,225,231,255,254,252,240,192,128,224,254,255, 31,  7,  0,  0,128,192,241,255,255,223,207,221,252,248,248,240,  0,  0,  0,  0,  0,  0,248,248,252,221,223,207,255,255,249,224,128,  0,  0,
			0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		};
		oled_write_raw_P(raw_logo, sizeof(raw_logo));
	}

	static void print_status_narrow(void) {
		// Print current mode
		oled_write_P(PSTR("\n\n"), false);
		oled_write_ln_P(PSTR("Mastr\nboard"), false);
		//oled_write_ln_P(PSTR("Slave\nboard"), false);

		oled_write_ln_P(PSTR(""), false);

		//snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state)
		
		sprintf(wpm_str, "wpm: %03d", get_current_wpm());
        oled_write(PSTR(wpm_str), false);
		
		oled_write_P(PSTR("\n\n"), false);
		
		// Print current layer
		oled_write_ln_P(PSTR("LAYER"), false);
		switch (get_highest_layer(layer_state)) {
			
			case _BASE:
				oled_write_P(PSTR("Base\n"), false);
				break;
				
			case _SETTINGS:
				oled_write_P(PSTR("Settn\n"), false);
				break;
				
			case _SYMBOLS:
				oled_write_P(PSTR("Symbl\n"), false);
				break;
				
			case _SHORTCUTS:
				oled_write_P(PSTR("Shtct\n"), false);
				break;
				
			case _NUMPAD:
				oled_write_P(PSTR("Nump\n"), false);
				break;
				
			case _EXTRAS:
				oled_write_P(PSTR("Extra\n"), false);
				break;
				
			default:
				oled_write_ln_P(PSTR("Undef\n"), false);
		}
	}

	oled_rotation_t oled_init_user(oled_rotation_t rotation) {
		if (is_keyboard_master()) {
			return OLED_ROTATION_270;
		}else{
			return OLED_ROTATION_270;
		}
		return rotation;
	}

	bool oled_task_user(void) {
		if (is_keyboard_master()) {
			
			switch (get_highest_layer(layer_state)) {
				case _BOARD:
					oled_write_P(PSTR("eeclr\n<-----\nboot\n----->\ndbtog\n<-----\nrbt\n----->\n"), false);
					break;
				default:
					print_status_narrow();
					//render_logo();
			}
			
			
		} else {
			
			switch (get_highest_layer(layer_state)) {
				case _BOARD:
					oled_write_P(PSTR("eeclr\n<----\nboot\n---->\ndbtog\n<----\nrbt\n---->\n"), false);
					break;
				default:
					//print_status_narrow();
					render_logo();
			}
			
		}
		return false;
	}			
#endif


/* //tri layer state
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
*/

/* //process_record_user (customs functions keys)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case KC_COLEMAKDH:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAKDH);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_D_MUTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_MEH));
                register_code(KC_UP);
            } else {
                unregister_mods(mod_config(MOD_MEH));
                unregister_code(KC_UP);
            }
    }
    return true;
}
*/

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}

#endif


//                           tap dance custom
//Determine the current tap dance state
int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 8;
}

//Initialize tap structure associated with example tap dance key
static tap rctrl_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
void rctrl_finished (tap_dance_state_t *state, void *user_data) {
  rctrl_tap_state.state = cur_dance(state);
  switch (rctrl_tap_state.state) {
    case SINGLE_TAP: 
      tap_code(KC_RCTL); 
      break;
    case SINGLE_HOLD: 
      tap_code(KC_RCTL); 
      break;
    case DOUBLE_TAP: 
      layer_on(_SHORTCUTS); 
      break;
  }
}

void rctrl_reset (tap_dance_state_t *state, void *user_data) {
  //if the key was held down and now is released then switch off the layer
  if (rctrl_tap_state.state==DOUBLE_TAP) {
    layer_off(_SHORTCUTS);
  }
  rctrl_tap_state.state = 0;
}

//Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
  //[RCTRL_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, rctrl_finished, rctrl_reset, 275)
  [RCTRL_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctrl_finished, rctrl_reset)
};

