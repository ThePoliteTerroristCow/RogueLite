#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

class Parser
{
public:
	Parser();
	~Parser();

	void writeConfigi(char *fileName, char *rootNode, char *childVariable, int value);
	void writeConfigf(char *fileName, char *rootNode, char *childVariable, float value);
	void writeConfigc(char *fileName, char *rootNode, char *childVariable, char value);
	void writeConfigstr(char *fileName, char *rootNode, char *childVariable, std::string value);

	void writeJson(char *fileName);
	void parseFile(char *fileName, char *valueName);

protected:
	struct storedPtStruct {
		pt::ptree storedAudioPtree, storedGraphicsPtree, rootAudioPtree, rootGraphicsPtree;
	}storedPtrees;
	char *configPath = "config\\";
	bool dirExists(char *fileDir);
	bool fileExists(const char *filePath);

	void readDefGraphicsCfg();
	void readDefAudioCfg();
	void writeDefGraphicsCfg();
	void writeDefAudioCfg();
};