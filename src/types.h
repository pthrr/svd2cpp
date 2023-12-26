#pragma once

#include <cstdint>

using u64 = uint_fast64_t;
using u32 = uint_fast32_t;
using u16 = uint_fast16_t;
using u8 = uint_fast8_t;
using i64 = int_fast64_t;
using i32 = int_fast32_t;
using i16 = int_fast16_t;
using i8 = int_fast8_t;
using f32 = float;
using f64 = double;

constexpr u64 KiB = 1024;
constexpr u64 MiB = KiB * KiB;
constexpr u64 GiB = KiB * KiB * KiB;
constexpr u64 TiB = KiB * KiB * KiB * KiB;
constexpr u64 PiB = KiB * KiB * KiB * KiB * KiB;
constexpr u64 EiB = KiB * KiB * KiB * KiB * KiB * KiB;

namespace types {

struct Version
{
    int major = -1;
    int minor = -1;
    int patch = -1;
};

} // namespace types
