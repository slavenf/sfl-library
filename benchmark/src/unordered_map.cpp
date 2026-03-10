#include "table.hpp"

#include <boost/unordered_map.hpp>
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
std::chrono::duration<double, std::milli> test_random_insert_2(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Map map(num_elements);

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

template <typename Map>
std::chrono::duration<double, std::milli> test_random_erase(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    std::vector<std::uint64_t> data(2 * num_elements);

    std::generate(data.begin(), data.end(), gen);

    volatile std::uint64_t sum = 0;

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

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Map>
std::chrono::duration<double, std::milli> test_copy_constructor(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    Map map1;

    std::uint64_t some_key = 0;

    for (int i = 0; i < num_elements; ++i)
    {
        std::uint64_t key = gen();

        if (i == num_elements / 2)
        {
            some_key = key;
        }

        map1[key] = i;
    }

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        const auto start = std::chrono::steady_clock::now();

        Map map2(map1);

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += map2.size() + map2[some_key];
        map1[some_key] = gen();
    }

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

template <typename Map>
std::chrono::duration<double, std::milli> test_copy_assignment(const int num_elements, const int num_iterations)
{
    std::vector<std::chrono::duration<double, std::milli>> times;

    std::random_device rd;

    std::mt19937 gen(rd());

    Map map1;

    std::uint64_t some_key = 0;

    for (int i = 0; i < num_elements; ++i)
    {
        std::uint64_t key = gen();

        if (i == num_elements / 2)
        {
            some_key = key;
        }

        map1[key] = i;
    }

    volatile std::uint64_t sum = 0;

    for (int i = 0; i < num_iterations; ++i)
    {
        Map map2;

        const auto start = std::chrono::steady_clock::now();

        map2 = map1;

        const auto end = std::chrono::steady_clock::now();

        times.push_back(end - start);

        sum += map2.size() + map2[some_key];
        map1[some_key] = gen();
    }

    (void)sum;

    std::sort(times.begin(), times.end());

    return times[times.size() / 2];
}

int main()
{
    using sfl_map   = sfl::unordered_map<std::uint64_t, std::uint64_t>;
    using std_map   = std::unordered_map<std::uint64_t, std::uint64_t>;
    using boost_map = boost::unordered_map<std::uint64_t, std::uint64_t>;

    struct arguments
    {
        int num_elements;
        int num_iterations;
    };

    for (const auto& args : {arguments{1000, 1000}, {100'000, 100}, {1'000'000, 10}})
    {
        sfl::benchmark::table table;

        table.set_title("Random insert ", args.num_elements," integers (default bucket count)");

        table.set_header("Container", "Time");

        table.add_row("sfl::unordered_map", test_random_insert<sfl_map>(args.num_elements, args.num_iterations));
        table.add_row("std::unordered_map", test_random_insert<std_map>(args.num_elements, args.num_iterations));
        table.add_row("boost::unordered_map", test_random_insert<boost_map>(args.num_elements, args.num_iterations));

        std::cout << table << std::endl;
    }

    for (const auto& args : {arguments{1000, 1000}, {100'000, 100}, {1'000'000, 10}})
    {
        sfl::benchmark::table table;

        table.set_title("Random insert ", args.num_elements," integers (specified bucket count)");

        table.set_header("Container", "Time");

        table.add_row("sfl::unordered_map", test_random_insert_2<sfl_map>(args.num_elements, args.num_iterations));
        table.add_row("std::unordered_map", test_random_insert_2<std_map>(args.num_elements, args.num_iterations));
        table.add_row("boost::unordered_map", test_random_insert_2<boost_map>(args.num_elements, args.num_iterations));

        std::cout << table << std::endl;
    }

    for (const auto& args : {arguments{1000, 1000}, {100'000, 100}, {1'000'000, 10}})
    {
        sfl::benchmark::table table;

        table.set_title("Random lookup ", args.num_elements," integers");

        table.set_header("Container", "Time");

        table.add_row("sfl::unordered_map", test_random_lookup<sfl_map>(args.num_elements, args.num_iterations));
        table.add_row("std::unordered_map", test_random_lookup<std_map>(args.num_elements, args.num_iterations));
        table.add_row("boost::unordered_map", test_random_lookup<boost_map>(args.num_elements, args.num_iterations));

        std::cout << table << std::endl;
    }

    for (const auto& args : {arguments{1000, 1000}, {100'000, 100}, {1'000'000, 10}})
    {
        sfl::benchmark::table table;

        table.set_title("Random erase ", args.num_elements," integers");

        table.set_header("Container", "Time");

        table.add_row("sfl::unordered_map", test_random_erase<sfl_map>(args.num_elements, args.num_iterations));
        table.add_row("std::unordered_map", test_random_erase<std_map>(args.num_elements, args.num_iterations));
        table.add_row("boost::unordered_map", test_random_erase<boost_map>(args.num_elements, args.num_iterations));

        std::cout << table << std::endl;
    }

    for (const auto& args : {arguments{1000, 1000}, {100'000, 100}, {1'000'000, 10}})
    {
        sfl::benchmark::table table;

        table.set_title("Copy constructor ", args.num_elements," integers");

        table.set_header("Container", "Time");

        table.add_row("sfl::unordered_map", test_copy_constructor<sfl_map>(args.num_elements, args.num_iterations));
        table.add_row("std::unordered_map", test_copy_constructor<std_map>(args.num_elements, args.num_iterations));
        table.add_row("boost::unordered_map", test_copy_constructor<boost_map>(args.num_elements, args.num_iterations));

        std::cout << table << std::endl;
    }

    for (const auto& args : {arguments{1000, 1000}, {100'000, 100}, {1'000'000, 10}})
    {
        sfl::benchmark::table table;

        table.set_title("Copy assignment ", args.num_elements," integers");

        table.set_header("Container", "Time");

        table.add_row("sfl::unordered_map", test_copy_assignment<sfl_map>(args.num_elements, args.num_iterations));
        table.add_row("std::unordered_map", test_copy_assignment<std_map>(args.num_elements, args.num_iterations));
        table.add_row("boost::unordered_map", test_copy_assignment<boost_map>(args.num_elements, args.num_iterations));

        std::cout << table << std::endl;
    }
}
