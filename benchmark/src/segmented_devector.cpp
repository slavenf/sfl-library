#include "table.hpp"

#include <boost/container/deque.hpp>
#include <sfl/segmented_devector.hpp>
#include <deque>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random> // mt19937, random_device
#include <unordered_map>
#include <vector>

template <typename Vector>
std::chrono::duration<double, std::milli> test_emplace_front(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Vector vec;

        const auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < num_elements; ++i)
        {
            std::uint64_t elem = gen();
            vec.emplace_front(elem);
            sum += elem;
        }

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += vec.size();
    }

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Vector>
std::chrono::duration<double, std::milli> test_emplace_back(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Vector vec;

        const auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < num_elements; ++i)
        {
            std::uint64_t elem = gen();
            vec.emplace_back(elem);
            sum += elem;
        }

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += vec.size();
    }

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Vector>
std::chrono::duration<double, std::milli> test_emplace_at_begin(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Vector vec;

        const auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < num_elements; ++i)
        {
            std::uint64_t elem = gen();
            vec.emplace(vec.begin(), elem);
            sum += elem;
        }

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += vec.size();
    }

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Vector>
std::chrono::duration<double, std::milli> test_emplace_at_end(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Vector vec;

        const auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < num_elements; ++i)
        {
            std::uint64_t elem = gen();
            vec.emplace(vec.end(), elem);
            sum += elem;
        }

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += vec.size();
    }

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Vector>
std::chrono::duration<double, std::milli> test_emplace_at_random(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Vector vec;

        const auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < num_elements; ++i)
        {
            auto pos = vec.cbegin() + (i != 0 ? gen() % i : 0);
            std::uint64_t elem = gen();
            vec.emplace(pos, elem);
            sum += elem;
        }

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += vec.size();
    }

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Vector>
std::chrono::duration<double, std::milli> test_erase_at_random(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Vector vec;

        for (int i = 0; i < num_elements; ++i)
        {
            vec.emplace_back(gen());
        }

        const auto start = std::chrono::steady_clock::now();

        for (int i = num_elements - 1; i > 0; --i)
        {
            auto pos = vec.cbegin() + i % gen();
            vec.erase(pos);
        }

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += vec.size();
    }

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Vector>
std::chrono::duration<double, std::milli> test_iterate_all(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Vector vec;

        for (int i = 0; i < num_elements; ++i)
        {
            std::uint64_t elem = gen();
            vec.emplace_back(elem);
            sum += elem;
        }

        const auto start = std::chrono::steady_clock::now();

        for (const auto& elem : vec)
        {
            sum += elem * 2;
        }

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);
    }

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Vector>
std::chrono::duration<double, std::milli> test_random_access(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Vector vec;

        for (int i = 0; i < num_elements; ++i)
        {
            std::uint64_t elem = gen();
            vec.emplace_back(elem);
            sum += elem;
        }

        const auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < num_elements; ++i)
        {
            sum += vec[gen() % (num_elements - 1)] * 2;
        }

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);
    }

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

int main()
{
    {
        constexpr int num_elements = 10'000'000;
        constexpr int num_iterations = 20;

        sfl::benchmark::table table;

        table.set_title("emplace_front (", num_elements," integers)");

        table.set_header("Container", "Time");

        table.add_row("sfl::segmented_devector<int, 1024>", test_emplace_front<sfl::segmented_devector<int, 1024>>(num_elements, num_iterations));
        table.add_row("sfl::segmented_devector<int, 32768>", test_emplace_front<sfl::segmented_devector<int, 32768>>(num_elements, num_iterations));
        table.add_row("std::deque<int>", test_emplace_front<std::deque<int>>(num_elements, num_iterations));
        table.add_row("boost::container::deque<int>", test_emplace_front<boost::container::deque<int>>(num_elements, num_iterations));

        std::cout << table << std::endl;
    }

    {
        constexpr int num_elements = 10'000'000;
        constexpr int num_iterations = 20;

        sfl::benchmark::table table;

        table.set_title("emplace_back (", num_elements," integers)");

        table.set_header("Container", "Time");

        table.add_row("sfl::segmented_devector<int, 1024>", test_emplace_back<sfl::segmented_devector<int, 1024>>(num_elements, num_iterations));
        table.add_row("sfl::segmented_devector<int, 32768>", test_emplace_back<sfl::segmented_devector<int, 32768>>(num_elements, num_iterations));
        table.add_row("std::deque<int>", test_emplace_back<std::deque<int>>(num_elements, num_iterations));
        table.add_row("boost::container::deque<int>", test_emplace_back<boost::container::deque<int>>(num_elements, num_iterations));

        std::cout << table << std::endl;
    }

    {
        constexpr int num_elements = 10'000'000;
        constexpr int num_iterations = 20;

        sfl::benchmark::table table;

        table.set_title("emplace @ begin() (", num_elements," integers)");

        table.set_header("Container", "Time");

        table.add_row("sfl::segmented_devector<int, 1024>", test_emplace_at_begin<sfl::segmented_devector<int, 1024>>(num_elements, num_iterations));
        table.add_row("sfl::segmented_devector<int, 32768>", test_emplace_at_begin<sfl::segmented_devector<int, 32768>>(num_elements, num_iterations));
        table.add_row("std::deque<int>", test_emplace_at_begin<std::deque<int>>(num_elements, num_iterations));
        table.add_row("boost::container::deque<int>", test_emplace_at_begin<boost::container::deque<int>>(num_elements, num_iterations));

        std::cout << table << std::endl;
    }

    {
        constexpr int num_elements = 10'000'000;
        constexpr int num_iterations = 20;

        sfl::benchmark::table table;

        table.set_title("emplace @ end() (", num_elements," integers)");

        table.set_header("Container", "Time");

        table.add_row("sfl::segmented_devector<int, 1024>", test_emplace_at_end<sfl::segmented_devector<int, 1024>>(num_elements, num_iterations));
        table.add_row("sfl::segmented_devector<int, 32768>", test_emplace_at_end<sfl::segmented_devector<int, 32768>>(num_elements, num_iterations));
        table.add_row("std::deque<int>", test_emplace_at_end<std::deque<int>>(num_elements, num_iterations));
        table.add_row("boost::container::deque<int>", test_emplace_at_end<boost::container::deque<int>>(num_elements, num_iterations));

        std::cout << table << std::endl;
    }

    {
        constexpr int num_elements = 100'000;
        constexpr int num_iterations = 20;

        sfl::benchmark::table table;

        table.set_title("emplace @ random position() (", num_elements," integers)");

        table.set_header("Container", "Time");

        table.add_row("sfl::segmented_devector<int, 1024>", test_emplace_at_random<sfl::segmented_devector<int, 1024>>(num_elements, num_iterations));
        table.add_row("sfl::segmented_devector<int, 32768>", test_emplace_at_random<sfl::segmented_devector<int, 32768>>(num_elements, num_iterations));
        table.add_row("std::deque<int>", test_emplace_at_random<std::deque<int>>(num_elements, num_iterations));
        table.add_row("boost::container::deque<int>", test_emplace_at_random<boost::container::deque<int>>(num_elements, num_iterations));

        std::cout << table << std::endl;
    }

    {
        constexpr int num_elements = 1'000'000;
        constexpr int num_iterations = 20;

        sfl::benchmark::table table;

        table.set_title("erase @ random position (", num_elements," integers)");

        table.set_header("Container", "Time");

        table.add_row("sfl::segmented_devector<int, 1024>", test_erase_at_random<sfl::segmented_devector<int, 1024>>(num_elements, num_iterations));
        table.add_row("sfl::segmented_devector<int, 32768>", test_erase_at_random<sfl::segmented_devector<int, 32768>>(num_elements, num_iterations));
        table.add_row("std::deque<int>", test_erase_at_random<std::deque<int>>(num_elements, num_iterations));
        table.add_row("boost::container::deque<int>", test_erase_at_random<boost::container::deque<int>>(num_elements, num_iterations));

        std::cout << table << std::endl;
    }

    {
        constexpr int num_elements = 1'000'000;
        constexpr int num_iterations = 20;

        sfl::benchmark::table table;

        table.set_title("Iterate all (", num_elements," integers)");

        table.set_header("Container", "Time");

        table.add_row("sfl::segmented_devector<int, 1024>", test_iterate_all<sfl::segmented_devector<int, 1024>>(num_elements, num_iterations));
        table.add_row("sfl::segmented_devector<int, 32768>", test_iterate_all<sfl::segmented_devector<int, 32768>>(num_elements, num_iterations));
        table.add_row("std::deque<int>", test_iterate_all<std::deque<int>>(num_elements, num_iterations));
        table.add_row("boost::container::deque<int>", test_iterate_all<boost::container::deque<int>>(num_elements, num_iterations));

        std::cout << table << std::endl;
    }

    {
        constexpr int num_elements = 1'000'000;
        constexpr int num_iterations = 20;

        sfl::benchmark::table table;

        table.set_title("Random access (", num_elements," integers)");

        table.set_header("Container", "Time");

        table.add_row("sfl::segmented_devector<int, 1024>", test_random_access<sfl::segmented_devector<int, 1024>>(num_elements, num_iterations));
        table.add_row("sfl::segmented_devector<int, 32768>", test_random_access<sfl::segmented_devector<int, 32768>>(num_elements, num_iterations));
        table.add_row("std::deque<int>", test_random_access<std::deque<int>>(num_elements, num_iterations));
        table.add_row("boost::container::deque<int>", test_random_access<boost::container::deque<int>>(num_elements, num_iterations));

        std::cout << table << std::endl;
    }
}
