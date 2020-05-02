#include "Logger.h"
#include "FileAuditSystemUtil.h"

#include <iostream>
#include <iomanip>

Logger::Logger()
{
	if (!isFileExist())
	{
		m_outfile.open(logFileDir, std::ofstream::out | std::ofstream::app);
		if (m_outfile.is_open())
		{
			m_outfile << std::setw(14) << "timestamp";
			m_outfile << std::setw(5) << "pid";
			m_outfile << std::setw(5) << "uid";
			m_outfile << std::setw(5) << "comm" << std::endl;
		}
	}
}

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

bool Logger::isFileExist()
{
    std::ifstream infile(logFileDir);
    return infile.good();
}

void Logger::write(const std::string& inMsg)
{
	std::lock_guard<std::mutex> lock{m_mutex};
	m_outfile.open(logFileDir, std::ofstream::out | std::ofstream::app);
	if (m_outfile.is_open())
	{
		m_outfile << inMsg << std::endl;
		m_outfile.close();
	}
}