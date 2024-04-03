//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include static_flat_map.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG // This is very important. Must be in the first line.

#define SFL_TEST_STATIC_FLAT_MAP
#include "sfl/static_flat_map.hpp"

#include "check.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xobj.hpp"

#include <vector>

void test_static_flat_map()
{
    using sfl::test::xint;
    using sfl::test::xobj;

    PRINT("Test PRIVATE member function insert_exactly_at(const_iterator, Args&&...)");
    {
        // Insert at the end
        {
            sfl::static_flat_map<xint, xint, 5, std::less<xint>> map;

            {
                CHECK(map.empty() == true);
                CHECK(map.full() == false);
                CHECK(map.size() == 0);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 5);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.end(), 10, 1);
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
                const auto res = map.insert_exactly_at(map.end(), 20, 1);
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
                const auto res = map.insert_exactly_at(map.end(), 30, 1);
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
                const auto res = map.insert_exactly_at(map.end(), 40, 1);
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
                const auto res = map.insert_exactly_at(map.end(), 50, 1);
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

        // Insert at the begin
        {
            sfl::static_flat_map<xint, xint, 5, std::less<xint>> map;

            {
                CHECK(map.empty() == true);
                CHECK(map.full() == false);
                CHECK(map.size() == 0);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 5);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.begin(), 50, 1);
                PRINT("<");

                CHECK(res == map.nth(0));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 1);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 4);
                CHECK(map.nth(0)->first == 50); CHECK(map.nth(0)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.begin(), 40, 1);
                PRINT("<");

                CHECK(res == map.nth(0));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 2);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 3);
                CHECK(map.nth(0)->first == 40); CHECK(map.nth(0)->second == 1);
                CHECK(map.nth(1)->first == 50); CHECK(map.nth(1)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.begin(), 30, 1);
                PRINT("<");

                CHECK(res == map.nth(0));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 3);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 2);
                CHECK(map.nth(0)->first == 30); CHECK(map.nth(0)->second == 1);
                CHECK(map.nth(1)->first == 40); CHECK(map.nth(1)->second == 1);
                CHECK(map.nth(2)->first == 50); CHECK(map.nth(2)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.begin(), 20, 1);
                PRINT("<");

                CHECK(res == map.nth(0));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 4);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 1);
                CHECK(map.nth(0)->first == 20); CHECK(map.nth(0)->second == 1);
                CHECK(map.nth(1)->first == 30); CHECK(map.nth(1)->second == 1);
                CHECK(map.nth(2)->first == 40); CHECK(map.nth(2)->second == 1);
                CHECK(map.nth(3)->first == 50); CHECK(map.nth(3)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.begin(), 10, 1);
                PRINT("<");

                CHECK(res == map.nth(0));
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

        {
            sfl::static_flat_map<xint, xint, 5, std::less<xint>> map;

            map.insert_exactly_at(map.end(), 10, 1);
            map.insert_exactly_at(map.end(), 20, 1);
            map.insert_exactly_at(map.end(), 30, 1);
            map.insert_exactly_at(map.end(), 40, 1);

            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 4);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            const auto res = map.insert_exactly_at(map.nth(0), 5, 1);

            CHECK(res == map.nth(0));
            CHECK(map.empty() == false);
            CHECK(map.full() == true);
            CHECK(map.size() == 5);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 0);
            CHECK(map.nth(0)->first ==  5); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 10); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 20); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 30); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 40); CHECK(map.nth(4)->second == 1);
        }

        {
            sfl::static_flat_map<xint, xint, 5, std::less<xint>> map;

            map.insert_exactly_at(map.end(), 10, 1);
            map.insert_exactly_at(map.end(), 20, 1);
            map.insert_exactly_at(map.end(), 30, 1);
            map.insert_exactly_at(map.end(), 40, 1);

            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 4);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            const auto res = map.insert_exactly_at(map.nth(1), 15, 1);

            CHECK(res == map.nth(1));
            CHECK(map.empty() == false);
            CHECK(map.full() == true);
            CHECK(map.size() == 5);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 0);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 15); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 20); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 30); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 40); CHECK(map.nth(4)->second == 1);
        }

        {
            sfl::static_flat_map<xint, xint, 5, std::less<xint>> map;

            map.insert_exactly_at(map.end(), 10, 1);
            map.insert_exactly_at(map.end(), 20, 1);
            map.insert_exactly_at(map.end(), 30, 1);
            map.insert_exactly_at(map.end(), 40, 1);

            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 4);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            const auto res = map.insert_exactly_at(map.nth(2), 25, 1);

            CHECK(res == map.nth(2));
            CHECK(map.empty() == false);
            CHECK(map.full() == true);
            CHECK(map.size() == 5);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 0);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 25); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 30); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 40); CHECK(map.nth(4)->second == 1);
        }

        {
            sfl::static_flat_map<xint, xint, 5, std::less<xint>> map;

            map.insert_exactly_at(map.end(), 10, 1);
            map.insert_exactly_at(map.end(), 20, 1);
            map.insert_exactly_at(map.end(), 30, 1);
            map.insert_exactly_at(map.end(), 40, 1);

            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 4);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            const auto res = map.insert_exactly_at(map.nth(3), 35, 1);

            CHECK(res == map.nth(3));
            CHECK(map.empty() == false);
            CHECK(map.full() == true);
            CHECK(map.size() == 5);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 0);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 35); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 40); CHECK(map.nth(4)->second == 1);
        }

        {
            sfl::static_flat_map<xint, xint, 5, std::less<xint>> map;

            map.insert_exactly_at(map.end(), 10, 1);
            map.insert_exactly_at(map.end(), 20, 1);
            map.insert_exactly_at(map.end(), 30, 1);
            map.insert_exactly_at(map.end(), 40, 1);

            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 4);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            const auto res = map.insert_exactly_at(map.nth(4), 45, 1);

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
            CHECK(map.nth(4)->first == 45); CHECK(map.nth(4)->second == 1);
        }
    }

    PRINT("Test PRIVATE member function is_insert_hint_good(const_iterator, const Value&)");
    {
        sfl::static_flat_map<xint, xint, 100, std::less<xint>> map;

        using value_type = std::pair<xint, xint>;

        ///////////////////////////////////////////////////////////////////////////

        map.insert_exactly_at(map.end(), value_type(20, 1));
        map.insert_exactly_at(map.end(), value_type(40, 1));
        map.insert_exactly_at(map.end(), value_type(60, 1));

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 20); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 40); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 60); CHECK(map.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////////

        CHECK(map.is_insert_hint_good(map.nth(0), value_type(20, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(1), value_type(20, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(2), value_type(20, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(3), value_type(20, 1)) == false);

        CHECK(map.is_insert_hint_good(map.nth(0), value_type(40, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(1), value_type(40, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(2), value_type(40, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(3), value_type(40, 1)) == false);

        CHECK(map.is_insert_hint_good(map.nth(0), value_type(60, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(1), value_type(60, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(2), value_type(60, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(3), value_type(60, 1)) == false);

        ///////////////////////////////////////////////////////////////////////////

        CHECK(map.is_insert_hint_good(map.nth(0), value_type(10, 1)) == true);
        CHECK(map.is_insert_hint_good(map.nth(1), value_type(10, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(2), value_type(10, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(3), value_type(10, 1)) == false);

        CHECK(map.is_insert_hint_good(map.nth(0), value_type(30, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(1), value_type(30, 1)) == true);
        CHECK(map.is_insert_hint_good(map.nth(2), value_type(30, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(3), value_type(30, 1)) == false);

        CHECK(map.is_insert_hint_good(map.nth(0), value_type(50, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(1), value_type(50, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(2), value_type(50, 1)) == true);
        CHECK(map.is_insert_hint_good(map.nth(3), value_type(50, 1)) == false);

        CHECK(map.is_insert_hint_good(map.nth(0), value_type(70, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(1), value_type(70, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(2), value_type(70, 1)) == false);
        CHECK(map.is_insert_hint_good(map.nth(3), value_type(70, 1)) == true);
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend, nth, index_of");
    {
        sfl::static_flat_map<xint, xint, 100, std::less<xint>> map;

        map.insert_exactly_at(map.end(), 20, 1);
        map.insert_exactly_at(map.end(), 40, 1);
        map.insert_exactly_at(map.end(), 60, 1);

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

        auto rit = map.rbegin();
        CHECK(rit->first == 60); CHECK(rit->second == 1); ++rit;
        CHECK(rit->first == 40); CHECK(rit->second == 1); ++rit;
        CHECK(rit->first == 20); CHECK(rit->second == 1); ++rit;
        CHECK(rit == map.rend());

        ///////////////////////////////////////////////////////////////////////

        auto crit = map.crbegin();
        CHECK(crit->first == 60); CHECK(crit->second == 1); ++crit;
        CHECK(crit->first == 40); CHECK(crit->second == 1); ++crit;
        CHECK(crit->first == 20); CHECK(crit->second == 1); ++crit;
        CHECK(crit == map.crend());

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

    PRINT("Test key_comp()");
    {
        {
            sfl::static_flat_map<xint, xint, 100, std::less<xint>> map;

            auto key_comp = map.key_comp();

            CHECK(key_comp(10, 10) == false);
            CHECK(key_comp(10, 20) == true);
            CHECK(key_comp(20, 10) == false);
            CHECK(key_comp(20, 20) == false);
        }

        {
            sfl::static_flat_map<xobj, xint, 100, xobj::less> map;

            auto key_comp = map.key_comp();

            CHECK(key_comp(xobj(10), 10) == false);
            CHECK(key_comp(xobj(10), 20) == true);
            CHECK(key_comp(xobj(20), 10) == false);
            CHECK(key_comp(xobj(20), 20) == false);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test value_comp()");
    {
        {
            sfl::static_flat_map<xint, xint, 100, std::less<xint>> map;

            auto value_comp = map.value_comp();

            CHECK(value_comp({10, 1}, {10, 2}) == false);
            CHECK(value_comp({10, 1}, {20, 2}) == true);
            CHECK(value_comp({20, 1}, {10, 2}) == false);
            CHECK(value_comp({20, 1}, {20, 2}) == false);
        }

        {
            sfl::static_flat_map<xobj, xint, 100, xobj::less> map;

            auto value_comp = map.value_comp();

            CHECK(value_comp({xobj(10), 1}, {xobj(10), 2}) == false);
            CHECK(value_comp({xobj(10), 1}, {xobj(20), 2}) == true);
            CHECK(value_comp({xobj(20), 1}, {xobj(10), 2}) == false);
            CHECK(value_comp({xobj(20), 1}, {xobj(20), 2}) == false);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test lower_bound, upper_bound, equal_range, find, count, contains");
    {
        // xint, xint
        {
            sfl::static_flat_map<xint, xint, 100, std::less<xint>> map;

            map.insert_exactly_at(map.end(), 20, 1);
            map.insert_exactly_at(map.end(), 40, 1);
            map.insert_exactly_at(map.end(), 60, 1);

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 20); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 40); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 60); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.lower_bound(10) == map.nth(0));
            CHECK(map.lower_bound(20) == map.nth(0));
            CHECK(map.lower_bound(30) == map.nth(1));
            CHECK(map.lower_bound(40) == map.nth(1));
            CHECK(map.lower_bound(50) == map.nth(2));
            CHECK(map.lower_bound(60) == map.nth(2));
            CHECK(map.lower_bound(70) == map.nth(3));

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.upper_bound(10) == map.nth(0));
            CHECK(map.upper_bound(20) == map.nth(1));
            CHECK(map.upper_bound(30) == map.nth(1));
            CHECK(map.upper_bound(40) == map.nth(2));
            CHECK(map.upper_bound(50) == map.nth(2));
            CHECK(map.upper_bound(60) == map.nth(3));
            CHECK(map.upper_bound(70) == map.nth(3));

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.equal_range(10) == std::make_pair(map.nth(0), map.nth(0)));
            CHECK(map.equal_range(20) == std::make_pair(map.nth(0), map.nth(1)));
            CHECK(map.equal_range(30) == std::make_pair(map.nth(1), map.nth(1)));
            CHECK(map.equal_range(40) == std::make_pair(map.nth(1), map.nth(2)));
            CHECK(map.equal_range(50) == std::make_pair(map.nth(2), map.nth(2)));
            CHECK(map.equal_range(60) == std::make_pair(map.nth(2), map.nth(3)));
            CHECK(map.equal_range(70) == std::make_pair(map.nth(3), map.nth(3)));

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
            sfl::static_flat_map<xobj, xint, 100, xobj::less> map;

            map.insert_exactly_at(map.end(), std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
            map.insert_exactly_at(map.end(), std::piecewise_construct, std::forward_as_tuple(40), std::forward_as_tuple(1));
            map.insert_exactly_at(map.end(), std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(1));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first.value() == 20); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first.value() == 40); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first.value() == 60); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.lower_bound(10) == map.nth(0));
            CHECK(map.lower_bound(20) == map.nth(0));
            CHECK(map.lower_bound(30) == map.nth(1));
            CHECK(map.lower_bound(40) == map.nth(1));
            CHECK(map.lower_bound(50) == map.nth(2));
            CHECK(map.lower_bound(60) == map.nth(2));
            CHECK(map.lower_bound(70) == map.nth(3));

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.upper_bound(10) == map.nth(0));
            CHECK(map.upper_bound(20) == map.nth(1));
            CHECK(map.upper_bound(30) == map.nth(1));
            CHECK(map.upper_bound(40) == map.nth(2));
            CHECK(map.upper_bound(50) == map.nth(2));
            CHECK(map.upper_bound(60) == map.nth(3));
            CHECK(map.upper_bound(70) == map.nth(3));

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.equal_range(10) == std::make_pair(map.nth(0), map.nth(0)));
            CHECK(map.equal_range(20) == std::make_pair(map.nth(0), map.nth(1)));
            CHECK(map.equal_range(30) == std::make_pair(map.nth(1), map.nth(1)));
            CHECK(map.equal_range(40) == std::make_pair(map.nth(1), map.nth(2)));
            CHECK(map.equal_range(50) == std::make_pair(map.nth(2), map.nth(2)));
            CHECK(map.equal_range(60) == std::make_pair(map.nth(2), map.nth(3)));
            CHECK(map.equal_range(70) == std::make_pair(map.nth(3), map.nth(3)));

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
}

int main()
{
    test_static_flat_map();
}
