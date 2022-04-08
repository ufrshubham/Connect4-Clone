# Connect4-Clone

A cross-platform clone of [Connect4](https://en.wikipedia.org/wiki/Connect_Four) game written in C++ using [SFML](https://www.sfml-dev.org/)

## Build Instructions

- Requirements
  - Git
  - CMake
  - C++ Compiler

- Steps

    ```bash
    # Clone this project along with submodules
    $ git clone --recursive https://github.com/ufrshubham/Connect4-Clone

    # Go to project root
    $ cd Connect4-Clone

    # Pull SFML as submodule (if you cloned without --recursive flag)
    $ git submodule update --init

    # Create a folder for build
    $ mkdir build

    # Go to build folder
    $ cd build

    # Generate project files
    $ cmake ..
    ```

- This will generate project files using default cmake generator for your platform. For example:

  - on `Windows` with `Visual Studio` installed, it will generate a `.sln`
  - on `Linux` with `make` installed, it will generate a `Makefile`
  - on `Mac` with `xcode` installed, it will generate a `.xcodeproj`
  