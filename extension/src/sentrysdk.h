//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef SENTRYSDK_CLASS_H
#define SENTRYSDK_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>
#include "thirdparty/include/sentry.h"

using namespace godot;

class SentrySdk : public Object
{
    GDCLASS(SentrySdk, Object);
    static sentry_options_t *options;

protected:
    static void _bind_methods();

public:
    SentrySdk();
    ~SentrySdk();

    static void setDsn(const String &dsn);
    static void setDebug(const int debug);
    static void setRelease(const String &release);
    static void setEnvironment(const String &environment);
    static void setSampleRate(const double sampleRate);
    static void setMaxBreadcrumbs(const int64_t maxbreadcrumbs);
    static void setAutoSessionTracking(const int autoSessionTracking);

    static void init();
    static void captureEvent(const String &message);
    static void captureError(const String &message);
    static void addBreadcrumb(const String &type, const String &message);
    // void crash();
};

#endif // SENTRYSDK_CLASS_H