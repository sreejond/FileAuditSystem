#include "EventListener.h"

EventListener::EventListener(const int inFileDescriptor, Delegate* inDelegate)
: m_fileDescriptor(inFileDescriptor)
, m_delegate(inDelegate)
, m_eventLoop(nullptr)
{
	m_eventLoop = ev_default_loop(EVFLAG_NOENV);
	//TODO: ev_loop_destroy()
	ev_io_init(&m_eventWatcher, m_delegate, m_fileDescriptor, EV_READ);
}

void EventListener::start()
{
	ev_io_start(m_eventLoop, &m_eventWatcher);
	//TODO: ev_io_stop()
	ev_loop(m_eventLoop, 0);
}