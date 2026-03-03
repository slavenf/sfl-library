#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/detail/bit/bit_cast.hpp"

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <type_traits>

#if SFL_CPP_VERSION >= SFL_CPP_20

template <typename T>
void test(std::size_t n)
{
    using unsigned_t = std::conditional_t
    <
        sizeof(T) == 4,
        std::uint32_t,
        std::conditional_t
        <
            sizeof(T) == 8,
            std::uint64_t,
            std::false_type
        >
    >;

    static_assert(!std::is_same_v<unsigned_t, std::false_type>);

    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_int_distribution<unsigned_t> dist
    (
        std::numeric_limits<unsigned_t>::min(),
        std::numeric_limits<unsigned_t>::max()
    );

    for (std::size_t i = 0; i < 10; ++i)
    {
        for (std::size_t j = 0; j < (n / 10); ++j)
        {
            const T value = static_cast<T>(dist(gen));

            const unsigned_t h_11 = sfl::dtl::bit_cast_impl_11<unsigned_t>(value);
            const unsigned_t h_20 = sfl::dtl::bit_cast_impl_20<unsigned_t>(value);

            if (h_11 != h_20)
            {
                std::cout << "ERROR: Hash mismatch\n"
                        << "  - value: " << value << "\n"
                        << "  - h_11: " << h_11 << "\n"
                        << "  - h_20: " << h_20 << std::endl;
                std::abort();
            }
        }

        std::cout << " " << ((i + 1) * 10) << "%" << std::endl;
    }
}

int main()
{
    constexpr std::size_t n = 1'000'000;

    std::cout << "Testing with `int`..." << std::endl;
    test<int>(n);

    std::cout << "Testing with `long`..." << std::endl;
    test<long>(n);

    std::cout << "Testing with `long long`..." << std::endl;
    test<long long>(n);

    std::cout << "Testing with `float`..." << std::endl;
    test<float>(n);

    std::cout << "Testing with `double`..." << std::endl;
    test<double>(n);
}

#else // before C++20

int main()
{
    // Nothing to do
}

#endif // before C++20
