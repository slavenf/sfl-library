//
// g++ -Wall -Wextra -Wpedantic -std=c++11 -g -I ../include -o test.out test_small_vector.cpp
// valgrind --leak-check=full ./test.out
//

#undef NDEBUG
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include <sfl/small_vector.hpp>

#include "MyInt.hpp"
#include "Person.hpp"

#include "statefull_alloc.hpp"
#include "stateless_alloc.hpp"
#include "stateless_alloc_no_prop.hpp"
#include "stateless_fancy_alloc.hpp"

#ifndef TP_ALLOC
//#define TP_ALLOC std::allocator
//#define TP_ALLOC sfl::statefull_alloc
//#define TP_ALLOC sfl::stateless_alloc
//#define TP_ALLOC sfl::stateless_alloc_no_prop
#define TP_ALLOC sfl::stateless_fancy_alloc
#endif

int main()
{
    using std::cout;
    using std::endl;

    cout << "Create empty containers and test all non-modifying "
            "member functions." << endl;
    {
        sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v1;
        const sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v2;
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v3;
        const sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v4;

        assert(v1.empty());
        assert(v2.empty());
        assert(v3.empty());
        assert(v4.empty());

        assert(v1.size() == 0);
        assert(v2.size() == 0);
        assert(v3.size() == 0);
        assert(v4.size() == 0);

        assert(v1.capacity() == 0);
        assert(v2.capacity() == 0);
        assert(v3.capacity() == 5);
        assert(v4.capacity() == 5);

        assert(v1.begin() == v1.end());
        assert(v2.begin() == v2.end());
        assert(v3.begin() == v3.end());
        assert(v4.begin() == v4.end());

        assert(v1.cbegin() == v1.cend());
        assert(v2.cbegin() == v2.cend());
        assert(v3.cbegin() == v3.cend());
        assert(v4.cbegin() == v4.cend());

        assert(v1.begin() == v1.cbegin());
        assert(v2.begin() == v2.cbegin());
        assert(v3.begin() == v3.cbegin());
        assert(v4.begin() == v4.cbegin());

        assert(v1.rbegin() == v1.rend());
        assert(v2.rbegin() == v2.rend());
        assert(v3.rbegin() == v3.rend());
        assert(v4.rbegin() == v4.rend());

        assert(v1.crbegin() == v1.crend());
        assert(v2.crbegin() == v2.crend());
        assert(v3.crbegin() == v3.crend());
        assert(v4.crbegin() == v4.crend());

        assert(v1.rbegin() == v1.crbegin());
        assert(v2.rbegin() == v2.crbegin());
        assert(v3.rbegin() == v3.crbegin());
        assert(v4.rbegin() == v4.crbegin());

        assert(v1.begin() == v1.nth(0));
        assert(v2.begin() == v2.nth(0));
        assert(v3.begin() == v3.nth(0));
        assert(v4.begin() == v4.nth(0));

        assert(v1.cbegin() == v1.nth(0));
        assert(v2.cbegin() == v2.nth(0));
        assert(v3.cbegin() == v3.nth(0));
        assert(v4.cbegin() == v4.nth(0));

        assert(v1.index_of(v1.nth(0)) == 0);
        assert(v2.index_of(v2.nth(0)) == 0);
        assert(v3.index_of(v3.nth(0)) == 0);
        assert(v4.index_of(v4.nth(0)) == 0);

        auto a1 = v1.get_allocator(); (void)a1;
        auto a2 = v2.get_allocator(); (void)a2;
        auto a3 = v3.get_allocator(); (void)a3;
        auto a4 = v4.get_allocator(); (void)a4;
    }

    cout << "Test emplace(const_iterator, Args&&...) (N > 0)." << endl;
    {
        sfl::small_vector<MyInt, 2, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            // Insert at the end (no reallocation)
            auto res = v.emplace(v.end(), 10);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 1);
            assert(v.capacity() == 2);
            assert(v[0] == 10);
        }

        {
            cout << ">" << endl;
            // Insert at the end (no reallocation)
            auto res = v.emplace(v.end(), 20);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 2);
            assert(v.capacity() == 2);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }

        {
            cout << ">" << endl;
            // Insert at the end (with reallocation)
            auto res = v.emplace(v.end(), 30);
            cout << "<" << endl;

            assert(res == v.nth(2));
            assert(v.size() == 3);
            assert(v.capacity() == 4);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            cout << ">" << endl;
            // Insert at middle (no reallocation)
            auto res = v.emplace(v.nth(1), 40);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 4);
            assert(v.capacity() == 4);
            assert(v[0] == 10);
            assert(v[1] == 40);
            assert(v[2] == 20);
            assert(v[3] == 30);
        }

        {
            cout << ">" << endl;
            // Insert at middle (with reallocation)
            auto res = v.emplace(v.nth(1), 50);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 5);
            assert(v.capacity() == 8);
            assert(v[0] == 10);
            assert(v[1] == 50);
            assert(v[2] == 40);
            assert(v[3] == 20);
            assert(v[4] == 30);
        }

        {
            cout << ">" << endl;
            // Insert at middle (no reallocation)
            auto res = v.emplace(v.nth(1), 60);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 6);
            assert(v.capacity() == 8);
            assert(v[0] == 10);
            assert(v[1] == 60);
            assert(v[2] == 50);
            assert(v[3] == 40);
            assert(v[4] == 20);
            assert(v[5] == 30);
        }
    }

    cout << "Test emplace(const_iterator, Args&&...) (N == 0)." << endl;
    {
        sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            // Insert at the end (with reallocation)
            auto res = v.emplace(v.end(), 10);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 1);
            assert(v.capacity() == 1);
            assert(v[0] == 10);
        }

        {
            cout << ">" << endl;
            // Insert at the end (with reallocation)
            auto res = v.emplace(v.end(), 20);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 2);
            assert(v.capacity() == 2);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }

        {
            cout << ">" << endl;
            // Insert at the end (with reallocation)
            auto res = v.emplace(v.end(), 30);
            cout << "<" << endl;

            assert(res == v.nth(2));
            assert(v.size() == 3);
            assert(v.capacity() == 4);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            cout << ">" << endl;
            // Insert at middle (no reallocation)
            auto res = v.emplace(v.nth(1), 40);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 4);
            assert(v.capacity() == 4);
            assert(v[0] == 10);
            assert(v[1] == 40);
            assert(v[2] == 20);
            assert(v[3] == 30);
        }

        {
            cout << ">" << endl;
            // Insert at middle (with reallocation)
            auto res = v.emplace(v.nth(1), 50);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 5);
            assert(v.capacity() == 8);
            assert(v[0] == 10);
            assert(v[1] == 50);
            assert(v[2] == 40);
            assert(v[3] == 20);
            assert(v[4] == 30);
        }

        {
            cout << ">" << endl;
            // Insert at middle (no reallocation)
            auto res = v.emplace(v.nth(1), 60);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 6);
            assert(v.capacity() == 8);
            assert(v[0] == 10);
            assert(v[1] == 60);
            assert(v[2] == 50);
            assert(v[3] == 40);
            assert(v[4] == 20);
            assert(v[5] == 30);
        }
    }

    cout << "Test non-modifying member functions on non-empty container." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        v.emplace(v.end(), 10);
        v.emplace(v.end(), 20);
        v.emplace(v.end(), 30);

        {
            auto it = v.begin();
            assert(*it == 10); ++it;
            assert(*it == 20); ++it;
            assert(*it == 30); ++it;
            assert(it == v.end());
        }

        {
            auto it = v.cbegin();
            assert(*it == 10); ++it;
            assert(*it == 20); ++it;
            assert(*it == 30); ++it;
            assert(it == v.cend());
        }

        {
            auto it = v.rbegin();
            assert(*it == 30); ++it;
            assert(*it == 20); ++it;
            assert(*it == 10); ++it;
            assert(it == v.rend());
        }

        {
            auto it = v.crbegin();
            assert(*it == 30); ++it;
            assert(*it == 20); ++it;
            assert(*it == 10); ++it;
            assert(it == v.crend());
        }

        {
            assert(*v.nth(0) == 10);
            assert(*v.nth(1) == 20);
            assert(*v.nth(2) == 30);
            assert(v.nth(3) == v.end());
        }

        {
            assert(std::next(v.begin(), 0) == v.nth(0));
            assert(std::next(v.begin(), 1) == v.nth(1));
            assert(std::next(v.begin(), 2) == v.nth(2));
        }

        {
            assert(std::next(v.cbegin(), 0) == v.nth(0));
            assert(std::next(v.cbegin(), 1) == v.nth(1));
            assert(std::next(v.cbegin(), 2) == v.nth(2));
        }

        {
            assert(v.nth(0) < v.nth(1));
            assert(v.nth(0) < v.nth(2));
            assert(v.nth(0) < v.nth(3));

            assert(v.nth(1) < v.nth(2));
            assert(v.nth(1) < v.nth(3));

            assert(v.nth(2) < v.nth(3));
        }

        {
            assert(v.index_of(v.nth(0)) == 0);
            assert(v.index_of(v.nth(1)) == 1);
            assert(v.index_of(v.nth(2)) == 2);
        }

        {
            assert(v.at(0) == 10);
            assert(v.at(1) == 20);
            assert(v.at(2) == 30);
        }

        {
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            assert(v.front() == 10);
        }

        {
            assert(v.back() == 30);
        }

        {
            auto data = v.data();
            assert(*data == 10); ++data;
            assert(*data == 20); ++data;
            assert(*data == 30); ++data;
        }
    }

    cout << "Test insert(const_iterator, const T&)." << endl;
    {
        sfl::small_vector<MyInt, 2, TP_ALLOC<MyInt>> v;

        {
            const MyInt i(10);

            cout << ">" << endl;
            // Insert at the end (no reallocation)
            auto res = v.insert(v.end(), i);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 1);
            assert(v.capacity() == 2);
            assert(v[0] == 10);
        }
    }

    cout << "Test insert(const_iterator, T&&)." << endl;
    {
        sfl::small_vector<MyInt, 2, TP_ALLOC<MyInt>> v;

        {
            MyInt i(10);

            cout << ">" << endl;
            // Insert at the end (no reallocation)
            auto res = v.insert(v.end(), std::move(i));
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(i == -10);
            assert(v.size() == 1);
            assert(v.capacity() == 2);
            assert(v[0] == 10);
        }
    }

    cout << "Test insert(const_iterator, size_type, const T&)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(0), 3, MyInt(10));
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 3);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
            assert(v[1] == 10);
            assert(v[2] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(1), 3, MyInt(20));
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 6);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 20);
            assert(v[3] == 20);
            assert(v[4] == 10);
            assert(v[5] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(1), 2, MyInt(30));
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 8);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
            assert(v[1] == 30);
            assert(v[2] == 30);
            assert(v[3] == 20);
            assert(v[4] == 20);
            assert(v[5] == 20);
            assert(v[6] == 10);
            assert(v[7] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(1), 4, MyInt(40));
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 12);
            assert(v.capacity() == 16);
            assert(v[0]  == 10);
            assert(v[1]  == 40);
            assert(v[2]  == 40);
            assert(v[3]  == 40);
            assert(v[4]  == 40);
            assert(v[5]  == 30);
            assert(v[6]  == 30);
            assert(v[7]  == 20);
            assert(v[8]  == 20);
            assert(v[9]  == 20);
            assert(v[10] == 10);
            assert(v[11] == 10);
        }
    }

    cout << "Test insert(const_iterator, InputIt, InputIt)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

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

            assert(res == v.nth(0));
            assert(v.size() == 4);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
        }
    }

    cout << "Test insert(const_iterator, ForwardIt, ForwardIt)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        {
            const std::vector<MyInt> data({10, 20, 30, 40});

            cout << ">" << endl;
            auto res = v.insert(v.begin(), data.begin(), data.end());
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 4);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
        }

        {
            const std::vector<MyInt> data({50, 60});

            cout << ">" << endl;
            auto res = v.insert(v.nth(2), data.begin(), data.end());
            cout << "<" << endl;

            assert(res == v.nth(2));
            assert(v.size() == 6);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 50);
            assert(v[3] == 60);
            assert(v[4] == 30);
            assert(v[5] == 40);
        }
    }

    cout << "Test insert(const_iterator, MoveIterator, MoveIterator)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        {
            std::vector<MyInt> data({10, 20, 30, 40});

            cout << ">" << endl;
            auto res = v.insert
            (
                v.begin(),
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(data[0] == -10);
            assert(data[1] == -20);
            assert(data[2] == -30);
            assert(data[3] == -40);
            assert(v.size() == 4);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
        }
    }

    cout << "Test insert(const_iterator, std::initializer_list)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        cout << ">" << endl;
        auto res = v.insert(v.nth(0), {10, 20, 30, 40});
        cout << "<" << endl;

        assert(res == v.nth(0));
        assert(v.size() == 4);
        assert(v[0] == 10);
        assert(v[1] == 20);
        assert(v[2] == 30);
        assert(v[3] == 40);
    }

    cout << "Test emplace_back(Args&&...)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            cout << "<" << endl;

            assert(v.size() == 1);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            v.emplace_back(std::move(i));
            cout << "<" << endl;

            assert(i == -20);
            assert(v.size() == 2);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }
    }

    cout << "Test push_back(const T&)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        {
            const MyInt i(10);

            cout << ">" << endl;
            v.push_back(i);
            cout << "<" << endl;

            assert(v.size() == 1);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
        }

        {
            const MyInt i(20);

            cout << ">" << endl;
            v.push_back(i);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }
    }

    cout << "Test push_back(T&&)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        {
            MyInt i(10);

            cout << ">" << endl;
            v.push_back(std::move(i));
            cout << "<" << endl;

            assert(i == -10);
            assert(v.size() == 1);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            v.push_back(std::move(i));
            cout << "<" << endl;

            assert(i == -20);
            assert(v.size() == 2);
            assert(v.capacity() == 10);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }
    }

    cout << "Test pop_back()." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            v.emplace_back(40);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
        }

        {
            cout << ">" << endl;
            v.pop_back();
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.pop_back();
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }

        {
            cout << ">" << endl;
            v.emplace_back(50);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 50);
        }

        {
            cout << ">" << endl;
            v.pop_back();
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }

        {
            cout << ">" << endl;
            v.pop_back();
            cout << "<" << endl;

            assert(v.size() == 1);
            assert(v[0] == 10);
        }

        {
            cout << ">" << endl;
            v.pop_back();
            cout << "<" << endl;

            assert(v.size() == 0);
        }
    }

    cout << "Test clear()." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            v.emplace_back(40);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
        }

        {
            cout << ">" << endl;
            v.clear();
            cout << "<" << endl;

            assert(v.size() == 0);
        }

        {
            cout << ">" << endl;
            v.emplace_back(50);
            v.emplace_back(60);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 50);
            assert(v[1] == 60);
        }

        {
            cout << ">" << endl;
            v.clear();
            cout << "<" << endl;

            assert(v.size() == 0);
        }
    }

    cout << "Test erase(const_iterator)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            v.emplace_back(40);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(1));
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 30);
            assert(v[2] == 40);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(0));
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 2);
            assert(v[0] == 30);
            assert(v[1] == 40);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(1));
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 1);
            assert(v[0] == 30);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(0));
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 0);
        }
    }

    cout << "Test erase(const_iterator, const_iterator)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            v.emplace_back(40);
            v.emplace_back(50);
            v.emplace_back(60);
            v.emplace_back(70);
            v.emplace_back(80);
            v.emplace_back(90);
            cout << "<" << endl;

            assert(v.size() == 9);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 50);
            assert(v[5] == 60);
            assert(v[6] == 70);
            assert(v[7] == 80);
            assert(v[8] == 90);
        }

        {
            cout << ">" << endl;
            // Erase nothing
            auto res = v.erase(v.nth(3), v.nth(3));
            cout << "<" << endl;

            assert(res == v.nth(3));
            assert(v.size() == 9);
        }

        {
            cout << ">" << endl;
            // Erase two elements near begin
            auto res = v.erase(v.nth(1), v.nth(3));
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 7);
            assert(v[0] == 10);
            assert(v[1] == 40);
            assert(v[2] == 50);
            assert(v[3] == 60);
            assert(v[4] == 70);
            assert(v[5] == 80);
            assert(v[6] == 90);
        }

        {
            cout << ">" << endl;
            // Erase two elements near end
            auto res = v.erase(v.nth(4), v.nth(6));
            cout << "<" << endl;

            assert(res == v.nth(4));
            assert(v.size() == 5);
            assert(v[0] == 10);
            assert(v[1] == 40);
            assert(v[2] == 50);
            assert(v[3] == 60);
            assert(v[4] == 90);
        }

        {
            cout << ">" << endl;
            // Remove two elements at begin
            auto res = v.erase(v.nth(0), v.nth(2));
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 3);
            assert(v[0] == 50);
            assert(v[1] == 60);
            assert(v[2] == 90);
        }

        {
            cout << ">" << endl;
            // Remove two elements at end
            auto res = v.erase(v.nth(1), v.nth(3));
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 1);
            assert(v[0] == 50);
        }

        {
            cout << ">" << endl;
            // Remove from begin to end
            auto res = v.erase(v.nth(0), v.nth(1));
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 0);
        }
    }

    cout << "Test resize(size_type)." << endl;
    {
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 5);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        // n == size
        {
            cout << ">" << endl;
            v.resize(3);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 5);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        // n > size && n > capacity
        {
            cout << ">" << endl;
            v.resize(6);
            cout << "<" << endl;

            assert(v.size() == 6);
            assert(v.capacity() == 6);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[4] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[5] == SFL_MY_INT_DEFAULT_VALUE);
        }

        // n < size
        {
            cout << ">" << endl;
            v.resize(2);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v.capacity() == 6);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }

        // n > size && n <= capacity
        {
            cout << ">" << endl;
            v.resize(4);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v.capacity() == 6);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[3] == SFL_MY_INT_DEFAULT_VALUE);
        }
    }

    cout << "Test resize(size_type, const T&)." << endl;
    {
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 5);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        // n == size
        {
            cout << ">" << endl;
            v.resize(3, 11);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 5);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        // n > size && n > capacity
        {
            cout << ">" << endl;
            v.resize(6, 40);
            cout << "<" << endl;

            assert(v.size() == 6);
            assert(v.capacity() == 6);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 40);
            assert(v[5] == 40);
        }

        // n < size
        {
            cout << ">" << endl;
            v.resize(2, 11);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v.capacity() == 6);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }

        // n > size && n <= capacity
        {
            cout << ">" << endl;
            v.resize(4, 50);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v.capacity() == 6);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 50);
            assert(v[3] == 50);
        }
    }

    cout << "Test swap(small_vector&)." << endl;
    {
        // v1 uses internal storage, v2 uses internal storage
        {
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v1({10, 11, 12});
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v2({20, 21, 22, 23});

            assert(v1.size() == 3);
            assert(*v1.nth(0) == 10);
            assert(*v1.nth(1) == 11);
            assert(*v1.nth(2) == 12);

            assert(v2.size() == 4);
            assert(*v2.nth(0) == 20);
            assert(*v2.nth(1) == 21);
            assert(*v2.nth(2) == 22);
            assert(*v2.nth(3) == 23);

            cout << ">" << endl;
            v1.swap(v2);
            cout << "<" << endl;

            assert(v1.size() == 4);
            assert(*v1.nth(0) == 20);
            assert(*v1.nth(1) == 21);
            assert(*v1.nth(2) == 22);
            assert(*v1.nth(3) == 23);

            assert(v2.size() == 3);
            assert(*v2.nth(0) == 10);
            assert(*v2.nth(1) == 11);
            assert(*v2.nth(2) == 12);

            cout << ">" << endl;
            v1.swap(v2);
            cout << "<" << endl;

            assert(v1.size() == 3);
            assert(*v1.nth(0) == 10);
            assert(*v1.nth(1) == 11);
            assert(*v1.nth(2) == 12);

            assert(v2.size() == 4);
            assert(*v2.nth(0) == 20);
            assert(*v2.nth(1) == 21);
            assert(*v2.nth(2) == 22);
            assert(*v2.nth(3) == 23);
        }

        // v1 uses internal storage, v2 uses external storage
        {
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v1({10, 11, 12});
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v2({20, 21, 22, 23, 24, 25});

            assert(v1.size() == 3);
            assert(*v1.nth(0) == 10);
            assert(*v1.nth(1) == 11);
            assert(*v1.nth(2) == 12);

            assert(v2.size() == 6);
            assert(*v2.nth(0) == 20);
            assert(*v2.nth(1) == 21);
            assert(*v2.nth(2) == 22);
            assert(*v2.nth(3) == 23);
            assert(*v2.nth(4) == 24);
            assert(*v2.nth(5) == 25);

            cout << ">" << endl;
            v1.swap(v2);
            cout << "<" << endl;

            assert(v1.size() == 6);
            assert(*v1.nth(0) == 20);
            assert(*v1.nth(1) == 21);
            assert(*v1.nth(2) == 22);
            assert(*v1.nth(3) == 23);
            assert(*v1.nth(4) == 24);
            assert(*v1.nth(5) == 25);

            assert(v2.size() == 3);
            assert(*v2.nth(0) == 10);
            assert(*v2.nth(1) == 11);
            assert(*v2.nth(2) == 12);
        }

        // v1 uses external storage, v2 uses internal storage
        {
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v1({10, 11, 12, 13, 14, 15});
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v2({20, 21, 22});

            assert(v1.size() == 6);
            assert(*v1.nth(0) == 10);
            assert(*v1.nth(1) == 11);
            assert(*v1.nth(2) == 12);
            assert(*v1.nth(3) == 13);
            assert(*v1.nth(4) == 14);
            assert(*v1.nth(5) == 15);

            assert(v2.size() == 3);
            assert(*v2.nth(0) == 20);
            assert(*v2.nth(1) == 21);
            assert(*v2.nth(2) == 22);

            cout << ">" << endl;
            v1.swap(v2);
            cout << "<" << endl;

            assert(v1.size() == 3);
            assert(*v1.nth(0) == 20);
            assert(*v1.nth(1) == 21);
            assert(*v1.nth(2) == 22);

            assert(v2.size() == 6);
            assert(*v2.nth(0) == 10);
            assert(*v2.nth(1) == 11);
            assert(*v2.nth(2) == 12);
            assert(*v2.nth(3) == 13);
            assert(*v2.nth(4) == 14);
            assert(*v2.nth(5) == 15);
        }

        // v1 uses external storage, v2 uses external storage
        {
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v1({10, 11, 12, 13, 14, 15});
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v2({20, 21, 22, 23, 24, 25});

            assert(v1.size() == 6);
            assert(*v1.nth(0) == 10);
            assert(*v1.nth(1) == 11);
            assert(*v1.nth(2) == 12);
            assert(*v1.nth(3) == 13);
            assert(*v1.nth(4) == 14);
            assert(*v1.nth(5) == 15);

            assert(v2.size() == 6);
            assert(*v2.nth(0) == 20);
            assert(*v2.nth(1) == 21);
            assert(*v2.nth(2) == 22);
            assert(*v2.nth(3) == 23);
            assert(*v2.nth(4) == 24);
            assert(*v2.nth(5) == 25);

            cout << ">" << endl;
            v1.swap(v2);
            cout << "<" << endl;

            assert(v1.size() == 6);
            assert(*v1.nth(0) == 20);
            assert(*v1.nth(1) == 21);
            assert(*v1.nth(2) == 22);
            assert(*v1.nth(3) == 23);
            assert(*v1.nth(4) == 24);
            assert(*v1.nth(5) == 25);

            assert(v2.size() == 6);
            assert(*v2.nth(0) == 10);
            assert(*v2.nth(1) == 11);
            assert(*v2.nth(2) == 12);
            assert(*v2.nth(3) == 13);
            assert(*v2.nth(4) == 14);
            assert(*v2.nth(5) == 15);
        }
    }

    cout << "Test at(const T&)." << endl;
    {
        #ifndef SFL_NO_EXCEPTIONS
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v;

        const auto& rv = v;

        {
            v.emplace_back(10);

            assert(v.size() == 1);
        }

        {
            bool exception_caught = false;

            try
            {
                assert(v.at(0) == 10);
            }
            catch (...)
            {
                exception_caught = true;
            }

            assert(!exception_caught);
        }

        {
            bool exception_caught = false;

            try
            {
                assert(rv.at(0) == 10);
            }
            catch (...)
            {
                exception_caught = true;
            }

            assert(!exception_caught);
        }

        {
            bool exception_caught = false;

            try
            {
                assert(v.at(15) == 1234);
            }
            catch (...)
            {
                exception_caught = true;
            }

            assert(exception_caught);
        }

        {
            bool exception_caught = false;

            try
            {
                assert(rv.at(15) == 1234);
            }
            catch (...)
            {
                exception_caught = true;
            }

            assert(exception_caught);
        }
        #endif
    }

    cout << "Test reserve and shrink_to_fit (N > 0)." << endl;
    {
        sfl::small_vector<MyInt, 4, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 4);
            assert(*v.nth(0) == 10);
            assert(*v.nth(1) == 20);
            assert(*v.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            v.reserve(2);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 4);
            assert(*v.nth(0) == 10);
            assert(*v.nth(1) == 20);
            assert(*v.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            v.reserve(10);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 10);
            assert(*v.nth(0) == 10);
            assert(*v.nth(1) == 20);
            assert(*v.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            v.reserve(7);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 10);
            assert(*v.nth(0) == 10);
            assert(*v.nth(1) == 20);
            assert(*v.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            v.shrink_to_fit();
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 4);
            assert(*v.nth(0) == 10);
            assert(*v.nth(1) == 20);
            assert(*v.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            v.clear();
            cout << "<" << endl;

            cout << ">" << endl;
            v.shrink_to_fit();
            cout << "<" << endl;

            assert(v.size() == 0);
            assert(v.capacity() == 4);
        }
    }

    cout << "Test reserve and shrink_to_fit (N == 0)." << endl;
    {
        sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.reserve(5);
            cout << "<" << endl;

            assert(v.size() == 0);
            assert(v.capacity() == 5);
        }

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 5);
            assert(*v.nth(0) == 10);
            assert(*v.nth(1) == 20);
            assert(*v.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            v.reserve(10);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 10);
            assert(*v.nth(0) == 10);
            assert(*v.nth(1) == 20);
            assert(*v.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            v.reserve(7);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 10);
            assert(*v.nth(0) == 10);
            assert(*v.nth(1) == 20);
            assert(*v.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            v.shrink_to_fit();
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 3);
            assert(*v.nth(0) == 10);
            assert(*v.nth(1) == 20);
            assert(*v.nth(2) == 30);
        }

        {
            cout << ">" << endl;
            v.clear();
            cout << "<" << endl;

            cout << ">" << endl;
            v.shrink_to_fit();
            cout << "<" << endl;

            assert(v.size() == 0);
            assert(v.capacity() == 0);
        }
    }

    cout << "Test constructor()." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v1;
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v2(alloc);

        assert(v1.size() == 0);
        assert(v2.size() == 0);

        assert(v1.capacity() == 10);
        assert(v2.capacity() == 10);
    }

    cout << "Test constructor(size_type)." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v1(3);
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v2(3, alloc);

        assert(v1.size() == 3);
        assert(v2.size() == 3);

        assert(v1.capacity() == 10);
        assert(v2.capacity() == 10);

        assert(v1[0] == SFL_MY_INT_DEFAULT_VALUE);
        assert(v1[1] == SFL_MY_INT_DEFAULT_VALUE);
        assert(v1[2] == SFL_MY_INT_DEFAULT_VALUE);

        assert(v2[0] == SFL_MY_INT_DEFAULT_VALUE);
        assert(v2[1] == SFL_MY_INT_DEFAULT_VALUE);
        assert(v2[2] == SFL_MY_INT_DEFAULT_VALUE);
    }

    cout << "Test constructor(size_type, const T&)." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        cout << ">" << endl;
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v1(3, 42);
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v2(3, 42, alloc);
        cout << "<" << endl;

        assert(v1.size() == 3);
        assert(v2.size() == 3);

        assert(v1.capacity() == 10);
        assert(v2.capacity() == 10);

        assert(v1[0] == 42);
        assert(v1[1] == 42);
        assert(v1[2] == 42);

        assert(v2[0] == 42);
        assert(v2[1] == 42);
        assert(v2[2] == 42);
    }

    cout << "Test constructor(InputIt, InputIt)." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        std::istringstream iss1("10 20 30 40");
        std::istringstream iss2("10 20 30 40");

        cout << ">" << endl;
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v1
        (
            (std::istream_iterator<int>(iss1)),
            (std::istream_iterator<int>())
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v2
        (
            (std::istream_iterator<int>(iss2)),
            (std::istream_iterator<int>()),
            alloc
        );
        cout << "<" << endl;

        assert(v1.size() == 4);
        assert(v2.size() == 4);

        assert(v1.capacity() == 10);
        assert(v2.capacity() == 10);

        assert(v1[0] == 10);
        assert(v1[1] == 20);
        assert(v1[2] == 30);
        assert(v1[3] == 40);

        assert(v2[0] == 10);
        assert(v2[1] == 20);
        assert(v2[2] == 30);
        assert(v2[3] == 40);
    }

    cout << "Test constructor(ForwardIt, ForwardIt)." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        const std::vector<MyInt> data({10, 20, 30, 40});

        cout << ">" << endl;
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v1(data.begin(), data.end());
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v2(data.begin(), data.end(), alloc);
        cout << "<" << endl;

        assert(v1.size() == 4);
        assert(v2.size() == 4);

        assert(v1.capacity() == 10);
        assert(v2.capacity() == 10);

        assert(v1[0] == 10);
        assert(v1[1] == 20);
        assert(v1[2] == 30);
        assert(v1[3] == 40);

        assert(v2[0] == 10);
        assert(v2[1] == 20);
        assert(v2[2] == 30);
        assert(v2[3] == 40);
    }

    cout << "Test constructor(MoveIterator, MoveIterator)." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        std::vector<MyInt> data1({10, 20, 30, 40});
        std::vector<MyInt> data2({10, 20, 30, 40});

        cout << ">" << endl;
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v1
        (
            std::make_move_iterator(data1.begin()),
            std::make_move_iterator(data1.end())
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v2
        (
            std::make_move_iterator(data2.begin()),
            std::make_move_iterator(data2.end()),
            alloc
        );
        cout << "<" << endl;

        assert(data1[0] == -10);
        assert(data1[1] == -20);
        assert(data1[2] == -30);
        assert(data1[3] == -40);

        assert(data2[0] == -10);
        assert(data2[1] == -20);
        assert(data2[2] == -30);
        assert(data2[3] == -40);

        assert(v1.size() == 4);
        assert(v2.size() == 4);

        assert(v1.capacity() == 10);
        assert(v2.capacity() == 10);

        assert(v1[0] == 10);
        assert(v1[1] == 20);
        assert(v1[2] == 30);
        assert(v1[3] == 40);

        assert(v2[0] == 10);
        assert(v2[1] == 20);
        assert(v2[2] == 30);
        assert(v2[3] == 40);
    }

    cout << "Test constructor(std::initializer_list)." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        cout << ">" << endl;
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v1({10, 20, 30, 40});
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v2({10, 20, 30, 40}, alloc);
        cout << "<" << endl;

        assert(v1.size() == 4);
        assert(v2.size() == 4);

        assert(v1.capacity() == 10);
        assert(v2.capacity() == 10);

        assert(v1[0] == 10);
        assert(v1[1] == 20);
        assert(v1[2] == 30);
        assert(v1[3] == 40);

        assert(v2[0] == 10);
        assert(v2[1] == 20);
        assert(v2[2] == 30);
        assert(v2[3] == 40);
    }

    cout << "Test constructor(const small_vector&) (N > 0)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v1({10, 20, 30, 40, 50});

        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v2(v1);

        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v3(v1, TP_ALLOC<MyInt>());

        assert(v1.size() == 5);
        assert(v1.capacity() == 10);
        assert(*v1.nth(0) == 10);
        assert(*v1.nth(1) == 20);
        assert(*v1.nth(2) == 30);
        assert(*v1.nth(3) == 40);
        assert(*v1.nth(4) == 50);

        assert(v2.size() == 5);
        assert(v2.capacity() == 10);
        assert(*v2.nth(0) == 10);
        assert(*v2.nth(1) == 20);
        assert(*v2.nth(2) == 30);
        assert(*v2.nth(3) == 40);
        assert(*v2.nth(4) == 50);

        assert(v3.size() == 5);
        assert(v3.capacity() == 10);
        assert(*v3.nth(0) == 10);
        assert(*v3.nth(1) == 20);
        assert(*v3.nth(2) == 30);
        assert(*v3.nth(3) == 40);
        assert(*v3.nth(4) == 50);
    }

    cout << "Test constructor(const small_vector&) (N == 0)." << endl;
    {
        sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v1({10, 20, 30, 40, 50});

        sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v2(v1);

        sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v3(v1, TP_ALLOC<MyInt>());

        assert(v1.size() == 5);
        assert(v1.capacity() == 5);
        assert(*v1.nth(0) == 10);
        assert(*v1.nth(1) == 20);
        assert(*v1.nth(2) == 30);
        assert(*v1.nth(3) == 40);
        assert(*v1.nth(4) == 50);

        assert(v2.size() == 5);
        assert(v2.capacity() == 5);
        assert(*v2.nth(0) == 10);
        assert(*v2.nth(1) == 20);
        assert(*v2.nth(2) == 30);
        assert(*v2.nth(3) == 40);
        assert(*v2.nth(4) == 50);

        assert(v3.size() == 5);
        assert(v3.capacity() == 5);
        assert(*v3.nth(0) == 10);
        assert(*v3.nth(1) == 20);
        assert(*v3.nth(2) == 30);
        assert(*v3.nth(3) == 40);
        assert(*v3.nth(4) == 50);
    }

    cout << "Test constructor(small_vector&&) (N > 0)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v1({10, 20, 30, 40, 50});

        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v2(std::move(v1));

        assert(v1.size() == 0);
        assert(v1.capacity() == 10);

        assert(v2.size() == 5);
        assert(v2.capacity() == 10);
        assert(*v2.nth(0) == 10);
        assert(*v2.nth(1) == 20);
        assert(*v2.nth(2) == 30);
        assert(*v2.nth(3) == 40);
        assert(*v2.nth(4) == 50);

        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v3(std::move(v2), TP_ALLOC<MyInt>());

        assert(v2.size() == 0);
        assert(v2.capacity() == 10);

        assert(v3.size() == 5);
        assert(v3.capacity() == 10);
        assert(*v3.nth(0) == 10);
        assert(*v3.nth(1) == 20);
        assert(*v3.nth(2) == 30);
        assert(*v3.nth(3) == 40);
        assert(*v3.nth(4) == 50);
    }

    cout << "Test constructor(small_vector&&) (N == 0)." << endl;
    {
        sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v1({10, 20, 30, 40, 50});

        sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v2(std::move(v1));

        assert(v1.size() == 0);
        assert(v1.capacity() == 0);

        assert(v2.size() == 5);
        assert(v2.capacity() == 5);
        assert(*v2.nth(0) == 10);
        assert(*v2.nth(1) == 20);
        assert(*v2.nth(2) == 30);
        assert(*v2.nth(3) == 40);
        assert(*v2.nth(4) == 50);

        sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v3(std::move(v2), TP_ALLOC<MyInt>());

        assert(v2.size() == 0);
        assert(v2.capacity() == 0);

        assert(v3.size() == 5);
        assert(v3.capacity() == 5);
        assert(*v3.nth(0) == 10);
        assert(*v3.nth(1) == 20);
        assert(*v3.nth(2) == 30);
        assert(*v3.nth(3) == 40);
        assert(*v3.nth(4) == 50);
    }

    cout << "Test assign(size_type, const T&)." << endl;
    {
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v;

        // n <= capacity && n > size
        {
            cout << ">" << endl;
            v.assign(3, 10);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 5);
            assert(v[0] == 10);
            assert(v[1] == 10);
            assert(v[2] == 10);
        }

        // n <= capacit< && n <= size
        {
            cout << ">" << endl;
            v.assign(2, 20);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v.capacity() == 5);
            assert(v[0] == 20);
            assert(v[1] == 20);
        }

        // n <= capacity && n > size
        {
            cout << ">" << endl;
            v.assign(4, 30);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v.capacity() == 5);
            assert(v[0] == 30);
            assert(v[1] == 30);
            assert(v[2] == 30);
            assert(v[3] == 30);
        }

        // n > capacity
        {
            cout << ">" << endl;
            v.assign(6, 40);
            cout << "<" << endl;

            assert(v.size() == 6);
            assert(v.capacity() == 6);
            assert(v[0] == 40);
            assert(v[1] == 40);
            assert(v[2] == 40);
            assert(v[3] == 40);
            assert(v[4] == 40);
            assert(v[5] == 40);
        }

        {
            cout << ">" << endl;
            v.assign(0, 50);
            cout << "<" << endl;

            assert(v.size() == 0);
            assert(v.capacity() == 6);
        }
    }

    cout << "Test assign(InputIt, InputIt)." << endl;
    {
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v;

        {
            std::istringstream iss("11 12 13");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 5);
            assert(v[0] == 11);
            assert(v[1] == 12);
            assert(v[2] == 13);
        }

        {
            std::istringstream iss("21 22");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v.capacity() == 5);
            assert(v[0] == 21);
            assert(v[1] == 22);
        }

        {
            std::istringstream iss("31 32 33 34");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v.capacity() == 5);
            assert(v[0] == 31);
            assert(v[1] == 32);
            assert(v[2] == 33);
            assert(v[3] == 34);
        }

        {
            std::istringstream iss("41 42 43 44 45 46");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            assert(v.size() == 6);
            assert(v.capacity() == 10);
            assert(v[0] == 41);
            assert(v[1] == 42);
            assert(v[2] == 43);
            assert(v[3] == 44);
            assert(v[4] == 45);
            assert(v[5] == 46);
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

            assert(v.size() == 0);
            assert(v.capacity() == 10);
        }
    }

    cout << "Test assign(ForwardIt, ForwardIt)." << endl;
    {
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v;

        // n <= capacity && n > size
        {
            const std::vector<int> data({11, 12, 13});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 5);
            assert(v[0] == 11);
            assert(v[1] == 12);
            assert(v[2] == 13);
        }

        // n <= capacity && n <= size
        {
            const std::vector<int> data({21, 22});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v.capacity() == 5);
            assert(v[0] == 21);
            assert(v[1] == 22);
        }

        // n <= capacity && n > size
        {
            const std::vector<int> data({31, 32, 33, 34});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v.capacity() == 5);
            assert(v[0] == 31);
            assert(v[1] == 32);
            assert(v[2] == 33);
            assert(v[3] == 34);
        }

        // n > capacity
        {
            const std::vector<int> data({41, 42, 43, 44, 45, 46});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 6);
            assert(v.capacity() == 6);
            assert(v[0] == 41);
            assert(v[1] == 42);
            assert(v[2] == 43);
            assert(v[3] == 44);
            assert(v[4] == 45);
            assert(v[5] == 46);
        }

        {
            const std::vector<int> data;

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 0);
            assert(v.capacity() == 6);
        }
    }

    cout << "Test assign(MoveIterator, MoveIterator)." << endl;
    {
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v;

        // n <= capacity && n > size
        {
            std::vector<MyInt> data({11, 12, 13});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            assert(data[0] == -11);
            assert(data[1] == -12);
            assert(data[2] == -13);
            assert(v.size() == 3);
            assert(v.capacity() == 5);
            assert(v[0] == 11);
            assert(v[1] == 12);
            assert(v[2] == 13);
        }

        // n <= capacity && n <= size
        {
            std::vector<MyInt> data({21, 22});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            assert(data[0] == -21);
            assert(data[1] == -22);
            assert(v.size() == 2);
            assert(v.capacity() == 5);
            assert(v[0] == 21);
            assert(v[1] == 22);
        }

        // n <= capacity && n > size
        {
            std::vector<MyInt> data({31, 32, 33, 34});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            assert(data[0] == -31);
            assert(data[1] == -32);
            assert(data[2] == -33);
            assert(data[3] == -34);
            assert(v.size() == 4);
            assert(v.capacity() == 5);
            assert(v[0] == 31);
            assert(v[1] == 32);
            assert(v[2] == 33);
            assert(v[3] == 34);
        }

        // n > capacity
        {
            std::vector<MyInt> data({41, 42, 43, 44, 45, 46});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            assert(data[0] == -41);
            assert(data[1] == -42);
            assert(data[2] == -43);
            assert(data[3] == -44);
            assert(data[4] == -45);
            assert(data[5] == -46);
            assert(v.size() == 6);
            assert(v.capacity() == 6);
            assert(v[0] == 41);
            assert(v[1] == 42);
            assert(v[2] == 43);
            assert(v[3] == 44);
            assert(v[4] == 45);
            assert(v[5] == 46);
        }
    }

    cout << "Test assign(std::initializer_list)." << endl;
    {
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v;

        // n <= capacity && n > size
        {
            cout << ">" << endl;
            v.assign({11, 12, 13});
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v.capacity() == 5);
            assert(v[0] == 11);
            assert(v[1] == 12);
            assert(v[2] == 13);
        }

        // n <= capacity && n <= size
        {
            cout << ">" << endl;
            v.assign({21, 22});
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v.capacity() == 5);
            assert(v[0] == 21);
            assert(v[1] == 22);
        }

        // n <= capacity && n > size
        {
            cout << ">" << endl;
            v.assign({31, 32, 33, 34});
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v.capacity() == 5);
            assert(v[0] == 31);
            assert(v[1] == 32);
            assert(v[2] == 33);
            assert(v[3] == 34);
        }

        // n > capacity
        {
            cout << ">" << endl;
            v.assign({41, 42, 43, 44, 45, 46});
            cout << "<" << endl;

            assert(v.size() == 6);
            assert(v.capacity() == 6);
            assert(v[0] == 41);
            assert(v[1] == 42);
            assert(v[2] == 43);
            assert(v[3] == 44);
            assert(v[4] == 45);
            assert(v[5] == 46);
        }

        {
            cout << ">" << endl;
            v.assign({});
            cout << "<" << endl;

            assert(v.size() == 0);
            assert(v.capacity() == 6);
        }
    }

    cout << "Test operator=(const small_vector&)." << endl;
    {
        // n <= capacity && n <= size
        {
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v1({11, 12, 13});
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v2({21, 22});

            assert(v1.size() == 3);
            assert(v1.capacity() == 5);

            assert(v2.size() == 2);
            assert(v2.capacity() == 5);

            cout << ">" << endl;
            v1 = v2;
            cout << "<" << endl;

            assert(v1.size() == 2);
            assert(v1.capacity() == 5);
            assert(*v1.nth(0) == 21);
            assert(*v1.nth(1) == 22);

            assert(v2.size() == 2);
            assert(v2.capacity() == 5);
            assert(*v2.nth(0) == 21);
            assert(*v2.nth(1) == 22);
        }

        // n <= capacity && n > size
        {
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v1({11, 12, 13});
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v2({21, 22, 23, 24, 25});

            assert(v1.size() == 3);
            assert(v1.capacity() == 5);

            assert(v2.size() == 5);
            assert(v2.capacity() == 5);

            cout << ">" << endl;
            v1 = v2;
            cout << "<" << endl;

            assert(v1.size() == 5);
            assert(v1.capacity() == 5);
            assert(*v1.nth(0) == 21);
            assert(*v1.nth(1) == 22);
            assert(*v1.nth(2) == 23);
            assert(*v1.nth(3) == 24);
            assert(*v1.nth(4) == 25);

            assert(v2.size() == 5);
            assert(v2.capacity() == 5);
            assert(*v2.nth(0) == 21);
            assert(*v2.nth(1) == 22);
            assert(*v2.nth(2) == 23);
            assert(*v2.nth(3) == 24);
            assert(*v2.nth(4) == 25);
        }

        // n > capacity
        {
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v1({11, 12, 13});
            sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v2({21, 22, 23, 24, 25, 26});

            assert(v1.size() == 3);
            assert(v1.capacity() == 5);

            assert(v2.size() == 6);
            assert(v2.capacity() == 6);

            cout << ">" << endl;
            v1 = v2;
            cout << "<" << endl;

            assert(v1.size() == 6);
            assert(v1.capacity() == 6);
            assert(*v1.nth(0) == 21);
            assert(*v1.nth(1) == 22);
            assert(*v1.nth(2) == 23);
            assert(*v1.nth(3) == 24);
            assert(*v1.nth(4) == 25);
            assert(*v1.nth(5) == 26);

            assert(v2.size() == 6);
            assert(v2.capacity() == 6);
            assert(*v2.nth(0) == 21);
            assert(*v2.nth(1) == 22);
            assert(*v2.nth(2) == 23);
            assert(*v2.nth(3) == 24);
            assert(*v2.nth(4) == 25);
            assert(*v2.nth(5) == 26);
        }
    }

    cout << "Test operator=(small_vector&&) (N > 0)." << endl;
    {
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v1({11, 12, 13});

        assert(v1.size() == 3);
        assert(v1.capacity() == 5);

        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v2({21, 22});

        assert(v2.size() == 2);
        assert(v2.capacity() == 5);

        cout << ">" << endl;
        v1 = std::move(v2);
        cout << "<" << endl;

        assert(v1.size() == 2);
        assert(v1.capacity() == 5);
        assert(*v1.nth(0) == 21);
        assert(*v1.nth(1) == 22);

        assert(v2.size() == 0);
        assert(v2.capacity() == 5);

        cout << ">" << endl;
        v2 = std::move(v1);
        cout << "<" << endl;

        assert(v1.size() == 0);
        assert(v1.capacity() == 5);

        assert(v2.size() == 2);
        assert(v2.capacity() == 5);
        assert(*v2.nth(0) == 21);
        assert(*v2.nth(1) == 22);
    }

    cout << "Test operator=(small_vector&&) (N == 0)." << endl;
    {
        sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v1;

        v1.reserve(3);
        v1.emplace_back(11);
        v1.emplace_back(12);
        v1.emplace_back(13);

        assert(v1.size() == 3);
        assert(v1.capacity() == 3);

        sfl::small_vector<MyInt, 0, TP_ALLOC<MyInt>> v2;

        v2.reserve(2);
        v2.emplace_back(21);
        v2.emplace_back(22);

        assert(v2.size() == 2);
        assert(v2.capacity() == 2);

        cout << ">" << endl;
        v1 = std::move(v2);
        cout << "<" << endl;

        assert(v1.size() == 2);
        assert(v1.capacity() == 2);
        assert(*v1.nth(0) == 21);
        assert(*v1.nth(1) == 22);

        assert(v2.size() == 0);
        assert(v2.capacity() == 0);

        v2.reserve(2);
        v2.emplace_back(31);
        v2.emplace_back(32);

        assert(v2.size() == 2);
        assert(v2.capacity() == 2);
        assert(*v2.nth(0) == 31);
        assert(*v2.nth(1) == 32);

        cout << ">" << endl;
        v2 = std::move(v1);
        cout << "<" << endl;

        assert(v1.size() == 0);
        assert(v1.capacity() == 0);

        assert(v2.size() == 2);
        assert(v2.capacity() == 2);
        assert(*v2.nth(0) == 21);
        assert(*v2.nth(1) == 22);
    }

    cout << "Test operator=(std::initializer_list)." << endl;
    {
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v1({11, 12, 13});
        assert(v1.size() == 3);
        assert(v1.capacity() == 5);

        cout << ">" << endl;
        v1 = {21, 22, 23};
        cout << "<" << endl;

        assert(v1.size() == 3);
        assert(v1.capacity() == 5);
        assert(*v1.nth(0) == 21);
        assert(*v1.nth(1) == 22);
        assert(*v1.nth(2) == 23);
    }

    cout << "Test non-member comparison operators." << endl;
    {
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v1({10, 20, 30});
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v2({10, 20, 30, 40});

        assert(v1 == v1);
        assert(!(v1 != v1));
        assert(!(v1 == v2));
        assert(v1 != v2);
        assert(!(v1 < v1));
        assert(v1 < v2);
        assert(v1 <= v1);
        assert(v1 >= v1);
        assert(v1 <= v2);
        assert(v2 > v1);
        assert(v2 >= v1);
        assert(v2 >= v2);
    }

    cout << "Test non-member swap." << endl;
    {
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v1({10, 11, 12});
        sfl::small_vector<MyInt, 5, TP_ALLOC<MyInt>> v2({20, 21, 22});

        using std::swap;
        swap(v1, v2);
    }

    cout << "Test non-member erase(small_vector&, const U&)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v1({10, 20, 20, 30, 30, 30});

        assert(v1.size() == 6);
        assert(v1[0] == 10);
        assert(v1[1] == 20);
        assert(v1[2] == 20);
        assert(v1[3] == 30);
        assert(v1[4] == 30);
        assert(v1[5] == 30);

        {
            cout << ">" << endl;
            auto res = erase(v1, 42);
            cout << "<" << endl;

            assert(res == 0);
            assert(v1.size() == 6);
            assert(v1[0] == 10);
            assert(v1[1] == 20);
            assert(v1[2] == 20);
            assert(v1[3] == 30);
            assert(v1[4] == 30);
            assert(v1[5] == 30);
        }

        {
            cout << ">" << endl;
            auto res = erase(v1, 20);
            cout << "<" << endl;

            assert(res == 2);
            assert(v1.size() == 4);
            assert(v1[0] == 10);
            assert(v1[1] == 30);
            assert(v1[2] == 30);
            assert(v1[3] == 30);
        }
    }

    cout << "Test non-member erase_if(small_vector&, Predicate)." << endl;
    {
        sfl::small_vector<MyInt, 10, TP_ALLOC<MyInt>> v1({10, 20, 20, 30, 30, 30});

        assert(v1.size() == 6);
        assert(v1[0] == 10);
        assert(v1[1] == 20);
        assert(v1[2] == 20);
        assert(v1[3] == 30);
        assert(v1[4] == 30);
        assert(v1[5] == 30);

        {
            cout << ">" << endl;
            auto res = erase_if(v1, [](const MyInt& x){ return x == 42; });
            cout << "<" << endl;

            assert(res == 0);
            assert(v1.size() == 6);
            assert(v1[0] == 10);
            assert(v1[1] == 20);
            assert(v1[2] == 20);
            assert(v1[3] == 30);
            assert(v1[4] == 30);
            assert(v1[5] == 30);
        }

        {
            cout << ">" << endl;
            auto res = erase_if(v1, [](const MyInt& x){ return x == 20; });
            cout << "<" << endl;

            assert(res == 2);
            assert(v1.size() == 4);
            assert(v1[0] == 10);
            assert(v1[1] == 30);
            assert(v1[2] == 30);
            assert(v1[3] == 30);
        }
    }
}
