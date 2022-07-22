#include "sign_list.h"

using namespace std::ranges;

sign_list::sign_list()
{
}

void sign_list::push_front(const sign &a)
{
    deque::push_front(a);
}

void sign_list::push_front(const sign_list &a)
{
    for_each(a, [this](const sign& s){
        push_front(s);
    });
}

sign_list::iterator sign_list::erase(const sign &a)
{
    auto it=find(*this,a);
    if(it!=end())
	{
        it=erase(*it);
	}
	return it;
}

bool operator==(const sign_list &a, const sign_list &b)
{
    return a==b;
}

bool operator!=(const sign_list &a, const sign_list &b)
{
    return a!=b;
}

std::string sign_list::to_string() const
{
	std::string s="";
    for(const sign& sign : *this )
    {
        s+=" " + sign.to_string();
    }
	return s;
}

bool operator<(const sign_list& a,const sign_list& b)
{
    return a<b;
}

std::ostream& operator<<(std::ostream &s,sign_list a)
{
	s<<a.to_string();
	return s;
}



