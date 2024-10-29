#include <stdbool.h>
#include <stdint.h>
#include "action_layer.h"
#include "color.h"
#include "info_config.h"
#include "keycodes.h"
#include "keymap_common.h"
#include "keymap_us.h"
#include "matrix.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "rgb_matrix.h"
#include QMK_KEYBOARD_H

#include "features/achordion.h"
#include "features/layer_lock.h"

#define LOCK_SCREEN LGUI(LCTL(KC_Q))
#define UNDO LCMD(KC_Z)
#define REDO LCMD(LSFT(KC_Z))
#define SELECT_LINE LCMD(KC_LSFT)
#define SELECT_WORD LOPT(KC_LSFT)

enum custom_layers { _QWERTY, _LOWER, _RAISE };

enum custom_keycodes {
    DOUBLE_EQUAL = SAFE_RANGE,
    NOT_EQUAL,
    LLOCK,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
        //
        // ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                        ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
        // ├    =    ┼    1    ┼    2    ┼    3    ┼    4    ┼    5    ┤                        ├    6    ┼    7    ┼    8    ┼    9    ┼    0    ┼    -    ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├   TAB   ┼    Q    ┼    W    ┼    E    ┼    R    ┼    T    ┤                        ├    Y    ┼    U    ┼    I    ┼    O    ┼    P    ┼    \    ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├   ESC   ┼ LSFT/A  ┼ LCTL/S  ┼ LOPT/D  ┼ LCMD/F  ┼ RCMD/G  ┤                        ├ RCMD/H  ┼ LCMD/J  ┼ ROPT/K  ┼ RCTL/L  ┼ RSFT/;  ┼    '    ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├   ENT   ┼    Z    ┼    X    ┼    C    ┼    V    ┼    B    ┼   HOME  ┤    ├   END   ┼    N    ┼    M    ┼    ,    ┼    .    ┼    /    ┼    `    ┤
        // ├─────────┴─────────┴─────────┴────┬────┴────┬────┴────┬────┴────┬────┘    └────┬────┴────┬────┴────┬────┴────┬────┴─────────┴─────────┴─────────┘
        //                                    ├   SFT   ┼   CMD   ┼LOWER/SPC┤              ├UPPER/ENT┼   CTL   ┼HYPR/BSPC┤
        //                                    └─────────┴─────────┴─────────┘              └─────────┴─────────┴─────────┘
        //
        KC_EQL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
        //
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
        //
        KC_ESC, SFT_T(KC_A), CTL_T(KC_S), LOPT_T(KC_D), LCMD_T(KC_F), RCMD_T(KC_G), RCMD_T(KC_H), LCMD_T(KC_J), ROPT_T(KC_K), RCTL_T(KC_L), RSFT_T(KC_SCLN), KC_QUOT,
        //
        KC_ENT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_HOME, KC_END, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_GRV,
        //
        KC_LSFT, KC_LCMD, LT(_LOWER, KC_SPC), LT(_RAISE, KC_ENT), KC_RCTL, HYPR_T(KC_BSPC)
        //
        ),

    [_LOWER] = LAYOUT(
        //
        // ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                        ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
        // ├  BOOT   ┼ EE CLR  ┼         ┼         ┼         ┼         ┤                        ├         ┼         ┼         ┼         ┼         ┼         ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├   TAB   ┼         ┼         ┼         ┼         ┼         ┤                        ├         ┼         ┼         ┼         ┼  UNDO   ┼  REDO   ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├   ESC   ┼   SFT   ┼   CTL   ┼   OPT   ┼   CMD   ┼         ┤                        ├  LEFT   ┼  DOWN   ┼   UP    ┼  RIGHT  ┼         ┼         ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├         ┼         ┼         ┼SELECT_W ┼SELECT_L ┼         ┼         ┤    ├ LYR LCK ┼         ┼         ┼         ┼         ┼         ┼         ┤
        // ├─────────┴─────────┴─────────┴────┬────┴────┬────┴────┬────┴────┬────┘    └────┬────┴────┬────┴────┬────┴────┬────┴─────────┴─────────┴─────────┘
        //                                    ├         ┼         ┼         ┤              ├   ENT   ┼         ┼   DEL   ┤
        //                                    └─────────┴─────────┴─────────┘              └─────────┴─────────┴─────────┘
        //
        QK_BOOT, EE_CLR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, UNDO, REDO,
        //
        KC_NO, KC_LSFT, KC_LCTL, KC_LOPT, KC_LCMD, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO,
        //
        KC_NO, KC_NO, KC_NO, SELECT_WORD, SELECT_LINE, KC_NO, KC_NO, LLOCK, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //
        KC_NO, KC_NO, KC_NO, KC_ENT, KC_NO, KC_DEL
        //
        ),

    [_RAISE] = LAYOUT(
        //
        // ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                        ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
        // ├         ┼         ┼         ┼         ┼         ┼         ┤                        ├         ┼         ┼         ┼         ┼ EE CLR  ┼  BOOT   ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├         ┼    _    ┼    /    ┼    +    ┼    -    ┼    *    ┤                        ├         ┼         ┼         ┼         ┼         ┼         ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├         ┼    :    ┼    [    ┼    {    ┼    (    ┼    <    ┤                        ├         ┼  PLAY   ┼PREVIOUS ┼  NEXT   ┼         ┼         ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├         ┼         ┼    ]    ┼    }    ┼    )    ┼    >    ┼ LCK SCR ┤    ├   END   ┼         ┼  MUTE   ┼  VOL -  ┼  VOL +  ┼         ┼         ┤
        // ├─────────┴─────────┴─────────┴────┬────┴────┬────┴────┬────┴────┬────┘    └────┬────┴────┬────┴────┬────┴────┬────┴─────────┴─────────┴─────────┘
        //                                    ├   !=    ┼    =    ┼   ==    ┤              ├   ENT   ┼  UPPER  ┼  BSPC   ┤
        //                                    └─────────┴─────────┴─────────┘              └─────────┴─────────┴─────────┘
        //
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, EE_CLR, QK_BOOT,
        //
        KC_NO, KC_UNDS, KC_KP_SLASH, KC_KP_PLUS, KC_KP_MINUS, KC_KP_ASTERISK, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        //
        KC_NO, LSFT(KC_SCLN), KC_LEFT_BRACKET, KC_LEFT_CURLY_BRACE, KC_LEFT_PAREN, KC_LEFT_ANGLE_BRACKET, KC_NO, KC_MPLY, KC_MPRV, KC_MNXT, KC_NO, KC_NO,
        //
        KC_NO, KC_NO, KC_RIGHT_BRACKET, KC_RIGHT_CURLY_BRACE, KC_RIGHT_PAREN, KC_RIGHT_ANGLE_BRACKET, LOCK_SCREEN, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO,
        //
        NOT_EQUAL, KC_KP_EQUAL, DOUBLE_EQUAL, KC_NO, KC_NO, KC_NO
        //
        )};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) {
        return false;
    }
    if (!process_layer_lock(keycode, record, LLOCK)) {
        return false;
    }

    switch (keycode) {
        case DOUBLE_EQUAL:
            if (record->event.pressed) {
                SEND_STRING("==");
            }
            break;
        case NOT_EQUAL:
            if (record->event.pressed) {
                SEND_STRING("!=");
            }
            break;
    }

    return true;
}

void matrix_scan_user(void) {
    achordion_task();
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    HSV     hsv           = {213, 255, rgblight_get_val()}; // MANGENTA
    uint8_t current_layer = get_highest_layer(layer_state | default_layer_state);
    switch (current_layer) {
        case _RAISE:
            hsv.h = 11; // CORAL
            break;
        case _LOWER:
            hsv.h = 106; // SPRINGGREEN
            break;
        default:
            rgb_matrix_sethsv(hsv.h, hsv.s, hsv.v);
            return false;
    }

    HSV boot_hsv   = {0, 255, rgb_matrix_get_val()};
    HSV ee_clr_hsv = {0, 0, rgb_matrix_get_val()};
    RGB layer_rgb  = hsv_to_rgb(hsv);
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t  index   = g_led_config.matrix_co[row][col];
            uint16_t keycode = keymap_key_to_keycode(current_layer, (keypos_t){col, row});

            if (keycode == QK_BOOT) {
                RGB rgb = hsv_to_rgb(boot_hsv);
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
            } else if (keycode == EE_CLR) {
                RGB rgb = hsv_to_rgb(ee_clr_hsv);
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
            } else if (keycode <= KC_NO) {
                rgb_matrix_set_color(index, HSV_BLACK);
            } else {
                rgb_matrix_set_color(index, layer_rgb.r, layer_rgb.g, layer_rgb.b);
            }
        }
    }

    return false;
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    switch (other_keycode) {
        case KC_SPC:
        case KC_TAB:
        case HYPR_T(KC_BSPC):
        case LT(_LOWER, KC_SPC):
        case LT(_RAISE, KC_ENT):
            return true;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    switch (tap_hold_keycode) {
        case HYPR_T(KC_BSPC):
        case LT(_LOWER, KC_SPC):
        case LT(_RAISE, KC_ENT):
            return 0;
    }

    return 1000;
}
