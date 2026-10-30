/*
---------------------------------------------------
The Return of Bumpy Log Development - by Nanni 2025
---------------------------------------------------

TO DO:
- Bumpy's dimension must be >20px
- How to initialize the enemy velocity?
- Add OBJ_FLOOR_SpinUp (maybe as a different status of OBJ_FLOOR_SpineDown)
- Cloud should not cross a cell with enemy
- Nasty enemy is dumb as well (add a random component?)
- Magnetic ceiling should attract even when VelX != 0 and !pressedDown
  maybe test when (hitfloor==true) but position and velocity must be reset...
---------------------------------------------------

03 Oct 2026 Build 30
---------------------
- Fixed various bugs and released a version for beta testing

02 Oct 2026 Build 29
---------------------
- Implemented cMagnetic
- Added all levels in the 1st world
- Implemented dumb, random, and nasty enemys

26 Sep 2026 Build 28
---------------------
- Added magnetic sprite
- Corrected an imprecision regarding jumping aside from a platform
- Tested super-dumb enemy

25 Sep 2026 Build 27
---------------------
- Implemented interaction with cGlue, cSideGlue and cTeleport
- Added new sprites (glue, teleport, floor up and down)
- Corrected bug with cDecision

22 Sep 2026 Build 26
---------------------
- Configurated for Release compiling mode
- TO DO:
  - Interaction with remaining objects: cTeleport, cGlue, cSideGlue, cEnemy, cMagnetic
  - Add sounds and sprites

14 May 2026 Build 25
---------------------
- Implemented interaction with cCatapult, cFace, cSideIce and cTeleport (not working)
- Started implemented (super-dumb)cEnemy

22 Nov 2025 Build 24
---------------------
- Added classes of all remaining objects (enemy, glue, catapult, teleport, face, magnetic),
    but still interaction is to be implemented!
- Extended the editor tool window with all the objects (with rotated texture rendered correctly)

20 Nov 2025 Build 23
---------------------
- Score and extra lives are shown in the world screen now.
- Corrected export code in the editor. Object type are printed as enum IDs, not numbers.
- Go to next world when one is completed.
- Password is shown at world beginning
- Start any world by entering the password

30 Oct 2025 Build 22
---------------------
- Implemented level test in the editor

29 Oct 2025 Build 21
---------------------
- Fixed bugs with Exit and Bumpy in the editor
- Implemented clear and export commands
- Added toggle grid command

28 Oct 2025 Build 20
---------------------
Editor:
- Added buttons for commands (but not working yet)
- Added central and side objects buttons
- Add a function for render any object in default mode, used in the editor tool window
- Substitute object/change status when an object is already in a cell

22 Oct 2025 Build 19
---------------------
- Started implementing the editor:
  You can select a floor object and add it to the level
  To Do:
  - Change object status when already present
  - Add side and central objects
  - Add commands (reset, export, test)
  - Add all the textures

06 Oct 2025 Build 18
---------------------
- Implemented world / level navigation
  Prepared a first world with test levels
- To do: show lives and points in the world view

04 Oct 2025 Build 17
---------------------
- Tested loading and playing a sound effect with SDL_mixer
- Added cLife object
- Implemented collision with cShooter.
- Implemented sliding on Ice.

15 Sep 2025 Build 16
---------------------
- Added cFakeSide and cInvisibleSide
- Added cOneBounce
- Added first draft of cWorld

13 Sep 2025 Build 15
---------------------
- Added the cloud as new object. Interaction implemented and tested.

06 Sep 2025 Build 14
---------------------
- Implemented the main menu, which includes for now:
   Play (run the test level)
   About (show some info)
   Exit

20 Aug 2025 Build 13
---------------------
- Added new objects: cSpine, cSpineDown and cSpineSide and cSpring
  (texture files are missing)

15 Aug 2025 Build 12
---------------------
- Added new objects: cNways, cFloorWall and cSideWall
  (texture files are missing)

14 Aug 2025 Build 11
---------------------
- Added new objects:
  OBJ_FLOOR_Up and OBJ_FLOOR_Down, OBJ_FLOOR_Forced, OBJ_FLOOR_Decision
  Mechanincs implemented, but file texture is missing.

12 Aug 2025 Build 10
---------------------
- Added and tested new object types:
  cPlainSide, cLeftOnly, cRightOnly, cReducingFloor, cInvisibleFloor, cFakeFloor
- Added new sprites from file: bumpy, reducing, invisible, fake, left, right
  (Sprites are all made with Piskel online editor)

09 Aug 2025 Build 09
---------------------
- Added and handled level exit
- Loaded some example of sprite (ice and floor objects)
- New module Media.cpp for loading sprites and sounds

06 Aug 2025 Build 08
---------------------
- Improved Bumpy's basic physics/geometry.
  It seems all ok now, except for random glitches to fix.

31 July 2025 Build 07
---------------------
- Implemented moving left/right.
- Jumping left/right is implemented, but Bumpy is not positioning correctly. TO FIX!
- Implemented bouncing against the window edges.
- Added new object cFood. It just disappears when Bumpy collides.

28 July 2025 Build 06
---------------------
- Implemented stop jumping
- To do:
  - Move/jump left or right. Then, we'll be ready for step 2.

27 July 2025 Build 05
---------------------
- Loaded TTF library with success. Now can load fonts.
- Implemented Bumpy's jumping up from the floor and rebouncing against a ceiling.
- Optimized the research of objects for checking collision.

26 July 2025 Build 04
---------------------
- Quit level when Bumpy falls down outside
- Rendered Bumpy as a circle
- Implemented bouncing against a floor
- Associate a cell to each object
- Checked collision with objects close to bumpy's cell
- Tried to load font, but it doesn't work

22 July 2025 Build 03
---------------------
- Level doesn't start untill a key is pressed
- Initialized objects at specific cells (not at some pixels)
- Introduced new object: plain floor. Not interacting yet with Bumpy
- Added e retro-game font file into the folder

20 July 2025 Build 02
---------------------
- Added structure Game/Level:
  - Game: in future there will be menu, settings, ecc...
          enter a default level by pressing enter
  - Level: rendered a background grid just for reference
          What happens for now: a red square simulates Bumpy's ball
          Bumpy is falling down for gravity: it starts accelerating,
          then reaches a constant speed and bounces at a fixed height
- To do now:
  - Initialize objects positioning at a specific cell (not at some pixels)
  - Bounce against some floor (not at fixed height). Introduce new objects!
  - Implement jumping and stop jumping
  - Implement moving left/right

10 July 2025 Build 01
---------------------
- Setup the project: it compiles and run correctly
- For now, it just show a square falling and bouncing
- Plan:
  1. Fundamental mechanics (fall, jump, move...)
  2. Level objects and interactions
  3. Structure/interface (menu, world/level navigation, editor...)
  4. Sounds, animations, graphics...
  5. Levels and test
  6. More (high scores, options/difficulty, fullscreen, variable level grid...)

Road map:

  2025        2026
  J A S O N D ... S O N D
1 ===................
2 ..=====...=......==
3 .....=.===.........
4 ..=...=..........=.
5 ..................=
6 ...................

*/