#pragma once

#include "grammar_alg.h"
#include "push_down.h"

class pd_to_gr :public grammar_alg
{

public:
    pd_to_gr(const push_down& pd);
    ~pd_to_gr();
    grammar get_grammar() const;
    std::string to_string() const;
private:
    std::vector<grammar> gr;

};
