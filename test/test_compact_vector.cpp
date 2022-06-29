//
// g++ -Wall -Wextra -Wpedantic -std=c++11 -g -I ../include -o test.out test_compact_vector.cpp
// valgrind --leak-check=full ./test.out
//

#undef NDEBUG
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include <sfl/compact_vector.hpp>

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
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1;
        const sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2;

        assert(v1.empty());
        assert(v2.empty());

        assert(v1.size() == 0);
        assert(v2.size() == 0);

        assert(v1.capacity() == 0);
        assert(v2.capacity() == 0);

        assert(v1.begin() == v1.end());
        assert(v2.begin() == v2.end());

        assert(v1.cbegin() == v1.cend());
        assert(v2.cbegin() == v2.cend());

        assert(v1.begin() == v1.cbegin());
        assert(v2.begin() == v2.cbegin());

        assert(v1.rbegin() == v1.rend());
        assert(v2.rbegin() == v2.rend());

        assert(v1.crbegin() == v1.crend());
        assert(v2.crbegin() == v2.crend());

        assert(v1.rbegin() == v1.crbegin());
        assert(v2.rbegin() == v2.crbegin());

        assert(v1.begin() == v1.nth(0));
        assert(v2.begin() == v2.nth(0));

        assert(v1.cbegin() == v1.nth(0));
        assert(v2.cbegin() == v2.nth(0));

        assert(v1.index_of(v1.nth(0)) == 0);
        assert(v2.index_of(v2.nth(0)) == 0);

        auto a1 = v1.get_allocator(); (void)a1;
        auto a2 = v2.get_allocator(); (void)a2;
    }

    cout << "Test emplace(const_iterator, Args&&...)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            auto res = v.emplace(v.end(), 10);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 1);
            assert(v[0] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.end(), 20);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 2);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.end(), 30);
            cout << "<" << endl;

            assert(res == v.nth(2));
            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(1), 40);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 4);
            assert(v[0] == 10);
            assert(v[1] == 40);
            assert(v[2] == 20);
            assert(v[3] == 30);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(1), 50);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 5);
            assert(v[0] == 10);
            assert(v[1] == 50);
            assert(v[2] == 40);
            assert(v[3] == 20);
            assert(v[4] == 30);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(1), 60);
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 6);
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
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

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
            assert(v.index_of(v.nth(0)) == 0);
            assert(v.index_of(v.nth(1)) == 1);
            assert(v.index_of(v.nth(2)) == 2);
        }

        {
            assert(v.at(0) == 10);
            assert(v.at(1) == 20);
            assert(v.at(2) == 30);

            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);

            assert(v.front() == 10);

            assert(v.back() == 30);
        }

        {
            auto data = v.data();
            assert(*data == 10); ++data;
            assert(*data == 20); ++data;
            assert(*data == 30); ++data;
        }
    }

    cout << "Test insert(const_iterator, const T& value)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            const MyInt i(10);

            cout << ">" << endl;
            auto res = v.emplace(v.end(), i);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 1);
            assert(v[0] == 10);
        }
    }

    cout << "Test insert(const_iterator, T&& value)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            MyInt i(10);

            cout << ">" << endl;
            auto res = v.emplace(v.end(), std::move(i));
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(i == -10);
            assert(v.size() == 1);
            assert(v[0] == 10);
        }
    }

    cout << "Test insert(const_iterator, size_type, const T&)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(0), 3, MyInt(10));
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 3);
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
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 20);
            assert(v[3] == 20);
            assert(v[4] == 10);
            assert(v[5] == 10);
        }
    }

    cout << "Test insert(const_iterator, InputIt, InputIt)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

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
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
        }
    }

    cout << "Test insert(const_iterator, ForwardIt, ForwardIt)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            const std::vector<MyInt> data({10, 20, 30, 40});

            cout << ">" << endl;
            auto res = v.insert(v.begin(), data.begin(), data.end());
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 4);
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
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

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
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
        }
    }

    cout << "Test insert(const_iterator, std::initializer_list)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

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
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            cout << "<" << endl;

            assert(v.size() == 1);
            assert(v[0] == 10);
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            v.emplace_back(std::move(i));
            cout << "<" << endl;

            assert(i == -20);
            assert(v.size() == 2);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }
    }

    cout << "Test push_back(const T&)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            const MyInt i(10);

            cout << ">" << endl;
            v.push_back(i);
            cout << "<" << endl;

            assert(v.size() == 1);
            assert(v[0] == 10);
        }

        {
            const MyInt i(20);

            cout << ">" << endl;
            v.push_back(i);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }
    }

    cout << "Test push_back(T&&)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            MyInt i(10);

            cout << ">" << endl;
            v.push_back(std::move(i));
            cout << "<" << endl;

            assert(i == -10);
            assert(v.size() == 1);
            assert(v[0] == 10);
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            v.push_back(std::move(i));
            cout << "<" << endl;

            assert(i == -20);
            assert(v.size() == 2);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }
    }

    cout << "Test clear()." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

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

    cout << "Test pop_back()." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
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

        {
            cout << ">" << endl;
            v.emplace_back(50);
            cout << "<" << endl;

            assert(v.size() == 1);
            assert(v[0] == 50);
        }

        {
            cout << ">" << endl;
            v.pop_back();
            cout << "<" << endl;

            assert(v.size() == 0);
        }
    }

    cout << "Test erase(const_iterator)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

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
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            v.emplace_back(40);
            v.emplace_back(50);
            cout << "<" << endl;

            assert(v.size() == 5);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 50);
        }

        {
            cout << ">" << endl;
            // Erase nothing
            auto res = v.erase(v.nth(3), v.nth(3));
            cout << "<" << endl;

            assert(res == v.nth(3));
            assert(v.size() == 5);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(1), v.nth(3));
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 40);
            assert(v[2] == 50);
        }

        {
            cout << ">" << endl;
            auto res = v.erase(v.nth(0), v.nth(1));
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 2);
            assert(v[0] == 40);
            assert(v[1] == 50);
        }
    }

    cout << "Test resize(size_type)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.resize(3);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.resize(6);
            cout << "<" << endl;

            assert(v.size() == 6);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[4] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[5] == SFL_MY_INT_DEFAULT_VALUE);
        }

        {
            cout << ">" << endl;
            v.resize(2);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }

        {
            cout << ">" << endl;
            v.resize(4);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[3] == SFL_MY_INT_DEFAULT_VALUE);
        }

        {
            cout << ">" << endl;
            v.resize(0);
            cout << "<" << endl;

            assert(v.size() == 0);
        }

        {
            cout << ">" << endl;
            v.resize(2);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[1] == SFL_MY_INT_DEFAULT_VALUE);
        }
    }

    cout << "Test resize(size_type, const T&)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.resize(3, 11);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.resize(6, 40);
            cout << "<" << endl;

            assert(v.size() == 6);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 40);
            assert(v[5] == 40);
        }

        {
            cout << ">" << endl;
            v.resize(2, 11);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }

        {
            cout << ">" << endl;
            v.resize(4, 50);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 50);
            assert(v[3] == 50);
        }

        {
            cout << ">" << endl;
            v.resize(0, 60);
            cout << "<" << endl;

            assert(v.size() == 0);
        }

        {
            cout << ">" << endl;
            v.resize(2, 70);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 70);
            assert(v[1] == 70);
        }
    }

    cout << "Test swap(compact_vector&)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2;

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

    cout << "Test at(const T&)." << endl;
    {
        #ifndef SFL_NO_EXCEPTIONS
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

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

    cout << "Test constructor()." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2(alloc);

        assert(v1.size() == 0);
        assert(v2.size() == 0);
    }

    cout << "Test constructor(size_type)." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1(3);
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2(3, alloc);
        cout << "<" << endl;

        assert(v1.size() == 3);
        assert(v2.size() == 3);

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
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1(3, 42);
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2(3, 42, alloc);
        cout << "<" << endl;

        assert(v1.size() == 3);
        assert(v2.size() == 3);

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
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1
        (
            (std::istream_iterator<int>(iss1)),
            (std::istream_iterator<int>())
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2
        (
            (std::istream_iterator<int>(iss2)),
            (std::istream_iterator<int>()),
            alloc
        );
        cout << "<" << endl;

        assert(v1.size() == 4);
        assert(v2.size() == 4);

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
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1(data.begin(), data.end());
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2(data.begin(), data.end(), alloc);
        cout << "<" << endl;

        assert(v1.size() == 4);
        assert(v2.size() == 4);

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
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1
        (
            std::make_move_iterator(data1.begin()),
            std::make_move_iterator(data1.end())
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2
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
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1({10, 20, 30, 40});
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2({10, 20, 30, 40}, alloc);
        cout << "<" << endl;

        assert(v1.size() == 4);
        assert(v2.size() == 4);

        assert(v1[0] == 10);
        assert(v1[1] == 20);
        assert(v1[2] == 30);
        assert(v1[3] == 40);

        assert(v2[0] == 10);
        assert(v2[1] == 20);
        assert(v2[2] == 30);
        assert(v2[3] == 40);
    }

    cout << "Test constructor(const compact_vector&)." << endl;
    {
        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1({10, 20, 30, 40, 50});
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2(v1);
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v3(v1, TP_ALLOC<MyInt>());
        cout << "<" << endl;

        assert(v1.size() == 5);
        assert(v1[0] == 10);
        assert(v1[1] == 20);
        assert(v1[2] == 30);
        assert(v1[3] == 40);
        assert(v1[4] == 50);

        assert(v2.size() == 5);
        assert(v2[0] == 10);
        assert(v2[1] == 20);
        assert(v2[2] == 30);
        assert(v2[3] == 40);
        assert(v2[4] == 50);

        assert(v3.size() == 5);
        assert(v3[0] == 10);
        assert(v3[1] == 20);
        assert(v3[2] == 30);
        assert(v3[3] == 40);
        assert(v3[4] == 50);
    }

    cout << "Test constructor(compact_vector&&)." << endl;
    {
        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1({10, 20, 30, 40, 50});
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2(std::move(v1));
        cout << "<" << endl;

        // v1 is in a valid but unspecified state

        assert(v2.size() == 5);
        assert(v2[0] == 10);
        assert(v2[1] == 20);
        assert(v2[2] == 30);
        assert(v2[3] == 40);
        assert(v2[4] == 50);

        cout << ">" << endl;
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v3(std::move(v2), TP_ALLOC<MyInt>());
        cout << "<" << endl;

        // v2 is in a valid but unspecified state

        assert(v3.size() == 5);
        assert(v3[0] == 10);
        assert(v3[1] == 20);
        assert(v3[2] == 30);
        assert(v3[3] == 40);
        assert(v3[4] == 50);
    }

    cout << "Test assign(size_type, const T&)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.assign(3, 10);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 10);
            assert(v[2] == 10);
        }

        {
            cout << ">" << endl;
            v.assign(3, 20);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 20);
            assert(v[1] == 20);
            assert(v[2] == 20);
        }

        {
            cout << ">" << endl;
            v.assign(2, 30);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 30);
            assert(v[1] == 30);
        }

        {
            cout << ">" << endl;
            v.assign(4, 40);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v[0] == 40);
            assert(v[1] == 40);
            assert(v[2] == 40);
            assert(v[3] == 40);
        }

        {
            cout << ">" << endl;
            v.assign(0, 50);
            cout << "<" << endl;

            assert(v.size() == 0);
        }
    }

    cout << "Test assign(InputIt, InputIt)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            std::istringstream iss("10 20 30");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
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

            assert(v.size() == 3);
            assert(v[0] == 40);
            assert(v[1] == 50);
            assert(v[2] == 60);
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

            assert(v.size() == 2);
            assert(v[0] == 70);
            assert(v[1] == 80);
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
        }
    }

    cout << "Test assign(ForwardIt, ForwardIt)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            const std::vector<int> data({10, 20, 30});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            const std::vector<int> data({40, 50, 60});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 40);
            assert(v[1] == 50);
            assert(v[2] == 60);
        }

        {
            const std::vector<int> data({70, 80});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 70);
            assert(v[1] == 80);
        }

        {
            const std::vector<int> data;

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 0);
        }
    }

    cout << "Test assign(MoveIterator, MoveIterator)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            std::vector<MyInt> data({10, 20, 30});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            assert(data[0] == -10);
            assert(data[1] == -20);
            assert(data[2] == -30);
            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            std::vector<MyInt> data({40, 50, 60});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            assert(data[0] == -40);
            assert(data[1] == -50);
            assert(data[2] == -60);
            assert(v.size() == 3);
            assert(v[0] == 40);
            assert(v[1] == 50);
            assert(v[2] == 60);
        }

        {
            std::vector<MyInt> data({70, 80});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            assert(data[0] == -70);
            assert(data[1] == -80);
            assert(v.size() == 2);
            assert(v[0] == 70);
            assert(v[1] == 80);
        }
    }

    cout << "Test assign(std::initializer_list)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.assign({10, 20, 30});
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.assign({40, 50, 60});
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 40);
            assert(v[1] == 50);
            assert(v[2] == 60);
        }

        {
            cout << ">" << endl;
            v.assign({70, 80});
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 70);
            assert(v[1] == 80);
        }

        {
            cout << ">" << endl;
            v.assign({});
            cout << "<" << endl;

            assert(v.size() == 0);
        }
    }

    cout << "Test operator=(const compact_vector&)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1({10, 20, 30});
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2({40, 50});

        assert(v1.size() == 3);
        assert(v2.size() == 2);

        cout << ">" << endl;
        v1 = v2;
        cout << "<" << endl;

        assert(v1.size() == 2);
        assert(v1[0] == 40);
        assert(v1[1] == 50);

        assert(v2.size() == 2);
        assert(v2[0] == 40);
        assert(v2[1] == 50);
    }

    cout << "Test operator=(compact_vector&&)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1({10, 20, 30});
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2({40, 50});

        assert(v1.size() == 3);
        assert(v2.size() == 2);

        cout << ">" << endl;
        v1 = std::move(v2);
        cout << "<" << endl;

        assert(v1.size() == 2);
        assert(v1[0] == 40);
        assert(v1[1] == 50);

        // v2 is in a valid but unspecified state

        cout << ">" << endl;
        v2 = std::move(v1);
        cout << "<" << endl;

        // v1 is in a valid but unspecified state

        assert(v2.size() == 2);
        assert(v2[0] == 40);
        assert(v2[1] == 50);
    }

    cout << "Test operator=(std::initializer_list)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1({10, 20, 30});
        assert(v1.size() == 3);

        cout << ">" << endl;
        v1 = {40, 50, 60};
        cout << "<" << endl;

        assert(v1.size() == 3);
        assert(v1[0] == 40);
        assert(v1[1] == 50);
        assert(v1[2] == 60);
    }

    cout << "Test non-member comparison operators." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1({10, 20, 30});
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2({10, 20, 30, 40});

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
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1({10, 11, 12});
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v2({20, 21, 22});

        using std::swap;
        swap(v1, v2);
    }

    cout << "Test non-member erase(compact_vector&, const U&)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1({10, 20, 20, 30, 30, 30});

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

    cout << "Test non-member erase_if(compact_vector&, Predicate)." << endl;
    {
        sfl::compact_vector<MyInt, TP_ALLOC<MyInt>> v1({10, 20, 20, 30, 30, 30});

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
