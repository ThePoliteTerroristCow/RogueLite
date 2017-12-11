#include <stdio.h>
#include "Main.h"

Parser::Parser() {}

Parser::~Parser() {}

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

void Parser::readDefAudioCfg() {
	struct defAudioStruct {
	public:
		std::string nodeRoot = "Audio.";
		std::string nodeMasterVolume = nodeRoot,
			nodeAmbientVolume = nodeRoot,
			nodeEffectsVolume = nodeRoot,
			nodeMusicVolume = nodeRoot;
		void appendAll() {
			nodeAmbientVolume.append(defAudioStruct::ambientVolume);
			nodeEffectsVolume.append(defAudioStruct::effectsVolume);
			nodeMasterVolume.append(defAudioStruct::masterVolume);
			nodeMusicVolume.append(defAudioStruct::musicVolume);
		}
	protected:
		char *ambientVolume = "AmbientVolume";
		char *effectsVolume = "EffectsVolume";
		char *masterVolume = "MasterVolume";
		char *musicVolume = "MusicVolume";
	}defAudio;

	defAudio.appendAll();
	storedPtrees.storedAudioPtree.add(defAudio.nodeMasterVolume, 100);
	storedPtrees.storedAudioPtree.add(defAudio.nodeAmbientVolume, 100);
	storedPtrees.storedAudioPtree.add(defAudio.nodeEffectsVolume, 100);
	storedPtrees.storedAudioPtree.add(defAudio.nodeMusicVolume, 100);
}
void Parser::readDefGraphicsCfg() {
	struct defMainCon {
	public:
		std::string nodeRoot = "MainWindow.";
		std::string nodeHeight = nodeRoot, nodeWidth = nodeRoot, nodeFS = nodeRoot;
		void appendAll() {
			nodeHeight.append(defMainCon::conHeight);
			nodeWidth.append(defMainCon::conWidth);
			nodeFS.append(defMainCon::conFS);
		}
	protected:
		char *conHeight = "Height";
		char *conWidth = "Width";
		char *conFS = "Fullscreen";
	}mainCon;

	mainCon.appendAll();
	storedPtrees.storedGraphicsPtree.add(mainCon.nodeWidth, engine.screenWidth);
	storedPtrees.storedGraphicsPtree.add(mainCon.nodeHeight, engine.screenHeight);
	storedPtrees.storedGraphicsPtree.add(mainCon.nodeFS, TCODConsole::root->isFullscreen());
}
void Parser::writeDefAudioCfg() {
	std::string filePath = configPath;
	filePath.append("audio.ini");
	if (dirExists(configPath) == false) {
		if (!TCODSystem::createDirectory(configPath)) {} // failure, else success
	}

	// This is probably a bad way to do it, but it'll work until I figure out how to add things more dynamically
	struct defAudioStruct {
	public:
		std::string nodeRoot = "Audio.";
		std::string nodeMasterVolume = nodeRoot,
			nodeAmbientVolume = nodeRoot,
			nodeEffectsVolume = nodeRoot,
			nodeMusicVolume = nodeRoot;
		void appendAll() {
			nodeAmbientVolume.append(defAudioStruct::ambientVolume);
			nodeEffectsVolume.append(defAudioStruct::effectsVolume);
			nodeMasterVolume.append(defAudioStruct::masterVolume);
			nodeMusicVolume.append(defAudioStruct::musicVolume);
		}
	protected:
		char *ambientVolume = "AmbientVolume";
		char *effectsVolume = "EffectsVolume";
		char *masterVolume = "MasterVolume";
		char *musicVolume = "MusicVolume";
	}defAudio;

	defAudio.appendAll();
	storedPtrees.storedAudioPtree.add(defAudio.nodeMasterVolume, 100);
	storedPtrees.storedAudioPtree.add(defAudio.nodeAmbientVolume, 100);
	storedPtrees.storedAudioPtree.add(defAudio.nodeEffectsVolume, 100);
	storedPtrees.storedAudioPtree.add(defAudio.nodeMusicVolume, 100);
	pt::write_ini(filePath, storedPtrees.storedAudioPtree);
}
void Parser::writeDefGraphicsCfg() {
	std::string filePath = configPath;
	filePath.append("graphics.ini");
	if (dirExists(configPath) == false) {
		if (!TCODSystem::createDirectory(configPath)) {} // failure, else success
	}

	// This is probably a bad way to do it, but it'll work until I figure out how to add things more dynamically
	struct defMainCon {
	public:
		std::string nodeRoot = "MainWindow.";
		std::string nodeHeight = nodeRoot, nodeWidth = nodeRoot, nodeFS = nodeRoot;
		void appendAll() {
			nodeHeight.append(defMainCon::conHeight);
			nodeWidth.append(defMainCon::conWidth);
			nodeFS.append(defMainCon::conFS);
		}
	protected:
		char *conHeight = "Height";
		char *conWidth = "Width";
		char *conFS = "Fullscreen";
	}mainCon;

	mainCon.appendAll();
	storedPtrees.storedGraphicsPtree.add(mainCon.nodeWidth, engine.screenWidth);
	storedPtrees.storedGraphicsPtree.add(mainCon.nodeHeight, engine.screenHeight);
	storedPtrees.storedGraphicsPtree.add(mainCon.nodeFS, TCODConsole::root->isFullscreen());
	pt::write_ini(filePath, storedPtrees.storedGraphicsPtree);
}

//////////////////////////////////////////////////////////////////////////

void Parser::writeConfigi(char *fileName, char *rootNode, char *childVariable, int value) {
	std::string filePath;
	filePath.append(configPath);
	filePath.append(fileName);
	std::string nodeVar;
	nodeVar.append(rootNode);
	nodeVar.append(".");
	nodeVar.append(childVariable);

	if (dirExists(configPath) == false) {
		if (!TCODSystem::createDirectory(configPath)) {} // failure, else success
	}

	if (strcmp(fileName, "graphics.ini") == 0) {
		if (fileExists(filePath.c_str()) == true) {
			readDefGraphicsCfg();
			try {
				pt::read_ini(filePath, storedPtrees.rootGraphicsPtree);
			}
			catch (const pt::ptree_error &ptError) {
				printf("%s", ptError.what());
			}
			try {
				storedPtrees.rootGraphicsPtree.add(nodeVar, value);
			}
			catch (const pt::ptree_error &ptError) {
				printf("%s", ptError.what());
			}
			try {
				pt::write_ini(filePath, storedPtrees.rootGraphicsPtree);
			}
			catch (const pt::ptree_error &ptError) {
				printf("%s", ptError.what());
			}
		}
		else writeDefGraphicsCfg();
	}
	else if (strcmp(fileName, "audio.ini") == 0) {
		if (fileExists(filePath.c_str()) == true) {
			readDefAudioCfg();
			try {
				pt::read_ini(filePath, storedPtrees.rootAudioPtree);
			}
			catch (const pt::ptree_error &ptError) {
				printf("%s", ptError.what());
			}
			try {
				storedPtrees.rootAudioPtree.add(nodeVar, value);
			}
			catch (const pt::ptree_error &ptError) {
				printf("%s", ptError.what());
			}
			try {
				pt::write_ini(filePath, storedPtrees.rootAudioPtree);
			}
			catch (const pt::ptree_error &ptError) {
				printf("%s", ptError.what());
			}
		}
		else writeDefAudioCfg();
	}
	else { printf("config file not found!\n"); return; }
}

//////////////////////////////////////////////////////////////////////////

void Parser::writeJson(char *fileName) {
	std::string filePath;
	filePath.append(configPath);
	filePath.append(fileName);

	// Check if config directory exists. Create it if it doesn't
	if (dirExists(configPath) == false) {
		if (!TCODSystem::createDirectory(configPath)) {
			printf("Unable to create directory '%s' as it may already exist\n", configPath); // write this to the log later on...
		}
		else printf("Created directory '%s'\n", configPath); // write this to the log later on...
	}

	pt::ptree root;
	root.add("Equipable.Armour.Wood.Value", 10);
	pt::write_json(filePath, root);
}

void Parser::parseFile(char *fileName, char *valueName) {
	pt::ptree root;
	int fValue = 0;
	if (fileName == NULL || valueName == NULL) {
		printf("Error parsing value '%s' in file '%s'!\n", valueName, fileName);
		return;
	}

	pt::read_json(fileName, root);
	fValue = root.get<int>(valueName, 0);
	printf("\nRead value '%i' from variable '%s' in file '%s'\n", fValue, valueName, fileName);
	printf("\nValue: %i\n", fValue);
}