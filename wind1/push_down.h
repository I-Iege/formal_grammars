#ifndef PUSH_DOWN_H
#define PUSH_DOWN_H
#include "sign_list.h"
#include "move.h"
#include "result.h"
#include <set>
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

#endif // PUSH_DOWN_H
