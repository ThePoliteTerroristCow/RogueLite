#include <string>
#include <Windows.h>
#pragma once

class CheatsUI {
public:
	struct dirNameStruct {
	public:
		std::string dataDirName = "data\\";
		std::string modDirName = "mods\\";
		std::string uiDirName = "data\\ui\\";
	}dir;
	std::string fileName = "data\\ui\\CheatsUI.dat";
	std::string modFileName = "data\\mods\\ui\\CheatsUI.dat";
	void verifyFile() {
		if (dirExists(dir.dataDirName.c_str()) == false) {
			CreateDirectoryA(dir.dataDirName.c_str(), NULL);
			if (dirExists(dir.modDirName.c_str()) == false) {
				CreateDirectoryA(dir.modDirName.c_str(), NULL);
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
		struct defaultValuesStruct {
			public:
			int topLeftX = 7;
			int width = 20;
			int height = 6;
			std::string uiTitle = "-- Cheats Enabled --";
		}defValues;
		struct namesStruct {
		public:
			char *cTopLeftX = "TopLeftX";
			char *cWidth = "Width";
			char *cHeight = "Height";
			char *uiTitle = "UITitle";
		}names;
		struct valuesStruct {
		public:
			int topLeftX;
			int width;
			int height;
			std::string uiTitle;
		}values;
		struct verifyStruct {
		public:
			bool bTopLeftX = false;
			bool bWidth = false;
			bool bHeight = false;
			bool bUITitle = false;
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

			if (_stricmp(tmpLeft, cfg.names.cHeight) == 0) {
				cfg.values.height = atoi(tmpRight);
				cfg.verify.bHeight = true;
				continue;
			}
			if (_stricmp(tmpLeft, cfg.names.cTopLeftX) == 0) {
				cfg.values.topLeftX = atoi(tmpRight);
				cfg.verify.bTopLeftX = true;
				continue;
			}
			if (_stricmp(tmpLeft, cfg.names.cWidth) == 0) {
				cfg.values.width = atoi(tmpRight);
				cfg.verify.bWidth = true;
				continue;
			}
			if (_stricmp(tmpLeft, cfg.names.uiTitle) == 0) {
				cfg.values.uiTitle = tmpRight;
				cfg.verify.bUITitle = true;
				continue;
			}
		}
		fclose(fd);
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return; // error
		}
		else {
			if (cfg.verify.bHeight != true) fprintf(fd, "%s = %i\n", cfg.names.cHeight, cfg.defValues.height);
			else fprintf(fd, "%s = %i\n", cfg.names.cHeight, cfg.values.height);
			if (cfg.verify.bTopLeftX != true) fprintf(fd, "%s = %i\n", cfg.names.cTopLeftX, cfg.defValues.topLeftX);
			else fprintf(fd, "%s = %i\n", cfg.names.cTopLeftX, cfg.values.topLeftX);
			if (cfg.verify.bWidth != true) fprintf(fd, "%s = %i\n", cfg.names.cWidth, cfg.defValues.width);
			else fprintf(fd, "%s = %i\n", cfg.names.cWidth, cfg.values.width);
			if (cfg.verify.bUITitle != true) fprintf(fd, "%s = %s\n", cfg.names.uiTitle, cfg.defValues.uiTitle.c_str());
			else fprintf(fd, "%s = %s\n", cfg.names.uiTitle, cfg.values.uiTitle.c_str());
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

			if (_stricmp(tmpLeft, cfg.names.cHeight) == 0) {
				cfg.values.height = atoi(tmpRight);
				cfg.verify.bHeight = true;
				continue;
			}
			if (_stricmp(tmpLeft, cfg.names.cTopLeftX) == 0) {
				cfg.values.topLeftX = atoi(tmpRight);
				cfg.verify.bTopLeftX = true;
				continue;
			}
			if (_stricmp(tmpLeft, cfg.names.cWidth) == 0) {
				cfg.values.width = atoi(tmpRight);
				cfg.verify.bWidth = true;
				continue;
			}
			if (_stricmp(tmpLeft, cfg.names.uiTitle) == 0) {
				cfg.values.uiTitle = tmpRight;
				cfg.verify.bUITitle = true;
				continue;
			}
		}
		fclose(fd);
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return; // error
		}
		else {
			if (cfg.verify.bHeight != true) fprintf(fd, "%s = %i\n", cfg.names.cHeight, cfg.defValues.height);
			else fprintf(fd, "%s = %i\n", cfg.names.cHeight, cfg.values.height);
			if (cfg.verify.bTopLeftX != true) fprintf(fd, "%s = %i\n", cfg.names.cTopLeftX, cfg.defValues.topLeftX);
			else fprintf(fd, "%s = %i\n", cfg.names.cTopLeftX, cfg.values.topLeftX);
			if (cfg.verify.bWidth != true) fprintf(fd, "%s = %i\n", cfg.names.cWidth, cfg.defValues.width);
			else fprintf(fd, "%s = %i\n", cfg.names.cWidth, cfg.values.width);
			if (cfg.verify.bUITitle != true) fprintf(fd, "%s = %s\n", cfg.names.uiTitle, cfg.defValues.uiTitle.c_str());
			else fprintf(fd, "%s = %s\n", cfg.names.uiTitle, cfg.values.uiTitle.c_str());
			fclose(fd);
		}
	}
	void writeDefFile() {
		FILE *fd;
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return; // error
		}
		fprintf(fd, "%s = %i\n", cfg.names.cHeight, cfg.defValues.height);
		fprintf(fd, "%s = %i\n", cfg.names.cTopLeftX, cfg.defValues.topLeftX);
		fprintf(fd, "%s = %i\n", cfg.names.cWidth, cfg.defValues.width);
		fprintf(fd, "%s = %s\n", cfg.names.uiTitle, cfg.defValues.uiTitle.c_str());
		fclose(fd);
		verifyDefFile();
	}
};
