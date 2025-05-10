#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include <sfl/unordered_map.hpp>

#include <boost/unordered_map.hpp>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <unordered_map>
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
std::chrono::duration<double, std::milli> test_random_insert_2(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    ankerl::nanobench::Rng rng;

    std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Map map(num_elements);

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

template <typename Map>
std::chrono::duration<double, std::milli> test_random_erase(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    std::vector<std::uint64_t> data(2 * num_elements);

    std::generate(data.begin(), data.end(), gen);

    std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Map map;

        std::shuffle(data.begin(), data.end(), gen);

        for (int i = 0; i < num_elements; ++i)
        {
            map[data[i]] = i;
        }

        std::shuffle(data.begin(), data.end(), gen);

        const auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < int(data.size()); ++i)
        {
            sum += map.erase(data[i]);
        }

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);
    }

    ankerl::nanobench::doNotOptimizeAway(sum);

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Map>
std::chrono::duration<double, std::milli> test_copy_constructor(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    ankerl::nanobench::Rng rng;

    Map map1;

    std::uint64_t some_key = 0;

    for (int i = 0; i < num_elements; ++i)
    {
        std::uint64_t key = rng();

        if (i == num_elements / 2)
        {
            some_key = key;
        }

        map1[key] = i;
    }

    std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        const auto start = std::chrono::steady_clock::now();

        Map map2(map1);

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += map2.size() + map2[some_key];
        map1[some_key] = rng();
    }

    ankerl::nanobench::doNotOptimizeAway(sum);

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Map>
std::chrono::duration<double, std::milli> test_copy_assignment(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    ankerl::nanobench::Rng rng;

    Map map1;

    std::uint64_t some_key = 0;

    for (int i = 0; i < num_elements; ++i)
    {
        std::uint64_t key = rng();

        if (i == num_elements / 2)
        {
            some_key = key;
        }

        map1[key] = i;
    }

    std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Map map2;

        const auto start = std::chrono::steady_clock::now();

        map2 = map1;

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += map2.size() + map2[some_key];
        map1[some_key] = rng();
    }

    ankerl::nanobench::doNotOptimizeAway(sum);

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

int main()
{
    using sfl_map   = sfl::unordered_map<std::uint64_t, std::uint64_t>;
    using std_map   = std::unordered_map<std::uint64_t, std::uint64_t>;
    using boost_map = boost::unordered_map<std::uint64_t, std::uint64_t>;

    std::cout << std::fixed;

    ///////////////////////////////////////////////////////////////////////////

    std::cout << "random insert 1k integers (default bucket count):" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_insert<sfl_map>  (1'000, 1'000) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_insert<std_map>  (1'000, 1'000) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_insert<boost_map>(1'000, 1'000) << std::endl;
    std::cout << std::endl;

    std::cout << "random insert 100k integers (default bucket count):" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_insert<sfl_map>  (100'000, 100) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_insert<std_map>  (100'000, 100) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_insert<boost_map>(100'000, 100) << std::endl;
    std::cout << std::endl;

    std::cout << "random insert 10M integers (default bucket count):" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_insert<sfl_map>  (10'000'000, 10) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_insert<std_map>  (10'000'000, 10) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_insert<boost_map>(10'000'000, 10) << std::endl;
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////

    std::cout << "random insert 1k integers (specified bucket count):" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_insert_2<sfl_map>  (1'000, 1'000) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_insert_2<std_map>  (1'000, 1'000) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_insert_2<boost_map>(1'000, 1'000) << std::endl;
    std::cout << std::endl;

    std::cout << "random insert 100k integers (specified bucket count):" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_insert_2<sfl_map>  (100'000, 100) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_insert_2<std_map>  (100'000, 100) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_insert_2<boost_map>(100'000, 100) << std::endl;
    std::cout << std::endl;

    std::cout << "random insert 10M integers (specified bucket count):" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_insert_2<sfl_map>  (10'000'000, 10) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_insert_2<std_map>  (10'000'000, 10) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_insert_2<boost_map>(10'000'000, 10) << std::endl;
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////

    std::cout << "random lookup 1k integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_lookup<sfl_map>  (1'000, 1'000) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_lookup<std_map>  (1'000, 1'000) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_lookup<boost_map>(1'000, 1'000) << std::endl;
    std::cout << std::endl;

    std::cout << "random lookup 100k integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_lookup<sfl_map>  (100'000, 100) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_lookup<std_map>  (100'000, 100) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_lookup<boost_map>(100'000, 100) << std::endl;
    std::cout << std::endl;

    std::cout << "random lookup 10M integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_lookup<sfl_map>  (10'000'000, 10) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_lookup<std_map>  (10'000'000, 10) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_lookup<boost_map>(10'000'000, 10) << std::endl;
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////

    std::cout << "random erase 1k integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_erase<sfl_map>  (1'000, 1'000) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_erase<std_map>  (1'000, 1'000) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_erase<boost_map>(1'000, 1'000) << std::endl;
    std::cout << std::endl;

    std::cout << "random erase 100k integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_erase<sfl_map>  (100'000, 100) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_erase<std_map>  (100'000, 100) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_erase<boost_map>(100'000, 100) << std::endl;
    std::cout << std::endl;

    std::cout << "random erase 10M integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_random_erase<sfl_map>  (10'000'000, 10) << std::endl;
    std::cout << " - std::unordered_map:   " << test_random_erase<std_map>  (10'000'000, 10) << std::endl;
    std::cout << " - boost::unordered_map: " << test_random_erase<boost_map>(10'000'000, 10) << std::endl;
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////

    std::cout << "copy constructor 1k integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_copy_constructor<sfl_map>  (1'000, 1'000) << std::endl;
    std::cout << " - std::unordered_map:   " << test_copy_constructor<std_map>  (1'000, 1'000) << std::endl;
    std::cout << " - boost::unordered_map: " << test_copy_constructor<boost_map>(1'000, 1'000) << std::endl;
    std::cout << std::endl;

    std::cout << "copy constructor 100k integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_copy_constructor<sfl_map>  (100'000, 100) << std::endl;
    std::cout << " - std::unordered_map:   " << test_copy_constructor<std_map>  (100'000, 100) << std::endl;
    std::cout << " - boost::unordered_map: " << test_copy_constructor<boost_map>(100'000, 100) << std::endl;
    std::cout << std::endl;

    std::cout << "copy constructor 10M integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_copy_constructor<sfl_map>  (10'000'000, 10) << std::endl;
    std::cout << " - std::unordered_map:   " << test_copy_constructor<std_map>  (10'000'000, 10) << std::endl;
    std::cout << " - boost::unordered_map: " << test_copy_constructor<boost_map>(10'000'000, 10) << std::endl;
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////

    std::cout << "copy assignment 1k integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_copy_assignment<sfl_map>  (1'000, 1'000) << std::endl;
    std::cout << " - std::unordered_map:   " << test_copy_assignment<std_map>  (1'000, 1'000) << std::endl;
    std::cout << " - boost::unordered_map: " << test_copy_assignment<boost_map>(1'000, 1'000) << std::endl;
    std::cout << std::endl;

    std::cout << "copy assignment 100k integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_copy_assignment<sfl_map>  (100'000, 100) << std::endl;
    std::cout << " - std::unordered_map:   " << test_copy_assignment<std_map>  (100'000, 100) << std::endl;
    std::cout << " - boost::unordered_map: " << test_copy_assignment<boost_map>(100'000, 100) << std::endl;
    std::cout << std::endl;

    std::cout << "copy assignment 10M integers:" << std::endl;
    std::cout << " - sfl::unordered_map:   " << test_copy_assignment<sfl_map>  (10'000'000, 10) << std::endl;
    std::cout << " - std::unordered_map:   " << test_copy_assignment<std_map>  (10'000'000, 10) << std::endl;
    std::cout << " - boost::unordered_map: " << test_copy_assignment<boost_map>(10'000'000, 10) << std::endl;
    std::cout << std::endl;
}
