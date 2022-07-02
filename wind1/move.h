#ifndef MOVE_H
#define MOVE_H
#include "sign.h"

struct move
{
    sign stack;
    sign c_state;
    sign c_terminal;
    move(const sign& s1,const sign& s2,const sign& s3) :stack(s1) , c_state(s2) , c_terminal(s3)
    {}
    move(const sign& s1,const sign& s2):stack(s1) , c_state(s2)
    {
        sign tmp ("e");
        c_terminal=tmp;
    }
    bool friend operator<(const move& a,const move& b)
    {

        if(a.c_state!=b.c_state)
        {
            return a.c_state<b.c_state;
        }
        else if(a.c_terminal!=b.c_terminal)
        {
            return a.c_terminal<b.c_terminal;
        }
        else
        {
            return a.stack<b.stack;
        }
    }
    std::string to_string()
    {
        sign e("e");
        std::string str;
        if(c_terminal==e)
        {
             str=stack.to_string() + " q<sub>" + c_state.to_string() + "</sub> ";
        }
        else
        {
            str=stack.to_string() + " q<sub>" + c_state.to_string() + "</sub> " + c_terminal.to_string() + " ";
        }
        return str;
    }

};


#endif // MOVE_H
