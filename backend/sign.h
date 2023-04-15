#pragma once

#include <iostream>
#include <deque>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

class sign
{
public:
    sign();
    sign(const char* name, const bool& term = true);
    sign(const std::string& name, const bool& term = true);
    sign(const sign& a);
    std::string to_string() const;
    bool Is_terminal() const;
    bool Is_empty() const;
    bool Is_equal(const std::string& s);
    void gen_sign();
    sign& operator=(const char*);
    sign& operator=(const sign&);
    friend std::ostream& operator<<(std::ostream& s, sign a);

    std::string str;

private:
    bool t;

public:
    constexpr auto friend operator<=>(const sign& left, const sign& right) 
    {
        if (left.str < right.str)
        {
            return std::strong_ordering::less;
        }
        else if (left.str > right.str)
        {
            return std::strong_ordering::greater;
        }
        return std::strong_ordering::equivalent;
    }

    constexpr bool friend operator==(const sign& a, const sign& b) { return a.str == b.str; }
    constexpr bool friend operator!=(const sign& a, const sign& b) { return !(a.str == b.str); }
};
