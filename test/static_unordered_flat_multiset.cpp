//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include static_unordered_flat_multiset.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG // This is very important. Must be in the first line.

#define SFL_TEST_STATIC_UNORDERED_FLAT_MULTISET
#include "sfl/static_unordered_flat_multiset.hpp"

#include "check.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xint_xint.hpp"
#include "xobj.hpp"

#include <vector>

void test_static_unordered_flat_multiset()
{
    using sfl::test::xint;
    using sfl::test::xint_xint;
    using sfl::test::xobj;

    PRINT("Test PRIVATE member function emplace_back(Args&&...)");
    {
        sfl::static_unordered_flat_multiset<xint_xint, 5, std::equal_to<xint_xint>> set;

        {
            CHECK(set.empty() == true);
            CHECK(set.full() == false);
            CHECK(set.size() == 0);
            CHECK(set.capacity() == 5);
            CHECK(set.available() == 5);
        }

        {
            PRINT(">");
            const auto res = set.emplace_back(10, 1);
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
            const auto res = set.emplace_back(20, 1);
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
            const auto res = set.emplace_back(30, 1);
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
            const auto res = set.emplace_back(40, 1);
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
            const auto res = set.emplace_back(50, 1);
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
}

int main()
{
    test_static_unordered_flat_multiset();
}
