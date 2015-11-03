#include "Config.h"
#include <string>
#include <Util.h>
#include <vector>
namespace Config {
	ConfigTable readConfig(std::string filename) {
		std::ifstream ifs("configs/" + filename);
		if (!ifs.is_open())
		{
			std::cerr << "can't open file: " << filename << std::endl;
			return ConfigTable();
		}
		std::cout << "read config:" << filename << std::endl;

		std::string line;
		ConfigTable configTable;
		while (ifs >> line)
		{
			std::vector<std::string> v = Util::split(line, ":");
			if (v.size() != 2)
			{
				std::cerr << "invalid config status" << std::endl;
				continue;
			}
			configTable[v[0]] = v[1];
		}
		return configTable;
	}
}