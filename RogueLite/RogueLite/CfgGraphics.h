#include <string>
#pragma once

class cfgGraphicsClass {
public:
	std::string fileName = "config\\graphics.dat";
	void verifyDefGraphics() {
		FILE *fd;
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return;
		}
		if (cfg.verify.bAntiAliasing != true) fprintf(fd, "%s = 0\n", cfg.names.antiAliasing);
		else fprintf(fd, "%s = %i\n", cfg.names.antiAliasing, cfg.values.iAntiAliasing);
		if (cfg.verify.bFullscreen != true) fprintf(fd, "%s = 0\n", cfg.names.fullscreen);
		else fprintf(fd, "%s = %i\n", cfg.names.fullscreen, cfg.values.iFullscreen);
		if (cfg.verify.bRendererType != true) fprintf(fd, "%s = 0\n", cfg.names.rendererType);
		else fprintf(fd, "%s = %i\n", cfg.names.rendererType, cfg.values.iRendererType);
		if (cfg.verify.bWindowHeight != true) fprintf(fd, "%s = 45\n", cfg.names.windowHeight);
		else fprintf(fd, "%s = %i\n", cfg.names.windowHeight, cfg.values.iWindowHeight);
		// cWindowTitle returns '80' instead of the actual name. Maybe try using std::string instead??
		if (cfg.verify.bWindowTitle != true) fprintf(fd, "%s = -- RogueLite --\n", cfg.names.windowTitle);
		else fprintf(fd, "%s = %s\n", cfg.names.windowTitle, cfg.values.cWindowTitle);
		if (cfg.verify.bWindowWidth != true) fprintf(fd, "%s = 80\n", cfg.names.windowWidth);
		else fprintf(fd, "%s = %i\n", cfg.names.windowWidth, cfg.values.iWindowWidth);
		fclose(fd);
	}
	struct cfgGraphicsStruct {
	public:
		struct valuesStruct {
		public:
			int iWindowHeight;
			int iWindowWidth;
			char *cWindowTitle;
			int iFullscreen;
			int iAntiAliasing;
			int iRendererType;
		}values;
		struct namesStruct {
		public:
			char *windowHeight = "WindowHeight";
			char *windowWidth = "WindowWidth";
			char *windowTitle = "WindowTitle";
			char *fullscreen = "Fullscreen";
			char *antiAliasing = "AntiAliasing";
			char *rendererType = "RenderType";
		}names;
		struct verifyStruct {
		public:
			bool bWindowHeight = false;
			bool bWindowWidth = false;
			bool bWindowTitle = false;
			bool bFullscreen = false;
			bool bAntiAliasing = false;
			bool bRendererType = false;
		}verify;
	}cfg;
};