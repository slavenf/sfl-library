#ifndef TPARAM_ALLOCATOR
#error Please define macro TPARAM_ALLOCATOR
#endif

using sfl::test::xint;

PRINT("Test emplace(const_iterator, Args&&...)");
{
    // N == 0
    {
        // Insert at the end
        {
            sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec;

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 10);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 1);
                CHECK(vec.capacity() == 1);
                CHECK(*vec.nth(0) == 10);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 20);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 2);
                CHECK(vec.capacity() == 2);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 30);
                PRINT("<");

                CHECK(res == vec.nth(2));
                CHECK(vec.size() == 3);
                CHECK(vec.capacity() == 4);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 40);
                PRINT("<");

                CHECK(res == vec.nth(3));
                CHECK(vec.size() == 4);
                CHECK(vec.capacity() == 4);
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
                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 60);
                PRINT("<");

                CHECK(res == vec.nth(5));
                CHECK(vec.size() == 6);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 70);
                PRINT("<");

                CHECK(res == vec.nth(6));
                CHECK(vec.size() == 7);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 80);
                PRINT("<");

                CHECK(res == vec.nth(7));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 80);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 90);
                PRINT("<");

                CHECK(res == vec.nth(8));
                CHECK(vec.size() == 9);
                CHECK(vec.capacity() == 16);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 80);
                CHECK(*vec.nth(8) == 90);
            }
        }

        // Insert at the begin
        {
            sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec;

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 90);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 1);
                CHECK(vec.capacity() == 1);
                CHECK(*vec.nth(0) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 80);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 2);
                CHECK(vec.capacity() == 2);
                CHECK(*vec.nth(0) == 80);
                CHECK(*vec.nth(1) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 70);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 3);
                CHECK(vec.capacity() == 4);
                CHECK(*vec.nth(0) == 70);
                CHECK(*vec.nth(1) == 80);
                CHECK(*vec.nth(2) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 60);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 4);
                CHECK(vec.capacity() == 4);
                CHECK(*vec.nth(0) == 60);
                CHECK(*vec.nth(1) == 70);
                CHECK(*vec.nth(2) == 80);
                CHECK(*vec.nth(3) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 50);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 50);
                CHECK(*vec.nth(1) == 60);
                CHECK(*vec.nth(2) == 70);
                CHECK(*vec.nth(3) == 80);
                CHECK(*vec.nth(4) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 40);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 6);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 40);
                CHECK(*vec.nth(1) == 50);
                CHECK(*vec.nth(2) == 60);
                CHECK(*vec.nth(3) == 70);
                CHECK(*vec.nth(4) == 80);
                CHECK(*vec.nth(5) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 30);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 7);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 30);
                CHECK(*vec.nth(1) == 40);
                CHECK(*vec.nth(2) == 50);
                CHECK(*vec.nth(3) == 60);
                CHECK(*vec.nth(4) == 70);
                CHECK(*vec.nth(5) == 80);
                CHECK(*vec.nth(6) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 20);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 20);
                CHECK(*vec.nth(1) == 30);
                CHECK(*vec.nth(2) == 40);
                CHECK(*vec.nth(3) == 50);
                CHECK(*vec.nth(4) == 60);
                CHECK(*vec.nth(5) == 70);
                CHECK(*vec.nth(6) == 80);
                CHECK(*vec.nth(7) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 10);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 9);
                CHECK(vec.capacity() == 16);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 80);
                CHECK(*vec.nth(8) == 90);
            }
        }

        // Insert near the end
        {
            sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec;

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 90);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 1);
                CHECK(vec.capacity() == 1);
                CHECK(*vec.nth(0) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 10);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 2);
                CHECK(vec.capacity() == 2);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 20);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 3);
                CHECK(vec.capacity() == 4);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 30);
                PRINT("<");

                CHECK(res == vec.nth(2));
                CHECK(vec.size() == 4);
                CHECK(vec.capacity() == 4);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 40);
                PRINT("<");

                CHECK(res == vec.nth(3));
                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 50);
                PRINT("<");

                CHECK(res == vec.nth(4));
                CHECK(vec.size() == 6);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 60);
                PRINT("<");

                CHECK(res == vec.nth(5));
                CHECK(vec.size() == 7);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 70);
                PRINT("<");

                CHECK(res == vec.nth(6));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 80);
                PRINT("<");

                CHECK(res == vec.nth(7));
                CHECK(vec.size() == 9);
                CHECK(vec.capacity() == 16);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 80);
                CHECK(*vec.nth(8) == 90);
            }
        }

        // Insert near the begin
        {
            sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec;

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 10);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 1);
                CHECK(vec.capacity() == 1);
                CHECK(*vec.nth(0) == 10);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 90);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 2);
                CHECK(vec.capacity() == 2);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 80);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 3);
                CHECK(vec.capacity() == 4);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 80);
                CHECK(*vec.nth(2) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 70);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 4);
                CHECK(vec.capacity() == 4);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 70);
                CHECK(*vec.nth(2) == 80);
                CHECK(*vec.nth(3) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 60);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 60);
                CHECK(*vec.nth(2) == 70);
                CHECK(*vec.nth(3) == 80);
                CHECK(*vec.nth(4) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 50);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 6);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 50);
                CHECK(*vec.nth(2) == 60);
                CHECK(*vec.nth(3) == 70);
                CHECK(*vec.nth(4) == 80);
                CHECK(*vec.nth(5) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 40);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 7);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 40);
                CHECK(*vec.nth(2) == 50);
                CHECK(*vec.nth(3) == 60);
                CHECK(*vec.nth(4) == 70);
                CHECK(*vec.nth(5) == 80);
                CHECK(*vec.nth(6) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 30);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 8);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 30);
                CHECK(*vec.nth(2) == 40);
                CHECK(*vec.nth(3) == 50);
                CHECK(*vec.nth(4) == 60);
                CHECK(*vec.nth(5) == 70);
                CHECK(*vec.nth(6) == 80);
                CHECK(*vec.nth(7) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 20);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 9);
                CHECK(vec.capacity() == 16);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 80);
                CHECK(*vec.nth(8) == 90);
            }
        }
    }

    // N == 3
    {
        // Insert at the end
        {
            sfl::small_vector<xint, 3, TPARAM_ALLOCATOR<xint>> vec;

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 10);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 1);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 10);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 20);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 2);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 30);
                PRINT("<");

                CHECK(res == vec.nth(2));
                CHECK(vec.size() == 3);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 40);
                PRINT("<");

                CHECK(res == vec.nth(3));
                CHECK(vec.size() == 4);
                CHECK(vec.capacity() == 6);
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
                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 6);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 60);
                PRINT("<");

                CHECK(res == vec.nth(5));
                CHECK(vec.size() == 6);
                CHECK(vec.capacity() == 6);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 70);
                PRINT("<");

                CHECK(res == vec.nth(6));
                CHECK(vec.size() == 7);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 80);
                PRINT("<");

                CHECK(res == vec.nth(7));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 80);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 90);
                PRINT("<");

                CHECK(res == vec.nth(8));
                CHECK(vec.size() == 9);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 80);
                CHECK(*vec.nth(8) == 90);
            }
        }

        // Insert at the begin
        {
            sfl::small_vector<xint, 3, TPARAM_ALLOCATOR<xint>> vec;

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 90);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 1);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 80);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 2);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 80);
                CHECK(*vec.nth(1) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 70);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 3);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 70);
                CHECK(*vec.nth(1) == 80);
                CHECK(*vec.nth(2) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 60);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 4);
                CHECK(vec.capacity() == 6);
                CHECK(*vec.nth(0) == 60);
                CHECK(*vec.nth(1) == 70);
                CHECK(*vec.nth(2) == 80);
                CHECK(*vec.nth(3) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 50);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 6);
                CHECK(*vec.nth(0) == 50);
                CHECK(*vec.nth(1) == 60);
                CHECK(*vec.nth(2) == 70);
                CHECK(*vec.nth(3) == 80);
                CHECK(*vec.nth(4) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 40);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 6);
                CHECK(vec.capacity() == 6);
                CHECK(*vec.nth(0) == 40);
                CHECK(*vec.nth(1) == 50);
                CHECK(*vec.nth(2) == 60);
                CHECK(*vec.nth(3) == 70);
                CHECK(*vec.nth(4) == 80);
                CHECK(*vec.nth(5) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 30);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 7);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 30);
                CHECK(*vec.nth(1) == 40);
                CHECK(*vec.nth(2) == 50);
                CHECK(*vec.nth(3) == 60);
                CHECK(*vec.nth(4) == 70);
                CHECK(*vec.nth(5) == 80);
                CHECK(*vec.nth(6) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 20);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 20);
                CHECK(*vec.nth(1) == 30);
                CHECK(*vec.nth(2) == 40);
                CHECK(*vec.nth(3) == 50);
                CHECK(*vec.nth(4) == 60);
                CHECK(*vec.nth(5) == 70);
                CHECK(*vec.nth(6) == 80);
                CHECK(*vec.nth(7) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.begin(), 10);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 9);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 80);
                CHECK(*vec.nth(8) == 90);
            }
        }

        // Insert near the end
        {
            sfl::small_vector<xint, 3, TPARAM_ALLOCATOR<xint>> vec;

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 90);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 1);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 10);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 2);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 20);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 3);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 30);
                PRINT("<");

                CHECK(res == vec.nth(2));
                CHECK(vec.size() == 4);
                CHECK(vec.capacity() == 6);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 40);
                PRINT("<");

                CHECK(res == vec.nth(3));
                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 6);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 50);
                PRINT("<");

                CHECK(res == vec.nth(4));
                CHECK(vec.size() == 6);
                CHECK(vec.capacity() == 6);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 60);
                PRINT("<");

                CHECK(res == vec.nth(5));
                CHECK(vec.size() == 7);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 70);
                PRINT("<");

                CHECK(res == vec.nth(6));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end() - 1, 80);
                PRINT("<");

                CHECK(res == vec.nth(7));
                CHECK(vec.size() == 9);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 80);
                CHECK(*vec.nth(8) == 90);
            }
        }

        // Insert near the begin
        {
            sfl::small_vector<xint, 3, TPARAM_ALLOCATOR<xint>> vec;

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 10);
                PRINT("<");

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 1);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 10);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.end(), 90);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 2);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 80);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 3);
                CHECK(vec.capacity() == 3);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 80);
                CHECK(*vec.nth(2) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 70);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 4);
                CHECK(vec.capacity() == 6);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 70);
                CHECK(*vec.nth(2) == 80);
                CHECK(*vec.nth(3) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 60);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == 6);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 60);
                CHECK(*vec.nth(2) == 70);
                CHECK(*vec.nth(3) == 80);
                CHECK(*vec.nth(4) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 50);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 6);
                CHECK(vec.capacity() == 6);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 50);
                CHECK(*vec.nth(2) == 60);
                CHECK(*vec.nth(3) == 70);
                CHECK(*vec.nth(4) == 80);
                CHECK(*vec.nth(5) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 40);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 7);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 40);
                CHECK(*vec.nth(2) == 50);
                CHECK(*vec.nth(3) == 60);
                CHECK(*vec.nth(4) == 70);
                CHECK(*vec.nth(5) == 80);
                CHECK(*vec.nth(6) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 30);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 30);
                CHECK(*vec.nth(2) == 40);
                CHECK(*vec.nth(3) == 50);
                CHECK(*vec.nth(4) == 60);
                CHECK(*vec.nth(5) == 70);
                CHECK(*vec.nth(6) == 80);
                CHECK(*vec.nth(7) == 90);
            }

            {
                PRINT(">");
                const auto res = vec.emplace(vec.nth(1), 20);
                PRINT("<");

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 9);
                CHECK(vec.capacity() == 12);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 60);
                CHECK(*vec.nth(6) == 70);
                CHECK(*vec.nth(7) == 80);
                CHECK(*vec.nth(8) == 90);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test begin, end, cbegin, cend, rbegin, rend, crbegin, crend, nth, index_of");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

///////////////////////////////////////////////////////////////////////////////

PRINT("Test get_allocator()");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    auto alloc = vec.get_allocator();

    (void)alloc;
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test clear()");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    xint value_10(10);

    auto res = vec.insert(vec.nth(0), value_10);

    CHECK(res == vec.nth(0));
    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 10);
    CHECK(value_10 == 10);
}

PRINT("Test insert(const_iterator, T&&)");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    xint value_10(10);

    auto res = vec.insert(vec.nth(0), std::move(value_10));

    CHECK(res == vec.nth(0));
    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 10);
    CHECK(value_10 == -10);
}

PRINT("Test insert(const_iterator, size_type, const T&)");
{
    // Without storage reallocation
    {
        #define N 100

        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(0), 3, 5);

            CHECK(res == vec.nth(0));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(1), 3, 15);

            CHECK(res == vec.nth(1));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(2), 3, 25);

            CHECK(res == vec.nth(2));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(3), 3, 35);

            CHECK(res == vec.nth(3));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(4), 3, 45);

            CHECK(res == vec.nth(4));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(5), 3, 55);

            CHECK(res == vec.nth(5));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 55);
            CHECK(*vec.nth(6) == 55);
            CHECK(*vec.nth(7) == 55);
        }

        #undef N
    }

    // With storage reallocation
    {
        #define N 5

        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(0), 3, 5);

            CHECK(res == vec.nth(0));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(1), 3, 15);

            CHECK(res == vec.nth(1));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(2), 3, 25);

            CHECK(res == vec.nth(2));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(3), 3, 35);

            CHECK(res == vec.nth(3));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(4), 3, 45);

            CHECK(res == vec.nth(4));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            auto res = vec.insert(vec.nth(5), 3, 55);

            CHECK(res == vec.nth(5));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 55);
            CHECK(*vec.nth(6) == 55);
            CHECK(*vec.nth(7) == 55);
        }

        #undef N
    }
}

PRINT("Test insert(const_iterator, InputIt, InputIt)");
{
    // Input iterator (exactly)
    {
        // Without storage reallocation
        {
            #define N 100

            {
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() == N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() == N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() == N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() == N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() == N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 51);
                CHECK(*vec.nth(6) == 52);
                CHECK(*vec.nth(7) == 53);
            }

            #undef N
        }

        // With storage reallocation
        {
            #define N 5

            {
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() > N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() > N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() > N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() > N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() > N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
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
                CHECK(vec.capacity() > N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 51);
                CHECK(*vec.nth(6) == 52);
                CHECK(*vec.nth(7) == 53);
            }

            #undef N
        }
    }

    // Forward iterator
    {
        // Without storage reallocation
        {
            #define N 100

            {
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({1, 2, 3});

                auto res = vec.insert(vec.nth(0), data.begin(), data.end());

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({11, 12, 13});

                auto res = vec.insert(vec.nth(1), data.begin(), data.end());

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({21, 22, 23});

                auto res = vec.insert(vec.nth(2), data.begin(), data.end());

                CHECK(res == vec.nth(2));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({31, 32, 33});

                auto res = vec.insert(vec.nth(3), data.begin(), data.end());

                CHECK(res == vec.nth(3));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({41, 42, 43});

                auto res = vec.insert(vec.nth(4), data.begin(), data.end());

                CHECK(res == vec.nth(4));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({51, 52, 53});

                auto res = vec.insert(vec.nth(5), data.begin(), data.end());

                CHECK(res == vec.nth(5));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 51);
                CHECK(*vec.nth(6) == 52);
                CHECK(*vec.nth(7) == 53);
            }

            #undef N
        }

        // With storage reallocation
        {
            #define N 5

            {
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({1, 2, 3});

                auto res = vec.insert(vec.nth(0), data.begin(), data.end());

                CHECK(res == vec.nth(0));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() > N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({11, 12, 13});

                auto res = vec.insert(vec.nth(1), data.begin(), data.end());

                CHECK(res == vec.nth(1));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() > N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({21, 22, 23});

                auto res = vec.insert(vec.nth(2), data.begin(), data.end());

                CHECK(res == vec.nth(2));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() > N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({31, 32, 33});

                auto res = vec.insert(vec.nth(3), data.begin(), data.end());

                CHECK(res == vec.nth(3));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() > N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({41, 42, 43});

                auto res = vec.insert(vec.nth(4), data.begin(), data.end());

                CHECK(res == vec.nth(4));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() > N);
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
                sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

                vec.emplace(vec.end(), 10);
                vec.emplace(vec.end(), 20);
                vec.emplace(vec.end(), 30);
                vec.emplace(vec.end(), 40);
                vec.emplace(vec.end(), 50);

                CHECK(vec.size() == 5);
                CHECK(vec.capacity() == N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);

                std::vector<xint> data({51, 52, 53});

                auto res = vec.insert(vec.nth(5), data.begin(), data.end());

                CHECK(res == vec.nth(5));
                CHECK(vec.size() == 8);
                CHECK(vec.capacity() > N);
                CHECK(*vec.nth(0) == 10);
                CHECK(*vec.nth(1) == 20);
                CHECK(*vec.nth(2) == 30);
                CHECK(*vec.nth(3) == 40);
                CHECK(*vec.nth(4) == 50);
                CHECK(*vec.nth(5) == 51);
                CHECK(*vec.nth(6) == 52);
                CHECK(*vec.nth(7) == 53);
            }

            #undef N
        }
    }
}

PRINT("Test insert(const_iterator, std::initializer_list");
{
    // Without storage reallocation
    {
        #define N 100

        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{1, 2, 3};

            auto res = vec.insert(vec.nth(0), ilist);

            CHECK(res == vec.nth(0));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{11, 12, 13};

            auto res = vec.insert(vec.nth(1), ilist);

            CHECK(res == vec.nth(1));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{21, 22, 23};

            auto res = vec.insert(vec.nth(2), ilist);

            CHECK(res == vec.nth(2));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{31, 32, 33};

            auto res = vec.insert(vec.nth(3), ilist);

            CHECK(res == vec.nth(3));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{41, 42, 43};

            auto res = vec.insert(vec.nth(4), ilist);

            CHECK(res == vec.nth(4));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{51, 52, 53};

            auto res = vec.insert(vec.nth(5), ilist);

            CHECK(res == vec.nth(5));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 51);
            CHECK(*vec.nth(6) == 52);
            CHECK(*vec.nth(7) == 53);
        }

        #undef N
    }

    // With storage reallocation
    {
        #define N 5

        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{1, 2, 3};

            auto res = vec.insert(vec.nth(0), ilist);

            CHECK(res == vec.nth(0));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{11, 12, 13};

            auto res = vec.insert(vec.nth(1), ilist);

            CHECK(res == vec.nth(1));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{21, 22, 23};

            auto res = vec.insert(vec.nth(2), ilist);

            CHECK(res == vec.nth(2));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{31, 32, 33};

            auto res = vec.insert(vec.nth(3), ilist);

            CHECK(res == vec.nth(3));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{41, 42, 43};

            auto res = vec.insert(vec.nth(4), ilist);

            CHECK(res == vec.nth(4));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
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
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::initializer_list<xint> ilist{51, 52, 53};

            auto res = vec.insert(vec.nth(5), ilist);

            CHECK(res == vec.nth(5));
            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > N);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 51);
            CHECK(*vec.nth(6) == 52);
            CHECK(*vec.nth(7) == 53);
        }

        #undef N
    }
}

PRINT("Test emplace_back(Args&&...)");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    CHECK(vec.emplace_back(10) == 10);
    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 10);
}

PRINT("Test push_back(const T&)");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    xint value_10(10);

    vec.push_back(value_10);

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 10);
    CHECK(value_10 == 10);
}

PRINT("Test push_back(T&&)");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    xint value_10(10);

    vec.push_back(std::move(value_10));

    CHECK(vec.size() == 1);
    CHECK(*vec.nth(0) == 10);
    CHECK(value_10 == -10);
}

PRINT("Test pop_back()");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        CHECK(vec.erase(vec.nth(0)) == vec.nth(0));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 20);
        CHECK(*vec.nth(1) == 30);
        CHECK(*vec.nth(2) == 40);
        CHECK(*vec.nth(3) == 50);
    }

    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        CHECK(vec.erase(vec.nth(1)) == vec.nth(1));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 30);
        CHECK(*vec.nth(2) == 40);
        CHECK(*vec.nth(3) == 50);
    }

    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        CHECK(vec.erase(vec.nth(2)) == vec.nth(2));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 40);
        CHECK(*vec.nth(3) == 50);
    }

    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        CHECK(vec.erase(vec.nth(3)) == vec.nth(3));
        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 50);
    }

    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        CHECK(vec.erase(vec.nth(4)) == vec.nth(4));
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
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

        CHECK(vec.size() == 0);

        CHECK(vec.erase(vec.nth(0), vec.nth(0)) == vec.nth(0));
    }

    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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
    // n == vec.size()
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        vec.resize(5);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }

    // n < vec.size()
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        vec.resize(2);

        CHECK(vec.size() == 2);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
    }

    // n > vec.size()  &&  n < vec.capacity()  (without storage reallocation)
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        vec.resize(8);

        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(6) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(7) == SFL_TEST_XINT_DEFAULT_VALUE);
    }

    // n > vec.size()  &&  n > vec.capacity()  (with storage reallocation)
    {
        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        vec.resize(8);

        CHECK(vec.size() == 8);
        CHECK(vec.capacity() > 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(6) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(7) == SFL_TEST_XINT_DEFAULT_VALUE);
    }
}

PRINT("Test resize(size_type, const T&)");
{
    // n == vec.size()
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        xint value_99(99);

        vec.resize(5, value_99);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
    }

    // n < vec.size()
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        xint value_99(99);

        vec.resize(2, value_99);

        CHECK(vec.size() == 2);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
    }

    // n > vec.size()  &&  n < vec.capacity()  (without storage reallocation)
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        xint value_99(99);

        vec.resize(8, value_99);

        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == value_99);
        CHECK(*vec.nth(6) == value_99);
        CHECK(*vec.nth(7) == value_99);
    }

    // n > vec.size()  &&  n > vec.capacity()  (with storage reallocation)
    {
        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        xint value_99(99);

        vec.resize(8, value_99);

        CHECK(vec.size() == 8);
        CHECK(vec.capacity() > 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == value_99);
        CHECK(*vec.nth(6) == value_99);
        CHECK(*vec.nth(7) == value_99);
    }
}

PRINT("Test swap(container&)");
{
    // Both containers are using internal storage
    {
        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec1, vec2;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        vec2.emplace(vec2.end(), 40);
        vec2.emplace(vec2.end(), 50);
        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);

        CHECK(vec1.size() == 3);
        CHECK(vec1.capacity() == 5);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        CHECK(vec2.size() == 4);
        CHECK(vec2.capacity() == 5);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);

        ///////////////////////////////////////////////////////////////////////

        vec1.swap(vec2);

        CHECK(vec1.size() == 4);
        CHECK(vec1.capacity() == 5);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);
        CHECK(*vec1.nth(3) == 70);

        CHECK(vec2.size() == 3);
        CHECK(vec2.capacity() == 5);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        vec1.swap(vec2);

        CHECK(vec1.size() == 3);
        CHECK(vec1.capacity() == 5);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        CHECK(vec2.size() == 4);
        CHECK(vec2.capacity() == 5);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
    }

    // One container is using internal storage and another is using external
    {
        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec1, vec2;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        vec2.emplace(vec2.end(), 40);
        vec2.emplace(vec2.end(), 50);
        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);
        vec2.emplace(vec2.end(), 80);
        vec2.emplace(vec2.end(), 90);

        CHECK(vec1.size() == 3);
        CHECK(vec1.capacity() == 5);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        CHECK(vec2.size() == 6);
        CHECK(vec2.capacity() == 10);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
        CHECK(*vec2.nth(4) == 80);
        CHECK(*vec2.nth(5) == 90);

        ///////////////////////////////////////////////////////////////////////

        vec1.swap(vec2);

        CHECK(vec1.size() == 6);
        CHECK(vec1.capacity() == 10);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);
        CHECK(*vec1.nth(3) == 70);
        CHECK(*vec1.nth(4) == 80);
        CHECK(*vec1.nth(5) == 90);

        CHECK(vec2.size() == 3);
        CHECK(vec2.capacity() == 5);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        vec1.swap(vec2);

        CHECK(vec1.size() == 3);
        CHECK(vec1.capacity() == 5);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        CHECK(vec2.size() == 6);
        CHECK(vec2.capacity() == 10);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
        CHECK(*vec2.nth(4) == 80);
        CHECK(*vec2.nth(5) == 90);
    }

    // Both containers are using external storage
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec1, vec2;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        vec2.emplace(vec2.end(), 40);
        vec2.emplace(vec2.end(), 50);
        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);

        CHECK(vec1.size() == 3);
        CHECK(vec1.capacity() == 4);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        CHECK(vec2.size() == 4);
        CHECK(vec2.capacity() == 4);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);

        ///////////////////////////////////////////////////////////////////////

        vec1.swap(vec2);

        CHECK(vec1.size() == 4);
        CHECK(vec1.capacity() == 4);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);
        CHECK(*vec1.nth(3) == 70);

        CHECK(vec2.size() == 3);
        CHECK(vec2.capacity() == 4);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        vec1.swap(vec2);

        CHECK(vec1.size() == 3);
        CHECK(vec1.capacity() == 4);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        CHECK(vec2.size() == 4);
        CHECK(vec2.capacity() == 4);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test at(size_type)");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.at(0) == 10);
    CHECK(vec.at(1) == 20);
    CHECK(vec.at(2) == 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    vec.at(0) = 40;
    vec.at(1) = 50;
    vec.at(2) = 60;

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 40);
    CHECK(*vec.nth(1) == 50);
    CHECK(*vec.nth(2) == 60);

    #if !defined(SFL_NO_EXCEPTIONS)
    bool caught_exception = false;

    try
    {
        vec.at(3) = 1;
    }
    catch (...)
    {
        caught_exception = true;
    }

    CHECK(caught_exception == true);
    #endif

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 40);
    CHECK(*vec.nth(1) == 50);
    CHECK(*vec.nth(2) == 60);
}

PRINT("Test operator[](size_type)");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec[0] == 10);
    CHECK(vec[1] == 20);
    CHECK(vec[2] == 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    vec[0] = 40;
    vec[1] = 50;
    vec[2] = 60;

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 40);
    CHECK(*vec.nth(1) == 50);
    CHECK(*vec.nth(2) == 60);
}

PRINT("Test front() and back()");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.front() == 10);
    CHECK(vec.back()  == 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    vec.front() = 40;
    vec.back()  = 60;

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 40);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 60);
}

PRINT("Test data()");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.size() == 3);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 30);

    auto data = vec.data();
    CHECK(*data == 10); ++data;
    CHECK(*data == 20); ++data;
    CHECK(*data == 30); ++data;
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test reserve(size_type) and shrink_to_fit()");
{
    // N = 0
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);

        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        vec.shrink_to_fit();

        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        vec.reserve(999);

        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == 999);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        vec.shrink_to_fit();

        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }

    // N = 100
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);

        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == 100);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        vec.shrink_to_fit();

        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == 100);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        vec.reserve(999);

        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == 999);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        vec.shrink_to_fit();

        CHECK(vec.size() == 3);
        CHECK(vec.capacity() == 100);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test container()");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    CHECK(vec.size() == 0);
}

PRINT("Test container(const Allocator&)");
{
    TPARAM_ALLOCATOR<xint> alloc;

    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec(alloc);

    CHECK(vec.size() == 0);
}

PRINT("Test container(size_type)");
{
    // N == 0
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec(4);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(1) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(2) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(3) == SFL_TEST_XINT_DEFAULT_VALUE);
    }

    // N != 0 && n < N
    {
        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(4);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(1) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(2) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(3) == SFL_TEST_XINT_DEFAULT_VALUE);
    }

    // N != 0 && n > N
    {
        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(6);

        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(1) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(2) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(3) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(4) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(5) == SFL_TEST_XINT_DEFAULT_VALUE);
    }
}

PRINT("Test container(size_type, const Allocator&)");
{
    // N == 0
    {
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec(4, alloc);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(1) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(2) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(3) == SFL_TEST_XINT_DEFAULT_VALUE);
    }

    // N != 0 && n < N
    {
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(4, alloc);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(1) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(2) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(3) == SFL_TEST_XINT_DEFAULT_VALUE);
    }

    // N != 0 && n > N
    {
        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(6, alloc);

        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(1) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(2) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(3) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(4) == SFL_TEST_XINT_DEFAULT_VALUE);
        CHECK(*vec.nth(5) == SFL_TEST_XINT_DEFAULT_VALUE);
    }
}

PRINT("Test container(size_type, const T&)");
{
    // N == 0
    {
        xint value_99(99);

        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec(4, value_99);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == value_99);
        CHECK(*vec.nth(1) == value_99);
        CHECK(*vec.nth(2) == value_99);
        CHECK(*vec.nth(3) == value_99);
    }

    // N != 0 && n < N
    {
        xint value_99(99);

        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(4, value_99);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == value_99);
        CHECK(*vec.nth(1) == value_99);
        CHECK(*vec.nth(2) == value_99);
        CHECK(*vec.nth(3) == value_99);
    }

    // N != 0 && n > N
    {
        xint value_99(99);

        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(6, value_99);

        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == value_99);
        CHECK(*vec.nth(1) == value_99);
        CHECK(*vec.nth(2) == value_99);
        CHECK(*vec.nth(3) == value_99);
        CHECK(*vec.nth(4) == value_99);
        CHECK(*vec.nth(5) == value_99);
    }
}

PRINT("Test container(size_type, const T&, const Allocator&)");
{
    // N == 0
    {
        TPARAM_ALLOCATOR<xint> alloc;

        xint value_99(99);

        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec(4, value_99, alloc);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == value_99);
        CHECK(*vec.nth(1) == value_99);
        CHECK(*vec.nth(2) == value_99);
        CHECK(*vec.nth(3) == value_99);
    }

    // N != 0 && n < N
    {
        TPARAM_ALLOCATOR<xint> alloc;

        xint value_99(99);

        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(4, value_99, alloc);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == value_99);
        CHECK(*vec.nth(1) == value_99);
        CHECK(*vec.nth(2) == value_99);
        CHECK(*vec.nth(3) == value_99);
    }

    // N != 0 && n > N
    {
        TPARAM_ALLOCATOR<xint> alloc;

        xint value_99(99);

        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(6, value_99, alloc);

        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == value_99);
        CHECK(*vec.nth(1) == value_99);
        CHECK(*vec.nth(2) == value_99);
        CHECK(*vec.nth(3) == value_99);
        CHECK(*vec.nth(4) == value_99);
        CHECK(*vec.nth(5) == value_99);
    }
}

PRINT("Test container(InputIt, InputIt)");
{
    // Input iterator (exactly)
    {
        // N == 0
        {
            std::istringstream iss("10 20 30 40");

            sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec
            (
                (std::istream_iterator<int>(iss)),
                (std::istream_iterator<int>())
            );

            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }

        // N != 0 && n < N
        {
            std::istringstream iss("10 20 30 40");

            sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec
            (
                (std::istream_iterator<int>(iss)),
                (std::istream_iterator<int>())
            );

            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }

        // N != 0 && n > N
        {
            std::istringstream iss("10 20 30 40 50 60");

            sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec
            (
                (std::istream_iterator<int>(iss)),
                (std::istream_iterator<int>())
            );

            CHECK(vec.size() == 6);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 60);
        }
    }

    // Forward iterator
    {
        // N == 0
        {
            std::vector<xint> data({10, 20, 30, 40});

            sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec(data.begin(), data.end());

            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }

        // N != 0 && n < N
        {
            std::vector<xint> data({10, 20, 30, 40});

            sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(data.begin(), data.end());

            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }

        // N != 0 && n > N
        {
            std::vector<xint> data({10, 20, 30, 40, 50, 60});

            sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(data.begin(), data.end());

            CHECK(vec.size() == 6);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 60);
        }
    }
}

PRINT("Test container(InputIt, InputIt, const Allocator&)");
{
    // Input iterator (exactly)
    {
        // N == 0
        {
            std::istringstream iss("10 20 30 40");

            TPARAM_ALLOCATOR<xint> alloc;

            sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec
            (
                (std::istream_iterator<int>(iss)),
                (std::istream_iterator<int>()),
                alloc
            );

            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }

        // N != 0 && n < N
        {
            std::istringstream iss("10 20 30 40");

            TPARAM_ALLOCATOR<xint> alloc;

            sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec
            (
                (std::istream_iterator<int>(iss)),
                (std::istream_iterator<int>()),
                alloc
            );

            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }

        // N != 0 && n > N
        {
            std::istringstream iss("10 20 30 40 50 60");

            TPARAM_ALLOCATOR<xint> alloc;

            sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec
            (
                (std::istream_iterator<int>(iss)),
                (std::istream_iterator<int>()),
                alloc
            );

            CHECK(vec.size() == 6);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 60);
        }
    }

    // Forward iterator
    {
        // N == 0
        {
            std::vector<xint> data({10, 20, 30, 40});

            TPARAM_ALLOCATOR<xint> alloc;

            sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec(data.begin(), data.end(), alloc);

            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }

        // N != 0 && n < N
        {
            std::vector<xint> data({10, 20, 30, 40});

            TPARAM_ALLOCATOR<xint> alloc;

            sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(data.begin(), data.end(), alloc);

            CHECK(vec.size() == 4);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
        }

        // N != 0 && n > N
        {
            std::vector<xint> data({10, 20, 30, 40, 50, 60});

            TPARAM_ALLOCATOR<xint> alloc;

            sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(data.begin(), data.end(), alloc);

            CHECK(vec.size() == 6);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);
            CHECK(*vec.nth(5) == 60);
        }
    }
}

PRINT("Test container(std::initializer_list)");
{
    // N == 0
    {
        std::initializer_list<xint> ilist{10, 20, 30, 40};

        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec(ilist);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }

    // N != 0 && n < N
    {
        std::initializer_list<xint> ilist{10, 20, 30, 40};

        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(ilist);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }

    // N != 0 && n > N
    {
        std::initializer_list<xint> ilist{10, 20, 30, 40, 50, 60};

        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(ilist);

        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
    }
}

PRINT("Test container(std::initializer_list, const Allocator&)");
{
    // N == 0
    {
        std::initializer_list<xint> ilist{10, 20, 30, 40};

        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec(ilist, alloc);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }

    // N != 0 && n < N
    {
        std::initializer_list<xint> ilist{10, 20, 30, 40};

        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(ilist, alloc);

        CHECK(vec.size() == 4);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
    }

    // N != 0 && n > N
    {
        std::initializer_list<xint> ilist{10, 20, 30, 40, 50, 60};

        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec(ilist, alloc);

        CHECK(vec.size() == 6);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);
        CHECK(*vec.nth(5) == 60);
    }
}

PRINT("Test container(const container&)");
{
    // N == 0
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec1;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec2(vec1);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);
    }

    // N == 100
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec1;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec2(vec1);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);
    }
}

PRINT("Test container(const container&, const Allocator&)");
{
    // N == 0
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec1;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec2(vec1, alloc);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);
    }

    // N == 100
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec1;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec2(vec1, alloc);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);
    }
}

PRINT("Test container(container&&)");
{
    // N == 0
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec1;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec2(std::move(vec1));

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        if (vec1.size() == 3)
        {
            // Elements were moved one-by-one
            CHECK(*vec1.nth(0) == -10);
            CHECK(*vec1.nth(1) == -20);
            CHECK(*vec1.nth(2) == -30);
        }
        else
        {
            // Storage was moved
            CHECK(vec1.size() == 0);
        }
    }

    // N == 100
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec1;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec2(std::move(vec1));

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);

        if (vec1.size() == 3)
        {
            // Elements were moved one-by-one
            CHECK(*vec1.nth(0) == -10);
            CHECK(*vec1.nth(1) == -20);
            CHECK(*vec1.nth(2) == -30);
        }
        else
        {
            // Storage was moved
            CHECK(vec1.size() == 0);
        }
    }
}

PRINT("Test container(container&&, const Allocator&)");
{
    // N == 0
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec1;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec2(std::move(vec1), alloc);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        if (vec1.size() == 3)
        {
            // Elements were moved one-by-one
            CHECK(*vec1.nth(0) == -10);
            CHECK(*vec1.nth(1) == -20);
            CHECK(*vec1.nth(2) == -30);
        }
        else
        {
            // Storage was moved
            CHECK(vec1.size() == 0);
        }
    }

    // N == 100
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec1;

        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        TPARAM_ALLOCATOR<xint> alloc;

        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec2(std::move(vec1), alloc);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 10);
        CHECK(*vec2.nth(1) == 20);
        CHECK(*vec2.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        if (vec1.size() == 3)
        {
            // Elements were moved one-by-one
            CHECK(*vec1.nth(0) == -10);
            CHECK(*vec1.nth(1) == -20);
            CHECK(*vec1.nth(2) == -30);
        }
        else
        {
            // Storage was moved
            CHECK(vec1.size() == 0);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test operator=(const container&)");
{
    // Permutation 1/8
    #define CONDITION vec1.size() < vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec1, vec2;

        vec1.reserve(3);
        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        vec2.reserve(5);
        vec2.emplace(vec2.end(), 40);
        vec2.emplace(vec2.end(), 50);
        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);
        vec2.emplace(vec2.end(), 80);

        CHECK(vec2.size() == 5);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
        CHECK(*vec2.nth(4) == 80);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = vec2;

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);
        CHECK(*vec1.nth(3) == 70);
        CHECK(*vec1.nth(4) == 80);

        CHECK(vec2.size() == 5);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
        CHECK(*vec2.nth(4) == 80);
    }
    #undef CONDITION

    // Permutation 2/8
    #define CONDITION vec1.size() < vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec1, vec2;

        vec1.reserve(100);
        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);

        vec2.reserve(5);
        vec2.emplace(vec2.end(), 40);
        vec2.emplace(vec2.end(), 50);
        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);
        vec2.emplace(vec2.end(), 80);

        CHECK(vec2.size() == 5);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
        CHECK(*vec2.nth(4) == 80);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = vec2;

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 40);
        CHECK(*vec1.nth(1) == 50);
        CHECK(*vec1.nth(2) == 60);
        CHECK(*vec1.nth(3) == 70);
        CHECK(*vec1.nth(4) == 80);

        CHECK(vec2.size() == 5);
        CHECK(*vec2.nth(0) == 40);
        CHECK(*vec2.nth(1) == 50);
        CHECK(*vec2.nth(2) == 60);
        CHECK(*vec2.nth(3) == 70);
        CHECK(*vec2.nth(4) == 80);
    }
    #undef CONDITION

    // Permutation 3/8
    #define CONDITION vec1.size() < vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
    {
        // Impossible condition
    }
    #undef CONDITION

    // Permutation 4/8
    #define CONDITION vec1.size() < vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
    {
        // Impossible condition
    }
    #undef CONDITION

    // Permutation 5/8
    #define CONDITION vec1.size() > vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec1, vec2;

        vec1.reserve(5);
        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);
        vec1.emplace(vec1.end(), 40);
        vec1.emplace(vec1.end(), 50);

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);
        CHECK(*vec1.nth(3) == 40);
        CHECK(*vec1.nth(4) == 50);

        vec2.reserve(100);
        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);
        vec2.emplace(vec2.end(), 80);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 60);
        CHECK(*vec2.nth(1) == 70);
        CHECK(*vec2.nth(2) == 80);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = vec2;

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 60);
        CHECK(*vec1.nth(1) == 70);
        CHECK(*vec1.nth(2) == 80);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 60);
        CHECK(*vec2.nth(1) == 70);
        CHECK(*vec2.nth(2) == 80);
    }
    #undef CONDITION

    // Permutation 6/8
    #define CONDITION vec1.size() > vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec1, vec2;

        vec1.reserve(100);
        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);
        vec1.emplace(vec1.end(), 40);
        vec1.emplace(vec1.end(), 50);

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);
        CHECK(*vec1.nth(3) == 40);
        CHECK(*vec1.nth(4) == 50);

        vec2.reserve(10);
        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);
        vec2.emplace(vec2.end(), 80);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 60);
        CHECK(*vec2.nth(1) == 70);
        CHECK(*vec2.nth(2) == 80);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = vec2;

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 60);
        CHECK(*vec1.nth(1) == 70);
        CHECK(*vec1.nth(2) == 80);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 60);
        CHECK(*vec2.nth(1) == 70);
        CHECK(*vec2.nth(2) == 80);
    }
    #undef CONDITION

    // Permutation 7/8
    #define CONDITION vec1.size() > vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
    {
        // Impossible condition
    }
    #undef CONDITION

    // Permutation 8/8
    #define CONDITION vec1.size() > vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
    {
        sfl::small_vector<xint, 0, TPARAM_ALLOCATOR<xint>> vec1, vec2;

        vec1.reserve(100);
        vec1.emplace(vec1.end(), 10);
        vec1.emplace(vec1.end(), 20);
        vec1.emplace(vec1.end(), 30);
        vec1.emplace(vec1.end(), 40);
        vec1.emplace(vec1.end(), 50);

        CHECK(vec1.size() == 5);
        CHECK(*vec1.nth(0) == 10);
        CHECK(*vec1.nth(1) == 20);
        CHECK(*vec1.nth(2) == 30);
        CHECK(*vec1.nth(3) == 40);
        CHECK(*vec1.nth(4) == 50);

        vec2.reserve(3);
        vec2.emplace(vec2.end(), 60);
        vec2.emplace(vec2.end(), 70);
        vec2.emplace(vec2.end(), 80);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 60);
        CHECK(*vec2.nth(1) == 70);
        CHECK(*vec2.nth(2) == 80);

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec1 = vec2;

        CHECK(vec1.size() == 3);
        CHECK(*vec1.nth(0) == 60);
        CHECK(*vec1.nth(1) == 70);
        CHECK(*vec1.nth(2) == 80);

        CHECK(vec2.size() == 3);
        CHECK(*vec2.nth(0) == 60);
        CHECK(*vec2.nth(1) == 70);
        CHECK(*vec2.nth(2) == 80);
    }
    #undef CONDITION
}

PRINT("Test operator=(container&&)");
{
    #define N 0
    {
        // Permutation 1/8
        #define CONDITION vec2.capacity() != N  &&  vec1.size() < vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec1, vec2;

            vec1.reserve(3);
            vec1.emplace(vec1.end(), 10);
            vec1.emplace(vec1.end(), 20);
            vec1.emplace(vec1.end(), 30);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);

            vec2.reserve(5);
            vec2.emplace(vec2.end(), 40);
            vec2.emplace(vec2.end(), 50);
            vec2.emplace(vec2.end(), 60);
            vec2.emplace(vec2.end(), 70);
            vec2.emplace(vec2.end(), 80);

            CHECK(vec2.size() == 5);
            CHECK(*vec2.nth(0) == 40);
            CHECK(*vec2.nth(1) == 50);
            CHECK(*vec2.nth(2) == 60);
            CHECK(*vec2.nth(3) == 70);
            CHECK(*vec2.nth(4) == 80);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            vec1 = std::move(vec2);

            CHECK(vec1.size() == 5);
            CHECK(*vec1.nth(0) == 40);
            CHECK(*vec1.nth(1) == 50);
            CHECK(*vec1.nth(2) == 60);
            CHECK(*vec1.nth(3) == 70);
            CHECK(*vec1.nth(4) == 80);

            if (vec2.size() == 5)
            {
                // Elements were moved one-by-one
                CHECK(*vec2.nth(0) == -40);
                CHECK(*vec2.nth(1) == -50);
                CHECK(*vec2.nth(2) == -60);
                CHECK(*vec2.nth(3) == -70);
                CHECK(*vec2.nth(4) == -80);
            }
            else
            {
                // Storage was moved
                CHECK(vec2.size() == 0);
            }
        }
        #undef CONDITION

        // Permutation 2/8
        #define CONDITION vec2.capacity() != N  &&  vec1.size() < vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec1, vec2;

            vec1.reserve(100);
            vec1.emplace(vec1.end(), 10);
            vec1.emplace(vec1.end(), 20);
            vec1.emplace(vec1.end(), 30);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);

            vec2.reserve(5);
            vec2.emplace(vec2.end(), 40);
            vec2.emplace(vec2.end(), 50);
            vec2.emplace(vec2.end(), 60);
            vec2.emplace(vec2.end(), 70);
            vec2.emplace(vec2.end(), 80);

            CHECK(vec2.size() == 5);
            CHECK(*vec2.nth(0) == 40);
            CHECK(*vec2.nth(1) == 50);
            CHECK(*vec2.nth(2) == 60);
            CHECK(*vec2.nth(3) == 70);
            CHECK(*vec2.nth(4) == 80);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            vec1 = std::move(vec2);

            CHECK(vec1.size() == 5);
            CHECK(*vec1.nth(0) == 40);
            CHECK(*vec1.nth(1) == 50);
            CHECK(*vec1.nth(2) == 60);
            CHECK(*vec1.nth(3) == 70);
            CHECK(*vec1.nth(4) == 80);

            if (vec2.size() == 5)
            {
                // Elements were moved one-by-one
                CHECK(*vec2.nth(0) == -40);
                CHECK(*vec2.nth(1) == -50);
                CHECK(*vec2.nth(2) == -60);
                CHECK(*vec2.nth(3) == -70);
                CHECK(*vec2.nth(4) == -80);
            }
            else
            {
                // Storage was moved
                CHECK(vec2.size() == 0);
            }
        }
        #undef CONDITION

        // Permutation 3/8
        #define CONDITION vec2.capacity() != N  &&  vec1.size() < vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
        {
            // Impossible condition
        }
        #undef CONDITION

        // Permutation 4/8
        #define CONDITION vec2.capacity() != N  &&  vec1.size() < vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
        {
            // Impossible condition
        }
        #undef CONDITION

        // Permutation 5/8
        #define CONDITION vec2.capacity() != N  &&  vec1.size() > vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec1, vec2;

            vec1.reserve(5);
            vec1.emplace(vec1.end(), 10);
            vec1.emplace(vec1.end(), 20);
            vec1.emplace(vec1.end(), 30);
            vec1.emplace(vec1.end(), 40);
            vec1.emplace(vec1.end(), 50);

            CHECK(vec1.size() == 5);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);
            CHECK(*vec1.nth(3) == 40);
            CHECK(*vec1.nth(4) == 50);

            vec2.reserve(100);
            vec2.emplace(vec2.end(), 60);
            vec2.emplace(vec2.end(), 70);
            vec2.emplace(vec2.end(), 80);

            CHECK(vec2.size() == 3);
            CHECK(*vec2.nth(0) == 60);
            CHECK(*vec2.nth(1) == 70);
            CHECK(*vec2.nth(2) == 80);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            vec1 = std::move(vec2);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 60);
            CHECK(*vec1.nth(1) == 70);
            CHECK(*vec1.nth(2) == 80);

            if (vec2.size() == 3)
            {
                // Elements were moved one-by-one
                CHECK(*vec2.nth(0) == -60);
                CHECK(*vec2.nth(1) == -70);
                CHECK(*vec2.nth(2) == -80);
            }
            else
            {
                // Storage was moved
                CHECK(vec2.size() == 0);
            }
        }
        #undef CONDITION

        // Permutation 6/8
        #define CONDITION vec2.capacity() != N  &&  vec1.size() > vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec1, vec2;

            vec1.reserve(100);
            vec1.emplace(vec1.end(), 10);
            vec1.emplace(vec1.end(), 20);
            vec1.emplace(vec1.end(), 30);
            vec1.emplace(vec1.end(), 40);
            vec1.emplace(vec1.end(), 50);

            CHECK(vec1.size() == 5);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);
            CHECK(*vec1.nth(3) == 40);
            CHECK(*vec1.nth(4) == 50);

            vec2.reserve(10);
            vec2.emplace(vec2.end(), 60);
            vec2.emplace(vec2.end(), 70);
            vec2.emplace(vec2.end(), 80);

            CHECK(vec2.size() == 3);
            CHECK(*vec2.nth(0) == 60);
            CHECK(*vec2.nth(1) == 70);
            CHECK(*vec2.nth(2) == 80);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            vec1 = std::move(vec2);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 60);
            CHECK(*vec1.nth(1) == 70);
            CHECK(*vec1.nth(2) == 80);

            if (vec2.size() == 3)
            {
                // Elements were moved one-by-one
                CHECK(*vec2.nth(0) == -60);
                CHECK(*vec2.nth(1) == -70);
                CHECK(*vec2.nth(2) == -80);
            }
            else
            {
                // Storage was moved
                CHECK(vec2.size() == 0);
            }
        }
        #undef CONDITION

        // Permutation 7/8
        #define CONDITION vec2.capacity() != N  &&  vec1.size() > vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
        {
            // Impossible condition
        }
        #undef CONDITION

        // Permutation 8/8
        #define CONDITION vec2.capacity() != N  &&  vec1.size() > vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec1, vec2;

            vec1.reserve(5);
            vec1.emplace(vec1.end(), 10);
            vec1.emplace(vec1.end(), 20);
            vec1.emplace(vec1.end(), 30);
            vec1.emplace(vec1.end(), 40);
            vec1.emplace(vec1.end(), 50);

            CHECK(vec1.size() == 5);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);
            CHECK(*vec1.nth(3) == 40);
            CHECK(*vec1.nth(4) == 50);

            vec2.reserve(3);
            vec2.emplace(vec2.end(), 60);
            vec2.emplace(vec2.end(), 70);
            vec2.emplace(vec2.end(), 80);

            CHECK(vec2.size() == 3);
            CHECK(*vec2.nth(0) == 60);
            CHECK(*vec2.nth(1) == 70);
            CHECK(*vec2.nth(2) == 80);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            vec1 = std::move(vec2);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 60);
            CHECK(*vec1.nth(1) == 70);
            CHECK(*vec1.nth(2) == 80);

            if (vec2.size() == 3)
            {
                // Elements were moved one-by-one
                CHECK(*vec2.nth(0) == -60);
                CHECK(*vec2.nth(1) == -70);
                CHECK(*vec2.nth(2) == -80);
            }
            else
            {
                // Storage was moved
                CHECK(vec2.size() == 0);
            }
        }
        #undef CONDITION
    }
    #undef N

    #define N 5
    {
        // Permutation 1/8
        #define CONDITION vec2.capacity() == N  &&  vec1.size() < vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
        {
            // Impossible condition
        }
        #undef CONDITION

        // Permutation 2/8
        #define CONDITION vec2.capacity() == N  &&  vec1.size() < vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec1, vec2;

            vec1.reserve(100);
            vec1.emplace(vec1.end(), 10);
            vec1.emplace(vec1.end(), 20);
            vec1.emplace(vec1.end(), 30);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);

            vec2.emplace(vec2.end(), 40);
            vec2.emplace(vec2.end(), 50);
            vec2.emplace(vec2.end(), 60);
            vec2.emplace(vec2.end(), 70);
            vec2.emplace(vec2.end(), 80);

            CHECK(vec2.size() == 5);
            CHECK(*vec2.nth(0) == 40);
            CHECK(*vec2.nth(1) == 50);
            CHECK(*vec2.nth(2) == 60);
            CHECK(*vec2.nth(3) == 70);
            CHECK(*vec2.nth(4) == 80);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            vec1 = std::move(vec2);

            CHECK(vec1.size() == 5);
            CHECK(*vec1.nth(0) == 40);
            CHECK(*vec1.nth(1) == 50);
            CHECK(*vec1.nth(2) == 60);
            CHECK(*vec1.nth(3) == 70);
            CHECK(*vec1.nth(4) == 80);

            if (vec2.size() == 5)
            {
                // Elements were moved one-by-one
                CHECK(*vec2.nth(0) == -40);
                CHECK(*vec2.nth(1) == -50);
                CHECK(*vec2.nth(2) == -60);
                CHECK(*vec2.nth(3) == -70);
                CHECK(*vec2.nth(4) == -80);
            }
            else
            {
                // Storage was moved
                CHECK(vec2.size() == 0);
            }
        }
        #undef CONDITION

        // Permutation 3/8
        #define CONDITION vec2.capacity() == N  &&  vec1.size() < vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
        {
            // Impossible condition
        }
        #undef CONDITION

        // Permutation 4/8
        #define CONDITION vec2.capacity() == N  &&  vec1.size() < vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
        {
            // Impossible condition
        }
        #undef CONDITION

        // Permutation 5/8
        #define CONDITION vec2.capacity() == N  &&  vec1.size() > vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
        {
            // Impossible condition
        }
        #undef CONDITION

        // Permutation 6/8
        #define CONDITION vec2.capacity() == N  &&  vec1.size() > vec2.size()  &&  vec1.size() < vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec1, vec2;

            vec1.reserve(100);
            vec1.emplace(vec1.end(), 10);
            vec1.emplace(vec1.end(), 20);
            vec1.emplace(vec1.end(), 30);
            vec1.emplace(vec1.end(), 40);

            CHECK(vec1.size() == 4);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);
            CHECK(*vec1.nth(3) == 40);

            vec2.emplace(vec2.end(), 60);
            vec2.emplace(vec2.end(), 70);
            vec2.emplace(vec2.end(), 80);

            CHECK(vec2.size() == 3);
            CHECK(*vec2.nth(0) == 60);
            CHECK(*vec2.nth(1) == 70);
            CHECK(*vec2.nth(2) == 80);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            vec1 = std::move(vec2);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 60);
            CHECK(*vec1.nth(1) == 70);
            CHECK(*vec1.nth(2) == 80);

            if (vec2.size() == 3)
            {
                // Elements were moved one-by-one
                CHECK(*vec2.nth(0) == -60);
                CHECK(*vec2.nth(1) == -70);
                CHECK(*vec2.nth(2) == -80);
            }
            else
            {
                // Storage was moved
                CHECK(vec2.size() == 0);
            }
        }
        #undef CONDITION

        // Permutation 7/8
        #define CONDITION vec2.capacity() == N  &&  vec1.size() > vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() < vec2.capacity()
        {
            // Impossible condition
        }
        #undef CONDITION

        // Permutation 8/8
        #define CONDITION vec2.capacity() == N  &&  vec1.size() > vec2.size()  &&  vec1.size() > vec2.capacity()  &&  vec1.capacity() > vec2.capacity()
        {
            sfl::small_vector<xint, N, TPARAM_ALLOCATOR<xint>> vec1, vec2;

            vec1.reserve(100);
            vec1.emplace(vec1.end(), 10);
            vec1.emplace(vec1.end(), 20);
            vec1.emplace(vec1.end(), 30);
            vec1.emplace(vec1.end(), 40);
            vec1.emplace(vec1.end(), 50);
            vec1.emplace(vec1.end(), 60);

            CHECK(vec1.size() == 6);
            CHECK(*vec1.nth(0) == 10);
            CHECK(*vec1.nth(1) == 20);
            CHECK(*vec1.nth(2) == 30);
            CHECK(*vec1.nth(3) == 40);
            CHECK(*vec1.nth(4) == 50);
            CHECK(*vec1.nth(5) == 60);

            vec2.emplace(vec2.end(), 60);
            vec2.emplace(vec2.end(), 70);
            vec2.emplace(vec2.end(), 80);

            CHECK(vec2.size() == 3);
            CHECK(*vec2.nth(0) == 60);
            CHECK(*vec2.nth(1) == 70);
            CHECK(*vec2.nth(2) == 80);

            ///////////////////////////////////////////////////////////////////////

            CHECK(CONDITION);

            vec1 = std::move(vec2);

            CHECK(vec1.size() == 3);
            CHECK(*vec1.nth(0) == 60);
            CHECK(*vec1.nth(1) == 70);
            CHECK(*vec1.nth(2) == 80);

            if (vec2.size() == 3)
            {
                // Elements were moved one-by-one
                CHECK(*vec2.nth(0) == -60);
                CHECK(*vec2.nth(1) == -70);
                CHECK(*vec2.nth(2) == -80);
            }
            else
            {
                // Storage was moved
                CHECK(vec2.size() == 0);
            }
        }
        #undef CONDITION
    }
    #undef N
}

PRINT("Test operator=(std::initializer_list)");
{
    // Permutation 1/4
    #define CONDITION ilist.size() < vec.size() && ilist.size() < vec.capacity()
    {
        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec;

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

        ///////////////////////////////////////////////////////////////////////

        std::initializer_list<xint> ilist
        {
            60,
            70,
            80
        };

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec = ilist;

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 60);
        CHECK(*vec.nth(1) == 70);
        CHECK(*vec.nth(2) == 80);
    }
    #undef CONDITION

    // Permutation 2/4
    #define CONDITION ilist.size() < vec.size() && ilist.size() > vec.capacity()
    {
        // Impossible condition
    }
    #undef CONDITION

    // Permutation 3/4
    #define CONDITION ilist.size() > vec.size() && ilist.size() < vec.capacity()
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        std::initializer_list<xint> ilist
        {
            40,
            50,
            60,
            70,
            80
        };

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec = ilist;

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 40);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
        CHECK(*vec.nth(4) == 80);
    }
    #undef CONDITION

    // Permutation 4/4
    #define CONDITION ilist.size() > vec.size() && ilist.size() > vec.capacity()
    {
        sfl::small_vector<xint, 3, TPARAM_ALLOCATOR<xint>> vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);

        CHECK(vec.size() == 3);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);

        ///////////////////////////////////////////////////////////////////////

        std::initializer_list<xint> ilist
        {
            40,
            50,
            60,
            70,
            80
        };

        ///////////////////////////////////////////////////////////////////////

        CHECK(CONDITION);

        vec = ilist;

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 40);
        CHECK(*vec.nth(1) == 50);
        CHECK(*vec.nth(2) == 60);
        CHECK(*vec.nth(3) == 70);
        CHECK(*vec.nth(4) == 80);
    }
    #undef CONDITION
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test assign(size_type, const T&)");
{
    // n == vec.size()
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        xint value_99(99);

        vec.assign(5, value_99);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == value_99);
        CHECK(*vec.nth(1) == value_99);
        CHECK(*vec.nth(2) == value_99);
        CHECK(*vec.nth(3) == value_99);
        CHECK(*vec.nth(4) == value_99);
    }

    // n < vec.size()
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        xint value_99(99);

        vec.assign(2, value_99);

        CHECK(vec.size() == 2);
        CHECK(*vec.nth(0) == value_99);
        CHECK(*vec.nth(1) == value_99);
    }

    // n > vec.size()  &&  n < vec.capacity()  (without storage reallocation)
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        xint value_99(99);

        vec.assign(8, value_99);

        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == value_99);
        CHECK(*vec.nth(1) == value_99);
        CHECK(*vec.nth(2) == value_99);
        CHECK(*vec.nth(3) == value_99);
        CHECK(*vec.nth(4) == value_99);
        CHECK(*vec.nth(5) == value_99);
        CHECK(*vec.nth(6) == value_99);
        CHECK(*vec.nth(7) == value_99);
    }

    // n > vec.size()  &&  n > vec.capacity()  (with storage reallocation)
    {
        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        xint value_99(99);

        vec.assign(8, value_99);

        CHECK(vec.size() == 8);
        CHECK(vec.capacity() > 5);
        CHECK(*vec.nth(0) == value_99);
        CHECK(*vec.nth(1) == value_99);
        CHECK(*vec.nth(2) == value_99);
        CHECK(*vec.nth(3) == value_99);
        CHECK(*vec.nth(4) == value_99);
        CHECK(*vec.nth(5) == value_99);
        CHECK(*vec.nth(6) == value_99);
        CHECK(*vec.nth(7) == value_99);
    }
}

PRINT("Test assign(InputIt, InputIt)");
{
    // Input iterator (exactly)
    {
        // n == vec.size()
        {
            sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

            std::istringstream iss("11 21 31 41 51");

            vec.assign
            (
                (std::istream_iterator<int>(iss)),
                (std::istream_iterator<int>())
            );

            CHECK(vec.size() == 5);
            CHECK(*vec.nth(0) == 11);
            CHECK(*vec.nth(1) == 21);
            CHECK(*vec.nth(2) == 31);
            CHECK(*vec.nth(3) == 41);
            CHECK(*vec.nth(4) == 51);
        }

        // n < vec.size()
        {
            sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

            std::istringstream iss("11 21");

            vec.assign
            (
                (std::istream_iterator<int>(iss)),
                (std::istream_iterator<int>())
            );

            CHECK(vec.size() == 2);
            CHECK(*vec.nth(0) == 11);
            CHECK(*vec.nth(1) == 21);
        }

        // n > vec.size()  &&  n < vec.capacity()  (without storage reallocation)
        {
            sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

            std::istringstream iss("11 21 31 41 51 61 71 81");

            vec.assign
            (
                (std::istream_iterator<int>(iss)),
                (std::istream_iterator<int>())
            );

            CHECK(vec.size() == 8);
            CHECK(*vec.nth(0) == 11);
            CHECK(*vec.nth(1) == 21);
            CHECK(*vec.nth(2) == 31);
            CHECK(*vec.nth(3) == 41);
            CHECK(*vec.nth(4) == 51);
            CHECK(*vec.nth(5) == 61);
            CHECK(*vec.nth(6) == 71);
            CHECK(*vec.nth(7) == 81);
        }

        // n > vec.size()  &&  n > vec.capacity()  (with storage reallocation)
        {
            sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 5);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::istringstream iss("11 21 31 41 51 61 71 81");

            vec.assign
            (
                (std::istream_iterator<int>(iss)),
                (std::istream_iterator<int>())
            );

            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > 5);
            CHECK(*vec.nth(0) == 11);
            CHECK(*vec.nth(1) == 21);
            CHECK(*vec.nth(2) == 31);
            CHECK(*vec.nth(3) == 41);
            CHECK(*vec.nth(4) == 51);
            CHECK(*vec.nth(5) == 61);
            CHECK(*vec.nth(6) == 71);
            CHECK(*vec.nth(7) == 81);
        }
    }

    // Forward iterator
    {
        // n == vec.size()
        {
            sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

            std::vector<xint> data({11, 21, 31, 41, 51});

            vec.assign(data.begin(), data.end());

            CHECK(vec.size() == 5);
            CHECK(*vec.nth(0) == 11);
            CHECK(*vec.nth(1) == 21);
            CHECK(*vec.nth(2) == 31);
            CHECK(*vec.nth(3) == 41);
            CHECK(*vec.nth(4) == 51);
        }

        // n < vec.size()
        {
            sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

            std::vector<xint> data({11, 21});

            vec.assign(data.begin(), data.end());

            CHECK(vec.size() == 2);
            CHECK(*vec.nth(0) == 11);
            CHECK(*vec.nth(1) == 21);
        }

        // n > vec.size()  &&  n < vec.capacity()  (without storage reallocation)
        {
            sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

            std::vector<xint> data({11, 21, 31, 41, 51, 61, 71, 81});

            vec.assign(data.begin(), data.end());

            CHECK(vec.size() == 8);
            CHECK(*vec.nth(0) == 11);
            CHECK(*vec.nth(1) == 21);
            CHECK(*vec.nth(2) == 31);
            CHECK(*vec.nth(3) == 41);
            CHECK(*vec.nth(4) == 51);
            CHECK(*vec.nth(5) == 61);
            CHECK(*vec.nth(6) == 71);
            CHECK(*vec.nth(7) == 81);
        }

        // n > vec.size()  &&  n > vec.capacity()  (with storage reallocation)
        {
            sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec;

            vec.emplace(vec.end(), 10);
            vec.emplace(vec.end(), 20);
            vec.emplace(vec.end(), 30);
            vec.emplace(vec.end(), 40);
            vec.emplace(vec.end(), 50);

            CHECK(vec.size() == 5);
            CHECK(vec.capacity() == 5);
            CHECK(*vec.nth(0) == 10);
            CHECK(*vec.nth(1) == 20);
            CHECK(*vec.nth(2) == 30);
            CHECK(*vec.nth(3) == 40);
            CHECK(*vec.nth(4) == 50);

            std::vector<xint> data({11, 21, 31, 41, 51, 61, 71, 81});

            vec.assign(data.begin(), data.end());

            CHECK(vec.size() == 8);
            CHECK(vec.capacity() > 5);
            CHECK(*vec.nth(0) == 11);
            CHECK(*vec.nth(1) == 21);
            CHECK(*vec.nth(2) == 31);
            CHECK(*vec.nth(3) == 41);
            CHECK(*vec.nth(4) == 51);
            CHECK(*vec.nth(5) == 61);
            CHECK(*vec.nth(6) == 71);
            CHECK(*vec.nth(7) == 81);
        }
    }
}

PRINT("Test assign(std::initializer_list");
{
    // n == vec.size()
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        std::initializer_list<xint> ilist{11, 21, 31, 41, 51};

        vec.assign(ilist);

        CHECK(vec.size() == 5);
        CHECK(*vec.nth(0) == 11);
        CHECK(*vec.nth(1) == 21);
        CHECK(*vec.nth(2) == 31);
        CHECK(*vec.nth(3) == 41);
        CHECK(*vec.nth(4) == 51);
    }

    // n < vec.size()
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        std::initializer_list<xint> ilist{11, 21};

        vec.assign(ilist);

        CHECK(vec.size() == 2);
        CHECK(*vec.nth(0) == 11);
        CHECK(*vec.nth(1) == 21);
    }

    // n > vec.size()  &&  n < vec.capacity()  (without storage reallocation)
    {
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

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

        std::initializer_list<xint> ilist{11, 21, 31, 41, 51, 61, 71, 81};

        vec.assign(ilist);

        CHECK(vec.size() == 8);
        CHECK(*vec.nth(0) == 11);
        CHECK(*vec.nth(1) == 21);
        CHECK(*vec.nth(2) == 31);
        CHECK(*vec.nth(3) == 41);
        CHECK(*vec.nth(4) == 51);
        CHECK(*vec.nth(5) == 61);
        CHECK(*vec.nth(6) == 71);
        CHECK(*vec.nth(7) == 81);
    }

    // n > vec.size()  &&  n > vec.capacity()  (with storage reallocation)
    {
        sfl::small_vector<xint, 5, TPARAM_ALLOCATOR<xint>> vec;

        vec.emplace(vec.end(), 10);
        vec.emplace(vec.end(), 20);
        vec.emplace(vec.end(), 30);
        vec.emplace(vec.end(), 40);
        vec.emplace(vec.end(), 50);

        CHECK(vec.size() == 5);
        CHECK(vec.capacity() == 5);
        CHECK(*vec.nth(0) == 10);
        CHECK(*vec.nth(1) == 20);
        CHECK(*vec.nth(2) == 30);
        CHECK(*vec.nth(3) == 40);
        CHECK(*vec.nth(4) == 50);

        std::initializer_list<xint> ilist{11, 21, 31, 41, 51, 61, 71, 81};

        vec.assign(ilist);

        CHECK(vec.size() == 8);
        CHECK(vec.capacity() > 5);
        CHECK(*vec.nth(0) == 11);
        CHECK(*vec.nth(1) == 21);
        CHECK(*vec.nth(2) == 31);
        CHECK(*vec.nth(3) == 41);
        CHECK(*vec.nth(4) == 51);
        CHECK(*vec.nth(5) == 61);
        CHECK(*vec.nth(6) == 71);
        CHECK(*vec.nth(7) == 81);
    }
}

///////////////////////////////////////////////////////////////////////////////

PRINT("Test NON-MEMBER comparison operators");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec1, vec2;

    vec1.emplace(vec1.end(), 10);
    vec1.emplace(vec1.end(), 20);
    vec1.emplace(vec1.end(), 30);

    vec2.emplace(vec2.end(), 10);
    vec2.emplace(vec2.end(), 20);
    vec2.emplace(vec2.end(), 30);
    vec2.emplace(vec2.end(), 40);
    vec2.emplace(vec2.end(), 50);

    CHECK((vec1 == vec1) == true);
    CHECK((vec1 == vec2) == false);
    CHECK((vec2 == vec1) == false);
    CHECK((vec2 == vec2) == true);

    CHECK((vec1 != vec1) == false);
    CHECK((vec1 != vec2) == true);
    CHECK((vec2 != vec1) == true);
    CHECK((vec2 != vec2) == false);

    CHECK((vec1 < vec1) == false);
    CHECK((vec1 < vec2) == true);
    CHECK((vec2 < vec1) == false);
    CHECK((vec2 < vec2) == false);

    CHECK((vec1 > vec1) == false);
    CHECK((vec1 > vec2) == false);
    CHECK((vec2 > vec1) == true);
    CHECK((vec2 > vec2) == false);

    CHECK((vec1 <= vec1) == true);
    CHECK((vec1 <= vec2) == true);
    CHECK((vec2 <= vec1) == false);
    CHECK((vec2 <= vec2) == true);

    CHECK((vec1 >= vec1) == true);
    CHECK((vec1 >= vec2) == false);
    CHECK((vec2 >= vec1) == true);
    CHECK((vec2 >= vec2) == true);
}

PRINT("Test NON-MEMBER swap(container&)");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec1, vec2;

    vec1.emplace(vec1.end(), 10);
    vec1.emplace(vec1.end(), 20);
    vec1.emplace(vec1.end(), 30);

    vec2.emplace(vec2.end(), 40);
    vec2.emplace(vec2.end(), 50);
    vec2.emplace(vec2.end(), 60);
    vec2.emplace(vec2.end(), 70);
    vec2.emplace(vec2.end(), 80);

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

    ///////////////////////////////////////////////////////////////////////////

    swap(vec1, vec2);

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
}

PRINT("Test NON-MEMBER erase(container&, const U&)");
{
    sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>> vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.size() == 5);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 20);
    CHECK(*vec.nth(3) == 20);
    CHECK(*vec.nth(4) == 30);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase(vec, 20) == 3);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase(vec, 20) == 0);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);
}

PRINT("Test NON-MEMBER erase_if(container&, Predicate)");
{
    using container_type =
        sfl::small_vector<xint, 100, TPARAM_ALLOCATOR<xint>>;

    using const_reference = typename container_type::const_reference;

    ///////////////////////////////////////////////////////////////////////////

    container_type vec;

    vec.emplace(vec.end(), 10);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 20);
    vec.emplace(vec.end(), 30);

    CHECK(vec.size() == 5);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 20);
    CHECK(*vec.nth(2) == 20);
    CHECK(*vec.nth(3) == 20);
    CHECK(*vec.nth(4) == 30);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(vec, [](const_reference& value){ return value == 20; }) == 3);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);

    ///////////////////////////////////////////////////////////////////////////

    CHECK(erase_if(vec, [](const_reference& value){ return value == 20; }) == 0);
    CHECK(vec.size() == 2);
    CHECK(*vec.nth(0) == 10);
    CHECK(*vec.nth(1) == 30);
}
