#include <zmk/behavior.h>
#include <zmk/keymap.h>
#include <zmk/endpoints.h>
#include <zmk/keys.h>
#include <dt-bindings/zmk/keys.h>

static int send_number_key_press(struct zmk_behavior_binding *binding, struct zmk_behavior_binding_event event) {
    uint8_t number = binding->param1;

    if (number > 0 && number <= 9) {
        zmk_keymap_keycode_pressed(ZC_1 + number - 1);
    } else if (number >= 10 && number <= 36) {
        uint8_t tens = number / 10;
        uint8_t ones = number % 10;
        zmk_keymap_keycode_pressed(ZC_0 + tens);
        zmk_keymap_keycode_released(ZC_0 + tens);
        zmk_keymap_keycode_pressed(ZC_0 + ones);
    }

    return 0;
}

static int send_number_key_release(struct zmk_behavior_binding *binding, struct zmk_behavior_binding_event event) {
    uint8_t number = binding->param1;

    if (number > 0 && number <= 9) {
        zmk_keymap_keycode_released(ZC_1 + number - 1);
    } else if (number >= 10 && number <= 36) {
        uint8_t ones = number % 10;
        zmk_keymap_keycode_released(ZC_0 + ones);
    }

    return 0;
}

ZMK_BEHAVIOR_DEF_VARIABLE_PRESS_RELEASE(send_number, send_number_key_press, send_number_key_release);
