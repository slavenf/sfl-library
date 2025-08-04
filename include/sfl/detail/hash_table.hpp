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
#include <sfl/detail/math/is_prime.hpp>
#include <sfl/detail/memory/construct_at.hpp>
#include <sfl/detail/memory/construct_at_a.hpp>
#include <sfl/detail/memory/destroy_at.hpp>
#include <sfl/detail/memory/destroy_at_a.hpp>
#include <sfl/detail/memory/destroy_n_a.hpp>
#include <sfl/detail/memory/to_address.hpp>
#include <sfl/detail/memory/uninitialized_default_construct_n_a.hpp>
#include <sfl/detail/type_traits/conjunction.hpp>
#include <sfl/detail/type_traits/disjunction.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/is_input_iterator.hpp>
#include <sfl/detail/type_traits/is_nothrow_swappable.hpp>
#include <sfl/detail/utility/compressed_pair.hpp>
#include <sfl/detail/utility/floating_point_to_size_t.hpp>
#include <sfl/detail/utility/optional_value.hpp>
#include <sfl/detail/utility/scope_guard.hpp>
#include <sfl/detail/allocator_traits.hpp>
#include <sfl/detail/cpp.hpp>

#include <algorithm>    // max, min
#include <cmath>        // ceil, floor
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

    hash_table_base_node() noexcept
        : next_()
    {}

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

    // Use this if node is first in group.
    void set_bucket_index(std::size_t bucket_index, std::true_type) noexcept
    {
        bucket_info_ = bucket_index;
    }

    // Use this if node is not first in group.
    void set_bucket_index(std::size_t bucket_index, std::false_type) noexcept
    {
        bucket_info_ = bucket_index | ~mask;
    }

    std::size_t get_bucket_index() const noexcept
    {
        return bucket_info_ & mask;
    }

    bool is_first_in_group() const noexcept
    {
        return !(bucket_info_ & ~mask);
    }

    void set_first_in_group()
    {
        bucket_info_ = bucket_info_ & mask;
    }

    #if 0 // Not used, but leave it here just in case
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
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename KeyHash, typename KeyEqual>
class hash_table_functions
{
private:

    unsigned char status_;

    union
    {
        sfl::dtl::compressed_pair<KeyHash, KeyEqual> functions_[2];
    };

public:

    hash_table_functions()
        : status_(0)
    {
        sfl::dtl::construct_at
        (
            std::addressof(functions_[status_]),
            sfl::dtl::compressed_pair_default_init_t(),
            sfl::dtl::compressed_pair_default_init_t()
        );
    }

    hash_table_functions(const KeyHash& hash)
        : status_(0)
    {
        sfl::dtl::construct_at
        (
            std::addressof(functions_[status_]),
            hash,
            sfl::dtl::compressed_pair_default_init_t()
        );
    }

    hash_table_functions(const KeyHash& hash, const KeyEqual& equal)
        : status_(0)
    {
        sfl::dtl::construct_at
        (
            std::addressof(functions_[status_]),
            hash,
            equal
        );
    }

    ~hash_table_functions()
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        sfl::dtl::destroy_at(std::addressof(functions_[status_]));
    }

    KeyHash& ref_to_key_hash()
    {
        return functions_[status_].first();
    }

    const KeyHash& ref_to_key_hash() const
    {
        return functions_[status_].first();
    }

    KeyEqual& ref_to_key_equal()
    {
        return functions_[status_].second();
    }

    const KeyEqual& ref_to_key_equal() const
    {
        return functions_[status_].second();
    }

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

    void priv_assign_copy(const hash_table_functions& other, std::true_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        functions_[status_] = other.functions_[other.status_];
    }

    void priv_assign_copy(const hash_table_functions& other, std::false_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        // Construct a new pair of functions.
        sfl::dtl::construct_at
        (
            std::addressof(functions_[status_ ^ 1]),
            other.functions_[other.status_ & 1]
        );
        status_ |= 2;

        // Destroy the old pair of functions.
        sfl::dtl::destroy_at
        (
            std::addressof(functions_[status_] & 1)
        );
        status_ ^= 3;
    }

    void priv_assign_move(hash_table_functions& other, std::true_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        functions_[status_] = std::move(other.functions_[other.status_]);
    }

    void priv_assign_move(hash_table_functions& other, std::false_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        // Construct a new pair of functions.
        // We intentionally avoid using std::move for the second argument.
        // Using std::move could cause issues if the operation throws an exception.
        // For instance, the first element of the (compressed) pair might be moved
        // successfully, but the second element could throw during its move.
        // This would leave the pair in an inconsistent state: the first element
        // would be moved from the source, while the second would remain intact.
        sfl::dtl::construct_at
        (
            std::addressof(functions_[status_ ^ 1]),
            other.functions_[other.status_ & 1]
        );
        status_ |= 2;

        // Destroy the old pair of functions.
        sfl::dtl::destroy_at
        (
            std::addressof(functions_[status_] & 1)
        );
        status_ ^= 3;
    }

    void priv_swap(hash_table_functions& other, std::true_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        using std::swap;

        swap(functions_[status_], other.functions_[other.status_]);
    }

    void priv_swap(hash_table_functions& other, std::false_type)
    {
        SFL_ASSERT(status_ == 0 || status_ == 1);
        SFL_ASSERT(other.status_ == 0 || other.status_ == 1);

        // Construct a new pair of functions in this
        sfl::dtl::construct_at
        (
            std::addressof(this->functions_[this->status_ ^ 1]),
            other.functions_[other.status_ & 1]
        );
        this->status_ |= 2;

        // Construct a new pair of functions in other
        SFL_TRY
        {
            sfl::dtl::construct_at
            (
                std::addressof(other.functions_[other.status_ ^ 1]),
                this->functions_[this->status_ & 1]
            );
            other.status_ |= 2;
        }
        SFL_CATCH (...)
        {
            this->status_ &= 1;

            sfl::dtl::destroy_at
            (
                std::addressof(this->functions_[this->status_ ^ 1])
            );

            SFL_RETHROW;
        }

        // Destroy the old pair of functions in this
        sfl::dtl::destroy_at
        (
            std::addressof(this->functions_[this->status_ & 1])
        );
        this->status_ ^= 3;

        // Destroy the old pair of functions in other
        sfl::dtl::destroy_at
        (
            std::addressof(other.functions_[other.status_ & 1])
        );
        other.status_ ^= 3;
    }
};

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

public:

    static bool check_bucket_count(std::size_t bucket_count)
    {
        return sfl::dtl::has_single_bit(bucket_count);
    }

    static std::size_t get_max_bucket_count()
    {
        return ~(std::numeric_limits<std::size_t>::max() >> 1) >> 1;
    }

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

    std::size_t get_bucket_count() const
    {
        return bucket_count_;
    }

    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(check_bucket_count(bucket_count));
        bucket_count_ = bucket_count;
        bucket_count_log2_ = sfl::dtl::bit_log2(bucket_count);
    }

    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return priv_calculate_bucket_index_for_hash<std::size_t>(hash);
    }

    void swap(hash_table_dynamic_pow2_bucket_count_policy& other)
    {
        using std::swap;
        swap(bucket_count_, other.bucket_count_);
        swap(bucket_count_log2_, other.bucket_count_log2_);
    }

private:

    // Fibonnaci hashing is used:
    // https://en.wikipedia.org/wiki/Hash_function#Fibonacci_hashing
    // https://probablydance.com/2018/06/16/fibonacci-hashing-the-optimization-that-the-world-forgot-or-a-better-alternative-to-integer-modulo/

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 64>* = nullptr>
    std::size_t priv_calculate_bucket_index_for_hash(std::size_t hash) const
    {
        static constexpr std::size_t a = 0x9e3779b97f4a7c15u;
        static constexpr int w = 64;
        const std::size_t bucket_index = (a * hash) >> (w - bucket_count_log2_);
        SFL_ASSERT(bucket_index < bucket_count_);
        return bucket_index;
    }

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 32>* = nullptr>
    std::size_t priv_calculate_bucket_index_for_hash(std::size_t hash) const
    {
        static constexpr std::size_t a = 0x9e3779b9u;
        static constexpr int w = 32;
        const std::size_t bucket_index = (a * hash) >> (w - bucket_count_log2_);
        SFL_ASSERT(bucket_index < bucket_count_);
        return bucket_index;
    }

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 16>* = nullptr>
    std::size_t priv_calculate_bucket_index_for_hash(std::size_t hash) const
    {
        static constexpr std::size_t a = 0x9e37u;
        static constexpr int w = 16;
        const std::size_t bucket_index = (a * hash) >> (w - bucket_count_log2_);
        SFL_ASSERT(bucket_index < bucket_count_);
        return bucket_index;
    }
};

template <std::size_t StaticBucketCount>
class hash_table_static_pow2_bucket_count_policy
{
    static_assert
    (
        sfl::dtl::has_single_bit(StaticBucketCount),
        "StaticBucketCount must be power of 2"
    );

public:

    static bool check_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
        return true;
    }

    static std::size_t get_max_bucket_count()
    {
        return StaticBucketCount;
    }

    static std::size_t calculate_new_bucket_count(std::size_t min_bucket_count)
    {
        SFL_ASSERT(min_bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(min_bucket_count);
        return StaticBucketCount;
    }

    std::size_t get_bucket_count() const
    {
        return StaticBucketCount;
    }

    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
    }

    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return priv_calculate_bucket_index_for_hash<std::size_t>(hash);
    }

    void swap(hash_table_static_pow2_bucket_count_policy& other)
    {
        sfl::dtl::ignore_unused(other);
    }

private:

    // Fibonnaci hashing is used:
    // https://en.wikipedia.org/wiki/Hash_function#Fibonacci_hashing
    // https://probablydance.com/2018/06/16/fibonacci-hashing-the-optimization-that-the-world-forgot-or-a-better-alternative-to-integer-modulo/

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 64>* = nullptr>
    std::size_t priv_calculate_bucket_index_for_hash(std::size_t hash) const
    {
        static constexpr std::size_t a = 0x9e3779b97f4a7c15u;
        static constexpr int w = 64;
        static constexpr int m = sfl::dtl::bit_log2(StaticBucketCount);
        const std::size_t bucket_index = (a * hash) >> (w - m);
        SFL_ASSERT(bucket_index < StaticBucketCount);
        return bucket_index;
    }

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 32>* = nullptr>
    std::size_t priv_calculate_bucket_index_for_hash(std::size_t hash) const
    {
        static constexpr std::size_t a = 0x9e3779b9u;
        static constexpr int w = 32;
        static constexpr int m = sfl::dtl::bit_log2(StaticBucketCount);
        const std::size_t bucket_index = (a * hash) >> (w - m);
        SFL_ASSERT(bucket_index < StaticBucketCount);
        return bucket_index;
    }

    template <typename SizeType,
              sfl::dtl::enable_if_t<std::numeric_limits<SizeType>::digits == 16>* = nullptr>
    std::size_t priv_calculate_bucket_index_for_hash(std::size_t hash) const
    {
        static constexpr std::size_t a = 0x9e37u;
        static constexpr int w = 16;
        static constexpr int m = sfl::dtl::bit_log2(StaticBucketCount);
        const std::size_t bucket_index = (a * hash) >> (w - m);
        SFL_ASSERT(bucket_index < StaticBucketCount);
        return bucket_index;
    }
};

template <>
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

class hash_table_dynamic_prime_bucket_count_policy
{
private:

    std::size_t bucket_count_;

public:

    static bool check_bucket_count(std::size_t bucket_count)
    {
        return sfl::dtl::is_prime(bucket_count);
    }

    static std::size_t get_max_bucket_count()
    {
        return sfl::dtl::hash_table_prime_list<>::list[sfl::dtl::hash_table_prime_list<>::size - 1];
    }

    static std::size_t calculate_new_bucket_count(std::size_t min_bucket_count)
    {
        return sfl::dtl::hash_table_prime_list<>::ceil(min_bucket_count);
    }

    std::size_t get_bucket_count() const
    {
        return bucket_count_;
    }

    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(check_bucket_count(bucket_count));
        bucket_count_ = bucket_count;
    }

    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return hash % bucket_count_;
    }

    void swap(hash_table_dynamic_prime_bucket_count_policy& other)
    {
        using std::swap;
        swap(bucket_count_, other.bucket_count_);
    }
};

template <std::size_t StaticBucketCount>
class hash_table_static_prime_bucket_count_policy
{
    static_assert
    (
        sfl::dtl::is_prime(StaticBucketCount),
        "StaticBucketCount must be prime number"
    );

public:

    static bool check_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
        return true;
    }

    static std::size_t get_max_bucket_count()
    {
        return StaticBucketCount;
    }

    static std::size_t calculate_new_bucket_count(std::size_t min_bucket_count)
    {
        SFL_ASSERT(min_bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(min_bucket_count);
        return StaticBucketCount;
    }

    std::size_t get_bucket_count() const
    {
        return StaticBucketCount;
    }

    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
    }

    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return hash % StaticBucketCount;
    }

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

    static bool check_bucket_count(std::size_t bucket_count)
    {
        return bucket_count > 0;
    }

    static std::size_t get_max_bucket_count()
    {
        return sfl::dtl::hash_table_prime_list<>::list[sfl::dtl::hash_table_prime_list<>::size - 1];
    }

    static std::size_t calculate_new_bucket_count(std::size_t min_bucket_count)
    {
        return sfl::dtl::hash_table_prime_list<>::ceil(min_bucket_count);
    }

    std::size_t get_bucket_count() const
    {
        return bucket_count_;
    }

    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(check_bucket_count(bucket_count));
        bucket_count_ = bucket_count;
    }

    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return hash % bucket_count_;
    }

    void swap(hash_table_dynamic_basic_bucket_count_policy& other)
    {
        using std::swap;
        swap(bucket_count_, other.bucket_count_);
    }
};

template <std::size_t StaticBucketCount>
class hash_table_static_basic_bucket_count_policy
{
    static_assert
    (
        StaticBucketCount > 0,
        "StaticBucketCount must be greater than zero"
    );

public:

    static bool check_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
        return true;
    }

    static std::size_t get_max_bucket_count()
    {
        return StaticBucketCount;
    }

    static std::size_t calculate_new_bucket_count(std::size_t min_bucket_count)
    {
        SFL_ASSERT(min_bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(min_bucket_count);
        return StaticBucketCount;
    }

    std::size_t get_bucket_count() const
    {
        return StaticBucketCount;
    }

    void set_bucket_count(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count == StaticBucketCount);
        sfl::dtl::ignore_unused(bucket_count);
    }

    std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
    {
        return hash % StaticBucketCount;
    }

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

    hash_table_standard_max_load_policy()
        : max_load_factor_(1.0f)
        , max_load_(0)
    {}

    void recalculate_max_load(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count != 0);
        max_load_ = sfl::dtl::floating_point_to_size_t
        (
            std::ceil
            (
                static_cast<double>(max_load_factor_) *
                static_cast<double>(bucket_count)
            )
        );
    }

    void set_max_load_factor(float max_load_factor)
    {
        static constexpr float smallest_max_load_factor = 0.001f;
        max_load_factor_ = std::max(smallest_max_load_factor, max_load_factor);
    }

    float get_max_load_factor() const
    {
        return max_load_factor_;
    }

    std::size_t get_max_load() const
    {
        return max_load_;
    }

    bool is_overloaded(std::size_t size) const
    {
        return size > max_load_;
    }

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

    void recalculate_max_load(std::size_t bucket_count)
    {
        SFL_ASSERT(bucket_count != 0);
        sfl::dtl::ignore_unused(bucket_count);
    }

    void set_max_load_factor(float max_load_factor)
    {
        sfl::dtl::ignore_unused(max_load_factor);
    }

    float get_max_load_factor() const
    {
        return 1.0f;
    }

    std::size_t get_max_load() const
    {
        return std::numeric_limits<std::size_t>::max();
    }

    bool is_overloaded(std::size_t size) const
    {
        sfl::dtl::ignore_unused(size);
        return false;
    }

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
           typename MaxLoadPolicy,
           typename UpperLevelContainer >
class hash_table
{
    #ifdef SFL_TEST_HASH_TABLE
    template <int>
    friend void ::test_hash_table();
    #endif

    friend UpperLevelContainer;

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

        friend UpperLevelContainer;

    public:

        using difference_type   = std::ptrdiff_t;
        using value_type        = Value;
        using pointer           = Value*;
        using reference         = Value&;
        using iterator_category = std::forward_iterator_tag;

    private:

        base_node_pointer node_;

    private:

        explicit iterator(base_node_pointer x) noexcept
            : node_(x)
        {}

    public:

        // Default constructor
        iterator() noexcept
        {}

        // Copy constructor
        iterator(const iterator& other) noexcept
            : node_(other.node_)
        {}

        // Copy assignment operator
        iterator& operator=(const iterator& other) noexcept
        {
            node_ = other.node_;
            return *this;
        }

        SFL_NODISCARD
        reference operator*() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ref();
        }

        SFL_NODISCARD
        pointer operator->() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ptr();
        }

        iterator& operator++() noexcept
        {
            node_ = node_->next_;
            return *this;
        }

        iterator operator++(int) noexcept
        {
            auto temp = *this;
            node_ = node_->next_;
            return temp;
        }

        SFL_NODISCARD
        friend bool operator==(const iterator& x, const iterator& y) noexcept
        {
            return x.node_ == y.node_;
        }

        SFL_NODISCARD
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

        friend UpperLevelContainer;

    public:

        using difference_type   = std::ptrdiff_t;
        using value_type        = Value;
        using pointer           = const Value*;
        using reference         = const Value&;
        using iterator_category = std::forward_iterator_tag;

    private:

        base_node_pointer node_;

    private:

        explicit const_iterator(base_node_pointer x) noexcept
            : node_(x)
        {}

    public:

        // Default constructor
        const_iterator() noexcept
        {}

        // Copy constructor
        const_iterator(const const_iterator& other) noexcept
            : node_(other.node_)
        {}

        // Converting constructor (from iterator to const_iterator)
        const_iterator(const iterator& other) noexcept
            : node_(other.node_)
        {}

        // Copy assignment operator
        const_iterator& operator=(const const_iterator& other) noexcept
        {
            node_ = other.node_;
            return *this;
        }

        SFL_NODISCARD
        reference operator*() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ref();
        }

        SFL_NODISCARD
        pointer operator->() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ptr();
        }

        const_iterator& operator++() noexcept
        {
            node_ = node_->next_;
            return *this;
        }

        const_iterator operator++(int) noexcept
        {
            auto temp = *this;
            node_ = node_->next_;
            return temp;
        }

        SFL_NODISCARD
        friend bool operator==(const const_iterator& x, const const_iterator& y) noexcept
        {
            return x.node_ == y.node_;
        }

        SFL_NODISCARD
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

        friend UpperLevelContainer;

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

        explicit local_iterator(base_node_pointer x) noexcept
            : node_(x)
        {}

        explicit local_iterator(base_node_pointer x, std::size_t bucket_index) noexcept
            : node_(x)
            , bucket_index_(bucket_index)
        {}

    public:

        // Default constructor
        local_iterator() noexcept
        {}

        // Copy constructor
        local_iterator(const local_iterator& other) noexcept
            : node_(other.node_)
            , bucket_index_(other.bucket_index_)
        {}

        // Copy assignment operator
        local_iterator& operator=(const local_iterator& other) noexcept
        {
            node_ = other.node_;
            bucket_index_ = other.bucket_index_;
            return *this;
        }

        SFL_NODISCARD
        reference operator*() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ref();
        }

        SFL_NODISCARD
        pointer operator->() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ptr();
        }

        local_iterator& operator++() noexcept
        {
            node_ = node_->next_;
            if (node_ != nullptr && hash_table::bucket_index_of(node_) != bucket_index_)
            {
                node_ = nullptr;
            }
            return *this;
        }

        local_iterator operator++(int) noexcept
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        SFL_NODISCARD
        friend bool operator==(const local_iterator& x, const local_iterator& y) noexcept
        {
            return x.node_ == y.node_;
        }

        SFL_NODISCARD
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

        friend UpperLevelContainer;

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

        explicit const_local_iterator(base_node_pointer x) noexcept
            : node_(x)
        {}

        explicit const_local_iterator(base_node_pointer x, std::size_t bucket_index) noexcept
            : node_(x)
            , bucket_index_(bucket_index)
        {}

    public:

        // Default constructor
        const_local_iterator() noexcept
        {}

        // Copy constructor
        const_local_iterator(const const_local_iterator& other) noexcept
            : node_(other.node_)
            , bucket_index_(other.bucket_index_)
        {}

        // Converting constructor (from local_iterator to const_local_iterator)
        const_local_iterator(const local_iterator& other) noexcept
            : node_(other.node_)
            , bucket_index_(other.bucket_index_)
        {}

        // Copy assignment operator
        const_local_iterator& operator=(const const_local_iterator& other) noexcept
        {
            node_ = other.node_;
            bucket_index_ = other.bucket_index_;
            return *this;
        }

        SFL_NODISCARD
        reference operator*() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ref();
        }

        SFL_NODISCARD
        pointer operator->() const noexcept
        {
            return static_cast<node_pointer>(node_)->value_.ptr();
        }

        const_local_iterator& operator++() noexcept
        {
            node_ = node_->next_;
            if (node_ != nullptr && hash_table::bucket_index_of(node_) != bucket_index_)
            {
                node_ = nullptr;
            }
            return *this;
        }

        const_local_iterator operator++(int) noexcept
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        SFL_NODISCARD
        friend bool operator==(const const_local_iterator& x, const const_local_iterator& y) noexcept
        {
            return x.node_ == y.node_;
        }

        SFL_NODISCARD
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
        base_node_pointer head()
        {
            return std::pointer_traits<base_node_pointer>::pointer_to(head_);
        }

        // Number of nodes in linked list
        std::size_t size_;

        // Bucket array
        bucket_pointer buckets_;

    public:

        data()
            : head_(nullptr)
            , size_(0)
        {}

        template <typename Alloc>
        data(const Alloc& alloc)
            : node_allocator_type(alloc)
            , bucket_allocator_type(alloc)
            , head_(nullptr)
            , size_(0)
        {}

        data(const key_hash& hash)
            : functions(hash)
            , head_(nullptr)
            , size_(0)
        {}

        template <typename Alloc>
        data(const key_hash& hash, const Alloc& alloc)
            : functions(hash)
            , node_allocator_type(alloc)
            , bucket_allocator_type(alloc)
            , head_(nullptr)
            , size_(0)
        {}

        data(const key_hash& hash, const key_equal& equal)
            : functions(hash, equal)
            , head_(nullptr)
            , size_(0)
        {}

        template <typename Alloc>
        data(const key_hash& hash, const key_equal& equal, const Alloc& alloc)
            : functions(hash, equal)
            , node_allocator_type(alloc)
            , bucket_allocator_type(alloc)
            , head_(nullptr)
            , size_(0)
        {}

        data(const data& other)
            : functions(other.ref_to_key_hash(), other.ref_to_key_equal())
            , node_allocator_type(sfl::dtl::allocator_traits<node_allocator_type>::select_on_container_copy_construction(other.ref_to_node_alloc()))
            , bucket_allocator_type(sfl::dtl::allocator_traits<bucket_allocator_type>::select_on_container_copy_construction(other.ref_to_bucket_alloc()))
            , head_(nullptr)
            , size_(0)
        {}

        template <typename Alloc>
        data(const data& other, const Alloc& alloc)
            : functions(other.ref_to_key_hash(), other.ref_to_key_equal())
            , node_allocator_type(alloc)
            , bucket_allocator_type(alloc)
            , head_(nullptr)
            , size_(0)
        {}

        data(data&& other)
            : functions(std::move(other.ref_to_key_hash()), std::move(other.ref_to_key_equal()))
            , node_allocator_type(std::move(other.ref_to_node_alloc()))
            , bucket_allocator_type(std::move(other.ref_to_bucket_alloc()))
            , head_(nullptr)
            , size_(0)
        {}

        template <typename Alloc>
        data(data&& other, const Alloc& alloc)
            : functions(std::move(other.ref_to_key_hash()), std::move(other.ref_to_key_equal()))
            , node_allocator_type(alloc)
            , bucket_allocator_type(alloc)
            , head_(nullptr)
            , size_(0)
        {}

        ~data()
        {}

        ///////////////////////////////////////////////////////////////////////

        key_hash& ref_to_key_hash()
        {
            return static_cast<functions*>(this)->ref_to_key_hash();
        }

        const key_hash& ref_to_key_hash() const
        {
            return static_cast<const functions*>(this)->ref_to_key_hash();
        }

        key_equal& ref_to_key_equal()
        {
            return static_cast<functions*>(this)->ref_to_key_equal();
        }

        const key_equal& ref_to_key_equal() const
        {
            return static_cast<const functions*>(this)->ref_to_key_equal();
        }

        node_allocator_type& ref_to_node_alloc()
        {
            return *this;
        }

        const node_allocator_type& ref_to_node_alloc() const
        {
            return *this;
        }

        bucket_allocator_type& ref_to_bucket_alloc()
        {
            return *this;
        }

        const bucket_allocator_type& ref_to_bucket_alloc() const
        {
            return *this;
        }

        ///////////////////////////////////////////////////////////////////////

        bool check_bucket_count(std::size_t n) const
        {
            return bucket_count_policy::check_bucket_count(n);
        }

        std::size_t calculate_new_bucket_count(std::size_t min_bucket_count) const
        {
            return bucket_count_policy::calculate_new_bucket_count(min_bucket_count);
        }

        std::size_t calculate_bucket_index_for_hash(std::size_t hash) const
        {
            return bucket_count_policy::calculate_bucket_index_for_hash(hash);
        }

        void set_bucket_count(std::size_t n)
        {
            bucket_count_policy::set_bucket_count(n);
            max_load_policy::recalculate_max_load(n);
        }

        std::size_t get_bucket_count() const
        {
            return bucket_count_policy::get_bucket_count();
        }

        std::size_t get_max_bucket_count() const
        {
            return bucket_count_policy::get_max_bucket_count();
        }

        float get_max_load_factor() const
        {
            return max_load_policy::get_max_load_factor();
        }

        void set_max_load_factor(float mlf)
        {
            max_load_policy::set_max_load_factor(mlf);
            max_load_policy::recalculate_max_load(get_bucket_count());
        }

        std::size_t get_max_load() const
        {
            return max_load_policy::get_max_load();
        }

        bool is_overloaded() const
        {
            return max_load_policy::is_overloaded(size_);
        }

        ///////////////////////////////////////////////////////////////////////

        void assign_copy_functions(const data& other)
        {
            functions::assign_copy(other);
        }

        ///////////////////////////////////////////////////////////////////////

        void assign_move_functions(data& other)
        {
            functions::assign_move(other);
        }

        ///////////////////////////////////////////////////////////////////////

        void swap_functions(data& other)
        {
            functions::swap(other);
        }

        void swap_bucket_count(data& other)
        {
            bucket_count_policy::swap(other);
        }

        void swap_max_load_factor(data& other)
        {
            max_load_policy::swap(other);
        }
    };

    mutable data data_;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    hash_table() = delete;

    hash_table(size_type initial_bucket_count)
        : data_()
    {
        initialize_empty(initial_bucket_count);
    }

    template <typename Alloc>
    hash_table(size_type initial_bucket_count, const Alloc& alloc)
        : data_(alloc)
    {
        initialize_empty(initial_bucket_count);
    }

    hash_table(size_type initial_bucket_count, const key_hash& hash)
        : data_(hash)
    {
        initialize_empty(initial_bucket_count);
    }

    template <typename Alloc>
    hash_table(size_type initial_bucket_count, const key_hash& hash, const Alloc& alloc)
        : data_(hash, alloc)
    {
        initialize_empty(initial_bucket_count);
    }

    hash_table(size_type initial_bucket_count, const key_hash& hash, const key_equal& equal)
        : data_(hash, equal)
    {
        initialize_empty(initial_bucket_count);
    }

    template <typename Alloc>
    hash_table(size_type initial_bucket_count, const key_hash& hash, const key_equal& equal, const Alloc& alloc)
        : data_(hash, equal, alloc)
    {
        initialize_empty(initial_bucket_count);
    }

    template <typename EqualOrUniqueTag>
    hash_table(const hash_table& other, EqualOrUniqueTag equal_or_unique_tag)
        : data_(other.data_)
    {
        initialize_copy(other, equal_or_unique_tag);
    }

    template <typename EqualOrUniqueTag, typename Alloc>
    hash_table(const hash_table& other, EqualOrUniqueTag equal_or_unique_tag, const Alloc& alloc)
        : data_(other.data_, alloc)
    {
        initialize_copy(other, equal_or_unique_tag);
    }

    template <typename EqualOrUniqueTag>
    hash_table(hash_table&& other, EqualOrUniqueTag equal_or_unique_tag)
        : data_(std::move(other.data_))
    {
        initialize_move(other, equal_or_unique_tag);
    }

    template <typename EqualOrUniqueTag, typename Alloc>
    hash_table(hash_table&& other, EqualOrUniqueTag equal_or_unique_tag, const Alloc& alloc)
        : data_(std::move(other.data_), alloc)
    {
        initialize_move(other, equal_or_unique_tag);
    }

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
    void assign_copy(const hash_table& other, EqualOrUniqueTag equal_or_unique_tag)
    {
        assign_copy_impl(other, equal_or_unique_tag);
    }

    template <typename EqualOrUniqueTag>
    void assign_move(hash_table& other, EqualOrUniqueTag equal_or_unique_tag)
    {
        assign_move_impl(other, equal_or_unique_tag);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
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
    // ---- ITERATORS ---------------------------------------------------------
    //

    SFL_NODISCARD
    iterator begin() noexcept
    {
        return iterator(data_.head()->next_);
    }

    SFL_NODISCARD
    const_iterator begin() const noexcept
    {
        return const_iterator(data_.head()->next_);
    }

    SFL_NODISCARD
    const_iterator cbegin() const noexcept
    {
        return const_iterator(data_.head()->next_);
    }

    SFL_NODISCARD
    iterator end() noexcept
    {
        return iterator(nullptr);
    }

    SFL_NODISCARD
    const_iterator end() const noexcept
    {
        return const_iterator(nullptr);
    }

    SFL_NODISCARD
    const_iterator cend() const noexcept
    {
        return const_iterator(nullptr);
    }

    //
    // ---- SIZE AND CAPACITY -------------------------------------------------
    //

    SFL_NODISCARD
    bool empty() const noexcept
    {
        return data_.size_ == 0;
    }

    SFL_NODISCARD
    size_type size() const noexcept
    {
        return data_.size_;
    }

    SFL_NODISCARD
    size_type max_size() const noexcept
    {
        return sfl::dtl::allocator_traits<node_allocator_type>::max_size(data_.ref_to_node_alloc());
    }

    //
    // ---- MODIFIERS ---------------------------------------------------------
    //

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
    iterator insert_equal(V&& value)
    {
        make_node_functor make_node(*this);
        return insert_equal(std::forward<V>(value), make_node);
    }

    template <typename V>
    std::pair<iterator, bool> insert_unique(V&& value)
    {
        make_node_functor make_node(*this);
        return insert_unique(std::forward<V>(value), make_node);
    }

    template <typename V>
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

    iterator erase_equal(const_iterator pos)
    {
        base_node_pointer x = remove_node_equal(pos.node_);
        drop_node(static_cast<node_pointer>(pos.node_));
        --data_.size_;
        return iterator(x);
    }

    iterator erase_unique(const_iterator pos)
    {
        base_node_pointer x = remove_node_unique(pos.node_);
        drop_node(static_cast<node_pointer>(pos.node_));
        --data_.size_;
        return iterator(x);
    }

    iterator erase_equal(const_iterator first, const_iterator last)
    {
        while (first != last)
        {
            first = erase_equal(first);
        }
        return iterator(first.node_);
    }

    iterator erase_unique(const_iterator first, const_iterator last)
    {
        while (first != last)
        {
            first = erase_unique(first);
        }
        return iterator(first.node_);
    }

    template <typename K>
    size_type erase_key_equal(const K& k)
    {
        const auto er = equal_range(k);
        const auto count = std::distance(er.first, er.second);
        erase_equal(er.first, er.second);
        return count;
    }

    template <typename K>
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

    void swap(hash_table& other)
    {
        swap_impl(other);
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    template <typename K>
    SFL_NODISCARD
    std::pair<iterator, iterator> equal_range(const K& k) noexcept
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
    std::pair<const_iterator, const_iterator> equal_range(const K& k) const noexcept
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
    iterator find(const K& k) noexcept
    {
        return iterator(find_node(k).pos);
    }

    template <typename K>
    SFL_NODISCARD
    const_iterator find(const K& k) const noexcept
    {
        return const_iterator(find_node(k).pos);
    }

    template <typename K>
    SFL_NODISCARD
    size_type count(const K& k) const noexcept
    {
        const auto er = equal_range(k);
        return std::distance(er.first, er.second);
    }

    template <typename K>
    SFL_NODISCARD
    bool contains(const K& k) const noexcept
    {
        return find_node(k).pos != nullptr;
    }

    //
    // ---- BUCKET INTERFACE --------------------------------------------------
    //

    SFL_NODISCARD
    local_iterator begin(size_type n)
    {
        SFL_ASSERT(n < bucket_count());
        bucket_pointer bucket = data_.buckets_ + n;
        return bucket->next_ != nullptr
                ? local_iterator(bucket->next_->next_, n)
                : local_iterator(nullptr);
    }

    SFL_NODISCARD
    const_local_iterator begin(size_type n) const
    {
        SFL_ASSERT(n < bucket_count());
        bucket_pointer bucket = data_.buckets_ + n;
        return bucket->next_ != nullptr
                ? const_local_iterator(bucket->next_->next_, n)
                : const_local_iterator(nullptr);
    }

    SFL_NODISCARD
    const_local_iterator cbegin(size_type n) const
    {
        SFL_ASSERT(n < bucket_count());
        bucket_pointer bucket = data_.buckets_ + n;
        return bucket->next_ != nullptr
                ? const_local_iterator(bucket->next_->next_, n)
                : const_local_iterator(nullptr);
    }

    SFL_NODISCARD
    local_iterator end(size_type n)
    {
        SFL_ASSERT(n < bucket_count());
        sfl::dtl::ignore_unused(n);
        return local_iterator(nullptr);
    }

    SFL_NODISCARD
    const_local_iterator end(size_type n) const
    {
        SFL_ASSERT(n < bucket_count());
        sfl::dtl::ignore_unused(n);
        return const_local_iterator(nullptr);
    }

    SFL_NODISCARD
    const_local_iterator cend(size_type n) const
    {
        SFL_ASSERT(n < bucket_count());
        sfl::dtl::ignore_unused(n);
        return const_local_iterator(nullptr);
    }

    SFL_NODISCARD
    size_type bucket_count() const
    {
        return data_.get_bucket_count();
    }

    SFL_NODISCARD
    size_type max_bucket_count() const
    {
        return std::max<size_type>
        (
            data_.get_max_bucket_count(),
            sfl::dtl::allocator_traits<bucket_allocator_type>::max_size(data_.ref_to_bucket_alloc())
        );
    }

    SFL_NODISCARD
    size_type bucket_size(size_type n) const
    {
        SFL_ASSERT(n < bucket_count());
        return std::distance(begin(n), end(n));
    }

    template <typename K>
    SFL_NODISCARD
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
    float load_factor() const
    {
        SFL_ASSERT(bucket_count() != 0);
        return static_cast<float>(data_.size_) /
               static_cast<float>(data_.get_bucket_count());
    }

    SFL_NODISCARD
    float max_load_factor() const
    {
        return data_.get_max_load_factor();
    }

    void max_load_factor(float mlf)
    {
        data_.set_max_load_factor(mlf);
    }

    void rehash(size_type count)
    {
        const std::size_t new_bucket_count = data_.calculate_new_bucket_count
        (
            std::max<std::size_t>
            (
                count,
                sfl::dtl::floating_point_to_size_t
                (
                    std::floor
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

    void reserve(size_type count)
    {
        rehash
        (
            sfl::dtl::floating_point_to_size_t
            (
                std::ceil
                (
                    static_cast<double>(count) /
                    static_cast<double>(data_.get_max_load_factor())
                )
            )
        );
    }

private:

    ///////////////////////////////////////////////////////////////////////////

    sfl::dtl::allocation_result<bucket_pointer, size_type> make_buckets(size_type n)
    {
        const auto res = sfl::dtl::allocator_traits<bucket_allocator_type>::allocate_at_least
        (
            data_.ref_to_bucket_alloc(),
            n
        );

        SFL_TRY
        {
            sfl::dtl::uninitialized_default_construct_n_a
            (
                data_.ref_to_bucket_alloc(),
                res.ptr,
                res.count
            );
        }
        SFL_CATCH (...)
        {
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

    node_pointer allocate_node()
    {
        return sfl::dtl::allocator_traits<node_allocator_type>::allocate
        (
            data_.ref_to_node_alloc(),
            1
        );
    }

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

        make_node_functor(hash_table& table)
            : table_(table)
        {}

        template <typename... Args>
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

    void drop_node(node_pointer p) noexcept
    {
        destroy_node(p);
        deallocate_node(p);
    }

    ///////////////////////////////////////////////////////////////////////////

    static const Key& key_of(node_pointer x) noexcept
    {
        return KeyOfValue()(x->value_.ref());
    }

    static const Key& key_of(base_node_pointer x) noexcept
    {
        return KeyOfValue()(static_cast<node_pointer>(x)->value_.ref());
    }

    ///////////////////////////////////////////////////////////////////////////

    static std::size_t bucket_index_of(node_pointer x) noexcept
    {
        return x->get_bucket_index();
    }

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

    void resize_buckets_and_rehash_if_overloaded()
    {
        if (data_.is_overloaded())
        {
            const std::size_t new_bucket_count = data_.calculate_new_bucket_count
            (
                sfl::dtl::floating_point_to_size_t
                (
                    std::floor
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

    void resize_buckets_and_rehash(std::size_t new_bucket_count)
    {
        SFL_ASSERT(data_.check_bucket_count(new_bucket_count));
        const auto res = make_buckets(new_bucket_count);
        SFL_ASSERT(res.count == new_bucket_count);

        drop_buckets(data_.buckets_, data_.get_bucket_count());

        data_.buckets_ = res.ptr;
        data_.set_bucket_count(res.count);

        for (bucket_pointer x = data_.buckets_, end = x + data_.get_bucket_count(); x != end; ++x)
        {
            x->next_ = nullptr;
        }

        base_node_pointer prev = data_.head();

        SFL_TRY
        {
            while (prev->next_)
            {
                node_pointer x = static_cast<node_pointer>(prev->next_);

                const std::size_t hash = data_.ref_to_key_hash()(key_of(x));
                const std::size_t bucket_index = data_.calculate_bucket_index_for_hash(hash);

                x->set_bucket_index(bucket_index, std::true_type());

                while (true)
                {
                    node_pointer next = static_cast<node_pointer>(x->next_);

                    if (next == nullptr || next->is_first_in_group())
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

template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5, typename TP6, typename TP7, typename TP8, typename TP9, typename TP10>
SFL_NODISCARD
bool operator==
(
    const hash_table<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10>& x,
    const hash_table<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10>& y
)
{
    return x.size() == y.size() && std::is_permutation(x.begin(), x.end(), y.begin());
}

template <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5, typename TP6, typename TP7, typename TP8, typename TP9, typename TP10>
SFL_NODISCARD
bool operator!=
(
    const hash_table<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10>& x,
    const hash_table<TP1, TP2, TP3, TP4, TP5, TP6, TP7, TP8, TP9, TP10>& y
)
{
    return !(x == y);
}

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_HASH_TABLE_HPP_INCLUDED
