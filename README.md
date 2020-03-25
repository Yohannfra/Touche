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

## Components
[Esp32](https://www.amazon.fr/AZ-Delivery-NodeMCU-d%C3%A9veloppement-d%C3%A9nergie-successeur/dp/B071P98VTG/ref=sr_1_3?keywords=esp32&qid=1568269992&s=gateway&sr=8-3) x 3 : 30€\
[Neopixel Ring](https://www.adafruit.com/product/1643) : 7€\
[Buzzer](https://www.amazon.fr/Saim-Lzq-3022-%C3%A9lectronique-Alarme-sonore-Buzzer/dp/B073RZFZ3P/ref=sr_1_8?__mk_fr_FR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&keywords=buzzer+12v&qid=1585170020&sr=8-8) x 2 : 10€\
[Banana Connectors](https://www.amazon.co.uk/KEESIN-Binding-Amplifier-Terminal-Connector-Type-D/dp/B077T2FC7K/ref=sr_1_53?keywords=Banana+plugs&qid=1585170164&s=electronics&sr=1-53&swrs=62F105F7CFECBA9A955371224D113825) * 20 : 10€\
[micro usb connector](https://www.amazon.fr/dp/B07RDHNL9H/ref=psdc_2908498031_t1_B07GZKMPJ8) x 10 : 7€\
[batteries](https://www.amazon.fr/dp/B07KKB874V?ref=ppx_pop_mob_ap_share) x 4 : 17€\
[power regulator](https://www.amazon.fr/dp/B07DJZKMYM?ref=ppx_pop_mob_ap_share) x 5 : 7€

**Total** : ~70€