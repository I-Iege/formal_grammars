#pragma once
#include <algorithm>
#include <ranges>
#include <deque>

export module formal_languages:sign_list; 

export import :sign;

//import <algorithm>;
//import <ranges>;
//import <deque>;

using namespace std::ranges;

export class sign_list : public std::deque<sign>
{
public:
    typedef std::deque<sign>::iterator iterator;
    typedef std::deque<sign>::const_iterator const_iterator;

    sign_list() {}

    sign_list(std::initializer_list<sign> init)
        : std::deque<sign>(init)
    {
    }

    void push_front(const sign& a) { deque::push_front(a); }

    void push_front(const sign_list& a)
    {
        for_each(a, [this](const sign& s) { push_front(s); });
    }

    sign_list::iterator erase(const sign& a)
    {

        auto it = find(*this, a);
        if (it != end())
        {
            it = std::deque<sign>::erase(it);
        }
        return it;
    }

    std::string to_string() const
    {
        std::string s = "";
        for (const sign& sign : *this)
        {
            s += " " + sign.to_string();
        }
        return s;
    }

    friend std::ostream& operator<<(std::ostream& s, sign_list a)
    {
        s << a.to_string();
        return s;
    }

    auto operator<=>(const sign_list& a) const = default;
};
