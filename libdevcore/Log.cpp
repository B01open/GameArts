
#include "Log.h"
#include <boost/log/core.hpp>

namespace dev
{
std::string const FileLogger = "FileLogger";
boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level, std::string>
    FileLoggerHandler(boost::log::keywords::channel = FileLogger);
}  // namespace dev