#include "CfgAudio.h"
#include "CfgControls.h"
#include "CfgGraphics.h"

class Parser
{
public:
	Parser();
	~Parser();
	cfgAudioClass *cfgAudio;
	cfgControlsClass *cfgControls;
	cfgGraphicsClass *cfgGraphics;
	void setupConfigFiles();
};