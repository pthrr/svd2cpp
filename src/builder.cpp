#include "builder.h"

auto ZeroPointerBuilder::build( std::stringstream& sstream ) const -> void
{
    sstream << "template <unsigned int zero = 0>\n"
               "constexpr unsigned int *zeroVal = reinterpret_cast<unsigned int *>(zero);\n\n";
}

auto FieldDefineBuilder::build( std::stringstream& sstream ) const -> void
{
    sstream << "#define __FIELD(_FieldName, _bitOffset, _bitMask, _address)                          \\\n"
               "struct _FieldName                                                                    \\\n"
               "{                                                                                    \\\n"
               "    constexpr static inline unsigned int bitOffset() { return _bitOffset; }          \\\n"
               "    constexpr static inline unsigned int bitMask() { return _bitMask; }              \\\n"
               "    constexpr static inline unsigned int *address() { return zeroVal<> + _address; } \\\n"
               "};\n\n";
}

auto PeripheralBuilder::build( std::stringstream& sstream ) const -> void
{
    sstream << "namespace " << m_PERIPHERAL.name << "{\n";

    for( const auto& REGISTER : m_PERIPHERAL.registers ) {
        RegisterBuilder( REGISTER, m_PERIPHERAL.baseAddress ).build( sstream );
    }

    sstream << "}\n\n";
}

auto RegisterBuilder::build( std::stringstream& sstream ) const -> void
{
    sstream << "    "
            << "namespace " << m_REGISTER.name << "{\n";

    for( const auto& m_FIELD : m_REGISTER.fields ) {
        FieldBuilder( m_FIELD, getRegisterAddress() ).build( sstream );
    }

    sstream << "    "
            << "}\n";
}

auto RegisterBuilder::getRegisterAddress() const -> unsigned int
{
    return m_BASE_ADDRESS + m_REGISTER.addressOffset;
}

auto FieldBuilder::build( std::stringstream& sstream ) const -> void
{
    sstream << "        "
            << "__FIELD(" << m_FIELD.name << ", " << m_FIELD.bitOffset << ", " << m_FIELD.bitWidth << ", "
            << std::hex << "0x" << getAddress() << std::dec << ")\n";
}

auto FieldBuilder::getAddress() const -> unsigned int
{
    return m_REGISTER_ADDRESS;
}

auto FunctionsBuilder::build( std::stringstream& sstream ) const -> void
{
    sstream << "template<class FIELD>\n"
               "constexpr inline void set(){\n"
               "    *FIELD::address() |= 1 << FIELD::bitOffset();\n"
               "}\n"
               "\n"
               "template<class FIELD, unsigned int VAL>\n"
               "constexpr inline void set(){\n"
               "    static_assert(VAL & (FIELD::bitMask() >> FIELD::bitOffset()), \"Value is too big\");\n"
               "    *FIELD::address() = *FIELD::address() & ~FIELD::bitMask() | VAL << FIELD::bitOffset();\n"
               "}\n"
               "\n"
               "template<class FIELD>\n"
               "constexpr inline void reset(){\n"
               "    *FIELD::address() &= ~(1 << FIELD::bitOffset());\n"
               "}\n"
               "\n"
               "template<class FIELD>\n"
               "constexpr inline unsigned int read(){\n"
               "    return (*FIELD::address() & FIELD::bitMask()) >> FIELD::bitOffset();\n"
               "}"
               "\n\n";
}
