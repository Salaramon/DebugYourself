
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>
#include <array>
#include <string.h>

#include <cppast/libclang_parser.hpp>
#include <type_safe/reference.hpp>
#include <cppast/cpp_class.hpp>
#include <cppast/cpp_entity_kind.hpp>
#include <process.hpp>
#include <clang-c/CXCompilationDatabase.h>

#include <pugixml.hpp>

#include "Configuration.h"
#include "CompilationDatabase.h"
/*
std::vector<std::string> getProjectFileNames(std::string extension) {

}

std::vector<std::string> getProjectCodeFileNames() {
	//for loop: iterate through files by extensions listed in a toml configuration file for all files to be included.
	std::vector<std::string> headerFiles = getProjectFileNames("eg. .h");
	//std::vector<std::string> cppFiles =
}
*/


int main(const int argc, const char* argv[]) {

	Configuration::initializeConfigurationFromExecutableArguments(argc, argv);

	CompilationDatabase compilationDatabase(
		Configuration::Project::path,
		Configuration::Solution::path,
		Configuration::Build::configuration,
		Configuration::Build::platform);

	std::string compData = compilationDatabase.getCompilationDatabase();

	
}



/*
int main(int argc, char* argv[]) {

	//argv[0] build dir

	cppast::cpp_entity_index entityIndex;
	//std::vector<std::string> projectFiles = getProjectCodeFileNames();
	cppast::libclang_compile_config libclangCompileConfig;

	auto error = CXCompilationDatabase_NoError;
	CXCompilationDatabase database = clang_CompilationDatabase_fromDirectory("", &error);
	if (error != CXCompilationDatabase_NoError) {
		std::cerr << "Failed to load compilation database!" << std::endl;
		return 1;
	}

	clang_

	(cppast::libclang_compilation_database)(reinterpret_cast<CXCompilationDatabase>(database));
	cppast::libclang_compilation_database cppastDatabase{};
	//cppast::libclang_compilation_database database(test);
	std::cout << sizeof(database) << std::endl;
	cppast::simple_file_parser<cppast::libclang_parser> parser(type_safe::ref(entityIndex));

	try {
		cppast::parse_database(parser, database);
	}
	catch (cppast::libclang_error& e)
	{
		std::cerr << "fatal libclang error: " << e.what() << '\n';
		return 1;
	}


	for (const cppast::cpp_file& file : parser.files()) {
		for (auto it = file.begin(); it != file.end(); it++) {
			if (it->kind() == cppast::cpp_entity_kind::class_t) {
				std::cout << it->name() << std::endl;
			}
		}
	}


}

*/