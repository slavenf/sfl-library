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

#ifndef SFL_DETAIL_STATIC_POOL_HPP_INCLUDED
#define SFL_DETAIL_STATIC_POOL_HPP_INCLUDED

#include <sfl/detail/cpp.hpp>

#include <cstddef> // size_t, ptrdiff_t
#include <memory> // addressof
#include <type_traits> // is_constant_evaluated

namespace sfl
{

namespace dtl
{

template <typename T, std::size_t N>
class static_pool
{
    static_assert(N > 0, "N must be greater than zero.");

public:

    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

private:

    union bucket
    {
    public:

        bucket* next_;

        T value_;

    public:

        SFL_CONSTEXPR_20
        bucket() noexcept
        {}

        bucket(const bucket& other) = delete;

        bucket(bucket&& other) = delete;

        bucket& operator=(const bucket& other) = delete;

        bucket& operator=(bucket&& other) = delete;

        SFL_CONSTEXPR_20
        ~bucket()
        {}
    };

    bucket buckets_[N];

    size_type n_allocated = 0;

    size_type n_initialized = 0;

    bucket* next_ = nullptr;

private:

    SFL_CONSTEXPR_20
    bucket* get_bucket_ptr(T* p) noexcept
    {
        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (std::is_constant_evaluated())
        {
            for (size_type i = 0; i < N; ++i)
            {
                if (p == std::addressof(buckets_[i].value_))
                {
                    return std::addressof(buckets_[i]);
                }
            }
            return nullptr;
        }
        else
        #endif
        {
            return reinterpret_cast<bucket*>(p);
        }
    }

    SFL_CONSTEXPR_20
    const bucket* get_bucket_ptr(const T* p) const noexcept
    {
        #if SFL_CPP_VERSION >= SFL_CPP_20
        if (std::is_constant_evaluated())
        {
            for (size_type i = 0; i < N; ++i)
            {
                if (p == std::addressof(buckets_[i].value_))
                {
                    return std::addressof(buckets_[i]);
                }
            }
            return nullptr;
        }
        else
        #endif
        {
            return reinterpret_cast<const bucket*>(p);
        }
    }

public:

    SFL_CONSTEXPR_20
    static_pool() noexcept
    {}

    static_pool(const static_pool& other) = delete;

    static_pool(static_pool&& other) = delete;

    static_pool& operator=(const static_pool& other) = delete;

    static_pool& operator=(static_pool&& other) = delete;

    SFL_CONSTEXPR_20
    ~static_pool()
    {
        SFL_ASSERT(empty());
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    bool empty() const noexcept
    {
        return n_allocated == 0;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    bool full() const noexcept
    {
        return n_allocated == N;
    }

    SFL_NODISCARD
    static constexpr size_type max_size() noexcept
    {
        return N;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    bool contains(const T* p) const noexcept
    {
        const bucket* q = get_bucket_ptr(p);
        return q != nullptr && buckets_ <= q && q < buckets_ + N;
    }

    SFL_NODISCARD
    SFL_CONSTEXPR_20
    T* allocate() noexcept
    {
        SFL_ASSERT(n_allocated < N);

        if (n_allocated < n_initialized)
        {
            // Nothing to do.
        }
        else
        {
            SFL_ASSERT(n_initialized < N);

            bucket* p = std::addressof(buckets_[n_initialized++]);

            p->next_ = nullptr;

            next_ = p;
        }

        bucket* p = next_;

        next_ = p->next_;

        ++n_allocated;

        return std::addressof(p->value_);
    }

    SFL_CONSTEXPR_20
    void deallocate(T* p) noexcept
    {
        SFL_ASSERT(n_allocated > 0);
        SFL_ASSERT(contains(p));

        bucket* q = get_bucket_ptr(p);

        q->next_ = next_;

        next_ = q;

        --n_allocated;
    }
};

} // namespace dtl

} // namespace sfl

#endif // SFL_DETAIL_STATIC_POOL_HPP_INCLUDED
