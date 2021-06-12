# Step 3 : Programming

In this step I'll show how to program everything.

In this step I'll do everything with the command line (I'm on Mac) and those commands also work on linux. If you're on Windows you could use [WSL](https://docs.microsoft.com/fr-fr/windows/wsl/install-win10) or try to do everything with vscode.



Clone the git repository

```
$ git clone https://github.com/Yohannfra/Touche
```



Install platformio core : https://docs.platformio.org/en/latest//core/installation.html

Once it's done you should have the command pio

```
$ pio --version
PlatformIO Core, version 5.1.1
```

### Select the default weapon

in **Code/shared/touche.h** line number **78**

by default it's
```c
#define DEFAULT_WEAPON_MODE EPEE
```

For now only **EPEE** and **FOIL** are available.


### Server

Go to the server's directory

```
$ cd Code/server/
```



Build the code

```
$ make release
```



Plug the server's pcb

![plug the server's pcb](https://imgur.com/6HzyVyg.jpg)

and run

```
$ make flash_release
```

You can now unplug the server's pcb.

### Client

Now go to the client's directory

```
$ cd ../client
```



Build the code

```
$ make release
```



Plug the first pcb (**only the first**)

![flash client](https://imgur.com/OblcLCM.jpg)

and run

```
$ make flash_release
```

you can unplug the pcb. Normally when the **make flash_release** ended the led blinked in red.



Now you'll have to edit a file, open **include/config.h"** in the client's directory and change this line (line 28)

```c
#define PLAYER_ROLE PLAYER_1  // change value to PLAYER_1 or PLAYER_2
```

to

```c
#define PLAYER_ROLE PLAYER_2  // change value to PLAYER_1 or PLAYER_2
```

Now save the file and close it.



Now build the code again

```
$ make release
```



Plug the second client's pcb and run

```
$ make flash_release
```



And now you should be done with the programming part. You can skip the next part if you want to make only one system.



## If you want to make multiple systems



Between each system you should change the nrf24l01 pipes addresses, it's in the file **Touche/Code/shared/radioPipes.h"**



The default pipe address is

```cpp
static const uint64_t PIPES_ADDRESSES[2] = {
    0xB3B4B5B601LL,  // PLAYER 1
    0xB3B4B5B602LL   // PLAYER 2
};
```



You can change that to anything as long as :

- The length is the same
- The two addresses are differents
- You keep the **0x** at the beginning and the **LL** at the end

A few valid examples:

```cpp
static const uint64_t PIPES_ADDRESSES[2] = {
    0xB5C4B5B601LL,  // PLAYER 1
    0xB5C4B5B602LL   // PLAYER 2
};

static const uint64_t PIPES_ADDRESSES[2] = {
    0xB1B4B5B601LL,  // PLAYER 1
    0xB1B4B5B602LL   // PLAYER 2
};

static const uint64_t PIPES_ADDRESSES[2] = {
    0xA9B4B5B601LL,  // PLAYER 1
    0xA9B4B5B602LL   // PLAYER 2
};

// ...
```

Refer to this thread if you want to know more about it: https://arduino.stackexchange.com/questions/2946/nrf24l01-pipe-question
