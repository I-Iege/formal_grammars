#pragma once
#include <ostream>
#include <compare>

export module formal_languages:s_rule;

import :sign;
import :sign_list;

export class s_rule
{
	
	sign n;
	int dot;
    sign_list r;

public:
	s_rule(sign k, const sign_list& a, int n)
        : n(k)
        , dot(n)
        , r(a)
    {
    }

    int get_dot() const { return this->dot; }

    void set_dot(const int a) { this->dot = a; }
    sign get_n() const { return this->n; }

    std::string to_string() const
    {
        std::string s = "";
        s += this->n.to_string();
        s += "->";

        for (int i = 0; i < r.size(); ++i)
        {
            if (i == this->dot)
            {
                s += ".";
            }
            s += " ";
            s += r[i].to_string();
        }
        if (r.size() == this->dot)
        {
            s += ".";
        }
        return s;
    }

    friend std::ostream& operator<<(std::ostream& s, const s_rule& a)
    {
        s << a.to_string();
        return s;
    }

    sign& operator[](const int& i) { return r[i]; }

    const sign& operator[](const int& i) const { return r[i]; }

    int size() const { return r.size(); }

    auto operator<=>(const s_rule& s) const = default;

};
