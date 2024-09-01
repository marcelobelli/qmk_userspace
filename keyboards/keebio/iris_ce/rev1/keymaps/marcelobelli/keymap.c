// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

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

enum custom_layers { _QWERTY, _LOWER, _RAISE };

enum custom_keycodes {
    DOUBLE_EQUAL = SAFE_RANGE,
    NOT_EQUAL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
        // ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                        ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
        // ├    =    ┼    1    ┼    2    ┼    3    ┼    4    ┼    5    ┤                        ├    6    ┼    7    ┼    8    ┼    9    ┼    0    ┼    -    ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├   TAB   ┼    Q    ┼    W    ┼    E    ┼    R    ┼    T    ┤                        ├    Y    ┼    U    ┼    I    ┼    O    ┼    P    ┼    \    ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├   ESC   ┼ LSFT/A  ┼ LCTL/S  ┼ LOPT/D  ┼ LCMD/F  ┼ RCMD/G  ┤                        ├ RCMD/H  ┼ LCMD/J  ┼ ROPT/K  ┼ RCTL/L  ┼ RSFT/;  ┼    '    ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├   ENT   ┼    Z    ┼    X    ┼    C    ┼    V    ┼    B    ┼   HOME  ┤    ├   END   ┼    N    ┼    M    ┼    ,    ┼    .    ┼    /    ┼    `    ┤
        // ├─────────┴─────────┴─────────┴────┬────┴────┬────┴────┬────┴────┬────┘    └────┬────┴────┬────┴────┬────┴────┬────┴─────────┴─────────┴─────────┘
        //                                    ├  LCMD   ┼  LOWER  ┼   SPC   ┤              ├   ENT   ┼  UPPER  ┼  BSPC   ┤
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
        KC_LGUI, TL_LOWR, KC_SPC, KC_ENT, TL_UPPR, KC_BSPC
        //
        ),

    [_LOWER] = LAYOUT(
        //
        // ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                        ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
        // ├    =    ┼    1    ┼    2    ┼    3    ┼    4    ┼    5    ┤                        ├    6    ┼    7    ┼    8    ┼    9    ┼    0    ┼    -    ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├   TAB   ┼    Q    ┼    W    ┼    E    ┼    R    ┼    T    ┤                        ├    Y    ┼    U    ┼    I    ┼    O    ┼    P    ┼    \    ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├   ESC   ┼ LSFT/A  ┼ LCTL/S  ┼ LOPT/D  ┼ LCMD/F  ┼ RCMD/G  ┤                        ├  LEFT   ┼  DOWN   ┼   UP    ┼  RIGHT  ┼ RSFT/;  ┼    '    ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├   ENT   ┼    Z    ┼    X    ┼    C    ┼    V    ┼    B    ┼   HOME  ┤    ├   END   ┼    N    ┼    M    ┼    ,    ┼    .    ┼    /    ┼    `    ┤
        // ├─────────┴─────────┴─────────┴────┬────┴────┬────┴────┬────┴────┬────┘    └────┬────┴────┬────┴────┬────┴────┬────┴─────────┴─────────┴─────────┘
        //                                    ├  LCMD   ┼  LOWER  ┼   SPC   ┤              ├   ENT   ┼  UPPER  ┼  BSPC   ┤
        //                                    └─────────┴─────────┴─────────┘              └─────────┴─────────┴─────────┘
        //
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PGUP,
        //
        KC_GRV, _______, _______, _______, QK_BOOT, KC_LBRC, KC_RBRC, _______, _______, _______, _______, KC_PGDN,
        //
        KC_DEL, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_PLUS, KC_BSLS,
        //
        RGB_MOD, EE_CLR, _______, _______, _______, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_P1, KC_P2, KC_P3, KC_MINS, _______,
        //
        _______, _______, KC_DEL, KC_DEL, _______, KC_P0
        //
        ),

    [_RAISE] = LAYOUT(
        // ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                        ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
        // ├         ┼         ┼         ┼         ┼         ┼         ┤                        ├         ┼         ┼         ┼         ┼         ┼  BOOT   ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├         ┼    -    ┼    +    ┼    =    ┼   ==    ┼   !=    ┤                        ├    Y    ┼    U    ┼    I    ┼    O    ┼    P    ┼ EE CLR  ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├         ┼    *    ┼    [    ┼    {    ┼    (    ┼    <    ┤                        ├ RCMD/H  ┼ LCMD/J  ┼ ROPT/K  ┼ RCTL/L  ┼ RSFT/;  ┼         ┤
        // ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
        // ├         ┼    /    ┼    ]    ┼    }    ┼    )    ┼    >    ┼ LCK SCR ┤    ├   END   ┼         ┼  MUTE   ┼  VOL -  ┼  VOL +  ┼    /    ┼         ┤
        // ├─────────┴─────────┴─────────┴────┬────┴────┬────┴────┬────┴────┬────┘    └────┬────┴────┬────┴────┬────┴────┬────┴─────────┴─────────┴─────────┘
        //                                    ├  LCMD   ┼  LOWER  ┼   SPC   ┤              ├   ENT   ┼  UPPER  ┼  BSPC   ┤
        //                                    └─────────┴─────────┴─────────┘              └─────────┴─────────┴─────────┘
        //
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        //
        _______, KC_KP_MINUS, KC_KP_PLUS, KC_KP_EQUAL, DOUBLE_EQUAL, NOT_EQUAL, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, QK_BOOT,
        //
        RGB_MOD, KC_KP_ASTERISK, KC_MNXT, KC_VOLU, KC_PGUP, KC_UNDS, KC_EQL, KC_HOME, RGB_HUI, RGB_SAI, RGB_VAI, KC_BSLS,
        //
        KC_MUTE, KC_KP_SLASH, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS, KC_LPRN, _______, KC_PLUS, KC_END, RGB_HUD, RGB_SAD, RGB_VAD, EE_CLR,
        //
        _______, _______, _______, _______, _______, _______
        //
        )};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) {
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

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t index = g_led_config.matrix_co[row][col];
            RGB     rgb   = hsv_to_rgb(hsv);

            if (keymap_key_to_keycode(current_layer, (keypos_t){col, row}) > KC_TRNS) {
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
            } else {
                rgb_matrix_set_color(index, HSV_BLACK);
            }
        }
    }

    return false;
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    switch (other_keycode) {
        case KC_SPC:
        case KC_TAB:
            return true;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}
