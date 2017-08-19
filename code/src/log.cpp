//
// Created by Noè Murr on 19/08/2017.
//

#include "../hdr/log.hpp"

int mm::Logger::logger_max_index = 0;
bool mm::LoggerFactory::init_called = false;
string mm::LoggerFactory::log_file_prefix = "";

mm::Logger &mm::LoggerFactory::get_logger(string name, plog::Severity severity, string filename) {

    if (loggers.find(name) == loggers.end()) {
        if (filename.empty()) {
            time_t now = time(0);
            stringstream ss;
            ss << log_file_prefix << name << ctime(&now) << ".txt";
            loggers.insert(pair<string, Logger>(name, Logger(ss.str(), severity)));
        } else {
            stringstream ss;
            ss << log_file_prefix << filename;
            loggers.insert(pair<string, Logger>(name, Logger(ss.str(), severity)));
        }
    }
    return loggers.at(name);
}

mm::LoggerFactory &mm::LoggerFactory::get_instance() noexcept(false) {
    static LoggerFactory instance;
    if (not init_called) throw logic_error("mm::LoggerFactory::init must be called before getting an instance");
    return instance;
}

void mm::LoggerFactory::init(const mm::Configuration &cfg) {
    try {
        log_file_prefix = cfg.get<string>("log_prefix");
    } catch (key_not_found_error &e) {
        log_file_prefix = "log/";
    }
    init_called = true;
}

mm::Logger::Logger(string filename, plog::Severity max_severity) {
    index = logger_max_index++;
    this->filename = filename;

    fileAppender = new plog::RollingFileAppender<plog::MessageOnlyFormatter, plog::NativeEOLConverter<>>(
            filename.c_str());

    plog::init(max_severity, fileAppender);

    severity = max_severity;

    auto now = time(0);
    auto tm = *std::localtime(&now);
    stringstream ss;

    ss << "[" << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << "] Logger started" << std::endl;

    LOG(severity) << ss.str();
}
