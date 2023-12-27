#pragma once

#include "peripheral.h"
#include "types.h"

#include <bitset>
#include <iostream>
#include <sstream>

struct IBuilder
{
    virtual void build( std::stringstream& ) const = 0;
    virtual ~IBuilder() = default;
};

struct ZeroPointerBuilder : public IBuilder
{
    void build( std::stringstream& sstream ) const final;
};

struct FieldDefineBuilder : public IBuilder
{
    void build( std::stringstream& sstream ) const final;
};

struct PeripheralBuilder : public IBuilder
{
    explicit PeripheralBuilder( const Peripheral& PERIPHERAL )
        : m_PERIPHERAL( PERIPHERAL )
    {
    }
    void build( std::stringstream& sstream ) const final;

private:
    const Peripheral& m_PERIPHERAL;
};

struct RegisterBuilder : public IBuilder
{
    RegisterBuilder( const Register& REGISTER, const unsigned int BASE_ADDRESS )
        : m_REGISTER{ REGISTER }
        , m_BASE_ADDRESS{ BASE_ADDRESS }
    {
    }
    void build( std::stringstream& sstream ) const final;
    [[nodiscard]] auto getRegisterAddress() const -> unsigned int;

private:
    const Register& m_REGISTER;
    const unsigned int m_BASE_ADDRESS;
};

struct FieldBuilder : public IBuilder
{
    FieldBuilder( const Field& FIELD, const unsigned int REGISTER_ADDRESS )
        : m_FIELD( FIELD )
        , m_REGISTER_ADDRESS( REGISTER_ADDRESS )
    {
    }
    auto build( std::stringstream& sstream ) const -> void final;
    [[nodiscard]] auto getAddress() const -> unsigned int;

private:
    const Field& m_FIELD;
    const unsigned int m_REGISTER_ADDRESS;
};

struct FunctionsBuilder : public IBuilder
{
    auto build( std::stringstream& sstream ) const -> void final;
};
