# Tower Defense

TODO: \<Add a brief high level description of the Game\>

# Group
- Julius Järvilinna
- Tousif Zaman
- Tomi Mikkola
- Konsta Kemppainen
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

# Prerequisites
## Install dependencies
### Linux 
#### Tested on Ubuntu 18.04
1. `sudo apt update`
2. Install toolchain (GCC, make, etc.) `sudo apt install build-essential`
3. Install CMake `sudo apt install cmake`
4. Install SFML 2.5.1 and its dependencies, refer https://www.sfml-dev.org/download/sfml/2.5.1/
   1. Download the SFML 2.5.1 tar.gz from the URL
   2. Extract and keep the folder `SFML 2.5.1` in your `home` directory
   3. The path should be `/home/<username>/SFML-2.5.1`

Note: It is also possible to skip step 4. and install SFML using `sudo apt-get install libsfml-dev` but the version installed will be the latest in the apt repository, follow 4. to be sure about `SFML 2.5.1`.
## Update CMakeLists.txt
Add the paths to `include` & `lib` directories as `SFML_INCLUDE_DIR` and `SFML_LIBRARY_DIR` respectively, in CMakeLists.txt


# Build and Run
Follow the below steps to build the project after the prerequisite steps are completed.
1. `git clone git@version.aalto.fi:cpp-autumun-2021/tower-defense/tower-defense-5.git` - to clone the project repository
2. Open a terminal and enter the project directory
3. `mkdir build` - make a `build` directory inside the project
4. `cd build` - enter the build directory
5. `cmake ..` - to run CMake and generate a makefile inside `build`
6. `make` - to use the makefile to build the project
7. `./towerdefense5` - finally, run the executable generated inside `build`


# TODOs (04-Nov-2021)
Assigned to `Tousif`
- Install SFML 2.5.1 on Windows as outlined in https://www.sfml-dev.org/tutorials/2.5/ and install this repository locally
- Update CMakeLists.txt and installation instructions accordingly
- Add GTest support
- Check how to optimize CMakeLists.txt for cross-platform compatibility
