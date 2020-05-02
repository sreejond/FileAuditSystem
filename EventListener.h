#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <ev.h>

using Delegate = void (struct ev_loop *loop, struct ev_io *io, int revents);

/**
 * \class EventListener
 *
 * \brief
 *
 * This class is responsible to configure the event loop
 * and setting up the delegate function to capture the events
 */
class EventListener
{
public:
	/**
      * \brief constructor
      * \param inFileDescriptor libaudit file descriptor
      * \param inDelegate delegate function
      */
	EventListener(const int inFileDescriptor, Delegate* inDelegate);
	/**
      * \brief start the event loop
      */
	void start();

private:
	// libaudit file descriptor
	const int m_fileDescriptor;
	// delegate function	
	Delegate* m_delegate;
	// event wather
	struct ev_io m_eventWatcher;
	// event loop
	struct ev_loop* m_eventLoop;
};

#endif /* EVENTLISTENER_H */