#include "Main.h"

Cheats cheats;
Engine engine(80, 50);
FOV fov;

int main(void)
{
	while (!TCODConsole::isWindowClosed()) {
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	return 0;
}