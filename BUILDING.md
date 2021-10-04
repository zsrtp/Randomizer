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

Install [devkitPro](https://devkitpro.org/wiki/Getting_Started) which is used to compile the Randomizer code to PowerPC instructions which the GameCube understands.

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
   _([MSYS2](https://www.msys2.org) is a collection of tools and libraries providing you with an easy-to-use environment for building, installing and running native Windows software.)_

1. Within the `msys2` shell, run the following to install `python3` and `git` for the msys2 environment:

   ```
   pacman -S python3 git
   ```

   - You can ignore any warnings about conflicting packages and proceed with installation.

**NOTE: it is recommended that you use `msys2.exe` as your shell when building the Randomizer.**

### Non-Windows

If you would like to provide instructions for non-Windows environments, we would be happy to review your pull request. Thanks!

## Building

The command you should run to clone the Randomizer repository will vary depending on whether or not you plan to create pull requests.

- If you think you might contribute commits to the Randomizer, fork the repository, then clone your fork:

  ```
  git clone https://github.com/<your-username>/Randomizer.git
  ```

- If you are just tinkering, you can use the following:

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

However! When developing a feature, you may find it quicker to initially develop for a single version of the game.
Once your feature works for a single version, you can work to support all versions.

Here is an example of how to build for the US GameCube version only:

```
make us
```

_(See the Makefile for all available commands.)_

Running `make us` will generate a `Randomizer.us.gci` file.
This GCI is a self-contained memory card file entry, and it contains our Randomizer code.

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
- The game will load the Randomizer code.

Repeating these steps every time you want to test a change is a little cumbersome, so we can do the following instead:

1. Right-click your TP game in Dolphin and select `Properties`.
1. In the popup, change to the `Gecko Codes` tab.
1. Click the `Add New Code...` button.
1. In the new popup, set `Name:` to `Randomizer REL Loader`.
1. Set `Creator:` to `Zephiles`
1. In `Notes:`, you can put the following:

   ```
   Automatically loads the TP Randomizer REL when starting up the game.
   ```

1. In `Code:`, copy and paste one of the following:
 - [US](https://pastebin.com/ES58EG3Z)
 - [EU](https://pastebin.com/MvaeFAyV)
 - [JP](https://pastebin.com/uRXqGGiq)

1. Click the `Save` button.
1. Make sure the checkbox next to the new `Randomizer REL Loader` entry is checked, then close the popup.

Now whenever you start up the game, the Randomizer code will automatically load.

_(If you would like to play TP without loading the Randomizer, you can uncheck the box next to `REL Loader`.)_
