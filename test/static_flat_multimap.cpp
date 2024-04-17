//
// g++ -std=c++11 -g -O0 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -I ../include static_flat_multimap.cpp
// valgrind --leak-check=full ./a.out
//

#undef NDEBUG // This is very important. Must be in the first line.

#define SFL_TEST_STATIC_FLAT_MULTIMAP
#include "sfl/static_flat_multimap.hpp"

#include "check.hpp"
#include "print.hpp"

#include "xint.hpp"
#include "xobj.hpp"

#include <vector>

void test_static_flat_multimap()
{
    using sfl::test::xint;
    using sfl::test::xobj;

    PRINT("Test PRIVATE member function insert_exactly_at(const_iterator, Args&&...)");
    {
        // Insert at the end
        {
            sfl::static_flat_multimap<xint, xint, 5, std::less<xint>> map;

            {
                CHECK(map.empty() == true);
                CHECK(map.full() == false);
                CHECK(map.size() == 0);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 5);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.end(), 10, 1);
                PRINT("<");

                CHECK(res == map.nth(0));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 1);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 4);
                CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.end(), 20, 1);
                PRINT("<");

                CHECK(res == map.nth(1));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 2);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 3);
                CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
                CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.end(), 30, 1);
                PRINT("<");

                CHECK(res == map.nth(2));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 3);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 2);
                CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
                CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
                CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.end(), 40, 1);
                PRINT("<");

                CHECK(res == map.nth(3));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 4);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 1);
                CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
                CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
                CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
                CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.end(), 50, 1);
                PRINT("<");

                CHECK(res == map.nth(4));
                CHECK(map.empty() == false);
                CHECK(map.full() == true);
                CHECK(map.size() == 5);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 0);
                CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
                CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
                CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
                CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
                CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);
            }
        }

        // Insert at the begin
        {
            sfl::static_flat_multimap<xint, xint, 5, std::less<xint>> map;

            {
                CHECK(map.empty() == true);
                CHECK(map.full() == false);
                CHECK(map.size() == 0);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 5);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.begin(), 50, 1);
                PRINT("<");

                CHECK(res == map.nth(0));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 1);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 4);
                CHECK(map.nth(0)->first == 50); CHECK(map.nth(0)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.begin(), 40, 1);
                PRINT("<");

                CHECK(res == map.nth(0));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 2);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 3);
                CHECK(map.nth(0)->first == 40); CHECK(map.nth(0)->second == 1);
                CHECK(map.nth(1)->first == 50); CHECK(map.nth(1)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.begin(), 30, 1);
                PRINT("<");

                CHECK(res == map.nth(0));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 3);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 2);
                CHECK(map.nth(0)->first == 30); CHECK(map.nth(0)->second == 1);
                CHECK(map.nth(1)->first == 40); CHECK(map.nth(1)->second == 1);
                CHECK(map.nth(2)->first == 50); CHECK(map.nth(2)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.begin(), 20, 1);
                PRINT("<");

                CHECK(res == map.nth(0));
                CHECK(map.empty() == false);
                CHECK(map.full() == false);
                CHECK(map.size() == 4);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 1);
                CHECK(map.nth(0)->first == 20); CHECK(map.nth(0)->second == 1);
                CHECK(map.nth(1)->first == 30); CHECK(map.nth(1)->second == 1);
                CHECK(map.nth(2)->first == 40); CHECK(map.nth(2)->second == 1);
                CHECK(map.nth(3)->first == 50); CHECK(map.nth(3)->second == 1);
            }

            {
                PRINT(">");
                const auto res = map.insert_exactly_at(map.begin(), 10, 1);
                PRINT("<");

                CHECK(res == map.nth(0));
                CHECK(map.empty() == false);
                CHECK(map.full() == true);
                CHECK(map.size() == 5);
                CHECK(map.capacity() == 5);
                CHECK(map.available() == 0);
                CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
                CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
                CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
                CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
                CHECK(map.nth(4)->first == 50); CHECK(map.nth(4)->second == 1);
            }
        }

        {
            sfl::static_flat_multimap<xint, xint, 5, std::less<xint>> map;

            map.insert_exactly_at(map.end(), 10, 1);
            map.insert_exactly_at(map.end(), 20, 1);
            map.insert_exactly_at(map.end(), 30, 1);
            map.insert_exactly_at(map.end(), 40, 1);

            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 4);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            const auto res = map.insert_exactly_at(map.nth(0), 5, 1);

            CHECK(res == map.nth(0));
            CHECK(map.empty() == false);
            CHECK(map.full() == true);
            CHECK(map.size() == 5);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 0);
            CHECK(map.nth(0)->first ==  5); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 10); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 20); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 30); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 40); CHECK(map.nth(4)->second == 1);
        }

        {
            sfl::static_flat_multimap<xint, xint, 5, std::less<xint>> map;

            map.insert_exactly_at(map.end(), 10, 1);
            map.insert_exactly_at(map.end(), 20, 1);
            map.insert_exactly_at(map.end(), 30, 1);
            map.insert_exactly_at(map.end(), 40, 1);

            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 4);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            const auto res = map.insert_exactly_at(map.nth(1), 15, 1);

            CHECK(res == map.nth(1));
            CHECK(map.empty() == false);
            CHECK(map.full() == true);
            CHECK(map.size() == 5);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 0);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 15); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 20); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 30); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 40); CHECK(map.nth(4)->second == 1);
        }

        {
            sfl::static_flat_multimap<xint, xint, 5, std::less<xint>> map;

            map.insert_exactly_at(map.end(), 10, 1);
            map.insert_exactly_at(map.end(), 20, 1);
            map.insert_exactly_at(map.end(), 30, 1);
            map.insert_exactly_at(map.end(), 40, 1);

            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 4);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            const auto res = map.insert_exactly_at(map.nth(2), 25, 1);

            CHECK(res == map.nth(2));
            CHECK(map.empty() == false);
            CHECK(map.full() == true);
            CHECK(map.size() == 5);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 0);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 25); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 30); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 40); CHECK(map.nth(4)->second == 1);
        }

        {
            sfl::static_flat_multimap<xint, xint, 5, std::less<xint>> map;

            map.insert_exactly_at(map.end(), 10, 1);
            map.insert_exactly_at(map.end(), 20, 1);
            map.insert_exactly_at(map.end(), 30, 1);
            map.insert_exactly_at(map.end(), 40, 1);

            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 4);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            const auto res = map.insert_exactly_at(map.nth(3), 35, 1);

            CHECK(res == map.nth(3));
            CHECK(map.empty() == false);
            CHECK(map.full() == true);
            CHECK(map.size() == 5);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 0);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 35); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 40); CHECK(map.nth(4)->second == 1);
        }

        {
            sfl::static_flat_multimap<xint, xint, 5, std::less<xint>> map;

            map.insert_exactly_at(map.end(), 10, 1);
            map.insert_exactly_at(map.end(), 20, 1);
            map.insert_exactly_at(map.end(), 30, 1);
            map.insert_exactly_at(map.end(), 40, 1);

            CHECK(map.empty() == false);
            CHECK(map.full() == false);
            CHECK(map.size() == 4);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 1);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);

            const auto res = map.insert_exactly_at(map.nth(4), 45, 1);

            CHECK(res == map.nth(4));
            CHECK(map.empty() == false);
            CHECK(map.full() == true);
            CHECK(map.size() == 5);
            CHECK(map.capacity() == 5);
            CHECK(map.available() == 0);
            CHECK(map.nth(0)->first == 10); CHECK(map.nth(0)->second == 1);
            CHECK(map.nth(1)->first == 20); CHECK(map.nth(1)->second == 1);
            CHECK(map.nth(2)->first == 30); CHECK(map.nth(2)->second == 1);
            CHECK(map.nth(3)->first == 40); CHECK(map.nth(3)->second == 1);
            CHECK(map.nth(4)->first == 45); CHECK(map.nth(4)->second == 1);
        }
    }
}

int main()
{
    test_static_flat_multimap();
}
