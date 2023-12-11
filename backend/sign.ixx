#pragma once
#include <string>
#include <ostream>


export module formal_languages:sign;

export class sign
{
public:
    sign()
        : str("")
        , t(false)
    {
    }

    sign(const std::string& name, const bool& term=false)
        : str(name)
        , t(term)
    {
    }

    sign(const char* name, const bool& term=false)
        : str(name)
        , t(term)
    {
    }

    sign(const sign& a)
    {
        this->str = a.str;
        this->t = a.t;
    }

    std::string to_string() const { return str; }
    bool Is_empty() const { return (str.length() == 0); }

    bool Is_terminal() const { return t; }

    bool Is_equal(const std::string& s) { return this->str == s; }

    void gen_sign()
    {
        char v1 = (rand() % 26) + 65;
        char v2[2];
        v2[0] = v1;
        v2[1] = '\0';
        this->str = std::string(v2);
        this->t = false;
    }
    sign& operator=(const char* a)
    {
        this->str = a;
        this->t = false;
        return *this;
    }
    sign& operator=(const sign& a)
    {
        this->str = a.str;
        this->t = a.t;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& s, sign a)
    {
        s << a.to_string();
        return s;
    }

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
