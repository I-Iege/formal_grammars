#pragma once

#include <iostream>
#include <vector>
#include <string>

export module formal_languages:grammar_alg;

export class grammar_alg
{
public:

   grammar_alg() { alg_it = 0; }

    ~grammar_alg() {}

    void next()
    {
        if (alg_it < (int)(info.size() - 1))
        {
            ++alg_it;
        }
    }
    void back()
    {
        if (alg_it > 0)
        {
            --alg_it;
        }
    }

    std::string progress() const
    {
        std::string s;
        s += std::to_string(alg_it + 1);
        s += "/";
        s += std::to_string(info.size());
        return s;
    }

    std::string show_info() const
    {
        if ((alg_it < (int)info.size() - 1))
        {
            return info[alg_it];
        }
        else
        {
            return "ok";
        }
    }

    virtual std::string to_string() const=0;

protected:
int alg_it;
std::vector<std::string> info;

};

