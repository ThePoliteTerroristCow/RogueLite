# RogueLite
A personal project that utilizes the libtcod 1.6.3 library.  
Debug and Release builds of whatever I'm working on are in their respective \RogueLite\Build folders  

-- Boost Library --  
Instead of using libtcod's built-in parser support I have (for the time being) opted to use the parser support included in the 'Boost' package. Until I have the time to streamline the files used, Boost version 1.65.1 will have to be setup properly on your end if you want to compile the code here. As a temporary remedy I've begun including the debug/release files on the 'Dev' branch in addition to the main release branch.   
  
-- VS2015 Setup --  
The following project properties must be modified to point to the correct locations in the included \libtcod\ folder. Their locations must also be modified according to the Configuration Mode (ie Release Mode, Debug Mode)  
  
Project Properties --> Configuration Properties --> VC++ Directories:  
  
    Include Directories: (libtcod\libtcod-1.6.3\include)  
  
    Library Directories: [DEBUG] (libtcod\libtcod-1.6.3\build\msvs\libtcod\Win32\Debug)  
    Library Directories: [RELEASE] (libtcod\libtcod-1.6.3\build\msvs\libtcod\Win32\Release)  
  
	Source Directories: (libtcod\libtcod-1.6.3\src)  
  
Project Properties --> Linker --> General:  
  
    Additional Library Directories: [DEBUG] (libtcod\libtcod-1.6.3\build\msvs\libtcod\Win32\Release)  
    Additional Library Directories: [RELEASE] (libtcod\libtcod-1.6.3\build\msvs\libtcod\Win32\Debug)  
  
  
-- LAUNCH PREREQUISITES --  
Place in the same directory as the main EXE file. Debug & Release versions have been pre-included in their respective RogueLite\Release Type folders. You can also build these yourself by opening the libtcod.sln file (libtcod\libtcod-1.6.3\build\msvs)  
  
--> SDL2.dll  
--> libtcod.dll   
--> libtcod-gui.dll  
--> terminal.png  