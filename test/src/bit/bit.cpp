#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/bit/bit_ceil.hpp"
#include "sfl/detail/bit/bit_log2.hpp"
#include "sfl/detail/bit/bit_width.hpp"
#include "sfl/detail/bit/countl_zero.hpp"
#include "sfl/detail/bit/has_single_bit.hpp"

#include <cstdint>

static_assert(sfl::dtl::bit_ceil(static_cast<std::uint64_t>(0)) == 1, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint64_t>(1)) == 1, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint64_t>(2)) == 2, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint64_t>(3)) == 4, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint64_t>(4)) == 4, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint64_t>(5)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint64_t>(6)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint64_t>(7)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint64_t>(8)) == 8, "");

static_assert(sfl::dtl::bit_ceil(static_cast<std::uint32_t>(0)) == 1, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint32_t>(1)) == 1, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint32_t>(2)) == 2, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint32_t>(3)) == 4, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint32_t>(4)) == 4, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint32_t>(5)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint32_t>(6)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint32_t>(7)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint32_t>(8)) == 8, "");

static_assert(sfl::dtl::bit_ceil(static_cast<std::uint16_t>(0)) == 1, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint16_t>(1)) == 1, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint16_t>(2)) == 2, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint16_t>(3)) == 4, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint16_t>(4)) == 4, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint16_t>(5)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint16_t>(6)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint16_t>(7)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint16_t>(8)) == 8, "");

static_assert(sfl::dtl::bit_ceil(static_cast<std::uint8_t>(0)) == 1, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint8_t>(1)) == 1, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint8_t>(2)) == 2, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint8_t>(3)) == 4, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint8_t>(4)) == 4, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint8_t>(5)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint8_t>(6)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint8_t>(7)) == 8, "");
static_assert(sfl::dtl::bit_ceil(static_cast<std::uint8_t>(8)) == 8, "");

static_assert(sfl::dtl::bit_log2(1u) == 0, "");
static_assert(sfl::dtl::bit_log2(2u) == 1, "");
static_assert(sfl::dtl::bit_log2(4u) == 2, "");
static_assert(sfl::dtl::bit_log2(8u) == 3, "");
static_assert(sfl::dtl::bit_log2(16u) == 4, "");

static_assert(sfl::dtl::bit_width(0u) == 0, "");
static_assert(sfl::dtl::bit_width(1u) == 1, "");
static_assert(sfl::dtl::bit_width(2u) == 2, "");
static_assert(sfl::dtl::bit_width(3u) == 2, "");
static_assert(sfl::dtl::bit_width(4u) == 3, "");
static_assert(sfl::dtl::bit_width(5u) == 3, "");
static_assert(sfl::dtl::bit_width(6u) == 3, "");
static_assert(sfl::dtl::bit_width(7u) == 3, "");
static_assert(sfl::dtl::bit_width(8u) == 4, "");

static_assert(sfl::dtl::countl_zero(static_cast<std::uint64_t>(0)) == 64 - 0, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint64_t>(1)) == 64 - 1, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint64_t>(2)) == 64 - 2, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint64_t>(3)) == 64 - 2, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint64_t>(4)) == 64 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint64_t>(5)) == 64 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint64_t>(6)) == 64 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint64_t>(7)) == 64 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint64_t>(8)) == 64 - 4, "");

static_assert(sfl::dtl::countl_zero(static_cast<std::uint32_t>(0)) == 32 - 0, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint32_t>(1)) == 32 - 1, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint32_t>(2)) == 32 - 2, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint32_t>(3)) == 32 - 2, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint32_t>(4)) == 32 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint32_t>(5)) == 32 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint32_t>(6)) == 32 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint32_t>(7)) == 32 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint32_t>(8)) == 32 - 4, "");

static_assert(sfl::dtl::countl_zero(static_cast<std::uint16_t>(0)) == 16 - 0, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint16_t>(1)) == 16 - 1, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint16_t>(2)) == 16 - 2, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint16_t>(3)) == 16 - 2, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint16_t>(4)) == 16 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint16_t>(5)) == 16 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint16_t>(6)) == 16 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint16_t>(7)) == 16 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint16_t>(8)) == 16 - 4, "");

static_assert(sfl::dtl::countl_zero(static_cast<std::uint8_t>(0)) == 8 - 0, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint8_t>(1)) == 8 - 1, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint8_t>(2)) == 8 - 2, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint8_t>(3)) == 8 - 2, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint8_t>(4)) == 8 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint8_t>(5)) == 8 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint8_t>(6)) == 8 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint8_t>(7)) == 8 - 3, "");
static_assert(sfl::dtl::countl_zero(static_cast<std::uint8_t>(8)) == 8 - 4, "");

static_assert(sfl::dtl::has_single_bit(0u) == false, "");
static_assert(sfl::dtl::has_single_bit(1u) == true, "");
static_assert(sfl::dtl::has_single_bit(2u) == true, "");
static_assert(sfl::dtl::has_single_bit(3u) == false, "");
static_assert(sfl::dtl::has_single_bit(4u) == true, "");
static_assert(sfl::dtl::has_single_bit(5u) == false, "");
static_assert(sfl::dtl::has_single_bit(6u) == false, "");
static_assert(sfl::dtl::has_single_bit(7u) == false, "");
static_assert(sfl::dtl::has_single_bit(8u) == true, "");

int main()
{}
