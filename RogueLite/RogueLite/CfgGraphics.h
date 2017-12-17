#include <string>
#include <Windows.h>
#pragma once

class cfgGraphicsClass {
public:
	struct dirNameStruct {
	public:
		std::string dataDirName = "data\\";
		std::string configDirName = "data\\config\\";
	}dir;
	std::string fileName = "data\\config\\graphics.dat";
	void verifyDefGraphics() {
		if (dirExists(dir.dataDirName.c_str()) == false) {
			CreateDirectoryA(dir.dataDirName.c_str(), NULL);
			if (dirExists(dir.configDirName.c_str()) == false) {
				CreateDirectoryA(dir.configDirName.c_str(), NULL);
			}
		}
		FILE *fd;
		fd = fopen(fileName.c_str(), "r");
		if (fd == NULL) {
			if (fileExists(fileName.c_str()) == false) writeDefFile();
			return;
		}
		else {
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

				if (_stricmp(tmpLeft, cfg.names.antiAliasing) == 0) {
					cfg.values.iAntiAliasing = atoi(tmpRight);
					cfg.verify.bAntiAliasing = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.fullscreen) == 0) {
					cfg.values.iFullscreen = atoi(tmpRight);
					cfg.verify.bFullscreen = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.rendererType) == 0) {
					cfg.values.iRendererType = atoi(tmpRight);
					cfg.verify.bRendererType = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.setFramerate) == 0) {
					cfg.values.iSetFramerate = atoi(tmpRight);
					cfg.verify.bSetFramerate = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.showFramerate) == 0) {
					cfg.values.iShowFramerate = atoi(tmpRight);
					cfg.verify.bShowFramerate = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.windowHeight) == 0) {
					cfg.values.iWindowHeight = atoi(tmpRight);
					cfg.verify.bWindowHeight = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.windowTitle) == 0) {
					cfg.values.cWindowTitle = tmpRight;
					cfg.verify.bWindowTitle = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.windowWidth) == 0) {
					cfg.values.iWindowWidth = atoi(tmpRight);
					cfg.verify.bWindowWidth = true;
					continue;
				}
			}
			fclose(fd);
			FILE *fd;
			fd = fopen(fileName.c_str(), "wt");
			if (fd == NULL) {
				return; // error
			}
			else {
				if (cfg.verify.bAntiAliasing != true) fprintf(fd, "%s = %i\n", cfg.names.antiAliasing, cfg.defVals.iAntiAliasing);
				else fprintf(fd, "%s = %i\n", cfg.names.antiAliasing, cfg.values.iAntiAliasing);
				if (cfg.verify.bFullscreen != true) fprintf(fd, "%s = %i\n", cfg.names.fullscreen, cfg.defVals.iFullscreen);
				else fprintf(fd, "%s = %i\n", cfg.names.fullscreen, cfg.values.iFullscreen);
				if (cfg.verify.bRendererType != true) fprintf(fd, "%s = %i\n", cfg.names.rendererType, cfg.defVals.iRendererType);
				else fprintf(fd, "%s = %i\n", cfg.names.rendererType, cfg.values.iRendererType);
				if (cfg.verify.bSetFramerate != true) fprintf(fd, "%s = %i\n", cfg.names.setFramerate, cfg.defVals.iSetFramerate);
				else fprintf(fd, "%s = %i\n", cfg.names.setFramerate, cfg.values.iSetFramerate);
				if (cfg.verify.bShowFramerate != true) fprintf(fd, "%s = %i\n", cfg.names.showFramerate, cfg.defVals.iShowFramerate);
				else fprintf(fd, "%s = %i\n", cfg.names.showFramerate, cfg.values.iShowFramerate);
				if (cfg.verify.bWindowHeight != true) fprintf(fd, "%s = %i\n", cfg.names.windowHeight, cfg.defVals.iWindowHeight);
				else fprintf(fd, "%s = %i\n", cfg.names.windowHeight, cfg.values.iWindowHeight);
				if (cfg.verify.bWindowTitle != true) fprintf(fd, "%s = %s\n", cfg.names.windowTitle, cfg.defVals.cWindowTitle.c_str());
				else fprintf(fd, "%s = %s\n", cfg.names.windowTitle, cfg.values.cWindowTitle.c_str());
				if (cfg.verify.bWindowWidth != true) fprintf(fd, "%s = %i\n", cfg.names.windowWidth, cfg.defVals.iWindowWidth);
				else fprintf(fd, "%s = %i\n", cfg.names.windowWidth, cfg.values.iWindowWidth);
				fclose(fd);
			}
		}
	}

	struct cfgGraphicsStruct {
	public:
		struct defaultValuesStruct {
		public:
			int iWindowHeight = 80;
			int iWindowWidth = 50;
			std::string cWindowTitle = "-- RogueLite --";
			int iFullscreen = 0;
			int iAntiAliasing = 0;
			int iRendererType = 0;
			int iSetFramerate = 0;
			int iShowFramerate = 0;
		}defVals;
		struct valuesStruct {
		public:
			int iWindowHeight;
			int iWindowWidth;
			std::string cWindowTitle;
			int iFullscreen;
			int iAntiAliasing;
			int iRendererType;
			int iSetFramerate;
			int iShowFramerate;
		}values;
		struct namesStruct {
		public:
			char *windowHeight = "WindowHeight";
			char *windowWidth = "WindowWidth";
			char *windowTitle = "WindowTitle";
			char *fullscreen = "Fullscreen";
			char *antiAliasing = "AntiAliasing";
			char *rendererType = "RenderType";
			char *setFramerate = "SetFPS";
			char *showFramerate = "ShowFPS";
		}names;
		struct verifyStruct {
		public:
			bool bWindowHeight = false;
			bool bWindowWidth = false;
			bool bWindowTitle = false;
			bool bFullscreen = false;
			bool bAntiAliasing = false;
			bool bRendererType = false;
			bool bSetFramerate = false;
			bool bShowFramerate = false;
		}verify;
	}cfg;

protected:
	bool dirExists(const char *fileDir) {
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
	bool fileExists(const char *fileDir) {
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
	void writeDefFile() {
		FILE *fd;
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return; // error
		}
		fprintf(fd, "%s = %i\n", cfg.names.antiAliasing, cfg.defVals.iAntiAliasing);
		fprintf(fd, "%s = %i\n", cfg.names.fullscreen, cfg.defVals.iFullscreen);
		fprintf(fd, "%s = %i\n", cfg.names.rendererType, cfg.defVals.iRendererType);
		fprintf(fd, "%s = %i\n", cfg.names.setFramerate, cfg.defVals.iSetFramerate);
		fprintf(fd, "%s = %i\n", cfg.names.showFramerate, cfg.defVals.iShowFramerate);
		fprintf(fd, "%s = %i\n", cfg.names.windowHeight, cfg.defVals.iWindowHeight);
		fprintf(fd, "%s = %s\n", cfg.names.windowTitle, cfg.defVals.cWindowTitle.c_str());
		fprintf(fd, "%s = %i\n", cfg.names.windowWidth, cfg.defVals.iWindowWidth);
		fclose(fd);
	}
};