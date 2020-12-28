## Wireless System For Fencing (WSFF)

---

A wireless scoring system for fencing based on **arduino** and **nrf24l01**.

It works for **epee** and **foil** support is in the roadmap.

---

This project is composed of parts : the client and the server
- The client is the board that each player will use and plug their weapons to
- The server is the scoring system, it turn on lights and play sounds if a player hits

---

## About the directory structure
Each directory has it's own README.md to explain this with more details.
```
.
├── Archive     # some old versions of the project
├── Documents   # pcb sources, fritzing schematics and datasheets of the components
├── client      # source code of the client
├── demo        # videos/demos of the system
├── server      # source code of the server
├── shared      # source code that is used in both client and server
└── tools       # a bunch of usefull scripts/programms I made for this project
```

## Licence

This project is licensed under the terms of the MIT license.
