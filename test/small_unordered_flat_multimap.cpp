//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include small_unordered_flat_multimap.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG
#include <cassert>
#include <iostream>
#include <vector>

#include <sfl/small_unordered_flat_multimap.hpp>

#include "common/xint.hpp"
#include "common/xstr.hpp"
#include "common/Person.hpp"

#include "common/statefull_alloc.hpp"
#include "common/stateless_alloc.hpp"
#include "common/stateless_alloc_no_prop.hpp"
#include "common/stateless_fancy_alloc.hpp"

#ifndef TPARAM_ALLOCATOR
//#define TPARAM_ALLOCATOR std::allocator
//#define TPARAM_ALLOCATOR sfl::test::statefull_alloc
//#define TPARAM_ALLOCATOR sfl::test::stateless_alloc
//#define TPARAM_ALLOCATOR sfl::test::stateless_alloc_no_prop
#define TPARAM_ALLOCATOR sfl::test::stateless_fancy_alloc
#endif

#define CHECK(expr) assert(expr)

/* FIXME: Handle alignment
static_assert
(
    sizeof(sfl::small_unordered_flat_multimap<double, double, 0>) ==
        3 * sizeof(sfl::small_unordered_flat_multimap<double, double, 0>::pointer),
    "Invalid size"
);

static_assert
(
    sizeof(sfl::small_unordered_flat_multimap<double, double, 5>) ==
        3 * sizeof(sfl::small_unordered_flat_multimap<double, double, 5>::pointer) +
        5 * sizeof(sfl::small_unordered_flat_multimap<double, double, 5>::value_type),
    "Invalid size"
);
*/

int main()
{
    using std::cout;
    using std::endl;
    using sfl::test::xint;
    using sfl::test::xstr;

    cout << "Create empty containers and test all non-modifying "
            "member functions." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1;

        const sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2;

        sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3;

        const sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m4;

        CHECK(m1.empty());
        CHECK(m2.empty());
        CHECK(m3.empty());
        CHECK(m4.empty());

        CHECK(m1.size() == 0);
        CHECK(m2.size() == 0);
        CHECK(m3.size() == 0);
        CHECK(m4.size() == 0);

        CHECK(m1.capacity() == 0);
        CHECK(m2.capacity() == 0);
        CHECK(m3.capacity() == 5);
        CHECK(m4.capacity() == 5);

        CHECK(m1.begin() == m1.end());
        CHECK(m2.begin() == m2.end());
        CHECK(m3.begin() == m3.end());
        CHECK(m4.begin() == m4.end());

        CHECK(m1.cbegin() == m1.cend());
        CHECK(m2.cbegin() == m2.cend());
        CHECK(m3.cbegin() == m3.cend());
        CHECK(m4.cbegin() == m4.cend());

        CHECK(m1.begin() == m1.cbegin());
        CHECK(m2.begin() == m2.cbegin());
        CHECK(m3.begin() == m3.cbegin());
        CHECK(m4.begin() == m4.cbegin());

        CHECK(m1.begin() == m1.nth(0));
        CHECK(m2.begin() == m2.nth(0));
        CHECK(m3.begin() == m3.nth(0));
        CHECK(m4.begin() == m4.nth(0));

        CHECK(m1.cbegin() == m1.nth(0));
        CHECK(m2.cbegin() == m2.nth(0));
        CHECK(m3.cbegin() == m3.nth(0));
        CHECK(m4.cbegin() == m4.nth(0));

        CHECK(m1.index_of(m1.nth(0)) == 0);
        CHECK(m2.index_of(m2.nth(0)) == 0);
        CHECK(m3.index_of(m3.nth(0)) == 0);
        CHECK(m4.index_of(m4.nth(0)) == 0);

        CHECK(m1.find(42) == m1.end());
        CHECK(m2.find(42) == m2.end());
        CHECK(m3.find(42) == m3.end());
        CHECK(m4.find(42) == m4.end());

        CHECK(m1.count(42) == 0);
        CHECK(m2.count(42) == 0);
        CHECK(m3.count(42) == 0);
        CHECK(m4.count(42) == 0);

        CHECK(m1.contains(42) == false);
        CHECK(m2.contains(42) == false);
        CHECK(m3.contains(42) == false);
        CHECK(m4.contains(42) == false);

        auto a1 = m1.get_allocator(); (void)a1;
        auto a2 = m2.get_allocator(); (void)a2;
        auto a3 = m3.get_allocator(); (void)a3;
        auto a4 = m4.get_allocator(); (void)a4;

        const xint i(10);
        const xint j(20);

        auto keq1 = m1.key_eq(); CHECK(keq1(i, i)); CHECK(!keq1(i, j));
        auto keq2 = m2.key_eq(); CHECK(keq2(i, i)); CHECK(!keq2(i, j));
        auto keq3 = m3.key_eq(); CHECK(keq3(i, i)); CHECK(!keq3(i, j));
        auto keq4 = m4.key_eq(); CHECK(keq4(i, i)); CHECK(!keq4(i, j));

        const std::pair<xint, xstr> p1(10, "/10/");
        const std::pair<xint, xstr> p2(20, "/20/");

        auto veq1 = m1.value_eq(); CHECK(veq1(p1, p1)); CHECK(!veq1(p1, p2));
        auto veq2 = m2.value_eq(); CHECK(veq2(p1, p1)); CHECK(!veq2(p1, p2));
        auto veq3 = m3.value_eq(); CHECK(veq3(p1, p1)); CHECK(!veq3(p1, p2));
        auto veq4 = m4.value_eq(); CHECK(veq4(p1, p1)); CHECK(!veq4(p1, p2));
    }

    cout << "Create empty containers and test all lookup functions "
            "that support transparent lookup." << endl;
    {
        sfl::small_unordered_flat_multimap<Person, xstr, 0, PersonEqual,
            TPARAM_ALLOCATOR<std::pair<Person, xstr>>
        > m1;

        const sfl::small_unordered_flat_multimap<Person, xstr, 0, PersonEqual,
            TPARAM_ALLOCATOR<std::pair<Person, xstr>>
        > m2;

        Person p(42, "John");

        CHECK(m1.find(p) == m1.end());
        CHECK(m2.find(p) == m1.end());

        CHECK(m1.find(42) == m1.end());
        CHECK(m2.find(42) == m1.end());

        CHECK(m1.count(p) == 0);
        CHECK(m2.count(p) == 0);

        CHECK(m1.count(42) == 0);
        CHECK(m2.count(42) == 0);

        CHECK(m1.contains(p) == false);
        CHECK(m2.contains(p) == false);

        CHECK(m1.contains(42) == false);
        CHECK(m2.contains(42) == false);
    }

    cout << "Test emplace(Args&&...) (N > 0, with reallocation)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 3, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10.1/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 3);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10.2/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 3);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20.1/"));
            cout << "<" << endl;

            CHECK(res == m.nth(2));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 3);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20.1/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20.2/"));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 6);
            CHECK(m.nth(0)->first == 20 && m.nth(0)->second == "/20.2/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.1/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.2/");
            CHECK(m.nth(3)->first == 20 && m.nth(3)->second == "/20.1/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15.1/"));
            cout << "<" << endl;

            CHECK(res == m.nth(4));
            CHECK(m.size() == 5);
            CHECK(m.capacity() == 6);
            CHECK(m.nth(0)->first == 20 && m.nth(0)->second == "/20.2/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.1/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.2/");
            CHECK(m.nth(3)->first == 20 && m.nth(3)->second == "/20.1/");
            CHECK(m.nth(4)->first == 15 && m.nth(4)->second == "/15.1/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15.2/"));
            cout << "<" << endl;

            CHECK(res == m.nth(5));
            CHECK(m.size() == 6);
            CHECK(m.capacity() == 6);
            CHECK(m.nth(0)->first == 20 && m.nth(0)->second == "/20.2/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.1/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.2/");
            CHECK(m.nth(3)->first == 20 && m.nth(3)->second == "/20.1/");
            CHECK(m.nth(4)->first == 15 && m.nth(4)->second == "/15.1/");
            CHECK(m.nth(5)->first == 15 && m.nth(5)->second == "/15.2/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30.1/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 7);
            CHECK(m.capacity() == 12);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30.1/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20.2/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.1/");
            CHECK(m.nth(3)->first == 10 && m.nth(3)->second == "/10.2/");
            CHECK(m.nth(4)->first == 20 && m.nth(4)->second == "/20.1/");
            CHECK(m.nth(5)->first == 15 && m.nth(5)->second == "/15.1/");
            CHECK(m.nth(6)->first == 15 && m.nth(6)->second == "/15.2/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30.2/");
            cout << "<" << endl;

            CHECK(res == m.nth(7));
            CHECK(m.size() == 8);
            CHECK(m.capacity() == 12);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30.1/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20.2/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.1/");
            CHECK(m.nth(3)->first == 10 && m.nth(3)->second == "/10.2/");
            CHECK(m.nth(4)->first == 20 && m.nth(4)->second == "/20.1/");
            CHECK(m.nth(5)->first == 15 && m.nth(5)->second == "/15.1/");
            CHECK(m.nth(6)->first == 15 && m.nth(6)->second == "/15.2/");
            CHECK(m.nth(7)->first == 30 && m.nth(7)->second == "/30.2/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16.1/");
            cout << "<" << endl;

            CHECK(res == m.nth(8));
            CHECK(m.size() == 9);
            CHECK(m.capacity() == 12);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30.1/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20.2/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.1/");
            CHECK(m.nth(3)->first == 10 && m.nth(3)->second == "/10.2/");
            CHECK(m.nth(4)->first == 20 && m.nth(4)->second == "/20.1/");
            CHECK(m.nth(5)->first == 15 && m.nth(5)->second == "/15.1/");
            CHECK(m.nth(6)->first == 15 && m.nth(6)->second == "/15.2/");
            CHECK(m.nth(7)->first == 30 && m.nth(7)->second == "/30.2/");
            CHECK(m.nth(8)->first == 16 && m.nth(8)->second == "/16.1/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16.2/");
            cout << "<" << endl;

            CHECK(res == m.nth(9));
            CHECK(m.size() == 10);
            CHECK(m.capacity() == 12);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30.1/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20.2/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.1/");
            CHECK(m.nth(3)->first == 10 && m.nth(3)->second == "/10.2/");
            CHECK(m.nth(4)->first == 20 && m.nth(4)->second == "/20.1/");
            CHECK(m.nth(5)->first == 15 && m.nth(5)->second == "/15.1/");
            CHECK(m.nth(6)->first == 15 && m.nth(6)->second == "/15.2/");
            CHECK(m.nth(7)->first == 30 && m.nth(7)->second == "/30.2/");
            CHECK(m.nth(8)->first == 16 && m.nth(8)->second == "/16.1/");
            CHECK(m.nth(9)->first == 16 && m.nth(9)->second == "/16.2/");
        }
    }

    cout << "Test emplace(Args&&...) (N == 0, with reallocation)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10.1/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 1);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10.2/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 2);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.2/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.1/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20.1/"));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 4);
            CHECK(m.nth(0)->first == 20 && m.nth(0)->second == "/20.1/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.1/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20.2/"));
            cout << "<" << endl;

            CHECK(res == m.nth(3));
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 4);
            CHECK(m.nth(0)->first == 20 && m.nth(0)->second == "/20.1/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.1/");
            CHECK(m.nth(3)->first == 20 && m.nth(3)->second == "/20.2/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15.1/"));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 5);
            CHECK(m.capacity() == 8);
            CHECK(m.nth(0)->first == 15 && m.nth(0)->second == "/15.1/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20.1/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.2/");
            CHECK(m.nth(3)->first == 10 && m.nth(3)->second == "/10.1/");
            CHECK(m.nth(4)->first == 20 && m.nth(4)->second == "/20.2/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15.2/"));
            cout << "<" << endl;

            CHECK(res == m.nth(5));
            CHECK(m.size() == 6);
            CHECK(m.capacity() == 8);
            CHECK(m.nth(0)->first == 15 && m.nth(0)->second == "/15.1/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20.1/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.2/");
            CHECK(m.nth(3)->first == 10 && m.nth(3)->second == "/10.1/");
            CHECK(m.nth(4)->first == 20 && m.nth(4)->second == "/20.2/");
            CHECK(m.nth(5)->first == 15 && m.nth(5)->second == "/15.2/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30.1/");
            cout << "<" << endl;

            CHECK(res == m.nth(6));
            CHECK(m.size() == 7);
            CHECK(m.capacity() == 8);
            CHECK(m.nth(0)->first == 15 && m.nth(0)->second == "/15.1/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20.1/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.2/");
            CHECK(m.nth(3)->first == 10 && m.nth(3)->second == "/10.1/");
            CHECK(m.nth(4)->first == 20 && m.nth(4)->second == "/20.2/");
            CHECK(m.nth(5)->first == 15 && m.nth(5)->second == "/15.2/");
            CHECK(m.nth(6)->first == 30 && m.nth(6)->second == "/30.1/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30.2/");
            cout << "<" << endl;

            CHECK(res == m.nth(7));
            CHECK(m.size() == 8);
            CHECK(m.capacity() == 8);
            CHECK(m.nth(0)->first == 15 && m.nth(0)->second == "/15.1/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20.1/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10.2/");
            CHECK(m.nth(3)->first == 10 && m.nth(3)->second == "/10.1/");
            CHECK(m.nth(4)->first == 20 && m.nth(4)->second == "/20.2/");
            CHECK(m.nth(5)->first == 15 && m.nth(5)->second == "/15.2/");
            CHECK(m.nth(6)->first == 30 && m.nth(6)->second == "/30.1/");
            CHECK(m.nth(7)->first == 30 && m.nth(7)->second == "/30.2/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16.1/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 9);
            CHECK(m.capacity() == 16);
            CHECK(m.nth(0)->first == 16 && m.nth(0)->second == "/16.1/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15.1/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20.1/");
            CHECK(m.nth(3)->first == 10 && m.nth(3)->second == "/10.2/");
            CHECK(m.nth(4)->first == 10 && m.nth(4)->second == "/10.1/");
            CHECK(m.nth(5)->first == 20 && m.nth(5)->second == "/20.2/");
            CHECK(m.nth(6)->first == 15 && m.nth(6)->second == "/15.2/");
            CHECK(m.nth(7)->first == 30 && m.nth(7)->second == "/30.1/");
            CHECK(m.nth(8)->first == 30 && m.nth(8)->second == "/30.2/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16.2/");
            cout << "<" << endl;

            CHECK(res == m.nth(9));
            CHECK(m.size() == 10);
            CHECK(m.capacity() == 16);
            CHECK(m.nth(0)->first == 16 && m.nth(0)->second == "/16.1/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15.1/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20.1/");
            CHECK(m.nth(3)->first == 10 && m.nth(3)->second == "/10.2/");
            CHECK(m.nth(4)->first == 10 && m.nth(4)->second == "/10.1/");
            CHECK(m.nth(5)->first == 20 && m.nth(5)->second == "/20.2/");
            CHECK(m.nth(6)->first == 15 && m.nth(6)->second == "/15.2/");
            CHECK(m.nth(7)->first == 30 && m.nth(7)->second == "/30.1/");
            CHECK(m.nth(8)->first == 30 && m.nth(8)->second == "/30.2/");
            CHECK(m.nth(9)->first == 16 && m.nth(9)->second == "/16.2/");
        }
    }

    cout << "Test non-modifying member functions on non-empty container (1)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        m.emplace(10, "/10/");
        m.emplace(20, "/20/");
        m.emplace(20, "/20/");
        m.emplace(30, "/30/");

        {
            auto it = m.begin();
            CHECK(it->first == 10 && it->second == "/10/"); ++it;
            CHECK(it->first == 20 && it->second == "/20/"); ++it;
            CHECK(it->first == 20 && it->second == "/20/"); ++it;
            CHECK(it->first == 30 && it->second == "/30/"); ++it;
            CHECK(it == m.end());
        }

        {
            auto it = m.cbegin();
            CHECK(it->first == 10 && it->second == "/10/"); ++it;
            CHECK(it->first == 20 && it->second == "/20/"); ++it;
            CHECK(it->first == 20 && it->second == "/20/"); ++it;
            CHECK(it->first == 30 && it->second == "/30/"); ++it;
            CHECK(it == m.cend());
        }

        {
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
            CHECK(m.nth(4) == m.end());
        }

        {
            CHECK(std::next(m.begin(), 0) == m.nth(0));
            CHECK(std::next(m.begin(), 1) == m.nth(1));
            CHECK(std::next(m.begin(), 2) == m.nth(2));
        }

        {
            CHECK(std::next(m.cbegin(), 0) == m.nth(0));
            CHECK(std::next(m.cbegin(), 1) == m.nth(1));
            CHECK(std::next(m.cbegin(), 2) == m.nth(2));
        }

        {
            CHECK(m.index_of(m.nth(0)) == 0);
            CHECK(m.index_of(m.nth(1)) == 1);
            CHECK(m.index_of(m.nth(2)) == 2);
        }

        {
            auto data = m.data();
            CHECK(data->first == 10 && data->second == "/10/"); ++data;
            CHECK(data->first == 20 && data->second == "/20/"); ++data;
            CHECK(data->first == 20 && data->second == "/20/"); ++data;
            CHECK(data->first == 30 && data->second == "/30/"); ++data;
        }

        {
            CHECK(m.find(10) == m.nth(0));
            CHECK(m.find(20) == m.nth(1));
            CHECK(m.find(30) == m.nth(3));
            CHECK(m.find(40) == m.end());
        }

        {
            CHECK(m.count(10) == 1);
            CHECK(m.count(20) == 2);
            CHECK(m.count(30) == 1);
            CHECK(m.count(40) == 0);
        }

        {
            CHECK(m.contains(10) == true);
            CHECK(m.contains(20) == true);
            CHECK(m.contains(30) == true);
            CHECK(m.contains(40) == false);
        }
    }

    cout << "Test non-modifying member functions on non-empty container (2)." << endl;
    {
        sfl::small_unordered_flat_multimap<Person, xstr, 10, PersonEqual,
            TPARAM_ALLOCATOR<std::pair<Person, xstr>>
        > m;

        m.emplace(Person(10, "Name 10"), "Person 10");
        m.emplace(Person(20, "Name 20"), "Person 20");
        m.emplace(Person(20, "Name 20"), "Person 20");
        m.emplace(Person(30, "Name 30"), "Person 30");

        {
            auto it = m.begin();
            CHECK(it->first.id() == 10 && it->first.name() == "Name 10" && it->second == "Person 10"); ++it;
            CHECK(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            CHECK(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            CHECK(it->first.id() == 30 && it->first.name() == "Name 30" && it->second == "Person 30"); ++it;
            CHECK(it == m.end());
        }

        {
            auto it = m.cbegin();
            CHECK(it->first.id() == 10 && it->first.name() == "Name 10" && it->second == "Person 10"); ++it;
            CHECK(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            CHECK(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            CHECK(it->first.id() == 30 && it->first.name() == "Name 30" && it->second == "Person 30"); ++it;
            CHECK(it == m.cend());
        }

        {
            CHECK(std::next(m.begin(), 0) == m.nth(0));
            CHECK(std::next(m.begin(), 1) == m.nth(1));
            CHECK(std::next(m.begin(), 2) == m.nth(2));
        }

        {
            CHECK(std::next(m.cbegin(), 0) == m.nth(0));
            CHECK(std::next(m.cbegin(), 1) == m.nth(1));
            CHECK(std::next(m.cbegin(), 2) == m.nth(2));
        }

        {
            CHECK(m.index_of(m.nth(0)) == 0);
            CHECK(m.index_of(m.nth(1)) == 1);
            CHECK(m.index_of(m.nth(2)) == 2);
        }

        {
            auto data = m.data();
            CHECK(data->first.id() == 10 && data->first.name() == "Name 10" && data->second == "Person 10"); ++data;
            CHECK(data->first.id() == 20 && data->first.name() == "Name 20" && data->second == "Person 20"); ++data;
            CHECK(data->first.id() == 20 && data->first.name() == "Name 20" && data->second == "Person 20"); ++data;
            CHECK(data->first.id() == 30 && data->first.name() == "Name 30" && data->second == "Person 30"); ++data;
        }

        {
            CHECK(m.find(Person(10, "xxx")) == m.nth(0));
            CHECK(m.find(Person(20, "xxx")) == m.nth(1));
            CHECK(m.find(Person(30, "xxx")) == m.nth(3));
            CHECK(m.find(Person(40, "xxx")) == m.end());
        }

        {
            CHECK(m.find(10) == m.nth(0));
            CHECK(m.find(20) == m.nth(1));
            CHECK(m.find(30) == m.nth(3));
            CHECK(m.find(40) == m.end());
        }

        {
            CHECK(m.count(Person(10, "xxx")) == 1);
            CHECK(m.count(Person(20, "xxx")) == 2);
            CHECK(m.count(Person(30, "xxx")) == 1);
            CHECK(m.count(Person(40, "xxx")) == 0);
        }

        {
            CHECK(m.count(10) == 1);
            CHECK(m.count(20) == 2);
            CHECK(m.count(30) == 1);
            CHECK(m.count(40) == 0);
        }

        {
            CHECK(m.contains(Person(10, "xxx")) == true);
            CHECK(m.contains(Person(20, "xxx")) == true);
            CHECK(m.contains(Person(30, "xxx")) == true);
            CHECK(m.contains(Person(40, "xxx")) == false);
        }

        {
            CHECK(m.contains(10) == true);
            CHECK(m.contains(20) == true);
            CHECK(m.contains(30) == true);
            CHECK(m.contains(40) == false);
        }
    }

    cout << "Test emplace_hint(const_iterator, Args&&...)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            // hint is ignored
            auto res = m.emplace_hint(m.nth(0), 10, "/10.1/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
        }

        {
            cout << ">" << endl;
            // hint is ignored
            auto res = m.emplace_hint(m.nth(0), 10, "/10.2/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
        }
    }

    cout << "Test insert(const value_type&)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            const std::pair<xint, xstr> v(10, "/10.1/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
        }

        {
            const std::pair<xint, xstr> v(10, "/10.2/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
        }
    }

    cout << "Test insert(value_type&&)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            std::pair<xint, xstr> v(10, "/10.1/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(v.first == -10 && v.second.value() == "");
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
        }

        {
            std::pair<xint, xstr> v(10, "/10.2/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(v.first == -10 && v.second.value() == "");
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
        }
    }

    cout << "Test insert(P&&)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(10, "/10.1/"));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(10, "/10.2/"));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
        }
    }

    cout << "Test insert(const_iterator, const value_type&)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            const std::pair<xint, xstr> v(10, "/10.1/");

            cout << ">" << endl;
            // hint is ignored
            auto res = m.insert(m.nth(0), v);
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
        }

        {
            const std::pair<xint, xstr> v(10, "/10.2/");

            cout << ">" << endl;
            // hint is ignored
            auto res = m.insert(m.nth(0), v);
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
        }
    }

    cout << "Test insert(const_iterator, value_type&&)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            std::pair<xint, xstr> v(10, "/10.1/");

            cout << ">" << endl;
            // hint is ignored
            auto res = m.insert(m.nth(0), std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(v.first == -10 && v.second == "");
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
        }

        {
            std::pair<xint, xstr> v(10, "/10.2/");

            cout << ">" << endl;
            // hint is ignored
            auto res = m.insert(m.nth(0), std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(v.first == -10 && v.second == "");
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
        }
    }

    cout << "Test insert(const_iterator, P&&...)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            // hint is ignored
            auto res = m.insert(m.nth(0), std::make_pair(10, "/10.1/"));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
        }

        {
            cout << ">" << endl;
            // hint is ignored
            auto res = m.insert(m.nth(0), std::make_pair(10, "/10.2/"));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
        }
    }

    cout << "Test insert(InputIt, InputIt)." << endl;
    {
        const std::vector<std::pair<xint, xstr>> v
        (
            {
                {10, "/10.1/"},
                {10, "/10.2/"},
                {20, "/20.1/"},
                {20, "/20.2/"},
                {15, "/15.1/"},
                {15, "/15.2/"},
                {30, "/30.1/"},
                {30, "/30.2/"}
            }
        );

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        cout << ">" << endl;
        m.insert(v.begin(), v.end());
        cout << "<" << endl;

        CHECK(m.size() == 8);
        CHECK(m.capacity() == 10);
        CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
        CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
        CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20.1/");
        CHECK(m.nth(3)->first == 20 && m.nth(3)->second == "/20.2/");
        CHECK(m.nth(4)->first == 15 && m.nth(4)->second == "/15.1/");
        CHECK(m.nth(5)->first == 15 && m.nth(5)->second == "/15.2/");
        CHECK(m.nth(6)->first == 30 && m.nth(6)->second == "/30.1/");
        CHECK(m.nth(7)->first == 30 && m.nth(7)->second == "/30.2/");
    }

    cout << "Test insert(std::initializer_list)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        cout << ">" << endl;
        m.insert
        (
            {
                {10, "/10.1/"},
                {10, "/10.2/"},
                {20, "/20.1/"},
                {20, "/20.2/"},
                {15, "/15.1/"},
                {15, "/15.2/"},
                {30, "/30.1/"},
                {30, "/30.2/"}
            }
        );
        cout << "<" << endl;

        CHECK(m.size() == 8);
        CHECK(m.capacity() == 10);
        CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10.1/");
        CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10.2/");
        CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20.1/");
        CHECK(m.nth(3)->first == 20 && m.nth(3)->second == "/20.2/");
        CHECK(m.nth(4)->first == 15 && m.nth(4)->second == "/15.1/");
        CHECK(m.nth(5)->first == 15 && m.nth(5)->second == "/15.2/");
        CHECK(m.nth(6)->first == 30 && m.nth(6)->second == "/30.1/");
        CHECK(m.nth(7)->first == 30 && m.nth(7)->second == "/30.2/");
    }

    cout << "Test clear()." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            m.emplace(40, "/40/");
            cout << "<" << endl;

            CHECK(m.size() == 4);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
            CHECK(m.nth(3)->first == 40 && m.nth(3)->second == "/40/");
        }

        {
            cout << ">" << endl;
            m.clear();
            cout << "<" << endl;

            CHECK(m.size() == 0);
        }

        {
            cout << ">" << endl;
            m.emplace(50, "/50/");
            m.emplace(60, "/60/");
            cout << "<" << endl;

            CHECK(m.size() == 2);
            CHECK(m.nth(0)->first == 50 && m.nth(0)->second == "/50/");
            CHECK(m.nth(1)->first == 60 && m.nth(1)->second == "/60/");
        }

        {
            cout << ">" << endl;
            m.clear();
            cout << "<" << endl;

            CHECK(m.size() == 0);
        }
    }

    cout << "Test erase(const_iterator)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            m.emplace(40, "/40/");
            cout << "<" << endl;

            CHECK(m.size() == 4);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
            CHECK(m.nth(3)->first == 40 && m.nth(3)->second == "/40/");
        }

        {
            cout << ">" << endl;
            auto res = m.erase(m.nth(1));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 3);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 40 && m.nth(1)->second == "/40/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.erase(m.nth(0));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 2);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
            CHECK(m.nth(1)->first == 40 && m.nth(1)->second == "/40/");
        }

        {
            cout << ">" << endl;
            auto res = m.erase(m.nth(1));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 1);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.erase(m.nth(0));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 0);
        }
    }

    cout << "Test erase(const_iterator, const_iterator)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            m.emplace(40, "/40/");
            m.emplace(50, "/50/");
            m.emplace(60, "/60/");
            m.emplace(70, "/70/");
            m.emplace(80, "/80/");
            m.emplace(90, "/90/");
            cout << "<" << endl;

            CHECK(m.size() == 9);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
            CHECK(m.nth(3)->first == 40 && m.nth(3)->second == "/40/");
            CHECK(m.nth(4)->first == 50 && m.nth(4)->second == "/50/");
            CHECK(m.nth(5)->first == 60 && m.nth(5)->second == "/60/");
            CHECK(m.nth(6)->first == 70 && m.nth(6)->second == "/70/");
            CHECK(m.nth(7)->first == 80 && m.nth(7)->second == "/80/");
            CHECK(m.nth(8)->first == 90 && m.nth(8)->second == "/90/");
        }

        {
            cout << ">" << endl;
            // Erase nothing
            auto res = m.erase(m.nth(3), m.nth(3));
            cout << "<" << endl;

            CHECK(res == m.nth(3));
            CHECK(m.size() == 9);
        }

        {
            cout << ">" << endl;
            // Erase two elements near begin
            auto res = m.erase(m.nth(1), m.nth(3));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 7);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 80 && m.nth(1)->second == "/80/");
            CHECK(m.nth(2)->first == 90 && m.nth(2)->second == "/90/");
            CHECK(m.nth(3)->first == 40 && m.nth(3)->second == "/40/");
            CHECK(m.nth(4)->first == 50 && m.nth(4)->second == "/50/");
            CHECK(m.nth(5)->first == 60 && m.nth(5)->second == "/60/");
            CHECK(m.nth(6)->first == 70 && m.nth(6)->second == "/70/");
        }

        {
            cout << ">" << endl;
            // Erase two elements near end
            auto res = m.erase(m.nth(4), m.nth(6));
            cout << "<" << endl;

            CHECK(res == m.nth(4));
            CHECK(m.size() == 5);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 80 && m.nth(1)->second == "/80/");
            CHECK(m.nth(2)->first == 90 && m.nth(2)->second == "/90/");
            CHECK(m.nth(3)->first == 40 && m.nth(3)->second == "/40/");
            CHECK(m.nth(4)->first == 70 && m.nth(4)->second == "/70/");
        }

        {
            cout << ">" << endl;
            // Remove two elements at begin
            auto res = m.erase(m.nth(0), m.nth(2));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 3);
            CHECK(m.nth(0)->first == 40 && m.nth(0)->second == "/40/");
            CHECK(m.nth(1)->first == 70 && m.nth(1)->second == "/70/");
            CHECK(m.nth(2)->first == 90 && m.nth(2)->second == "/90/");
        }

        {
            cout << ">" << endl;
            // Remove two elements at end
            auto res = m.erase(m.nth(1), m.nth(3));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 1);
            CHECK(m.nth(0)->first == 40 && m.nth(0)->second == "/40/");
        }

        {
            cout << ">" << endl;
            // Remove from begin to end
            auto res = m.erase(m.nth(0), m.nth(1));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 0);
        }
    }

    cout << "Test erase(const Key&)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(20, "/20/");
            m.emplace(20, "/20/");
            m.emplace(10, "/10/");
            m.emplace(30, "/30/");
            m.emplace(40, "/40/");
            m.emplace(10, "/10/");
            cout << "<" << endl;

            CHECK(m.size() == 8);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 20 && m.nth(3)->second == "/20/");
            CHECK(m.nth(4)->first == 10 && m.nth(4)->second == "/10/");
            CHECK(m.nth(5)->first == 30 && m.nth(5)->second == "/30/");
            CHECK(m.nth(6)->first == 40 && m.nth(6)->second == "/40/");
            CHECK(m.nth(7)->first == 10 && m.nth(7)->second == "/10/");
        }

        {
            const xint i(20);

            cout << ">" << endl;
            auto res = m.erase(i);
            cout << "<" << endl;

            CHECK(res == 3);
            CHECK(m.size() == 5);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10/");
            CHECK(m.nth(2)->first == 40 && m.nth(2)->second == "/40/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
            CHECK(m.nth(4)->first == 10 && m.nth(4)->second == "/10/");
        }

        {
            const xint i(15);

            cout << ">" << endl;
            auto res = m.erase(i);
            cout << "<" << endl;

            CHECK(res == 0);
            CHECK(m.size() == 5);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 10 && m.nth(1)->second == "/10/");
            CHECK(m.nth(2)->first == 40 && m.nth(2)->second == "/40/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
            CHECK(m.nth(4)->first == 10 && m.nth(4)->second == "/10/");
        }

        {
            const xint i(10);

            cout << ">" << endl;
            auto res = m.erase(i);
            cout << "<" << endl;

            CHECK(res == 3);
            CHECK(m.size() == 2);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
            CHECK(m.nth(1)->first == 40 && m.nth(1)->second == "/40/");
        }
    }

    cout << "Test erase(K&&) (transparent erase)." << endl;
    {
        sfl::small_unordered_flat_multimap<Person, xstr, 10, PersonEqual,
            TPARAM_ALLOCATOR<std::pair<Person, xstr>>
        > s;

        {
            cout << ">" << endl;
            s.emplace(Person(10, "/10/"), "Person /10/");
            s.emplace(Person(20, "/20/"), "Person /20/");
            s.emplace(Person(20, "*20*"), "Person *20*");
            cout << "<" << endl;

            CHECK(s.size() == 3);
        }

        {
            cout << ">" << endl;
            auto res = s.erase(10);
            cout << "<" << endl;

            CHECK(res == 1);
            CHECK(s.size() == 2);
        }

        {
            cout << ">" << endl;
            auto res = s.erase(15);
            cout << "<" << endl;

            CHECK(res == 0);
            CHECK(s.size() == 2);
        }

        {
            const Person p(20, "persons are compared by ID only");

            cout << ">" << endl;
            auto res = s.erase(p);
            cout << "<" << endl;

            CHECK(res == 2);
            CHECK(s.size() == 0);
        }
    }

    cout << "Test swap(small_unordered_flat_multimap&)." << endl;
    {
        // m1 uses internal storage, m2 uses internal storage
        {
            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m1;

            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m2;

            m1.emplace(10, "/10/");
            m1.emplace(11, "/11/");
            m1.emplace(12, "/12/");

            m2.emplace(20, "/20/");
            m2.emplace(21, "/21/");
            m2.emplace(22, "/22/");
            m2.emplace(23, "/23/");

            CHECK(m1.size() == 3);
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            CHECK(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            CHECK(m2.size() == 4);
            CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            CHECK(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            CHECK(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            CHECK(m1.size() == 4);
            CHECK(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            CHECK(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            CHECK(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
            CHECK(m1.nth(3)->first == 23 && m1.nth(3)->second == "/23/");

            CHECK(m2.size() == 3);
            CHECK(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
            CHECK(m2.nth(1)->first == 11 && m2.nth(1)->second == "/11/");
            CHECK(m2.nth(2)->first == 12 && m2.nth(2)->second == "/12/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            CHECK(m1.size() == 3);
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            CHECK(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            CHECK(m2.size() == 4);
            CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            CHECK(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            CHECK(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
        }

        // m1 uses internal storage, m2 uses external storage
        {
            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m1;

            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m2;

            m1.emplace(10, "/10/");
            m1.emplace(11, "/11/");
            m1.emplace(12, "/12/");

            m2.emplace(20, "/20/");
            m2.emplace(21, "/21/");
            m2.emplace(22, "/22/");
            m2.emplace(23, "/23/");
            m2.emplace(24, "/24/");
            m2.emplace(25, "/25/");

            CHECK(m1.size() == 3);
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            CHECK(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            CHECK(m2.size() == 6);
            CHECK(m2.nth(0)->first == 25 && m2.nth(0)->second == "/25/");
            CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
            CHECK(m2.nth(2)->first == 21 && m2.nth(2)->second == "/21/");
            CHECK(m2.nth(3)->first == 22 && m2.nth(3)->second == "/22/");
            CHECK(m2.nth(4)->first == 23 && m2.nth(4)->second == "/23/");
            CHECK(m2.nth(5)->first == 24 && m2.nth(5)->second == "/24/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            CHECK(m1.size() == 6);
            CHECK(m1.nth(0)->first == 25 && m1.nth(0)->second == "/25/");
            CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
            CHECK(m1.nth(2)->first == 21 && m1.nth(2)->second == "/21/");
            CHECK(m1.nth(3)->first == 22 && m1.nth(3)->second == "/22/");
            CHECK(m1.nth(4)->first == 23 && m1.nth(4)->second == "/23/");
            CHECK(m1.nth(5)->first == 24 && m1.nth(5)->second == "/24/");

            CHECK(m2.size() == 3);
            CHECK(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
            CHECK(m2.nth(1)->first == 11 && m2.nth(1)->second == "/11/");
            CHECK(m2.nth(2)->first == 12 && m2.nth(2)->second == "/12/");
        }

        // m1 uses external storage, m2 uses internal storage
        {
            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m1;

            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m2;

            m1.emplace(10, "/10/");
            m1.emplace(11, "/11/");
            m1.emplace(12, "/12/");
            m1.emplace(13, "/13/");
            m1.emplace(14, "/14/");
            m1.emplace(15, "/15/");

            m2.emplace(20, "/20/");
            m2.emplace(21, "/21/");
            m2.emplace(22, "/22/");

            CHECK(m1.size() == 6);
            CHECK(m1.nth(0)->first == 15 && m1.nth(0)->second == "/15/");
            CHECK(m1.nth(1)->first == 10 && m1.nth(1)->second == "/10/");
            CHECK(m1.nth(2)->first == 11 && m1.nth(2)->second == "/11/");
            CHECK(m1.nth(3)->first == 12 && m1.nth(3)->second == "/12/");
            CHECK(m1.nth(4)->first == 13 && m1.nth(4)->second == "/13/");
            CHECK(m1.nth(5)->first == 14 && m1.nth(5)->second == "/14/");

            CHECK(m2.size() == 3);
            CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            CHECK(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            CHECK(m1.size() == 3);
            CHECK(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            CHECK(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            CHECK(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");

            CHECK(m2.size() == 6);
            CHECK(m2.nth(0)->first == 15 && m2.nth(0)->second == "/15/");
            CHECK(m2.nth(1)->first == 10 && m2.nth(1)->second == "/10/");
            CHECK(m2.nth(2)->first == 11 && m2.nth(2)->second == "/11/");
            CHECK(m2.nth(3)->first == 12 && m2.nth(3)->second == "/12/");
            CHECK(m2.nth(4)->first == 13 && m2.nth(4)->second == "/13/");
            CHECK(m2.nth(5)->first == 14 && m2.nth(5)->second == "/14/");
        }

        // m1 uses external storage, m2 uses external storage
        {
            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m1;

            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m2;

            m1.emplace(10, "/10/");
            m1.emplace(11, "/11/");
            m1.emplace(12, "/12/");
            m1.emplace(13, "/13/");
            m1.emplace(14, "/14/");
            m1.emplace(15, "/15/");

            m2.emplace(20, "/20/");
            m2.emplace(21, "/21/");
            m2.emplace(22, "/22/");
            m2.emplace(23, "/23/");
            m2.emplace(24, "/24/");
            m2.emplace(25, "/25/");

            CHECK(m1.size() == 6);
            CHECK(m1.nth(0)->first == 15 && m1.nth(0)->second == "/15/");
            CHECK(m1.nth(1)->first == 10 && m1.nth(1)->second == "/10/");
            CHECK(m1.nth(2)->first == 11 && m1.nth(2)->second == "/11/");
            CHECK(m1.nth(3)->first == 12 && m1.nth(3)->second == "/12/");
            CHECK(m1.nth(4)->first == 13 && m1.nth(4)->second == "/13/");
            CHECK(m1.nth(5)->first == 14 && m1.nth(5)->second == "/14/");

            CHECK(m2.size() == 6);
            CHECK(m2.nth(0)->first == 25 && m2.nth(0)->second == "/25/");
            CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
            CHECK(m2.nth(2)->first == 21 && m2.nth(2)->second == "/21/");
            CHECK(m2.nth(3)->first == 22 && m2.nth(3)->second == "/22/");
            CHECK(m2.nth(4)->first == 23 && m2.nth(4)->second == "/23/");
            CHECK(m2.nth(5)->first == 24 && m2.nth(5)->second == "/24/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            CHECK(m1.size() == 6);
            CHECK(m1.nth(0)->first == 25 && m1.nth(0)->second == "/25/");
            CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
            CHECK(m1.nth(2)->first == 21 && m1.nth(2)->second == "/21/");
            CHECK(m1.nth(3)->first == 22 && m1.nth(3)->second == "/22/");
            CHECK(m1.nth(4)->first == 23 && m1.nth(4)->second == "/23/");
            CHECK(m1.nth(5)->first == 24 && m1.nth(5)->second == "/24/");

            CHECK(m2.size() == 6);
            CHECK(m2.nth(0)->first == 15 && m2.nth(0)->second == "/15/");
            CHECK(m2.nth(1)->first == 10 && m2.nth(1)->second == "/10/");
            CHECK(m2.nth(2)->first == 11 && m2.nth(2)->second == "/11/");
            CHECK(m2.nth(3)->first == 12 && m2.nth(3)->second == "/12/");
            CHECK(m2.nth(4)->first == 13 && m2.nth(4)->second == "/13/");
            CHECK(m2.nth(5)->first == 14 && m2.nth(5)->second == "/14/");
        }
    }

    cout << "Test reserve and shrink_to_fit (N > 0)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 5);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.reserve(4);
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 5);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.reserve(10);
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.reserve(6);
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.shrink_to_fit();
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 5);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }
    }

    cout << "Test reserve and shrink_to_fit (N == 0)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 4);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10/");
        }

        {
            cout << ">" << endl;
            m.reserve(4);
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 4);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10/");
        }

        {
            cout << ">" << endl;
            m.reserve(10);
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10/");
        }

        {
            cout << ">" << endl;
            m.reserve(6);
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10/");
        }

        {
            cout << ">" << endl;
            m.shrink_to_fit();
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 3);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10/");
        }

        {
            cout << ">" << endl;
            m.clear();
            cout << "<" << endl;

            cout << ">" << endl;
            m.shrink_to_fit();
            cout << "<" << endl;

            CHECK(m.size() == 0);
            CHECK(m.capacity() == 0);
        }

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 4);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 10 && m.nth(2)->second == "/10/");
        }
    }

    cout << "Test empty constructors." << endl;
    {
        std::equal_to<xint> eq;
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1;

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(eq);

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3(alloc);

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m4(eq, alloc);

        CHECK(m1.size() == 0);
        CHECK(m1.capacity() == 10);

        CHECK(m2.size() == 0);
        CHECK(m2.capacity() == 10);

        CHECK(m3.size() == 0);
        CHECK(m3.capacity() == 10);

        CHECK(m4.size() == 0);
        CHECK(m4.capacity() == 10);
    }

    cout << "Test range constructors." << endl;
    {
        std::equal_to<xint> eq;
        TPARAM_ALLOCATOR<xint> alloc;

        const std::vector<std::pair<xint, xstr>> v
        (
            {
                {30, "/30/"},
                {20, "/20/"},
                {10, "/10/"},
                {10, "/10/"},
                {20, "/20/"}
            }
        );

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1(v.begin(), v.end());

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(v.begin(), v.end(), eq);

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3(v.begin(), v.end(), alloc);

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m4(v.begin(), v.end(), eq, alloc);

        CHECK(m1.size() == 5);
        CHECK(m1.capacity() == 10);
        CHECK(m1.nth(0)->first == 30 && m1.nth(0)->second == "/30/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        CHECK(m1.nth(2)->first == 10 && m1.nth(2)->second == "/10/");
        CHECK(m1.nth(3)->first == 10 && m1.nth(3)->second == "/10/");
        CHECK(m1.nth(4)->first == 20 && m1.nth(4)->second == "/20/");

        CHECK(m2.size() == 5);
        CHECK(m2.capacity() == 10);
        CHECK(m2.nth(0)->first == 30 && m2.nth(0)->second == "/30/");
        CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        CHECK(m2.nth(2)->first == 10 && m2.nth(2)->second == "/10/");
        CHECK(m2.nth(3)->first == 10 && m2.nth(3)->second == "/10/");
        CHECK(m2.nth(4)->first == 20 && m2.nth(4)->second == "/20/");

        CHECK(m3.size() == 5);
        CHECK(m3.capacity() == 10);
        CHECK(m3.nth(0)->first == 30 && m3.nth(0)->second == "/30/");
        CHECK(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        CHECK(m3.nth(2)->first == 10 && m3.nth(2)->second == "/10/");
        CHECK(m3.nth(3)->first == 10 && m3.nth(3)->second == "/10/");
        CHECK(m3.nth(4)->first == 20 && m3.nth(4)->second == "/20/");

        CHECK(m4.size() == 5);
        CHECK(m4.capacity() == 10);
        CHECK(m4.nth(0)->first == 30 && m4.nth(0)->second == "/30/");
        CHECK(m4.nth(1)->first == 20 && m4.nth(1)->second == "/20/");
        CHECK(m4.nth(2)->first == 10 && m4.nth(2)->second == "/10/");
        CHECK(m4.nth(3)->first == 10 && m4.nth(3)->second == "/10/");
        CHECK(m4.nth(4)->first == 20 && m4.nth(4)->second == "/20/");
    }

    cout << "Test initializer_list constructors." << endl;
    {
        std::equal_to<xint> eq;
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {30, "/30/"},
                {20, "/20/"},
                {10, "/10/"},
                {10, "/10/"},
                {20, "/20/"}
            }
        );

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2
        (
            {
                {30, "/30/"},
                {20, "/20/"},
                {10, "/10/"},
                {10, "/10/"},
                {20, "/20/"}
            }, eq
        );

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3
        (
            {
                {30, "/30/"},
                {20, "/20/"},
                {10, "/10/"},
                {10, "/10/"},
                {20, "/20/"}
            }, alloc
        );

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m4
        (
            {
                {30, "/30/"},
                {20, "/20/"},
                {10, "/10/"},
                {10, "/10/"},
                {20, "/20/"}
            }, eq, alloc
        );

        CHECK(m1.size() == 5);
        CHECK(m1.capacity() == 10);
        CHECK(m1.nth(0)->first == 30 && m1.nth(0)->second == "/30/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        CHECK(m1.nth(2)->first == 10 && m1.nth(2)->second == "/10/");
        CHECK(m1.nth(3)->first == 10 && m1.nth(3)->second == "/10/");
        CHECK(m1.nth(4)->first == 20 && m1.nth(4)->second == "/20/");

        CHECK(m2.size() == 5);
        CHECK(m2.capacity() == 10);
        CHECK(m2.nth(0)->first == 30 && m2.nth(0)->second == "/30/");
        CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        CHECK(m2.nth(2)->first == 10 && m2.nth(2)->second == "/10/");
        CHECK(m2.nth(3)->first == 10 && m2.nth(3)->second == "/10/");
        CHECK(m2.nth(4)->first == 20 && m2.nth(4)->second == "/20/");

        CHECK(m3.size() == 5);
        CHECK(m3.capacity() == 10);
        CHECK(m3.nth(0)->first == 30 && m3.nth(0)->second == "/30/");
        CHECK(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        CHECK(m3.nth(2)->first == 10 && m3.nth(2)->second == "/10/");
        CHECK(m3.nth(3)->first == 10 && m3.nth(3)->second == "/10/");
        CHECK(m3.nth(4)->first == 20 && m3.nth(4)->second == "/20/");

        CHECK(m4.size() == 5);
        CHECK(m4.capacity() == 10);
        CHECK(m4.nth(0)->first == 30 && m4.nth(0)->second == "/30/");
        CHECK(m4.nth(1)->first == 20 && m4.nth(1)->second == "/20/");
        CHECK(m4.nth(2)->first == 10 && m4.nth(2)->second == "/10/");
        CHECK(m4.nth(3)->first == 10 && m4.nth(3)->second == "/10/");
        CHECK(m4.nth(4)->first == 20 && m4.nth(4)->second == "/20/");
    }

    cout << "Test copy constructors (N > 0)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {20, "/20/"},
                {30, "/30/"}
            }
        );

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(m1);

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3(m1, TPARAM_ALLOCATOR<xint>());

        CHECK(m1.size() == 3);
        CHECK(m1.capacity() == 10);
        CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        CHECK(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        CHECK(m2.size() == 3);
        CHECK(m2.capacity() == 10);
        CHECK(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
        CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        CHECK(m2.nth(2)->first == 30 && m2.nth(2)->second == "/30/");

        CHECK(m3.size() == 3);
        CHECK(m3.capacity() == 10);
        CHECK(m3.nth(0)->first == 10 && m3.nth(0)->second == "/10/");
        CHECK(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        CHECK(m3.nth(2)->first == 30 && m3.nth(2)->second == "/30/");
    }

    cout << "Test copy constructors (N == 0)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {20, "/20/"},
                {30, "/30/"}
            }
        );

        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(m1);

        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3(m1, TPARAM_ALLOCATOR<xint>());

        CHECK(m1.size() == 3);
        CHECK(m1.capacity() == 4);
        CHECK(m1.nth(0)->first == 30 && m1.nth(0)->second == "/30/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        CHECK(m1.nth(2)->first == 10 && m1.nth(2)->second == "/10/");

        CHECK(m2.size() == 3);
        CHECK(m2.capacity() == 3);
        CHECK(m2.nth(0)->first == 30 && m2.nth(0)->second == "/30/");
        CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        CHECK(m2.nth(2)->first == 10 && m2.nth(2)->second == "/10/");

        CHECK(m3.size() == 3);
        CHECK(m3.capacity() == 3);
        CHECK(m3.nth(0)->first == 30 && m3.nth(0)->second == "/30/");
        CHECK(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        CHECK(m3.nth(2)->first == 10 && m3.nth(2)->second == "/10/");
    }

    cout << "Test move constructors (N > 0)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {20, "/20/"},
                {30, "/30/"}
            }
        );

        CHECK(m1.size() == 3);
        CHECK(m1.capacity() == 10);
        CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        CHECK(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(std::move(m1));

        // m1 is in a valid but unspecified state

        CHECK(m2.size() == 3);
        CHECK(m2.capacity() == 10);
        CHECK(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
        CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        CHECK(m2.nth(2)->first == 30 && m2.nth(2)->second == "/30/");

        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3(std::move(m2), TPARAM_ALLOCATOR<xint>());

        // m2 is in a valid but unspecified state

        CHECK(m3.size() == 3);
        CHECK(m3.capacity() == 10);
        CHECK(m3.nth(0)->first == 10 && m3.nth(0)->second == "/10/");
        CHECK(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        CHECK(m3.nth(2)->first == 30 && m3.nth(2)->second == "/30/");
    }

    cout << "Test move constructors (N == 0)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {20, "/20/"},
                {30, "/30/"}
            }
        );

        CHECK(m1.size() == 3);
        CHECK(m1.capacity() == 4);
        CHECK(m1.nth(0)->first == 30 && m1.nth(0)->second == "/30/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        CHECK(m1.nth(2)->first == 10 && m1.nth(2)->second == "/10/");

        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(std::move(m1));

        // m1 is in a valid but unspecified state

        CHECK(m2.size() == 3);
        CHECK(m2.capacity() == 3 || m2.capacity() == 4); // Capacity depends on allocators.
        CHECK(m2.nth(0)->first == 30 && m2.nth(0)->second == "/30/");
        CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        CHECK(m2.nth(2)->first == 10 && m2.nth(2)->second == "/10/");

        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3(std::move(m2), TPARAM_ALLOCATOR<xint>());

        // m2 is in a valid but unspecified state

        CHECK(m3.size() == 3);
        CHECK(m3.capacity() == 3 || m3.capacity() == 4); // Capacity depends on allocators.
        CHECK(m3.nth(0)->first == 30 && m3.nth(0)->second == "/30/");
        CHECK(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        CHECK(m3.nth(2)->first == 10 && m3.nth(2)->second == "/10/");
    }

    cout << "Test copy assignment operator." << endl;
    {
        // n <= capacity && n <= size
        {
            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m1
            (
                {
                    {10, "/10/"},
                    {11, "/11/"},
                    {12, "/12/"}
                }
            );

            CHECK(m1.size() == 3);
            CHECK(m1.capacity() == 5);
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            CHECK(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m2
            (
                {
                    {20, "/20/"},
                    {21, "/21/"}
                }
            );

            CHECK(m2.size() == 2);
            CHECK(m2.capacity() == 5);
            CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");

            cout << ">" << endl;
            m1 = m2;
            cout << "<" << endl;

            CHECK(m1.size() == 2);
            CHECK(m1.capacity() == 5);
            CHECK(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            CHECK(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");

            CHECK(m2.size() == 2);
            CHECK(m2.capacity() == 5);
            CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
        }

        // n <= capacity && n > size
        {
            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m1
            (
                {
                    {10, "/10/"},
                    {11, "/11/"},
                    {12, "/12/"}
                }
            );

            CHECK(m1.size() == 3);
            CHECK(m1.capacity() == 5);
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            CHECK(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m2
            (
                {
                    {20, "/20/"},
                    {21, "/21/"},
                    {22, "/22/"},
                    {23, "/23/"},
                    {24, "/24/"}
                }
            );

            CHECK(m2.size() == 5);
            CHECK(m2.capacity() == 5);
            CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            CHECK(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            CHECK(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            CHECK(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");

            cout << ">" << endl;
            m1 = m2;
            cout << "<" << endl;

            CHECK(m1.size() == 5);
            CHECK(m1.capacity() == 5);
            CHECK(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            CHECK(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            CHECK(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
            CHECK(m1.nth(3)->first == 23 && m1.nth(3)->second == "/23/");
            CHECK(m1.nth(4)->first == 24 && m1.nth(4)->second == "/24/");

            CHECK(m2.size() == 5);
            CHECK(m2.capacity() == 5);
            CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            CHECK(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            CHECK(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            CHECK(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");
        }

        // n > capacity
        {
            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m1
            (
                {
                    {10, "/10/"},
                    {11, "/11/"},
                    {12, "/12/"}
                }
            );

            CHECK(m1.size() == 3);
            CHECK(m1.capacity() == 5);
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            CHECK(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m2
            (
                {
                    {20, "/20/"},
                    {21, "/21/"},
                    {22, "/22/"},
                    {23, "/23/"},
                    {24, "/24/"},
                    {25, "/25/"}
                }
            );

            CHECK(m2.size() == 6);
            CHECK(m2.capacity() == 10);
            CHECK(m2.nth(0)->first == 25 && m2.nth(0)->second == "/25/");
            CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
            CHECK(m2.nth(2)->first == 21 && m2.nth(2)->second == "/21/");
            CHECK(m2.nth(3)->first == 22 && m2.nth(3)->second == "/22/");
            CHECK(m2.nth(4)->first == 23 && m2.nth(4)->second == "/23/");
            CHECK(m2.nth(5)->first == 24 && m2.nth(5)->second == "/24/");

            cout << ">" << endl;
            m1 = m2;
            cout << "<" << endl;

            CHECK(m1.size() == 6);
            CHECK(m1.capacity() == 6);
            CHECK(m1.nth(0)->first == 25 && m1.nth(0)->second == "/25/");
            CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
            CHECK(m1.nth(2)->first == 21 && m1.nth(2)->second == "/21/");
            CHECK(m1.nth(3)->first == 22 && m1.nth(3)->second == "/22/");
            CHECK(m1.nth(4)->first == 23 && m1.nth(4)->second == "/23/");
            CHECK(m1.nth(5)->first == 24 && m1.nth(5)->second == "/24/");

            CHECK(m2.size() == 6);
            CHECK(m2.capacity() == 10);
            CHECK(m2.nth(0)->first == 25 && m2.nth(0)->second == "/25/");
            CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
            CHECK(m2.nth(2)->first == 21 && m2.nth(2)->second == "/21/");
            CHECK(m2.nth(3)->first == 22 && m2.nth(3)->second == "/22/");
            CHECK(m2.nth(4)->first == 23 && m2.nth(4)->second == "/23/");
            CHECK(m2.nth(5)->first == 24 && m2.nth(5)->second == "/24/");
        }
    }

    cout << "Test move assignment operator (N > 0)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {11, "/11/"},
                {12, "/12/"}
            }
        );

        CHECK(m1.size() == 3);
        CHECK(m1.capacity() == 5);
        CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
        CHECK(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

        sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2
        (
            {
                {20, "/20/"},
                {21, "/21/"}
            }
        );

        CHECK(m2.size() == 2);
        CHECK(m2.capacity() == 5);
        CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
        CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");

        cout << ">" << endl;
        m1 = std::move(m2);
        cout << "<" << endl;

        CHECK(m1.size() == 2);
        CHECK(m1.capacity() == 5);
        CHECK(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
        CHECK(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");

        // m2 is in a valid but unspecified state

        cout << ">" << endl;
        m2 = std::move(m1);
        cout << "<" << endl;

        // m1 is in a valid but unspecified state

        CHECK(m2.size() == 2);
        CHECK(m2.capacity() == 5);
        CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
        CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
    }

    cout << "Test move assignment operator (N == 0)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {11, "/11/"},
                {12, "/12/"}
            }
        );

        CHECK(m1.size() == 3);
        CHECK(m1.capacity() == 4);
        CHECK(m1.nth(0)->first == 12 && m1.nth(0)->second == "/12/");
        CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
        CHECK(m1.nth(2)->first == 10 && m1.nth(2)->second == "/10/");

        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2
        (
            {
                {20, "/20/"},
                {21, "/21/"}
            }
        );

        CHECK(m2.size() == 2);
        CHECK(m2.capacity() == 2);
        CHECK(m2.nth(0)->first == 21 && m2.nth(0)->second == "/21/");
        CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");

        cout << ">" << endl;
        m1 = std::move(m2);
        cout << "<" << endl;

        CHECK(m1.size() == 2);
        CHECK(m1.capacity() == 2);
        CHECK(m1.nth(0)->first == 21 && m1.nth(0)->second == "/21/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");

        // m2 is in a valid but unspecified state

        sfl::small_unordered_flat_multimap<xint, xstr, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3
        (
            {
                {30, "/30/"},
                {31, "/31/"}
            }
        );

        CHECK(m3.size() == 2);
        CHECK(m3.capacity() == 2);
        CHECK(m3.nth(0)->first == 31 && m3.nth(0)->second == "/31/");
        CHECK(m3.nth(1)->first == 30 && m3.nth(1)->second == "/30/");

        cout << ">" << endl;
        m3 = std::move(m1);
        cout << "<" << endl;

        // m1 is in a valid but unspecified state

        CHECK(m3.size() == 2);
        CHECK(m3.capacity() == 2);
        CHECK(m3.nth(0)->first == 21 && m3.nth(0)->second == "/21/");
        CHECK(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
    }

    cout << "Test initializer_list assignment operator." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {11, "/11/"},
                {12, "/12/"}
            }
        );

        CHECK(m1.size() == 3);
        CHECK(m1.capacity() == 5);
        CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
        CHECK(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

        cout << ">" << endl;
        m1 = {
            {22, "/22/"},
            {21, "/21/"},
            {20, "/20/"},
            {20, "/20/"},
            {21, "/21/"},
        };
        cout << "<" << endl;

        CHECK(m1.size() == 5);
        CHECK(m1.capacity() == 5);
        CHECK(m1.nth(0)->first == 22 && m1.nth(0)->second == "/22/");
        CHECK(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
        CHECK(m1.nth(2)->first == 20 && m1.nth(2)->second == "/20/");
        CHECK(m1.nth(3)->first == 20 && m1.nth(3)->second == "/20/");
        CHECK(m1.nth(4)->first == 21 && m1.nth(4)->second == "/21/");
    }

    cout << "Test non-member comparison operators." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {20, "/20/"},
                {30, "/30/"}
            }
        );

        sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2
        (
            {
                {10, "/10/"},
                {20, "/20/"},
                {30, "/30/"},
                {40, "/40/"}
            }
        );

        CHECK(m1 == m1);
        CHECK(m1 != m2);
    }

    cout << "Test non-member swap." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {11, "/11/"},
                {12, "/12/"}
            }
        );

        sfl::small_unordered_flat_multimap<xint, xstr, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2
        (
            {
                {20, "/20/"},
                {21, "/21/"}
            }
        );

        using std::swap;
        swap(m1, m2);
    }

    cout << "Test non-member erase_if(small_unordered_flat_multimap&, Predicate)." << endl;
    {
        sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {20, "/20/"},
                {20, "/20/"},
                {30, "/30/"}
            }
        );

        using const_reference =
            typename sfl::small_unordered_flat_multimap<xint, xstr, 10, std::equal_to<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            >::const_reference;

        CHECK(m1.size() == 4);
        CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        CHECK(m1.nth(2)->first == 20 && m1.nth(2)->second == "/20/");
        CHECK(m1.nth(3)->first == 30 && m1.nth(3)->second == "/30/");

        {
            cout << ">" << endl;
            auto res = erase_if
            (
                m1,
                [](const_reference& val){ return val.first == 42; }
            );
            cout << "<" << endl;

            CHECK(res == 0);
            CHECK(m1.size() == 4);
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
            CHECK(m1.nth(2)->first == 20 && m1.nth(2)->second == "/20/");
            CHECK(m1.nth(3)->first == 30 && m1.nth(3)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = erase_if
            (
                m1,
                [](const_reference& val){ return val.first == 20; }
            );
            cout << "<" << endl;

            CHECK(res == 2);
            CHECK(m1.size() == 2);
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 30 && m1.nth(1)->second == "/30/");
        }
    }
}
