//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#include "sentrysdk.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "thirdparty/include/sentry.h"

using namespace godot;

static void godot_logger(sentry_level_t level, const char *message, va_list args, void *_data)
{
    char buffer[256];
    snprintf(buffer, 256, "Sentry: ");
    vsnprintf(buffer+8, 256-8, message, args);

    switch (level)
    {
    case SENTRY_LEVEL_DEBUG:
        UtilityFunctions::print(buffer);
        break;
    case SENTRY_LEVEL_INFO:
        UtilityFunctions::print(buffer);
        break;
    case  SENTRY_LEVEL_WARNING:
        UtilityFunctions::push_warning(buffer);
        break;
    case SENTRY_LEVEL_ERROR:
        UtilityFunctions::push_error(buffer);
        break;
    default:
        break;
    }
}

sentry_options_t *SentrySdk::options = sentry_options_new();

SentrySdk::SentrySdk()
{}

SentrySdk::~SentrySdk()
{}

void SentrySdk::setDsn(const String &dsn)
{
    sentry_options_set_dsn(options, dsn.utf8().get_data());
}

void SentrySdk::setDebug(const int debug)
{
    sentry_options_set_debug(options, debug);
}

void SentrySdk::setRelease(const String &release)
{
    sentry_options_set_release(options, release.utf8().get_data());
}

void SentrySdk::setEnvironment(const String &environment)
{
    sentry_options_set_environment(options, environment.utf8().get_data());
}

void SentrySdk::setSampleRate(const double sampleRate)
{
    sentry_options_set_sample_rate(options, sampleRate);
}

void SentrySdk::setMaxBreadcrumbs(const int64_t maxBreadcrumbs)
{
    sentry_options_set_max_breadcrumbs(options, (size_t)maxBreadcrumbs);
}

void SentrySdk::setAutoSessionTracking(const int autoSessionTracking)
{
    sentry_options_set_auto_session_tracking(options, autoSessionTracking);
}

void SentrySdk::init()
{
    // TODO: This should not be necessary
    sentry_options_set_handler_path(options, "/Users/bitfox/Workspace/GodotSentry/extension/src/thirdparty/bin/crashpad_handler");    
    sentry_options_set_logger(options, godot_logger, nullptr);

    sentry_init(options);
}

void SentrySdk::captureEvent(const String &message)
{
    sentry_value_t event = sentry_value_new_message_event(SENTRY_LEVEL_INFO, "Sentry", message.utf8().get_data());
    sentry_capture_event(event);
}

void SentrySdk::captureError(const String &message)
{
    sentry_value_t event = sentry_value_new_message_event(SENTRY_LEVEL_ERROR, "Sentry", message.utf8().get_data());
    sentry_capture_event(event);
}

void SentrySdk::addBreadcrumb(const String &type, const String &message)
{
    sentry_value_t crumb = sentry_value_new_breadcrumb(type.utf8().get_data(), message.utf8().get_data());
    sentry_add_breadcrumb(crumb);
}

// void SentrySdk::crash()
// {
//     char *ptr = 0;
//     *ptr += 1;
// }

void SentrySdk::_bind_methods()
{
    ClassDB::bind_static_method("SentrySdk", D_METHOD("setDsn", "dsn"), &SentrySdk::setDsn);
    ClassDB::bind_static_method("SentrySdk", D_METHOD("setDebug", "debug"), &SentrySdk::setDebug);
    ClassDB::bind_static_method("SentrySdk", D_METHOD("setRelease", "release"), &SentrySdk::setRelease);
    ClassDB::bind_static_method("SentrySdk", D_METHOD("setEnvironment", "environment"), &SentrySdk::setEnvironment);
    ClassDB::bind_static_method("SentrySdk", D_METHOD("setSampleRate", "sampleRate"), &SentrySdk::setSampleRate);
    ClassDB::bind_static_method("SentrySdk", D_METHOD("setMaxBreadcrumbs", "maxBreadcrumbs"), &SentrySdk::setMaxBreadcrumbs);
    ClassDB::bind_static_method("SentrySdk", D_METHOD("setAutoSessionTracking", "autoSessionTracking"), &SentrySdk::setAutoSessionTracking);

    ClassDB::bind_static_method("SentrySdk", D_METHOD("init"), &SentrySdk::init);
    ClassDB::bind_static_method("SentrySdk", D_METHOD("captureEvent", "message"), &SentrySdk::captureEvent);
    ClassDB::bind_static_method("SentrySdk", D_METHOD("captureError", "message"), &SentrySdk::captureError);
    ClassDB::bind_static_method("SentrySdk", D_METHOD("addBreadcrumb", "type", "message"), &SentrySdk::addBreadcrumb);
    // ClassDB::bind_method(D_METHOD("crash"), &SentrySdk::crash);
}