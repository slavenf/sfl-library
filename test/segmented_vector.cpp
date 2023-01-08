//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include segmented_vector.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include <sfl/segmented_vector.hpp>

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

#ifndef TPARAM_N
#define TPARAM_N 4
#endif

#define CHECK(expr) assert(expr)

int main()
{
    using std::cout;
    using std::endl;
    using sfl::test::xint;

    cout << "Test non-modifying member functions on empty container." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1;
        const sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2;

        CHECK(v1.empty());
        CHECK(v2.empty());

        CHECK(v1.size() == 0);
        CHECK(v2.size() == 0);

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

    cout << "Test emplace_back(Args&&...) (1)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.emplace_back(10);
            cout << "<" << endl;

            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        {
            cout << ">" << endl;
            v.emplace_back(20);
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        {
            cout << ">" << endl;
            v.emplace_back(30);
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            cout << ">" << endl;
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
            v.emplace_back(60);
            cout << "<" << endl;

            CHECK(v.size() == 6);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
            CHECK(v[5] == 60);
        }

        {
            cout << ">" << endl;
            v.emplace_back(70);
            cout << "<" << endl;

            CHECK(v.size() == 7);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
            CHECK(v[5] == 60);
            CHECK(v[6] == 70);
        }

        {
            cout << ">" << endl;
            v.emplace_back(80);
            cout << "<" << endl;

            CHECK(v.size() == 8);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
            CHECK(v[5] == 60);
            CHECK(v[6] == 70);
            CHECK(v[7] == 80);
        }

        {
            cout << ">" << endl;
            v.emplace_back(90);
            cout << "<" << endl;

            CHECK(v.size() == 9);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
            CHECK(v[5] == 60);
            CHECK(v[6] == 70);
            CHECK(v[7] == 80);
            CHECK(v[8] == 90);
        }

        {
            cout << ">" << endl;
            v.emplace_back(100);
            cout << "<" << endl;

            CHECK(v.size() == 10);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
            CHECK(v[5] == 60);
            CHECK(v[6] == 70);
            CHECK(v[7] == 80);
            CHECK(v[8] == 90);
            CHECK(v[9] == 100);
        }

        {
            cout << ">" << endl;
            v.emplace_back(110);
            cout << "<" << endl;

            CHECK(v.size() == 11);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
            CHECK(v[5] == 60);
            CHECK(v[6] == 70);
            CHECK(v[7] == 80);
            CHECK(v[8] == 90);
            CHECK(v[9] == 100);
            CHECK(v[10] == 110);
        }

        {
            cout << ">" << endl;
            v.emplace_back(120);
            cout << "<" << endl;

            CHECK(v.size() == 12);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
            CHECK(v[5] == 60);
            CHECK(v[6] == 70);
            CHECK(v[7] == 80);
            CHECK(v[8] == 90);
            CHECK(v[9] == 100);
            CHECK(v[10] == 110);
            CHECK(v[11] == 120);
        }

        {
            cout << ">" << endl;
            v.emplace_back(130);
            cout << "<" << endl;

            CHECK(v.size() == 13);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
            CHECK(v[5] == 60);
            CHECK(v[6] == 70);
            CHECK(v[7] == 80);
            CHECK(v[8] == 90);
            CHECK(v[9] == 100);
            CHECK(v[10] == 110);
            CHECK(v[11] == 120);
            CHECK(v[12] == 130);
        }
    }

    cout << "Test emplace_back(Args&&...) (2)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        constexpr int n = 100;

        for (int i = 0; i < n; ++i)
        {
            v.emplace_back(i);
        }
    }

    cout << "Test emplace(const_iterator, Args&&...) (1)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 10);
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 20);
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 2);
            CHECK(v[0] == 20);
            CHECK(v[1] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 30);
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 3);
            CHECK(v[0] == 30);
            CHECK(v[1] == 20);
            CHECK(v[2] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 40);
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 4);
            CHECK(v[0] == 40);
            CHECK(v[1] == 30);
            CHECK(v[2] == 20);
            CHECK(v[3] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 50);
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 5);
            CHECK(v[0] == 50);
            CHECK(v[1] == 40);
            CHECK(v[2] == 30);
            CHECK(v[3] == 20);
            CHECK(v[4] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(0), 60);
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 6);
            CHECK(v[0] == 60);
            CHECK(v[1] == 50);
            CHECK(v[2] == 40);
            CHECK(v[3] == 30);
            CHECK(v[4] == 20);
            CHECK(v[5] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(3), 70);
            cout << "<" << endl;

            CHECK(res == v.nth(3));
            CHECK(v.size() == 7);
            CHECK(v[0] == 60);
            CHECK(v[1] == 50);
            CHECK(v[2] == 40);
            CHECK(v[3] == 70);
            CHECK(v[4] == 30);
            CHECK(v[5] == 20);
            CHECK(v[6] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(5), 80);
            cout << "<" << endl;

            CHECK(res == v.nth(5));
            CHECK(v.size() == 8);
            CHECK(v[0] == 60);
            CHECK(v[1] == 50);
            CHECK(v[2] == 40);
            CHECK(v[3] == 70);
            CHECK(v[4] == 30);
            CHECK(v[5] == 80);
            CHECK(v[6] == 20);
            CHECK(v[7] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(8), 90);
            cout << "<" << endl;

            CHECK(res == v.nth(8));
            CHECK(v.size() == 9);
            CHECK(v[0] == 60);
            CHECK(v[1] == 50);
            CHECK(v[2] == 40);
            CHECK(v[3] == 70);
            CHECK(v[4] == 30);
            CHECK(v[5] == 80);
            CHECK(v[6] == 20);
            CHECK(v[7] == 10);
            CHECK(v[8] == 90);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(8), 100);
            cout << "<" << endl;

            CHECK(res == v.nth(8));
            CHECK(v.size() == 10);
            CHECK(v[0] == 60);
            CHECK(v[1] == 50);
            CHECK(v[2] == 40);
            CHECK(v[3] == 70);
            CHECK(v[4] == 30);
            CHECK(v[5] == 80);
            CHECK(v[6] == 20);
            CHECK(v[7] == 10);
            CHECK(v[8] == 100);
            CHECK(v[9] == 90);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(8), 110);
            cout << "<" << endl;

            CHECK(res == v.nth(8));
            CHECK(v.size() == 11);
            CHECK(v[0] == 60);
            CHECK(v[1] == 50);
            CHECK(v[2] == 40);
            CHECK(v[3] == 70);
            CHECK(v[4] == 30);
            CHECK(v[5] == 80);
            CHECK(v[6] == 20);
            CHECK(v[7] == 10);
            CHECK(v[8] == 110);
            CHECK(v[9] == 100);
            CHECK(v[10] == 90);
        }

        {
            cout << ">" << endl;
            auto res = v.emplace(v.nth(8), 120);
            cout << "<" << endl;

            CHECK(res == v.nth(8));
            CHECK(v.size() == 12);
            CHECK(v[0] == 60);
            CHECK(v[1] == 50);
            CHECK(v[2] == 40);
            CHECK(v[3] == 70);
            CHECK(v[4] == 30);
            CHECK(v[5] == 80);
            CHECK(v[6] == 20);
            CHECK(v[7] == 10);
            CHECK(v[8] == 120);
            CHECK(v[9] == 110);
            CHECK(v[10] == 100);
            CHECK(v[11] == 90);
        }
    }

    cout << "Test emplace(const_iterator, Args&&...) (2)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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
            CHECK(v.at(0) == 10);
            CHECK(v.at(1) == 20);
            CHECK(v.at(2) == 30);
            CHECK(v.at(3) == 40);
            CHECK(v.at(4) == 50);
            CHECK(v.at(5) == 60);
            CHECK(v.at(6) == 70);
            CHECK(v.at(7) == 80);
            CHECK(v.at(8) == 90);
        }

        {
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
            CHECK(v[5] == 60);
            CHECK(v[6] == 70);
            CHECK(v[7] == 80);
            CHECK(v[8] == 90);
        }

        {
            CHECK(v.front() == 10);
        }

        {
            CHECK(v.back() == 90);
        }

        {
            CHECK(*v.nth(0) == v.at(0));
            CHECK(*v.nth(1) == v.at(1));
            CHECK(*v.nth(2) == v.at(2));
            CHECK(*v.nth(3) == v.at(3));
            CHECK(*v.nth(4) == v.at(4));
            CHECK(*v.nth(5) == v.at(5));
            CHECK(*v.nth(6) == v.at(6));
            CHECK(*v.nth(7) == v.at(7));
            CHECK(*v.nth(8) == v.at(8));
        }

        {
            CHECK(v.index_of(v.nth(0)) == 0);
            CHECK(v.index_of(v.nth(1)) == 1);
            CHECK(v.index_of(v.nth(2)) == 2);
            CHECK(v.index_of(v.nth(3)) == 3);
            CHECK(v.index_of(v.nth(4)) == 4);
            CHECK(v.index_of(v.nth(5)) == 5);
            CHECK(v.index_of(v.nth(6)) == 6);
            CHECK(v.index_of(v.nth(7)) == 7);
            CHECK(v.index_of(v.nth(8)) == 8);
            CHECK(v.index_of(v.nth(9)) == 9);
        }

        {
            auto it = v.begin();
            CHECK(++it == v.nth(1));
            CHECK(++it == v.nth(2));
            CHECK(++it == v.nth(3));
            CHECK(++it == v.nth(4));
            CHECK(++it == v.nth(5));
            CHECK(++it == v.nth(6));
            CHECK(++it == v.nth(7));
            CHECK(++it == v.nth(8));
            CHECK(++it == v.nth(9));

            auto cit = v.cbegin();
            CHECK(++cit == v.nth(1));
            CHECK(++cit == v.nth(2));
            CHECK(++cit == v.nth(3));
            CHECK(++cit == v.nth(4));
            CHECK(++cit == v.nth(5));
            CHECK(++cit == v.nth(6));
            CHECK(++cit == v.nth(7));
            CHECK(++cit == v.nth(8));
            CHECK(++cit == v.nth(9));
        }

        {
            auto it = v.begin();
            CHECK(it++ == v.nth(0));
            CHECK(it++ == v.nth(1));
            CHECK(it++ == v.nth(2));
            CHECK(it++ == v.nth(3));
            CHECK(it++ == v.nth(4));
            CHECK(it++ == v.nth(5));
            CHECK(it++ == v.nth(6));
            CHECK(it++ == v.nth(7));
            CHECK(it++ == v.nth(8));

            auto cit = v.cbegin();
            CHECK(cit++ == v.nth(0));
            CHECK(cit++ == v.nth(1));
            CHECK(cit++ == v.nth(2));
            CHECK(cit++ == v.nth(3));
            CHECK(cit++ == v.nth(4));
            CHECK(cit++ == v.nth(5));
            CHECK(cit++ == v.nth(6));
            CHECK(cit++ == v.nth(7));
            CHECK(cit++ == v.nth(8));
        }

        {
            auto it = v.end();
            CHECK(--it == v.nth(8));
            CHECK(--it == v.nth(7));
            CHECK(--it == v.nth(6));
            CHECK(--it == v.nth(5));
            CHECK(--it == v.nth(4));
            CHECK(--it == v.nth(3));
            CHECK(--it == v.nth(2));
            CHECK(--it == v.nth(1));
            CHECK(--it == v.nth(0));

            auto cit = v.cend();
            CHECK(--cit == v.nth(8));
            CHECK(--cit == v.nth(7));
            CHECK(--cit == v.nth(6));
            CHECK(--cit == v.nth(5));
            CHECK(--cit == v.nth(4));
            CHECK(--cit == v.nth(3));
            CHECK(--cit == v.nth(2));
            CHECK(--cit == v.nth(1));
            CHECK(--cit == v.nth(0));
        }

        {
            auto it = v.end();
            CHECK(it-- == v.nth(9));
            CHECK(it-- == v.nth(8));
            CHECK(it-- == v.nth(7));
            CHECK(it-- == v.nth(6));
            CHECK(it-- == v.nth(5));
            CHECK(it-- == v.nth(4));
            CHECK(it-- == v.nth(3));
            CHECK(it-- == v.nth(2));
            CHECK(it-- == v.nth(1));

            auto cit = v.cend();
            CHECK(cit-- == v.nth(9));
            CHECK(cit-- == v.nth(8));
            CHECK(cit-- == v.nth(7));
            CHECK(cit-- == v.nth(6));
            CHECK(cit-- == v.nth(5));
            CHECK(cit-- == v.nth(4));
            CHECK(cit-- == v.nth(3));
            CHECK(cit-- == v.nth(2));
            CHECK(cit-- == v.nth(1));
        }


        {
            CHECK(v.begin() + 0 == v.nth(0));
            CHECK(v.begin() + 1 == v.nth(1));
            CHECK(v.begin() + 2 == v.nth(2));
            CHECK(v.begin() + 3 == v.nth(3));
            CHECK(v.begin() + 4 == v.nth(4));
            CHECK(v.begin() + 5 == v.nth(5));
            CHECK(v.begin() + 6 == v.nth(6));
            CHECK(v.begin() + 7 == v.nth(7));
            CHECK(v.begin() + 8 == v.nth(8));
            CHECK(v.begin() + 9 == v.nth(9));

            CHECK(v.cbegin() + 0 == v.nth(0));
            CHECK(v.cbegin() + 1 == v.nth(1));
            CHECK(v.cbegin() + 2 == v.nth(2));
            CHECK(v.cbegin() + 3 == v.nth(3));
            CHECK(v.cbegin() + 4 == v.nth(4));
            CHECK(v.cbegin() + 5 == v.nth(5));
            CHECK(v.cbegin() + 6 == v.nth(6));
            CHECK(v.cbegin() + 7 == v.nth(7));
            CHECK(v.cbegin() + 8 == v.nth(8));
            CHECK(v.cbegin() + 9 == v.nth(9));
        }

        {
            CHECK(v.end() - 0 == v.nth(9));
            CHECK(v.end() - 1 == v.nth(8));
            CHECK(v.end() - 2 == v.nth(7));
            CHECK(v.end() - 3 == v.nth(6));
            CHECK(v.end() - 4 == v.nth(5));
            CHECK(v.end() - 5 == v.nth(4));
            CHECK(v.end() - 6 == v.nth(3));
            CHECK(v.end() - 7 == v.nth(2));
            CHECK(v.end() - 8 == v.nth(1));
            CHECK(v.end() - 9 == v.nth(0));

            CHECK(v.cend() - 0 == v.nth(9));
            CHECK(v.cend() - 1 == v.nth(8));
            CHECK(v.cend() - 2 == v.nth(7));
            CHECK(v.cend() - 3 == v.nth(6));
            CHECK(v.cend() - 4 == v.nth(5));
            CHECK(v.cend() - 5 == v.nth(4));
            CHECK(v.cend() - 6 == v.nth(3));
            CHECK(v.cend() - 7 == v.nth(2));
            CHECK(v.cend() - 8 == v.nth(1));
            CHECK(v.cend() - 9 == v.nth(0));
        }

        {
            CHECK(v.nth(0) - v.nth(0) == 0);
            CHECK(v.nth(1) - v.nth(0) == 1);
            CHECK(v.nth(2) - v.nth(0) == 2);
            CHECK(v.nth(3) - v.nth(0) == 3);
            CHECK(v.nth(4) - v.nth(0) == 4);
            CHECK(v.nth(5) - v.nth(0) == 5);
            CHECK(v.nth(6) - v.nth(0) == 6);
            CHECK(v.nth(7) - v.nth(0) == 7);
            CHECK(v.nth(8) - v.nth(0) == 8);
            CHECK(v.nth(9) - v.nth(0) == 9);

            CHECK(v.nth(1) - v.nth(1) == 0);
            CHECK(v.nth(2) - v.nth(1) == 1);
            CHECK(v.nth(3) - v.nth(1) == 2);
            CHECK(v.nth(4) - v.nth(1) == 3);
            CHECK(v.nth(5) - v.nth(1) == 4);
            CHECK(v.nth(6) - v.nth(1) == 5);
            CHECK(v.nth(7) - v.nth(1) == 6);
            CHECK(v.nth(8) - v.nth(1) == 7);
            CHECK(v.nth(9) - v.nth(1) == 8);

            CHECK(v.nth(2) - v.nth(2) == 0);
            CHECK(v.nth(3) - v.nth(2) == 1);
            CHECK(v.nth(4) - v.nth(2) == 2);
            CHECK(v.nth(5) - v.nth(2) == 3);
            CHECK(v.nth(6) - v.nth(2) == 4);
            CHECK(v.nth(7) - v.nth(2) == 5);
            CHECK(v.nth(8) - v.nth(2) == 6);
            CHECK(v.nth(9) - v.nth(2) == 7);

            CHECK(v.nth(3) - v.nth(3) == 0);
            CHECK(v.nth(4) - v.nth(3) == 1);
            CHECK(v.nth(5) - v.nth(3) == 2);
            CHECK(v.nth(6) - v.nth(3) == 3);
            CHECK(v.nth(7) - v.nth(3) == 4);
            CHECK(v.nth(8) - v.nth(3) == 5);
            CHECK(v.nth(9) - v.nth(3) == 6);

            CHECK(v.nth(4) - v.nth(4) == 0);
            CHECK(v.nth(5) - v.nth(4) == 1);
            CHECK(v.nth(6) - v.nth(4) == 2);
            CHECK(v.nth(7) - v.nth(4) == 3);
            CHECK(v.nth(8) - v.nth(4) == 4);
            CHECK(v.nth(9) - v.nth(4) == 5);

            CHECK(v.nth(5) - v.nth(5) == 0);
            CHECK(v.nth(6) - v.nth(5) == 1);
            CHECK(v.nth(7) - v.nth(5) == 2);
            CHECK(v.nth(8) - v.nth(5) == 3);
            CHECK(v.nth(9) - v.nth(5) == 4);

            CHECK(v.nth(6) - v.nth(6) == 0);
            CHECK(v.nth(7) - v.nth(6) == 1);
            CHECK(v.nth(8) - v.nth(6) == 2);
            CHECK(v.nth(9) - v.nth(6) == 3);

            CHECK(v.nth(7) - v.nth(7) == 0);
            CHECK(v.nth(8) - v.nth(7) == 1);
            CHECK(v.nth(9) - v.nth(7) == 2);

            CHECK(v.nth(8) - v.nth(8) == 0);
            CHECK(v.nth(9) - v.nth(8) == 1);

            CHECK(v.nth(9) - v.nth(9) == 0);
        }

        {
            CHECK(v.nth(0) - v.nth(0) == -0);
            CHECK(v.nth(0) - v.nth(1) == -1);
            CHECK(v.nth(0) - v.nth(2) == -2);
            CHECK(v.nth(0) - v.nth(3) == -3);
            CHECK(v.nth(0) - v.nth(4) == -4);
            CHECK(v.nth(0) - v.nth(5) == -5);
            CHECK(v.nth(0) - v.nth(6) == -6);
            CHECK(v.nth(0) - v.nth(7) == -7);
            CHECK(v.nth(0) - v.nth(8) == -8);
            CHECK(v.nth(0) - v.nth(9) == -9);

            CHECK(v.nth(1) - v.nth(1) == -0);
            CHECK(v.nth(1) - v.nth(2) == -1);
            CHECK(v.nth(1) - v.nth(3) == -2);
            CHECK(v.nth(1) - v.nth(4) == -3);
            CHECK(v.nth(1) - v.nth(5) == -4);
            CHECK(v.nth(1) - v.nth(6) == -5);
            CHECK(v.nth(1) - v.nth(7) == -6);
            CHECK(v.nth(1) - v.nth(8) == -7);
            CHECK(v.nth(1) - v.nth(9) == -8);

            CHECK(v.nth(2) - v.nth(2) == -0);
            CHECK(v.nth(2) - v.nth(3) == -1);
            CHECK(v.nth(2) - v.nth(4) == -2);
            CHECK(v.nth(2) - v.nth(5) == -3);
            CHECK(v.nth(2) - v.nth(6) == -4);
            CHECK(v.nth(2) - v.nth(7) == -5);
            CHECK(v.nth(2) - v.nth(8) == -6);
            CHECK(v.nth(2) - v.nth(9) == -7);

            CHECK(v.nth(3) - v.nth(3) == -0);
            CHECK(v.nth(3) - v.nth(4) == -1);
            CHECK(v.nth(3) - v.nth(5) == -2);
            CHECK(v.nth(3) - v.nth(6) == -3);
            CHECK(v.nth(3) - v.nth(7) == -4);
            CHECK(v.nth(3) - v.nth(8) == -5);
            CHECK(v.nth(3) - v.nth(9) == -6);

            CHECK(v.nth(4) - v.nth(4) == -0);
            CHECK(v.nth(4) - v.nth(5) == -1);
            CHECK(v.nth(4) - v.nth(6) == -2);
            CHECK(v.nth(4) - v.nth(7) == -3);
            CHECK(v.nth(4) - v.nth(8) == -4);
            CHECK(v.nth(4) - v.nth(9) == -5);

            CHECK(v.nth(5) - v.nth(5) == -0);
            CHECK(v.nth(5) - v.nth(6) == -1);
            CHECK(v.nth(5) - v.nth(7) == -2);
            CHECK(v.nth(5) - v.nth(8) == -3);
            CHECK(v.nth(5) - v.nth(9) == -4);

            CHECK(v.nth(6) - v.nth(6) == -0);
            CHECK(v.nth(6) - v.nth(7) == -1);
            CHECK(v.nth(6) - v.nth(8) == -2);
            CHECK(v.nth(6) - v.nth(9) == -3);

            CHECK(v.nth(7) - v.nth(7) == -0);
            CHECK(v.nth(7) - v.nth(8) == -1);
            CHECK(v.nth(7) - v.nth(9) == -2);

            CHECK(v.nth(8) - v.nth(8) == -0);
            CHECK(v.nth(8) - v.nth(9) == -1);

            CHECK(v.nth(9) - v.nth(9) == -0);
        }

        {
            CHECK(v.nth(0) < v.nth(1));
            CHECK(v.nth(0) < v.nth(2));
            CHECK(v.nth(0) < v.nth(3));
            CHECK(v.nth(0) < v.nth(4));
            CHECK(v.nth(0) < v.nth(5));
            CHECK(v.nth(0) < v.nth(6));
            CHECK(v.nth(0) < v.nth(7));
            CHECK(v.nth(0) < v.nth(8));
            CHECK(v.nth(0) < v.nth(9));

            CHECK(v.nth(1) < v.nth(2));
            CHECK(v.nth(1) < v.nth(3));
            CHECK(v.nth(1) < v.nth(4));
            CHECK(v.nth(1) < v.nth(5));
            CHECK(v.nth(1) < v.nth(6));
            CHECK(v.nth(1) < v.nth(7));
            CHECK(v.nth(1) < v.nth(8));
            CHECK(v.nth(1) < v.nth(9));

            CHECK(v.nth(2) < v.nth(3));
            CHECK(v.nth(2) < v.nth(4));
            CHECK(v.nth(2) < v.nth(5));
            CHECK(v.nth(2) < v.nth(6));
            CHECK(v.nth(2) < v.nth(7));
            CHECK(v.nth(2) < v.nth(8));
            CHECK(v.nth(2) < v.nth(9));

            CHECK(v.nth(3) < v.nth(4));
            CHECK(v.nth(3) < v.nth(5));
            CHECK(v.nth(3) < v.nth(6));
            CHECK(v.nth(3) < v.nth(7));
            CHECK(v.nth(3) < v.nth(8));
            CHECK(v.nth(3) < v.nth(9));

            CHECK(v.nth(4) < v.nth(5));
            CHECK(v.nth(4) < v.nth(6));
            CHECK(v.nth(4) < v.nth(7));
            CHECK(v.nth(4) < v.nth(8));
            CHECK(v.nth(4) < v.nth(9));

            CHECK(v.nth(5) < v.nth(6));
            CHECK(v.nth(5) < v.nth(7));
            CHECK(v.nth(5) < v.nth(8));
            CHECK(v.nth(5) < v.nth(9));

            CHECK(v.nth(6) < v.nth(7));
            CHECK(v.nth(6) < v.nth(8));
            CHECK(v.nth(6) < v.nth(9));

            CHECK(v.nth(7) < v.nth(8));
            CHECK(v.nth(7) < v.nth(9));

            CHECK(v.nth(8) < v.nth(9));
        }
    }

    cout << "Test insert(const_iterator, const T&)." << endl;
    {
        // Only one test is enough. `insert` calls `emplace`.

        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            const xint i(10);

            cout << ">" << endl;
            auto res = v.insert(v.nth(0), i);
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }
    }

    cout << "Test insert(const_iterator, T&&)." << endl;
    {
        // Only one test is enough. `insert` calls `emplace`.

        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            xint i(10);

            cout << ">" << endl;
            auto res = v.insert(v.nth(0), std::move(i));
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(i == -10);
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }
    }

    cout << "Test insert(const_iterator, size_type, const T&)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(0), 5, xint(10));
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 5);
            CHECK(v[0] == 10);
            CHECK(v[1] == 10);
            CHECK(v[2] == 10);
            CHECK(v[3] == 10);
            CHECK(v[4] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(1), 2, xint(20));
            cout << "<" << endl;

            CHECK(res == v.nth(1));
            CHECK(v.size() == 7);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 20);
            CHECK(v[3] == 10);
            CHECK(v[4] == 10);
            CHECK(v[5] == 10);
            CHECK(v[6] == 10);
        }

        {
            cout << ">" << endl;
            auto res = v.insert(v.nth(3), 10, xint(30));
            cout << "<" << endl;

            CHECK(res == v.nth(3));
            CHECK(v.size() == 17);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 20);
            CHECK(v[3] == 30);
            CHECK(v[4] == 30);
            CHECK(v[5] == 30);
            CHECK(v[6] == 30);
            CHECK(v[7] == 30);
            CHECK(v[8] == 30);
            CHECK(v[9] == 30);
            CHECK(v[10] == 30);
            CHECK(v[11] == 30);
            CHECK(v[12] == 30);
            CHECK(v[13] == 10);
            CHECK(v[14] == 10);
            CHECK(v[15] == 10);
            CHECK(v[16] == 10);
        }
    }

    cout << "Test insert(const_iterator, InputIt, InputIt)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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

            CHECK(res == v.nth(0));
            CHECK(v.size() == 10);
            CHECK(v[0] == 100);
            CHECK(v[1] == 101);
            CHECK(v[2] == 102);
            CHECK(v[3] == 103);
            CHECK(v[4] == 104);
            CHECK(v[5] == 105);
            CHECK(v[6] == 106);
            CHECK(v[7] == 107);
            CHECK(v[8] == 108);
            CHECK(v[9] == 109);
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

            CHECK(res == v.nth(7));
            CHECK(v.size() == 20);
            CHECK(v[0] == 100);
            CHECK(v[1] == 101);
            CHECK(v[2] == 102);
            CHECK(v[3] == 103);
            CHECK(v[4] == 104);
            CHECK(v[5] == 105);
            CHECK(v[6] == 106);
            CHECK(v[7] == 200);
            CHECK(v[8] == 201);
            CHECK(v[9] == 202);
            CHECK(v[10] == 203);
            CHECK(v[11] == 204);
            CHECK(v[12] == 205);
            CHECK(v[13] == 206);
            CHECK(v[14] == 207);
            CHECK(v[15] == 208);
            CHECK(v[16] == 209);
            CHECK(v[17] == 107);
            CHECK(v[18] == 108);
            CHECK(v[19] == 109);
        }
    }

    cout << "Test insert(const_iterator, ForwardIt, ForwardIt)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            const std::vector<xint> data({100, 101, 102, 103, 104, 105, 106, 107, 108, 109});

            cout << ">" << endl;
            auto res = v.insert(v.begin(), data.begin(), data.end());
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 10);
            CHECK(v[0] == 100);
            CHECK(v[1] == 101);
            CHECK(v[2] == 102);
            CHECK(v[3] == 103);
            CHECK(v[4] == 104);
            CHECK(v[5] == 105);
            CHECK(v[6] == 106);
            CHECK(v[7] == 107);
            CHECK(v[8] == 108);
            CHECK(v[9] == 109);
        }

        {
            const std::vector<xint> data({200, 201, 202});

            cout << ">" << endl;
            auto res = v.insert(v.nth(2), data.begin(), data.end());
            cout << "<" << endl;

            CHECK(res == v.nth(2));
            CHECK(v.size() == 13);
            CHECK(v[0] == 100);
            CHECK(v[1] == 101);
            CHECK(v[2] == 200);
            CHECK(v[3] == 201);
            CHECK(v[4] == 202);
            CHECK(v[5] == 102);
            CHECK(v[6] == 103);
            CHECK(v[7] == 104);
            CHECK(v[8] == 105);
            CHECK(v[9] == 106);
            CHECK(v[10] == 107);
            CHECK(v[11] == 108);
            CHECK(v[12] == 109);
        }

        {
            const std::vector<xint> data({300, 301, 302, 303, 304, 305, 306});

            cout << ">" << endl;
            auto res = v.insert(v.nth(11), data.begin(), data.end());
            cout << "<" << endl;

            CHECK(res == v.nth(11));
            CHECK(v.size() == 20);
            CHECK(v[0] == 100);
            CHECK(v[1] == 101);
            CHECK(v[2] == 200);
            CHECK(v[3] == 201);
            CHECK(v[4] == 202);
            CHECK(v[5] == 102);
            CHECK(v[6] == 103);
            CHECK(v[7] == 104);
            CHECK(v[8] == 105);
            CHECK(v[9] == 106);
            CHECK(v[10] == 107);
            CHECK(v[11] == 300);
            CHECK(v[12] == 301);
            CHECK(v[13] == 302);
            CHECK(v[14] == 303);
            CHECK(v[15] == 304);
            CHECK(v[16] == 305);
            CHECK(v[17] == 306);
            CHECK(v[18] == 108);
            CHECK(v[19] == 109);
        }
    }

    cout << "Test insert(const_iterator, MoveIterator, MoveIterator)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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

    cout << "Test push_back(const T&)." << endl;
    {
        // Only one test is enough. `push_back` calls `emplace`.

        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            const xint i(10);

            cout << ">" << endl;
            v.push_back(i);
            cout << "<" << endl;

            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }
    }

    cout << "Test push_back(T&&)." << endl;
    {
        // Only one test is enough. `push_back` calls `emplace`.

        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            xint i(10);

            cout << ">" << endl;
            v.push_back(std::move(i));
            cout << "<" << endl;

            CHECK(i == -10);
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }
    }

    cout << "Test pop_back()." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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
            v.pop_back();
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            cout << ">" << endl;
            v.pop_back();
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        {
            cout << ">" << endl;
            v.emplace_back(50);
            cout << "<" << endl;

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 50);
        }

        {
            cout << ">" << endl;
            v.pop_back();
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
    }

    cout << "Test clear()." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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

    cout << "Test erase(const_iterator)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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

            CHECK(v.size() == 9);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
            CHECK(v[5] == 60);
            CHECK(v[6] == 70);
            CHECK(v[7] == 80);
            CHECK(v[8] == 90);
        }

        {
            cout << ">" << endl;
            // Erase nothing
            auto res = v.erase(v.nth(3), v.nth(3));
            cout << "<" << endl;

            CHECK(res == v.nth(3));
            CHECK(v.size() == 9);
        }

        {
            cout << ">" << endl;
            // Erase two elements near begin
            auto res = v.erase(v.nth(1), v.nth(3));
            cout << "<" << endl;

            CHECK(res == v.nth(1));
            CHECK(v.size() == 7);
            CHECK(v[0] == 10);
            CHECK(v[1] == 40);
            CHECK(v[2] == 50);
            CHECK(v[3] == 60);
            CHECK(v[4] == 70);
            CHECK(v[5] == 80);
            CHECK(v[6] == 90);
        }

        {
            cout << ">" << endl;
            // Erase two elements near end
            auto res = v.erase(v.nth(4), v.nth(6));
            cout << "<" << endl;

            CHECK(res == v.nth(4));
            CHECK(v.size() == 5);
            CHECK(v[0] == 10);
            CHECK(v[1] == 40);
            CHECK(v[2] == 50);
            CHECK(v[3] == 60);
            CHECK(v[4] == 90);
        }

        {
            cout << ">" << endl;
            // Remove two elements at begin
            auto res = v.erase(v.nth(0), v.nth(2));
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 3);
            CHECK(v[0] == 50);
            CHECK(v[1] == 60);
            CHECK(v[2] == 90);
        }

        {
            cout << ">" << endl;
            // Remove two elements at end
            auto res = v.erase(v.nth(1), v.nth(3));
            cout << "<" << endl;

            CHECK(res == v.nth(1));
            CHECK(v.size() == 1);
            CHECK(v[0] == 50);
        }

        {
            cout << ">" << endl;
            // Remove from begin to end
            auto res = v.erase(v.nth(0), v.nth(1));
            cout << "<" << endl;

            CHECK(res == v.nth(0));
            CHECK(v.size() == 0);
        }
    }

    cout << "Test resize(size_type)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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
            v.resize(10);
            cout << "<" << endl;

            CHECK(v.size() == 10);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[4] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[5] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[6] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[7] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[8] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[9] == SFL_MY_INT_DEFAULT_VALUE);
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
            v.resize(4);
            cout << "<" << endl;

            CHECK(v.size() == 4);
            CHECK(v[0] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[1] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[2] == SFL_MY_INT_DEFAULT_VALUE);
            CHECK(v[3] == SFL_MY_INT_DEFAULT_VALUE);
        }
    }

    cout << "Test resize(size_type, const T&)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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
            v.resize(10, 40);
            cout << "<" << endl;

            CHECK(v.size() == 10);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 40);
            CHECK(v[5] == 40);
            CHECK(v[6] == 40);
            CHECK(v[7] == 40);
            CHECK(v[8] == 40);
            CHECK(v[9] == 40);
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
            v.resize(4, 70);
            cout << "<" << endl;

            CHECK(v.size() == 4);
            CHECK(v[0] == 70);
            CHECK(v[1] == 70);
            CHECK(v[2] == 70);
            CHECK(v[3] == 70);
        }
    }

    cout << "Test swap(segmented_vector&)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1;
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2;

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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

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

    cout << "Test reserve(size_type) and shrink_to_fit()." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        CHECK(v.size() == 0);

        const auto cap1 = v.capacity();

        v.reserve(50);

        const auto cap2 = v.capacity();

        CHECK(cap2 >= cap1);

        v.emplace_back(10);
        v.emplace_back(20);
        v.emplace_back(30);
        v.emplace_back(40);
        v.emplace_back(50);
        v.emplace_back(60);
        v.emplace_back(70);
        v.emplace_back(80);
        v.emplace_back(90);

        CHECK(v.size() == 9);
        CHECK(v[0] == 10);
        CHECK(v[1] == 20);
        CHECK(v[2] == 30);
        CHECK(v[3] == 40);
        CHECK(v[4] == 50);
        CHECK(v[5] == 60);
        CHECK(v[6] == 70);
        CHECK(v[7] == 80);
        CHECK(v[8] == 90);

        v.shrink_to_fit();

        const auto cap3 = v.capacity();

        CHECK(cap3 <= cap2);

        CHECK(v.size() == 9);
        CHECK(v[0] == 10);
        CHECK(v[1] == 20);
        CHECK(v[2] == 30);
        CHECK(v[3] == 40);
        CHECK(v[4] == 50);
        CHECK(v[5] == 60);
        CHECK(v[6] == 70);
        CHECK(v[7] == 80);
        CHECK(v[8] == 90);

        v.reserve(200);

        const auto cap4 = v.capacity();

        CHECK(cap4 >= cap3);

        CHECK(v.size() == 9);
        CHECK(v[0] == 10);
        CHECK(v[1] == 20);
        CHECK(v[2] == 30);
        CHECK(v[3] == 40);
        CHECK(v[4] == 50);
        CHECK(v[5] == 60);
        CHECK(v[6] == 70);
        CHECK(v[7] == 80);
        CHECK(v[8] == 90);

        v.shrink_to_fit();

        const auto cap5 = v.capacity();

        CHECK(cap5 == cap3);
    }

    cout << "Test constructor()." << endl;
    {
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1;
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2(alloc);

        CHECK(v1.size() == 0);
        CHECK(v2.size() == 0);
    }

    cout << "Test constructor(size_type)." << endl;
    {
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1(3);
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2(3, alloc);

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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1(3, 42);
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2(3, 42, alloc);
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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1
        (
            (std::istream_iterator<int>(iss1)),
            (std::istream_iterator<int>())
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2
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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1
        (
            data.begin(),
            data.end()
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2
        (
            data.begin(),
            data.end(),
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

    cout << "Test constructor(MoveIterator, MoveIterator)." << endl;
    {
        TPARAM_ALLOCATOR<xint> alloc;

        std::vector<xint> data1({10, 20, 30, 40});
        std::vector<xint> data2({10, 20, 30, 40});

        cout << ">" << endl;
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1
        (
            std::make_move_iterator(data1.begin()),
            std::make_move_iterator(data1.end())
        );
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2
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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30, 40});
        cout << "<" << endl;

        cout << ">" << endl;
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2({10, 20, 30, 40}, alloc);
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

    cout << "Test constructor(const segmented_vector&)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30, 40, 50});

        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2(v1);

        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v3(v1, TPARAM_ALLOCATOR<xint>());

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

    cout << "Test constructor(segmented_vector&&)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30, 40, 50});

        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2(std::move(v1));

        // v1 is in a valid but unspecified state

        CHECK(v2.size() == 5);
        CHECK(v2[0] == 10);
        CHECK(v2[1] == 20);
        CHECK(v2[2] == 30);
        CHECK(v2[3] == 40);
        CHECK(v2[4] == 50);

        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v3(std::move(v2), TPARAM_ALLOCATOR<xint>());

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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.assign(10, 10);
            cout << "<" << endl;

            CHECK(v.size() == 10);
            CHECK(v[0] == 10);
            CHECK(v[1] == 10);
            CHECK(v[2] == 10);
            CHECK(v[3] == 10);
            CHECK(v[4] == 10);
            CHECK(v[5] == 10);
            CHECK(v[6] == 10);
            CHECK(v[7] == 10);
            CHECK(v[8] == 10);
            CHECK(v[9] == 10);
        }

        {
            cout << ">" << endl;
            v.assign(5, 20);
            cout << "<" << endl;

            CHECK(v.size() == 5);
            CHECK(v[0] == 20);
            CHECK(v[1] == 20);
            CHECK(v[2] == 20);
            CHECK(v[3] == 20);
            CHECK(v[4] == 20);
        }

        {
            cout << ">" << endl;
            v.assign(9, 30);
            cout << "<" << endl;

            CHECK(v.size() == 9);
            CHECK(v[0] == 30);
            CHECK(v[1] == 30);
            CHECK(v[2] == 30);
            CHECK(v[3] == 30);
            CHECK(v[4] == 30);
            CHECK(v[5] == 30);
            CHECK(v[6] == 30);
            CHECK(v[7] == 30);
            CHECK(v[8] == 30);
        }

        {
            cout << ">" << endl;
            v.assign(0, 40);
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }

        {
            cout << ">" << endl;
            v.assign(4, 50);
            cout << "<" << endl;

            CHECK(v.size() == 4);
            CHECK(v[0] == 50);
            CHECK(v[1] == 50);
            CHECK(v[2] == 50);
            CHECK(v[3] == 50);
        }
    }

    cout << "Test assign(InputIt, InputIt)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            std::istringstream iss("11 12 13 14 15 16 17 18 19");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            CHECK(v.size() == 9);
            CHECK(v[0] == 11);
            CHECK(v[1] == 12);
            CHECK(v[2] == 13);
            CHECK(v[3] == 14);
            CHECK(v[4] == 15);
            CHECK(v[5] == 16);
            CHECK(v[6] == 17);
            CHECK(v[7] == 18);
            CHECK(v[8] == 19);
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

            CHECK(v.size() == 5);
            CHECK(v[0] == 21);
            CHECK(v[1] == 22);
            CHECK(v[2] == 23);
            CHECK(v[3] == 24);
            CHECK(v[4] == 25);
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

            CHECK(v.size() == 7);
            CHECK(v[0] == 31);
            CHECK(v[1] == 32);
            CHECK(v[2] == 33);
            CHECK(v[3] == 34);
            CHECK(v[4] == 35);
            CHECK(v[5] == 36);
            CHECK(v[6] == 37);
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

        {
            std::istringstream iss("41 42");

            cout << ">" << endl;
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 41);
            CHECK(v[1] == 42);
        }
    }

    cout << "Test assign(ForwardIt, ForwardIt)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            const std::vector<int> data({11, 12, 13, 14, 15, 16, 17, 18, 19});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            CHECK(v.size() == 9);
            CHECK(v[0] == 11);
            CHECK(v[1] == 12);
            CHECK(v[2] == 13);
            CHECK(v[3] == 14);
            CHECK(v[4] == 15);
            CHECK(v[5] == 16);
            CHECK(v[6] == 17);
            CHECK(v[7] == 18);
            CHECK(v[8] == 19);
        }

        {
            const std::vector<int> data({21, 22, 23, 24, 25});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            CHECK(v.size() == 5);
            CHECK(v[0] == 21);
            CHECK(v[1] == 22);
            CHECK(v[2] == 23);
            CHECK(v[3] == 24);
            CHECK(v[4] == 25);
        }

        {
            const std::vector<int> data({31, 32, 33, 34, 35, 36, 37});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            CHECK(v.size() == 7);
            CHECK(v[0] == 31);
            CHECK(v[1] == 32);
            CHECK(v[2] == 33);
            CHECK(v[3] == 34);
            CHECK(v[4] == 35);
            CHECK(v[5] == 36);
            CHECK(v[6] == 37);
        }

        {
            const std::vector<int> data;

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }

        {
            const std::vector<int> data({41, 42});

            cout << ">" << endl;
            v.assign(data.begin(), data.end());
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 41);
            CHECK(v[1] == 42);
        }
    }

    cout << "Test assign(MoveIterator, MoveIterator)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            std::vector<xint> data({11, 12, 13, 14, 15, 16, 17, 18, 19});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            CHECK(data[0] == -11);
            CHECK(data[1] == -12);
            CHECK(data[2] == -13);
            CHECK(data[3] == -14);
            CHECK(data[4] == -15);
            CHECK(data[5] == -16);
            CHECK(data[6] == -17);
            CHECK(data[7] == -18);
            CHECK(data[8] == -19);
            CHECK(v.size() == 9);
            CHECK(v[0] == 11);
            CHECK(v[1] == 12);
            CHECK(v[2] == 13);
            CHECK(v[3] == 14);
            CHECK(v[4] == 15);
            CHECK(v[5] == 16);
            CHECK(v[6] == 17);
            CHECK(v[7] == 18);
            CHECK(v[8] == 19);
        }

        {
            std::vector<xint> data({21, 22, 23, 24, 25});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            CHECK(data[0] == -21);
            CHECK(data[1] == -22);
            CHECK(data[2] == -23);
            CHECK(data[3] == -24);
            CHECK(data[4] == -25);
            CHECK(v.size() == 5);
            CHECK(v[0] == 21);
            CHECK(v[1] == 22);
            CHECK(v[2] == 23);
            CHECK(v[3] == 24);
            CHECK(v[4] == 25);
        }

        {
            std::vector<xint> data({31, 32, 33, 34, 35, 36, 37});

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            CHECK(data[0] == -31);
            CHECK(data[1] == -32);
            CHECK(data[2] == -33);
            CHECK(data[3] == -34);
            CHECK(data[4] == -35);
            CHECK(data[5] == -36);
            CHECK(data[6] == -37);
            CHECK(v.size() == 7);
            CHECK(v[0] == 31);
            CHECK(v[1] == 32);
            CHECK(v[2] == 33);
            CHECK(v[3] == 34);
            CHECK(v[4] == 35);
            CHECK(v[5] == 36);
            CHECK(v[6] == 37);
        }

        {
            std::vector<xint> data;

            cout << ">" << endl;
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }
    }

    cout << "Test assign(std::initializer_list)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v;

        {
            cout << ">" << endl;
            v.assign({11, 12, 13, 14, 15, 16, 17, 18, 19});
            cout << "<" << endl;

            CHECK(v.size() == 9);
            CHECK(v[0] == 11);
            CHECK(v[1] == 12);
            CHECK(v[2] == 13);
            CHECK(v[3] == 14);
            CHECK(v[4] == 15);
            CHECK(v[5] == 16);
            CHECK(v[6] == 17);
            CHECK(v[7] == 18);
            CHECK(v[8] == 19);
        }

        {
            cout << ">" << endl;
            v.assign({21, 22, 23, 24, 25});
            cout << "<" << endl;

            CHECK(v.size() == 5);
            CHECK(v[0] == 21);
            CHECK(v[1] == 22);
            CHECK(v[2] == 23);
            CHECK(v[3] == 24);
            CHECK(v[4] == 25);
        }

        {
            cout << ">" << endl;
            v.assign({31, 32, 33, 34, 35, 36, 37});
            cout << "<" << endl;

            CHECK(v.size() == 7);
            CHECK(v[0] == 31);
            CHECK(v[1] == 32);
            CHECK(v[2] == 33);
            CHECK(v[3] == 34);
            CHECK(v[4] == 35);
            CHECK(v[5] == 36);
            CHECK(v[6] == 37);
        }

        {
            const std::vector<int> data;

            cout << ">" << endl;
            v.assign({});
            cout << "<" << endl;

            CHECK(v.size() == 0);
        }

        {
            cout << ">" << endl;
            v.assign({41, 42});
            cout << "<" << endl;

            CHECK(v.size() == 2);
            CHECK(v[0] == 41);
            CHECK(v[1] == 42);
        }
    }

    cout << "Test operator=(const segmented_vector&)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30});
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2({40, 50});

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

    cout << "Test operator=(segmented_vector&&)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30});
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2({40, 50});

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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30});
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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1({10, 20, 30});
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2({10, 20, 30, 40});

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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1({10, 11, 12});
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v2({20, 21, 22});

        using std::swap;
        swap(v1, v2);
    }

    cout << "Test non-member erase(compact_vector&, const U&)." << endl;
    {
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1({10, 20, 20, 30, 30, 30});

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
        sfl::segmented_vector<xint, TPARAM_N, TPARAM_ALLOCATOR<xint>> v1({10, 20, 20, 30, 30, 30});

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
