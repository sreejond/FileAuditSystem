#include "DaemonProcess.h"
#include "Exception.h"

#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>

void DaemonProcess::create()
{
	// Fork off the parent process
	pid_t pid = fork();

	// An error occurred
	if (pid < 0) 
	{
		throw Exception("First child process creation failed!!");
	}

	// Success: Let the parent terminate
	if (pid > 0) 
	{
		exit(EXIT_SUCCESS);
	}

	// On success: The child process becomes session leader
	if (setsid() < 0) 
	{
		throw Exception("First child process failed to become session leader!!");
	}

	// Ignore signal sent from child to parent process
	signal(SIGCHLD, SIG_IGN);
	signal(SIGHUP, SIG_IGN);

	// Fork off for the second time
	pid = fork();

	// An error occurred
	if (pid < 0) 
	{
		throw Exception("Second child process creation failed!!");
	}

	// Success: Let the parent terminate
	if (pid > 0) 
	{
		exit(EXIT_SUCCESS);
	}

	// Set new file permissions
	umask(0);

	// Change the working directory to the root directory
	chdir("/");

	// Close all open file descriptors
	for (int fd = sysconf(_SC_OPEN_MAX); fd >= 0; fd--) {
		close(fd);
	}
}