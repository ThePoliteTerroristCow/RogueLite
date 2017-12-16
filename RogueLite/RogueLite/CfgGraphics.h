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
		FILE *fd;
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return;
		}
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
};