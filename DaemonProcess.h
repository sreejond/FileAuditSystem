#ifndef DAEMONPROCESS_H
#define DAEMONPROCESS_H

/**
 * \class DaemonProcess
 *
 * \brief
 *
 * This class is responsible to create a daemon process
 */
class DaemonProcess
{
public:
	/**
      * \brief create the daemon process
      */
	static void create();

	/**
      * \brief deleted copy constructor
      */
	DaemonProcess(const DaemonProcess&) = delete;
	/**
      * \brief deleted copy assignment operator
      */
    void operator=(DaemonProcess const&) = delete;
    
private:
	/**
      * \brief default constructor
      */
	DaemonProcess() = default;
};

#endif /* DAEMONPROCESS_H */

