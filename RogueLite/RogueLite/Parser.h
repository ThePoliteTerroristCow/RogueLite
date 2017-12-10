class Parser
{
public:
	Parser();
	~Parser();

	void writeIni(char *fileName);
	void writeJson(char *fileName);
	void parseFile(char *fileName, char *valueName);

protected:
	char *configPath = "config\\";
	bool dirExists(char *fileDir);
};