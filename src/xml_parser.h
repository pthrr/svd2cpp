#pragma once

#include "device_info.h"
#include "peripheral.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <tinyxml2.h>

struct XmlParser
{
    XmlParser( const std::string& inputFile );
    std::optional< std::string > isError() const;
    void parseXml();
    inline const DeviceInfo& getDeviceInfo() const
    {
        return deviceInfo;
    }
    inline const std::vector< Peripheral >& getPeripherals() const
    {
        return peripherals;
    }

private:
    // tinyxml2::XMLElement* getDevice
    void setDeviceInfoAttrib( tinyxml2::XMLElement* deviceRoot, const char* name, std::string& field ) const;
    void setDeviceInfoAttrib( tinyxml2::XMLElement* deviceRoot, const char* name, unsigned int& field ) const;
    void setDeviceInfoAttrib( tinyxml2::XMLElement* deviceRoot, const char* name, EAccess& field ) const;

    Peripheral parsePeripheral( tinyxml2::XMLElement* peripheralRoot ) const;
    AddressBlock parseAddressBlock( tinyxml2::XMLElement* addressBlockRoot ) const;
    Register parseRegister( tinyxml2::XMLElement* registerRoot ) const;
    Field parseField( tinyxml2::XMLElement* fieldRoot ) const;

private:
    tinyxml2::XMLDocument xmlDocument;
    static const inline std::string noValue = "Not found";
    DeviceInfo deviceInfo;
    std::vector< Peripheral > peripherals;
};
