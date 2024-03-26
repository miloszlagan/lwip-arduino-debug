# LwIP Arduino Debug

Setup for debugging Arduino and LwIP behaviour under full ESP-IDF build system.

## Setup

1. Init submodules

```bash
git submodule update --init --recursive
```

Due to a Arduino having C++-ish compilation rules a patch in `components/AsyncTCP/CMakeLists.txt` is required to compile the project.

```cmake
target_compile_options(${COMPONENT_TARGET} PRIVATE -fno-rtti -Wno-error=address)
```

2. Setup the ESP-IDF environment

Install recommended ESP-IDF extension for VSCode. Run `>ESP-IDF: Configure ESP-IDF Extension` and follow configuration steps.

Personally I have installed the ESP-IDF toolchain files to seperate folders to accomodate multiple versions of the ESP-IDF:
```
~/esp-idf
    v4/
    tools-v4/
    v5/
    tools-v5/
```

To do this select `Advanced` installation and set the `ESP-IDF Path` and `ESP-IDF Tools Path` to the appropriate folders.

3. Setup and build

Open terminal via `>ESP-IDF: Open ESP-IDF Terminal` task and setup WiFi in `Example Connection Configuration` menu:
  
```bash
idf.py menuconfig
```

Exit and save the configuration. Then build the project:

```bash
idf.py build
```

4. Flash and monitor

```bash
idf.py flash monitor
# or use a better serial monitor
idf.py flash && tio /dev/ttyACM0 -b 115200
```

Built-in monitor can by closed by pressing `Ctrl+]`. To close `tio` press `Ctrl+t` `q`.

## Debugging

Launch `Launch` configuration in VSCode `Run and Debug` tab. This will start the GDB server and attach to the target. You can now set breakpoints and inspect the code.

Good luck.
