# Crazyflie Firmware  [![Build Status](https://api.travis-ci.org/bitcraze/crazyflie-firmware.svg)](https://travis-ci.org/bitcraze/crazyflie-firmware)

This project contains the source code for the Crazyflie 2.0 firmware with modification allowing SITL and HITL simulation.

## Modifications for SITL and HITL

The modifications made in order to have SITL and HITL possible includes the following files :

### sitl_make/CMakeLists.txt
This file is the cmake file in order to build crazyflie instance for SITL simulation. It's doing the same work as the original Makefile but rather include fake sensors, actuators and remove all low level dependencies. The crazyflie instance ```cf2``` is built using your default c++/c compiler.

##### In default SITL compilation the procedure is the following :
```sh
cd crazyflie-firmware/sitl_make
mkdir build
cd build
cmake ..
```

##### For compilation with verification tool enabled
```sh
cd crazyflie-firmware/sitl_make
mkdir build
cd build
cmake .. -DBUILD_VERIF=ON
```
You can change the verification algorithm parameter by changing [one of the following](https://github.com/wuwushrek/crazyflie-firmware/blob/24a9c046737a53d2775a927824fb75cc4389cd55/sitl_make/CMakeLists.txt#L47-L49) line in the CMakeList.txt file. This can also be accomplished by disabling this lines and setting the parameter in [config_outer.h](https://github.com/wuwushrek/crazyflie-firmware/blob/master/src/outer_ode/interface/config_outer.h).

### src/config/FreeRTOSConfig.h, src/config/config.h, src/lib/FreeRTOS/portable/GCC/Linux/port.c, src/lib/FreeRTOS/portable/GCC/Linux/portmacro.h

The modifications here implies configuration of FreeRTOS for Linux support and definition of 
## Dependencies

You'll need to use either the [Crazyflie VM](https://wiki.bitcraze.io/projects:virtualmachine:index),
[the toolbelt](https://wiki.bitcraze.io/projects:dockerbuilderimage:index) or
install some ARM toolchain.

### Install a toolchain

#### OS X
```bash
brew tap PX4/homebrew-px4
brew install gcc-arm-none-eabi
```

#### Debian/Ubuntu

Tested on Ubuntu 14.04 64b, Ubuntu 16.04 64b, and Ubuntu 18.04 64b:

For Ubuntu 14.04 :

```bash
sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded
sudo apt-get update
sudo apt-get install libnewlib-arm-none-eabi
```

For Ubuntu 16.04 and Ubuntu 18.04:

```bash
sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
sudo apt-get update
sudo apt install gcc-arm-embedded
```

Note: Do not use the `gcc-arm-none-eabi` package that is part of the Ubuntu repository as this is outdated.

#### Arch Linux

```bash
sudo pacman -S community/arm-none-eabi-gcc community/arm-none-eabi-gdb community/arm-none-eabi-newlib
```

#### Windows

The GCC ARM Embedded toolchain for Windows is available at [launchpad.net](https://launchpad.net/gcc-arm-embedded/+download). Download the zip archive rather than the executable installer. There are a few different systems for running UNIX-style shells and build systems on Windows; the instructions below are for [Cygwin](https://www.cygwin.com/).

Install Cygwin with [setup-x86_64.exe](https://www.cygwin.com/setup-x86_64.exe). Use the standard `C:\cygwin64` installation directory and install at least the `make` and `git` packages.

Download the latest `gcc-arm-none-eabi-*-win32.zip` archive from [launchpad.net](https://launchpad.net/gcc-arm-embedded/+download). Create the directory `C:\cygwin64\opt\gcc-arm-none-eabi` and extract the contents of the zip file to it.

Launch a Cygwin terminal and run the following to append to your `~/.bashrc` file:
```bash
echo '[[ $PATH == */opt/gcc-arm-none-eabi/bin* ]] || export PATH=/opt/gcc-arm-none-eabi/bin:$PATH' >>~/.bashrc
source ~/.bashrc
```

Verify the toolchain installation with `arm-none-eabi-gcc --version`

### Cloning

This repository uses git submodules. Clone with the `--recursive` flag

```bash
git clone --recursive https://github.com/wuwushrek/crazyflie-firmware
```

If you already have cloned the repo without the `--recursive` option, you need to
get the submodules manually

```bash
cd crazyflie-firmware
git submodule init
git submodule update
```


## Compiling in standard mode

### Crazyflie 2.X

This is the default build so just running ```make``` is enough or:
```bash
make PLATFORM=cf2
```

or with the toolbelt

```bash
tb make PLATFORM=cf2
```

### Crazyflie in HITL mode

```bash
make PLATFORM=hitl
```

### Flashing the crazyflie

```bash
make cload
```

### config.mk
To create custom build options create a file called `config.mk` in the `tools/make/`
folder and fill it with options. E.g.
```
PLATFORM=CF2
DEBUG=1
CLOAD=0
```
More information can be found on the
[Bitcraze wiki](http://wiki.bitcraze.io/projects:crazyflie2:index)


```
# Make targets:
```
all        : Shortcut for build
compile    : Compile cflie.hex. WARNING: Do NOT update version.c
build      : Update version.c and compile cflie.elf/hex
clean_o    : Clean only the Objects files, keep the executables (ie .elf, .hex)
clean      : Clean every compiled files
mrproper   : Clean every compiled files and the classical editors backup files

cload      : If the crazyflie-clients-python is placed on the same directory level and
             the Crazyradio/Crazyradio PA is inserted it will try to flash the firmware
             using the wireless bootloader.
flash      : Flash .elf using OpenOCD
halt       : Halt the target using OpenOCD
reset      : Reset the target using OpenOCD
openocd    : Launch OpenOCD
```

# Unit testing

## Running all unit tests

With the environment set up locally

        make unit

with the docker builder image and the toolbelt

        tb make unit

## Running one unit test

When working with one specific file it is often convenient to run only one unit test

       make unit FILES=test/utils/src/test_num.c

or with the toolbelt

       tb make unit FILES=test/utils/src/test_num.c

## Running unit tests with specific build settings

Defines are managed by make and are passed on to the unit test code. Use the
normal ways of configuring make when running tests. For instance to run test
for Crazyflie 1

      make unit LPS_TDOA_ENABLE=1

## Dependencies

Frameworks for unit testing and mocking are pulled in as git submodules.

The testing framework uses ruby and rake to generate and run code.

To minimize the need for installations and configuration, use the docker builder
image (bitcraze/builder) that contains all tools needed. All scripts in the
tools/build directory are intended to be run in the image. The
[toolbelt](https://wiki.bitcraze.io/projects:dockerbuilderimage:index) makes it
easy to run the tool scripts.
