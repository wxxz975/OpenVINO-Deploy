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
        static void log()
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

#define log(fmt, ...)   Logger::instance()->log()
#define err(fmt, ...)   Logger::instance()->err()

}



