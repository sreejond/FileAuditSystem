#include "Exception.h"

Exception::Exception(const char* inMsg)
: m_msg(inMsg)
{}

Exception::Exception(const std::string& inMsg)
: m_msg(inMsg)
{}

const char* Exception::what() const throw()
{
   return m_msg.c_str();
}