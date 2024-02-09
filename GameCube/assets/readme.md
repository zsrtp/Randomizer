# Assets
This folder contains various assets, here is a brief explanation

## LST Files
Used for linking external symbols to memory addresses, to account for version differences there is one `.lst` file for each version (us, eu, jp)

## Banner & Icon
### Gamecube
To use a custom banner and icon in the resulting gci you want to look at the following files:
- banner.xcf
- icon.xcf
- ../bin/Tga2bti.exe (C) [Lunaboy](http://kuribo64.net/board/thread.php?id=1599)

1. Edit the template files in [gimp](https://www.gimp.org/)
2. Export as `TGA` with the following settings:

![](https://share.aecx.cc/E1B13M)
(No compression; Origin: Bottom Left)

3. Execute `Tga2bti.exe -4A3 <file.tga> <file.raw>` for both files (`icon` and `banner`)
_Note: `5A3` is _not_ supported by the tool but 4A3 seems to work just fine_


### Wii
To use a custom banner and icon(s) in the resulting save file, you want to look at the following files/folders:
- wii_banner.xcf
- icons/
- ../bin/img2wibn.py (C) [kipcode66](https://github.com/kipcode66/wii_tools)

1. Edit the template files in [gimp](https://www.gimp.org/)
2. Export as a `PNG`.

`./bin/img2wibn.py -t "Twilight Princess" -s "Randomizer" -f 0 -a 43690 assets/wii_banner.raw assets/wii_banner.png assets/icons/tpr_*`

the animation speed `43690` is `0xAAAA`. This is a 16 bit number that contains 2-bit speed value for each frame (8 frames max)