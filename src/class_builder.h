#pragma once

#include "builder.h"
#include "device_info.h"
#include "peripheral.h"

#include <cxxopts.hpp>

#include <memory>
#include <sstream>
#include <vector>

struct ClassBuilder
{
    ClassBuilder( const cxxopts::ParseResult& results_,
        const DeviceInfo& deviceInfo_,
        const std::vector< Peripheral >& peripherals_ );
    void setupBuilders();
    void build();
    auto getStream() const -> const std::stringstream&;

private:
    const cxxopts::ParseResult& results;
    const DeviceInfo& deviceInfo;
    const std::vector< Peripheral >& peripherals;
    std::vector< std::unique_ptr< IBuilder > > builders;
    std::stringstream m_output_stream;
};
