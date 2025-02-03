/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_MIDDLE,
    LAYER_SYMBOLS,
    LAYER_POINTER,
    LAYER_MAIN_POINTER,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define MIDDLE MO(LAYER_MIDDLE)
#define SYMBOLS MO(LAYER_SYMBOLS)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_TAB LT(LAYER_LOWER, KC_TAB)
#define PT_A CTL_T(KC_A)
#define PT_S OPT_T(KC_S)
#define PT_D CMD_T(KC_D)
#define PT_F SFT_T(KC_F)
#define PT_SPC LT(LAYER_MIDDLE, KC_SPC)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

enum custom_keycodes {
    SMTD_KEYCODES_BEGIN = SAFE_RANGE,
    CKC_SCLN, // reads as C(ustom) + KC_A, but you may give any name here
    CKC_L,
    CKC_K,
    CKC_J,
    SMTD_KEYCODES_END,
};
#include "sm_td.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }
    // your code here

    return true;
}

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(CKC_SCLN, KC_SCLN, KC_LEFT_CTRL)
        SMTD_MT(CKC_L, KC_L, KC_LOPT)
        SMTD_MT(CKC_K, KC_K, KC_LCMD)
        SMTD_MT(CKC_J, KC_J, KC_LSFT)
    }
}

enum combos {
    ER_MINUS,
    UI_UNDERSCORE,
    IO_EQUAL,
    FG_LEFT_PAREN,
    JH_RIGHT_PAREN,
    VB_LEFT_CURLY_BRACE,
    MN_RIGHT_CURLY_BRACE,
    RT_LEFT_BRACKET,
    UY_RIGHT_BRACKET,
    COMMA_M_LEFT_BRACKET, // ru х
    COMMA_DOT_LEFT_BRACKET, // ru ъ
    DK_BTN1,
    SL_DRGSCRL,
    FJ_CAPS_WORD,
    QW_TILD,
    WE_GRV,
    SPC_RAISE_SYMBOLS,
    DOT_SLSH_QUES,
};

const uint16_t PROGMEM er_combo[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM fg_combo[] = {PT_F, KC_G, COMBO_END};
const uint16_t PROGMEM jh_combo[] = {CKC_J, KC_H, COMBO_END};
const uint16_t PROGMEM vb_combo[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM mn_combo[] = {KC_M, KC_N, COMBO_END};
const uint16_t PROGMEM rt_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM uy_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM fj_combo[] = {PT_F, CKC_J, COMBO_END};
const uint16_t PROGMEM dk_combo[] = {PT_D, CKC_K, COMBO_END};
const uint16_t PROGMEM sl_combo[] = {PT_S, CKC_L, COMBO_END};
const uint16_t PROGMEM comma_m_combo[] = {KC_COMM, KC_M, COMBO_END};
const uint16_t PROGMEM spc_raise_combo[] = {KC_SPC, RAISE, COMBO_END};
const uint16_t PROGMEM dot_slsh_combo[] = {KC_DOT, PT_SLSH, COMBO_END};
const uint16_t PROGMEM comm_dot_combo[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[] = {
    [ER_MINUS]                = COMBO(er_combo, KC_MINS),
    [UI_UNDERSCORE]           = COMBO(ui_combo, KC_UNDS),
    [IO_EQUAL]                = COMBO(io_combo, KC_EQL),
    [FG_LEFT_PAREN]           = COMBO(fg_combo, KC_LPRN),
    [JH_RIGHT_PAREN]          = COMBO(jh_combo, KC_RPRN),
    [VB_LEFT_CURLY_BRACE]     = COMBO(vb_combo, KC_LCBR),
    [MN_RIGHT_CURLY_BRACE]    = COMBO(mn_combo, KC_RCBR),
    [RT_LEFT_BRACKET]         = COMBO(rt_combo, KC_LEFT_BRACKET),
    [UY_RIGHT_BRACKET]        = COMBO(uy_combo, KC_RIGHT_BRACKET),
    [COMMA_M_LEFT_BRACKET]    = COMBO(comma_m_combo, KC_LEFT_BRACKET),
    [COMMA_DOT_LEFT_BRACKET]  = COMBO(comm_dot_combo, KC_RIGHT_BRACKET),
    [FJ_CAPS_WORD]            = COMBO(fj_combo, CW_TOGG),
    [DK_BTN1]                 = COMBO(dk_combo, KC_BTN1),
    [SL_DRGSCRL]              = COMBO(sl_combo, DRGSCRL),
    [WE_GRV]                  = COMBO(we_combo, KC_GRV),
    [QW_TILD]                 = COMBO(qw_combo, KC_TILD),
    [SPC_RAISE_SYMBOLS]       = COMBO(spc_raise_combo, SYMBOLS),
    [DOT_SLSH_QUES]           = COMBO(dot_slsh_combo, S(KC_7)),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O, KC_P,    KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_LSFT,   PT_A,    PT_S,    PT_D,    PT_F,    KC_G,      KC_H,    CKC_J, CKC_K,   CKC_L,  CKC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_LCTL,   PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, KC_LALT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    KC_LGUI, KC_SPC, PT_TAB,     KC_DEL, RAISE,
                                            MIDDLE, KC_BSPC,     KC_ENT
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,    KC_F8, KC_F9,  KC_F10, KC_F11, KC_F12,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      RGB_MOD,  UG_HUEU, UG_SATU, UG_VALU, UG_SPDU, XXXXXXX,    XXXXXXX,   KC_7,  KC_8,   KC_9, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      RGB_TOG,  KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,    KC_PPLS,   KC_4,  KC_5,   KC_6, KC_PMNS, KC_PEQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      RGB_RMOD, UG_HUED, UG_SATD, UG_VALD, UG_SPDD, XXXXXXX,    KC_PAST,   KC_1,  KC_2,   KC_3, KC_PSLS, KC_PDOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, _______,    S(KC_P), KC_DEL,
                                           XXXXXXX, XXXXXXX,    KC_0
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,  KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      KC_MPLY, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, XXXXXXX,    XXXXXXX, KC_LSFT,  KC_LGUI, KC_LALT, KC_LCTL, KC_MUTE,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      KC_MPRV, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                      RSG(KC_LBRC), RSG(KC_RBRC), G(KC_SPC),    XXXXXXX, _______,
                                       RSG(KC_A), G(KC_GRV),    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MIDDLE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_F15, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_AMPR, KC_ASTR, KC_PIPE, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      KC_CAPS, KC_LCTL, KC_LALT,  KC_LGUI, KC_LSFT, XXXXXXX,    XXXXXXX, KC_DLR,  KC_PERC, KC_CIRC, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_F14, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, XXXXXXX,    S(KC_P), KC_RPRN,
                                           _______, XXXXXXX,    KC_LPRN
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_SYMBOLS] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, KC_LT,   KC_UNDS, KC_GT,   XXXXXXX,    XXXXXXX, KC_AMPR, KC_ASTR, KC_PIPE, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       S(KC_P), KC_LBRC, KC_LPRN, KC_MINS, KC_RPRN, KC_RBRC,    XXXXXXX, KC_DLR,  KC_PERC, KC_CIRC, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, KC_LCBR, KC_EQL,  KC_RCBR, XXXXXXX,    XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
                                           XXXXXXX, XXXXXXX,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_BOOT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,    EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  QK_BOOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      DPI_MOD, KC_LCTL, KC_LALT,  KC_LGUI, KC_LSFT, DPI_RMOD,   S_D_MOD, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, S_D_RMOD,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1,
                                           XXXXXXX, DRGSCRL,    KC_BTN2
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MAIN_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LCTL, KC_LALT,  KC_LGUI, KC_LSFT, KC_ESC,    XXXXXXX, DRGSCRL, KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
                                           XXXXXXX, _______,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
