#pragma once

#include <format>
#include <string>

#include "types.h"

namespace version {

constexpr i8 PROJECT_VERSION_MAJOR{ 0 };
constexpr i8 PROJECT_VERSION_MINOR{ 1 };
constexpr i8 PROJECT_VERSION_PATCH{ 0 };

struct Version
{
    i8 major = -1;
    i8 minor = -1;
    i8 patch = -1;
};

static constexpr inline Version PROJECT_VERSION{
    PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH };

#ifdef NDEBUG
constexpr bool IS_DEBUG = false;
#else
constexpr bool IS_DEBUG = true;
#endif

static constexpr inline const char* BUILD_VERSION = "<COMMIT_SHA>";
static constexpr inline const char* BUILD_TYPE = IS_DEBUG ? "DEBUG" : "RELEASE";

auto getVersionInfo() -> std::string
{
    return std::format( "{}.{}.{}", PROJECT_VERSION.major, PROJECT_VERSION.minor, PROJECT_VERSION.patch );
}

auto getBuildInfo() -> std::string
{
    std::string build_type{ BUILD_TYPE };
    std::string build_version{ BUILD_VERSION };

    if( build_version.compare( "<COMMIT_SHA>" ) == 0 || build_version.empty() ) {
        return build_type;
    }

    return std::format( "{}-{}", build_version, build_type );
}

} // namespace version
