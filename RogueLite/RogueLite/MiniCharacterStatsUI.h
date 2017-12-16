#include <string>
#include <Windows.h>
#pragma once

class MiniCharacterStatsUI {
public:
	struct dirNameStruct {
	public:
		std::string dataDirName = "data\\";
		std::string modsDirName = "mods\\";
		std::string uiDirName = "data\\ui\\";
	}dir;
	std::string fileName = "data\\ui\\MiniCharacterStatsUI.dat";
	std::string modFileName = "data\\mods\\ui\\MiniCharacterStatsUI.dat";
	void verifyFile() {
		if (dirExists(dir.dataDirName.c_str()) == false) {
			CreateDirectoryA(dir.dataDirName.c_str(), NULL);
			if (dirExists(dir.modsDirName.c_str()) == false) {
				CreateDirectoryA(dir.modsDirName.c_str(), NULL);
			}
			if (dirExists(dir.uiDirName.c_str()) == false) {
				CreateDirectoryA(dir.uiDirName.c_str(), NULL);
			}
		}
		// Try to open the modded file first. If it isn't found, read from the default file instead
		FILE *fd;
		fd = fopen(modFileName.c_str(), "r");
		if (fd != NULL) {
			fclose(fd);
			verifyModFile();
			return;
		}
		else {
			fd = fopen(fileName.c_str(), "r");
			if (fd == NULL) {
				// Neither file was found, so we write the default file 
				writeDefFile();
				return;
			}
			else {
				fclose(fd);
				verifyDefFile();
				return;
			}
		}
	}

	struct uiStruct {
	public:
		struct hpUIStruct {
			struct defaultValuesStruct {
			public:
				int topLeftX = 0;
				int width = 0;
				int height = 0;
				std::string cTitle = "HP";
			}defValues;
			struct namesStruct {
			public:
				char *cTopLeftX = "TopLeftX";
				char *cWidth = "Width";
				char *cHeight = "Height";
				char *cTitle = "OverlayTitle";
			}names;
			struct valuesStruct {
			public:
				int topLeftX;
				int width;
				int height;
				std::string cTitle;
			}values;
			struct verifyStruct {
			public:
				bool bTopLeftX = false;
				bool bWidth = false;
				bool bHeight = false;
				bool bTitle = false;
			}verify;
		}hpBar;
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
	void verifyDefFile() {
		FILE *fd;
		fd = fopen(fileName.c_str(), "r");
		if (fd == NULL) {
			return; // error
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
			if (_stricmp(tmpLeft, cfg.hpBar.names.cHeight) == 0) {
				cfg.hpBar.values.height = atoi(tmpRight);
				cfg.hpBar.verify.bHeight = true;
				continue;
			}
			if (_stricmp(tmpLeft, cfg.hpBar.names.cTitle) == 0) {
				cfg.hpBar.values.cTitle = tmpRight;
				cfg.hpBar.verify.bTitle = true;
				continue;
			}
			if (_stricmp(tmpLeft, cfg.hpBar.names.cTopLeftX) == 0) {
				cfg.hpBar.values.topLeftX = atoi(tmpRight);
				cfg.hpBar.verify.bTopLeftX = true;
				continue;
			}
			if (_stricmp(tmpLeft, cfg.hpBar.names.cWidth) == 0) {
				cfg.hpBar.values.width = atoi(tmpRight);
				cfg.hpBar.verify.bWidth = true;
				continue;
			}
		}
		fclose(fd);
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return; // error
		}
		else {
			if (cfg.hpBar.verify.bHeight != true) fprintf(fd, "%s = %i\n", cfg.hpBar.names.cHeight, cfg.hpBar.defValues.height);
			else fprintf(fd, "%s = %i\n", cfg.hpBar.names.cHeight, cfg.hpBar.values.height);
			if (cfg.hpBar.verify.bTitle != true) fprintf(fd, "%s = %s\n", cfg.hpBar.names.cTitle, cfg.hpBar.defValues.cTitle.c_str());
			else fprintf(fd, "%s = %s\n", cfg.hpBar.names.cTitle, cfg.hpBar.values.cTitle.c_str());
			if (cfg.hpBar.verify.bTopLeftX != true) fprintf(fd, "%s = %i\n", cfg.hpBar.names.cTopLeftX, cfg.hpBar.defValues.topLeftX);
			else fprintf(fd, "%s = %i\n", cfg.hpBar.names.cTopLeftX, cfg.hpBar.values.topLeftX);
			if (cfg.hpBar.verify.bWidth != true) fprintf(fd, "%s = %i\n", cfg.hpBar.names.cWidth, cfg.hpBar.defValues.width);
			else fprintf(fd, "%s = %i\n", cfg.hpBar.names.cWidth, cfg.hpBar.values.width);
			fclose(fd);
		}
	}
	void verifyModFile() {
		FILE *fd;
		fd = fopen(modFileName.c_str(), "r");
		if (fd == NULL) {
			return; // error
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
			if (_stricmp(tmpLeft, cfg.hpBar.names.cHeight) == 0) {
				cfg.hpBar.values.height = atoi(tmpRight);
				cfg.hpBar.verify.bHeight = true;
				continue;
			}
			if (_stricmp(tmpLeft, cfg.hpBar.names.cTopLeftX) == 0) {
				cfg.hpBar.values.topLeftX = atoi(tmpRight);
				cfg.hpBar.verify.bTopLeftX = true;
				continue;
			}
			if (_stricmp(tmpLeft, cfg.hpBar.names.cWidth) == 0) {
				cfg.hpBar.values.width = atoi(tmpRight);
				cfg.hpBar.verify.bWidth = true;
				continue;
			}
		}
		fclose(fd);
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return; // error
		}
		else {
			if (cfg.hpBar.verify.bHeight != true) fprintf(fd, "%s = %i\n", cfg.hpBar.names.cHeight, cfg.hpBar.defValues.height);
			else fprintf(fd, "%s = %i\n", cfg.hpBar.names.cHeight, cfg.hpBar.values.height);
			if (cfg.hpBar.verify.bTitle != true) fprintf(fd, "%s = %s\n", cfg.hpBar.names.cTitle, cfg.hpBar.defValues.cTitle.c_str());
			else fprintf(fd, "%s = %s\n", cfg.hpBar.names.cTitle, cfg.hpBar.values.cTitle.c_str());
			if (cfg.hpBar.verify.bTopLeftX != true) fprintf(fd, "%s = %i\n", cfg.hpBar.names.cTopLeftX, cfg.hpBar.defValues.topLeftX);
			else fprintf(fd, "%s = %i\n", cfg.hpBar.names.cTopLeftX, cfg.hpBar.values.topLeftX);
			if (cfg.hpBar.verify.bWidth != true) fprintf(fd, "%s = %i\n", cfg.hpBar.names.cWidth, cfg.hpBar.defValues.width);
			else fprintf(fd, "%s = %i\n", cfg.hpBar.names.cWidth, cfg.hpBar.values.width);
			fclose(fd);
		}
	}
	void writeDefFile() {
		FILE *fd;
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return; // error
		}
		fprintf(fd, "%s = %i\n", cfg.hpBar.names.cHeight, cfg.hpBar.defValues.height);
		fprintf(fd, "%s = %i\n", cfg.hpBar.names.cTopLeftX, cfg.hpBar.defValues.topLeftX);
		fprintf(fd, "%s = %i\n", cfg.hpBar.names.cWidth, cfg.hpBar.defValues.width);
		fclose(fd);
		verifyDefFile();
	}
};