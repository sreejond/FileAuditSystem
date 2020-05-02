#include "MonitorDirectory.h"
#include "Exception.h"

#include <unistd.h>
#include <iostream>

MonitorDirectory::MonitorDirectory()
{
	m_auditFileDescriptor = audit_open();
	if (m_auditFileDescriptor < 0)
	{
		throw Exception("Failed to open libaudit!!");
	}

	audit_set_pid(m_auditFileDescriptor, getpid(), WAIT_YES);
	audit_set_enabled(m_auditFileDescriptor, 1);
}

MonitorDirectory::~MonitorDirectory()
{
	removeAllDirectory();
	audit_close(m_auditFileDescriptor);
}

MonitorDirectory& MonitorDirectory::getInstance()
{
    static MonitorDirectory instance;
    return instance;
}

bool MonitorDirectory::addDirectory(const std::string& inDirectory)
{
	struct audit_rule_data* rule = new audit_rule_data();
	m_auditRules[inDirectory] = rule;

	if (audit_add_watch_dir(AUDIT_DIR, &rule, inDirectory.c_str()) < 0)
	{
		throw Exception("Failed to add directory for monitoring!!");
	}

	if (audit_add_rule_data(m_auditFileDescriptor, rule, AUDIT_FILTER_EXIT, AUDIT_ALWAYS) <= 0)
	{
		throw Exception("Failed to add rule to monitor a directory!!");	
	}

	return true;
}

bool MonitorDirectory::removeDirectory(const std::string& inDirectory)
{
	auto iter = m_auditRules.find(inDirectory);
	if (iter == m_auditRules.end())
	{
		throw Exception("Directory is not in the monitoring list!!");
	}
	
	deleteRule(iter->second);
	return true;
}

bool MonitorDirectory::removeAllDirectory()
{
	for (auto iter = m_auditRules.begin(); iter != m_auditRules.end(); iter++)
	{
		deleteRule(iter->second);
	}

	return true;
}

bool MonitorDirectory::deleteRule(struct audit_rule_data* rule)
{
	try
	{
		if (audit_delete_rule_data(m_auditFileDescriptor, rule, AUDIT_FILTER_EXIT, AUDIT_ALWAYS) <= 0)
		{
			throw Exception("Failed to remove directory!!");
		}
	}
	catch (Exception& e)
	{
		delete rule;
		throw;
	}

	delete rule;
	return true;	
}