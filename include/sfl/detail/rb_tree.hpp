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

#ifndef SFL_DETAIL_RB_TREE_HPP_INCLUDED
#define SFL_DETAIL_RB_TREE_HPP_INCLUDED

#include <sfl/private.hpp>
#include <sfl/detail/allocator_traits.hpp>
#include <sfl/detail/cpp.hpp>
#include <sfl/detail/optional_value.hpp>
#include <sfl/detail/type_traits.hpp>

#include <algorithm>    // equal, lexicographical_compare
#include <cstddef>      // size_t, ptrdiff_t
#include <iterator>     // iterator_traits, xxxxx_iterator_tag, reverse_iterator
#include <type_traits>  // is_xxxxx
#include <utility>      // forward, move, pair

#ifdef SFL_TEST_RB_TREE
template <int>
void test_rb_tree();
#endif

namespace sfl
{

namespace dtl
{

enum class rb_tree_node_color
{
    red,
    black
};

struct rb_tree_node_base
{
    rb_tree_node_color color_;
    rb_tree_node_base* parent_;
    rb_tree_node_base* left_;
    rb_tree_node_base* right_;
};

template <typename Value, typename Allocator>
struct rb_tree_node : rb_tree_node_base
{
    static_assert
    (
        std::is_same<typename Allocator::value_type, Value>::value,
        "Allocator::value_type must be Value."
    );

    sfl::dtl::optional_value<Value> value_;
};

template < typename Key,
           typename Value,
           typename KeyOfValue,
           typename KeyCompare,
           typename Allocator,
           typename UpperLevelContainer >
class rb_tree
{
    static_assert
    (
        std::is_same<typename Allocator::value_type, Value>::value,
        "Allocator::value_type must be Value."
    );

    #ifdef SFL_TEST_RB_TREE
    template <int>
    friend void ::test_rb_tree();
    #endif

    friend UpperLevelContainer;

public:

    using allocator_type  = Allocator;
    using key_type        = Key;
    using value_type      = Value;
    using size_type       = typename sfl::dtl::allocator_traits<allocator_type>::size_type;
    using difference_type = typename sfl::dtl::allocator_traits<allocator_type>::difference_type;
    using key_compare     = KeyCompare;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename sfl::dtl::allocator_traits<allocator_type>::pointer;
    using const_pointer   = typename sfl::dtl::allocator_traits<allocator_type>::const_pointer;

private:

    using node_type = rb_tree_node<value_type, allocator_type>;
    using node_allocator_type = typename sfl::dtl::allocator_traits<allocator_type>::template rebind_alloc<node_type>;

public:

    class iterator
    {
        #ifdef SFL_TEST_RB_TREE
        template <int>
        friend void ::test_rb_tree();
        #endif

        friend class rb_tree;

        friend UpperLevelContainer;

    public:

        using difference_type   = std::ptrdiff_t;
        using value_type        = Value;
        using pointer           = Value*;
        using reference         = Value&;
        using iterator_category = std::bidirectional_iterator_tag;

    private:

        rb_tree_node_base* node_;

    private:

        explicit iterator(rb_tree_node_base* x) noexcept
            : node_(x)
        {}

    public:

        // Default constructor
        iterator() noexcept
            : node_()
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
            return *static_cast<node_type*>(node_)->value_.get();
        }

        SFL_NODISCARD
        pointer operator->() const noexcept
        {
            return static_cast<node_type*>(node_)->value_.get();
        }

        iterator& operator++() noexcept
        {
            node_ = rb_tree::next(node_);
            return *this;
        }

        iterator operator++(int) noexcept
        {
            auto temp = *this;
            node_ = rb_tree::next(node_);
            return temp;
        }

        iterator& operator--() noexcept
        {
            node_ = rb_tree::prev(node_);
            return *this;
        }

        iterator operator--(int) noexcept
        {
            auto temp = *this;
            node_ = rb_tree::prev(node_);
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
        #ifdef SFL_TEST_RB_TREE
        template <int>
        friend void ::test_rb_tree();
        #endif

        friend class rb_tree;

        friend UpperLevelContainer;

    public:

        using difference_type   = std::ptrdiff_t;
        using value_type        = Value;
        using pointer           = const Value*;
        using reference         = const Value&;
        using iterator_category = std::bidirectional_iterator_tag;

    private:

        const rb_tree_node_base* node_;

    private:

        explicit const_iterator(const rb_tree_node_base* x) noexcept
            : node_(x)
        {}

    public:

        // Default constructor
        const_iterator() noexcept
            : node_()
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
            return *static_cast<const node_type*>(node_)->value_.get();
        }

        SFL_NODISCARD
        pointer operator->() const noexcept
        {
            return static_cast<const node_type*>(node_)->value_.get();
        }

        const_iterator& operator++() noexcept
        {
            node_ = rb_tree::next(node_);
            return *this;
        }

        const_iterator operator++(int) noexcept
        {
            auto temp = *this;
            node_ = rb_tree::next(node_);
            return temp;
        }

        const_iterator& operator--() noexcept
        {
            node_ = rb_tree::prev(node_);
            return *this;
        }

        const_iterator operator--(int) noexcept
        {
            auto temp = *this;
            node_ = rb_tree::prev(node_);
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

    private:

        iterator to_iterator() const noexcept
        {
            return iterator(const_cast<rb_tree_node_base*>(node_));
        }
    };

    using reverse_iterator = std::reverse_iterator<iterator>;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:

    class data_base
    {
    public:

        rb_tree_node_base header_;

        size_type size_;

        SFL_NODISCARD
        rb_tree_node_base* header() noexcept
        {
            return &header_;
        }

        SFL_NODISCARD
        const rb_tree_node_base* header() const noexcept
        {
            return &header_;
        }

        SFL_NODISCARD
        rb_tree_node_base*& root() noexcept
        {
            return header_.left_;
        }

        SFL_NODISCARD
        const rb_tree_node_base* root() const noexcept
        {
            return header_.left_;
        }

        SFL_NODISCARD
        rb_tree_node_base*& minimum() noexcept
        {
            return header_.parent_;
        }

        SFL_NODISCARD
        const rb_tree_node_base* minimum() const noexcept
        {
            return header_.parent_;
        }

        void reset() noexcept
        {
            header_.color_  = rb_tree_node_color::red;
            header_.parent_ = &header_; // minimum
            header_.left_   = nullptr;  // root
            header_.right_  = nullptr;  // unused
            size_ = 0;
        }

        data_base() noexcept
        {
            reset();
        }

        data_base(const data_base& other) = delete;

        data_base(data_base&& other) = delete;

        data_base& operator=(const data_base& other) = delete;

        data_base& operator=(data_base&& other) = delete;

        ~data_base() noexcept
        {};
    };

    class data : public data_base, public node_allocator_type, public key_compare
    {
    public:

        data() noexcept
        (
            std::is_nothrow_default_constructible<node_allocator_type>::value &&
            std::is_nothrow_default_constructible<key_compare>::value
        )
            : node_allocator_type()
            , key_compare()
        {}

        template <typename Allocator2>
        data(const Allocator2& alloc) noexcept
        (
            std::is_nothrow_copy_constructible<node_allocator_type>::value &&
            std::is_nothrow_default_constructible<key_compare>::value
        )
            : node_allocator_type(alloc)
            , key_compare()
        {}

        data(const key_compare& comp) noexcept
        (
            std::is_nothrow_default_constructible<node_allocator_type>::value &&
            std::is_nothrow_copy_constructible<key_compare>::value
        )
            : node_allocator_type()
            , key_compare(comp)
        {}

        template <typename Allocator2>
        data(const key_compare& comp, const Allocator2& alloc) noexcept
        (
            std::is_nothrow_copy_constructible<node_allocator_type>::value &&
            std::is_nothrow_copy_constructible<key_compare>::value
        )
            : node_allocator_type(alloc)
            , key_compare(comp)
        {}

        template <typename Allocator2>
        data(key_compare&& comp, const Allocator2& alloc) noexcept
        (
            std::is_nothrow_copy_constructible<node_allocator_type>::value &&
            std::is_nothrow_move_constructible<key_compare>::value
        )
            : node_allocator_type(alloc)
            , key_compare(std::move(comp))
        {}

        template <typename Allocator2>
        data(key_compare&& comp, Allocator2&& alloc) noexcept
        (
            std::is_nothrow_move_constructible<node_allocator_type>::value &&
            std::is_nothrow_move_constructible<key_compare>::value
        )
            : node_allocator_type(std::move(alloc))
            , key_compare(std::move(comp))
        {}
    };

    data data_;

public:

    //
    // ---- CONSTRUCTION AND DESTRUCTION --------------------------------------
    //

    rb_tree() noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<KeyCompare>::value
    )
    {}

    explicit rb_tree(const KeyCompare& comp) noexcept
    (
        std::is_nothrow_default_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<KeyCompare>::value
    )
        : data_(comp)
    {}

    template <typename Allocator2>
    explicit rb_tree(const Allocator2& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_default_constructible<KeyCompare>::value
    )
        : data_(alloc)
    {}

    template <typename Allocator2>
    explicit rb_tree(const KeyCompare& comp, const Allocator2& alloc) noexcept
    (
        std::is_nothrow_copy_constructible<Allocator>::value &&
        std::is_nothrow_copy_constructible<KeyCompare>::value
    )
        : data_(comp, alloc)
    {}

    rb_tree(const rb_tree& other)
        : data_
        (
            other.ref_to_comp(),
            sfl::dtl::allocator_traits<node_allocator_type>::select_on_container_copy_construction(other.ref_to_node_alloc())
        )
    {
        initialize_copy(other);
    }

    template <typename Allocator2>
    rb_tree(const rb_tree& other, const Allocator2& alloc)
        : data_(other.ref_to_comp(), alloc)
    {
        initialize_copy(other);
    }

    rb_tree(rb_tree&& other)
        : data_
        (
            std::move(other.ref_to_comp()),
            std::move(other.ref_to_node_alloc())
        )
    {
        initialize_move(other);
    }

    template <typename Allocator2>
    rb_tree(rb_tree&& other, const Allocator2& alloc)
        : data_
        (
            std::move(other.ref_to_comp()),
            alloc
        )
    {
        initialize_move(other);
    }

    ~rb_tree() noexcept
    {
        if (data_.root() != nullptr)
        {
            clear(data_.root());
        }
    }

    //
    // ---- ASSIGNMENT --------------------------------------------------------
    //

    rb_tree& operator=(const rb_tree& other)
    {
        assign_copy(other);
        return *this;
    }

    rb_tree& operator=(rb_tree&& other)
    {
        assign_move(other);
        return *this;
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
    // ---- ALLOCATOR ---------------------------------------------------------
    //

    SFL_NODISCARD
    node_allocator_type& ref_to_node_alloc() noexcept
    {
        return data_;
    }

    SFL_NODISCARD
    const node_allocator_type& ref_to_node_alloc() const noexcept
    {
        return data_;
    }

    SFL_NODISCARD
    allocator_type get_allocator() const
    {
        return allocator_type(ref_to_node_alloc());
    }

    //
    // ---- KEY COMPARE -------------------------------------------------------
    //

    SFL_NODISCARD
    key_compare& ref_to_comp() noexcept
    {
        return data_;
    }

    SFL_NODISCARD
    const key_compare& ref_to_comp() const noexcept
    {
        return data_;
    }

    SFL_NODISCARD
    key_compare key_comp() const
    {
        return ref_to_comp();
    }

    //
    // ---- ITERATORS ---------------------------------------------------------
    //

    SFL_NODISCARD
    iterator begin() noexcept
    {
        return iterator(data_.minimum());
    }

    SFL_NODISCARD
    const_iterator begin() const noexcept
    {
        return const_iterator(data_.minimum());
    }

    SFL_NODISCARD
    const_iterator cbegin() const noexcept
    {
        return const_iterator(data_.minimum());
    }

    SFL_NODISCARD
    iterator end() noexcept
    {
        return iterator(data_.header());
    }

    SFL_NODISCARD
    const_iterator end() const noexcept
    {
        return const_iterator(data_.header());
    }

    SFL_NODISCARD
    const_iterator cend() const noexcept
    {
        return const_iterator(data_.header());
    }

    SFL_NODISCARD
    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    SFL_NODISCARD
    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    SFL_NODISCARD
    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    SFL_NODISCARD
    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    SFL_NODISCARD
    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    SFL_NODISCARD
    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(begin());
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
        return sfl::dtl::allocator_traits<node_allocator_type>::max_size(ref_to_node_alloc());
    }

    //
    // ---- MODIFIERS ---------------------------------------------------------
    //

    void clear()
    {
        if (data_.root() != nullptr)
        {
            clear(data_.root());
        }

        data_.reset();
    }

    template <typename... Args>
    iterator emplace_equal(Args&&... args)
    {
        make_node_functor make_node(*this);
        auto* x = make_node(std::forward<Args>(args)...);
        auto res = calculate_position_for_insert_equal(key(x));
        insert(x, res.pos, res.left, data_.root(), data_.minimum());
        ++data_.size_;
        return iterator(x);
    }

    template <typename... Args>
    std::pair<iterator, bool> emplace_unique(Args&&... args)
    {
        make_node_functor make_node(*this);
        auto* x = make_node(std::forward<Args>(args)...);
        auto res = calculate_position_for_insert_unique(key(x));
        if (res.status)
        {
            insert(x, res.pos, res.left, data_.root(), data_.minimum());
            ++data_.size_;
            return std::make_pair(iterator(x), true);
        }
        else
        {
            drop_node(x);
            return std::make_pair(iterator(res.pos), false);
        }
    }

    template <typename... Args>
    iterator emplace_hint_equal(const_iterator hint, Args&&... args)
    {
        make_node_functor make_node(*this);
        auto* x = make_node(std::forward<Args>(args)...);
        auto res = calculate_position_for_insert_hint_equal(hint, key(x));
        insert(x, res.pos, res.left, data_.root(), data_.minimum());
        ++data_.size_;
        return iterator(x);
    }

    template <typename... Args>
    iterator emplace_hint_unique(const_iterator hint, Args&&... args)
    {
        make_node_functor make_node(*this);
        auto* x = make_node(std::forward<Args>(args)...);
        auto res = calculate_position_for_insert_hint_unique(hint, key(x));
        if (res.status)
        {
            insert(x, res.pos, res.left, data_.root(), data_.minimum());
            ++data_.size_;
            return iterator(x);
        }
        else
        {
            drop_node(x);
            return iterator(res.pos);
        }
    }

private:

    template <typename V, typename MakeNodeFunctor>
    iterator insert_equal(V&& value, MakeNodeFunctor& make_node)
    {
        auto res = calculate_position_for_insert_equal(KeyOfValue()(value));
        auto* x = make_node(std::forward<V>(value));
        insert(x, res.pos, res.left, data_.root(), data_.minimum());
        ++data_.size_;
        return iterator(x);
    }

    template <typename V, typename MakeNodeFunctor>
    std::pair<iterator, bool> insert_unique(V&& value, MakeNodeFunctor& make_node)
    {
        auto res = calculate_position_for_insert_unique(KeyOfValue()(value));
        if (res.status)
        {
            auto* x = make_node(std::forward<V>(value));
            insert(x, res.pos, res.left, data_.root(), data_.minimum());
            ++data_.size_;
            return std::make_pair(iterator(x), true);
        }
        else
        {
            return std::make_pair(iterator(res.pos), false);
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
        auto res = calculate_position_for_insert_hint_equal(hint, KeyOfValue()(value));
        make_node_functor make_node(*this);
        auto* x = make_node(std::forward<V>(value));
        insert(x, res.pos, res.left, data_.root(), data_.minimum());
        ++data_.size_;
        return iterator(x);
    }

    template <typename V>
    iterator insert_hint_unique(const_iterator hint, V&& value)
    {
        auto res = calculate_position_for_insert_hint_unique(hint, KeyOfValue()(value));
        if (res.status)
        {
            make_node_functor make_node(*this);
            auto* x = make_node(std::forward<V>(value));
            insert(x, res.pos, res.left, data_.root(), data_.minimum());
            ++data_.size_;
            return iterator(x);
        }
        else
        {
            return iterator(res.pos);
        }
    }

    iterator erase(iterator pos)
    {
        rb_tree_node_base* x = pos.node_;
        rb_tree_node_base* y = next(x);
        --data_.size_;
        remove(x, data_.root(), data_.minimum());
        drop_node(static_cast<node_type*>(x));
        return iterator(y);
    }

    iterator erase(const_iterator pos)
    {
        rb_tree_node_base* x = pos.to_iterator().node_;
        rb_tree_node_base* y = next(x);
        --data_.size_;
        remove(x, data_.root(), data_.minimum());
        drop_node(static_cast<node_type*>(x));
        return iterator(y);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        auto it = first.to_iterator();
        while (it != last)
        {
            it = erase(it);
        }
        return it;
    }

    template <typename K>
    size_type erase(const K& k)
    {
        const auto er = equal_range(k);
        const auto sz = std::distance(er.first, er.second);
        erase(er.first, er.second);
        return sz;
    }

    void swap(rb_tree& other)
    {
        swap(other, typename sfl::dtl::allocator_traits<node_allocator_type>::is_partially_propagable());
    }

    //
    // ---- LOOKUP ------------------------------------------------------------
    //

    template <typename K>
    SFL_NODISCARD
    iterator lower_bound(const K& k) noexcept
    {
        rb_tree_node_base* x = data_.root();
        rb_tree_node_base* y = data_.header();

        while (x != nullptr)
        {
            if (!ref_to_comp()(key(x), k))
            {
                y = x;
                x = x->left_;
            }
            else
            {
                x = x->right_;
            }
        }

        return iterator(y);
    }

    template <typename K>
    SFL_NODISCARD
    const_iterator lower_bound(const K& k) const noexcept
    {
        const rb_tree_node_base* x = data_.root();
        const rb_tree_node_base* y = data_.header();

        while (x != nullptr)
        {
            if (!ref_to_comp()(key(x), k))
            {
                y = x;
                x = x->left_;
            }
            else
            {
                x = x->right_;
            }
        }

        return const_iterator(y);
    }

    template <typename K>
    SFL_NODISCARD
    iterator upper_bound(const K& k) noexcept
    {
        rb_tree_node_base* x = data_.root();
        rb_tree_node_base* y = data_.header();

        while (x != nullptr)
        {
            if (ref_to_comp()(k, key(x)))
            {
                y = x;
                x = x->left_;
            }
            else
            {
                x = x->right_;
            }
        }

        return iterator(y);
    }

    template <typename K>
    SFL_NODISCARD
    const_iterator upper_bound(const K& k) const noexcept
    {
        const rb_tree_node_base* x = data_.root();
        const rb_tree_node_base* y = data_.header();

        while (x != nullptr)
        {
            if (ref_to_comp()(k, key(x)))
            {
                y = x;
                x = x->left_;
            }
            else
            {
                x = x->right_;
            }
        }

        return const_iterator(y);
    }

    template <typename K>
    SFL_NODISCARD
    std::pair<iterator, iterator> equal_range(const K& k) noexcept
    {
        rb_tree_node_base* x = data_.root();
        rb_tree_node_base* y = data_.header();

        while (x != nullptr)
        {
            if (ref_to_comp()(key(x), k))
            {
                x = x->right_;
            }
            else if (ref_to_comp()(k, key(x)))
            {
                y = x;
                x = x->left_;
            }
            else
            {
                // lower bound
                auto* x_lower = x->left_;
                auto* y_lower = x;
                while (x_lower != nullptr)
                {
                    if (!ref_to_comp()(key(x_lower), k))
                    {
                        y_lower = x_lower;
                        x_lower = x_lower->left_;
                    }
                    else
                    {
                        x_lower = x_lower->right_;
                    }
                }

                // upper bound
                auto* x_upper = x->right_;
                auto* y_upper = y;
                while (x_upper != nullptr)
                {
                    if (ref_to_comp()(k, key(x_upper)))
                    {
                        y_upper = x_upper;
                        x_upper = x_upper->left_;
                    }
                    else
                    {
                        x_upper = x_upper->right_;
                    }
                }

                return std::make_pair(iterator(y_lower), iterator(y_upper));
            }
        }

        return std::make_pair(iterator(y), iterator(y));
    }

    template <typename K>
    SFL_NODISCARD
    std::pair<const_iterator, const_iterator> equal_range(const K& k) const noexcept
    {
        const rb_tree_node_base* x = data_.root();
        const rb_tree_node_base* y = data_.header();

        while (x != nullptr)
        {
            if (ref_to_comp()(key(x), k))
            {
                x = x->right_;
            }
            else if (ref_to_comp()(k, key(x)))
            {
                y = x;
                x = x->left_;
            }
            else
            {
                // lower bound
                auto* x_lower = x->left_;
                auto* y_lower = x;
                while (x_lower != nullptr)
                {
                    if (!ref_to_comp()(key(x_lower), k))
                    {
                        y_lower = x_lower;
                        x_lower = x_lower->left_;
                    }
                    else
                    {
                        x_lower = x_lower->right_;
                    }
                }

                // upper bound
                auto* x_upper = x->right_;
                auto* y_upper = y;
                while (x_upper != nullptr)
                {
                    if (ref_to_comp()(k, key(x_upper)))
                    {
                        y_upper = x_upper;
                        x_upper = x_upper->left_;
                    }
                    else
                    {
                        x_upper = x_upper->right_;
                    }
                }

                return std::make_pair(const_iterator(y_lower), const_iterator(y_upper));
            }
        }

        return std::make_pair(const_iterator(y), const_iterator(y));
    }

    template <typename K>
    SFL_NODISCARD
    iterator find(const K& k) noexcept
    {
        auto it = lower_bound(k);

        if (it != end() && ref_to_comp()(k, key(it.node_)))
        {
            it = end();
        }

        return it;
    }

    template <typename K>
    SFL_NODISCARD
    const_iterator find(const K& k) const noexcept
    {
        auto it = lower_bound(k);

        if (it != end() && ref_to_comp()(k, key(it.node_)))
        {
            it = end();
        }

        return it;
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
        return find(k) != end();
    }

private:

    static rb_tree_node_base* minimum(rb_tree_node_base* x) noexcept
    {
        SFL_ASSERT(x != nullptr);

        while (x->left_ != nullptr)
        {
            x = x->left_;
        }

        return x;
    }

    static const rb_tree_node_base* minimum(const rb_tree_node_base* x) noexcept
    {
        SFL_ASSERT(x != nullptr);

        while (x->left_ != nullptr)
        {
            x = x->left_;
        }

        return x;
    }

    static rb_tree_node_base* maximum(rb_tree_node_base* x) noexcept
    {
        SFL_ASSERT(x != nullptr);

        while (x->right_ != nullptr)
        {
            x = x->right_;
        }

        return x;
    }

    static const rb_tree_node_base* maximum(const rb_tree_node_base* x) noexcept
    {
        SFL_ASSERT(x != nullptr);

        while (x->right_ != nullptr)
        {
            x = x->right_;
        }

        return x;
    }

    static rb_tree_node_base* next(rb_tree_node_base* x) noexcept
    {
        SFL_ASSERT(x != nullptr);

        if (x->right_ != nullptr)
        {
            return minimum(x->right_);
        }
        else
        {
            rb_tree_node_base* y = x->parent_;

            while (x == y->right_)
            {
                x = y;
                y = y->parent_;
            }

            return y;
        }
    }

    static const rb_tree_node_base* next(const rb_tree_node_base* x) noexcept
    {
        SFL_ASSERT(x != nullptr);

        if (x->right_ != nullptr)
        {
            return minimum(x->right_);
        }
        else
        {
            const rb_tree_node_base* y = x->parent_;

            while (x == y->right_)
            {
                x = y;
                y = y->parent_;
            }

            return y;
        }
    }

    static rb_tree_node_base* prev(rb_tree_node_base* x) noexcept
    {
        SFL_ASSERT(x != nullptr);

        if (x->left_ != nullptr)
        {
            return maximum(x->left_);
        }
        else
        {
            rb_tree_node_base* y = x->parent_;

            while (x == y->left_)
            {
                x = y;
                y = y->parent_;
            }

            return y;
        }
    }

    static const rb_tree_node_base* prev(const rb_tree_node_base* x) noexcept
    {
        SFL_ASSERT(x != nullptr);

        if (x->left_ != nullptr)
        {
            return maximum(x->left_);
        }
        else
        {
            const rb_tree_node_base* y = x->parent_;

            while (x == y->left_)
            {
                x = y;
                y = y->parent_;
            }

            return y;
        }
    }

    static void rotate_left(rb_tree_node_base* x) noexcept
    {
        /*
         *    |                       |
         *    x         left          y
         *   / \       rotate        / \
         *  a   y     -------->     x   c
         *     / \    @ node x     / \
         *    b   c               a   b
         */

        SFL_ASSERT(x != nullptr);
        SFL_ASSERT(x->right_ != nullptr);

        rb_tree_node_base* y = x->right_;

        x->right_ = y->left_;

        if (y->left_ != nullptr)
        {
            y->left_->parent_ = x;
        }

        y->parent_ = x->parent_;

        if (x == x->parent_->left_)
        {
            x->parent_->left_ = y;
        }
        else
        {
            x->parent_->right_ = y;
        }

        y->left_ = x;

        x->parent_ = y;
    }

    static void rotate_right(rb_tree_node_base* x) noexcept
    {
        /*
         *      |                   |
         *      x      right        y
         *     / \     rotate      / \
         *    y   c   -------->   a   x
         *   / \      @ node x       / \
         *  a   b                   b   c
         */

        SFL_ASSERT(x != nullptr);
        SFL_ASSERT(x->left_ != nullptr);

        rb_tree_node_base* y = x->left_;

        x->left_ = y->right_;

        if (y->right_ != nullptr)
        {
            y->right_->parent_ = x;
        }

        y->parent_ = x->parent_;

        if (x == x->parent_->right_)
        {
            x->parent_->right_ = y;
        }
        else
        {
            x->parent_->left_ = y;
        }

        y->right_ = x;

        x->parent_ = y;
    }

    static void insert(rb_tree_node_base* x,
                       rb_tree_node_base* parent,
                       bool insert_left,
                       rb_tree_node_base*& root,
                       rb_tree_node_base*& minimum) noexcept
    {
        SFL_ASSERT(x != nullptr);
        SFL_ASSERT(parent != nullptr);
        SFL_ASSERT(x != parent);

        x->parent_ = parent;
        x->left_   = nullptr;
        x->right_  = nullptr;
        x->color_  = rb_tree_node_color::red;

        if (insert_left)
        {
            parent->left_ = x; // If tree is empty, then this also updates root.

            if (parent == minimum)
            {
                minimum = x;
            }
        }
        else
        {
            parent->right_ = x;
        }

        insert_fixup(x, root);
    }

    static void insert_fixup(rb_tree_node_base* x, rb_tree_node_base*& root) noexcept
    {
        while (x != root && x->parent_->color_ == rb_tree_node_color::red)
        {
            if (x->parent_ == x->parent_->parent_->left_) // is z's parent a left child?
            {
                rb_tree_node_base* y = x->parent_->parent_->right_; // y is z's uncle

                if (y != nullptr && y->color_ == rb_tree_node_color::red) // are z's parent and uncle both red?
                {
                    // Case 1
                    x->parent_->color_ = rb_tree_node_color::black;
                    y->color_ = rb_tree_node_color::black;
                    x->parent_->parent_->color_ = rb_tree_node_color::red;
                    x = x->parent_->parent_;
                }
                else
                {
                    if (x == x->parent_->right_)
                    {
                        // Case 2
                        x = x->parent_;
                        rotate_left(x);
                    }

                    // Case 3
                    x->parent_->color_ = rb_tree_node_color::black;
                    x->parent_->parent_->color_ = rb_tree_node_color::red;
                    rotate_right(x->parent_->parent_);
                }
            }
            else // same as block above, but with "right" and "left" exchanged
            {
                rb_tree_node_base* y = x->parent_->parent_->left_;

                if (y != nullptr && y->color_ == rb_tree_node_color::red)
                {
                    x->parent_->color_ = rb_tree_node_color::black;
                    y->color_ = rb_tree_node_color::black;
                    x->parent_->parent_->color_ = rb_tree_node_color::red;
                    x = x->parent_->parent_;
                }
                else
                {
                    if (x == x->parent_->left_)
                    {
                        x = x->parent_;
                        rotate_right(x);
                    }

                    x->parent_->color_ = rb_tree_node_color::black;
                    x->parent_->parent_->color_ = rb_tree_node_color::red;
                    rotate_left(x->parent_->parent_);
                }
            }
        }

        root->color_ = rb_tree_node_color::black;
    }

    static void transplant(rb_tree_node_base* x, rb_tree_node_base* y)
    {
        SFL_ASSERT(x != nullptr);
        SFL_ASSERT(x->parent_ != nullptr);

        if (x == x->parent_->left_)
        {
            x->parent_->left_ = y;
        }
        else
        {
            x->parent_->right_ = y;
        }

        if (y != nullptr)
        {
            y->parent_ = x->parent_;
        }
    }

    static void remove(rb_tree_node_base* z, rb_tree_node_base*& root, rb_tree_node_base*& minimum)
    {
        SFL_ASSERT(z != nullptr);

        if (z == minimum)
        {
            minimum = next(z);
        }

        rb_tree_node_base* x;
        rb_tree_node_base* y = z;
        rb_tree_node_color y_original_color = y->color_;

        if (z->left_ == nullptr)
        {
            x = z->right_;
            transplant(z, z->right_);
        }
        else if (z->right_ == nullptr)
        {
            x = z->left_;
            transplant(z, z->left_);
        }
        else
        {
            y = rb_tree::minimum(z->right_);
            y_original_color = y->color_;
            x = y->right_;

            if (y != z->right_)
            {
                transplant(y, y->right_);
                y->right_ = z->right_;
                y->right_->parent_ = y;
            }
            else if (x != nullptr)
            {
                x->parent_ = y;
            }

            transplant(z, y);
            y->left_ = z->left_;
            y->left_->parent_ = y;
            y->color_ = z->color_;
        }

        if (y_original_color == rb_tree_node_color::black)
        {
            remove_fixup(x, root);
        }
    }

    static void remove_fixup(rb_tree_node_base* x, rb_tree_node_base*& root)
    {
        if (x == nullptr)
        {
            return;
        }

        while (x != root && x->color_ == rb_tree_node_color::black)
        {
            if (x == x->parent_->left_) // is x a left child?
            {
                rb_tree_node_base* w = x->parent_->right_; // w is x's sibling

                if (w->color_ == rb_tree_node_color::red)
                {
                    // Case 1
                    w->color_ = rb_tree_node_color::black;
                    x->parent_->color_ = rb_tree_node_color::red;
                    rotate_left(x->parent_);
                    w = x->parent_->right_;
                }

                if
                (
                    (w->left_  == nullptr || w->left_->color_  == rb_tree_node_color::black) &&
                    (w->right_ == nullptr || w->right_->color_ == rb_tree_node_color::black)
                )
                {
                    // Case 2
                    w->color_ = rb_tree_node_color::red;
                    x = x->parent_;
                }
                else
                {
                    if (w->right_ == nullptr || w->right_->color_ == rb_tree_node_color::black)
                    {
                        // Case 3
                        w->left_->color_ = rb_tree_node_color::black;
                        w->color_ = rb_tree_node_color::red;
                        rotate_right(w);
                        w = x->parent_->right_;
                    }

                    // Case 4
                    w->color_ = x->parent_->color_;
                    x->parent_->color_ = rb_tree_node_color::black;
                    w->right_->color_ = rb_tree_node_color::black;
                    rotate_left(x->parent_);
                    x = root;
                }
            }
            else // same as block above, but with "right" and "left" exchanged
            {
                rb_tree_node_base* w = x->parent_->left_;

                if (w->color_ == rb_tree_node_color::red)
                {
                    w->color_ = rb_tree_node_color::black;
                    x->parent_->color_ = rb_tree_node_color::red;
                    rotate_right(x->parent_);
                    w = x->parent_->left_;
                }

                if
                (
                    (w->right_ == nullptr || w->right_->color_ == rb_tree_node_color::black) &&
                    (w->left_  == nullptr || w->left_->color_  == rb_tree_node_color::black)
                )
                {
                    w->color_ = rb_tree_node_color::red;
                    x = x->parent_;
                }
                else
                {
                    if (w->left_ == nullptr || w->left_->color_ == rb_tree_node_color::black)
                    {
                        w->right_->color_ = rb_tree_node_color::black;
                        w->color_ = rb_tree_node_color::red;
                        rotate_left(w);
                        w = x->parent_->left_;
                    }

                    w->color_ = x->parent_->color_;
                    x->parent_->color_ = rb_tree_node_color::black;
                    w->left_->color_ = rb_tree_node_color::black;
                    rotate_right(x->parent_);
                    x = root;
                }
            }
        }

        x->color_ = rb_tree_node_color::black;
    }

    ///////////////////////////////////////////////////////////////////////////

    static const Key& key(const node_type* x) noexcept
    {
        return KeyOfValue()(*x->value_.get());
    }

    static const Key& key(const rb_tree_node_base* x) noexcept
    {
        return KeyOfValue()(*static_cast<const node_type*>(x)->value_.get());
    }

    ///////////////////////////////////////////////////////////////////////////

    node_type* allocate_node()
    {
        using node_allocator_pointer = typename sfl::dtl::allocator_traits<node_allocator_type>::pointer;
        node_allocator_pointer p = sfl::dtl::allocate(ref_to_node_alloc(), 1);
        return sfl::dtl::to_address(p);
    }

    void deallocate_node(node_type* p) noexcept
    {
        using node_allocator_pointer = typename sfl::dtl::allocator_traits<node_allocator_type>::pointer;
        node_allocator_pointer q = std::pointer_traits<node_allocator_pointer>::pointer_to(*p);
        sfl::dtl::deallocate(ref_to_node_alloc(), q, 1);
    }

    template <typename... Args>
    void construct_node(node_type* p, Args&&... args)
    {
        sfl::dtl::construct_at_a(ref_to_node_alloc(), p);

        SFL_TRY
        {
            sfl::dtl::construct_at_a
            (
                ref_to_node_alloc(),
                p->value_.get(),
                std::forward<Args>(args)...
            );
        }
        SFL_CATCH (...)
        {
            sfl::dtl::destroy_at_a(ref_to_node_alloc(), p);
            SFL_RETHROW;
        }
    }

    void destroy_node(node_type* p) noexcept
    {
        sfl::dtl::destroy_at_a(ref_to_node_alloc(), p->value_.get());
        sfl::dtl::destroy_at_a(ref_to_node_alloc(), p);
    }

    class make_node_functor
    {
    private:

        rb_tree& tree_;

    public:

        make_node_functor(rb_tree& tree)
            : tree_(tree)
        {}

        template <typename... Args>
        node_type* operator()(Args&&... args)
        {
            auto* p = tree_.allocate_node();

            SFL_TRY
            {
                tree_.construct_node(p, std::forward<Args>(args)...);
            }
            SFL_CATCH (...)
            {
                tree_.deallocate_node(p);
                SFL_RETHROW;
            }

            return p;
        }
    };

    class make_node_with_recycling_functor
    {
    private:

        rb_tree& tree_;

        rb_tree_node_base* root_;

    public:

        make_node_with_recycling_functor(rb_tree& tree)
            : tree_(tree)
            , root_(tree.data_.root())
        {
            tree.data_.reset();
        }

        ~make_node_with_recycling_functor()
        {
            if (root_ != nullptr)
            {
                tree_.clear(root_);
            }
        }

        template <typename... Args>
        node_type* operator()(Args&&... args)
        {
            auto* p = this->allocate_node();

            SFL_TRY
            {
                tree_.construct_node(p, std::forward<Args>(args)...);
            }
            SFL_CATCH (...)
            {
                tree_.deallocate_node(p);
                SFL_RETHROW;
            }

            return p;
        }

    private:

        node_type* allocate_node()
        {
            if (root_ == nullptr)
            {
                return tree_.allocate_node();
            }
            else
            {
                rb_tree_node_base* node = tree_.minimum(root_);

                if (node != root_)
                {
                    node->parent_->left_ = node->right_;

                    if (node->right_ != nullptr)
                    {
                        node->right_->parent_ = node->parent_;
                    }
                }
                else
                {
                    root_ = node->right_;

                    if (node->right_ != nullptr)
                    {
                        node->right_->parent_ = nullptr;
                    }
                }

                tree_.destroy_node(static_cast<node_type*>(node));

                return static_cast<node_type*>(node);
            }
        }
    };

    void drop_node(node_type* p) noexcept
    {
        destroy_node(p);
        deallocate_node(p);
    }

    ///////////////////////////////////////////////////////////////////////////

    struct position_for_insert_equal
    {
        rb_tree_node_base* pos;
        bool               left;
    };

    struct position_for_insert_unique
    {
        rb_tree_node_base* pos;
        bool               left;
        bool               status;
    };

    template <typename K>
    position_for_insert_equal calculate_position_for_insert_equal(const K& k)
    {
        rb_tree_node_base* x = data_.root();
        rb_tree_node_base* y = data_.header();

        bool comp = true;

        while (x != nullptr)
        {
            y = x;

            comp = ref_to_comp()(k, key(x));

            if (comp)
            {
                x = x->left_;
            }
            else
            {
                x = x->right_;
            }
        }

        return position_for_insert_equal{y, comp};
    }

    template <typename K>
    position_for_insert_unique calculate_position_for_insert_unique(const K& k)
    {
        rb_tree_node_base* x = data_.root();
        rb_tree_node_base* y = data_.header();

        bool comp = true;

        while (x != nullptr)
        {
            y = x;

            comp = ref_to_comp()(k, key(x));

            if (comp)
            {
                x = x->left_;
            }
            else
            {
                x = x->right_;
            }
        }

        if (comp && y == data_.minimum())
        {
            return position_for_insert_unique{y, comp, true};
        }

        rb_tree_node_base* z = comp ? prev(y) : y;

        if (z != data_.header() && !ref_to_comp()(key(z), k))
        {
            return position_for_insert_unique{z, comp, false};
        }

        return position_for_insert_unique{y, comp, true};
    }

    template <typename K>
    position_for_insert_equal calculate_position_for_insert_hint_equal(const_iterator hint, const K& k)
    {
        if (hint == cend())
        {
            if (empty())
            {
                return calculate_position_for_insert_equal(k);
            }
            else
            {
                const_iterator maximum = std::prev(hint);

                if (!ref_to_comp()(k, key(maximum.node_))) // k >= maximum
                {
                    return position_for_insert_equal{maximum.to_iterator().node_, false};
                }
                else
                {
                    return calculate_position_for_insert_equal(k);
                }
            }
        }
        else if (!ref_to_comp()(key(hint.node_), k)) // k <= hint
        {
            if (hint == cbegin()) // hint == minimum
            {
                return position_for_insert_equal{hint.to_iterator().node_, true};
            }
            else
            {
                const_iterator prev = std::prev(hint);

                if (!ref_to_comp()(k, key(prev.node_))) // prev <= k
                {
                    if (prev.node_->right_ == nullptr)
                    {
                        return position_for_insert_equal{prev.to_iterator().node_, false};
                    }
                    else
                    {
                        return position_for_insert_equal{hint.to_iterator().node_, true};
                    }
                }
                else // prev > k
                {
                    return calculate_position_for_insert_equal(k);
                }
            }
        }
        else // hint < k
        {
            if (hint == std::prev(cend())) // hint == maximum
            {
                return position_for_insert_equal{hint.to_iterator().node_, false};
            }
            else
            {
                const_iterator next = std::next(hint);

                if (!ref_to_comp()(key(next.node_), k)) // k <= next
                {
                    if (next.node_->left_ == nullptr)
                    {
                        return position_for_insert_equal{next.to_iterator().node_, true};
                    }
                    else
                    {
                        return position_for_insert_equal{hint.to_iterator().node_, false};
                    }
                }
                else // k > next
                {
                    return calculate_position_for_insert_equal(k);
                }
            }
        }
    }

    template <typename K>
    position_for_insert_unique calculate_position_for_insert_hint_unique(const_iterator hint, const K& k)
    {
        if (hint == cend())
        {
            if (empty())
            {
                return calculate_position_for_insert_unique(k);
            }
            else
            {
                const_iterator maximum = std::prev(hint);

                if (ref_to_comp()(key(maximum.node_), k)) // maximum < k
                {
                    return position_for_insert_unique{maximum.to_iterator().node_, false, true};
                }
                else
                {
                    return calculate_position_for_insert_unique(k);
                }
            }
        }
        else if (ref_to_comp()(k, key(hint.node_))) // k < hint
        {
            if (hint == cbegin()) // hint == minimum
            {
                return position_for_insert_unique{hint.to_iterator().node_, true, true};
            }
            else
            {
                const_iterator prev = std::prev(hint);

                if (ref_to_comp()(key(prev.node_), k)) // prev < k
                {
                    if (prev.node_->right_ == nullptr)
                    {
                        return position_for_insert_unique{prev.to_iterator().node_, false, true};
                    }
                    else
                    {
                        return position_for_insert_unique{hint.to_iterator().node_, true, true};
                    }
                }
                else // prev >= k
                {
                    return calculate_position_for_insert_unique(k);
                }
            }
        }
        else if (ref_to_comp()(key(hint.node_), k)) // hint < k
        {
            if (hint == std::prev(cend())) // hint == maximum
            {
                return position_for_insert_unique{hint.to_iterator().node_, false, true};
            }
            else
            {
                const_iterator next = std::next(hint);

                if (ref_to_comp()(k, key(next.node_))) // k < next
                {
                    if (next.node_->left_ == nullptr)
                    {
                        return position_for_insert_unique{next.to_iterator().node_, true, true};
                    }
                    else
                    {
                        return position_for_insert_unique{hint.to_iterator().node_, false, true};
                    }
                }
                else // k >= next
                {
                    return calculate_position_for_insert_unique(k);
                }
            }
        }
        else // k == hint
        {
            return position_for_insert_unique{hint.to_iterator().node_, false, false};
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    template <typename MakeNodeFunctor>
    rb_tree_node_base* copy(const rb_tree_node_base* x, MakeNodeFunctor& make_node)
    {
        SFL_ASSERT(x != nullptr);

        rb_tree_node_base* y = make_node(*static_cast<const node_type*>(x)->value_.get());

        y->color_ = x->color_;
        y->left_  = nullptr;
        y->right_ = nullptr;

        SFL_TRY
        {
            if (x->left_ != nullptr)
            {
                y->left_ = copy(x->left_, make_node);
                y->left_->parent_ = y;
            }

            if (x->right_ != nullptr)
            {
                y->right_ = copy(x->right_, make_node);
                y->right_->parent_ = y;
            }
        }
        SFL_CATCH (...)
        {
            drop_node(static_cast<node_type*>(y));
            SFL_RETHROW;
        }

        return y;
    }

    template <typename MakeNodeFunctor>
    rb_tree_node_base* move(rb_tree_node_base* x, MakeNodeFunctor& make_node)
    {
        SFL_ASSERT(x != nullptr);

        rb_tree_node_base* y = make_node(std::move(*static_cast<node_type*>(x)->value_.get()));

        y->color_ = x->color_;
        y->left_  = nullptr;
        y->right_ = nullptr;

        SFL_TRY
        {
            if (x->left_ != nullptr)
            {
                y->left_ = move(x->left_, make_node);
                y->left_->parent_ = y;
            }

            if (x->right_ != nullptr)
            {
                y->right_ = move(x->right_, make_node);
                y->right_->parent_ = y;
            }
        }
        SFL_CATCH (...)
        {
            drop_node(static_cast<node_type*>(y));
            SFL_RETHROW;
        }

        return y;
    }

    void clear(rb_tree_node_base* x)
    {
        SFL_ASSERT(x != nullptr);

        if (x->left_ != nullptr)
        {
            clear(x->left_);
        }

        if (x->right_ != nullptr)
        {
            clear(x->right_);
        }

        drop_node(static_cast<node_type*>(x));
    }

    ///////////////////////////////////////////////////////////////////////////

    void initialize_copy(const rb_tree& other)
    {
        if (other.data_.root() != nullptr)
        {
            make_node_functor make_node(*this);
            data_.root() = copy(other.data_.root(), make_node);
            data_.minimum() = minimum(data_.root());
            data_.size_ = other.data_.size_;
        }
    }

    void initialize_move(rb_tree& other)
    {
        initialize_move(other, typename sfl::dtl::allocator_traits<node_allocator_type>::is_partially_propagable());
    }

    void initialize_move(rb_tree& other, std::true_type)
    {
        if (other.data_.root() != nullptr)
        {
            make_node_functor make_node(*this);
            data_.root() = move(other.data_.root(), make_node);
            data_.minimum() = minimum(data_.root());
            data_.size_ = other.data_.size_;
        }
    }

    void initialize_move(rb_tree& other, std::false_type)
    {
        initialize_move(other, std::false_type(), typename sfl::dtl::allocator_traits<node_allocator_type>::is_always_equal());
    }

    void initialize_move(rb_tree& other, std::false_type, std::true_type)
    {
        data_.root() = other.data_.root();
        data_.minimum() = other.data_.minimum();
        data_.size_ = other.data_.size_;
        other.data_.reset();
    }

    void initialize_move(rb_tree& other, std::false_type, std::false_type)
    {
        if (ref_to_node_alloc() == other.ref_to_node_alloc())
        {
            initialize_move(other, std::false_type(), std::true_type());
        }
        else
        {
            initialize_move(other, std::true_type());
        }
    }

    void assign_copy(const rb_tree& other)
    {
        if (this != &other)
        {
            if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_copy_assignment::value)
            {
                if (ref_to_node_alloc() != other.ref_to_node_alloc())
                {
                    clear();
                }

                ref_to_node_alloc() = other.ref_to_node_alloc();
            }

            ref_to_comp() = other.ref_to_comp();

            make_node_with_recycling_functor make_node(*this);

            if (other.data_.root() != nullptr)
            {
                data_.root() = copy(other.data_.root(), make_node);
                data_.minimum() = minimum(data_.root());
                data_.size_ = other.data_.size_;
            }
        }
    }

    void assign_move(rb_tree& other)
    {
        assign_move(other, typename sfl::dtl::allocator_traits<node_allocator_type>::is_partially_propagable());
    }

    void assign_move(rb_tree& other, std::true_type)
    {
        if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_move_assignment::value)
        {
            if (ref_to_node_alloc() != other.ref_to_node_alloc())
            {
                clear();
            }

            ref_to_node_alloc() = std::move(other.ref_to_node_alloc());
        }

        ref_to_comp() = std::move(other.ref_to_comp());

        make_node_with_recycling_functor make_node(*this);

        if (other.data_.root() != nullptr)
        {
            data_.root() = move(other.data_.root(), make_node);
            data_.minimum() = minimum(data_.root());
            data_.size_ = other.data_.size_;
        }
    }

    void assign_move(rb_tree& other, std::false_type)
    {
        assign_move(other, std::false_type(), typename sfl::dtl::allocator_traits<node_allocator_type>::is_always_equal());
    }

    void assign_move(rb_tree& other, std::false_type, std::true_type)
    {
        if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_move_assignment::value)
        {
            ref_to_node_alloc() = std::move(other.ref_to_node_alloc());
        }

        ref_to_comp() = std::move(other.ref_to_comp());

        clear();

        data_.root() = other.data_.root();
        data_.minimum() = other.data_.minimum();
        data_.size_ = other.data_.size_;

        other.data_.reset();
    }

    void assign_move(rb_tree& other, std::false_type, std::false_type)
    {
        if (ref_to_node_alloc() == other.ref_to_node_alloc())
        {
            assign_move(other, std::false_type(), std::true_type());
        }
        else
        {
            assign_move(other, std::true_type());
        }
    }

    void swap(rb_tree& other, std::true_type)
    {
        SFL_ASSERT(this->size() < this->max_size());
        SFL_ASSERT(other.size() < other.max_size());

        using std::swap;

        rb_tree_node_base* old_this = this->data_.root();
        rb_tree_node_base* old_other = other.data_.root();

        if (old_this != nullptr)
        {
            old_this->parent_ = nullptr;
        }
        if (old_other != nullptr)
        {
            old_other->parent_ = nullptr;
        }

        this->data_.reset();
        other.data_.reset();

        if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value)
        {
            swap(ref_to_node_alloc(), other.ref_to_node_alloc()); // noexcept
        }

        SFL_TRY
        {
            struct help
            {
                static rb_tree_node_base* next_to_swap(rb_tree_node_base* x)
                {
                    SFL_ASSERT(x != nullptr);

                    if (x->left_ != nullptr)
                    {
                        return next_to_swap(x->left_);
                    }
                    else if (x->right_ != nullptr)
                    {
                        return next_to_swap(x->right_);
                    }
                    else
                    {
                        return x;
                    }
                }

                static rb_tree_node_base* detach(rb_tree_node_base* x)
                {
                    SFL_ASSERT(x != nullptr);
                    SFL_ASSERT(x->left_ == nullptr);
                    SFL_ASSERT(x->right_ == nullptr);

                    rb_tree_node_base* parent = x->parent_;

                    if (parent != nullptr)
                    {
                        if (x == parent->left_)
                        {
                            parent->left_ = nullptr;
                        }
                        else
                        {
                            parent->right_ = nullptr;
                        }
                    }

                    return parent;
                }
            };

            rb_tree_node_base* p_this = old_this;
            rb_tree_node_base* p_other = old_other;

            while (true)
            {
                bool done = true;

                if (p_this != nullptr)
                {
                    done = false;

                    p_this = help::next_to_swap(p_this);

                    if
                    (
                        sfl::dtl::allocator_traits<node_allocator_type>::is_storage_unpropagable
                        (
                            this->ref_to_node_alloc(),
                            static_cast<node_type*>(p_this)
                        )
                        ||
                        (
                            !sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value
                            &&
                            this->ref_to_node_alloc() != other.ref_to_node_alloc()
                        )
                    )
                    {
                        other.insert_equal(std::move(*static_cast<node_type*>(p_this)->value_.get())); // may throw exception

                        rb_tree_node_base* p_this_parent = help::detach(p_this);

                        this->drop_node(static_cast<node_type*>(p_this));

                        p_this = p_this_parent;
                    }
                    else
                    {
                        auto res = other.calculate_position_for_insert_equal(key(p_this));

                        rb_tree_node_base* p_this_parent = help::detach(p_this);

                        insert(p_this, res.pos, res.left, other.data_.root(), other.data_.minimum());

                        ++other.data_.size_;

                        p_this = p_this_parent;
                    }
                }

                if (p_other != nullptr)
                {
                    done = false;

                    p_other = help::next_to_swap(p_other);

                    if
                    (
                        sfl::dtl::allocator_traits<node_allocator_type>::is_storage_unpropagable
                        (
                            other.ref_to_node_alloc(),
                            static_cast<node_type*>(p_other)
                        )
                        ||
                        (
                            !sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value
                            &&
                            this->ref_to_node_alloc() != other.ref_to_node_alloc()
                        )
                    )
                    {
                        this->insert_equal(std::move(*static_cast<node_type*>(p_other)->value_.get())); // may throw exception

                        rb_tree_node_base* p_other_parent = help::detach(p_other);

                        other.drop_node(static_cast<node_type*>(p_other));

                        p_other = p_other_parent;
                    }
                    else
                    {
                        auto res = this->calculate_position_for_insert_equal(key(p_other));

                        rb_tree_node_base* p_other_parent = help::detach(p_other);

                        insert(p_other, res.pos, res.left, this->data_.root(), this->data_.minimum());

                        ++this->data_.size_;

                        p_other = p_other_parent;
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
            struct help
            {
                static rb_tree_node_base* next_to_remove(rb_tree_node_base* x)
                {
                    SFL_ASSERT(x != nullptr);

                    if (x->left_ != nullptr)
                    {
                        return next_to_remove(x->left_);
                    }
                    else if (x->right_ != nullptr)
                    {
                        return next_to_remove(x->right_);
                    }
                    else
                    {
                        return x;
                    }
                }

                static rb_tree_node_base* detach(rb_tree_node_base* x)
                {
                    SFL_ASSERT(x != nullptr);
                    SFL_ASSERT(x->left_ == nullptr);
                    SFL_ASSERT(x->right_ == nullptr);

                    rb_tree_node_base* parent = x->parent_;

                    if (parent != nullptr)
                    {
                        if (x == parent->left_)
                        {
                            parent->left_ = nullptr;
                        }
                        else
                        {
                            parent->right_ = nullptr;
                        }
                    }

                    return parent;
                }
            };

            rb_tree_node_base* p_this = old_this;
            rb_tree_node_base* p_other = old_other;

            while (p_this != nullptr)
            {
                p_this = help::next_to_remove(p_this);

                rb_tree_node_base* p_this_parent = help::detach(p_this);

                if
                (
                    sfl::dtl::allocator_traits<node_allocator_type>::is_storage_unpropagable
                    (
                        this->ref_to_node_alloc(),
                        static_cast<node_type*>(p_this)
                    )
                )
                {
                    this->drop_node(static_cast<node_type*>(p_this));
                }
                else
                {
                    if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value)
                    {
                        other.drop_node(static_cast<node_type*>(p_this));
                    }
                    else
                    {
                        this->drop_node(static_cast<node_type*>(p_this));
                    }
                }

                p_this = p_this_parent;
            }

            while (p_other != nullptr)
            {
                p_other = help::next_to_remove(p_other);

                rb_tree_node_base* p_other_parent = help::detach(p_other);

                if
                (
                    sfl::dtl::allocator_traits<node_allocator_type>::is_storage_unpropagable
                    (
                        other.ref_to_node_alloc(),
                        static_cast<node_type*>(p_other)
                    )
                )
                {
                    other.drop_node(static_cast<node_type*>(p_other));
                }
                else
                {
                    if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value)
                    {
                        this->drop_node(static_cast<node_type*>(p_other));
                    }
                    else
                    {
                        other.drop_node(static_cast<node_type*>(p_other));
                    }
                }

                p_other = p_other_parent;
            }

            SFL_RETHROW;
        }
    }

    void swap(rb_tree& other, std::false_type)
    {
        swap(other, std::false_type(), typename sfl::dtl::allocator_traits<node_allocator_type>::is_always_equal());
    }

    void swap(rb_tree& other, std::false_type, std::true_type)
    {
        using std::swap;

        if (sfl::dtl::allocator_traits<node_allocator_type>::propagate_on_container_swap::value)
        {
            swap(ref_to_node_alloc(), other.ref_to_node_alloc());
        }

        swap(ref_to_comp(), other.ref_to_comp());

        swap(data_.root(), other.data_.root());
        swap(data_.minimum(), other.data_.minimum());
        swap(data_.size_, other.data_.size_);
    }

    void swap(rb_tree& other, std::false_type, std::false_type)
    {
        if (ref_to_node_alloc() == other.ref_to_node_alloc())
        {
            swap(other, std::false_type(), std::true_type());
        }
        else
        {
            swap(other, std::true_type());
        }
    }
};

//
// ---- NON-MEMBER FUNCTIONS --------------------------------------------------
//

template < typename Key,
           typename Value,
           typename KeyOfValue,
           typename KeyCompare,
           typename Allocator,
           typename UpperLevelContainer >
SFL_NODISCARD
bool operator==
(
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& x,
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& y
)
{
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template < typename Key,
           typename Value,
           typename KeyOfValue,
           typename KeyCompare,
           typename Allocator,
           typename UpperLevelContainer >
SFL_NODISCARD
bool operator!=
(
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& x,
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& y
)
{
    return !(x == y);
}

template < typename Key,
           typename Value,
           typename KeyOfValue,
           typename KeyCompare,
           typename Allocator,
           typename UpperLevelContainer >
SFL_NODISCARD
bool operator<
(
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& x,
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& y
)
{
    return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template < typename Key,
           typename Value,
           typename KeyOfValue,
           typename KeyCompare,
           typename Allocator,
           typename UpperLevelContainer >
SFL_NODISCARD
bool operator>
(
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& x,
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& y
)
{
    return y < x;
}

template < typename Key,
           typename Value,
           typename KeyOfValue,
           typename KeyCompare,
           typename Allocator,
           typename UpperLevelContainer >
SFL_NODISCARD
bool operator<=
(
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& x,
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& y
)
{
    return !(y < x);
}

template < typename Key,
           typename Value,
           typename KeyOfValue,
           typename KeyCompare,
           typename Allocator,
           typename UpperLevelContainer >
SFL_NODISCARD
bool operator>=
(
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& x,
    const rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& y
)
{
    return !(x < y);
}

template < typename Key,
           typename Value,
           typename KeyOfValue,
           typename KeyCompare,
           typename Allocator,
           typename UpperLevelContainer >
void swap
(
    rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& x,
    rb_tree<Key, Value, KeyOfValue, KeyCompare, Allocator, UpperLevelContainer>& y
)
{
    x.swap(y);
}

} //namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_RB_TREE_HPP_INCLUDED
