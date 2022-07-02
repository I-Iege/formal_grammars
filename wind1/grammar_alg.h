#pragma once

#include <iostream>
#include <vector>

class grammar_alg
{
public:
    grammar_alg();
    virtual ~grammar_alg();
    void next();
    void back();
    std::string show_info() const;
    std::string progress() const;

    virtual std::string to_string() const=0;

protected:
int alg_it;
std::vector<std::string> info;

};

