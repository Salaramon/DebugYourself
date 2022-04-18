#pragma once

#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <iostream>

class Configuration
{
public:

	static void initializeConfigurationFromExecutableArguments(const int argc, const char* argv[]) {
		const std::vector<std::string> arguments(argv + 1, argv + argc);
		for (size_t i = 0; i < arguments.size(); i += 2) {
			const size_t flag = i;
			const size_t arg = i + 1;
			auto it = argumentCallbacks.find(arguments[flag]);
			if (it == argumentCallbacks.end()) {
				std::cerr << "Invalid flag \"" << flag << "\"" << std::endl;
			}
			else {
				it->second(arguments[arg]);
			}
		}
	}

	struct Project {
		inline static std::string path;
	};
	struct Build {
		inline static std::string configuration;
		inline static std::string platform;
		inline static std::string sdk;
	};
	struct Solution {
		inline static std::string path;
	};

	

private:


	//Argument callbacks
	inline static void projectPath(const std::string arg) {
		Configuration::Project::path = arg;
	}
	inline static void solutionPath(const std::string arg) {
		Configuration::Solution::path = arg;
	}
	inline static void buildConfiguration(const std::string arg) {
		Configuration::Build::configuration = arg;
	}
	inline static void buildSDK(const std::string arg) {
		Configuration::Build::sdk = arg;
	}
	inline static void buildPlatform(const std::string arg) {
		Configuration::Build::platform = arg;
	}

	//Argument callback map
	inline static std::unordered_map<std::string, std::function<void(std::string)>> argumentCallbacks = {
		{"-p", &Configuration::projectPath},
		{"-s", &Configuration::solutionPath},
		{"-vs-conf", &Configuration::buildConfiguration},
		{"-vs-plat", &Configuration::buildPlatform},
		{"-sdk", &Configuration::buildSDK}
	};
};

