#include "logging.h"

static auto extractFileName( const std::string& filePath ) -> std::string
{
    size_t pos{ filePath.find_last_of( "/\\" ) };

    if( pos != std::string::npos ) {
        return filePath.substr( pos + 1 );
    }

    return filePath;
}

namespace logging {

auto getLogger( const std::string& name ) -> spdlog::logger&
{
    auto logger{ spdlog::get( name ) };

    if( !logger ) {
        logger = spdlog::stdout_color_mt( name );
    }

    return *logger;
}

auto getFileLogger( const std::string& filePath ) -> spdlog::logger&
{
    auto fileName{ extractFileName( filePath ) };
    return getLogger( fileName );
}

} // namespace logging
