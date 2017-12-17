#include <string>
#include <Windows.h>
#pragma once

class cfgAudioClass {
public:
	struct dirNameStruct {
	public:
		std::string dataDirName = "data\\";
		std::string configDirName = "data\\config\\";
	}dir;
	std::string fileName = "data\\config\\audio.dat";
	void verifyDefAudio() {
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

				// Find & store our values
				if (_stricmp(tmpLeft, cfg.names.ambientVolume) == 0) {
					cfg.values.iAmbientVolume = atoi(tmpRight);
					cfg.verify.bAmbientVolume = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.effectsVolume) == 0) {
					cfg.values.iEffectsVolume = atoi(tmpRight);
					cfg.verify.bEffectsVolume = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.masterVolume) == 0) {
					cfg.values.iMasterVolume = atoi(tmpRight);
					cfg.verify.bMasterVolume = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.musicVolume) == 0) {
					cfg.values.iMusicVolume = atoi(tmpRight);
					cfg.verify.bMusicVolume = true;
					continue;
				}
				if (_stricmp(tmpLeft, cfg.names.uiVolume) == 0) {
					cfg.values.iUIVolume = atoi(tmpRight);
					cfg.verify.bUIVolume = true;
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
				if (cfg.verify.bMasterVolume != true) fprintf(fd, "%s = %i\n", cfg.names.masterVolume, cfg.defValues.iMasterVolume);
				else fprintf(fd, "%s = %i\n", cfg.names.masterVolume, cfg.values.iMasterVolume);
				if (cfg.verify.bAmbientVolume != true) fprintf(fd, "%s = %i\n", cfg.names.ambientVolume, cfg.defValues.iAmbientVolume);
				else fprintf(fd, "%s = %i\n", cfg.names.ambientVolume, cfg.values.iAmbientVolume);
				if (cfg.verify.bEffectsVolume != true) fprintf(fd, "%s = %i\n", cfg.names.effectsVolume, cfg.defValues.iEffectsVolume);
				else fprintf(fd, "%s = %i\n", cfg.names.effectsVolume, cfg.values.iEffectsVolume);
				if (cfg.verify.bMusicVolume != true) fprintf(fd, "%s = %i\n", cfg.names.musicVolume, cfg.defValues.iMusicVolume);
				else fprintf(fd, "%s = %i\n", cfg.names.musicVolume, cfg.values.iMusicVolume);
				if (cfg.verify.bUIVolume != true) fprintf(fd, "%s = %i\n", cfg.names.uiVolume, cfg.defValues.iUIVolume);
				else fprintf(fd, "%s = %i\n", cfg.names.uiVolume, cfg.values.iUIVolume);
				fclose(fd);
			}
		}
	}
	struct cfgAudioStruct {
	public:
		struct defaultValuesStruct {
		public:
			int iAmbientVolume = 100;
			int iEffectsVolume = 100;
			int iMasterVolume = 100;
			int iMusicVolume = 100;
			int iUIVolume = 100;
		}defValues;
		struct valuesStruct {
		public:
			int iAmbientVolume;
			int iEffectsVolume;
			int iMasterVolume;
			int iMusicVolume;
			int iUIVolume;
		}values;
		struct namesStruct {
		public:
			char *ambientVolume = "AmbientVolume";
			char *effectsVolume = "EffectsVolume";
			char *masterVolume = "MasterVolume";
			char *musicVolume = "MusicVolume";
			char *uiVolume = "UIVolume";
		}names;
		struct verifyStruct {
		public:
			bool bAmbientVolume = false;
			bool bEffectsVolume = false;
			bool bMasterVolume = false;
			bool bMusicVolume = false;
			bool bUIVolume = false;
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
		fprintf(fd, "%s = %i\n", cfg.names.masterVolume, cfg.defValues.iMasterVolume);
		fprintf(fd, "%s = %i\n", cfg.names.ambientVolume, cfg.defValues.iAmbientVolume);
		fprintf(fd, "%s = %i\n", cfg.names.effectsVolume, cfg.defValues.iEffectsVolume);
		fprintf(fd, "%s = %i\n", cfg.names.musicVolume, cfg.defValues.iMusicVolume);
		fprintf(fd, "%s = %i\n", cfg.names.uiVolume, cfg.defValues.iUIVolume);
		fclose(fd);
	}
};