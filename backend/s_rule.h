#pragma once

#include "sign_list.h"

class s_rule
{
	
	sign n;
	int dot;
    sign_list r;

	public:
	
	s_rule(sign k,const sign_list& a,int n);

	int get_dot() const;
	void set_dot(const int a);
	sign get_n() const;
	std::string to_string() const;

    constexpr auto operator<=>(const s_rule&) const = default;


	friend std::ostream& operator<<(std::ostream &s,const s_rule &a);


    sign& operator[](const int &i);
    const sign& operator[](const int &i) const;
    int size() const;
};
