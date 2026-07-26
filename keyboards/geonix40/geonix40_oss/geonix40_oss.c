/* Copyright 2025 bofhgit
 * Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
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

#include "keyboard_common.h"

#ifndef NO_LED
#    define NO_LED 255
#endif

// Battery indicator LEDs: top row (TAB through BSPC)
const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

// clang-format off
led_config_t g_led_config = {
    // Key Matrix to LED Index (4x12 scan matrix)
    // Row 3, Col 1 is NO_LED (space between MO2 and DEL in bottom row)
    {
    { 0,       1,       2,       3,       4,       5,       6,       7,       8,       9,       10,      11      },
    { 12,      13,      14,      15,      16,      17,      18,      19,      20,      21,      22,      23      },
    { 24,      25,      26,      27,      28,      29,      30,      31,      32,      33,      34,      35      },
    { 36,      NO_LED,  37,      38,      39,      40,      41,      42,      43,      44,      45,      46      }
    },
    // LED Index to Physical Position
    {
    { 0,  10}, { 20, 10}, { 40, 10}, { 60, 10}, { 80, 10}, {100, 10}, {120, 10}, {140, 10}, {160, 10}, {180, 10}, {200, 10}, {224, 10},
    { 0,  20}, { 20, 20}, { 40, 20}, { 60, 20}, { 80, 20}, {100, 20}, {120, 20}, {140, 20}, {160, 20}, {180, 20}, {200, 20}, {224, 20},
    { 0,  30}, { 20, 30}, { 40, 30}, { 60, 30}, { 80, 30}, {100, 30}, {120, 30}, {140, 30}, {160, 30}, {180, 30}, {200, 30}, {224, 30},
    { 0,  40},            { 40, 40}, { 60, 40}, { 80, 40}, {100, 40}, {120, 40}, {140, 40}, {160, 40}, {180, 40}, {200, 40}, {224, 40}
    },
    // LED Index to Flag (1 = per-key, 0 = indicator/underglow)
    {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    }
};
// clang-format on

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    bool result = kb_rgb_matrix_indicators_common(led_min, led_max);

    // Show current BLE channel / 2.4G persistently (not just during pairing or Fn-hold)
    if (!Led_Rf_Pair_Flg && !Key_Fn_Status && Keyboard_Info.Key_Mode != QMK_USB_MODE) {
        kb_show_current_connection_mode();
    }

    return result;
}

void notify_usb_device_state_change_user(struct usb_device_state usb_device_state) {
    kb_notify_usb_device_state_change(usb_device_state);
}

bool led_update_user(led_t led_state) {
    return kb_led_update(led_state);
}

void housekeeping_task_user(void) {
    kb_housekeeping_task();
}

void board_init(void) {
    kb_board_init();
}

void keyboard_post_init_user(void) {
    kb_keyboard_post_init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return kb_process_record_common(keycode, record);
}

// ============================================================================
// Compatibility shims for patched core files
// This repo's action_util.c/h call these instead of host_keyboard_send()
// and del_key() directly. The open-source library installs its own host
// driver, so routing through host_keyboard_send() is correct here.
// ============================================================================

void User_send_nkro_report(void) {
    keyboard_report->mods = get_mods() | get_weak_mods() | get_oneshot_mods();
    host_keyboard_send(keyboard_report);
}

void User_send_6kro_report(void) {
    keyboard_report->mods = get_mods() | get_weak_mods() | get_oneshot_mods();
    host_keyboard_send(keyboard_report);
}

void del_key_from_report(uint8_t key) {
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == key) {
            keyboard_report->keys[i] = 0;
        }
    }
}
