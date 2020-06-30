all: build

build:
	ln -s -f ../../shared/constants.cpp ./src/
	ln -s -f ../../shared/Utils.cpp ./src/
	@pio run

debug:
	@pio debug

flash:
	@pio run --target upload

clean:
	@pio run --target clean
