#ifndef LOGGER_H
#define LOGGER_H


#define QUILL_DISABLE_NON_PREFIXED_MACROS

#include "quill/LogMacros.h"
#include "quill/Logger.h"
#include "quill/Backend.h"
#include "quill/sinks/ConsoleSink.h"
#include "quill/Frontend.h"
#include "quill/std/Array.h"
#include "quill/std/Chrono.h"
#include "quill/std/Deque.h"
#include "quill/std/FilesystemPath.h"
#include "quill/std/ForwardList.h"
#include "quill/std/List.h"
#include "quill/std/Map.h"
#include "quill/std/Optional.h"
#include "quill/std/Pair.h"
#include "quill/std/Set.h"
#include "quill/std/Tuple.h"
#include "quill/std/UnorderedMap.h"
#include "quill/std/UnorderedSet.h"
#include "quill/std/Vector.h"
#include "quill/std/WideString.h"

#include "quill/Utility.h"

inline quill::Logger* global_logger_a;

// Define custom log macros using global_logger_a.
#define LOG_TRACE_L3(fmt, ...)  QUILL_LOG_TRACE_L3(global_logger_a, fmt, ##__VA_ARGS__)
#define LOG_TRACE_L2(fmt, ...)  QUILL_LOG_TRACE_L2(global_logger_a, fmt, ##__VA_ARGS__)
#define LOG_TRACE_L1(fmt, ...)  QUILL_LOG_TRACE_L1(global_logger_a, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)     QUILL_LOG_DEBUG(global_logger_a, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)      QUILL_LOG_INFO(global_logger_a, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)   QUILL_LOG_WARNING(global_logger_a, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)     QUILL_LOG_ERROR(global_logger_a, fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)  QUILL_LOG_CRITICAL(global_logger_a, fmt, ##__VA_ARGS__)


inline void setupLogger( const std::string &loggerName = "root" , quill::LogLevel logLevel = quill::LogLevel::Info )
{
    (void)loggerName;

    // Start the backend Log thread
    quill::BackendOptions backend_options;
    quill::Backend::start(backend_options);

    // Frontend
    quill::ConsoleColours custom_console_colours;
    custom_console_colours.set_default_colours();
    custom_console_colours.set_colour(quill::LogLevel::Info, quill::ConsoleColours::cyan); // overwrite the colour for INFO
    custom_console_colours.set_colour(quill::LogLevel::TraceL3, quill::ConsoleColours::magenta); // overwrite the colour for INFO
    custom_console_colours.set_colour(quill::LogLevel::Error, quill::ConsoleColours::red); // overwrite the colour for INFO
    custom_console_colours.set_colour(quill::LogLevel::Warning, quill::ConsoleColours::yellow); // overwrite the colour for INFO
    custom_console_colours.set_colour(quill::LogLevel::Debug, quill::ConsoleColours::red ); // overwrite the colour for INFO

    // Create the sink
    auto console_sink =
        quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1", custom_console_colours);

    // formatter : https://quillcpp.readthedocs.io/en/latest/formatters.html
    global_logger_a = quill::Frontend::create_or_get_logger( "root" , std::move(console_sink) , quill::PatternFormatterOptions { "%(time) [%(thread_id)] %(short_source_location:<28) %(log_level_short_code:<9) "
                                                                                                                            "%(caller_function) : %(message)",
                                                                                                                            "%H:%M:%S.%Qms", quill::Timezone::GmtTime });

    // LOG Level
    global_logger_a->set_log_level(logLevel);
}


#endif // LOGGER_H
