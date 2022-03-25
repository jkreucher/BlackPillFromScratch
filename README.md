# Blackpill from Scratch

Copyright 2022 Jannik Kreucher


## Table Of Contents
  - [Project](#project)
  - [Setting up the development environment](#setting-up-the-development-environment)

## Project
The goal of this project is to write all hardware drivers for the Blackpill from scratch without using HAL or even CMSIS libraries. I started this project to get to know the STM32F411. I uploaded my project files for everyone to use. Maybe this helps you in any shape or form. I am by no means a professional programmer so take any code in this project with a grain of salt.


## Setting up the development environment

Install ST-Link tools
```
sudo apt install stlink-tools stlink-gui
```

Download arm-gcc from [their website](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads). Then extract the archieve
```
sudo tar xjf gcc-arm-none-eabi-<version>-x86_64-linux.tar.bz2 -C /usr/share/
```

Link the executables
```
sudo ln -s /usr/share/gcc-arm-none-eabi-<version>-x86_64-linux/bin/arm-none-eabi-gcc /usr/bin/arm-none-eabi-gcc
sudo ln -s /usr/share/gcc-arm-none-eabi-<version>-x86_64-linux/bin/arm-none-eabi-g++ /usr/bin/arm-none-eabi-g++
sudo ln -s /usr/share/gcc-arm-none-eabi-<version>-x86_64-linux/bin/arm-none-eabi-gdb /usr/bin/arm-none-eabi-gdb
sudo ln -s /usr/share/gcc-arm-none-eabi-<version>-x86_64-linux/bin/arm-none-eabi-size /usr/bin/arm-none-eabi-size
```

When running `arm-none-eabi-gdb` you might encounter problems with missing libraries. This can be fixed my linking to a newer version
```
sudo apt install libncurses-dev
sudo ln -s /usr/lib/x86_64-linux-gnu/libncurses.so.6 /usr/lib/x86_64-linux-gnu/libncurses.so.5
sudo ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so.6 /usr/lib/x86_64-linux-gnu/libtinfo.so.5
```

Install OpenOCD
```
git clone https://github.com/openocd-org/openocd.git
./bootstrap
./configure
make
sudo make install
```

### Setting up VS Code
Install the plugin `Cortex-Debug` by marus25. Launch VS Code Quick Open (Ctrl+P), paste the following command, and press enter.
```
ext install marus25.cortex-debug
```

Now open a project folder with VS Code and try debugging on your Blackpill.

