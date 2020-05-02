#ifndef PARSER_H
#define PARSER_H

#include <unordered_map>

/**
 * \class Parser
 *
 * \brief
 *
 * This class is responsible to parse SYSTEM_CALL event message from libaudit
 */
class Parser
{
public:
	/**
      * \brief parse SYSTEM_CALL event message into key value pairs
      * \param outKeyValue store key value pairs
      */
	static void parse(const std::string& inMsg, std::unordered_map<std::string, std::string>& outKeyValue);

	/**
      * \brief deleted copy constructor
      */
	Parser(const Parser&) = delete;
	/**
      * \brief deleted copy assignment operator
      */
    void operator=(Parser const&) = delete;
    
private:
	/**
      * \brief default constructor
      */
	Parser() = default;
	/**
      * \brief parse timestamp
      * \param timestampMsg timestamp message
      * \param outKeyValues store key value pair
      */
	static void parseTimeStamp(const std::string& timestampMsg, std::unordered_map<std::string, std::string>& outKeyValues);
};

#endif /* PARSER_H */