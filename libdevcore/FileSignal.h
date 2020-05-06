
#pragma once
#include <boost/filesystem.hpp>
#include <cstdio>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace dev
{
class FileSignal
{
public:
    static void callIfFileExist(const std::string& _file, std::function<void(void)> _f)
    {
        try
        {
            if (boost::filesystem::exists(_file))
            {
                boost::filesystem::remove(_file);  // Just call once, even _f() exception happens
                _f();
                if (boost::filesystem::exists(_file))
                {
                    // Delete file signal generated during f() is executing
                    boost::filesystem::remove(_file);
                }
            }
        }
        catch (std::exception& _e)
        {
            if (boost::filesystem::exists(_file))
            {
                // Delete file signal generated during f() is executing
                boost::filesystem::remove(_file);
            }
            std::cerr << "GAME ART file signal error: "
                      << "file: " << _file << " what: " << _e.what() << std::endl;
        }
    }
};
}  // namespace dev
