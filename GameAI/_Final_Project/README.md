#EGP-410 Assignment 5: Final Project (Brian Baron & Colin Brady)

#Commit:
	b609e88c595943302489a8ef2ccbbf904deba932
	Repo Link: https://github.com/tgpx31/EGP-410

#To Compile/Link:
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

To run, right click and select Debug->start new instance of the project you want (editor or game)

RELEASE:
	* Should be fine

#CONTROLS
	* ESC: Exit the application

In editor:
	* F1: menu
	* Left Mouse: place tile
	* Right Mouse: remove tile
	* 1-4: select tile type
	* S: Save
	* Up/Down arrows: change current map	

In game:
	* WASD: player movement (up, down, left, right, respectively)
	* F1: Property menu and debug lines/collision circles
	* I: player invicincible toggle
	* Up and down arrows: select active property in menu
	* +/-: Modifty selected property

##Other Inputs:
	* Invalid key inputs result in an output telling you you hit the default case

#Additional Notes: