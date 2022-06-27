//
// g++ -Wall -Wextra -Wpedantic -std=c++11 -g -I ../include -o test.out test_segmented_vector.cpp
// valgrind --leak-check=full ./test.out
//

#undef NDEBUG
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include <sfl/segmented_vector.hpp>

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

#ifndef TP_N
#define TP_N 4
#endif

int main()
{
    using std::cout;
    using std::endl;

    cout << "Test non-modifying member functions on empty container." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1;
        const sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2;

        assert(v1.empty());
        assert(v2.empty());

        assert(v1.size() == 0);
        assert(v2.size() == 0);

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

    cout << "Test emplace_back(Args&&...) (1)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            cout << "<" << endl;

            assert(v.size() == 1);
            assert(v[0] == 10);
        }

        {
            cout << ">" << endl;
            v.emplace_back(20);
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 10);
            assert(v[1] == 20);
        }

        {
            cout << ">" << endl;
            v.emplace_back(30);
            cout << "<" << endl;

            assert(v.size() == 3);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
        }

        {
            cout << ">" << endl;
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
            v.emplace_back(60);
            cout << "<" << endl;

            assert(v.size() == 6);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 50);
            assert(v[5] == 60);
        }

        {
            cout << ">" << endl;
            v.emplace_back(70);
            cout << "<" << endl;

            assert(v.size() == 7);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 50);
            assert(v[5] == 60);
            assert(v[6] == 70);
        }

        {
            cout << ">" << endl;
            v.emplace_back(80);
            cout << "<" << endl;

            assert(v.size() == 8);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 50);
            assert(v[5] == 60);
            assert(v[6] == 70);
            assert(v[7] == 80);
        }

        {
            cout << ">" << endl;
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
            v.emplace_back(100);
            cout << "<" << endl;

            assert(v.size() == 10);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 50);
            assert(v[5] == 60);
            assert(v[6] == 70);
            assert(v[7] == 80);
            assert(v[8] == 90);
            assert(v[9] == 100);
        }

        {
            cout << ">" << endl;
            v.emplace_back(110);
            cout << "<" << endl;

            assert(v.size() == 11);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 50);
            assert(v[5] == 60);
            assert(v[6] == 70);
            assert(v[7] == 80);
            assert(v[8] == 90);
            assert(v[9] == 100);
            assert(v[10] == 110);
        }

        {
            cout << ">" << endl;
            v.emplace_back(120);
            cout << "<" << endl;

            assert(v.size() == 12);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 50);
            assert(v[5] == 60);
            assert(v[6] == 70);
            assert(v[7] == 80);
            assert(v[8] == 90);
            assert(v[9] == 100);
            assert(v[10] == 110);
            assert(v[11] == 120);
        }

        {
            cout << ">" << endl;
            v.emplace_back(130);
            cout << "<" << endl;

            assert(v.size() == 13);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 50);
            assert(v[5] == 60);
            assert(v[6] == 70);
            assert(v[7] == 80);
            assert(v[8] == 90);
            assert(v[9] == 100);
            assert(v[10] == 110);
            assert(v[11] == 120);
            assert(v[12] == 130);
        }
    }

    cout << "Test emplace_back(Args&&...) (2)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        constexpr int n = 100;

        for (int i = 0; i < n; ++i)
        {
            v.emplace_back(i);
        }
    }

    cout << "Test emplace(const_iterator, Args&&...) (1)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 10);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 1);
            assert(v[0] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 20);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 2);
            assert(v[0] == 20);
            assert(v[1] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 30);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 3);
            assert(v[0] == 30);
            assert(v[1] == 20);
            assert(v[2] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 40);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 4);
            assert(v[0] == 40);
            assert(v[1] == 30);
            assert(v[2] == 20);
            assert(v[3] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 50);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 5);
            assert(v[0] == 50);
            assert(v[1] == 40);
            assert(v[2] == 30);
            assert(v[3] == 20);
            assert(v[4] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 60);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 6);
            assert(v[0] == 60);
            assert(v[1] == 50);
            assert(v[2] == 40);
            assert(v[3] == 30);
            assert(v[4] == 20);
            assert(v[5] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(3), 70);
            cout << "<" << endl;

            assert(res == v.nth(3));
            assert(v.size() == 7);
            assert(v[0] == 60);
            assert(v[1] == 50);
            assert(v[2] == 40);
            assert(v[3] == 70);
            assert(v[4] == 30);
            assert(v[5] == 20);
            assert(v[6] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(5), 80);
            cout << "<" << endl;

            assert(res == v.nth(5));
            assert(v.size() == 8);
            assert(v[0] == 60);
            assert(v[1] == 50);
            assert(v[2] == 40);
            assert(v[3] == 70);
            assert(v[4] == 30);
            assert(v[5] == 80);
            assert(v[6] == 20);
            assert(v[7] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(8), 90);
            cout << "<" << endl;

            assert(res == v.nth(8));
            assert(v.size() == 9);
            assert(v[0] == 60);
            assert(v[1] == 50);
            assert(v[2] == 40);
            assert(v[3] == 70);
            assert(v[4] == 30);
            assert(v[5] == 80);
            assert(v[6] == 20);
            assert(v[7] == 10);
            assert(v[8] == 90);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(8), 100);
            cout << "<" << endl;

            assert(res == v.nth(8));
            assert(v.size() == 10);
            assert(v[0] == 60);
            assert(v[1] == 50);
            assert(v[2] == 40);
            assert(v[3] == 70);
            assert(v[4] == 30);
            assert(v[5] == 80);
            assert(v[6] == 20);
            assert(v[7] == 10);
            assert(v[8] == 100);
            assert(v[9] == 90);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(8), 110);
            cout << "<" << endl;

            assert(res == v.nth(8));
            assert(v.size() == 11);
            assert(v[0] == 60);
            assert(v[1] == 50);
            assert(v[2] == 40);
            assert(v[3] == 70);
            assert(v[4] == 30);
            assert(v[5] == 80);
            assert(v[6] == 20);
            assert(v[7] == 10);
            assert(v[8] == 110);
            assert(v[9] == 100);
            assert(v[10] == 90);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(8), 120);
            cout << "<" << endl;

            assert(res == v.nth(8));
            assert(v.size() == 12);
            assert(v[0] == 60);
            assert(v[1] == 50);
            assert(v[2] == 40);
            assert(v[3] == 70);
            assert(v[4] == 30);
            assert(v[5] == 80);
            assert(v[6] == 20);
            assert(v[7] == 10);
            assert(v[8] == 120);
            assert(v[9] == 110);
            assert(v[10] == 100);
            assert(v[11] == 90);
        }
    }

    cout << "Test emplace(const_iterator, Args&&...) (2)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        constexpr int n = 100;

        for (int i = 0; i < n; ++i)
        {
            v.emplace(v.begin(), 1000 + i);
        }

        for (int i = 0; i < n; ++i)
        {
            v.emplace(v.begin() + 10 + i, 2000 + i);
        }
    }

    cout << "Test non-modifying member functions on non-empty container." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        v.emplace_back(10);
        v.emplace_back(20);
        v.emplace_back(30);
        v.emplace_back(40);
        v.emplace_back(50);
        v.emplace_back(60);
        v.emplace_back(70);
        v.emplace_back(80);
        v.emplace_back(90);

        {
            assert(v.at(0) == 10);
            assert(v.at(1) == 20);
            assert(v.at(2) == 30);
            assert(v.at(3) == 40);
            assert(v.at(4) == 50);
            assert(v.at(5) == 60);
            assert(v.at(6) == 70);
            assert(v.at(7) == 80);
            assert(v.at(8) == 90);
        }

        {
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
            assert(v.front() == 10);
        }

        {
            assert(v.back() == 90);
        }

        {
            assert(*v.nth(0) == v.at(0));
            assert(*v.nth(1) == v.at(1));
            assert(*v.nth(2) == v.at(2));
            assert(*v.nth(3) == v.at(3));
            assert(*v.nth(4) == v.at(4));
            assert(*v.nth(5) == v.at(5));
            assert(*v.nth(6) == v.at(6));
            assert(*v.nth(7) == v.at(7));
            assert(*v.nth(8) == v.at(8));
        }

        {
            assert(v.index_of(v.nth(0)) == 0);
            assert(v.index_of(v.nth(1)) == 1);
            assert(v.index_of(v.nth(2)) == 2);
            assert(v.index_of(v.nth(3)) == 3);
            assert(v.index_of(v.nth(4)) == 4);
            assert(v.index_of(v.nth(5)) == 5);
            assert(v.index_of(v.nth(6)) == 6);
            assert(v.index_of(v.nth(7)) == 7);
            assert(v.index_of(v.nth(8)) == 8);
            assert(v.index_of(v.nth(9)) == 9);
        }

        {
            auto it = v.begin();
            assert(++it == v.nth(1));
            assert(++it == v.nth(2));
            assert(++it == v.nth(3));
            assert(++it == v.nth(4));
            assert(++it == v.nth(5));
            assert(++it == v.nth(6));
            assert(++it == v.nth(7));
            assert(++it == v.nth(8));
            assert(++it == v.nth(9));

            auto cit = v.cbegin();
            assert(++cit == v.nth(1));
            assert(++cit == v.nth(2));
            assert(++cit == v.nth(3));
            assert(++cit == v.nth(4));
            assert(++cit == v.nth(5));
            assert(++cit == v.nth(6));
            assert(++cit == v.nth(7));
            assert(++cit == v.nth(8));
            assert(++cit == v.nth(9));
        }

        {
            auto it = v.begin();
            assert(it++ == v.nth(0));
            assert(it++ == v.nth(1));
            assert(it++ == v.nth(2));
            assert(it++ == v.nth(3));
            assert(it++ == v.nth(4));
            assert(it++ == v.nth(5));
            assert(it++ == v.nth(6));
            assert(it++ == v.nth(7));
            assert(it++ == v.nth(8));

            auto cit = v.cbegin();
            assert(cit++ == v.nth(0));
            assert(cit++ == v.nth(1));
            assert(cit++ == v.nth(2));
            assert(cit++ == v.nth(3));
            assert(cit++ == v.nth(4));
            assert(cit++ == v.nth(5));
            assert(cit++ == v.nth(6));
            assert(cit++ == v.nth(7));
            assert(cit++ == v.nth(8));
        }

        {
            auto it = v.end();
            assert(--it == v.nth(8));
            assert(--it == v.nth(7));
            assert(--it == v.nth(6));
            assert(--it == v.nth(5));
            assert(--it == v.nth(4));
            assert(--it == v.nth(3));
            assert(--it == v.nth(2));
            assert(--it == v.nth(1));
            assert(--it == v.nth(0));

            auto cit = v.cend();
            assert(--cit == v.nth(8));
            assert(--cit == v.nth(7));
            assert(--cit == v.nth(6));
            assert(--cit == v.nth(5));
            assert(--cit == v.nth(4));
            assert(--cit == v.nth(3));
            assert(--cit == v.nth(2));
            assert(--cit == v.nth(1));
            assert(--cit == v.nth(0));
        }

        {
            auto it = v.end();
            assert(it-- == v.nth(9));
            assert(it-- == v.nth(8));
            assert(it-- == v.nth(7));
            assert(it-- == v.nth(6));
            assert(it-- == v.nth(5));
            assert(it-- == v.nth(4));
            assert(it-- == v.nth(3));
            assert(it-- == v.nth(2));
            assert(it-- == v.nth(1));

            auto cit = v.cend();
            assert(cit-- == v.nth(9));
            assert(cit-- == v.nth(8));
            assert(cit-- == v.nth(7));
            assert(cit-- == v.nth(6));
            assert(cit-- == v.nth(5));
            assert(cit-- == v.nth(4));
            assert(cit-- == v.nth(3));
            assert(cit-- == v.nth(2));
            assert(cit-- == v.nth(1));
        }


        {
            assert(v.begin() + 0 == v.nth(0));
            assert(v.begin() + 1 == v.nth(1));
            assert(v.begin() + 2 == v.nth(2));
            assert(v.begin() + 3 == v.nth(3));
            assert(v.begin() + 4 == v.nth(4));
            assert(v.begin() + 5 == v.nth(5));
            assert(v.begin() + 6 == v.nth(6));
            assert(v.begin() + 7 == v.nth(7));
            assert(v.begin() + 8 == v.nth(8));
            assert(v.begin() + 9 == v.nth(9));

            assert(v.cbegin() + 0 == v.nth(0));
            assert(v.cbegin() + 1 == v.nth(1));
            assert(v.cbegin() + 2 == v.nth(2));
            assert(v.cbegin() + 3 == v.nth(3));
            assert(v.cbegin() + 4 == v.nth(4));
            assert(v.cbegin() + 5 == v.nth(5));
            assert(v.cbegin() + 6 == v.nth(6));
            assert(v.cbegin() + 7 == v.nth(7));
            assert(v.cbegin() + 8 == v.nth(8));
            assert(v.cbegin() + 9 == v.nth(9));
        }

        {
            assert(v.end() - 0 == v.nth(9));
            assert(v.end() - 1 == v.nth(8));
            assert(v.end() - 2 == v.nth(7));
            assert(v.end() - 3 == v.nth(6));
            assert(v.end() - 4 == v.nth(5));
            assert(v.end() - 5 == v.nth(4));
            assert(v.end() - 6 == v.nth(3));
            assert(v.end() - 7 == v.nth(2));
            assert(v.end() - 8 == v.nth(1));
            assert(v.end() - 9 == v.nth(0));

            assert(v.cend() - 0 == v.nth(9));
            assert(v.cend() - 1 == v.nth(8));
            assert(v.cend() - 2 == v.nth(7));
            assert(v.cend() - 3 == v.nth(6));
            assert(v.cend() - 4 == v.nth(5));
            assert(v.cend() - 5 == v.nth(4));
            assert(v.cend() - 6 == v.nth(3));
            assert(v.cend() - 7 == v.nth(2));
            assert(v.cend() - 8 == v.nth(1));
            assert(v.cend() - 9 == v.nth(0));
        }

        {
            assert(v.nth(0) - v.nth(0) == 0);
            assert(v.nth(1) - v.nth(0) == 1);
            assert(v.nth(2) - v.nth(0) == 2);
            assert(v.nth(3) - v.nth(0) == 3);
            assert(v.nth(4) - v.nth(0) == 4);
            assert(v.nth(5) - v.nth(0) == 5);
            assert(v.nth(6) - v.nth(0) == 6);
            assert(v.nth(7) - v.nth(0) == 7);
            assert(v.nth(8) - v.nth(0) == 8);
            assert(v.nth(9) - v.nth(0) == 9);

            assert(v.nth(1) - v.nth(1) == 0);
            assert(v.nth(2) - v.nth(1) == 1);
            assert(v.nth(3) - v.nth(1) == 2);
            assert(v.nth(4) - v.nth(1) == 3);
            assert(v.nth(5) - v.nth(1) == 4);
            assert(v.nth(6) - v.nth(1) == 5);
            assert(v.nth(7) - v.nth(1) == 6);
            assert(v.nth(8) - v.nth(1) == 7);
            assert(v.nth(9) - v.nth(1) == 8);

            assert(v.nth(2) - v.nth(2) == 0);
            assert(v.nth(3) - v.nth(2) == 1);
            assert(v.nth(4) - v.nth(2) == 2);
            assert(v.nth(5) - v.nth(2) == 3);
            assert(v.nth(6) - v.nth(2) == 4);
            assert(v.nth(7) - v.nth(2) == 5);
            assert(v.nth(8) - v.nth(2) == 6);
            assert(v.nth(9) - v.nth(2) == 7);

            assert(v.nth(3) - v.nth(3) == 0);
            assert(v.nth(4) - v.nth(3) == 1);
            assert(v.nth(5) - v.nth(3) == 2);
            assert(v.nth(6) - v.nth(3) == 3);
            assert(v.nth(7) - v.nth(3) == 4);
            assert(v.nth(8) - v.nth(3) == 5);
            assert(v.nth(9) - v.nth(3) == 6);

            assert(v.nth(4) - v.nth(4) == 0);
            assert(v.nth(5) - v.nth(4) == 1);
            assert(v.nth(6) - v.nth(4) == 2);
            assert(v.nth(7) - v.nth(4) == 3);
            assert(v.nth(8) - v.nth(4) == 4);
            assert(v.nth(9) - v.nth(4) == 5);

            assert(v.nth(5) - v.nth(5) == 0);
            assert(v.nth(6) - v.nth(5) == 1);
            assert(v.nth(7) - v.nth(5) == 2);
            assert(v.nth(8) - v.nth(5) == 3);
            assert(v.nth(9) - v.nth(5) == 4);

            assert(v.nth(6) - v.nth(6) == 0);
            assert(v.nth(7) - v.nth(6) == 1);
            assert(v.nth(8) - v.nth(6) == 2);
            assert(v.nth(9) - v.nth(6) == 3);

            assert(v.nth(7) - v.nth(7) == 0);
            assert(v.nth(8) - v.nth(7) == 1);
            assert(v.nth(9) - v.nth(7) == 2);

            assert(v.nth(8) - v.nth(8) == 0);
            assert(v.nth(9) - v.nth(8) == 1);

            assert(v.nth(9) - v.nth(9) == 0);
        }

        {
            assert(v.nth(0) - v.nth(0) == -0);
            assert(v.nth(0) - v.nth(1) == -1);
            assert(v.nth(0) - v.nth(2) == -2);
            assert(v.nth(0) - v.nth(3) == -3);
            assert(v.nth(0) - v.nth(4) == -4);
            assert(v.nth(0) - v.nth(5) == -5);
            assert(v.nth(0) - v.nth(6) == -6);
            assert(v.nth(0) - v.nth(7) == -7);
            assert(v.nth(0) - v.nth(8) == -8);
            assert(v.nth(0) - v.nth(9) == -9);

            assert(v.nth(1) - v.nth(1) == -0);
            assert(v.nth(1) - v.nth(2) == -1);
            assert(v.nth(1) - v.nth(3) == -2);
            assert(v.nth(1) - v.nth(4) == -3);
            assert(v.nth(1) - v.nth(5) == -4);
            assert(v.nth(1) - v.nth(6) == -5);
            assert(v.nth(1) - v.nth(7) == -6);
            assert(v.nth(1) - v.nth(8) == -7);
            assert(v.nth(1) - v.nth(9) == -8);

            assert(v.nth(2) - v.nth(2) == -0);
            assert(v.nth(2) - v.nth(3) == -1);
            assert(v.nth(2) - v.nth(4) == -2);
            assert(v.nth(2) - v.nth(5) == -3);
            assert(v.nth(2) - v.nth(6) == -4);
            assert(v.nth(2) - v.nth(7) == -5);
            assert(v.nth(2) - v.nth(8) == -6);
            assert(v.nth(2) - v.nth(9) == -7);

            assert(v.nth(3) - v.nth(3) == -0);
            assert(v.nth(3) - v.nth(4) == -1);
            assert(v.nth(3) - v.nth(5) == -2);
            assert(v.nth(3) - v.nth(6) == -3);
            assert(v.nth(3) - v.nth(7) == -4);
            assert(v.nth(3) - v.nth(8) == -5);
            assert(v.nth(3) - v.nth(9) == -6);

            assert(v.nth(4) - v.nth(4) == -0);
            assert(v.nth(4) - v.nth(5) == -1);
            assert(v.nth(4) - v.nth(6) == -2);
            assert(v.nth(4) - v.nth(7) == -3);
            assert(v.nth(4) - v.nth(8) == -4);
            assert(v.nth(4) - v.nth(9) == -5);

            assert(v.nth(5) - v.nth(5) == -0);
            assert(v.nth(5) - v.nth(6) == -1);
            assert(v.nth(5) - v.nth(7) == -2);
            assert(v.nth(5) - v.nth(8) == -3);
            assert(v.nth(5) - v.nth(9) == -4);

            assert(v.nth(6) - v.nth(6) == -0);
            assert(v.nth(6) - v.nth(7) == -1);
            assert(v.nth(6) - v.nth(8) == -2);
            assert(v.nth(6) - v.nth(9) == -3);

            assert(v.nth(7) - v.nth(7) == -0);
            assert(v.nth(7) - v.nth(8) == -1);
            assert(v.nth(7) - v.nth(9) == -2);

            assert(v.nth(8) - v.nth(8) == -0);
            assert(v.nth(8) - v.nth(9) == -1);

            assert(v.nth(9) - v.nth(9) == -0);
        }

        {
            assert(v.nth(0) < v.nth(1));
            assert(v.nth(0) < v.nth(2));
            assert(v.nth(0) < v.nth(3));
            assert(v.nth(0) < v.nth(4));
            assert(v.nth(0) < v.nth(5));
            assert(v.nth(0) < v.nth(6));
            assert(v.nth(0) < v.nth(7));
            assert(v.nth(0) < v.nth(8));
            assert(v.nth(0) < v.nth(9));

            assert(v.nth(1) < v.nth(2));
            assert(v.nth(1) < v.nth(3));
            assert(v.nth(1) < v.nth(4));
            assert(v.nth(1) < v.nth(5));
            assert(v.nth(1) < v.nth(6));
            assert(v.nth(1) < v.nth(7));
            assert(v.nth(1) < v.nth(8));
            assert(v.nth(1) < v.nth(9));

            assert(v.nth(2) < v.nth(3));
            assert(v.nth(2) < v.nth(4));
            assert(v.nth(2) < v.nth(5));
            assert(v.nth(2) < v.nth(6));
            assert(v.nth(2) < v.nth(7));
            assert(v.nth(2) < v.nth(8));
            assert(v.nth(2) < v.nth(9));

            assert(v.nth(3) < v.nth(4));
            assert(v.nth(3) < v.nth(5));
            assert(v.nth(3) < v.nth(6));
            assert(v.nth(3) < v.nth(7));
            assert(v.nth(3) < v.nth(8));
            assert(v.nth(3) < v.nth(9));

            assert(v.nth(4) < v.nth(5));
            assert(v.nth(4) < v.nth(6));
            assert(v.nth(4) < v.nth(7));
            assert(v.nth(4) < v.nth(8));
            assert(v.nth(4) < v.nth(9));

            assert(v.nth(5) < v.nth(6));
            assert(v.nth(5) < v.nth(7));
            assert(v.nth(5) < v.nth(8));
            assert(v.nth(5) < v.nth(9));

            assert(v.nth(6) < v.nth(7));
            assert(v.nth(6) < v.nth(8));
            assert(v.nth(6) < v.nth(9));

            assert(v.nth(7) < v.nth(8));
            assert(v.nth(7) < v.nth(9));

            assert(v.nth(8) < v.nth(9));
        }
    }

    cout << "Test insert(const_iterator, const T&)." << endl;
    {
        // Only one test is enough. `insert` calls `emplace`.

        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            const MyInt i(10);

            cout << ">" << endl;
            auto res = v.insert(v.nth(0), i);
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 1);
            assert(v[0] == 10);
        }
    }

    cout << "Test insert(const_iterator, T&&)." << endl;
    {
        // Only one test is enough. `insert` calls `emplace`.

        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            MyInt i(10);

            cout << ">" << endl;
            auto res = v.insert(v.nth(0), std::move(i));
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(i == -10);
            assert(v.size() == 1);
            assert(v[0] == 10);
        }
    }

    cout << "Test insert(const_iterator, size_type, const T&)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(0), 5, MyInt(10));
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 5);
            assert(v[0] == 10);
            assert(v[1] == 10);
            assert(v[2] == 10);
            assert(v[3] == 10);
            assert(v[4] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(1), 2, MyInt(20));
            cout << "<" << endl;

            assert(res == v.nth(1));
            assert(v.size() == 7);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 20);
            assert(v[3] == 10);
            assert(v[4] == 10);
            assert(v[5] == 10);
            assert(v[6] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(3), 10, MyInt(30));
            cout << "<" << endl;

            assert(res == v.nth(3));
            assert(v.size() == 17);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 20);
            assert(v[3] == 30);
            assert(v[4] == 30);
            assert(v[5] == 30);
            assert(v[6] == 30);
            assert(v[7] == 30);
            assert(v[8] == 30);
            assert(v[9] == 30);
            assert(v[10] == 30);
            assert(v[11] == 30);
            assert(v[12] == 30);
            assert(v[13] == 10);
            assert(v[14] == 10);
            assert(v[15] == 10);
            assert(v[16] == 10);
        }
    }

    cout << "Test insert(const_iterator, InputIt, InputIt)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            std::istringstream iss("100 101 102 103 104 105 106 107 108 109");

            cout << ">" << endl;
            auto res = v.insert
            (
                v.nth(0),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 10);
            assert(v[0] == 100);
            assert(v[1] == 101);
            assert(v[2] == 102);
            assert(v[3] == 103);
            assert(v[4] == 104);
            assert(v[5] == 105);
            assert(v[6] == 106);
            assert(v[7] == 107);
            assert(v[8] == 108);
            assert(v[9] == 109);
        }

        {
            std::istringstream iss("200 201 202 203 204 205 206 207 208 209");

            cout << ">" << endl;
            auto res = v.insert
            (
                v.nth(7),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            assert(res == v.nth(7));
            assert(v.size() == 20);
            assert(v[0] == 100);
            assert(v[1] == 101);
            assert(v[2] == 102);
            assert(v[3] == 103);
            assert(v[4] == 104);
            assert(v[5] == 105);
            assert(v[6] == 106);
            assert(v[7] == 200);
            assert(v[8] == 201);
            assert(v[9] == 202);
            assert(v[10] == 203);
            assert(v[11] == 204);
            assert(v[12] == 205);
            assert(v[13] == 206);
            assert(v[14] == 207);
            assert(v[15] == 208);
            assert(v[16] == 209);
            assert(v[17] == 107);
            assert(v[18] == 108);
            assert(v[19] == 109);
        }
    }

    cout << "Test insert(const_iterator, ForwardIt, ForwardIt)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            const std::vector<MyInt> data({100, 101, 102, 103, 104, 105, 106, 107, 108, 109});

            cout << ">" << endl;
            auto res = v.insert(v.begin(), data.begin(), data.end());
            cout << "<" << endl;

            assert(res == v.nth(0));
            assert(v.size() == 10);
            assert(v[0] == 100);
            assert(v[1] == 101);
            assert(v[2] == 102);
            assert(v[3] == 103);
            assert(v[4] == 104);
            assert(v[5] == 105);
            assert(v[6] == 106);
            assert(v[7] == 107);
            assert(v[8] == 108);
            assert(v[9] == 109);
        }

        {
            const std::vector<MyInt> data({200, 201, 202});

            cout << ">" << endl;
            auto res = v.insert(v.nth(2), data.begin(), data.end());
            cout << "<" << endl;

            assert(res == v.nth(2));
            assert(v.size() == 13);
            assert(v[0] == 100);
            assert(v[1] == 101);
            assert(v[2] == 200);
            assert(v[3] == 201);
            assert(v[4] == 202);
            assert(v[5] == 102);
            assert(v[6] == 103);
            assert(v[7] == 104);
            assert(v[8] == 105);
            assert(v[9] == 106);
            assert(v[10] == 107);
            assert(v[11] == 108);
            assert(v[12] == 109);
        }

        {
            const std::vector<MyInt> data({300, 301, 302, 303, 304, 305, 306});

            cout << ">" << endl;
            auto res = v.insert(v.nth(11), data.begin(), data.end());
            cout << "<" << endl;

            assert(res == v.nth(11));
            assert(v.size() == 20);
            assert(v[0] == 100);
            assert(v[1] == 101);
            assert(v[2] == 200);
            assert(v[3] == 201);
            assert(v[4] == 202);
            assert(v[5] == 102);
            assert(v[6] == 103);
            assert(v[7] == 104);
            assert(v[8] == 105);
            assert(v[9] == 106);
            assert(v[10] == 107);
            assert(v[11] == 300);
            assert(v[12] == 301);
            assert(v[13] == 302);
            assert(v[14] == 303);
            assert(v[15] == 304);
            assert(v[16] == 305);
            assert(v[17] == 306);
            assert(v[18] == 108);
            assert(v[19] == 109);
        }
    }

    cout << "Test insert(const_iterator, MoveIterator, MoveIterator)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

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

    cout << "Test push_back(const T&)." << endl;
    {
        // Only one test is enough. `push_back` calls `emplace`.

        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            const MyInt i(10);

            cout << ">" << endl;
            v.push_back(i);
            cout << "<" << endl;

            assert(v.size() == 1);
            assert(v[0] == 10);
        }
    }

    cout << "Test push_back(T&&)." << endl;
    {
        // Only one test is enough. `push_back` calls `emplace`.

        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            MyInt i(10);

            cout << ">" << endl;
            v.push_back(std::move(i));
            cout << "<" << endl;

            assert(i == -10);
            assert(v.size() == 1);
            assert(v[0] == 10);
        }
    }

    cout << "Test pop_back()." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

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
            v.resize(10);
            cout << "<" << endl;

            assert(v.size() == 10);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[4] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[5] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[6] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[7] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[8] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[9] == SFL_MY_INT_DEFAULT_VALUE);
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
            v.resize(4);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v[0] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[1] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[2] == SFL_MY_INT_DEFAULT_VALUE);
            assert(v[3] == SFL_MY_INT_DEFAULT_VALUE);
        }
    }

    cout << "Test resize(size_type, const T&)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

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
            v.resize(10, 40);
            cout << "<" << endl;

            assert(v.size() == 10);
            assert(v[0] == 10);
            assert(v[1] == 20);
            assert(v[2] == 30);
            assert(v[3] == 40);
            assert(v[4] == 40);
            assert(v[5] == 40);
            assert(v[6] == 40);
            assert(v[7] == 40);
            assert(v[8] == 40);
            assert(v[9] == 40);
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
            v.resize(4, 70);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v[0] == 70);
            assert(v[1] == 70);
            assert(v[2] == 70);
            assert(v[3] == 70);
        }
    }

    cout << "Test swap(segmented_vector&)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1;
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2;

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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

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

    cout << "Test reserve(size_type) and shrink_to_fit()." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        assert(v.size() == 0);

        const auto cap1 = v.capacity();

        v.reserve(50);

        const auto cap2 = v.capacity();

        assert(cap2 >= cap1);

        v.emplace_back(10);
        v.emplace_back(20);
        v.emplace_back(30);
        v.emplace_back(40);
        v.emplace_back(50);
        v.emplace_back(60);
        v.emplace_back(70);
        v.emplace_back(80);
        v.emplace_back(90);

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

        v.shrink_to_fit();

        const auto cap3 = v.capacity();

        assert(cap3 <= cap2);

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

        v.reserve(200);

        const auto cap4 = v.capacity();

        assert(cap4 >= cap3);

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

        v.shrink_to_fit();

        const auto cap5 = v.capacity();

        assert(cap5 == cap3);
    }

    cout << "Test constructor()." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1;
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2(alloc);

        assert(v1.size() == 0);
        assert(v2.size() == 0);
    }

    cout << "Test constructor(size_type)." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1(3);
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2(3, alloc);

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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1(3, 42);
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2(3, 42, alloc);
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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1
        (
            (std::istream_iterator<int>(iss1)),
            (std::istream_iterator<int>())
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2
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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1
        (
            data.begin(),
            data.end()
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2
        (
            data.begin(),
            data.end(),
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

    cout << "Test constructor(MoveIterator, MoveIterator)." << endl;
    {
        TP_ALLOC<MyInt> alloc;

        std::vector<MyInt> data1({10, 20, 30, 40});
        std::vector<MyInt> data2({10, 20, 30, 40});

        cout << ">" << endl;
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1
        (
            std::make_move_iterator(data1.begin()),
            std::make_move_iterator(data1.end())
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2
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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1({10, 20, 30, 40});
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2({10, 20, 30, 40}, alloc);
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

    cout << "Test constructor(const segmented_vector&)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1({10, 20, 30, 40, 50});

        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2(v1);

        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v3(v1, TP_ALLOC<MyInt>());

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

    cout << "Test constructor(segmented_vector&&)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1({10, 20, 30, 40, 50});

        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2(std::move(v1));

        assert(v1.size() == 0);

        assert(v2.size() == 5);
        assert(v2[0] == 10);
        assert(v2[1] == 20);
        assert(v2[2] == 30);
        assert(v2[3] == 40);
        assert(v2[4] == 50);

        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v3(std::move(v2), TP_ALLOC<MyInt>());

        assert(v2.size() == 0);

        assert(v3.size() == 5);
        assert(v3[0] == 10);
        assert(v3[1] == 20);
        assert(v3[2] == 30);
        assert(v3[3] == 40);
        assert(v3[4] == 50);
    }

    cout << "Test assign(size_type, const T&)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.assign(10, 10);
            cout << "<" << endl;

            assert(v.size() == 10);
            assert(v[0] == 10);
            assert(v[1] == 10);
            assert(v[2] == 10);
            assert(v[3] == 10);
            assert(v[4] == 10);
            assert(v[5] == 10);
            assert(v[6] == 10);
            assert(v[7] == 10);
            assert(v[8] == 10);
            assert(v[9] == 10);
        }

        {
            cout << ">" << endl;
            v.assign(5, 20);
            cout << "<" << endl;

            assert(v.size() == 5);
            assert(v[0] == 20);
            assert(v[1] == 20);
            assert(v[2] == 20);
            assert(v[3] == 20);
            assert(v[4] == 20);
        }

        {
            cout << ">" << endl;
            v.assign(9, 30);
            cout << "<" << endl;

            assert(v.size() == 9);
            assert(v[0] == 30);
            assert(v[1] == 30);
            assert(v[2] == 30);
            assert(v[3] == 30);
            assert(v[4] == 30);
            assert(v[5] == 30);
            assert(v[6] == 30);
            assert(v[7] == 30);
            assert(v[8] == 30);
        }

        {
            cout << ">" << endl;
            v.assign(0, 40);
            cout << "<" << endl;

            assert(v.size() == 0);
        }

        {
            cout << ">" << endl;
            v.assign(4, 50);
            cout << "<" << endl;

            assert(v.size() == 4);
            assert(v[0] == 50);
            assert(v[1] == 50);
            assert(v[2] == 50);
            assert(v[3] == 50);
        }
    }

    cout << "Test assign(InputIt, InputIt)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            std::istringstream iss("11 12 13 14 15 16 17 18 19");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            assert(v.size() == 9);
            assert(v[0] == 11);
            assert(v[1] == 12);
            assert(v[2] == 13);
            assert(v[3] == 14);
            assert(v[4] == 15);
            assert(v[5] == 16);
            assert(v[6] == 17);
            assert(v[7] == 18);
            assert(v[8] == 19);
        }

        {
            std::istringstream iss("21 22 23 24 25");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            assert(v.size() == 5);
            assert(v[0] == 21);
            assert(v[1] == 22);
            assert(v[2] == 23);
            assert(v[3] == 24);
            assert(v[4] == 25);
        }

        {
            std::istringstream iss("31 32 33 34 35 36 37");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            assert(v.size() == 7);
            assert(v[0] == 31);
            assert(v[1] == 32);
            assert(v[2] == 33);
            assert(v[3] == 34);
            assert(v[4] == 35);
            assert(v[5] == 36);
            assert(v[6] == 37);
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

        {
            std::istringstream iss("41 42");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 41);
            assert(v[1] == 42);
        }
    }

    cout << "Test assign(ForwardIt, ForwardIt)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            const std::vector<int> data({11, 12, 13, 14, 15, 16, 17, 18, 19});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 9);
            assert(v[0] == 11);
            assert(v[1] == 12);
            assert(v[2] == 13);
            assert(v[3] == 14);
            assert(v[4] == 15);
            assert(v[5] == 16);
            assert(v[6] == 17);
            assert(v[7] == 18);
            assert(v[8] == 19);
        }

        {
            const std::vector<int> data({21, 22, 23, 24, 25});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 5);
            assert(v[0] == 21);
            assert(v[1] == 22);
            assert(v[2] == 23);
            assert(v[3] == 24);
            assert(v[4] == 25);
        }

        {
            const std::vector<int> data({31, 32, 33, 34, 35, 36, 37});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 7);
            assert(v[0] == 31);
            assert(v[1] == 32);
            assert(v[2] == 33);
            assert(v[3] == 34);
            assert(v[4] == 35);
            assert(v[5] == 36);
            assert(v[6] == 37);
        }

        {
            const std::vector<int> data;

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 0);
        }

        {
            const std::vector<int> data({41, 42});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 41);
            assert(v[1] == 42);
        }
    }

    cout << "Test assign(MoveIterator, MoveIterator)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            std::vector<MyInt> data({11, 12, 13, 14, 15, 16, 17, 18, 19});

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
            assert(data[3] == -14);
            assert(data[4] == -15);
            assert(data[5] == -16);
            assert(data[6] == -17);
            assert(data[7] == -18);
            assert(data[8] == -19);
            assert(v.size() == 9);
            assert(v[0] == 11);
            assert(v[1] == 12);
            assert(v[2] == 13);
            assert(v[3] == 14);
            assert(v[4] == 15);
            assert(v[5] == 16);
            assert(v[6] == 17);
            assert(v[7] == 18);
            assert(v[8] == 19);
        }

        {
            std::vector<MyInt> data({21, 22, 23, 24, 25});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            assert(data[0] == -21);
            assert(data[1] == -22);
            assert(data[2] == -23);
            assert(data[3] == -24);
            assert(data[4] == -25);
            assert(v.size() == 5);
            assert(v[0] == 21);
            assert(v[1] == 22);
            assert(v[2] == 23);
            assert(v[3] == 24);
            assert(v[4] == 25);
        }

        {
            std::vector<MyInt> data({31, 32, 33, 34, 35, 36, 37});

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
            assert(data[4] == -35);
            assert(data[5] == -36);
            assert(data[6] == -37);
            assert(v.size() == 7);
            assert(v[0] == 31);
            assert(v[1] == 32);
            assert(v[2] == 33);
            assert(v[3] == 34);
            assert(v[4] == 35);
            assert(v[5] == 36);
            assert(v[6] == 37);
        }

        {
            std::vector<MyInt> data;

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            assert(v.size() == 0);
        }
    }

    cout << "Test assign(std::initializer_list)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v;

        {
            cout << ">" << endl;
            v.assign({11, 12, 13, 14, 15, 16, 17, 18, 19});
            cout << "<" << endl;

            assert(v.size() == 9);
            assert(v[0] == 11);
            assert(v[1] == 12);
            assert(v[2] == 13);
            assert(v[3] == 14);
            assert(v[4] == 15);
            assert(v[5] == 16);
            assert(v[6] == 17);
            assert(v[7] == 18);
            assert(v[8] == 19);
        }

        {
            cout << ">" << endl;
            v.assign({21, 22, 23, 24, 25});
            cout << "<" << endl;

            assert(v.size() == 5);
            assert(v[0] == 21);
            assert(v[1] == 22);
            assert(v[2] == 23);
            assert(v[3] == 24);
            assert(v[4] == 25);
        }

        {
            cout << ">" << endl;
            v.assign({31, 32, 33, 34, 35, 36, 37});
            cout << "<" << endl;

            assert(v.size() == 7);
            assert(v[0] == 31);
            assert(v[1] == 32);
            assert(v[2] == 33);
            assert(v[3] == 34);
            assert(v[4] == 35);
            assert(v[5] == 36);
            assert(v[6] == 37);
        }

        {
            const std::vector<int> data;

            cout << ">" << endl;
            v.assign({});
            cout << "<" << endl;

            assert(v.size() == 0);
        }

        {
            cout << ">" << endl;
            v.assign({41, 42});
            cout << "<" << endl;

            assert(v.size() == 2);
            assert(v[0] == 41);
            assert(v[1] == 42);
        }
    }

    cout << "Test operator=(const segmented_vector&)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1({10, 20, 30});
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2({40, 50});

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

    cout << "Test operator=(segmented_vector&&)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1({10, 20, 30});
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2({40, 50});

        assert(v1.size() == 3);
        assert(v2.size() == 2);

        cout << ">" << endl;
        v1 = std::move(v2);
        cout << "<" << endl;

        assert(v1.size() == 2);
        assert(v1[0] == 40);
        assert(v1[1] == 50);

        assert(v2.size() == 0);

        cout << ">" << endl;
        v2 = std::move(v1);
        cout << "<" << endl;

        assert(v1.size() == 0);

        assert(v2.size() == 2);
        assert(v2[0] == 40);
        assert(v2[1] == 50);
    }

    cout << "Test operator=(std::initializer_list)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1({10, 20, 30});
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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1({10, 20, 30});
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2({10, 20, 30, 40});

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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1({10, 11, 12});
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v2({20, 21, 22});

        using std::swap;
        swap(v1, v2);
    }

    cout << "Test non-member erase(compact_vector&, const U&)." << endl;
    {
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1({10, 20, 20, 30, 30, 30});

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
        sfl::segmented_vector<MyInt, TP_N, TP_ALLOC<MyInt>> v1({10, 20, 20, 30, 30, 30});

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
