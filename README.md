# Tower Of Pain

Tower Of Pain is a simple roguelike game for the Arduboy, inspired by the classics like Hack (1982), but extremely simplified to fit in Arduboy miniature game system.

## Arduboy

Please refer to https://community.arduboy.com/ on how to acquire, compile or upload games to the Arduboy system.

## Gameplay

Tower Of Pain is a game of chance, as such your ability to reach the highest level may take some time (but is not impossible). A variety of options are available in each encounter and each level in the tower (some may be locked based on your actions).

![Alt Text](https://github.com/franalvarez21/TowerOfPain/blob/main/TowerOfPain/images/demo.gif)

You can:
- Attack, spare or run from an encounter.
- Use some of the items found in the dungeon.
- Talk with the enemies.

Each action may result in different outcomes, from simple ones to more complex ones...

Just remember... you don't have experience or levels... so you may not get stronger than at the start.

## Emulation notes

There is an emulator named 'ProjectABE' that can be used. But please be aware of the sound setting before loading a game, as the sound may be a bit too loud at the start depending on your system.

Regarding the last point, Tower Of Pain sound seems to work well on the Arduboy system, but on emulators not so much.. as it relies on the frame count to determine when to produce a beep.

https://github.com/felipemanga/ProjectABE

./ProjectABE TowerOfPain/distributable/TowerOfPain.ino.leonardo.hex

## Sound

Sound is always disabled by default, can be enabled in the main and pause menu.

Visual hints are displayed only if the sounds are disabled.

## Details

Nice to have (under consideration):
- Better sound control (for emulation compatibility)
- Better map and enemy spawning (currently uses a simple walker method, could be better)
- Code space optimizations.

## Compilation log

June 17, 2021. V1.2.0

Sketch uses 28536 bytes (99%) of program storage space. Maximum is 28672 bytes.
Global variables use 1530 bytes (59%) of dynamic memory, leaving 1030 bytes for local variables. Maximum is 2560 bytes.

June 10, 2021. V1.1.2

Sketch uses 28380 bytes (98%) of program storage space. Maximum is 28672 bytes.
Global variables use 1529 bytes (59%) of dynamic memory, leaving 1031 bytes for local variables. Maximum is 2560 bytes.

June 7, 2021. V1.1.1

Sketch uses 28286 bytes (98%) of program storage space. Maximum is 28672 bytes.
Global variables use 1522 bytes (59%) of dynamic memory, leaving 1038 bytes for local variables. Maximum is 2560 bytes.

June 7, 2021. V1.1

Sketch uses 28332 bytes (98%) of program storage space. Maximum is 28672 bytes.
Global variables use 1522 bytes (59%) of dynamic memory, leaving 1038 bytes for local variables. Maximum is 2560 bytes.

May 31, 2021. V1.0

Sketch uses 28236 bytes (98%) of program storage space. Maximum is 28672 bytes.
Global variables use 1522 bytes (59%) of dynamic memory, leaving 1038 bytes for local variables. Maximum is 2560 bytes.
