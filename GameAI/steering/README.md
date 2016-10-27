# EGP-410 Assignment 3 (Brian Baron)

# Commit:
	sha
	Repo Link: https://github.com/tgpx31/EGP-410

# To Compile/Link:
Assuming that you are downloading the entire git repository:
Build Deanlib.sln, libraries are already linked. Using Visual Studio 2015

Otherwise:
IN PROJECT PROPERTIES:
DEBUG:
	* Go to debugging, and set environment to: PATH=../../external libs/Allegro5/bin;%PATH%
	* Go to C/C++, set additional include directories to: ..\..\DeanLib;..\..\External Libs\Allegro5\include;
	* Go to Linker, set additional library directories to: %(AdditionalLibraryDirectories);..\..\External libs\Allegro5\lib;..\..\DeanLib\debug
	* In Linker->Input, set additional Dependencies to %(AdditionalDependencies);allegro-5.0.10-monolith-md-debug.lib;DeanLib.lib;

Note that your paths may differ depending on your location of DeanLib and Allegro libraries.

RELEASE:
	* Should be fine

# Keyboard Inputs:
## In Properties:
	* P: open properties menu
	* V, R, A, C: Select properties (displayed on screen)
		** [Velocity, Radius, Angular Velocity, Unit Accel, Cohesion, Seperation, Alignment]
	* +/-: increment and decrement the value of selected property

## Other Inputs:
	* I: Spawn 5 Boids Units @ mouse position
	* D: Delete a random Unit form the map
	* CTRL + S: Save steering weights to savedWeights.txt
	* ESC: Exit the game

# Additional Notes:
The Boids Steering behavior is the result of weighted blending from Cohesion, Seperation, and Alignment behaviors.
savedWeights.txt is automatically loaded if existing on run. If it isn't there, it loads default weights.