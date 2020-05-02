#ifndef CONFIGURATIONREADER_H
#define CONFIGURATIONREADER_H

#include <vector>
#include <string>

/**
 * \class ConfigurationReader
 *
 * \brief
 *
 * This class is responsible to read the configuration file.
 * The assumption here is configuration file will contain 
 * one directory path per line.
 */
class ConfigurationReader
{
public:
	/**
      * \brief return the only object of this singletone class (thread safe)
      */
    static ConfigurationReader& getInstance();

    /**
      * \brief deleted copy constructor
      */
    ConfigurationReader(const ConfigurationReader&) = delete;
    /**
      * \brief deleted copy assignment operator
      */
    void operator=(const ConfigurationReader&) = delete;

    /**
      * \brief parse the configuration file and store directories into a vector
      */
    void readConfiguration();
    /**
      * \return the monitored directories
      */
    const std::vector<std::string>& getMonitoringDirectories() const;

private:
	/**
      * \brief default constructor
      */
	ConfigurationReader() = default;

	// list of monitored directories
	std::vector<std::string> monitoringDirectories;
};

#endif /* CONFIGURATIONREADER_H */