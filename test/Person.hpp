#ifndef SFL_PERSON_HPP
#define SFL_PERSON_HPP

#include <iostream>
#include <string>

class Person
{
private:

    int id_;
    std::string name_;

public:

    explicit Person(int id, const std::string& name) : id_(id), name_(name)
    {}

    int id() const
    {
        return id_;
    }

    std::string name() const
    {
        return name_;
    }
};

struct PersonLess
{
    using is_transparent = void;

    bool operator()(const Person& e1, const Person& e2) const
    {
        return e1.id() < e2.id();
    }

    bool operator()(int id, const Person& e) const
    {
        return id < e.id();
    }

    bool operator()(const Person& e, int id) const
    {
        return e.id() < id;
    }
};

struct PersonEqual
{
    using is_transparent = void;

    bool operator()(const Person& e1, const Person& e2) const
    {
        return e1.id() == e2.id();
    }

    bool operator()(int id, const Person& e) const
    {
        return id == e.id();
    }

    bool operator()(const Person& e, int id) const
    {
        return e.id() == id;
    }
};

std::ostream& operator<<(std::ostream& os, const Person& e)
{
    return os << "{" << e.id() << ", " << e.name() << "}";
}

#endif // SFL_PERSON_HPP
