## Wireless System For Fencing (WSFF)

A wireless scoring system for fencing based on esp32 chips and [ESP-NOW] protocol

This project is composed of parts : the client and the server
- The client is the board that each player will use and plug their weapons to
- The server is the scoring system, it turn on lights and play sounds it a player hit

## Build process

Both parts are build using [platformIO](https://platformio.org/)

A unix based system is needed to build this project, I will add later the support for Windows.

To build the client
```bash
$ cd client
$ make
```
To build the server
```bash
$ cd server
$ make
```

That's all

## Flashing the boards

To flash the client, connect the esp32 via usb and run
```bash
$ cd client
$ make flash
```

To flash the server, connect the esp32 via usb and run
```bash
$ cd server
$ make flash
```
