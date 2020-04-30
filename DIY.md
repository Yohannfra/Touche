# A tutorial to help you create your wireless fencing system

## Components and supplies

- [3 : esp32 devboards](https://www.amazon.fr/AZDelivery-NodeMCU-d%C3%A9veloppement-d%C3%A9nergie-successeur/dp/B074RGW2VQ/ref=sr_1_3?dchild=1&keywords=esp32&qid=1587810621&sr=8-3)
- [3 : Neopixel ring](https://www.amazon.fr/dp/B07TZK9DNT/ref=twister_B0822WQBQX?_encoding=UTF8&psc=1)
- [1 : 12V buzzer](https://www.amazon.fr/LZQ-3022-Discontinu-alarme-Avertisseur-Sonore/dp/B010V4UVHG/ref=sr_1_11?__mk_fr_FR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=buzzer+12v&qid=1587810751&sr=8-11)
- [6 : banana plugs](https://www.amazon.co.uk/KEESIN-Binding-Amplifier-Terminal-Connector-Type-D/dp/B077T2FC7K/ref=sr_1_53?keywords=Banana+plugs&qid=1585170164&s=electronics&sr=1-53&swrs=62F105F7CFECBA9A955371224D113825)
- [3 : micro USB Tp4056 charger circuits](https://www.amazon.fr/Tp4056-Chargeur-Batterie-Lithium-Charger/dp/B07NVBLMVQ/ref=sr_1_4?dchild=1&keywords=tp4056&qid=1586195969&sr=8-4)
- [3 : 3.7V batteries](https://www.amazon.fr/dp/B07KKB874V?ref=ppx_pop_mob_ap_share)
- [3 : power switches](https://www.amazon.fr/TOOGOO-broches-Positions-commutateur-glissiere/dp/B00X3KCA0M/ref=sr_1_5?__mk_fr_FR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=KP9NN4MA18AC&dchild=1&keywords=interrupteur+a+glissiere&qid=1587811346&s=hi&sprefix=interrupteur+a+g%2Cdiy%2C148&sr=1-5)

#### Total cost : ~ 100€

## Building tools

- soldering iron
- 3d printer (i used an Ender 3, so event a cheap one should work)
- screwdriver
- a few screw
- some electric wire
- a hot glue pistol


## 3d printing

You can find all the files to print [here](thingverselink).

You need to print
- 2 : client_base.stl
- 2 : client_cover.stl
- 1 : server_base.stl
- 1 : server_cover.stl

The two bases need printing support.\
On my ender 3 without the adhesion it fails so i'd reccomend you to print all parts with adhesion.

## Flashing the boards

**An unix based system is needed for this part (Linux/Mac)**

- Install the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
- Install [PlatformIO](https://platformio.org/)
- Clone and go to the repository
    ```
    $ git clone https://github.com/Yohannfra/WSFF && cd WSFF
    ```
- Sort yours esp32, 2 will be the clients and one will be the server
- Change directory
    ```
    $ cd tools/get_esp32_mac_address
    ```
- For each esp32 :
    - Plug the board to the computer and type
        ```
        make && make flash
        ```
    - Open screen to view the value of the mac address
        ```
        screen /dev/ttyUSB0 115200
        ```
    - Edit the file **constants.cpp** and replace the mac addresses with yours
        ```
            $ nano ../../shared/constants.cpp
        ```
    - Unplug the board

- Now go to the client directory
    ```
    $ cd ../../client/
    ```
- For your two client boards
    - Plug the board to the computer and type
        ```
        $ make && make flash
        ```
    - Unplug the board
- Now the server board
    ```
        cd ../server/
    ```
    - Plug the board to the computer and type
        ```
        $ make && make flash
        ```
    - Unplug the board

- Done !

## Soldering and assembling

**You need all the 3d printed parts now**
