/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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

#define TAPPING_TERM 300

// Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT

// This mode functions like Accelerated mode, however, you can hold KC_ACL0, KC_ACL1 and KC_ACL2 to momentarily (while held) set the cursor and scroll speeds to constant speeds. When no acceleration keys are held, this mode is identical to Accelerated mode, and can be modified using all of the relevant settings.,
#define MK_COMBINED

#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_MAX_SPEED

// #define MOUSEKEY_INTERVAL 16
// #define MOUSEKEY_DELAY 0
// #define MOUSEKEY_TIME_TO_MAX 60
// #define MOUSEKEY_MAX_SPEED 7

#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 2    // 3
#define MOUSEKEY_TIME_TO_MAX 16 // 42 // 52

#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 46
#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 8

// hoeveel tijd je hebt om de leader key sequence te voltooien
#define LEADER_TIMEOUT 300
#define LEADER_PER_KEY_TIMING // dan komt er per key tijd bij om de sequence te voltooien

// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
#define EE_HANDS
