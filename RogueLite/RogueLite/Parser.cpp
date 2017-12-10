#include <stdio.h>
#include <Windows.h>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Main.h"
namespace pt = boost::property_tree;

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

void Parser::writeIni(char *fileName) {
	std::string filePath;
	filePath.append(configPath);
	filePath.append(fileName);

	// Check if config directory exists. Create it if it doesn't
	if (dirExists(configPath) == false) {
		if (!CreateDirectoryA(configPath, NULL)) {
			printf("Unable to create directory '%s' as it may already exist\n", configPath); // write this to the log later on...
		}
		else printf("Created directory '%s'\n", configPath); // write this to the log later on...
	}

	pt::ptree root;
	root.add("a.value", NULL);
	pt::write_ini(filePath, root);
}

void Parser::writeJson(char *fileName) {
	std::string filePath;
	filePath.append(configPath);
	filePath.append(fileName);

	// Check if config directory exists. Create it if it doesn't
	if (dirExists(configPath) == false) {
		if (!CreateDirectoryA(configPath, NULL)) {
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