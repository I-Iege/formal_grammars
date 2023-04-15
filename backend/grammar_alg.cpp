#include "grammar_alg.h"
#include <string>

grammar_alg::grammar_alg() { alg_it = 0; }

grammar_alg::~grammar_alg() {}

void grammar_alg::next()
{
    if (alg_it < (int)(info.size() - 1))
    {
        ++alg_it;
    }
}
void grammar_alg::back()
{
    if (alg_it > 0)
    {
        --alg_it;
    }
}

std::string grammar_alg::progress() const
{
    std::string s;
    s += std::to_string(alg_it + 1);
    s += "/";
    s += std::to_string(info.size());
    return s;
}

std::string grammar_alg::show_info() const
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
