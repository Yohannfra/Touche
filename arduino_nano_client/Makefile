all: build

build:
	@pio run -e debug

release:
	@pio run -e release

flash:
	@pio run --target upload

clean:
	@pio run --target clean

.PHONY: build flash clean all release
