# Druidic Defense
Druidic Defense is a conventional [Tower Defense](https://en.wikipedia.org/wiki/Tower_defense) game with different towers,
enemies, maps and enemy waves. 

## Game Features and highlights
The game currently supports the below features:
* 10 rounds of play
* 6 types of towers
* 4 types of enemies
* 2 different maps
* Towers can be bought, sold and upgraded during/in-between rounds
* For certain towers, player can decide which enemy will be shot (first/last/close/strong)
* Some enemies are armored and take more damage from certain towers
* Maps have obstacles (trees, rocks, water, path) where towers cannot be placed
* Collisions are visible by change in color of a tower's target range
* An options menu with game settings
* Rounds can be set to start automatically in the options and pause menus
* Maps and rounds are not hardcoded but allow for easy customization
* Gameplay can be paused and then resumed again
* Groovy background music
* Colorful artwork

# Group
- Julius Järvilinna
- Tousif Zaman
- Tomi Mikkola
- Konsta Kemppainen

# How to compile the project from source

First you need to clone the repository and download all the required dependencies (git submodules). This can be achieved with Git by doing the following:

1. Open your terminal in the directory where you want to download the project.
2. Run `git clone --recurse-submodules git@version.aalto.fi:cpp-autumun-2021/tower-defense/tower-defense-5.git` in the terminal.

The rest is platform-specific. Scroll down to see instructions for your platform.

## Windows

Tested on Windows 10.

1. Install CMake from the [CMake website](https://cmake.org/download/).
2. Install [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/).
3. Install the `Desktop development with C++` workload.
4. Make a build folder in the project directory.
5. Once you have a terminal open in the build folder, run `cmake ..`
6. If the files are created successfully, open `TowerDefense5.sln` in Visual Studio 2022.
7. Build and run the project in Visual Studio 2022.

## Linux

Tested on Ubuntu 18.04.

1. Run `sudo apt update` in the terminal.
2. Install toolchain (GCC, make, etc.) by running `sudo apt install build-essential` in the terminal.
3. Install CMake by running `sudo apt install cmake` in the terminal.
4. Open a terminal in the project directory.
5. `mkdir build` - make a `build` directory inside the project.
6. `cd build` - enter the build directory.
7. `cmake ..` - run CMake and generate a makefile inside `build`.
8. `make` - use the makefile to build the project.
9. `./TowerDefense5` - finally, run the executable generated inside `bin`.

# Note on Code Formatting
We use [clang-format](https://clang.llvm.org/docs/ClangFormatStyleOptions.html) with Google C++ style guide.
There are shortcuts to invoke the formatter on the project source depending on the IDE/editor used.
- In Visual Studio, open a source file and hit `Ctrl+K, Ctrl+D` to apply the formatting.
- Refer [this](https://code.visualstudio.com/docs/cpp/cpp-ide) to set up clang-format for VSCode. Open a source file and hit `Ctrl+Shift+I` to apply the formatting. 

# Source code documentation
Our project uses [Doxygen](https://github.com/doxygen/doxygen) to document source code. To be able to generate the 
documentation from this repository, you need to [install Doxygen](https://www.doxygen.nl/download.html). The compilation steps mentioned earlier take care of generating the documentation as well. The documented output is generated inside [**doc**](https://version.aalto.fi/gitlab/cpp-autumun-2021/tower-defense/tower-defense-5/-/tree/master/doc) in a dedicated folder as an HTML file. 

# Unit Tests
We use [GoogleTest](https://github.com/google/googletest/blob/main/googletest/README.md) to write unit tests. The `CMakeLists.txt`
takes care of installing the necessary dependencies and generates an executable for all unit test sources present inside `tests` directory. Run this executable 
to see the status of unit tests (passed/failed).
```bash
cd tower-defense-5          # enter project root directory
mkdir build && cd build     # make a build directory
cmake ..                    # run CMake
make                        # make tests along with sources
../bin/TowerDefense5_tests  # run tests executable from executables directory
```
# Repository organization

The project repository at the top-level is organised as the following tree:

|__assets/ \
|__bin/ \
|__build/ \
|__doc/ \
|__include/ \
|__libs/ \
|__plan/ \
|__src/ \
|__tests/ \
|__CMakeLists.txt \
|__Meeting-notes.md \
|__README.md \

# Project Implementation 
Group members used the git repository to push work on the project, making commits to different feature branches
which would then be merged to a **master** branch through a merge request (MR). The MRs added by an author were reviewed 
by other members and merged by the author after correcting any comments/feedback received. We followed a clean progress 
by adding descriptive commit messages and details wherever necessary. Project related communications were handled over a Telegram group. 

# Working practices

Our project group met weekly (Tueday evenings at 6pm) to discuss the below points:
- What each member has done during the week
- Are there challenges or problems? Discuss the possible solutions
- Plan for the next week for everyone
- Deviations and changes to the project plan, if any
- After each meeting, the meeting notes were committed to the project repository in the `Meeting-notes.md` file. 
