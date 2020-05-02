#include "EventHandler.h"
#include "MonitorDirectory.h"
#include "Logger.h"
#include "Exception.h"
#include "FileAuditSystemUtil.h"
#include "Parser.h"

#include <libaudit.h>
#include <ctime>
#include <iostream>

void EventHandler::processEvent(struct ev_loop *loop, 
							struct ev_io *io, 
							int revents)
{
	char buffer[MAX_AUDIT_MESSAGE_LENGTH];
	time_t timetoday;
	time(&timetoday);
	struct audit_reply reply;

	if (audit_get_reply(MonitorDirectory::getInstance().getFileDescriptor(), 
						&reply, 
						GET_REPLY_NONBLOCKING, 
						0) < 0)
	{
		throw Exception("Event handler failed to receive valid reply!!");
	}

	if (reply.type == AUDIT_SYSCALL)
	{
		std::unordered_map<std::string, std::string> keyValues;
		std::string replyMsg(reply.message);
		Parser::parse(replyMsg, keyValues);
		std::string logMsg = createMsg(keyValues);
		Logger::getInstance().write(logMsg);
	}
}

std::string EventHandler::createMsg(const std::unordered_map<std::string, std::string>& inKeyValues)
{
	std::string logMsg;
	for (const auto& monitorPoint : monitorPoints)
	{
		auto iter = inKeyValues.find(monitorPoint);
		if (iter != inKeyValues.end())
		{
			logMsg.append(iter->second);
			logMsg.append(" ");
		}
	}

	return logMsg;
}