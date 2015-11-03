#pragma once
#include <map>
#include <fstream>
#include <iostream>

namespace Config {
	typedef	std::map< std::string, std::string > ConfigTable;
	ConfigTable readConfig(std::string filename);

}