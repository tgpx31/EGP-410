# EGP-410 Assignment 2 (Brian Baron)

# Commit:
	3ed651b41d70578b27828466494bd65750eb680a
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
	* I: open properties menu
	* V, R, A, C: Select properties (displayed on screen) [Velocity, Radius, Angular Velocity, Unit Accel]
	* +/-: increment and decrement the value of selected property
## Out of Properties:
	* S: Spawn WanderAndSeek unit 200px away
	* F: Spaw WanderAndFlee unit 100px away

# Additional Notes: