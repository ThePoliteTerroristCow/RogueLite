# RogueLite
A personal project that utilizes the libtcod 1.6.3 library.  
Debug and Release builds of whatever I'm working on are in their respective \RogueLite\Build folders  
  
-- VS2015 Setup --  
The following project properties must be modified to point to the correct locations in the included \libtcod\ folder. Their locations must also be modified according to the Configuration Mode (ie Release Mode, Debug Mode)  
  
Project Properties --> Configuration Properties --> VC++ Directories:  
  
    Include Directories: (libtcod\libtcod-1.6.3\include)  
  
    Library Directories [DEBUG] (libtcod\libtcod-1.6.3\build\msvs\libtcod\Win32\Debug)  
    Library Directories [RELEASE] (libtcod\libtcod-1.6.3\build\msvs\libtcod\Win32\Release)  
  
	Source Directories: (libtcod\libtcod-1.6.3\src)  
  
Project Properties --> Linker --> General:  
    Additional Library Directories [DEBUG] (libtcod\libtcod-1.6.3\build\msvs\libtcod\Win32\Release)  
    Additional Library Directories [RELEASE] (libtcod\libtcod-1.6.3\build\msvs\libtcod\Win32\Debug)  
  
  
-- LAUNCH PREREQUISITES --  
Place in the same directory as the main EXE file. Debug versions are in the RogueLite\Debug folder. Release versions are in the RogueLite\Release folder. You can also build these yourself by opening the libtcod.sln file (libtcod\libtcod-1.6.3\build\msvs)  
  
--> SDL2.dll  
--> libtcod.dll   
--> libtcod-gui.dll  
--> terminal.png  