//
// Copyright (c) 2022 Slaven Falandys
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef SFL_DETAIL_HASH_TABLE_HPP_INCLUDED
#define SFL_DETAIL_HASH_TABLE_HPP_INCLUDED

#include <sfl/detail/bit/bit_ceil.hpp>
#include <sfl/detail/bit/bit_log2.hpp>
#include <sfl/detail/bit/has_single_bit.hpp>
#include <sfl/detail/math/ceil.hpp>
#include <sfl/detail/math/floor.hpp>
#include <sfl/detail/math/is_prime.hpp>
#include <sfl/detail/memory/construct_at.hpp>
#include <sfl/detail/memory/construct_at_a.hpp>
#include <sfl/detail/memory/destroy_at.hpp>
#include <sfl/detail/memory/destroy_at_a.hpp>
#include <sfl/detail/memory/destroy_n_a.hpp>
#include <sfl/detail/memory/to_address.hpp>
#include <sfl/detail/type_traits/conjunction.hpp>
#include <sfl/detail/type_traits/disjunction.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/is_input_iterator.hpp>
#include <sfl/detail/type_traits/is_nothrow_swappable.hpp>
#include <sfl/detail/utility/compressed_pair.hpp>
#include <sfl/detail/utility/floating_point_to_size_t.hpp>
#include <sfl/detail/utility/ignore_unused.hpp>
#include <sfl/detail/utility/optional_value.hpp>
#include <sfl/detail/utility/scope_guard.hpp>
#include <sfl/detail/allocator_traits.hpp>
#include <sfl/detail/cpp.hpp>

#include <algorithm>    // max, min
#include <cstddef>      // size_t, ptrdiff_t
#include <iterator>     // iterator_traits, xxxxx_iterator_tag
#include <limits>       // numeric_limits
#include <memory>       // pointer_traits
#include <tuple>        // forward_as_tuple
#include <type_traits>  // is_xxxxx
#include <utility>      // forward, move, pair

#ifdef SFL_TEST_HASH_TABLE
template <int>
void test_hash_table();
#endif

namespace sfl
{

namespace dtl
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// TAGS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

struct hash_table_equal_t {};

struct hash_table_unique_t {};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// NODES
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename VoidPointer>
struct hash_table_base_node
{
    using base_node_pointer = typename std::pointer_traits<VoidPointer>::template rebind<hash_table_base_node>;

    base_node_pointer next_;

    SFL_CONSTEXPR_20
    hash_table_base_node() noexcept
    {}

    SFL_CONSTEXPR_20
    hash_table_base_node(base_node_pointer next) noexcept
        : next_(next)
    {}
};

template <typename Value, typename VoidPointer>
struct hash_table_node : hash_table_base_node<VoidPointer>
{
    using typename hash_table_base_node<VoidPointer>::base_node_pointer;

    using node_pointer = typename std::pointer_traits<VoidPointer>::template rebind<hash_table_node>;

    std::size_t bucket_info_;

    static constexpr std::size_t mask = std::numeric_limits<std::size_t>::max() >> 1;

    sfl::dtl::optional_value<Value> value_;

    #if defined(_MSC_VER) && SFL_CPP_VERSION >= SFL_CPP_20 // Visual C++ needs this in C++20 constexpr
    SFL_CONSTEXPR_20
    ~hash_table_node()
    {}
    #endif

    // Use this if node is first in group.
    SFL_CONSTEXPR_20
    void set_bucket_index(std::size_t bucket_index, std::true_type) noexcept
    {
        bucket_info_ = bucket_index;
    }

    // Use this if node is not first in group.
    SFL_CONSTEXPR_20
    void set_bucket_index(std::size_t bucket_index, std::false_type) noexcept
    {
        bucket_info_ = bucket_index | ~mask;
    }

    SFL_CONSTEXPR_20
    std::size_t get_bucket_index() const noexcept
    {
        return bucket_info_ & mask;
    }

    SFL_CONSTEXPR_20
    bool is_first_in_group() const noexcept
    {
        return !(bucket_info_ & ~mask);
    }

    SFL_CONSTEXPR_20
    void set_first_in_group()
    {
        bucket_info_ = bucket_info_ & mask;
    }

    #if 0 // Not used, but leave it here just in case
    SFL_CONSTEXPR_20
    void reset_first_in_group()
    {
        bucket_info_ = bucket_info_ | ~mask;
    }
    #endif
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// BUCKETS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename BaseNodePointer>
struct hash_table_bucket
{
    BaseNodePointer next_;

    SFL_CONSTEXPR_20
    hash_table_bucket() noexcept
    {}

    SFL_CONSTEXPR_20
    hash_table_bucket(BaseNodePointer next) noexcept
        : next_(next)
    {}
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template < typename KeyHash, typename KeyEqual,
           bool AreBothFunctionsEmpty = std::is_empty<KeyHash>::value && std::is_empty<KeyEqual>::value >
class hash_table_functions
{
private:

    union
    {
        sfl::dtl::compressed_pair<KeyHash, KeyEqual> functions0_;
    };

    union
    {
        sfl::dtl::compressed_pair<KeyHash, KeyEqual> functions1_;
    };

    unsigned char status_;

public:

    SFL_CONSTEXPR_20
    hash_table_functions()
        : status_(0)
    {
        sfl::dtl::construct_at
        (
            std::addressof(functions0_),
            sfl::dtl::compressed_pair_default_init_t(),
            sfl::dtl::compressed_pair_default_init_t()
        );
    }

    SFL_CONSTEXPR_20
    hash_table_functions(const KeyHash& hash)
        : status_(0)
    {
        sfl::dtl::construct_at
        (
            std::addressof(functions0_),
            hash,
            sfl::dtl::compressed_pair_default_init_t()
        );
    }

    SFL_CONSTEXPR_20
    hash_table_functions(const KeyHash& hash, const KeyEqual& equal)
        : status_(0)
    {
        sfl::dtl::construct_at
        (
            std::addressof(functions0_),
            hash,
            equal
        );
    }

    SFL_CONSTEXPR_20
    ~hash_table_functions()
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        sfl::dtl::destroy_at(std::addressof(status_ == 0 ? functions0_ : functions1_));
    }

    SFL_CONSTEXPR_20
    KeyHash& ref_to_key_hash()
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        return status_ == 0 ? functions0_.first() : functions1_.first();
    }

    SFL_CONSTEXPR_20
    const KeyHash& ref_to_key_hash() const
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        return status_ == 0 ? functions0_.first() : functions1_.first();
    }

    SFL_CONSTEXPR_20
    KeyEqual& ref_to_key_equal()
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        return status_ == 0 ? functions0_.second() : functions1_.second();
    }

    SFL_CONSTEXPR_20
    const KeyEqual& ref_to_key_equal() const
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        return status_ == 0 ? functions0_.second() : functions1_.second();
    }

    SFL_CONSTEXPR_20
    void assign_copy(const hash_table_functions& other)
    {
        priv_assign_copy
        (
            other,
            typename sfl::dtl::conjunction
            <
                typename std::is_nothrow_copy_assignable<KeyHash>,
                typename std::is_nothrow_copy_assignable<KeyEqual>
            >()
        );
    }

    SFL_CONSTEXPR_20
    void assign_move(hash_table_functions& other)
    {
        priv_assign_move
        (
            other,
            typename sfl::dtl::conjunction
            <
                typename std::is_nothrow_move_assignable<KeyHash>,
                typename std::is_nothrow_move_assignable<KeyEqual>
            >()
        );
    }

    SFL_CONSTEXPR_20
    void swap(hash_table_functions& other)
    {
        priv_swap
        (
            other,
            typename sfl::dtl::conjunction
            <
                typename sfl::dtl::is_nothrow_swappable<KeyHash>,
                typename sfl::dtl::is_nothrow_swappable<KeyEqual>
            >()
        );
    }

private:

    SFL_CONSTEXPR_20
    void priv_assign_copy(const hash_table_functions& other, std::true_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        auto& this_functions = (status_ == 0) ? functions0_ : functions1_;

        auto& other_functions = (other.status_ == 0) ? other.functions0_ : other.functions1_;

        this_functions = other_functions;
    }

    SFL_CONSTEXPR_20
    void priv_assign_copy(const hash_table_functions& other, std::false_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        auto& this_old_functions = (status_ == 0) ? functions0_ : functions1_;

        auto& this_new_functions = (status_ == 0) ? functions1_ : functions0_;

        auto& other_functions = (other.status_ == 0) ? other.functions0_ : other.functions1_;

        // Construct a new pair of functions (may throw)
        sfl::dtl::construct_at(std::addressof(this_new_functions), other_functions);

        // Destroy the old pair of functions (noexcept)
        sfl::dtl::destroy_at(std::addressof(this_old_functions));

        // Change active functions (noexcept)
        status_ ^= 1;
    }

    SFL_CONSTEXPR_20
    void priv_assign_move(hash_table_functions& other, std::true_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        auto& this_functions = (status_ == 0) ? functions0_ : functions1_;

        auto& other_functions = (other.status_ == 0) ? other.functions0_ : other.functions1_;

        this_functions = std::move(other_functions);
    }

    SFL_CONSTEXPR_20
    void priv_assign_move(hash_table_functions& other, std::false_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        auto& this_old_functions = (status_ == 0) ? functions0_ : functions1_;

        auto& this_new_functions = (status_ == 0) ? functions1_ : functions0_;

        auto& other_functions = (other.status_ == 0) ? other.functions0_ : other.functions1_;

        // Construct a new pair of functions.
        // We intentionally avoid using std::move for the second argument.
        // Using std::move could cause issues if the operation throws an exception.
        // For instance, the first element of the (compressed) pair might be moved
        // successfully, but the second element could throw during its move.
        // This would leave the pair in an inconsistent state: the first element
        // would be moved from the source, while the second would remain intact.
        sfl::dtl::construct_at(std::addressof(this_new_functions), other_functions);

        // Destroy the old pair of functions (noexcept)
        sfl::dtl::destroy_at(std::addressof(this_old_functions));

        // Change active functions (noexcept)
        status_ ^= 1;
    }

    SFL_CONSTEXPR_20
    void priv_swap(hash_table_functions& other, std::true_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        auto& this_functions = (status_ == 0) ? functions0_ : functions1_;

        auto& other_functions = (other.status_ == 0) ? other.functions0_ : other.functions1_;

        using std::swap;

        swap(this_functions, other_functions);
    }

    SFL_CONSTEXPR_20
    void priv_swap(hash_table_functions& other, std::false_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        auto& this_old_functions = (status_ == 0) ? functions0_ : functions1_;

        auto& this_new_functions = (status_ == 0) ? functions1_ : functions0_;

        auto& other_old_functions = (other.status_ == 0) ? other.functions0_ : other.functions1_;

        auto& other_new_functions = (other.status_ == 0) ? other.functions1_ : other.functions0_;

        // Construct a new pair of functions in this (may throw)
        sfl::dtl::construct_at(std::addressof(this_new_functions), other_old_functions);

        // Construct a new pair of functions in other (may throw)
        SFL_TRY
        {
            sfl::dtl::construct_at(std::addressof(other_new_functions), this_old_functions);
        }
        SFL_CATCH (...)
        {
            sfl::dtl::destroy_at(std::addressof(this_new_functions));
            SFL_RETHROW;
        }

        // Destroy the old pair of functions in this (noexcept)
        sfl::dtl::destroy_at(std::addressof(this_old_functions));

        // Destroy the old pair of functions in other (noexcept)
        sfl::dtl::destroy_at(std::addressof(other_old_functions));

        // Change active functions (noexcept)
        status_ ^= 1;
        other.status_ ^= 1;
    }
};

#if defined(_MSC_VER) && SFL_CPP_VERSION >= SFL_CPP_20

//
// This is partial workaround for Visual C++ compiler bug
// https://developercommunity.visualstudio.com/t/MSVC-false-positive-read-of-an-uninitial/10808174
//
template <typename KeyHash, typename KeyEqual>
class hash_table_functions<KeyHash, KeyEqual, true> : private KeyHash, private KeyEqual
{
public:

    SFL_CONSTEXPR_20
    hash_table_functions()
        : KeyHash()
        , KeyEqual()
    {}

    SFL_CONSTEXPR_20
    hash_table_functions(const KeyHash& hash)
        : KeyHash(hash)
        , KeyEqual()
    {}

    SFL_CONSTEXPR_20
    hash_table_functions(const KeyHash& hash, const KeyEqual& equal)
        : KeyHash(hash)
        , KeyEqual(equal)
    {}

    SFL_CONSTEXPR_20
    KeyHash& ref_to_key_hash()
    {
        return *this;
    }

    SFL_CONSTEXPR_20
    const KeyHash& ref_to_key_hash() const
    {
        return *this;
    }

    SFL_CONSTEXPR_20
    KeyEqual& ref_to_key_equal()
    {
        return *this;
    }

    SFL_CONSTEXPR_20
    const KeyEqual& ref_to_key_equal() const
    {
        return *this;
    }

    SFL_CONSTEXPR_20
    void assign_copy(const hash_table_functions& other)
    {
        // Nothing to do
        sfl::dtl::ignore_unused(other);
    }

    SFL_CONSTEXPR_20
    void assign_move(hash_table_functions& other)
    {
        // Nothing to do
        sfl::dtl::ignore_unused(other);
    }

    SFL_CONSTEXPR_20
    void swap(hash_table_functions& other)
    {
        // Nothing to do
        sfl::dtl::ignore_unused(other);
    }
};

#endif // defined(_MSC_VER) && SFL_CPP_VERSION >= SFL_CPP_20

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// POWER OF 2 BUCKET COUNT POLICY
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class hash_table_dynamic_pow2_bucket_count_policy
{
private:

    std::size_t bucket_count_;

    int bucket_count_log2_;

private:

    // Fibonnaci hashing is used:
    // https://en.wikipedia.org/wiki/Hash_function#Fibonacci_hashing
    // https://probablydance.com/2018/06/16/fibonacci-hashing-the-optimization-that-the-world-forgot-or-a-better-alternative-to-integer-modulo/

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 64>* = nullptr>
    SFL_CONSTEXPR_20
    SizeType priv_calculate_bucket_index_for_hash(SizeType hash) const
    {
        constexpr SizeType a = 0x9e3779b97f4a7c15u;
        constexpr int w = 64;
        const SizeType bucket_index = (a * hash) >> (w - bucket_count_log2_);
        SFL_ASSERT(bucket_index < bucket_count_);
        return bucket_index;
    }

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 32>* = nullptr>
    SFL_CONSTEXPR_20
    SizeType priv_calculate_bucket_index_for_hash(SizeType hash) const
    {
        constexpr SizeType a = 0x9e3779b9u;
        constexpr int w = 32;
        const SizeType bucket_index = (a * hash) >> (w - bucket_count_log2_);
        SFL_ASSERT(bucket_index < bucket_count_);
        return bucket_index;
    }

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 16>* = nullptr>
    SFL_CONSTEXPR_20
    SizeType priv_calculate_bucket_index_for_hash(SizeType hash) const
    {
        constexpr SizeType a = 0x9e37u;
        constexpr int w = 16;
        const SizeType bucket_index = (a * hash) >> (w - bucket_count_log2_);
        SFL_ASSERT(bucket_index < bucket_count_);
        return bucket_index;
    }

public:

    SFL_CONSTEXPR_20
    static bool check_bucket_count(std::size_t bucket_count)
    {
        return sfl::dtl::has_single_bit(bucket_count);
    }

    SFL_CONSTEXPR_20
    static std::size_t get_max_bucket_count()
    {
        return ~(std::numeric_limits<std::size_t>::max() >> 1) >> 1;
    }

    SFL_CONSTEXPR_20
    static std::size_t calculate_new_bucket_count(std::size_t min_bucket_count)
    {
        return std::max<std::size_t>
        (
            16,
            std::min<std::size_t>
            (
                sfl::dtl::bit_ceil(min_bucket_count),
                get_max_bucket_count()
            )
        );
    }

    SFL_CONSTEXPR_20
    std::size_t get_bucket_count() const
    {
        return bucket_count_;
    }

    SFL_CONSTEXPR_20
    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(check_bucket_count(bucket_count));
        bucket_count_ = bucket_count;
        bucket_count_log2_ = sfl::dtl::bit_log2(bucket_count);
    }

    SFL_CONSTEXPR_20
    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return priv_calculate_bucket_index_for_hash<std::size_t>(hash);
    }

    SFL_CONSTEXPR_20
    void swap(hash_table_dynamic_pow2_bucket_count_policy& other)
    {
        using std::swap;
        swap(bucket_count_, other.bucket_count_);
        swap(bucket_count_log2_, other.bucket_count_log2_);
    }
};

///////////////////////////////////////////////////////////////////////////////

template <std::size_t StaticBucketCount>
class hash_table_static_pow2_bucket_count_policy
{
    static_assert
    (
        sfl::dtl::has_single_bit(StaticBucketCount),
        "StaticBucketCount must be power of 2"
    );

private:

    // Fibonnaci hashing is used:
    // https://en.wikipedia.org/wiki/Hash_function#Fibonacci_hashing
    // https://probablydance.com/2018/06/16/fibonacci-hashing-the-optimization-that-the-world-forgot-or-a-better-alternative-to-integer-modulo/

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 64>* = nullptr>
    SFL_CONSTEXPR_20
    SizeType priv_calculate_bucket_index_for_hash(SizeType hash) const
    {
        constexpr SizeType a = 0x9e3779b97f4a7c15u;
        constexpr int w = 64;
        constexpr int m = sfl::dtl::bit_log2(StaticBucketCount);
        const SizeType bucket_index = (a * hash) >> (w - m);
        SFL_ASSERT(bucket_index < StaticBucketCount);
        return bucket_index;
    }

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 32>* = nullptr>
    SFL_CONSTEXPR_20
    SizeType priv_calculate_bucket_index_for_hash(SizeType hash) const
    {
        constexpr SizeType a = 0x9e3779b9u;
        constexpr int w = 32;
        constexpr int m = sfl::dtl::bit_log2(StaticBucketCount);
        const SizeType bucket_index = (a * hash) >> (w - m);
        SFL_ASSERT(bucket_index < StaticBucketCount);
        return bucket_index;
    }

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 16>* = nullptr>
    SFL_CONSTEXPR_20
    SizeType priv_calculate_bucket_index_for_hash(SizeType hash) const
    {
        constexpr SizeType a = 0x9e37u;
        constexpr int w = 16;
        constexpr int m = sfl::dtl::bit_log2(StaticBucketCount);
        const SizeType bucket_index = (a * hash) >> (w - m);
        SFL_ASSERT(bucket_index < StaticBucketCount);
        return bucket_index;
    }

public:

    SFL_CONSTEXPR_20
    static bool check_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
        return true;
    }

    SFL_CONSTEXPR_20
    static std::size_t get_max_bucket_count()
    {
        return StaticBucketCount;
    }

    SFL_CONSTEXPR_20
    static std::size_t calculate_new_bucket_count(std::size_t min_bucket_count)
    {
        SFL_ASSERT(min_bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(min_bucket_count);
        return StaticBucketCount;
    }

    SFL_CONSTEXPR_20
    std::size_t get_bucket_count() const
    {
        return StaticBucketCount;
    }

    SFL_CONSTEXPR_20
    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
    }

    SFL_CONSTEXPR_20
    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return priv_calculate_bucket_index_for_hash<std::size_t>(hash);
    }

    SFL_CONSTEXPR_20
    void swap(hash_table_static_pow2_bucket_count_policy& other)
    {
        sfl::dtl::ignore_unused(other);
    }
};

template <>
SFL_CONSTEXPR_20
inline std::size_t hash_table_static_pow2_bucket_count_policy<1>::calculate_bucket_index_for_hash(std::size_t hash) const
{
    sfl::dtl::ignore_unused(hash);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// PRIME BUCKET COUNT POLICY
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename Dummy = void>
struct hash_table_prime_list
{
    static const std::size_t list[];
    static const std::size_t size;

    static std::size_t ceil(std::size_t x)
    {
        const std::size_t* begin = list;
        const std::size_t* end = begin + size;
        const std::size_t* res = std::lower_bound(begin, end, x);
        if (res == end)
        {
            --res;
        }
        return *res;
    }
};

template <typename Dummy>
const std::size_t hash_table_prime_list<Dummy>::list[] =
{
    17u, 29u, 37u, 53u, 67u, 79u, 97u, 131u, 193u, 257u, 389u, 521u, 769u,
    1031u, 1543u, 2053u, 3079u, 6151u, 12289u, 24593u, 49157u, 98317u, 196613u,
    393241u, 786433u, 1572869u, 3145739u, 6291469u, 12582917u, 25165843u,
    50331653u, 100663319u, 201326611u, 402653189u, 805306457u, 1610612741u,
    3221225473u, 4294967291u
};

template <typename Dummy>
const std::size_t hash_table_prime_list<Dummy>::size = sizeof(hash_table_prime_list<Dummy>::list) / sizeof(std::size_t);

///////////////////////////////////////////////////////////////////////////////

#if SFL_CPP_VERSION >= SFL_CPP_20

template <typename Dummy = void>
struct hash_table_prime_list_constexpr20
{
    static constexpr std::size_t list[] =
    {
        17u, 29u, 37u, 53u, 67u, 79u, 97u, 131u, 193u, 257u, 389u, 521u, 769u,
        1031u, 1543u, 2053u, 3079u, 6151u, 12289u, 24593u, 49157u, 98317u, 196613u,
        393241u, 786433u, 1572869u, 3145739u, 6291469u, 12582917u, 25165843u,
        50331653u, 100663319u, 201326611u, 402653189u, 805306457u, 1610612741u,
        3221225473u, 4294967291u
    };

    static constexpr std::size_t size = sizeof(list) / sizeof(std::size_t);

    static constexpr std::size_t ceil(std::size_t x)
    {
        const std::size_t* begin = list;
        const std::size_t* end = begin + size;
        const std::size_t* res = std::lower_bound(begin, end, x);
        if (res == end)
        {
            --res;
        }
        return *res;
    }
};

#endif // SFL_CPP_VERSION >= SFL_CPP_20

///////////////////////////////////////////////////////////////////////////////

class hash_table_dynamic_prime_bucket_count_policy
{
private:

    std::size_t bucket_count_;

public:

    SFL_CONSTEXPR_20
    static bool check_bucket_count(std::size_t bucket_count)
    {
        return sfl::dtl::is_prime(bucket_count);
    }

    SFL_CONSTEXPR_20
    static std::size_t get_max_bucket_count()
    {
        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (std::is_constant_evaluated())
        {
            return sfl::dtl::hash_table_prime_list_constexpr20<>::list[sfl::dtl::hash_table_prime_list_constexpr20<>::size - 1];
        }
        #endif

        return sfl::dtl::hash_table_prime_list<>::list[sfl::dtl::hash_table_prime_list<>::size - 1];
    }

    SFL_CONSTEXPR_20
    static std::size_t calculate_new_bucket_count(std::size_t min_bucket_count)
    {
        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (std::is_constant_evaluated())
        {
            return sfl::dtl::hash_table_prime_list_constexpr20<>::ceil(min_bucket_count);
        }
        #endif

        return sfl::dtl::hash_table_prime_list<>::ceil(min_bucket_count);
    }

    SFL_CONSTEXPR_20
    std::size_t get_bucket_count() const
    {
        return bucket_count_;
    }

    SFL_CONSTEXPR_20
    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(check_bucket_count(bucket_count));
        bucket_count_ = bucket_count;
    }

    SFL_CONSTEXPR_20
    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return hash % bucket_count_;
    }

    SFL_CONSTEXPR_20
    void swap(hash_table_dynamic_prime_bucket_count_policy& other)
    {
        using std::swap;
        swap(bucket_count_, other.bucket_count_);
    }
};

///////////////////////////////////////////////////////////////////////////////

template <std::size_t StaticBucketCount>
class hash_table_static_prime_bucket_count_policy
{
    static_assert
    (
        sfl::dtl::is_prime(StaticBucketCount),
        "StaticBucketCount must be prime number"
    );

public:

    SFL_CONSTEXPR_20
    static bool check_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
        return true;
    }

    SFL_CONSTEXPR_20
    static std::size_t get_max_bucket_count()
    {
        return StaticBucketCount;
    }

    SFL_CONSTEXPR_20
    static std::size_t calculate_new_bucket_count(std::size_t min_bucket_count)
    {
        SFL_ASSERT(min_bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(min_bucket_count);
        return StaticBucketCount;
    }

    SFL_CONSTEXPR_20
    std::size_t get_bucket_count() const
    {
        return StaticBucketCount;
    }

    SFL_CONSTEXPR_20
    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
    }

    SFL_CONSTEXPR_20
    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return hash % StaticBucketCount;
    }

    SFL_CONSTEXPR_20
    void swap(hash_table_static_prime_bucket_count_policy& other)
    {
        sfl::dtl::ignore_unused(other);
    }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// BASIC BUCKET COUNT POLICY
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class hash_table_dynamic_basic_bucket_count_policy
{
private:

    std::size_t bucket_count_;

public:

    SFL_CONSTEXPR_20
    static bool check_bucket_count(std::size_t bucket_count)
    {
        return bucket_count > 0;
    }

    SFL_CONSTEXPR_20
    static std::size_t get_max_bucket_count()
    {
        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (std::is_constant_evaluated())
        {
            return sfl::dtl::hash_table_prime_list_constexpr20<>::list[sfl::dtl::hash_table_prime_list_constexpr20<>::size - 1];
        }
        #endif

        return sfl::dtl::hash_table_prime_list<>::list[sfl::dtl::hash_table_prime_list<>::size - 1];
    }

    SFL_CONSTEXPR_20
    static std::size_t calculate_new_bucket_count(std::size_t min_bucket_count)
    {
        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (std::is_constant_evaluated())
        {
            return sfl::dtl::hash_table_prime_list_constexpr20<>::ceil(min_bucket_count);
        }
        #endif

        return sfl::dtl::hash_table_prime_list<>::ceil(min_bucket_count);
    }

    SFL_CONSTEXPR_20
    std::size_t get_bucket_count() const
    {
        return bucket_count_;
    }

    SFL_CONSTEXPR_20
    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(check_bucket_count(bucket_count));
        bucket_count_ = bucket_count;
    }

    SFL_CONSTEXPR_20
    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return hash % bucket_count_;
    }

    SFL_CONSTEXPR_20
    void swap(hash_table_dynamic_basic_bucket_count_policy& other)
    {
        using std::swap;
        swap(bucket_count_, other.bucket_count_);
    }
};

///////////////////////////////////////////////////////////////////////////////

template <std::size_t StaticBucketCount>
class hash_table_static_basic_bucket_count_policy
{
    static_assert
    (
        StaticBucketCount > 0,
        "StaticBucketCount must be greater than zero"
    );

public:

    SFL_CONSTEXPR_20
    static bool check_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
        return true;
    }

    SFL_CONSTEXPR_20
    static std::size_t get_max_bucket_count()
    {
        return StaticBucketCount;
    }

    SFL_CONSTEXPR_20
    static std::size_t calculate_new_bucket_count(std::size_t min_bucket_count)
    {
        SFL_ASSERT(min_bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(min_bucket_count);
        return StaticBucketCount;
    }

    SFL_CONSTEXPR_20
    std::size_t get_bucket_count() const
    {
        return StaticBucketCount;
    }

    SFL_CONSTEXPR_20
    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
    }

    SFL_CONSTEXPR_20
    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return hash % StaticBucketCount;
    }

    SFL_CONSTEXPR_20
    void swap(hash_table_static_basic_bucket_count_policy& other)
    {
        sfl::dtl::ignore_unused(other);
    }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// STANDARD MAX LOAD POLICY
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class hash_table_standard_max_load_policy
{
private:

    float max_load_factor_;

    std::size_t max_load_;

public:

    SFL_CONSTEXPR_20
    hash_table_standard_max_load_policy()
        : max_load_factor_(1.0f)
        , max_load_(0)
    {}

    SFL_CONSTEXPR_20
    void recalculate_max_load(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count != 0);
        max_load_ = sfl::dtl::floating_point_to_size_t
        (
            sfl::dtl::ceil
            (
                static_cast<double>(max_load_factor_) *
                static_cast<double>(bucket_count)
            )
        );
    }

    SFL_CONSTEXPR_20
    void set_max_load_factor(float max_load_factor)
    {
        constexpr float smallest_max_load_factor = 0.001f;
        max_load_factor_ = std::max(smallest_max_load_factor, max_load_factor);
    }

    SFL_CONSTEXPR_20
    float get_max_load_factor() const
    {
        return max_load_factor_;
    }

    SFL_CONSTEXPR_20
    std::size_t get_max_load() const
    {
        return max_load_;
    }

    SFL_CONSTEXPR_20
    bool is_overloaded(std::size_t size) const
    {
        return size > max_load_;
    }

    SFL_CONSTEXPR_20
    void swap(hash_table_standard_max_load_policy& other)
    {
        using std::swap;
        swap(max_load_factor_, other.max_load_factor_);
        swap(max_load_, other.max_load_);
    }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// NO MAX LOAD POLICY
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class hash_table_no_max_load_policy
{
public:

    SFL_CONSTEXPR_20
    void recalculate_max_load(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count != 0);
        sfl::dtl::ignore_unused(bucket_count);
    }

    SFL_CONSTEXPR_20
    void set_max_load_factor(float max_load_factor)
    {
        sfl::dtl::ignore_unused(max_load_factor);
    }

    SFL_CONSTEXPR_20
    float get_max_load_factor() const
    {
        return 1.0f;
    }

    SFL_CONSTEXPR_20
    std::size_t get_max_load() const
    {
        return std::numeric_limits<std::size_t>::max();
    }

    SFL_CONSTEXPR_20
    bool is_overloaded(std::size_t size) const
    {
        sfl::dtl::ignore_unused(size);
        return false;
    }

    SFL_CONSTEXPR_20
    void swap(hash_table_no_max_load_policy& other)
    {
        sfl::dtl::ignore_unused(other);
    }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// HASH TABLE
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template < typename Key,
           typename Value,
           typename KeyOfValue,
           typename KeyHash,
           typename KeyEqual,
           typename NodeAllocator,
           typename BucketAllocator,
           typename BucketCountPolicy,
           typename MaxLoadPolicy >
class hash_table
{
    #ifdef SFL_TEST_HASH_TABLE
    template <int>
    friend void ::test_hash_table();
    #endif

public:

    using key_type = Key;

    using value_type = Value;

    using size_type = std::size_t;

    using difference_type = std::ptrdiff_t;

    using key_hash = KeyHash;

    using key_equal = KeyEqual;

private:

    using functions = sfl::dtl::hash_table_functions<key_hash, key_equal>;

    using node_allocator_void_pointer = typename sfl::dtl::allocator_traits<NodeAllocator>::void_pointer;

    using base_node_type = sfl::dtl::hash_table_base_node<node_allocator_void_pointer>;

    using base_node_pointer = typename base_node_type::base_node_pointer;

    using node_type = sfl::dtl::hash_table_node<value_type, node_allocator_void_pointer>;

    using node_pointer = typename node_type::node_pointer;

    using bucket_type = sfl::dtl::hash_table_bucket<base_node_pointer>;

    using node_allocator_type = typename sfl::dtl::allocator_traits<NodeAllocator>::template rebind_alloc<node_type>;

    using bucket_allocator_type = typename sfl::dtl::allocator_traits<BucketAllocator>::template rebind_alloc<bucket_type>;

    using bucket_pointer = typename sfl::dtl::allocator_traits<bucket_allocator_type>::pointer;

    using bucket_count_policy = BucketCountPolicy;

    using max_load_policy = MaxLoadPolicy;

public:

    class iterator
    {
        #ifdef SFL_TEST_HASH_TABLE
        template <int>
        friend void ::test_hash_table();
        #endif

        friend class hash_table;

    public:

        using difference_type   = std::ptrdiff_t;
        using value_type        = Value;
        using pointer           = Value*;
        using reference         = Value&;
        using iterator_category = std::forward_iterator_tag;

    private:

        base_node_pointer node_;

    #if defined(_MSC_VER) // Workaround for Visual C++ bug in C++20 constexpr
    public:
    #else
    private:
    #endif

        SFL_CONSTEXPR_20
        explicit iterator(base_node_pointer x) noexcept
            : node_(x)
        {}

    public:

        // Default constructor
        SFL_CONSTEXPR_20
        iterator() noexcept
        {}

        // Copy constructor
        SFL_CONSTEXPR_20
        iterator(const iterator& other) noexcept
            : node_(other.node_)
        {}

        // Copy assignment operator
        SFL_CONSTEXPR_20
        iterator& operator=(const iterator& other) noexcept
        {
            node_ = other.node_;
            return *this;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        reference operator*() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ref();
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        pointer operator->() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ptr();
        }

        SFL_CONSTEXPR_20
        iterator& operator++() noexcept
        {
            node_ = node_->next_;
            return *this;
        }

        SFL_CONSTEXPR_20
        iterator operator++(int) noexcept
        {
            auto temp = *this;
            node_ = node_->next_;
            return temp;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        friend bool operator==(const iterator& x, const iterator& y) noexcept
        {
            return x.node_ == y.node_;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        friend bool operator!=(const iterator& x, const iterator& y) noexcept
        {
            return !(x == y);
        }
    };

    class const_iterator
    {
        #ifdef SFL_TEST_HASH_TABLE
        template <int>
        friend void ::test_hash_table();
        #endif

        friend class hash_table;

    public:

        using difference_type   = std::ptrdiff_t;
        using value_type        = Value;
        using pointer           = const Value*;
        using reference         = const Value&;
        using iterator_category = std::forward_iterator_tag;

    private:

        base_node_pointer node_;

    #if defined(_MSC_VER) // Workaround for Visual C++ bug in C++20 constexpr
    public:
    #else
    private:
    #endif

        SFL_CONSTEXPR_20
        explicit const_iterator(base_node_pointer x) noexcept
            : node_(x)
        {}

    public:

        // Default constructor
        SFL_CONSTEXPR_20
        const_iterator() noexcept
        {}

        // Copy constructor
        SFL_CONSTEXPR_20
        const_iterator(const const_iterator& other) noexcept
            : node_(other.node_)
        {}

        // Converting constructor (from iterator to const_iterator)
        SFL_CONSTEXPR_20
        const_iterator(const iterator& other) noexcept
            : node_(other.node_)
        {}

        // Copy assignment operator
        SFL_CONSTEXPR_20
        const_iterator& operator=(const const_iterator& other) noexcept
        {
            node_ = other.node_;
            return *this;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        reference operator*() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ref();
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        pointer operator->() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ptr();
        }

        SFL_CONSTEXPR_20
        const_iterator& operator++() noexcept
        {
            node_ = node_->next_;
            return *this;
        }

        SFL_CONSTEXPR_20
        const_iterator operator++(int) noexcept
        {
            auto temp = *this;
            node_ = node_->next_;
            return temp;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        friend bool operator==(const const_iterator& x, const const_iterator& y) noexcept
        {
            return x.node_ == y.node_;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        friend bool operator!=(const const_iterator& x, const const_iterator& y) noexcept
        {
            return !(x == y);
        }
    };

    class local_iterator
    {
        #ifdef SFL_TEST_HASH_TABLE
        template <int>
        friend void ::test_hash_table();
        #endif

        friend class hash_table;

    public:

        using difference_type   = std::ptrdiff_t;
        using value_type        = Value;
        using pointer           = Value*;
        using reference         = Value&;
        using iterator_category = std::forward_iterator_tag;

    private:

        base_node_pointer node_;

        std::size_t bucket_index_;

    private:

        SFL_CONSTEXPR_20
        explicit local_iterator(base_node_pointer x) noexcept
            : node_(x)
            , bucket_index_() // Needed here only because of C++20 constexpr (Clang 18 complains if not here)
        {}

        SFL_CONSTEXPR_20
        explicit local_iterator(base_node_pointer x, std::size_t bucket_index) noexcept
            : node_(x)
            , bucket_index_(bucket_index)
        {}

    public:

        // Default constructor
        SFL_CONSTEXPR_20
        local_iterator() noexcept
        {}

        // Copy constructor
        SFL_CONSTEXPR_20
        local_iterator(const local_iterator& other) noexcept
            : node_(other.node_)
            , bucket_index_(other.bucket_index_)
        {}

        // Copy assignment operator
        SFL_CONSTEXPR_20
        local_iterator& operator=(const local_iterator& other) noexcept
        {
            node_ = other.node_;
            bucket_index_ = other.bucket_index_;
            return *this;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        reference operator*() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ref();
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        pointer operator->() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ptr();
        }

        SFL_CONSTEXPR_20
        local_iterator& operator++() noexcept
        {
            node_ = node_->next_;
            if (node_ != nullptr && hash_table::bucket_index_of(node_) != bucket_index_)
            {
                node_ = nullptr;
            }
            return *this;
        }

        SFL_CONSTEXPR_20
        local_iterator operator++(int) noexcept
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        friend bool operator==(const local_iterator& x, const local_iterator& y) noexcept
        {
            return x.node_ == y.node_;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        friend bool operator!=(const local_iterator& x, const local_iterator& y) noexcept
        {
            return !(x == y);
        }
    };

    class const_local_iterator
    {
        #ifdef SFL_TEST_HASH_TABLE
        template <int>
        friend void ::test_hash_table();
        #endif

        friend class hash_table;

    public:

        using difference_type   = std::ptrdiff_t;
        using value_type        = Value;
        using pointer           = const Value*;
        using reference         = const Value&;
        using iterator_category = std::forward_iterator_tag;

    private:

        base_node_pointer node_;
        std::size_t bucket_index_;

    private:

        SFL_CONSTEXPR_20
        explicit const_local_iterator(base_node_pointer x) noexcept
            : node_(x)
            , bucket_index_() // Needed here only because of C++20 constexpr (Clang 18 complains if not here)
        {}

        SFL_CONSTEXPR_20
        explicit const_local_iterator(base_node_pointer x, std::size_t bucket_index) noexcept
            : node_(x)
            , bucket_index_(bucket_index)
        {}

    public:

        // Default constructor
        SFL_CONSTEXPR_20
        const_local_iterator() noexcept
        {}

        // Copy constructor
        SFL_CONSTEXPR_20
        const_local_iterator(const const_local_iterator& other) noexcept
            : node_(other.node_)
            , bucket_index_(other.bucket_index_)
        {}

        // Converting constructor (from local_iterator to const_local_iterator)
        SFL_CONSTEXPR_20
        const_local_iterator(const local_iterator& other) noexcept
            : node_(other.node_)
            , bucket_index_(other.bucket_index_)
        {}

        // Copy assignment operator
        SFL_CONSTEXPR_20
        const_local_iterator& operator=(const const_local_iterator& other) noexcept
        {
            node_ = other.node_;
            bucket_index_ = other.bucket_index_;
            return *this;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        reference operator*() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ref();
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        pointer operator->() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ptr();
        }

        SFL_CONSTEXPR_20
        const_local_iterator& operator++() noexcept
        {
            node_ = node_->next_;
            if (node_ != nullptr && hash_table::bucket_index_of(node_) != bucket_index_)
            {
                node_ = nullptr;
            }
            return *this;
        }

        SFL_CONSTEXPR_20
        const_local_iterator operator++(int) noexcept
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        friend bool operator==(const const_local_iterator& x, const const_local_iterator& y) noexcept
        {
            return x.node_ == y.node_;
        }

        SFL_NODISCARD
        SFL_CONSTEXPR_20
        friend bool operator!=(const const_local_iterator& x, const const_local_iterator& y) noexcept
        {
            return !(x == y);
        }
    };

private:

    class data
        : private functions
        , private node_allocator_type
        , private bucket_allocator_type
        , private bucket_count_policy
        , private max_load_policy
    {
    private:

        // Linked list head
        base_node_type head_;

    public:

        // Pointer to linked list head
        SFL_CONSTEXPR_20
        base_node_pointer head() const
        {
            return std::pointer_traits<base_node_pointer>::pointer_to(const_cast<base_node_type&>(head_));
        }

        // Number of nodes in linked list
        std::size_t size_;

        // Bucket array
        bucket_pointer buckets_;

    public:

        SFL_CONSTEXPR_20
        data()
            : head_(nullptr)
            , size_(0)
        {}

        template <typename Alloc>
        SFL_CONSTEXPR_20
        data(const Alloc& alloc)
            : node_allocator_type(alloc)
            , bucket_allocator_type(alloc)
            , head_(nullptr)
            , size_(0)
        {}

        SFL_CONSTEXPR_20
        data(const key_hash& hash)
            : functions(hash)
            , head_(nullptr)
            , size_(0)
        {}

        template <typename Alloc>
        SFL_CONSTEXPR_20
        data(const key_hash& hash, const Alloc& alloc)
            : functions(hash)
            , node_allocator_type(alloc)
            , bucket_allocator_type(alloc)
            , head_(nullptr)
            , size_(0)
        {}

        SFL_CONSTEXPR_20
        data(const key_hash& hash, const key_equal& equal)
            : functions(hash, equal)
            , head_(nullptr)
            , size_(0)
        {}

        template <typename Alloc>
        SFL_CONSTEXPR_20
        data(const key_hash& hash, const key_equal& equal, const Alloc& alloc)
            : functions(hash, equal)
            , node_allocator_type(alloc)
            , bucket_allocator_type(alloc)
            , head_(nullptr)
            , size_(0)
        {}

        SFL_CONSTEXPR_20
        data(const data& other)
            : functions(other.ref_to_key_hash(), other.ref_to_key_equal())
            , node_allocator_type(sfl::dtl::allocator_traits<node_allocator_type>::select_on_container_copy_construction(other.ref_to_node_alloc()))
            , bucket_allocator_type(sfl::dtl::allocator_traits<bucket_allocator_type>::select_on_container_copy_construction(other.ref_to_bucket_alloc()))
            , head_(nullptr)
            , size_(0)
        {}

        template <typename Alloc>
        SFL_CONSTEXPR_20
        data(const data& other, const Alloc& alloc)
            : functions(other.ref_to_key_hash(), other.ref_to_key_equal())
            , node_allocator_type(alloc)
            , bucket_allocator_type(alloc)
            , head_(nullptr)
            , size_(0)
        {}

        SFL_CONSTEXPR_20
        data(data&& other)
            : functions(std::move(other.ref_to_key_hash()), std::move(other.ref_to_key_equal()))
            , node_allocator_type(std::move(other.ref_to_node_alloc()))
            , bucket_allocator_type(std::move(other.ref_to_bucket_alloc()))
            , head_(nullptr)
            , size_(0)
        {}

        template <typename Alloc>
        SFL_CONSTEXPR_20
        data(data&& other, const Alloc& alloc)
            : functions(std::move(other.ref_to_key_hash()), std::move(other.ref_to_key_equal()))
            , node_allocator_type(alloc)
            , bucket_allocator_type(alloc)
            , head_(nullptr)
            , size_(0)
        {}

        SFL_CONSTEXPR_20
        ~data()
        {}

        ///////////////////////////////////////////////////////////////////////

        SFL_CONSTEXPR_20
        key_hash& ref_to_key_hash()
        {
            return static_cast<functions*>(this)->ref_to_key_hash();
        }

        SFL_CONSTEXPR_20
        const key_hash& ref_to_key_hash() const
        {
            return static_cast<const functions*>(this)->ref_to_key_hash();
        }

        SFL_CONSTEXPR_20
        key_equal& ref_to_key_equal()
        {
            return static_cast<functions*>(this)->ref_to_key_equal();
        }

        SFL_CONSTEXPR_20
        const key_equal& ref_to_key_equal() const
        {
            return static_cast<const functions*>(this)->ref_to_key_equal();
        }

        SFL_CONSTEXPR_20
        node_allocator_type& ref_to_node_alloc()
        {
            return *this;
        }

        SFL_CONSTEXPR_20
        const node_allocator_type& ref_to_node_alloc() const
        {
            return *this;
        }

        SFL_CONSTEXPR_20
        bucket_allocator_type& ref_to_bucket_alloc()
        {
            return *this;
        }

        SFL_CONSTEXPR_20
        const bucket_allocator_type& ref_to_bucket_alloc() const
        {
            return *this;
        }

        ///////////////////////////////////////////////////////////////////////

        SFL_CONSTEXPR_20
        bool check_bucket_count(std::size_t n) const
        {
            return bucket_count_policy::check_bucket_count(n);
        }

        SFL_CONSTEXPR_20
        std::size_t calculate_new_bucket_count(std::size_t min_bucket_count) const
        {
            return bucket_count_policy::calculate_new_bucket_count(min_bucket_count);
        }

        SFL_CONSTEXPR_20
        std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
        {
            return bucket_count_policy::calculate_bucket_index_for_hash(hash);
        }

        SFL_CONSTEXPR_20
        void set_bucket_count(std::size_t n)
        {
            bucket_count_policy::set_bucket_count(n);
            max_load_policy::recalculate_max_load(n);
        }

        SFL_CONSTEXPR_20
        std::size_t get_bucket_count() const
        {
            return bucket_count_policy::get_bucket_count();
        }

        SFL_CONSTEXPR_20
        std::size_t get_max_bucket_count() const
        {
            return bucket_count_policy::get_max_bucket_count();
        }

        SFL_CONSTEXPR_20
        float get_max_load_factor() const
        {
            return max_load_policy::get_max_load_factor();
        }

        SFL_CONSTEXPR_20
        void set_max_load_factor(float mlf)
        {
            max_load_policy::set_max_load_factor(mlf);
            max_load_policy::recalculate_max_load(get_bucket_count());
        }

        SFL_CONSTEXPR_20
        std::size_t get_max_load() const
        {
            return max_load_policy::get_max_load();
        }

        SFL_CONSTEXPR_20
        bool is_overloaded() const
        {
            return max_load_policy::is_overloaded(size_);
        }

        ///////////////////////////////////////////////////////////////////////

        SFL_CONSTEXPR_20
        void assign_copy_functions(const data& other)
        {
            functions::assign_copy(other);
        }

        ///////////////////////////////////////////////////////////////////////

        SFL_CONSTEXPR_20
        void assign_move_functions(data& other)
        {
            functions::assign_move(other);
        }

        ///////////////////////////////////////////////////////////////////////

        SFL_CONSTEXPR_20
        void swap_functions(data& other)
        {
            functions::swap(other);
        }

        SFL_CONSTEXPR_20
        void swap_bucket_count(data& other)
        {
            bucket_count_policy::swap(other);
        }

        SFL_CONSTEXPR_20
        void swap_max_load_factor(data& other)
        {
            max_load_policy::swap(other);
        }
    };

    data data_;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    SFL_CONSTEXPR_20
    hash_table() = delete;

    SFL_CONSTEXPR_20
    hash_table(size_type initial_bucket_count)
        : data_()
    {
        initialize_empty(initial_bucket_count);
    }

    template <typename Alloc>
    SFL_CONSTEXPR_20
    hash_table(size_type initial_bucket_count, const Alloc& alloc)
        : data_(alloc)
    {
        initialize_empty(initial_bucket_count);
    }

    SFL_CONSTEXPR_20
    hash_table(size_type initial_bucket_count, const key_hash& hash)
        : data_(hash)
    {
        initialize_empty(initial_bucket_count);
    }

    template <typename Alloc>
    SFL_CONSTEXPR_20
    hash_table(size_type initial_bucket_count, const key_hash& hash, const Alloc& alloc)
        : data_(hash, alloc)
    {
        initialize_empty(initial_bucket_count);
    }

    SFL_CONSTEXPR_20
    hash_table(size_type initial_bucket_count, const key_hash& hash, const key_equal& equal)
        : data_(hash, equal)
    {
        initialize_empty(initial_bucket_count);
    }

    template <typename Alloc>
    SFL_CONSTEXPR_20
    hash_table(size_type initial_bucket_count, const key_hash& hash, const key_equal& equal, const Alloc& alloc)
        : data_(hash, equal, alloc)
    {
        initialize_empty(initial_bucket_count);
    }

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    hash_table(const hash_table& other, EqualOrUniqueTag equal_or_unique_tag)
        : data_(other.data_)
    {
        initialize_copy(other, equal_or_unique_tag);
    }

    template <typename EqualOrUniqueTag, typename Alloc>
    SFL_CONSTEXPR_20
    hash_table(const hash_table& other, EqualOrUniqueTag equal_or_unique_tag, const Alloc& alloc)
        : data_(other.data_, alloc)
    {
        initialize_copy(other, equal_or_unique_tag);
    }

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    hash_table(hash_table&& other, EqualOrUniqueTag equal_or_unique_tag)
        : data_(std::move(other.data_))
    {
        initialize_move(other, equal_or_unique_tag);
    }

    template <typename EqualOrUniqueTag, typename Alloc>
    SFL_CONSTEXPR_20
    hash_table(hash_table&& other, EqualOrUniqueTag equal_or_unique_tag, const Alloc& alloc)
        : data_(std::move(other.data_), alloc)
    {
        initialize_move(other, equal_or_unique_tag);
    }

    SFL_CONSTEXPR_20
    ~hash_table()
    {
        for (base_node_pointer x = data_.head()->next_; x != nullptr; )
        {
            base_node_pointer y = x->next_;
            drop_node(static_cast<node_pointer>(x));
            x = y;
        }

        drop_buckets(data_.buckets_, data_.get_bucket_count());
    }

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    // This is deleted. Use `assign_copy` instead.
    hash_table& operator=(const hash_table& other) = delete;

    // This is deleted. Use `assign_move` instead.
    hash_table& operator=(hash_table&& other) = delete;

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void assign_copy(const hash_table& other, EqualOrUniqueTag equal_or_unique_tag)
    {
        assign_copy_impl(other, equal_or_unique_tag);
    }

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void assign_move(hash_table& other, EqualOrUniqueTag equal_or_unique_tag)
    {
        assign_move_impl(other, equal_or_unique_tag);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    SFL_CONSTEXPR_20
    void assign_range_equal(InputIt first, InputIt last)
    {
        make_node_with_recycling_functor make_node(*this);

        while (first != last)
        {
            insert_equal(*first, make_node);
            ++first;
        }
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    SFL_CONSTEXPR_20
    void assign_range_unique(InputIt first, InputIt last)
    {
        make_node_with_recycling_functor make_node(*this);

        while (first != last)
        {
            insert_unique(*first, make_node);
            ++first;
        }
    }

    //
    // ---- KEY HASH ----------------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    key_hash& ref_to_key_hash() noexcept
    {
        return data_.ref_to_key_hash();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const key_hash& ref_to_key_hash() const noexcept
    {
        return data_.ref_to_key_hash();
    }

    //
    // ---- KEY EQUAL ---------------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    key_equal& ref_to_key_equal() noexcept
    {
        return data_.ref_to_key_equal();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const key_equal& ref_to_key_equal() const noexcept
    {
        return data_.ref_to_key_equal();
    }

    //
    // ---- ALLOCATOR ---------------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    node_allocator_type& ref_to_node_alloc() noexcept
    {
        return data_.ref_to_node_alloc();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const node_allocator_type& ref_to_node_alloc() const noexcept
    {
        return data_.ref_to_node_alloc();
    }

    //
    // ---- ITERATORS ---------------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator begin() noexcept
    {
        return iterator(data_.head()->next_);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator begin() const noexcept
    {
        return const_iterator(data_.head()->next_);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator cbegin() const noexcept
    {
        return const_iterator(data_.head()->next_);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator end() noexcept
    {
        return iterator(nullptr);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator end() const noexcept
    {
        return const_iterator(nullptr);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator cend() const noexcept
    {
        return const_iterator(nullptr);
    }

    //
    // ---- SIZE AND CAPACITY -------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    bool empty() const noexcept
    {
        return data_.size_ == 0;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type size() const noexcept
    {
        return data_.size_;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type max_size() const noexcept
    {
        return sfl::dtl::allocator_traits<node_allocator_type>::max_size(data_.ref_to_node_alloc());
    }

    //
    // ---- MODIFIERS ---------------------------------------------------------
    //

    SFL_CONSTEXPR_20
    void clear()
    {
        for (base_node_pointer x = data_.head()->next_; x != nullptr; )
        {
            base_node_pointer y = x->next_;
            drop_node(static_cast<node_pointer>(x));
            x = y;
        }

        for (bucket_pointer x = data_.buckets_, end = x + data_.get_bucket_count(); x != end; ++x)
        {
            x->next_ = nullptr;
        }

        data_.head()->next_ = nullptr;
        data_.size_ = 0;
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    iterator emplace_equal(Args&&... args)
    {
        make_node_functor make_node(*this);
        node_pointer x = make_node(std::forward<Args>(args)...);
        auto guard = sfl::dtl::make_scope_guard([&](){ drop_node(x); });
        auto res = find_node(key_of(x)); // may throw
        insert_node_equal(x, res.bucket_index, res.pos);
        guard.dismiss();
        ++data_.size_;
        resize_buckets_and_rehash_if_overloaded();
        return iterator(x);
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> emplace_unique(Args&&... args)
    {
        make_node_functor make_node(*this);
        node_pointer x = make_node(std::forward<Args>(args)...);
        auto guard = sfl::dtl::make_scope_guard([&](){ drop_node(x); });
        auto res = find_node(key_of(x)); // may throw
        if (res.pos != nullptr)
        {
            return std::make_pair(iterator(res.pos), false);
        }
        else
        {
            insert_node_unique(x, res.bucket_index);
            guard.dismiss();
            ++data_.size_;
            resize_buckets_and_rehash_if_overloaded();
            return std::make_pair(iterator(x), true);
        }
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    iterator emplace_hint_equal(const_iterator hint, Args&&... args)
    {
        make_node_functor make_node(*this);
        node_pointer x = make_node(std::forward<Args>(args)...);
        auto guard = sfl::dtl::make_scope_guard([&](){ drop_node(x); });
        auto res = find_node_hint(hint, key_of(x)); // may throw
        insert_node_equal(x, res.bucket_index, res.pos);
        guard.dismiss();
        ++data_.size_;
        resize_buckets_and_rehash_if_overloaded();
        return iterator(x);
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    iterator emplace_hint_unique(const_iterator hint, Args&&... args)
    {
        make_node_functor make_node(*this);
        node_pointer x = make_node(std::forward<Args>(args)...);
        auto guard = sfl::dtl::make_scope_guard([&](){ drop_node(x); });
        auto res = find_node_hint(hint, key_of(x)); // may throw
        if (res.pos != nullptr)
        {
            return iterator(res.pos);
        }
        else
        {
            insert_node_unique(x, res.bucket_index);
            guard.dismiss();
            ++data_.size_;
            resize_buckets_and_rehash_if_overloaded();
            return iterator(x);
        }
    }

private:

    template <typename V, typename MakeNodeFunctor>
    SFL_CONSTEXPR_20
    iterator insert_equal(V&& value, MakeNodeFunctor& make_node)
    {
        auto res = find_node(KeyOfValue()(value));
        node_pointer x = make_node(std::forward<V>(value));
        insert_node_equal(x, res.bucket_index, res.pos);
        ++data_.size_;
        resize_buckets_and_rehash_if_overloaded();
        return iterator(x);
    }

    template <typename V, typename MakeNodeFunctor>
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> insert_unique(V&& value, MakeNodeFunctor& make_node)
    {
        auto res = find_node(KeyOfValue()(value));
        if (res.pos != nullptr)
        {
            return std::make_pair(iterator(res.pos), false);
        }
        else
        {
            node_pointer x = make_node(std::forward<V>(value));
            insert_node_unique(x, res.bucket_index);
            ++data_.size_;
            resize_buckets_and_rehash_if_overloaded();
            return std::make_pair(iterator(x), true);
        }
    }

public:

    template <typename V>
    SFL_CONSTEXPR_20
    iterator insert_equal(V&& value)
    {
        make_node_functor make_node(*this);
        return insert_equal(std::forward<V>(value), make_node);
    }

    template <typename V>
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> insert_unique(V&& value)
    {
        make_node_functor make_node(*this);
        return insert_unique(std::forward<V>(value), make_node);
    }

    template <typename V>
    SFL_CONSTEXPR_20
    iterator insert_hint_equal(const_iterator hint, V&& value)
    {
        auto res = find_node_hint(hint, KeyOfValue()(value));
        make_node_functor make_node(*this);
        node_pointer x = make_node(std::forward<V>(value));
        insert_node_equal(x, res.bucket_index, res.pos);
        ++data_.size_;
        resize_buckets_and_rehash_if_overloaded();
        return iterator(x);
    }

    template <typename V>
    SFL_CONSTEXPR_20
    iterator insert_hint_unique(const_iterator hint, V&& value)
    {
        auto res = find_node_hint(hint, KeyOfValue()(value));
        if (res.pos != nullptr)
        {
            return iterator(res.pos);
        }
        else
        {
            make_node_functor make_node(*this);
            node_pointer x = make_node(std::forward<V>(value));
            insert_node_unique(x, res.bucket_index);
            ++data_.size_;
            resize_buckets_and_rehash_if_overloaded();
            return iterator(x);
        }
    }

    template <typename K, typename M>
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> insert_or_assign(K&& k, M&& obj)
    {
        auto res = find_node(k);
        if (res.pos != nullptr)
        {
            iterator it(res.pos);
            it->second = std::forward<M>(obj);
            return std::make_pair(it, false);
        }
        else
        {
            make_node_functor make_node(*this);
            node_pointer x = make_node
            (
                std::piecewise_construct,
                std::forward_as_tuple(std::forward<K>(k)),
                std::forward_as_tuple(std::forward<M>(obj))
            );
            insert_node_unique(x, res.bucket_index);
            ++data_.size_;
            resize_buckets_and_rehash_if_overloaded();
            return std::make_pair(iterator(x), true);
        }
    }

    template <typename K, typename M>
    SFL_CONSTEXPR_20
    iterator insert_or_assign_hint(const_iterator hint, K&& k, M&& obj)
    {
        auto res = find_node_hint(hint, k);
        if (res.pos != nullptr)
        {
            iterator it(res.pos);
            it->second = std::forward<M>(obj);
            return it;
        }
        else
        {
            make_node_functor make_node(*this);
            node_pointer x = make_node
            (
                std::piecewise_construct,
                std::forward_as_tuple(std::forward<K>(k)),
                std::forward_as_tuple(std::forward<M>(obj))
            );
            insert_node_unique(x, res.bucket_index);
            ++data_.size_;
            resize_buckets_and_rehash_if_overloaded();
            return iterator(x);
        }
    }

    template <typename K, typename... Args>
    SFL_CONSTEXPR_20
    std::pair<iterator, bool> try_emplace(K&& k, Args&&... args)
    {
        auto res = find_node(k);
        if (res.pos != nullptr)
        {
            return std::make_pair(iterator(res.pos), false);
        }
        else
        {
            make_node_functor make_node(*this);
            node_pointer x = make_node
            (
                std::piecewise_construct,
                std::forward_as_tuple(std::forward<K>(k)),
                std::forward_as_tuple(std::forward<Args>(args)...)
            );
            insert_node_unique(x, res.bucket_index);
            ++data_.size_;
            resize_buckets_and_rehash_if_overloaded();
            return std::make_pair(iterator(x), true);
        }
    }

    template <typename K, typename... Args>
    SFL_CONSTEXPR_20
    iterator try_emplace_hint(const_iterator hint, K&& k, Args&&... args)
    {
        auto res = find_node_hint(hint, k);
        if (res.pos != nullptr)
        {
            return iterator(res.pos);
        }
        else
        {
            make_node_functor make_node(*this);
            node_pointer x = make_node
            (
                std::piecewise_construct,
                std::forward_as_tuple(std::forward<K>(k)),
                std::forward_as_tuple(std::forward<Args>(args)...)
            );
            insert_node_unique(x, res.bucket_index);
            ++data_.size_;
            resize_buckets_and_rehash_if_overloaded();
            return iterator(x);
        }
    }

    SFL_CONSTEXPR_20
    iterator erase_equal(const_iterator pos)
    {
        base_node_pointer x = remove_node_equal(pos.node_);
        drop_node(static_cast<node_pointer>(pos.node_));
        --data_.size_;
        return iterator(x);
    }

    SFL_CONSTEXPR_20
    iterator erase_unique(const_iterator pos)
    {
        base_node_pointer x = remove_node_unique(pos.node_);
        drop_node(static_cast<node_pointer>(pos.node_));
        --data_.size_;
        return iterator(x);
    }

    SFL_CONSTEXPR_20
    iterator erase_equal(const_iterator first, const_iterator last)
    {
        while (first != last)
        {
            first = erase_equal(first);
        }
        return iterator(first.node_);
    }

    SFL_CONSTEXPR_20
    iterator erase_unique(const_iterator first, const_iterator last)
    {
        while (first != last)
        {
            first = erase_unique(first);
        }
        return iterator(first.node_);
    }

    template <typename K>
    SFL_CONSTEXPR_20
    size_type erase_key_equal(const K& k)
    {
        const auto er = equal_range(k);
        const auto count = std::distance(er.first, er.second);
        erase_equal(er.first, er.second);
        return count;
    }

    template <typename K>
    SFL_CONSTEXPR_20
    size_type erase_key_unique(const K& k)
    {
        base_node_pointer prev = find_node_before(k).pos;

        if (prev != nullptr)
        {
            base_node_pointer x = prev->next_;
            remove_node_unique(prev, x);
            drop_node(static_cast<node_pointer>(x));
            --data_.size_;
            return 1;
        }
        else
        {
            return 0;
        }
    }

    SFL_CONSTEXPR_20
    void swap(hash_table& other)
    {
        swap_impl(other);
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    template <typename K>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    std::pair<iterator, iterator> equal_range(const K& k)
    {
        base_node_pointer x = find_node(k).pos;
        base_node_pointer y = x;

        if (x != nullptr)
        {
            while (true)
            {
                y = y->next_;

                if (y == nullptr || static_cast<node_pointer>(y)->is_first_in_group())
                {
                    break;
                }
            }
        }

        return std::make_pair(iterator(x), iterator(y));
    }

    template <typename K>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    std::pair<const_iterator, const_iterator> equal_range(const K& k) const
    {
        base_node_pointer x = find_node(k).pos;
        base_node_pointer y = x;

        if (x != nullptr)
        {
            while (true)
            {
                y = y->next_;

                if (y == nullptr || static_cast<node_pointer>(y)->is_first_in_group())
                {
                    break;
                }
            }
        }

        return std::make_pair(const_iterator(x), const_iterator(y));
    }

    template <typename K>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    iterator find(const K& k)
    {
        return iterator(find_node(k).pos);
    }

    template <typename K>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_iterator find(const K& k) const
    {
        return const_iterator(find_node(k).pos);
    }

    template <typename K>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type count_equal(const K& k) const
    {
        const auto er = equal_range(k);
        return std::distance(er.first, er.second);
    }

    template <typename K>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type count_unique(const K& k) const
    {
        return find(k) != end() ? 1 : 0;
    }

    template <typename K>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    bool contains(const K& k) const
    {
        return find_node(k).pos != nullptr;
    }

    //
    // ---- BUCKET INTERFACE --------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    local_iterator begin(size_type n)
    {
        SFL_ASSERT(n < bucket_count());
        bucket_pointer bucket = data_.buckets_ + n;
        return bucket->next_ != nullptr
                ? local_iterator(bucket->next_->next_, n)
                : local_iterator(nullptr);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_local_iterator begin(size_type n) const
    {
        SFL_ASSERT(n < bucket_count());
        bucket_pointer bucket = data_.buckets_ + n;
        return bucket->next_ != nullptr
                ? const_local_iterator(bucket->next_->next_, n)
                : const_local_iterator(nullptr);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_local_iterator cbegin(size_type n) const
    {
        SFL_ASSERT(n < bucket_count());
        bucket_pointer bucket = data_.buckets_ + n;
        return bucket->next_ != nullptr
                ? const_local_iterator(bucket->next_->next_, n)
                : const_local_iterator(nullptr);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    local_iterator end(size_type n)
    {
        SFL_ASSERT(n < bucket_count());
        sfl::dtl::ignore_unused(n);
        return local_iterator(nullptr);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_local_iterator end(size_type n) const
    {
        SFL_ASSERT(n < bucket_count());
        sfl::dtl::ignore_unused(n);
        return const_local_iterator(nullptr);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    const_local_iterator cend(size_type n) const
    {
        SFL_ASSERT(n < bucket_count());
        sfl::dtl::ignore_unused(n);
        return const_local_iterator(nullptr);
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type bucket_count() const
    {
        return data_.get_bucket_count();
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type max_bucket_count() const
    {
        return std::max<size_type>
        (
            data_.get_max_bucket_count(),
            sfl::dtl::allocator_traits<bucket_allocator_type>::max_size(data_.ref_to_bucket_alloc())
        );
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type bucket_size(size_type n) const
    {
        SFL_ASSERT(n < bucket_count());
        return std::distance(begin(n), end(n));
    }

    template <typename K>
    SFL_NODISCARD
    SFL_CONSTEXPR_20
    size_type bucket(const K& k) const
    {
        const std::size_t hash = data_.ref_to_key_hash()(k);
        const std::size_t bucket_index = data_.calculate_bucket_index_for_hash(hash);
        return bucket_index;
    }

    //
    // ---- HASH POLICY -------------------------------------------------------
    //

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    float load_factor() const
    {
        SFL_ASSERT(bucket_count() != 0);
        return static_cast<float>(data_.size_) /
               static_cast<float>(data_.get_bucket_count());
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    float max_load_factor() const
    {
        return data_.get_max_load_factor();
    }

    SFL_CONSTEXPR_20
    void max_load_factor(float mlf)
    {
        data_.set_max_load_factor(mlf);
    }

    SFL_CONSTEXPR_20
    void rehash(size_type count)
    {
        const std::size_t new_bucket_count = data_.calculate_new_bucket_count
        (
            std::max<std::size_t>
            (
                count,
                sfl::dtl::floating_point_to_size_t
                (
                    sfl::dtl::floor
                    (
                        static_cast<double>(data_.size_) /
                        static_cast<double>(data_.get_max_load_factor())
                    )
                ) + 1
            )
        );

        if (new_bucket_count != data_.get_bucket_count())
        {
            resize_buckets_and_rehash(new_bucket_count);
        }
    }

    SFL_CONSTEXPR_20
    void reserve(size_type count)
    {
        rehash
        (
            sfl::dtl::floating_point_to_size_t
            (
                sfl::dtl::ceil
                (
                    static_cast<double>(count) /
                    static_cast<double>(data_.get_max_load_factor())
                )
            )
        );
    }

private:

    ///////////////////////////////////////////////////////////////////////////

    SFL_CONSTEXPR_20
    sfl::dtl::allocation_result<bucket_pointer, size_type> make_buckets(size_type n)
    {
        const auto res = sfl::dtl::allocator_traits<bucket_allocator_type>::allocate_at_least
        (
            data_.ref_to_bucket_alloc(),
            n
        );

        bucket_pointer curr = res.ptr;

        SFL_TRY
        {
            for (bucket_pointer end = res.ptr + res.count; curr != end; ++curr)
            {
                sfl::dtl::construct_at_a
                (
                    data_.ref_to_bucket_alloc(),
                    curr,
                    nullptr
                );
            }
        }
        SFL_CATCH (...)
        {
            while (curr-- != res.ptr)
            {
                sfl::dtl::destroy_at_a
                (
                    data_.ref_to_bucket_alloc(),
                    curr
                );
            }

            sfl::dtl::allocator_traits<bucket_allocator_type>::deallocate
            (
                data_.ref_to_bucket_alloc(),
                res.ptr,
                res.count
            );

            SFL_RETHROW;
        }

        return res;
    }

    SFL_CONSTEXPR_20
    void drop_buckets(bucket_pointer p, size_type n) noexcept
    {
        sfl::dtl::destroy_n_a
        (
            data_.ref_to_bucket_alloc(),
            p,
            n
        );

        sfl::dtl::allocator_traits<bucket_allocator_type>::deallocate
        (
            data_.ref_to_bucket_alloc(),
            p,
            n
        );
    }

    ///////////////////////////////////////////////////////////////////////////

    SFL_CONSTEXPR_20
    node_pointer allocate_node()
    {
        return sfl::dtl::allocator_traits<node_allocator_type>::allocate
        (
            data_.ref_to_node_alloc(),
            1
        );
    }

    SFL_CONSTEXPR_20
    void deallocate_node(node_pointer p) noexcept
    {
        sfl::dtl::allocator_traits<node_allocator_type>::deallocate
        (
            data_.ref_to_node_alloc(),
            p,
            1
        );
    }

    template <typename... Args>
    SFL_CONSTEXPR_20
    void construct_node(node_pointer p, Args&&... args)
    {
        sfl::dtl::construct_at_a(data_.ref_to_node_alloc(), p);

        SFL_TRY
        {
            sfl::dtl::construct_at_a
            (
                data_.ref_to_node_alloc(),
                p->value_.ptr(),
                std::forward<Args>(args)...
            );
        }
        SFL_CATCH (...)
        {
            sfl::dtl::destroy_at_a(data_.ref_to_node_alloc(), p);
            SFL_RETHROW;
        }
    }

    SFL_CONSTEXPR_20
    void destroy_node(node_pointer p) noexcept
    {
        sfl::dtl::destroy_at_a(data_.ref_to_node_alloc(), p->value_.ptr());
        sfl::dtl::destroy_at_a(data_.ref_to_node_alloc(), p);
    }

    class make_node_functor
    {
    private:

        hash_table& table_;

    public:

        SFL_CONSTEXPR_20
        make_node_functor(hash_table& table)
            : table_(table)
        {}

        template <typename... Args>
        SFL_CONSTEXPR_20
        node_pointer operator()(Args&&... args)
        {
            node_pointer p = table_.allocate_node();

            SFL_TRY
            {
                table_.construct_node(p, std::forward<Args>(args)...);
            }
            SFL_CATCH (...)
            {
                table_.deallocate_node(p);
                SFL_RETHROW;
            }

            return p;
        }
    };

    class make_node_with_recycling_functor
    {
    private:

        hash_table& table_;

        base_node_pointer x_;

    public:

        SFL_CONSTEXPR_20
        make_node_with_recycling_functor(hash_table& table)
            : table_(table)
            , x_(table.data_.head()->next_)
        {
            for (bucket_pointer x = table_.data_.buckets_, end = x + table_.data_.get_bucket_count(); x != end; ++x)
            {
                x->next_ = nullptr;
            }

            table.data_.head()->next_ = nullptr;
            table.data_.size_ = 0;
        }

        SFL_CONSTEXPR_20
        ~make_node_with_recycling_functor()
        {
            while (x_ != nullptr)
            {
                base_node_pointer y = x_->next_;
                table_.drop_node(static_cast<node_pointer>(x_));
                x_ = y;
            }
        }

        template <typename... Args>
        SFL_CONSTEXPR_20
        node_pointer operator()(Args&&... args)
        {
            node_pointer p = this->allocate_node();

            SFL_TRY
            {
                table_.construct_node(p, std::forward<Args>(args)...);
            }
            SFL_CATCH (...)
            {
                table_.deallocate_node(p);
                SFL_RETHROW;
            }

            return p;
        }

    private:

        SFL_CONSTEXPR_20
        node_pointer allocate_node()
        {
            if (x_ == nullptr)
            {
                return table_.allocate_node();
            }
            else
            {
                base_node_pointer n = x_;
                x_ = x_->next_;
                table_.destroy_node(static_cast<node_pointer>(n));
                return static_cast<node_pointer>(n);
            }
        }
    };

    SFL_CONSTEXPR_20
    void drop_node(node_pointer p) noexcept
    {
        destroy_node(p);
        deallocate_node(p);
    }

    ///////////////////////////////////////////////////////////////////////////

    SFL_CONSTEXPR_20
    static const Key& key_of(node_pointer x) noexcept
    {
        return KeyOfValue()(x->value_.ref());
    }

    SFL_CONSTEXPR_20
    static const Key& key_of(base_node_pointer x) noexcept
    {
        return KeyOfValue()(static_cast<node_pointer>(x)->value_.ref());
    }

    ///////////////////////////////////////////////////////////////////////////

    SFL_CONSTEXPR_20
    static std::size_t bucket_index_of(node_pointer x) noexcept
    {
        return x->get_bucket_index();
    }

    SFL_CONSTEXPR_20
    static std::size_t bucket_index_of(base_node_pointer x) noexcept
    {
        return static_cast<node_pointer>(x)->get_bucket_index();
    }

    ///////////////////////////////////////////////////////////////////////////

    struct find_node_result
    {
        base_node_pointer pos;
        std::size_t       bucket_index;
    };

    template <typename K>
    SFL_CONSTEXPR_20
    find_node_result find_node(const K& k) const
    {
        const std::size_t hash = data_.ref_to_key_hash()(k);

        const std::size_t bucket_index = data_.calculate_bucket_index_for_hash(hash);

        bucket_pointer bucket = data_.buckets_ + bucket_index;

        if (bucket->next_ != nullptr)
        {
            base_node_pointer x = bucket->next_->next_;

            while (x != nullptr && bucket_index_of(x) == bucket_index)
            {
                if (data_.ref_to_key_equal()(k, key_of(x)))
                {
                    return find_node_result{x, bucket_index};
                }

                x = x->next_;
            }
        }

        return find_node_result{nullptr, bucket_index};
    }

    template <typename K>
    SFL_CONSTEXPR_20
    find_node_result find_node_hint(const_iterator hint, const K& k) const
    {
        if (hint.node_ != nullptr && data_.ref_to_key_equal()(key_of(hint.node_), k))
        {
            return find_node_result{hint.node_, bucket_index_of(hint.node_)};
        }
        else
        {
            return find_node(k);
        }
    }

    template <typename K>
    SFL_CONSTEXPR_20
    find_node_result find_node_before(const K& k) const
    {
        const std::size_t hash = data_.ref_to_key_hash()(k);

        const std::size_t bucket_index = data_.calculate_bucket_index_for_hash(hash);

        bucket_pointer bucket = data_.buckets_ + bucket_index;

        if (bucket->next_ != nullptr)
        {
            base_node_pointer prev = bucket->next_;
            base_node_pointer x = prev->next_;

            while (x != nullptr && bucket_index_of(x) == bucket_index)
            {
                if (data_.ref_to_key_equal()(k, key_of(x)))
                {
                    return find_node_result{prev, bucket_index};
                }

                prev = x;
                x = prev->next_;
            }
        }

        return find_node_result{nullptr, bucket_index};
    }

    ///////////////////////////////////////////////////////////////////////////

    SFL_CONSTEXPR_20
    void insert_node_equal(node_pointer x, std::size_t bucket_index, base_node_pointer pos)
    {
        if (pos != nullptr)
        {
            x->set_bucket_index(bucket_index, std::false_type());

            if (pos->next_ != nullptr && bucket_index_of(pos->next_) != bucket_index_of(pos))
            {
                bucket_pointer other_bucket = data_.buckets_ + bucket_index_of(pos->next_);
                other_bucket->next_ = x;
            }

            x->next_ = pos->next_;
            pos->next_ = x;
        }
        else
        {
            x->set_bucket_index(bucket_index, std::true_type());

            bucket_pointer bucket = data_.buckets_ + bucket_index;

            if (bucket->next_ != nullptr)
            {
                x->next_ = bucket->next_->next_;
                bucket->next_->next_ = x;
            }
            else
            {
                if (data_.head()->next_ != nullptr)
                {
                    bucket_pointer other_bucket = data_.buckets_ + bucket_index_of(data_.head()->next_);
                    other_bucket->next_ = x;
                }

                bucket->next_ = data_.head();
                x->next_ = data_.head()->next_;
                data_.head()->next_ = x;
            }
        }
    }

    SFL_CONSTEXPR_20
    void insert_node_unique(node_pointer x, std::size_t bucket_index)
    {
        x->set_bucket_index(bucket_index, std::true_type());

        bucket_pointer bucket = data_.buckets_ + bucket_index;

        if (bucket->next_ != nullptr)
        {
            x->next_ = bucket->next_->next_;
            bucket->next_->next_ = x;
        }
        else
        {
            if (data_.head()->next_ != nullptr)
            {
                bucket_pointer other_bucket = data_.buckets_ + bucket_index_of(data_.head()->next_);
                other_bucket->next_ = x;
            }

            bucket->next_ = data_.head();
            x->next_ = data_.head()->next_;
            data_.head()->next_ = x;
        }
    }

    SFL_CONSTEXPR_20
    base_node_pointer remove_node_equal(base_node_pointer x)
    {
        bucket_pointer bucket = data_.buckets_ + bucket_index_of(x);

        SFL_ASSERT(bucket->next_ != nullptr);

        base_node_pointer prev = bucket->next_;

        while (prev->next_ != x)
        {
            prev = prev->next_;
        }

        base_node_pointer next = x->next_;

        // Is x last in bucket?
        if (next == nullptr || bucket_index_of(next) != bucket_index_of(x))
        {
            if (next != nullptr)
            {
                bucket_pointer next_bucket = data_.buckets_ + bucket_index_of(next);
                next_bucket->next_ = prev;
            }

            // Is x first in bucket?
            if (bucket->next_->next_ == x)
            {
                bucket->next_ = nullptr;
            }
        }

        if (static_cast<node_pointer>(x)->is_first_in_group() && next != nullptr)
        {
            static_cast<node_pointer>(next)->set_first_in_group();
        }

        prev->next_ = next;

        return next;
    }

    SFL_CONSTEXPR_20
    base_node_pointer remove_node_unique(base_node_pointer x)
    {
        bucket_pointer bucket = data_.buckets_ + bucket_index_of(x);

        SFL_ASSERT(bucket->next_ != nullptr);

        base_node_pointer prev = bucket->next_;

        while (prev->next_ != x)
        {
            prev = prev->next_;
        }

        base_node_pointer next = x->next_;

        // Is x last in bucket?
        if (next == nullptr || bucket_index_of(next) != bucket_index_of(x))
        {
            if (next != nullptr)
            {
                bucket_pointer next_bucket = data_.buckets_ + bucket_index_of(next);
                next_bucket->next_ = prev;
            }

            // Is x first in bucket?
            if (bucket->next_->next_ == x)
            {
                bucket->next_ = nullptr;
            }
        }

        prev->next_ = next;

        return next;
    }

    SFL_CONSTEXPR_20
    base_node_pointer remove_node_unique(base_node_pointer prev, base_node_pointer x)
    {
        SFL_ASSERT(x == prev->next_);

        bucket_pointer bucket = data_.buckets_ + bucket_index_of(x);

        SFL_ASSERT(bucket->next_ != nullptr);

        base_node_pointer next = x->next_;

        // Is x last in bucket?
        if (next == nullptr || bucket_index_of(next) != bucket_index_of(x))
        {
            if (next != nullptr)
            {
                bucket_pointer next_bucket = data_.buckets_ + bucket_index_of(next);
                next_bucket->next_ = prev;
            }

            // Is x first in bucket?
            if (bucket->next_->next_ == x)
            {
                bucket->next_ = nullptr;
            }
        }

        prev->next_ = next;

        return next;
    }

    ///////////////////////////////////////////////////////////////////////////

    SFL_CONSTEXPR_20
    void resize_buckets_and_rehash_if_overloaded()
    {
        if (data_.is_overloaded())
        {
            const std::size_t new_bucket_count = data_.calculate_new_bucket_count
            (
                sfl::dtl::floating_point_to_size_t
                (
                    sfl::dtl::floor
                    (
                        static_cast<double>(data_.size_) /
                        static_cast<double>(data_.get_max_load_factor())
                    )
                ) + 1
            );

            if (new_bucket_count != data_.get_bucket_count())
            {
                resize_buckets_and_rehash(new_bucket_count);
            }
        }
    }

    SFL_CONSTEXPR_20
    void resize_buckets_and_rehash(std::size_t new_bucket_count)
    {
        SFL_ASSERT(data_.check_bucket_count(new_bucket_count));
        const auto res = make_buckets(new_bucket_count);
        SFL_ASSERT(res.count == new_bucket_count);

        drop_buckets(data_.buckets_, data_.get_bucket_count());

        data_.buckets_ = res.ptr;
        data_.set_bucket_count(res.count);

        base_node_pointer prev = data_.head();

        SFL_TRY
        {
            while (prev->next_)
            {
                node_pointer x = static_cast<node_pointer>(prev->next_);

                const std::size_t hash = data_.ref_to_key_hash()(key_of(x));
                const std::size_t bucket_index = data_.calculate_bucket_index_for_hash(hash);

                x->set_bucket_index(bucket_index, std::true_type());

                while (x->next_ != nullptr)
                {
                    node_pointer next = static_cast<node_pointer>(x->next_);

                    if (next->is_first_in_group())
                    {
                        break;
                    }

                    x = next;
                    x->set_bucket_index(bucket_index, std::false_type());
                }

                bucket_pointer bucket = data_.buckets_ + bucket_index;

                if (bucket->next_ != nullptr)
                {
                    base_node_pointer next = x->next_;
                    x->next_ = bucket->next_->next_;
                    bucket->next_->next_ = prev->next_;
                    prev->next_ = next;
                }
                else
                {
                    bucket->next_ = prev;
                    prev = x;
                }
            }
        }
        SFL_CATCH (...)
        {
            base_node_pointer x = prev->next_;
            prev->next_ = nullptr;

            while (x != nullptr)
            {
                base_node_pointer y = x->next_;
                drop_node(static_cast<node_pointer>(x));
                --data_.size_;
                x = y;
            }

            SFL_RETHROW;
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    template <typename MakeNodeFunctor>
    SFL_CONSTEXPR_20
    void copy(base_node_pointer x, MakeNodeFunctor& make_node, sfl::dtl::hash_table_equal_t)
    {
        while (x != nullptr)
        {
            node_pointer n1 = make_node(static_cast<node_pointer>(x)->value_.ref());
            const std::size_t hash = data_.ref_to_key_hash()(key_of(n1));
            const std::size_t bucket_index = data_.calculate_bucket_index_for_hash(hash);
            insert_node_unique(n1, bucket_index);
            ++data_.size_;
            x = x->next_;

            while (x != nullptr && !static_cast<node_pointer>(x)->is_first_in_group())
            {
                node_pointer n2 = make_node(static_cast<node_pointer>(x)->value_.ref());
                insert_node_equal(n2, bucket_index, n1);
                ++data_.size_;
                n1 = n2;
                x = x->next_;
            }
        }
    }

    template <typename MakeNodeFunctor>
    SFL_CONSTEXPR_20
    void copy(base_node_pointer x, MakeNodeFunctor& make_node, sfl::dtl::hash_table_unique_t)
    {
        while (x != nullptr)
        {
            node_pointer n1 = make_node(static_cast<node_pointer>(x)->value_.ref());
            const std::size_t hash = data_.ref_to_key_hash()(key_of(n1));
            const std::size_t bucket_index = data_.calculate_bucket_index_for_hash(hash);
            insert_node_unique(n1, bucket_index);
            ++data_.size_;
            x = x->next_;
        }
    }

    template <typename MakeNodeFunctor>
    SFL_CONSTEXPR_20
    void move(base_node_pointer x, MakeNodeFunctor& make_node, sfl::dtl::hash_table_equal_t)
    {
        while (x != nullptr)
        {
            node_pointer n1 = make_node(std::move(static_cast<node_pointer>(x)->value_.ref()));
            const std::size_t hash = data_.ref_to_key_hash()(key_of(n1));
            const std::size_t bucket_index = data_.calculate_bucket_index_for_hash(hash);
            insert_node_unique(n1, bucket_index);
            ++data_.size_;
            x = x->next_;

            while (x != nullptr && !static_cast<node_pointer>(x)->is_first_in_group())
            {
                node_pointer n2 = make_node(std::move(static_cast<node_pointer>(x)->value_.ref()));
                insert_node_equal(n2, bucket_index, n1);
                ++data_.size_;
                n1 = n2;
                x = x->next_;
            }
        }
    }

    template <typename MakeNodeFunctor>
    SFL_CONSTEXPR_20
    void move(base_node_pointer x, MakeNodeFunctor& make_node, sfl::dtl::hash_table_unique_t)
    {
        while (x != nullptr)
        {
            node_pointer n1 = make_node(std::move(static_cast<node_pointer>(x)->value_.ref()));
            const std::size_t hash = data_.ref_to_key_hash()(key_of(n1));
            const std::size_t bucket_index = data_.calculate_bucket_index_for_hash(hash);
            insert_node_unique(n1, bucket_index);
            ++data_.size_;
            x = x->next_;
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    SFL_CONSTEXPR_20
    void initialize_empty(size_type initial_bucket_count)
    {
        SFL_ASSERT(data_.check_bucket_count(initial_bucket_count));
        const auto res = make_buckets(initial_bucket_count);
        SFL_ASSERT(res.count == initial_bucket_count);
        data_.buckets_ = res.ptr;
        data_.set_bucket_count(res.count);
    }

    ///////////////////////////////////////////////////////////////////////////

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void initialize_copy(const hash_table& other, EqualOrUniqueTag equal_or_unique_tag)
    {
        SFL_ASSERT(data_.check_bucket_count(other.data_.get_bucket_count()));
        const auto res = make_buckets(other.data_.get_bucket_count());
        SFL_ASSERT(res.count == other.data_.get_bucket_count());
        data_.buckets_ = res.ptr;
        data_.set_bucket_count(res.count);
        data_.set_max_load_factor(other.data_.get_max_load_factor());

        SFL_TRY
        {
            make_node_functor make_node(*this);
            copy(other.data_.head()->next_, make_node, equal_or_unique_tag);
        }
        SFL_CATCH (...)
        {
            for (base_node_pointer x = data_.head()->next_; x != nullptr; )
            {
                base_node_pointer y = x->next_;
                drop_node(static_cast<node_pointer>(x));
                x = y;
            }

            drop_buckets(data_.buckets_, data_.get_bucket_count());

            SFL_RETHROW;
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void initialize_move(hash_table& other, EqualOrUniqueTag equal_or_unique_tag)
    {
        // PRECONDITION
        static_assert
        (
            std::is_same
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::is_partially_propagable::type,
                typename sfl::dtl::allocator_traits<bucket_allocator_type>::is_partially_propagable::type
            >::value,
            "Both node allocator and bucket allocator should have the same `is_partially_propagable` type"
        );

        // PRECONDITION
        static_assert
        (
            std::is_same
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::is_always_equal::type,
                typename sfl::dtl::allocator_traits<bucket_allocator_type>::is_always_equal::type
            >::value,
            "Both node allocator and bucket allocator should have the same `is_always_equal` type"
        );

        // PRECONDITION
        SFL_ASSERT
        (
            (
                data_.ref_to_node_alloc() == other.data_.ref_to_node_alloc() &&
                data_.ref_to_bucket_alloc() == other.data_.ref_to_bucket_alloc()
            )
            ||
            (
                data_.ref_to_node_alloc() != other.data_.ref_to_node_alloc() &&
                data_.ref_to_bucket_alloc() != other.data_.ref_to_bucket_alloc()
            )
        );

        initialize_move
        (
            other,
            equal_or_unique_tag,
            typename sfl::dtl::allocator_traits<node_allocator_type>::is_partially_propagable()
        );
    }

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void initialize_move(hash_table& other, EqualOrUniqueTag equal_or_unique_tag, std::true_type)
    {
        SFL_ASSERT(data_.check_bucket_count(other.data_.get_bucket_count()));
        const auto res = make_buckets(other.data_.get_bucket_count());
        SFL_ASSERT(res.count == other.data_.get_bucket_count());
        data_.buckets_ = res.ptr;
        data_.set_bucket_count(res.count);
        data_.set_max_load_factor(other.data_.get_max_load_factor());

        SFL_TRY
        {
            make_node_functor make_node(*this);
            move(other.data_.head()->next_, make_node, equal_or_unique_tag);
        }
        SFL_CATCH (...)
        {
            for (base_node_pointer x = data_.head()->next_; x != nullptr; )
            {
                base_node_pointer y = x->next_;
                drop_node(static_cast<node_pointer>(x));
                x = y;
            }

            drop_buckets(data_.buckets_, data_.get_bucket_count());

            SFL_RETHROW;
        }
    }

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void initialize_move(hash_table& other, EqualOrUniqueTag equal_or_unique_tag, std::false_type)
    {
        initialize_move
        (
            other,
            equal_or_unique_tag,
            std::false_type(),
            typename sfl::dtl::allocator_traits<node_allocator_type>::is_always_equal()
        );
    }

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void initialize_move(hash_table& other, EqualOrUniqueTag equal_or_unique_tag, std::false_type, std::true_type)
    {
        sfl::dtl::ignore_unused(equal_or_unique_tag);

        // Make new buckets before stealing other data.
        // If this operation throws, this and other remain in valid state.
        const auto res = other.make_buckets(other.data_.calculate_new_bucket_count(1));

        // Steal other data (noexcept)
        data_.head()->next_ = other.data_.head()->next_;
        data_.size_ = other.data_.size_;
        data_.buckets_ = other.data_.buckets_;
        data_.set_bucket_count(other.data_.get_bucket_count());
        data_.set_max_load_factor(other.data_.get_max_load_factor());

        // Fix bucket pointer of the first node in the list (noexcept)
        if (data_.head()->next_ != nullptr)
        {
            bucket_pointer first_bucket = data_.buckets_ + bucket_index_of(data_.head()->next_);
            first_bucket->next_ = data_.head();
        }

        // Set other data (noexcept)
        other.data_.head()->next_ = nullptr;
        other.data_.size_ = 0;
        other.data_.buckets_ = res.ptr;
        other.data_.set_bucket_count(res.count);
    }

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void initialize_move(hash_table& other, EqualOrUniqueTag equal_or_unique_tag, std::false_type, std::false_type)
    {
        if (data_.ref_to_node_alloc() == other.data_.ref_to_node_alloc())
        {
            initialize_move(other, equal_or_unique_tag, std::false_type(), std::true_type());
        }
        else
        {
            initialize_move(other, equal_or_unique_tag, std::true_type());
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void assign_copy_impl(const hash_table& other, EqualOrUniqueTag equal_or_unique_tag)
    {
        // PRECONDITION
        static_assert
        (
            std::is_same
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_copy_assignment::type,
                typename sfl::dtl::allocator_traits<bucket_allocator_type>::propagate_on_container_copy_assignment::type
            >::value,
            "Both node allocator and bucket allocator should have the same `propagate_on_container_copy_assignment` type"
        );

        // PRECONDITION
        static_assert
        (
            std::is_same
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::is_always_equal::type,
                typename sfl::dtl::allocator_traits<bucket_allocator_type>::is_always_equal::type
            >::value,
            "Both node allocator and bucket allocator should have the same `is_always_equal` type"
        );

        // PRECONDITION
        SFL_ASSERT
        (
            (
                data_.ref_to_node_alloc()   == other.data_.ref_to_node_alloc() &&
                data_.ref_to_bucket_alloc() == other.data_.ref_to_bucket_alloc()
            )
            ||
            (
                data_.ref_to_node_alloc()   != other.data_.ref_to_node_alloc() &&
                data_.ref_to_bucket_alloc() != other.data_.ref_to_bucket_alloc()
            )
        );

        if (this != &other)
        {
            if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_copy_assignment::value)
            {
                if
                (
                    data_.ref_to_node_alloc() != other.data_.ref_to_node_alloc()
                    ||
                    other.data_.size_ > data_.get_max_load()
                )
                {
                    // Make new buckets for this using other allocator.
                    // May throw exception. No effects if thrown.
                    SFL_ASSERT(data_.check_bucket_count(other.data_.get_bucket_count()));
                    const auto res = const_cast<hash_table&>(other).make_buckets(other.data_.get_bucket_count());
                    SFL_ASSERT(res.count == other.data_.get_bucket_count());

                    // Copy functions. May throw exception.
                    SFL_TRY
                    {
                        data_.assign_copy_functions(other.data_);
                    }
                    SFL_CATCH (...)
                    {
                        const_cast<hash_table&>(other).drop_buckets(res.ptr, res.count);
                        SFL_RETHROW;
                    }

                    // Drop nodes (noexcept)
                    for (base_node_pointer x = data_.head()->next_; x != nullptr; )
                    {
                        base_node_pointer y = x->next_;
                        drop_node(static_cast<node_pointer>(x));
                        x = y;
                    }

                    // Drop buckets (noexcept)
                    drop_buckets(data_.buckets_, data_.get_bucket_count());

                    // Reset header and size (noexcept)
                    data_.head()->next_ = nullptr;
                    data_.size_ = 0;

                    // Set new buckets (noexcept)
                    data_.buckets_ = res.ptr;
                    data_.set_bucket_count(res.count);
                }
                else
                {
                    data_.assign_copy_functions(other.data_);
                }

                // Copy allocators (noexcept)
                data_.ref_to_node_alloc() = other.data_.ref_to_node_alloc();
                data_.ref_to_bucket_alloc() = other.data_.ref_to_bucket_alloc();
            }
            else
            {
                if (other.data_.size_ > data_.get_max_load())
                {
                    // Make new buckets for this.
                    // May throw exception. No effects if thrown.
                    SFL_ASSERT(data_.check_bucket_count(other.data_.get_bucket_count()));
                    const auto res = make_buckets(other.data_.get_bucket_count());
                    SFL_ASSERT(res.count == other.data_.get_bucket_count());

                    // Copy functions. May throw exception.
                    SFL_TRY
                    {
                        data_.assign_copy_functions(other.data_);
                    }
                    SFL_CATCH (...)
                    {
                        drop_buckets(res.ptr, res.count);
                        SFL_RETHROW;
                    }

                    // Drop nodes (noexcept)
                    for (base_node_pointer x = data_.head()->next_; x != nullptr; )
                    {
                        base_node_pointer y = x->next_;
                        drop_node(static_cast<node_pointer>(x));
                        x = y;
                    }

                    // Drop buckets (noexcept)
                    drop_buckets(data_.buckets_, data_.get_bucket_count());

                    // Reset header and size (noexcept)
                    data_.head()->next_ = nullptr;
                    data_.size_ = 0;

                    // Set new buckets (noexcept)
                    data_.buckets_ = res.ptr;
                    data_.set_bucket_count(res.count);
                }
                else
                {
                    data_.assign_copy_functions(other.data_);
                }
            }

            // Copy max load factor (noexcept)
            data_.set_max_load_factor(other.data_.get_max_load_factor());

            // Copy elements one-by-one from other to this. May throw exception.
            make_node_with_recycling_functor make_node(*this);
            copy(other.data_.head()->next_, make_node, equal_or_unique_tag);
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void assign_move_impl(hash_table& other, EqualOrUniqueTag equal_or_unique_tag)
    {
        // PRECONDITION
        static_assert
        (
            std::is_same
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::is_partially_propagable::type,
                typename sfl::dtl::allocator_traits<bucket_allocator_type>::is_partially_propagable::type
            >::value,
            "Both node allocator and bucket allocator should have the same `is_partially_propagable` type"
        );

        // PRECONDITION
        static_assert
        (
            std::is_same
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_move_assignment::type,
                typename sfl::dtl::allocator_traits<bucket_allocator_type>::propagate_on_container_move_assignment::type
            >::value,
            "Both node allocator and bucket allocator should have the same `propagate_on_container_move_assignment` type"
        );

        // PRECONDITION
        static_assert
        (
            std::is_same
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::is_always_equal::type,
                typename sfl::dtl::allocator_traits<bucket_allocator_type>::is_always_equal::type
            >::value,
            "Both node allocator and bucket allocator should have the same `is_always_equal` type"
        );

        // PRECONDITION
        SFL_ASSERT
        (
            (
                data_.ref_to_node_alloc()   == other.data_.ref_to_node_alloc() &&
                data_.ref_to_bucket_alloc() == other.data_.ref_to_bucket_alloc()
            )
            ||
            (
                data_.ref_to_node_alloc()   != other.data_.ref_to_node_alloc() &&
                data_.ref_to_bucket_alloc() != other.data_.ref_to_bucket_alloc()
            )
        );

        assign_move_impl
        (
            other,
            equal_or_unique_tag,
            typename sfl::dtl::allocator_traits<node_allocator_type>::is_partially_propagable()
        );
    }

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void assign_move_impl(hash_table& other, EqualOrUniqueTag equal_or_unique_tag, std::true_type)
    {
        if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_move_assignment::value)
        {
            if
            (
                data_.ref_to_node_alloc() != other.data_.ref_to_node_alloc()
                ||
                other.data_.size_ > data_.get_max_load()
            )
            {
                // Make new buckets for this using other allocator.
                // May throw exception. No effects if thrown.
                SFL_ASSERT(data_.check_bucket_count(other.data_.get_bucket_count()));
                const auto res = const_cast<hash_table&>(other).make_buckets(other.data_.get_bucket_count());
                SFL_ASSERT(res.count == other.data_.get_bucket_count());

                // Move functions. May throw exception.
                SFL_TRY
                {
                    data_.assign_move_functions(other.data_);
                }
                SFL_CATCH (...)
                {
                    const_cast<hash_table&>(other).drop_buckets(res.ptr, res.count);
                    SFL_RETHROW;
                }

                // Drop nodes (noexcept)
                for (base_node_pointer x = data_.head()->next_; x != nullptr; )
                {
                    base_node_pointer y = x->next_;
                    drop_node(static_cast<node_pointer>(x));
                    x = y;
                }

                // Drop buckets (noexcept)
                drop_buckets(data_.buckets_, data_.get_bucket_count());

                // Reset header and size (noexcept)
                data_.head()->next_ = nullptr;
                data_.size_ = 0;

                // Set new buckets (noexcept)
                data_.buckets_ = res.ptr;
                data_.set_bucket_count(res.count);
            }
            else
            {
                data_.assign_move_functions(other.data_);
            }

            // Move allocators (noexcept)
            data_.ref_to_node_alloc() = std::move(other.data_.ref_to_node_alloc());
            data_.ref_to_bucket_alloc() = std::move(other.data_.ref_to_bucket_alloc());
        }
        else
        {
            if (other.data_.size_ > data_.get_max_load())
            {
                // Make new buckets for this.
                // May throw exception. No effects if thrown.
                SFL_ASSERT(data_.check_bucket_count(other.data_.get_bucket_count()));
                const auto res = make_buckets(other.data_.get_bucket_count());
                SFL_ASSERT(res.count == other.data_.get_bucket_count());

                // Move functions. May throw exception.
                SFL_TRY
                {
                    data_.assign_move_functions(other.data_);
                }
                SFL_CATCH (...)
                {
                    drop_buckets(res.ptr, res.count);
                    SFL_RETHROW;
                }

                // Drop nodes (noexcept)
                for (base_node_pointer x = data_.head()->next_; x != nullptr; )
                {
                    base_node_pointer y = x->next_;
                    drop_node(static_cast<node_pointer>(x));
                    x = y;
                }

                // Drop buckets (noexcept)
                drop_buckets(data_.buckets_, data_.get_bucket_count());

                // Reset header and size (noexcept)
                data_.head()->next_ = nullptr;
                data_.size_ = 0;

                // Set new buckets (noexcept)
                data_.buckets_ = res.ptr;
                data_.set_bucket_count(res.count);
            }
            else
            {
                data_.assign_move_functions(other.data_);
            }
        }

        // Copy max load factor (noexcept)
        data_.set_max_load_factor(other.data_.get_max_load_factor());

        // Move elements one-by-one from other to this. May throw exception.
        make_node_with_recycling_functor make_node(*this);
        move(other.data_.head()->next_, make_node, equal_or_unique_tag);
    }

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void assign_move_impl(hash_table& other, EqualOrUniqueTag equal_or_unique_tag, std::false_type)
    {
        assign_move_impl
        (
            other,
            equal_or_unique_tag,
            std::false_type(),
            typename sfl::dtl::disjunction
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_move_assignment,
                typename sfl::dtl::allocator_traits<node_allocator_type>::is_always_equal
            >()
        );
    }

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void assign_move_impl(hash_table& other, EqualOrUniqueTag equal_or_unique_tag, std::false_type, std::true_type)
    {
        sfl::dtl::ignore_unused(equal_or_unique_tag);

        // Make new buckets for other before stealing data from other.
        // May throw exception. No effects if thrown.
        const auto res = other.make_buckets(other.data_.calculate_new_bucket_count(1));

        // Move functions. May throw exception.
        SFL_TRY
        {
            data_.assign_move_functions(other.data_);
        }
        SFL_CATCH (...)
        {
            other.drop_buckets(res.ptr, res.count);
            SFL_RETHROW;
        }

        // Drop nodes (noexcept)
        for (base_node_pointer x = data_.head()->next_; x != nullptr; )
        {
            base_node_pointer y = x->next_;
            drop_node(static_cast<node_pointer>(x));
            x = y;
        }

        // Drop buckets (noexcept)
        drop_buckets(data_.buckets_, data_.get_bucket_count());

        // Move allocators (noexcept)
        if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_move_assignment::value)
        {
            data_.ref_to_node_alloc() = std::move(other.data_.ref_to_node_alloc());
            data_.ref_to_bucket_alloc() = std::move(other.data_.ref_to_bucket_alloc());
        }

        // Steal data (noexcept)
        data_.head()->next_ = other.data_.head()->next_;
        data_.size_ = other.data_.size_;
        data_.buckets_ = other.data_.buckets_;
        data_.set_bucket_count(other.data_.get_bucket_count());
        data_.set_max_load_factor(other.data_.get_max_load_factor());

        // Fix bucket pointer of the first node in the list (noexcept)
        if (data_.head()->next_ != nullptr)
        {
            bucket_pointer first_bucket = data_.buckets_ + bucket_index_of(data_.head()->next_);
            first_bucket->next_ = data_.head();
        }

        // Set other data (noexcept)
        other.data_.head()->next_ = nullptr;
        other.data_.size_ = 0;
        other.data_.buckets_ = res.ptr;
        other.data_.set_bucket_count(res.count);
    }

    template <typename EqualOrUniqueTag>
    SFL_CONSTEXPR_20
    void assign_move_impl(hash_table& other, EqualOrUniqueTag equal_or_unique_tag, std::false_type, std::false_type)
    {
        if (data_.ref_to_node_alloc() == other.data_.ref_to_node_alloc())
        {
            assign_move_impl(other, equal_or_unique_tag, std::false_type(), std::true_type());
        }
        else
        {
            assign_move_impl(other, equal_or_unique_tag, std::true_type());
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    SFL_CONSTEXPR_20
    void swap_impl(hash_table& other)
    {
        // PRECONDITION
        static_assert
        (
            std::is_same
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::is_partially_propagable::type,
                typename sfl::dtl::allocator_traits<bucket_allocator_type>::is_partially_propagable::type
            >::value,
            "Both node allocator and bucket allocator should have the same `is_partially_propagable` type"
        );

        // PRECONDITION
        static_assert
        (
            std::is_same
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::type,
                typename sfl::dtl::allocator_traits<bucket_allocator_type>::propagate_on_container_swap::type
            >::value,
            "Both node allocator and bucket allocator should have the same `propagate_on_container_swap` type"
        );

        // PRECONDITION
        static_assert
        (
            std::is_same
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::is_always_equal::type,
                typename sfl::dtl::allocator_traits<bucket_allocator_type>::is_always_equal::type
            >::value,
            "Both node allocator and bucket allocator should have the same `is_always_equal` type"
        );

        // PRECONDITION
        SFL_ASSERT
        (
            (
                data_.ref_to_node_alloc() == other.data_.ref_to_node_alloc() &&
                data_.ref_to_bucket_alloc() == other.data_.ref_to_bucket_alloc()
            )
            ||
            (
                data_.ref_to_node_alloc() != other.data_.ref_to_node_alloc() &&
                data_.ref_to_bucket_alloc() != other.data_.ref_to_bucket_alloc()
            )
        );

        swap_impl
        (
            other,
            typename sfl::dtl::allocator_traits<node_allocator_type>::is_partially_propagable()
        );
    }

    SFL_CONSTEXPR_20
    void swap_impl(hash_table& other, std::true_type)
    {
        SFL_ASSERT(this->size() < this->max_size());
        SFL_ASSERT(other.size() < other.max_size());

        using std::swap;

        // Swap functions. May throw exception. No effects if thrown.
        data_.swap_functions(other.data_);

        // Steal data (noexcept)
        base_node_pointer old_this = this->data_.head()->next_;
        base_node_pointer old_other = other.data_.head()->next_;

        // Reset header (noexcept)
        this->data_.head()->next_ = nullptr;
        other.data_.head()->next_ = nullptr;

        // Reset size (noexcept)
        this->data_.size_ = 0;
        other.data_.size_ = 0;

        // Reset buckets (noexcept)
        for (bucket_pointer x = this->data_.buckets_, end = x + this->data_.get_bucket_count(); x != end; ++x)
        {
            x->next_ = nullptr;
        }
        for (bucket_pointer x = other.data_.buckets_, end = x + other.data_.get_bucket_count(); x != end; ++x)
        {
            x->next_ = nullptr;
        }

        // Swap allocators (noexcept)
        if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value)
        {
            swap(this->data_.ref_to_node_alloc(), other.data_.ref_to_node_alloc());
            swap(this->data_.ref_to_bucket_alloc(), other.data_.ref_to_bucket_alloc());
        }

        // Swap buckets (noexcept)
        if
        (
            !sfl::dtl::allocator_traits<bucket_allocator_type>::is_storage_unpropagable
            (
                this->data_.ref_to_bucket_alloc(),
                this->data_.buckets_
            )
            &&
            !sfl::dtl::allocator_traits<bucket_allocator_type>::is_storage_unpropagable
            (
                other.data_.ref_to_bucket_alloc(),
                other.data_.buckets_
            )
            &&
            (
                sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value
                ||
                this->data_.ref_to_node_alloc() == other.data_.ref_to_node_alloc()
            )
        )
        {
            swap(this->data_.buckets_, other.data_.buckets_);
        }

        // Swap max load factor (noexcept)
        data_.swap_max_load_factor(other.data_);

        // Swap nodes one-by-one. May throw exception.
        SFL_TRY
        {
            while (true)
            {
                bool done = true;

                if (old_this != nullptr)
                {
                    done = false;

                    if
                    (
                        sfl::dtl::allocator_traits<node_allocator_type>::is_storage_unpropagable
                        (
                            this->data_.ref_to_node_alloc(),
                            static_cast<node_pointer>(old_this)
                        )
                        ||
                        (
                            !sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value
                            &&
                            this->data_.ref_to_node_alloc() != other.data_.ref_to_node_alloc()
                        )
                    )
                    {
                        other.insert_equal(std::move(static_cast<node_pointer>(old_this)->value_.ref())); // may throw
                        base_node_pointer next = old_this->next_;
                        this->drop_node(static_cast<node_pointer>(old_this));
                        old_this = next;
                    }
                    else
                    {
                        base_node_pointer next = old_this->next_;
                        const auto res = other.find_node(key_of(old_this)); // may throw
                        other.insert_node_equal(static_cast<node_pointer>(old_this), res.bucket_index, res.pos);
                        ++other.data_.size_;
                        other.resize_buckets_and_rehash_if_overloaded();
                        old_this = next;
                    }
                }

                if (old_other != nullptr)
                {
                    done = false;

                    if
                    (
                        sfl::dtl::allocator_traits<node_allocator_type>::is_storage_unpropagable
                        (
                            other.data_.ref_to_node_alloc(),
                            static_cast<node_pointer>(old_other)
                        )
                        ||
                        (
                            !sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value
                            &&
                            other.data_.ref_to_node_alloc() != this->data_.ref_to_node_alloc()
                        )
                    )
                    {
                        this->insert_equal(std::move(static_cast<node_pointer>(old_other)->value_.ref())); // may throw
                        base_node_pointer next = old_other->next_;
                        other.drop_node(static_cast<node_pointer>(old_other));
                        old_other = next;
                    }
                    else
                    {
                        base_node_pointer next = old_other->next_;
                        const auto res = this->find_node(key_of(old_other)); // may throw
                        this->insert_node_equal(static_cast<node_pointer>(old_other), res.bucket_index, res.pos);
                        ++this->data_.size_;
                        this->resize_buckets_and_rehash_if_overloaded();
                        old_other = next;
                    }
                }

                if (done)
                {
                    break;
                }
            }
        }
        SFL_CATCH (...)
        {
            while (old_this != nullptr)
            {
                base_node_pointer next = old_this->next_;

                if
                (
                    sfl::dtl::allocator_traits<node_allocator_type>::is_storage_unpropagable
                    (
                        this->data_.ref_to_node_alloc(),
                        static_cast<node_pointer>(old_this)
                    )
                )
                {
                    this->drop_node(static_cast<node_pointer>(old_this));
                }
                else
                {
                    if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value)
                    {
                        other.drop_node(static_cast<node_pointer>(old_this));
                    }
                    else
                    {
                        this->drop_node(static_cast<node_pointer>(old_this));
                    }
                }

                old_this = next;
            }

            while (old_other != nullptr)
            {
                base_node_pointer next = old_other->next_;

                if
                (
                    sfl::dtl::allocator_traits<node_allocator_type>::is_storage_unpropagable
                    (
                        other.data_.ref_to_node_alloc(),
                        static_cast<node_pointer>(old_other)
                    )
                )
                {
                    other.drop_node(static_cast<node_pointer>(old_other));
                }
                else
                {
                    if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value)
                    {
                        this->drop_node(static_cast<node_pointer>(old_other));
                    }
                    else
                    {
                        other.drop_node(static_cast<node_pointer>(old_other));
                    }
                }

                old_other = next;
            }

            SFL_RETHROW;
        }
    }

    SFL_CONSTEXPR_20
    void swap_impl(hash_table& other, std::false_type)
    {
        swap_impl
        (
            other,
            std::false_type(),
            typename sfl::dtl::disjunction
            <
                typename sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap,
                typename sfl::dtl::allocator_traits<node_allocator_type>::is_always_equal
            >()
        );
    }

    SFL_CONSTEXPR_20
    void swap_impl(hash_table& other, std::false_type, std::true_type)
    {
        using std::swap;

        // Swap functions. May throw exception. No effects if thrown.
        data_.swap_functions(other.data_);

        // Swap allocators (noexcept)
        if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value)
        {
            swap(data_.ref_to_node_alloc(), other.data_.ref_to_node_alloc());
            swap(data_.ref_to_bucket_alloc(), other.data_.ref_to_bucket_alloc());
        }

        // Swap data (noexcept)
        swap(data_.head()->next_, other.data_.head()->next_);
        swap(data_.size_, other.data_.size_);
        swap(data_.buckets_, other.data_.buckets_);
        data_.swap_bucket_count(other.data_);
        data_.swap_max_load_factor(other.data_);

        // Fix bucket pointer of the first node in the list (noexcept)
        if (data_.head()->next_ != nullptr)
        {
            bucket_pointer first_bucket = data_.buckets_ + bucket_index_of(data_.head()->next_);
            first_bucket->next_ = data_.head();
        }

        // Fix bucket pointer of the first node in the list (noexcept)
        if (other.data_.head()->next_ != nullptr)
        {
            bucket_pointer first_bucket = other.data_.buckets_ + bucket_index_of(other.data_.head()->next_);
            first_bucket->next_ = other.data_.head();
        }
    }

    SFL_CONSTEXPR_20
    void swap_impl(hash_table& other, std::false_type, std::false_type)
    {
        if (data_.ref_to_node_alloc() == other.data_.ref_to_node_alloc())
        {
            swap_impl(other, std::false_type(), std::true_type());
        }
        else
        {
            swap_impl(other, std::true_type());
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    SFL_CONSTEXPR_20
    bool verify() const
    {
        for (auto it = begin(); it != end(); ++it)
        {
            if (bucket_index_of(it.node_) != bucket(key_of(it.node_)))
            {
                return false;
            }

            auto er = equal_range(key_of(it.node_));

            for (auto it2 = er.first; it2 != er.second; ++it2)
            {
                if (!data_.ref_to_key_equal()(key_of(it.node_), key_of(it2.node_)))
                {
                    return false;
                }
            }

            auto next = std::next(it);

            if (next != end())
            {
                if (static_cast<node_pointer>(next.node_)->is_first_in_group())
                {
                    if (data_.ref_to_key_equal()(key_of(it.node_), key_of(next.node_)))
                    {
                        return false;
                    }
                }
                else
                {
                    if (!data_.ref_to_key_equal()(key_of(it.node_), key_of(next.node_)))
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// NON-MEMBER FUNCTIONS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5, typename TP6, typename TP7, typename TP8, typename TP9>
SFL_NODISCARD
SFL_CONSTEXPR_20
bool operator==
(
    const hash_table<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9>& x,
    const hash_table<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9>& y
)
{
    return x.size() == y.size() && std::is_permutation(x.begin(), x.end(), y.begin());
}

template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5, typename TP6, typename TP7, typename TP8, typename TP9>
SFL_NODISCARD
SFL_CONSTEXPR_20
bool operator!=
(
    const hash_table<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9>& x,
    const hash_table<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9>& y
)
{
    return !(x == y);
}

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_HASH_TABLE_HPP_INCLUDED
