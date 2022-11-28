# Touché Project
# Copyright (C) 2021 Assouline Yohann
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# defaults player role
# PLAYER_ROLE=0

# export PLATFORMIO_BUILD_FLAGS = -DPLAYER_ROLE=$(PLAYER_ROLE)

# defaults
all: debug
flash: flash_debug
clean: clean_debug

# debug config
debug:
	@pio run -e debug

flash_debug:
	@pio run -e debug --target upload

clean_debug:
	@pio run -e debug --target clean

# release config
release:
	@pio run -e release

flash_release:
	@pio run -e release --target upload

clean_release:
	@pio run -e release --target clean

# common
clean_all: clean_debug clean_release

fclean:
	$(RM) -r .pio

re: fclean all

lint:
	cppcheck --quiet --enable=warning,style,performance,portability src include lib/** ../shared/*.h ../shared/libraries/**

compiledb:
	@pio run --target compiledb

.PHONY: all flash clean debug flash_debug clean_debug release \
		flash_release clean_release clean_all fclean re lint compiledb
