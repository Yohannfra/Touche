/*
Touché Project
Copyright (C) 2021 Assouline Yohann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "LedRing.hpp"

LedRing::LedRing(byte pin) : strip(2 * NEOPIXEL_RING_SIZE, pin, NEO_GRB + NEO_KHZ800)
{
    _colorPlayer1 = RED_RGB;
    _colorPlayer2 = GREEN_RGB;
}

void LedRing::init()
{
    strip.begin();
    strip.setBrightness(50);
    strip.show();
}

void LedRing::turn_off()
{
    strip.clear();
    strip.show();
}

void LedRing::set_color(color_t color, uint8_t start, uint8_t end)
{
    for (size_t i = start; i < end; i++) {
        strip.setPixelColor(i, color.r, color.g, color.b);
    }
    strip.show();
}

void LedRing::do_circle_annimation(color_t color)
{
    static uint8_t step = 0;

    if (color.r == 0 && color.g == 0 && color.b == 0) {  // reset annimation
        step = 0;
        turn_off();
        return;
    }

    uint8_t index = step % (2 * NEOPIXEL_RING_SIZE);

    strip.clear();
    set_color(color, 0, index);
    strip.show();
    step++;
}

void LedRing::blink(color_t color, int time_ms, size_t nb_blinks, uint8_t index)
{
    for (size_t i = 0; i < nb_blinks; i++) {
        set_color(color, index, NEOPIXEL_RING_SIZE * 2);
        delay(time_ms);
        turn_off();
        delay(time_ms);
    }
}

void LedRing::blinkBoth(color_t color, color_t color2, int time_ms, size_t nb_blinks)
{
    for (size_t i = 0; i < nb_blinks; i++) {
        set_color(color, 0, NEOPIXEL_RING_SIZE);
        set_color(color2, NEOPIXEL_RING_SIZE, NEOPIXEL_RING_SIZE * 2);
        delay(time_ms);
        turn_off();
        delay(time_ms);
    }
}

void LedRing::set_half_colors(color_t color_1, color_t color_2)
{
    for (size_t i = 0; i < 2; i++) {
        if (i % 2)
            strip.setPixelColor(i, color_1.r, color_1.g, color_1.b);
        else
            strip.setPixelColor(i, color_2.r, color_2.g, color_2.b);
    }
    strip.show();
}

void LedRing::show_hits(uint16_t hits)
{
    ActionManager::action_type_e action_player1 = static_cast<ActionManager::action_type_e>((hits >> 8) & 0xFF);
    ActionManager::action_type_e action_player2 = static_cast<ActionManager::action_type_e>(hits & 0xFF);

    // player 1
    if (action_player1 == ActionManager::VALID_HIT) {
        set_color(_colorPlayer1);
    } else if (action_player1 == ActionManager::INVALID_HIT) {
        set_color(ORANGE_RGB);
    }

    // player 2
    if (action_player2 == ActionManager::VALID_HIT) {
        set_color(_colorPlayer2, NEOPIXEL_RING_SIZE, NEOPIXEL_RING_SIZE * 2);
    } else if (action_player2 == ActionManager::VALID_HIT) {
        set_color(ORANGE_RGB, NEOPIXEL_RING_SIZE, NEOPIXEL_RING_SIZE * 2);
    }
}

void LedRing::switchColors()
{
    color_t tmp;

    memcpy(&tmp, &_colorPlayer1, sizeof(color_t));
    memcpy(&_colorPlayer1, &_colorPlayer2, sizeof(color_t));
    memcpy(&_colorPlayer2, &tmp, sizeof(color_t));
}

color_t LedRing::getPlayerColor(touche_role_e player)
{
    return player == PLAYER_1 ? _colorPlayer1 : _colorPlayer2;
}
