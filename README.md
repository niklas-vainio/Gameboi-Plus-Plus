# gameboi++
It's been 6 years... can I make a better one?

This project is a lightweight Gameboy emulator designed to run as a desktop app on MacOS. This emulator is intended as a successor to the one I originally developed in 2020 (see [here](https://github.com/niklas-vainio/GameboyEmulator)), now that I have ( \* *coughs* \*) actual programming exerience.

# Installation
**Prerequisites:** `g++` and `cmake` must be installed.  
To set up everything for this project, including pulling in SDL3 as a submodule, run:
```
source scripts/install.sh
```

The current build setup is designed for MacOS, other systems may have issues.

# Building and Running
To compile everything, run:
```
make
```
This will generate a build folder containing an executable `gameboi++`. This can be run manually with `build/gameboi++`, or by running:
```
make run
```

To compile and run with arguments, run:
```
make run ARGS="args here"
```

To clean everything in the build folder *except* SDL files, run:
```
make clean
```

To clean everything in the build folder including SDL files, run:
```
make clean-full
```

# Formatting
To format all files in the codebase, run `source scripts/format_all.sh`

#
Created by Niklas Vainio  
Started on 01/25/2026
