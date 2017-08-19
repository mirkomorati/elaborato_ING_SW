//
// Created by Noè Murr on 19/08/2017.
//

#ifndef ELABORATO_ING_SW_LOG_HPP
#define ELABORATO_ING_SW_LOG_HPP

#include <map>
#include <string>

using namespace std;
namespace mm {

    class Logger {

        // maximum number of logger
        static int logger_max_index;

        // the index of this logger
        int index;

    public:


    };

    // singleton
    class LoggerFactory {
    public:
        static LoggerFactory &get_instance();

        LoggerFactory(const LoggerFactory &old) = delete;

        const LoggerFactory &operator=(const LoggerFactory &old) = delete;

        Logger &get_logger(string name);

    private:
        LoggerFactory() = default;

        map<string, Logger> loggers;
    };
}

#endif //ELABORATO_ING_SW_LOG_HPP
