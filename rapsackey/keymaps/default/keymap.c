// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

//#include "keymap_german.h"

#define _DEFAULT_LAYER1 0
#define _NUMBER_LAYER2 1
#define _NAVIGATION_LAYER3 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *      C5R1 C4R1 C3R1 C2R1 C1R1   C1R5 C2R5 C3R5 C4R5 C5R5
     * C4R4 C5R2 C4R2 C3R2 C2R2 C1R2   C1R6 C2R6 C3R6 C4R6 C5R6 C4R8
     * C3R4 C5R3 C4R3 C3R3 C2R3 C1R3   C1R7 C2R7 C3R7 C4R7 C5R7 C3R8
     *                     C2R4 C1R4   C1R8 C2R8
     */
    /*
     *         GP26GP2 GP22GP2 GP20GP2 GP23GP2 GP21GP2   GP21GP6 GP23GP6 GP20GP6 GP22GP6 GP26GP6
     * GP22GP5 GP26GP3 GP22GP3 GP20GP3 GP23GP3 GP21GP3   GP21GP7 GP23GP7 GP20GP7 GP22GP7 GP26GP7 GP22GP9
     * GP20GP5 GP26GP4 GP22GP4 GP20GP4 GP23GP4 GP21GP4   GP21GP8 GP23GP8 GP20GP8 GP22GP8 GP26GP8 GP20GP9
     *                                 GP23GP5 GP21GP5   GP21GP9 GP23GP9
     */
     /*
     *    04 03 02 01 00   40 41 42 43 44 
     * 33 14 13 12 11 10   50 51 52 53 54 73
     * 32 24 23 22 21 20   60 61 62 63 64 72
     *             31 30   70 71
     */


    /*     Q W E R T   Z U I O P
     * TAB A S D F G   H J K L Ö ENTER
     * ECS Y X C V B   N M Ü Ä ß L3
     *      BSPC SPC   LSHFT L2                     
     */ 
     // Idee: Wenn L2 oder L3 gedrückt sind, dann wirken diese wie Alt und Strg --> https://docs.qmk.fm/mod_tap
     
     // statt Ü,Ä usw werden die englischen zeichen verwendet, da der Commputer diese dann umwandelt
     // https://mechanische-tastaturen.net/qmk-und-via-guide/qmk-via-keycodes-fuer-deutsche-zeichen/
    [_DEFAULT_LAYER1] = LAYOUT( /* Qwertz */
                KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Z,    KC_U,    KC_I,      KC_O,     KC_P,
    KC_TAB,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,      KC_L,     KC_SCLN,    KC_ENTER,
    KC_ESCAPE,  KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_LBRC,   KC_QUOT,  KC_MINS,  TO(_NAVIGATION_LAYER3),
                                   KC_BACKSPACE, KC_SPACE,          KC_LEFT_SHIFT, TO(_NUMBER_LAYER2)
    ),
    /*     ! " ' [ ]   - 7 8 9 /
     * TAB ? : . ( )   0 4 5 6 * ENTER
     * ECS ^ ; , { }   + 1 2 3 = L3
     *      BSPC SPC   L1 WIN
     */
    [_NUMBER_LAYER2] = LAYOUT( 
                LSFT(KC_1),       LSFT(KC_2),        LSFT(KC_NUHS),    RALT(KC_8),    RALT(KC_9),           KC_SLSH,    KC_7,    KC_8,    KC_9,    LSFT(KC_7),
    KC_TAB,     LSFT(KC_MINS),    LSFT(KC_DOT),      KC_DOT,           LSFT(KC_8),    LSFT(KC_9),           KC_0,       KC_4,    KC_5,    KC_6,    LSFT(KC_RBRC),  KC_ENTER,
    KC_ESCAPE,  KC_GRV,           LSFT(KC_COMM),     KC_COMM,          RALT(KC_7),    RALT(KC_0),           KC_RBRC,    KC_1,    KC_2,    KC_3,    LSFT(KC_0),     TO(_NAVIGATION_LAYER3),
                                                                       KC_BACKSPACE,  KC_SPACE,             TO(_DEFAULT_LAYER1), KC_LEFT_GUI
    ),
    /*         StrgF  Up  copy  paste    _ \ % € nxtTrack
     * TAB Strg left Down Right StrgA    < > & # play/pause  ENTER
     * ECS Shift   snipping undo redo    | @ ° ~ mute        ALT
     *                       BSPC SPC   L1 L2
     */
    [_NAVIGATION_LAYER3] = LAYOUT( 
                KC_NO,            LCTL(KC_F),    KC_UP,         LCTL(KC_C),     LCTL(KC_V),               LSFT(KC_SLSH),    RALT(KC_MINS),    LSFT(KC_5),     RALT(KC_E),     KC_MEDIA_NEXT_TRACK,
    KC_TAB,     KC_LEFT_CTRL,     KC_LEFT,       KC_DOWN,       KC_RIGHT,       LCTL(KC_A),               KC_NUBS,          LSFT(KC_NUBS),    LSFT(KC_6),     KC_NUHS,        KC_MEDIA_PLAY_PAUSE,   KC_ENTER,
    KC_ESCAPE,  KC_LEFT_SHIFT,    KC_NO,         LSG(KC_S),     LCTL(KC_Z),     LCTL(KC_Y),               RALT(KC_NUBS),    RALT(KC_Q),       LSFT(KC_GRV),   RALT(KC_RBRC),  KC_PAUSE,              KC_LEFT_ALT,
                                                                KC_BACKSPACE,   KC_SPACE,                 TO(_DEFAULT_LAYER1), TO(_NUMBER_LAYER2)
    )
};

// example code for Shift + Backspace to act as the delete key
// https://docs.qmk.fm/feature_advanced_keycodes
// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {

    case KC_BSPC:
        {
        // Initialize a boolean variable that keeps track
        // of the delete key status: registered or not?
        static bool delkey_registered;
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // Update the boolean variable to reflect the status of KC_DEL
                delkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_BSPC
            // In case KC_DEL is still being sent even after the release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // Let QMK process the KC_BSPC keycode as usual outside of shift
        return true;
    }

    }
    return true;
};