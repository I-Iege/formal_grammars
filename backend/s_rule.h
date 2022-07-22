#pragma once

#include "sign_list.h"

class s_rule
{
	
	sign n;
	int dot;
    sign_list r;

	public:
	
	s_rule(sign k,const sign_list& a,int n);
	bool friend operator<(const s_rule& a, const s_rule& b);
	bool friend operator==(const s_rule& a, const s_rule& b);
	bool friend operator!=(const s_rule& a, const s_rule& b);
	int get_dot() const;
	void set_dot(const int a);
	sign get_n() const;
	std::string to_string() const;
	friend std::ostream& operator<<(std::ostream &s,const s_rule &a);


    sign& operator[](const int &i);
    const sign& operator[](const int &i) const;
    int size() const;
};
