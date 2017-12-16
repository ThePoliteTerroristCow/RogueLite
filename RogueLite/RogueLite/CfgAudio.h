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
		FILE *fd;
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return;
		}
		else {
		if (cfg.verify.bAmbientVolume != true) fprintf(fd, "%s = %i\n", cfg.names.ambientVolume, cfg.defValues.iAmbientVolume);
		else fprintf(fd, "%s = %i\n", cfg.names.ambientVolume, cfg.values.iAmbientVolume);
		if (cfg.verify.bEffectsVolume != true) fprintf(fd, "%s = %i\n", cfg.names.effectsVolume, cfg.defValues.iEffectsVolume);
		else fprintf(fd, "%s = %i\n", cfg.names.effectsVolume, cfg.values.iEffectsVolume);
		if (cfg.verify.bMasterVolume != true) fprintf(fd, "%s = %i\n", cfg.names.masterVolume, cfg.defValues.iMasterVolume);
		else fprintf(fd, "%s = %i\n", cfg.names.masterVolume, cfg.values.iMasterVolume);
		if (cfg.verify.bMusicVolume != true) fprintf(fd, "%s = %i\n", cfg.names.musicVolume, cfg.defValues.iMusicVolume);
		else fprintf(fd, "%s = %i\n", cfg.names.musicVolume, cfg.values.iMusicVolume);
		if (cfg.verify.bUIVolume != true) fprintf(fd, "%s = %i\n", cfg.names.uiVolume, cfg.defValues.iUIVolume);
		else fprintf(fd, "%s = %i\n", cfg.names.uiVolume, cfg.values.iUIVolume);
			fclose(fd);
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
};