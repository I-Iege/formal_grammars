#pragma once
#include <string>

export module formal_languages:result;

import :sign;
import :sign_list;

export struct result
{
    sign_list stack;
    sign n_state;
    result(const sign_list &sl,const sign &s2)
        : stack(sl)
        , n_state(s2)
    {
    }

    std::string to_string()
    {
        std::string str = stack.to_string() + " q<sub>" + n_state.to_string() +"</sub>";
        return str;
    }
};
