# Tower Defense

TODO: \<Add a brief high level description of the Game\>

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
9. `./TowerDefense5` - finally, run the executable generated inside `build`.

# Note on Code Formatting
We use [clang-format](https://clang.llvm.org/docs/ClangFormatStyleOptions.html) with Google C++ style guide.
There are shortcuts to invoke the formatter on the project source depending on the IDE/editor used.
1. In Visual Studio, open a source file and hit `Ctrl+K, Ctrl+D` to apply the formatting.
2. In VSCode, open a source file and hit `Ctrl+Shift+I` to apply the formatting.
 
# Repository organization

The project repository is organised as the following tree:

| \
|__doc/ \
|__include/ \
|__libs/ \
|__plan/ \
|__src/ \
|__tests/ \
|__CMakeLists.txt \
|__README.md \
|__Meeting-notes.md

# Project Implementation 
You must use git repository for the work on the project, making frequent enough commits so 
that the project group (and course staff) can follow the progress.

The completed project work will be demonstrated to the group's advisor at a demo session. 
The final demonstrations are arranged on week 50. After the final demonstrations project group 
evaluates another project, and self-evaluates own project. In addition, project members will 
give a confidential individual assessment of each group member

The course staff should be able to easily compile the project work using makefile and related 
instructions provided in the git repository. The final output should be in the **master branch** of the git repository.

# Working practices

Each project group is assigned an advisor from the project teaching personnel. 
There will be a dedicated Teams channel for each project topic to facilitate discussion between 
the groups in the same topic and the advisor. 

**The group should meet weekly.** The weekly meeting does not need to be long if there are no special issues 
to discuss, and can be taken remotely as voice/video chat on the group Teams channel (or Zoom or other similar tool), 
preferably at a regular weekly time. In the meeting the group updates:

- What each member has done during the week
- Are there challenges or problems? Discuss the possible solutions
- Plan for the next week for everyone
- Deviations and changes to the project plan, if any
- After the meetings, the meeting notes will be committed to the project repository in the `Meeting-notes.md` file. 
    * The commits within the week should have some commit messages referring to the meeting notes so 
      that the project advisor can follow the progress.  
    * **The meeting notes should be in English.**

> Everyone may not be able to participate to all meetings, but at least a couple of members should be present in each meeting. 
> Regular absence from meetings will affect in individual evaluation.

# Source code documentation
It is strongly recommended to use Doxygen to document your source code.
Please go over the *Project Guidelines* for details.

# TODOs (04-Nov-2021)

- Add GTest support
- Check how to optimize CMakeLists.txt for cross-platform compatibility
