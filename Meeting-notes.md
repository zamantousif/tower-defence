# Meeting Notes
# Meeting 01.11.2021 18:00

**Participants**: 
1. Julius Järvilinna
2. Tousif Zaman
3. Tomi Mikkola
4. Konsta Kemppainen

## Summary of works
1. This was our very first team meeting.
2. We had a round of basic introduction about ourselves.
3. Discussed about towers, enemy, GUI and other parts of the game.
4. A preliminary version of the class relationship diagram was done.
5. Each member agreed to take up some responsibilities of the implementation.
6. Team decided that Tuesday evening would be most appropriate for team meetings.

## Actions
1. Julius agreed to implement the towers and the enemy classes.
2. Tousif decided to add CMake support to the repository and start work on abstract classes.
3. Tomi will decide the look of the towers and enemies.
4. Konsta will look into map implementation and GUI.

## Project status (as of 05.11.2021 22:45)
Short summary of current project status. 
1. Team has been working on the project plan and the tentative schedule.
2. Initial repository structure is added with CMake+SFML support for Linux.

## Challenges
1. We might have to render and update to GUI at the same time, there is concern about data races.

### TODOs
1. Tousif: Add abstract class implementations so that further implementation could begin.
2. Team: Take the repository into use and report any issues with CMake/SFML.

# Meeting 09.11.2021 18:00

**Participants**: 
1. Julius Järvilinna
2. Tousif Zaman
3. Tomi Mikkola
4. Konsta Kemppainen

## Discussion/ Summary of works
1. We acknowledged Tomi’s work on the Trello board
2. We discussed problems with CMake on Windows
3. Konsta researched CMake and tried to get it to work on Windows using the Visual Studio compiler with varying success.
4. Julius tried to get the project working on school ssh connection
5. We discussed a bit about Git practices

## Actions
1. Tousif will investigate with Konsta and try to get a successful build + run on Windows for the code repository
2. Tousif and Julius will work on implementing abstract classes (object, tower, enemy, projectile) and a basic version of Game() class 
3. Julius and Tomi have to install compilers to get the project working locally on their computers as it’s probably quite difficult get GUI show up with school ssh-remote connection
4.  Julius can ideate tower models and communicate them to Tomi who is designing the final tower visuals
5. Check with the instructor/TA if implementing tower upgrades gives us enough extra points to consider it?

## Project status (as of 09.11.2021 18:45)
Short summary of current project status. 
1. We have trouble getting CMake to work on Windows.
2. We are able to build + run the repository on Linux though.
3. Planning of the project is in a good phase.

## Challenges
1. Getting SFML + CMake to work on Windows 
2. We might have to render and update to GUI at the same time, there is concern about data races.

### TODOs
1. Tousif + Julius: Add abstract class implementations so that further implementation could begin.
2. Team: Take the repository into use and report any issues with CMake/SFML.
# Meeting 16.11.2021 18:00

**Participants**: 
1. Julius Järvilinna
2. Tousif Zaman
3. Tomi Mikkola
4. Konsta Kemppainen

## Discussion/ Summary of works
1. Everyone has now been able to compile the project using CMake
2. Basic planning of 5 towers has now been done
3. We went over how to handle merge requests and when git rebase should be used

## What’s next?
1. Tousif will continue work on implementing abstract classes (object, tower, enemy, projectile) and a basic version of Game() class 
2. Konsta will work on the technical implementation of maps (although he’s very very busy this week!).
3. Julius will design what kind of enemies and an enemy theme will be used
4. Tomi will make art for at least one map and several towers and projectiles

## Project status (as of 16.11.2021 20:30)
Short summary of current project status. 
1. Code compiles with CMake for everyone
2. We went cross-platform and cross-compiler way with MSVC, Linux and different set of compilers used to build the project
3. Initial version of abstract class for game Object is added
4. We have more clarity on the tower and enemy implementations

## Challenges
1. We might have to render and update to GUI at the same time, there is concern about data races.

### TODOs
1. Implement GUI
________________
# Meeting 23.11.2021 18:00

**Participants**: 
1. Julius Järvilinna
2. Tousif Zaman
3. Tomi Mikkola

## Discussion/ Summary of works
1. Tomi showed the artwork he’s been working on: many towers, enemies and a map.
2. Julius has designed several enemies
3. Tousif has worked on the abstract classes and showed us how to do unit tests

## What’s next?
1. Tomi will work on the GUI
2. Julius will begin proper tower implementation
3. Tousif will wrap up the Enemy class implementation and add some pending tests for other classes.
4. We need to figure out GUI and MAP implementations.

## Project status (as of 23.11.2021 20:30)
1. We have basic versions of sprites for the game objects and the map.
2. We added some base implementations and test cases.
3. We revisited the class diagram and made some corrections/additions.

## Challenges
1. We need to pick up more on the implementation part of the project.

________________

# Meeting 30.11.2021 18:00

**Participants**: 
1. Julius Järvilinna
2. Tousif Zaman
3. Tomi Mikkola
4. Konsta Kemppainen

## Discussion/ Summary of works
1. We discussed how enemy rounds will be implemented. They consist of “waves” that consist of some amount of some type of enemy that arrives according to some time interval. These waves also have an offset relative to the start of the round, 0 being the start of the round and 1000 being one second after the round has started.
2. We went over everyone’s work in the past week
3. Julius and Tousif solved problems with getting the tests to work on Windows in VScode and with Mingw.
4. We decided to apply Google C++ style guide for our project. Clang-format support is added to apply these settings to the project sources.
5. Konsta cleaned up a lot of code and added map.cpp (which supports loading a map from a json file).

## What’s next?
1. Tomi and Konsta will work on the GUI and application class
2. Julius will keep working on towers and enemies
3. Tousif will work on enemy path following and tower-buying collision detection
4. Konsta will implement Game.cpp and Application.cpp

## Project status (as of 30.11.2021 20:30)
1. Most basic classes are implemented
2. Artwork is mostly done

## Challenges
The deadline is nearing!

________________

# Meeting 07.12.2021 18:00

**Participants**: 
1. Julius Järvilinna
2. Tousif Zaman
3. Tomi Mikkola
4. Konsta Kemppainen

## Discussion/ Summary of works
1. Tomi worked on the GUI and application class
2. Julius worked on towers and enemies
3. Tousif worked on tower-buying collision detection on paper
4. Konsta worked on Game.cpp and solved a recursion problem with forward declarations.

## What’s next?
1. Tomi will finish off GUI, make all missing artwork and help with the game class
2. Tousif will finish collision functions and work on enemy path following
3. Julius will finish work on towers and enemies
4. Konsta will finish up Map.cpp and Game.cpp and possibly implement the Update method for Enemy, Tower and Projectile. Konsta might also work on the Update method of Game.

## Project status (as of 07.12.2021 19:00)
1. Most parts of the game are implemented such as GUI, game, towers, enemies, etc.
2. We will check how to add support for Doxygen document generation for the project
3. Once done with current activities, the next available team member will start adding content to the doc/readme.

## Challenges
The deadline is haunting us!
