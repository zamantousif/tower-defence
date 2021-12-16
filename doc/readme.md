# Project Documentation

## Group Members
* Julius Järvilinna 596174
* Tousif Zaman 980285
* Tomi Mikkola 793155
* Konsta Kemppainen 1008250

## Overview

We made a pretty conventional Tower Defense (TD) game with 6 unique tower types and 4 different enemies, 2 maps, and 10 enemy rounds. In our TD game, towers can be bought, sold and upgraded during or in-between rounds. Each tower has 3 upgrades with the third upgrade giving the tower some special ability. Different enemies have different health and movement speed values. We have two different damage types, some towers being more effective against certain enemy types. We also have a boss enemy that is immune to slowing towers. We have nice background music which sound level can be changed in the settings. Our level map consists of a background image, where the enemies path consists of predetermined points on the map. Towers can’t be placed on the path of the enemies. 

Maps also have obstacles such as trees and rocks that towers cannot be placed on. We thought also of making the map consist of tiles, but decided we want rather to make it a background image with an array of 2D points to describe the enemy path, because we thought it would look cooler.

The in-game user interface allows players to buy and place towers, hover over towers in the shop to gain more information on them and start rounds. The UI shows how much money and lives the player has and how much towers cost. Towers placed on the map can be clicked on to show their range and open up a menu that lets the player upgrade and sell the tower. We also added targeting options such as those in Bloons TD games.
Killed enemies drop nature's essence, which is used as currency for buying and upgrading towers. Enemies with more HP drop more money. If an enemy gets past the player’s defenses, the player will lose lives based on the amount of money the enemy would have dropped. Maps and enemy rounds are read from files.

Towers can be clicked after placement to open a menu in which you can upgrade, sell and change targeting options of the tower. Towers start at tier 1 and can be upgraded thrice. The first two upgrades increase some of the basic stats: damage, rate of fire and range. Most tier 4 upgrades are special and change the tower in some way. In the same menu a tower can be set to target the first, last, closest or strongest enemy within its range.

There are four enemy types. The cockroach is a basic enemy. Flies are faster than cockroaches. Beetles are armored and have a lot of health. Dragonflies are armored bosses that have a lot of health and are immune to slowing effects. Armored enemies have a yellow health bar. They have a lot of health, but take extra damage from certain sources such as the coconut cannon and sniper towers.

## Game Play

The game opens in the main menu, from which the player can start the game, open the options menu or quit the game. In the options menu sound volume and whether rounds start automatically can be changed. Starting the game puts the player in a map select screen where they can choose between two different maps.

Once a map is selected the game starts. Rounds of enemies rush through the path on the map and the player must stop them from getting to the end of the path by placing towers on the map. The game ends once all rounds are beaten or the player runs out of health. There are 6 different towers in the shop on the right, more info on the towers can be gained by hovering over them in the GUI. The game can be paused from the top right. Towers are bought and placed by clicking on one of the shop icons and then clicking on the game map in the desired position. Towers can be clicked on after placement to open the upgrading menu.

## Software Structure

The below diagram representes the high level design philosophy of the game.

@image latex td_class_design.png width=\textwidth

The below diagram shows the inheritance relationship between the game objects.

@image latex td_class_diagram.png width=\textwidth

## Data Structure Decisions

Some of the data structure decisions we took in the implementation are highlighted below:

* Game objects are stored in lists because removal is `O(1)`
* Collisions are handled using maps because accessing a map is `O(log n)`
* We preferred using `std::optional` over `nullptr` to enforce error handling and to avoid null chaos
* We used `unsigned int` wherever applicable (as opposed to bare `int`)
* We favor `const` references instead of copying wherever applicable (for example `const std::string&`)
* `sf::vector2f` are always passed in by copy because they are just 8 bytes and copying them is faster

## Instructions

First you need to clone the repository and download all the required dependencies (git submodules). This can be achieved with Git by doing the following:
1. Open your terminal in the directory where you want to download the project.
2. Run `git clone --recurse-submodules git@version.aalto.fi:cpp-autumun-2021/tower-defense/tower-defense-5.git` in the terminal.

The rest is platform-specific. Please read below to see instructions for your platform.

## How to compile the program

### Windows

Tested on Windows 10.
1. Install CMake from the [CMake website](https://cmake.org/download/).
2. Install [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/).
3. Install the `Desktop development with C++` workload.
4. Make a build folder in the project directory.
5. Once you have a terminal open in the build folder, run `cmake ..`
6. If the files are created successfully, open `TowerDefense5.sln` in Visual Studio 2022.
7. Build and run the project in Visual Studio 2022.

### Linux

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

## Testing

We wrote our own tests for collision detections; otherwise, we tested most aspects of our game visually by running TowerDefense5.exe and checking for problems. We use [GoogleTest](https://github.com/google/googletest/blob/main/googletest/README.md) to write unit tests. The `CMakeLists.txt` takes care of installing the necessary dependencies and generates an executable for all unit test sources present inside `tests` directory. Run this executable to see the status of unit tests (passed/failed).

### Steps to generate text executable and run it

```
cd tower-defense-5          # enter project root directory
mkdir build && cd build     # make a build directory
cmake ..                    # run CMake
make                        # make tests along with sources
../bin/TowerDefense5_tests  # run tests executable from executables directory
```

## Work log

Tomi took care of the artistic side of our project, like designing how the enemies and towers look like and did the GUI of our game. Tomi also worked on the application class of our game. Konsta worked with CMake at the start of our project. Later Konsta worked on Map.cpp and Game.cpp. Tousif also worked with CMake, designed abstract classes of our game, implemented the collision detection algorithms with unit tests. Julius was responsible for towers and enemies planning and he implemented tower and projectile subclasses. Julius also made some functions into tower, projectile and enemy abstract classes. Everyone was involved in our weekly meetings for most weeks and took part in planning and discussing the game features. Overall team workload was weighted more at the end of the project, when the deadline was nearing. It took a while until the project picked up steam because CMake was a little problematic (on Windows especially).

Detailed weekly work done was as follows:

### Week 1 (1.11-8.11)
* Tomi did Trello board for our team
* Konsta researched CMake and tried to get it to work on Windows using the Visual Studio compiler. He also imported the external libraries as git submodules. Getting them to link properly was surprisingly difficult.
* Julius tried to get the project working on school ssh connection
* Tousif created the basic structure of the project, added CMake support

Time used for project on week 1 per team member:
* Julius 6h
* Tousif 8h
* Konsta 12h
* Tomi 4h


### Week 2 (9.11-15.11)
* Julius planned 5 basic towers and tried to get the code to compile with VScode
* Tousif and Konsta worked on the CMakeLists and finally got it working.
* Tousif and Konsta helped Julius and Tomi to get the code to compile
* Use of Git was discussed and teached to Julius and Tomi, whom had only little previous experience with it 

Time used for project on week 2 per team member:
* Julius 6h
* Tousif 8h
* Konsta 8h
* Tomi 5h

### Week 3 (16.11-22.11)
* Tomi did the artwork for many towers, enemies and a map
* Julius designed several enemies
* Tousif worked on abstract classes and added googletest support for the project
* Konsta improved the README (instructions for how to compile the code on Windows) and figured out how to make it automatically generate solution filters for Visual Studio.

Time used for project on week 3 per team member:
* Julius 4h
* Tousif 8h
* Konsta 2h
* Tomi 10h

### Week 4 (23.11-29.11)
* Tomi worked on more artwork
* Julius and Tousif solved problems with getting the tests to work on Windows in VScode and with Mingw
* Julius worked on doing tower implementations
* Konsta cleaned up some code and added a missing getter.
* Tousif finished up abstract classes, added basic unit tests for it 

Time used for project on week 4 per team member:
* Julius 15h
* Tousif 15h
* Konsta 2h
* Tomi 4h

### Week 5 (30.11-6.12)
* Tomi worked on the GUI and application class
* Julius worked on towers and enemies
* Tousif added clang-format support to format the code, worked on collision detection math involving circles and polygons on paper and started the implementation
* Konsta cleaned up a lot of code and worked on Game.cpp.

Time used for project on week 5 per team member:
* Julius 20h
* Tousif 25h
* Konsta 8h
* Tomi 40h

### Week 6 (7.12-12.12)
* Tomi finished off GUI, made all missing artwork and helped with the game class
* Julius finished his implementation of towers and enemies and worked on project documentation
* Tousif implemented and fixed bugs in collision detection functions and added them to Game.
* Konsta worked on Game.cpp (added a function for loading in enemies and a function for loading in rounds) and implemented the Update method for Game. He also cleaned up a lot of code and added.

Time used for project on week 6 per team member:
* Julius 8h
* Tousif 25h
* Konsta 25h
* Tomi 35h
