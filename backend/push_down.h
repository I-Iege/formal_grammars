#pragma once

#include "move.h"
#include "result.h"
#include <set>
#include <map>
#include <list>

import formal_languages;

struct push_down
{
    std::map<move,std::list<result> > M;
    sign_list Z;
    sign_list K;
    sign_list T;
    sign Z0;
    sign Q0;
    std::set<sign> H;
};
