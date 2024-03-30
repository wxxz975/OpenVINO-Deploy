#pragma once

#include <iostream>
#include <cstdarg>

#include "Singleton.hpp"


namespace Common
{
    class Logger: public SingletonHolder<Logger>
    {
    public:
        Logger() = default;
        ~Logger() = default;

    public:
        static void log(const std::string& message, const std::string& file, int line)
        {

        }

        static void err()
        {

        }

    private:
        static void printMessage()
        {
            
        }

    };

}



