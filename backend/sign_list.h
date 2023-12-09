#pragma once

#include <initializer_list>
#include <deque>
#include <string>

import formal_languages;

class sign_list : public std::deque<sign>
{

public:
	
	typedef std::deque<sign>::iterator iterator;
	typedef std::deque<sign>::const_iterator const_iterator;


	sign_list();
    sign_list(std::initializer_list<sign> init);

	void push_front(const sign&);

    void push_front(const sign_list&);



    sign_list::iterator erase(const sign&);


	auto operator<=>(const sign_list& a) const = default;

	std::string to_string() const;	
	friend std::ostream& operator<<(std::ostream &s,sign_list a);
	
};


