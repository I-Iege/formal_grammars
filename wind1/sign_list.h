#pragma once

#include "sign.h"

class sign_list
{
protected:
	std::deque<sign> r;
public:
	
	typedef std::deque<sign>::iterator iterator;
	typedef std::deque<sign>::const_iterator const_iterator;
	sign_list::iterator begin();
	sign_list::iterator end();
	sign_list::const_iterator begin() const;
	sign_list::const_iterator end() const;

	sign_list();
	sign_list(const sign_list& a);
	sign& operator[](const int&);
	const sign& operator[](const int&) const;
	void pop_front();
	void pop_back();
	void push_front(const sign&);
	void push_front(const sign_list&);
	void push_back(const sign&);
    void clear();
	sign& find(const sign&);
	int size() const;
    sign_list::iterator erase(sign_list::iterator);
	sign_list::iterator erase(const sign&);
    bool friend operator<(const sign_list&,const sign_list&);
	friend bool operator==(const sign_list &a, const sign_list &b);
    friend bool operator!=(const sign_list &a, const sign_list &b);
	std::string to_string() const;	
	friend std::ostream& operator<<(std::ostream &s,sign_list a);
	
};


