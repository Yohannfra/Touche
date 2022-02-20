cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(touche_client)

target_sources(app PRIVATE
    src/main.c
    src/alive.c

    src/button/button.c
    src/button/button.h

    src/mac_address/mac_address.c
    src/mac_address/mac_address.h

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
