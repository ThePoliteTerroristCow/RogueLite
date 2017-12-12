#include <stdio.h>
#include <string>
#include "Main.h"

Parser::Parser() { cfgAudio = new cfgAudioClass; cfgGraphics = new cfgGraphicsClass; }
Parser::~Parser() { delete cfgAudio; delete cfgGraphics; }

bool Parser::dirExists(char *fileDir) {
	FILE *fd;
	fd = fopen(fileDir, "r");
	if (fd == NULL) {
		return false;
	}
	else {
		fclose(fd);
		return true;
	}
}
bool Parser::fileExists(const char *filePath) {
	FILE *fd;
	fd = fopen(filePath, "r");
	if (fd == NULL) {
		return false;
	}
	else {
		fclose(fd);
		return true;
	}
}

//////////////////////////////////////////////////////////////////////////

void Parser::readAudioCfg() {
	FILE *fd;
	if (dirExists(configPath) == false) {
		TCODSystem::createDirectory(configPath);
	}
	if (fileExists(cfgAudio->fileName.c_str()) == false) {
		cfgAudio->verifyDefAudio();
	}
	fd = fopen(cfgAudio->fileName.c_str(), "rt");
	if (fd == NULL) {
		printf("Error reading '%s'\n", cfgAudio->fileName.c_str());
		return;
	}

	char line[512], tmpLeft[512], tmpRight[512];
	char *ptr;
	while (fgets(line, 511, fd) != NULL) {
		while (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
		if (line[0] == '#') continue;
		ptr = strstr(line, "=");
		if (ptr == NULL) continue;
		*ptr = '\0';
		while (line[strlen(line) - 1] == ' ') line[strlen(line) - 1] = '\0';
		strcpy(tmpLeft, line);
		strcpy(tmpRight, ptr + 1);
		while (tmpRight[strlen(tmpRight) - 1] == ' ') tmpRight[strlen(tmpRight) - 1] = '\0';
		while (tmpRight[0] == ' ') strcpy(tmpRight, tmpRight + 1);

		// Find & store our values
		if (_stricmp(tmpLeft, cfgAudio->cfg.names.ambientVolume) == 0) {
			cfgAudio->cfg.values.iAmbientVolume = atoi(tmpRight);
			cfgAudio->cfg.verify.bAmbientVolume = true;
			//printf("%s %i\n", cfgAudio->cfg.names.ambientVolume, cfgAudio->cfg.values.iAmbientVolume);
			continue;
		}
		if (_stricmp(tmpLeft, cfgAudio->cfg.names.effectsVolume) == 0) {
			cfgAudio->cfg.values.iEffectsVolume = atoi(tmpRight);
			cfgAudio->cfg.verify.bEffectsVolume = true;
			//printf("%s %i\n", cfgAudio->cfg.names.effectsVolume, cfgAudio->cfg.values.iEffectsVolume);
			continue;
		}
		if (_stricmp(tmpLeft, cfgAudio->cfg.names.masterVolume) == 0) {
			cfgAudio->cfg.values.iMasterVolume = atoi(tmpRight);
			cfgAudio->cfg.verify.bMasterVolume = true;
			//printf("%s %i\n", cfgAudio->cfg.names.masterVolume, cfgAudio->cfg.values.iMasterVolume);
			continue;
		}
		if (_stricmp(tmpLeft, cfgAudio->cfg.names.musicVolume) == 0) {
			cfgAudio->cfg.values.iMusicVolume = atoi(tmpRight);
			cfgAudio->cfg.verify.bMusicVolume = true;
			//printf("%s %i\n", cfgAudio->cfg.names.musicVolume, cfgAudio->cfg.values.iMusicVolume);
			continue;
		}
		if (_stricmp(tmpLeft, cfgAudio->cfg.names.uiVolume) == 0) {
			cfgAudio->cfg.values.iUIVolume = atoi(tmpRight);
			cfgAudio->cfg.verify.bUIVolume = true;
			//printf("%s %i\n", cfgAudio->cfg.names.uiVolume, cfgAudio->cfg.values.iUIVolume);
			continue;
		}
	}
	fclose(fd);
	cfgAudio->verifyDefAudio();
	return;
}

void Parser::readGraphicsCfg() {
	FILE *fd;
	if (dirExists(configPath) == false) {
		TCODSystem::createDirectory(configPath);
	}
	if (fileExists(cfgGraphics->fileName.c_str()) == false) {
		cfgGraphics->verifyDefGraphics();
	}
	fd = fopen(cfgGraphics->fileName.c_str(), "rt");
	if (fd == NULL) {
		printf("Error reading '%s'\n", cfgGraphics->fileName.c_str());
		return;
	}

	char line[512], tmpLeft[512], tmpRight[512];
	char *ptr;
	while (fgets(line, 511, fd) != NULL) {
		while (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
		if (line[0] == '#') continue;
		ptr = strstr(line, "=");
		if (ptr == NULL) continue;
		*ptr = '\0';
		while (line[strlen(line) - 1] == ' ') line[strlen(line) - 1] = '\0';
		strcpy(tmpLeft, line);
		strcpy(tmpRight, ptr + 1);
		while (tmpRight[strlen(tmpRight) - 1] == ' ') tmpRight[strlen(tmpRight) - 1] = '\0';
		while (tmpRight[0] == ' ') strcpy(tmpRight, tmpRight + 1);

		// Find & store our values
		if (_stricmp(tmpLeft, cfgGraphics->cfg.names.antiAliasing) == 0) {
			cfgGraphics->cfg.values.iAntiAliasing = atoi(tmpRight);
			cfgGraphics->cfg.verify.bAntiAliasing = true;
			//printf("%s %i\n", cfgGraphics->cfg.names.antiAliasing, cfgGraphics->cfg.values.iAntiAliasing);
			continue;
		}
		if (_stricmp(tmpLeft, cfgGraphics->cfg.names.fullscreen) == 0) {
			cfgGraphics->cfg.values.iFullscreen = atoi(tmpRight);
			cfgGraphics->cfg.verify.bFullscreen = true;
			//printf("%s %i\n", cfgGraphics->cfg.names.fullscreen, cfgGraphics->cfg.values.iFullscreen);
			continue;
		}
		if (_stricmp(tmpLeft, cfgGraphics->cfg.names.rendererType) == 0) {
			cfgGraphics->cfg.values.iRendererType = atoi(tmpRight);
			cfgGraphics->cfg.verify.bRendererType = true;
			//printf("%s %i\n", cfgGraphics->cfg.names.rendererType, cfgGraphics->cfg.values.iRendererType);
			continue;
		}
		if (_stricmp(tmpLeft, cfgGraphics->cfg.names.windowHeight) == 0) {
			cfgGraphics->cfg.values.iWindowHeight = atoi(tmpRight);
			cfgGraphics->cfg.verify.bWindowHeight = true;
			//printf("%s %i\n", cfgGraphics->cfg.names.windowHeight, cfgGraphics->cfg.values.iWindowHeight);
			continue;
		}
		// cWindowTitle returns '80' instead of the actual name. Maybe try using std::string instead??
		if (_stricmp(tmpLeft, cfgGraphics->cfg.names.windowTitle) == 0) {
			cfgGraphics->cfg.values.cWindowTitle = tmpRight;
			cfgGraphics->cfg.verify.bWindowTitle = true;
			//printf("%s %s\n", cfgGraphics->cfg.names.windowTitle, cfgGraphics->cfg.values.cWindowTitle);
			continue;
		}
		if (_stricmp(tmpLeft, cfgGraphics->cfg.names.windowWidth) == 0) {
			cfgGraphics->cfg.values.iWindowWidth = atoi(tmpRight);
			cfgGraphics->cfg.verify.bWindowWidth = true;
			//printf("%s %i\n", cfgGraphics->cfg.names.windowWidth, cfgGraphics->cfg.values.iWindowWidth);
			continue;
		}
	}
	fclose(fd);
	cfgGraphics->verifyDefGraphics();
	return;
}