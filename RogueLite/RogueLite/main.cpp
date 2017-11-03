#include "Main.h"

Engine engine(80, 50);

int main(void)
{
	while (!TCODConsole::isWindowClosed()) {
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	return 0;
}