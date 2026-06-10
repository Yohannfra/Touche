# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project overview

Touché is a wireless scoring system for fencing (currently epee only) built on Arduino Nano (ATmega328) and nRF24L01 radios.

The system has one base station (the **server**) and two fencer boxes (the **clients**) — this server/client naming is used throughout the repo.

Besides firmware, the repo contains PCB sources and STL files (`Documents/`), a DIY tutorial (`Assembly_Guide/`), and old ESP32 prototypes (`Archive/` — do not develop there).

## Build commands

Firmware is built with PlatformIO (`pio` must be on PATH). Run make from `Code/client` or `Code/server` — both Makefiles expose the same targets:

```bash
make            # build debug (default env)
make release    # build release (defines DISABLE_LOGGING)
make flash      # build + upload debug over serial
make flash_release
make lint       # cppcheck over src, include, lib/**, and ../shared
make compiledb  # generate compile_commands.json via pio
make fclean     # remove .pio build dir
```

There are no automated tests; CI (`.github/workflows/build.yml`) builds debug and release for both client and server.

To monitor several boards at once: `scripts/monitor_3_devices.bash` (tmux + screen, 9600 baud).

## Architecture

```
Code/
├── client/   # fencer box firmware
├── server/   # base station firmware
└── shared/   # code compiled into both
```

- `Code/shared/protocol.h` defines the radio protocol: a packet is a single byte — 2 high bits for the sender role (`PLAYER_1`, `PLAYER_2`, `SERVER`), 6 low bits for the payload type (hit, calibration, weapon change, piste mode). Use `CREATE_PACKET` / `GET_ROLE` / `GET_PAYLOAD`. The server replies state to clients via the nRF24 ack payload (`CREATE_ACK_PAYLOAD`, bit layout documented in the header).
- `Code/shared/libraries/` (RadioModule, Timer, utils) is pulled into both builds via `lib_extra_dirs` in each `platformio.ini`; `Code/shared/*.h` headers are on the include path via `-iquote ../shared`.
- Per-target device drivers live in `Code/{client,server}/lib/` as PlatformIO libraries (client: Weapon, VirtualGround, RGB_Led, PlayerConfig; server: ActionManager, Button, Buzzer, LedRing, Potentiometer, ServerConfig).
- Hardware pin assignments and defaults are in `Code/{client,server}/include/config.h`. A client's identity is set with `PLAYER_ROLE` (PLAYER_1 or PLAYER_2) in `Code/client/include/config.h` — it is persisted on the device, so it only needs to be set the first time an Arduino is flashed.
- Logging uses a fork of ArduinoLog; debug builds log to Serial at 9600 baud, release builds compile logging out with `DISABLE_LOGGING`.

## Conventions

- All source files carry the GPL-3.0 license header — include it in new files.
- Build flags are `-Wall -Wextra`; keep code warning-clean.
