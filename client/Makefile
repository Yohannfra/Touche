#defaults
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

# write id config
write_role:
	@pio run -e write_role

flash_write_role:
	@pio run -e write_role --target upload

clean_write_role:
	@pio run -e write_role --target clean

# common
clean_all: clean_debug clean_release

fclean:
	$(RM) -r .pio

re: fclean all

.PHONY: all flash clean debug flash_debug clean_debug release \
		flash_release clean_release clean_all fclean re
