#pragma once

#include <iostream>
#include <deque>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

class sign
{
	public:
        sign();
        sign(const char* name,const bool& term=true);
		sign(const std::string& name,const bool& term=true);
		sign(const sign& a);
		std::string to_string() const;
		bool Is_terminal() const;
		bool Is_empty() const;
		bool Is_equal(const std::string& s);
		void gen_sign();
		sign& operator=(const char*);
		sign& operator=(const sign&);
        friend std::ostream& operator<<(std::ostream &s,sign a);

        bool friend operator==(const sign&, const sign&);
        bool friend operator!=(const sign&,const sign&);
		bool friend operator<(const sign&,const sign&);
        bool friend operator>(const sign&,const sign&);


		std::string str;
    private:
		bool t;
};

