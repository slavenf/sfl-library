#include "table.hpp"

#include <sfl/small_unordered_linear_map.hpp>
#include <sfl/small_unordered_map.hpp>
#include <sfl/unordered_map.hpp>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random> // mt19937, random_device
#include <unordered_map>
#include <vector>

template <typename Map>
std::chrono::duration<double, std::milli> test_random_insert(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Map map;

        const auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < num_elements; ++i)
        {
            std::uint64_t key = gen();
            map[key] = i;
            sum += key;
        }

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += map.size();
    }

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Map>
std::chrono::duration<double, std::milli> test_random_lookup(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    std::vector<std::uint64_t> data(2 * num_elements);

    std::generate(data.begin(), data.end(), gen);

    Map map;

    for (int i = 0; i < num_elements; ++i)
    {
        map[data[i]] = i;
    }

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        std::shuffle(data.begin(), data.end(), gen);

        const auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < int(data.size()); ++i)
        {
            auto it = map.find(data[i]);

            if (it != map.end())
            {
                sum += it->second;
                it->second = gen();
            }
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
    using sfl_small_unordered_map = sfl::small_unordered_map<std::uint64_t, std::uint64_t, 128>;
    using sfl_small_unordered_linear_map = sfl::small_unordered_linear_map<std::uint64_t, std::uint64_t, 128>;
    using sfl_unordered_map = sfl::unordered_map<std::uint64_t, std::uint64_t>;
    using std_unordered_map = std::unordered_map<std::uint64_t, std::uint64_t>;

    for (const int num_elements : {2, 4, 8, 16, 32, 64, 128})
    {
        constexpr int num_iterations = 100'000;

        sfl::benchmark::table table;

        table.set_title("Random insert ", num_elements," integers");

        table.set_header("Container", "Time");

        table.add_row("sfl::small_unordered_map", test_random_insert<sfl_small_unordered_map>(num_elements, num_iterations));
        table.add_row("sfl::small_unordered_linear_map", test_random_insert<sfl_small_unordered_linear_map>(num_elements, num_iterations));
        table.add_row("sfl::unordered_map", test_random_insert<sfl_unordered_map>(num_elements, num_iterations));
        table.add_row("std::unordered_map", test_random_insert<std_unordered_map>(num_elements, num_iterations));

        std::cout << table << std::endl;
    }

    for (const int num_elements : {2, 4, 8, 16, 32, 64, 128})
    {
        constexpr int num_iterations = 100'000;

        sfl::benchmark::table table;

        table.set_title("Random lookup ", num_elements," integers");

        table.set_header("Container", "Time");

        table.add_row("sfl::small_unordered_map", test_random_lookup<sfl_small_unordered_map>(num_elements, num_iterations));
        table.add_row("sfl::small_unordered_linear_map", test_random_lookup<sfl_small_unordered_linear_map>(num_elements, num_iterations));
        table.add_row("sfl::unordered_map", test_random_lookup<sfl_unordered_map>(num_elements, num_iterations));
        table.add_row("std::unordered_map", test_random_lookup<std_unordered_map>(num_elements, num_iterations));

        std::cout << table << std::endl;
    }
}
