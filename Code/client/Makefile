# Touché Project
# Copyright (C) 2024 Assouline Yohann
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
## all: build debug version (default)
all: debug
## flash: build and upload debug version
flash: flash_debug
## clean: clean debug build
clean: clean_debug

.PHONY: debug
## debug: build debug version
debug:
	@pio run -e debug

.PHONY: flash_debug
## flash_debug: build and upload debug version
flash_debug:
	@pio run -e debug --target upload

.PHONY: clean_debug
## clean_debug: clean debug build
clean_debug:
	@pio run -e debug --target clean

.PHONY: release
## release: build release version
release:
	@pio run -e release

.PHONY: flash_release
## flash_release: build and upload release version
flash_release:
	@pio run -e release --target upload

.PHONY: clean_release
## clean_release: clean release build
clean_release:
	@pio run -e release --target clean

.PHONY: clean_all
## clean_all: clean debug and release builds
clean_all: clean_debug clean_release

.PHONY: fclean
## fclean: remove .pio directory
fclean:
	$(RM) -r .pio

.PHONY: re
## re: fclean then rebuild
re: fclean all

.PHONY: lint
## lint: run cppcheck on sources
lint:
	cppcheck -x c++ --quiet --enable=warning,style,performance,portability src include lib/** ../shared/*.h ../shared/libraries/**

.PHONY: compiledb
## compiledb: generate compile_commands.json
compiledb:
	@pio run --target compiledb

## help: show this help message
help: Makefile
	@echo
	@echo " Choose a command to run:"
	@echo
	@sed -n 's/^##//p' $< | column -t -s ':' |  sed -e 's/^/ /'
	@echo
