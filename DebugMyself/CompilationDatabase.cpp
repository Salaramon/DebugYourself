#include "CompilationDatabase.h"


CompilationDatabase::CompilationDatabase(std::string projectPath, std::string solutionPath, std::string configuration, std::string platform) {

	nlohmann::json compilationDatabase;

	pugi::xml_document vcxprojDocument;
	std::string vcxprojName = getVSProjectFileName(projectPath);

	if (!vcxprojName.empty()) {
		std::vector<std::string> cppFileList = getVSCompilationDatabaseFiles(projectPath + vcxprojName);
		std::vector<std::string> includes = getVSCompilationDatabaseIncludes(projectPath, vcxprojName, solutionPath, configuration, platform);
		std::vector<std::string> arguments;
		for (auto& file : cppFileList) {
			arguments = getVSCompilationDatabaseArguments(projectPath, vcxprojName, file, includes);
		}



		nlohmann::json entry;
		for (size_t i = 0; i < cppFileList.size(); i++) {
			entry[Fields::directory] = projectPath;
			entry[Fields::file] = cppFileList[i];
			entry[Fields::arguments] = arguments;
			compilationDatabase.push_back(entry);
		}
	}

	database = compilationDatabase.dump();

	//std::ofstream file("compile_commands.json");
	//file.write(database.c_str(), database.length());
	//file.close();



}
