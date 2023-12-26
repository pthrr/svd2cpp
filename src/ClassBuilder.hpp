#pragma once

#include "DeviceInfo.hpp"
#include "IBuilder.hpp"
#include "Peripheral.hpp"

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
    const std::stringstream& getStream() const;

private:
    const cxxopts::ParseResult& results;
    const DeviceInfo& deviceInfo;
    const std::vector< Peripheral >& peripherals;
    std::vector< std::unique_ptr< IBuilder > > builders;
    std::stringstream outputStream;
};
