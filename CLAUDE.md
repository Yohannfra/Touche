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

- `Code/shared/protocol.h` defines the radio protocol — see the "Radio protocol" section below.
- `Code/shared/libraries/` (RadioModule, Timer, utils) is pulled into both builds via `lib_extra_dirs` in each `platformio.ini`; `Code/shared/*.h` headers are on the include path via `-iquote ../shared`.
- Per-target device drivers live in `Code/{client,server}/lib/` as PlatformIO libraries (client: Weapon, VirtualGround, RGB_Led, PlayerConfig; server: ActionManager, Button, Buzzer, LedRing, Potentiometer, ServerConfig).
- Hardware pin assignments and defaults are in `Code/{client,server}/include/config.h`. A client's identity is set with `PLAYER_ROLE` (PLAYER_1 or PLAYER_2) in `Code/client/include/config.h` — it is persisted on the device, so it only needs to be set the first time an Arduino is flashed.
- Logging uses a fork of ArduinoLog; debug builds log to Serial at 9600 baud, release builds compile logging out with `DISABLE_LOGGING`.

## Radio protocol

Defined in `Code/shared/protocol.h` (packet/ack layout) and `Code/shared/libraries/RadioModule/` (transport).

Clients send packets to the server; the server never initiates — it replies via the nRF24 auto-ack payload.

**Packet (client → server)** — a single byte (`packet_t`):

```
bits 7-6: sender role (touche_role_e: PLAYER_1=0, PLAYER_2=1, SERVER=2)
bits 5-0: payload type (payload_type_e)
```

Payload types: `HIT`, `INVALID_HIT`; `CALIBRATION_STARTING` / `CALIBRATION_END` / `CALIBRATION_FAILED`; `CHANGING_TO_EPEE` / `CHANGING_TO_FOIL` / `CHANGING_TO_SABRE`; `ENABLE_PISTE_MODE` / `DISABLE_PISTE_MODE`.

Note `HIT = 1`, so a packet value of 0 means "no message" (`RadioModule::receiveMsg()` returns 0 when nothing was read). Always use `CREATE_PACKET(role, payload)` / `GET_ROLE(p)` / `GET_PAYLOAD(p)` rather than manual bit twiddling.

**Ack payload (server → client)** — a single byte (`ack_payload_t`) carrying the server state, returned by `RadioModule::sendMsg()`:

```
bit 3: piste mode enabled
bit 2: SABRE    } exactly one
bit 1: FOIL     } weapon bit
bit 0: EPEE     } is set
0xFF (ACK_ERROR): send failed or no ack payload received
```

Build it with `CREATE_ACK_PAYLOAD(pisteEnabled, weapon)`; the server stages it with `RadioModule::setAckPayload()` so it is attached to the ack of the *next* received packet — clients learn state changes lazily, on their next transmission.

**Transport details** (`RadioModule`, `Code/shared/radioPipes.h`):

- 250 kbps / max PA level for range; payload size is 1 byte; dynamic payloads enabled (required for ack payloads).
- Each player has its own pipe address (`PIPES_ADDRESSES` in `radioPipes.h`); the server listens on both.
- Collision handling for simultaneous hits: hardware retry delays differ per player (`setRetries`), and `sendMsg()` adds a software retry loop (up to 250 ms) with a per-role backoff before giving up with `ACK_ERROR`.

## Conventions

- All source files carry the GPL-3.0 license header — include it in new files.
- Build flags are `-Wall -Wextra`; keep code warning-clean.
