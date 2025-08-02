#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/static_unordered_flat_map.hpp"

#include "check.hpp"
#include "istream_view.hpp"
#include "nth.hpp"
#include "pair_io.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xobj.hpp"

#include <sstream>
#include <vector>

void test_static_unordered_flat_map()
{
    using sfl::test::xint;
    using sfl::test::xobj;

    PRINT("Test begin, end, cbegin, cend, nth, index_of");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        map.emplace(20, 1);
        map.emplace(40, 1);
        map.emplace(60, 1);

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

    ///////////////////////////////////////////////////////////////////////////

    PRINT("Test static_capacity");
    {
        CHECK((sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>>::static_capacity == 100));
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test key_eq()");
    {
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            auto key_eq = map.key_eq();

            CHECK(key_eq(10, 10) == true);
            CHECK(key_eq(10, 20) == false);
            CHECK(key_eq(20, 10) == false);
            CHECK(key_eq(20, 20) == true);
        }

        {
            sfl::static_unordered_flat_map<xobj, xint, 100, xobj::equal> map;

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
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            auto value_eq = map.value_eq();

            CHECK(value_eq({10, 1}, {10, 2}) == true);
            CHECK(value_eq({10, 1}, {20, 2}) == false);
            CHECK(value_eq({20, 1}, {10, 2}) == false);
            CHECK(value_eq({20, 1}, {20, 2}) == true);
        }

        {
            sfl::static_unordered_flat_map<xobj, xint, 100, xobj::equal> map;

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
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(20, 1);
            map.emplace(40, 1);
            map.emplace(60, 1);

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
            sfl::static_unordered_flat_map<xobj, xint, 100, xobj::equal> map;

            map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
            map.emplace(std::piecewise_construct, std::forward_as_tuple(40), std::forward_as_tuple(1));
            map.emplace(std::piecewise_construct, std::forward_as_tuple(60), std::forward_as_tuple(1));

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
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        CHECK(map.size() == 0);

        map.emplace(10, 1);
        map.emplace(20, 1);
        map.emplace(30, 1);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

        map.clear();

        CHECK(map.size() == 0);

        map.emplace(40, 2);
        map.emplace(50, 2);
        map.emplace(60, 2);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 40); CHECK(map.nth(0)->second == 2);
        CHECK(map.nth(1)->first == 50); CHECK(map.nth(1)->second == 2);
        CHECK(map.nth(2)->first == 60); CHECK(map.nth(2)->second == 2);

        map.clear();

        CHECK(map.size() == 0);
    }

    PRINT("Test emplace(Args&&...)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            CHECK(map.emplace(10, 1) == std::make_pair(map.nth(0), true));
            CHECK(map.emplace(20, 1) == std::make_pair(map.nth(1), true));
            CHECK(map.emplace(30, 1) == std::make_pair(map.nth(2), true));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
        }

        {
            CHECK(map.emplace(10, 2) == std::make_pair(map.nth(0), false));
            CHECK(map.emplace(20, 2) == std::make_pair(map.nth(1), false));
            CHECK(map.emplace(30, 2) == std::make_pair(map.nth(2), false));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
        }
    }

    PRINT("Test emplace_hint(const_iterator, Args&&...)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            CHECK(map.emplace_hint(map.begin(), 10, 1) == map.nth(0));
            CHECK(map.emplace_hint(map.begin(), 20, 1) == map.nth(1));
            CHECK(map.emplace_hint(map.begin(), 30, 1) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
        }

        {
            CHECK(map.emplace_hint(map.begin(), 10, 2) == map.nth(0));
            CHECK(map.emplace_hint(map.begin(), 20, 2) == map.nth(1));
            CHECK(map.emplace_hint(map.begin(), 30, 2) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
        }
    }

    PRINT("Test insert(const value_type&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        using value_type = std::pair<xint, xint>;

        {
            value_type value_10_1(10, 1);
            value_type value_20_1(20, 1);
            value_type value_30_1(30, 1);

            CHECK(map.insert(value_10_1) == std::make_pair(map.nth(0), true));
            CHECK(map.insert(value_20_1) == std::make_pair(map.nth(1), true));
            CHECK(map.insert(value_30_1) == std::make_pair(map.nth(2), true));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_1.first == 10); CHECK(value_10_1.second == 1);
            CHECK(value_20_1.first == 20); CHECK(value_20_1.second == 1);
            CHECK(value_30_1.first == 30); CHECK(value_30_1.second == 1);
        }

        {
            value_type value_10_2(10, 2);
            value_type value_20_2(20, 2);
            value_type value_30_2(30, 2);

            CHECK(map.insert(value_10_2) == std::make_pair(map.nth(0), false));
            CHECK(map.insert(value_20_2) == std::make_pair(map.nth(1), false));
            CHECK(map.insert(value_30_2) == std::make_pair(map.nth(2), false));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_2.first == 10); CHECK(value_10_2.second == 2);
            CHECK(value_20_2.first == 20); CHECK(value_20_2.second == 2);
            CHECK(value_30_2.first == 30); CHECK(value_30_2.second == 2);
        }
    }

    PRINT("Test insert(value_type&&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        using value_type = std::pair<xint, xint>;

        {
            value_type value_10_1(10, 1);
            value_type value_20_1(20, 1);
            value_type value_30_1(30, 1);

            CHECK(map.insert(std::move(value_10_1)) == std::make_pair(map.nth(0), true));
            CHECK(map.insert(std::move(value_20_1)) == std::make_pair(map.nth(1), true));
            CHECK(map.insert(std::move(value_30_1)) == std::make_pair(map.nth(2), true));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_1.first == -10); CHECK(value_10_1.second == -1);
            CHECK(value_20_1.first == -20); CHECK(value_20_1.second == -1);
            CHECK(value_30_1.first == -30); CHECK(value_30_1.second == -1);
        }

        {
            value_type value_10_2(10, 2);
            value_type value_20_2(20, 2);
            value_type value_30_2(30, 2);

            CHECK(map.insert(std::move(value_10_2)) == std::make_pair(map.nth(0), false));
            CHECK(map.insert(std::move(value_20_2)) == std::make_pair(map.nth(1), false));
            CHECK(map.insert(std::move(value_30_2)) == std::make_pair(map.nth(2), false));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_2.first == +10); CHECK(value_10_2.second == +2);
            CHECK(value_20_2.first == +20); CHECK(value_20_2.second == +2);
            CHECK(value_30_2.first == +30); CHECK(value_30_2.second == +2);
        }
    }

    PRINT("Test insert(P&&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        using value_type = std::pair<long, long>;

        {
            value_type value_10_1(10, 1);
            value_type value_20_1(20, 1);
            value_type value_30_1(30, 1);

            CHECK(map.insert(std::move(value_10_1)) == std::make_pair(map.nth(0), true));
            CHECK(map.insert(std::move(value_20_1)) == std::make_pair(map.nth(1), true));
            CHECK(map.insert(std::move(value_30_1)) == std::make_pair(map.nth(2), true));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_1.first == 10); CHECK(value_10_1.second == 1);
            CHECK(value_20_1.first == 20); CHECK(value_20_1.second == 1);
            CHECK(value_30_1.first == 30); CHECK(value_30_1.second == 1);
        }

        {
            value_type value_10_2(10, 2);
            value_type value_20_2(20, 2);
            value_type value_30_2(30, 2);

            CHECK(map.insert(std::move(value_10_2)) == std::make_pair(map.nth(0), false));
            CHECK(map.insert(std::move(value_20_2)) == std::make_pair(map.nth(1), false));
            CHECK(map.insert(std::move(value_30_2)) == std::make_pair(map.nth(2), false));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_2.first == 10); CHECK(value_10_2.second == 2);
            CHECK(value_20_2.first == 20); CHECK(value_20_2.second == 2);
            CHECK(value_30_2.first == 30); CHECK(value_30_2.second == 2);
        }
    }

    PRINT("Test insert(const_iterator, const value_type&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        using value_type = std::pair<xint, xint>;

        {
            value_type value_10_1(10, 1);
            value_type value_20_1(20, 1);
            value_type value_30_1(30, 1);

            CHECK(map.insert(map.begin(), value_10_1) == map.nth(0));
            CHECK(map.insert(map.begin(), value_20_1) == map.nth(1));
            CHECK(map.insert(map.begin(), value_30_1) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_1.first == 10); CHECK(value_10_1.second == 1);
            CHECK(value_20_1.first == 20); CHECK(value_20_1.second == 1);
            CHECK(value_30_1.first == 30); CHECK(value_30_1.second == 1);
        }

        {
            value_type value_10_2(10, 2);
            value_type value_20_2(20, 2);
            value_type value_30_2(30, 2);

            CHECK(map.insert(map.begin(), value_10_2) == map.nth(0));
            CHECK(map.insert(map.begin(), value_20_2) == map.nth(1));
            CHECK(map.insert(map.begin(), value_30_2) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_2.first == 10); CHECK(value_10_2.second == 2);
            CHECK(value_20_2.first == 20); CHECK(value_20_2.second == 2);
            CHECK(value_30_2.first == 30); CHECK(value_30_2.second == 2);
        }
    }

    PRINT("Test insert(const_iterator, value_type&&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        using value_type = std::pair<xint, xint>;

        {
            value_type value_10_1(10, 1);
            value_type value_20_1(20, 1);
            value_type value_30_1(30, 1);

            CHECK(map.insert(map.begin(), std::move(value_10_1)) == map.nth(0));
            CHECK(map.insert(map.begin(), std::move(value_20_1)) == map.nth(1));
            CHECK(map.insert(map.begin(), std::move(value_30_1)) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_1.first == -10); CHECK(value_10_1.second == -1);
            CHECK(value_20_1.first == -20); CHECK(value_20_1.second == -1);
            CHECK(value_30_1.first == -30); CHECK(value_30_1.second == -1);
        }

        {
            value_type value_10_2(10, 2);
            value_type value_20_2(20, 2);
            value_type value_30_2(30, 2);

            CHECK(map.insert(map.begin(), std::move(value_10_2)) == map.nth(0));
            CHECK(map.insert(map.begin(), std::move(value_20_2)) == map.nth(1));
            CHECK(map.insert(map.begin(), std::move(value_30_2)) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_2.first == +10); CHECK(value_10_2.second == +2);
            CHECK(value_20_2.first == +20); CHECK(value_20_2.second == +2);
            CHECK(value_30_2.first == +30); CHECK(value_30_2.second == +2);
        }
    }

    PRINT("Test insert(const_iterator, P&&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        using value_type = std::pair<long, long>;

        {
            value_type value_10_1(10, 1);
            value_type value_20_1(20, 1);
            value_type value_30_1(30, 1);

            CHECK(map.insert(map.begin(), std::move(value_10_1)) == map.nth(0));
            CHECK(map.insert(map.begin(), std::move(value_20_1)) == map.nth(1));
            CHECK(map.insert(map.begin(), std::move(value_30_1)) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_1.first == 10); CHECK(value_10_1.second == 1);
            CHECK(value_20_1.first == 20); CHECK(value_20_1.second == 1);
            CHECK(value_30_1.first == 30); CHECK(value_30_1.second == 1);
        }

        {
            value_type value_10_2(10, 2);
            value_type value_20_2(20, 2);
            value_type value_30_2(30, 2);

            CHECK(map.insert(map.begin(), std::move(value_10_2)) == map.nth(0));
            CHECK(map.insert(map.begin(), std::move(value_20_2)) == map.nth(1));
            CHECK(map.insert(map.begin(), std::move(value_30_2)) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(value_10_2.first == 10); CHECK(value_10_2.second == 2);
            CHECK(value_20_2.first == 20); CHECK(value_20_2.second == 2);
            CHECK(value_30_2.first == 30); CHECK(value_30_2.second == 2);
        }
    }

    PRINT("Test insert(InputIt, InputIt)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            std::vector<std::pair<xint, xint>> data
            (
                {
                    {10, 1},
                    {20, 1},
                    {30, 1}
                }
            );

            map.insert(data.begin(), data.end());

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
        }

        {
            std::vector<std::pair<xint, xint>> data
            (
                {
                    {10, 2},
                    {20, 2},
                    {30, 2}
                }
            );

            map.insert(data.begin(), data.end());

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
        }
    }

    PRINT("Test insert(std::initializer_list)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            std::initializer_list<std::pair<xint, xint>> ilist
            {
                {10, 1},
                {20, 1},
                {30, 1}
            };

            map.insert(ilist);

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
        }

        {
            std::initializer_list<std::pair<xint, xint>> ilist
            {
                {10, 2},
                {20, 2},
                {30, 2}
            };

            map.insert(ilist);

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
        }
    }

    PRINT("Test insert_range(Range&&");
    {
        // Input iterator (exactly)
        {
            std::istringstream iss("10 1 20 1 30 1 20 2 20 3");

            sfl::static_unordered_flat_map<xint, xint, 32, std::equal_to<xint>> map;

            #if SFL_CPP_VERSION >= SFL_CPP_20
            map.insert_range(std::views::istream<std::pair<int, int>>(iss));
            #else
            map.insert_range(sfl::test::istream_view<std::pair<int, int>>(iss));
            #endif

            CHECK(map.size() == 3);
            CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
            CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
            CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
        }

        // Forward iterator
        {
            std::vector<std::pair<xint, xint>> data
            (
                {
                    {10, 1},
                    {20, 1},
                    {30, 1},
                    {20, 2},
                    {20, 3}
                }
            );

            sfl::static_unordered_flat_map<xint, xint, 32, std::equal_to<xint>> map;

            #if SFL_CPP_VERSION >= SFL_CPP_20
            map.insert_range(std::views::all(data));
            #else
            map.insert_range(data);
            #endif

            CHECK(map.size() == 3);
            CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
            CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
            CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
        }
    }

    PRINT("Test insert_or_assign(const Key&, M&&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.insert_or_assign(key_10, 1) == std::make_pair(map.nth(0), true));
            CHECK(map.insert_or_assign(key_20, 1) == std::make_pair(map.nth(1), true));
            CHECK(map.insert_or_assign(key_30, 1) == std::make_pair(map.nth(2), true));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == 10);
            CHECK(key_20 == 20);
            CHECK(key_30 == 30);
        }

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.insert_or_assign(key_10, 2) == std::make_pair(map.nth(0), false));
            CHECK(map.insert_or_assign(key_20, 2) == std::make_pair(map.nth(1), false));
            CHECK(map.insert_or_assign(key_30, 2) == std::make_pair(map.nth(2), false));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 2);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 2);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 2);

            CHECK(key_10 == 10);
            CHECK(key_20 == 20);
            CHECK(key_30 == 30);
        }
    }

    PRINT("Test insert_or_assign(Key&&, M&&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.insert_or_assign(std::move(key_10), 1) == std::make_pair(map.nth(0), true));
            CHECK(map.insert_or_assign(std::move(key_20), 1) == std::make_pair(map.nth(1), true));
            CHECK(map.insert_or_assign(std::move(key_30), 1) == std::make_pair(map.nth(2), true));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == -10);
            CHECK(key_20 == -20);
            CHECK(key_30 == -30);
        }

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.insert_or_assign(std::move(key_10), 2) == std::make_pair(map.nth(0), false));
            CHECK(map.insert_or_assign(std::move(key_20), 2) == std::make_pair(map.nth(1), false));
            CHECK(map.insert_or_assign(std::move(key_30), 2) == std::make_pair(map.nth(2), false));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 2);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 2);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 2);

            CHECK(key_10 == +10);
            CHECK(key_20 == +20);
            CHECK(key_30 == +30);
        }
    }

    PRINT("Test insert_or_assign(K&&, M&&)");
    {
        sfl::static_unordered_flat_map<xobj, xint, 100, xobj::equal> map;

        {
            CHECK(map.insert_or_assign(10, 1) == std::make_pair(map.nth(0), true));
            CHECK(map.insert_or_assign(20, 1) == std::make_pair(map.nth(1), true));
            CHECK(map.insert_or_assign(30, 1) == std::make_pair(map.nth(2), true));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 1);
        }

        {
            CHECK(map.insert_or_assign(10, 2) == std::make_pair(map.nth(0), false));
            CHECK(map.insert_or_assign(20, 2) == std::make_pair(map.nth(1), false));
            CHECK(map.insert_or_assign(30, 2) == std::make_pair(map.nth(2), false));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 2);
            CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 2);
            CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 2);
        }
    }

    PRINT("Test insert_or_assign(const_iterator, const Key&, M&&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.insert_or_assign(map.begin(), key_10, 1) == map.nth(0));
            CHECK(map.insert_or_assign(map.begin(), key_20, 1) == map.nth(1));
            CHECK(map.insert_or_assign(map.begin(), key_30, 1) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == 10);
            CHECK(key_20 == 20);
            CHECK(key_30 == 30);
        }

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.insert_or_assign(map.begin(), key_10, 2) == map.nth(0));
            CHECK(map.insert_or_assign(map.begin(), key_20, 2) == map.nth(1));
            CHECK(map.insert_or_assign(map.begin(), key_30, 2) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 2);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 2);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 2);

            CHECK(key_10 == 10);
            CHECK(key_20 == 20);
            CHECK(key_30 == 30);
        }
    }

    PRINT("Test insert_or_assign(const_iterator, Key&&, M&&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.insert_or_assign(map.begin(), std::move(key_10), 1) == map.nth(0));
            CHECK(map.insert_or_assign(map.begin(), std::move(key_20), 1) == map.nth(1));
            CHECK(map.insert_or_assign(map.begin(), std::move(key_30), 1) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == -10);
            CHECK(key_20 == -20);
            CHECK(key_30 == -30);
        }

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.insert_or_assign(map.begin(), std::move(key_10), 2) == map.nth(0));
            CHECK(map.insert_or_assign(map.begin(), std::move(key_20), 2) == map.nth(1));
            CHECK(map.insert_or_assign(map.begin(), std::move(key_30), 2) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 2);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 2);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 2);

            CHECK(key_10 == +10);
            CHECK(key_20 == +20);
            CHECK(key_30 == +30);
        }
    }

    PRINT("Test insert_or_assign(const_iterator, K&&, M&&)");
    {
        sfl::static_unordered_flat_map<xobj, xint, 100, xobj::equal> map;

        {
            CHECK(map.insert_or_assign(map.begin(), 10, 1) == map.nth(0));
            CHECK(map.insert_or_assign(map.begin(), 20, 1) == map.nth(1));
            CHECK(map.insert_or_assign(map.begin(), 30, 1) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 1);
        }

        {
            CHECK(map.insert_or_assign(map.begin(), 10, 2) == map.nth(0));
            CHECK(map.insert_or_assign(map.begin(), 20, 2) == map.nth(1));
            CHECK(map.insert_or_assign(map.begin(), 30, 2) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 2);
            CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 2);
            CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 2);
        }
    }

    PRINT("Test try_emplace(const Key&, Args&&...)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.try_emplace(key_10, 1) == std::make_pair(map.nth(0), true));
            CHECK(map.try_emplace(key_20, 1) == std::make_pair(map.nth(1), true));
            CHECK(map.try_emplace(key_30, 1) == std::make_pair(map.nth(2), true));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == 10);
            CHECK(key_20 == 20);
            CHECK(key_30 == 30);
        }

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.try_emplace(key_10, 2) == std::make_pair(map.nth(0), false));
            CHECK(map.try_emplace(key_20, 2) == std::make_pair(map.nth(1), false));
            CHECK(map.try_emplace(key_30, 2) == std::make_pair(map.nth(2), false));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == 10);
            CHECK(key_20 == 20);
            CHECK(key_30 == 30);
        }
    }

    PRINT("Test try_emplace(Key&&, Args&&...)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.try_emplace(std::move(key_10), 1) == std::make_pair(map.nth(0), true));
            CHECK(map.try_emplace(std::move(key_20), 1) == std::make_pair(map.nth(1), true));
            CHECK(map.try_emplace(std::move(key_30), 1) == std::make_pair(map.nth(2), true));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == -10);
            CHECK(key_20 == -20);
            CHECK(key_30 == -30);
        }

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.try_emplace(std::move(key_10), 2) == std::make_pair(map.nth(0), false));
            CHECK(map.try_emplace(std::move(key_20), 2) == std::make_pair(map.nth(1), false));
            CHECK(map.try_emplace(std::move(key_30), 2) == std::make_pair(map.nth(2), false));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == +10);
            CHECK(key_20 == +20);
            CHECK(key_30 == +30);
        }
    }

    PRINT("Test try_emplace(K&&, Args&&...)");
    {
        sfl::static_unordered_flat_map<xobj, xint, 100, xobj::equal> map;

        {
            CHECK(map.try_emplace(10, 1) == std::make_pair(map.nth(0), true));
            CHECK(map.try_emplace(20, 1) == std::make_pair(map.nth(1), true));
            CHECK(map.try_emplace(30, 1) == std::make_pair(map.nth(2), true));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 1);
        }

        {
            CHECK(map.try_emplace(10, 2) == std::make_pair(map.nth(0), false));
            CHECK(map.try_emplace(20, 2) == std::make_pair(map.nth(1), false));
            CHECK(map.try_emplace(30, 2) == std::make_pair(map.nth(2), false));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 1);
        }
    }

    PRINT("Test try_emplace(const_iterator, const Key&, Args&&...)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.try_emplace(map.begin(), key_10, 1) == map.nth(0));
            CHECK(map.try_emplace(map.begin(), key_20, 1) == map.nth(1));
            CHECK(map.try_emplace(map.begin(), key_30, 1) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == 10);
            CHECK(key_20 == 20);
            CHECK(key_30 == 30);
        }

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.try_emplace(map.begin(), key_10, 2) == map.nth(0));
            CHECK(map.try_emplace(map.begin(), key_20, 2) == map.nth(1));
            CHECK(map.try_emplace(map.begin(), key_30, 2) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == 10);
            CHECK(key_20 == 20);
            CHECK(key_30 == 30);
        }
    }

    PRINT("Test try_emplace(const_iterator, Key&&, Args&&...)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.try_emplace(map.begin(), std::move(key_10), 1) == map.nth(0));
            CHECK(map.try_emplace(map.begin(), std::move(key_20), 1) == map.nth(1));
            CHECK(map.try_emplace(map.begin(), std::move(key_30), 1) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == -10);
            CHECK(key_20 == -20);
            CHECK(key_30 == -30);
        }

        {
            xint key_10(10);
            xint key_20(20);
            xint key_30(30);

            CHECK(map.try_emplace(map.begin(), std::move(key_10), 2) == map.nth(0));
            CHECK(map.try_emplace(map.begin(), std::move(key_20), 2) == map.nth(1));
            CHECK(map.try_emplace(map.begin(), std::move(key_30), 2) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            CHECK(key_10 == +10);
            CHECK(key_20 == +20);
            CHECK(key_30 == +30);
        }
    }

    PRINT("Test try_emplace(const_iterator, K&&, Args&&...)");
    {
        sfl::static_unordered_flat_map<xobj, xint, 100, xobj::equal> map;

        {
            CHECK(map.try_emplace(map.begin(), 10, 1) == map.nth(0));
            CHECK(map.try_emplace(map.begin(), 20, 1) == map.nth(1));
            CHECK(map.try_emplace(map.begin(), 30, 1) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 1);
        }

        {
            CHECK(map.try_emplace(map.begin(), 10, 2) == map.nth(0));
            CHECK(map.try_emplace(map.begin(), 20, 2) == map.nth(1));
            CHECK(map.try_emplace(map.begin(), 30, 2) == map.nth(2));

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 1);
        }
    }

    PRINT("Test erase(const_iterator)");
    {
        // Erase at the end
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);
            map.emplace(40, 1);
            map.emplace(50, 1);

            CHECK(map.size() == 5);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(4)) == map.nth(4));
            CHECK(map.size() == 4);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(3)) == map.nth(3));
            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(2)) == map.nth(2));
            CHECK(map.size() == 2);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(1)) == map.nth(1));
            CHECK(map.size() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0)) == map.nth(0));
            CHECK(map.size() == 0);
        }

        // Erase at the begin
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);
            map.emplace(40, 1);
            map.emplace(50, 1);

            CHECK(map.size() == 5);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0)) == map.nth(0));
            CHECK(map.size() == 4);
            CHECK(map.nth(0)->first == 50); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0)) == map.nth(0));
            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 40); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0)) == map.nth(0));
            CHECK(map.size() == 2);
            CHECK(map.nth(0)->first == 30); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0)) == map.nth(0));
            CHECK(map.size() == 1);
            CHECK(map.nth(0)->first == 20); CHECK(map.nth(0)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0)) == map.nth(0));
            CHECK(map.size() == 0);
        }

        // Erase near the end
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);
            map.emplace(40, 1);
            map.emplace(50, 1);

            CHECK(map.size() == 5);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(3)) == map.nth(3));
            CHECK(map.size() == 4);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 50); CHECK(map.nth(3)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(2)) == map.nth(2));
            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 50); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(1)) == map.nth(1));
            CHECK(map.size() == 2);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 50); CHECK(map.nth(1)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0)) == map.nth(0));
            CHECK(map.size() == 1);
            CHECK(map.nth(0)->first == 50); CHECK(map.nth(0)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0)) == map.nth(0));
            CHECK(map.size() == 0);
        }

        // Erase near the begin
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);
            map.emplace(40, 1);
            map.emplace(50, 1);

            CHECK(map.size() == 5);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(1)) == map.nth(1));
            CHECK(map.size() == 4);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 50); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(1)) == map.nth(1));
            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 40); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(1)) == map.nth(1));
            CHECK(map.size() == 2);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 30); CHECK(map.nth(1)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(1)) == map.nth(1));
            CHECK(map.size() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0)) == map.nth(0));
            CHECK(map.size() == 0);
        }
    }

    PRINT("Test erase(const_iterator, const_iterator)");
    {
        // Erase at the end
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);
            map.emplace(40, 1);
            map.emplace(50, 1);
            map.emplace(60, 1);
            map.emplace(70, 1);
            map.emplace(80, 1);
            map.emplace(90, 1);

            CHECK(map.size() == 9);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);
            CHECK(map.nth(5)->first == 60); CHECK(map.nth(5)->second == 1);
            CHECK(map.nth(6)->first == 70); CHECK(map.nth(6)->second == 1);
            CHECK(map.nth(7)->first == 80); CHECK(map.nth(7)->second == 1);
            CHECK(map.nth(8)->first == 90); CHECK(map.nth(8)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(6), map.nth(9)) == map.nth(6));
            CHECK(map.size() == 6);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);
            CHECK(map.nth(5)->first == 60); CHECK(map.nth(5)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(3), map.nth(6)) == map.nth(3));
            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0), map.nth(3)) == map.nth(0));
            CHECK(map.size() == 0);
        }

        // Erase at the begin
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);
            map.emplace(40, 1);
            map.emplace(50, 1);
            map.emplace(60, 1);
            map.emplace(70, 1);
            map.emplace(80, 1);
            map.emplace(90, 1);

            CHECK(map.size() == 9);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);
            CHECK(map.nth(5)->first == 60); CHECK(map.nth(5)->second == 1);
            CHECK(map.nth(6)->first == 70); CHECK(map.nth(6)->second == 1);
            CHECK(map.nth(7)->first == 80); CHECK(map.nth(7)->second == 1);
            CHECK(map.nth(8)->first == 90); CHECK(map.nth(8)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0), map.nth(3)) == map.nth(0));
            CHECK(map.size() == 6);
            CHECK(map.nth(0)->first == 70); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 80); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 90); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);
            CHECK(map.nth(5)->first == 60); CHECK(map.nth(5)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0), map.nth(3)) == map.nth(0));
            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 40); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 50); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 60); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0), map.nth(3)) == map.nth(0));
            CHECK(map.size() == 0);
        }

        // Erase near the end
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);
            map.emplace(40, 1);
            map.emplace(50, 1);
            map.emplace(60, 1);
            map.emplace(70, 1);
            map.emplace(80, 1);
            map.emplace(90, 1);

            CHECK(map.size() == 9);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);
            CHECK(map.nth(5)->first == 60); CHECK(map.nth(5)->second == 1);
            CHECK(map.nth(6)->first == 70); CHECK(map.nth(6)->second == 1);
            CHECK(map.nth(7)->first == 80); CHECK(map.nth(7)->second == 1);
            CHECK(map.nth(8)->first == 90); CHECK(map.nth(8)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(5), map.nth(8)) == map.nth(5));
            CHECK(map.size() == 6);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);
            CHECK(map.nth(5)->first == 90); CHECK(map.nth(5)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(2), map.nth(5)) == map.nth(2));
            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 90); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(1), map.nth(2)) == map.nth(1));
            CHECK(map.size() == 2);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 90); CHECK(map.nth(1)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0), map.nth(2)) == map.nth(0));
            CHECK(map.size() == 0);
        }

        // Erase near the begin
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);
            map.emplace(40, 1);
            map.emplace(50, 1);
            map.emplace(60, 1);
            map.emplace(70, 1);
            map.emplace(80, 1);
            map.emplace(90, 1);

            CHECK(map.size() == 9);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);
            CHECK(map.nth(5)->first == 60); CHECK(map.nth(5)->second == 1);
            CHECK(map.nth(6)->first == 70); CHECK(map.nth(6)->second == 1);
            CHECK(map.nth(7)->first == 80); CHECK(map.nth(7)->second == 1);
            CHECK(map.nth(8)->first == 90); CHECK(map.nth(8)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(1), map.nth(4)) == map.nth(1));
            CHECK(map.size() == 6);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 70); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 80); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 90); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);
            CHECK(map.nth(5)->first == 60); CHECK(map.nth(5)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(1), map.nth(4)) == map.nth(1));
            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 50); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 60); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(1), map.nth(2)) == map.nth(1));
            CHECK(map.size() == 2);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 60); CHECK(map.nth(1)->second == 1);

            ///////////////////////////////////////////////////////////////////////

            CHECK(map.erase(map.nth(0), map.nth(2)) == map.nth(0));
            CHECK(map.size() == 0);
        }
    }

    PRINT("Test erase(const Key&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        map.emplace(10, 1);
        map.emplace(20, 1);
        map.emplace(30, 1);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

        CHECK(map.erase(30) == 1);
        CHECK(map.erase(30) == 0);
        CHECK(map.size() == 2);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);

        CHECK(map.erase(20) == 1);
        CHECK(map.erase(20) == 0);
        CHECK(map.size() == 1);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);

        CHECK(map.erase(10) == 1);
        CHECK(map.erase(10) == 0);
        CHECK(map.size() == 0);
    }

    PRINT("Test erase(K&&)");
    {
        sfl::static_unordered_flat_map<xobj, xint, 100, xobj::equal> map;

        map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(1));

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 1);

        CHECK(map.erase(30) == 1);
        CHECK(map.erase(30) == 0);
        CHECK(map.size() == 2);
        CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 1);

        CHECK(map.erase(20) == 1);
        CHECK(map.erase(20) == 0);
        CHECK(map.size() == 1);
        CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 1);

        CHECK(map.erase(10) == 1);
        CHECK(map.erase(10) == 0);
        CHECK(map.size() == 0);
    }

    PRINT("Test swap(container&)");
    {
        // Swap with self
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////

            map.swap(map);

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
        }

        // map1.size() == map2.size()
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1, map2;

            map1.emplace(10, 1);
            map1.emplace(20, 1);
            map1.emplace(30, 1);

            map2.emplace(40, 2);
            map2.emplace(50, 2);
            map2.emplace(60, 2);

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
            CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
            CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == 40); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 50); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 60); CHECK(map2.nth(2)->second == 2);

            ///////////////////////////////////////////////////////////////////

            map1.swap(map2);

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 40); CHECK(map1.nth(0)->second == 2);
            CHECK(map1.nth(1)->first == 50); CHECK(map1.nth(1)->second == 2);
            CHECK(map1.nth(2)->first == 60); CHECK(map1.nth(2)->second == 2);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == 10); CHECK(map2.nth(0)->second == 1);
            CHECK(map2.nth(1)->first == 20); CHECK(map2.nth(1)->second == 1);
            CHECK(map2.nth(2)->first == 30); CHECK(map2.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////

            map1.swap(map2);

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
            CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
            CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == 40); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 50); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 60); CHECK(map2.nth(2)->second == 2);
        }

        // map1.size() != map2.size()
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1, map2;

            map1.emplace(10, 1);
            map1.emplace(20, 1);
            map1.emplace(30, 1);

            map2.emplace(40, 2);
            map2.emplace(50, 2);
            map2.emplace(60, 2);
            map2.emplace(70, 2);
            map2.emplace(80, 2);

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
            CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
            CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);

            CHECK(map2.size() == 5);
            CHECK(map2.nth(0)->first == 40); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 50); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 60); CHECK(map2.nth(2)->second == 2);
            CHECK(map2.nth(3)->first == 70); CHECK(map2.nth(3)->second == 2);
            CHECK(map2.nth(4)->first == 80); CHECK(map2.nth(4)->second == 2);

            ///////////////////////////////////////////////////////////////////

            map1.swap(map2);

            CHECK(map1.size() == 5);
            CHECK(map1.nth(0)->first == 40); CHECK(map1.nth(0)->second == 2);
            CHECK(map1.nth(1)->first == 50); CHECK(map1.nth(1)->second == 2);
            CHECK(map1.nth(2)->first == 60); CHECK(map1.nth(2)->second == 2);
            CHECK(map1.nth(3)->first == 70); CHECK(map1.nth(3)->second == 2);
            CHECK(map1.nth(4)->first == 80); CHECK(map1.nth(4)->second == 2);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == 10); CHECK(map2.nth(0)->second == 1);
            CHECK(map2.nth(1)->first == 20); CHECK(map2.nth(1)->second == 1);
            CHECK(map2.nth(2)->first == 30); CHECK(map2.nth(2)->second == 1);

            ///////////////////////////////////////////////////////////////////

            map1.swap(map2);

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
            CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
            CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);

            CHECK(map2.size() == 5);
            CHECK(map2.nth(0)->first == 40); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 50); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 60); CHECK(map2.nth(2)->second == 2);
            CHECK(map2.nth(3)->first == 70); CHECK(map2.nth(3)->second == 2);
            CHECK(map2.nth(4)->first == 80); CHECK(map2.nth(4)->second == 2);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test at(const Key&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        map.emplace(10, 1);
        map.emplace(20, 1);
        map.emplace(30, 1);

        CHECK(map.at(10) == 1);
        CHECK(map.at(20) == 1);
        CHECK(map.at(30) == 1);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

        map.at(10) = 2;
        map.at(20) = 2;
        map.at(30) = 2;

        CHECK(map.at(10) == 2);
        CHECK(map.at(20) == 2);
        CHECK(map.at(30) == 2);

        #if !defined(SFL_NO_EXCEPTIONS)
        bool caught_exception = false;

        try
        {
            map.at(40) = 1;
        }
        catch (...)
        {
            caught_exception = true;
        }

        CHECK(caught_exception == true);
        #endif

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 2);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 2);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 2);
    }

    PRINT("Test at(const K&)");
    {
        sfl::static_unordered_flat_map<xobj, xint, 100, xobj::equal> map;

        map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(1));

        CHECK(map.at(10) == 1);
        CHECK(map.at(20) == 1);
        CHECK(map.at(30) == 1);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 1);

        map.at(10) = 2;
        map.at(20) = 2;
        map.at(30) = 2;

        CHECK(map.at(10) == 2);
        CHECK(map.at(20) == 2);
        CHECK(map.at(30) == 2);

        #if !defined(SFL_NO_EXCEPTIONS)
        bool caught_exception = false;

        try
        {
            map.at(40) = 1;
        }
        catch (...)
        {
            caught_exception = true;
        }

        CHECK(caught_exception == true);
        #endif

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 2);
        CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 2);
        CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 2);
    }

    PRINT("Test operator[](const Key&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        map.emplace(10, 1);
        map.emplace(20, 1);
        map.emplace(30, 1);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////////

        xint key_10 = 10;
        xint key_20 = 20;
        xint key_30 = 30;
        xint key_40 = 40;
        xint key_50 = 50;
        xint key_60 = 60;

        map[key_10] = 2;
        map[key_20] = 2;
        map[key_30] = 2;
        map[key_40] = 2;
        map[key_50] = 2;
        map[key_60] = 2;

        CHECK(map.size() == 6);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 2);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 2);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 2);
        CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 2);
        CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 2);
        CHECK(map.nth(5)->first == 60); CHECK(map.nth(5)->second == 2);

        CHECK(key_10 == 10);
        CHECK(key_20 == 20);
        CHECK(key_30 == 30);
        CHECK(key_40 == 40);
        CHECK(key_50 == 50);
        CHECK(key_60 == 60);
    }

    PRINT("Test operator[](Key&&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        map.emplace(10, 1);
        map.emplace(20, 1);
        map.emplace(30, 1);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////////

        xint key_10 = 10;
        xint key_20 = 20;
        xint key_30 = 30;
        xint key_40 = 40;
        xint key_50 = 50;
        xint key_60 = 60;

        map[std::move(key_10)] = 2;
        map[std::move(key_20)] = 2;
        map[std::move(key_30)] = 2;
        map[std::move(key_40)] = 2;
        map[std::move(key_50)] = 2;
        map[std::move(key_60)] = 2;

        CHECK(map.size() == 6);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 2);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 2);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 2);
        CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 2);
        CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 2);
        CHECK(map.nth(5)->first == 60); CHECK(map.nth(5)->second == 2);

        CHECK(key_10 == +10);
        CHECK(key_20 == +20);
        CHECK(key_30 == +30);
        CHECK(key_40 == -40);
        CHECK(key_50 == -50);
        CHECK(key_60 == -60);
    }

    PRINT("Test operator[](K&&)");
    {
        sfl::static_unordered_flat_map<xobj, xint, 100, xobj::equal> map;

        map.emplace(std::piecewise_construct, std::forward_as_tuple(10), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(20), std::forward_as_tuple(1));
        map.emplace(std::piecewise_construct, std::forward_as_tuple(30), std::forward_as_tuple(1));

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////////

        map[10] = 2;
        map[20] = 2;
        map[30] = 2;
        map[40] = 2;
        map[50] = 2;
        map[60] = 2;

        CHECK(map.size() == 6);
        CHECK(map.nth(0)->first.value() == 10); CHECK(map.nth(0)->second == 2);
        CHECK(map.nth(1)->first.value() == 20); CHECK(map.nth(1)->second == 2);
        CHECK(map.nth(2)->first.value() == 30); CHECK(map.nth(2)->second == 2);
        CHECK(map.nth(3)->first.value() == 40); CHECK(map.nth(3)->second == 2);
        CHECK(map.nth(4)->first.value() == 50); CHECK(map.nth(4)->second == 2);
        CHECK(map.nth(5)->first.value() == 60); CHECK(map.nth(5)->second == 2);
    }

    PRINT("Test data()");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        map.emplace(10, 1);
        map.emplace(20, 1);
        map.emplace(30, 1);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////////

        auto data = map.data();
        CHECK(data->first == 10); CHECK(data->second == 1); ++data;
        CHECK(data->first == 20); CHECK(data->second == 1); ++data;
        CHECK(data->first == 30); CHECK(data->second == 1); ++data;
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test container()");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

        CHECK(map.size() == 0);
        CHECK(map.capacity() == 100);
        CHECK(map.available() == 100);
    }

    PRINT("Test container(const KeyEqual&)");
    {
        std::equal_to<xint> equal;

        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map(equal);

        CHECK(map.size() == 0);
        CHECK(map.capacity() == 100);
        CHECK(map.available() == 100);
    }

    PRINT("Test container(InputIt, InputIt)");
    {
        std::vector<std::pair<xint, xint>> data
        (
            {
                {10, 1},
                {20, 1},
                {30, 1},

                {10, 2},
                {20, 2},
                {30, 2}
            }
        );

        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map(data.begin(), data.end());

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
    }

    PRINT("Test container(InputIt, InputIt, const KeyEqual&)");
    {
        std::vector<std::pair<xint, xint>> data
        (
            {
                {10, 1},
                {20, 1},
                {30, 1},

                {10, 2},
                {20, 2},
                {30, 2}
            }
        );

        std::equal_to<xint> equal;

        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map(data.begin(), data.end(), equal);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
    }

    PRINT("Test container(std::initializer_list)");
    {
        std::initializer_list<std::pair<xint, xint>> ilist
        {
            {10, 1},
            {20, 1},
            {30, 1},

            {10, 2},
            {20, 2},
            {30, 2}
        };

        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map(ilist);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
    }

    PRINT("Test container(std::initializer_list, const KeyEqual&)");
    {
        std::initializer_list<std::pair<xint, xint>> ilist
        {
            {10, 1},
            {20, 1},
            {30, 1},

            {10, 2},
            {20, 2},
            {30, 2}
        };

        std::equal_to<xint> equal;

        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map(ilist, equal);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
    }

    PRINT("Test container(const container&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1;

        map1.emplace(10, 1);
        map1.emplace(20, 1);
        map1.emplace(30, 1);

        CHECK(map1.size() == 3);
        CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
        CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
        CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////

        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map2(map1);

        CHECK(map2.size() == 3);
        CHECK(map2.nth(0)->first == 10); CHECK(map2.nth(0)->second == 1);
        CHECK(map2.nth(1)->first == 20); CHECK(map2.nth(1)->second == 1);
        CHECK(map2.nth(2)->first == 30); CHECK(map2.nth(2)->second == 1);
    }

    PRINT("Test container(container&&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1;

        map1.emplace(10, 1);
        map1.emplace(20, 1);
        map1.emplace(30, 1);

        CHECK(map1.size() == 3);
        CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
        CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
        CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////

        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map2(std::move(map1));

        CHECK(map2.size() == 3);
        CHECK(map2.nth(0)->first == 10); CHECK(map2.nth(0)->second == 1);
        CHECK(map2.nth(1)->first == 20); CHECK(map2.nth(1)->second == 1);
        CHECK(map2.nth(2)->first == 30); CHECK(map2.nth(2)->second == 1);

        CHECK(map1.size() == 3);
        CHECK(map1.nth(0)->first == -10); CHECK(map1.nth(0)->second == -1);
        CHECK(map1.nth(1)->first == -20); CHECK(map1.nth(1)->second == -1);
        CHECK(map1.nth(2)->first == -30); CHECK(map1.nth(2)->second == -1);
    }

    PRINT("Test container(sfl::from_range_t, Range&&)");
    {
        // Input iterator (exactly)
        {
            std::istringstream iss("10 1 20 1 30 1 20 2 20 3");

            #if SFL_CPP_VERSION >= SFL_CPP_20
            sfl::static_unordered_flat_map<xint, xint, 32, std::equal_to<xint>> map
            (
                (sfl::from_range_t()),
                (std::views::istream<std::pair<int, int>>(iss))
            );
            #else
            sfl::static_unordered_flat_map<xint, xint, 32, std::equal_to<xint>> map
            (
                (sfl::from_range_t()),
                (sfl::test::istream_view<std::pair<int, int>>(iss))
            );
            #endif

            CHECK(map.empty() == false);
            CHECK(map.size() == 3);
            CHECK(map.max_size() > 0);
            CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
            CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
            CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
        }

        // Forward iterator
        {
            std::vector<std::pair<xint, xint>> data
            (
                {
                    {10, 1},
                    {20, 1},
                    {30, 1},
                    {20, 2},
                    {20, 3}
                }
            );

            #if SFL_CPP_VERSION >= SFL_CPP_20
            sfl::static_unordered_flat_map<xint, xint, 32, std::equal_to<xint>> map
            (
                sfl::from_range_t(),
                std::views::all(data)
            );
            #else
            sfl::static_unordered_flat_map<xint, xint, 32, std::equal_to<xint>> map
            (
                sfl::from_range_t(),
                data
            );
            #endif

            CHECK(map.empty() == false);
            CHECK(map.size() == 3);
            CHECK(map.max_size() > 0);
            CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
            CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
            CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
        }
    }

    PRINT("Test container(sfl::from_range_t, Range&&, const KeyEqual&)");
    {
        // Input iterator (exactly)
        {
            std::istringstream iss("10 1 20 1 30 1 20 2 20 3");

            std::equal_to<xint> equal;

            #if SFL_CPP_VERSION >= SFL_CPP_20
            sfl::static_unordered_flat_map<xint, xint, 32, std::equal_to<xint>> map
            (
                (sfl::from_range_t()),
                (std::views::istream<std::pair<int, int>>(iss)),
                equal
            );
            #else
            sfl::static_unordered_flat_map<xint, xint, 32, std::equal_to<xint>> map
            (
                (sfl::from_range_t()),
                (sfl::test::istream_view<std::pair<int, int>>(iss)),
                equal
            );
            #endif

            CHECK(map.empty() == false);
            CHECK(map.size() == 3);
            CHECK(map.max_size() > 0);
            CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
            CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
            CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
        }

        // Forward iterator
        {
            std::vector<std::pair<xint, xint>> data
            (
                {
                    {10, 1},
                    {20, 1},
                    {30, 1},
                    {20, 2},
                    {20, 3}
                }
            );

            std::equal_to<xint> equal;

            #if SFL_CPP_VERSION >= SFL_CPP_20
            sfl::static_unordered_flat_map<xint, xint, 32, std::equal_to<xint>> map
            (
                sfl::from_range_t(),
                std::views::all(data),
                equal
            );
            #else
            sfl::static_unordered_flat_map<xint, xint, 32, std::equal_to<xint>> map
            (
                sfl::from_range_t(),
                data,
                equal
            );
            #endif

            CHECK(map.empty() == false);
            CHECK(map.size() == 3);
            CHECK(map.max_size() > 0);
            CHECK(NTH(map, 0)->first == 10); CHECK(NTH(map, 0)->second == 1);
            CHECK(NTH(map, 1)->first == 20); CHECK(NTH(map, 1)->second == 1);
            CHECK(NTH(map, 2)->first == 30); CHECK(NTH(map, 2)->second == 1);
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    PRINT("Test operator=(const container&)");
    {
        #define CONDITION map1.size() == map2.size()
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1, map2;

            map1.emplace(10, 1);
            map1.emplace(20, 1);
            map1.emplace(30, 1);

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
            CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
            CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);

            map2.emplace(40, 2);
            map2.emplace(50, 2);
            map2.emplace(60, 2);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == 40); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 50); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 60); CHECK(map2.nth(2)->second == 2);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            map1 = map2;

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 40); CHECK(map1.nth(0)->second == 2);
            CHECK(map1.nth(1)->first == 50); CHECK(map1.nth(1)->second == 2);
            CHECK(map1.nth(2)->first == 60); CHECK(map1.nth(2)->second == 2);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == 40); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 50); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 60); CHECK(map2.nth(2)->second == 2);
        }
        #undef CONDITION

        #define CONDITION map1.size() < map2.size()
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1, map2;

            map1.emplace(10, 1);
            map1.emplace(20, 1);
            map1.emplace(30, 1);

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
            CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
            CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);

            map2.emplace(40, 2);
            map2.emplace(50, 2);
            map2.emplace(60, 2);
            map2.emplace(70, 2);
            map2.emplace(80, 2);

            CHECK(map2.size() == 5);
            CHECK(map2.nth(0)->first == 40); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 50); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 60); CHECK(map2.nth(2)->second == 2);
            CHECK(map2.nth(3)->first == 70); CHECK(map2.nth(3)->second == 2);
            CHECK(map2.nth(4)->first == 80); CHECK(map2.nth(4)->second == 2);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            map1 = map2;

            CHECK(map1.size() == 5);
            CHECK(map1.nth(0)->first == 40); CHECK(map1.nth(0)->second == 2);
            CHECK(map1.nth(1)->first == 50); CHECK(map1.nth(1)->second == 2);
            CHECK(map1.nth(2)->first == 60); CHECK(map1.nth(2)->second == 2);
            CHECK(map1.nth(3)->first == 70); CHECK(map1.nth(3)->second == 2);
            CHECK(map1.nth(4)->first == 80); CHECK(map1.nth(4)->second == 2);

            CHECK(map2.size() == 5);
            CHECK(map2.nth(0)->first == 40); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 50); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 60); CHECK(map2.nth(2)->second == 2);
            CHECK(map2.nth(3)->first == 70); CHECK(map2.nth(3)->second == 2);
            CHECK(map2.nth(4)->first == 80); CHECK(map2.nth(4)->second == 2);
        }
        #undef CONDITION

        #define CONDITION map1.size() > map2.size()
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1, map2;

            map1.emplace(10, 1);
            map1.emplace(20, 1);
            map1.emplace(30, 1);
            map1.emplace(40, 1);
            map1.emplace(50, 1);

            CHECK(map1.size() == 5);
            CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
            CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
            CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);
            CHECK(map1.nth(3)->first == 40); CHECK(map1.nth(3)->second == 1);
            CHECK(map1.nth(4)->first == 50); CHECK(map1.nth(4)->second == 1);

            map2.emplace(60, 2);
            map2.emplace(70, 2);
            map2.emplace(80, 2);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == 60); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 70); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 80); CHECK(map2.nth(2)->second == 2);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            map1 = map2;

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 60); CHECK(map1.nth(0)->second == 2);
            CHECK(map1.nth(1)->first == 70); CHECK(map1.nth(1)->second == 2);
            CHECK(map1.nth(2)->first == 80); CHECK(map1.nth(2)->second == 2);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == 60); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 70); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 80); CHECK(map2.nth(2)->second == 2);
        }
        #undef CONDITION
    }

    PRINT("Test operator=(container&&)");
    {
        #define CONDITION map1.size() == map2.size()
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1, map2;

            map1.emplace(10, 1);
            map1.emplace(20, 1);
            map1.emplace(30, 1);

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
            CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
            CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);

            map2.emplace(40, 2);
            map2.emplace(50, 2);
            map2.emplace(60, 2);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == 40); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 50); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 60); CHECK(map2.nth(2)->second == 2);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            map1 = std::move(map2);

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 40); CHECK(map1.nth(0)->second == 2);
            CHECK(map1.nth(1)->first == 50); CHECK(map1.nth(1)->second == 2);
            CHECK(map1.nth(2)->first == 60); CHECK(map1.nth(2)->second == 2);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == -40); CHECK(map2.nth(0)->second == -2);
            CHECK(map2.nth(1)->first == -50); CHECK(map2.nth(1)->second == -2);
            CHECK(map2.nth(2)->first == -60); CHECK(map2.nth(2)->second == -2);
        }
        #undef CONDITION

        #define CONDITION map1.size() < map2.size()
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1, map2;

            map1.emplace(10, 1);
            map1.emplace(20, 1);
            map1.emplace(30, 1);

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
            CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
            CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);

            map2.emplace(40, 2);
            map2.emplace(50, 2);
            map2.emplace(60, 2);
            map2.emplace(70, 2);
            map2.emplace(80, 2);

            CHECK(map2.size() == 5);
            CHECK(map2.nth(0)->first == 40); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 50); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 60); CHECK(map2.nth(2)->second == 2);
            CHECK(map2.nth(3)->first == 70); CHECK(map2.nth(3)->second == 2);
            CHECK(map2.nth(4)->first == 80); CHECK(map2.nth(4)->second == 2);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            map1 = std::move(map2);

            CHECK(map1.size() == 5);
            CHECK(map1.nth(0)->first == 40); CHECK(map1.nth(0)->second == 2);
            CHECK(map1.nth(1)->first == 50); CHECK(map1.nth(1)->second == 2);
            CHECK(map1.nth(2)->first == 60); CHECK(map1.nth(2)->second == 2);
            CHECK(map1.nth(3)->first == 70); CHECK(map1.nth(3)->second == 2);
            CHECK(map1.nth(4)->first == 80); CHECK(map1.nth(4)->second == 2);

            CHECK(map2.size() == 5);
            CHECK(map2.nth(0)->first == -40); CHECK(map2.nth(0)->second == -2);
            CHECK(map2.nth(1)->first == -50); CHECK(map2.nth(1)->second == -2);
            CHECK(map2.nth(2)->first == -60); CHECK(map2.nth(2)->second == -2);
            CHECK(map2.nth(3)->first == -70); CHECK(map2.nth(3)->second == -2);
            CHECK(map2.nth(4)->first == -80); CHECK(map2.nth(4)->second == -2);
        }
        #undef CONDITION

        #define CONDITION map1.size() > map2.size()
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1, map2;

            map1.emplace(10, 1);
            map1.emplace(20, 1);
            map1.emplace(30, 1);
            map1.emplace(40, 1);
            map1.emplace(50, 1);

            CHECK(map1.size() == 5);
            CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
            CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
            CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);
            CHECK(map1.nth(3)->first == 40); CHECK(map1.nth(3)->second == 1);
            CHECK(map1.nth(4)->first == 50); CHECK(map1.nth(4)->second == 1);

            map2.emplace(60, 2);
            map2.emplace(70, 2);
            map2.emplace(80, 2);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == 60); CHECK(map2.nth(0)->second == 2);
            CHECK(map2.nth(1)->first == 70); CHECK(map2.nth(1)->second == 2);
            CHECK(map2.nth(2)->first == 80); CHECK(map2.nth(2)->second == 2);

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            map1 = std::move(map2);

            CHECK(map1.size() == 3);
            CHECK(map1.nth(0)->first == 60); CHECK(map1.nth(0)->second == 2);
            CHECK(map1.nth(1)->first == 70); CHECK(map1.nth(1)->second == 2);
            CHECK(map1.nth(2)->first == 80); CHECK(map1.nth(2)->second == 2);

            CHECK(map2.size() == 3);
            CHECK(map2.nth(0)->first == -60); CHECK(map2.nth(0)->second == -2);
            CHECK(map2.nth(1)->first == -70); CHECK(map2.nth(1)->second == -2);
            CHECK(map2.nth(2)->first == -80); CHECK(map2.nth(2)->second == -2);
        }
        #undef CONDITION
    }

    PRINT("Test operator=(std::initializer_list)");
    {
        #define CONDITION map.size() == ilist.size()
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            std::initializer_list<std::pair<xint, xint>> ilist
            {
                {40, 2},
                {50, 2},
                {60, 2}
            };

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            map = ilist;

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 40); CHECK(map.nth(0)->second == 2);
            CHECK(map.nth(1)->first == 50); CHECK(map.nth(1)->second == 2);
            CHECK(map.nth(2)->first == 60); CHECK(map.nth(2)->second == 2);
        }
        #undef CONDITION

        #define CONDITION map.size() < ilist.size()
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

            std::initializer_list<std::pair<xint, xint>> ilist
            {
                {40, 2},
                {50, 2},
                {60, 2},
                {70, 2},
                {80, 2}
            };

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            map = ilist;

            CHECK(map.size() == 5);
            CHECK(map.nth(0)->first == 40); CHECK(map.nth(0)->second == 2);
            CHECK(map.nth(1)->first == 50); CHECK(map.nth(1)->second == 2);
            CHECK(map.nth(2)->first == 60); CHECK(map.nth(2)->second == 2);
            CHECK(map.nth(3)->first == 70); CHECK(map.nth(3)->second == 2);
            CHECK(map.nth(4)->first == 80); CHECK(map.nth(4)->second == 2);
        }
        #undef CONDITION

        #define CONDITION map.size() > ilist.size()
        {
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map;

            map.emplace(10, 1);
            map.emplace(20, 1);
            map.emplace(30, 1);
            map.emplace(40, 1);
            map.emplace(50, 1);

            CHECK(map.size() == 5);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);

            std::initializer_list<std::pair<xint, xint>> ilist
            {
                {60, 2},
                {70, 2},
                {80, 2}
            };

            ///////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            map = ilist;

            CHECK(map.size() == 3);
            CHECK(map.nth(0)->first == 60); CHECK(map.nth(0)->second == 2);
            CHECK(map.nth(1)->first == 70); CHECK(map.nth(1)->second == 2);
            CHECK(map.nth(2)->first == 80); CHECK(map.nth(2)->second == 2);
        }
        #undef CONDITION
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test NON-MEMBER comparison operators");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1, map2, map3;

        map1.emplace(10, 1);
        map1.emplace(20, 1);
        map1.emplace(30, 1);

        map2.emplace(10, 1);
        map2.emplace(20, 1);
        map2.emplace(30, 1);
        map2.emplace(40, 1);
        map2.emplace(50, 1);

        map3.emplace(20, 1);
        map3.emplace(10, 1);
        map3.emplace(30, 1);
        map3.emplace(50, 1);
        map3.emplace(40, 1);

        CHECK((map1 == map1) == true);
        CHECK((map1 == map2) == false);
        CHECK((map2 == map1) == false);
        CHECK((map2 == map2) == true);

        CHECK((map1 != map1) == false);
        CHECK((map1 != map2) == true);
        CHECK((map2 != map1) == true);
        CHECK((map2 != map2) == false);

        CHECK((map2 == map3) == true);
        CHECK((map3 == map2) == true);
        CHECK((map2 != map3) == false);
        CHECK((map3 != map2) == false);
    }

    PRINT("Test NON-MEMBER swap(container&)");
    {
        sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>> map1, map2;

        map1.emplace(10, 1);
        map1.emplace(20, 1);
        map1.emplace(30, 1);

        map2.emplace(40, 2);
        map2.emplace(50, 2);
        map2.emplace(60, 2);
        map2.emplace(70, 2);
        map2.emplace(80, 2);

        CHECK(map1.size() == 3);
        CHECK(map1.nth(0)->first == 10); CHECK(map1.nth(0)->second == 1);
        CHECK(map1.nth(1)->first == 20); CHECK(map1.nth(1)->second == 1);
        CHECK(map1.nth(2)->first == 30); CHECK(map1.nth(2)->second == 1);

        CHECK(map2.size() == 5);
        CHECK(map2.nth(0)->first == 40); CHECK(map2.nth(0)->second == 2);
        CHECK(map2.nth(1)->first == 50); CHECK(map2.nth(1)->second == 2);
        CHECK(map2.nth(2)->first == 60); CHECK(map2.nth(2)->second == 2);
        CHECK(map2.nth(3)->first == 70); CHECK(map2.nth(3)->second == 2);
        CHECK(map2.nth(4)->first == 80); CHECK(map2.nth(4)->second == 2);

        ///////////////////////////////////////////////////////////////////////////

        swap(map1, map2);

        CHECK(map1.size() == 5);
        CHECK(map1.nth(0)->first == 40); CHECK(map1.nth(0)->second == 2);
        CHECK(map1.nth(1)->first == 50); CHECK(map1.nth(1)->second == 2);
        CHECK(map1.nth(2)->first == 60); CHECK(map1.nth(2)->second == 2);
        CHECK(map1.nth(3)->first == 70); CHECK(map1.nth(3)->second == 2);
        CHECK(map1.nth(4)->first == 80); CHECK(map1.nth(4)->second == 2);

        CHECK(map2.size() == 3);
        CHECK(map2.nth(0)->first == 10); CHECK(map2.nth(0)->second == 1);
        CHECK(map2.nth(1)->first == 20); CHECK(map2.nth(1)->second == 1);
        CHECK(map2.nth(2)->first == 30); CHECK(map2.nth(2)->second == 1);
    }

    PRINT("Test NON-MEMBER erase_if(container&, Predicate)");
    {
        using container_type =
            sfl::static_unordered_flat_map<xint, xint, 100, std::equal_to<xint>>;

        using const_reference = typename container_type::const_reference;

        ///////////////////////////////////////////////////////////////////////////

        container_type map;

        map.emplace(10, 1);
        map.emplace(20, 1);
        map.emplace(30, 1);

        CHECK(map.size() == 3);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
        CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////////

        CHECK(erase_if(map, [](const_reference& value){ return value.first == 20; }) == 1);
        CHECK(map.size() == 2);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 30); CHECK(map.nth(1)->second == 1);

        ///////////////////////////////////////////////////////////////////////////

        CHECK(erase_if(map, [](const_reference& value){ return value.first == 20; }) == 0);
        CHECK(map.size() == 2);
        CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
        CHECK(map.nth(1)->first == 30); CHECK(map.nth(1)->second == 1);
    }
}

int main()
{
    test_static_unordered_flat_map();
}
