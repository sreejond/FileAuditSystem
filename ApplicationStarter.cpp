#include <iostream>

#include "DaemonProcess.h"
#include "Exception.h"
#include "EventListener.h"
#include "MonitorDirectory.h"
#include "EventHandler.h"
#include "ConfigurationReader.h"

int main(int argc, char *argv[])
{
	try
	{
		DaemonProcess::create();
		ConfigurationReader& configurationReader = ConfigurationReader::getInstance();
		configurationReader.readConfiguration();
		auto monitoringDirectories = configurationReader.getMonitoringDirectories();
		
		MonitorDirectory& monitorDirectory = MonitorDirectory::getInstance();
		for (auto& directory : monitoringDirectories)
		{
			monitorDirectory.addDirectory(directory);
		}
		
		EventListener eventListener{monitorDirectory.getFileDescriptor(), &EventHandler::processEvent};
		eventListener.start();
	}
	catch (Exception& e) 
	{
		std::string message(e.what());
		syslog(LOG_ERR, "%s", message.c_str());
		return EXIT_FAILURE;
	}
	catch(...)
	{
		std::string message("Uncaught exception!!");
		syslog(LOG_ERR, "%s", message.c_str());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}