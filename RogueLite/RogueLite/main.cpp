#include "stdafx.h"

Engine engine;

int main(void)
{
	while (!TCODConsole::isWindowClosed()) {
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	return 0;
}