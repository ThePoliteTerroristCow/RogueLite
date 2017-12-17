#include <string>
#include <Windows.h>
#pragma once

class cfgControlsClass {
public:
	struct dirNameStruct {
	public:
		std::string dataDirName = "data\\";
		std::string configDirName = "data\\config\\";
	}dir;
	std::string fileName = "data\\config\\controls.dat";
	void verifyDefControls() {
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

				if (_stricmp(tmpLeft, cfg.names.moveDown) == 0) {
					cfg.values.moveDown = tmpRight;
					cfg.verify.bMoveDown = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.moveLeft) == 0) {
					cfg.values.moveLeft = tmpRight;
					cfg.verify.bMoveLeft = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.moveRight) == 0) {
					cfg.values.moveRight = tmpRight;
					cfg.verify.bMoveRight = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.moveUp) == 0) {
					cfg.values.moveUp = tmpRight;
					cfg.verify.bMoveUp = true;
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
				isStrValid();
				fprintf(fd, "#Gameplay\n");
				if (cfg.verify.bMoveUp != true) fprintf(fd, "%s = %s\n", cfg.names.moveUp, cfg.defValues.moveUp.c_str());
				else fprintf(fd, "%s = %s\n", cfg.names.moveUp, cfg.values.moveUp.c_str());
				if (cfg.verify.bMoveDown != true) fprintf(fd, "%s = %s\n", cfg.names.moveDown, cfg.defValues.moveDown.c_str());
				else fprintf(fd, "%s = %s\n", cfg.names.moveDown, cfg.values.moveDown.c_str());
				if (cfg.verify.bMoveLeft != true) fprintf(fd, "%s = %s\n", cfg.names.moveLeft, cfg.defValues.moveLeft.c_str());
				else fprintf(fd, "%s = %s\n", cfg.names.moveLeft, cfg.values.moveLeft.c_str());
				if (cfg.verify.bMoveRight != true) fprintf(fd, "%s = %s\n", cfg.names.moveRight, cfg.defValues.moveRight.c_str());
				else fprintf(fd, "%s = %s\n", cfg.names.moveRight, cfg.values.moveRight.c_str());
				fclose(fd);
			}
		}
	}

	struct cfgControlsStruct {
	public:
		struct defValuesStruct {
		public:
			std::string moveUp = "w";
			std::string moveDown = "s";
			std::string moveLeft = "a";
			std::string moveRight = "d";
		}defValues;
		struct namesStruct {
		public:
			char *moveUp = "Up";
			char *moveDown = "Down";
			char *moveLeft = "Left";
			char *moveRight = "Right";
		}names;
		struct valuesStruct {
		public:
			std::string moveUp;
			std::string moveDown;
			std::string moveLeft;
			std::string moveRight;
		}values;
		struct verifyStruct {
		public:
			bool bMoveUp = false;
			bool bMoveDown = false;
			bool bMoveLeft = false;
			bool bMoveRight = false;
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
	void isStrValid() {
		if (strlen(cfg.values.moveDown.c_str()) <= 0) cfg.values.moveDown = cfg.defValues.moveDown;
		else if (strlen(cfg.values.moveDown.c_str()) > 1) cfg.values.moveDown = cfg.defValues.moveDown;
		if (strlen(cfg.values.moveLeft.c_str()) <= 0) cfg.values.moveLeft = cfg.defValues.moveLeft;
		else if (strlen(cfg.values.moveLeft.c_str()) > 1) cfg.values.moveLeft = cfg.defValues.moveLeft;
		if (strlen(cfg.values.moveRight.c_str()) <= 0) cfg.values.moveRight = cfg.defValues.moveRight;
		else if (strlen(cfg.values.moveRight.c_str()) > 1) cfg.values.moveRight = cfg.defValues.moveRight;
		if (strlen(cfg.values.moveUp.c_str()) <= 0) cfg.values.moveUp = cfg.defValues.moveUp;
		else if (strlen(cfg.values.moveUp.c_str()) > 1) cfg.values.moveUp = cfg.defValues.moveUp;
	}
	void writeDefFile() {
		FILE *fd;
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return; // error
		}
		fprintf(fd, "#Gameplay\n");
		fprintf(fd, "%s = %s\n", cfg.names.moveUp, cfg.defValues.moveUp.c_str());
		fprintf(fd, "%s = %s\n", cfg.names.moveDown, cfg.defValues.moveDown.c_str());
		fprintf(fd, "%s = %s\n", cfg.names.moveLeft, cfg.defValues.moveLeft.c_str());
		fprintf(fd, "%s = %s\n", cfg.names.moveRight, cfg.defValues.moveRight.c_str());
		fclose(fd);
		verifyDefControls();
	}
};
