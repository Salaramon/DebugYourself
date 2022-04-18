#pragma once

#include <filesystem>
#include <algorithm>
#include <fstream>

#include <nlohmann/json.hpp>
#include <pugixml.hpp>

#include "Configuration.h"

class CompilationDatabase
{
public:
	CompilationDatabase(std::string projectPath, std::string solutionPath, std::string configuration, std::string platform);

	std::vector<std::string> getVSCompilationDatabaseFiles(std::string vcxprojPath) {
		std::vector<std::string> output;

		pugi::xml_document vcxprojDocument;
		pugi::xml_parse_result vcxprojResult = vcxprojDocument.load_file(vcxprojPath.c_str());


		pugi::xml_node cppIncludeStart = vcxprojDocument.find_node([](const pugi::xml_node& node) {
			return node.name() == std::string("ClCompile") && node.attribute("Include"); });

		do {
			if (cppIncludeStart.name() == std::string("ClCompile") && cppIncludeStart.attribute("Include")) {
				output.push_back(cppIncludeStart.attribute("Include").value());
			}
		}
		while (cppIncludeStart = cppIncludeStart.next_sibling());

		return output;
	}

	void findReplaceAll(std::string& data, std::string search, std::string replaceStr)
	{
		while (data.find(search) != std::string::npos) {
			data.replace(data.find(search), search.size(), replaceStr);
		}
	}

	void splitInsert(std::vector<std::string>& vec, std::string str, const std::string delim) {
		size_t pos = str.find(delim);
		while (pos != std::string::npos) {
			vec.push_back(str.substr(0, pos));
			str.replace(0, pos+1, "");
			pos = str.find(delim);
		}
	}

	std::vector<std::string> getVSCompilationDatabaseIncludes(std::string projectPath, std::string vcxprojName, std::string solutionPath, std::string configuration, std::string platform) {
		std::vector<std::string> output;
		output.push_back("C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.31.31103/include");
		output.push_back("C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.31.31103/atlmfc/include");
		output.push_back("C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/VS/include");
		output.push_back("C:/Program Files (x86)/Windows Kits/10/Include/10.0.20348.0/ucrt");
		output.push_back("C:/Program Files (x86)/Windows Kits/10/Include/10.0.20348.0/um");
		output.push_back("C:/Program Files (x86)/Windows Kits/10/Include/10.0.20348.0/shared");
		output.push_back("C:/Program Files (x86)/Windows Kits/10/Include/10.0.20348.0/winrt");
		output.push_back("C:/Program Files (x86)/Windows Kits/10/Include/10.0.20348.0/cppwinrt");


		pugi::xml_document vcxprojDocument;
		std::cout << (projectPath + vcxprojName).c_str() << std::endl;
		pugi::xml_parse_result vcxprojResult = vcxprojDocument.load_file((projectPath + vcxprojName).c_str());


		auto nodeSearch = [](const pugi::xml_node& node) {
			std::cout << (node.name() == std::string("PropertyGroup")) << node.child("IncludePath") << node.attribute("Condition") << std::endl;
			return node.name() == std::string("PropertyGroup") && node.child("IncludePath") && node.attribute("Condition"); };

		pugi::xml_node includePaths;

		while (pugi::xml_node includePaths = vcxprojDocument.find_node([](const pugi::xml_node& node) {
			std::cout << (node.name() == std::string("PropertyGroup")) << static_cast<bool>(node.child("IncludePath")) << static_cast<bool>(node.attribute("Condition")) << std::endl;
			return node.name() == std::string("PropertyGroup") && node.child("IncludePath") && node.attribute("Condition"); })){

			if (includePaths.attribute("Condition").value() == std::string("'$(Configuration)|$(Platform)'=='" + configuration + "|" + platform + "'")) {
				std::string includes = includePaths.child("IncludePath").text().as_string();
				findReplaceAll(includes, Macros::ProjectDir, projectPath);
				findReplaceAll(includes, Macros::SolutionDir, solutionPath);
				findReplaceAll(includes, Macros::IncludePath, "");

				splitInsert(output, includes, ";");
				break;
			}
		}

		return output;
	}

	std::vector<std::string> getVSCompilationDatabaseArguments(std::string vcxprojPath, std::string vcxprojName, const std::string file, const std::vector<std::string>& includes) {
		std::vector<std::string> output;

		output.push_back(Defaults::clang);
		output.push_back(Defaults::cpp);
		output.push_back(file);
		output.push_back("-std=c++20"); //TEMPORARY
		output.push_back(Defaults::wall);
		for (auto& in : includes) {
			output.push_back("-I");
			output.push_back(in);
		}

		return output;
	}

	std::string getVSProjectFileName(std::string projectPath) {
		for (const auto& entry : std::filesystem::directory_iterator(projectPath)) {
			if (entry.path().extension().compare(".vcxproj") == 0) {
				return entry.path().filename().string();;
				break;
			}
		}
		std::cerr << "Could not find \".vcxproj\"." << std::endl;
		return "";
	}

	void createFromVSProject(std::string path) {
		
	}

	std::string getCompilationDatabase() {
		return database;
	}

private:


	std::string database;

	struct Defaults {
		inline static const std::string clang = "clang++";
		inline static const std::string cpp = "-xc++";
		inline static const std::string wall = "-Wall";

	};
	struct Fields {
		inline static const std::string directory = "directory";
		inline static const std::string file = "file";
		inline static const std::string arguments = "arguments";
		inline static const std::string command = "command";
		inline static const std::string output = "output";
	};
	struct Macros {
		inline static const std::string SolutionDir = "$(SolutionDir)";
		inline static const std::string ProjectDir = "$(ProjectDir)"; 
		inline static const std::string IncludePath = "$(IncludePath)";
	};
};

