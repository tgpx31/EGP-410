# EGP-410 Assignment 4 (Brian Baron)

# Commit:
	35b07f0d13ce52cbedeab505bb20b11661e31c54
	Repo Link: https://github.com/tgpx31/EGP-410

# To Compile/Link:
If you have the whole repo:
Rebuild entire solution. Should be linked. Set start up project to game.

Otherwise:
IN PROJECT PROPERTIES:
DEBUG:
	* Go to debugging, and set environment to: PATH=../../../../external libs/Allegro5/bin;%PATH%
	* Go to C/C++, set additional include directories to: ..\CommonPathfindingLib;..\..\..\..\DeanLib;..\..\..\..\External Libs\Allegro5\include;
	* Go to Linker, set additional library directories to: ..\CommonPathfindingLib\Debug;..\..\..\..\External libs\Allegro5\lib;..\..\..\..\DeanLib\debug
	* In Linker->Input, set additional Dependencies to CommonPathfindingLib.lib;allegro-5.0.10-monolith-md-debug.lib;DeanLib.lib;%(AdditionalDependencies)

Note that your paths may differ depending on your location of DeanLib and Allegro libraries.

RELEASE:
	* Should be fine

# Keyboard Inputs:
## In Properties:
	* D: Set Pathfinding method to Dijkstra
	* A: Set Pathfinding method to A* (AStar)
	* ESC: Exit the application

## Other Inputs:
	* Left mouse button places the start node, and then the goal node of the path

# Additional Notes:
The Editor project allows you to edit and create a new level. Right click, start a new instance to run it.
	* S saves the level
	* Left mouse button places walls
	* Right mouse button removes malls