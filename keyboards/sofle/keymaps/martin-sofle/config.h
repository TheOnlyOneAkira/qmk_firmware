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
#pragma once
  
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED D5 // Specify an optional status LED by GPIO number which blinks when entering the bootloader

//#define USE_MATRIX_I2C

/* Select hand configuration */
// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

///https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/

#define CUSTOM_FONT
#define CUSTOM_LAYER_READ //if you remove this it causes issues - needs better guarding

#ifdef TAP_CODE_DELAY
	#undef TAP_CODE_DELAY
	#define TAP_CODE_DELAY 20
#endif
#ifdef QUICK_TAP_TERM
	#undef QUICK_TAP_TERM
	#define QUICK_TAP_TERM 0
#endif
#ifdef TAPPING_TERM
    #undef TAPPING_TERM
    #define TAPPING_TERM 200
#endif
// #define TAPPING_TERM 175
// #define TAPPING_TERM_PER_KEY
#define ENCODER_DIRECTION_FLIP




#define RGBLIGHT_SLEEP
#define RGBLIGHT_LAYERS
/* ws2812 RGB LED */
#define WS2812_DI_PIN D3

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM

	//#define RGBLIGHT_EFFECT_BREATHING
	#define RGBLIGHT_EFFECT_RAINBOW_MOOD
	//#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
	//#define RGBLIGHT_EFFECT_SNAKE
	//#define RGBLIGHT_EFFECT_KNIGHT
	//#define RGBLIGHT_EFFECT_CHRISTMAS
	//#define RGBLIGHT_EFFECT_STATIC_GRADIENT
	//#define RGBLIGHT_EFFECT_RGB_TEST
	//#define RGBLIGHT_EFFECT_ALTERNATING
	//#define RGBLIGHT_EFFECT_TWINKLE

    #define RGBLED_NUM 72
	//#define RGBLED_SPLIT
	#define RGBLED_SPLIT { 36, 36 } // haven't figured out how to use this yet

	//#define RGBLED_NUM 30
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif