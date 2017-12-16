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
	bool dirExists(const char *fileDir);
	bool fileExists(const char *filePath);
};