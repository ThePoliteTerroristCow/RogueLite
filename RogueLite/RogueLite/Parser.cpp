#include <stdio.h>
#include <string>
#include "Main.h"

Parser::Parser() { cfgAudio = new cfgAudioClass; cfgControls = new cfgControlsClass; cfgGraphics = new cfgGraphicsClass; }
Parser::~Parser() { delete cfgAudio; delete cfgControls; delete cfgGraphics; }

void Parser::setupConfigFiles() {
	cfgAudio->verifyDefAudio();
	cfgControls->verifyDefControls();
	cfgGraphics->verifyDefGraphics();
}