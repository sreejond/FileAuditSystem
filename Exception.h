#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

/**
 * \class Exception
 *
 * \brief
 *
 * This class is responsible to create the exception message
 */
class Exception: public std::exception
{
public:
     /**
      * \brief constructor
      * \param inMsg C string type message
      */
    explicit Exception(const char* inMsg);

    /**
      * \brief constructor
      * \param inMsg C++ std::string type message
      */
    explicit Exception(const std::string& inMsg);

    /**
      * \brief virtual destructor
      */
    virtual ~Exception() throw() {}
    
    /**
      * \brief returns a pointer to the constant C string message
      */
    virtual const char* what() const throw() override;

protected:
    // contain error message
    std::string m_msg;
};

#endif /* EXCEPTION_H */