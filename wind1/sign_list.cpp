#include "sign_list.h"

sign_list::iterator sign_list::begin()
{	
	return this->r.begin();
}

sign_list::iterator sign_list::end()
{
	return this->r.end();
}

sign_list::const_iterator sign_list::begin() const
{
	return this->r.begin();
}

sign_list::const_iterator sign_list::end() const
{
	return this->r.end();
}

sign_list::sign_list()
{
}

sign_list::sign_list(const sign_list& a)
{
	this->r=a.r;
}

sign& sign_list::operator[](const int &i)
{
	return r[i];
}

const sign& sign_list::operator[](const int &i) const
{
	return r[i];
}

void sign_list::pop_front()
{
	r.pop_front();
}

void sign_list::pop_back()
{
	r.pop_back();
}

void sign_list::push_front(const sign &a)
{
	r.push_front(a);
}

void sign_list::push_front(const sign_list &a)
{
	for(int i=a.size()-1;i>=0;--i)
	{
		this->push_front(a[i]);
	}
}

void sign_list::push_back(const sign &a)
{
	r.push_back(a);
}

void sign_list::clear()
{
    r.clear();
}

int sign_list::size() const
{
	return r.size();
}

sign& sign_list::find(const sign &s)
{
	return *(std::find(r.begin(),r.end(),s));
}

sign_list::iterator sign_list::erase(sign_list::iterator a)
{
    sign_list::iterator it=r.erase(a);
    return it;
}

sign_list::iterator sign_list::erase(const sign &a)
{

	sign_list::iterator it=std::find(r.begin(),r.end(),a);
	if(it!=r.end())
	{
		it=r.erase(it);
	}
	return it;
}

bool operator==(const sign_list &a, const sign_list &b)
{
	return a.r==b.r;
}


bool operator!=(const sign_list &a, const sign_list &b)
{
    return a.r!=b.r;
}

std::string sign_list::to_string() const
{
	std::string s="";
	for(sign_list::const_iterator it=this->begin();it!=this->end();++it)
	{
		s+=" " + it->to_string();
	}
	return s;
}

bool operator<(const sign_list& a,const sign_list& b)
{
    return a.r<b.r;
}

std::ostream& operator<<(std::ostream &s,sign_list a)
{
	s<<a.to_string();
	return s;
}



