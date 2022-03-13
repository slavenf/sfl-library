//
// g++ -Wall -Wextra -std=c++11 -g -I ../include -o test.out test_small_flat_map.cpp
// valgrind --leak-check=full ./test.out
//

#undef NDEBUG
#include <cassert>
#include <iostream>
#include <vector>

#include <sfl/small_flat_map.hpp>

#include "MyInt.hpp"
#include "MyString.hpp"
#include "Person.hpp"

int main()
{
    using std::cout;
    using std::endl;

    cout << "Create empty containers and test all non-modifying "
            "member functions." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 0> m1;
        const sfl::small_flat_map<MyInt, MyString, 0> m2;
        sfl::small_flat_map<MyInt, MyString, 5> m3;
        const sfl::small_flat_map<MyInt, MyString, 5> m4;

        assert(m1.empty());
        assert(m2.empty());
        assert(m3.empty());
        assert(m4.empty());

        assert(m1.size() == 0);
        assert(m2.size() == 0);
        assert(m3.size() == 0);
        assert(m4.size() == 0);

        assert(m1.capacity() == 0);
        assert(m2.capacity() == 0);
        assert(m3.capacity() == 5);
        assert(m4.capacity() == 5);

        assert(m1.begin() == m1.end());
        assert(m2.begin() == m2.end());
        assert(m3.begin() == m3.end());
        assert(m4.begin() == m4.end());

        assert(m1.cbegin() == m1.cend());
        assert(m2.cbegin() == m2.cend());
        assert(m3.cbegin() == m3.cend());
        assert(m4.cbegin() == m4.cend());

        assert(m1.begin() == m1.cbegin());
        assert(m2.begin() == m2.cbegin());
        assert(m3.begin() == m3.cbegin());
        assert(m4.begin() == m4.cbegin());

        assert(m1.rbegin() == m1.rend());
        assert(m2.rbegin() == m2.rend());
        assert(m3.rbegin() == m3.rend());
        assert(m4.rbegin() == m4.rend());

        assert(m1.crbegin() == m1.crend());
        assert(m2.crbegin() == m2.crend());
        assert(m3.crbegin() == m3.crend());
        assert(m4.crbegin() == m4.crend());

        assert(m1.rbegin() == m1.crbegin());
        assert(m2.rbegin() == m2.crbegin());
        assert(m3.rbegin() == m3.crbegin());
        assert(m4.rbegin() == m4.crbegin());

        assert(m1.begin() == m1.nth(0));
        assert(m2.begin() == m2.nth(0));
        assert(m3.begin() == m3.nth(0));
        assert(m4.begin() == m4.nth(0));

        assert(m1.cbegin() == m1.nth(0));
        assert(m2.cbegin() == m2.nth(0));
        assert(m3.cbegin() == m3.nth(0));
        assert(m4.cbegin() == m4.nth(0));

        assert(m1.index_of(m1.nth(0)) == 0);
        assert(m2.index_of(m2.nth(0)) == 0);
        assert(m3.index_of(m3.nth(0)) == 0);
        assert(m4.index_of(m4.nth(0)) == 0);

        assert(m1.data() == m1.begin());
        assert(m2.data() == m2.begin());
        assert(m3.data() == m3.begin());
        assert(m4.data() == m4.begin());

        assert(m1.lower_bound(42) == m1.end());
        assert(m2.lower_bound(42) == m2.end());
        assert(m3.lower_bound(42) == m3.end());
        assert(m4.lower_bound(42) == m4.end());

        assert(m1.upper_bound(42) == m1.end());
        assert(m2.upper_bound(42) == m2.end());
        assert(m3.upper_bound(42) == m3.end());
        assert(m4.upper_bound(42) == m4.end());

        assert(m1.equal_range(42) == std::make_pair(m1.end(), m1.end()));
        assert(m2.equal_range(42) == std::make_pair(m2.end(), m2.end()));
        assert(m3.equal_range(42) == std::make_pair(m3.end(), m3.end()));
        assert(m4.equal_range(42) == std::make_pair(m4.end(), m4.end()));

        assert(m1.find(42) == m1.end());
        assert(m2.find(42) == m2.end());
        assert(m3.find(42) == m3.end());
        assert(m4.find(42) == m4.end());

        assert(m1.count(42) == 0);
        assert(m2.count(42) == 0);
        assert(m3.count(42) == 0);
        assert(m4.count(42) == 0);

        assert(m1.contains(42) == false);
        assert(m2.contains(42) == false);
        assert(m3.contains(42) == false);
        assert(m4.contains(42) == false);

        auto a1 = m1.get_allocator(); (void)a1;
        auto a2 = m2.get_allocator(); (void)a2;
        auto a3 = m3.get_allocator(); (void)a3;
        auto a4 = m4.get_allocator(); (void)a4;

        const MyInt i(10);
        const MyInt j(20);

        auto kc1 = m1.key_comp(); assert(kc1(i, j));
        auto kc2 = m2.key_comp(); assert(kc2(i, j));
        auto kc3 = m3.key_comp(); assert(kc3(i, j));
        auto kc4 = m4.key_comp(); assert(kc4(i, j));

        const std::pair<MyInt, MyString> p1(10, "/10/");
        const std::pair<MyInt, MyString> p2(20, "/20/");

        auto vc1 = m1.value_comp(); assert(vc1(p1, p2));
        auto vc2 = m2.value_comp(); assert(vc2(p1, p2));
        auto vc3 = m3.value_comp(); assert(vc3(p1, p2));
        auto vc4 = m4.value_comp(); assert(vc4(p1, p2));
    }

    cout << "Create empty containers and test all lookup functions "
            "that support transparent lookup." << endl;
    {
        sfl::small_flat_map<Person, MyString, 0, PersonLess> m1;
        const sfl::small_flat_map<Person, MyString, 0, PersonLess> m2;

        Person p(42, "John");

        assert(m1.lower_bound(p) == m1.end());
        assert(m2.lower_bound(p) == m1.end());

        assert(m1.lower_bound(42) == m1.end());
        assert(m2.lower_bound(42) == m1.end());

        assert(m1.upper_bound(p) == m1.end());
        assert(m2.upper_bound(p) == m1.end());

        assert(m1.upper_bound(42) == m1.end());
        assert(m2.upper_bound(42) == m1.end());

        assert(m1.equal_range(p) == std::make_pair(m1.end(), m1.end()));
        assert(m2.equal_range(p) == std::make_pair(m1.cend(), m1.cend()));

        assert(m1.equal_range(42) == std::make_pair(m1.end(), m1.end()));
        assert(m2.equal_range(42) == std::make_pair(m1.cend(), m1.cend()));

        assert(m1.find(p) == m1.end());
        assert(m2.find(p) == m1.end());

        assert(m1.find(42) == m1.end());
        assert(m2.find(42) == m1.end());

        assert(m1.count(p) == 0);
        assert(m2.count(p) == 0);

        assert(m1.count(42) == 0);
        assert(m2.count(42) == 0);

        assert(m1.contains(p) == false);
        assert(m2.contains(p) == false);

        assert(m1.contains(42) == false);
        assert(m2.contains(42) == false);
    }

    cout << "Test emplace(Args&&...) (N > 0, with reallocation)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 3> m;

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), true));
            assert(m.size() == 1);
            assert(m.capacity() == 3);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(m.size() == 2);
            assert(m.capacity() == 3);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(m.size() == 3);
            assert(m.capacity() == 3);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(3), true));
            assert(m.size() == 4);
            assert(m.capacity() == 6);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(3), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(2), true));
            assert(m.size() == 5);
            assert(m.capacity() == 6);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 16 && m.nth(2)->second == "/16/");
            assert(m.nth(3)->first == 20 && m.nth(3)->second == "/20/");
            assert(m.nth(4)->first == 30 && m.nth(4)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(2), false));
        }
    }

    cout << "Test emplace(Args&&...) (N == 0, with reallocation)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 0> m;

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), true));
            assert(m.size() == 1);
            assert(m.capacity() == 1);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(10, "/10/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(m.size() == 2);
            assert(m.capacity() == 2);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(m.size() == 3);
            assert(m.capacity() == 4);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(15),
                                 std::forward_as_tuple("/15/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(3), true));
            assert(m.size() == 4);
            assert(m.capacity() == 4);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(30, "/30/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(3), false));
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(2), true));
            assert(m.size() == 5);
            assert(m.capacity() == 8);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 16 && m.nth(2)->second == "/16/");
            assert(m.nth(3)->first == 20 && m.nth(3)->second == "/20/");
            assert(m.nth(4)->first == 30 && m.nth(4)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.emplace(16, "/16/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(2), false));
        }
    }

    cout << "Test non-modifying member functions on non-empty container (1)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        m.emplace(10, "/10/");
        m.emplace(20, "/20/");
        m.emplace(30, "/30/");

        {
            auto it = m.begin();
            assert(it->first == 10 && it->second == "/10/"); ++it;
            assert(it->first == 20 && it->second == "/20/"); ++it;
            assert(it->first == 30 && it->second == "/30/"); ++it;
            assert(it == m.end());
        }

        {
            auto it = m.cbegin();
            assert(it->first == 10 && it->second == "/10/"); ++it;
            assert(it->first == 20 && it->second == "/20/"); ++it;
            assert(it->first == 30 && it->second == "/30/"); ++it;
            assert(it == m.cend());
        }

        {
            auto it = m.rbegin();
            assert(it->first == 30 && it->second == "/30/"); ++it;
            assert(it->first == 20 && it->second == "/20/"); ++it;
            assert(it->first == 10 && it->second == "/10/"); ++it;
            assert(it == m.rend());
        }

        {
            auto it = m.crbegin();
            assert(it->first == 30 && it->second == "/30/"); ++it;
            assert(it->first == 20 && it->second == "/20/"); ++it;
            assert(it->first == 10 && it->second == "/10/"); ++it;
            assert(it == m.crend());
        }

        {
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
            assert(m.nth(3) == m.end());
        }

        {
            assert(std::next(m.begin(), 0) == m.nth(0));
            assert(std::next(m.begin(), 1) == m.nth(1));
            assert(std::next(m.begin(), 2) == m.nth(2));
        }

        {
            assert(std::next(m.cbegin(), 0) == m.nth(0));
            assert(std::next(m.cbegin(), 1) == m.nth(1));
            assert(std::next(m.cbegin(), 2) == m.nth(2));
        }

        {
            assert(m.index_of(m.nth(0)) == 0);
            assert(m.index_of(m.nth(1)) == 1);
            assert(m.index_of(m.nth(2)) == 2);
        }

        {
            auto data = m.data();
            assert(data->first == 10 && data->second == "/10/"); ++data;
            assert(data->first == 20 && data->second == "/20/"); ++data;
            assert(data->first == 30 && data->second == "/30/"); ++data;
        }

        {
            assert(m.lower_bound(10) == m.nth(0));
            assert(m.lower_bound(20) == m.nth(1));
            assert(m.lower_bound(30) == m.nth(2));
        }

        {
            assert(m.upper_bound(10) == m.nth(1));
            assert(m.upper_bound(20) == m.nth(2));
            assert(m.upper_bound(30) == m.nth(3));
        }

        {
            assert(m.equal_range(10) == std::make_pair(m.nth(0), m.nth(1)));
            assert(m.equal_range(20) == std::make_pair(m.nth(1), m.nth(2)));
            assert(m.equal_range(30) == std::make_pair(m.nth(2), m.nth(3)));
            assert(m.equal_range(40) == std::make_pair(m.end(), m.end()));
        }

        {
            assert(m.find(10) == m.nth(0));
            assert(m.find(20) == m.nth(1));
            assert(m.find(30) == m.nth(2));
            assert(m.find(40) == m.end());
        }

        {
            assert(m.count(10) == 1);
            assert(m.count(20) == 1);
            assert(m.count(30) == 1);
            assert(m.count(40) == 0);
        }

        {
            assert(m.contains(10) == true);
            assert(m.contains(20) == true);
            assert(m.contains(30) == true);
            assert(m.contains(40) == false);
        }

        {
            assert(m.at(10) == "/10/");
            assert(m.at(20) == "/20/");
            assert(m.at(30) == "/30/");
        }

        {
            assert(m[10] == "/10/");
            assert(m[20] == "/20/");
            assert(m[30] == "/30/");
        }
    }

    cout << "Test non-modifying member functions on non-empty container (2)." << endl;
    {
        sfl::small_flat_map<Person, MyString, 10, PersonLess> m;

        m.emplace(Person(10, "Name 10"), "Person 10");
        m.emplace(Person(20, "Name 20"), "Person 20");
        m.emplace(Person(30, "Name 30"), "Person 30");

        {
            auto it = m.begin();
            assert(it->first.id() == 10 && it->first.name() == "Name 10" && it->second == "Person 10"); ++it;
            assert(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            assert(it->first.id() == 30 && it->first.name() == "Name 30" && it->second == "Person 30"); ++it;
            assert(it == m.end());
        }

        {
            auto it = m.cbegin();
            assert(it->first.id() == 10 && it->first.name() == "Name 10" && it->second == "Person 10"); ++it;
            assert(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            assert(it->first.id() == 30 && it->first.name() == "Name 30" && it->second == "Person 30"); ++it;
            assert(it == m.cend());
        }

        {
            auto it = m.rbegin();
            assert(it->first.id() == 30 && it->first.name() == "Name 30" && it->second == "Person 30"); ++it;
            assert(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            assert(it->first.id() == 10 && it->first.name() == "Name 10" && it->second == "Person 10"); ++it;
            assert(it == m.rend());
        }

        {
            auto it = m.crbegin();
            assert(it->first.id() == 30 && it->first.name() == "Name 30" && it->second == "Person 30"); ++it;
            assert(it->first.id() == 20 && it->first.name() == "Name 20" && it->second == "Person 20"); ++it;
            assert(it->first.id() == 10 && it->first.name() == "Name 10" && it->second == "Person 10"); ++it;
            assert(it == m.crend());
        }

        {
            assert(std::next(m.begin(), 0) == m.nth(0));
            assert(std::next(m.begin(), 1) == m.nth(1));
            assert(std::next(m.begin(), 2) == m.nth(2));
        }

        {
            assert(std::next(m.cbegin(), 0) == m.nth(0));
            assert(std::next(m.cbegin(), 1) == m.nth(1));
            assert(std::next(m.cbegin(), 2) == m.nth(2));
        }

        {
            assert(m.index_of(m.nth(0)) == 0);
            assert(m.index_of(m.nth(1)) == 1);
            assert(m.index_of(m.nth(2)) == 2);
        }

        {
            auto data = m.data();
            assert(data->first.id() == 10 && data->first.name() == "Name 10" && data->second == "Person 10"); ++data;
            assert(data->first.id() == 20 && data->first.name() == "Name 20" && data->second == "Person 20"); ++data;
            assert(data->first.id() == 30 && data->first.name() == "Name 30" && data->second == "Person 30"); ++data;
        }

        {
            assert(m.lower_bound(Person(10, "xxx")) == m.nth(0));
            assert(m.lower_bound(Person(20, "xxx")) == m.nth(1));
            assert(m.lower_bound(Person(30, "xxx")) == m.nth(2));
        }

        {
            assert(m.lower_bound(10) == m.nth(0));
            assert(m.lower_bound(20) == m.nth(1));
            assert(m.lower_bound(30) == m.nth(2));
        }

        {
            assert(m.upper_bound(Person(10, "xxx")) == m.nth(1));
            assert(m.upper_bound(Person(20, "xxx")) == m.nth(2));
            assert(m.upper_bound(Person(30, "xxx")) == m.nth(3));
        }

        {
            assert(m.upper_bound(10) == m.nth(1));
            assert(m.upper_bound(20) == m.nth(2));
            assert(m.upper_bound(30) == m.nth(3));
        }

        {
            assert(m.equal_range(Person(10, "xxx")) == std::make_pair(m.nth(0), m.nth(1)));
            assert(m.equal_range(Person(20, "xxx")) == std::make_pair(m.nth(1), m.nth(2)));
            assert(m.equal_range(Person(30, "xxx")) == std::make_pair(m.nth(2), m.nth(3)));
            assert(m.equal_range(Person(40, "xxx")) == std::make_pair(m.end(), m.end()));
        }

        {
            assert(m.equal_range(10) == std::make_pair(m.nth(0), m.nth(1)));
            assert(m.equal_range(20) == std::make_pair(m.nth(1), m.nth(2)));
            assert(m.equal_range(30) == std::make_pair(m.nth(2), m.nth(3)));
            assert(m.equal_range(40) == std::make_pair(m.end(), m.end()));
        }

        {
            assert(m.find(Person(10, "xxx")) == m.nth(0));
            assert(m.find(Person(20, "xxx")) == m.nth(1));
            assert(m.find(Person(30, "xxx")) == m.nth(2));
            assert(m.find(Person(40, "xxx")) == m.end());
        }

        {
            assert(m.find(10) == m.nth(0));
            assert(m.find(20) == m.nth(1));
            assert(m.find(30) == m.nth(2));
            assert(m.find(40) == m.end());
        }

        {
            assert(m.count(Person(10, "xxx")) == 1);
            assert(m.count(Person(20, "xxx")) == 1);
            assert(m.count(Person(30, "xxx")) == 1);
            assert(m.count(Person(40, "xxx")) == 0);
        }

        {
            assert(m.count(10) == 1);
            assert(m.count(20) == 1);
            assert(m.count(30) == 1);
            assert(m.count(40) == 0);
        }

        {
            assert(m.contains(Person(10, "xxx")) == true);
            assert(m.contains(Person(20, "xxx")) == true);
            assert(m.contains(Person(30, "xxx")) == true);
            assert(m.contains(Person(40, "xxx")) == false);
        }

        {
            assert(m.contains(10) == true);
            assert(m.contains(20) == true);
            assert(m.contains(30) == true);
            assert(m.contains(40) == false);
        }
    }

    cout << "Test emplace_hint(const_iterator, Args&&...)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.emplace_hint(m.nth(0), 10, "/10/");
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            // good hint, element exists
            auto res = m.emplace_hint(m.nth(0), 10, "/error/");
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.emplace_hint(m.nth(1), 20, "/20/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            // good hint, element exists
            auto res = m.emplace_hint(m.nth(1), 20, "/error/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.emplace_hint(m.nth(1), 15, "/15/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            // good hint, element exists
            auto res = m.emplace_hint(m.nth(1), 15, "/error/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            // bad hint, element does not exist
            auto res = m.emplace_hint(m.nth(0), 30, "/30/");
            cout << "<" << endl;

            assert(res == m.nth(3));
            assert(m.size() == 4);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            cout << ">" << endl;
            // bad hint, element exists
            auto res = m.emplace_hint(m.nth(0), 30, "/error/");
            cout << "<" << endl;

            assert(res == m.nth(3));
            assert(m.size() == 4);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }
    }

    cout << "Test insert(const value_type&)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            const std::pair<MyInt, MyString> v(10, "/10/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), true));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const std::pair<MyInt, MyString> v(10, "/10/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), false));
        }

        {
            const std::pair<MyInt, MyString> v(20, "/20/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const std::pair<MyInt, MyString> v(20, "/20/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
        }

        {
            const std::pair<MyInt, MyString> v(15, "/15/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            const std::pair<MyInt, MyString> v(15, "/15/");

            cout << ">" << endl;
            auto res = m.insert(v);
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
        }
    }

    cout << "Test insert(value_type&&)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            std::pair<MyInt, MyString> v(10, "/10/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), true));
            assert(v.first == -10 && v.second.value() == "");
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            std::pair<MyInt, MyString> v(10, "/10/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), false));
            assert(v.first == 10 && v.second == "/10/");
        }

        {
            std::pair<MyInt, MyString> v(20, "/20/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(v.first == -20 && v.second.value() == "");
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            std::pair<MyInt, MyString> v(20, "/20/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
            assert(v.first == 20 && v.second == "/20/");
        }

        {
            std::pair<MyInt, MyString> v(15, "/15/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(v.first == -15 && v.second.value() == "");
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            std::pair<MyInt, MyString> v(15, "/15/");

            cout << ">" << endl;
            auto res = m.insert(std::move(v));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
            assert(v.first == 15 && v.second == "/15/");
        }
    }

    cout << "Test insert(P&&)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(10, "/10/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), true));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(10, "/10/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), false));
        }

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(20, "/20/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
        }

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(15, "/15/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(std::make_pair(15, "/15/"));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
        }
    }

    cout << "Test insert(const_iterator, const value_type&)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            const std::pair<MyInt, MyString> v(10, "/10/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(0), v);
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const std::pair<MyInt, MyString> v(10, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(0), v);
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const std::pair<MyInt, MyString> v(20, "/20/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(1), v);
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const std::pair<MyInt, MyString> v(20, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(1), v);
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const std::pair<MyInt, MyString> v(15, "/15/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(1), v);
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            const std::pair<MyInt, MyString> v(15, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(1), v);
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            const std::pair<MyInt, MyString> v(30, "/30/");

            cout << ">" << endl;
            // bad hint, element does not exist
            auto res = m.insert(m.nth(0), v);
            cout << "<" << endl;

            assert(res == m.nth(3));
            assert(m.size() == 4);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            const std::pair<MyInt, MyString> v(30, "/error/");

            cout << ">" << endl;
            // bad hint, element exists
            auto res = m.insert(m.nth(0), v);
            cout << "<" << endl;

            assert(res == m.nth(3));
            assert(m.size() == 4);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }
    }

    cout << "Test insert(const_iterator, value_type&&)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            std::pair<MyInt, MyString> v(10, "/10/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(0), std::move(v));
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(v.first == -10 && v.second == "");
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            std::pair<MyInt, MyString> v(10, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(0), std::move(v));
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(v.first == 10 && v.second == "/error/");
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            std::pair<MyInt, MyString> v(20, "/20/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(1), std::move(v));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(v.first == -20 && v.second == "");
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            std::pair<MyInt, MyString> v(20, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(1), std::move(v));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(v.first == 20 && v.second == "/error/");
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            std::pair<MyInt, MyString> v(15, "/15/");

            cout << ">" << endl;
            // good hint, element does not exist
            auto res = m.insert(m.nth(1), std::move(v));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(v.first == -15 && v.second == "");
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            std::pair<MyInt, MyString> v(15, "/error/");

            cout << ">" << endl;
            // good hint, element exists
            auto res = m.insert(m.nth(1), std::move(v));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(v.first == 15 && v.second == "/error/");
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            std::pair<MyInt, MyString> v(30, "/30/");

            cout << ">" << endl;
            // bad hint, element does not exist
            auto res = m.insert(m.nth(0), std::move(v));
            cout << "<" << endl;

            assert(res == m.nth(3));
            assert(v.first == -30 && v.second == "");
            assert(m.size() == 4);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            std::pair<MyInt, MyString> v(30, "/error/");

            cout << ">" << endl;
            // bad hint, element exists
            auto res = m.insert(m.nth(0), std::move(v));
            cout << "<" << endl;

            assert(res == m.nth(3));
            assert(v.first == 30 && v.second == "/error/");
            assert(m.size() == 4);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }
    }

    cout << "Test insert(const_iterator, P&&...)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin(), std::make_pair(10, "/10/"));
            cout << "<" << endl;

            assert(res == m.begin());
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin(), std::make_pair(10, "/error/"));
            cout << "<" << endl;

            assert(res == m.begin());
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin() + 1, std::make_pair(20, "/20/"));
            cout << "<" << endl;

            assert(res == m.begin() + 1);
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin() + 1, std::make_pair(20, "/error/"));
            cout << "<" << endl;

            assert(res == m.begin() + 1);
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin() + 1, std::make_pair(15, "/15/"));
            cout << "<" << endl;

            assert(res == m.begin() + 1);
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin() + 1, std::make_pair(15, "/error/"));
            cout << "<" << endl;

            assert(res == m.begin() + 1);
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin(), std::make_pair(30, "/30/"));
            cout << "<" << endl;

            assert(res == m.begin() + 3);
            assert(m.size() == 4);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.insert(m.begin(), std::make_pair(30, "/error/"));
            cout << "<" << endl;

            assert(res == m.begin() + 3);
            assert(m.size() == 4);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
            assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
        }
    }

    cout << "Test insert(InputIt, InputIt)." << endl;
    {
        const std::vector<std::pair<MyInt, MyString>> v
        (
            {
                {10, "/10/"},
                {10, "/10.1/"},
                {20, "/20/"},
                {20, "/20.1/"},
                {15, "/15/"},
                {15, "/15.1/"},
                {30, "/30/"},
                {30, "/30.1/"}
            }
        );

        sfl::small_flat_map<MyInt, MyString, 10> m;

        cout << ">" << endl;
        m.insert(v.begin(), v.end());
        cout << "<" << endl;

        assert(m.size() == 4);
        assert(m.capacity() == 10);
        assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
        assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
    }

    cout << "Test insert(std::initializer_list)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        cout << ">" << endl;
        m.insert
        (
            {
                {10, "/10/"},
                {10, "/10.1/"},
                {20, "/20/"},
                {20, "/20.1/"},
                {15, "/15/"},
                {15, "/15.1/"},
                {30, "/30/"},
                {30, "/30.1/"},
            }
        );
        cout << "<" << endl;

        assert(m.size() == 4);
        assert(m.capacity() == 10);
        assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
        assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        assert(m.nth(3)->first == 30 && m.nth(3)->second == "/30/");
    }

    cout << "Test insert_or_assign(const Key&, M&&)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            const MyInt i(10);

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, "/10/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), true));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const MyInt i(10);

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, "/910/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), false));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
        }

        {
            const MyInt i(20);

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, "/20/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const MyInt i(20);

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, "/920/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/920/");
        }

        {
            const MyInt i(15);
            MyString s("/15/");

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, std::move(s));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(s == "");
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }

        {
            const MyInt i(15);
            MyString s("/915/");

            cout << ">" << endl;
            auto res = m.insert_or_assign(i, std::move(s));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
            assert(s == "");
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/915/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }
    }

    cout << "Test insert_or_assign(Key&&, M&&)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            MyInt i(10);

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), "/10/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), true));
            assert(i == -10);
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            MyInt i(10);

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), "/910/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), false));
            assert(i == 10);
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), "/20/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(i == -20);
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), "/920/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
            assert(i == 20);
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/920/");
        }

        {
            MyInt i(15);
            MyString s("/15/");

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), std::move(s));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(i == -15);
            assert(s == "");
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }

        {
            MyInt i(15);
            MyString s("/915/");

            cout << ">" << endl;
            auto res = m.insert_or_assign(std::move(i), std::move(s));
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
            assert(i == 15);
            assert(s == "");
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/915/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }
    }

    cout << "Test insert_or_assign(const_iterator, const Key&, M&&)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            const MyInt i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(0), i, "/10/");
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const MyInt i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(0), i, "/910/");
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
        }

        {
            const MyInt i(20);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(1), i, "/20/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const MyInt i(20);

            cout << ">" << endl;
            // bad hint
            auto res = m.insert_or_assign(m.nth(0), i, "/920/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/920/");
        }

        {
            const MyInt i(15);
            MyString s("/15/");

            cout << ">" << endl;
            // bad hint
            auto res = m.insert_or_assign(m.nth(0), i, std::move(s));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(s == "");
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }

        {
            const MyInt i(15);
            MyString s("/915/");

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(1), i, std::move(s));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(s == "");
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/915/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }
    }

    cout << "Test insert_or_assign(const_iterator, Key&&, M&&)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            MyInt i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(0), std::move(i), "/10/");
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(i == -10);
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            MyInt i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(0), std::move(i), "/910/");
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(i == 10);
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(1), std::move(i), "/20/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(i == -20);
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            // bad hint
            auto res = m.insert_or_assign(m.nth(0), std::move(i), "/920/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(i == 20);
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/920/");
        }

        {
            MyInt i(15);
            MyString s("/15/");

            cout << ">" << endl;
            // bad hint
            auto res = m.insert_or_assign(m.nth(0), std::move(i), std::move(s));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(i == -15);
            assert(s == "");
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }

        {
            MyInt i(15);
            MyString s("/915/");

            cout << ">" << endl;
            // good hint
            auto res = m.insert_or_assign(m.nth(1), std::move(i), std::move(s));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(i == 15);
            assert(s == "");
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/910/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/915/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/920/");
        }
    }

    cout << "Test try_emplace(const Key&, Args&&...)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            const MyInt i(10);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/10/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), true));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const MyInt i(10);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/910/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), false));
        }

        {
            const MyInt i(20);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/20/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const MyInt i(20);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/920/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
        }

        {
            const MyInt i(15);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/15/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            const MyInt i(15);

            cout << ">" << endl;
            auto res = m.try_emplace(i, "/915/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
        }
    }

    cout << "Test try_emplace(Key&&, Args&&...)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            MyInt i(10);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/10/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), true));
            assert(i == -10);
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            MyInt i(10);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/910/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(0), false));
            assert(i == 10);
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/20/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(i == -20);
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/920/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
            assert(i == 20);
        }

        {
            MyInt i(15);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/15/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), true));
            assert(i == -15);
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            MyInt i(15);

            cout << ">" << endl;
            auto res = m.try_emplace(std::move(i), "/915/");
            cout << "<" << endl;

            assert(res == std::make_pair(m.nth(1), false));
            assert(i == 15);
        }
    }

    cout << "Test try_emplace(const_iterator, const Key&, Args&&...)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            const MyInt i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(0), i, "/10/");
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const MyInt i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(0), i, "/910/");
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const MyInt i(20);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(1), i, "/20/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const MyInt i(20);

            cout << ">" << endl;
            // bad hint
            auto res = m.try_emplace(m.nth(1), i, "/920/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            const MyInt i(15);

            cout << ">" << endl;
            // bad hint
            auto res = m.try_emplace(m.nth(0), i, "/15/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            const MyInt i(15);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(1), i, "/915/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }
    }

    cout << "Test try_emplace(const_iterator, Key&&, Args&&...)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            MyInt i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(0), std::move(i), "/10/");
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(i == -10);
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            MyInt i(10);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(0), std::move(i), "/910/");
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(i == 10);
            assert(m.size() == 1);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(1), std::move(i), "/20/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(i == -20);
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            MyInt i(20);

            cout << ">" << endl;
            // bad hint
            auto res = m.try_emplace(m.nth(1), std::move(i), "/920/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(i == 20);
            assert(m.size() == 2);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            MyInt i(15);

            cout << ">" << endl;
            // bad hint
            auto res = m.try_emplace(m.nth(0), std::move(i), "/15/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(i == -15);
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }

        {
            MyInt i(15);

            cout << ">" << endl;
            // good hint
            auto res = m.try_emplace(m.nth(1), std::move(i), "/915/");
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(i == 15);
            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 15 && m.nth(1)->second == "/15/");
            assert(m.nth(2)->first == 20 && m.nth(2)->second == "/20/");
        }
    }

    cout << "Test clear()." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            m.emplace(40, "/40/");
            cout << "<" << endl;

            assert(m.size() == 4);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
            assert(m.nth(3)->first == 40 && m.nth(3)->second == "/40/");
        }

        {
            cout << ">" << endl;
            m.clear();
            cout << "<" << endl;

            assert(m.size() == 0);
        }

        {
            cout << ">" << endl;
            m.emplace(50, "/50/");
            m.emplace(60, "/60/");
            cout << "<" << endl;

            assert(m.size() == 2);
            assert(m.nth(0)->first == 50 && m.nth(0)->second == "/50/");
            assert(m.nth(1)->first == 60 && m.nth(1)->second == "/60/");
        }

        {
            cout << ">" << endl;
            m.clear();
            cout << "<" << endl;

            assert(m.size() == 0);
        }
    }

    cout << "Test erase(const_iterator)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            m.emplace(40, "/40/");
            cout << "<" << endl;

            assert(m.size() == 4);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
            assert(m.nth(3)->first == 40 && m.nth(3)->second == "/40/");
        }

        {
            cout << ">" << endl;
            auto res = m.erase(m.nth(1));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 3);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 30 && m.nth(1)->second == "/30/");
            assert(m.nth(2)->first == 40 && m.nth(2)->second == "/40/");
        }

        {
            cout << ">" << endl;
            auto res = m.erase(m.nth(0));
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 2);
            assert(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
            assert(m.nth(1)->first == 40 && m.nth(1)->second == "/40/");
        }

        {
            cout << ">" << endl;
            auto res = m.erase(m.nth(1));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 1);
            assert(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = m.erase(m.nth(0));
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 0);
        }
    }

    cout << "Test erase(const_iterator, const_iterator)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            m.emplace(40, "/40/");
            m.emplace(50, "/50/");
            m.emplace(60, "/60/");
            m.emplace(70, "/70/");
            m.emplace(80, "/80/");
            m.emplace(90, "/90/");
            cout << "<" << endl;

            assert(m.size() == 9);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
            assert(m.nth(3)->first == 40 && m.nth(3)->second == "/40/");
            assert(m.nth(4)->first == 50 && m.nth(4)->second == "/50/");
            assert(m.nth(5)->first == 60 && m.nth(5)->second == "/60/");
            assert(m.nth(6)->first == 70 && m.nth(6)->second == "/70/");
            assert(m.nth(7)->first == 80 && m.nth(7)->second == "/80/");
            assert(m.nth(8)->first == 90 && m.nth(8)->second == "/90/");
        }

        {
            cout << ">" << endl;
            // Erase nothing
            auto res = m.erase(m.nth(3), m.nth(3));
            cout << "<" << endl;

            assert(res == m.nth(3));
            assert(m.size() == 9);
        }

        {
            cout << ">" << endl;
            // Erase two elements near begin
            auto res = m.erase(m.nth(1), m.nth(3));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 7);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 40 && m.nth(1)->second == "/40/");
            assert(m.nth(2)->first == 50 && m.nth(2)->second == "/50/");
            assert(m.nth(3)->first == 60 && m.nth(3)->second == "/60/");
            assert(m.nth(4)->first == 70 && m.nth(4)->second == "/70/");
            assert(m.nth(5)->first == 80 && m.nth(5)->second == "/80/");
            assert(m.nth(6)->first == 90 && m.nth(6)->second == "/90/");
        }

        {
            cout << ">" << endl;
            // Erase two elements near end
            auto res = m.erase(m.nth(4), m.nth(6));
            cout << "<" << endl;

            assert(res == m.nth(4));
            assert(m.size() == 5);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 40 && m.nth(1)->second == "/40/");
            assert(m.nth(2)->first == 50 && m.nth(2)->second == "/50/");
            assert(m.nth(3)->first == 60 && m.nth(3)->second == "/60/");
            assert(m.nth(4)->first == 90 && m.nth(4)->second == "/90/");
        }

        {
            cout << ">" << endl;
            // Remove two elements at begin
            auto res = m.erase(m.nth(0), m.nth(2));
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 3);
            assert(m.nth(0)->first == 50 && m.nth(0)->second == "/50/");
            assert(m.nth(1)->first == 60 && m.nth(1)->second == "/60/");
            assert(m.nth(2)->first == 90 && m.nth(2)->second == "/90/");
        }

        {
            cout << ">" << endl;
            // Remove two elements at end
            auto res = m.erase(m.nth(1), m.nth(3));
            cout << "<" << endl;

            assert(res == m.nth(1));
            assert(m.size() == 1);
            assert(m.nth(0)->first == 50 && m.nth(0)->second == "/50/");
        }

        {
            cout << ">" << endl;
            // Remove from begin to end
            auto res = m.erase(m.nth(0), m.nth(1));
            cout << "<" << endl;

            assert(res == m.nth(0));
            assert(m.size() == 0);
        }
    }

    cout << "Test erase(const Key&)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            const MyInt i(10);

            cout << ">" << endl;
            auto res = m.erase(i);
            cout << "<" << endl;

            assert(res == 1);
            assert(m.size() == 2);
            assert(m.nth(0)->first == 20 && m.nth(0)->second == "/20/");
            assert(m.nth(1)->first == 30 && m.nth(1)->second == "/30/");
        }

        {
            const MyInt i(15);

            cout << ">" << endl;
            auto res = m.erase(i);
            cout << "<" << endl;

            assert(res == 0);
            assert(m.size() == 2);
            assert(m.nth(0)->first == 20 && m.nth(0)->second == "/20/");
            assert(m.nth(1)->first == 30 && m.nth(1)->second == "/30/");
        }

        {
            const MyInt i(20);

            cout << ">" << endl;
            auto res = m.erase(i);
            cout << "<" << endl;

            assert(res == 1);
            assert(m.size() == 1);
            assert(m.nth(0)->first == 30 && m.nth(0)->second == "/30/");
        }
    }

    cout << "Test erase(K&&) (transparent erase)." << endl;
    {
        sfl::small_flat_map<Person, MyString, 10, PersonLess> m;

        {
            cout << ">" << endl;
            m.emplace
            (
                std::piecewise_construct,
                std::forward_as_tuple(10, "Person /10/"),
                std::forward_as_tuple("/10/")
            );
            m.emplace
            (
                std::piecewise_construct,
                std::forward_as_tuple(20, "Person /20/"),
                std::forward_as_tuple("/20/")
            );
            cout << "<" << endl;

            assert(m.size() == 2);
        }

        {
            cout << ">" << endl;
            auto res = m.erase(10);
            cout << "<" << endl;

            assert(res == 1);
            assert(m.size() == 1);
        }

        {
            cout << ">" << endl;
            auto res = m.erase(15);
            cout << "<" << endl;

            assert(res == 0);
            assert(m.size() == 1);
        }

        {
            const Person p(20, "persons are compared by ID only");

            cout << ">" << endl;
            auto res = m.erase(p);
            cout << "<" << endl;

            assert(res == 1);
            assert(m.size() == 0);
        }
    }

    cout << "Test swap(small_flat_map&)." << endl;
    {
        // m1 uses internal storage, m2 uses internal storage
        {
            sfl::small_flat_map<MyInt, MyString, 5> m1;
            sfl::small_flat_map<MyInt, MyString, 5> m2;

            m1.emplace(10, "/10/");
            m1.emplace(11, "/11/");
            m1.emplace(12, "/12/");

            m2.emplace(20, "/20/");
            m2.emplace(21, "/21/");
            m2.emplace(22, "/22/");
            m2.emplace(23, "/23/");

            assert(m1.size() == 3);
            assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            assert(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            assert(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            assert(m2.size() == 4);
            assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            assert(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            assert(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            assert(m1.size() == 4);
            assert(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            assert(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            assert(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
            assert(m1.nth(3)->first == 23 && m1.nth(3)->second == "/23/");

            assert(m2.size() == 3);
            assert(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
            assert(m2.nth(1)->first == 11 && m2.nth(1)->second == "/11/");
            assert(m2.nth(2)->first == 12 && m2.nth(2)->second == "/12/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            assert(m1.size() == 3);
            assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            assert(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            assert(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            assert(m2.size() == 4);
            assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            assert(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            assert(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
        }

        // m1 uses internal storage, m2 uses external storage
        {
            sfl::small_flat_map<MyInt, MyString, 5> m1;
            sfl::small_flat_map<MyInt, MyString, 5> m2;

            m1.emplace(10, "/10/");
            m1.emplace(11, "/11/");
            m1.emplace(12, "/12/");

            m2.emplace(20, "/20/");
            m2.emplace(21, "/21/");
            m2.emplace(22, "/22/");
            m2.emplace(23, "/23/");
            m2.emplace(24, "/24/");
            m2.emplace(25, "/25/");

            assert(m1.size() == 3);
            assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            assert(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            assert(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            assert(m2.size() == 6);
            assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            assert(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            assert(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            assert(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");
            assert(m2.nth(5)->first == 25 && m2.nth(5)->second == "/25/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            assert(m1.size() == 6);
            assert(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            assert(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            assert(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
            assert(m1.nth(3)->first == 23 && m1.nth(3)->second == "/23/");
            assert(m1.nth(4)->first == 24 && m1.nth(4)->second == "/24/");
            assert(m1.nth(5)->first == 25 && m1.nth(5)->second == "/25/");

            assert(m2.size() == 3);
            assert(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
            assert(m2.nth(1)->first == 11 && m2.nth(1)->second == "/11/");
            assert(m2.nth(2)->first == 12 && m2.nth(2)->second == "/12/");
        }

        // m1 uses external storage, m2 uses internal storage
        {
            sfl::small_flat_map<MyInt, MyString, 5> m1;
            sfl::small_flat_map<MyInt, MyString, 5> m2;

            m1.emplace(10, "/10/");
            m1.emplace(11, "/11/");
            m1.emplace(12, "/12/");
            m1.emplace(13, "/13/");
            m1.emplace(14, "/14/");
            m1.emplace(15, "/15/");

            m2.emplace(20, "/20/");
            m2.emplace(21, "/21/");
            m2.emplace(22, "/22/");

            assert(m1.size() == 6);
            assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            assert(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            assert(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");
            assert(m1.nth(3)->first == 13 && m1.nth(3)->second == "/13/");
            assert(m1.nth(4)->first == 14 && m1.nth(4)->second == "/14/");
            assert(m1.nth(5)->first == 15 && m1.nth(5)->second == "/15/");

            assert(m2.size() == 3);
            assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            assert(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            assert(m1.size() == 3);
            assert(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            assert(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            assert(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");

            assert(m2.size() == 6);
            assert(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
            assert(m2.nth(1)->first == 11 && m2.nth(1)->second == "/11/");
            assert(m2.nth(2)->first == 12 && m2.nth(2)->second == "/12/");
            assert(m2.nth(3)->first == 13 && m2.nth(3)->second == "/13/");
            assert(m2.nth(4)->first == 14 && m2.nth(4)->second == "/14/");
            assert(m2.nth(5)->first == 15 && m2.nth(5)->second == "/15/");
        }

        // m1 uses external storage, m2 uses external storage
        {
            sfl::small_flat_map<MyInt, MyString, 5> m1;
            sfl::small_flat_map<MyInt, MyString, 5> m2;

            m1.emplace(10, "/10/");
            m1.emplace(11, "/11/");
            m1.emplace(12, "/12/");
            m1.emplace(13, "/13/");
            m1.emplace(14, "/14/");
            m1.emplace(15, "/15/");

            m2.emplace(20, "/20/");
            m2.emplace(21, "/21/");
            m2.emplace(22, "/22/");
            m2.emplace(23, "/23/");
            m2.emplace(24, "/24/");
            m2.emplace(25, "/25/");

            assert(m1.size() == 6);
            assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            assert(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            assert(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");
            assert(m1.nth(3)->first == 13 && m1.nth(3)->second == "/13/");
            assert(m1.nth(4)->first == 14 && m1.nth(4)->second == "/14/");
            assert(m1.nth(5)->first == 15 && m1.nth(5)->second == "/15/");

            assert(m2.size() == 6);
            assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            assert(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            assert(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            assert(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");
            assert(m2.nth(5)->first == 25 && m2.nth(5)->second == "/25/");

            cout << ">" << endl;
            m1.swap(m2);
            cout << "<" << endl;

            assert(m1.size() == 6);
            assert(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            assert(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            assert(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
            assert(m1.nth(3)->first == 23 && m1.nth(3)->second == "/23/");
            assert(m1.nth(4)->first == 24 && m1.nth(4)->second == "/24/");
            assert(m1.nth(5)->first == 25 && m1.nth(5)->second == "/25/");

            assert(m2.size() == 6);
            assert(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
            assert(m2.nth(1)->first == 11 && m2.nth(1)->second == "/11/");
            assert(m2.nth(2)->first == 12 && m2.nth(2)->second == "/12/");
            assert(m2.nth(3)->first == 13 && m2.nth(3)->second == "/13/");
            assert(m2.nth(4)->first == 14 && m2.nth(4)->second == "/14/");
            assert(m2.nth(5)->first == 15 && m2.nth(5)->second == "/15/");
        }
    }

    cout << "Test at(const Key&)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;
        const auto& rm = m;

        {
            m.emplace(10, "/10/");

            assert(m.size() == 1);
        }

        {
            bool exception_caught = false;

            try
            {
                assert(m.at(10) == "/10/");
            }
            catch (...)
            {}

            assert(!exception_caught);
        }

        {
            bool exception_caught = false;

            try
            {
                assert(rm.at(10) == "/10/");
            }
            catch (...)
            {}

            assert(!exception_caught);
        }

        {
            bool exception_caught = false;

            try
            {
                assert(m.at(15) == "/15/");
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
                assert(rm.at(15) == "/15/");
            }
            catch (...)
            {
                exception_caught = true;
            }

            assert(exception_caught);
        }
    }

    cout << "Test operator[]." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m;

        {
            m.emplace(10, "/10/");

            assert(m.size() == 1);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const MyInt i(10);

            assert(m[i] == "/10/");
            assert(m.size() == 1);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            assert(m[10] == "/10/");
            assert(m.size() == 1);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
        }

        {
            const MyInt i(20);

            assert(m[i] == "");
            assert(m.size() == 2);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "");

            m[i] = "/20/";

            assert(m.size() == 2);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
        }

        {
            assert(m[30] == "");
            assert(m.size() == 3);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "");

            m[30] = "/30/";

            assert(m.size() == 3);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }
    }

    cout << "Test reserve and shrink_to_fit (N > 0)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 5> m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.capacity() == 5);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.reserve(4);
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.capacity() == 5);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.reserve(10);
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.reserve(6);
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.shrink_to_fit();
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.capacity() == 5);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }
    }

    cout << "Test reserve and shrink_to_fit (N == 0)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 0> m;

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.capacity() == 4);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.reserve(4);
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.capacity() == 4);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.reserve(10);
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.reserve(6);
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.capacity() == 10);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.shrink_to_fit();
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.capacity() == 3);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            m.clear();
            cout << "<" << endl;

            cout << ">" << endl;
            m.shrink_to_fit();
            cout << "<" << endl;

            assert(m.size() == 0);
            assert(m.capacity() == 0);
        }

        {
            cout << ">" << endl;
            m.emplace(10, "/10/");
            m.emplace(20, "/20/");
            m.emplace(30, "/30/");
            cout << "<" << endl;

            assert(m.size() == 3);
            assert(m.capacity() == 4);
            assert(m.nth(0)->first == 10 && m.nth(0)->second == "/10/");
            assert(m.nth(1)->first == 20 && m.nth(1)->second == "/20/");
            assert(m.nth(2)->first == 30 && m.nth(2)->second == "/30/");
        }
    }

    cout << "Test empty constructors." << endl;
    {
        std::less<MyInt> comp;
        std::allocator<MyInt> alloc;

        sfl::small_flat_map<MyInt, MyString, 10> m1;
        sfl::small_flat_map<MyInt, MyString, 10> m2(comp);
        sfl::small_flat_map<MyInt, MyString, 10> m3(alloc);
        sfl::small_flat_map<MyInt, MyString, 10> m4(comp, alloc);

        assert(m1.size() == 0);
        assert(m1.capacity() == 10);

        assert(m2.size() == 0);
        assert(m2.capacity() == 10);

        assert(m3.size() == 0);
        assert(m3.capacity() == 10);

        assert(m4.size() == 0);
        assert(m4.capacity() == 10);
    }

    cout << "Test range constructors." << endl;
    {
        std::less<MyInt> comp;
        std::allocator<MyInt> alloc;

        const std::vector<std::pair<MyInt, MyString>> v
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );

        sfl::small_flat_map<MyInt, MyString, 10> m1(v.begin(), v.end());
        sfl::small_flat_map<MyInt, MyString, 10> m2(v.begin(), v.end(), comp);
        sfl::small_flat_map<MyInt, MyString, 10> m3(v.begin(), v.end(), alloc);
        sfl::small_flat_map<MyInt, MyString, 10> m4(v.begin(), v.end(), comp, alloc);

        assert(m1.size() == 3);
        assert(m1.capacity() == 10);
        assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        assert(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        assert(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        assert(m2.size() == 3);
        assert(m2.capacity() == 10);
        assert(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
        assert(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        assert(m2.nth(2)->first == 30 && m2.nth(2)->second == "/30/");

        assert(m3.size() == 3);
        assert(m3.capacity() == 10);
        assert(m3.nth(0)->first == 10 && m3.nth(0)->second == "/10/");
        assert(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        assert(m3.nth(2)->first == 30 && m3.nth(2)->second == "/30/");

        assert(m4.size() == 3);
        assert(m4.capacity() == 10);
        assert(m4.nth(0)->first == 10 && m4.nth(0)->second == "/10/");
        assert(m4.nth(1)->first == 20 && m4.nth(1)->second == "/20/");
        assert(m4.nth(2)->first == 30 && m4.nth(2)->second == "/30/");
    }

    cout << "Test initializer_list constructors." << endl;
    {
        std::less<MyInt> comp;
        std::allocator<MyInt> alloc;

        sfl::small_flat_map<MyInt, MyString, 10> m1
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );
        sfl::small_flat_map<MyInt, MyString, 10> m2
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }, comp
        );
        sfl::small_flat_map<MyInt, MyString, 10> m3
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }, alloc
        );
        sfl::small_flat_map<MyInt, MyString, 10> m4
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }, comp, alloc
        );

        assert(m1.size() == 3);
        assert(m1.capacity() == 10);
        assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        assert(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        assert(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        assert(m2.size() == 3);
        assert(m2.capacity() == 10);
        assert(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
        assert(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        assert(m2.nth(2)->first == 30 && m2.nth(2)->second == "/30/");

        assert(m3.size() == 3);
        assert(m3.capacity() == 10);
        assert(m3.nth(0)->first == 10 && m3.nth(0)->second == "/10/");
        assert(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        assert(m3.nth(2)->first == 30 && m3.nth(2)->second == "/30/");

        assert(m4.size() == 3);
        assert(m4.capacity() == 10);
        assert(m4.nth(0)->first == 10 && m4.nth(0)->second == "/10/");
        assert(m4.nth(1)->first == 20 && m4.nth(1)->second == "/20/");
        assert(m4.nth(2)->first == 30 && m4.nth(2)->second == "/30/");
    }

    cout << "Test copy constructors (N > 0)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m1
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );

        sfl::small_flat_map<MyInt, MyString, 10> m2(m1);

        sfl::small_flat_map<MyInt, MyString, 10> m3(m1, std::allocator<MyInt>());

        assert(m1.size() == 3);
        assert(m1.capacity() == 10);
        assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        assert(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        assert(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        assert(m2.size() == 3);
        assert(m2.capacity() == 10);
        assert(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
        assert(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        assert(m2.nth(2)->first == 30 && m2.nth(2)->second == "/30/");

        assert(m3.size() == 3);
        assert(m3.capacity() == 10);
        assert(m3.nth(0)->first == 10 && m3.nth(0)->second == "/10/");
        assert(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        assert(m3.nth(2)->first == 30 && m3.nth(2)->second == "/30/");
    }

    cout << "Test copy constructors (N == 0)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 0> m1
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );

        sfl::small_flat_map<MyInt, MyString, 0> m2(m1);

        sfl::small_flat_map<MyInt, MyString, 0> m3(m1, std::allocator<MyInt>());

        assert(m1.size() == 3);
        assert(m1.capacity() == 4);
        assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        assert(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        assert(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        assert(m2.size() == 3);
        assert(m2.capacity() == 3);
        assert(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
        assert(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        assert(m2.nth(2)->first == 30 && m2.nth(2)->second == "/30/");

        assert(m3.size() == 3);
        assert(m3.capacity() == 3);
        assert(m3.nth(0)->first == 10 && m3.nth(0)->second == "/10/");
        assert(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        assert(m3.nth(2)->first == 30 && m3.nth(2)->second == "/30/");
    }

    cout << "Test move constructors (N > 0)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m1
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );

        assert(m1.size() == 3);
        assert(m1.capacity() == 10);
        assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        assert(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        assert(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        sfl::small_flat_map<MyInt, MyString, 10> m2(std::move(m1));

        assert(m1.size() == 0);
        assert(m1.capacity() == 10);

        assert(m2.size() == 3);
        assert(m2.capacity() == 10);
        assert(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
        assert(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        assert(m2.nth(2)->first == 30 && m2.nth(2)->second == "/30/");

        sfl::small_flat_map<MyInt, MyString, 10> m3(std::move(m2), std::allocator<MyInt>());

        assert(m2.size() == 0);
        assert(m2.capacity() == 10);

        assert(m3.size() == 3);
        assert(m3.capacity() == 10);
        assert(m3.nth(0)->first == 10 && m3.nth(0)->second == "/10/");
        assert(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        assert(m3.nth(2)->first == 30 && m3.nth(2)->second == "/30/");
    }

    cout << "Test move constructors (N == 0)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 0> m1
        (
            {
                {10, "/10/"},
                {30, "/30/"},
                {20, "/20/"},
                {10, "/910/"},
                {20, "/920/"}
            }
        );

        assert(m1.size() == 3);
        assert(m1.capacity() == 4);
        assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        assert(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        assert(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        sfl::small_flat_map<MyInt, MyString, 0> m2(std::move(m1));

        assert(m1.size() == 0);
        assert(m1.capacity() == 0);

        assert(m2.size() == 3);
        assert(m2.capacity() == 4);
        assert(m2.nth(0)->first == 10 && m2.nth(0)->second == "/10/");
        assert(m2.nth(1)->first == 20 && m2.nth(1)->second == "/20/");
        assert(m2.nth(2)->first == 30 && m2.nth(2)->second == "/30/");

        sfl::small_flat_map<MyInt, MyString, 0> m3(std::move(m2), std::allocator<MyInt>());

        assert(m2.size() == 0);
        assert(m2.capacity() == 0);

        assert(m3.size() == 3);
        assert(m3.capacity() == 4);
        assert(m3.nth(0)->first == 10 && m3.nth(0)->second == "/10/");
        assert(m3.nth(1)->first == 20 && m3.nth(1)->second == "/20/");
        assert(m3.nth(2)->first == 30 && m3.nth(2)->second == "/30/");
    }

    cout << "Test copy assignment operator." << endl;
    {
        // n <= capacity && n <= size
        {
            sfl::small_flat_map<MyInt, MyString, 5> m1
            (
                {
                    {10, "/10/"},
                    {11, "/11/"},
                    {12, "/12/"}
                }
            );

            assert(m1.size() == 3);
            assert(m1.capacity() == 5);
            assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            assert(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            assert(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            sfl::small_flat_map<MyInt, MyString, 5> m2
            (
                {
                    {20, "/20/"},
                    {21, "/21/"}
                }
            );

            assert(m2.size() == 2);
            assert(m2.capacity() == 5);
            assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");

            cout << ">" << endl;
            m1 = m2;
            cout << "<" << endl;

            assert(m1.size() == 2);
            assert(m1.capacity() == 5);
            assert(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            assert(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");

            assert(m2.size() == 2);
            assert(m2.capacity() == 5);
            assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
        }

        // n <= capacity && n > size
        {
            sfl::small_flat_map<MyInt, MyString, 5> m1
            (
                {
                    {10, "/10/"},
                    {11, "/11/"},
                    {12, "/12/"}
                }
            );

            assert(m1.size() == 3);
            assert(m1.capacity() == 5);
            assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            assert(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            assert(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            sfl::small_flat_map<MyInt, MyString, 5> m2
            (
                {
                    {20, "/20/"},
                    {21, "/21/"},
                    {22, "/22/"},
                    {23, "/23/"},
                    {24, "/24/"}
                }
            );

            assert(m2.size() == 5);
            assert(m2.capacity() == 5);
            assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            assert(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            assert(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            assert(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");

            cout << ">" << endl;
            m1 = m2;
            cout << "<" << endl;

            assert(m1.size() == 5);
            assert(m1.capacity() == 5);
            assert(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            assert(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            assert(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
            assert(m1.nth(3)->first == 23 && m1.nth(3)->second == "/23/");
            assert(m1.nth(4)->first == 24 && m1.nth(4)->second == "/24/");

            assert(m2.size() == 5);
            assert(m2.capacity() == 5);
            assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            assert(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            assert(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            assert(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");
        }

        // n > capacity
        {
            sfl::small_flat_map<MyInt, MyString, 5> m1
            (
                {
                    {10, "/10/"},
                    {11, "/11/"},
                    {12, "/12/"}
                }
            );

            assert(m1.size() == 3);
            assert(m1.capacity() == 5);
            assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            assert(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
            assert(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

            sfl::small_flat_map<MyInt, MyString, 5> m2
            (
                {
                    {20, "/20/"},
                    {21, "/21/"},
                    {22, "/22/"},
                    {23, "/23/"},
                    {24, "/24/"},
                    {25, "/25/"}
                }
            );

            assert(m2.size() == 6);
            assert(m2.capacity() == 10);
            assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            assert(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            assert(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            assert(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");
            assert(m2.nth(5)->first == 25 && m2.nth(5)->second == "/25/");

            cout << ">" << endl;
            m1 = m2;
            cout << "<" << endl;

            assert(m1.size() == 6);
            assert(m1.capacity() == 6);
            assert(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
            assert(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
            assert(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
            assert(m1.nth(3)->first == 23 && m1.nth(3)->second == "/23/");
            assert(m1.nth(4)->first == 24 && m1.nth(4)->second == "/24/");
            assert(m1.nth(5)->first == 25 && m1.nth(5)->second == "/25/");

            assert(m2.size() == 6);
            assert(m2.capacity() == 10);
            assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
            assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
            assert(m2.nth(2)->first == 22 && m2.nth(2)->second == "/22/");
            assert(m2.nth(3)->first == 23 && m2.nth(3)->second == "/23/");
            assert(m2.nth(4)->first == 24 && m2.nth(4)->second == "/24/");
            assert(m2.nth(5)->first == 25 && m2.nth(5)->second == "/25/");
        }
    }

    cout << "Test move assignment operator (N > 0)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 5> m1
        (
            {
                {10, "/10/"},
                {11, "/11/"},
                {12, "/12/"}
            }
        );

        assert(m1.size() == 3);
        assert(m1.capacity() == 5);
        assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        assert(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
        assert(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

        sfl::small_flat_map<MyInt, MyString, 5> m2
        (
            {
                {20, "/20/"},
                {21, "/21/"}
            }
        );

        assert(m2.size() == 2);
        assert(m2.capacity() == 5);
        assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
        assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");

        cout << ">" << endl;
        m1 = std::move(m2);
        cout << "<" << endl;

        assert(m1.size() == 2);
        assert(m1.capacity() == 5);
        assert(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
        assert(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");

        assert(m2.size() == 0);
        assert(m2.capacity() == 5);

        cout << ">" << endl;
        m2 = std::move(m1);
        cout << "<" << endl;

        assert(m1.size() == 0);
        assert(m1.capacity() == 5);

        assert(m2.size() == 2);
        assert(m2.capacity() == 5);
        assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
        assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");
    }

    cout << "Test move assignment operator (N == 0)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 0> m1
        (
            {
                {10, "/10/"},
                {11, "/11/"},
                {12, "/12/"}
            }
        );

        assert(m1.size() == 3);
        assert(m1.capacity() == 4);
        assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        assert(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
        assert(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

        sfl::small_flat_map<MyInt, MyString, 0> m2
        (
            {
                {20, "/20/"},
                {21, "/21/"}
            }
        );

        assert(m2.size() == 2);
        assert(m2.capacity() == 2);
        assert(m2.nth(0)->first == 20 && m2.nth(0)->second == "/20/");
        assert(m2.nth(1)->first == 21 && m2.nth(1)->second == "/21/");

        cout << ">" << endl;
        m1 = std::move(m2);
        cout << "<" << endl;

        assert(m1.size() == 2);
        assert(m1.capacity() == 2);
        assert(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
        assert(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");

        assert(m2.size() == 0);
        assert(m2.capacity() == 0);

        sfl::small_flat_map<MyInt, MyString, 0> m3
        (
            {
                {30, "/30/"},
                {31, "/31/"}
            }
        );

        assert(m3.size() == 2);
        assert(m3.capacity() == 2);
        assert(m3.nth(0)->first == 30 && m3.nth(0)->second == "/30/");
        assert(m3.nth(1)->first == 31 && m3.nth(1)->second == "/31/");

        cout << ">" << endl;
        m3 = std::move(m1);
        cout << "<" << endl;

        assert(m1.size() == 0);
        assert(m1.capacity() == 0);

        assert(m3.size() == 2);
        assert(m3.capacity() == 2);
        assert(m3.nth(0)->first == 20 && m3.nth(0)->second == "/20/");
        assert(m3.nth(1)->first == 21 && m3.nth(1)->second == "/21/");
    }

    cout << "Test initializer_list assignment operator." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 5> m1
        (
            {
                {10, "/10/"},
                {11, "/11/"},
                {12, "/12/"}
            }
        );

        assert(m1.size() == 3);
        assert(m1.capacity() == 5);
        assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        assert(m1.nth(1)->first == 11 && m1.nth(1)->second == "/11/");
        assert(m1.nth(2)->first == 12 && m1.nth(2)->second == "/12/");

        cout << ">" << endl;
        m1 = {
            {20, "/20/"},
            {22, "/22/"},
            {21, "/21/"},
            {20, "/20/"},
            {21, "/21/"},
        };
        cout << "<" << endl;

        assert(m1.size() == 3);
        assert(m1.capacity() == 5);
        assert(m1.nth(0)->first == 20 && m1.nth(0)->second == "/20/");
        assert(m1.nth(1)->first == 21 && m1.nth(1)->second == "/21/");
        assert(m1.nth(2)->first == 22 && m1.nth(2)->second == "/22/");
    }

    cout << "Test non-member comparison operators." << endl;
    {
        sfl::small_flat_map<int, char, 5> m1
        (
            {
                {1, 'a'},
                {2, 'b'},
                {3, 'c'}
            }
        );

        sfl::small_flat_map<int, char, 5> m2
        (
            {
                {1, 'a'},
                {2, 'b'},
                {3, 'c'},
                {4, 'd'}
            }
        );

        assert(m1 == m1);
        assert(m1 != m2);
        assert(m1 < m2);
        assert(m2 > m1);
        assert(m1 <= m1);
        assert(m1 <= m2);
        assert(m2 >= m2);
        assert(m2 >= m1);
    }

    cout << "Test non-member swap." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 5> m1
        (
            {
                {10, "/10/"},
                {11, "/11/"},
                {12, "/12/"}
            }
        );

        sfl::small_flat_map<MyInt, MyString, 5> m2
        (
            {
                {20, "/20/"},
                {21, "/21/"}
            }
        );

        using std::swap;
        swap(m1, m2);
    }

    cout << "Test non-member erase_if(small_flat_map&, Predicate)." << endl;
    {
        sfl::small_flat_map<MyInt, MyString, 10> m1
        (
            {
                {10, "/10/"},
                {20, "/20/"},
                {30, "/30/"}
            }
        );

        using const_reference =
            typename sfl::small_flat_map<MyInt, MyString, 10>::const_reference;

        assert(m1.size() == 3);
        assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
        assert(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
        assert(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");

        {
            cout << ">" << endl;
            auto res = erase_if
            (
                m1,
                [](const_reference& val){ return val.first == 42; }
            );
            cout << "<" << endl;

            assert(res == 0);
            assert(m1.size() == 3);
            assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            assert(m1.nth(1)->first == 20 && m1.nth(1)->second == "/20/");
            assert(m1.nth(2)->first == 30 && m1.nth(2)->second == "/30/");
        }

        {
            cout << ">" << endl;
            auto res = erase_if
            (
                m1,
                [](const_reference& val){ return val.first == 20; }
            );
            cout << "<" << endl;

            assert(res == 1);
            assert(m1.size() == 2);
            assert(m1.nth(0)->first == 10 && m1.nth(0)->second == "/10/");
            assert(m1.nth(1)->first == 30 && m1.nth(1)->second == "/30/");
        }
    }
}
