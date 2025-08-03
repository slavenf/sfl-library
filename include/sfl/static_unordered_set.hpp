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

#ifndef SFL_STATIC_UNORDERED_SET_HPP_INCLUDED
#define SFL_STATIC_UNORDERED_SET_HPP_INCLUDED

#include <sfl/detail/bit/bit_ceil.hpp>
#include <sfl/detail/concepts/container_compatible_range.hpp>
#include <sfl/detail/functional/identity.hpp>
#include <sfl/detail/math/is_pow2.hpp>
#include <sfl/detail/math/is_prime.hpp>
#include <sfl/detail/type_traits/enable_if_t.hpp>
#include <sfl/detail/type_traits/has_is_transparent.hpp>
#include <sfl/detail/type_traits/is_input_iterator.hpp>
#include <sfl/detail/cpp.hpp>
#include <sfl/detail/functional.hpp>
#include <sfl/detail/hash_table.hpp>
#include <sfl/detail/static_node_allocator.hpp>
#include <sfl/detail/static_storage_allocator.hpp>
#include <sfl/detail/tags.hpp>

#include <cstddef>          // size_t
#include <functional>       // equal_to, hash
#include <initializer_list> // initializer_list
#include <type_traits>      // conditional
#include <utility>          // forward, move, pair

namespace sfl
{

template < typename Key,
           std::size_t StaticCapacity,
           std::size_t StaticBucketCount = sfl::dtl::bit_ceil(StaticCapacity),
           typename Hash = std::hash<Key>,
           typename KeyEqual = std::equal_to<Key> >
class static_unordered_set
{
    static_assert(StaticCapacity > 0, "StaticCapacity must be greater than zero.");
    static_assert(StaticBucketCount > 0, "StaticBucketCount must be greater than zero.");

public:

    using key_type        = Key;
    using value_type      = Key;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using hasher          = Hash;
    using key_equal       = KeyEqual;

private:

    using node_allocator_type = sfl::dtl::static_node_allocator<value_type, StaticCapacity>;

    using bucket_allocator_type = sfl::dtl::static_storage_allocator<value_type, StaticBucketCount>;

    using bucket_count_policy = typename std::conditional
    <
        sfl::dtl::is_pow2(StaticBucketCount),
        sfl::dtl::hash_table_static_pow2_bucket_count_policy<StaticBucketCount>,
        typename std::conditional
        <
            sfl::dtl::is_prime(StaticBucketCount),
            sfl::dtl::hash_table_static_prime_bucket_count_policy<StaticBucketCount>,
            sfl::dtl::hash_table_static_basic_bucket_count_policy<StaticBucketCount>
        >::type
    >::type;

    using max_load_policy = sfl::dtl::hash_table_no_max_load_policy;

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
        static_unordered_set
    >;

    hash_table hash_table_;

public:

    using size_type            = typename hash_table::size_type;
    using difference_type      = typename hash_table::difference_type;
    using pointer              = value_type*;
    using const_pointer        = const value_type*;
    using iterator             = typename hash_table::const_iterator; // MUST BE const
    using const_iterator       = typename hash_table::const_iterator;
    using local_iterator       = typename hash_table::const_local_iterator; // MUST BE const
    using const_local_iterator = typename hash_table::const_local_iterator;

public:

    static constexpr size_type static_capacity = StaticCapacity;
    static constexpr size_type static_bucket_count = StaticBucketCount;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    static_unordered_set()
        : hash_table_(StaticBucketCount)
    {}

    static_unordered_set(const Hash& hash)
        : hash_table_(StaticBucketCount, hash)
    {}

    static_unordered_set(const Hash& hash, const KeyEqual& equal)
        : hash_table_(StaticBucketCount, hash, equal)
    {}

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    static_unordered_set(InputIt first, InputIt last)
        : hash_table_(StaticBucketCount)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    static_unordered_set(InputIt first, InputIt last, const Hash& hash)
        : hash_table_(StaticBucketCount, hash)
    {
        insert(first, last);
    }

    template <typename InputIt,
              sfl::dtl::enable_if_t<sfl::dtl::is_input_iterator<InputIt>::value>* = nullptr>
    static_unordered_set(InputIt first, InputIt last, const Hash& hash, const KeyEqual& equal)
        : hash_table_(StaticBucketCount, hash, equal)
    {
        insert(first, last);
    }

    static_unordered_set(std::initializer_list<value_type> ilist)
        : static_unordered_set(ilist.begin(), ilist.end())
    {}

    static_unordered_set(std::initializer_list<value_type> ilist, const Hash& hash)
        : static_unordered_set(ilist.begin(), ilist.end(), hash)
    {}

    static_unordered_set(std::initializer_list<value_type> ilist, const Hash& hash, const KeyEqual& equal)
        : static_unordered_set(ilist.begin(), ilist.end(), hash, equal)
    {}

    static_unordered_set(const static_unordered_set& other)
        : hash_table_(other.hash_table_, sfl::dtl::hash_table_unique_t())
    {}

    static_unordered_set(static_unordered_set&& other)
        : hash_table_(std::move(other.hash_table_), sfl::dtl::hash_table_unique_t())
    {}

#if SFL_CPP_VERSION >= SFL_CPP_20

    template <sfl::dtl::container_compatible_range<value_type> Range>
    static_unordered_set(sfl::from_range_t, Range&& range)
        : hash_table_(StaticBucketCount)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    static_unordered_set(sfl::from_range_t, Range&& range, const Hash& hash)
        : hash_table_(StaticBucketCount, hash)
    {
        insert_range(std::forward<Range>(range));
    }

    template <sfl::dtl::container_compatible_range<value_type> Range>
    static_unordered_set(sfl::from_range_t, Range&& range, const Hash& hash, const KeyEqual& equal)
        : hash_table_(StaticBucketCount, hash, equal)
    {
        insert_range(std::forward<Range>(range));
    }

#else // before C++20

    template <typename Range>
    static_unordered_set(sfl::from_range_t, Range&& range)
        : hash_table_(StaticBucketCount)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    static_unordered_set(sfl::from_range_t, Range&& range, const Hash& hash)
        : hash_table_(StaticBucketCount, hash)
    {
        insert_range(std::forward<Range>(range));
    }

    template <typename Range>
    static_unordered_set(sfl::from_range_t, Range&& range, const Hash& hash, const KeyEqual& equal)
        : hash_table_(StaticBucketCount, hash, equal)
    {
        insert_range(std::forward<Range>(range));
    }

#endif // before C++20

    ~static_unordered_set()
    {}

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    static_unordered_set& operator=(const static_unordered_set& other)
    {
        hash_table_.assign_copy(other.hash_table_, sfl::dtl::hash_table_unique_t());
        return *this;
    }

    static_unordered_set& operator=(static_unordered_set&& other)
    {
        hash_table_.assign_move(other.hash_table_, sfl::dtl::hash_table_unique_t());
        return *this;
    }

    static_unordered_set& operator=(std::initializer_list<value_type> ilist)
    {
        hash_table_.assign_range_unique(ilist.begin(), ilist.end());
        return *this;
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
    bool full() const noexcept
    {
        return size() == capacity();
    }

    SFL_NODISCARD
    size_type size() const noexcept
    {
        return hash_table_.size();
    }

    SFL_NODISCARD
    static constexpr size_type max_size() noexcept
    {
        return StaticCapacity;
    }

    SFL_NODISCARD
    static constexpr size_type capacity() noexcept
    {
        return StaticCapacity;
    }

    SFL_NODISCARD
    size_type available() const noexcept
    {
        return capacity() - size();
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
        SFL_ASSERT(!full());
        return hash_table_.emplace_unique(std::forward<Args>(args)...);
    }

    template <typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        SFL_ASSERT(!full());
        return hash_table_.emplace_hint_unique(hint, std::forward<Args>(args)...);
    }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        SFL_ASSERT(!full());
        return hash_table_.insert_unique(value);
    }

    std::pair<iterator, bool> insert(value_type&& value)
    {
        SFL_ASSERT(!full());
        return hash_table_.insert_unique(std::move(value));
    }

    iterator insert(const_iterator hint, const value_type& value)
    {
        SFL_ASSERT(!full());
        return hash_table_.insert_hint_unique(hint, value);
    }

    iterator insert(const_iterator hint, value_type&& value)
    {
        SFL_ASSERT(!full());
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

    void swap(static_unordered_set& other)
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
    static constexpr size_type bucket_count() noexcept
    {
        return StaticBucketCount;
    }

    SFL_NODISCARD
    static constexpr size_type max_bucket_count() noexcept
    {
        return StaticBucketCount;
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
    static constexpr float max_load_factor()
    {
        return static_cast<float>(StaticCapacity) / static_cast<float>(StaticBucketCount);
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

    template <typename K2, std::size_t N2, std::size_t M2, typename H2, typename E2>
    friend bool operator==(const static_unordered_set<K2, N2, M2, H2, E2>& x, const static_unordered_set<K2, N2, M2, H2, E2>& y);

    template <typename K2, std::size_t N2, std::size_t M2, typename H2, typename E2>
    friend bool operator!=(const static_unordered_set<K2, N2, M2, H2, E2>& x, const static_unordered_set<K2, N2, M2, H2, E2>& y);
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template <typename K, std::size_t N, std::size_t M, typename H, typename E>
SFL_NODISCARD
bool operator==
(
    const static_unordered_set<K, N, M, H, E>& x,
    const static_unordered_set<K, N, M, H, E>& y
)
{
    return x.hash_table_ == y.hash_table_;
}

template <typename K, std::size_t N, std::size_t M, typename H, typename E>
SFL_NODISCARD
bool operator!=
(
    const static_unordered_set<K, N, M, H, E>& x,
    const static_unordered_set<K, N, M, H, E>& y
)
{
    return x.hash_table_ != y.hash_table_;
}

template <typename K, std::size_t N, std::size_t M, typename H, typename E>
void swap
(
    static_unordered_set<K, N, M, H, E>& x,
    static_unordered_set<K, N, M, H, E>& y
)
{
    x.swap(y);
}

template <typename K, std::size_t N, std::size_t M, typename H, typename E, typename Predicate>
typename static_unordered_set<K, N, M, H, E>::size_type
    erase_if(static_unordered_set<K, N, M, H, E>& c, Predicate pred)
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

#endif // SFL_STATIC_UNORDERED_SET_HPP_INCLUDED
