all: build

build:
	ln -s -f ../../shared/constants.cpp ./src/
	@pio run

flash:
	@pio run --target upload

clean:
	@pio run --target clean
