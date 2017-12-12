#include "CfgAudio.h"
#include "CfgGraphics.h"

class Parser
{
public:
	Parser();
	~Parser();
	cfgAudioClass *cfgAudio;
	cfgGraphicsClass *cfgGraphics;

	void readAudioCfg();
	void readGraphicsCfg();

protected:
	char *configPath = "config\\";
	bool dirExists(char *fileDir);
	bool fileExists(const char *filePath);
};