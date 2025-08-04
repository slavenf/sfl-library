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

#ifndef SFL_SMALL_UNORDERED_SET_HPP_INCLUDED
#define SFL_SMALL_UNORDERED_SET_HPP_INCLUDED

#include <sfl/detail/bit/bit_ceil.hpp>
#include <sfl/detail/concepts/container_compatible_range.hpp>
#include <sfl/detail/functional/identity.hpp>
#include <sfl/detail/math/is_pow2.hpp>
#include <sfl/detail/math/is_prime.hpp>
#include <sfl/detail/tags/from_range_t.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/has_is_transparent.hpp>
#include <sfl/detail/type_traits/is_input_iterator.hpp>
#include <sfl/detail/allocator_traits.hpp>
#include <sfl/detail/cpp.hpp>
#include <sfl/detail/exceptions.hpp>
#include <sfl/detail/hash_table.hpp>
#include <sfl/detail/small_node_allocator.hpp>
#include <sfl/detail/small_storage_allocator.hpp>

#include <cstddef>          // size_t
#include <functional>       // equal_to, hash
#include <initializer_list> // initializer_list
#include <memory>           // allocator
#include <type_traits>      // conditional, is_same
#include <utility>          // forward, move, pair

namespace sfl
{

template < typename Key,
           std::size_t StaticCapacity,
           std::size_t StaticBucketCount = StaticCapacity == 0 ? 0 : sfl::dtl::bit_ceil(StaticCapacity),
           typename Hash = std::hash<Key>,
           typename KeyEqual = std::equal_to<Key>,
           typename Allocator = std::allocator<Key> >
class small_unordered_set
{
    static_assert
    (
        (StaticCapacity == 0 && StaticBucketCount == 0) ||
        (StaticCapacity != 0 && StaticBucketCount != 0),
        "StaticCapacity and StaticBucketCount must both be zero or both be non-zero."
    );

    static_assert
    (
        std::is_same<typename Allocator::value_type, Key>::value,
        "Allocator::value_type must be Key."
    );

public:

    using allocator_type  = Allocator;
    using key_type        = Key;
    using value_type      = Key;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using hasher          = Hash;
    using key_equal       = KeyEqual;

private:

    using node_allocator_type = sfl::dtl::small_node_allocator<value_type, StaticCapacity, Allocator>;

    using bucket_allocator_type = sfl::dtl::small_storage_allocator<value_type, StaticBucketCount, Allocator>;

    using bucket_count_policy = typename std::conditional
    <
        sfl::dtl::is_pow2(StaticBucketCount),
        sfl::dtl::hash_table_dynamic_pow2_bucket_count_policy,
        typename std::conditional
        <
            sfl::dtl::is_prime(StaticBucketCount),
            sfl::dtl::hash_table_dynamic_prime_bucket_count_policy,
            sfl::dtl::hash_table_dynamic_basic_bucket_count_policy
        >::type
    >::type;

    using max_load_policy = sfl::dtl::hash_table_standard_max_load_policy;

    using hash_table = sfl::dtl::hash_table
    <
        key_type,
        value_type,
        sfl::dtl::identity,
        hasher,
        key_equal,
        node_allocator_type,
        bucket_allocator_type,
        bucket_count_policy,
        max_load_policy,
        small_unordered_set
    >;

    hash_table hash_table_;

public:

    using size_type            = typename hash_table::size_type;
    using difference_type      = typename hash_table::difference_type;
    using pointer              = typename sfl::dtl::allocator_traits<Allocator>::pointer;
    using const_pointer        = typename sfl::dtl::allocator_traits<Allocator>::const_pointer;
    using iterator             = typename hash_table::const_iterator; // MUST BE const
    using const_iterator       = typename hash_table::const_iterator;
    using local_iterator       = typename hash_table::const_local_iterator; // MUST BE const
    using const_local_iterator = typename hash_table::const_local_iterator;

public:

    static constexpr size_type static_capacity = StaticCapacity;
    static constexpr size_type static_bucket_count = StaticBucketCount;

private:

    static std::size_t calculate_initial_bucket_count(std::size_t n)
    {
        #ifdef _MSC_VER // Visual C++
        #pragma warning(push)
        #pragma warning(disable : 4127) // conditional expression is constant
        #endif

        if (StaticBucketCount > 0 && n <= StaticBucketCount)
        {
            return StaticBucketCount;
        }
        else
        {
            return bucket_count_policy::calculate_new_bucket_count(n);
        }

        #ifdef _MSC_VER // Visual C++
        #pragma warning(pop)
        #endif
    }

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    small_unordered_set()
        : hash_table_(calculate_initial_bucket_count(0))
    {}

    explicit
    small_unordered_set(const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(0), alloc)
    {}

    explicit
    small_unordered_set(size_type bucket_count)
        : hash_table_(calculate_initial_bucket_count(bucket_count))
    {}

    small_unordered_set(size_type bucket_count, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), alloc)
    {}

    small_unordered_set(size_type bucket_count, const Hash& hash)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash)
    {}

    small_unordered_set(size_type bucket_count, const Hash& hash, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, alloc)
    {}

    small_unordered_set(size_type bucket_count, const Hash& hash, const KeyEqual& equal)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, equal)
    {}

    small_unordered_set(size_type bucket_count, const Hash& hash, const KeyEqual& equal, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, equal, alloc)
    {}

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_unordered_set(InputIt first, InputIt last)
        : hash_table_(calculate_initial_bucket_count(0))
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count)
        : hash_table_(calculate_initial_bucket_count(bucket_count))
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), alloc)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count, const Hash& hash)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count, const Hash& hash, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, alloc)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count, const Hash& hash, const KeyEqual& equal)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, equal)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    small_unordered_set(InputIt first, InputIt last, size_type bucket_count, const Hash& hash, const KeyEqual& equal, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, equal, alloc)
    {
        insert(first, last);
    }

    small_unordered_set(std::initializer_list<value_type> ilist)
        : small_unordered_set(ilist.begin(), ilist.end())
    {}

    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count)
        : small_unordered_set(ilist.begin(), ilist.end(), bucket_count)
    {}

    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count, const Allocator& alloc)
        : small_unordered_set(ilist.begin(), ilist.end(), bucket_count, alloc)
    {}

    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count, const Hash& hash)
        : small_unordered_set(ilist.begin(), ilist.end(), bucket_count, hash)
    {}

    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count, const Hash& hash, const Allocator& alloc)
        : small_unordered_set(ilist.begin(), ilist.end(), bucket_count, hash, alloc)
    {}

    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count, const Hash& hash, const KeyEqual& equal)
        : small_unordered_set(ilist.begin(), ilist.end(), bucket_count, hash, equal)
    {}

    small_unordered_set(std::initializer_list<value_type> ilist, size_type bucket_count, const Hash& hash, const KeyEqual& equal, const Allocator& alloc)
        : small_unordered_set(ilist.begin(), ilist.end(), bucket_count, hash, equal, alloc)
    {}

    small_unordered_set(const small_unordered_set& other)
        : hash_table_(other.hash_table_, sfl::dtl::hash_table_unique_t())
    {}

    small_unordered_set(const small_unordered_set& other, const Allocator& alloc)
        : hash_table_(other.hash_table_, sfl::dtl::hash_table_unique_t(), alloc)
    {}

    small_unordered_set(small_unordered_set&& other)
        : hash_table_(std::move(other.hash_table_), sfl::dtl::hash_table_unique_t())
    {}

    small_unordered_set(small_unordered_set&& other, const Allocator& alloc)
        : hash_table_(std::move(other.hash_table_), sfl::dtl::hash_table_unique_t(), alloc)
    {}

#if SFL_CPP_VERSION >= SFL_CPP_20

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_unordered_set(sfl::from_range_t, Range&& range)
        : hash_table_(calculate_initial_bucket_count(0))
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count)
        : hash_table_(calculate_initial_bucket_count(bucket_count))
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), alloc)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, alloc)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash, const KeyEqual& equal)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, equal)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash, const KeyEqual& equal, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, equal, alloc)
    {
        insert_range(std::forward<Range>(range));
    }

#else // before C++20

    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range)
        : hash_table_(calculate_initial_bucket_count(0))
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count)
        : hash_table_(calculate_initial_bucket_count(bucket_count))
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), alloc)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, alloc)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash, const KeyEqual& equal)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, equal)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    small_unordered_set(sfl::from_range_t, Range&& range, size_type bucket_count, const Hash& hash, const KeyEqual& equal, const Allocator& alloc)
        : hash_table_(calculate_initial_bucket_count(bucket_count), hash, equal, alloc)
    {
        insert_range(std::forward<Range>(range));
    }

#endif // before C++20

    ~small_unordered_set()
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    small_unordered_set& operator=(const small_unordered_set& other)
    {
        hash_table_.assign_copy(other.hash_table_, sfl::dtl::hash_table_unique_t());
        return *this;
    }

    small_unordered_set& operator=(small_unordered_set&& other)
    {
        hash_table_.assign_move(other.hash_table_, sfl::dtl::hash_table_unique_t());
        return *this;
    }

    small_unordered_set& operator=(std::initializer_list<value_type> ilist)
    {
        hash_table_.assign_range_unique(ilist.begin(), ilist.end());
        return *this;
    }

    //
    // ---- ALLOCATOR ---------------------------------------------------------
    //

    SFL_NODISCARD
    allocator_type get_allocator() const noexcept
    {
        return allocator_type(hash_table_.data_.ref_to_node_alloc());
    }

    //
    // ---- HASH_FUNCTION -----------------------------------------------------
    //

    SFL_NODISCARD
    hasher hash_function() const
    {
        return hasher(hash_table_.data_.ref_to_key_hash());
    }

    //
    // ---- KEY EQUAL ---------------------------------------------------------
    //

    SFL_NODISCARD
    key_equal key_eq() const
    {
        return key_equal(hash_table_.data_.ref_to_key_equal());
    }

    //
    // ---- ITERATORS ---------------------------------------------------------
    //

    SFL_NODISCARD
    iterator begin() noexcept
    {
        return hash_table_.begin();
    }

    SFL_NODISCARD
    const_iterator begin() const noexcept
    {
        return hash_table_.begin();
    }

    SFL_NODISCARD
    const_iterator cbegin() const noexcept
    {
        return hash_table_.cbegin();
    }

    SFL_NODISCARD
    iterator end() noexcept
    {
        return hash_table_.end();
    }

    SFL_NODISCARD
    const_iterator end() const noexcept
    {
        return hash_table_.end();
    }

    SFL_NODISCARD
    const_iterator cend() const noexcept
    {
        return hash_table_.cend();
    }

    //
    // ---- SIZE AND CAPACITY -------------------------------------------------
    //

    SFL_NODISCARD
    bool empty() const noexcept
    {
        return hash_table_.empty();
    }

    SFL_NODISCARD
    size_type size() const noexcept
    {
        return hash_table_.size();
    }

    SFL_NODISCARD
    size_type max_size() const noexcept
    {
        return hash_table_.max_size();
    }

    //
    // ---- MODIFIERS ---------------------------------------------------------
    //

    void clear()
    {
        hash_table_.clear();
    }

    template <typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args)
    {
        return hash_table_.emplace_unique(std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        return hash_table_.emplace_hint_unique(hint, std::forward<Args>(args)...);
    }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        return hash_table_.insert_unique(value);
    }

    std::pair<iterator, bool> insert(value_type&& value)
    {
        return hash_table_.insert_unique(std::move(value));
    }

    iterator insert(const_iterator hint, const value_type& value)
    {
        return hash_table_.insert_hint_unique(hint, value);
    }

    iterator insert(const_iterator hint, value_type&& value)
    {
        return hash_table_.insert_hint_unique(hint, std::move(value));
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    void insert(InputIt first, InputIt last)
    {
        insert_range_aux(first, last);
    }

    void insert(std::initializer_list<value_type> ilist)
    {
        insert_range_aux(ilist.begin(), ilist.end());
    }

#if SFL_CPP_VERSION >= SFL_CPP_20

    template <sfl::dtl::container_compatible_range<value_type> Range>
    void insert_range(Range&& range)
    {
        insert_range_aux(std::ranges::begin(range), std::ranges::end(range));
    }

#else // before C++20

    template <typename Range>
    void insert_range(Range&& range)
    {
        using std::begin;
        using std::end;
        insert_range_aux(begin(range), end(range));
    }

#endif // before C++20

    iterator erase(const_iterator pos)
    {
        return hash_table_.erase_unique(pos);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        return hash_table_.erase_unique(first, last);
    }

    size_type erase(const Key& key)
    {
        return hash_table_.erase_key_unique(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Hash, K>::value &&
                                     sfl::dtl::has_is_transparent<KeyEqual, K>::value >* = nullptr>
    size_type erase(K&& x)
    {
        return hash_table_.erase_key_unique(x);
    }

    void swap(small_unordered_set& other)
    {
        hash_table_.swap(other.hash_table_);
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    SFL_NODISCARD
    std::pair<iterator, iterator> equal_range(const Key& key)
    {
        return hash_table_.equal_range(key);
    }

    SFL_NODISCARD
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const
    {
        return hash_table_.equal_range(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Hash, K>::value &&
                                     sfl::dtl::has_is_transparent<KeyEqual, K>::value >* = nullptr>
    SFL_NODISCARD
    std::pair<iterator, iterator> equal_range(const K& x)
    {
        return hash_table_.equal_range(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Hash, K>::value &&
                                     sfl::dtl::has_is_transparent<KeyEqual, K>::value >* = nullptr>
    SFL_NODISCARD
    std::pair<const_iterator, const_iterator> equal_range(const K& x) const
    {
        return hash_table_.equal_range(x);
    }

    SFL_NODISCARD
    iterator find(const Key& key)
    {
        return hash_table_.find(key);
    }

    SFL_NODISCARD
    const_iterator find(const Key& key) const
    {
        return hash_table_.find(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Hash, K>::value &&
                                     sfl::dtl::has_is_transparent<KeyEqual, K>::value >* = nullptr>
    SFL_NODISCARD
    iterator find(const K& x)
    {
        return hash_table_.find(x);
    }

    template <typename K,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Hash, K>::value &&
                                     sfl::dtl::has_is_transparent<KeyEqual, K>::value >* = nullptr>
    SFL_NODISCARD
    const_iterator find(const K& x) const
    {
        return hash_table_.find(x);
    }

    SFL_NODISCARD
    size_type count(const Key& key) const
    {
        return hash_table_.count(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Hash, K>::value &&
                                     sfl::dtl::has_is_transparent<KeyEqual, K>::value >* = nullptr>
    SFL_NODISCARD
    size_type count(const K& x) const
    {
        return hash_table_.count(x);
    }

    SFL_NODISCARD
    bool contains(const Key& key) const
    {
        return hash_table_.contains(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Hash, K>::value &&
                                     sfl::dtl::has_is_transparent<KeyEqual, K>::value >* = nullptr>
    SFL_NODISCARD
    bool contains(const K& x) const
    {
        return hash_table_.contains(x);
    }

    //
    // ---- BUCKET INTERFACE --------------------------------------------------
    //

    SFL_NODISCARD
    local_iterator begin(size_type n) noexcept
    {
        return hash_table_.begin(n);
    }

    SFL_NODISCARD
    const_local_iterator begin(size_type n) const noexcept
    {
        return hash_table_.begin(n);
    }

    SFL_NODISCARD
    const_local_iterator cbegin(size_type n) const noexcept
    {
        return hash_table_.cbegin(n);
    }

    SFL_NODISCARD
    local_iterator end(size_type n) noexcept
    {
        return hash_table_.end(n);
    }

    SFL_NODISCARD
    const_local_iterator end(size_type n) const noexcept
    {
        return hash_table_.end(n);
    }

    SFL_NODISCARD
    const_local_iterator cend(size_type n) const noexcept
    {
        return hash_table_.cend(n);
    }

    SFL_NODISCARD
    size_type bucket_count() const
    {
        return hash_table_.bucket_count();
    }

    SFL_NODISCARD
    size_type max_bucket_count() const
    {
        return hash_table_.max_bucket_count();
    }

    SFL_NODISCARD
    size_type bucket_size(size_type n) const
    {
        return hash_table_.bucket_size(n);
    }

    SFL_NODISCARD
    size_type bucket(const Key& key) const
    {
        return hash_table_.bucket(key);
    }

    template <typename K,
              sfl::dtl::enable_if_t< sfl::dtl::has_is_transparent<Hash, K>::value &&
                                     sfl::dtl::has_is_transparent<KeyEqual, K>::value >* = nullptr>
    SFL_NODISCARD
    size_type bucket(const K& x) const
    {
        return hash_table_.bucket(x);
    }

    //
    // ---- HASH POLICY -------------------------------------------------------
    //

    SFL_NODISCARD
    float load_factor() const
    {
        return hash_table_.load_factor();
    }

    SFL_NODISCARD
    float max_load_factor() const
    {
        return hash_table_.max_load_factor();
    }

    void max_load_factor(float mlf)
    {
        hash_table_.max_load_factor(mlf);
    }

    void rehash(size_type count)
    {
        hash_table_.rehash(count);
    }

    void reserve(size_type count)
    {
        hash_table_.reserve(count);
    }

private:

    template <typename InputIt, typename Sentinel>
    void insert_range_aux(InputIt first, Sentinel last)
    {
        while (first != last)
        {
            insert(*first);
            ++first;
        }
    }

    template <typename K2, std::size_t N2, std::size_t M2, typename H2, typename E2, typename A2>
    friend bool operator==(const small_unordered_set<K2, N2, M2, H2, E2, A2>& x, const small_unordered_set<K2, N2, M2, H2, E2, A2>& y);

    template <typename K2, std::size_t N2, std::size_t M2, typename H2, typename E2, typename A2>
    friend bool operator!=(const small_unordered_set<K2, N2, M2, H2, E2, A2>& x, const small_unordered_set<K2, N2, M2, H2, E2, A2>& y);
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template <typename K, std::size_t N, std::size_t M, typename H, typename E, typename A>
SFL_NODISCARD
bool operator==
(
    const small_unordered_set<K, N, M, H, E, A>& x,
    const small_unordered_set<K, N, M, H, E, A>& y
)
{
    return x.hash_table_ == y.hash_table_;
}

template <typename K, std::size_t N, std::size_t M, typename H, typename E, typename A>
SFL_NODISCARD
bool operator!=
(
    const small_unordered_set<K, N, M, H, E, A>& x,
    const small_unordered_set<K, N, M, H, E, A>& y
)
{
    return x.hash_table_ != y.hash_table_;
}

template <typename K, std::size_t N, std::size_t M, typename H, typename E, typename A>
void swap
(
    small_unordered_set<K, N, M, H, E, A>& x,
    small_unordered_set<K, N, M, H, E, A>& y
)
{
    x.swap(y);
}

template <typename K, std::size_t N, std::size_t M, typename H, typename E, typename A, typename Predicate>
typename small_unordered_set<K, N, M, H, E, A>::size_type
    erase_if(small_unordered_set<K, N, M, H, E, A>& c, Predicate pred)
{
    auto old_size = c.size();

    for (auto it = c.begin(); it != c.end(); )
    {
        if (pred(*it))
        {
            it = c.erase(it);
        }
        else
        {
            ++it;
        }
    }

    return old_size - c.size();
}

} // namespace sfl

#endif // SFL_SMALL_UNORDERED_SET_HPP_INCLUDED
