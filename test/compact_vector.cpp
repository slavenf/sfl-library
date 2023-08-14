//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include compact_vector.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include <sfl/compact_vector.hpp>

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

static_assert
(
    sizeof(sfl::compact_vector<int>) ==
        2 * sizeof(sfl::compact_vector<int>::pointer),
    "Invalid size"
);

int main()
{
    using std::cout;
    using std::endl;
    using sfl::test::xint;

    cout << "Create empty containers and test all non-modifying "
            "member functions." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1;
        const sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2;

        CHECK(v1.empty());
        CHECK(v2.empty());

        CHECK(v1.size() == 0);
        CHECK(v2.size() == 0);

        CHECK(v1.capacity() == 0);
        CHECK(v2.capacity() == 0);

        CHECK(v1.begin() == v1.end());
        CHECK(v2.begin() == v2.end());

        CHECK(v1.cbegin() == v1.cend());
        CHECK(v2.cbegin() == v2.cend());

        CHECK(v1.begin() == v1.cbegin());
        CHECK(v2.begin() == v2.cbegin());

        CHECK(v1.rbegin() == v1.rend());
        CHECK(v2.rbegin() == v2.rend());

        CHECK(v1.crbegin() == v1.crend());
        CHECK(v2.crbegin() == v2.crend());

        CHECK(v1.rbegin() == v1.crbegin());
        CHECK(v2.rbegin() == v2.crbegin());

        CHECK(v1.begin() == v1.nth(0));
        CHECK(v2.begin() == v2.nth(0));

        CHECK(v1.cbegin() == v1.nth(0));
        CHECK(v2.cbegin() == v2.nth(0));

        CHECK(v1.index_of(v1.nth(0)) == 0);
        CHECK(v2.index_of(v2.nth(0)) == 0);

        auto a1 = v1.get_allocator(); (void)a1;
        auto a2 = v2.get_allocator(); (void)a2;
    }

    cout << "Test emplace(const_iterator, Args&&...)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            auto res = v.emplace(v.end(), 10);
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.end(), 20);
            cout << "<" << endl;

            CHECK(res == v.nth(1));
            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.end(), 30);
            cout << "<" << endl;

            CHECK(res == v.nth(2));
            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(1), 40);
            cout << "<" << endl;

            CHECK(res == v.nth(1));
            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 40);
            CHECK(v[2] == 20);
            CHECK(v[3] == 30);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(1), 50);
            cout << "<" << endl;

            CHECK(res == v.nth(1));
            CHECK(v.size() == 5);
            CHECK(v[0] == 10);
            CHECK(v[1] == 50);
            CHECK(v[2] == 40);
            CHECK(v[3] == 20);
            CHECK(v[4] == 30);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(1), 60);
            cout << "<" << endl;

            CHECK(res == v.nth(1));
            CHECK(v.size() == 6);
            CHECK(v[0] == 10);
            CHECK(v[1] == 60);
            CHECK(v[2] == 50);
            CHECK(v[3] == 40);
            CHECK(v[4] == 20);
            CHECK(v[5] == 30);
        }
    }

    cout << "Test non-modifying member functions on non-empty container." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        v.emplace(v.end(), 10);
        v.emplace(v.end(), 20);
        v.emplace(v.end(), 30);

        {
            auto it = v.begin();
            CHECK(*it == 10); ++it;
            CHECK(*it == 20); ++it;
            CHECK(*it == 30); ++it;
            CHECK(it == v.end());
        }

        {
            auto it = v.cbegin();
            CHECK(*it == 10); ++it;
            CHECK(*it == 20); ++it;
            CHECK(*it == 30); ++it;
            CHECK(it == v.cend());
        }

        {
            auto it = v.rbegin();
            CHECK(*it == 30); ++it;
            CHECK(*it == 20); ++it;
            CHECK(*it == 10); ++it;
            CHECK(it == v.rend());
        }

        {
            auto it = v.crbegin();
            CHECK(*it == 30); ++it;
            CHECK(*it == 20); ++it;
            CHECK(*it == 10); ++it;
            CHECK(it == v.crend());
        }

        {
            CHECK(*v.nth(0) == 10);
            CHECK(*v.nth(1) == 20);
            CHECK(*v.nth(2) == 30);
            CHECK(v.nth(3) == v.end());
        }

        {
            CHECK(std::next(v.begin(), 0) == v.nth(0));
            CHECK(std::next(v.begin(), 1) == v.nth(1));
            CHECK(std::next(v.begin(), 2) == v.nth(2));
        }

        {
            CHECK(std::next(v.cbegin(), 0) == v.nth(0));
            CHECK(std::next(v.cbegin(), 1) == v.nth(1));
            CHECK(std::next(v.cbegin(), 2) == v.nth(2));
        }

        {
            CHECK(v.index_of(v.nth(0)) == 0);
            CHECK(v.index_of(v.nth(1)) == 1);
            CHECK(v.index_of(v.nth(2)) == 2);
        }

        {
            CHECK(v.at(0) == 10);
            CHECK(v.at(1) == 20);
            CHECK(v.at(2) == 30);

            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);

            CHECK(v.front() == 10);

            CHECK(v.back() == 30);
        }

        {
            auto data = v.data();
            CHECK(*data == 10); ++data;
            CHECK(*data == 20); ++data;
            CHECK(*data == 30); ++data;
        }
    }

    cout << "Test insert(const_iterator, const T& value)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            const xint i(10);

            cout << ">" << endl;
            auto res = v.emplace(v.end(), i);
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }
    }

    cout << "Test insert(const_iterator, T&& value)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            xint i(10);

            cout << ">" << endl;
            auto res = v.emplace(v.end(), std::move(i));
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(i == -10);
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }
    }

    cout << "Test insert(const_iterator, size_type, const T&)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(0), 3, xint(10));
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 10);
            CHECK(v[2] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(1), 3, xint(20));
            cout << "<" << endl;

            CHECK(res == v.nth(1));
            CHECK(v.size() == 6);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 20);
            CHECK(v[3] == 20);
            CHECK(v[4] == 10);
            CHECK(v[5] == 10);
        }
    }

    cout << "Test insert(const_iterator, InputIt, InputIt)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            std::istringstream iss("10 20 30 40");

            cout << ">" << endl;
            auto res = v.insert
            (
                v.nth(0),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }
    }

    cout << "Test insert(const_iterator, ForwardIt, ForwardIt)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            const std::vector<xint> data({10, 20, 30, 40});

            cout << ">" << endl;
            auto res = v.insert(v.begin(), data.begin(), data.end());
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }

        {
            const std::vector<xint> data({50, 60});

            cout << ">" << endl;
            auto res = v.insert(v.nth(2), data.begin(), data.end());
            cout << "<" << endl;

            CHECK(res == v.nth(2));
            CHECK(v.size() == 6);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 50);
            CHECK(v[3] == 60);
            CHECK(v[4] == 30);
            CHECK(v[5] == 40);
        }
    }

    cout << "Test insert(const_iterator, MoveIterator, MoveIterator)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            std::vector<xint> data({10, 20, 30, 40});

            cout << ">" << endl;
            auto res = v.insert
            (
                v.begin(),
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(data[0] == -10);
            CHECK(data[1] == -20);
            CHECK(data[2] == -30);
            CHECK(data[3] == -40);
            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }
    }

    cout << "Test insert(const_iterator, std::initializer_list)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        cout << ">" << endl;
        auto res = v.insert(v.nth(0), {10, 20, 30, 40});
        cout << "<" << endl;

        CHECK(res == v.nth(0));
        CHECK(v.size() == 4);
        CHECK(v[0] == 10);
        CHECK(v[1] == 20);
        CHECK(v[2] == 30);
        CHECK(v[3] == 40);
    }

    cout << "Test emplace_back(Args&&...)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            cout << "<" << endl;

            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        {
            xint i(20);

            cout << ">" << endl;
            v.emplace_back(std::move(i));
            cout << "<" << endl;

            CHECK(i == -20);
            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }
    }

    cout << "Test push_back(const T&)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            const xint i(10);

            cout << ">" << endl;
            v.push_back(i);
            cout << "<" << endl;

            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        {
            const xint i(20);

            cout << ">" << endl;
            v.push_back(i);
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }
    }

    cout << "Test push_back(T&&)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            xint i(10);

            cout << ">" << endl;
            v.push_back(std::move(i));
            cout << "<" << endl;

            CHECK(i == -10);
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        {
            xint i(20);

            cout << ">" << endl;
            v.push_back(std::move(i));
            cout << "<" << endl;

            CHECK(i == -20);
            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }
    }

    cout << "Test clear()." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            v.emplace_back(40);
            cout << "<" << endl;

            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }

        {
            cout << ">" << endl;
            v.clear();
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }

        {
            cout << ">" << endl;
            v.emplace_back(50);
            v.emplace_back(60);
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 50);
            CHECK(v[1] == 60);
        }

        {
            cout << ">" << endl;
            v.clear();
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }
    }

    cout << "Test pop_back()." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        {
            cout << ">" << endl;
            v.pop_back();
            cout << "<" << endl;

            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        {
            cout << ">" << endl;
            v.pop_back();
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }

        {
            cout << ">" << endl;
            v.emplace_back(50);
            cout << "<" << endl;

            CHECK(v.size() == 1);
            CHECK(v[0] == 50);
        }

        {
            cout << ">" << endl;
            v.pop_back();
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }
    }

    cout << "Test erase(const_iterator)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            v.emplace_back(40);
            cout << "<" << endl;

            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(1));
            cout << "<" << endl;

            CHECK(res == v.nth(1));
            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 30);
            CHECK(v[2] == 40);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(0));
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 2);
            CHECK(v[0] == 30);
            CHECK(v[1] == 40);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(1));
            cout << "<" << endl;

            CHECK(res == v.nth(1));
            CHECK(v.size() == 1);
            CHECK(v[0] == 30);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(0));
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 0);
        }
    }

    cout << "Test erase(const_iterator, const_iterator)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            v.emplace_back(40);
            v.emplace_back(50);
            cout << "<" << endl;

            CHECK(v.size() == 5);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
        }

        {
            cout << ">" << endl;
            // Erase nothing
            auto res = v.erase(v.nth(3), v.nth(3));
            cout << "<" << endl;

            CHECK(res == v.nth(3));
            CHECK(v.size() == 5);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(1), v.nth(3));
            cout << "<" << endl;

            CHECK(res == v.nth(1));
            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 40);
            CHECK(v[2] == 50);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(0), v.nth(1));
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 2);
            CHECK(v[0] == 40);
            CHECK(v[1] == 50);
        }
    }

    cout << "Test resize(size_type)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.resize(3);
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.resize(6);
            cout << "<" << endl;

            CHECK(v.size() == 6);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[4] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[5] == SFL_MY_INT_DEFAULT_VALUE);
        }

        {
            cout << ">" << endl;
            v.resize(2);
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        {
            cout << ">" << endl;
            v.resize(4);
            cout << "<" << endl;

            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[3] == SFL_MY_INT_DEFAULT_VALUE);
        }

        {
            cout << ">" << endl;
            v.resize(0);
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }

        {
            cout << ">" << endl;
            v.resize(2);
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[1] == SFL_MY_INT_DEFAULT_VALUE);
        }
    }

    cout << "Test resize(size_type, const T&)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.resize(3, 11);
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.resize(6, 40);
            cout << "<" << endl;

            CHECK(v.size() == 6);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 40);
            CHECK(v[5] == 40);
        }

        {
            cout << ">" << endl;
            v.resize(2, 11);
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        {
            cout << ">" << endl;
            v.resize(4, 50);
            cout << "<" << endl;

            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 50);
            CHECK(v[3] == 50);
        }

        {
            cout << ">" << endl;
            v.resize(0, 60);
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }

        {
            cout << ">" << endl;
            v.resize(2, 70);
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 70);
            CHECK(v[1] == 70);
        }
    }

    cout << "Test swap(compact_vector&)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2;

        cout << ">" << endl;
        v1.emplace_back(10);
        v1.emplace_back(11);
        v1.emplace_back(12);
        cout << "<" << endl;

        cout << ">" << endl;
        v2.emplace_back(20);
        v2.emplace_back(21);
        v2.emplace_back(22);
        v2.emplace_back(23);
        cout << "<" << endl;

        CHECK(v1.size() == 3);
        CHECK(*v1.nth(0) == 10);
        CHECK(*v1.nth(1) == 11);
        CHECK(*v1.nth(2) == 12);

        CHECK(v2.size() == 4);
        CHECK(*v2.nth(0) == 20);
        CHECK(*v2.nth(1) == 21);
        CHECK(*v2.nth(2) == 22);
        CHECK(*v2.nth(3) == 23);

        cout << ">" << endl;
        v1.swap(v2);
        cout << "<" << endl;

        CHECK(v1.size() == 4);
        CHECK(*v1.nth(0) == 20);
        CHECK(*v1.nth(1) == 21);
        CHECK(*v1.nth(2) == 22);
        CHECK(*v1.nth(3) == 23);

        CHECK(v2.size() == 3);
        CHECK(*v2.nth(0) == 10);
        CHECK(*v2.nth(1) == 11);
        CHECK(*v2.nth(2) == 12);

        cout << ">" << endl;
        v1.swap(v2);
        cout << "<" << endl;

        CHECK(v1.size() == 3);
        CHECK(*v1.nth(0) == 10);
        CHECK(*v1.nth(1) == 11);
        CHECK(*v1.nth(2) == 12);

        CHECK(v2.size() == 4);
        CHECK(*v2.nth(0) == 20);
        CHECK(*v2.nth(1) == 21);
        CHECK(*v2.nth(2) == 22);
        CHECK(*v2.nth(3) == 23);
    }

    cout << "Test at(const T&)." << endl;
    {
        #ifndef SFL_NO_EXCEPTIONS
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        const auto& rv = v;

        {
            v.emplace_back(10);

            CHECK(v.size() == 1);
        }

        {
            bool exception_caught = false;

            try
            {
                CHECK(v.at(0) == 10);
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
                CHECK(rv.at(0) == 10);
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
                CHECK(v.at(15) == 1234);
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
                CHECK(rv.at(15) == 1234);
            }
            catch (...)
            {
                exception_caught = true;
            }

            CHECK(exception_caught);
        }
        #endif
    }

    cout << "Test constructor()." << endl;
    {
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2(alloc);

        CHECK(v1.size() == 0);
        CHECK(v2.size() == 0);
    }

    cout << "Test constructor(size_type)." << endl;
    {
        TPARAM_ALLOCATOR<xint> alloc;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1(3);
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2(3, alloc);
        cout << "<" << endl;

        CHECK(v1.size() == 3);
        CHECK(v2.size() == 3);

        CHECK(v1[0] == SFL_MY_INT_DEFAULT_VALUE);
        CHECK(v1[1] == SFL_MY_INT_DEFAULT_VALUE);
        CHECK(v1[2] == SFL_MY_INT_DEFAULT_VALUE);

        CHECK(v2[0] == SFL_MY_INT_DEFAULT_VALUE);
        CHECK(v2[1] == SFL_MY_INT_DEFAULT_VALUE);
        CHECK(v2[2] == SFL_MY_INT_DEFAULT_VALUE);
    }

    cout << "Test constructor(size_type, const T&)." << endl;
    {
        TPARAM_ALLOCATOR<xint> alloc;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1(3, 42);
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2(3, 42, alloc);
        cout << "<" << endl;

        CHECK(v1.size() == 3);
        CHECK(v2.size() == 3);

        CHECK(v1[0] == 42);
        CHECK(v1[1] == 42);
        CHECK(v1[2] == 42);

        CHECK(v2[0] == 42);
        CHECK(v2[1] == 42);
        CHECK(v2[2] == 42);
    }

    cout << "Test constructor(InputIt, InputIt)." << endl;
    {
        TPARAM_ALLOCATOR<xint> alloc;

        std::istringstream iss1("10 20 30 40");
        std::istringstream iss2("10 20 30 40");

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1
        (
            (std::istream_iterator<int>(iss1)),
            (std::istream_iterator<int>())
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2
        (
            (std::istream_iterator<int>(iss2)),
            (std::istream_iterator<int>()),
            alloc
        );
        cout << "<" << endl;

        CHECK(v1.size() == 4);
        CHECK(v2.size() == 4);

        CHECK(v1[0] == 10);
        CHECK(v1[1] == 20);
        CHECK(v1[2] == 30);
        CHECK(v1[3] == 40);

        CHECK(v2[0] == 10);
        CHECK(v2[1] == 20);
        CHECK(v2[2] == 30);
        CHECK(v2[3] == 40);
    }

    cout << "Test constructor(ForwardIt, ForwardIt)." << endl;
    {
        TPARAM_ALLOCATOR<xint> alloc;

        const std::vector<xint> data({10, 20, 30, 40});

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1(data.begin(), data.end());
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2(data.begin(), data.end(), alloc);
        cout << "<" << endl;

        CHECK(v1.size() == 4);
        CHECK(v2.size() == 4);

        CHECK(v1[0] == 10);
        CHECK(v1[1] == 20);
        CHECK(v1[2] == 30);
        CHECK(v1[3] == 40);

        CHECK(v2[0] == 10);
        CHECK(v2[1] == 20);
        CHECK(v2[2] == 30);
        CHECK(v2[3] == 40);
    }

    cout << "Test constructor(MoveIterator, MoveIterator)." << endl;
    {
        TPARAM_ALLOCATOR<xint> alloc;

        std::vector<xint> data1({10, 20, 30, 40});
        std::vector<xint> data2({10, 20, 30, 40});

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1
        (
            std::make_move_iterator(data1.begin()),
            std::make_move_iterator(data1.end())
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2
        (
            std::make_move_iterator(data2.begin()),
            std::make_move_iterator(data2.end()),
            alloc
        );
        cout << "<" << endl;

        CHECK(data1[0] == -10);
        CHECK(data1[1] == -20);
        CHECK(data1[2] == -30);
        CHECK(data1[3] == -40);

        CHECK(data2[0] == -10);
        CHECK(data2[1] == -20);
        CHECK(data2[2] == -30);
        CHECK(data2[3] == -40);

        CHECK(v1.size() == 4);
        CHECK(v2.size() == 4);

        CHECK(v1[0] == 10);
        CHECK(v1[1] == 20);
        CHECK(v1[2] == 30);
        CHECK(v1[3] == 40);

        CHECK(v2[0] == 10);
        CHECK(v2[1] == 20);
        CHECK(v2[2] == 30);
        CHECK(v2[3] == 40);
    }

    cout << "Test constructor(std::initializer_list)." << endl;
    {
        TPARAM_ALLOCATOR<xint> alloc;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30, 40});
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2({10, 20, 30, 40}, alloc);
        cout << "<" << endl;

        CHECK(v1.size() == 4);
        CHECK(v2.size() == 4);

        CHECK(v1[0] == 10);
        CHECK(v1[1] == 20);
        CHECK(v1[2] == 30);
        CHECK(v1[3] == 40);

        CHECK(v2[0] == 10);
        CHECK(v2[1] == 20);
        CHECK(v2[2] == 30);
        CHECK(v2[3] == 40);
    }

    cout << "Test constructor(const compact_vector&)." << endl;
    {
        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30, 40, 50});
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2(v1);
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v3(v1, TPARAM_ALLOCATOR<xint>());
        cout << "<" << endl;

        CHECK(v1.size() == 5);
        CHECK(v1[0] == 10);
        CHECK(v1[1] == 20);
        CHECK(v1[2] == 30);
        CHECK(v1[3] == 40);
        CHECK(v1[4] == 50);

        CHECK(v2.size() == 5);
        CHECK(v2[0] == 10);
        CHECK(v2[1] == 20);
        CHECK(v2[2] == 30);
        CHECK(v2[3] == 40);
        CHECK(v2[4] == 50);

        CHECK(v3.size() == 5);
        CHECK(v3[0] == 10);
        CHECK(v3[1] == 20);
        CHECK(v3[2] == 30);
        CHECK(v3[3] == 40);
        CHECK(v3[4] == 50);
    }

    cout << "Test constructor(compact_vector&&)." << endl;
    {
        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30, 40, 50});
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2(std::move(v1));
        cout << "<" << endl;

        // v1 is in a valid but unspecified state

        CHECK(v2.size() == 5);
        CHECK(v2[0] == 10);
        CHECK(v2[1] == 20);
        CHECK(v2[2] == 30);
        CHECK(v2[3] == 40);
        CHECK(v2[4] == 50);

        cout << ">" << endl;
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v3(std::move(v2), TPARAM_ALLOCATOR<xint>());
        cout << "<" << endl;

        // v2 is in a valid but unspecified state

        CHECK(v3.size() == 5);
        CHECK(v3[0] == 10);
        CHECK(v3[1] == 20);
        CHECK(v3[2] == 30);
        CHECK(v3[3] == 40);
        CHECK(v3[4] == 50);
    }

    cout << "Test assign(size_type, const T&)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.assign(3, 10);
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 10);
            CHECK(v[2] == 10);
        }

        {
            cout << ">" << endl;
            v.assign(3, 20);
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 20);
            CHECK(v[1] == 20);
            CHECK(v[2] == 20);
        }

        {
            cout << ">" << endl;
            v.assign(2, 30);
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 30);
            CHECK(v[1] == 30);
        }

        {
            cout << ">" << endl;
            v.assign(4, 40);
            cout << "<" << endl;

            CHECK(v.size() == 4);
            CHECK(v[0] == 40);
            CHECK(v[1] == 40);
            CHECK(v[2] == 40);
            CHECK(v[3] == 40);
        }

        {
            cout << ">" << endl;
            v.assign(0, 50);
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }
    }

    cout << "Test assign(InputIt, InputIt)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            std::istringstream iss("10 20 30");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            std::istringstream iss("40 50 60");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 40);
            CHECK(v[1] == 50);
            CHECK(v[2] == 60);
        }

        {
            std::istringstream iss("70 80");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 70);
            CHECK(v[1] == 80);
        }

        {
            std::istringstream iss("");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }
    }

    cout << "Test assign(ForwardIt, ForwardIt)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            const std::vector<int> data({10, 20, 30});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            const std::vector<int> data({40, 50, 60});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 40);
            CHECK(v[1] == 50);
            CHECK(v[2] == 60);
        }

        {
            const std::vector<int> data({70, 80});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 70);
            CHECK(v[1] == 80);
        }

        {
            const std::vector<int> data;

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }
    }

    cout << "Test assign(MoveIterator, MoveIterator)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            std::vector<xint> data({10, 20, 30});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            CHECK(data[0] == -10);
            CHECK(data[1] == -20);
            CHECK(data[2] == -30);
            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            std::vector<xint> data({40, 50, 60});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            CHECK(data[0] == -40);
            CHECK(data[1] == -50);
            CHECK(data[2] == -60);
            CHECK(v.size() == 3);
            CHECK(v[0] == 40);
            CHECK(v[1] == 50);
            CHECK(v[2] == 60);
        }

        {
            std::vector<xint> data({70, 80});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            CHECK(data[0] == -70);
            CHECK(data[1] == -80);
            CHECK(v.size() == 2);
            CHECK(v[0] == 70);
            CHECK(v[1] == 80);
        }
    }

    cout << "Test assign(std::initializer_list)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.assign({10, 20, 30});
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.assign({40, 50, 60});
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 40);
            CHECK(v[1] == 50);
            CHECK(v[2] == 60);
        }

        {
            cout << ">" << endl;
            v.assign({70, 80});
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 70);
            CHECK(v[1] == 80);
        }

        {
            cout << ">" << endl;
            v.assign({});
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }
    }

    cout << "Test operator=(const compact_vector&)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30});
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2({40, 50});

        CHECK(v1.size() == 3);
        CHECK(v2.size() == 2);

        cout << ">" << endl;
        v1 = v2;
        cout << "<" << endl;

        CHECK(v1.size() == 2);
        CHECK(v1[0] == 40);
        CHECK(v1[1] == 50);

        CHECK(v2.size() == 2);
        CHECK(v2[0] == 40);
        CHECK(v2[1] == 50);
    }

    cout << "Test operator=(compact_vector&&)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30});
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2({40, 50});

        CHECK(v1.size() == 3);
        CHECK(v2.size() == 2);

        cout << ">" << endl;
        v1 = std::move(v2);
        cout << "<" << endl;

        CHECK(v1.size() == 2);
        CHECK(v1[0] == 40);
        CHECK(v1[1] == 50);

        // v2 is in a valid but unspecified state

        cout << ">" << endl;
        v2 = std::move(v1);
        cout << "<" << endl;

        // v1 is in a valid but unspecified state

        CHECK(v2.size() == 2);
        CHECK(v2[0] == 40);
        CHECK(v2[1] == 50);
    }

    cout << "Test operator=(std::initializer_list)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30});
        CHECK(v1.size() == 3);

        cout << ">" << endl;
        v1 = {40, 50, 60};
        cout << "<" << endl;

        CHECK(v1.size() == 3);
        CHECK(v1[0] == 40);
        CHECK(v1[1] == 50);
        CHECK(v1[2] == 60);
    }

    cout << "Test non-member comparison operators." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30});
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2({10, 20, 30, 40});

        CHECK(v1 == v1);
        CHECK(!(v1 != v1));
        CHECK(!(v1 == v2));
        CHECK(v1 != v2);
        CHECK(!(v1 < v1));
        CHECK(v1 < v2);
        CHECK(v1 <= v1);
        CHECK(v1 >= v1);
        CHECK(v1 <= v2);
        CHECK(v2 > v1);
        CHECK(v2 >= v1);
        CHECK(v2 >= v2);
    }

    cout << "Test non-member swap." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1({10, 11, 12});
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v2({20, 21, 22});

        using std::swap;
        swap(v1, v2);
    }

    cout << "Test non-member erase(compact_vector&, const U&)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1({10, 20, 20, 30, 30, 30});

        CHECK(v1.size() == 6);
        CHECK(v1[0] == 10);
        CHECK(v1[1] == 20);
        CHECK(v1[2] == 20);
        CHECK(v1[3] == 30);
        CHECK(v1[4] == 30);
        CHECK(v1[5] == 30);

        {
            cout << ">" << endl;
            auto res = erase(v1, 42);
            cout << "<" << endl;

            CHECK(res == 0);
            CHECK(v1.size() == 6);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 20);
            CHECK(v1[2] == 20);
            CHECK(v1[3] == 30);
            CHECK(v1[4] == 30);
            CHECK(v1[5] == 30);
        }

        {
            cout << ">" << endl;
            auto res = erase(v1, 20);
            cout << "<" << endl;

            CHECK(res == 2);
            CHECK(v1.size() == 4);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 30);
            CHECK(v1[2] == 30);
            CHECK(v1[3] == 30);
        }
    }

    cout << "Test non-member erase_if(compact_vector&, Predicate)." << endl;
    {
        sfl::compact_vector<xint, TPARAM_ALLOCATOR<xint>> v1({10, 20, 20, 30, 30, 30});

        CHECK(v1.size() == 6);
        CHECK(v1[0] == 10);
        CHECK(v1[1] == 20);
        CHECK(v1[2] == 20);
        CHECK(v1[3] == 30);
        CHECK(v1[4] == 30);
        CHECK(v1[5] == 30);

        {
            cout << ">" << endl;
            auto res = erase_if(v1, [](const xint& x){ return x == 42; });
            cout << "<" << endl;

            CHECK(res == 0);
            CHECK(v1.size() == 6);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 20);
            CHECK(v1[2] == 20);
            CHECK(v1[3] == 30);
            CHECK(v1[4] == 30);
            CHECK(v1[5] == 30);
        }

        {
            cout << ">" << endl;
            auto res = erase_if(v1, [](const xint& x){ return x == 20; });
            cout << "<" << endl;

            CHECK(res == 2);
            CHECK(v1.size() == 4);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 30);
            CHECK(v1[2] == 30);
            CHECK(v1[3] == 30);
        }
    }
}
