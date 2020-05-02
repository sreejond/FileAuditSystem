#ifndef MONITORDIRECTORY_H
#define MONITORDIRECTORY_H

#include <libaudit.h>
#include <unordered_map>

/**
 * \class MonitorDirectory
 *
 * \brief
 *
 * This class is responsible to setup libaudit for monitoring provided directories
 */
class MonitorDirectory final
{
public:
	/**
      * \brief default destructor
      */
	~MonitorDirectory();

	/**
      * \brief return the only object of this singletone class (thread safe)
      */
    static MonitorDirectory& getInstance();

    /**
      * \brief deleted copy constructor
      */
    MonitorDirectory(const MonitorDirectory&) = delete;
    /**
      * \brief deleted copy assignment operator
      */
    void operator=(const MonitorDirectory&) = delete;

    /**
      * \brief add directory rule for libaudit
      * \param inDirectory directory path
      */
    bool addDirectory(const std::string& inDirectory);
    /**
      * \brief remove directory rule from libaudit
      * \param inDirectory directory path
      */
    bool removeDirectory(const std::string& inDirectory);
    /**
      * \brief getter method for libaudit file descriptor
      * \return libaudit file descriptor
      */
    inline int getFileDescriptor() const {return m_auditFileDescriptor;}

private:
	/**
      * \brief constructor
      */
	MonitorDirectory();
	/**
      * \brief remove all directory rule from libaudit
      */
	bool removeAllDirectory();
	/**
      * \brief delete directory rule from libaudit
      * \param rule libaudit rule
      */
	bool deleteRule(struct audit_rule_data* rule);

	// libaudit file descriptor
	int m_auditFileDescriptor;
	// mapping of directory path to libaudit rule
	std::unordered_map<std::string, struct audit_rule_data*> m_auditRules;
};

#endif /* MONITORDIRECTORY_H */