# Building TP Randomizer

For more information about developing for the Randomizer, please check the [wiki](https://wiki.zeldatp.net/Dev).

## Table of contents

- [Prerequisites](#prerequisites)
  - [Windows](#windows)
  - [Non-Windows](#non-windows)
- [Building](#building)
  - [Building the Randomizer](#building-the-randomizer)
- [Testing in Dolphin](#testing-in-dolphin)
  - [Loading the Randomizer](#loading-the-randomizer)

## Prerequisites

### Windows

Install [devkitPro](https://devkitpro.org/wiki/Getting_Started) which is used to compile the Randomizer code to PowerPC instructions which the GameCube and Wii understand.

1. Download the graphical installer by following the above link.

1. Within the installer, the following selections are recommended:

   - "Download and install/install from downloaded files"
   - "Remove downloaded files"
   - For components to install, you must leave "Gamecube Development" checked.
     - It is recommended that you also leave "Wii Development" checked since there are plans for the Randomizer to support Wii versions in the future.
       You can uncheck the others options.
   - You can leave the Destination Folder as the default (likely `C:\devkitPro`).
   - You can leave the Start Menu folder as the default.
   - Click "Install".
     Installation may take a few minutes.

1. Once installation finishes, navigate to the devkitPro folder (likely `C:\devkitPro`).

1. Change to the `msys2` folder, then run `msys2.exe` by double-clicking.<br>
   _([MSYS2](#https://www.msys2.org) is a collection of tools and libraries providing you with an easy-to-use environment for building, installing and running native Windows software.)_

1. Within the `msys2` shell, run the following to install `python3` and `git` for the msys2 environment:

   ```
   pacman -S python3 git
   ```

   - You can ignore any warnings about conflicting packages and proceed with installation.

**NOTE: it is recommended that you use `msys2.exe` as your shell when building the Randomizer.**

### Non-Windows

If you would like to provide instructions for non-Windows environments, we would be happy to review your pull request. Thanks!

## Building

The commands you should run to clone the Randomizer repository will vary depending on whether or not you plan to create any pull requests:

- If you would like to contribute commits to the Randomizer, fork the repository, then clone your fork:
  ```
  git clone https://github.com/your-username/Randomizer.git
  ```
- If you are just trying it out, run the following:
  ```
  git clone https://github.com/zsrtp/Randomizer.git
  ```

Change to the new `Randomizer` directory:

```
cd Randomizer
```

Run the following two commands to fetch and update the [libtp_rel](https://github.com/zsrtp/libtp_rel) dependency:

```
git submodule init
git submodule update --remote
```

### Building the Randomizer

Navigate to the `GameCube` directory.

```
cd GameCube
```

To build the Randomizer for all TP versions, you can run the `make` command.

However! When developing a feature, you may find it quicker to initially build for a single version of the game.
Once your feature works for a single version, you can work to support all versions.

Here is an example of how to build for the US GameCube version only:

```
make us
```

_(See the Makefile for all available commands.)_

Running `make us` will generate a `Randomizer.us.gci` file.

The `gci` is a self-contained memory card file entry, and it contains our Randomizer code.

## Testing in Dolphin

_These instructions assume you built a US GameCube GCI.
For other TP versions, paths will be slightly different._

To test your changes in [Dolphin Emulator](#https://dolphin-emu.org), Dolphin needs to be able to find your Randomizer GCI file.

1. Within Dolphin, navigate to `Options > Configuration`.
1. Within the popup, change to the `GameCube` tab.
1. Change the dropdown next to `Slot A:` to `GCI Folder`.
   - The GCI Folder is a folder on your computer which Dolphin will read and write GCI files to.
     You can think of the GCI Folder as a memory card and the GCI files it contains as files on the memory card.
     The GCI Folder is where we will put your generated Randomizer GCI file.
1. Close the popup.

The GCI Folder will likely be '`<My-Dolphin-Folder>/User/GC/USA/Card A`' for US games.

If this path does not exist, you can do one of the following:

- Manually create the folders as necessary.
- Open a US GameCube game in Dolphin and create a save file.

Now that your GCI Folder is set up and Dolphin knows where to find it, you can copy your generated Randomizer GCI file there.

### Loading the Randomizer

You should now have the generated Randomizer GCI file in the GCI Folder.

If you were to start up TP in Dolphin at this point, the Randomizer code will NOT load.
This is because the only file on a memory card which the vanilla TP game loads in the TP save file (the Randomizer REL is not a TP save file).

Normally the steps to load the Randomizer REL are as follows:

- Put a special REL Loader TP save file on the memory card.
- Start up TP.
  - TP will load the hacked save file.
- Select the REL Loader quest log.
  - This causes TP to execute some custom instructions which were in the hacked save file.
- The game will load in the Randomizer code.

Repeating these steps every time you want to test a change is a little cumbersome, so we can do the following instead:

1. Right-click on your TP game in Dolphin and select `Properties`.
1. In the popup, change to the `Gecko Codes` tab.
1. Click the `Add New Code...` button.
1. In the new popup, set the `Name` to `Randomizer REL Loader`.
1. Set the `Creator` to `TP Randomizer` or whatever you would like.
1. In `Notes:`, you can put the following:
   ```
   Automatically loads the TP Randomizer REL when starting up the game.
   ```
1. In `Code:`, copy and paste the following:
   ```
   06004218 0000000f
   43757374 6f6d2052
   454c2046 696c6500
   c20063f8 0000003a
   3fe08000 3fc0802c
   3fa08033 3f808035
   3b600000 3f40000f
   635a4240 63836a4c
   7c6803a6 38600000
   38800000 38a00000
   4e800021 2c03ffff
   4082000c 375affff
   4181ffdc 2c030000
   4082017c 638372f4
   7c6803a6 38600000
   3c80803e 60840f40
   38a00000 4e800021
   2c030000 40820158
   38800014 480000e5
   7c7a1b78 63837f98
   7c6803a6 38600000
   63e44218 7f45d378
   4e800021 2c030000
   40820104 38800200
   480000b9 7c781b78
   638388cc 7c6803a6
   7f43d378 7f04c378
   38a00200 38c02000
   4e800021 2c030000
   408200bc 83380040
   3b3901ff 5739002c
   7f04c378 4800006d
   7f24cb78 48000075
   7c781b78 638388cc
   7c6803a6 7f43d378
   7f04c378 7f25cb78
   38c02200 4e800021
   2c030000 40820078
   80980020 48000045
   7c791b78 63a3e510
   7c6803a6 7f03c378
   7f24cb78 4e800021
   2c030001 40820038
   933f42dc 931f42e0
   83780034 48000048
   63c3f7ac 7c6903a6
   806d86b4 4e800420
   63c3f128 7c6903a6
   806d86b4 38a00020
   4e800420 63a3e7a8
   7c6803a6 7f03c378
   4e800021 7f24cb78
   4bffffc9 7f04c378
   4bffffc1 638380b4
   7c6803a6 7f43d378
   4e800021 7f44d378
   4bffffa9 638373d8
   7c6803a6 38600000
   4e800021 2c1b0000
   4182000c 7f6803a6
   4e800021 3c60803f
   60000000 00000000
   ```
1. Click the `Save` button.
1. Make sure the checkbox next to the new `Randomizer REL Loader` entry is checked, then close the popup.

Now whenever you start up the game, the Randomizer code will automatically load.

_(If you would like to play TP without loading the Randomizer, you can uncheck the box next to `REL Loader`.)_
