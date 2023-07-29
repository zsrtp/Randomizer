The assembly used for the codehandler in this folder was taken from the **Neogamma** project, which can be found [here](https://github.com/iGlitch/Neogamma/tree/master/code_handler_source). The **Neogamma** project is licensed under **GNU GPL, version 2**, so a license file for that has been included in this folder.

The assembly is intended to be built using the following three programs (in which **file** is replaced with the filename):
```
powerpc-eabi-gcc -nostartfiles -nodefaultlibs -Wl,-Ttext,0x80001800 -o file.elf file.s

powerpc-eabi-strip --strip-debug --strip-all --discard-all -o file.elf -F elf32-powerpc file.elf

powerpc-eabi-objcopy -I elf32-powerpc -O binary file.elf file.bin
```
The binary can then be passed to `file2header.py` to create a header file that contains the raw bytes of the binary in a **uint8_t** array, which can then be used in the main project's code. Additonal arguments for `file2header.py` can be seen by passing **-h** to it.