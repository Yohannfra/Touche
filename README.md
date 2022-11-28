# Touché

![](https://github.com/Yohannfra/Touche/workflows/Build/badge.svg)


![](.github/full_set.jpg)


## Overview

Touché is a wireless scoring system for fencing based on **Arduino** and **nrf24l01**.

The goal is to make an **affordable**, **open source** and **open hardware** system.

It currently only works for **epee**.

⚠️  Foil and  sabre support is in the roadmap but in a latter version that will certainly be on a different mcu (ESP32 or STM32).

#### The system is divided into 3 parts: one base station and two fencer boxes.

*During the early days of this project I called the base station the **server**
and the fencer boxes the **clients**, I will use this naming in this document
and across the project.*


## Getting started

To make a system you'll have to go through these steps:
1. Order the PCB and all the components
2. 3D print the boxes
3. Program the Arduino
4. Solder the PCB and assemble everything
5. Enjoy!

I wrote a step-by-step tutorial that you can find in [Assembly_Guide](./Assembly_Guide).

If you have a question about anything (please read the tutorial first) you can open a Github issue and I will try my best to answer you.

## About the directory structure

This repository contains all the **sources**, **3D files**, and **PCB files** needed to make this system.

```
.
├── Archive           # some old versions of the project
├── Documents         # pcb sources, and STL files
├── Code              # source code
├── Assembly_Guide/   # step by step tutorial to DIY
```
Each directory has its own README.md to explain this with more details.

## Roadmap

See Github issues.

## Contribute

If you have any improvement idea, find a bug or encounter a problem you can open a Github issue.

## License

All the code, CAD files, PCB files, and everything within this repository is licensed under the terms of the [GNU General Public License V3.0](./LICENSE).
