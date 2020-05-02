#include "Parser.h"
#include <iostream>

void Parser::parse(const std::string& inMsg, std::unordered_map<std::string, std::string>& outKeyValues)
{
	size_t startPos = 0;
	size_t endPos = 0;
	bool timestampParsed = false;
	while (startPos < inMsg.size() && endPos != std::string::npos)
	{
		endPos = inMsg.find(' ', startPos);
		std::string keyValue;
		if (endPos == std::string::npos)
			keyValue = inMsg.substr(startPos);
		else 
			keyValue = inMsg.substr(startPos, endPos - startPos);
		startPos = endPos + 1;
		if(!timestampParsed)
		{
			parseTimeStamp(keyValue, outKeyValues);
			timestampParsed = true;
		}
		size_t equalCharPos = keyValue.find('=');
		std::string key = keyValue.substr(0, equalCharPos);
		std::string value = keyValue.substr(equalCharPos + 1);
		if (value[0] == '"')
			value = value.substr(1, value.size() - 2);
		outKeyValues[key] = value;
	}
}


void Parser::parseTimeStamp(const std::string& timestampMsg, std::unordered_map<std::string, std::string>& outKeyValues)
{
	size_t startPos = timestampMsg.find('(');
	size_t endPos = timestampMsg.find(':');
	std::string timestamp = timestampMsg.substr(startPos + 1, endPos - startPos - 1);
	outKeyValues["timestamp"] = timestamp;
}