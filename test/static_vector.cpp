//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include static_vector.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG // This is very important. Must be in the first line.

#include "sfl/static_vector.hpp"

#include "check.hpp"
#include "print.hpp"

#include "xint.hpp"

#include <sstream>
#include <vector>

int main()
{
    using sfl::test::xint;

    PRINT("Test emplace_back(Args&&...)");
    {
        sfl::static_vector<xint, 5> vec;

        {
            CHECK(vec.empty() == true);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 0);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 5);
        }

        {
            PRINT(">");
            const auto res = vec.emplace_back(10);
            PRINT("<");

            CHECK(res == 10);
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 1);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 4);
            CHECK(*vec.nth(0) == 10);
        }

        {
            PRINT(">");
            const auto res = vec.emplace_back(20);
            PRINT("<");

            CHECK(res == 20);
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 2);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 3);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
        }

        {
            PRINT(">");
            const auto res = vec.emplace_back(30);
            PRINT("<");

            CHECK(res == 30);
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 3);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 2);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
        }

        {
            PRINT(">");
            const auto res = vec.emplace_back(40);
            PRINT("<");

            CHECK(res == 40);
            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 4);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 1);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }

        {
            PRINT(">");
            const auto res = vec.emplace_back(50);
            PRINT("<");

            CHECK(res == 50);
            CHECK(vec.empty() == false);
            CHECK(vec.full() == true);
            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 0);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
        }
    }

    PRINT("Test emplace(const_iterator, Args&&...)");
    {
        // Insert at the end
        {
            sfl::static_vector<xint, 5> vec;

            {
                CHECK(vec.empty() == true);
                CHECK(vec.full() == false);
                CHECK(vec.size() == 0);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 5);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 10);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.empty() == false);
                CHECK(vec.full() == false);
                CHECK(vec.size() == 1);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 4);
                CHECK(*vec.nth(0) == 10);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 20);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.empty() == false);
                CHECK(vec.full() == false);
                CHECK(vec.size() == 2);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 3);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 30);
                PRINT("<");

                CHECK(res == vec.nth(2));
                CHECK(vec.empty() == false);
                CHECK(vec.full() == false);
                CHECK(vec.size() == 3);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 2);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 40);
                PRINT("<");

                CHECK(res == vec.nth(3));
                CHECK(vec.empty() == false);
                CHECK(vec.full() == false);
                CHECK(vec.size() == 4);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 1);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 50);
                PRINT("<");

                CHECK(res == vec.nth(4));
                CHECK(vec.empty() == false);
                CHECK(vec.full() == true);
                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 0);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
            }
        }

        // Insert at the begin
        {
            sfl::static_vector<xint, 5> vec;

            {
                CHECK(vec.empty() == true);
                CHECK(vec.full() == false);
                CHECK(vec.size() == 0);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 5);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 50);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.empty() == false);
                CHECK(vec.full() == false);
                CHECK(vec.size() == 1);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 4);
                CHECK(*vec.nth(0) == 50);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 40);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.empty() == false);
                CHECK(vec.full() == false);
                CHECK(vec.size() == 2);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 3);
                CHECK(*vec.nth(0) == 40);
                CHECK(*vec.nth(1) == 50);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 30);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.empty() == false);
                CHECK(vec.full() == false);
                CHECK(vec.size() == 3);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 2);
                CHECK(*vec.nth(0) == 30);
                CHECK(*vec.nth(1) == 40);
                CHECK(*vec.nth(2) == 50);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 20);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.empty() == false);
                CHECK(vec.full() == false);
                CHECK(vec.size() == 4);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 1);
                CHECK(*vec.nth(0) == 20);
                CHECK(*vec.nth(1) == 30);
                CHECK(*vec.nth(2) == 40);
                CHECK(*vec.nth(3) == 50);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 10);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.empty() == false);
                CHECK(vec.full() == true);
                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 5);
                CHECK(vec.available() == 0);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
            }
        }

        {
            sfl::static_vector<xint, 5> vec;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);

            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 4);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 1);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);

            const auto res = vec.emplace(vec.nth(0), 5);

            CHECK(res == vec.nth(0));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == true);
            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 0);
            CHECK(*vec.nth(0) ==  5);
            CHECK(*vec.nth(1) == 10);
            CHECK(*vec.nth(2) == 20);
            CHECK(*vec.nth(3) == 30);
            CHECK(*vec.nth(4) == 40);
        }

        {
            sfl::static_vector<xint, 5> vec;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);

            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 4);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 1);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);

            const auto res = vec.emplace(vec.nth(1), 15);

            CHECK(res == vec.nth(1));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == true);
            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 0);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 15);
            CHECK(*vec.nth(2) == 20);
            CHECK(*vec.nth(3) == 30);
            CHECK(*vec.nth(4) == 40);
        }

        {
            sfl::static_vector<xint, 5> vec;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);

            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 4);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 1);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);

            const auto res = vec.emplace(vec.nth(2), 25);

            CHECK(res == vec.nth(2));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == true);
            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 0);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 25);
            CHECK(*vec.nth(3) == 30);
            CHECK(*vec.nth(4) == 40);
        }

        {
            sfl::static_vector<xint, 5> vec;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);

            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 4);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 1);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);

            const auto res = vec.emplace(vec.nth(3), 35);

            CHECK(res == vec.nth(3));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == true);
            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 0);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 35);
            CHECK(*vec.nth(4) == 40);
        }

        {
            sfl::static_vector<xint, 5> vec;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);

            CHECK(vec.empty() == false);
            CHECK(vec.full() == false);
            CHECK(vec.size() == 4);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 1);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);

            const auto res = vec.emplace(vec.nth(4), 45);

            CHECK(res == vec.nth(4));
            CHECK(vec.empty() == false);
            CHECK(vec.full() == true);
            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 5);
            CHECK(vec.available() == 0);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 45);
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    PRINT("Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend, nth, index_of");
    {
        sfl::static_vector<xint, 100> vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        auto it = vec.begin();
        CHECK(*it == 10); ++it;
        CHECK(*it == 20); ++it;
        CHECK(*it == 30); ++it;
        CHECK(it == vec.end());

        ///////////////////////////////////////////////////////////////////////

        auto cit = vec.cbegin();
        CHECK(*cit == 10); ++cit;
        CHECK(*cit == 20); ++cit;
        CHECK(*cit == 30); ++cit;
        CHECK(cit == vec.cend());

        ///////////////////////////////////////////////////////////////////////

        auto rit = vec.rbegin();
        CHECK(*rit == 30); ++rit;
        CHECK(*rit == 20); ++rit;
        CHECK(*rit == 10); ++rit;
        CHECK(rit == vec.rend());

        ///////////////////////////////////////////////////////////////////////

        auto crit = vec.crbegin();
        CHECK(*crit == 30); ++crit;
        CHECK(*crit == 20); ++crit;
        CHECK(*crit == 10); ++crit;
        CHECK(crit == vec.crend());

        ///////////////////////////////////////////////////////////////////////

        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(vec.nth(3) == vec.end());

        ///////////////////////////////////////////////////////////////////////

        CHECK(std::next(vec.begin(), 0) == vec.nth(0));
        CHECK(std::next(vec.begin(), 1) == vec.nth(1));
        CHECK(std::next(vec.begin(), 2) == vec.nth(2));
        CHECK(std::next(vec.begin(), 3) == vec.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(std::next(vec.cbegin(), 0) == vec.nth(0));
        CHECK(std::next(vec.cbegin(), 1) == vec.nth(1));
        CHECK(std::next(vec.cbegin(), 2) == vec.nth(2));
        CHECK(std::next(vec.cbegin(), 3) == vec.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(vec.nth(0) < vec.nth(1));
        CHECK(vec.nth(0) < vec.nth(2));
        CHECK(vec.nth(0) < vec.nth(3));

        CHECK(vec.nth(1) < vec.nth(2));
        CHECK(vec.nth(1) < vec.nth(3));

        CHECK(vec.nth(2) < vec.nth(3));

        ///////////////////////////////////////////////////////////////////////

        CHECK(vec.index_of(vec.nth(0)) == 0);
        CHECK(vec.index_of(vec.nth(1)) == 1);
        CHECK(vec.index_of(vec.nth(2)) == 2);
        CHECK(vec.index_of(vec.nth(3)) == 3);
    }

    ///////////////////////////////////////////////////////////////////////////

    PRINT("Test clear()");
    {
        sfl::static_vector<xint, 100> vec;

        CHECK(vec.size() == 0);

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        vec.clear();

        CHECK(vec.size() == 0);

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        vec.clear();

        CHECK(vec.size() == 0);
    }

    PRINT("Test insert(const_iterator, const T&)");
    {
        sfl::static_vector<xint, 100> vec;

        xint value_10(10);

        auto res = vec.insert(vec.nth(0), value_10);

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(value_10 == 10);
    }

    PRINT("Test insert(const_iterator, T&&)");
    {
        sfl::static_vector<xint, 100> vec;

        xint value_10(10);

        auto res = vec.insert(vec.nth(0), std::move(value_10));

        CHECK(res == vec.nth(0));
        CHECK(vec.size() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(value_10 == -10);
    }

    PRINT("Test insert(const_iterator, size_type, const T&)");
    {
        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(0), 3, 5);

            CHECK(res == vec.nth(0));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) ==  5);
            CHECK(*vec.nth(1) ==  5);
            CHECK(*vec.nth(2) ==  5);
            CHECK(*vec.nth(3) == 10);
            CHECK(*vec.nth(4) == 20);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(1), 3, 15);

            CHECK(res == vec.nth(1));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 15);
            CHECK(*vec.nth(2) == 15);
            CHECK(*vec.nth(3) == 15);
            CHECK(*vec.nth(4) == 20);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(2), 3, 25);

            CHECK(res == vec.nth(2));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 25);
            CHECK(*vec.nth(3) == 25);
            CHECK(*vec.nth(4) == 25);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(3), 3, 35);

            CHECK(res == vec.nth(3));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 35);
            CHECK(*vec.nth(4) == 35);
            CHECK(*vec.nth(5) == 35);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(4), 3, 45);

            CHECK(res == vec.nth(4));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 45);
            CHECK(*vec.nth(5) == 45);
            CHECK(*vec.nth(6) == 45);
            CHECK(*vec.nth(7) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(5), 3, 55);

            CHECK(res == vec.nth(5));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 55);
            CHECK(*vec.nth(6) == 55);
            CHECK(*vec.nth(7) == 55);
        }
    }

    PRINT("Test insert(const_iterator, InputIt, InputIt)");
    {
        // Input iterator (exactly)
        {
            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::istringstream iss("1 2 3");

                auto res = vec.insert
                (
                    vec.nth(0),
                    std::istream_iterator<int>(iss),
                    std::istream_iterator<int>()
                );

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) ==  1);
                CHECK(*vec.nth(1) ==  2);
                CHECK(*vec.nth(2) ==  3);
                CHECK(*vec.nth(3) == 10);
                CHECK(*vec.nth(4) == 20);
                CHECK(*vec.nth(5) == 30);
                CHECK(*vec.nth(6) == 40);
                CHECK(*vec.nth(7) == 50);
            }

            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::istringstream iss("11 12 13");

                auto res = vec.insert
                (
                    vec.nth(1),
                    std::istream_iterator<int>(iss),
                    std::istream_iterator<int>()
                );

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 11);
                CHECK(*vec.nth(2) == 12);
                CHECK(*vec.nth(3) == 13);
                CHECK(*vec.nth(4) == 20);
                CHECK(*vec.nth(5) == 30);
                CHECK(*vec.nth(6) == 40);
                CHECK(*vec.nth(7) == 50);
            }

            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::istringstream iss("21 22 23");

                auto res = vec.insert
                (
                    vec.nth(2),
                    std::istream_iterator<int>(iss),
                    std::istream_iterator<int>()
                );

                CHECK(res == vec.nth(2));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 21);
                CHECK(*vec.nth(3) == 22);
                CHECK(*vec.nth(4) == 23);
                CHECK(*vec.nth(5) == 30);
                CHECK(*vec.nth(6) == 40);
                CHECK(*vec.nth(7) == 50);
            }

            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::istringstream iss("31 32 33");

                auto res = vec.insert
                (
                    vec.nth(3),
                    std::istream_iterator<int>(iss),
                    std::istream_iterator<int>()
                );

                CHECK(res == vec.nth(3));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 31);
                CHECK(*vec.nth(4) == 32);
                CHECK(*vec.nth(5) == 33);
                CHECK(*vec.nth(6) == 40);
                CHECK(*vec.nth(7) == 50);
            }

            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::istringstream iss("41 42 43");

                auto res = vec.insert
                (
                    vec.nth(4),
                    std::istream_iterator<int>(iss),
                    std::istream_iterator<int>()
                );

                CHECK(res == vec.nth(4));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 41);
                CHECK(*vec.nth(5) == 42);
                CHECK(*vec.nth(6) == 43);
                CHECK(*vec.nth(7) == 50);
            }

            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::istringstream iss("51 52 53");

                auto res = vec.insert
                (
                    vec.nth(5),
                    std::istream_iterator<int>(iss),
                    std::istream_iterator<int>()
                );

                CHECK(res == vec.nth(5));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 51);
                CHECK(*vec.nth(6) == 52);
                CHECK(*vec.nth(7) == 53);
            }
        }

        // Forward iterator
        {
            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({1, 2, 3});

                auto res = vec.insert(vec.nth(0), data.begin(), data.end());

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) ==  1);
                CHECK(*vec.nth(1) ==  2);
                CHECK(*vec.nth(2) ==  3);
                CHECK(*vec.nth(3) == 10);
                CHECK(*vec.nth(4) == 20);
                CHECK(*vec.nth(5) == 30);
                CHECK(*vec.nth(6) == 40);
                CHECK(*vec.nth(7) == 50);
            }

            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({11, 12, 13});

                auto res = vec.insert(vec.nth(1), data.begin(), data.end());

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 11);
                CHECK(*vec.nth(2) == 12);
                CHECK(*vec.nth(3) == 13);
                CHECK(*vec.nth(4) == 20);
                CHECK(*vec.nth(5) == 30);
                CHECK(*vec.nth(6) == 40);
                CHECK(*vec.nth(7) == 50);
            }

            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({21, 22, 23});

                auto res = vec.insert(vec.nth(2), data.begin(), data.end());

                CHECK(res == vec.nth(2));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 21);
                CHECK(*vec.nth(3) == 22);
                CHECK(*vec.nth(4) == 23);
                CHECK(*vec.nth(5) == 30);
                CHECK(*vec.nth(6) == 40);
                CHECK(*vec.nth(7) == 50);
            }

            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({31, 32, 33});

                auto res = vec.insert(vec.nth(3), data.begin(), data.end());

                CHECK(res == vec.nth(3));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 31);
                CHECK(*vec.nth(4) == 32);
                CHECK(*vec.nth(5) == 33);
                CHECK(*vec.nth(6) == 40);
                CHECK(*vec.nth(7) == 50);
            }

            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({41, 42, 43});

                auto res = vec.insert(vec.nth(4), data.begin(), data.end());

                CHECK(res == vec.nth(4));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 41);
                CHECK(*vec.nth(5) == 42);
                CHECK(*vec.nth(6) == 43);
                CHECK(*vec.nth(7) == 50);
            }

            {
                sfl::static_vector<xint, 100> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 95);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({51, 52, 53});

                auto res = vec.insert(vec.nth(5), data.begin(), data.end());

                CHECK(res == vec.nth(5));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 100);
                CHECK(vec.available() == 92);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 51);
                CHECK(*vec.nth(6) == 52);
                CHECK(*vec.nth(7) == 53);
            }
        }
    }

    PRINT("Test insert(const_iterator, std::initializer_list");
    {
        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{1, 2, 3};

            auto res = vec.insert(vec.nth(0), ilist);

            CHECK(res == vec.nth(0));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) ==  1);
            CHECK(*vec.nth(1) ==  2);
            CHECK(*vec.nth(2) ==  3);
            CHECK(*vec.nth(3) == 10);
            CHECK(*vec.nth(4) == 20);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{11, 12, 13};

            auto res = vec.insert(vec.nth(1), ilist);

            CHECK(res == vec.nth(1));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 11);
            CHECK(*vec.nth(2) == 12);
            CHECK(*vec.nth(3) == 13);
            CHECK(*vec.nth(4) == 20);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{21, 22, 23};

            auto res = vec.insert(vec.nth(2), ilist);

            CHECK(res == vec.nth(2));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 21);
            CHECK(*vec.nth(3) == 22);
            CHECK(*vec.nth(4) == 23);
            CHECK(*vec.nth(5) == 30);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{31, 32, 33};

            auto res = vec.insert(vec.nth(3), ilist);

            CHECK(res == vec.nth(3));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 31);
            CHECK(*vec.nth(4) == 32);
            CHECK(*vec.nth(5) == 33);
            CHECK(*vec.nth(6) == 40);
            CHECK(*vec.nth(7) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{41, 42, 43};

            auto res = vec.insert(vec.nth(4), ilist);

            CHECK(res == vec.nth(4));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 41);
            CHECK(*vec.nth(5) == 42);
            CHECK(*vec.nth(6) == 43);
            CHECK(*vec.nth(7) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{51, 52, 53};

            auto res = vec.insert(vec.nth(5), ilist);

            CHECK(res == vec.nth(5));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 92);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 51);
            CHECK(*vec.nth(6) == 52);
            CHECK(*vec.nth(7) == 53);
        }
    }

    PRINT("Test push_back(const T&)");
    {
        sfl::static_vector<xint, 100> vec;

        xint value_10(10);

        vec.push_back(value_10);

        CHECK(vec.size() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(value_10 == 10);
    }

    PRINT("Test push_back(T&&)");
    {
        sfl::static_vector<xint, 100> vec;

        xint value_10(10);

        vec.push_back(std::move(value_10));

        CHECK(vec.size() == 1);
        CHECK(*vec.nth(0) == 10);
        CHECK(value_10 == -10);
    }

    PRINT("Test pop_back()");
    {
        sfl::static_vector<xint, 100> vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////////

        vec.pop_back();

        CHECK(vec.size() == 2);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);

        ///////////////////////////////////////////////////////////////////////////

        vec.pop_back();

        CHECK(vec.size() == 1);
        CHECK(*vec.nth(0) == 10);

        ///////////////////////////////////////////////////////////////////////////

        vec.pop_back();

        CHECK(vec.size() == 0);
    }

    PRINT("Test erase(const_iterator)");
    {
        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.erase(vec.nth(0));

            CHECK(res == vec.nth(0));
            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 20);
            CHECK(*vec.nth(1) == 30);
            CHECK(*vec.nth(2) == 40);
            CHECK(*vec.nth(3) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.erase(vec.nth(1));

            CHECK(res == vec.nth(1));
            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 30);
            CHECK(*vec.nth(2) == 40);
            CHECK(*vec.nth(3) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.erase(vec.nth(2));

            CHECK(res == vec.nth(2));
            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 40);
            CHECK(*vec.nth(3) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.erase(vec.nth(3));

            CHECK(res == vec.nth(3));
            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 50);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.erase(vec.nth(4));

            CHECK(res == vec.nth(4));
            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }
    }

    PRINT("Test erase(const_iterator, const_iterator)");
    {
        {
            sfl::static_vector<xint, 100> vec;

            CHECK(vec.size() == 0);

            CHECK(vec.erase(vec.nth(0), vec.nth(0)) == vec.nth(0));
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);
            vec.emplace(vec.end(), 60);
            vec.emplace(vec.end(), 70);

            CHECK(vec.size() == 7);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 60);
            CHECK(*vec.nth(6) == 70);

            CHECK(vec.erase(vec.nth(0), vec.nth(0)) == vec.nth(0));
            CHECK(vec.erase(vec.nth(1), vec.nth(1)) == vec.nth(1));
            CHECK(vec.erase(vec.nth(2), vec.nth(2)) == vec.nth(2));
            CHECK(vec.erase(vec.nth(3), vec.nth(3)) == vec.nth(3));
            CHECK(vec.erase(vec.nth(4), vec.nth(4)) == vec.nth(4));
            CHECK(vec.erase(vec.nth(5), vec.nth(5)) == vec.nth(5));
            CHECK(vec.erase(vec.nth(6), vec.nth(6)) == vec.nth(6));
            CHECK(vec.erase(vec.nth(7), vec.nth(7)) == vec.nth(7));
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);
            vec.emplace(vec.end(), 60);
            vec.emplace(vec.end(), 70);

            CHECK(vec.size() == 7);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 60);
            CHECK(*vec.nth(6) == 70);

            CHECK(vec.erase(vec.nth(0), vec.nth(3)) == vec.nth(0));
            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 40);
            CHECK(*vec.nth(1) == 50);
            CHECK(*vec.nth(2) == 60);
            CHECK(*vec.nth(3) == 70);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);
            vec.emplace(vec.end(), 60);
            vec.emplace(vec.end(), 70);

            CHECK(vec.size() == 7);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 60);
            CHECK(*vec.nth(6) == 70);

            CHECK(vec.erase(vec.nth(1), vec.nth(4)) == vec.nth(1));
            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 50);
            CHECK(*vec.nth(2) == 60);
            CHECK(*vec.nth(3) == 70);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);
            vec.emplace(vec.end(), 60);
            vec.emplace(vec.end(), 70);

            CHECK(vec.size() == 7);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 60);
            CHECK(*vec.nth(6) == 70);

            CHECK(vec.erase(vec.nth(2), vec.nth(5)) == vec.nth(2));
            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 60);
            CHECK(*vec.nth(3) == 70);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);
            vec.emplace(vec.end(), 60);
            vec.emplace(vec.end(), 70);

            CHECK(vec.size() == 7);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 60);
            CHECK(*vec.nth(6) == 70);

            CHECK(vec.erase(vec.nth(3), vec.nth(6)) == vec.nth(3));
            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 70);
        }

        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);
            vec.emplace(vec.end(), 60);
            vec.emplace(vec.end(), 70);

            CHECK(vec.size() == 7);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 60);
            CHECK(*vec.nth(6) == 70);

            CHECK(vec.erase(vec.nth(4), vec.nth(7)) == vec.nth(4));
            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }
    }

    PRINT("Test resize(size_type)");
    {
        #define CONDITION n < vec.size()
        {
            sfl::static_vector<xint, 100> vec;

            using size_type = typename sfl::static_vector<xint, 100>::size_type;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);
            vec.emplace_back(50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            const size_type n = vec.size() - 1;

            CHECK(CONDITION);

            vec.resize(n);

            CHECK(vec.size() == 4);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 96);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }
        #undef CONDITION

        #define CONDITION n == vec.size()
        {
            sfl::static_vector<xint, 100> vec;

            using size_type = typename sfl::static_vector<xint, 100>::size_type;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);
            vec.emplace_back(50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            const size_type n = vec.size();

            CHECK(CONDITION);

            vec.resize(n);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
        }
        #undef CONDITION

        #define CONDITION n > vec.size() && n < vec.capacity()
        {
            sfl::static_vector<xint, 100> vec;

            using size_type = typename sfl::static_vector<xint, 100>::size_type;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);
            vec.emplace_back(50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            const size_type n = vec.capacity() - 1;

            CHECK(CONDITION);

            vec.resize(n);

            CHECK(vec.size() == n);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 1);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            for (size_type i = 5; i < n; ++i)
            {
                CHECK(*vec.nth(i) == SFL_TEST_XINT_DEFAULT_VALUE);
            }
        }
        #undef CONDITION

        #define CONDITION n > vec.size() && n == vec.capacity()
        {
            sfl::static_vector<xint, 100> vec;

            using size_type = typename sfl::static_vector<xint, 100>::size_type;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);
            vec.emplace_back(50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            const size_type n = vec.capacity();

            CHECK(CONDITION);

            vec.resize(n);

            CHECK(vec.size() == n);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 0);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            for (size_type i = 5; i < n; ++i)
            {
                CHECK(*vec.nth(i) == SFL_TEST_XINT_DEFAULT_VALUE);
            }
        }
        #undef CONDITION
    }

    PRINT("Test resize(size_type, const T&)");
    {
        #define CONDITION n < vec.size()
        {
            sfl::static_vector<xint, 100> vec;

            using size_type = typename sfl::static_vector<xint, 100>::size_type;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);
            vec.emplace_back(50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            const size_type n = vec.size() - 1;

            CHECK(CONDITION);

            xint value(987654);

            vec.resize(n, value);

            CHECK(vec.size() == 4);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 96);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }
        #undef CONDITION

        #define CONDITION n == vec.size()
        {
            sfl::static_vector<xint, 100> vec;

            using size_type = typename sfl::static_vector<xint, 100>::size_type;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);
            vec.emplace_back(50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            const size_type n = vec.size();

            CHECK(CONDITION);

            xint value(987654);

            vec.resize(n, value);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
        }
        #undef CONDITION

        #define CONDITION n > vec.size() && n < vec.capacity()
        {
            sfl::static_vector<xint, 100> vec;

            using size_type = typename sfl::static_vector<xint, 100>::size_type;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);
            vec.emplace_back(50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            const size_type n = vec.capacity() - 1;

            CHECK(CONDITION);

            xint value(987654);

            vec.resize(n, value);

            CHECK(vec.size() == n);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 1);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            for (size_type i = 5; i < n; ++i)
            {
                CHECK(*vec.nth(i) == value);
            }
        }
        #undef CONDITION

        #define CONDITION n > vec.size() && n == vec.capacity()
        {
            sfl::static_vector<xint, 100> vec;

            using size_type = typename sfl::static_vector<xint, 100>::size_type;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);
            vec.emplace_back(40);
            vec.emplace_back(50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 95);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            const size_type n = vec.capacity();

            CHECK(CONDITION);

            xint value(987654);

            vec.resize(n, value);

            CHECK(vec.size() == n);
            CHECK(vec.capacity() == 100);
            CHECK(vec.available() == 0);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            for (size_type i = 5; i < n; ++i)
            {
                CHECK(*vec.nth(i) == value);
            }
        }
        #undef CONDITION
    }

    PRINT("Test swap(static_vector&)");
    {
        // Swap with self
        {
            sfl::static_vector<xint, 100> vec;

            vec.emplace_back(10);
            vec.emplace_back(20);
            vec.emplace_back(30);

            CHECK(vec.size() == 3);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);

            ///////////////////////////////////////////////////////////////////

            vec.swap(vec);

            CHECK(vec.size() == 3);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
        }

        // vec1.size() == vec2.size()
        {
            sfl::static_vector<xint, 100> vec1, vec2;

            vec1.emplace_back(10);
            vec1.emplace_back(20);
            vec1.emplace_back(30);

            vec2.emplace_back(40);
            vec2.emplace_back(50);
            vec2.emplace_back(60);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);

            CHECK(vec2.size() == 3);
            CHECK(*vec2.nth(0) == 40);
            CHECK(*vec2.nth(1) == 50);
            CHECK(*vec2.nth(2) == 60);

            ///////////////////////////////////////////////////////////////////

            vec1.swap(vec2);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 40);
            CHECK(*vec1.nth(1) == 50);
            CHECK(*vec1.nth(2) == 60);

            CHECK(vec2.size() == 3);
            CHECK(*vec2.nth(0) == 10);
            CHECK(*vec2.nth(1) == 20);
            CHECK(*vec2.nth(2) == 30);

            ///////////////////////////////////////////////////////////////////

            vec1.swap(vec2);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);

            CHECK(vec2.size() == 3);
            CHECK(*vec2.nth(0) == 40);
            CHECK(*vec2.nth(1) == 50);
            CHECK(*vec2.nth(2) == 60);
        }

        // vec1.size() != vec2.size()
        {
            sfl::static_vector<xint, 100> vec1, vec2;

            vec1.emplace_back(10);
            vec1.emplace_back(20);
            vec1.emplace_back(30);

            vec2.emplace_back(40);
            vec2.emplace_back(50);
            vec2.emplace_back(60);
            vec2.emplace_back(70);
            vec2.emplace_back(80);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);

            CHECK(vec2.size() == 5);
            CHECK(*vec2.nth(0) == 40);
            CHECK(*vec2.nth(1) == 50);
            CHECK(*vec2.nth(2) == 60);
            CHECK(*vec2.nth(3) == 70);
            CHECK(*vec2.nth(4) == 80);

            ///////////////////////////////////////////////////////////////////

            vec1.swap(vec2);

            CHECK(vec1.size() == 5);
            CHECK(*vec1.nth(0) == 40);
            CHECK(*vec1.nth(1) == 50);
            CHECK(*vec1.nth(2) == 60);
            CHECK(*vec1.nth(3) == 70);
            CHECK(*vec1.nth(4) == 80);

            CHECK(vec2.size() == 3);
            CHECK(*vec2.nth(0) == 10);
            CHECK(*vec2.nth(1) == 20);
            CHECK(*vec2.nth(2) == 30);

            ///////////////////////////////////////////////////////////////////

            vec1.swap(vec2);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);

            CHECK(vec2.size() == 5);
            CHECK(*vec2.nth(0) == 40);
            CHECK(*vec2.nth(1) == 50);
            CHECK(*vec2.nth(2) == 60);
            CHECK(*vec2.nth(3) == 70);
            CHECK(*vec2.nth(4) == 80);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    PRINT("Test non-modifying member functions (empty container)");
    {
        // Non-const container
        {
            sfl::static_vector<xint, 5> v;

            CHECK(v.empty() == true);
            CHECK(v.full() == false);
            CHECK(v.size() == 0);
            CHECK(v.max_size() == 5);
            CHECK(v.capacity() == 5);
            CHECK(v.available() == 5);
            CHECK(v.begin() == v.end());
            CHECK(v.cbegin() == v.cend());
            CHECK(v.begin() == v.cbegin());
            CHECK(v.rbegin() == v.rend());
            CHECK(v.crbegin() == v.crend());
            CHECK(v.rbegin() == v.crbegin());
            CHECK(v.begin() == v.nth(0));
            CHECK(v.cbegin() == v.nth(0));
            CHECK(v.index_of(v.nth(0)) == 0);
        }

        // Const container
        {
            const sfl::static_vector<xint, 5> v;

            CHECK(v.empty() == true);
            CHECK(v.full() == false);
            CHECK(v.size() == 0);
            CHECK(v.max_size() == 5);
            CHECK(v.capacity() == 5);
            CHECK(v.available() == 5);
            CHECK(v.begin() == v.end());
            CHECK(v.cbegin() == v.cend());
            CHECK(v.begin() == v.cbegin());
            CHECK(v.rbegin() == v.rend());
            CHECK(v.crbegin() == v.crend());
            CHECK(v.rbegin() == v.crbegin());
            CHECK(v.begin() == v.nth(0));
            CHECK(v.cbegin() == v.nth(0));
            CHECK(v.index_of(v.nth(0)) == 0);
        }
    }

    PRINT("Test emplace_back(Args&&...)");
    {
        sfl::static_vector<xint, 5> v;

        {
            PRINT(">");
            const auto& res = v.emplace_back(10);
            PRINT("<");

            CHECK(res == 10);
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        {
            PRINT(">");
            const auto& res = v.emplace_back(20);
            PRINT("<");

            CHECK(res == 20);
            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        {
            PRINT(">");
            const auto& res = v.emplace_back(30);
            PRINT("<");

            CHECK(res == 30);
            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            PRINT(">");
            const auto& res = v.emplace_back(40);
            PRINT("<");

            CHECK(res == 40);
            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }

        {
            PRINT(">");
            const auto& res = v.emplace_back(50);
            PRINT("<");

            CHECK(res == 50);
            CHECK(v.size() == 5);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
        }
    }

    PRINT("Test non-modifying member functions (non-empty container)");
    {
        sfl::static_vector<xint, 3> v;

        {
            CHECK(v.empty() == true);
            CHECK(v.full() == false);
            CHECK(v.size() == 0);
            CHECK(v.capacity() == 3);
            CHECK(v.available() == 3);

            v.emplace_back(10);

            CHECK(v.empty() == false);
            CHECK(v.full() == false);
            CHECK(v.size() == 1);
            CHECK(v.capacity() == 3);
            CHECK(v.available() == 2);

            v.emplace_back(20);

            CHECK(v.empty() == false);
            CHECK(v.full() == false);
            CHECK(v.size() == 2);
            CHECK(v.capacity() == 3);
            CHECK(v.available() == 1);

            v.emplace_back(30);

            CHECK(v.empty() == false);
            CHECK(v.full() == true);
            CHECK(v.size() == 3);
            CHECK(v.capacity() == 3);
            CHECK(v.available() == 0);
        }

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
            CHECK(v.nth(0) < v.nth(1));
            CHECK(v.nth(0) < v.nth(2));
            CHECK(v.nth(0) < v.nth(3));

            CHECK(v.nth(1) < v.nth(2));
            CHECK(v.nth(1) < v.nth(3));

            CHECK(v.nth(2) < v.nth(3));
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
        }

        {
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            CHECK(v.front() == 10);
        }

        {
            CHECK(v.back() == 30);
        }

        {
            auto data = v.data();
            CHECK(*data == 10); ++data;
            CHECK(*data == 20); ++data;
            CHECK(*data == 30); ++data;
        }
    }

    PRINT("Test emplace(const_iterator, Args&&...)");
    {
        sfl::static_vector<xint, 6> v;

        // Emplace at the end
        {
            PRINT(">");
            auto res = v.emplace(v.end(), 10);
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        // Emplace at the end
        {
            PRINT(">");
            auto res = v.emplace(v.end(), 20);
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        // Emplace at the end
        {
            PRINT(">");
            auto res = v.emplace(v.end(), 30);
            PRINT("<");

            CHECK(res == v.nth(2));
            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        // Emplace at middle (closer to the end)
        {
            PRINT(">");
            auto res = v.emplace(v.nth(2), 25);
            PRINT("<");

            CHECK(res == v.nth(2));
            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 25);
            CHECK(v[3] == 30);
        }

        // Emplace at middle (closer to the begin)
        {
            PRINT(">");
            auto res = v.emplace(v.nth(1), 15);
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(v.size() == 5);
            CHECK(v[0] == 10);
            CHECK(v[1] == 15);
            CHECK(v[2] == 20);
            CHECK(v[3] == 25);
            CHECK(v[4] == 30);
        }

        // Emplace at the begin
        {
            PRINT(">");
            auto res = v.emplace(v.begin(), 5);
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(v.size() == 6);
            CHECK(v[0] == 5);
            CHECK(v[1] == 10);
            CHECK(v[2] == 15);
            CHECK(v[3] == 20);
            CHECK(v[4] == 25);
            CHECK(v[5] == 30);
        }
    }

    PRINT("Test clear()");
    {
        sfl::static_vector<xint, 5> v;

        {
            PRINT(">");
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            v.emplace_back(40);
            PRINT("<");

            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }

        {
            PRINT(">");
            v.clear();
            PRINT("<");

            CHECK(v.size() == 0);
        }

        {
            PRINT(">");
            v.emplace_back(50);
            v.emplace_back(60);
            PRINT("<");

            CHECK(v.size() == 2);
            CHECK(v[0] == 50);
            CHECK(v[1] == 60);
        }

        {
            PRINT(">");
            v.clear();
            PRINT("<");

            CHECK(v.size() == 0);
        }
    }

    PRINT("Test insert(const_iterator, const T&)");
    {
        sfl::static_vector<xint, 5> v;

        {
            const xint elem(10);

            PRINT(">");
            auto res = v.insert(v.end(), elem);
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }
    }

    PRINT("Test insert(const_iterator, T&&)");
    {
        sfl::static_vector<xint, 5> v;

        {
            xint elem(10);

            PRINT(">");
            auto res = v.insert(v.end(), std::move(elem));
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(elem == -10);
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }
    }

    PRINT("Test insert(const_iterator, size_type, const T&)");
    {
        sfl::static_vector<xint, 12> v;

        {
            PRINT(">");
            auto res = v.insert(v.nth(0), 3, xint(10));
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 10);
            CHECK(v[2] == 10);
        }

        {
            PRINT(">");
            auto res = v.insert(v.nth(1), 3, xint(20));
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(v.size() == 6);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 20);
            CHECK(v[3] == 20);
            CHECK(v[4] == 10);
            CHECK(v[5] == 10);
        }

        {
            PRINT(">");
            auto res = v.insert(v.nth(1), 2, xint(30));
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(v.size() == 8);
            CHECK(v[0] == 10);
            CHECK(v[1] == 30);
            CHECK(v[2] == 30);
            CHECK(v[3] == 20);
            CHECK(v[4] == 20);
            CHECK(v[5] == 20);
            CHECK(v[6] == 10);
            CHECK(v[7] == 10);
        }

        {
            PRINT(">");
            auto res = v.insert(v.nth(1), 4, xint(40));
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(v.size() == 12);
            CHECK(v[0]  == 10);
            CHECK(v[1]  == 40);
            CHECK(v[2]  == 40);
            CHECK(v[3]  == 40);
            CHECK(v[4]  == 40);
            CHECK(v[5]  == 30);
            CHECK(v[6]  == 30);
            CHECK(v[7]  == 20);
            CHECK(v[8]  == 20);
            CHECK(v[9]  == 20);
            CHECK(v[10] == 10);
            CHECK(v[11] == 10);
        }
    }

    PRINT("Test insert(const_iterator, InputIt, InputIt)");
    {
        sfl::static_vector<xint, 100> v;

        {
            std::istringstream iss("10 20 30 40");

            PRINT(">");
            auto res = v.insert
            (
                v.nth(0),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }

        {
            std::istringstream iss("31 32 33 34");

            PRINT(">");
            auto res = v.insert
            (
                v.nth(3),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            PRINT("<");

            CHECK(res == v.nth(3));
            CHECK(v.size() == 8);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 31);
            CHECK(v[4] == 32);
            CHECK(v[5] == 33);
            CHECK(v[6] == 34);
            CHECK(v[7] == 40);
        }

        {
            std::istringstream iss("11 12");

            PRINT(">");
            auto res = v.insert
            (
                v.nth(1),
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(v.size() == 10);
            CHECK(v[0] == 10);
            CHECK(v[1] == 11);
            CHECK(v[2] == 12);
            CHECK(v[3] == 20);
            CHECK(v[4] == 30);
            CHECK(v[5] == 31);
            CHECK(v[6] == 32);
            CHECK(v[7] == 33);
            CHECK(v[8] == 34);
            CHECK(v[9] == 40);
        }
    }

    PRINT("Test insert(const_iterator, ForwardIt, ForwardIt)");
    {
        sfl::static_vector<xint, 100> v;

        {
            const std::vector<xint> data({10, 20, 30, 40});

            PRINT(">");
            auto res = v.insert(v.begin(), data.begin(), data.end());
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }

        {
            const std::vector<xint> data({31, 32, 33, 34});

            PRINT(">");
            auto res = v.insert(v.nth(3), data.begin(), data.end());
            PRINT("<");

            CHECK(res == v.nth(3));
            CHECK(v.size() == 8);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 31);
            CHECK(v[4] == 32);
            CHECK(v[5] == 33);
            CHECK(v[6] == 34);
            CHECK(v[7] == 40);
        }

        {
            const std::vector<xint> data({11, 12});

            PRINT(">");
            auto res = v.insert(v.nth(1), data.begin(), data.end());
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(v.size() == 10);
            CHECK(v[0] == 10);
            CHECK(v[1] == 11);
            CHECK(v[2] == 12);
            CHECK(v[3] == 20);
            CHECK(v[4] == 30);
            CHECK(v[5] == 31);
            CHECK(v[6] == 32);
            CHECK(v[7] == 33);
            CHECK(v[8] == 34);
            CHECK(v[9] == 40);
        }
    }

    PRINT("Test insert(const_iterator, MoveIterator, MoveIterator)");
    {
        sfl::static_vector<xint, 100> v;

        {
            std::vector<xint> data({10, 20, 30, 40});

            PRINT(">");
            auto res = v.insert
            (
                v.begin(),
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            PRINT("<");

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

        {
            std::vector<xint> data({31, 32, 33, 34});

            PRINT(">");
            auto res = v.insert
            (
                v.nth(3),
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            PRINT("<");

            CHECK(res == v.nth(3));
            CHECK(data[0] == -31);
            CHECK(data[1] == -32);
            CHECK(data[2] == -33);
            CHECK(data[3] == -34);
            CHECK(v.size() == 8);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 31);
            CHECK(v[4] == 32);
            CHECK(v[5] == 33);
            CHECK(v[6] == 34);
            CHECK(v[7] == 40);
        }

        {
            std::vector<xint> data({11, 12});

            PRINT(">");
            auto res = v.insert
            (
                v.nth(1),
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(data[0] == -11);
            CHECK(data[1] == -12);
            CHECK(v.size() == 10);
            CHECK(v[0] == 10);
            CHECK(v[1] == 11);
            CHECK(v[2] == 12);
            CHECK(v[3] == 20);
            CHECK(v[4] == 30);
            CHECK(v[5] == 31);
            CHECK(v[6] == 32);
            CHECK(v[7] == 33);
            CHECK(v[8] == 34);
            CHECK(v[9] == 40);
        }
    }

    PRINT("Test insert(const_iterator, std::initializer_list)");
    {
        sfl::static_vector<xint, 100> v;

        {
            PRINT(">");
            auto res = v.insert(v.nth(0), {10, 20, 30, 40});
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }

        {
            PRINT(">");
            auto res = v.insert(v.nth(3), {31, 32, 33, 34});
            PRINT("<");

            CHECK(res == v.nth(3));
            CHECK(v.size() == 8);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 31);
            CHECK(v[4] == 32);
            CHECK(v[5] == 33);
            CHECK(v[6] == 34);
            CHECK(v[7] == 40);
        }

        {
            PRINT(">");
            auto res = v.insert(v.nth(1), {11, 12});
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(v.size() == 10);
            CHECK(v[0] == 10);
            CHECK(v[1] == 11);
            CHECK(v[2] == 12);
            CHECK(v[3] == 20);
            CHECK(v[4] == 30);
            CHECK(v[5] == 31);
            CHECK(v[6] == 32);
            CHECK(v[7] == 33);
            CHECK(v[8] == 34);
            CHECK(v[9] == 40);
        }
    }

    PRINT("Test push_back(const T&)");
    {
        sfl::static_vector<xint, 5> v;

        {
            const xint elem(10);

            PRINT(">");
            v.push_back(elem);
            PRINT("<");

            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        {
            const xint elem(20);

            PRINT(">");
            v.push_back(elem);
            PRINT("<");

            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        {
            const xint elem(30);

            PRINT(">");
            v.push_back(elem);
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            const xint elem(40);

            PRINT(">");
            v.push_back(elem);
            PRINT("<");

            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }

        {
            const xint elem(50);

            PRINT(">");
            v.push_back(elem);
            PRINT("<");

            CHECK(v.size() == 5);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
        }
    }

    PRINT("Test push_back(T&&)");
    {
        sfl::static_vector<xint, 5> v;

        {
            xint elem(10);

            PRINT(">");
            v.push_back(std::move(elem));
            PRINT("<");

            CHECK(elem == -10);
            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        {
            xint elem(20);

            PRINT(">");
            v.push_back(std::move(elem));
            PRINT("<");

            CHECK(elem == -20);
            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        {
            xint elem(30);

            PRINT(">");
            v.push_back(std::move(elem));
            PRINT("<");

            CHECK(elem == -30);
            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            xint elem(40);

            PRINT(">");
            v.push_back(std::move(elem));
            PRINT("<");

            CHECK(elem == -40);
            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }

        {
            xint elem(50);

            PRINT(">");
            v.push_back(std::move(elem));
            PRINT("<");

            CHECK(elem == -50);
            CHECK(v.size() == 5);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
            CHECK(v[4] == 50);
        }
    }

    PRINT("Test pop_back()");
    {
        sfl::static_vector<xint, 10> v;

        {
            PRINT(">");
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        {
            PRINT(">");
            v.pop_back();
            PRINT("<");

            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        {
            PRINT(">");
            v.pop_back();
            PRINT("<");

            CHECK(v.size() == 1);
            CHECK(v[0] == 10);
        }

        {
            PRINT(">");
            v.pop_back();
            PRINT("<");

            CHECK(v.size() == 0);
        }
    }

    PRINT("Test erase(const_iterator)");
    {
        sfl::static_vector<xint, 10> v;

        {
            PRINT(">");
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            v.emplace_back(40);
            PRINT("<");

            CHECK(v.size() == 4);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 40);
        }

        {
            PRINT(">");
            auto res = v.erase(v.nth(1));
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 30);
            CHECK(v[2] == 40);
        }

        {
            PRINT(">");
            auto res = v.erase(v.nth(0));
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(v.size() == 2);
            CHECK(v[0] == 30);
            CHECK(v[1] == 40);
        }

        {
            PRINT(">");
            auto res = v.erase(v.nth(1));
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(v.size() == 1);
            CHECK(v[0] == 30);
        }

        {
            PRINT(">");
            auto res = v.erase(v.nth(0));
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(v.size() == 0);
        }
    }

    PRINT("Test erase(const_iterator, const_iterator)");
    {
        sfl::static_vector<xint, 10> v;

        {
            PRINT(">");
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            v.emplace_back(40);
            v.emplace_back(50);
            v.emplace_back(60);
            v.emplace_back(70);
            v.emplace_back(80);
            v.emplace_back(90);
            PRINT("<");

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
            PRINT(">");
            // Erase nothing
            auto res = v.erase(v.nth(3), v.nth(3));
            PRINT("<");

            CHECK(res == v.nth(3));
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
            PRINT(">");
            // Erase two elements near begin
            auto res = v.erase(v.nth(1), v.nth(3));
            PRINT("<");

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
            PRINT(">");
            // Erase two elements near end
            auto res = v.erase(v.nth(4), v.nth(6));
            PRINT("<");

            CHECK(res == v.nth(4));
            CHECK(v.size() == 5);
            CHECK(v[0] == 10);
            CHECK(v[1] == 40);
            CHECK(v[2] == 50);
            CHECK(v[3] == 60);
            CHECK(v[4] == 90);
        }

        {
            PRINT(">");
            // Remove two elements at begin
            auto res = v.erase(v.nth(0), v.nth(2));
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(v.size() == 3);
            CHECK(v[0] == 50);
            CHECK(v[1] == 60);
            CHECK(v[2] == 90);
        }

        {
            PRINT(">");
            // Remove two elements at end
            auto res = v.erase(v.nth(1), v.nth(3));
            PRINT("<");

            CHECK(res == v.nth(1));
            CHECK(v.size() == 1);
            CHECK(v[0] == 50);
        }

        {
            PRINT(">");
            // Remove from begin to end
            auto res = v.erase(v.nth(0), v.nth(1));
            PRINT("<");

            CHECK(res == v.nth(0));
            CHECK(v.size() == 0);
        }
    }

    PRINT("Test resize(size_type)");
    {
        sfl::static_vector<xint, 10> v;

        {
            PRINT(">");
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        // n == size
        {
            PRINT(">");
            v.resize(3);
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        // n > size
        {
            PRINT(">");
            v.resize(6);
            PRINT("<");

            CHECK(v.size() == 6);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == SFL_TEST_XINT_DEFAULT_VALUE);
            CHECK(v[4] == SFL_TEST_XINT_DEFAULT_VALUE);
            CHECK(v[5] == SFL_TEST_XINT_DEFAULT_VALUE);
        }

        // n < size
        {
            PRINT(">");
            v.resize(2);
            PRINT("<");

            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        // n > size
        {
            PRINT(">");
            v.resize(6);
            PRINT("<");

            CHECK(v.size() == 6);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == SFL_TEST_XINT_DEFAULT_VALUE);
            CHECK(v[3] == SFL_TEST_XINT_DEFAULT_VALUE);
            CHECK(v[4] == SFL_TEST_XINT_DEFAULT_VALUE);
            CHECK(v[5] == SFL_TEST_XINT_DEFAULT_VALUE);
        }
    }

    PRINT("Test resize(size_type, const T&)");
    {
        sfl::static_vector<xint, 10> v;

        {
            PRINT(">");
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        // n == size
        {
            PRINT(">");
            v.resize(3, 111);
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        // n > size
        {
            PRINT(">");
            v.resize(6, 222);
            PRINT("<");

            CHECK(v.size() == 6);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
            CHECK(v[3] == 222);
            CHECK(v[4] == 222);
            CHECK(v[5] == 222);
        }

        // n < size
        {
            PRINT(">");
            v.resize(2, 333);
            PRINT("<");

            CHECK(v.size() == 2);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
        }

        // n > size
        {
            PRINT(">");
            v.resize(6, 444);
            PRINT("<");

            CHECK(v.size() == 6);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 444);
            CHECK(v[3] == 444);
            CHECK(v[4] == 444);
            CHECK(v[5] == 444);
        }
    }

    PRINT("Test swap(static_vector&)");
    {
        // Swap with self
        {
            sfl::static_vector<xint, 10> v;

            PRINT(">");
            v.emplace_back(10);
            v.emplace_back(20);
            v.emplace_back(30);
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);

            PRINT(">");
            v.swap(v);
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 20);
            CHECK(v[2] == 30);
        }

        // v1.size() == v2.size()
        {
            sfl::static_vector<xint, 10> v1;
            sfl::static_vector<xint, 10> v2;

            PRINT(">");
            v1.emplace_back(10);
            v1.emplace_back(11);
            v1.emplace_back(12);
            PRINT("<");

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);

            PRINT(">");
            v2.emplace_back(20);
            v2.emplace_back(21);
            v2.emplace_back(22);
            PRINT("<");

            CHECK(v2.size() == 3);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);

            PRINT(">");
            v1.swap(v2);
            PRINT("<");

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 20);
            CHECK(v1[1] == 21);
            CHECK(v1[2] == 22);

            CHECK(v2.size() == 3);
            CHECK(v2[0] == 10);
            CHECK(v2[1] == 11);
            CHECK(v2[2] == 12);

            PRINT(">");
            v1.swap(v2);
            PRINT("<");

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);

            CHECK(v2.size() == 3);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);
        }

        // v1.size() != v2.size()
        {
            sfl::static_vector<xint, 10> v1;
            sfl::static_vector<xint, 10> v2;

            PRINT(">");
            v1.emplace_back(10);
            v1.emplace_back(11);
            v1.emplace_back(12);
            PRINT("<");

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);

            PRINT(">");
            v2.emplace_back(20);
            v2.emplace_back(21);
            v2.emplace_back(22);
            v2.emplace_back(23);
            v2.emplace_back(24);
            PRINT("<");

            CHECK(v2.size() == 5);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);
            CHECK(v2[3] == 23);
            CHECK(v2[4] == 24);

            PRINT(">");
            v1.swap(v2);
            PRINT("<");

            CHECK(v1.size() == 5);
            CHECK(v1[0] == 20);
            CHECK(v1[1] == 21);
            CHECK(v1[2] == 22);
            CHECK(v1[3] == 23);
            CHECK(v1[4] == 24);

            CHECK(v2.size() == 3);
            CHECK(v2[0] == 10);
            CHECK(v2[1] == 11);
            CHECK(v2[2] == 12);

            PRINT(">");
            v1.swap(v2);
            PRINT("<");

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);

            CHECK(v2.size() == 5);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);
            CHECK(v2[3] == 23);
            CHECK(v2[4] == 24);
        }
    }

    PRINT("Test constructor()");
    {
        sfl::static_vector<xint, 10> v;

        CHECK(v.size() == 0);
    }

    PRINT("Test constructor(size_type)");
    {
        sfl::static_vector<xint, 10> v(3);

        CHECK(v.size() == 3);
        CHECK(v[0] == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(v[1] == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(v[2] == SFL_TEST_XINT_DEFAULT_VALUE);
    }

    PRINT("Test constructor(size_type, const T&)");
    {
        sfl::static_vector<xint, 10> v(3, 42);

        CHECK(v.size() == 3);
        CHECK(v[0] == 42);
        CHECK(v[1] == 42);
        CHECK(v[2] == 42);
    }

    PRINT("Test constructor(InputIt, InputIt)");
    {
        std::istringstream iss("10 20 30 40");

        PRINT(">");
        sfl::static_vector<xint, 10> v
        (
            (std::istream_iterator<int>(iss)),
            (std::istream_iterator<int>())
        );
        PRINT("<");

        CHECK(v.size() == 4);
        CHECK(v[0] == 10);
        CHECK(v[1] == 20);
        CHECK(v[2] == 30);
        CHECK(v[3] == 40);
    }

    PRINT("Test constructor(ForwardIt, ForwardIt)");
    {
        const std::vector<xint> data({10, 20, 30, 40});

        PRINT(">");
        sfl::static_vector<xint, 10> v(data.begin(), data.end());
        PRINT("<");

        CHECK(v.size() == 4);
        CHECK(v[0] == 10);
        CHECK(v[1] == 20);
        CHECK(v[2] == 30);
        CHECK(v[3] == 40);
    }

    PRINT("Test constructor(MoveIterator, MoveIterator)");
    {
        std::vector<xint> data({10, 20, 30, 40});

        PRINT(">");
        sfl::static_vector<xint, 10> v
        (
            std::make_move_iterator(data.begin()),
            std::make_move_iterator(data.end())
        );
        PRINT("<");

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

    PRINT("Test constructor(std::initializer_list)");
    {
        PRINT(">");
        sfl::static_vector<xint, 10> v({10, 20, 30, 40});
        PRINT("<");

        CHECK(v.size() == 4);
        CHECK(v[0] == 10);
        CHECK(v[1] == 20);
        CHECK(v[2] == 30);
        CHECK(v[3] == 40);
    }

    PRINT("Test constructor(const static_vector&)");
    {
        sfl::static_vector<xint, 10> v1({10, 20, 30, 40});
        sfl::static_vector<xint, 10> v2(v1);

        CHECK(v1.size() == 4);
        CHECK(v1[0] == 10);
        CHECK(v1[1] == 20);
        CHECK(v1[2] == 30);
        CHECK(v1[3] == 40);

        CHECK(v2.size() == 4);
        CHECK(v2[0] == 10);
        CHECK(v2[1] == 20);
        CHECK(v2[2] == 30);
        CHECK(v2[3] == 40);
    }

    PRINT("Test constructor(static_vector&&)");
    {
        sfl::static_vector<xint, 10> v1({10, 20, 30, 40});
        sfl::static_vector<xint, 10> v2(std::move(v1));

        // v1 is in valid but unspecified state
        CHECK(v1.size() == 4);
        CHECK(v1[0] == -10);
        CHECK(v1[1] == -20);
        CHECK(v1[2] == -30);
        CHECK(v1[3] == -40);

        CHECK(v2.size() == 4);
        CHECK(v2[0] == 10);
        CHECK(v2[1] == 20);
        CHECK(v2[2] == 30);
        CHECK(v2[3] == 40);
    }

    PRINT("Test assign(size_type, const T&)");
    {
        sfl::static_vector<xint, 10> v;

        {
            PRINT(">");
            v.assign(3, 10);
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 10);
            CHECK(v[1] == 10);
            CHECK(v[2] == 10);
        }

        {
            PRINT(">");
            v.assign(2, 20);
            PRINT("<");

            CHECK(v.size() == 2);
            CHECK(v[0] == 20);
            CHECK(v[1] == 20);
        }

        {
            PRINT(">");
            v.assign(4, 30);
            PRINT("<");

            CHECK(v.size() == 4);
            CHECK(v[0] == 30);
            CHECK(v[1] == 30);
            CHECK(v[2] == 30);
            CHECK(v[3] == 30);
        }

        {
            PRINT(">");
            v.assign(6, 40);
            PRINT("<");

            CHECK(v.size() == 6);
            CHECK(v[0] == 40);
            CHECK(v[1] == 40);
            CHECK(v[2] == 40);
            CHECK(v[3] == 40);
            CHECK(v[4] == 40);
            CHECK(v[5] == 40);
        }

        {
            PRINT(">");
            v.assign(0, 50);
            PRINT("<");

            CHECK(v.size() == 0);
        }
    }

    PRINT("Test assign(InputIt, InputIt)");
    {
        sfl::static_vector<xint, 10> v;

        {
            std::istringstream iss("11 12 13");

            PRINT(">");
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 11);
            CHECK(v[1] == 12);
            CHECK(v[2] == 13);
        }

        {
            std::istringstream iss("21 22");

            PRINT(">");
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            PRINT("<");

            CHECK(v.size() == 2);
            CHECK(v[0] == 21);
            CHECK(v[1] == 22);
        }

        {
            std::istringstream iss("31 32 33 34");

            PRINT(">");
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            PRINT("<");

            CHECK(v.size() == 4);
            CHECK(v[0] == 31);
            CHECK(v[1] == 32);
            CHECK(v[2] == 33);
            CHECK(v[3] == 34);
        }

        {
            std::istringstream iss("41 42 43 44 45 46");

            PRINT(">");
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            PRINT("<");

            CHECK(v.size() == 6);
            CHECK(v[0] == 41);
            CHECK(v[1] == 42);
            CHECK(v[2] == 43);
            CHECK(v[3] == 44);
            CHECK(v[4] == 45);
            CHECK(v[5] == 46);
        }

        {
            std::istringstream iss("");

            PRINT(">");
            v.assign
            (
                std::istream_iterator<int>(iss),
                std::istream_iterator<int>()
            );
            PRINT("<");

            CHECK(v.size() == 0);
            CHECK(v.capacity() == 10);
        }
    }

    PRINT("Test assign(ForwardIt, ForwardIt)");
    {
        sfl::static_vector<xint, 10> v;

        {
            const std::vector<int> data({11, 12, 13});

            PRINT(">");
            v.assign(data.begin(), data.end());
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 11);
            CHECK(v[1] == 12);
            CHECK(v[2] == 13);
        }

        {
            const std::vector<int> data({21, 22});

            PRINT(">");
            v.assign(data.begin(), data.end());
            PRINT("<");

            CHECK(v.size() == 2);
            CHECK(v[0] == 21);
            CHECK(v[1] == 22);
        }

        {
            const std::vector<int> data({31, 32, 33, 34});

            PRINT(">");
            v.assign(data.begin(), data.end());
            PRINT("<");

            CHECK(v.size() == 4);
            CHECK(v[0] == 31);
            CHECK(v[1] == 32);
            CHECK(v[2] == 33);
            CHECK(v[3] == 34);
        }

        {
            const std::vector<int> data({41, 42, 43, 44, 45, 46});

            PRINT(">");
            v.assign(data.begin(), data.end());
            PRINT("<");

            CHECK(v.size() == 6);
            CHECK(v[0] == 41);
            CHECK(v[1] == 42);
            CHECK(v[2] == 43);
            CHECK(v[3] == 44);
            CHECK(v[4] == 45);
            CHECK(v[5] == 46);
        }

        {
            const std::vector<int> data;

            PRINT(">");
            v.assign(data.begin(), data.end());
            PRINT("<");

            CHECK(v.size() == 0);
        }
    }

    PRINT("Test assign(MoveIterator, MoveIterator)");
    {
        sfl::static_vector<xint, 10> v;

        {
            std::vector<xint> data({11, 12, 13});

            PRINT(">");
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            PRINT("<");

            CHECK(data[0] == -11);
            CHECK(data[1] == -12);
            CHECK(data[2] == -13);
            CHECK(v.size() == 3);
            CHECK(v[0] == 11);
            CHECK(v[1] == 12);
            CHECK(v[2] == 13);
        }

        {
            std::vector<xint> data({21, 22});

            PRINT(">");
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            PRINT("<");

            CHECK(data[0] == -21);
            CHECK(data[1] == -22);
            CHECK(v.size() == 2);
            CHECK(v[0] == 21);
            CHECK(v[1] == 22);
        }

        {
            std::vector<xint> data({31, 32, 33, 34});

            PRINT(">");
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            PRINT("<");

            CHECK(data[0] == -31);
            CHECK(data[1] == -32);
            CHECK(data[2] == -33);
            CHECK(data[3] == -34);
            CHECK(v.size() == 4);
            CHECK(v[0] == 31);
            CHECK(v[1] == 32);
            CHECK(v[2] == 33);
            CHECK(v[3] == 34);
        }

        {
            std::vector<xint> data({41, 42, 43, 44, 45, 46});

            PRINT(">");
            v.assign
            (
                std::make_move_iterator(data.begin()),
                std::make_move_iterator(data.end())
            );
            PRINT("<");

            CHECK(data[0] == -41);
            CHECK(data[1] == -42);
            CHECK(data[2] == -43);
            CHECK(data[3] == -44);
            CHECK(data[4] == -45);
            CHECK(data[5] == -46);
            CHECK(v.size() == 6);
            CHECK(v[0] == 41);
            CHECK(v[1] == 42);
            CHECK(v[2] == 43);
            CHECK(v[3] == 44);
            CHECK(v[4] == 45);
            CHECK(v[5] == 46);
        }
    }

    PRINT("Test assign(std::initializer_list)");
    {
        sfl::static_vector<xint, 10> v;

        // n <= capacity && n > size
        {
            PRINT(">");
            v.assign({11, 12, 13});
            PRINT("<");

            CHECK(v.size() == 3);
            CHECK(v[0] == 11);
            CHECK(v[1] == 12);
            CHECK(v[2] == 13);
        }

        // n <= capacity && n <= size
        {
            PRINT(">");
            v.assign({21, 22});
            PRINT("<");

            CHECK(v.size() == 2);
            CHECK(v[0] == 21);
            CHECK(v[1] == 22);
        }

        // n <= capacity && n > size
        {
            PRINT(">");
            v.assign({31, 32, 33, 34});
            PRINT("<");

            CHECK(v.size() == 4);
            CHECK(v[0] == 31);
            CHECK(v[1] == 32);
            CHECK(v[2] == 33);
            CHECK(v[3] == 34);
        }

        // n > capacity
        {
            PRINT(">");
            v.assign({41, 42, 43, 44, 45, 46});
            PRINT("<");

            CHECK(v.size() == 6);
            CHECK(v[0] == 41);
            CHECK(v[1] == 42);
            CHECK(v[2] == 43);
            CHECK(v[3] == 44);
            CHECK(v[4] == 45);
            CHECK(v[5] == 46);
        }

        {
            PRINT(">");
            v.assign({});
            PRINT("<");

            CHECK(v.size() == 0);
        }
    }

    PRINT("Test operator=(const static_vector&)");
    {
        // v1.size() == v2.size()
        {
            sfl::static_vector<xint, 10> v1({10, 11, 12});
            sfl::static_vector<xint, 10> v2({20, 21, 22});

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);

            CHECK(v2.size() == 3);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);

            PRINT(">");
            v1 = v2;
            PRINT("<");

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 20);
            CHECK(v1[1] == 21);
            CHECK(v1[2] == 22);

            CHECK(v2.size() == 3);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);
        }

        // v1.size() < v2.size()
        {
            sfl::static_vector<xint, 10> v1({10, 11, 12});
            sfl::static_vector<xint, 10> v2({20, 21, 22, 23, 24});

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);

            CHECK(v2.size() == 5);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);
            CHECK(v2[3] == 23);
            CHECK(v2[4] == 24);

            PRINT(">");
            v1 = v2;
            PRINT("<");

            CHECK(v1.size() == 5);
            CHECK(v1[0] == 20);
            CHECK(v1[1] == 21);
            CHECK(v1[2] == 22);
            CHECK(v1[3] == 23);
            CHECK(v1[4] == 24);

            CHECK(v2.size() == 5);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);
            CHECK(v2[3] == 23);
            CHECK(v2[4] == 24);
        }

        // v1.size() > v2.size()
        {
            sfl::static_vector<xint, 10> v1({10, 11, 12, 13, 14});
            sfl::static_vector<xint, 10> v2({20, 21, 22});

            CHECK(v1.size() == 5);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);
            CHECK(v1[3] == 13);
            CHECK(v1[4] == 14);

            CHECK(v2.size() == 3);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);

            PRINT(">");
            v1 = v2;
            PRINT("<");

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 20);
            CHECK(v1[1] == 21);
            CHECK(v1[2] == 22);

            CHECK(v2.size() == 3);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);
        }
    }

    PRINT("Test operator=(static_vector&&)");
    {
        // v1.size() == v2.size()
        {
            sfl::static_vector<xint, 10> v1({10, 11, 12});
            sfl::static_vector<xint, 10> v2({20, 21, 22});

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);

            CHECK(v2.size() == 3);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);

            PRINT(">");
            v1 = std::move(v2);
            PRINT("<");

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 20);
            CHECK(v1[1] == 21);
            CHECK(v1[2] == 22);

            // v2 is in a valid but unspecified state
            CHECK(v2.size() == 3);
            CHECK(v2[0] == -20);
            CHECK(v2[1] == -21);
            CHECK(v2[2] == -22);
        }

        // v1.size() < v2.size()
        {
            sfl::static_vector<xint, 10> v1({10, 11, 12});
            sfl::static_vector<xint, 10> v2({20, 21, 22, 23, 24});

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);

            CHECK(v2.size() == 5);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);
            CHECK(v2[3] == 23);
            CHECK(v2[4] == 24);

            PRINT(">");
            v1 = std::move(v2);
            PRINT("<");

            CHECK(v1.size() == 5);
            CHECK(v1[0] == 20);
            CHECK(v1[1] == 21);
            CHECK(v1[2] == 22);
            CHECK(v1[3] == 23);
            CHECK(v1[4] == 24);

            // v2 is in a valid but unspecified state
            CHECK(v2.size() == 5);
            CHECK(v2[0] == -20);
            CHECK(v2[1] == -21);
            CHECK(v2[2] == -22);
            CHECK(v2[3] == -23);
            CHECK(v2[4] == -24);
        }

        // v1.size() > v2.size()
        {
            sfl::static_vector<xint, 10> v1({10, 11, 12, 13, 14});
            sfl::static_vector<xint, 10> v2({20, 21, 22});

            CHECK(v1.size() == 5);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);
            CHECK(v1[3] == 13);
            CHECK(v1[4] == 14);

            CHECK(v2.size() == 3);
            CHECK(v2[0] == 20);
            CHECK(v2[1] == 21);
            CHECK(v2[2] == 22);

            PRINT(">");
            v1 = std::move(v2);
            PRINT("<");

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 20);
            CHECK(v1[1] == 21);
            CHECK(v1[2] == 22);

            // v2 is in a valid but unspecified state
            CHECK(v2.size() == 3);
            CHECK(v2[0] == -20);
            CHECK(v2[1] == -21);
            CHECK(v2[2] == -22);
        }
    }

    PRINT("Test operator=(std::initializer_list)");
    {
        // v1.size() == ilist.size()
        {
            sfl::static_vector<xint, 10> v1({10, 11, 12});

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);

            PRINT(">");
            v1 = {20, 21, 22};
            PRINT("<");

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 20);
            CHECK(v1[1] == 21);
            CHECK(v1[2] == 22);
        }

        // v1.size() < ilist.size()
        {
            sfl::static_vector<xint, 10> v1({10, 11, 12});

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);

            PRINT(">");
            v1 = {20, 21, 22, 23, 24};
            PRINT("<");

            CHECK(v1.size() == 5);
            CHECK(v1[0] == 20);
            CHECK(v1[1] == 21);
            CHECK(v1[2] == 22);
            CHECK(v1[3] == 23);
            CHECK(v1[4] == 24);
        }

        // v1.size() > ilist.size()
        {
            sfl::static_vector<xint, 10> v1({10, 11, 12, 13, 14});

            CHECK(v1.size() == 5);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 11);
            CHECK(v1[2] == 12);
            CHECK(v1[3] == 13);
            CHECK(v1[4] == 14);

            PRINT(">");
            v1 = {20, 21, 22};
            PRINT("<");

            CHECK(v1.size() == 3);
            CHECK(v1[0] == 20);
            CHECK(v1[1] == 21);
            CHECK(v1[2] == 22);
        }
    }

    PRINT("Test non-member comparison operators");
    {
        sfl::static_vector<xint, 10> v1({10, 20, 30});
        sfl::static_vector<xint, 10> v2({10, 20, 30, 40});

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

    PRINT("Test non-member swap");
    {
        sfl::static_vector<xint, 10> v1({10, 11, 12});
        sfl::static_vector<xint, 10> v2({20, 21, 22});

        using std::swap;
        swap(v1, v2);
    }

    PRINT("Test non-member erase(static_vector&, const U&)");
    {
        sfl::static_vector<xint, 10> v1({10, 20, 20, 30, 30, 30});

        CHECK(v1.size() == 6);
        CHECK(v1[0] == 10);
        CHECK(v1[1] == 20);
        CHECK(v1[2] == 20);
        CHECK(v1[3] == 30);
        CHECK(v1[4] == 30);
        CHECK(v1[5] == 30);

        {
            PRINT(">");
            auto res = erase(v1, 42);
            PRINT("<");

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
            PRINT(">");
            auto res = erase(v1, 20);
            PRINT("<");

            CHECK(res == 2);
            CHECK(v1.size() == 4);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 30);
            CHECK(v1[2] == 30);
            CHECK(v1[3] == 30);
        }
    }

    PRINT("Test non-member erase_if(small_vector&, Predicate)");
    {
        sfl::static_vector<xint, 10> v1({10, 20, 20, 30, 30, 30});

        CHECK(v1.size() == 6);
        CHECK(v1[0] == 10);
        CHECK(v1[1] == 20);
        CHECK(v1[2] == 20);
        CHECK(v1[3] == 30);
        CHECK(v1[4] == 30);
        CHECK(v1[5] == 30);

        {
            PRINT(">");
            auto res = erase_if(v1, [](const xint& x){ return x == 42; });
            PRINT("<");

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
            PRINT(">");
            auto res = erase_if(v1, [](const xint& x){ return x == 20; });
            PRINT("<");

            CHECK(res == 2);
            CHECK(v1.size() == 4);
            CHECK(v1[0] == 10);
            CHECK(v1[1] == 30);
            CHECK(v1[2] == 30);
            CHECK(v1[3] == 30);
        }
    }
}
