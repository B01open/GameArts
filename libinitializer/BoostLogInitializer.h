
#pragma once
#include "Common.h"
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/named_scope.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/shared_ptr.hpp>

namespace dev
{
namespace initializer
{
class LogInitializer
{
public:
    class Sink : public boost::log::sinks::text_file_backend
    {
    public:
        void consume(const boost::log::record_view& rec, const std::string& str)
        {
            boost::log::sinks::text_file_backend::consume(rec, str);
            auto severity =
                rec.attribute_values()[boost::log::aux::default_attribute_names::severity()]
                    .extract<boost::log::trivial::severity_level>();
            // bug fix: determine m_ptr before get the log level
            //          serverity.get() will call  BOOST_ASSERT(m_ptr)
            if (severity.get_ptr() && severity.get() == boost::log::trivial::severity_level::fatal)
            {
                // abort if encounter fatal, will generate coredump
                // must make sure only use LOG(FATAL) when encounter the most serious problem
                // forbid use LOG(FATAL) in the function that should exit normally
                std::abort();
            }
        }
    };
    typedef std::shared_ptr<LogInitializer> Ptr;
    typedef boost::log::sinks::asynchronous_sink<Sink> sink_t;
    virtual ~LogInitializer() { stopLogging(); }
    LogInitializer() {}
    void initLog(boost::property_tree::ptree const& _pt,
        std::string const& channel = dev::FileLogger, std::string const& logType = "log");

    void stopLogging();

    unsigned getLogLevel(std::string const& levelStr);
    static void inline logRotateByTime(){};
    static int m_currentHour;
    static int m_index;

private:
    void stopLogging(boost::shared_ptr<sink_t> sink);
    std::vector<boost::shared_ptr<sink_t>> m_sinks;
};
}  // namespace initializer
}  // namespace dev
