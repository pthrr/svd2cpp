#pragma once

#include <sstream>

struct IBuilder
{
    virtual void build( std::stringstream& ) const = 0;
    virtual ~IBuilder() = default;
};
