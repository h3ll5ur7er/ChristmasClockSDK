# Christmas Clock

## Gitpod

When starting in gitpod, the environment is automatically prepared. All required packages are installed and the raspberry pi pico sdk is cloned from the git master branch.

## SDK Setup

Install the following packages to cross compile for the RP2040:

```bash
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

## Prepare build files (Pico SDK from git)

```bash
mkdir build
cd build
cmake -DPICO_SDK_FETCH_FROM_GIT=ON ..
```

## Prepare build files (local Pico SDK)

```bash
mkdir build
cd build
cmake -DPICO_SDK_PATH=/path/to/pico-sdk ..
```

## Build

```bash
make -j$(nproc)
```

## Deploy

- Press BOOTSEL button on the Pico board and reset the board
- Copy the `build/ChristmasClock.uf2` file to the Pico board
