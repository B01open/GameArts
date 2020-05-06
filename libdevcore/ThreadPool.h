

#pragma once
#include "Log.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <iosfwd>
#include <memory>

namespace dev
{
class ThreadPool
{
public:
    typedef std::shared_ptr<ThreadPool> Ptr;

    explicit ThreadPool(const std::string& threadName, size_t size) : m_work(_ioService)
    {
        _threadName = threadName;
        std::shared_ptr<std::vector<std::string>> fields =
            std::make_shared<std::vector<std::string>>();
        if (boost::log::core::get())
        {
            boost::split(*fields, _threadName, boost::is_any_of("-"), boost::token_compress_on);
        }

        for (size_t i = 0; i < size; ++i)
        {
            _workers.create_thread([this, fields] {
                if (fields->size() > 1)
                {
                    boost::log::core::get()->add_thread_attribute(
                        "GroupId", boost::log::attributes::constant<std::string>((*fields)[1]));
                }
                dev::pthread_setThreadName(_threadName);
                _ioService.run();
            });
        }
    }
    void stop()
    {
        _ioService.stop();
        if (!_workers.is_this_thread_in())
        {
            _workers.join_all();
        }
    }

    ~ThreadPool() { stop(); }

    // Add new work item to the pool.
    template <class F>
    void enqueue(F f)
    {
        _ioService.post(f);
    }

private:
    std::string _threadName;
    boost::thread_group _workers;
    boost::asio::io_service _ioService;
    // m_work ensures that io_service's run() function will not exit while work is underway
    boost::asio::io_service::work m_work;
};

}  // namespace dev
