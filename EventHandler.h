#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <string>
#include <unordered_map>

/**
 * \class EventHandler
 *
 * \brief
 *
 * This class is responsible to catch the event triggered by libaudit
 */
class EventHandler
{
public:
	/**
      * \brief This is the delegate function that being passed to libaudit
      */
	static void processEvent(struct ev_loop *loop, struct ev_io *io, int revents);

	/**
      * \brief deleted copy constructor
      */
	EventHandler(const EventHandler&) = delete;
    /**
      * \brief deleted copy assignement operator
      */
    void operator=(EventHandler const&) = delete;
    
private:
	/**
      * \brief default constructor
      */
	EventHandler() = default;
	/**
      * \brief create the log message based on the monitored points provided in FileAuditSystemUtil.h
      * \param parsed key value pair from the SYSTEM_CALL message
      * \return log message
      */
	static std::string createMsg(const std::unordered_map<std::string, std::string>& inKeyValues);
};

#endif /* EVENTHANDLER_H */