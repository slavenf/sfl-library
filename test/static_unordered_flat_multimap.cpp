//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include static_unordered_flat_multimap.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG // This is very important. Must be in the first line.

#define SFL_TEST_STATIC_UNORDERED_FLAT_MULTIMAP
#include "sfl/static_unordered_flat_multimap.hpp"

#include "check.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xobj.hpp"

#include <vector>

void test_static_unordered_flat_multimap()
{
    using sfl::test::xint;
    using sfl::test::xobj;

    PRINT("Test PRIVATE member function emplace_back(Args&&...)");
    {
        sfl::static_unordered_flat_multimap<xint, xint, 5, std::equal_to<xint>> map;

        {
            CHECK(map.empty() == true);
            CHECK(map.full() == false);
            CHECK(map.size() == 0);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 5);
        }

        {
            PRINT(">");
            const auto res = map.emplace_back(10, 1);
            PRINT("<");

            CHECK(res == map.nth(0));
            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 1);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 4);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        }

        {
            PRINT(">");
            const auto res = map.emplace_back(20, 1);
            PRINT("<");

            CHECK(res == map.nth(1));
            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 2);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        }

        {
            PRINT(">");
            const auto res = map.emplace_back(30, 1);
            PRINT("<");

            CHECK(res == map.nth(2));
            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 3);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 2);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
        }

        {
            PRINT(">");
            const auto res = map.emplace_back(40, 1);
            PRINT("<");

            CHECK(res == map.nth(3));
            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 4);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
        }

        {
            PRINT(">");
            const auto res = map.emplace_back(50, 1);
            PRINT("<");

            CHECK(res == map.nth(4));
            CHECK(map.empty() == false);
            CHECK(map.full() == true);
            CHECK(map.size() == 5);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 0);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test begin, end, cbegin, cend, nth, index_of");
    {
        sfl::static_unordered_flat_multimap<xint, xint, 100, std::equal_to<xint>> map;

        map.emplace_back(20, 1);
        map.emplace_back(40, 1);
        map.emplace_back(60, 1);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 20); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 40); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 60); CHECK(map.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////

        auto it = map.begin();
        CHECK(it->first == 20); CHECK(it->second == 1); ++it;
        CHECK(it->first == 40); CHECK(it->second == 1); ++it;
        CHECK(it->first == 60); CHECK(it->second == 1); ++it;
        CHECK(it == map.end());

        ///////////////////////////////////////////////////////////////////////

        auto cit = map.cbegin();
        CHECK(cit->first == 20); CHECK(cit->second == 1); ++cit;
        CHECK(cit->first == 40); CHECK(cit->second == 1); ++cit;
        CHECK(cit->first == 60); CHECK(cit->second == 1); ++cit;
        CHECK(cit == map.cend());

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.nth(0)->first == 20); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 40); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 60); CHECK(map.nth(2)->second == 1);
        CHECK(map.nth(3) == map.end());

        ///////////////////////////////////////////////////////////////////////

        CHECK(std::next(map.begin(), 0) == map.nth(0));
        CHECK(std::next(map.begin(), 1) == map.nth(1));
        CHECK(std::next(map.begin(), 2) == map.nth(2));
        CHECK(std::next(map.begin(), 3) == map.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(std::next(map.cbegin(), 0) == map.nth(0));
        CHECK(std::next(map.cbegin(), 1) == map.nth(1));
        CHECK(std::next(map.cbegin(), 2) == map.nth(2));
        CHECK(std::next(map.cbegin(), 3) == map.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.nth(0) < map.nth(1));
        CHECK(map.nth(0) < map.nth(2));
        CHECK(map.nth(0) < map.nth(3));

        CHECK(map.nth(1) < map.nth(2));
        CHECK(map.nth(1) < map.nth(3));

        CHECK(map.nth(2) < map.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(map.index_of(map.nth(0)) == 0);
        CHECK(map.index_of(map.nth(1)) == 1);
        CHECK(map.index_of(map.nth(2)) == 2);
        CHECK(map.index_of(map.nth(3)) == 3);
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test key_eq()");
    {
        {
            sfl::static_unordered_flat_multimap<xint, xint, 100, std::equal_to<xint>> map;

            auto key_eq = map.key_eq();

            CHECK(key_eq(10, 10) == true);
            CHECK(key_eq(10, 20) == false);
            CHECK(key_eq(20, 10) == false);
            CHECK(key_eq(20, 20) == true);
        }

        {
            sfl::static_unordered_flat_multimap<xobj, xint, 100, xobj::equal> map;

            auto key_eq = map.key_eq();

            CHECK(key_eq(xobj(10), 10) == true);
            CHECK(key_eq(xobj(10), 20) == false);
            CHECK(key_eq(xobj(20), 10) == false);
            CHECK(key_eq(xobj(20), 20) == true);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test value_eq()");
    {
        {
            sfl::static_unordered_flat_multimap<xint, xint, 100, std::equal_to<xint>> map;

            auto value_eq = map.value_eq();

            CHECK(value_eq({10, 1}, {10, 2}) == true);
            CHECK(value_eq({10, 1}, {20, 2}) == false);
            CHECK(value_eq({20, 1}, {10, 2}) == false);
            CHECK(value_eq({20, 1}, {20, 2}) == true);
        }

        {
            sfl::static_unordered_flat_multimap<xobj, xint, 100, xobj::equal> map;

            auto value_eq = map.value_eq();

            CHECK(value_eq({xobj(10), 1}, {xobj(10), 2}) == true);
            CHECK(value_eq({xobj(10), 1}, {xobj(20), 2}) == false);
            CHECK(value_eq({xobj(20), 1}, {xobj(10), 2}) == false);
            CHECK(value_eq({xobj(20), 1}, {xobj(20), 2}) == true);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test find, count, contains");
    {
        // xint, xint
        {
            sfl::static_unordered_flat_multimap<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace_back(20, 1);
            map.emplace_back(40, 1);
            map.emplace_back(60, 1);

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 20); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 40); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 60); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.find(10) == map.end());
            CHECK(map.find(20) == map.nth(0));
            CHECK(map.find(30) == map.end());
            CHECK(map.find(40) == map.nth(1));
            CHECK(map.find(50) == map.end());
            CHECK(map.find(60) == map.nth(2));
            CHECK(map.find(70) == map.end());

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.count(10) == 0);
            CHECK(map.count(20) == 1);
            CHECK(map.count(30) == 0);
            CHECK(map.count(40) == 1);
            CHECK(map.count(50) == 0);
            CHECK(map.count(60) == 1);
            CHECK(map.count(70) == 0);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.contains(10) == false);
            CHECK(map.contains(20) == true);
            CHECK(map.contains(30) == false);
            CHECK(map.contains(40) == true);
            CHECK(map.contains(50) == false);
            CHECK(map.contains(60) == true);
            CHECK(map.contains(70) == false);
        }

        // xobj, xint
        {
            sfl::static_unordered_flat_multimap<xobj, xint, 100, xobj::equal> map;

            map.emplace_back(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
            map.emplace_back(std::piecewise_construct, std::forward_as_tuple(40), std::forward_as_tuple(1));
            map.emplace_back(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(1));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first.value() == 20); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first.value() == 40); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first.value() == 60); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.find(10) == map.end());
            CHECK(map.find(20) == map.nth(0));
            CHECK(map.find(30) == map.end());
            CHECK(map.find(40) == map.nth(1));
            CHECK(map.find(50) == map.end());
            CHECK(map.find(60) == map.nth(2));
            CHECK(map.find(70) == map.end());

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.count(10) == 0);
            CHECK(map.count(20) == 1);
            CHECK(map.count(30) == 0);
            CHECK(map.count(40) == 1);
            CHECK(map.count(50) == 0);
            CHECK(map.count(60) == 1);
            CHECK(map.count(70) == 0);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.contains(10) == false);
            CHECK(map.contains(20) == true);
            CHECK(map.contains(30) == false);
            CHECK(map.contains(40) == true);
            CHECK(map.contains(50) == false);
            CHECK(map.contains(60) == true);
            CHECK(map.contains(70) == false);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test clear()");
    {
        sfl::static_unordered_flat_multimap<xint, xint, 100, std::equal_to<xint>> map;

        CHECK(map.size() == 0);

        map.emplace_back(10, 1);
        map.emplace_back(20, 1);
        map.emplace_back(30, 1);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

        map.clear();

        CHECK(map.size() == 0);

        map.emplace_back(40, 2);
        map.emplace_back(50, 2);
        map.emplace_back(60, 2);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 40); CHECK(map.nth(0)->second == 2);
        CHECK(map.nth(1)->first == 50); CHECK(map.nth(1)->second == 2);
        CHECK(map.nth(2)->first == 60); CHECK(map.nth(2)->second == 2);

        map.clear();

        CHECK(map.size() == 0);
    }
}

int main()
{
    test_static_unordered_flat_multimap();
}
