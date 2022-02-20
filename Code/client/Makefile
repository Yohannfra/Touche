# BOARD=nrf52840dongle_nrf52840
BOARD=nrf52840dk_nrf52840

build:
	west build -b $(BOARD) -d build/$(BOARD)
	@cp build/$(BOARD)/compile_commands.json .


flash_dongle:
	nrfutil pkg generate --hw-version 52 --sd-req=0x00 \
			--application build/$(BOARD)/zephyr/zephyr.hex \
			--application-version 1 client.zip && \
	nrfutil dfu usb-serial -pkg client.zip -p /dev/tty.usbmodemDCCE98444FED1

flash:
	west flash -d build/$(BOARD)/

gdb:
	west debug -d build/$(BOARD)/

lint:
	cppcheck --quiet --enable=warning,style,performance,portability src ../shared

menuconfig:
	west build -b $(BOARD) -t menuconfig

.PHONY: build flash_dongle flash gdb lint menuconfig
