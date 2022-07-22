#pragma once

#include "s_rule.h"
#include <exception>
#include <set>
#include <vector>

/*
#ifdef BUILDING_DLL
#define GRAMMAR __declspec(dllexport)
#else
#define GRAMMAR __declspec(dllimport)
#endif
*/

class /*GRAMMAR*/ grammar
{
	friend class greibach;	
	friend class early_alg;
	friend class push_down;
    friend class gr_to_pd;
    friend class pd_to_gr;
public:
	grammar();
	grammar(const char* fname);
	grammar(const sign_list &n ,const sign_list &t,const std::map<sign,std::list<sign_list> >& p,const sign& s);
	~grammar();
	friend /*GRAMMAR*/ std::ostream& operator<<(std::ostream &s,const grammar a);
	
//	void early_alg(std::vector<sign> a);
	void reduction();
	grammar chomsky() const;
    	std::string to_string() const;
	void to_file(const std::string &fname) const;
    void find_derivables();
    void rename();
private:

	sign_list N;
	sign_list T;
	std::map<sign,std::list<sign_list> > P;
	sign S;

	void split(const std::string str,sign_list &v,const char delim=' ');
	void split(const sign str,sign_list &v,const char delim=' ');

    void make_combination_list(std::vector<std::vector<int> >&, std::vector<int>, int, int, int);
    std::list<sign_list> make_comb_rules(std::vector<int>,std::set<int>,const sign_list &);

    void replace(const sign&,const sign&);
	std::map<sign,int> make_sort();
	sign_list::iterator erase(const sign a);
	bool find_rule(const sign_list &a,sign &b);

    void eliminate_t();
	void eliminate_epsilon(); 	
	std::set<sign> make_epsilon_set(sign e);
	sign gen_sign();
	std::list<sign_list>::iterator findprefix(const sign a);

    void substitute_pd_e_rules();
	
};
