#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include <sfl/small_unordered_flat_map.hpp>
#include <sfl/small_unordered_map.hpp>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <vector>

template <typename Map>
std::chrono::duration<double, std::milli> test_random_insert(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    ankerl::nanobench::Rng rng;

    std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Map map;

        const auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < num_elements; ++i)
        {
            std::uint64_t key = rng();
            map[key] = i;
            sum += key;
        }

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += map.size();
    }

    ankerl::nanobench::doNotOptimizeAway(sum);

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

    std::uint64_t sum = 0;

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

    ankerl::nanobench::doNotOptimizeAway(sum);

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

int main()
{
    using sfl_small_unordered_map = sfl::small_unordered_map<std::uint64_t, std::uint64_t, 128>;
    using sfl_small_unordered_flat_map = sfl::small_unordered_flat_map<std::uint64_t, std::uint64_t, 128>;
    using std_unordered_map = std::unordered_map<std::uint64_t, std::uint64_t>;

    std::cout << std::fixed;

    for (const int n : {2, 4, 8, 16, 32, 64, 128})
    {
        std::cout << "random insert " << n << " integers:" << std::endl;
        std::cout << " - sfl::small_unordered_map:      " << test_random_insert<sfl_small_unordered_map>(n, 100'000) << std::endl;
        std::cout << " - sfl::small_unordered_flat_map: " << test_random_insert<sfl_small_unordered_flat_map>(n, 100'000) << std::endl;
        std::cout << " - std::unordered_map:            " << test_random_insert<std_unordered_map>(n, 100'000) << std::endl;
        std::cout << std::endl;
    }

    for (const int n : {2, 4, 8, 16, 32, 64, 128})
    {
        std::cout << "random lookup " << n << " integers:" << std::endl;
        std::cout << " - sfl::small_unordered_map:      " << test_random_lookup<sfl_small_unordered_map>(n, 100'000) << std::endl;
        std::cout << " - sfl::small_unordered_flat_map: " << test_random_lookup<sfl_small_unordered_flat_map>(n, 100'000) << std::endl;
        std::cout << " - std::unordered_map:            " << test_random_lookup<std_unordered_map>(n, 100'000) << std::endl;
        std::cout << std::endl;
    }
}
