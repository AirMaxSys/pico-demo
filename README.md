Clone all submodules with one CMD:
```git
git clone https://github.com/AirMaxSys/pico_demo.git --recurse-submodules
```
Or using separate CMDs:
```git
git clone https://github.com/AirMaxSys/pico_demo.git
git submodule update --init --recursive
```
Make sure set cmake environment variables right.
```cmake
set(PICO_SDK_PATH "../sdk/pico-sdk")
set(CMAKE_C_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/arm-none-eabi-g++")
```