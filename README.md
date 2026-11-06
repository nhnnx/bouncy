# Bouncy's Arcade Fantasy

Bouncy's Arcade Fantasy is a tribute to Bumpy's Arcade Fantasy videogame by Loriciel for MS-DOS (1992).

It is written in C++ with SDL3 by Nanni (2026).

The main game mechanism has been implemented, and in the current version it includes only a world of levels inspired by the original Bumpy game. Many more worlds and levels are to be added in future.
However, there is still to fix some detail. Also, a lot of work regarding graphics, sound, and animation is missing. 

Prerequisites & Dependencies
----------------------------

To build and run Bouncy, ensure you have the following tools and libraries installed on your system.

Build Tools

- C++ Compiler with C++17 support or higher (e.g., MSVC on Windows, GCC on Linux).

- CMake (version 3.15 or higher).

- Git (for repository management).

Required Libraries (SDL3 Stack). The project relies on SDL3 and its official extension libraries:

- SDL3 3.4.18

- SDL3_image 3.4.8

- SDL3_mixer 3.2.4

- SDL3_ttf 3.2.2
	
Building Instructions
------------------------

On Windows edit the CMakeLists.txt with the proper path the SDL3 libraries.
Then run CMake.

Game Rules
------------------------

The game is divided into multiple worlds, each containing a series of levels. Complete all the levels in a world to advance to the next one.

Objective: guide Bouncy to collect all the yellow dots in each level. Once all dots are collected, the exit portal will appear. Reach it to complete the level.

Levels feature various interactive blocks and hazards. When Bouncy interacts with them, they trigger different mechanics (e.g., bouncing, sliding, or hazards that cause instant death).

The world screen displays your current lives and total score.

Controls:

    Arrow Keys: Move / Navigate
	
	Space: Jump

    Enter: Confirm / Select

    Esc: Quit / Back
	
For any help request, doubt, feedback, bug report... write to signornanni@hotmail.it

Have fun!
