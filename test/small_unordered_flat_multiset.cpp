//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include small_unordered_flat_multiset.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#include <sfl/small_unordered_flat_multiset.hpp>

#include "common/xint.hpp"
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
    sizeof(sfl::small_unordered_flat_multiset<double, 0>) ==
        3 * sizeof(sfl::small_unordered_flat_multiset<double, 0>::pointer),
    "Invalid size"
);

static_assert
(
    sizeof(sfl::small_unordered_flat_multiset<double, 5>) ==
        3 * sizeof(sfl::small_unordered_flat_multiset<double, 5>::pointer) +
        5 * sizeof(sfl::small_unordered_flat_multiset<double, 5>::value_type),
    "Invalid size"
);
*/

int main()
{
    using std::cout;
    using std::endl;
    using sfl::test::xint;

    cout << "Create empty containers and test all non-modifying "
            "member functions." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1;

        const sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2;

        sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s3;

        const sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s4;

        CHECK(s1.empty());
        CHECK(s2.empty());
        CHECK(s3.empty());
        CHECK(s4.empty());

        CHECK(s1.size() == 0);
        CHECK(s2.size() == 0);
        CHECK(s3.size() == 0);
        CHECK(s4.size() == 0);

        CHECK(s1.capacity() == 0);
        CHECK(s2.capacity() == 0);
        CHECK(s3.capacity() == 5);
        CHECK(s4.capacity() == 5);

        CHECK(s1.begin() == s1.end());
        CHECK(s2.begin() == s2.end());
        CHECK(s3.begin() == s3.end());
        CHECK(s4.begin() == s4.end());

        CHECK(s1.cbegin() == s1.cend());
        CHECK(s2.cbegin() == s2.cend());
        CHECK(s3.cbegin() == s3.cend());
        CHECK(s4.cbegin() == s4.cend());

        CHECK(s1.begin() == s1.cbegin());
        CHECK(s2.begin() == s2.cbegin());
        CHECK(s3.begin() == s3.cbegin());
        CHECK(s4.begin() == s4.cbegin());

        CHECK(s1.begin() == s1.nth(0));
        CHECK(s2.begin() == s2.nth(0));
        CHECK(s3.begin() == s3.nth(0));
        CHECK(s4.begin() == s4.nth(0));

        CHECK(s1.cbegin() == s1.nth(0));
        CHECK(s2.cbegin() == s2.nth(0));
        CHECK(s3.cbegin() == s3.nth(0));
        CHECK(s4.cbegin() == s4.nth(0));

        CHECK(s1.index_of(s1.nth(0)) == 0);
        CHECK(s2.index_of(s2.nth(0)) == 0);
        CHECK(s3.index_of(s3.nth(0)) == 0);
        CHECK(s4.index_of(s4.nth(0)) == 0);

        CHECK(s1.find(42) == s1.end());
        CHECK(s2.find(42) == s2.end());
        CHECK(s3.find(42) == s3.end());
        CHECK(s4.find(42) == s4.end());

        CHECK(s1.count(42) == 0);
        CHECK(s2.count(42) == 0);
        CHECK(s3.count(42) == 0);
        CHECK(s4.count(42) == 0);

        CHECK(s1.contains(42) == false);
        CHECK(s2.contains(42) == false);
        CHECK(s3.contains(42) == false);
        CHECK(s4.contains(42) == false);

        auto a1 = s1.get_allocator(); (void)a1;
        auto a2 = s2.get_allocator(); (void)a2;
        auto a3 = s3.get_allocator(); (void)a3;
        auto a4 = s4.get_allocator(); (void)a4;

        const xint i(10);
        const xint j(20);

        auto keq1 = s1.key_eq(); CHECK(keq1(i, i)); CHECK(!keq1(i, j));
        auto keq2 = s2.key_eq(); CHECK(keq2(i, i)); CHECK(!keq2(i, j));
        auto keq3 = s3.key_eq(); CHECK(keq3(i, i)); CHECK(!keq3(i, j));
        auto keq4 = s4.key_eq(); CHECK(keq4(i, i)); CHECK(!keq4(i, j));
    }

    cout << "Create empty containers and test all lookup functions "
            "that support transparent lookup." << endl;
    {
        sfl::small_unordered_flat_multiset<Person, 0, PersonEqual,
            TPARAM_ALLOCATOR<Person>
        > s1;

        const sfl::small_unordered_flat_multiset<Person, 0, PersonEqual,
            TPARAM_ALLOCATOR<Person>
        > s2;

        Person p(42, "John");

        CHECK(s1.find(p) == s1.end());
        CHECK(s2.find(p) == s1.end());

        CHECK(s1.find(42) == s1.end());
        CHECK(s2.find(42) == s1.end());

        CHECK(s1.count(p) == 0);
        CHECK(s2.count(p) == 0);

        CHECK(s1.count(42) == 0);
        CHECK(s2.count(42) == 0);

        CHECK(s1.contains(p) == false);
        CHECK(s2.contains(p) == false);

        CHECK(s1.contains(42) == false);
        CHECK(s2.contains(42) == false);
    }

    cout << "Test emplace(Args&&...) (N > 0, with reallocation)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 3, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            cout << ">" << endl;
            auto res = s.emplace(10);
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 1);
            CHECK(s.capacity() == 3);
            CHECK(*s.nth(0) == 10);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(10);
            cout << "<" << endl;

            CHECK(res == s.nth(1));
            CHECK(s.size() == 2);
            CHECK(s.capacity() == 3);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 10);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(20);
            cout << "<" << endl;

            CHECK(res == s.nth(2));
            CHECK(s.size() == 3);
            CHECK(s.capacity() == 3);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 10);
            CHECK(*s.nth(2) == 20);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(20);
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 4);
            CHECK(s.capacity() == 6);
            CHECK(*s.nth(0) == 20);
            CHECK(*s.nth(1) == 10);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 20);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(15);
            cout << "<" << endl;

            CHECK(res == s.nth(4));
            CHECK(s.size() == 5);
            CHECK(s.capacity() == 6);
            CHECK(*s.nth(0) == 20);
            CHECK(*s.nth(1) == 10);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 20);
            CHECK(*s.nth(4) == 15);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(15);
            cout << "<" << endl;

            CHECK(res == s.nth(5));
            CHECK(s.size() == 6);
            CHECK(s.capacity() == 6);
            CHECK(*s.nth(0) == 20);
            CHECK(*s.nth(1) == 10);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 20);
            CHECK(*s.nth(4) == 15);
            CHECK(*s.nth(5) == 15);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(30);
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 7);
            CHECK(s.capacity() == 12);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 10);
            CHECK(*s.nth(4) == 20);
            CHECK(*s.nth(5) == 15);
            CHECK(*s.nth(6) == 15);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(30);
            cout << "<" << endl;

            CHECK(res == s.nth(7));
            CHECK(s.size() == 8);
            CHECK(s.capacity() == 12);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 10);
            CHECK(*s.nth(4) == 20);
            CHECK(*s.nth(5) == 15);
            CHECK(*s.nth(6) == 15);
            CHECK(*s.nth(7) == 30);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(16);
            cout << "<" << endl;

            CHECK(res == s.nth(8));
            CHECK(s.size() == 9);
            CHECK(s.capacity() == 12);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 10);
            CHECK(*s.nth(4) == 20);
            CHECK(*s.nth(5) == 15);
            CHECK(*s.nth(6) == 15);
            CHECK(*s.nth(7) == 30);
            CHECK(*s.nth(8) == 16);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(16);
            cout << "<" << endl;

            CHECK(res == s.nth(9));
            CHECK(s.size() == 10);
            CHECK(s.capacity() == 12);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 10);
            CHECK(*s.nth(4) == 20);
            CHECK(*s.nth(5) == 15);
            CHECK(*s.nth(6) == 15);
            CHECK(*s.nth(7) == 30);
            CHECK(*s.nth(8) == 16);
            CHECK(*s.nth(9) == 16);
        }
    }

    cout << "Test emplace(Args&&...) (N == 0, with reallocation)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            cout << ">" << endl;
            auto res = s.emplace(10);
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 1);
            CHECK(s.capacity() == 1);
            CHECK(*s.nth(0) == 10);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(10);
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 2);
            CHECK(s.capacity() == 2);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 10);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(20);
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 3);
            CHECK(s.capacity() == 4);
            CHECK(*s.nth(0) == 20);
            CHECK(*s.nth(1) == 10);
            CHECK(*s.nth(2) == 10);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(20);
            cout << "<" << endl;

            CHECK(res == s.nth(3));
            CHECK(s.size() == 4);
            CHECK(s.capacity() == 4);
            CHECK(*s.nth(0) == 20);
            CHECK(*s.nth(1) == 10);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 20);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(15);
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 5);
            CHECK(s.capacity() == 8);
            CHECK(*s.nth(0) == 15);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 10);
            CHECK(*s.nth(4) == 20);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(15);
            cout << "<" << endl;

            CHECK(res == s.nth(5));
            CHECK(s.size() == 6);
            CHECK(s.capacity() == 8);
            CHECK(*s.nth(0) == 15);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 10);
            CHECK(*s.nth(4) == 20);
            CHECK(*s.nth(5) == 15);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(30);
            cout << "<" << endl;

            CHECK(res == s.nth(6));
            CHECK(s.size() == 7);
            CHECK(s.capacity() == 8);
            CHECK(*s.nth(0) == 15);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 10);
            CHECK(*s.nth(4) == 20);
            CHECK(*s.nth(5) == 15);
            CHECK(*s.nth(6) == 30);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(30);
            cout << "<" << endl;

            CHECK(res == s.nth(7));
            CHECK(s.size() == 8);
            CHECK(s.capacity() == 8);
            CHECK(*s.nth(0) == 15);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
            CHECK(*s.nth(3) == 10);
            CHECK(*s.nth(4) == 20);
            CHECK(*s.nth(5) == 15);
            CHECK(*s.nth(6) == 30);
            CHECK(*s.nth(7) == 30);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(16);
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 9);
            CHECK(s.capacity() == 16);
            CHECK(*s.nth(0) == 16);
            CHECK(*s.nth(1) == 15);
            CHECK(*s.nth(2) == 20);
            CHECK(*s.nth(3) == 10);
            CHECK(*s.nth(4) == 10);
            CHECK(*s.nth(5) == 20);
            CHECK(*s.nth(6) == 15);
            CHECK(*s.nth(7) == 30);
            CHECK(*s.nth(8) == 30);
        }

        {
            cout << ">" << endl;
            auto res = s.emplace(16);
            cout << "<" << endl;

            CHECK(res == s.nth(9));
            CHECK(s.size() == 10);
            CHECK(s.capacity() == 16);
            CHECK(*s.nth(0) == 16);
            CHECK(*s.nth(1) == 15);
            CHECK(*s.nth(2) == 20);
            CHECK(*s.nth(3) == 10);
            CHECK(*s.nth(4) == 10);
            CHECK(*s.nth(5) == 20);
            CHECK(*s.nth(6) == 15);
            CHECK(*s.nth(7) == 30);
            CHECK(*s.nth(8) == 30);
            CHECK(*s.nth(9) == 16);
        }
    }

    cout << "Test non-modifying member functions on non-empty container (1)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        s.emplace(10);
        s.emplace(20);
        s.emplace(20);
        s.emplace(30);

        {
            auto it = s.begin();
            CHECK(*it == 10); ++it;
            CHECK(*it == 20); ++it;
            CHECK(*it == 20); ++it;
            CHECK(*it == 30); ++it;
            CHECK(it == s.end());
        }

        {
            auto it = s.cbegin();
            CHECK(*it == 10); ++it;
            CHECK(*it == 20); ++it;
            CHECK(*it == 20); ++it;
            CHECK(*it == 30); ++it;
            CHECK(it == s.cend());
        }

        {
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 20);
            CHECK(*s.nth(3) == 30);
            CHECK(s.nth(4) == s.end());
        }

        {
            CHECK(std::next(s.begin(), 0) == s.nth(0));
            CHECK(std::next(s.begin(), 1) == s.nth(1));
            CHECK(std::next(s.begin(), 2) == s.nth(2));
        }

        {
            CHECK(std::next(s.cbegin(), 0) == s.nth(0));
            CHECK(std::next(s.cbegin(), 1) == s.nth(1));
            CHECK(std::next(s.cbegin(), 2) == s.nth(2));
        }

        {
            CHECK(s.index_of(s.nth(0)) == 0);
            CHECK(s.index_of(s.nth(1)) == 1);
            CHECK(s.index_of(s.nth(2)) == 2);
        }

        {
            auto data = s.data();
            CHECK(*data == 10); ++data;
            CHECK(*data == 20); ++data;
            CHECK(*data == 20); ++data;
            CHECK(*data == 30); ++data;
        }

        {
            CHECK(s.find(10) == s.nth(0));
            CHECK(s.find(20) == s.nth(1));
            CHECK(s.find(30) == s.nth(3));
            CHECK(s.find(40) == s.end());
        }

        {
            CHECK(s.count(10) == 1);
            CHECK(s.count(20) == 2);
            CHECK(s.count(30) == 1);
            CHECK(s.count(40) == 0);
        }

        {
            CHECK(s.contains(10) == true);
            CHECK(s.contains(20) == true);
            CHECK(s.contains(30) == true);
            CHECK(s.contains(40) == false);
        }
    }

    cout << "Test non-modifying member functions on non-empty container (2)." << endl;
    {
        sfl::small_unordered_flat_multiset<Person, 10, PersonEqual,
            TPARAM_ALLOCATOR<Person>
        > s;

        s.emplace(10, "Name 10");
        s.emplace(20, "Name 20");
        s.emplace(20, "Name 20");
        s.emplace(30, "Name 30");

        {
            auto it = s.begin();
            CHECK(it->id() == 10 && it->name() == "Name 10"); ++it;
            CHECK(it->id() == 20 && it->name() == "Name 20"); ++it;
            CHECK(it->id() == 20 && it->name() == "Name 20"); ++it;
            CHECK(it->id() == 30 && it->name() == "Name 30"); ++it;
            CHECK(it == s.end());
        }

        {
            auto it = s.cbegin();
            CHECK(it->id() == 10 && it->name() == "Name 10"); ++it;
            CHECK(it->id() == 20 && it->name() == "Name 20"); ++it;
            CHECK(it->id() == 20 && it->name() == "Name 20"); ++it;
            CHECK(it->id() == 30 && it->name() == "Name 30"); ++it;
            CHECK(it == s.cend());
        }

        {
            CHECK(std::next(s.begin(), 0) == s.nth(0));
            CHECK(std::next(s.begin(), 1) == s.nth(1));
            CHECK(std::next(s.begin(), 2) == s.nth(2));
        }

        {
            CHECK(std::next(s.cbegin(), 0) == s.nth(0));
            CHECK(std::next(s.cbegin(), 1) == s.nth(1));
            CHECK(std::next(s.cbegin(), 2) == s.nth(2));
        }

        {
            CHECK(s.index_of(s.nth(0)) == 0);
            CHECK(s.index_of(s.nth(1)) == 1);
            CHECK(s.index_of(s.nth(2)) == 2);
        }

        {
            auto data = s.data();
            CHECK(data->id() == 10 && data->name() == "Name 10"); ++data;
            CHECK(data->id() == 20 && data->name() == "Name 20"); ++data;
            CHECK(data->id() == 20 && data->name() == "Name 20"); ++data;
            CHECK(data->id() == 30 && data->name() == "Name 30"); ++data;
        }

        {
            CHECK(s.find(Person(10, "xxx")) == s.nth(0));
            CHECK(s.find(Person(20, "xxx")) == s.nth(1));
            CHECK(s.find(Person(30, "xxx")) == s.nth(3));
            CHECK(s.find(Person(40, "xxx")) == s.end());
        }

        {
            CHECK(s.find(10) == s.nth(0));
            CHECK(s.find(20) == s.nth(1));
            CHECK(s.find(30) == s.nth(3));
            CHECK(s.find(40) == s.end());
        }

        {
            CHECK(s.count(Person(10, "xxx")) == 1);
            CHECK(s.count(Person(20, "xxx")) == 2);
            CHECK(s.count(Person(30, "xxx")) == 1);
            CHECK(s.count(Person(40, "xxx")) == 0);
        }

        {
            CHECK(s.count(10) == 1);
            CHECK(s.count(20) == 2);
            CHECK(s.count(30) == 1);
            CHECK(s.count(40) == 0);
        }

        {
            CHECK(s.contains(Person(10, "xxx")) == true);
            CHECK(s.contains(Person(20, "xxx")) == true);
            CHECK(s.contains(Person(30, "xxx")) == true);
            CHECK(s.contains(Person(40, "xxx")) == false);
        }

        {
            CHECK(s.contains(10) == true);
            CHECK(s.contains(20) == true);
            CHECK(s.contains(30) == true);
            CHECK(s.contains(40) == false);
        }
    }

    cout << "Test emplace_hint(const_iterator, Args&&...)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            cout << ">" << endl;
            // hint is ignored
            auto res = s.emplace_hint(s.nth(0), 10);
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 1);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
        }

        {
            cout << ">" << endl;
            // hint is ignored
            auto res = s.emplace_hint(s.nth(0), 10);
            cout << "<" << endl;

            CHECK(res == s.nth(1));
            CHECK(s.size() == 2);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 10);
        }
    }

    cout << "Test insert(const value_type&)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            const xint v(10);

            cout << ">" << endl;
            auto res = s.insert(v);
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 1);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
        }

        {
            const xint v(10);

            cout << ">" << endl;
            auto res = s.insert(v);
            cout << "<" << endl;

            CHECK(res == s.nth(1));
            CHECK(s.size() == 2);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 10);
        }
    }

    cout << "Test insert(value_type&&)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            xint v(10);

            cout << ">" << endl;
            auto res = s.insert(std::move(v));
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(v == -10);
            CHECK(s.size() == 1);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
        }

        {
            xint v(10);

            cout << ">" << endl;
            auto res = s.insert(std::move(v));
            cout << "<" << endl;

            CHECK(res == s.nth(1));
            CHECK(v == -10);
            CHECK(s.size() == 2);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 10);
        }
    }

    cout << "Test insert(const_iterator, const value_type&)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            const xint v(10);

            cout << ">" << endl;
            // hint is ignored
            auto res = s.insert(s.nth(0), v);
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 1);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
        }

        {
            const xint v(10);

            cout << ">" << endl;
            // hint is ignored
            auto res = s.insert(s.nth(0), v);
            cout << "<" << endl;

            CHECK(res == s.nth(1));
            CHECK(s.size() == 2);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 10);
        }
    }

    cout << "Test insert(const_iterator, value_type&&)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            xint v(10);

            cout << ">" << endl;
            // hint is ignored
            auto res = s.insert(s.nth(0), std::move(v));
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(v == -10);
            CHECK(s.size() == 1);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
        }

        {
            xint v(10);

            cout << ">" << endl;
            // hint is ignored
            auto res = s.insert(s.nth(0), std::move(v));
            cout << "<" << endl;

            CHECK(res == s.nth(1));
            CHECK(v == -10);
            CHECK(s.size() == 2);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 10);
        }
    }

    cout << "Test insert(InputIt, InputIt)." << endl;
    {
        const std::vector<xint> v({10, 10, 20, 20, 15, 15, 30, 30});;

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        cout << ">" << endl;
        s.insert(v.begin(), v.end());
        cout << "<" << endl;

        CHECK(s.size() == 8);
        CHECK(s.capacity() == 10);
        CHECK(*s.nth(0) == 10);
        CHECK(*s.nth(1) == 10);
        CHECK(*s.nth(2) == 20);
        CHECK(*s.nth(3) == 20);
        CHECK(*s.nth(4) == 15);
        CHECK(*s.nth(5) == 15);
        CHECK(*s.nth(6) == 30);
        CHECK(*s.nth(7) == 30);
    }

    cout << "Test insert(std::initializer_list)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        cout << ">" << endl;
        s.insert({10, 10, 20, 20, 15, 15, 30, 30});
        cout << "<" << endl;

        CHECK(s.size() == 8);
        CHECK(s.capacity() == 10);
        CHECK(*s.nth(0) == 10);
        CHECK(*s.nth(1) == 10);
        CHECK(*s.nth(2) == 20);
        CHECK(*s.nth(3) == 20);
        CHECK(*s.nth(4) == 15);
        CHECK(*s.nth(5) == 15);
        CHECK(*s.nth(6) == 30);
        CHECK(*s.nth(7) == 30);
    }

    cout << "Test clear()." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            cout << ">" << endl;
            s.emplace(10);
            s.emplace(20);
            s.emplace(30);
            s.emplace(40);
            cout << "<" << endl;

            CHECK(s.size() == 4);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 30);
            CHECK(*s.nth(3) == 40);
        }

        {
            cout << ">" << endl;
            s.clear();
            cout << "<" << endl;

            CHECK(s.size() == 0);
        }

        {
            cout << ">" << endl;
            s.emplace(50);
            s.emplace(60);
            cout << "<" << endl;

            CHECK(s.size() == 2);
            CHECK(*s.nth(0) == 50);
            CHECK(*s.nth(1) == 60);
        }

        {
            cout << ">" << endl;
            s.clear();
            cout << "<" << endl;

            CHECK(s.size() == 0);
        }
    }

    cout << "Test erase(const_iterator)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            cout << ">" << endl;
            s.emplace(10);
            s.emplace(20);
            s.emplace(30);
            s.emplace(40);
            cout << "<" << endl;

            CHECK(s.size() == 4);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 30);
            CHECK(*s.nth(3) == 40);
        }

        {
            cout << ">" << endl;
            auto res = s.erase(s.nth(1));
            cout << "<" << endl;

            CHECK(res == s.nth(1));
            CHECK(s.size() == 3);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 40);
            CHECK(*s.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            auto res = s.erase(s.nth(0));
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 2);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 40);
        }

        {
            cout << ">" << endl;
            auto res = s.erase(s.nth(1));
            cout << "<" << endl;

            CHECK(res == s.nth(1));
            CHECK(s.size() == 1);
            CHECK(*s.nth(0) == 30);
        }

        {
            cout << ">" << endl;
            auto res = s.erase(s.nth(0));
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 0);
        }
    }

    cout << "Test erase(const_iterator, const_iterator)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            cout << ">" << endl;
            s.emplace(10);
            s.emplace(20);
            s.emplace(30);
            s.emplace(40);
            s.emplace(50);
            s.emplace(60);
            s.emplace(70);
            s.emplace(80);
            s.emplace(90);
            cout << "<" << endl;

            CHECK(s.size() == 9);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 30);
            CHECK(*s.nth(3) == 40);
            CHECK(*s.nth(4) == 50);
            CHECK(*s.nth(5) == 60);
            CHECK(*s.nth(6) == 70);
            CHECK(*s.nth(7) == 80);
            CHECK(*s.nth(8) == 90);
        }

        {
            cout << ">" << endl;
            // Erase nothing
            auto res = s.erase(s.nth(3), s.nth(3));
            cout << "<" << endl;

            CHECK(res == s.nth(3));
            CHECK(s.size() == 9);
        }

        {
            cout << ">" << endl;
            // Erase two elements near begin
            auto res = s.erase(s.nth(1), s.nth(3));
            cout << "<" << endl;

            CHECK(res == s.nth(1));
            CHECK(s.size() == 7);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 80);
            CHECK(*s.nth(2) == 90);
            CHECK(*s.nth(3) == 40);
            CHECK(*s.nth(4) == 50);
            CHECK(*s.nth(5) == 60);
            CHECK(*s.nth(6) == 70);
        }

        {
            cout << ">" << endl;
            // Erase two elements near end
            auto res = s.erase(s.nth(4), s.nth(6));
            cout << "<" << endl;

            CHECK(res == s.nth(4));
            CHECK(s.size() == 5);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 80);
            CHECK(*s.nth(2) == 90);
            CHECK(*s.nth(3) == 40);
            CHECK(*s.nth(4) == 70);
        }

        {
            cout << ">" << endl;
            // Remove two elements at begin
            auto res = s.erase(s.nth(0), s.nth(2));
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 3);
            CHECK(*s.nth(0) == 40);
            CHECK(*s.nth(1) == 70);
            CHECK(*s.nth(2) == 90);
        }

        {
            cout << ">" << endl;
            // Remove two elements at end
            auto res = s.erase(s.nth(1), s.nth(3));
            cout << "<" << endl;

            CHECK(res == s.nth(1));
            CHECK(s.size() == 1);
            CHECK(*s.nth(0) == 40);
        }

        {
            cout << ">" << endl;
            // Remove from begin to end
            auto res = s.erase(s.nth(0), s.nth(1));
            cout << "<" << endl;

            CHECK(res == s.nth(0));
            CHECK(s.size() == 0);
        }
    }

    cout << "Test erase(const Key&)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            cout << ">" << endl;
            s.emplace(10);
            s.emplace(20);
            s.emplace(20);
            s.emplace(20);
            s.emplace(10);
            s.emplace(30);
            s.emplace(40);
            s.emplace(10);
            cout << "<" << endl;

            CHECK(s.size() == 8);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 20);
            CHECK(*s.nth(3) == 20);
            CHECK(*s.nth(4) == 10);
            CHECK(*s.nth(5) == 30);
            CHECK(*s.nth(6) == 40);
            CHECK(*s.nth(7) == 10);
        }

        {
            const xint i(20);

            cout << ">" << endl;
            auto res = s.erase(i);
            cout << "<" << endl;

            CHECK(res == 3);
            CHECK(s.size() == 5);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 10);
            CHECK(*s.nth(2) == 40);
            CHECK(*s.nth(3) == 30);
            CHECK(*s.nth(4) == 10);
        }

        {
            const xint i(15);

            cout << ">" << endl;
            auto res = s.erase(i);
            cout << "<" << endl;

            CHECK(res == 0);
            CHECK(s.size() == 5);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 10);
            CHECK(*s.nth(2) == 40);
            CHECK(*s.nth(3) == 30);
            CHECK(*s.nth(4) == 10);
        }

        {
            const xint i(10);

            cout << ">" << endl;
            auto res = s.erase(i);
            cout << "<" << endl;

            CHECK(res == 3);
            CHECK(s.size() == 2);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 40);
        }
    }

    cout << "Test erase(K&&) (transparent erase)." << endl;
    {
        sfl::small_unordered_flat_multiset<Person, 10, PersonEqual,
            TPARAM_ALLOCATOR<Person>
        > s;

        {
            cout << ">" << endl;
            s.emplace(10, "/10/");
            s.emplace(20, "/20/");
            s.emplace(20, "*20*");
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

    cout << "Test swap(small_unordered_flat_multiset&)." << endl;
    {
        // s1 uses internal storage, s2 uses internal storage
        {
            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s1;

            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s2;

            s1.emplace(10);
            s1.emplace(11);
            s1.emplace(12);

            s2.emplace(20);
            s2.emplace(21);
            s2.emplace(22);
            s2.emplace(23);

            CHECK(s1.size() == 3);
            CHECK(*s1.nth(0) == 10);
            CHECK(*s1.nth(1) == 11);
            CHECK(*s1.nth(2) == 12);

            CHECK(s2.size() == 4);
            CHECK(*s2.nth(0) == 20);
            CHECK(*s2.nth(1) == 21);
            CHECK(*s2.nth(2) == 22);
            CHECK(*s2.nth(3) == 23);

            cout << ">" << endl;
            s1.swap(s2);
            cout << "<" << endl;

            CHECK(s1.size() == 4);
            CHECK(*s1.nth(0) == 20);
            CHECK(*s1.nth(1) == 21);
            CHECK(*s1.nth(2) == 22);
            CHECK(*s1.nth(3) == 23);

            CHECK(s2.size() == 3);
            CHECK(*s2.nth(0) == 10);
            CHECK(*s2.nth(1) == 11);
            CHECK(*s2.nth(2) == 12);

            cout << ">" << endl;
            s1.swap(s2);
            cout << "<" << endl;

            CHECK(s1.size() == 3);
            CHECK(*s1.nth(0) == 10);
            CHECK(*s1.nth(1) == 11);
            CHECK(*s1.nth(2) == 12);

            CHECK(s2.size() == 4);
            CHECK(*s2.nth(0) == 20);
            CHECK(*s2.nth(1) == 21);
            CHECK(*s2.nth(2) == 22);
            CHECK(*s2.nth(3) == 23);
        }

        // s1 uses internal storage, s2 uses external storage
        {
            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s1;

            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s2;

            s1.emplace(10);
            s1.emplace(11);
            s1.emplace(12);

            s2.emplace(20);
            s2.emplace(21);
            s2.emplace(22);
            s2.emplace(23);
            s2.emplace(24);
            s2.emplace(25);

            CHECK(s1.size() == 3);
            CHECK(*s1.nth(0) == 10);
            CHECK(*s1.nth(1) == 11);
            CHECK(*s1.nth(2) == 12);

            CHECK(s2.size() == 6);
            CHECK(*s2.nth(0) == 25);
            CHECK(*s2.nth(1) == 20);
            CHECK(*s2.nth(2) == 21);
            CHECK(*s2.nth(3) == 22);
            CHECK(*s2.nth(4) == 23);
            CHECK(*s2.nth(5) == 24);

            cout << ">" << endl;
            s1.swap(s2);
            cout << "<" << endl;

            CHECK(s1.size() == 6);
            CHECK(*s1.nth(0) == 25);
            CHECK(*s1.nth(1) == 20);
            CHECK(*s1.nth(2) == 21);
            CHECK(*s1.nth(3) == 22);
            CHECK(*s1.nth(4) == 23);
            CHECK(*s1.nth(5) == 24);

            CHECK(s2.size() == 3);
            CHECK(*s2.nth(0) == 10);
            CHECK(*s2.nth(1) == 11);
            CHECK(*s2.nth(2) == 12);
        }

        // s1 uses external storage, s2 uses internal storage
        {
            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s1;

            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s2;

            s1.emplace(10);
            s1.emplace(11);
            s1.emplace(12);
            s1.emplace(13);
            s1.emplace(14);
            s1.emplace(15);

            s2.emplace(20);
            s2.emplace(21);
            s2.emplace(22);

            CHECK(s1.size() == 6);
            CHECK(*s1.nth(0) == 15);
            CHECK(*s1.nth(1) == 10);
            CHECK(*s1.nth(2) == 11);
            CHECK(*s1.nth(3) == 12);
            CHECK(*s1.nth(4) == 13);
            CHECK(*s1.nth(5) == 14);

            CHECK(s2.size() == 3);
            CHECK(*s2.nth(0) == 20);
            CHECK(*s2.nth(1) == 21);
            CHECK(*s2.nth(2) == 22);

            cout << ">" << endl;
            s1.swap(s2);
            cout << "<" << endl;

            CHECK(s1.size() == 3);
            CHECK(*s1.nth(0) == 20);
            CHECK(*s1.nth(1) == 21);
            CHECK(*s1.nth(2) == 22);

            CHECK(s2.size() == 6);
            CHECK(*s2.nth(0) == 15);
            CHECK(*s2.nth(1) == 10);
            CHECK(*s2.nth(2) == 11);
            CHECK(*s2.nth(3) == 12);
            CHECK(*s2.nth(4) == 13);
            CHECK(*s2.nth(5) == 14);
        }

        // s1 uses external storage, s2 uses external storage
        {
            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s1;

            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s2;

            s1.emplace(10);
            s1.emplace(11);
            s1.emplace(12);
            s1.emplace(13);
            s1.emplace(14);
            s1.emplace(15);

            s2.emplace(20);
            s2.emplace(21);
            s2.emplace(22);
            s2.emplace(23);
            s2.emplace(24);
            s2.emplace(25);

            CHECK(s1.size() == 6);
            CHECK(*s1.nth(0) == 15);
            CHECK(*s1.nth(1) == 10);
            CHECK(*s1.nth(2) == 11);
            CHECK(*s1.nth(3) == 12);
            CHECK(*s1.nth(4) == 13);
            CHECK(*s1.nth(5) == 14);

            CHECK(s2.size() == 6);
            CHECK(*s2.nth(0) == 25);
            CHECK(*s2.nth(1) == 20);
            CHECK(*s2.nth(2) == 21);
            CHECK(*s2.nth(3) == 22);
            CHECK(*s2.nth(4) == 23);
            CHECK(*s2.nth(5) == 24);

            cout << ">" << endl;
            s1.swap(s2);
            cout << "<" << endl;

            CHECK(s1.size() == 6);
            CHECK(*s1.nth(0) == 25);
            CHECK(*s1.nth(1) == 20);
            CHECK(*s1.nth(2) == 21);
            CHECK(*s1.nth(3) == 22);
            CHECK(*s1.nth(4) == 23);
            CHECK(*s1.nth(5) == 24);

            CHECK(s2.size() == 6);
            CHECK(*s2.nth(0) == 15);
            CHECK(*s2.nth(1) == 10);
            CHECK(*s2.nth(2) == 11);
            CHECK(*s2.nth(3) == 12);
            CHECK(*s2.nth(4) == 13);
            CHECK(*s2.nth(5) == 14);
        }
    }

    cout << "Test reserve and shrink_to_fit (N > 0)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            cout << ">" << endl;
            s.emplace(10);
            s.emplace(20);
            s.emplace(30);
            cout << "<" << endl;

            CHECK(s.size() == 3);
            CHECK(s.capacity() == 5);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            s.reserve(4);
            cout << "<" << endl;

            CHECK(s.size() == 3);
            CHECK(s.capacity() == 5);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            s.reserve(10);
            cout << "<" << endl;

            CHECK(s.size() == 3);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            s.reserve(6);
            cout << "<" << endl;

            CHECK(s.size() == 3);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            s.shrink_to_fit();
            cout << "<" << endl;

            CHECK(s.size() == 3);
            CHECK(s.capacity() == 5);
            CHECK(*s.nth(0) == 10);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 30);
        }
    }

    cout << "Test reserve and shrink_to_fit (N == 0)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s;

        {
            cout << ">" << endl;
            s.emplace(10);
            s.emplace(20);
            s.emplace(30);
            cout << "<" << endl;

            CHECK(s.size() == 3);
            CHECK(s.capacity() == 4);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
        }

        {
            cout << ">" << endl;
            s.reserve(4);
            cout << "<" << endl;

            CHECK(s.size() == 3);
            CHECK(s.capacity() == 4);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
        }

        {
            cout << ">" << endl;
            s.reserve(10);
            cout << "<" << endl;

            CHECK(s.size() == 3);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
        }

        {
            cout << ">" << endl;
            s.reserve(6);
            cout << "<" << endl;

            CHECK(s.size() == 3);
            CHECK(s.capacity() == 10);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
        }

        {
            cout << ">" << endl;
            s.shrink_to_fit();
            cout << "<" << endl;

            CHECK(s.size() == 3);
            CHECK(s.capacity() == 3);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
        }

        {
            cout << ">" << endl;
            s.clear();
            cout << "<" << endl;

            cout << ">" << endl;
            s.shrink_to_fit();
            cout << "<" << endl;

            CHECK(s.size() == 0);
            CHECK(s.capacity() == 0);
        }

        {
            cout << ">" << endl;
            s.emplace(10);
            s.emplace(20);
            s.emplace(30);
            cout << "<" << endl;

            CHECK(s.size() == 3);
            CHECK(s.capacity() == 4);
            CHECK(*s.nth(0) == 30);
            CHECK(*s.nth(1) == 20);
            CHECK(*s.nth(2) == 10);
        }
    }

    cout << "Test empty constructors." << endl;
    {
        std::equal_to<xint> eq;
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1;

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2(eq);

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s3(alloc);

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s4(eq, alloc);

        CHECK(s1.size() == 0);
        CHECK(s1.capacity() == 10);

        CHECK(s2.size() == 0);
        CHECK(s2.capacity() == 10);

        CHECK(s3.size() == 0);
        CHECK(s3.capacity() == 10);

        CHECK(s4.size() == 0);
        CHECK(s4.capacity() == 10);
    }

    cout << "Test range constructors." << endl;
    {
        std::equal_to<xint> eq;
        TPARAM_ALLOCATOR<xint> alloc;

        const std::vector<xint> v({10, 20, 30, 10, 20});

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1(v.begin(), v.end());

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2(v.begin(), v.end(), eq);

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s3(v.begin(), v.end(), alloc);

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s4(v.begin(), v.end(), eq, alloc);


        CHECK(s1.size() == 5);
        CHECK(s1.capacity() == 10);
        CHECK(*s1.nth(0) == 10);
        CHECK(*s1.nth(1) == 20);
        CHECK(*s1.nth(2) == 30);
        CHECK(*s1.nth(3) == 10);
        CHECK(*s1.nth(4) == 20);

        CHECK(s2.size() == 5);
        CHECK(s2.capacity() == 10);
        CHECK(*s2.nth(0) == 10);
        CHECK(*s2.nth(1) == 20);
        CHECK(*s2.nth(2) == 30);
        CHECK(*s2.nth(3) == 10);
        CHECK(*s2.nth(4) == 20);

        CHECK(s3.size() == 5);
        CHECK(s3.capacity() == 10);
        CHECK(*s3.nth(0) == 10);
        CHECK(*s3.nth(1) == 20);
        CHECK(*s3.nth(2) == 30);
        CHECK(*s3.nth(3) == 10);
        CHECK(*s3.nth(4) == 20);

        CHECK(s4.size() == 5);
        CHECK(s4.capacity() == 10);
        CHECK(*s4.nth(0) == 10);
        CHECK(*s4.nth(1) == 20);
        CHECK(*s4.nth(2) == 30);
        CHECK(*s4.nth(3) == 10);
        CHECK(*s4.nth(4) == 20);
    }

    cout << "Test initializer_list constructors." << endl;
    {
        std::equal_to<xint> eq;
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1({10, 20, 30, 10, 20});

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2({10, 20, 30, 10, 20}, eq);

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s3({10, 20, 30, 10, 20}, alloc);

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s4({10, 20, 30, 10, 20}, eq, alloc);

        CHECK(s1.size() == 5);
        CHECK(s1.capacity() == 10);
        CHECK(*s1.nth(0) == 10);
        CHECK(*s1.nth(1) == 20);
        CHECK(*s1.nth(2) == 30);
        CHECK(*s1.nth(3) == 10);
        CHECK(*s1.nth(4) == 20);

        CHECK(s2.size() == 5);
        CHECK(s2.capacity() == 10);
        CHECK(*s2.nth(0) == 10);
        CHECK(*s2.nth(1) == 20);
        CHECK(*s2.nth(2) == 30);
        CHECK(*s2.nth(3) == 10);
        CHECK(*s2.nth(4) == 20);

        CHECK(s3.size() == 5);
        CHECK(s3.capacity() == 10);
        CHECK(*s3.nth(0) == 10);
        CHECK(*s3.nth(1) == 20);
        CHECK(*s3.nth(2) == 30);
        CHECK(*s3.nth(3) == 10);
        CHECK(*s3.nth(4) == 20);

        CHECK(s4.size() == 5);
        CHECK(s4.capacity() == 10);
        CHECK(*s4.nth(0) == 10);
        CHECK(*s4.nth(1) == 20);
        CHECK(*s4.nth(2) == 30);
        CHECK(*s4.nth(3) == 10);
        CHECK(*s4.nth(4) == 20);
    }

    cout << "Test copy constructors (N > 0)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1({10, 20, 30});

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2(s1);

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s3(s1, TPARAM_ALLOCATOR<xint>());

        CHECK(s1.size() == 3);
        CHECK(s1.capacity() == 10);
        CHECK(*s1.nth(0) == 10);
        CHECK(*s1.nth(1) == 20);
        CHECK(*s1.nth(2) == 30);

        CHECK(s2.size() == 3);
        CHECK(s2.capacity() == 10);
        CHECK(*s2.nth(0) == 10);
        CHECK(*s2.nth(1) == 20);
        CHECK(*s2.nth(2) == 30);

        CHECK(s3.size() == 3);
        CHECK(s3.capacity() == 10);
        CHECK(*s3.nth(0) == 10);
        CHECK(*s3.nth(1) == 20);
        CHECK(*s3.nth(2) == 30);
    }

    cout << "Test copy constructors (N == 0)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1({10, 20, 30});

        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2(s1);

        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s3(s1, TPARAM_ALLOCATOR<xint>());

        CHECK(s1.size() == 3);
        CHECK(s1.capacity() == 4);
        CHECK(*s1.nth(0) == 30);
        CHECK(*s1.nth(1) == 20);
        CHECK(*s1.nth(2) == 10);

        CHECK(s2.size() == 3);
        CHECK(s2.capacity() == 3);
        CHECK(*s2.nth(0) == 30);
        CHECK(*s2.nth(1) == 20);
        CHECK(*s2.nth(2) == 10);

        CHECK(s3.size() == 3);
        CHECK(s3.capacity() == 3);
        CHECK(*s3.nth(0) == 30);
        CHECK(*s3.nth(1) == 20);
        CHECK(*s3.nth(2) == 10);
    }

    cout << "Test move constructors (N > 0)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1({10, 20, 30});

        CHECK(s1.size() == 3);
        CHECK(s1.capacity() == 10);
        CHECK(*s1.nth(0) == 10);
        CHECK(*s1.nth(1) == 20);
        CHECK(*s1.nth(2) == 30);

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2(std::move(s1));

        // s1 is in a valid but unspecified state

        CHECK(s2.size() == 3);
        CHECK(s2.capacity() == 10);
        CHECK(*s2.nth(0) == 10);
        CHECK(*s2.nth(1) == 20);
        CHECK(*s2.nth(2) == 30);

        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s3(std::move(s2), TPARAM_ALLOCATOR<xint>());

        // s2 is in a valid but unspecified state

        CHECK(s3.size() == 3);
        CHECK(s3.capacity() == 10);
        CHECK(*s3.nth(0) == 10);
        CHECK(*s3.nth(1) == 20);
        CHECK(*s3.nth(2) == 30);
    }

    cout << "Test move constructors (N == 0)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1({10, 20, 30});

        CHECK(s1.size() == 3);
        CHECK(s1.capacity() == 4);
        CHECK(*s1.nth(0) == 30);
        CHECK(*s1.nth(1) == 20);
        CHECK(*s1.nth(2) == 10);

        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2(std::move(s1));

        // s1 is in a valid but unspecified state

        CHECK(s2.size() == 3);
        CHECK(s2.capacity() == 3 || s2.capacity() == 4); // Capacity depends on allocators.
        CHECK(*s2.nth(0) == 30);
        CHECK(*s2.nth(1) == 20);
        CHECK(*s2.nth(2) == 10);

        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s3(std::move(s2), TPARAM_ALLOCATOR<xint>());

        // s2 is in a valid but unspecified state

        CHECK(s3.size() == 3);
        CHECK(s3.capacity() == 3 || s3.capacity() == 4); // Capacity depends on allocators.
        CHECK(*s3.nth(0) == 30);
        CHECK(*s3.nth(1) == 20);
        CHECK(*s3.nth(2) == 10);
    }

    cout << "Test copy assignment operator." << endl;
    {
        // n <= capacity && n <= size
        {
            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s1({10, 11, 12});

            CHECK(s1.size() == 3);
            CHECK(s1.capacity() == 5);
            CHECK(*s1.nth(0) == 10);
            CHECK(*s1.nth(1) == 11);
            CHECK(*s1.nth(2) == 12);

            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s2({20, 21});

            CHECK(s2.size() == 2);
            CHECK(s2.capacity() == 5);
            CHECK(*s2.nth(0) == 20);
            CHECK(*s2.nth(1) == 21);

            cout << ">" << endl;
            s1 = s2;
            cout << "<" << endl;

            CHECK(s1.size() == 2);
            CHECK(s1.capacity() == 5);
            CHECK(*s1.nth(0) == 20);
            CHECK(*s1.nth(1) == 21);

            CHECK(s2.size() == 2);
            CHECK(s2.capacity() == 5);
            CHECK(*s2.nth(0) == 20);
            CHECK(*s2.nth(1) == 21);
        }

        // n <= capacity && n > size
        {
            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s1({10, 11, 12});

            CHECK(s1.size() == 3);
            CHECK(s1.capacity() == 5);
            CHECK(*s1.nth(0) == 10);
            CHECK(*s1.nth(1) == 11);
            CHECK(*s1.nth(2) == 12);

            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s2({20, 21, 22, 23, 24});

            CHECK(s2.size() == 5);
            CHECK(s2.capacity() == 5);
            CHECK(*s2.nth(0) == 20);
            CHECK(*s2.nth(1) == 21);
            CHECK(*s2.nth(2) == 22);
            CHECK(*s2.nth(3) == 23);
            CHECK(*s2.nth(4) == 24);

            cout << ">" << endl;
            s1 = s2;
            cout << "<" << endl;

            CHECK(s1.size() == 5);
            CHECK(s1.capacity() == 5);
            CHECK(*s1.nth(0) == 20);
            CHECK(*s1.nth(1) == 21);
            CHECK(*s1.nth(2) == 22);
            CHECK(*s1.nth(3) == 23);
            CHECK(*s1.nth(4) == 24);

            CHECK(s2.size() == 5);
            CHECK(s2.capacity() == 5);
            CHECK(*s2.nth(0) == 20);
            CHECK(*s2.nth(1) == 21);
            CHECK(*s2.nth(2) == 22);
            CHECK(*s2.nth(3) == 23);
            CHECK(*s2.nth(4) == 24);
        }

        // n > capacity
        {
            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s1({10, 11, 12});

            CHECK(s1.size() == 3);
            CHECK(s1.capacity() == 5);
            CHECK(*s1.nth(0) == 10);
            CHECK(*s1.nth(1) == 11);
            CHECK(*s1.nth(2) == 12);

            sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            > s2({20, 21, 22, 23, 24, 25});

            CHECK(s2.size() == 6);
            CHECK(s2.capacity() == 10);
            CHECK(*s2.nth(0) == 25);
            CHECK(*s2.nth(1) == 20);
            CHECK(*s2.nth(2) == 21);
            CHECK(*s2.nth(3) == 22);
            CHECK(*s2.nth(4) == 23);
            CHECK(*s2.nth(5) == 24);

            cout << ">" << endl;
            s1 = s2;
            cout << "<" << endl;

            CHECK(s1.size() == 6);
            CHECK(s1.capacity() == 6);
            CHECK(*s1.nth(0) == 25);
            CHECK(*s1.nth(1) == 20);
            CHECK(*s1.nth(2) == 21);
            CHECK(*s1.nth(3) == 22);
            CHECK(*s1.nth(4) == 23);
            CHECK(*s1.nth(5) == 24);

            CHECK(s2.size() == 6);
            CHECK(s2.capacity() == 10);
            CHECK(*s2.nth(0) == 25);
            CHECK(*s2.nth(1) == 20);
            CHECK(*s2.nth(2) == 21);
            CHECK(*s2.nth(3) == 22);
            CHECK(*s2.nth(4) == 23);
            CHECK(*s2.nth(5) == 24);
        }
    }

    cout << "Test move assignment operator (N > 0)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1({10, 11, 12});

        CHECK(s1.size() == 3);
        CHECK(s1.capacity() == 5);
        CHECK(*s1.nth(0) == 10);
        CHECK(*s1.nth(1) == 11);
        CHECK(*s1.nth(2) == 12);

        sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2({20, 21});

        CHECK(s2.size() == 2);
        CHECK(s2.capacity() == 5);
        CHECK(*s2.nth(0) == 20);
        CHECK(*s2.nth(1) == 21);

        cout << ">" << endl;
        s1 = std::move(s2);
        cout << "<" << endl;

        CHECK(s1.size() == 2);
        CHECK(s1.capacity() == 5);
        CHECK(*s1.nth(0) == 20);
        CHECK(*s1.nth(1) == 21);

        // s2 is in a valid but unspecified state

        cout << ">" << endl;
        s2 = std::move(s1);
        cout << "<" << endl;

        // s1 is in a valid but unspecified state

        CHECK(s2.size() == 2);
        CHECK(s2.capacity() == 5);
        CHECK(*s2.nth(0) == 20);
        CHECK(*s2.nth(1) == 21);
    }

    cout << "Test move assignment operator (N == 0)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1({10, 11, 12});

        CHECK(s1.size() == 3);
        CHECK(s1.capacity() == 4);
        CHECK(*s1.nth(0) == 12);
        CHECK(*s1.nth(1) == 11);
        CHECK(*s1.nth(2) == 10);

        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2({20, 21});

        CHECK(s2.size() == 2);
        CHECK(s2.capacity() == 2);
        CHECK(*s2.nth(0) == 21);
        CHECK(*s2.nth(1) == 20);

        cout << ">" << endl;
        s1 = std::move(s2);
        cout << "<" << endl;

        CHECK(s1.size() == 2);
        CHECK(s1.capacity() == 2);
        CHECK(*s1.nth(0) == 21);
        CHECK(*s1.nth(1) == 20);

        // s2 is in a valid but unspecified state

        sfl::small_unordered_flat_multiset<xint, 0, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s3({30, 31});

        CHECK(s3.size() == 2);
        CHECK(s3.capacity() == 2);
        CHECK(*s3.nth(0) == 31);
        CHECK(*s3.nth(1) == 30);

        cout << ">" << endl;
        s3 = std::move(s1);
        cout << "<" << endl;

        // s1 is in a valid but unspecified state

        CHECK(s3.size() == 2);
        CHECK(s3.capacity() == 2);
        CHECK(*s3.nth(0) == 21);
        CHECK(*s3.nth(1) == 20);
    }

    cout << "Test initializer_list assignment operator." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1({10, 11, 12});

        CHECK(s1.size() == 3);
        CHECK(s1.capacity() == 5);
        CHECK(*s1.nth(0) == 10);
        CHECK(*s1.nth(1) == 11);
        CHECK(*s1.nth(2) == 12);

        cout << ">" << endl;
        s1 = {20, 21, 22, 20, 21};
        cout << "<" << endl;

        CHECK(s1.size() == 5);
        CHECK(s1.capacity() == 5);
        CHECK(*s1.nth(0) == 20);
        CHECK(*s1.nth(1) == 21);
        CHECK(*s1.nth(2) == 22);
        CHECK(*s1.nth(3) == 20);
        CHECK(*s1.nth(4) == 21);
    }

    cout << "Test non-member comparison operators." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1({10, 20, 30});

        sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2({20, 30, 10});

        sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s3({30, 40, 10, 20});

        CHECK(s1 == s1);
        CHECK(s1 == s2);
        CHECK(s1 != s3);
    }

    cout << "Test non-member swap." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1({10, 11, 12});

        sfl::small_unordered_flat_multiset<xint, 5, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s2({20, 21, 22});

        using std::swap;
        swap(s1, s2);
    }

    cout << "Test non-member erase_if(small_unordered_flat_multiset&, Predicate)." << endl;
    {
        sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
            TPARAM_ALLOCATOR<xint>
        > s1({10, 20, 20, 30});

        using const_reference =
            typename sfl::small_unordered_flat_multiset<xint, 10, std::equal_to<xint>,
                TPARAM_ALLOCATOR<xint>
            >::const_reference;

        CHECK(s1.size() == 4);
        CHECK(*s1.nth(0) == 10);
        CHECK(*s1.nth(1) == 20);
        CHECK(*s1.nth(2) == 20);
        CHECK(*s1.nth(3) == 30);

        {
            cout << ">" << endl;
            auto res = erase_if
            (
                s1,
                [](const_reference& val){ return val == 42; }
            );
            cout << "<" << endl;

            CHECK(res == 0);
            CHECK(s1.size() == 4);
            CHECK(*s1.nth(0) == 10);
            CHECK(*s1.nth(1) == 20);
            CHECK(*s1.nth(2) == 20);
            CHECK(*s1.nth(3) == 30);
        }

        {
            cout << ">" << endl;
            auto res = erase_if
            (
                s1,
                [](const_reference& val){ return val == 20; }
            );
            cout << "<" << endl;

            CHECK(res == 2);
            CHECK(s1.size() == 2);
            CHECK(*s1.nth(0) == 10);
            CHECK(*s1.nth(1) == 30);
        }
    }
}
