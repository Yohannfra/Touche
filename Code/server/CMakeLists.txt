cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(touche_server)

target_sources(app PRIVATE
    src/main.c

    src/actions_handler/actions_handler.c
    src/actions_handler/actions_handler.h

    src/buzzer/buzzer.c
    src/buzzer/buzzer.h

    src/led_ring/led_ring.c
    src/led_ring/led_ring.h

    ../shared/led/led.c
    ../shared/led/led.h

    ../shared/radio/radio.c
    ../shared/radio/radio.h
    )

target_include_directories(app PRIVATE
        ../shared
        ../shared/radio
        ../shared/led
    )
