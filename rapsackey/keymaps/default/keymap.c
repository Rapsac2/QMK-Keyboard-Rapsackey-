// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "print.h"

#define _DEFAULT_LAYER1 0
#define _NUMBER_LAYER2 1
#define _NAVIGATION_LAYER3 2

#define MODTAP_HOLD_THRESHOLD 200  // ms, ab wann Hold als Hold gilt
#define Backspace_HOLD_THRESHOLD 200
#define TOGGLE_TAPHOLD_HOLD_THRESHOLD 2000




enum custom_keycodes {
    BSPC_CTRL = SAFE_RANGE,
    ALT_LAYER3TAP,
    CTRL_LAYER2TAP,
    SHIFT_LAYER1TAP,
    TOGGLE_TAPHOLD
};

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
                KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,      KC_O,     KC_P,
    KC_ESCAPE,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,      KC_L,     KC_SCLN,    KC_ENTER,
    KC_TAB,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_LBRC,   KC_QUOT,  KC_MINS,    ALT_LAYER3TAP,
                                  KC_SPACE,    BSPC_CTRL,           CTRL_LAYER2TAP, KC_LEFT_SHIFT
    ),
    /*     ! " ' [ ]   - 7 8 9 /
     * TAB ? : . ( )   0 4 5 6 * ENTER
     * ECS ^ ; , { }   + 1 2 3 = L3
     *      BSPC SPC   L1 WIN
     */
    [_NUMBER_LAYER2] = LAYOUT( 
                LSFT(KC_1),       LSFT(KC_2),        LSFT(KC_NUHS),    RALT(KC_8),    RALT(KC_9),           KC_SLSH,    KC_7,    KC_8,    KC_9,    LSFT(KC_7),
    KC_ESCAPE,  LSFT(KC_MINS),    LSFT(KC_DOT),      KC_DOT,           LSFT(KC_8),    LSFT(KC_9),           KC_0,       KC_4,    KC_5,    KC_6,    LSFT(KC_RBRC),  KC_ENTER,
    KC_TAB,     KC_GRV,           LSFT(KC_COMM),     KC_COMM,          RALT(KC_7),    RALT(KC_0),           KC_RBRC,    KC_1,    KC_2,    KC_3,    LSFT(KC_0),     ALT_LAYER3TAP,
                                                                       KC_SPACE,       BSPC_CTRL,           KC_LGUI, SHIFT_LAYER1TAP 
    ),
    /*      del StrgF  Up  copy paste    _ \ % € nxtTrack                                                   
     * TAB Strg left Down Right StrgA    < > & # play/pause  ENTER
     * ECS Shift   snipping undo redo    | @ ° ~ mute        ALT
     *                       BSPC SPC   L1 L2
     */
    [_NAVIGATION_LAYER3] = LAYOUT( 
                KC_DEL,           LCTL(KC_F),    KC_UP,         LCTL(KC_C),     LCTL(KC_V),               LSFT(KC_SLSH),    RALT(KC_MINS),    LSFT(KC_5),     RALT(KC_E),     TOGGLE_TAPHOLD,
    KC_ESCAPE,  KC_LEFT_CTRL,     KC_LEFT,       KC_DOWN,       KC_RIGHT,       LCTL(KC_A),               KC_NUBS,          LSFT(KC_NUBS),    LSFT(KC_6),     KC_NUHS,        KC_MEDIA_PLAY_PAUSE,   KC_ENTER,
    KC_TAB,     KC_LEFT_SHIFT,    KC_NO,         LSG(KC_S),     LCTL(KC_Z),     LCTL(KC_Y),               RALT(KC_NUBS),    RALT(KC_Q),       LSFT(KC_GRV),   RALT(KC_RBRC),  KC_PAUSE,              KC_LEFT_ALT,
                                                                KC_SPACE,        BSPC_CTRL,               CTRL_LAYER2TAP,   SHIFT_LAYER1TAP
    )
};

// example code for Shift + Backspace to act as the delete key
// https://docs.qmk.fm/feature_advanced_keycodes
// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;

static bool bspc_held = false;
static bool del_held = false;
static uint16_t bspc_timer = 0;
static uint16_t del_timer = 0;
static bool ctrl_sent = false;

static bool isctrllayer2key_pressed = false;
static uint16_t ctrllayer2key_timer = 0;
static uint8_t ctrllayer2key_previous_layer = 0;

static bool isaltlayer3key_pressed = false;
static uint16_t altlayer3key_timer = 0;
static uint8_t altlayer3key_previous_layer = 0;

static bool isshiftlayer1key_pressed = false;
static uint16_t shiftlayer1key_timer = 0;
static uint8_t shiftlayer1key_previous_layer = 0;

static bool isTOGGLE_TAPHOLD_pressed = false;
static uint16_t TOGGLE_TAPHOLD_timer = 0;
static bool TOGGLE_TAPHOLD_state = true; //standardmäßig ist tap hold aktiv



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    dprintf("------------------------\n");
    dprintf("Layer: %u\n", get_highest_layer(layer_state));
    dprintf("Mod state: 0b%08b\n", mod_state);
    dprintf("TAP_HOLD state: %u\n", TOGGLE_TAPHOLD_state);
    switch (keycode) {
    case BSPC_CTRL: // on tap Backspace senden, wenn gehalten Strg+Backspace und wenn Shift gehalten ist, dann Delete senden und delete + Strg
    if (record->event.pressed) {
                ctrl_sent = false;
                if(mod_state & MOD_MASK_SHIFT){ //shift variante testen
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(KC_DEL);
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    del_timer = timer_read();
                    del_held = true;
                    return false;
                } else {
                    // Sofort Backspace senden
                    tap_code(KC_BSPC);
                    bspc_held = true;
                    bspc_timer = timer_read();
                }
            } else {
                bspc_held = false;
                del_held = false;
            }
            return false; // Kein Standardverhalten (keine Ahnung ob weitere hotkey dann noch gehen)


    case CTRL_LAYER2TAP: // on tap layer wechseln und wenn gehalten strg senden
        if(record->event.pressed) {
            
            ctrllayer2key_timer = timer_read();
            isctrllayer2key_pressed = true;
            ctrllayer2key_previous_layer = get_highest_layer(layer_state);
            layer_move(_NUMBER_LAYER2);
            
            
        } else {
            isctrllayer2key_pressed = false;
            unregister_code(KC_LCTL);
        }
        return false;
    
        case ALT_LAYER3TAP:
        if(record->event.pressed) {
            
            altlayer3key_timer = timer_read();
            isaltlayer3key_pressed = true;
            altlayer3key_previous_layer = get_highest_layer(layer_state);
            layer_move(_NAVIGATION_LAYER3);
            
            
        } else {
            isaltlayer3key_pressed = false;
            unregister_code(KC_LALT);
        }
        return false;

        case SHIFT_LAYER1TAP:
        if(record->event.pressed) {
            
            shiftlayer1key_timer = timer_read();
            isshiftlayer1key_pressed = true;
            shiftlayer1key_previous_layer = get_highest_layer(layer_state);
            layer_move(_DEFAULT_LAYER1);
            
            
        } else {
            isshiftlayer1key_pressed = false;
            unregister_code(KC_LSFT);
        }
        return false;
    
    
    case TOGGLE_TAPHOLD: // toggelt das tap hold-verhalten der sondertasten
        if(record->event.pressed) {
            TOGGLE_TAPHOLD_timer = timer_read();
            isTOGGLE_TAPHOLD_pressed = true;
        } else {
            isTOGGLE_TAPHOLD_pressed = false;
            if (timer_elapsed(TOGGLE_TAPHOLD_timer) < TOGGLE_TAPHOLD_HOLD_THRESHOLD) {
                tap_code(KC_MEDIA_NEXT_TRACK); // Beispiel: Bei kurzem Drücken skip track gesenden
            } else { //beim langen Drücken den Zustand toggeln
                TOGGLE_TAPHOLD_state = !TOGGLE_TAPHOLD_state; 
            }
        }
        return false; // verhindert die weitergabe des keycodes an qmk
    


    }
    return true;
};


void matrix_scan_user(void) {
    if (TOGGLE_TAPHOLD_state && bspc_held && !ctrl_sent && timer_elapsed(bspc_timer) > Backspace_HOLD_THRESHOLD) { 
        // Wenn Taste noch gehalten wird und Zeit abgelaufen ist
        tap_code16(LCTL(KC_BSPC));
        ctrl_sent = true;
    }
    if (TOGGLE_TAPHOLD_state && del_held && !ctrl_sent && timer_elapsed(del_timer) > Backspace_HOLD_THRESHOLD){
        tap_code16(LCTL(KC_DEL));
        ctrl_sent = true;
    }
    
    //layer wechseln wenn die Zeit abgelaufen ist
    if(TOGGLE_TAPHOLD_state && isctrllayer2key_pressed && timer_elapsed(ctrllayer2key_timer) > MODTAP_HOLD_THRESHOLD){
        layer_move(ctrllayer2key_previous_layer);
        register_code(KC_LCTL); 
    }
    if(TOGGLE_TAPHOLD_state && isaltlayer3key_pressed && timer_elapsed(altlayer3key_timer) > MODTAP_HOLD_THRESHOLD){
        layer_move(altlayer3key_previous_layer);
        register_code(KC_LCTL); 
    }
    if(TOGGLE_TAPHOLD_state && isshiftlayer1key_pressed && timer_elapsed(shiftlayer1key_timer) > MODTAP_HOLD_THRESHOLD){
        layer_move(shiftlayer1key_previous_layer);
        register_code(KC_LSFT); 
    }
}
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}