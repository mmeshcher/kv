#include "logs.hpp"
#include "Globals.hpp"

void init()
{
    boost::log::register_simple_formatter_factory<
            boost::log::trivial::severity_level,
            char
    >("Severity");
    static const std::string format =
    "[%TimeStamp%][%ThreadID%][%Severity%]: %Message%";

    auto sinkFile = boost::log::add_file_log(
            boost::log::keywords::file_name = "logs/log_%N.log",
            boost::log::keywords::rotation_size = 128 * 1024 * 1024,
            boost::log::keywords::auto_flush = true,
            boost::log::keywords::format = format
    );
    sinkFile->set_filter(
            boost::log::trivial::severity >= boost::log::trivial::trace
    );

    static const boost::unordered_map<std::string,
    boost::log::trivial::severity_level> CONSOLE_FILTER = {
            {"debug", boost::log::trivial::info},
            {"info", boost::log::trivial::info},
            {"warning", boost::log::trivial::warning},
            {"error", boost::log::trivial::error},
    };

    auto sinkConsole = boost::log::add_console_log(
            std::cout,
            boost::log::keywords::format = format
    );
    sinkConsole->set_filter(
            boost::log::trivial::severity >=
            CONSOLE_FILTER.at(Globals::logLevel)
    );

    boost::log::add_common_attributes();
     BOOST_LOG_TRIVIAL(debug) << "Log setup complete";
    BOOST_LOG_TRIVIAL(info) << "Input: " << Globals::input
                            << "\nOutput: " << Globals::output
                            << "\nThreads: " << Globals::threadAmount
                            << "\nLogLevel: " << Globals::logLevel;
                            
}