#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_nordic.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define WORK 3 // media keys

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    EPRM,
    VRSN,
    RGB_SLD,
    WK_SLSH,// / ?
    WK_SC,  // ; :
    WK_QUOT,// ' "
    WK_TLD, // ` ~
    WK_EQL, // = +
    WK_CMA, // , <
    WK_DOT, // . >
    WK_LSQ, // [ {
    WK_RSQ  // ] }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Basic layer using swedish locale.
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   <    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   +    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L3  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   Å    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |ö / L2|ä / Cmd |
     * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
     * | LShift |   Z |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |-/Ctrl| RShift |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *  |´ /Ctrl|  '   |AltShf| Left | Right|                                       |  Up  | Down | AltGr| ¨    | ~L1   |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
     *                                 ,------|------|------|       |------+--------+------.
     *                                 |      |      | Home |       | PgUp |        |      |
     *                                 |Backsp| Del  |------|       |------|  Enter |Space |
     *                                 |ace   |      | End  |       | PgDn |        |      |
     *                                 `--------------------'       `----------------------'
     */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
// KC_LBRC = Å; KC_BSLS = '; KC_EQL = ´; KC_RBRC = ¨; KC_FN3 = < KC_LABK = ;;
    [BASE] = KEYMAP( // layer 0 : default
            // left hand
            NO_LESS,        KC_1,                 KC_2,                        KC_3,                           KC_4,                              KC_5,                                      KC_LEFT,
            KC_TAB,         KC_Q,                 KC_W,                        KC_E,                           KC_R,                              KC_T,                                      TG(WORK),
            KC_BSPC,        KC_A,                 KC_S,                        KC_D,                           KC_F,                              KC_G,
            KC_LSFT,        KC_Z,                 KC_X,                        KC_C,                           KC_V,                              KC_B,                                      ALL_T(KC_NO),
            CTL_T(NO_ACUT), KC_BSLS,              LALT(KC_LSFT),               KC_LEFT,                        KC_RGHT,
            ALT_T(KC_APP),  KC_LGUI,
            KC_HOME,
            KC_BSPC,        KC_DELT,              KC_END,
            // right hand
            KC_RGHT,        KC_6,                 KC_7,                        KC_8,                           KC_9,                              KC_0,                                      NO_PLUS,
            TG(SYMB),       KC_Y,                 KC_U,                        KC_I,                           KC_O,                              KC_P,                                      NO_AM,
            KC_H,           KC_J,                 KC_K,                        KC_L,                           LT(MDIA,                           NO_AE),                                    GUI_T(NO_OSLH),
            MEH_T(KC_NO),   KC_N,                 KC_M,                        KC_COMM,                        KC_DOT,                            CTL_T(NO_MINS),                            KC_RSFT,
            KC_UP,          KC_DOWN,              NO_ALGR,                     NO_QUOT,                        KC_FN1,
            KC_LALT,        CTL_T(KC_ESC),
            KC_PGUP,
            KC_PGDN,        KC_ENT,               KC_SPC
            ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
    [SYMB] = KEYMAP(
            // left hand
            VRSN,           KC_F1,                KC_F2,                       KC_F3,                          KC_F4,                             KC_F5,                                     KC_TRNS,
            KC_TRNS,        KC_EXLM,              KC_AT,                       KC_LCBR,                        KC_RCBR,                           KC_PIPE,                                   KC_TRNS,
            KC_TRNS,        KC_HASH,              KC_DLR,                      KC_LPRN,                        KC_RPRN,                           KC_GRV,
            KC_TRNS,        KC_PERC,              KC_CIRC,                     KC_LBRC,                        KC_RBRC,                           KC_TILD,                                   KC_TRNS,
            EPRM,           KC_TRNS,              KC_TRNS,                     KC_TRNS,                        KC_TRNS,
            RGB_MOD,        KC_TRNS,
            KC_TRNS,
            RGB_VAD,        RGB_VAI,              KC_TRNS,
            // right hand
            KC_TRNS,        KC_F6,                KC_F7,                       KC_F8,                          KC_F9,                             KC_F10,                                    KC_F11,
            KC_TRNS,        KC_UP,                KC_7,                        KC_8,                           KC_9,                              KC_ASTR,                                   KC_F12,
            KC_DOWN,        KC_4,                 KC_5,                        KC_6,                           KC_PLUS,                           KC_TRNS,
            KC_TRNS,        KC_AMPR,              KC_1,                        KC_2,                           KC_3,                              KC_BSLS,                                   KC_TRNS,
            KC_TRNS,        KC_DOT,               KC_0,                        KC_EQL,                         KC_TRNS,
            RGB_TOG,        RGB_SLD,
            KC_TRNS,
            KC_TRNS,        RGB_HUD,              RGB_HUI
            ),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
    [MDIA] = KEYMAP(
            KC_TRNS,        KC_TRNS,              KC_TRNS,                     KC_TRNS,                        KC_TRNS,                           KC_TRNS,                                   KC_TRNS,
            KC_TRNS,        KC_TRNS,              KC_TRNS,                     KC_MS_U,                        KC_TRNS,                           KC_TRNS,                                   KC_TRNS,
            KC_TRNS,        KC_TRNS,              KC_MS_L,                     KC_MS_D,                        KC_MS_R,                           KC_TRNS,
            KC_TRNS,        KC_TRNS,              KC_TRNS,                     KC_TRNS,                        KC_TRNS,                           KC_TRNS,                                   KC_TRNS,
            KC_TRNS,        KC_TRNS,              KC_TRNS,                     KC_BTN1,                        KC_BTN2,
            KC_TRNS,        KC_TRNS,
            KC_TRNS,
            KC_TRNS,        KC_TRNS,              KC_TRNS,
            // right hand
            KC_TRNS,        KC_TRNS,              KC_TRNS,                     KC_TRNS,                        KC_TRNS,                           KC_TRNS,                                   KC_TRNS,
            KC_TRNS,        KC_TRNS,              KC_TRNS,                     KC_TRNS,                        KC_TRNS,                           KC_TRNS,                                   KC_TRNS,
            KC_TRNS,        KC_TRNS,              KC_TRNS,                     KC_TRNS,                        KC_TRNS,                           KC_MPLY,
            KC_TRNS,        KC_TRNS,              KC_TRNS,                     KC_MPRV,                        KC_MNXT,                           KC_TRNS,                                   KC_TRNS,
            KC_VOLU,        KC_VOLD,              KC_MUTE,                     KC_TRNS,                        KC_TRNS,
            KC_TRNS,        KC_TRNS,
            KC_TRNS,
            KC_TRNS,        KC_TRNS,              KC_WBAK
            ),
/* Keymap 3: Workman
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   D  |   R  |   W  |   B  |  L3  |           |  L1  |   J  |   F  |   U  |   P  |   ;  |   =    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |I / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctl |   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *  |  [   |  ]   |AltShf| Left | Right|                                       |  Up  | Down | AltGr| ¨    | ~L1   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 |Backsp| Del  |------|       |------|  Enter |Space |
 *                                 |ace   |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 *
 */
//WORKMAN
    [WORK] = KEYMAP(
            // left hand
            WK_TLD,         KC_1,                 KC_2,                        KC_3,                           KC_4,                              KC_5,                                      KC_LEFT,
            KC_TAB,         KC_Q,                 KC_D,                        KC_R,                           KC_W,                              KC_B,                                      TG(WORK),
            KC_BSPC,        KC_A,                 KC_S,                        KC_H,                           KC_T,                              KC_G,
            KC_LSFT,        CTL_T(KC_Z),          KC_X,                        KC_M,                           KC_C,                              KC_V,                                      ALL_T(KC_NO),
            WK_LSQ,         WK_RSQ,               LALT(KC_LSFT),               KC_LEFT,                        KC_RGHT,
            ALT_T(KC_APP),  KC_LGUI,
            KC_HOME,
            KC_BSPC,        KC_DELT,              KC_END,
            // right hand
            KC_RGHT,        KC_6,                 KC_7,                        KC_8,                           KC_9,                              KC_0,                                      NO_MINS,
            TG(SYMB),       KC_J,                 KC_F,                        KC_U,                           KC_P,                              WK_SC,                                     WK_EQL,
            KC_Y,           KC_N,                 KC_E,                        KC_O,                           LT(MDIA,                           KC_I),                                     GUI_T(WK_QUOT),
            MEH_T(KC_NO),   KC_K,                 KC_L,                        WK_CMA,                         WK_DOT,                            WK_SLSH,                                   KC_RSFT,
            KC_UP,          KC_DOWN,              NO_ALGR,                     NO_QUOT,                        KC_FN1,
            KC_LALT,        CTL_T(KC_ESC),
            KC_PGUP,
            KC_PGDN,        KC_ENT,               KC_SPC
            ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)   // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t * action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    // MACRODOWN only works in this function
    switch (id) {
        case 0:

            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }

            break;

        case 1:

            if (record->event.pressed) { // For resetting EEPROM
                eeconfig_init();
            }

            break;
    }
    return MACRO_NONE;
};

void press_key_with_level_mods(uint16_t key) {
    const uint8_t interesting_mods = MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT) | MOD_BIT(KC_RALT);

    // Save the state
    const uint8_t real_mods = get_mods();
    const uint8_t weak_mods = get_weak_mods();
    const uint8_t macro_mods = get_macro_mods();

    uint8_t target_mods = (key >> 8) & (QK_MODS_MAX >> 8);

    // The 5th bit indicates that it's a right hand mod,
    // which needs some fixup
    if (target_mods & 0x10) {
        target_mods &= 0xF;
        target_mods <<= 4;
    }

    // Clear the mods that we are potentially going to modify,
    del_mods(interesting_mods);
    del_weak_mods(interesting_mods);
    del_macro_mods(interesting_mods);

    // Enable the mods that we need
    add_mods(target_mods & interesting_mods);

    // Press and release the key
    register_code(key & 0xFF);
    unregister_code(key & 0xFF);

    // Restore the previous state
    set_mods(real_mods);
    set_weak_mods(weak_mods);
    set_macro_mods(macro_mods);
    send_keyboard_report();
}

void override_key(keyrecord_t *record, uint16_t normal, uint16_t shifted) {
    const uint8_t shift = MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT);

    if (record->event.pressed) {
        bool shift_pressed = keyboard_report->mods & shift;
        const uint16_t target = shift_pressed ? shifted : normal;
        uint8_t keycode = target & 0xFF;

        if (keycode == KC_NO) {
            return;
        }

        press_key_with_level_mods(target);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // dynamically generate these.
        case EPRM:

            if (record->event.pressed) {
                eeconfig_init();
            }

            return false;

            break;

        case VRSN:

            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }

            return false;

            break;

        case RGB_SLD:

            if (record->event.pressed) {
                #ifdef RGBLIGHT_ENABLE
                rgblight_mode(1);
                #endif
            }

            return false;

            break;

        case WK_SLSH: // / ?
            override_key(record, KC_PSLS, NO_QUES);
            break;

        case WK_SC: // ; :
            override_key(record, NO_SCLN, NO_COLN);

            break;

        case WK_QUOT: // ' "
            override_key(record, NO_APOS, NO_QUO2);

            break;

        case WK_TLD: // ` ~
            override_key(record, NO_GRV, NO_TILD);

            break;

        case WK_EQL: // = +
            override_key(record, NO_EQL, NO_PLUS);

            break;

        case WK_CMA: // , <
            override_key(record, KC_COMM, NO_LESS);

            break;

        case WK_DOT: // . >
            override_key(record, KC_DOT, NO_GRTR);

            break;

        case WK_LSQ: // [ {
            override_key(record, NO_LBRC, NO_LCBR);

            break;

        case WK_RSQ: // ] }
            override_key(record, NO_RBRC, NO_RCBR);

            break;
    }
    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;

        case 2:
            ergodox_right_led_2_on();
            break;

        default:
            // none
            break;
    }
};
