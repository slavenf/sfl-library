//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include small_flat_map.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG
#include <cassert>
#include <iostream>
#include <vector>

#include <sfl/small_flat_map.hpp>

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

static_assert
(
    sizeof(sfl::small_flat_map<double, double, 0>) ==
        3 * sizeof(sfl::small_flat_map<double, double, 0>::pointer),
    "Invalid size"
);

static_assert
(
    sizeof(sfl::small_flat_map<double, double, 5>) ==
        3 * sizeof(sfl::small_flat_map<double, double, 5>::pointer) +
        5 * sizeof(sfl::small_flat_map<double, double, 0>::value_type),
    "Invalid size"
);

int main()
{
    using std::cout;
    using std::endl;
    using sfl::test::xint;
    using sfl::test::xstr;

    cout << "Create empty containers and test all non-modifying "
            "member functions." << endl;
    {
        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1;

        const sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2;

        sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3;

        const sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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

        CHECK(m1.rbegin() == m1.rend());
        CHECK(m2.rbegin() == m2.rend());
        CHECK(m3.rbegin() == m3.rend());
        CHECK(m4.rbegin() == m4.rend());

        CHECK(m1.crbegin() == m1.crend());
        CHECK(m2.crbegin() == m2.crend());
        CHECK(m3.crbegin() == m3.crend());
        CHECK(m4.crbegin() == m4.crend());

        CHECK(m1.rbegin() == m1.crbegin());
        CHECK(m2.rbegin() == m2.crbegin());
        CHECK(m3.rbegin() == m3.crbegin());
        CHECK(m4.rbegin() == m4.crbegin());

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

        CHECK(m1.lower_bound(42) == m1.end());
        CHECK(m2.lower_bound(42) == m2.end());
        CHECK(m3.lower_bound(42) == m3.end());
        CHECK(m4.lower_bound(42) == m4.end());

        CHECK(m1.upper_bound(42) == m1.end());
        CHECK(m2.upper_bound(42) == m2.end());
        CHECK(m3.upper_bound(42) == m3.end());
        CHECK(m4.upper_bound(42) == m4.end());

        CHECK(m1.equal_range(42) == std::make_pair(m1.end(), m1.end()));
        CHECK(m2.equal_range(42) == std::make_pair(m2.end(), m2.end()));
        CHECK(m3.equal_range(42) == std::make_pair(m3.end(), m3.end()));
        CHECK(m4.equal_range(42) == std::make_pair(m4.end(), m4.end()));

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

        auto kc1 = m1.key_comp(); CHECK(kc1(i, j));
        auto kc2 = m2.key_comp(); CHECK(kc2(i, j));
        auto kc3 = m3.key_comp(); CHECK(kc3(i, j));
        auto kc4 = m4.key_comp(); CHECK(kc4(i, j));

        const std::pair<xint, xstr> p1(10, "/10/");
        const std::pair<xint, xstr> p2(20, "/20/");

        auto vc1 = m1.value_comp(); CHECK(vc1(p1, p2));
        auto vc2 = m2.value_comp(); CHECK(vc2(p1, p2));
        auto vc3 = m3.value_comp(); CHECK(vc3(p1, p2));
        auto vc4 = m4.value_comp(); CHECK(vc4(p1, p2));
    }

    cout << "Create empty containers and test all lookup functions "
            "that support transparent lookup." << endl;
    {
        sfl::small_flat_map<Person, xstr, 0, PersonLess,
            TPARAM_ALLOCATOR<std::pair<Person, xstr>>
        > m1;

        const sfl::small_flat_map<Person, xstr, 0, PersonLess,
            TPARAM_ALLOCATOR<std::pair<Person, xstr>>
        > m2;

        Person p(42, "John");

        CHECK(m1.lower_bound(p) == m1.end());
        CHECK(m2.lower_bound(p) == m1.end());

        CHECK(m1.lower_bound(42) == m1.end());
        CHECK(m2.lower_bound(42) == m1.end());

        CHECK(m1.upper_bound(p) == m1.end());
        CHECK(m2.upper_bound(p) == m1.end());

        CHECK(m1.upper_bound(42) == m1.end());
        CHECK(m2.upper_bound(42) == m1.end());

        CHECK(m1.equal_range(p) == std::make_pair(m1.end(), m1.end()));
        CHECK(m2.equal_range(p) == std::make_pair(m1.cend(), m1.cend()));

        CHECK(m1.equal_range(42) == std::make_pair(m1.end(), m1.end()));
        CHECK(m2.equal_range(42) == std::make_pair(m1.cend(), m1.cend()));

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
        sfl::small_flat_map<xint, xstr, 3, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), true));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 3);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 3);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 3);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(3), true));
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 6);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(3), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(2), true));
            CHECK(m.size() == 5);
            CHECK(m.capacity() == 6);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 16 && m.nth(2)->second == "/16/");
            CHECK(m.nth(3)->first == 20 && m.nth(3)->second == "/20/");
            CHECK(m.nth(4)->first == 30 && m.nth(4)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(2), false));
        }
    }

    cout << "Test emplace(Args&&...) (N == 0, with reallocation)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), true));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 1);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 2);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 4);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(3), true));
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 4);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(3), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(2), true));
            CHECK(m.size() == 5);
            CHECK(m.capacity() == 8);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 16 && m.nth(2)->second == "/16/");
            CHECK(m.nth(3)->first == 20 && m.nth(3)->second == "/20/");
            CHECK(m.nth(4)->first == 30 && m.nth(4)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(2), false));
        }
    }

    cout << "Test non-modifying member functions on non-empty container (1)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        m.emplace(10, "/10/");
        m.emplace(20, "/20/");
        m.emplace(30, "/30/");

        {
            auto it = m.begin();
            CHECK(it->first == 10 && it->second == "/10/"); ++it;
            CHECK(it->first == 20 && it->second == "/20/"); ++it;
            CHECK(it->first == 30 && it->second == "/30/"); ++it;
            CHECK(it == m.end());
        }

        {
            auto it = m.cbegin();
            CHECK(it->first == 10 && it->second == "/10/"); ++it;
            CHECK(it->first == 20 && it->second == "/20/"); ++it;
            CHECK(it->first == 30 && it->second == "/30/"); ++it;
            CHECK(it == m.cend());
        }

        {
            auto it = m.rbegin();
            CHECK(it->first == 30 && it->second == "/30/"); ++it;
            CHECK(it->first == 20 && it->second == "/20/"); ++it;
            CHECK(it->first == 10 && it->second == "/10/"); ++it;
            CHECK(it == m.rend());
        }

        {
            auto it = m.crbegin();
            CHECK(it->first == 30 && it->second == "/30/"); ++it;
            CHECK(it->first == 20 && it->second == "/20/"); ++it;
            CHECK(it->first == 10 && it->second == "/10/"); ++it;
            CHECK(it == m.crend());
        }

        {
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
            CHECK(m.nth(3) == m.end());
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
            CHECK(data->first == 30 && data->second == "/30/"); ++data;
        }

        {
            CHECK(m.lower_bound(10) == m.nth(0));
            CHECK(m.lower_bound(20) == m.nth(1));
            CHECK(m.lower_bound(30) == m.nth(2));
        }

        {
            CHECK(m.upper_bound(10) == m.nth(1));
            CHECK(m.upper_bound(20) == m.nth(2));
            CHECK(m.upper_bound(30) == m.nth(3));
        }

        {
            CHECK(m.equal_range(10) == std::make_pair(m.nth(0), m.nth(1)));
            CHECK(m.equal_range(20) == std::make_pair(m.nth(1), m.nth(2)));
            CHECK(m.equal_range(30) == std::make_pair(m.nth(2), m.nth(3)));
            CHECK(m.equal_range(40) == std::make_pair(m.end(), m.end()));
        }

        {
            CHECK(m.find(10) == m.nth(0));
            CHECK(m.find(20) == m.nth(1));
            CHECK(m.find(30) == m.nth(2));
            CHECK(m.find(40) == m.end());
        }

        {
            CHECK(m.count(10) == 1);
            CHECK(m.count(20) == 1);
            CHECK(m.count(30) == 1);
            CHECK(m.count(40) == 0);
        }

        {
            CHECK(m.contains(10) == true);
            CHECK(m.contains(20) == true);
            CHECK(m.contains(30) == true);
            CHECK(m.contains(40) == false);
        }

        {
            CHECK(m.at(10) == "/10/");
            CHECK(m.at(20) == "/20/");
            CHECK(m.at(30) == "/30/");
        }

        {
            CHECK(m[10] == "/10/");
            CHECK(m[20] == "/20/");
            CHECK(m[30] == "/30/");
        }
    }

    cout << "Test non-modifying member functions on non-empty container (2)." << endl;
    {
        sfl::small_flat_map<Person, xstr, 10, PersonLess,
            TPARAM_ALLOCATOR<std::pair<Person, xstr>>
        > m;

        m.emplace(Person(10, "Name 10"), "Person 10");
        m.emplace(Person(20, "Name 20"), "Person 20");
        m.emplace(Person(30, "Name 30"), "Person 30");

        {
            auto it = m.begin();
            CHECK(it->first.id() == 10 && it->first.name() == "Name 10" && it->second == "Person 10"); ++it;
            CHECK(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            CHECK(it->first.id() == 30 && it->first.name() == "Name 30" && it->second == "Person 30"); ++it;
            CHECK(it == m.end());
        }

        {
            auto it = m.cbegin();
            CHECK(it->first.id() == 10 && it->first.name() == "Name 10" && it->second == "Person 10"); ++it;
            CHECK(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            CHECK(it->first.id() == 30 && it->first.name() == "Name 30" && it->second == "Person 30"); ++it;
            CHECK(it == m.cend());
        }

        {
            auto it = m.rbegin();
            CHECK(it->first.id() == 30 && it->first.name() == "Name 30" && it->second == "Person 30"); ++it;
            CHECK(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            CHECK(it->first.id() == 10 && it->first.name() == "Name 10" && it->second == "Person 10"); ++it;
            CHECK(it == m.rend());
        }

        {
            auto it = m.crbegin();
            CHECK(it->first.id() == 30 && it->first.name() == "Name 30" && it->second == "Person 30"); ++it;
            CHECK(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            CHECK(it->first.id() == 10 && it->first.name() == "Name 10" && it->second == "Person 10"); ++it;
            CHECK(it == m.crend());
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
            CHECK(data->first.id() == 30 && data->first.name() == "Name 30" && data->second == "Person 30"); ++data;
        }

        {
            CHECK(m.lower_bound(Person(10, "xxx")) == m.nth(0));
            CHECK(m.lower_bound(Person(20, "xxx")) == m.nth(1));
            CHECK(m.lower_bound(Person(30, "xxx")) == m.nth(2));
        }

        {
            CHECK(m.lower_bound(10) == m.nth(0));
            CHECK(m.lower_bound(20) == m.nth(1));
            CHECK(m.lower_bound(30) == m.nth(2));
        }

        {
            CHECK(m.upper_bound(Person(10, "xxx")) == m.nth(1));
            CHECK(m.upper_bound(Person(20, "xxx")) == m.nth(2));
            CHECK(m.upper_bound(Person(30, "xxx")) == m.nth(3));
        }

        {
            CHECK(m.upper_bound(10) == m.nth(1));
            CHECK(m.upper_bound(20) == m.nth(2));
            CHECK(m.upper_bound(30) == m.nth(3));
        }

        {
            CHECK(m.equal_range(Person(10, "xxx")) == std::make_pair(m.nth(0), m.nth(1)));
            CHECK(m.equal_range(Person(20, "xxx")) == std::make_pair(m.nth(1), m.nth(2)));
            CHECK(m.equal_range(Person(30, "xxx")) == std::make_pair(m.nth(2), m.nth(3)));
            CHECK(m.equal_range(Person(40, "xxx")) == std::make_pair(m.end(), m.end()));
        }

        {
            CHECK(m.equal_range(10) == std::make_pair(m.nth(0), m.nth(1)));
            CHECK(m.equal_range(20) == std::make_pair(m.nth(1), m.nth(2)));
            CHECK(m.equal_range(30) == std::make_pair(m.nth(2), m.nth(3)));
            CHECK(m.equal_range(40) == std::make_pair(m.end(), m.end()));
        }

        {
            CHECK(m.find(Person(10, "xxx")) == m.nth(0));
            CHECK(m.find(Person(20, "xxx")) == m.nth(1));
            CHECK(m.find(Person(30, "xxx")) == m.nth(2));
            CHECK(m.find(Person(40, "xxx")) == m.end());
        }

        {
            CHECK(m.find(10) == m.nth(0));
            CHECK(m.find(20) == m.nth(1));
            CHECK(m.find(30) == m.nth(2));
            CHECK(m.find(40) == m.end());
        }

        {
            CHECK(m.count(Person(10, "xxx")) == 1);
            CHECK(m.count(Person(20, "xxx")) == 1);
            CHECK(m.count(Person(30, "xxx")) == 1);
            CHECK(m.count(Person(40, "xxx")) == 0);
        }

        {
            CHECK(m.count(10) == 1);
            CHECK(m.count(20) == 1);
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
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.emplace_hint(m.nth(0), 10, "/10/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            // good hint, element exists
            auto res = m.emplace_hint(m.nth(0), 10, "/error/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.emplace_hint(m.nth(1), 20, "/20/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            // good hint, element exists
            auto res = m.emplace_hint(m.nth(1), 20, "/error/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.emplace_hint(m.nth(1), 15, "/15/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            // good hint, element exists
            auto res = m.emplace_hint(m.nth(1), 15, "/error/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            // bad hint, element does not exist
            auto res = m.emplace_hint(m.nth(0), 30, "/30/");
            cout << "<" << endl;

            CHECK(res == m.nth(3));
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            cout << ">" << endl;
            // bad hint, element exists
            auto res = m.emplace_hint(m.nth(0), 30, "/error/");
            cout << "<" << endl;

            CHECK(res == m.nth(3));
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }
    }

    cout << "Test insert(const value_type&)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            const std::pair<xint, xstr> v(10, "/10/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), true));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const std::pair<xint, xstr> v(10, "/10/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), false));
        }

        {
            const std::pair<xint, xstr> v(20, "/20/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const std::pair<xint, xstr> v(20, "/20/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
        }

        {
            const std::pair<xint, xstr> v(15, "/15/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            const std::pair<xint, xstr> v(15, "/15/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
        }
    }

    cout << "Test insert(value_type&&)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            std::pair<xint, xstr> v(10, "/10/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), true));
            CHECK(v.first == -10 && v.second.value() == "");
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            std::pair<xint, xstr> v(10, "/10/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), false));
            CHECK(v.first == 10 && v.second == "/10/");
        }

        {
            std::pair<xint, xstr> v(20, "/20/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(v.first == -20 && v.second.value() == "");
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            std::pair<xint, xstr> v(20, "/20/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
            CHECK(v.first == 20 && v.second == "/20/");
        }

        {
            std::pair<xint, xstr> v(15, "/15/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(v.first == -15 && v.second.value() == "");
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            std::pair<xint, xstr> v(15, "/15/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
            CHECK(v.first == 15 && v.second == "/15/");
        }
    }

    cout << "Test insert(P&&)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(10, "/10/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), true));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(10, "/10/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), false));
        }

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
        }

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(15, "/15/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(15, "/15/"));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
        }
    }

    cout << "Test insert(const_iterator, const value_type&)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            const std::pair<xint, xstr> v(10, "/10/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(0), v);
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const std::pair<xint, xstr> v(10, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(0), v);
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const std::pair<xint, xstr> v(20, "/20/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(1), v);
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const std::pair<xint, xstr> v(20, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(1), v);
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const std::pair<xint, xstr> v(15, "/15/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(1), v);
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            const std::pair<xint, xstr> v(15, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(1), v);
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            const std::pair<xint, xstr> v(30, "/30/");

            cout << ">" << endl;
            // bad hint, element does not exist
            auto res = m.insert(m.nth(0), v);
            cout << "<" << endl;

            CHECK(res == m.nth(3));
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            const std::pair<xint, xstr> v(30, "/error/");

            cout << ">" << endl;
            // bad hint, element exists
            auto res = m.insert(m.nth(0), v);
            cout << "<" << endl;

            CHECK(res == m.nth(3));
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }
    }

    cout << "Test insert(const_iterator, value_type&&)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            std::pair<xint, xstr> v(10, "/10/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(0), std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(v.first == -10 && v.second == "");
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            std::pair<xint, xstr> v(10, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(0), std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(v.first == 10 && v.second == "/error/");
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            std::pair<xint, xstr> v(20, "/20/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(1), std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(v.first == -20 && v.second == "");
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            std::pair<xint, xstr> v(20, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(1), std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(v.first == 20 && v.second == "/error/");
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            std::pair<xint, xstr> v(15, "/15/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(1), std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(v.first == -15 && v.second == "");
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            std::pair<xint, xstr> v(15, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(1), std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(v.first == 15 && v.second == "/error/");
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            std::pair<xint, xstr> v(30, "/30/");

            cout << ">" << endl;
            // bad hint, element does not exist
            auto res = m.insert(m.nth(0), std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(3));
            CHECK(v.first == -30 && v.second == "");
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            std::pair<xint, xstr> v(30, "/error/");

            cout << ">" << endl;
            // bad hint, element exists
            auto res = m.insert(m.nth(0), std::move(v));
            cout << "<" << endl;

            CHECK(res == m.nth(3));
            CHECK(v.first == 30 && v.second == "/error/");
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }
    }

    cout << "Test insert(const_iterator, P&&...)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin(), std::make_pair(10, "/10/"));
            cout << "<" << endl;

            CHECK(res == m.begin());
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin(), std::make_pair(10, "/error/"));
            cout << "<" << endl;

            CHECK(res == m.begin());
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin() + 1, std::make_pair(20, "/20/"));
            cout << "<" << endl;

            CHECK(res == m.begin() + 1);
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin() + 1, std::make_pair(20, "/error/"));
            cout << "<" << endl;

            CHECK(res == m.begin() + 1);
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin() + 1, std::make_pair(15, "/15/"));
            cout << "<" << endl;

            CHECK(res == m.begin() + 1);
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin() + 1, std::make_pair(15, "/error/"));
            cout << "<" << endl;

            CHECK(res == m.begin() + 1);
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin(), std::make_pair(30, "/30/"));
            cout << "<" << endl;

            CHECK(res == m.begin() + 3);
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin(), std::make_pair(30, "/error/"));
            cout << "<" << endl;

            CHECK(res == m.begin() + 3);
            CHECK(m.size() == 4);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }
    }

    cout << "Test insert(InputIt, InputIt)." << endl;
    {
        const std::vector<std::pair<xint, xstr>> v
        (
            {
                {10, "/10/"},
                {10, "/10.1/"},
                {20, "/20/"},
                {20, "/20.1/"},
                {15, "/15/"},
                {15, "/15.1/"},
                {30, "/30/"},
                {30, "/30.1/"}
            }
        );

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        cout << ">" << endl;
        m.insert(v.begin(), v.end());
        cout << "<" << endl;

        CHECK(m.size() == 4);
        CHECK(m.capacity() == 10);
        CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
        CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
    }

    cout << "Test insert(std::initializer_list)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        cout << ">" << endl;
        m.insert
        (
            {
                {10, "/10/"},
                {10, "/10.1/"},
                {20, "/20/"},
                {20, "/20.1/"},
                {15, "/15/"},
                {15, "/15.1/"},
                {30, "/30/"},
                {30, "/30.1/"},
            }
        );
        cout << "<" << endl;

        CHECK(m.size() == 4);
        CHECK(m.capacity() == 10);
        CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
        CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        CHECK(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
    }

    cout << "Test insert_or_assign(const Key&, M&&)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            const xint i(10);

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, "/10/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), true));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const xint i(10);

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, "/910/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), false));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
        }

        {
            const xint i(20);

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, "/20/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const xint i(20);

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, "/920/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/920/");
        }

        {
            const xint i(15);
            xstr s("/15/");

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, std::move(s));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(s == "");
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }

        {
            const xint i(15);
            xstr s("/915/");

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, std::move(s));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
            CHECK(s == "");
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/915/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }
    }

    cout << "Test insert_or_assign(Key&&, M&&)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            xint i(10);

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), "/10/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), true));
            CHECK(i == -10);
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            xint i(10);

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), "/910/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), false));
            CHECK(i == 10);
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
        }

        {
            xint i(20);

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), "/20/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(i == -20);
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            xint i(20);

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), "/920/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
            CHECK(i == 20);
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/920/");
        }

        {
            xint i(15);
            xstr s("/15/");

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), std::move(s));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(i == -15);
            CHECK(s == "");
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }

        {
            xint i(15);
            xstr s("/915/");

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), std::move(s));
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
            CHECK(i == 15);
            CHECK(s == "");
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/915/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }
    }

    cout << "Test insert_or_assign(const_iterator, const Key&, M&&)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            const xint i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(0), i, "/10/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const xint i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(0), i, "/910/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
        }

        {
            const xint i(20);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(1), i, "/20/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const xint i(20);

            cout << ">" << endl;
            // bad hint
            auto res = m.insert_or_assign(m.nth(0), i, "/920/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/920/");
        }

        {
            const xint i(15);
            xstr s("/15/");

            cout << ">" << endl;
            // bad hint
            auto res = m.insert_or_assign(m.nth(0), i, std::move(s));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(s == "");
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }

        {
            const xint i(15);
            xstr s("/915/");

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(1), i, std::move(s));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(s == "");
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/915/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }
    }

    cout << "Test insert_or_assign(const_iterator, Key&&, M&&)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            xint i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(0), std::move(i), "/10/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(i == -10);
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            xint i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(0), std::move(i), "/910/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(i == 10);
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
        }

        {
            xint i(20);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(1), std::move(i), "/20/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(i == -20);
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            xint i(20);

            cout << ">" << endl;
            // bad hint
            auto res = m.insert_or_assign(m.nth(0), std::move(i), "/920/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(i == 20);
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/920/");
        }

        {
            xint i(15);
            xstr s("/15/");

            cout << ">" << endl;
            // bad hint
            auto res = m.insert_or_assign(m.nth(0), std::move(i), std::move(s));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(i == -15);
            CHECK(s == "");
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }

        {
            xint i(15);
            xstr s("/915/");

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(1), std::move(i), std::move(s));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(i == 15);
            CHECK(s == "");
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/915/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }
    }

    cout << "Test try_emplace(const Key&, Args&&...)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            const xint i(10);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/10/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), true));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const xint i(10);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/910/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), false));
        }

        {
            const xint i(20);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/20/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const xint i(20);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/920/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
        }

        {
            const xint i(15);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/15/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            const xint i(15);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/915/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
        }
    }

    cout << "Test try_emplace(Key&&, Args&&...)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            xint i(10);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/10/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), true));
            CHECK(i == -10);
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            xint i(10);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/910/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(0), false));
            CHECK(i == 10);
        }

        {
            xint i(20);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/20/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(i == -20);
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            xint i(20);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/920/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
            CHECK(i == 20);
        }

        {
            xint i(15);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/15/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), true));
            CHECK(i == -15);
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            xint i(15);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/915/");
            cout << "<" << endl;

            CHECK(res == std::make_pair(m.nth(1), false));
            CHECK(i == 15);
        }
    }

    cout << "Test try_emplace(const_iterator, const Key&, Args&&...)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            const xint i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(0), i, "/10/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const xint i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(0), i, "/910/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const xint i(20);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(1), i, "/20/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const xint i(20);

            cout << ">" << endl;
            // bad hint
            auto res = m.try_emplace(m.nth(1), i, "/920/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const xint i(15);

            cout << ">" << endl;
            // bad hint
            auto res = m.try_emplace(m.nth(0), i, "/15/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            const xint i(15);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(1), i, "/915/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }
    }

    cout << "Test try_emplace(const_iterator, Key&&, Args&&...)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            xint i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(0), std::move(i), "/10/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(i == -10);
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            xint i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(0), std::move(i), "/910/");
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(i == 10);
            CHECK(m.size() == 1);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            xint i(20);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(1), std::move(i), "/20/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(i == -20);
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            xint i(20);

            cout << ">" << endl;
            // bad hint
            auto res = m.try_emplace(m.nth(1), std::move(i), "/920/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(i == 20);
            CHECK(m.size() == 2);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            xint i(15);

            cout << ">" << endl;
            // bad hint
            auto res = m.try_emplace(m.nth(0), std::move(i), "/15/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(i == -15);
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            xint i(15);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(1), std::move(i), "/915/");
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(i == 15);
            CHECK(m.size() == 3);
            CHECK(m.capacity() == 10);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            CHECK(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }
    }

    cout << "Test clear()." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
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
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
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
            CHECK(m.nth(1)->first == 30 && m.nth(1)->second == "/30/");
            CHECK(m.nth(2)->first == 40 && m.nth(2)->second == "/40/");
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
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
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
            CHECK(m.nth(1)->first == 40 && m.nth(1)->second == "/40/");
            CHECK(m.nth(2)->first == 50 && m.nth(2)->second == "/50/");
            CHECK(m.nth(3)->first == 60 && m.nth(3)->second == "/60/");
            CHECK(m.nth(4)->first == 70 && m.nth(4)->second == "/70/");
            CHECK(m.nth(5)->first == 80 && m.nth(5)->second == "/80/");
            CHECK(m.nth(6)->first == 90 && m.nth(6)->second == "/90/");
        }

        {
            cout << ">" << endl;
            // Erase two elements near end
            auto res = m.erase(m.nth(4), m.nth(6));
            cout << "<" << endl;

            CHECK(res == m.nth(4));
            CHECK(m.size() == 5);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 40 && m.nth(1)->second == "/40/");
            CHECK(m.nth(2)->first == 50 && m.nth(2)->second == "/50/");
            CHECK(m.nth(3)->first == 60 && m.nth(3)->second == "/60/");
            CHECK(m.nth(4)->first == 90 && m.nth(4)->second == "/90/");
        }

        {
            cout << ">" << endl;
            // Remove two elements at begin
            auto res = m.erase(m.nth(0), m.nth(2));
            cout << "<" << endl;

            CHECK(res == m.nth(0));
            CHECK(m.size() == 3);
            CHECK(m.nth(0)->first == 50 && m.nth(0)->second == "/50/");
            CHECK(m.nth(1)->first == 60 && m.nth(1)->second == "/60/");
            CHECK(m.nth(2)->first == 90 && m.nth(2)->second == "/90/");
        }

        {
            cout << ">" << endl;
            // Remove two elements at end
            auto res = m.erase(m.nth(1), m.nth(3));
            cout << "<" << endl;

            CHECK(res == m.nth(1));
            CHECK(m.size() == 1);
            CHECK(m.nth(0)->first == 50 && m.nth(0)->second == "/50/");
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
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            const xint i(10);

            cout << ">" << endl;
            auto res = m.erase(i);
            cout << "<" << endl;

            CHECK(res == 1);
            CHECK(m.size() == 2);
            CHECK(m.nth(0)->first == 20 && m.nth(0)->second == "/20/");
            CHECK(m.nth(1)->first == 30 && m.nth(1)->second == "/30/");
        }

        {
            const xint i(15);

            cout << ">" << endl;
            auto res = m.erase(i);
            cout << "<" << endl;

            CHECK(res == 0);
            CHECK(m.size() == 2);
            CHECK(m.nth(0)->first == 20 && m.nth(0)->second == "/20/");
            CHECK(m.nth(1)->first == 30 && m.nth(1)->second == "/30/");
        }

        {
            const xint i(20);

            cout << ">" << endl;
            auto res = m.erase(i);
            cout << "<" << endl;

            CHECK(res == 1);
            CHECK(m.size() == 1);
            CHECK(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
        }
    }

    cout << "Test erase(K&&) (transparent erase)." << endl;
    {
        sfl::small_flat_map<Person, xstr, 10, PersonLess,
            TPARAM_ALLOCATOR<std::pair<Person, xstr>>
        > m;

        {
            cout << ">" << endl;
            m.emplace
            (
                std::piecewise_construct,
                std::forward_as_tuple(10, "Person /10/"),
                std::forward_as_tuple("/10/")
            );
            m.emplace
            (
                std::piecewise_construct,
                std::forward_as_tuple(20, "Person /20/"),
                std::forward_as_tuple("/20/")
            );
            cout << "<" << endl;

            CHECK(m.size() == 2);
        }

        {
            cout << ">" << endl;
            auto res = m.erase(10);
            cout << "<" << endl;

            CHECK(res == 1);
            CHECK(m.size() == 1);
        }

        {
            cout << ">" << endl;
            auto res = m.erase(15);
            cout << "<" << endl;

            CHECK(res == 0);
            CHECK(m.size() == 1);
        }

        {
            const Person p(20, "persons are compared by ID only");

            cout << ">" << endl;
            auto res = m.erase(p);
            cout << "<" << endl;

            CHECK(res == 1);
            CHECK(m.size() == 0);
        }
    }

    cout << "Test swap(small_flat_map&)." << endl;
    {
        // m1 uses internal storage, m2 uses internal storage
        {
            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m1;

            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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
            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m1;

            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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
            CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            CHECK(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            CHECK(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            CHECK(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");
            CHECK(m2.nth(5)->first == 25 && m2.nth(5)->second == "/25/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            CHECK(m1.size() == 6);
            CHECK(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            CHECK(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            CHECK(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
            CHECK(m1.nth(3)->first == 23 && m1.nth(3)->second == "/23/");
            CHECK(m1.nth(4)->first == 24 && m1.nth(4)->second == "/24/");
            CHECK(m1.nth(5)->first == 25 && m1.nth(5)->second == "/25/");

            CHECK(m2.size() == 3);
            CHECK(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
            CHECK(m2.nth(1)->first == 11 && m2.nth(1)->second == "/11/");
            CHECK(m2.nth(2)->first == 12 && m2.nth(2)->second == "/12/");
        }

        // m1 uses external storage, m2 uses internal storage
        {
            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m1;

            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            CHECK(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");
            CHECK(m1.nth(3)->first == 13 && m1.nth(3)->second == "/13/");
            CHECK(m1.nth(4)->first == 14 && m1.nth(4)->second == "/14/");
            CHECK(m1.nth(5)->first == 15 && m1.nth(5)->second == "/15/");

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
            CHECK(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
            CHECK(m2.nth(1)->first == 11 && m2.nth(1)->second == "/11/");
            CHECK(m2.nth(2)->first == 12 && m2.nth(2)->second == "/12/");
            CHECK(m2.nth(3)->first == 13 && m2.nth(3)->second == "/13/");
            CHECK(m2.nth(4)->first == 14 && m2.nth(4)->second == "/14/");
            CHECK(m2.nth(5)->first == 15 && m2.nth(5)->second == "/15/");
        }

        // m1 uses external storage, m2 uses external storage
        {
            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            > m1;

            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            CHECK(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");
            CHECK(m1.nth(3)->first == 13 && m1.nth(3)->second == "/13/");
            CHECK(m1.nth(4)->first == 14 && m1.nth(4)->second == "/14/");
            CHECK(m1.nth(5)->first == 15 && m1.nth(5)->second == "/15/");

            CHECK(m2.size() == 6);
            CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            CHECK(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            CHECK(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            CHECK(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");
            CHECK(m2.nth(5)->first == 25 && m2.nth(5)->second == "/25/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            CHECK(m1.size() == 6);
            CHECK(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            CHECK(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            CHECK(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
            CHECK(m1.nth(3)->first == 23 && m1.nth(3)->second == "/23/");
            CHECK(m1.nth(4)->first == 24 && m1.nth(4)->second == "/24/");
            CHECK(m1.nth(5)->first == 25 && m1.nth(5)->second == "/25/");

            CHECK(m2.size() == 6);
            CHECK(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
            CHECK(m2.nth(1)->first == 11 && m2.nth(1)->second == "/11/");
            CHECK(m2.nth(2)->first == 12 && m2.nth(2)->second == "/12/");
            CHECK(m2.nth(3)->first == 13 && m2.nth(3)->second == "/13/");
            CHECK(m2.nth(4)->first == 14 && m2.nth(4)->second == "/14/");
            CHECK(m2.nth(5)->first == 15 && m2.nth(5)->second == "/15/");
        }
    }

    cout << "Test at(const Key&)." << endl;
    {
        #ifndef SFL_NO_EXCEPTIONS
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        const auto& rm = m;

        {
            m.emplace(10, "/10/");

            CHECK(m.size() == 1);
        }

        {
            bool exception_caught = false;

            try
            {
                CHECK(m.at(10) == "/10/");
            }
            catch (...)
            {
                exception_caught = true;
            }

            CHECK(!exception_caught);
        }

        {
            bool exception_caught = false;

            try
            {
                CHECK(rm.at(10) == "/10/");
            }
            catch (...)
            {
                exception_caught = true;
            }

            CHECK(!exception_caught);
        }

        {
            bool exception_caught = false;

            try
            {
                CHECK(m.at(15) == "/15/");
            }
            catch (...)
            {
                exception_caught = true;
            }

            CHECK(exception_caught);
        }

        {
            bool exception_caught = false;

            try
            {
                CHECK(rm.at(15) == "/15/");
            }
            catch (...)
            {
                exception_caught = true;
            }

            CHECK(exception_caught);
        }
        #endif
    }

    cout << "Test operator[]." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m;

        {
            m.emplace(10, "/10/");

            CHECK(m.size() == 1);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const xint i(10);

            CHECK(m[i] == "/10/");
            CHECK(m.size() == 1);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            CHECK(m[10] == "/10/");
            CHECK(m.size() == 1);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const xint i(20);

            CHECK(m[i] == "");
            CHECK(m.size() == 2);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "");

            m[i] = "/20/";

            CHECK(m.size() == 2);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            CHECK(m[30] == "");
            CHECK(m.size() == 3);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "");

            m[30] = "/30/";

            CHECK(m.size() == 3);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }
    }

    cout << "Test reserve and shrink_to_fit (N > 0)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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
        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
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
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.reserve(4);
            cout << "<" << endl;

            CHECK(m.size() == 3);
            CHECK(m.capacity() == 4);
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
            CHECK(m.capacity() == 3);
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
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
            CHECK(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            CHECK(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            CHECK(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }
    }

    cout << "Test empty constructors." << endl;
    {
        std::less<xint> comp;
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1;

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(comp);

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3(alloc);

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m4(comp, alloc);

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
        std::less<xint> comp;
        TPARAM_ALLOCATOR<xint> alloc;

        const std::vector<std::pair<xint, xstr>> v
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1(v.begin(), v.end());

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(v.begin(), v.end(), comp);

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3(v.begin(), v.end(), alloc);

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m4(v.begin(), v.end(), comp, alloc);

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

        CHECK(m4.size() == 3);
        CHECK(m4.capacity() == 10);
        CHECK(m4.nth(0)->first == 10 && m4.nth(0)->second == "/10/");
        CHECK(m4.nth(1)->first == 20 && m4.nth(1)->second == "/20/");
        CHECK(m4.nth(2)->first == 30 && m4.nth(2)->second == "/30/");
    }

    cout << "Test initializer_list constructors." << endl;
    {
        std::less<xint> comp;
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }, comp
        );

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }, alloc
        );

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m4
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }, comp, alloc
        );

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

        CHECK(m4.size() == 3);
        CHECK(m4.capacity() == 10);
        CHECK(m4.nth(0)->first == 10 && m4.nth(0)->second == "/10/");
        CHECK(m4.nth(1)->first == 20 && m4.nth(1)->second == "/20/");
        CHECK(m4.nth(2)->first == 30 && m4.nth(2)->second == "/30/");
    }

    cout << "Test copy constructors (N > 0)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(m1);

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
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
        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );

        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(m1);

        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3(m1, TPARAM_ALLOCATOR<xint>());

        CHECK(m1.size() == 3);
        CHECK(m1.capacity() == 4);
        CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        CHECK(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        CHECK(m2.size() == 3);
        CHECK(m2.capacity() == 3);
        CHECK(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
        CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        CHECK(m2.nth(2)->first == 30 && m2.nth(2)->second == "/30/");

        CHECK(m3.size() == 3);
        CHECK(m3.capacity() == 3);
        CHECK(m3.nth(0)->first == 10 && m3.nth(0)->second == "/10/");
        CHECK(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        CHECK(m3.nth(2)->first == 30 && m3.nth(2)->second == "/30/");
    }

    cout << "Test move constructors (N > 0)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );

        CHECK(m1.size() == 3);
        CHECK(m1.capacity() == 10);
        CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        CHECK(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(std::move(m1));

        // m1 is in a valid but unspecified state

        CHECK(m2.size() == 3);
        CHECK(m2.capacity() == 10);
        CHECK(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
        CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        CHECK(m2.nth(2)->first == 30 && m2.nth(2)->second == "/30/");

        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
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
        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );

        CHECK(m1.size() == 3);
        CHECK(m1.capacity() == 4);
        CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        CHECK(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m2(std::move(m1));

        // m1 is in a valid but unspecified state

        CHECK(m2.size() == 3);
        CHECK(m2.capacity() == 3 || m2.capacity() == 4); // Capacity depends on allocators.
        CHECK(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
        CHECK(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        CHECK(m2.nth(2)->first == 30 && m2.nth(2)->second == "/30/");

        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m3(std::move(m2), TPARAM_ALLOCATOR<xint>());

        // m2 is in a valid but unspecified state

        CHECK(m3.size() == 3);
        CHECK(m3.capacity() == 3 || m3.capacity() == 4); // Capacity depends on allocators.
        CHECK(m3.nth(0)->first == 10 && m3.nth(0)->second == "/10/");
        CHECK(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        CHECK(m3.nth(2)->first == 30 && m3.nth(2)->second == "/30/");
    }

    cout << "Test copy assignment operator." << endl;
    {
        // n <= capacity && n <= size
        {
            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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

            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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
            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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

            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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
            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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

            sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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
            CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            CHECK(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            CHECK(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            CHECK(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");
            CHECK(m2.nth(5)->first == 25 && m2.nth(5)->second == "/25/");

            cout << ">" << endl;
            m1 = m2;
            cout << "<" << endl;

            CHECK(m1.size() == 6);
            CHECK(m1.capacity() == 6);
            CHECK(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            CHECK(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            CHECK(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
            CHECK(m1.nth(3)->first == 23 && m1.nth(3)->second == "/23/");
            CHECK(m1.nth(4)->first == 24 && m1.nth(4)->second == "/24/");
            CHECK(m1.nth(5)->first == 25 && m1.nth(5)->second == "/25/");

            CHECK(m2.size() == 6);
            CHECK(m2.capacity() == 10);
            CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            CHECK(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            CHECK(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            CHECK(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");
            CHECK(m2.nth(5)->first == 25 && m2.nth(5)->second == "/25/");
        }
    }

    cout << "Test move assignment operator (N > 0)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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

        sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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
        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
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
        CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        CHECK(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
        CHECK(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
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
        CHECK(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
        CHECK(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");

        cout << ">" << endl;
        m1 = std::move(m2);
        cout << "<" << endl;

        CHECK(m1.size() == 2);
        CHECK(m1.capacity() == 2);
        CHECK(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
        CHECK(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");

        // m2 is in a valid but unspecified state

        sfl::small_flat_map<xint, xstr, 0, std::less<xint>,
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
        CHECK(m3.nth(0)->first == 30 && m3.nth(0)->second == "/30/");
        CHECK(m3.nth(1)->first == 31 && m3.nth(1)->second == "/31/");

        cout << ">" << endl;
        m3 = std::move(m1);
        cout << "<" << endl;

        // m1 is in a valid but unspecified state

        CHECK(m3.size() == 2);
        CHECK(m3.capacity() == 2);
        CHECK(m3.nth(0)->first == 20 && m3.nth(0)->second == "/20/");
        CHECK(m3.nth(1)->first == 21 && m3.nth(1)->second == "/21/");
    }

    cout << "Test initializer_list assignment operator." << endl;
    {
        sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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
            {20, "/20/"},
            {22, "/22/"},
            {21, "/21/"},
            {20, "/20/"},
            {21, "/21/"},
        };
        cout << "<" << endl;

        CHECK(m1.size() == 3);
        CHECK(m1.capacity() == 5);
        CHECK(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
        CHECK(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
        CHECK(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
    }

    cout << "Test non-member comparison operators." << endl;
    {
        sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {20, "/20/"},
                {30, "/30/"}
            }
        );

        sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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
        CHECK(m1 < m2);
        CHECK(m2 > m1);
        CHECK(m1 <= m1);
        CHECK(m1 <= m2);
        CHECK(m2 >= m2);
        CHECK(m2 >= m1);
    }

    cout << "Test non-member swap." << endl;
    {
        sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {11, "/11/"},
                {12, "/12/"}
            }
        );

        sfl::small_flat_map<xint, xstr, 5, std::less<xint>,
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

    cout << "Test non-member erase_if(small_flat_map&, Predicate)." << endl;
    {
        sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
            TPARAM_ALLOCATOR<std::pair<xint, xstr>>
        > m1
        (
            {
                {10, "/10/"},
                {20, "/20/"},
                {30, "/30/"}
            }
        );

        using const_reference =
            typename sfl::small_flat_map<xint, xstr, 10, std::less<xint>,
                TPARAM_ALLOCATOR<std::pair<xint, xstr>>
            >::const_reference;

        CHECK(m1.size() == 3);
        CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        CHECK(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        {
            cout << ">" << endl;
            auto res = erase_if
            (
                m1,
                [](const_reference& val){ return val.first == 42; }
            );
            cout << "<" << endl;

            CHECK(res == 0);
            CHECK(m1.size() == 3);
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
            CHECK(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = erase_if
            (
                m1,
                [](const_reference& val){ return val.first == 20; }
            );
            cout << "<" << endl;

            CHECK(res == 1);
            CHECK(m1.size() == 2);
            CHECK(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            CHECK(m1.nth(1)->first == 30 && m1.nth(1)->second == "/30/");
        }
    }
}
