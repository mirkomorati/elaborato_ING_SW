//
// Created by Noè Murr on 19/08/2017.
//

#ifndef ELABORATO_ING_SW_LOG_HPP
#define ELABORATO_ING_SW_LOG_HPP

#include <map>
#include <string>
#include <plog/Log.h>
#include <plog/Formatters/MessageOnlyFormatter.h>
#include <plog/Converters/NativeEOLConverter.h>
#include "Configuration.hpp"
#include <type_traits>

using namespace std;
namespace mm {
    class Logger {
        friend class LoggerFactory;

    public:
        template<typename T>
        Logger &operator<<(const T &data) {

            if (msg.str().empty()) {
                auto now = time(0);
                auto tm = *std::localtime(&now);
                msg << "[" << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << "] ";
            }
            msg << data;

            return *this;
        }

        Logger &operator<<(ostream &(*data)(ostream &)) {
            LOG(severity) << msg.str();
            return *this;
        }

    private:
        // maximum number of logger
        static int logger_max_index;

        // the index of this logger
        int index;

        // the logger severity
        plog::Severity severity;

        // the logger filename
        string filename;

        // file appender
        plog::RollingFileAppender<plog::MessageOnlyFormatter, plog::NativeEOLConverter<>> *fileAppender;

        // the message
        stringstream msg;

        Logger(string filename, plog::Severity max_severity = plog::Severity::none);
    };

    // singleton
    class LoggerFactory {
    public:
        static LoggerFactory &get_instance() noexcept(false);

        static void init(const Configuration &cfg);

        static bool init_called;
        static string log_file_prefix;

        LoggerFactory(const LoggerFactory &old) = delete;

        const LoggerFactory &operator=(const LoggerFactory &old) = delete;

        Logger &get_logger(string name, plog::Severity severity = plog::Severity::none, string filename = string());

    private:
        LoggerFactory() = default;

        map<string, Logger> loggers;
    };
}

#endif //ELABORATO_ING_SW_LOG_HPP
