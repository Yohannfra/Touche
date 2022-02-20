# Client source code

### Build

You must have the pio command available.

```bash
make           # debug version
make_release   # release version
```

### Flash

```bash
make flash           # debug version
make flash_release   # release version
```

### Change the default player

If it's the first time you program and Arduino with this code you must set which 'Player' it will be, it can be **PLAYER_1** or **PLAYER_2**
Once it's done once for an Arduino you should not need to change that anymore.

Change it in **./include/config.h** line 28

```cpp
#define PLAYER_ROLE PLAYER_1  // change value to PLAYER_1 or PLAYER_2
```
