/**
 
 *
 *
 * @file StorageException.h
 * @author: mingzhenliu
 * @date 2018-09-13
 */
#pragma once
#include <libdevcore/Exceptions.h>
#include <exception>
#include <string>

namespace dev
{
namespace storage
{
class StorageException : public dev::Exception
{
public:
    StorageException(int errorCode, const std::string& what)
      : dev::Exception(what), m_errorCode(errorCode)
    {}

    virtual int errorCode() { return m_errorCode; }

private:
    int m_errorCode = 0;
};

}  // namespace storage

}  // namespace dev
