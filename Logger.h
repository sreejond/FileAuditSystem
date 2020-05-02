#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <mutex>

/**
 * \class Logger
 *
 * \brief
 *
 * This class is responsible to write the monitored events in the log file
 * provided by FileAuditSystemUtil.h
 */
class Logger
{
public:
	/**
      * \brief return the only object of this singletone class (thread safe)
      */
	static Logger& getInstance();
	/**
      * \brief write the log message into log file (thread safe)
      * \param inMsg log message
      */
	void write(const std::string& inMsg);

	/**
      * \brief deleted copy constructor
      */
    Logger(const Logger&) = delete;
    /**
      * \brief deleted copy assignment operator
      */
    void operator=(const Logger&) = delete;

private:
	/**
      * \brief constructor
      */
	Logger();
	/**
      * \brief check if the log file exist
      * \return true if file exist; otherwise false
      */
	bool isFileExist();
	
	// log file ofstream
	std::ofstream m_outfile;
	// mutex for synchronized write()
	std::mutex m_mutex;
};

#endif /* LOGGER_H */