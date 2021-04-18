/*
WSFF Project
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

#ifndef RADIOPIPES_H
#define RADIOPIPES_H

#include <stdint.h>

/*
    Modify this file to change the addresses used by the NRF24l01 modules.
 */

static const uint64_t PIPES_ADDRESSES[2] = {
    0xB3B4B5B601LL, // PLAYER 1
    0xB3B4B5B602LL  // PLAYER 2
};

#endif // RADIOPIPES_H
