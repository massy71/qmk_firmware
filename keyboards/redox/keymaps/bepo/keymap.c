#include QMK_KEYBOARD_H
#include "keymap_bepo.h"
#include "sendstring_bepo.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BEPO 0
#define _NAV 1
#define _MOUSE 2
#define _BUTTON 3
#define _MEDIA 4
#define _NUM 5
#define _SYM 6
#define _FUN 7

enum custom_keycodes {
  BEPO = SAFE_RANGE,
  NAV,
  MOUSE,
  BUTTON,
  MEDIA,
  NUM,
  SYM,
  FUN,
  EMAILP,
  EMAILW
};

#define KC_COPY LCTL(BP_C)
#define KC_PASTE LCTL(BP_V)
#define KC_UNDO LCTL(BP_Z)
#define KC_REDO LCTL(BP_Y)

// Tap dance keycodes
enum tap_dance{
  TD_COMM, // , -> ;
  TD_DOT,  // . -> :
};

// Comma to semicolon
void dance_comm_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (BP_COMM);
  } else {
    register_code (KC_RSFT);
    register_code (BP_COMM);
  }
}
void dance_comm_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (BP_COMM);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (BP_COMM);
  }
}

// Dot to colon
void dance_dot_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (BP_DOT);
  } else {
    register_code (KC_RSFT);
    register_code (BP_DOT);
  }
}
void dance_dot_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (BP_DOT);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (BP_DOT);
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_COMM]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_comm_finished, dance_comm_reset),
  [TD_DOT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dot_finished, dance_dot_reset)
};

// - Tap dance:
#define BP_TDCO TD(TD_COMM)          // ,, -> ;
#define BP_TDDO TD(TD_DOT)           // .. -> :

//Macros

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case EMAILP:  // Types ../ to go up a directory on the shell.
      if (record->event.pressed) {
        SEND_STRING("massimo.casalini@gmail.com");
      }
      return false;

    case EMAILW:  // Types triple equal ===
      if (record->event.pressed) {
        SEND_STRING("massimo.casalini@agedi.fr");
      }
      return false;
  }
  return true;
}

// Shortcut to make keymap more readable

// Home row modifiers
#define BP_LGUA LGUI_T(BP_A)
#define BP_LALU LALT_T(BP_U)
#define BP_LCTI LCTL_T(BP_I)
#define BP_LSFE LSFT_T(BP_E)
#define BP_RSFT RSFT_T(BP_T)
#define BP_RCTS RCTL_T(BP_S)
#define BP_RALR RALT_T(BP_R)
#define BP_RGUN RGUI_T(BP_N)

// Layer mod
#define BP_NASP LT(_NAV, KC_SPC)
#define BP_MOTA LT(_MOUSE, KC_TAB)
#define BP_MEES LT(_MEDIA, KC_ESC)
#define BP_NUBS LT(_NUM, KC_BSPC)
#define BP_SYEN LT(_SYM, KC_ENT)
#define BP_FUDE LT(_FUN, KC_DEL)
#define BP_NAV TG(_NAV)
#define BP_MOUS TG(_MOUSE)
#define BP_BUTT TG(_BUTTON)
#define BP_MEDI TG(_MEDIA)
#define BP_NUM TG(_NUM)
#define BP_SYM TG(_SYM)
#define BP_FUN TG(_FUN)


// RGB
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_RED}
);
const rgblight_segment_t PROGMEM my_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_CYAN}
);
const rgblight_segment_t PROGMEM my_mouse_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_YELLOW}
);
const rgblight_segment_t PROGMEM my_button_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_PINK}
);
const rgblight_segment_t PROGMEM my_media_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM my_num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_BLUE}
);
const rgblight_segment_t PROGMEM my_sym_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_GREEN}
);
const rgblight_segment_t PROGMEM my_fun_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_ORANGE}
);
// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_nav_layer,
    my_mouse_layer,
    my_button_layer,
    my_media_layer,
    my_num_layer,
    my_sym_layer,
    my_fun_layer
);
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(2, layer_state_cmp(state, _MOUSE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _BUTTON));
    rgblight_set_layer_state(4, layer_state_cmp(state, _MEDIA));
    rgblight_set_layer_state(5, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(6, layer_state_cmp(state, _SYM));
    rgblight_set_layer_state(7, layer_state_cmp(state, _FUN));
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BEPO] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     BP_DLR  ,BP_DQUO ,BP_LDAQ ,BP_RDAQ ,BP_LPRN ,BP_RPRN ,                                            BP_PLUS ,BP_MINS ,BP_SLSH ,BP_ASTR ,BP_EQL  ,BP_PERC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,BP_B    ,BP_EACU ,BP_P    ,BP_O    ,BP_EGRV ,BP_AT   ,                          BP_DCIR ,BP_V    ,BP_D    ,BP_L    ,BP_J    ,BP_Z    ,BP_W    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BP_ECIR ,BP_LGUA ,BP_LALU ,BP_LCTI ,BP_LSFE ,BP_TDCO ,_______ ,                          _______ ,BP_C    ,BP_RSFT ,BP_RCTS ,BP_RALR ,BP_RGUN ,BP_M    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BP_BUTT ,BP_AGRV ,BP_Y    ,BP_X    ,BP_TDDO ,BP_K    ,KC_PGUP ,KC_PGDN ,        KC_HOME ,KC_END  ,BP_QUOT ,BP_Q    ,BP_G    ,BP_H    ,BP_F    ,BP_CCED ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,KC_PPLS ,KC_PMNS ,KC_PAST ,     BP_MEES ,    BP_NASP ,BP_MOTA ,        BP_SYEN ,BP_NUBS ,    BP_FUDE ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

 [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,QK_BOOT ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_AGIN ,KC_PSTE , KC_COPY, KC_CUT ,KC_UNDO ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_LGUI ,KC_LALT ,KC_LCTL ,KC_LSFT ,_______ ,_______ ,                          _______ ,KC_CAPS ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,BP_NUM  ,BP_NAV  ,_______ ,_______ ,_______ ,        _______ ,_______ ,KC_INS  ,KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END  ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        KC_ENT  ,KC_BSPC ,    KC_DEL  ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

 [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,QK_BOOT ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_AGIN ,KC_PSTE , KC_COPY, KC_CUT ,KC_UNDO ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_LGUI ,KC_LALT ,KC_LCTL ,KC_LSFT ,_______ ,_______ ,                          _______ ,_______ ,KC_MS_L ,KC_MS_D ,KC_MS_U ,KC_MS_R ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,BP_SYM  ,BP_MOUS ,_______ ,_______ ,_______ ,        _______ ,_______ ,_______ ,KC_WH_L ,KC_WH_D ,KC_WH_U ,KC_WH_R ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        KC_BTN2 ,KC_BTN1 ,    KC_BTN3 ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

 [_BUTTON] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_UNDO ,KC_CUT  ,KC_COPY ,KC_PSTE ,KC_AGIN ,_______ ,                          _______ ,KC_AGIN ,KC_PSTE ,KC_COPY ,KC_CUT  ,KC_UNDO ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_LGUI ,KC_LALT ,KC_LCTL ,KC_LSFT ,_______ ,_______ ,                          _______ ,_______ ,KC_RSFT ,KC_RCTL ,KC_RALT ,KC_RGUI ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_UNDO ,KC_CUT  ,KC_COPY ,KC_PSTE ,KC_AGIN ,_______ ,_______ ,        _______ ,_______ ,KC_AGIN ,KC_PSTE ,KC_COPY ,KC_CUT  ,KC_UNDO ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     KC_BTN3 ,    KC_BTN1 ,KC_BTN2 ,        KC_BTN2 ,KC_BTN1 ,    KC_BTN3 ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

 [_MEDIA] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,QK_BOOT ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,RGB_TOG ,RGB_MOD ,RGB_HUI ,RGB_SAI ,RGB_VAI ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_LGUI ,KC_LALT ,KC_LCTL ,KC_LSFT ,_______ ,_______ ,                          _______ ,_______ ,KC_MPRV ,KC_VOLD ,KC_VOLU ,KC_MNXT ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,BP_FUN  ,BP_MEDI ,_______ ,_______ ,_______ ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        KC_MSTP ,KC_MPLY ,    KC_MUTE ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

 [_NUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,BP_LBRC ,KC_P7   ,KC_P8   ,KC_P9   ,BP_RBRC ,KC_PSLS ,                          _______ ,_______ ,_______ ,_______ ,_______ ,QK_BOOT ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,BP_LPRN ,KC_P4   ,KC_P5   ,KC_P6   ,BP_RPRN ,BP_EQL  ,                          _______ ,_______ ,KC_RSFT ,KC_RCTL ,KC_RALT ,KC_RGUI ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,BP_LCBR ,KC_P1   ,KC_P2   ,KC_P3   ,BP_RCBR ,KC_PAST ,KC_PPLS ,        _______ ,_______ ,_______ ,BP_NUM  ,BP_NAV  ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,BP_COMM ,     KC_PDOT ,    KC_P0   ,KC_PMNS ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     EMAILP  ,BP_LCBR ,BP_AMPR ,BP_ASTR ,BP_LPRN ,BP_RCBR ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,QK_BOOT ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     EMAILW  ,BP_COLN ,BP_DLR  ,BP_PERC ,BP_CIRC ,KC_PPLS ,_______ ,                          _______ ,_______ ,KC_RSFT ,KC_RCTL ,KC_RALT ,KC_RGUI ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,BP_TILD ,BP_EXLM ,BP_AT   ,BP_HASH ,BP_PIPE ,_______ ,_______ ,        _______ ,_______ ,_______ ,BP_SYM  ,BP_MOUS ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     BP_LPRN ,    BP_RPRN ,BP_UNDS ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_FUN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_F12  ,KC_F7   ,KC_F8   ,KC_F9   ,KC_PSCR ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,QK_BOOT ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_F11  ,KC_F4   ,KC_F5   ,KC_F6   ,KC_SCRL ,_______ ,                          _______ ,_______ ,KC_RSFT ,KC_RCTL ,KC_RALT ,KC_RGUI ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_F10  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_PAUS ,_______ ,_______ ,        _______ ,_______ ,_______ ,BP_FUN  ,BP_MEDI ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     KC_APP  ,    KC_SPC  ,KC_TAB  ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
};
