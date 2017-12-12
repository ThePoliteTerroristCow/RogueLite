#include <string>
#pragma once

class cfgAudioClass {
public:
	std::string fileName = "config\\audio.dat";
	void verifyDefAudio() {
		FILE *fd;
		fd = fopen(fileName.c_str(), "wt");
		if (fd == NULL) {
			return;
		}
		else {
		if (cfg.verify.bAmbientVolume != true) fprintf(fd, "%s = 100\n", cfg.names.ambientVolume);
		else fprintf(fd, "%s = %i\n", cfg.names.ambientVolume, cfg.values.iAmbientVolume);
		if (cfg.verify.bEffectsVolume != true) fprintf(fd, "%s = 100\n", cfg.names.effectsVolume);
		else fprintf(fd, "%s = %i\n", cfg.names.effectsVolume, cfg.values.iEffectsVolume);
		if (cfg.verify.bMasterVolume != true) fprintf(fd, "%s = 100\n", cfg.names.masterVolume);
		else fprintf(fd, "%s = %i\n", cfg.names.masterVolume, cfg.values.iMasterVolume);
		if (cfg.verify.bMusicVolume != true) fprintf(fd, "%s = 100\n", cfg.names.musicVolume);
		else fprintf(fd, "%s = %i\n", cfg.names.musicVolume, cfg.values.iMusicVolume);
		if (cfg.verify.bUIVolume != true) fprintf(fd, "%s = 100\n", cfg.names.uiVolume);
		else fprintf(fd, "%s = %i\n", cfg.names.uiVolume, cfg.values.iUIVolume);
			fclose(fd);
		}
	}
	struct cfgAudioStruct {
	public:
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