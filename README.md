# TowerOfPain
Tower Of Pain game for Arduboy

Tower Of Pain is a simple hack game, inspired by the likes of Hack 1982, but simplified to fit in Arduboy miniature game system.
Contains other elements inspired by different rpg games, but much was done without checking the source to avoid copy/paste of "how" it should work.

Please refer to https://community.arduboy.com/ on how to acquire, compile or upload games to the Arduboy system.

There is an emulator named 'ProjectABE' that can be use. But please be aware of the sound setting before loading a game, as the sound may be a bit to loud at the start depending on your system.

Regarding the last point, Tower Of Pain sound seems to work well on the Arduboy system, but on emulators not so much.. as it relies on the frame count to determine when to produce a beep.

Point pending so far:
- Better sound control
- Better map and enemy spawning (currently uses a simple walker method)
- 15 out of 20 enemies are available (current code capacity is at 97%)

Compilation log:

May 30, 2021
Sketch uses 27942 bytes (97%) of program storage space. Maximum is 28672 bytes.
Global variables use 1520 bytes (59%) of dynamic memory, leaving 1040 bytes for local variables. Maximum is 2560 bytes.
