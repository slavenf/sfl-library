//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include static_flat_set.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG // This is very important. Must be in the first line.

#define SFL_TEST_STATIC_FLAT_SET
#include "sfl/static_flat_set.hpp"

#include "check.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xint_xint.hpp"
#include "xobj.hpp"

#include <vector>

void test_static_flat_set()
{
    using sfl::test::xint;
    using sfl::test::xint_xint;
    using sfl::test::xobj;

    PRINT("Test PRIVATE member function insert_exactly_at(const_iterator, Args&&...)");
    {
        // Insert at the end
        {
            sfl::static_flat_set<xint_xint, 5, std::less<xint_xint>> set;

            {
                CHECK(set.empty() == true);
                CHECK(set.full() == false);
                CHECK(set.size() == 0);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 5);
            }

            {
                PRINT(">");
                const auto res = set.insert_exactly_at(set.end(), 10, 1);
                PRINT("<");

                CHECK(res == set.nth(0));
                CHECK(set.empty() == false);
                CHECK(set.full() == false);
                CHECK(set.size() == 1);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 4);
                CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            }

            {
                PRINT(">");
                const auto res = set.insert_exactly_at(set.end(), 20, 1);
                PRINT("<");

                CHECK(res == set.nth(1));
                CHECK(set.empty() == false);
                CHECK(set.full() == false);
                CHECK(set.size() == 2);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 3);
                CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
                CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            }

            {
                PRINT(">");
                const auto res = set.insert_exactly_at(set.end(), 30, 1);
                PRINT("<");

                CHECK(res == set.nth(2));
                CHECK(set.empty() == false);
                CHECK(set.full() == false);
                CHECK(set.size() == 3);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 2);
                CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
                CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
                CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
            }

            {
                PRINT(">");
                const auto res = set.insert_exactly_at(set.end(), 40, 1);
                PRINT("<");

                CHECK(res == set.nth(3));
                CHECK(set.empty() == false);
                CHECK(set.full() == false);
                CHECK(set.size() == 4);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 1);
                CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
                CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
                CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
                CHECK(set.nth(3)->first == 40); CHECK(set.nth(3)->second == 1);
            }

            {
                PRINT(">");
                const auto res = set.insert_exactly_at(set.end(), 50, 1);
                PRINT("<");

                CHECK(res == set.nth(4));
                CHECK(set.empty() == false);
                CHECK(set.full() == true);
                CHECK(set.size() == 5);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 0);
                CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
                CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
                CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
                CHECK(set.nth(3)->first == 40); CHECK(set.nth(3)->second == 1);
                CHECK(set.nth(4)->first == 50); CHECK(set.nth(4)->second == 1);
            }
        }

        // Insert at the begin
        {
            sfl::static_flat_set<xint_xint, 5, std::less<xint_xint>> set;

            {
                CHECK(set.empty() == true);
                CHECK(set.full() == false);
                CHECK(set.size() == 0);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 5);
            }

            {
                PRINT(">");
                const auto res = set.insert_exactly_at(set.begin(), 50, 1);
                PRINT("<");

                CHECK(res == set.nth(0));
                CHECK(set.empty() == false);
                CHECK(set.full() == false);
                CHECK(set.size() == 1);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 4);
                CHECK(set.nth(0)->first == 50); CHECK(set.nth(0)->second == 1);
            }

            {
                PRINT(">");
                const auto res = set.insert_exactly_at(set.begin(), 40, 1);
                PRINT("<");

                CHECK(res == set.nth(0));
                CHECK(set.empty() == false);
                CHECK(set.full() == false);
                CHECK(set.size() == 2);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 3);
                CHECK(set.nth(0)->first == 40); CHECK(set.nth(0)->second == 1);
                CHECK(set.nth(1)->first == 50); CHECK(set.nth(1)->second == 1);
            }

            {
                PRINT(">");
                const auto res = set.insert_exactly_at(set.begin(), 30, 1);
                PRINT("<");

                CHECK(res == set.nth(0));
                CHECK(set.empty() == false);
                CHECK(set.full() == false);
                CHECK(set.size() == 3);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 2);
                CHECK(set.nth(0)->first == 30); CHECK(set.nth(0)->second == 1);
                CHECK(set.nth(1)->first == 40); CHECK(set.nth(1)->second == 1);
                CHECK(set.nth(2)->first == 50); CHECK(set.nth(2)->second == 1);
            }

            {
                PRINT(">");
                const auto res = set.insert_exactly_at(set.begin(), 20, 1);
                PRINT("<");

                CHECK(res == set.nth(0));
                CHECK(set.empty() == false);
                CHECK(set.full() == false);
                CHECK(set.size() == 4);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 1);
                CHECK(set.nth(0)->first == 20); CHECK(set.nth(0)->second == 1);
                CHECK(set.nth(1)->first == 30); CHECK(set.nth(1)->second == 1);
                CHECK(set.nth(2)->first == 40); CHECK(set.nth(2)->second == 1);
                CHECK(set.nth(3)->first == 50); CHECK(set.nth(3)->second == 1);
            }

            {
                PRINT(">");
                const auto res = set.insert_exactly_at(set.begin(), 10, 1);
                PRINT("<");

                CHECK(res == set.nth(0));
                CHECK(set.empty() == false);
                CHECK(set.full() == true);
                CHECK(set.size() == 5);
                CHECK(set.capacity() == 5);
                CHECK(set.available() == 0);
                CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
                CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
                CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
                CHECK(set.nth(3)->first == 40); CHECK(set.nth(3)->second == 1);
                CHECK(set.nth(4)->first == 50); CHECK(set.nth(4)->second == 1);
            }
        }

        {
            sfl::static_flat_set<xint_xint, 5, std::less<xint_xint>> set;

            set.insert_exactly_at(set.end(), 10, 1);
            set.insert_exactly_at(set.end(), 20, 1);
            set.insert_exactly_at(set.end(), 30, 1);
            set.insert_exactly_at(set.end(), 40, 1);

            CHECK(set.empty() == false);
            CHECK(set.full() == false);
            CHECK(set.size() == 4);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 1);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 40); CHECK(set.nth(3)->second == 1);

            const auto res = set.insert_exactly_at(set.nth(0), 5, 1);

            CHECK(res == set.nth(0));
            CHECK(set.empty() == false);
            CHECK(set.full() == true);
            CHECK(set.size() == 5);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 0);
            CHECK(set.nth(0)->first ==  5); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 10); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 20); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 30); CHECK(set.nth(3)->second == 1);
            CHECK(set.nth(4)->first == 40); CHECK(set.nth(4)->second == 1);
        }

        {
            sfl::static_flat_set<xint_xint, 5, std::less<xint_xint>> set;

            set.insert_exactly_at(set.end(), 10, 1);
            set.insert_exactly_at(set.end(), 20, 1);
            set.insert_exactly_at(set.end(), 30, 1);
            set.insert_exactly_at(set.end(), 40, 1);

            CHECK(set.empty() == false);
            CHECK(set.full() == false);
            CHECK(set.size() == 4);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 1);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 40); CHECK(set.nth(3)->second == 1);

            const auto res = set.insert_exactly_at(set.nth(1), 15, 1);

            CHECK(res == set.nth(1));
            CHECK(set.empty() == false);
            CHECK(set.full() == true);
            CHECK(set.size() == 5);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 0);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 15); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 20); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 30); CHECK(set.nth(3)->second == 1);
            CHECK(set.nth(4)->first == 40); CHECK(set.nth(4)->second == 1);
        }

        {
            sfl::static_flat_set<xint_xint, 5, std::less<xint_xint>> set;

            set.insert_exactly_at(set.end(), 10, 1);
            set.insert_exactly_at(set.end(), 20, 1);
            set.insert_exactly_at(set.end(), 30, 1);
            set.insert_exactly_at(set.end(), 40, 1);

            CHECK(set.empty() == false);
            CHECK(set.full() == false);
            CHECK(set.size() == 4);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 1);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 40); CHECK(set.nth(3)->second == 1);

            const auto res = set.insert_exactly_at(set.nth(2), 25, 1);

            CHECK(res == set.nth(2));
            CHECK(set.empty() == false);
            CHECK(set.full() == true);
            CHECK(set.size() == 5);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 0);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 25); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 30); CHECK(set.nth(3)->second == 1);
            CHECK(set.nth(4)->first == 40); CHECK(set.nth(4)->second == 1);
        }

        {
            sfl::static_flat_set<xint_xint, 5, std::less<xint_xint>> set;

            set.insert_exactly_at(set.end(), 10, 1);
            set.insert_exactly_at(set.end(), 20, 1);
            set.insert_exactly_at(set.end(), 30, 1);
            set.insert_exactly_at(set.end(), 40, 1);

            CHECK(set.empty() == false);
            CHECK(set.full() == false);
            CHECK(set.size() == 4);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 1);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 40); CHECK(set.nth(3)->second == 1);

            const auto res = set.insert_exactly_at(set.nth(3), 35, 1);

            CHECK(res == set.nth(3));
            CHECK(set.empty() == false);
            CHECK(set.full() == true);
            CHECK(set.size() == 5);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 0);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 35); CHECK(set.nth(3)->second == 1);
            CHECK(set.nth(4)->first == 40); CHECK(set.nth(4)->second == 1);
        }

        {
            sfl::static_flat_set<xint_xint, 5, std::less<xint_xint>> set;

            set.insert_exactly_at(set.end(), 10, 1);
            set.insert_exactly_at(set.end(), 20, 1);
            set.insert_exactly_at(set.end(), 30, 1);
            set.insert_exactly_at(set.end(), 40, 1);

            CHECK(set.empty() == false);
            CHECK(set.full() == false);
            CHECK(set.size() == 4);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 1);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 40); CHECK(set.nth(3)->second == 1);

            const auto res = set.insert_exactly_at(set.nth(4), 45, 1);

            CHECK(res == set.nth(4));
            CHECK(set.empty() == false);
            CHECK(set.full() == true);
            CHECK(set.size() == 5);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 0);
            CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
            CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
            CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);
            CHECK(set.nth(3)->first == 40); CHECK(set.nth(3)->second == 1);
            CHECK(set.nth(4)->first == 45); CHECK(set.nth(4)->second == 1);
        }
    }

    PRINT("Test PRIVATE member function is_insert_hint_good(const_iterator, const Value&)");
    {
        sfl::static_flat_set<xint_xint, 100, std::less<xint_xint>> set;

        using value_type = xint_xint;

        ///////////////////////////////////////////////////////////////////////////

        set.insert_exactly_at(set.end(), value_type(20, 1));
        set.insert_exactly_at(set.end(), value_type(40, 1));
        set.insert_exactly_at(set.end(), value_type(60, 1));

        CHECK(set.size() == 3);
        CHECK(set.nth(0)->first == 20); CHECK(set.nth(0)->second == 1);
        CHECK(set.nth(1)->first == 40); CHECK(set.nth(1)->second == 1);
        CHECK(set.nth(2)->first == 60); CHECK(set.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////////

        CHECK(set.is_insert_hint_good(set.nth(0), value_type(20, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(1), value_type(20, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(2), value_type(20, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(3), value_type(20, 1)) == false);

        CHECK(set.is_insert_hint_good(set.nth(0), value_type(40, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(1), value_type(40, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(2), value_type(40, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(3), value_type(40, 1)) == false);

        CHECK(set.is_insert_hint_good(set.nth(0), value_type(60, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(1), value_type(60, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(2), value_type(60, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(3), value_type(60, 1)) == false);

        ///////////////////////////////////////////////////////////////////////////

        CHECK(set.is_insert_hint_good(set.nth(0), value_type(10, 1)) == true);
        CHECK(set.is_insert_hint_good(set.nth(1), value_type(10, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(2), value_type(10, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(3), value_type(10, 1)) == false);

        CHECK(set.is_insert_hint_good(set.nth(0), value_type(30, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(1), value_type(30, 1)) == true);
        CHECK(set.is_insert_hint_good(set.nth(2), value_type(30, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(3), value_type(30, 1)) == false);

        CHECK(set.is_insert_hint_good(set.nth(0), value_type(50, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(1), value_type(50, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(2), value_type(50, 1)) == true);
        CHECK(set.is_insert_hint_good(set.nth(3), value_type(50, 1)) == false);

        CHECK(set.is_insert_hint_good(set.nth(0), value_type(70, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(1), value_type(70, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(2), value_type(70, 1)) == false);
        CHECK(set.is_insert_hint_good(set.nth(3), value_type(70, 1)) == true);
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend, nth, index_of");
    {
        sfl::static_flat_set<xint_xint, 100, std::less<xint_xint>> set;

        set.insert_exactly_at(set.end(), 20, 1);
        set.insert_exactly_at(set.end(), 40, 1);
        set.insert_exactly_at(set.end(), 60, 1);

        CHECK(set.size() == 3);
        CHECK(set.nth(0)->first == 20); CHECK(set.nth(0)->second == 1);
        CHECK(set.nth(1)->first == 40); CHECK(set.nth(1)->second == 1);
        CHECK(set.nth(2)->first == 60); CHECK(set.nth(2)->second == 1);

        ///////////////////////////////////////////////////////////////////////

        auto it = set.begin();
        CHECK(it->first == 20); CHECK(it->second == 1); ++it;
        CHECK(it->first == 40); CHECK(it->second == 1); ++it;
        CHECK(it->first == 60); CHECK(it->second == 1); ++it;
        CHECK(it == set.end());

        ///////////////////////////////////////////////////////////////////////

        auto cit = set.cbegin();
        CHECK(cit->first == 20); CHECK(cit->second == 1); ++cit;
        CHECK(cit->first == 40); CHECK(cit->second == 1); ++cit;
        CHECK(cit->first == 60); CHECK(cit->second == 1); ++cit;
        CHECK(cit == set.cend());

        ///////////////////////////////////////////////////////////////////////

        auto rit = set.rbegin();
        CHECK(rit->first == 60); CHECK(rit->second == 1); ++rit;
        CHECK(rit->first == 40); CHECK(rit->second == 1); ++rit;
        CHECK(rit->first == 20); CHECK(rit->second == 1); ++rit;
        CHECK(rit == set.rend());

        ///////////////////////////////////////////////////////////////////////

        auto crit = set.crbegin();
        CHECK(crit->first == 60); CHECK(crit->second == 1); ++crit;
        CHECK(crit->first == 40); CHECK(crit->second == 1); ++crit;
        CHECK(crit->first == 20); CHECK(crit->second == 1); ++crit;
        CHECK(crit == set.crend());

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.nth(0)->first == 20); CHECK(set.nth(0)->second == 1);
        CHECK(set.nth(1)->first == 40); CHECK(set.nth(1)->second == 1);
        CHECK(set.nth(2)->first == 60); CHECK(set.nth(2)->second == 1);
        CHECK(set.nth(3) == set.end());

        ///////////////////////////////////////////////////////////////////////

        CHECK(std::next(set.begin(), 0) == set.nth(0));
        CHECK(std::next(set.begin(), 1) == set.nth(1));
        CHECK(std::next(set.begin(), 2) == set.nth(2));
        CHECK(std::next(set.begin(), 3) == set.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(std::next(set.cbegin(), 0) == set.nth(0));
        CHECK(std::next(set.cbegin(), 1) == set.nth(1));
        CHECK(std::next(set.cbegin(), 2) == set.nth(2));
        CHECK(std::next(set.cbegin(), 3) == set.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.nth(0) < set.nth(1));
        CHECK(set.nth(0) < set.nth(2));
        CHECK(set.nth(0) < set.nth(3));

        CHECK(set.nth(1) < set.nth(2));
        CHECK(set.nth(1) < set.nth(3));

        CHECK(set.nth(2) < set.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(set.index_of(set.nth(0)) == 0);
        CHECK(set.index_of(set.nth(1)) == 1);
        CHECK(set.index_of(set.nth(2)) == 2);
        CHECK(set.index_of(set.nth(3)) == 3);
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test key_comp()");
    {
        {
            sfl::static_flat_set<xint, 100, std::less<xint>> set;

            auto key_comp = set.key_comp();

            CHECK(key_comp(10, 10) == false);
            CHECK(key_comp(10, 20) == true);
            CHECK(key_comp(20, 10) == false);
            CHECK(key_comp(20, 20) == false);
        }

        {
            sfl::static_flat_set<xobj, 100, xobj::less> set;

            auto key_comp = set.key_comp();

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
            sfl::static_flat_set<xint, 100, std::less<xint>> set;

            auto value_comp = set.value_comp();

            CHECK(value_comp(10, 10) == false);
            CHECK(value_comp(10, 20) == true);
            CHECK(value_comp(20, 10) == false);
            CHECK(value_comp(20, 20) == false);
        }

        {
            sfl::static_flat_set<xobj, 100, xobj::less> set;

            auto value_comp = set.value_comp();

            CHECK(value_comp(xobj(10), 10) == false);
            CHECK(value_comp(xobj(10), 20) == true);
            CHECK(value_comp(xobj(20), 10) == false);
            CHECK(value_comp(xobj(20), 20) == false);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test lower_bound, upper_bound, equal_range, find, count, contains");
    {
        // xint
        {
            sfl::static_flat_set<xint, 100, std::less<xint>> set;

            set.insert_exactly_at(set.end(), 20);
            set.insert_exactly_at(set.end(), 40);
            set.insert_exactly_at(set.end(), 60);

            CHECK(set.size() == 3);
            CHECK(*set.nth(0) == 20);
            CHECK(*set.nth(1) == 40);
            CHECK(*set.nth(2) == 60);

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.lower_bound(10) == set.nth(0));
            CHECK(set.lower_bound(20) == set.nth(0));
            CHECK(set.lower_bound(30) == set.nth(1));
            CHECK(set.lower_bound(40) == set.nth(1));
            CHECK(set.lower_bound(50) == set.nth(2));
            CHECK(set.lower_bound(60) == set.nth(2));
            CHECK(set.lower_bound(70) == set.nth(3));

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.upper_bound(10) == set.nth(0));
            CHECK(set.upper_bound(20) == set.nth(1));
            CHECK(set.upper_bound(30) == set.nth(1));
            CHECK(set.upper_bound(40) == set.nth(2));
            CHECK(set.upper_bound(50) == set.nth(2));
            CHECK(set.upper_bound(60) == set.nth(3));
            CHECK(set.upper_bound(70) == set.nth(3));

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.equal_range(10) == std::make_pair(set.nth(0), set.nth(0)));
            CHECK(set.equal_range(20) == std::make_pair(set.nth(0), set.nth(1)));
            CHECK(set.equal_range(30) == std::make_pair(set.nth(1), set.nth(1)));
            CHECK(set.equal_range(40) == std::make_pair(set.nth(1), set.nth(2)));
            CHECK(set.equal_range(50) == std::make_pair(set.nth(2), set.nth(2)));
            CHECK(set.equal_range(60) == std::make_pair(set.nth(2), set.nth(3)));
            CHECK(set.equal_range(70) == std::make_pair(set.nth(3), set.nth(3)));

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.find(10) == set.end());
            CHECK(set.find(20) == set.nth(0));
            CHECK(set.find(30) == set.end());
            CHECK(set.find(40) == set.nth(1));
            CHECK(set.find(50) == set.end());
            CHECK(set.find(60) == set.nth(2));
            CHECK(set.find(70) == set.end());

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.count(10) == 0);
            CHECK(set.count(20) == 1);
            CHECK(set.count(30) == 0);
            CHECK(set.count(40) == 1);
            CHECK(set.count(50) == 0);
            CHECK(set.count(60) == 1);
            CHECK(set.count(70) == 0);

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.contains(10) == false);
            CHECK(set.contains(20) == true);
            CHECK(set.contains(30) == false);
            CHECK(set.contains(40) == true);
            CHECK(set.contains(50) == false);
            CHECK(set.contains(60) == true);
            CHECK(set.contains(70) == false);
        }

        // xobj
        {
            sfl::static_flat_set<xobj, 100, xobj::less> set;

            set.insert_exactly_at(set.end(), 20);
            set.insert_exactly_at(set.end(), 40);
            set.insert_exactly_at(set.end(), 60);

            CHECK(set.size() == 3);
            CHECK(set.nth(0)->value() == 20);
            CHECK(set.nth(1)->value() == 40);
            CHECK(set.nth(2)->value() == 60);

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.lower_bound(10) == set.nth(0));
            CHECK(set.lower_bound(20) == set.nth(0));
            CHECK(set.lower_bound(30) == set.nth(1));
            CHECK(set.lower_bound(40) == set.nth(1));
            CHECK(set.lower_bound(50) == set.nth(2));
            CHECK(set.lower_bound(60) == set.nth(2));
            CHECK(set.lower_bound(70) == set.nth(3));

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.upper_bound(10) == set.nth(0));
            CHECK(set.upper_bound(20) == set.nth(1));
            CHECK(set.upper_bound(30) == set.nth(1));
            CHECK(set.upper_bound(40) == set.nth(2));
            CHECK(set.upper_bound(50) == set.nth(2));
            CHECK(set.upper_bound(60) == set.nth(3));
            CHECK(set.upper_bound(70) == set.nth(3));

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.equal_range(10) == std::make_pair(set.nth(0), set.nth(0)));
            CHECK(set.equal_range(20) == std::make_pair(set.nth(0), set.nth(1)));
            CHECK(set.equal_range(30) == std::make_pair(set.nth(1), set.nth(1)));
            CHECK(set.equal_range(40) == std::make_pair(set.nth(1), set.nth(2)));
            CHECK(set.equal_range(50) == std::make_pair(set.nth(2), set.nth(2)));
            CHECK(set.equal_range(60) == std::make_pair(set.nth(2), set.nth(3)));
            CHECK(set.equal_range(70) == std::make_pair(set.nth(3), set.nth(3)));

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.find(10) == set.end());
            CHECK(set.find(20) == set.nth(0));
            CHECK(set.find(30) == set.end());
            CHECK(set.find(40) == set.nth(1));
            CHECK(set.find(50) == set.end());
            CHECK(set.find(60) == set.nth(2));
            CHECK(set.find(70) == set.end());

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.count(10) == 0);
            CHECK(set.count(20) == 1);
            CHECK(set.count(30) == 0);
            CHECK(set.count(40) == 1);
            CHECK(set.count(50) == 0);
            CHECK(set.count(60) == 1);
            CHECK(set.count(70) == 0);

            ///////////////////////////////////////////////////////////////////////

            CHECK(set.contains(10) == false);
            CHECK(set.contains(20) == true);
            CHECK(set.contains(30) == false);
            CHECK(set.contains(40) == true);
            CHECK(set.contains(50) == false);
            CHECK(set.contains(60) == true);
            CHECK(set.contains(70) == false);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    PRINT("Test clear()");
    {
        sfl::static_flat_set<xint_xint, 100, std::less<xint_xint>> set;

        CHECK(set.size() == 0);

        set.insert_exactly_at(set.end(), 10, 1);
        set.insert_exactly_at(set.end(), 20, 1);
        set.insert_exactly_at(set.end(), 30, 1);

        CHECK(set.size() == 3);
        CHECK(set.nth(0)->first == 10); CHECK(set.nth(0)->second == 1);
        CHECK(set.nth(1)->first == 20); CHECK(set.nth(1)->second == 1);
        CHECK(set.nth(2)->first == 30); CHECK(set.nth(2)->second == 1);

        set.clear();

        CHECK(set.size() == 0);

        set.insert_exactly_at(set.end(), 40, 2);
        set.insert_exactly_at(set.end(), 50, 2);
        set.insert_exactly_at(set.end(), 60, 2);

        CHECK(set.size() == 3);
        CHECK(set.nth(0)->first == 40); CHECK(set.nth(0)->second == 2);
        CHECK(set.nth(1)->first == 50); CHECK(set.nth(1)->second == 2);
        CHECK(set.nth(2)->first == 60); CHECK(set.nth(2)->second == 2);

        set.clear();

        CHECK(set.size() == 0);
    }
}

int main()
{
    test_static_flat_set();
}
