#include "ConfigurationReader.h"
#include "FileAuditSystemUtil.h"

#include <fstream>

ConfigurationReader& ConfigurationReader::getInstance()
{
    static ConfigurationReader instance;
    return instance;
}

void ConfigurationReader::readConfiguration()
{
	std::ifstream infile(configurationFile);
	std::string directory;
	while (std::getline(infile, directory))
	{
		if (directory.empty())	continue;
		monitoringDirectories.push_back(directory);
	}
}

const std::vector<std::string>& ConfigurationReader::getMonitoringDirectories() const
{
	return monitoringDirectories;
}