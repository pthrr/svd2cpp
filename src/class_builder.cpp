#include "class_builder.h"

ClassBuilder::ClassBuilder( const cxxopts::ParseResult& results_,
    const DeviceInfo& deviceInfo_,
    const std::vector< Peripheral >& peripherals_ )
    : results( results_ )
    , deviceInfo( deviceInfo_ )
    , peripherals( peripherals_ )
    , builders{}
{
}

void ClassBuilder::setupBuilders()
{
    builders.push_back( std::make_unique< ZeroPointerBuilder >() );
    builders.push_back( std::make_unique< FieldDefineBuilder >() );

    for( auto& peripheral : peripherals ) {
        builders.push_back( std::make_unique< PeripheralBuilder >( peripheral ) );
    }

    builders.push_back( std::make_unique< FunctionsBuilder >() );
}

void ClassBuilder::build()
{
    for( auto& builder : builders ) {
        builder->build( m_output_stream );
    }
}

auto ClassBuilder::getStream() const -> const std::stringstream&
{
    return m_output_stream;
}
